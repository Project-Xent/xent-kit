#include "xtk_reconcile_internal.h"
#include "../xtk_internal.h"

#include <xtk/xtk_alloc.h>

#include <limits.h>
#include <stdlib.h>

static XtkCtrl control_for_local(XtkBatchResult const *result, XtkLocalId local) {
	return result->controls [local].control;
}

static XtkSubId sub_for_token(XtkBatchResult const *result, XtkSubRef token) {
	return result->subscriptions [token].id;
}

static bool result_counts_ok(XtkBatchResult const *result, uint32_t locals, uint32_t subs) {
	return result && result->control_count == locals && result->subscription_count == subs;
}

static bool result_arrays_ok(XtkBatchResult const *result) {
	for (uint32_t i = 0; i < result->control_count; i++) {
		if (!result->controls || result->controls [i].local != i) return false;
		if (result->controls [i].control == XTK_CTRL_INVALID) return false;
	}
	for (uint32_t i = 0; i < result->subscription_count; i++) {
		if (!result->subscriptions || result->subscriptions [i].token != i) return false;
		if (result->subscriptions [i].id == XTK_SUBSCRIPTION_INVALID) return false;
	}
	return true;
}

static bool result_plan_ok(XtkPlanRec const *plan, XtkBatchResult const *result) {
	if (!plan) return true;
	if (plan->is_create && plan->local >= result->control_count) return false;
	for (int i = 0; i < plan->sub_token_count; i++)
		if (plan->sub_tokens [i] >= result->subscription_count) return false;
	for (int i = 0; i < plan->child_count; i++)
		if (!result_plan_ok(plan->children [i].plan, result)) return false;
	return true;
}

void xtk_publication_verify_result(
  XtkPlanRec const *plan, XtkBatchResult const *result, uint32_t locals, uint32_t subs
) {
	if (!result_counts_ok(result, locals, subs) || !result_arrays_ok(result) || !result_plan_ok(plan, result)) abort();
}

bool xtk_node_reserve(XtkNode *n, int count) {
	if (!n || count < 0) return false;
	if (count <= n->child_cap) return true;
	int cap = n->child_cap ? n->child_cap : 8;
	while (cap < count) {
		if (cap > INT_MAX / 2) {
			cap = count;
			break;
		}
		cap *= 2;
	}
	if (( size_t ) cap > SIZE_MAX / sizeof(XtkNode *)) return false;
	XtkNode **items = ( XtkNode ** ) xtk_alloc_resize(n->children, sizeof(XtkNode *) * ( size_t ) cap);
	if (!items) return false;
	n->children  = items;
	n->child_cap = cap;
	return true;
}

bool xtk_node_reserve_subs(XtkNode *n, int sub_token_count) {
	if (!n) return false;
	if (sub_token_count <= 0 || sub_token_count <= n->sub_cap) return true;
	XtkSubId *ids = ( XtkSubId * ) xtk_alloc_resize(n->sub_ids, sizeof(*ids) * ( size_t ) sub_token_count);
	if (!ids) return false;
	n->sub_ids = ids;
	n->sub_cap = sub_token_count;
	return true;
}

static void node_free_tree(XtkRt *rt, XtkNode *n) {
	if (!n) return;
	for (int i = 0; i < n->child_count; i++) node_free_tree(rt, n->children [i]);
	if (rt) {
		if (n->region_id) xtk_rt_region_remove(rt, n);
		if (rt->committed_count > 0u) rt->committed_count--;
	}
	xtk_alloc_free(n->binding);
	xtk_prop_state_destroy(n->props);
	if (n->key.kind == XTK_KEY_STRING) xtk_alloc_free(( void * ) n->key.value.string);
	xtk_alloc_free(n->sub_ids);
	xtk_alloc_free(n->children);
	xtk_alloc_free(n);
}

static XtkNode *resolve_node(XtkRt *rt, XtkPlanRec *plan, XtkBatchResult const *result) {
	XtkNode *n = plan->is_create ? plan->fresh : plan->committed;
	if (!plan->is_create) return n;
	XtkCtrl control = control_for_local(result, plan->local);
	if (control == XTK_CTRL_INVALID) return NULL;
	n->node     = ( XentNodeId ) control;
	n->host     = ( XentNodeId ) control;
	plan->fresh = NULL;
	if (rt) rt->committed_count++;
	return n;
}

