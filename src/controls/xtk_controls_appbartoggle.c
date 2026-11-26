#include "xtk_controls_internal.h"

XtkLocalId xtk_appbartoggle_create(XtkTxn *txn, XtkNodeRef parent, XtkAppBarToggleProps const *props) {
	return xtk_controls_create(txn, XTK_CTRL_APPBARTOGGLE, parent, props, &xtk_pack_appbartoggle);
}

bool xtk_appbartoggle_setw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_ctrl_setf32(scene, control, XTK_PROP_WIDTH, value, change);
}

bool xtk_appbartoggle_seth(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_ctrl_setf32(scene, control, XTK_PROP_HEIGHT, value, change);
}

bool xtk_appbartoggle_setgrow(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_ctrl_setf32(scene, control, XTK_PROP_GROW, value, change);
}

bool xtk_appbartoggle_setself(XtkScene *scene, XtkCtrl control, XentFlexAlign value, XtkChangeStamp change) {
	return xtk_ctrl_setenum(scene, control, XTK_PROP_ALIGN_SELF, value, change);
}

bool xtk_appbartoggle_setml(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_ctrl_setf32(scene, control, XTK_PROP_MARGIN_LEFT, value, change);
}

bool xtk_appbartoggle_setmt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_ctrl_setf32(scene, control, XTK_PROP_MARGIN_TOP, value, change);
}

bool xtk_appbartoggle_setmr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_ctrl_setf32(scene, control, XTK_PROP_MARGIN_RIGHT, value, change);
}

bool xtk_appbartoggle_setmb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_ctrl_setf32(scene, control, XTK_PROP_MARGIN_BOTTOM, value, change);
}

bool xtk_appbartoggle_settip(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change) {
	return xtk_ctrl_setstring(scene, control, XTK_PROP_TOOLTIP, data, xtk_controls_text_len(data, len), change);
}

bool xtk_appbartoggle_setaname(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
) {
	return xtk_ctrl_setstring(scene, control, XTK_PROP_A11Y_NAME, data, xtk_controls_text_len(data, len), change);
}

bool xtk_appbartoggle_setaid(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change) {
	return xtk_ctrl_setstring(scene, control, XTK_PROP_A11Y_ID, data, xtk_controls_text_len(data, len), change);
}

bool xtk_appbartoggle_setahelp(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
) {
	return xtk_ctrl_setstring(scene, control, XTK_PROP_A11Y_HELP, data, xtk_controls_text_len(data, len), change);
}

bool xtk_appbartoggle_setadesc(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
) {
	return xtk_ctrl_setstring(
	  scene, control, XTK_PROP_A11Y_DESCRIPTION, data, xtk_controls_text_len(data, len), change
	);
}

bool xtk_appbartoggle_setastatus(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
) {
	return xtk_ctrl_setstring(
	  scene, control, XTK_PROP_A11Y_ITEM_STATUS, data, xtk_controls_text_len(data, len), change
	);
}

bool xtk_appbartoggle_setaitem(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
) {
	return xtk_ctrl_setstring(scene, control, XTK_PROP_A11Y_ITEM_TYPE, data, xtk_controls_text_len(data, len), change);
}

bool xtk_appbartoggle_setactype(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
) {
	return xtk_ctrl_setstring(
	  scene, control, XTK_PROP_A11Y_CONTROL_TYPE, data, xtk_controls_text_len(data, len), change
	);
}

bool xtk_appbartoggle_setaaccel(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
) {
	return xtk_ctrl_setstring(
	  scene, control, XTK_PROP_A11Y_ACCELERATOR, data, xtk_controls_text_len(data, len), change
	);
}

bool xtk_appbartoggle_setakey(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change) {
	return xtk_ctrl_setstring(scene, control, XTK_PROP_A11Y_ACCESS_KEY, data, xtk_controls_text_len(data, len), change);
}

bool xtk_appbartoggle_setalandmark(XtkScene *scene, XtkCtrl control, XtkLandmark value, XtkChangeStamp change) {
	return xtk_ctrl_setenum(scene, control, XTK_PROP_A11Y_LANDMARK, value, change);
}

bool xtk_appbartoggle_setalandname(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
) {
	return xtk_ctrl_setstring(
	  scene, control, XTK_PROP_A11Y_LANDMARK_NAME, data, xtk_controls_text_len(data, len), change
	);
}

bool xtk_appbartoggle_setalive(XtkScene *scene, XtkCtrl control, XtkLiveSetting value, XtkChangeStamp change) {
	return xtk_ctrl_setenum(scene, control, XTK_PROP_A11Y_LIVE, value, change);
}

