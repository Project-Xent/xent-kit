#include "xtk_controls_internal.h"

XtkLocalId xtk_navslot_create(XtkTxn *txn, XtkNodeRef parent, XtkNavSlotProps const *props) {
	if (!props) return xtk_txn_create(txn, XTK_CTRL_NAVSLOT, parent, xtk_ref_none(), NULL, 0u);
	XtkPropPatch   patches [6];
	uint32_t       count  = 0u;
	XtkChangeStamp change = props->stamp;
	xtk_controls_append_f32(patches, &count, (props->set >> 0u) & 1u, XTK_PROP_WIDTH, props->w, change);
	xtk_controls_append_f32(patches, &count, (props->set >> 1u) & 1u, XTK_PROP_HEIGHT, props->h, change);
	xtk_controls_append_f32(patches, &count, (props->set >> 2u) & 1u, XTK_PROP_GROW, props->grow, change);
	xtk_controls_append_f32(patches, &count, (props->set >> 3u) & 1u, XTK_PROP_SHRINK, props->shrink, change);
	xtk_controls_append_enum(patches, &count, (props->set >> 4u) & 1u, XTK_PROP_ALIGN_SELF, props->self, change);
	xtk_controls_append_enum(patches, &count, (props->set >> 5u) & 1u, XTK_PROP_NAV_SLOT, props->slot, change);
	return xtk_txn_create(txn, XTK_CTRL_NAVSLOT, parent, xtk_ref_none(), patches, count);
}

bool xtk_navslot_setw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_ctrl_setf32(scene, control, XTK_PROP_WIDTH, value, change);
}

bool xtk_navslot_seth(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_ctrl_setf32(scene, control, XTK_PROP_HEIGHT, value, change);
}

bool xtk_navslot_setgrow(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_ctrl_setf32(scene, control, XTK_PROP_GROW, value, change);
}

bool xtk_navslot_setshrink(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_ctrl_setf32(scene, control, XTK_PROP_SHRINK, value, change);
}

bool xtk_navslot_setself(XtkScene *scene, XtkCtrl control, XentFlexAlign value, XtkChangeStamp change) {
	return xtk_ctrl_setenum(scene, control, XTK_PROP_ALIGN_SELF, value, change);
}

bool xtk_navslot_setslot(XtkScene *scene, XtkCtrl control, XtkNavSlot value, XtkChangeStamp change) {
	return xtk_ctrl_setenum(scene, control, XTK_PROP_NAV_SLOT, value, change);
}
