#include "xtk_controls_internal.h"

XtkLocalId xtk_progress_create(XtkTxn *txn, XtkNodeRef parent, XtkProgressProps const *props) {
	if (!props) return xtk_txn_create(txn, XTK_CTRL_PROGRESS, parent, xtk_ref_none(), NULL, 0u);
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
	xtk_controls_append_f32(patches, &count, (props->set >> 15u) & 1u, XTK_PROP_PADDING_LEFT, props->pl, change);
	xtk_controls_append_f32(patches, &count, (props->set >> 16u) & 1u, XTK_PROP_PADDING_TOP, props->pt, change);
	xtk_controls_append_f32(patches, &count, (props->set >> 17u) & 1u, XTK_PROP_PADDING_RIGHT, props->pr, change);
	xtk_controls_append_f32(patches, &count, (props->set >> 18u) & 1u, XTK_PROP_PADDING_BOTTOM, props->pb, change);
	xtk_controls_append_f32(
	  patches, &count, (props->set >> 19u) & 1u, XTK_PROP_PROGRESS_BORDER_WIDTH, props->border_width, change
	);
	return xtk_txn_create(txn, XTK_CTRL_PROGRESS, parent, xtk_ref_none(), patches, count);
}

bool xtk_progress_setw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_ctrl_setf32(scene, control, XTK_PROP_WIDTH, value, change);
}

bool xtk_progress_seth(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_ctrl_setf32(scene, control, XTK_PROP_HEIGHT, value, change);
}

bool xtk_progress_setgrow(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_ctrl_setf32(scene, control, XTK_PROP_GROW, value, change);
}

bool xtk_progress_setself(XtkScene *scene, XtkCtrl control, XentFlexAlign value, XtkChangeStamp change) {
	return xtk_ctrl_setenum(scene, control, XTK_PROP_ALIGN_SELF, value, change);
}

bool xtk_progress_setml(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_ctrl_setf32(scene, control, XTK_PROP_MARGIN_LEFT, value, change);
}

bool xtk_progress_setmt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_ctrl_setf32(scene, control, XTK_PROP_MARGIN_TOP, value, change);
}

bool xtk_progress_setmr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_ctrl_setf32(scene, control, XTK_PROP_MARGIN_RIGHT, value, change);
}

bool xtk_progress_setmb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_ctrl_setf32(scene, control, XTK_PROP_MARGIN_BOTTOM, value, change);
}

bool xtk_progress_settip(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change) {
	return xtk_ctrl_setstring(scene, control, XTK_PROP_TOOLTIP, data, xtk_controls_text_len(data, len), change);
}

bool xtk_progress_setmin(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_ctrl_setf32(scene, control, XTK_PROP_MIN_F32, value, change);
}

bool xtk_progress_setmax(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_ctrl_setf32(scene, control, XTK_PROP_MAX_F32, value, change);
}

bool xtk_progress_setvalue(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_ctrl_setf32(scene, control, XTK_PROP_VALUE_F32, value, change);
}

bool xtk_progress_setindeterminate(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change) {
	return xtk_ctrl_setbool(scene, control, XTK_PROP_INDETERMINATE, value, change);
}

bool xtk_progress_setstate(XtkScene *scene, XtkCtrl control, XtkProgressState value, XtkChangeStamp change) {
	return xtk_ctrl_setenum(scene, control, XTK_PROP_PROGRESS_STATE, value, change);
}

bool xtk_progress_setpl(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_ctrl_setf32(scene, control, XTK_PROP_PADDING_LEFT, value, change);
}

bool xtk_progress_setpt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_ctrl_setf32(scene, control, XTK_PROP_PADDING_TOP, value, change);
}

bool xtk_progress_setpr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_ctrl_setf32(scene, control, XTK_PROP_PADDING_RIGHT, value, change);
}

bool xtk_progress_setpb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_ctrl_setf32(scene, control, XTK_PROP_PADDING_BOTTOM, value, change);
}

bool xtk_progress_setborder_width(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_ctrl_setf32(scene, control, XTK_PROP_PROGRESS_BORDER_WIDTH, value, change);
}
