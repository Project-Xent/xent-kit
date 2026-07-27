#include <xtk/xtk_scene.h>

XtkScene xtk_scene_from_host(XtkHost *host) { return (XtkScene) {.host = host}; }

uint64_t xtk_scene_revision(XtkScene const *scene) {
	if (!scene || !scene->host || !scene->host->vt) return 0u;
	return scene->host->vt->revision(scene->host);
}

XtkCtrl xtk_scene_root(XtkScene const *scene) {
	if (!scene || !scene->host || !scene->host->vt) return XTK_CTRL_INVALID;
	return scene->host->vt->root(scene->host);
}

bool xtk_txn_begin(XtkScene *scene, XtkTxn *out) {
	if (!scene || !scene->host || !out) return false;
	XtkBatch *batch = xtk_batch_alloc(xtk_scene_revision(scene));
	if (!batch) return false;
	out->scene = scene;
	out->batch = batch;
	return true;
}

XtkBatchResult *xtk_txn_commit(XtkTxn *txn, XtkBatchDiag *diagnostic) {
	if (!txn || !txn->scene || !txn->scene->host || !txn->batch) return NULL;
	XtkHost     *host    = txn->scene->host;
	XtkPrepare  *prepare = NULL;
	XtkBatchDiag local;
	if (!diagnostic) diagnostic = &local;
	if (host->vt->prepare(host, txn->batch, &prepare, diagnostic) != XTK_BATCH_OK) {
		xtk_batch_free(txn->batch);
		txn->batch = NULL;
		return NULL;
	}
	XtkBatchResult *result = host->vt->commit(host, prepare, diagnostic);
	xtk_batch_free(txn->batch);
	txn->batch = NULL;
	return result;
}

void xtk_txn_abort(XtkTxn *txn) {
	if (!txn) return;
	xtk_batch_free(txn->batch);
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
	xtk_batch_result_destroy(result);
	return true;
}

bool xtk_control_set(XtkScene *scene, XtkCtrl control, XtkPropertyId id, XtkValue value, XtkChangeStamp change) {
	return one_shot_set(scene, control, id, value, change);
}

bool xtk_control_set_bool(XtkScene *scene, XtkCtrl control, XtkPropertyId id, bool value, XtkChangeStamp change) {
	return one_shot_set(scene, control, id, (XtkValue) {.kind = XTK_VALUE_BOOL, .u.b = value}, change);
}

bool xtk_control_set_f32(XtkScene *scene, XtkCtrl control, XtkPropertyId id, float value, XtkChangeStamp change) {
	return one_shot_set(scene, control, id, (XtkValue) {.kind = XTK_VALUE_F32, .u.f32 = value}, change);
}

bool xtk_control_set_i32(XtkScene *scene, XtkCtrl control, XtkPropertyId id, int32_t value, XtkChangeStamp change) {
	return one_shot_set(scene, control, id, (XtkValue) {.kind = XTK_VALUE_I32, .u.i32 = value}, change);
}

bool xtk_control_set_f64(XtkScene *scene, XtkCtrl control, XtkPropertyId id, double value, XtkChangeStamp change) {
	return one_shot_set(scene, control, id, (XtkValue) {.kind = XTK_VALUE_F64, .u.f64 = value}, change);
}

bool xtk_control_set_enum(XtkScene *scene, XtkCtrl control, XtkPropertyId id, uint32_t value, XtkChangeStamp change) {
	return one_shot_set(scene, control, id, (XtkValue) {.kind = XTK_VALUE_ENUM, .u.u32 = value}, change);
}

bool xtk_control_set_color(XtkScene *scene, XtkCtrl control, XtkPropertyId id, XtkColor value, XtkChangeStamp change) {
	return one_shot_set(scene, control, id, (XtkValue) {.kind = XTK_VALUE_COLOR, .u.color = value}, change);
}

bool xtk_control_set_resource(
  XtkScene *scene, XtkCtrl control, XtkPropertyId id, XtkResource value, XtkChangeStamp change
) {
	return one_shot_set(scene, control, id, (XtkValue) {.kind = XTK_VALUE_RESOURCE, .u.resource = value}, change);
}

bool xtk_control_set_string(
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

bool xtk_control_get(
  XtkScene const *scene, XtkCtrl control, XtkPropertyId id, XtkValueView *out_value, XtkChangeStamp *out_change
) {
	if (!scene || !scene->host || !scene->host->vt) return false;
	return scene->host->vt->prop(scene->host, control, id, out_value, out_change);
}
