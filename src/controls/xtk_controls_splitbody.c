#include "xtk_controls_internal.h"

XtkLocalId xtk_splitbody_create(XtkTxn *txn, XtkNodeRef parent, XtkContainerProps const *props) {
	if (!props) return xtk_txn_create(txn, XTK_CTRL_SPLITBODY, parent, xtk_ref_none(), NULL, 0u);
	XtkPropPatch   patches [26];
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
	xtk_controls_append_enum(patches, &count, (props->set >> 11u) & 1u, XTK_PROP_ALIGN_ITEMS, props->items, change);
	xtk_controls_append_enum(
	  patches, &count, (props->set >> 12u) & 1u, XTK_PROP_JUSTIFY_CONTENT, props->justify, change
	);
	xtk_controls_append_f32(patches, &count, (props->set >> 13u) & 1u, XTK_PROP_GAP, props->gap, change);
	xtk_controls_append_f32(patches, &count, (props->set >> 14u) & 1u, XTK_PROP_PADDING_LEFT, props->pl, change);
	xtk_controls_append_f32(patches, &count, (props->set >> 15u) & 1u, XTK_PROP_PADDING_TOP, props->pt, change);
	xtk_controls_append_f32(patches, &count, (props->set >> 16u) & 1u, XTK_PROP_PADDING_RIGHT, props->pr, change);
	xtk_controls_append_f32(patches, &count, (props->set >> 17u) & 1u, XTK_PROP_PADDING_BOTTOM, props->pb, change);
	xtk_controls_append_bool(patches, &count, (props->set >> 18u) & 1u, XTK_PROP_FILL, props->fill, change);
	xtk_controls_append_bool(patches, &count, (props->set >> 19u) & 1u, XTK_PROP_FIT_WIDTH, props->fitw, change);
	xtk_controls_append_bool(patches, &count, (props->set >> 20u) & 1u, XTK_PROP_FIT_HEIGHT, props->fith, change);
	xtk_controls_append_enum(patches, &count, (props->set >> 21u) & 1u, XTK_PROP_WRAP, props->wrap, change);
	xtk_controls_append_enum(patches, &count, (props->set >> 22u) & 1u, XTK_PROP_DROP_OPERATION, props->drop, change);
	xtk_controls_append_string(
	  patches, &count, (props->set >> 23u) & 1u, XTK_PROP_DRAG_TEXT, props->dragtext, props->dragtext_len, change
	);
	xtk_controls_append_string(
	  patches, &count, (props->set >> 24u) & 1u, XTK_PROP_DRAG_FILES, props->dragfiles, props->dragfiles_len, change
	);
	xtk_controls_append_enum(patches, &count, (props->set >> 25u) & 1u, XTK_PROP_FLOW_DIRECTION, props->flow, change);
	return xtk_txn_create(txn, XTK_CTRL_SPLITBODY, parent, xtk_ref_none(), patches, count);
}

bool xtk_splitbody_setw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_ctrl_setf32(scene, control, XTK_PROP_WIDTH, value, change);
}

bool xtk_splitbody_seth(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_ctrl_setf32(scene, control, XTK_PROP_HEIGHT, value, change);
}

bool xtk_splitbody_setgrow(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_ctrl_setf32(scene, control, XTK_PROP_GROW, value, change);
}

bool xtk_splitbody_setshrink(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_ctrl_setf32(scene, control, XTK_PROP_SHRINK, value, change);
}

bool xtk_splitbody_setself(XtkScene *scene, XtkCtrl control, XentFlexAlign value, XtkChangeStamp change) {
	return xtk_ctrl_setenum(scene, control, XTK_PROP_ALIGN_SELF, value, change);
}

bool xtk_splitbody_setml(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_ctrl_setf32(scene, control, XTK_PROP_MARGIN_LEFT, value, change);
}

bool xtk_splitbody_setmt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_ctrl_setf32(scene, control, XTK_PROP_MARGIN_TOP, value, change);
}

bool xtk_splitbody_setmr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_ctrl_setf32(scene, control, XTK_PROP_MARGIN_RIGHT, value, change);
}

bool xtk_splitbody_setmb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_ctrl_setf32(scene, control, XTK_PROP_MARGIN_BOTTOM, value, change);
}

