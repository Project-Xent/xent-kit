#include "xtk_controls_internal.h"

XtkLocalId xtk_image_create(XtkTxn *txn, XtkNodeRef parent, XtkImageProps const *props) {
	if (!props) return xtk_txn_create(txn, XTK_CTRL_IMAGE, parent, xtk_ref_none(), NULL, 0u);
	XtkPropPatch   patches [15];
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
	xtk_controls_append_resource(patches, &count, (props->set >> 9u) & 1u, XTK_PROP_IMAGE_SOURCE, props->src, change);
	xtk_controls_append_enum(patches, &count, (props->set >> 10u) & 1u, XTK_PROP_IMAGE_STRETCH, props->fit, change);
	xtk_controls_append_f32(patches, &count, (props->set >> 11u) & 1u, XTK_PROP_NINE_GRID_LEFT, props->nl, change);
	xtk_controls_append_f32(patches, &count, (props->set >> 12u) & 1u, XTK_PROP_NINE_GRID_TOP, props->nt, change);
	xtk_controls_append_f32(patches, &count, (props->set >> 13u) & 1u, XTK_PROP_NINE_GRID_RIGHT, props->nr, change);
	xtk_controls_append_f32(patches, &count, (props->set >> 14u) & 1u, XTK_PROP_NINE_GRID_BOTTOM, props->nb, change);
	return xtk_txn_create(txn, XTK_CTRL_IMAGE, parent, xtk_ref_none(), patches, count);
}

bool xtk_image_setw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_ctrl_setf32(scene, control, XTK_PROP_WIDTH, value, change);
}

bool xtk_image_seth(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_ctrl_setf32(scene, control, XTK_PROP_HEIGHT, value, change);
}

bool xtk_image_setgrow(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_ctrl_setf32(scene, control, XTK_PROP_GROW, value, change);
}

bool xtk_image_setself(XtkScene *scene, XtkCtrl control, XentFlexAlign value, XtkChangeStamp change) {
	return xtk_ctrl_setenum(scene, control, XTK_PROP_ALIGN_SELF, value, change);
}

bool xtk_image_setml(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_ctrl_setf32(scene, control, XTK_PROP_MARGIN_LEFT, value, change);
}

bool xtk_image_setmt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_ctrl_setf32(scene, control, XTK_PROP_MARGIN_TOP, value, change);
}

bool xtk_image_setmr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_ctrl_setf32(scene, control, XTK_PROP_MARGIN_RIGHT, value, change);
}

bool xtk_image_setmb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_ctrl_setf32(scene, control, XTK_PROP_MARGIN_BOTTOM, value, change);
}

bool xtk_image_settip(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change) {
	return xtk_ctrl_setstring(scene, control, XTK_PROP_TOOLTIP, data, xtk_controls_text_len(data, len), change);
}

bool xtk_image_setsrc(XtkScene *scene, XtkCtrl control, XtkResource value, XtkChangeStamp change) {
	return xtk_ctrl_setresource(scene, control, XTK_PROP_IMAGE_SOURCE, value, change);
}

bool xtk_image_setfit(XtkScene *scene, XtkCtrl control, XtkImageStretch value, XtkChangeStamp change) {
	return xtk_ctrl_setenum(scene, control, XTK_PROP_IMAGE_STRETCH, value, change);
}

bool xtk_image_setnl(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_ctrl_setf32(scene, control, XTK_PROP_NINE_GRID_LEFT, value, change);
}

bool xtk_image_setnt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_ctrl_setf32(scene, control, XTK_PROP_NINE_GRID_TOP, value, change);
}

bool xtk_image_setnr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_ctrl_setf32(scene, control, XTK_PROP_NINE_GRID_RIGHT, value, change);
}

bool xtk_image_setnb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_ctrl_setf32(scene, control, XTK_PROP_NINE_GRID_BOTTOM, value, change);
}

XtkSubRef xtk_image_onopened(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg) {
	return xtk_txn_on(txn, target, XTK_EVENT_IMAGE_OPENED, XTK_EVENT_PHASE_MASK_TARGET, fn, arg);
}

XtkSubRef xtk_image_onfailed(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg) {
	return xtk_txn_on(txn, target, XTK_EVENT_IMAGE_FAILED, XTK_EVENT_PHASE_MASK_TARGET, fn, arg);
}
