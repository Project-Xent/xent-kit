#include "xtk_controls_internal.h"

XtkLocalId xtk_pager_create(XtkTxn *txn, XtkNodeRef parent, XtkPagerProps const *props) {
	if (!props) return xtk_txn_create(txn, XTK_CTRL_PAGER, parent, xtk_ref_none(), NULL, 0u);
	XtkPropPatch   patches [19];
	uint32_t       count  = 0u;
	XtkChangeStamp change = props->stamp;
	xtk_controls_append_f32(patches, &count, (props->set >> 0u) & 1u, XTK_PROP_WIDTH, props->w, change);
	xtk_controls_append_f32(patches, &count, (props->set >> 1u) & 1u, XTK_PROP_HEIGHT, props->h, change);
	xtk_controls_append_f32(patches, &count, (props->set >> 2u) & 1u, XTK_PROP_GROW, props->grow, change);
	xtk_controls_append_f32(patches, &count, (props->set >> 3u) & 1u, XTK_PROP_SHRINK, props->shrink, change);
	xtk_controls_append_enum(patches, &count, (props->set >> 4u) & 1u, XTK_PROP_ALIGN_SELF, props->self, change);
	xtk_controls_append_f32(patches, &count, (props->set >> 5u) & 1u, XTK_PROP_MARGIN_LEFT, props->ml, change);
	xtk_controls_append_f32(patches, &count, (props->set >> 6u) & 1u, XTK_PROP_MARGIN_TOP, props->mt, change);
	xtk_controls_append_f32(patches, &count, (props->set >> 7u) & 1u, XTK_PROP_MARGIN_RIGHT, props->mr, change);
	xtk_controls_append_f32(patches, &count, (props->set >> 8u) & 1u, XTK_PROP_MARGIN_BOTTOM, props->mb, change);
	xtk_controls_append_string(
	  patches, &count, (props->set >> 9u) & 1u, XTK_PROP_TOOLTIP, props->tip, props->tip_len, change
	);
	xtk_controls_append_i32(patches, &count, (props->set >> 10u) & 1u, XTK_PROP_SELECTED_INDEX, props->sel, change);
	xtk_controls_append_i32(patches, &count, (props->set >> 11u) & 1u, XTK_PROP_ITEM_COUNT, props->nitem, change);
	xtk_controls_append_enum(patches, &count, (props->set >> 12u) & 1u, XTK_PROP_DISPLAY_MODE, props->display, change);
	xtk_controls_append_enum(patches, &count, (props->set >> 13u) & 1u, XTK_PROP_FIRST_BUTTON, props->first, change);
	xtk_controls_append_enum(patches, &count, (props->set >> 14u) & 1u, XTK_PROP_PREVIOUS_BUTTON, props->prev, change);
	xtk_controls_append_enum(patches, &count, (props->set >> 15u) & 1u, XTK_PROP_NEXT_BUTTON, props->next, change);
	xtk_controls_append_enum(patches, &count, (props->set >> 16u) & 1u, XTK_PROP_LAST_BUTTON, props->last, change);
	xtk_controls_append_string(
	  patches, &count, (props->set >> 17u) & 1u, XTK_PROP_PREFIX, props->prefix, props->prefix_len, change
	);
	xtk_controls_append_string(
	  patches, &count, (props->set >> 18u) & 1u, XTK_PROP_SUFFIX, props->suffix, props->suffix_len, change
	);
	return xtk_txn_create(txn, XTK_CTRL_PAGER, parent, xtk_ref_none(), patches, count);
}

bool xtk_pager_setw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_control_set_f32(scene, control, XTK_PROP_WIDTH, value, change);
}

bool xtk_pager_seth(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_control_set_f32(scene, control, XTK_PROP_HEIGHT, value, change);
}

bool xtk_pager_setgrow(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_control_set_f32(scene, control, XTK_PROP_GROW, value, change);
}

bool xtk_pager_setshrink(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_control_set_f32(scene, control, XTK_PROP_SHRINK, value, change);
}

bool xtk_pager_setself(XtkScene *scene, XtkCtrl control, uint32_t value, XtkChangeStamp change) {
	return xtk_control_set_enum(scene, control, XTK_PROP_ALIGN_SELF, value, change);
}

bool xtk_pager_setml(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_control_set_f32(scene, control, XTK_PROP_MARGIN_LEFT, value, change);
}

bool xtk_pager_setmt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_control_set_f32(scene, control, XTK_PROP_MARGIN_TOP, value, change);
}

bool xtk_pager_setmr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_control_set_f32(scene, control, XTK_PROP_MARGIN_RIGHT, value, change);
}

bool xtk_pager_setmb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_control_set_f32(scene, control, XTK_PROP_MARGIN_BOTTOM, value, change);
}

bool xtk_pager_settip(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change) {
	return xtk_control_set_string(scene, control, XTK_PROP_TOOLTIP, data, xtk_controls_text_len(data, len), change);
}

bool xtk_pager_setsel(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change) {
	return xtk_control_set_i32(scene, control, XTK_PROP_SELECTED_INDEX, value, change);
}

bool xtk_pager_setnitem(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change) {
	return xtk_control_set_i32(scene, control, XTK_PROP_ITEM_COUNT, value, change);
}

bool xtk_pager_setdisplay(XtkScene *scene, XtkCtrl control, uint32_t value, XtkChangeStamp change) {
	return xtk_control_set_enum(scene, control, XTK_PROP_DISPLAY_MODE, value, change);
}

bool xtk_pager_setfirst(XtkScene *scene, XtkCtrl control, uint32_t value, XtkChangeStamp change) {
	return xtk_control_set_enum(scene, control, XTK_PROP_FIRST_BUTTON, value, change);
}

bool xtk_pager_setprev(XtkScene *scene, XtkCtrl control, uint32_t value, XtkChangeStamp change) {
	return xtk_control_set_enum(scene, control, XTK_PROP_PREVIOUS_BUTTON, value, change);
}

bool xtk_pager_setnext(XtkScene *scene, XtkCtrl control, uint32_t value, XtkChangeStamp change) {
	return xtk_control_set_enum(scene, control, XTK_PROP_NEXT_BUTTON, value, change);
}

bool xtk_pager_setlast(XtkScene *scene, XtkCtrl control, uint32_t value, XtkChangeStamp change) {
	return xtk_control_set_enum(scene, control, XTK_PROP_LAST_BUTTON, value, change);
}

bool xtk_pager_setprefix(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change) {
	return xtk_control_set_string(scene, control, XTK_PROP_PREFIX, data, xtk_controls_text_len(data, len), change);
}

bool xtk_pager_setsuffix(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change) {
	return xtk_control_set_string(scene, control, XTK_PROP_SUFFIX, data, xtk_controls_text_len(data, len), change);
}

XtkSubRef xtk_pager_onselect(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg) {
	return xtk_txn_on(txn, target, XTK_EVENT_SELECT, XTK_EVENT_PHASE_MASK_TARGET, fn, arg);
}

XtkSubRef xtk_pager_oninvoke(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg) {
	return xtk_txn_on(txn, target, XTK_EVENT_INVOKE, XTK_EVENT_PHASE_MASK_TARGET, fn, arg);
}
