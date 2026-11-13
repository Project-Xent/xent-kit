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

typedef struct Slot {
	uint32_t hash;
	int      old_index;
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

typedef struct Keyed {
	XtkNode const *old;
	XtkEl const   *next;
	XtkScratch    *scratch;
	XtkKeyedMatch *match;
	bool          *claimed;
	int            old_n, new_n, prefix, suffix;
} Keyed;

static bool keyed_pair(Keyed const *k, int oi, int ni) {
	XtkNode const *old  = k->old->children [oi];
	XtkEl const   *next = xtk_el_child(k->next, ni);
	return same_key(old, next) && xtk_plan_same_type(old, next);
}

static void keyed_claim(Keyed *k, int oi, int ni) {
	k->match->old [ni] = oi;
	k->claimed [oi]    = true;
}

static void keyed_affixes(Keyed *k) {
	int limit = k->old_n < k->new_n ? k->old_n : k->new_n;
	while (k->prefix < limit && keyed_pair(k, k->prefix, k->prefix)) keyed_claim(k, k->prefix, k->prefix), k->prefix++;
	limit -= k->prefix;
	while (k->suffix < limit && keyed_pair(k, k->old_n - 1 - k->suffix, k->new_n - 1 - k->suffix))
		keyed_claim(k, k->old_n - 1 - k->suffix, k->new_n - 1 - k->suffix), k->suffix++;
}

static int keyed_lookup(Keyed const *k, Slot const *slots, uint32_t mask, int ni) {
	XtkEl const *want = xtk_el_child(k->next, ni);
	uint32_t     h    = xtk_key_hash(&XTK_EL_DATA(want)->key);
	for (uint32_t s = h & mask; slots [s].old_index != 0; s = (s + 1u) & mask) {
		int oi = slots [s].old_index - 1;
		if (slots [s].hash == h && same_key(k->old->children [oi], want)) return oi;
	}
	return -1;
}

static Slot *keyed_index(Keyed const *k, int old_mid, uint32_t *cap) {
	*cap        = hash_cap(old_mid);
	Slot *slots = *cap ? ( Slot * ) xtk_scratch_reserve(k->scratch, sizeof(Slot) * *cap, _Alignof(Slot)) : NULL;
	if (!slots) return NULL;
	memset(slots, 0, sizeof(Slot) * *cap);
	uint32_t mask = *cap - 1u;
	for (int oi = k->prefix; oi < k->prefix + old_mid; oi++) {
		uint32_t h = xtk_key_hash(&k->old->children [oi]->key);
		uint32_t s = h & mask;
		while (slots [s].old_index != 0) s = (s + 1u) & mask;
		slots [s] = (Slot) {.hash = h, .old_index = oi + 1};
	}
	return slots;
}

static bool keyed_middle(Keyed *k) {
	int old_mid = k->old_n - k->prefix - k->suffix;
	if (old_mid <= 0) return true;
	uint32_t cap;
	Slot    *slots = keyed_index(k, old_mid, &cap);
	if (!slots) return false;
	for (int ni = k->prefix; ni < k->new_n - k->suffix; ni++) {
		int oi = keyed_lookup(k, slots, cap - 1u, ni);
		if (oi < 0 || !xtk_plan_same_type(k->old->children [oi], xtk_el_child(k->next, ni))) continue;
		if (k->claimed [oi]) return false;
		keyed_claim(k, oi, ni);
	}
	return true;
}

static bool keyed_mark_moves(Keyed *k, int const *seq, int const *seq_new, int matched) {
	bool *in_lis = ( bool * ) xtk_scratch_reserve(k->scratch, sizeof(bool) * ( size_t ) matched, _Alignof(bool));
	if (!in_lis) return false;
	size_t mark = xtk_scratch_mark(k->scratch);
	int    lis  = lis_length(seq, matched, k->scratch, in_lis);
	xtk_scratch_rewind(k->scratch, mark);
	if (lis < 0) return false;
	k->match->moves_needed = matched - lis;
	for (int i = 0; i < matched; i++)
		if (!in_lis [i]) k->match->move [seq_new [i]] = true;
	return true;
}

static bool keyed_moves(Keyed *k) {
	int new_mid = k->new_n - k->prefix - k->suffix;
	if (new_mid <= 0) return true;
	int *seq     = ( int * ) xtk_scratch_reserve(k->scratch, sizeof(int) * ( size_t ) new_mid, _Alignof(int));
	int *seq_new = ( int * ) xtk_scratch_reserve(k->scratch, sizeof(int) * ( size_t ) new_mid, _Alignof(int));
	if (!seq || !seq_new) return false;
	int matched = 0;
	for (int ni = k->prefix; ni < k->prefix + new_mid; ni++) {
		if (k->match->old [ni] < 0) continue;
		seq [matched]       = k->match->old [ni];
		seq_new [matched++] = ni;
	}
	return matched == 0 || keyed_mark_moves(k, seq, seq_new, matched);
}

static bool keyed_outputs(Keyed *k) {
	XtkKeyedMatch *m = k->match;
	if (k->new_n > 0) {
		m->old  = ( int * ) xtk_scratch_reserve(k->scratch, sizeof(int) * ( size_t ) k->new_n, _Alignof(int));
		m->move = ( bool * ) xtk_scratch_reserve(k->scratch, sizeof(bool) * ( size_t ) k->new_n, _Alignof(bool));
		if (!m->old || !m->move) return false;
		for (int i = 0; i < k->new_n; i++) m->old [i] = -1;
		memset(m->move, 0, sizeof(bool) * ( size_t ) k->new_n);
	}
	if (k->old_n <= 0) return true;
	m->retire = ( int * ) xtk_scratch_reserve(k->scratch, sizeof(int) * ( size_t ) k->old_n, _Alignof(int));
	return m->retire != NULL;
}

bool xtk_plan_match_keyed(XtkNode const *old_node, XtkEl const *next_el, XtkScratch *scratch, XtkKeyedMatch *match) {
	Keyed k = {
	  .old     = old_node,
	  .next    = next_el,
	  .scratch = scratch,
	  .match   = match,
	  .old_n   = old_node ? old_node->child_count : 0,
	  .new_n   = XTK_EL_DATA(next_el)->child_count,
	};
	*match = (XtkKeyedMatch) {0};
	if (!keyed_scratch_ensure(scratch, k.old_n, k.new_n) || !keyed_outputs(&k)) return false;
	size_t mark = xtk_scratch_mark(scratch);
	if (k.old_n > 0) {
		k.claimed = ( bool * ) xtk_scratch_reserve(scratch, sizeof(bool) * ( size_t ) k.old_n, _Alignof(bool));
		if (!k.claimed) return false;
		memset(k.claimed, 0, sizeof(bool) * ( size_t ) k.old_n);
	}
	keyed_affixes(&k);
	bool ok = keyed_middle(&k) && keyed_moves(&k);
	for (int i = 0; ok && i < k.old_n; i++)
		if (!k.claimed [i]) match->retire [match->retire_count++] = i;
	xtk_scratch_rewind(scratch, mark);
	return ok;
}
