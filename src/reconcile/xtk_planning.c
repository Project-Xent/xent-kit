#include "xtk_reconcile_internal.h"
#include "xtk_key.h"
#include "../xtk_internal.h"

#include <xtk/xtk_alloc.h>

#include <xtk/xtk_catalog.h>

#include <limits.h>
#include <string.h>

#define XTK_PLAN_DEPTH_MAX 256

typedef struct PlanShape {
	size_t nodes;
	size_t children;
	size_t old_nodes;
} PlanShape;

static bool count_add(size_t *value, size_t add) {
	if (*value > SIZE_MAX - add) return false;
	*value += add;
	return true;
}

static bool measure_elements(XtkEl const *el, int depth, PlanShape *shape) {
	if (!el || depth > XTK_PLAN_DEPTH_MAX || XTK_EL_DATA(el)->child_count < 0) return false;
	if (!count_add(&shape->nodes, 1u)) return false;
	if (!count_add(&shape->children, ( size_t ) XTK_EL_DATA(el)->child_count)) return false;
	for (int i = 0; i < XTK_EL_DATA(el)->child_count; i++)
		if (!measure_elements(xtk_el_child(el, i), depth + 1, shape)) return false;
	return true;
}

static bool measure_committed(XtkNode const *node, int depth, PlanShape *shape) {
	if (!node) return true;
	if (depth > XTK_PLAN_DEPTH_MAX || node->child_count < 0) return false;
	if (!count_add(&shape->old_nodes, 1u)) return false;
	for (int i = 0; i < node->child_count; i++)
		if (!measure_committed(node->children [i], depth + 1, shape)) return false;
	return true;
}

static bool size_part(size_t count, size_t item, size_t align, size_t *total) {
	if (count && item > SIZE_MAX / count) return false;
	size_t bytes = count * item;
	if (count && align - 1u > (SIZE_MAX - bytes) / count) return false;
	return count_add(total, bytes + count * (align - 1u));
}

static bool plan_storage_size(PlanShape const *shape, size_t *out) {
	size_t total = 0u;
	if (!size_part(shape->nodes, sizeof(XtkPlanRec), _Alignof(XtkPlanRec), &total)) return false;
	if (!size_part(shape->children, sizeof(XtkStagedChild), _Alignof(XtkStagedChild), &total)) return false;
	if (!size_part(shape->old_nodes, sizeof(XtkNode *), _Alignof(XtkNode *), &total)) return false;
	*out = total;
	return true;
}

