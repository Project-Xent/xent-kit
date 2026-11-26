#include "xtk_reconcile_internal.h"
#include "xtk_identity.h"
#include "xtk_internal.h"

#include <string.h>

static bool status_retriable(XtkFrameStatus status) { return status != XTK_FRAME_IDENTITY_FAILED; }

static void txn_fail(XtkReconcileTxn *txn, XtkFrameStatus status) {
	txn->status = status;
	if (txn->root_plan) xtk_plan_abort_fresh(txn->root_plan);
	xtk_txn_abort(&txn->xtxn);
	txn->batch = NULL;
	xtk_scratch_reset(txn->plans);
	xtk_ui_abort_candidate(txn->rt->ui);
	if (status_retriable(status) && txn->rt->fail_retries < XTK_RETRY_CAP) {
		txn->rt->fail_retries++;
		txn->rt->force = true;
	}
}

static XtkFrameStatus txn_abort(XtkReconcileTxn *txn, XtkPlanRec *root, XtkFrameStatus status) {
	xtk_plan_abort_fresh(root);
	xtk_plan_free(root);
	txn->root_plan = NULL;
	txn_fail(txn, status);
	return txn->status;
}

static XtkFrameStatus txn_finish(XtkReconcileTxn *txn, XtkPlanRec *root, XtkBatchResult const *result) {
	txn->rt->root = xtk_publication_resolve(txn->rt, root, result);
	if (result) xtk_publication_retire(txn->rt, txn);
	xtk_plan_free(root);
	xtk_scratch_reset(txn->plans);
	return XTK_FRAME_COMMITTED;
}

static XtkFrameStatus txn_empty_commit(XtkReconcileTxn *txn, XtkPlanRec *root) {
	xtk_txn_abort(&txn->xtxn);
	return txn_finish(txn, root, NULL);
}

static XtkFrameStatus stage_status(XtkBatchStage stage) {
	if (stage == XTK_BATCH_STAGE_PREPARE) return XTK_FRAME_PREPARE_FAILED;
	if (stage == XTK_BATCH_STAGE_COMMIT) return XTK_FRAME_COMMIT_FAILED;
	return XTK_FRAME_PREFLIGHT_FAILED;
}

static XtkFrameStatus txn_commit(XtkReconcileTxn *txn, XtkPlanRec *root, XtkBatchDiag *diag) {
	uint32_t        locals = txn->batch->next_local;
	uint32_t        subs   = txn->batch->next_sub;
	XtkBatchResult *result = xtk_txn_commit(&txn->xtxn, &txn->diagnostic);
	txn->batch             = NULL;
	if (!result) {
		if (diag) *diag = txn->diagnostic;
		return txn_abort(txn, root, stage_status(txn->diagnostic.stage));
	}
	xtk_publication_verify_result(root, result, locals, subs);
	XtkFrameStatus status = txn_finish(txn, root, result);
	xtk_batchresult_destroy(result);
	return status;
}

static XtkFrameStatus txn_null_tree(XtkRt *rt) {
	xtk_ui_abort_candidate(rt->ui);
	if (rt->fail_retries < XTK_RETRY_CAP) {
		rt->fail_retries++;
		rt->force = true;
	}
	return XTK_FRAME_BUILD_FAILED;
}

static void txn_record_batch_metrics(XtkReconcileTxn *txn) {
	txn->metrics->mutations = txn->batch->count;
	for (uint32_t i = 0; i < txn->batch->count; i++) {
		XtkBatchOp const *op = &txn->batch->ops [i];
		if (op->kind == XTK_BATCH_OP_CREATE) txn->metrics->property_patches += op->u.create.prop_count;
		if (op->kind == XTK_BATCH_OP_SET_PROP) txn->metrics->property_patches++;
	}
}

static void txn_reset_arenas(XtkRt *rt, XtkBatchDiag *diag, XtkIdentityDiag *identity, XtkFrameMetrics *metrics) {
	if (diag) *diag = (XtkBatchDiag) {0};
	if (identity) *identity = (XtkIdentityDiag) {0};
	if (metrics) *metrics = (XtkFrameMetrics) {0};
	xtk_scratch_reset(rt->scratch);
	if (rt->patch_arena) xtk_arena_reset(rt->patch_arena);
}

static XtkFrameStatus txn_plan_batch(XtkReconcileTxn *txn, XtkEl *next, XtkIdentityDiag *identity, XtkPlanRec **root) {
	if (!xtk_txn_beginwith(&txn->rt->scene, txn->rt->batch, &txn->xtxn)) {
		txn_fail(txn, XTK_FRAME_PREFLIGHT_FAILED);
		return txn->status;
	}
	txn->batch = xtk_txn_batch(&txn->xtxn);
	if (!xtk_plan_prepare(txn, next)) {
		txn_fail(txn, XTK_FRAME_PREFLIGHT_FAILED);
		return txn->status;
	}
	if (!xtk_plan_root(txn, next, root)) {
		if (txn->identity_failed) {
			txn->identity.frame_sequence = txn->rt->frame_sequence;
			if (identity) *identity = txn->identity;
			return txn_abort(txn, *root, XTK_FRAME_IDENTITY_FAILED);
		}
		return txn_abort(txn, *root, XTK_FRAME_PREFLIGHT_FAILED);
	}
	return XTK_FRAME_COMMITTED;
}

