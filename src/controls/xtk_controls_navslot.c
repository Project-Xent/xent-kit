#include "xtk_controls_internal.h"

XtkLocalId xtk_navslot_create(XtkTxn *txn, XtkNodeRef parent, XtkNavSlotProps const *props) {
	return xtk_controls_create(txn, XTK_CTRL_NAVSLOT, parent, props, &xtk_pack_navslot);
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
