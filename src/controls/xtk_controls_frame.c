#include "xtk_controls_internal.h"

XtkLocalId xtk_frame_create(XtkTxn *txn, XtkNodeRef parent, XtkFrameProps const *props) {
	return xtk_controls_create(txn, XTK_CTRL_FRAME, parent, props, &xtk_pack_frame);
}

bool xtk_frame_setw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_ctrl_setf32(scene, control, XTK_PROP_WIDTH, value, change);
}

bool xtk_frame_seth(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_ctrl_setf32(scene, control, XTK_PROP_HEIGHT, value, change);
}

bool xtk_frame_setgrow(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_ctrl_setf32(scene, control, XTK_PROP_GROW, value, change);
}

bool xtk_frame_setshrink(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_ctrl_setf32(scene, control, XTK_PROP_SHRINK, value, change);
}

bool xtk_frame_setself(XtkScene *scene, XtkCtrl control, XentFlexAlign value, XtkChangeStamp change) {
	return xtk_ctrl_setenum(scene, control, XTK_PROP_ALIGN_SELF, value, change);
}

bool xtk_frame_settransition(XtkScene *scene, XtkCtrl control, XtkNavTransitionKind value, XtkChangeStamp change) {
	return xtk_ctrl_setenum(scene, control, XTK_PROP_FRAME_TRANSITION, value, change);
}

bool xtk_frame_setis_back(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change) {
	return xtk_ctrl_setbool(scene, control, XTK_PROP_FRAME_BACK, value, change);
}

bool xtk_frame_setpage_key(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change) {
	return xtk_ctrl_seti32(scene, control, XTK_PROP_FRAME_PAGE_KEY, value, change);
}
