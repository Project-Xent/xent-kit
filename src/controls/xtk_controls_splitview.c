#include "xtk_controls_internal.h"

XtkLocalId xtk_splitview_create(XtkTxn *txn, XtkNodeRef parent, XtkSplitViewProps const *props) {
	if (!props) return xtk_txn_create(txn, XTK_CTRL_SPLITVIEW, parent, xtk_ref_none(), NULL, 0u);
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
	xtk_controls_append_enum(patches, &count, (props->set >> 10u) & 1u, XTK_PROP_ORIENTATION, props->dir, change);
	xtk_controls_append_f32(patches, &count, (props->set >> 11u) & 1u, XTK_PROP_GAP, props->gap, change);
	xtk_controls_append_f32(patches, &count, (props->set >> 12u) & 1u, XTK_PROP_PADDING_LEFT, props->pl, change);
	xtk_controls_append_f32(patches, &count, (props->set >> 13u) & 1u, XTK_PROP_PADDING_TOP, props->pt, change);
	xtk_controls_append_f32(patches, &count, (props->set >> 14u) & 1u, XTK_PROP_PADDING_RIGHT, props->pr, change);
	xtk_controls_append_f32(patches, &count, (props->set >> 15u) & 1u, XTK_PROP_PADDING_BOTTOM, props->pb, change);
	xtk_controls_append_bool(patches, &count, (props->set >> 16u) & 1u, XTK_PROP_FILL, props->fill, change);
	xtk_controls_append_bool(patches, &count, (props->set >> 17u) & 1u, XTK_PROP_OPEN, props->open, change);
	xtk_controls_append_enum(patches, &count, (props->set >> 18u) & 1u, XTK_PROP_DISPLAY_MODE, props->display, change);
	xtk_controls_append_enum(
	  patches, &count, (props->set >> 19u) & 1u, XTK_PROP_PANE_PLACEMENT, props->placement, change
	);
	xtk_controls_append_f32(
	  patches, &count, (props->set >> 20u) & 1u, XTK_PROP_OPEN_PANE_LENGTH, props->openlen, change
	);
	xtk_controls_append_f32(
	  patches, &count, (props->set >> 21u) & 1u, XTK_PROP_COMPACT_PANE_LENGTH, props->compactlen, change
	);
	return xtk_txn_create(txn, XTK_CTRL_SPLITVIEW, parent, xtk_ref_none(), patches, count);
}

bool xtk_splitview_setw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_ctrl_setf32(scene, control, XTK_PROP_WIDTH, value, change);
}

bool xtk_splitview_seth(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_ctrl_setf32(scene, control, XTK_PROP_HEIGHT, value, change);
}

bool xtk_splitview_setgrow(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_ctrl_setf32(scene, control, XTK_PROP_GROW, value, change);
}

bool xtk_splitview_setshrink(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_ctrl_setf32(scene, control, XTK_PROP_SHRINK, value, change);
}

bool xtk_splitview_setself(XtkScene *scene, XtkCtrl control, XentFlexAlign value, XtkChangeStamp change) {
	return xtk_ctrl_setenum(scene, control, XTK_PROP_ALIGN_SELF, value, change);
}

bool xtk_splitview_setml(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_ctrl_setf32(scene, control, XTK_PROP_MARGIN_LEFT, value, change);
}

bool xtk_splitview_setmt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_ctrl_setf32(scene, control, XTK_PROP_MARGIN_TOP, value, change);
}

bool xtk_splitview_setmr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_ctrl_setf32(scene, control, XTK_PROP_MARGIN_RIGHT, value, change);
}

bool xtk_splitview_setmb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_ctrl_setf32(scene, control, XTK_PROP_MARGIN_BOTTOM, value, change);
}

bool xtk_splitview_settip(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change) {
	return xtk_ctrl_setstring(scene, control, XTK_PROP_TOOLTIP, data, xtk_controls_text_len(data, len), change);
}

bool xtk_splitview_setdir(XtkScene *scene, XtkCtrl control, XtkStackDirection value, XtkChangeStamp change) {
	return xtk_ctrl_setenum(scene, control, XTK_PROP_ORIENTATION, value, change);
}

bool xtk_splitview_setgap(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_ctrl_setf32(scene, control, XTK_PROP_GAP, value, change);
}

bool xtk_splitview_setpl(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_ctrl_setf32(scene, control, XTK_PROP_PADDING_LEFT, value, change);
}

bool xtk_splitview_setpt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_ctrl_setf32(scene, control, XTK_PROP_PADDING_TOP, value, change);
}

bool xtk_splitview_setpr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_ctrl_setf32(scene, control, XTK_PROP_PADDING_RIGHT, value, change);
}

bool xtk_splitview_setpb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_ctrl_setf32(scene, control, XTK_PROP_PADDING_BOTTOM, value, change);
}

bool xtk_splitview_setfill(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change) {
	return xtk_ctrl_setbool(scene, control, XTK_PROP_FILL, value, change);
}

bool xtk_splitview_setopen(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change) {
	return xtk_ctrl_setbool(scene, control, XTK_PROP_OPEN, value, change);
}

bool xtk_splitview_setdisplay(XtkScene *scene, XtkCtrl control, XtkSplitViewDisplayMode value, XtkChangeStamp change) {
	return xtk_ctrl_setenum(scene, control, XTK_PROP_DISPLAY_MODE, value, change);
}

bool xtk_splitview_setplacement(
  XtkScene *scene, XtkCtrl control, XtkSplitViewPanePlacement value, XtkChangeStamp change
) {
	return xtk_ctrl_setenum(scene, control, XTK_PROP_PANE_PLACEMENT, value, change);
}

bool xtk_splitview_setopenlen(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_ctrl_setf32(scene, control, XTK_PROP_OPEN_PANE_LENGTH, value, change);
}

bool xtk_splitview_setcompactlen(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_ctrl_setf32(scene, control, XTK_PROP_COMPACT_PANE_LENGTH, value, change);
}
