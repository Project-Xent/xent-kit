#include "xtk_reconcile_internal.h"
#include "xtk_identity.h"
#include "xtk_key.h"
#include "../xtk_internal.h"

#include <xtk/xtk_alloc.h>
#include <xtk/xtk_catalog.h>

#include <limits.h>
#include <string.h>

static bool count_add(size_t *value, size_t add) {
	if (*value > SIZE_MAX - add) return false;
	*value += add;
	return true;
}

static bool size_part(size_t count, size_t item, size_t align, size_t *total) {
	if (count && item > SIZE_MAX / count) return false;
	size_t bytes = count * item;
	if (count && align - 1u > (SIZE_MAX - bytes) / count) return false;
	return count_add(total, bytes + count * (align - 1u));
}

bool xtk_plan_prepare(XtkReconcileTxn *txn, XtkEl const *next) {
	if (!next || !next->ui) return false;
	size_t nodes     = ( size_t ) next->ui->composition.element_count + 1u;
	size_t children  = nodes;
	size_t old_nodes = ( size_t ) txn->rt->committed_count + 1u;
	size_t need      = 0u;
	if (!size_part(nodes, sizeof(XtkPlanRec), _Alignof(XtkPlanRec), &need)) return false;
	if (!size_part(children, sizeof(XtkStagedChild), _Alignof(XtkStagedChild), &need)) return false;
	if (!size_part(old_nodes, sizeof(XtkNode *), _Alignof(XtkNode *), &need)) return false;
	xtk_scratch_reset(txn->plans);
	if (!xtk_scratch_ensure(txn->plans, need)) return false;
	if (old_nodes > INT_MAX) return false;
	txn->retire_nodes
	  = ( XtkNode ** ) xtk_scratch_reserve(txn->plans, old_nodes * sizeof(XtkNode *), _Alignof(XtkNode *));
	if (!txn->retire_nodes) return false;
	txn->retire_cap = ( int ) old_nodes;
	return xtk_identity_alloc_regions(txn->scratch, ( uint32_t ) nodes, &txn->seen_regions, &txn->seen_region_cap);
}

static XtkNode *node_fresh(XtkCtrlId type) {
	XtkNode *n = ( XtkNode * ) xtk_alloc_zero(1, sizeof(*n));
	if (!n) return NULL;
	n->type_id = type;
	return n;
}

static bool retire_push(XtkReconcileTxn *txn, XtkNode *n) {
	if (txn->retire_count >= txn->retire_cap) return false;
	txn->retire_nodes [txn->retire_count++] = n;
	return true;
}

void xtk_plan_free(XtkPlanRec *plan) {
	if (!plan) return;
	for (int i = 0; i < plan->child_count; i++) xtk_plan_free(plan->children [i].plan);
	xtk_alloc_free(plan->next_binding);
	xtk_prop_state_destroy(plan->next_props);
	if (plan->patch_slots) {
		xtk_prop_slots_release(plan->patch_slots, plan->patch_count);
		plan->patch_slots = NULL;
	}
	if (plan->next_key.kind == XTK_KEY_STRING) xtk_alloc_free(( void * ) plan->next_key.value.string);
	xtk_alloc_free(plan->sub_tokens);
}

static bool plan_key(XtkPlanRec *plan, XtkNode const *committed, XtkEl const *el) {
	XtkKey const *key = &XTK_EL_DATA(el)->key;
	if (committed && xtk_key_equal(&committed->key, key)) return true;
	plan->key_changed = true;
	plan->next_key    = *key;
	if (key->kind != XTK_KEY_STRING || !key->value.string) return true;
	size_t len  = strlen(key->value.string) + 1u;
	char  *copy = xtk_alloc(len);
	if (!copy) return false;
	memcpy(copy, key->value.string, len);
	plan->next_key.value.string = copy;
	return true;
}

void xtk_plan_abort_fresh(XtkPlanRec *plan) {
	if (!plan) return;
	for (int i = 0; i < plan->child_count; i++) xtk_plan_abort_fresh(plan->children [i].plan);
	if (plan->patch_slots) {
		xtk_prop_slots_release(plan->patch_slots, plan->patch_count);
		plan->patch_slots = NULL;
	}
	if (plan->is_create && plan->fresh) {
		xtk_alloc_free(plan->fresh->children);
		xtk_alloc_free(plan->fresh->sub_ids);
		xtk_alloc_free(plan->fresh);
		plan->fresh = NULL;
	}
}