XtkFrameStatus
xtk_reconcile_run(XtkRt *rt, XtkEl *next, XtkBatchDiag *diag, XtkIdentityDiag *identity, XtkFrameMetrics *metrics) {
	XtkReconcileTxn txn = {
	  .rt = rt, .scratch = rt->scratch, .plans = rt->plan_scratch, .status = XTK_FRAME_COMMITTED, .metrics = metrics};
	txn_reset_arenas(rt, diag, identity, metrics);
	if (!next) return txn_null_tree(rt);
	if (xtk_ui_failed(rt->ui) || !xtk_normalize_tree(rt, next, rt->root)) {
		txn_fail(&txn, XTK_FRAME_BUILD_FAILED);
		return txn.status;
	}
	XtkPlanRec    *root   = NULL;
	XtkFrameStatus status = txn_plan_batch(&txn, next, identity, &root);
	if (status != XTK_FRAME_COMMITTED) return status;
	txn_record_batch_metrics(&txn);
	if (txn.batch->count == 0) return txn_empty_commit(&txn, root);
	return txn_commit(&txn, root, diag);
}

typedef struct RegionTarget {
	XtkRtRegion *reg;
	XtkNode     *old;
	XtkNode     *parent;
	int          slot;
	XtkEl       *el;
	XtkPlanRec  *plan;
} RegionTarget;

static bool region_ancestor_dirty(XtkRt const *rt, XtkNode const *node) {
	for (XtkNode const *p = node->parent; p; p = p->parent) {
		if (!p->region_id) continue;
		XtkRtRegion *anc = xtk_rt_region_find(rt, p->region_id);
		if (anc && anc->dirty) return true;
	}
	return false;
}

static int region_slot_in_parent(XtkNode const *parent, XtkNode const *child) {
	if (!parent) return 0;
	for (int i = 0; i < parent->child_count; i++)
		if (parent->children [i] == child) return i;
	return -1;
}

static uint32_t collect_region_targets(XtkRt *rt, uint64_t const *ids, uint32_t count, RegionTarget *out) {
	uint32_t n = 0u;
	for (uint32_t i = 0; i < count; i++) {
		XtkRtRegion *reg = xtk_rt_region_find(rt, ids [i]);
		if (!reg || !reg->node || !reg->dirty || !reg->build || region_ancestor_dirty(rt, reg->node)) continue;
		int slot = region_slot_in_parent(reg->node->parent, reg->node);
		if (slot < 0) continue;
		out [n++] = (RegionTarget) {.reg = reg, .old = reg->node, .parent = reg->node->parent, .slot = slot};
	}
	return n;
}

static bool build_region_target(XtkRt *rt, RegionTarget *t) {
	XtkEl *el = t->reg->build(rt->ui, t->reg->ctx);
	if (!el || xtk_ui_failed(rt->ui)) return false;
	XtkElementData *data = XTK_EL_DATA(el);
	data->region_id      = t->reg->id;
	data->region_flags   = XTK_REGION_SUB;
	data->region_build   = t->reg->build;
	data->region_ctx     = t->reg->ctx;
	if (data->key.kind == XTK_KEY_NONE && t->old->key.kind != XTK_KEY_NONE) {
		if (t->old->key.kind == XTK_KEY_U64) xtk_keyed_u64(el, t->old->key.value.u64);
		else xtk_keyed(rt->ui, t->old->key.value.string, el);
	}
	if (!xtk_normalize_tree(rt, el, t->old)) return false;
	t->el = el;
	return !xtk_ui_failed(rt->ui);
}

static XtkFrameStatus regions_fail(XtkReconcileTxn *txn, RegionTarget *targets, uint32_t n, XtkFrameStatus status) {
	for (uint32_t i = 0; i < n; i++) {
		xtk_plan_abort_fresh(targets [i].plan);
		xtk_plan_free(targets [i].plan);
	}
	txn->root_plan = NULL;
	txn_fail(txn, status);
	return txn->status;
}

static bool plan_region_target(XtkReconcileTxn *txn, RegionTarget *t) {
	XtkNodeRef pref   = xtk_ref_existing(( XtkCtrl ) (t->parent ? t->parent->node : txn->rt->host_root));
	XtkNodeRef before = t->parent && t->slot + 1 < t->parent->child_count
	                    ? xtk_ref_existing(( XtkCtrl ) t->parent->children [t->slot + 1]->node)
	                    : xtk_ref_none();
	return xtk_plan_subtree(txn, t->el, t->old, pref, before, &t->plan);
}

