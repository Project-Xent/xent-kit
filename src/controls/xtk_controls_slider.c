#include "xtk_controls_internal.h"

XtkLocalId xtk_slider_create(XtkTxn *txn, XtkNodeRef parent, XtkSliderProps const *props) {
	if (!props) return xtk_txn_create(txn, XTK_CTRL_SLIDER, parent, xtk_ref_none(), NULL, 0u);
	XtkPropPatch   patches [23];
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
	xtk_controls_append_f32(patches, &count, (props->set >> 10u) & 1u, XTK_PROP_MIN_F32, props->min, change);
	xtk_controls_append_f32(patches, &count, (props->set >> 11u) & 1u, XTK_PROP_MAX_F32, props->max, change);
	xtk_controls_append_f32(patches, &count, (props->set >> 12u) & 1u, XTK_PROP_VALUE_F32, props->value, change);
	xtk_controls_append_f32(patches, &count, (props->set >> 13u) & 1u, XTK_PROP_STEP_F32, props->step, change);
	xtk_controls_append_f32(patches, &count, (props->set >> 14u) & 1u, XTK_PROP_TICK_FREQUENCY, props->tick, change);
	xtk_controls_append_enum(
	  patches, &count, (props->set >> 15u) & 1u, XTK_PROP_TICK_PLACEMENT, props->tickplace, change
	);
	xtk_controls_append_enum(
	  patches, &count, (props->set >> 16u) & 1u, XTK_PROP_SLIDER_SNAPS_TO, props->snapsto, change
	);
	xtk_controls_append_f32(
	  patches, &count, (props->set >> 17u) & 1u, XTK_PROP_SMALL_CHANGE, props->smallchange, change
	);
	xtk_controls_append_f32(
	  patches, &count, (props->set >> 18u) & 1u, XTK_PROP_LARGE_CHANGE, props->largechange, change
	);
	xtk_controls_append_enum(patches, &count, (props->set >> 19u) & 1u, XTK_PROP_ORIENTATION, props->dir, change);
	xtk_controls_append_bool(patches, &count, (props->set >> 20u) & 1u, XTK_PROP_IS_RANGE, props->range, change);
	xtk_controls_append_f32(patches, &count, (props->set >> 21u) & 1u, XTK_PROP_RANGE_START, props->rangestart, change);
	xtk_controls_append_f32(patches, &count, (props->set >> 22u) & 1u, XTK_PROP_RANGE_END, props->rangeend, change);
	return xtk_txn_create(txn, XTK_CTRL_SLIDER, parent, xtk_ref_none(), patches, count);
}

bool xtk_slider_setw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_ctrl_setf32(scene, control, XTK_PROP_WIDTH, value, change);
}

bool xtk_slider_seth(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_ctrl_setf32(scene, control, XTK_PROP_HEIGHT, value, change);
}

bool xtk_slider_setgrow(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_ctrl_setf32(scene, control, XTK_PROP_GROW, value, change);
}

bool xtk_slider_setself(XtkScene *scene, XtkCtrl control, XentFlexAlign value, XtkChangeStamp change) {
	return xtk_ctrl_setenum(scene, control, XTK_PROP_ALIGN_SELF, value, change);
}

bool xtk_slider_setml(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_ctrl_setf32(scene, control, XTK_PROP_MARGIN_LEFT, value, change);
}

bool xtk_slider_setmt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_ctrl_setf32(scene, control, XTK_PROP_MARGIN_TOP, value, change);
}

bool xtk_slider_setmr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_ctrl_setf32(scene, control, XTK_PROP_MARGIN_RIGHT, value, change);
}

bool xtk_slider_setmb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_ctrl_setf32(scene, control, XTK_PROP_MARGIN_BOTTOM, value, change);
}

bool xtk_slider_settip(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change) {
	return xtk_ctrl_setstring(scene, control, XTK_PROP_TOOLTIP, data, xtk_controls_text_len(data, len), change);
}

bool xtk_slider_setenabled(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change) {
	return xtk_ctrl_setbool(scene, control, XTK_PROP_ENABLED, value, change);
}

bool xtk_slider_setmin(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_ctrl_setf32(scene, control, XTK_PROP_MIN_F32, value, change);
}

bool xtk_slider_setmax(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_ctrl_setf32(scene, control, XTK_PROP_MAX_F32, value, change);
}

bool xtk_slider_setvalue(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_ctrl_setf32(scene, control, XTK_PROP_VALUE_F32, value, change);
}

bool xtk_slider_setstep(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_ctrl_setf32(scene, control, XTK_PROP_STEP_F32, value, change);
}

bool xtk_slider_settick(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_ctrl_setf32(scene, control, XTK_PROP_TICK_FREQUENCY, value, change);
}

bool xtk_slider_settickplace(XtkScene *scene, XtkCtrl control, XtkTickPlacement value, XtkChangeStamp change) {
	return xtk_ctrl_setenum(scene, control, XTK_PROP_TICK_PLACEMENT, value, change);
}

bool xtk_slider_setsnapsto(XtkScene *scene, XtkCtrl control, XtkSliderSnap value, XtkChangeStamp change) {
	return xtk_ctrl_setenum(scene, control, XTK_PROP_SLIDER_SNAPS_TO, value, change);
}

bool xtk_slider_setsmallchange(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_ctrl_setf32(scene, control, XTK_PROP_SMALL_CHANGE, value, change);
}

bool xtk_slider_setlargechange(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_ctrl_setf32(scene, control, XTK_PROP_LARGE_CHANGE, value, change);
}

bool xtk_slider_setdir(XtkScene *scene, XtkCtrl control, XtkStackDirection value, XtkChangeStamp change) {
	return xtk_ctrl_setenum(scene, control, XTK_PROP_ORIENTATION, value, change);
}

bool xtk_slider_setrange(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change) {
	return xtk_ctrl_setbool(scene, control, XTK_PROP_IS_RANGE, value, change);
}

bool xtk_slider_setrangestart(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_ctrl_setf32(scene, control, XTK_PROP_RANGE_START, value, change);
}

bool xtk_slider_setrangeend(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_ctrl_setf32(scene, control, XTK_PROP_RANGE_END, value, change);
}

XtkSubRef xtk_slider_onchange(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg) {
	return xtk_txn_on(txn, target, XTK_EVENT_CHANGE_F32, XTK_EVENT_PHASE_MASK_TARGET, fn, arg);
}

XtkSubRef xtk_slider_onrange(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg) {
	return xtk_txn_on(txn, target, XTK_EVENT_CHANGE_RANGE, XTK_EVENT_PHASE_MASK_TARGET, fn, arg);
}