static bool encode_destroy_tree(XtkReconcileTxn *txn, XtkNode *n) {
	if (!n) return true;
	for (int i = 0; i < n->child_count; i++)
		if (!encode_destroy_tree(txn, n->children [i])) return false;
	return xtk_batch_drop(txn->batch, xtk_ref_existing(( XtkCtrl ) n->node));
}

static bool plan_node(
  XtkReconcileTxn *txn, XtkPlanRec *parent, XtkNodeRef parent_ref, XtkEl const *el, XtkNode *committed,
  XtkNodeRef before, uint32_t depth, XtkPlanRec **out
);

static bool retire_child(XtkReconcileTxn *txn, XtkNode *node, int index) {
	if (!node || index < 0 || index >= node->child_count) return false;
	XtkNode *child = node->children [index];
	if (!child || !encode_destroy_tree(txn, child)) return false;
	return retire_push(txn, child);
}

static bool retire_range(XtkReconcileTxn *txn, XtkNode *node, int first, int count) {
	for (int i = 0; i < count; i++)
		if (!retire_child(txn, node, first + i)) return false;
	return true;
}

static void staged_init(XtkPlanRec *plan) {
	for (int i = 0; i < plan->child_count; i++) {
		plan->children [i].old_index = -1;
		plan->children [i].do_move   = false;
	}
}

static int positional_prefix(XtkNode const *node, XtkEl const *el, int shared, XtkStagedChild *children) {
	int prefix = 0;
	while (prefix < shared && xtk_plan_same_type(node->children [prefix], xtk_el_child(el, prefix))) {
		children [prefix].old_index = prefix;
		prefix++;
	}
	return prefix;
}

static int positional_suffix(XtkNode const *node, XtkEl const *el, int shared, int prefix, XtkStagedChild *children) {
	int suffix = 0;
	while (prefix + suffix < shared) {
		int index = shared - 1 - suffix;
		if (!xtk_plan_same_type(node->children [index], xtk_el_child(el, index))) break;
		children [index].old_index = index;
		suffix++;
	}
	return suffix;
}

static bool positional_middle(XtkReconcileTxn *txn, XtkPlanRec *plan, int first, int end) {
	for (int i = first; i < end; i++) {
		if (xtk_plan_same_type(plan->committed->children [i], xtk_el_child(plan->el, i))) {
			plan->children [i].old_index = i;
			continue;
		}
		if (!retire_child(txn, plan->committed, i)) return false;
	}
	return true;
}

static bool match_positional(XtkReconcileTxn *txn, XtkPlanRec *plan) {
	XtkEl const *el     = plan->el;
	XtkNode     *node   = plan->committed;
	int          old_n  = node ? node->child_count : 0;
	int          shared = old_n < plan->child_count ? old_n : plan->child_count;
	int          prefix = positional_prefix(node, el, shared, plan->children);
	int          suffix = positional_suffix(node, el, shared, prefix, plan->children);
	if (!positional_middle(txn, plan, prefix, shared - suffix)) return false;
	return retire_range(txn, node, shared, old_n - shared);
}

static void keyed_copy_matches(XtkPlanRec *plan, int const *old, bool const *move) {
	for (int i = 0; i < plan->child_count; i++) {
		plan->children [i].old_index = old [i];
		plan->children [i].do_move   = move [i];
	}
}

static bool match_keyed(XtkReconcileTxn *txn, XtkPlanRec *plan) {
	size_t        mark = xtk_scratch_mark(txn->scratch);
	XtkKeyedMatch match;
	bool          ok = xtk_plan_match_keyed(plan->committed, plan->el, txn->scratch, &match);
	for (int i = 0; ok && i < match.retire_count; i++) ok = retire_child(txn, plan->committed, match.retire [i]);
	if (ok) keyed_copy_matches(plan, match.old, match.move);
	xtk_scratch_rewind(txn->scratch, mark);
	return ok;
}

