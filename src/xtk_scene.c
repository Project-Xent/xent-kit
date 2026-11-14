#include <xtk/xtk_scene.h>

#include "batch/xtk_batch_internal.h"

XtkScene xtk_scene_fromhost(XtkHost *host) { return (XtkScene) {.host = host}; }

uint64_t xtk_scene_revision(XtkScene const *scene) {
	if (!scene || !scene->host || !scene->host->vt) return 0u;
	return scene->host->vt->revision(scene->host);
}

XtkCtrl xtk_scene_root(XtkScene const *scene) {
	if (!scene || !scene->host || !scene->host->vt) return XTK_CTRL_INVALID;
	return scene->host->vt->root(scene->host);
}

XtkCtrlDesc const *xtk_scene_ctrldesc(XtkScene const *scene, XtkCtrlId type) {
	if (!scene || !scene->host || !scene->host->vt || type == XTK_CTRL_ID_INVALID) return NULL;
	return scene->host->vt->desc(scene->host, type);
}

bool xtk_txn_begin(XtkScene *scene, XtkTxn *out) {
	if (!scene || !scene->host || !out) return false;
	XtkBatch *batch = xtk_batch_alloc(xtk_scene_revision(scene));
	if (!batch) return false;
	*out = (XtkTxn) {.scene = scene, .batch = batch};
	return true;
}

bool xtk_txn_beginwith(XtkScene *scene, XtkBatch *batch, XtkTxn *out) {
	if (!scene || !scene->host || !batch || !out) return false;
	xtk_batch_reset(batch, xtk_scene_revision(scene));
	*out = (XtkTxn) {.scene = scene, .batch = batch, .borrowed = true};
	return true;
}

static XtkBatchResult *txn_fail(XtkTxn *txn, XtkBatchDiag *diagnostic, XtkBatchStage stage) {
	diagnostic->stage = stage;
	xtk_txn_abort(txn);
	return NULL;
}

static bool        txn_live(XtkTxn const *txn) { return txn && txn->scene && txn->scene->host && txn->batch; }

static XtkPrepare *txn_prepare(XtkHost *host, XtkBatch *batch, XtkBatchDiag *diagnostic) {
	XtkPrepare *prepare = NULL;
	if (host->vt->prepare(host, batch, &prepare, diagnostic) == XTK_BATCH_OK) return prepare;
	if (prepare) host->vt->abort(host, prepare);
	return NULL;
}

XtkBatchResult *xtk_txn_commit(XtkTxn *txn, XtkBatchDiag *diagnostic) {
	if (!txn_live(txn)) return NULL;
	XtkHost     *host = txn->scene->host;
	XtkBatchDiag local;
	if (!diagnostic) diagnostic = &local;
	if (xtk_batch_preflight(txn->batch, diagnostic) != XTK_BATCH_OK)
		return txn_fail(txn, diagnostic, XTK_BATCH_STAGE_VALIDATE);
	if (host->vt->preflight && host->vt->preflight(host, txn->batch, diagnostic) != XTK_BATCH_OK)
		return txn_fail(txn, diagnostic, XTK_BATCH_STAGE_PREFLIGHT);
	XtkPrepare *prepare = txn_prepare(host, txn->batch, diagnostic);
	if (!prepare) return txn_fail(txn, diagnostic, XTK_BATCH_STAGE_PREPARE);
	XtkBatchResult *result = host->vt->commit(host, prepare, diagnostic);
	if (!result) diagnostic->stage = XTK_BATCH_STAGE_COMMIT;
	xtk_txn_abort(txn);
	return result;
}

void xtk_txn_abort(XtkTxn *txn) {
	if (!txn || !txn->batch) return;
	if (txn->borrowed) xtk_batch_reset(txn->batch, xtk_scene_revision(txn->scene));
	else xtk_batch_free(txn->batch);
	txn->batch = NULL;
}

XtkBatch  *xtk_txn_batch(XtkTxn *txn) { return txn ? txn->batch : NULL; }

XtkLocalId xtk_txn_create(
  XtkTxn *txn, XtkCtrlId type, XtkNodeRef parent, XtkNodeRef before, XtkPropPatch const *props, uint32_t prop_count
) {
	if (!txn || !txn->batch) return XTK_LOCAL_INVALID;
	return xtk_batch_create(txn->batch, type, parent, before, props, prop_count);
}

bool xtk_txn_drop(XtkTxn *txn, XtkNodeRef target) { return txn && txn->batch && xtk_batch_drop(txn->batch, target); }

bool xtk_txn_set(XtkTxn *txn, XtkNodeRef target, XtkPropertyId id, XtkValue value, XtkChangeStamp change) {
	return txn && txn->batch && xtk_batch_set(txn->batch, target, id, value, change);
}

