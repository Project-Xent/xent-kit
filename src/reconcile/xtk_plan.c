#include "xtk_plan.h"
#include "xtk_key.h"
#include "xtk_reconcile_internal.h"
#include "../xtk_hash.h"
#include "../xtk_internal.h"
#include <xtk/xtk_reconcile.h>

#include <stdint.h>
#include <string.h>

bool xtk_plan_same_type(XtkNode const *old_node, XtkEl const *next_el) {
	return old_node && next_el && old_node->type_id == XTK_EL_DATA(next_el)->type;
}

static bool same_key(XtkNode const *old_node, XtkEl const *next_el) {
	return xtk_key_present(&old_node->key) && xtk_key_equal(&old_node->key, &XTK_EL_DATA(next_el)->key);
}

bool xtk_plan_match_positional(XtkNode const *old_node, XtkEl const *next_el, int *out_old) {
	int old_n  = old_node ? old_node->child_count : 0;
	int new_n  = XTK_EL_DATA(next_el)->child_count;
	int shared = old_n < new_n ? old_n : new_n;

	for (int i = 0; i < new_n; i++) out_old [i] = -1;

	int prefix = 0;
	while (prefix < shared && xtk_plan_same_type(old_node->children [prefix], xtk_el_child(next_el, prefix))) prefix++;
	int suffix = 0;
	while (prefix + suffix < shared
		   && xtk_plan_same_type(old_node->children [shared - 1 - suffix], xtk_el_child(next_el, shared - 1 - suffix)))
		suffix++;

	for (int i = 0; i < prefix; i++) out_old [i] = i;
	for (int i = 0; i < suffix; i++) out_old [shared - 1 - i] = shared - 1 - i;

	for (int i = prefix; i < shared - suffix; i++)
		out_old [i] = xtk_plan_same_type(old_node->children [i], xtk_el_child(next_el, i)) ? i : -1;
	return true;
}

typedef struct Slot {
	uint32_t hash;
	int      old_index; /* +1; 0 empty */
} Slot;

static int lis_bisect(int const *seq, int const *tails, int len, int value) {
	int lo = 0, hi = len;
	while (lo < hi) {
		int mid = lo + (hi - lo) / 2;
		if (seq [tails [mid]] < value) lo = mid + 1;
		else hi = mid;
	}
	return lo;
}

static int lis_length(int const *seq, int n, XtkScratch *scratch, bool *in_lis) {
	for (int i = 0; i < n; i++) in_lis [i] = false;
	if (n <= 0) return 0;

	int *tails = ( int * ) xtk_scratch_reserve(scratch, sizeof(int) * ( size_t ) n, _Alignof(int));
	int *pred  = ( int * ) xtk_scratch_reserve(scratch, sizeof(int) * ( size_t ) n, _Alignof(int));
	if (!tails || !pred) return -1;

	int len = 0;
	for (int i = 0; i < n; i++) {
		int lo     = lis_bisect(seq, tails, len, seq [i]);
		pred [i]   = lo > 0 ? tails [lo - 1] : -1;
		tails [lo] = i;
		if (lo == len) len++;
	}

	int at = tails [len - 1];
	while (at >= 0) {
		in_lis [at] = true;
		at          = pred [at];
	}
	return len;
}

static int keyed_prefix(XtkNode const *old_node, XtkEl const *next_el, int old_n, int new_n, int *out_old) {
	int n     = 0;
	int limit = old_n < new_n ? old_n : new_n;
	while (n < limit) {
		if (!same_key(old_node->children [n], xtk_el_child(next_el, n))) break;
		if (!xtk_plan_same_type(old_node->children [n], xtk_el_child(next_el, n))) break;
		out_old [n] = n;
		n++;
	}
	return n;
}

static int keyed_suffix(XtkNode const *old_node, XtkEl const *next_el, int old_n, int new_n, int prefix, int *out_old) {
	int n     = 0;
	int limit = (old_n - prefix) < (new_n - prefix) ? (old_n - prefix) : (new_n - prefix);
	while (n < limit) {
		int oi = old_n - 1 - n;
		int ni = new_n - 1 - n;
		if (!same_key(old_node->children [oi], xtk_el_child(next_el, ni))) break;
		if (!xtk_plan_same_type(old_node->children [oi], xtk_el_child(next_el, ni))) break;
		out_old [ni] = oi;
		n++;
	}
	return n;
}

static uint32_t hash_cap(int old_mid) {
	uint32_t cap = 1u;
	while (cap < ( uint32_t ) old_mid * 2u) {
		if (cap > UINT32_MAX / 2u) return 0;
		cap *= 2u;
	}
	return cap;
}