static bool match_children(XtkReconcileTxn *txn, XtkPlanRec *plan) {
	XtkSiblingMode next  = xtk_sibling_mode(plan->el);
	int            old_n = plan->committed ? plan->committed->child_count : 0;
	XtkSiblingMode old   = old_n == 0                                           ? XTK_SIBLING_EMPTY
	                     : xtk_key_present(&plan->committed->children [0]->key) ? XTK_SIBLING_KEYED
	                                                                            : XTK_SIBLING_POSITIONAL;
	if (old_n == 0) return true;
	if (next == XTK_SIBLING_EMPTY || (old != XTK_SIBLING_EMPTY && next != old))
		return retire_range(txn, plan->committed, 0, old_n);
	if (next == XTK_SIBLING_POSITIONAL) return match_positional(txn, plan);
	if (next == XTK_SIBLING_KEYED) return match_keyed(txn, plan);
	return false;
}

static bool stage_fresh_children(XtkReconcileTxn *txn, XtkPlanRec *plan, XtkEl const *el, int new_n, uint32_t depth) {
	plan->children_changed = new_n > 0;
	for (int i = 0; i < new_n; i++) {
		if (depth < XTK_IDENTITY_PATH_MAX) txn->walk_path [depth] = i;
		XtkPlanRec *child = NULL;
		if (!plan_node(txn, plan, plan->ref, xtk_el_child(el, i), NULL, xtk_ref_none(), depth + 1u, &child))
			return false;
		plan->children [i].el   = xtk_el_child(el, i);
		plan->children [i].plan = child;
		if (child->subtree_dirty) plan->subtree_dirty = true;
	}
	return true;
}

static unsigned child_slot(bool nav, XtkEl const *child) {
	unsigned slot         = XTK_EL_DATA(child)->nav_slot;
	bool     content_slot = slot == XTK_NAV_SLOT_PAGE_HEADER || slot == XTK_NAV_SLOT_CONTENT_OVERLAY;
	return nav && (slot <= XTK_NAV_SLOT_SEARCH || content_slot) ? slot : XTK_NAV_SLOT_CONTENT;
}

static bool changed_child_slot(XtkNode const *old, unsigned slot) {
	if (!old || old->type_id != XTK_CTRL_NAVSLOT || !old->props) return false;
	XtkPropSlot const *prop = xtk_prop_state_find(old->props, XTK_PROP_NAV_SLOT);
	return prop ? prop->value.u.u32 != slot : slot != XTK_NAV_SLOT_CONTENT;
}

static bool stage_child(
  XtkReconcileTxn *txn, XtkPlanRec *plan, XtkStagedChild *staged, XtkNode *old, XtkNodeRef *anchor, bool changed_slot,
  uint32_t depth
) {
	XtkPlanRec *child = NULL;
	if (!plan_node(txn, plan, plan->ref, staged->el, old, *anchor, depth + 1u, &child)) {
		staged->plan = child;
		return false;
	}
	staged->plan = child;
	bool move    = staged->do_move || changed_slot;
	if (!child->is_create && move && !xtk_batch_move(txn->batch, plan->ref, child->ref, *anchor)) return false;
	*anchor = child->ref;
	if (child->subtree_dirty) plan->subtree_dirty = true;
	return true;
}

static bool stage_one_child(
  XtkReconcileTxn *txn, XtkPlanRec *plan, XtkEl const *el, XtkNode *node, XtkNodeRef *anchors, int i, bool nav,
  uint32_t depth
) {
	if (depth < XTK_IDENTITY_PATH_MAX) txn->walk_path [depth] = i;
	XtkStagedChild *staged = &plan->children [i];
	int             index  = staged->old_index;
	XtkNode        *old    = (index >= 0 && node && index < node->child_count) ? node->children [index] : NULL;
	staged->el             = xtk_el_child(el, i);
	unsigned slot          = child_slot(nav, staged->el);
	bool     changed_slot  = nav && changed_child_slot(old, slot);
	if (index != i || !old || changed_slot) plan->children_changed = true;
	return stage_child(txn, plan, staged, old, &anchors [slot], changed_slot, depth);
}

