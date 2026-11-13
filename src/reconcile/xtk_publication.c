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

static bool result_counts_ok(XtkReconcileTxn const *txn, XtkBatchResult const *result) {
	if (!result) return false;
	return result->control_count == txn->batch->next_local && result->subscription_count == txn->batch->next_sub;
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

void xtk_publication_verify_result(XtkReconcileTxn const *txn, XtkPlanRec const *plan, XtkBatchResult const *result) {
	if (!result_counts_ok(txn, result) || !result_arrays_ok(result) || !result_plan_ok(plan, result)) abort();
}

static bool node_reserve(XtkNode *n, int count) {
	if (count < 0) return false;
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

static void node_free_tree(XtkRt *rt, XtkNode *n) {
	if (!n) return;
	for (int i = 0; i < n->child_count; i++) node_free_tree(rt, n->children [i]);
	if (rt->cfg.node_cleanup) rt->cfg.node_cleanup(rt->cfg.ctx, n->node, n->ext);
	xtk_alloc_free(n->binding);
	xtk_prop_state_destroy(n->props);
	if (n->key.kind == XTK_KEY_STRING) xtk_alloc_free(( void * ) n->key.value.string);
	xtk_alloc_free(n->sub_ids);
	xtk_alloc_free(n->children);
	xtk_alloc_free(n);
}

static bool publish_reserve_subs(XtkNode *n, int sub_token_count) {
	if (sub_token_count <= 0 || sub_token_count <= n->sub_cap) return true;
	XtkSubId *ids = ( XtkSubId * ) xtk_alloc_resize(n->sub_ids, sizeof(*ids) * ( size_t ) sub_token_count);
	if (!ids) return false;
	n->sub_ids = ids;
	n->sub_cap = sub_token_count;
	return true;
}

static bool preflight_children(XtkReconcileTxn *txn, XtkPlanRec *plan) {
	for (int i = 0; i < plan->child_count; i++)
		if (!xtk_publication_preflight(txn, plan->children [i].plan)) return false;
	return true;
}

bool xtk_publication_preflight(XtkReconcileTxn *txn, XtkPlanRec *plan) {
	if (!plan) return true;
	if (plan->region_skip) return true;
	XtkNode *n = plan->is_create ? plan->fresh : plan->committed;
	if (!n) return false;
	if (!node_reserve(n, plan->child_count)) return false;
	if (!publish_reserve_subs(n, plan->sub_token_count)) return false;
	return preflight_children(txn, plan);
}

static XtkNode *resolve_node(XtkPlanRec *plan, XtkBatchResult const *result) {
	XtkNode *n = plan->is_create ? plan->fresh : plan->committed;
	if (!plan->is_create) return n;
	XtkCtrl control = control_for_local(result, plan->local);
	if (control == XTK_CTRL_INVALID) return NULL;
	n->node     = ( XentNodeId ) control;
	n->host     = ( XentNodeId ) control;
	plan->fresh = NULL;
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

static void resolve_children(XtkPlanRec *plan, XtkNode *n, XtkBatchResult const *result) {
	for (int i = 0; i < plan->child_count; i++)
		n->children [i] = xtk_publication_resolve(plan->children [i].plan, result);
	n->child_count = plan->child_count;
}

static void resolve_state(XtkPlanRec *plan, XtkNode *n) {
	n->type_id = XTK_EL_DATA(plan->el)->type;
	if (plan->next_props) {
		xtk_prop_state_destroy(n->props);
		n->props         = plan->next_props;
		plan->next_props = NULL;
	}
	XtkElementData *data = XTK_EL_DATA(plan->el);
	n->region_id         = data->region_id;
	n->region_revision   = data->region_revision;
	n->region_flags      = data->region_flags & ~XTK_REGION_REF;
	if (!plan->key_changed) return;
	if (n->key.kind == XTK_KEY_STRING) xtk_alloc_free(( void * ) n->key.value.string);
	n->key         = plan->next_key;
	plan->next_key = (XtkKey) {0};
}

XtkNode *xtk_publication_resolve(XtkPlanRec *plan, XtkBatchResult const *result) {
	if (plan->region_skip) return plan->committed;
	XtkNode *n = resolve_node(plan, result);
	if (!n) return NULL;
	resolve_binding(plan, n, result);
	resolve_children(plan, n, result);
	resolve_state(plan, n);
	return n;
}

void xtk_publication_retire(XtkRt *rt, XtkReconcileTxn *txn) {
	for (int i = 0; i < txn->retire_count; i++) node_free_tree(rt, txn->retire_nodes [i]);
}

static bool unmount_commit(XtkRt *rt, XtkBatch *batch) {
	XtkPrepare  *prep = NULL;
	XtkBatchDiag d    = {0};
	if (rt->host->vt->prepare(rt->host, batch, &prep, &d) != XTK_BATCH_OK || !prep) {
		if (prep) rt->host->vt->abort(rt->host, prep);
		return false;
	}
	XtkBatchResult *result = rt->host->vt->commit(rt->host, prep, &d);
	if (!result) return false;
	xtk_batchresult_destroy(result);
	return true;
}

bool xtk_unmount_all(XtkRt *rt) {
	if (!rt || !rt->root) return true;
	XtkBatch *batch = xtk_batch_alloc(rt->host->vt->revision(rt->host));
	if (!batch) return false;
	bool ok = xtk_batch_drop(batch, xtk_ref_existing(( XtkCtrl ) rt->root->node)) && unmount_commit(rt, batch);
	xtk_batch_free(batch);
	if (!ok) return false;
	node_free_tree(rt, rt->root);
	rt->root = NULL;
	return true;
}