bool xtk_splitbody_settip(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change) {
	return xtk_ctrl_setstring(scene, control, XTK_PROP_TOOLTIP, data, xtk_controls_text_len(data, len), change);
}

bool xtk_splitbody_setdir(XtkScene *scene, XtkCtrl control, XtkStackDirection value, XtkChangeStamp change) {
	return xtk_ctrl_setenum(scene, control, XTK_PROP_ORIENTATION, value, change);
}

bool xtk_splitbody_setitems(XtkScene *scene, XtkCtrl control, XentFlexAlign value, XtkChangeStamp change) {
	return xtk_ctrl_setenum(scene, control, XTK_PROP_ALIGN_ITEMS, value, change);
}

bool xtk_splitbody_setjustify(XtkScene *scene, XtkCtrl control, XentFlexJustify value, XtkChangeStamp change) {
	return xtk_ctrl_setenum(scene, control, XTK_PROP_JUSTIFY_CONTENT, value, change);
}

bool xtk_splitbody_setgap(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_ctrl_setf32(scene, control, XTK_PROP_GAP, value, change);
}

bool xtk_splitbody_setpl(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_ctrl_setf32(scene, control, XTK_PROP_PADDING_LEFT, value, change);
}

bool xtk_splitbody_setpt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_ctrl_setf32(scene, control, XTK_PROP_PADDING_TOP, value, change);
}

bool xtk_splitbody_setpr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_ctrl_setf32(scene, control, XTK_PROP_PADDING_RIGHT, value, change);
}

bool xtk_splitbody_setpb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_ctrl_setf32(scene, control, XTK_PROP_PADDING_BOTTOM, value, change);
}

bool xtk_splitbody_setfill(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change) {
	return xtk_ctrl_setbool(scene, control, XTK_PROP_FILL, value, change);
}

bool xtk_splitbody_setfitw(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change) {
	return xtk_ctrl_setbool(scene, control, XTK_PROP_FIT_WIDTH, value, change);
}

bool xtk_splitbody_setfith(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change) {
	return xtk_ctrl_setbool(scene, control, XTK_PROP_FIT_HEIGHT, value, change);
}

bool xtk_splitbody_setwrap(XtkScene *scene, XtkCtrl control, XentFlexWrap value, XtkChangeStamp change) {
	return xtk_ctrl_setenum(scene, control, XTK_PROP_WRAP, value, change);
}

bool xtk_splitbody_setdrop(XtkScene *scene, XtkCtrl control, XtkDropOperation value, XtkChangeStamp change) {
	return xtk_ctrl_setenum(scene, control, XTK_PROP_DROP_OPERATION, value, change);
}

bool xtk_splitbody_setdragtext(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
) {
	return xtk_ctrl_setstring(scene, control, XTK_PROP_DRAG_TEXT, data, xtk_controls_text_len(data, len), change);
}

bool xtk_splitbody_setdragfiles(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
) {
	return xtk_ctrl_setstring(scene, control, XTK_PROP_DRAG_FILES, data, xtk_controls_text_len(data, len), change);
}

bool xtk_splitbody_setflow(XtkScene *scene, XtkCtrl control, XentDirection value, XtkChangeStamp change) {
	return xtk_ctrl_setenum(scene, control, XTK_PROP_FLOW_DIRECTION, value, change);
}

XtkSubRef xtk_splitbody_ondraghover(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg) {
	return xtk_txn_on(txn, target, XTK_EVENT_DRAG_HOVER, XTK_EVENT_PHASE_MASK_TARGET, fn, arg);
}

XtkSubRef xtk_splitbody_ondropfiles(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg) {
	return xtk_txn_on(txn, target, XTK_EVENT_DROP_FILES, XTK_EVENT_PHASE_MASK_TARGET, fn, arg);
}

XtkSubRef xtk_splitbody_ondroptext(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg) {
	return xtk_txn_on(txn, target, XTK_EVENT_DROP_TEXT, XTK_EVENT_PHASE_MASK_TARGET, fn, arg);
}

XtkSubRef xtk_splitbody_ondragcompleted(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg) {
	return xtk_txn_on(txn, target, XTK_EVENT_DRAG_COMPLETED, XTK_EVENT_PHASE_MASK_TARGET, fn, arg);
}