static bool
stage_children(XtkReconcileTxn *txn, XtkPlanRec *plan, XtkEl const *el, XtkNode *node, int new_n, uint32_t depth) {
	if (plan->is_create) return stage_fresh_children(txn, plan, el, new_n, depth);
	if (node && node->child_count != new_n) plan->children_changed = true;
	XtkNodeRef anchors [XTK_NAV_SLOT_CONTENT_OVERLAY + 1];
	for (unsigned i = 0; i <= XTK_NAV_SLOT_CONTENT_OVERLAY; i++) anchors [i] = xtk_ref_none();
	bool nav = XTK_EL_DATA(el)->type == XTK_CTRL_NAV;
	for (int i = new_n - 1; i >= 0; i--)
		if (!stage_one_child(txn, plan, el, node, anchors, i, nav, depth)) return false;
	return true;
}

static bool plan_alloc_children(XtkReconcileTxn *txn, XtkPlanRec *plan, int new_n) {
	plan->child_count = new_n;
	if (new_n <= 0) return true;
	plan->children = ( XtkStagedChild * ) xtk_scratch_reserve(
	  txn->plans, ( size_t ) new_n * sizeof(XtkStagedChild), _Alignof(XtkStagedChild)
	);
	if (!plan->children) return false;
	memset(plan->children, 0, ( size_t ) new_n * sizeof(XtkStagedChild));
	return true;
}

static bool plan_diff_children(XtkReconcileTxn *txn, XtkPlanRec *plan, uint32_t depth) {
	XtkEl const     *el    = plan->el;
	XtkNode         *node  = plan->committed;
	int              new_n = XTK_EL_DATA(el)->child_count;
	XtkIdentityError iderr
	  = xtk_identity_check_siblings(&txn->rt->scene, el, txn->scratch, depth, txn->walk_path, &txn->identity);
	if (iderr != XTK_IDENTITY_OK) {
		txn->identity_failed = true;
		return false;
	}
	XtkNode *target_node = plan->is_create ? plan->fresh : node;
	if (!xtk_node_reserve(target_node, new_n) || !plan_alloc_children(txn, plan, new_n)) return false;
	staged_init(plan);
	if (!match_children(txn, plan) || !stage_children(txn, plan, el, node, new_n, depth)) return false;
	if (plan->children_changed) plan->subtree_dirty = true;
	return true;
}

static bool record_sub_tokens(XtkReconcileTxn *txn, XtkPlanRec *plan, uint32_t sub_before) {
	int n = ( int ) (txn->batch->next_sub - sub_before);
	if (n <= 0) return true;
	plan->sub_tokens = ( XtkSubRef * ) xtk_alloc(( size_t ) n * sizeof(XtkSubRef));
	if (!plan->sub_tokens) return false;
	plan->sub_token_count = n;
	for (int i = 0; i < n; i++) plan->sub_tokens [i] = sub_before + ( uint32_t ) i;
	XtkNode *target = plan->is_create ? plan->fresh : plan->committed;
	return xtk_node_reserve_subs(target, n);
}

static bool plan_binding_alloc(XtkReconcileTxn *txn, XtkPlanRec *plan, XtkEl const *el, XtkBinding const *prev) {
	if (!xtk_el_needs_binding(el)) return true;
	plan->next_binding = ( XtkBinding * ) xtk_alloc_zero(1, sizeof(*plan->next_binding));
	if (!plan->next_binding) return false;
	plan->next_binding->rt = txn->rt;
	if (prev) {
		plan->next_binding->realized = prev->realized;
		plan->next_binding->echo     = prev->echo;
	}
	plan->binding_changed = true;
	return true;
}

static bool plan_subscribe_fresh(XtkReconcileTxn *txn, XtkPlanRec *plan, XtkEl const *el, uint32_t sub_before) {
	if (!plan->next_binding) return true;
	if (!xtk_encode_subscribe(txn->batch, plan->ref, plan->next_binding, el)) return false;
	return record_sub_tokens(txn, plan, sub_before);
}

static bool plan_create(
  XtkReconcileTxn *txn, XtkPlanRec *plan, XtkNodeRef parent_ref, XtkEl const *el, XtkNode *committed, XtkNodeRef before
) {
	plan->is_create = true;
	plan->fresh     = node_fresh(XTK_EL_DATA(el)->type);
	if (!plan->fresh || !plan_binding_alloc(txn, plan, el, NULL)) return false;
	uint32_t sub_before = txn->batch->next_sub;
	if (!xtk_encode_create(txn->batch, parent_ref, before, el, &plan->local)) return false;
	plan->ref = xtk_ref_local(plan->local);
	if (!plan_subscribe_fresh(txn, plan, el, sub_before)) return false;
	if (!committed) return true;
	if (!encode_destroy_tree(txn, committed)) return false;
	return retire_push(txn, committed);
}