static void resolve_binding(XtkPlanRec *plan, XtkNode *n, XtkBatchResult const *result) {
	if (!plan->binding_changed) return;
	xtk_alloc_free(n->binding);
	n->binding         = plan->next_binding;
	plan->next_binding = NULL;
	n->sub_count       = plan->sub_token_count;
	for (int i = 0; i < plan->sub_token_count; i++) n->sub_ids [i] = sub_for_token(result, plan->sub_tokens [i]);
}

static void resolve_children(XtkRt *rt, XtkPlanRec *plan, XtkNode *n, XtkBatchResult const *result) {
	if (!plan->children_changed) {
		for (int i = 0; i < plan->child_count; i++) {
			XtkPlanRec *cp = plan->children [i].plan;
			if (cp->subtree_dirty) n->children [i] = xtk_publication_resolve(rt, cp, result);
			if (n->children [i]) n->children [i]->parent = n;
		}
		return;
	}
	for (int i = 0; i < plan->child_count; i++) {
		n->children [i] = xtk_publication_resolve(rt, plan->children [i].plan, result);
		if (n->children [i]) n->children [i]->parent = n;
	}
	n->child_count = plan->child_count;
}

static void resolve_props(XtkPlanRec *plan, XtkNode *n) {
	if (plan->patch_slots) {
		xtk_prop_state_apply_patch(n->props, plan->patch_slots, plan->patch_count, plan->next_model_ver);
		plan->patch_slots = NULL;
		return;
	}
	if (plan->next_props) {
		xtk_prop_state_destroy(n->props);
		n->props         = plan->next_props;
		plan->next_props = NULL;
	}
}

static void resolve_state(XtkRt *rt, XtkPlanRec *plan, XtkNode *n) {
	n->type_id = XTK_EL_DATA(plan->el)->type;
	resolve_props(plan, n);
	XtkElementData *data = XTK_EL_DATA(plan->el);
	if (n->region_id && n->region_id != data->region_id && rt) xtk_rt_region_remove(rt, n);
	n->region_id       = data->region_id;
	n->region_revision = data->region_revision;
	n->region_flags    = data->region_flags & ~XTK_REGION_REF;
	n->region_build    = data->region_build;
	n->region_ctx      = data->region_ctx;
	if (n->region_id && rt) ( void ) xtk_rt_region_register(rt, n);
	if (!plan->key_changed) return;
	if (n->key.kind == XTK_KEY_STRING) xtk_alloc_free(( void * ) n->key.value.string);
	n->key         = plan->next_key;
	plan->next_key = (XtkKey) {0};
}

XtkNode *xtk_publication_resolve(XtkRt *rt, XtkPlanRec *plan, XtkBatchResult const *result) {
	if (plan->region_skip || !plan->subtree_dirty) return plan->committed;
	XtkNode *n = resolve_node(rt, plan, result);
	if (!n) return NULL;
	resolve_binding(plan, n, result);
	resolve_children(rt, plan, n, result);
	resolve_state(rt, plan, n);
	return n;
}

void xtk_publication_retire(XtkRt *rt, XtkReconcileTxn *txn) {
	for (int i = 0; i < txn->retire_count; i++) node_free_tree(rt, txn->retire_nodes [i]);
}

bool xtk_unmount_all(XtkRt *rt) {
	if (!rt || !rt->root) return true;
	XtkTxn txn;
	if (!xtk_txn_begin(&rt->scene, &txn)) return false;
	if (!xtk_txn_drop(&txn, xtk_ref_existing(( XtkCtrl ) rt->root->node))) {
		xtk_txn_abort(&txn);
		return false;
	}
	XtkBatchResult *result = xtk_txn_commit(&txn, NULL);
	if (!result) return false;
	xtk_batchresult_destroy(result);
	node_free_tree(rt, rt->root);
	rt->root = NULL;
	return true;
}