bool xtk_plan_prepare(XtkReconcileTxn *txn, XtkEl const *next) {
	PlanShape shape = {0};
	if (!measure_elements(next, 0, &shape)) return false;
	if (!measure_committed(txn->rt->root, 0, &shape)) return false;
	size_t need = 0u;
	if (!plan_storage_size(&shape, &need)) return false;
	xtk_scratch_reset(txn->plans);
	if (!xtk_scratch_ensure(txn->plans, need)) return false;
	if (!shape.old_nodes) return true;
	if (shape.old_nodes > INT_MAX) return false;
	txn->retire_nodes
	  = ( XtkNode ** ) xtk_scratch_reserve(txn->plans, shape.old_nodes * sizeof(XtkNode *), _Alignof(XtkNode *));
	if (!txn->retire_nodes) return false;
	txn->retire_cap = ( int ) shape.old_nodes;
	return true;
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
  XtkReconcileTxn *txn, XtkPlanRec *parent, XtkEl const *el, XtkNode *committed, XtkNodeRef before, XtkPlanRec **out
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

static bool stage_fresh_children(XtkReconcileTxn *txn, XtkPlanRec *plan, XtkEl const *el, int new_n) {
	for (int i = 0; i < new_n; i++) {
		XtkPlanRec *child = NULL;
		if (!plan_node(txn, plan, xtk_el_child(el, i), NULL, xtk_ref_none(), &child)) return false;
		plan->children [i].el   = xtk_el_child(el, i);
		plan->children [i].plan = child;
	}
	return true;
}

static bool stage_children(XtkReconcileTxn *txn, XtkPlanRec *plan, XtkEl const *el, XtkNode *node, int new_n) {
	if (plan->is_create) return stage_fresh_children(txn, plan, el, new_n);
	XtkNodeRef before = xtk_ref_none();
	for (int i = new_n - 1; i >= 0; i--) {
		int         oi          = plan->children [i].old_index;
		XtkNode    *oldn        = (oi >= 0 && node && oi < node->child_count) ? node->children [oi] : NULL;
		XtkPlanRec *cp          = NULL;
		bool        ok          = plan_node(txn, plan, xtk_el_child(el, i), oldn, before, &cp);
		plan->children [i].plan = cp;
		if (!ok) return false;
		plan->children [i].el = xtk_el_child(el, i);
		if (!cp->is_create && plan->children [i].do_move && !xtk_batch_move(txn->batch, plan->ref, cp->ref, before))
			return false;
		before = cp->ref;
	}
	return true;
}

static bool plan_diff_children(XtkReconcileTxn *txn, XtkPlanRec *plan) {
	XtkEl const *el    = plan->el;
	XtkNode     *node  = plan->committed;
	int          new_n = XTK_EL_DATA(el)->child_count;

	if (new_n > 0) {
		plan->children = ( XtkStagedChild * ) xtk_scratch_reserve(
		  txn->plans, ( size_t ) new_n * sizeof(XtkStagedChild), _Alignof(XtkStagedChild)
		);
		if (!plan->children) return false;
		memset(plan->children, 0, ( size_t ) new_n * sizeof(XtkStagedChild));
	}
	plan->child_count = new_n;
	staged_init(plan);
	if (!match_children(txn, plan)) return false;
	return stage_children(txn, plan, el, node, new_n);
}

static bool record_sub_tokens(XtkReconcileTxn *txn, XtkPlanRec *plan, uint32_t sub_before) {
	int n = ( int ) (txn->batch->next_sub - sub_before);
	if (n <= 0) return true;
	plan->sub_tokens = ( XtkSubRef * ) xtk_alloc(( size_t ) n * sizeof(XtkSubRef));
	if (!plan->sub_tokens) return false;
	plan->sub_token_count = n;
	for (int i = 0; i < n; i++) plan->sub_tokens [i] = sub_before + ( uint32_t ) i;
	return true;
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
  XtkReconcileTxn *txn, XtkPlanRec *plan, XtkPlanRec *parent, XtkEl const *el, XtkNode *committed, XtkNodeRef before
) {
	plan->is_create = true;
	plan->fresh     = node_fresh(XTK_EL_DATA(el)->type);
	if (!plan->fresh || !plan_binding_alloc(txn, plan, el, NULL)) return false;
	XtkNodeRef pref       = parent ? parent->ref : xtk_ref_existing(( XtkCtrl ) txn->rt->host_root);
	uint32_t   sub_before = txn->batch->next_sub;
	if (!xtk_encode_create(txn->batch, pref, before, el, &plan->local)) return false;
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
		if (!(b->user_events & (1u << event))) continue;
		XtkPropertyId ids [XTK_MIRROR_MAX];
		uint32_t      n = xtk_catalog_mirrors(committed->type_id, event, ids);
		for (uint32_t i = 0; i < n && echo.nforce < 8u; i++) echo.force [echo.nforce++] = ids [i];
	}
	b->user_events = 0u;
	return echo;
}

static bool plan_reuse(XtkReconcileTxn *txn, XtkPlanRec *plan, XtkEl const *el, XtkNode *committed, XtkPropView props) {
	plan->ref = xtk_ref_existing(( XtkCtrl ) committed->node);
	bool    changed;
	XtkEcho echo = node_echo(committed);
	if (!xtk_prop_state_diff(txn->batch, plan->ref, committed->props, props, &echo, &changed)) return false;
	if (changed) {
		plan->next_props = xtk_prop_state_copy(props);
		if (!plan->next_props) return false;
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

static bool plan_content(
  XtkReconcileTxn *txn, XtkPlanRec *plan, XtkPlanRec *parent, XtkEl const *el, XtkNode *committed, XtkNodeRef before
) {
	XtkPropPatch props_items [XTK_PROP_STANDARD_COUNT + 1u];
	XtkPropView  props;
	if (!xtk_prop_view_build(el, props_items, XTK_PROP_STANDARD_COUNT + 1u, &props)) return false;
	bool ok    = plan_key(plan, committed, el);
	bool reuse = committed && committed->type_id == XTK_EL_DATA(el)->type;
	if (ok && reuse) ok = plan_reuse(txn, plan, el, committed, props);
	if (ok && !reuse) {
		plan->next_props = xtk_prop_state_copy(props);
		ok               = plan->next_props && plan_create(txn, plan, parent, el, committed, before);
	}
	xtk_prop_view_destroy(&props);
	if (!ok) return false;
	return plan_diff_children(txn, plan);
}

static bool plan_node(
  XtkReconcileTxn *txn, XtkPlanRec *parent, XtkEl const *el, XtkNode *committed, XtkNodeRef before, XtkPlanRec **out
) {
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
	return plan_content(txn, plan, parent, el, committed, before);
}

bool xtk_plan_root(XtkReconcileTxn *txn, XtkEl *next, XtkPlanRec **root) {
	bool       root_reuse = txn->rt->root && txn->rt->root->type_id == XTK_EL_DATA(next)->type;
	XtkNodeRef before     = xtk_ref_none();
	XtkNode   *old_root   = root_reuse ? txn->rt->root : NULL;
	if (!plan_node(txn, NULL, next, old_root, before, root)) return false;
	txn->root_plan = *root;
	if (root_reuse || !txn->rt->root) return true;
	if (!encode_destroy_tree(txn, txn->rt->root)) return false;
	return retire_push(txn, txn->rt->root);
}