static bool plan_binding_sync(XtkReconcileTxn *txn, XtkPlanRec *plan, XtkEl const *el, XtkBinding const *prev) {
	if (!plan_binding_alloc(txn, plan, el, prev)) return false;
	if (!plan->next_binding) return true;
	uint32_t sub_before = txn->batch->next_sub;
	if (!xtk_encode_subscribe(txn->batch, plan->ref, plan->next_binding, el)) return false;
	return record_sub_tokens(txn, plan, sub_before);
}

static bool plan_binding(XtkReconcileTxn *txn, XtkPlanRec *plan, XtkNode *committed, XtkEl const *el) {
	if (committed->binding && xtk_binding_msgs_equal(committed->binding, el)) return true;
	bool next_has_binding = xtk_el_needs_binding(el);
	if (!committed->binding && !next_has_binding) return true;
	plan->binding_changed = true;
	if (committed->binding && !xtk_encode_unsubscribe_all(txn->batch, committed)) return false;
	return plan_binding_sync(txn, plan, el, committed->binding);
}

static XtkEcho node_echo(XtkNode const *committed) {
	XtkEcho     echo = {0};
	XtkBinding *b    = committed->binding;
	if (!b) return echo;
	echo.stamp = b->echo;
	for (XtkEventId event = 1; event < ( XtkEventId ) XTK_EVENT_STANDARD_COUNT; event++) {
		if (!(b->user_events & (1ull << event))) continue;
		XtkPropertyId ids [XTK_MIRROR_MAX];
		uint32_t      n = xtk_catalog_mirrors(committed->type_id, event, ids);
		for (uint32_t i = 0; i < n && echo.nforce < 8u; i++) echo.force [echo.nforce++] = ids [i];
	}
	b->user_events = 0u;
	return echo;
}

static XtkArena *ensure_patch_arena(XtkRt *rt) {
	if (rt->patch_arena) return rt->patch_arena;
	XtkArena *arena = ( XtkArena * ) xtk_alloc_zero(1, sizeof(*arena));
	if (!arena) return NULL;
	if (!xtk_arena_init(arena, 16u * 1024u)) {
		xtk_alloc_free(arena);
		return NULL;
	}
	rt->patch_arena = arena;
	return arena;
}

static bool plan_reuse(
  XtkReconcileTxn *txn, XtkPlanRec *plan, XtkEl const *el, XtkNode *committed, XtkPropView props, XtkModelVer next_ver,
  bool skip_model
) {
	plan->ref = xtk_ref_existing(( XtkCtrl ) committed->node);
	bool    changed;
	XtkEcho echo = node_echo(committed);
	if (!xtk_prop_state_diff(txn->batch, plan->ref, committed->props, props, skip_model, &echo, &changed)) return false;
	if (changed) {
		XtkArena *arena = ensure_patch_arena(txn->rt);
		if (!arena) return false;
		if (!xtk_prop_state_prepare(
			  committed->props, props, next_ver, skip_model, arena, &plan->next_props, &plan->patch_slots,
			  &plan->patch_count
			))
			return false;
		plan->next_model_ver = next_ver;
	}
	return plan_binding(txn, plan, committed, el);
}

static bool plan_region_ref(XtkPlanRec *plan, XtkElementData const *data, XtkNode *committed) {
	if (!(data->region_flags & XTK_REGION_REF)) return false;
	if (!committed || committed->region_id != data->region_id || committed->region_revision != data->region_revision)
		return false;
	plan->region_skip = true;
	plan->ref         = xtk_ref_existing(( XtkCtrl ) committed->node);
	return true;
}

static bool region_meta_changed(XtkNode const *committed, XtkElementData const *data) {
	if (!committed) return true;
	uint32_t next_flags = data->region_flags & ~XTK_REGION_REF;
	return committed->region_id != data->region_id
	    || committed->region_revision != data->region_revision
	    || committed->region_flags != next_flags
	    || committed->region_build != data->region_build
	    || committed->region_ctx != data->region_ctx;
}