bool xtk_txn_insert(XtkTxn *txn, XtkNodeRef parent, XtkNodeRef child, XtkNodeRef before) {
	return txn && txn->batch && xtk_batch_insert(txn->batch, parent, child, before);
}

bool xtk_txn_move(XtkTxn *txn, XtkNodeRef parent, XtkNodeRef child, XtkNodeRef before) {
	return txn && txn->batch && xtk_batch_move(txn->batch, parent, child, before);
}

bool xtk_txn_reparent(XtkTxn *txn, XtkNodeRef child, XtkNodeRef new_parent, XtkNodeRef before) {
	return txn && txn->batch && xtk_batch_reparent(txn->batch, child, new_parent, before);
}

XtkSubRef xtk_txn_on(XtkTxn *txn, XtkNodeRef target, XtkEventId event, uint32_t phases, XtkEventFn fn, void *arg) {
	if (!txn || !txn->batch) return XTK_SUB_TOKEN_INVALID;
	return xtk_batch_on(txn->batch, target, event, phases, fn, arg);
}

bool        xtk_txn_off(XtkTxn *txn, XtkSubId id) { return txn && txn->batch && xtk_batch_off(txn->batch, id); }

static bool one_shot_set(XtkScene *scene, XtkCtrl control, XtkPropertyId id, XtkValue value, XtkChangeStamp change) {
	XtkTxn txn;
	if (!xtk_txn_begin(scene, &txn)) return false;
	if (!xtk_txn_set(&txn, xtk_ref_existing(control), id, value, change)) {
		xtk_txn_abort(&txn);
		return false;
	}
	XtkBatchResult *result = xtk_txn_commit(&txn, NULL);
	if (!result) return false;
	xtk_batchresult_destroy(result);
	return true;
}

bool xtk_ctrl_set(XtkScene *scene, XtkCtrl control, XtkPropertyId id, XtkValue value, XtkChangeStamp change) {
	return one_shot_set(scene, control, id, value, change);
}

bool xtk_ctrl_setbool(XtkScene *scene, XtkCtrl control, XtkPropertyId id, bool value, XtkChangeStamp change) {
	return one_shot_set(scene, control, id, (XtkValue) {.kind = XTK_VALUE_BOOL, .u.b = value}, change);
}

bool xtk_ctrl_setf32(XtkScene *scene, XtkCtrl control, XtkPropertyId id, float value, XtkChangeStamp change) {
	return one_shot_set(scene, control, id, (XtkValue) {.kind = XTK_VALUE_F32, .u.f32 = value}, change);
}

bool xtk_ctrl_seti32(XtkScene *scene, XtkCtrl control, XtkPropertyId id, int32_t value, XtkChangeStamp change) {
	return one_shot_set(scene, control, id, (XtkValue) {.kind = XTK_VALUE_I32, .u.i32 = value}, change);
}

bool xtk_ctrl_setf64(XtkScene *scene, XtkCtrl control, XtkPropertyId id, double value, XtkChangeStamp change) {
	return one_shot_set(scene, control, id, (XtkValue) {.kind = XTK_VALUE_F64, .u.f64 = value}, change);
}

bool xtk_ctrl_setenum(XtkScene *scene, XtkCtrl control, XtkPropertyId id, uint32_t value, XtkChangeStamp change) {
	return one_shot_set(scene, control, id, (XtkValue) {.kind = XTK_VALUE_ENUM, .u.u32 = value}, change);
}

bool xtk_ctrl_setcolor(XtkScene *scene, XtkCtrl control, XtkPropertyId id, XtkColor value, XtkChangeStamp change) {
	return one_shot_set(scene, control, id, (XtkValue) {.kind = XTK_VALUE_COLOR, .u.color = value}, change);
}

bool xtk_ctrl_setresource(
  XtkScene *scene, XtkCtrl control, XtkPropertyId id, XtkResource value, XtkChangeStamp change
) {
	return one_shot_set(scene, control, id, (XtkValue) {.kind = XTK_VALUE_RESOURCE, .u.resource = value}, change);
}

bool xtk_ctrl_setstring(
  XtkScene *scene, XtkCtrl control, XtkPropertyId id, char const *data, uint32_t len, XtkChangeStamp change
) {
	if (data == NULL && len > 0u) return false;
	return one_shot_set(
	  scene, control, id,
	  (XtkValue) {
		.kind = XTK_VALUE_STRING, .u.string = {.data = ( char * ) data, .len = len}
    },
	  change
	);
}

bool xtk_ctrl_get(
  XtkScene const *scene, XtkCtrl control, XtkPropertyId id, XtkValueView *out_value, XtkChangeStamp *out_change
) {
	if (!scene || !scene->host || !scene->host->vt) return false;
	return scene->host->vt->prop(scene->host, control, id, out_value, out_change);
}
