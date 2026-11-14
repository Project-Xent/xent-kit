#include "xtk_controls_internal.h"

XtkLocalId xtk_teachtip_create(XtkTxn *txn, XtkNodeRef parent, XtkTeachingTipProps const *props) {
	if (!props) return xtk_txn_create(txn, XTK_CTRL_TEACHTIP, parent, xtk_ref_none(), NULL, 0u);
	XtkPropPatch   patches [22];
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
	xtk_controls_append_string(
	  patches, &count, (props->set >> 10u) & 1u, XTK_PROP_TEXT, props->text, props->text_len, change
	);
	xtk_controls_append_string(
	  patches, &count, (props->set >> 11u) & 1u, XTK_PROP_SUBTITLE, props->subtitle, props->subtitle_len, change
	);
	xtk_controls_append_string(
	  patches, &count, (props->set >> 12u) & 1u, XTK_PROP_ICON, props->icon, props->icon_len, change
	);
	xtk_controls_append_string(
	  patches, &count, (props->set >> 13u) & 1u, XTK_PROP_ACTION_TEXT, props->action, props->action_len, change
	);
	xtk_controls_append_bool(
	  patches, &count, (props->set >> 14u) & 1u, XTK_PROP_ACTION_ACCENT, props->actionaccent, change
	);
	xtk_controls_append_string(
	  patches, &count, (props->set >> 15u) & 1u, XTK_PROP_CLOSE_TEXT, props->close, props->close_len, change
	);
	xtk_controls_append_enum(patches, &count, (props->set >> 16u) & 1u, XTK_PROP_PLACEMENT, props->placement, change);
	xtk_controls_append_bool(patches, &count, (props->set >> 17u) & 1u, XTK_PROP_UNTARGETED, props->untargeted, change);
	xtk_controls_append_bool(
	  patches, &count, (props->set >> 18u) & 1u, XTK_PROP_LIGHT_DISMISS, props->lightdismiss, change
	);
	xtk_controls_append_enum(patches, &count, (props->set >> 19u) & 1u, XTK_PROP_TAIL_VISIBILITY, props->tail, change);
	xtk_controls_append_f32(
	  patches, &count, (props->set >> 20u) & 1u, XTK_PROP_PLACEMENT_MARGIN, props->placementmargin, change
	);
	xtk_controls_append_bool(patches, &count, (props->set >> 21u) & 1u, XTK_PROP_OPEN, props->open, change);
	return xtk_txn_create(txn, XTK_CTRL_TEACHTIP, parent, xtk_ref_none(), patches, count);
}

bool xtk_teachtip_setw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_ctrl_setf32(scene, control, XTK_PROP_WIDTH, value, change);
}

bool xtk_teachtip_seth(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_ctrl_setf32(scene, control, XTK_PROP_HEIGHT, value, change);
}

bool xtk_teachtip_setgrow(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_ctrl_setf32(scene, control, XTK_PROP_GROW, value, change);
}

bool xtk_teachtip_setshrink(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_ctrl_setf32(scene, control, XTK_PROP_SHRINK, value, change);
}

bool xtk_teachtip_setself(XtkScene *scene, XtkCtrl control, XentFlexAlign value, XtkChangeStamp change) {
	return xtk_ctrl_setenum(scene, control, XTK_PROP_ALIGN_SELF, value, change);
}

bool xtk_teachtip_setml(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_ctrl_setf32(scene, control, XTK_PROP_MARGIN_LEFT, value, change);
}

bool xtk_teachtip_setmt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_ctrl_setf32(scene, control, XTK_PROP_MARGIN_TOP, value, change);
}

bool xtk_teachtip_setmr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_ctrl_setf32(scene, control, XTK_PROP_MARGIN_RIGHT, value, change);
}

bool xtk_teachtip_setmb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_ctrl_setf32(scene, control, XTK_PROP_MARGIN_BOTTOM, value, change);
}

bool xtk_teachtip_settip(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change) {
	return xtk_ctrl_setstring(scene, control, XTK_PROP_TOOLTIP, data, xtk_controls_text_len(data, len), change);
}

bool xtk_teachtip_settext(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change) {
	return xtk_ctrl_setstring(scene, control, XTK_PROP_TEXT, data, xtk_controls_text_len(data, len), change);
}

bool xtk_teachtip_setsubtitle(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change) {
	return xtk_ctrl_setstring(scene, control, XTK_PROP_SUBTITLE, data, xtk_controls_text_len(data, len), change);
}

bool xtk_teachtip_seticon(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change) {
	return xtk_ctrl_setstring(scene, control, XTK_PROP_ICON, data, xtk_controls_text_len(data, len), change);
}

bool xtk_teachtip_setaction(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change) {
	return xtk_ctrl_setstring(scene, control, XTK_PROP_ACTION_TEXT, data, xtk_controls_text_len(data, len), change);
}

bool xtk_teachtip_setactionaccent(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change) {
	return xtk_ctrl_setbool(scene, control, XTK_PROP_ACTION_ACCENT, value, change);
}

bool xtk_teachtip_setclose(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change) {
	return xtk_ctrl_setstring(scene, control, XTK_PROP_CLOSE_TEXT, data, xtk_controls_text_len(data, len), change);
}

bool xtk_teachtip_setplacement(XtkScene *scene, XtkCtrl control, XtkTeachingTipPlacement value, XtkChangeStamp change) {
	return xtk_ctrl_setenum(scene, control, XTK_PROP_PLACEMENT, value, change);
}

bool xtk_teachtip_setuntargeted(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change) {
	return xtk_ctrl_setbool(scene, control, XTK_PROP_UNTARGETED, value, change);
}

bool xtk_teachtip_setlightdismiss(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change) {
	return xtk_ctrl_setbool(scene, control, XTK_PROP_LIGHT_DISMISS, value, change);
}

bool xtk_teachtip_settail(XtkScene *scene, XtkCtrl control, XtkTeachingTipTail value, XtkChangeStamp change) {
	return xtk_ctrl_setenum(scene, control, XTK_PROP_TAIL_VISIBILITY, value, change);
}

bool xtk_teachtip_setplacementmargin(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_ctrl_setf32(scene, control, XTK_PROP_PLACEMENT_MARGIN, value, change);
}

bool xtk_teachtip_setopen(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change) {
	return xtk_ctrl_setbool(scene, control, XTK_PROP_OPEN, value, change);
}

XtkSubRef xtk_teachtip_onclose(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg) {
	return xtk_txn_on(txn, target, XTK_EVENT_CLOSE, XTK_EVENT_PHASE_MASK_TARGET, fn, arg);
}

XtkSubRef xtk_teachtip_oninvoke(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg) {
	return xtk_txn_on(txn, target, XTK_EVENT_INVOKE, XTK_EVENT_PHASE_MASK_TARGET, fn, arg);
}
