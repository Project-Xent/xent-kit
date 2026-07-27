#include "xtk_controls_internal.h"

XtkLocalId xtk_breadcrumb_create(XtkTxn *txn, XtkNodeRef parent, XtkSelectionProps const *props) {
	if (!props) return xtk_txn_create(txn, XTK_CTRL_BREADCRUMB, parent, xtk_ref_none(), NULL, 0u);
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
	  patches, &count, (props->set >> 8u) & 1u, XTK_PROP_TOOLTIP, props->tip, props->tip_len, change
	);
	xtk_controls_append_bool(patches, &count, (props->set >> 9u) & 1u, XTK_PROP_ENABLED, props->enabled, change);
	xtk_controls_append_i32(patches, &count, (props->set >> 10u) & 1u, XTK_PROP_SELECTED_INDEX, props->sel, change);
	xtk_controls_append_i32(patches, &count, (props->set >> 11u) & 1u, XTK_PROP_ITEM_COUNT, props->nitem, change);
	return xtk_txn_create(txn, XTK_CTRL_BREADCRUMB, parent, xtk_ref_none(), patches, count);
}

bool xtk_breadcrumb_setw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_control_set_f32(scene, control, XTK_PROP_WIDTH, value, change);
}

bool xtk_breadcrumb_seth(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_control_set_f32(scene, control, XTK_PROP_HEIGHT, value, change);
}

bool xtk_breadcrumb_setgrow(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_control_set_f32(scene, control, XTK_PROP_GROW, value, change);
}

bool xtk_breadcrumb_setself(XtkScene *scene, XtkCtrl control, uint32_t value, XtkChangeStamp change) {
	return xtk_control_set_enum(scene, control, XTK_PROP_ALIGN_SELF, value, change);
}

bool xtk_breadcrumb_setml(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_control_set_f32(scene, control, XTK_PROP_MARGIN_LEFT, value, change);
}

bool xtk_breadcrumb_setmt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_control_set_f32(scene, control, XTK_PROP_MARGIN_TOP, value, change);
}

bool xtk_breadcrumb_setmr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_control_set_f32(scene, control, XTK_PROP_MARGIN_RIGHT, value, change);
}

bool xtk_breadcrumb_setmb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_control_set_f32(scene, control, XTK_PROP_MARGIN_BOTTOM, value, change);
}

bool xtk_breadcrumb_settip(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change) {
	return xtk_control_set_string(scene, control, XTK_PROP_TOOLTIP, data, xtk_controls_text_len(data, len), change);
}

bool xtk_breadcrumb_setenabled(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change) {
	return xtk_control_set_bool(scene, control, XTK_PROP_ENABLED, value, change);
}

bool xtk_breadcrumb_setsel(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change) {
	return xtk_control_set_i32(scene, control, XTK_PROP_SELECTED_INDEX, value, change);
}

bool xtk_breadcrumb_setnitem(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change) {
	return xtk_control_set_i32(scene, control, XTK_PROP_ITEM_COUNT, value, change);
}

XtkSubRef xtk_breadcrumb_onselect(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg) {
	return xtk_txn_on(txn, target, XTK_EVENT_SELECT, XTK_EVENT_PHASE_MASK_TARGET, fn, arg);
}

XtkSubRef xtk_breadcrumb_oninvoke(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg) {
	return xtk_txn_on(txn, target, XTK_EVENT_INVOKE, XTK_EVENT_PHASE_MASK_TARGET, fn, arg);
}