static bool model_ver_same(XtkModelVer a, XtkModelVer b) {
	return xtk_model_ver_valid(a) && a.ptr == b.ptr && a.revision == b.revision;
}

static bool node_reusable(XtkRt const *rt, XtkNode const *committed, XtkEl const *el) {
	XtkCtrlId type = XTK_EL_DATA(el)->type;
	return committed && committed->type_id == type && !xtk_rt_remounting(rt, type);
}

static bool plan_content(
  XtkReconcileTxn *txn, XtkPlanRec *plan, XtkNodeRef parent_ref, XtkEl const *el, XtkNode *committed, XtkNodeRef before,
  uint32_t depth
) {
	bool         reuse      = node_reusable(txn->rt, committed, el);
	XtkModelVer  next_ver   = xtk_el_model_ver(el);
	bool         skip_model = reuse && committed->props && model_ver_same(committed->props->model_ver, next_ver);
	XtkPropPatch props_items [XTK_PROP_STANDARD_COUNT + 1u];
	XtkPropView  props;
	if (!xtk_prop_view_build(el, props_items, XTK_PROP_STANDARD_COUNT + 1u, skip_model, &props)) return false;
	bool ok = plan_key(plan, committed, el);
	if (ok && reuse) ok = plan_reuse(txn, plan, el, committed, props, next_ver, skip_model);
	if (ok && !reuse) {
		plan->next_props = xtk_prop_state_copy(props, next_ver);
		ok               = plan->next_props && plan_create(txn, plan, parent_ref, el, committed, before);
	}
	xtk_prop_view_destroy(&props);
	if (!ok) return false;
	if (plan->is_create
	    || plan->next_props
	    || plan->patch_slots
	    || plan->binding_changed
	    || plan->key_changed
	    || region_meta_changed(committed, XTK_EL_DATA(el)))
		plan->subtree_dirty = true;
	return plan_diff_children(txn, plan, depth);
}

static bool plan_node(
  XtkReconcileTxn *txn, XtkPlanRec *parent, XtkNodeRef parent_ref, XtkEl const *el, XtkNode *committed,
  XtkNodeRef before, uint32_t depth, XtkPlanRec **out
) {
	XtkIdentityError iderr = xtk_identity_check_node(
	  &txn->rt->scene, el, depth, txn->walk_path, txn->seen_regions, txn->seen_region_cap, &txn->identity
	);
	if (iderr != XTK_IDENTITY_OK) {
		txn->identity_failed = true;
		return false;
	}
	txn->metrics->nodes_compared++;
	XtkPlanRec *plan = ( XtkPlanRec * ) xtk_scratch_reserve(txn->plans, sizeof(*plan), _Alignof(XtkPlanRec));
	if (!plan) return false;
	memset(plan, 0, sizeof(*plan));
	plan->el             = el;
	plan->committed      = committed;
	plan->parent         = parent;
	plan->local          = XTK_LOCAL_INVALID;
	*out                 = plan;
	XtkElementData *data = XTK_EL_DATA(el);
	if (data->region_flags & XTK_REGION_REF) {
		bool skipped = plan_region_ref(plan, data, committed);
		if (skipped) txn->metrics->nodes_skipped++;
		return skipped;
	}
	return plan_content(txn, plan, parent_ref, el, committed, before, depth);
}

bool xtk_plan_subtree(
  XtkReconcileTxn *txn, XtkEl *next, XtkNode *committed, XtkNodeRef parent_ref, XtkNodeRef before, XtkPlanRec **root
) {
	bool     reuse   = node_reusable(txn->rt, committed, next);
	XtkNode *old_ptr = reuse ? committed : NULL;
	if (!plan_node(txn, NULL, parent_ref, next, old_ptr, before, 0u, root)) return false;
	if (reuse || !committed) return true;
	if (!encode_destroy_tree(txn, committed)) return false;
	return retire_push(txn, committed);
}

bool xtk_plan_root(XtkReconcileTxn *txn, XtkEl *next, XtkPlanRec **root) {
	XtkNodeRef host_ref = xtk_ref_existing(( XtkCtrl ) txn->rt->host_root);
	bool       ok       = xtk_plan_subtree(txn, next, txn->rt->root, host_ref, xtk_ref_none(), root);
	txn->root_plan      = *root;
	return ok;
}
