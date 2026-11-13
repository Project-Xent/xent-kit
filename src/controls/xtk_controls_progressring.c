#include "xtk_controls_internal.h"

XtkLocalId xtk_progressring_create(XtkTxn *txn, XtkNodeRef parent, XtkProgressProps const *props) {
	if (!props) return xtk_txn_create(txn, XTK_CTRL_PROGRESSRING, parent, xtk_ref_none(), NULL, 0u);
	XtkPropPatch   patches [20];
	uint32_t       count  = 0u;
	XtkChangeStamp change = props->stamp;
	xtk_controls_append_f32(patches, &count, (props->set >> 0u) & 1u, XTK_PROP_WIDTH, props->w, change);
	xtk_controls_append_f32(patches, &count, (props->set >> 1u) & 1u, XTK_PROP_HEIGHT, props->h, change);
	xtk_controls_append_f32(patches, &count, (props->set >> 2u) & 1u, XTK_PROP_GROW, props->grow, change);
	xtk_controls_append_enum(patches, &count, (props->set >> 3u) & 1u, XTK_PROP_ALIGN_SELF, props->self, change);
	xtk_controls_append_f32(patches, &count, (props->set >> 4u) & 1u, XTK_PROP_MARGIN_LEFT, props->ml, change);
	xtk_controls_append_f32(patches, &count, (props->set >> 5u) & 1u, XTK_PROP_MARGIN_TOP, props->mt, change);
	xtk_controls_append_f32(patches, &count, (props->set >> 6u) & 1u, XTK_PROP_MARGIN_RIGHT, props->mr, change);
	xtk_controls_append_f32(patches, &count, (props->set >> 7u) & 1u, XTK_PROP_MARGIN_BOTTOM, props->mb, change);
	xtk_controls_append_string(
	  patches, &count, (props->set >> 8u) & 1u, XTK_PROP_TOOLTIP, props->tip, props->tip_len, change
	);
	xtk_controls_append_f32(patches, &count, (props->set >> 9u) & 1u, XTK_PROP_MIN_F32, props->min, change);
	xtk_controls_append_f32(patches, &count, (props->set >> 10u) & 1u, XTK_PROP_MAX_F32, props->max, change);
	xtk_controls_append_f32(patches, &count, (props->set >> 11u) & 1u, XTK_PROP_VALUE_F32, props->value, change);
	xtk_controls_append_bool(
	  patches, &count, (props->set >> 12u) & 1u, XTK_PROP_INDETERMINATE, props->indeterminate, change
	);
	xtk_controls_append_enum(patches, &count, (props->set >> 13u) & 1u, XTK_PROP_PROGRESS_STATE, props->state, change);
	xtk_controls_append_bool(
	  patches, &count, (props->set >> 14u) & 1u, XTK_PROP_PROGRESS_ACTIVE, props->active, change
	);
	return xtk_txn_create(txn, XTK_CTRL_PROGRESSRING, parent, xtk_ref_none(), patches, count);
}

bool xtk_progressring_setw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_ctrl_setf32(scene, control, XTK_PROP_WIDTH, value, change);
}

bool xtk_progressring_seth(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_ctrl_setf32(scene, control, XTK_PROP_HEIGHT, value, change);
}

bool xtk_progressring_setgrow(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_ctrl_setf32(scene, control, XTK_PROP_GROW, value, change);
}

bool xtk_progressring_setself(XtkScene *scene, XtkCtrl control, uint32_t value, XtkChangeStamp change) {
	return xtk_ctrl_setenum(scene, control, XTK_PROP_ALIGN_SELF, value, change);
}

bool xtk_progressring_setml(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_ctrl_setf32(scene, control, XTK_PROP_MARGIN_LEFT, value, change);
}

bool xtk_progressring_setmt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_ctrl_setf32(scene, control, XTK_PROP_MARGIN_TOP, value, change);
}

bool xtk_progressring_setmr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_ctrl_setf32(scene, control, XTK_PROP_MARGIN_RIGHT, value, change);
}

bool xtk_progressring_setmb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_ctrl_setf32(scene, control, XTK_PROP_MARGIN_BOTTOM, value, change);
}

bool xtk_progressring_settip(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change) {
	return xtk_ctrl_setstring(scene, control, XTK_PROP_TOOLTIP, data, xtk_controls_text_len(data, len), change);
}

bool xtk_progressring_setmin(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_ctrl_setf32(scene, control, XTK_PROP_MIN_F32, value, change);
}

bool xtk_progressring_setmax(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_ctrl_setf32(scene, control, XTK_PROP_MAX_F32, value, change);
}

bool xtk_progressring_setvalue(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_ctrl_setf32(scene, control, XTK_PROP_VALUE_F32, value, change);
}

bool xtk_progressring_setindeterminate(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change) {
	return xtk_ctrl_setbool(scene, control, XTK_PROP_INDETERMINATE, value, change);
}

bool xtk_progressring_setstate(XtkScene *scene, XtkCtrl control, uint32_t value, XtkChangeStamp change) {
	return xtk_ctrl_setenum(scene, control, XTK_PROP_PROGRESS_STATE, value, change);
}

bool xtk_progressring_setactive(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change) {
	return xtk_ctrl_setbool(scene, control, XTK_PROP_PROGRESS_ACTIVE, value, change);
}
