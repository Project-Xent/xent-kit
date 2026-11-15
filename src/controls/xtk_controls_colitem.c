#include "xtk_controls_internal.h"

XtkLocalId xtk_colitem_create(XtkTxn *txn, XtkNodeRef parent, XtkColumnProps const *props) {
	if (!props) return xtk_txn_create(txn, XTK_CTRL_COLITEM, parent, xtk_ref_none(), NULL, 0u);
	XtkPropPatch   patches [9];
	uint32_t       count  = 0u;
	XtkChangeStamp change = props->stamp;
	xtk_controls_append_f32(patches, &count, (props->set >> 0u) & 1u, XTK_PROP_WIDTH, props->w, change);
	xtk_controls_append_f32(patches, &count, (props->set >> 1u) & 1u, XTK_PROP_MIN_WIDTH, props->minw, change);
	xtk_controls_append_f32(patches, &count, (props->set >> 2u) & 1u, XTK_PROP_MAX_WIDTH, props->maxw, change);
	xtk_controls_append_string(
	  patches, &count, (props->set >> 3u) & 1u, XTK_PROP_TEXT, props->text, props->text_len, change
	);
	xtk_controls_append_string(
	  patches, &count, (props->set >> 4u) & 1u, XTK_PROP_TOOLTIP, props->tip, props->tip_len, change
	);
	xtk_controls_append_enum(patches, &count, (props->set >> 5u) & 1u, XTK_PROP_TEXT_ALIGN, props->align, change);
	xtk_controls_append_bool(patches, &count, (props->set >> 6u) & 1u, XTK_PROP_ENABLED, props->enabled, change);
	xtk_controls_append_bool(patches, &count, (props->set >> 7u) & 1u, XTK_PROP_RESIZABLE, props->resizable, change);
	xtk_controls_append_enum(patches, &count, (props->set >> 8u) & 1u, XTK_PROP_SORT_DIRECTION, props->sort, change);
	return xtk_txn_create(txn, XTK_CTRL_COLITEM, parent, xtk_ref_none(), patches, count);
}

bool xtk_colitem_setw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_ctrl_setf32(scene, control, XTK_PROP_WIDTH, value, change);
}

bool xtk_colitem_setminw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_ctrl_setf32(scene, control, XTK_PROP_MIN_WIDTH, value, change);
}

bool xtk_colitem_setmaxw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_ctrl_setf32(scene, control, XTK_PROP_MAX_WIDTH, value, change);
}

bool xtk_colitem_settext(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change) {
	return xtk_ctrl_setstring(scene, control, XTK_PROP_TEXT, data, xtk_controls_text_len(data, len), change);
}

bool xtk_colitem_settip(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change) {
	return xtk_ctrl_setstring(scene, control, XTK_PROP_TOOLTIP, data, xtk_controls_text_len(data, len), change);
}

bool xtk_colitem_setalign(XtkScene *scene, XtkCtrl control, XtkTextAlign value, XtkChangeStamp change) {
	return xtk_ctrl_setenum(scene, control, XTK_PROP_TEXT_ALIGN, value, change);
}

bool xtk_colitem_setenabled(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change) {
	return xtk_ctrl_setbool(scene, control, XTK_PROP_ENABLED, value, change);
}

bool xtk_colitem_setresizable(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change) {
	return xtk_ctrl_setbool(scene, control, XTK_PROP_RESIZABLE, value, change);
}

bool xtk_colitem_setsort(XtkScene *scene, XtkCtrl control, XtkSortDirection value, XtkChangeStamp change) {
	return xtk_ctrl_setenum(scene, control, XTK_PROP_SORT_DIRECTION, value, change);
}

XtkSubRef xtk_colitem_oninvoke(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg) {
	return xtk_txn_on(txn, target, XTK_EVENT_INVOKE, XTK_EVENT_PHASE_MASK_TARGET, fn, arg);
}

XtkSubRef xtk_colitem_onresize(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg) {
	return xtk_txn_on(txn, target, XTK_EVENT_RESIZE, XTK_EVENT_PHASE_MASK_TARGET, fn, arg);
}

XtkSubRef xtk_colitem_onfit(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg) {
	return xtk_txn_on(txn, target, XTK_EVENT_FIT, XTK_EVENT_PHASE_MASK_TARGET, fn, arg);
}

XtkSubRef xtk_colitem_onreorder(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg) {
	return xtk_txn_on(txn, target, XTK_EVENT_REORDER, XTK_EVENT_PHASE_MASK_TARGET, fn, arg);
}