bool xtk_appbartoggle_setaheading(XtkScene *scene, XtkCtrl control, XtkHeadingLevel value, XtkChangeStamp change) {
	return xtk_ctrl_setenum(scene, control, XTK_PROP_A11Y_HEADING, value, change);
}

bool xtk_appbartoggle_setaview(XtkScene *scene, XtkCtrl control, XtkAccessView value, XtkChangeStamp change) {
	return xtk_ctrl_setenum(scene, control, XTK_PROP_A11Y_VIEW, value, change);
}

bool xtk_appbartoggle_setarequired(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change) {
	return xtk_ctrl_setbool(scene, control, XTK_PROP_A11Y_REQUIRED, value, change);
}

bool xtk_appbartoggle_setavalid(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change) {
	return xtk_ctrl_setbool(scene, control, XTK_PROP_A11Y_DATA_VALID, value, change);
}

bool xtk_appbartoggle_setaperipheral(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change) {
	return xtk_ctrl_setbool(scene, control, XTK_PROP_A11Y_PERIPHERAL, value, change);
}

bool xtk_appbartoggle_setadialog(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change) {
	return xtk_ctrl_setbool(scene, control, XTK_PROP_A11Y_DIALOG, value, change);
}

bool xtk_appbartoggle_setapos(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change) {
	return xtk_ctrl_seti32(scene, control, XTK_PROP_A11Y_POSITION, value, change);
}

bool xtk_appbartoggle_setasize(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change) {
	return xtk_ctrl_seti32(scene, control, XTK_PROP_A11Y_SIZE, value, change);
}

bool xtk_appbartoggle_setalevel(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change) {
	return xtk_ctrl_seti32(scene, control, XTK_PROP_A11Y_LEVEL, value, change);
}

bool xtk_appbartoggle_setaculture(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change) {
	return xtk_ctrl_seti32(scene, control, XTK_PROP_A11Y_CULTURE, value, change);
}

bool xtk_appbartoggle_setalabel(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
) {
	return xtk_ctrl_setstring(scene, control, XTK_PROP_A11Y_LABELED_BY, data, xtk_controls_text_len(data, len), change);
}

bool xtk_appbartoggle_setadescribed(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
) {
	return xtk_ctrl_setstring(
	  scene, control, XTK_PROP_A11Y_DESCRIBED_BY, data, xtk_controls_text_len(data, len), change
	);
}

bool xtk_appbartoggle_setaflowsto(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
) {
	return xtk_ctrl_setstring(scene, control, XTK_PROP_A11Y_FLOWS_TO, data, xtk_controls_text_len(data, len), change);
}

bool xtk_appbartoggle_setaflowsfrom(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
) {
	return xtk_ctrl_setstring(scene, control, XTK_PROP_A11Y_FLOWS_FROM, data, xtk_controls_text_len(data, len), change);
}

bool xtk_appbartoggle_setacontrols(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
) {
	return xtk_ctrl_setstring(scene, control, XTK_PROP_A11Y_CONTROLLED, data, xtk_controls_text_len(data, len), change);
}

bool xtk_appbartoggle_settext(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change) {
	return xtk_ctrl_setstring(scene, control, XTK_PROP_TEXT, data, xtk_controls_text_len(data, len), change);
}

bool xtk_appbartoggle_seticon(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change) {
	return xtk_ctrl_setstring(scene, control, XTK_PROP_ICON, data, xtk_controls_text_len(data, len), change);
}

bool xtk_appbartoggle_setenabled(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change) {
	return xtk_ctrl_setbool(scene, control, XTK_PROP_ENABLED, value, change);
}

bool xtk_appbartoggle_setlabelpos(XtkScene *scene, XtkCtrl control, XtkElementLabel value, XtkChangeStamp change) {
	return xtk_ctrl_setenum(scene, control, XTK_PROP_LABEL_POSITION, value, change);
}

bool xtk_appbartoggle_setaccel(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
) {
	return xtk_ctrl_setstring(
	  scene, control, XTK_PROP_ACCELERATOR_TEXT, data, xtk_controls_text_len(data, len), change
	);
}

bool xtk_appbartoggle_setchecked(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change) {
	return xtk_ctrl_setbool(scene, control, XTK_PROP_CHECKED, value, change);
}

bool xtk_appbartoggle_setsecondary(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change) {
	return xtk_ctrl_setbool(scene, control, XTK_PROP_SECONDARY, value, change);
}

bool xtk_appbartoggle_setorder(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change) {
	return xtk_ctrl_seti32(scene, control, XTK_PROP_DYNAMIC_OVERFLOW_ORDER, value, change);
}

XtkSubRef xtk_appbartoggle_onchange(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg) {
	return xtk_txn_on(txn, target, XTK_EVENT_CHANGE_BOOL, XTK_EVENT_PHASE_MASK_TARGET, fn, arg);
}
