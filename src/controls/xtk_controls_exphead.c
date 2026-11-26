#include "xtk_controls_internal.h"

XtkLocalId xtk_exphead_create(XtkTxn *txn, XtkNodeRef parent, XtkItemProps const *props) {
	return xtk_controls_create(txn, XTK_CTRL_EXPHEAD, parent, props, &xtk_pack_item);
}

bool xtk_exphead_setw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_ctrl_setf32(scene, control, XTK_PROP_WIDTH, value, change);
}

bool xtk_exphead_seth(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_ctrl_setf32(scene, control, XTK_PROP_HEIGHT, value, change);
}

bool xtk_exphead_setgrow(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_ctrl_setf32(scene, control, XTK_PROP_GROW, value, change);
}

bool xtk_exphead_setself(XtkScene *scene, XtkCtrl control, XentFlexAlign value, XtkChangeStamp change) {
	return xtk_ctrl_setenum(scene, control, XTK_PROP_ALIGN_SELF, value, change);
}

bool xtk_exphead_setml(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_ctrl_setf32(scene, control, XTK_PROP_MARGIN_LEFT, value, change);
}

bool xtk_exphead_setmt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_ctrl_setf32(scene, control, XTK_PROP_MARGIN_TOP, value, change);
}

bool xtk_exphead_setmr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_ctrl_setf32(scene, control, XTK_PROP_MARGIN_RIGHT, value, change);
}

bool xtk_exphead_setmb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_ctrl_setf32(scene, control, XTK_PROP_MARGIN_BOTTOM, value, change);
}

bool xtk_exphead_settext(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change) {
	return xtk_ctrl_setstring(scene, control, XTK_PROP_TEXT, data, xtk_controls_text_len(data, len), change);
}

bool xtk_exphead_settip(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change) {
	return xtk_ctrl_setstring(scene, control, XTK_PROP_TOOLTIP, data, xtk_controls_text_len(data, len), change);
}

bool xtk_exphead_setaname(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change) {
	return xtk_ctrl_setstring(scene, control, XTK_PROP_A11Y_NAME, data, xtk_controls_text_len(data, len), change);
}

bool xtk_exphead_setaid(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change) {
	return xtk_ctrl_setstring(scene, control, XTK_PROP_A11Y_ID, data, xtk_controls_text_len(data, len), change);
}

bool xtk_exphead_setahelp(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change) {
	return xtk_ctrl_setstring(scene, control, XTK_PROP_A11Y_HELP, data, xtk_controls_text_len(data, len), change);
}

bool xtk_exphead_setadesc(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change) {
	return xtk_ctrl_setstring(
	  scene, control, XTK_PROP_A11Y_DESCRIPTION, data, xtk_controls_text_len(data, len), change
	);
}

bool xtk_exphead_setastatus(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change) {
	return xtk_ctrl_setstring(
	  scene, control, XTK_PROP_A11Y_ITEM_STATUS, data, xtk_controls_text_len(data, len), change
	);
}

bool xtk_exphead_setaitem(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change) {
	return xtk_ctrl_setstring(scene, control, XTK_PROP_A11Y_ITEM_TYPE, data, xtk_controls_text_len(data, len), change);
}

bool xtk_exphead_setactype(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change) {
	return xtk_ctrl_setstring(
	  scene, control, XTK_PROP_A11Y_CONTROL_TYPE, data, xtk_controls_text_len(data, len), change
	);
}

bool xtk_exphead_setaaccel(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change) {
	return xtk_ctrl_setstring(
	  scene, control, XTK_PROP_A11Y_ACCELERATOR, data, xtk_controls_text_len(data, len), change
	);
}

bool xtk_exphead_setakey(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change) {
	return xtk_ctrl_setstring(scene, control, XTK_PROP_A11Y_ACCESS_KEY, data, xtk_controls_text_len(data, len), change);
}

bool xtk_exphead_setalandmark(XtkScene *scene, XtkCtrl control, XtkLandmark value, XtkChangeStamp change) {
	return xtk_ctrl_setenum(scene, control, XTK_PROP_A11Y_LANDMARK, value, change);
}