static bool scratch_part(size_t *size, size_t count, size_t item, size_t align) {
	if (count && item > SIZE_MAX / count) return false;
	size_t bytes = count * item;
	if (bytes > SIZE_MAX - *size || align - 1u > SIZE_MAX - *size - bytes) return false;
	*size += bytes + align - 1u;
	return true;
}

typedef struct ScratchPart {
	size_t count;
	size_t size;
	size_t align;
} ScratchPart;

static bool keyed_scratch_ensure(XtkScratch *scratch, int old_n, int new_n) {
	uint32_t slots = hash_cap(old_n);
	if (!slots) return false;
	ScratchPart const parts [] = {
	  {( size_t ) new_n, sizeof(int),  _Alignof(int) },
	  {( size_t ) new_n, sizeof(bool), _Alignof(bool)},
	  {( size_t ) old_n, sizeof(int),  _Alignof(int) },
	  {( size_t ) old_n, sizeof(bool), _Alignof(bool)},
	  {slots,            sizeof(Slot), _Alignof(Slot)},
	  {( size_t ) new_n, sizeof(int),  _Alignof(int) },
	  {( size_t ) new_n, sizeof(int),  _Alignof(int) },
	  {( size_t ) new_n, sizeof(bool), _Alignof(bool)},
	  {( size_t ) new_n, sizeof(int),  _Alignof(int) },
	  {( size_t ) new_n, sizeof(int),  _Alignof(int) },
	};
	size_t size = 0u;
	for (size_t i = 0; i < sizeof(parts) / sizeof(parts [0]); i++)
		if (!scratch_part(&size, parts [i].count, parts [i].size, parts [i].align)) return false;
	if (scratch->used > SIZE_MAX - size) return false;
	return xtk_scratch_ensure(scratch, scratch->used + size);
}

static void hash_insert_old(Slot *slots, uint32_t cap, XtkNode const *old_node, int prefix, int old_mid) {
	uint32_t mask = cap - 1u;
	for (int i = 0; i < old_mid; i++) {
		int           oi  = prefix + i;
		XtkKey const *key = &old_node->children [oi]->key;
		uint32_t      h   = xtk_key_hash(key);
		uint32_t      s   = h & mask;
		while (slots [s].old_index != 0) s = (s + 1u) & mask;
		slots [s].hash      = h;
		slots [s].old_index = oi + 1;
	}
}

static int hash_lookup(Slot const *slots, uint32_t cap, XtkNode const *old_node, XtkEl const *want, XtkKey const *key) {
	uint32_t h    = xtk_key_hash(key);
	uint32_t mask = cap - 1u;
	uint32_t s    = h & mask;
	while (slots [s].old_index != 0) {
		int oi = slots [s].old_index - 1;
		if (slots [s].hash == h && same_key(old_node->children [oi], want)) return oi;
		s = (s + 1u) & mask;
	}
	return -1;
}

static bool match_mid_hashed(
  XtkNode const *old_node, XtkEl const *next_el, XtkScratch *scratch, int prefix, int old_mid, int new_mid,
  int *out_old, bool *claimed
) {
	uint32_t cap = hash_cap(old_mid);
	if (!cap) return false;
	Slot *slots = ( Slot * ) xtk_scratch_reserve(scratch, sizeof(Slot) * cap, _Alignof(Slot));
	if (!slots) return false;
	memset(slots, 0, sizeof(Slot) * cap);
	hash_insert_old(slots, cap, old_node, prefix, old_mid);

	for (int i = 0; i < new_mid; i++) {
		int ni = prefix + i;
		int found
		  = hash_lookup(slots, cap, old_node, xtk_el_child(next_el, ni), &XTK_EL_DATA(xtk_el_child(next_el, ni))->key);
		if (found < 0 || !xtk_plan_same_type(old_node->children [found], xtk_el_child(next_el, ni))) {
			out_old [ni] = -1;
			continue;
		}
		if (claimed [found]) return false;
		claimed [found] = true;
		out_old [ni]    = found;
	}
	return true;
}

static bool mark_moves(
  XtkScratch *scratch, int *out_old, bool *out_move, int *moves_needed, int prefix, int new_mid, int *seq, int *seq_new
) {
	int matched = 0;
	for (int i = 0; i < new_mid; i++) {
		int ni = prefix + i;
		if (out_old [ni] < 0) continue;
		seq [matched]     = out_old [ni];
		seq_new [matched] = ni;
		matched++;
	}
	if (matched <= 0) return true;

	bool *in_lis = ( bool * ) xtk_scratch_reserve(scratch, sizeof(bool) * ( size_t ) matched, _Alignof(bool));
	if (!in_lis) return false;
	size_t lis_mark = xtk_scratch_mark(scratch);
	int    lis      = lis_length(seq, matched, scratch, in_lis);
	if (lis < 0) return false;
	*moves_needed = matched - lis;
	for (int i = 0; i < matched; i++)
		if (!in_lis [i]) out_move [seq_new [i]] = true;
	xtk_scratch_rewind(scratch, lis_mark);
	return true;
}

