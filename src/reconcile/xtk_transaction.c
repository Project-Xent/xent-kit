#include "xtk_reconcile_internal.h"

#include "../batch/xtk_batch_internal.h"
#include "xtk_identity.h"

#include "xtk_internal.h"

static void txn_fail(XtkReconcileTxn *txn, XtkFrameStatus status) {
	txn->status = status;
	if (txn->prepared && txn->prepare) {
		txn->rt->host->vt->abort(txn->rt->host, txn->prepare);
		txn->prepare  = NULL;
		txn->prepared = false;
	}
	if (txn->root_plan) xtk_plan_abort_fresh(txn->root_plan);
	if (txn->batch) {
		xtk_batch_reset(txn->batch, txn->rt->host->vt->revision(txn->rt->host));
		txn->batch = NULL;
	}
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

static XtkFrameStatus txn_empty_commit(XtkReconcileTxn *txn, XtkEl *next, XtkPlanRec *root) {
	( void ) next;
	txn->rt->root = xtk_publication_resolve(root, NULL);
	xtk_plan_free(root);
	xtk_batch_reset(txn->batch, txn->rt->host->vt->revision(txn->rt->host));
	xtk_scratch_reset(txn->plans);
	return XTK_FRAME_COMMITTED;
}

static XtkFrameStatus
txn_diag_abort(XtkReconcileTxn *txn, XtkPlanRec *root, XtkBatchDiag *diag, XtkFrameStatus status) {
	if (diag) *diag = txn->diagnostic;
	return txn_abort(txn, root, status);
}

static XtkFrameStatus txn_host_preflight(XtkReconcileTxn *txn, XtkPlanRec *root, XtkBatchDiag *diag) {
	if (!txn->rt->host->vt->preflight) return XTK_FRAME_COMMITTED;
	XtkBatchError perr = txn->rt->host->vt->preflight(txn->rt->host, txn->batch, &txn->diagnostic);
	if (perr == XTK_BATCH_OK) return XTK_FRAME_COMMITTED;
	return txn_diag_abort(txn, root, diag, XTK_FRAME_PREFLIGHT_FAILED);
}

static void bind_created_virtual_regions(XtkRt *rt, XtkPlanRec const *plan, XtkNode const *published) {
	if (!plan || !published) return;
	XtkElementData const *data = XTK_EL_DATA(plan->el);
	if (plan->is_create && data->virtualized && rt->cfg.virtual_range) {
		XtkVirtualRange range = {data->virtual_first, data->virtual_last, data->virtual_lanes};
		rt->cfg.virtual_range(rt->cfg.ctx, published->node, &range);
	}
	for (int i = 0; i < plan->child_count; i++)
		bind_created_virtual_regions(rt, plan->children [i].plan, published->children [i]);
}

static XtkFrameStatus txn_host_commit(XtkReconcileTxn *txn, XtkEl *next, XtkPlanRec *root, XtkBatchDiag *diag) {
	XtkFrameStatus pf = txn_host_preflight(txn, root, diag);
	if (pf != XTK_FRAME_COMMITTED) return pf;

	XtkBatchError prep_err = txn->rt->host->vt->prepare(txn->rt->host, txn->batch, &txn->prepare, &txn->diagnostic);
	if (prep_err != XTK_BATCH_OK || !txn->prepare) return txn_diag_abort(txn, root, diag, XTK_FRAME_PREPARE_FAILED);
	txn->prepared          = true;

	XtkBatchResult *result = txn->rt->host->vt->commit(txn->rt->host, txn->prepare, &txn->diagnostic);
	txn->prepare           = NULL;
	txn->prepared          = false;
	if (!result) return txn_diag_abort(txn, root, diag, XTK_FRAME_COMMIT_FAILED);

	xtk_publication_verify_result(txn, root, result);
	XtkNode *published = xtk_publication_resolve(root, result);
	xtk_batchresult_destroy(result);

	txn->rt->root = published;
	bind_created_virtual_regions(txn->rt, root, published);
	xtk_publication_retire(txn->rt, txn);
	xtk_plan_free(root);
	xtk_batch_reset(txn->batch, txn->rt->host->vt->revision(txn->rt->host));
	xtk_scratch_reset(txn->plans);
	return XTK_FRAME_COMMITTED;
}

static XtkFrameStatus txn_null_tree(XtkRt *rt) {
	xtk_ui_abort_candidate(rt->ui);
	rt->force         = true;
	rt->frame_pending = true;
	return XTK_FRAME_BUILD_FAILED;
}

static XtkFrameStatus txn_validate_candidate(XtkReconcileTxn *txn, XtkEl *next, XtkIdentityDiag *identity) {
	xtk_scratch_reset(txn->scratch);
	if (xtk_ui_failed(txn->rt->ui)) {
		txn_fail(txn, XTK_FRAME_BUILD_FAILED);
		return txn->status;
	}
	if (!xtk_normalize_tree(txn->rt, next)) {
		txn_fail(txn, XTK_FRAME_BUILD_FAILED);
		return txn->status;
	}
	if (xtk_identity_validate_tree(txn->rt->host, next, txn->scratch, &txn->identity) == XTK_IDENTITY_OK)
		return XTK_FRAME_COMMITTED;
	txn->identity.frame_sequence = txn->rt->frame_sequence;
	if (identity) *identity = txn->identity;
	txn_fail(txn, XTK_FRAME_IDENTITY_FAILED);
	return txn->status;
}

static XtkFrameStatus txn_plan_batch(XtkReconcileTxn *txn, XtkEl *next, XtkPlanRec **root, XtkBatchDiag *diag) {
	txn->batch = txn->rt->batch_cache;
	xtk_batch_reset(txn->batch, txn->rt->host->vt->revision(txn->rt->host));
	if (!xtk_plan_prepare(txn, next)) {
		txn_fail(txn, XTK_FRAME_PREFLIGHT_FAILED);
		return txn->status;
	}
	if (!xtk_plan_root(txn, next, root)) return txn_abort(txn, *root, XTK_FRAME_PREFLIGHT_FAILED);
	if (!xtk_publication_preflight(txn, *root)) return txn_abort(txn, *root, XTK_FRAME_PREFLIGHT_FAILED);
	XtkBatchError err = xtk_batch_preflight(txn->batch, &txn->diagnostic);
	if (err != XTK_BATCH_OK) return txn_diag_abort(txn, *root, diag, XTK_FRAME_PREFLIGHT_FAILED);
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
	status           = txn_plan_batch(&txn, next, &root, diag);
	if (status != XTK_FRAME_COMMITTED) return status;
	txn_record_batch_metrics(&txn);
	if (txn.batch->count == 0) return txn_empty_commit(&txn, next, root);
	return txn_host_commit(&txn, next, root, diag);
}
