#include "xtk_controls_internal.h"

XtkLocalId xtk_scrollbar_create(XtkTxn *txn, XtkNodeRef parent, XtkScrollBarProps const *props) {
	if (!props) return xtk_txn_create(txn, XTK_CTRL_SCROLLBAR, parent, xtk_ref_none(), NULL, 0u);
	XtkPropPatch   patches [18];
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
	xtk_controls_append_bool(patches, &count, (props->set >> 9u) & 1u, XTK_PROP_ENABLED, props->enabled, change);
	xtk_controls_append_enum(patches, &count, (props->set >> 10u) & 1u, XTK_PROP_ORIENTATION, props->dir, change);
	xtk_controls_append_f64(patches, &count, (props->set >> 11u) & 1u, XTK_PROP_MIN_F64, props->min, change);
	xtk_controls_append_f64(patches, &count, (props->set >> 12u) & 1u, XTK_PROP_MAX_F64, props->max, change);
	xtk_controls_append_f64(patches, &count, (props->set >> 13u) & 1u, XTK_PROP_VALUE_F64, props->value, change);
	xtk_controls_append_f64(patches, &count, (props->set >> 14u) & 1u, XTK_PROP_VIEWPORT_SIZE, props->viewport, change);
	xtk_controls_append_f32(
	  patches, &count, (props->set >> 15u) & 1u, XTK_PROP_SMALL_CHANGE, props->smallchange, change
	);
	xtk_controls_append_f32(
	  patches, &count, (props->set >> 16u) & 1u, XTK_PROP_LARGE_CHANGE, props->largechange, change
	);
	xtk_controls_append_enum(
	  patches, &count, (props->set >> 17u) & 1u, XTK_PROP_INDICATOR_MODE, props->indicator, change
	);
	return xtk_txn_create(txn, XTK_CTRL_SCROLLBAR, parent, xtk_ref_none(), patches, count);
}

bool xtk_scrollbar_setw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_ctrl_setf32(scene, control, XTK_PROP_WIDTH, value, change);
}

bool xtk_scrollbar_seth(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_ctrl_setf32(scene, control, XTK_PROP_HEIGHT, value, change);
}

bool xtk_scrollbar_setgrow(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_ctrl_setf32(scene, control, XTK_PROP_GROW, value, change);
}

bool xtk_scrollbar_setself(XtkScene *scene, XtkCtrl control, uint32_t value, XtkChangeStamp change) {
	return xtk_ctrl_setenum(scene, control, XTK_PROP_ALIGN_SELF, value, change);
}

bool xtk_scrollbar_setml(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_ctrl_setf32(scene, control, XTK_PROP_MARGIN_LEFT, value, change);
}

bool xtk_scrollbar_setmt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_ctrl_setf32(scene, control, XTK_PROP_MARGIN_TOP, value, change);
}

bool xtk_scrollbar_setmr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_ctrl_setf32(scene, control, XTK_PROP_MARGIN_RIGHT, value, change);
}

bool xtk_scrollbar_setmb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_ctrl_setf32(scene, control, XTK_PROP_MARGIN_BOTTOM, value, change);
}

bool xtk_scrollbar_settip(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change) {
	return xtk_ctrl_setstring(scene, control, XTK_PROP_TOOLTIP, data, xtk_controls_text_len(data, len), change);
}

bool xtk_scrollbar_setenabled(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change) {
	return xtk_ctrl_setbool(scene, control, XTK_PROP_ENABLED, value, change);
}

bool xtk_scrollbar_setdir(XtkScene *scene, XtkCtrl control, uint32_t value, XtkChangeStamp change) {
	return xtk_ctrl_setenum(scene, control, XTK_PROP_ORIENTATION, value, change);
}

bool xtk_scrollbar_setmin(XtkScene *scene, XtkCtrl control, double value, XtkChangeStamp change) {
	return xtk_ctrl_setf64(scene, control, XTK_PROP_MIN_F64, value, change);
}

bool xtk_scrollbar_setmax(XtkScene *scene, XtkCtrl control, double value, XtkChangeStamp change) {
	return xtk_ctrl_setf64(scene, control, XTK_PROP_MAX_F64, value, change);
}

bool xtk_scrollbar_setvalue(XtkScene *scene, XtkCtrl control, double value, XtkChangeStamp change) {
	return xtk_ctrl_setf64(scene, control, XTK_PROP_VALUE_F64, value, change);
}

bool xtk_scrollbar_setviewport(XtkScene *scene, XtkCtrl control, double value, XtkChangeStamp change) {
	return xtk_ctrl_setf64(scene, control, XTK_PROP_VIEWPORT_SIZE, value, change);
}

bool xtk_scrollbar_setsmallchange(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_ctrl_setf32(scene, control, XTK_PROP_SMALL_CHANGE, value, change);
}

bool xtk_scrollbar_setlargechange(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_ctrl_setf32(scene, control, XTK_PROP_LARGE_CHANGE, value, change);
}

bool xtk_scrollbar_setindicator(XtkScene *scene, XtkCtrl control, uint32_t value, XtkChangeStamp change) {
	return xtk_ctrl_setenum(scene, control, XTK_PROP_INDICATOR_MODE, value, change);
}

XtkSubRef xtk_scrollbar_onchange(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg) {
	return xtk_txn_on(txn, target, XTK_EVENT_CHANGE_F64, XTK_EVENT_PHASE_MASK_TARGET, fn, arg);
}
