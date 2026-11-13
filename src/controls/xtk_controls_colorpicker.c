#include "xtk_controls_internal.h"

XtkLocalId xtk_colorpicker_create(XtkTxn *txn, XtkNodeRef parent, XtkColorPickerProps const *props) {
	if (!props) return xtk_txn_create(txn, XTK_CTRL_COLORPICKER, parent, xtk_ref_none(), NULL, 0u);
	XtkPropPatch   patches [14];
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
	xtk_controls_append_color(patches, &count, (props->set >> 10u) & 1u, XTK_PROP_COLOR, props->color, change);
	xtk_controls_append_bool(patches, &count, (props->set >> 11u) & 1u, XTK_PROP_ALPHA_ENABLED, props->alpha, change);
	xtk_controls_append_bool(
	  patches, &count, (props->set >> 12u) & 1u, XTK_PROP_MORE_BUTTON_VISIBLE, props->morebutton, change
	);
	xtk_controls_append_enum(patches, &count, (props->set >> 13u) & 1u, XTK_PROP_SPECTRUM, props->spectrum, change);
	return xtk_txn_create(txn, XTK_CTRL_COLORPICKER, parent, xtk_ref_none(), patches, count);
}

bool xtk_colorpicker_setw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_ctrl_setf32(scene, control, XTK_PROP_WIDTH, value, change);
}

bool xtk_colorpicker_seth(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_ctrl_setf32(scene, control, XTK_PROP_HEIGHT, value, change);
}

bool xtk_colorpicker_setgrow(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_ctrl_setf32(scene, control, XTK_PROP_GROW, value, change);
}

bool xtk_colorpicker_setself(XtkScene *scene, XtkCtrl control, uint32_t value, XtkChangeStamp change) {
	return xtk_ctrl_setenum(scene, control, XTK_PROP_ALIGN_SELF, value, change);
}

bool xtk_colorpicker_setml(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_ctrl_setf32(scene, control, XTK_PROP_MARGIN_LEFT, value, change);
}

bool xtk_colorpicker_setmt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_ctrl_setf32(scene, control, XTK_PROP_MARGIN_TOP, value, change);
}

bool xtk_colorpicker_setmr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_ctrl_setf32(scene, control, XTK_PROP_MARGIN_RIGHT, value, change);
}

bool xtk_colorpicker_setmb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_ctrl_setf32(scene, control, XTK_PROP_MARGIN_BOTTOM, value, change);
}

bool xtk_colorpicker_settip(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change) {
	return xtk_ctrl_setstring(scene, control, XTK_PROP_TOOLTIP, data, xtk_controls_text_len(data, len), change);
}

bool xtk_colorpicker_setenabled(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change) {
	return xtk_ctrl_setbool(scene, control, XTK_PROP_ENABLED, value, change);
}

bool xtk_colorpicker_setcolor(XtkScene *scene, XtkCtrl control, XtkColor value, XtkChangeStamp change) {
	return xtk_ctrl_setcolor(scene, control, XTK_PROP_COLOR, value, change);
}

bool xtk_colorpicker_setalpha(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change) {
	return xtk_ctrl_setbool(scene, control, XTK_PROP_ALPHA_ENABLED, value, change);
}

bool xtk_colorpicker_setmorebutton(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change) {
	return xtk_ctrl_setbool(scene, control, XTK_PROP_MORE_BUTTON_VISIBLE, value, change);
}

bool xtk_colorpicker_setspectrum(XtkScene *scene, XtkCtrl control, uint32_t value, XtkChangeStamp change) {
	return xtk_ctrl_setenum(scene, control, XTK_PROP_SPECTRUM, value, change);
}

XtkSubRef xtk_colorpicker_onvalue(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg) {
	return xtk_txn_on(txn, target, XTK_EVENT_VALUE_CHANGED, XTK_EVENT_PHASE_MASK_TARGET, fn, arg);
}
