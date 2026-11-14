#include "xtk_reconcile_internal.h"

#include "xtk_identity.h"

#include "xtk_internal.h"

static void txn_fail(XtkReconcileTxn *txn, XtkFrameStatus status) {
	txn->status = status;
	if (txn->root_plan) xtk_plan_abort_fresh(txn->root_plan);
	xtk_txn_abort(&txn->xtxn);
	txn->batch = NULL;
	xtk_scratch_reset(txn->plans);
	xtk_ui_abort_candidate(txn->rt->ui);
	txn->rt->force         = true;
	txn->rt->frame_pending = true;
}

static XtkFrameStatus txn_abort(XtkReconcileTxn *txn, XtkPlanRec *root, XtkFrameStatus status) {
	xtk_plan_abort_fresh(root);
	xtk_plan_free(root);
	txn->root_plan = NULL;
	txn_fail(txn, status);
	return txn->status;
}

static XtkFrameStatus txn_finish(XtkReconcileTxn *txn, XtkPlanRec *root, XtkBatchResult const *result) {
	txn->rt->root = xtk_publication_resolve(root, result);
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
	rt->force         = true;
	rt->frame_pending = true;
	return XTK_FRAME_BUILD_FAILED;
}

static XtkFrameStatus txn_validate_candidate(XtkReconcileTxn *txn, XtkEl *next, XtkIdentityDiag *identity) {
	xtk_scratch_reset(txn->scratch);
	if (xtk_ui_failed(txn->rt->ui) || !xtk_normalize_tree(txn->rt, next)) {
		txn_fail(txn, XTK_FRAME_BUILD_FAILED);
		return txn->status;
	}
	if (xtk_identity_validate_tree(&txn->rt->scene, next, txn->scratch, &txn->identity) == XTK_IDENTITY_OK)
		return XTK_FRAME_COMMITTED;
	txn->identity.frame_sequence = txn->rt->frame_sequence;
	if (identity) *identity = txn->identity;
	txn_fail(txn, XTK_FRAME_IDENTITY_FAILED);
	return txn->status;
}

static XtkFrameStatus txn_plan_batch(XtkReconcileTxn *txn, XtkEl *next, XtkPlanRec **root) {
	if (!xtk_txn_beginwith(&txn->rt->scene, txn->rt->batch, &txn->xtxn)) {
		txn_fail(txn, XTK_FRAME_PREFLIGHT_FAILED);
		return txn->status;
	}
	txn->batch = xtk_txn_batch(&txn->xtxn);
	if (!xtk_plan_prepare(txn, next)) {
		txn_fail(txn, XTK_FRAME_PREFLIGHT_FAILED);
		return txn->status;
	}
	if (!xtk_plan_root(txn, next, root)) return txn_abort(txn, *root, XTK_FRAME_PREFLIGHT_FAILED);
	if (!xtk_publication_preflight(txn, *root)) return txn_abort(txn, *root, XTK_FRAME_PREFLIGHT_FAILED);
	return XTK_FRAME_COMMITTED;
}

static void txn_record_batch_metrics(XtkReconcileTxn *txn) {
	txn->metrics->mutations = txn->batch->count;
	for (uint32_t i = 0; i < txn->batch->count; i++) {
		XtkBatchOp const *op = &txn->batch->ops [i];
		if (op->kind == XTK_BATCH_OP_CREATE) txn->metrics->property_patches += op->u.create.prop_count;
		if (op->kind == XTK_BATCH_OP_SET_PROP) txn->metrics->property_patches++;
	}
}

XtkFrameStatus
xtk_reconcile_run(XtkRt *rt, XtkEl *next, XtkBatchDiag *diag, XtkIdentityDiag *identity, XtkFrameMetrics *metrics) {
	XtkReconcileTxn txn = {
	  .rt = rt, .scratch = rt->scratch, .plans = rt->plan_scratch, .status = XTK_FRAME_COMMITTED, .metrics = metrics};
	if (diag) *diag = (XtkBatchDiag) {0};
	if (identity) *identity = (XtkIdentityDiag) {0};
	if (metrics) *metrics = (XtkFrameMetrics) {0};
	if (!next) return txn_null_tree(rt);

	XtkFrameStatus status = txn_validate_candidate(&txn, next, identity);
	if (status != XTK_FRAME_COMMITTED) return status;
	XtkPlanRec *root = NULL;
	status           = txn_plan_batch(&txn, next, &root);
	if (status != XTK_FRAME_COMMITTED) return status;
	txn_record_batch_metrics(&txn);
	if (txn.batch->count == 0) return txn_empty_commit(&txn, root);
	return txn_commit(&txn, root, diag);
}
