#include "xtk_controls_internal.h"

XtkLocalId xtk_titlebar_create(XtkTxn *txn, XtkNodeRef parent, XtkTitleBarProps const *props) {
	return xtk_controls_create(txn, XTK_CTRL_TITLEBAR, parent, props, &xtk_pack_titlebar);
}

bool xtk_titlebar_setw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_ctrl_setf32(scene, control, XTK_PROP_WIDTH, value, change);
}

bool xtk_titlebar_seth(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_ctrl_setf32(scene, control, XTK_PROP_HEIGHT, value, change);
}

bool xtk_titlebar_setgrow(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_ctrl_setf32(scene, control, XTK_PROP_GROW, value, change);
}

bool xtk_titlebar_setshrink(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_ctrl_setf32(scene, control, XTK_PROP_SHRINK, value, change);
}

bool xtk_titlebar_setself(XtkScene *scene, XtkCtrl control, XentFlexAlign value, XtkChangeStamp change) {
	return xtk_ctrl_setenum(scene, control, XTK_PROP_ALIGN_SELF, value, change);
}

bool xtk_titlebar_setml(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_ctrl_setf32(scene, control, XTK_PROP_MARGIN_LEFT, value, change);
}

bool xtk_titlebar_setmt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_ctrl_setf32(scene, control, XTK_PROP_MARGIN_TOP, value, change);
}

bool xtk_titlebar_setmr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_ctrl_setf32(scene, control, XTK_PROP_MARGIN_RIGHT, value, change);
}

bool xtk_titlebar_setmb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_ctrl_setf32(scene, control, XTK_PROP_MARGIN_BOTTOM, value, change);
}

bool xtk_titlebar_settip(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change) {
	return xtk_ctrl_setstring(scene, control, XTK_PROP_TOOLTIP, data, xtk_controls_text_len(data, len), change);
}

bool xtk_titlebar_setaname(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change) {
	return xtk_ctrl_setstring(scene, control, XTK_PROP_A11Y_NAME, data, xtk_controls_text_len(data, len), change);
}

bool xtk_titlebar_setaid(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change) {
	return xtk_ctrl_setstring(scene, control, XTK_PROP_A11Y_ID, data, xtk_controls_text_len(data, len), change);
}

bool xtk_titlebar_setahelp(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change) {
	return xtk_ctrl_setstring(scene, control, XTK_PROP_A11Y_HELP, data, xtk_controls_text_len(data, len), change);
}

bool xtk_titlebar_setadesc(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change) {
	return xtk_ctrl_setstring(
	  scene, control, XTK_PROP_A11Y_DESCRIPTION, data, xtk_controls_text_len(data, len), change
	);
}

bool xtk_titlebar_setastatus(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change) {
	return xtk_ctrl_setstring(
	  scene, control, XTK_PROP_A11Y_ITEM_STATUS, data, xtk_controls_text_len(data, len), change
	);
}

bool xtk_titlebar_setaitem(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change) {
	return xtk_ctrl_setstring(scene, control, XTK_PROP_A11Y_ITEM_TYPE, data, xtk_controls_text_len(data, len), change);
}

bool xtk_titlebar_setactype(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change) {
	return xtk_ctrl_setstring(
	  scene, control, XTK_PROP_A11Y_CONTROL_TYPE, data, xtk_controls_text_len(data, len), change
	);
}

bool xtk_titlebar_setaaccel(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change) {
	return xtk_ctrl_setstring(
	  scene, control, XTK_PROP_A11Y_ACCELERATOR, data, xtk_controls_text_len(data, len), change
	);
}

bool xtk_titlebar_setakey(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change) {
	return xtk_ctrl_setstring(scene, control, XTK_PROP_A11Y_ACCESS_KEY, data, xtk_controls_text_len(data, len), change);
}

bool xtk_titlebar_setalandmark(XtkScene *scene, XtkCtrl control, XtkLandmark value, XtkChangeStamp change) {
	return xtk_ctrl_setenum(scene, control, XTK_PROP_A11Y_LANDMARK, value, change);
}

bool xtk_titlebar_setalandname(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
) {
	return xtk_ctrl_setstring(
	  scene, control, XTK_PROP_A11Y_LANDMARK_NAME, data, xtk_controls_text_len(data, len), change
	);
}

bool xtk_titlebar_setalive(XtkScene *scene, XtkCtrl control, XtkLiveSetting value, XtkChangeStamp change) {
	return xtk_ctrl_setenum(scene, control, XTK_PROP_A11Y_LIVE, value, change);
}