bool xtk_exphead_setalandname(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change) {
	return xtk_ctrl_setstring(
	  scene, control, XTK_PROP_A11Y_LANDMARK_NAME, data, xtk_controls_text_len(data, len), change
	);
}

bool xtk_exphead_setalive(XtkScene *scene, XtkCtrl control, XtkLiveSetting value, XtkChangeStamp change) {
	return xtk_ctrl_setenum(scene, control, XTK_PROP_A11Y_LIVE, value, change);
}

bool xtk_exphead_setaheading(XtkScene *scene, XtkCtrl control, XtkHeadingLevel value, XtkChangeStamp change) {
	return xtk_ctrl_setenum(scene, control, XTK_PROP_A11Y_HEADING, value, change);
}

bool xtk_exphead_setaview(XtkScene *scene, XtkCtrl control, XtkAccessView value, XtkChangeStamp change) {
	return xtk_ctrl_setenum(scene, control, XTK_PROP_A11Y_VIEW, value, change);
}

bool xtk_exphead_setarequired(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change) {
	return xtk_ctrl_setbool(scene, control, XTK_PROP_A11Y_REQUIRED, value, change);
}

bool xtk_exphead_setavalid(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change) {
	return xtk_ctrl_setbool(scene, control, XTK_PROP_A11Y_DATA_VALID, value, change);
}

bool xtk_exphead_setaperipheral(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change) {
	return xtk_ctrl_setbool(scene, control, XTK_PROP_A11Y_PERIPHERAL, value, change);
}

bool xtk_exphead_setadialog(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change) {
	return xtk_ctrl_setbool(scene, control, XTK_PROP_A11Y_DIALOG, value, change);
}

bool xtk_exphead_setapos(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change) {
	return xtk_ctrl_seti32(scene, control, XTK_PROP_A11Y_POSITION, value, change);
}

bool xtk_exphead_setasize(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change) {
	return xtk_ctrl_seti32(scene, control, XTK_PROP_A11Y_SIZE, value, change);
}

bool xtk_exphead_setalevel(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change) {
	return xtk_ctrl_seti32(scene, control, XTK_PROP_A11Y_LEVEL, value, change);
}

bool xtk_exphead_setaculture(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change) {
	return xtk_ctrl_seti32(scene, control, XTK_PROP_A11Y_CULTURE, value, change);
}

bool xtk_exphead_setalabel(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change) {
	return xtk_ctrl_setstring(scene, control, XTK_PROP_A11Y_LABELED_BY, data, xtk_controls_text_len(data, len), change);
}

bool xtk_exphead_setadescribed(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
) {
	return xtk_ctrl_setstring(
	  scene, control, XTK_PROP_A11Y_DESCRIBED_BY, data, xtk_controls_text_len(data, len), change
	);
}

bool xtk_exphead_setaflowsto(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change) {
	return xtk_ctrl_setstring(scene, control, XTK_PROP_A11Y_FLOWS_TO, data, xtk_controls_text_len(data, len), change);
}

bool xtk_exphead_setaflowsfrom(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
) {
	return xtk_ctrl_setstring(scene, control, XTK_PROP_A11Y_FLOWS_FROM, data, xtk_controls_text_len(data, len), change);
}

bool xtk_exphead_setacontrols(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change) {
	return xtk_ctrl_setstring(scene, control, XTK_PROP_A11Y_CONTROLLED, data, xtk_controls_text_len(data, len), change);
}

bool xtk_exphead_seticon(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change) {
	return xtk_ctrl_setstring(scene, control, XTK_PROP_ICON, data, xtk_controls_text_len(data, len), change);
}

bool xtk_exphead_setenabled(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change) {
	return xtk_ctrl_setbool(scene, control, XTK_PROP_ENABLED, value, change);
}

bool xtk_exphead_setselected(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change) {
	return xtk_ctrl_setbool(scene, control, XTK_PROP_SELECTED, value, change);
}

bool xtk_exphead_setexpanded(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change) {
	return xtk_ctrl_setbool(scene, control, XTK_PROP_EXPANDED, value, change);
}