static void claim_affix(bool *claimed, int old_n, int prefix, int suffix) {
	if (!claimed) return;
	for (int i = 0; i < prefix; i++) claimed [i] = true;
	for (int i = 0; i < suffix; i++) claimed [old_n - 1 - i] = true;
}

static bool *claim_alloc(XtkScratch *scratch, int old_n) {
	if (old_n <= 0) return NULL;
	bool *claimed = ( bool * ) xtk_scratch_reserve(scratch, sizeof(bool) * ( size_t ) old_n, _Alignof(bool));
	if (!claimed) return NULL;
	memset(claimed, 0, sizeof(bool) * ( size_t ) old_n);
	return claimed;
}

static bool match_mid_and_moves(
  XtkNode const *old_node, XtkEl const *next_el, XtkScratch *scratch, int prefix, int old_mid, int new_mid,
  int *out_old, bool *out_move, bool *claimed, int *moves_needed
) {
	if (old_mid > 0 && !match_mid_hashed(old_node, next_el, scratch, prefix, old_mid, new_mid, out_old, claimed))
		return false;
	if (new_mid <= 0) return true;
	int *seq     = ( int * ) xtk_scratch_reserve(scratch, sizeof(int) * ( size_t ) new_mid, _Alignof(int));
	int *seq_new = ( int * ) xtk_scratch_reserve(scratch, sizeof(int) * ( size_t ) new_mid, _Alignof(int));
	if (!seq || !seq_new) return false;
	return mark_moves(scratch, out_old, out_move, moves_needed, prefix, new_mid, seq, seq_new);
}

static void keyed_init_outputs(int new_n, int *out_old, bool *out_move, int *retire_count, int *moves_needed) {
	*retire_count = 0;
	*moves_needed = 0;
	for (int i = 0; i < new_n; i++) {
		out_old [i]  = -1;
		out_move [i] = false;
	}
}

static bool keyed_outputs_alloc(XtkScratch *scratch, int old_n, int new_n, XtkKeyedMatch *match) {
	if (new_n > 0) {
		match->old  = ( int * ) xtk_scratch_reserve(scratch, sizeof(int) * ( size_t ) new_n, _Alignof(int));
		match->move = ( bool * ) xtk_scratch_reserve(scratch, sizeof(bool) * ( size_t ) new_n, _Alignof(bool));
		if (!match->old || !match->move) return false;
	}
	if (old_n <= 0) return true;
	match->retire = ( int * ) xtk_scratch_reserve(scratch, sizeof(int) * ( size_t ) old_n, _Alignof(int));
	return match->retire != NULL;
}

static void collect_unclaimed(bool const *claimed, int old_n, int *retire, int *retire_count) {
	for (int i = 0; i < old_n; i++)
		if (!claimed [i]) retire [(*retire_count)++] = i;
}

bool xtk_plan_match_keyed(XtkNode const *old_node, XtkEl const *next_el, XtkScratch *scratch, XtkKeyedMatch *match) {
	int old_n = old_node ? old_node->child_count : 0;
	int new_n = XTK_EL_DATA(next_el)->child_count;
	*match    = (XtkKeyedMatch) {0};
	if (!keyed_scratch_ensure(scratch, old_n, new_n)) return false;
	if (!keyed_outputs_alloc(scratch, old_n, new_n, match)) return false;
	keyed_init_outputs(new_n, match->old, match->move, &match->retire_count, &match->moves_needed);

	int    prefix  = keyed_prefix(old_node, next_el, old_n, new_n, match->old);
	int    suffix  = keyed_suffix(old_node, next_el, old_n, new_n, prefix, match->old);
	int    old_mid = old_n - prefix - suffix;
	int    new_mid = new_n - prefix - suffix;

	size_t mark    = xtk_scratch_mark(scratch);
	bool  *claimed = claim_alloc(scratch, old_n);
	if (old_n > 0 && !claimed) return false;
	claim_affix(claimed, old_n, prefix, suffix);

	if (!match_mid_and_moves(
		  old_node, next_el, scratch, prefix, old_mid, new_mid, match->old, match->move, claimed, &match->moves_needed
		))
	{
		xtk_scratch_rewind(scratch, mark);
		return false;
	}
	collect_unclaimed(claimed, old_n, match->retire, &match->retire_count);
	xtk_scratch_rewind(scratch, mark);
	return true;
}