bool xtk_titlebar_setaheading(XtkScene *scene, XtkCtrl control, XtkHeadingLevel value, XtkChangeStamp change) {
	return xtk_ctrl_setenum(scene, control, XTK_PROP_A11Y_HEADING, value, change);
}

bool xtk_titlebar_setaview(XtkScene *scene, XtkCtrl control, XtkAccessView value, XtkChangeStamp change) {
	return xtk_ctrl_setenum(scene, control, XTK_PROP_A11Y_VIEW, value, change);
}

bool xtk_titlebar_setarequired(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change) {
	return xtk_ctrl_setbool(scene, control, XTK_PROP_A11Y_REQUIRED, value, change);
}

bool xtk_titlebar_setavalid(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change) {
	return xtk_ctrl_setbool(scene, control, XTK_PROP_A11Y_DATA_VALID, value, change);
}

bool xtk_titlebar_setaperipheral(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change) {
	return xtk_ctrl_setbool(scene, control, XTK_PROP_A11Y_PERIPHERAL, value, change);
}

bool xtk_titlebar_setadialog(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change) {
	return xtk_ctrl_setbool(scene, control, XTK_PROP_A11Y_DIALOG, value, change);
}

bool xtk_titlebar_setapos(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change) {
	return xtk_ctrl_seti32(scene, control, XTK_PROP_A11Y_POSITION, value, change);
}

bool xtk_titlebar_setasize(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change) {
	return xtk_ctrl_seti32(scene, control, XTK_PROP_A11Y_SIZE, value, change);
}

bool xtk_titlebar_setalevel(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change) {
	return xtk_ctrl_seti32(scene, control, XTK_PROP_A11Y_LEVEL, value, change);
}

bool xtk_titlebar_setaculture(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change) {
	return xtk_ctrl_seti32(scene, control, XTK_PROP_A11Y_CULTURE, value, change);
}

bool xtk_titlebar_setalabel(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change) {
	return xtk_ctrl_setstring(scene, control, XTK_PROP_A11Y_LABELED_BY, data, xtk_controls_text_len(data, len), change);
}

bool xtk_titlebar_setadescribed(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
) {
	return xtk_ctrl_setstring(
	  scene, control, XTK_PROP_A11Y_DESCRIBED_BY, data, xtk_controls_text_len(data, len), change
	);
}

bool xtk_titlebar_setaflowsto(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change) {
	return xtk_ctrl_setstring(scene, control, XTK_PROP_A11Y_FLOWS_TO, data, xtk_controls_text_len(data, len), change);
}

bool xtk_titlebar_setaflowsfrom(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
) {
	return xtk_ctrl_setstring(scene, control, XTK_PROP_A11Y_FLOWS_FROM, data, xtk_controls_text_len(data, len), change);
}

bool xtk_titlebar_setacontrols(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
) {
	return xtk_ctrl_setstring(scene, control, XTK_PROP_A11Y_CONTROLLED, data, xtk_controls_text_len(data, len), change);
}

bool xtk_titlebar_settext(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change) {
	return xtk_ctrl_setstring(scene, control, XTK_PROP_TEXT, data, xtk_controls_text_len(data, len), change);
}

bool xtk_titlebar_setsubtitle(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change) {
	return xtk_ctrl_setstring(scene, control, XTK_PROP_SUBTITLE, data, xtk_controls_text_len(data, len), change);
}

bool xtk_titlebar_seticon(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change) {
	return xtk_ctrl_setstring(scene, control, XTK_PROP_ICON, data, xtk_controls_text_len(data, len), change);
}

bool xtk_titlebar_setshowback(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change) {
	return xtk_ctrl_setbool(scene, control, XTK_PROP_SHOW_BACK, value, change);
}

bool xtk_titlebar_setbackdisabled(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change) {
	return xtk_ctrl_setbool(scene, control, XTK_PROP_BACK_DISABLED, value, change);
}

bool xtk_titlebar_setshowtoggle(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change) {
	return xtk_ctrl_setbool(scene, control, XTK_PROP_SHOW_PANE_TOGGLE, value, change);
}

bool xtk_titlebar_setintegrate(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change) {
	return xtk_ctrl_setbool(scene, control, XTK_PROP_INTEGRATE_WINDOW, value, change);
}

XtkSubRef xtk_titlebar_oninvoke(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg) {
	return xtk_txn_on(txn, target, XTK_EVENT_INVOKE, XTK_EVENT_PHASE_MASK_TARGET, fn, arg);
}

XtkSubRef xtk_titlebar_ontoggle(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg) {
	return xtk_txn_on(txn, target, XTK_EVENT_TOGGLE, XTK_EVENT_PHASE_MASK_TARGET, fn, arg);
}
