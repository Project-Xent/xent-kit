#include "xtk_controls_internal.h"

XtkLocalId xtk_tooltip_create(XtkTxn *txn, XtkNodeRef parent, XtkOverlayProps const *props) {
	if (!props) return xtk_txn_create(txn, XTK_CTRL_TOOLTIP, parent, xtk_ref_none(), NULL, 0u);
	XtkPropPatch   patches [12];
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
	  patches, &count, (props->set >> 8u) & 1u, XTK_PROP_TEXT, props->text, props->text_len, change
	);
	xtk_controls_append_string(
	  patches, &count, (props->set >> 9u) & 1u, XTK_PROP_TOOLTIP, props->tip, props->tip_len, change
	);
	xtk_controls_append_bool(patches, &count, (props->set >> 10u) & 1u, XTK_PROP_OPEN, props->open, change);
	xtk_controls_append_bool(patches, &count, (props->set >> 11u) & 1u, XTK_PROP_ENABLED, props->enabled, change);
	return xtk_txn_create(txn, XTK_CTRL_TOOLTIP, parent, xtk_ref_none(), patches, count);
}

bool xtk_tooltip_setw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_control_set_f32(scene, control, XTK_PROP_WIDTH, value, change);
}

bool xtk_tooltip_seth(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_control_set_f32(scene, control, XTK_PROP_HEIGHT, value, change);
}

bool xtk_tooltip_setgrow(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_control_set_f32(scene, control, XTK_PROP_GROW, value, change);
}

bool xtk_tooltip_setself(XtkScene *scene, XtkCtrl control, uint32_t value, XtkChangeStamp change) {
	return xtk_control_set_enum(scene, control, XTK_PROP_ALIGN_SELF, value, change);
}

bool xtk_tooltip_setml(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_control_set_f32(scene, control, XTK_PROP_MARGIN_LEFT, value, change);
}

bool xtk_tooltip_setmt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_control_set_f32(scene, control, XTK_PROP_MARGIN_TOP, value, change);
}

bool xtk_tooltip_setmr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_control_set_f32(scene, control, XTK_PROP_MARGIN_RIGHT, value, change);
}

bool xtk_tooltip_setmb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_control_set_f32(scene, control, XTK_PROP_MARGIN_BOTTOM, value, change);
}

bool xtk_tooltip_settext(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change) {
	return xtk_control_set_string(scene, control, XTK_PROP_TEXT, data, xtk_controls_text_len(data, len), change);
}

bool xtk_tooltip_settip(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change) {
	return xtk_control_set_string(scene, control, XTK_PROP_TOOLTIP, data, xtk_controls_text_len(data, len), change);
}

bool xtk_tooltip_setopen(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change) {
	return xtk_control_set_bool(scene, control, XTK_PROP_OPEN, value, change);
}

bool xtk_tooltip_setenabled(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change) {
	return xtk_control_set_bool(scene, control, XTK_PROP_ENABLED, value, change);
}