static void resolve_region_targets(
  XtkRt *rt, XtkReconcileTxn *txn, RegionTarget *targets, uint32_t n, XtkBatchResult const *result
) {
	for (uint32_t i = 0; i < n; i++) {
		XtkNode *res = xtk_publication_resolve(rt, targets [i].plan, result);
		if (res) res->parent = targets [i].parent;
		if (targets [i].parent) targets [i].parent->children [targets [i].slot] = res;
		else rt->root = res;
		xtk_plan_free(targets [i].plan);
	}
	if (result) xtk_publication_retire(rt, txn);
	xtk_scratch_reset(txn->plans);
	for (uint32_t i = 0; i < rt->dirty_region_count; i++) {
		XtkRtRegion *reg = xtk_rt_region_find(rt, rt->dirty_regions [i]);
		if (reg) reg->dirty = false;
	}
	rt->dirty_region_count = 0u;
}

static bool
region_verify_plans(RegionTarget const *targets, uint32_t n, XtkBatchResult const *result, uint32_t l, uint32_t s) {
	for (uint32_t i = 0; i < n; i++) xtk_publication_verify_result(targets [i].plan, result, l, s);
	return result != NULL;
}

static bool regions_plan_all(
  XtkRt *rt, XtkReconcileTxn *txn, RegionTarget *targets, uint32_t n, XtkIdentityDiag *identity,
  XtkFrameStatus *fail_status
) {
	for (uint32_t i = 0; i < n; i++) {
		if (build_region_target(rt, &targets [i])) continue;
		*fail_status = regions_fail(txn, targets, 0u, XTK_FRAME_BUILD_FAILED);
		return false;
	}
	if (!xtk_txn_beginwith(&rt->scene, rt->batch, &txn->xtxn) || !xtk_plan_prepare(txn, targets [0].el)) {
		*fail_status = regions_fail(txn, targets, 0u, XTK_FRAME_PREFLIGHT_FAILED);
		return false;
	}
	txn->batch = xtk_txn_batch(&txn->xtxn);
	for (uint32_t i = 0; i < n; i++) {
		if (plan_region_target(txn, &targets [i])) continue;
		if (txn->identity_failed) {
			txn->identity.frame_sequence = rt->frame_sequence;
			if (identity) *identity = txn->identity;
			*fail_status = regions_fail(txn, targets, n, XTK_FRAME_IDENTITY_FAILED);
			return false;
		}
		*fail_status = regions_fail(txn, targets, n, XTK_FRAME_PREFLIGHT_FAILED);
		return false;
	}
	return true;
}

static XtkBatchResult *
regions_commit_batch(XtkReconcileTxn *txn, RegionTarget const *targets, uint32_t n, XtkBatchDiag *diag, bool *ok) {
	*ok = true;
	if (txn->batch->count == 0u) {
		xtk_txn_abort(&txn->xtxn);
		return NULL;
	}
	uint32_t        locals = txn->batch->next_local;
	uint32_t        subs   = txn->batch->next_sub;
	XtkBatchResult *result = xtk_txn_commit(&txn->xtxn, &txn->diagnostic);
	txn->batch             = NULL;
	if (!result) {
		if (diag) *diag = txn->diagnostic;
		*ok = false;
		return NULL;
	}
	region_verify_plans(targets, n, result, locals, subs);
	return result;
}

XtkFrameStatus xtk_reconcile_regions(
  XtkRt *rt, uint64_t const *ids, uint32_t count, XtkBatchDiag *diag, XtkIdentityDiag *identity,
  XtkFrameMetrics *metrics
) {
	XtkReconcileTxn txn = {
	  .rt = rt, .scratch = rt->scratch, .plans = rt->plan_scratch, .status = XTK_FRAME_COMMITTED, .metrics = metrics};
	txn_reset_arenas(rt, diag, identity, metrics);
	xtk_ui_begin(rt->ui);
	RegionTarget *targets
	  = count ? ( RegionTarget * ) xtk_arena_alloc(xtk_ui_arena(rt->ui), sizeof(*targets) * count) : NULL;
	if (!targets) {
		txn_fail(&txn, XTK_FRAME_BUILD_FAILED);
		return txn.status;
	}
	uint32_t n = collect_region_targets(rt, ids, count, targets);
	if (n == 0u) {
		rt->dirty_region_count = 0u;
		return XTK_FRAME_CLEAN;
	}
	uint32_t       prior_committed = rt->committed_count;
	XtkFrameStatus fail_status     = XTK_FRAME_COMMITTED;
	if (!regions_plan_all(rt, &txn, targets, n, identity, &fail_status)) return fail_status;
	txn_record_batch_metrics(&txn);
	bool            commit_ok = false;
	XtkBatchResult *result    = regions_commit_batch(&txn, targets, n, diag, &commit_ok);
	if (!commit_ok) return regions_fail(&txn, targets, n, stage_status(txn.diagnostic.stage));
	resolve_region_targets(rt, &txn, targets, n, result);
	xtk_batchresult_destroy(result);
	if (metrics && prior_committed > metrics->nodes_compared)
		metrics->nodes_skipped += prior_committed - metrics->nodes_compared;
	return XTK_FRAME_COMMITTED;
}
