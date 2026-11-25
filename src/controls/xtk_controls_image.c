#include "xtk_controls_internal.h"

XtkLocalId xtk_image_create(XtkTxn *txn, XtkNodeRef parent, XtkImageProps const *props) {
	if (!props) return xtk_txn_create(txn, XTK_CTRL_IMAGE, parent, xtk_ref_none(), NULL, 0u);
	XtkPropPatch   patches [42];
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
	xtk_controls_append_string(
	  patches, &count, (props->set >> 9u) & 1u, XTK_PROP_A11Y_NAME, props->aname, props->aname_len, change
	);
	xtk_controls_append_string(
	  patches, &count, (props->set >> 10u) & 1u, XTK_PROP_A11Y_ID, props->aid, props->aid_len, change
	);
	xtk_controls_append_string(
	  patches, &count, (props->set >> 11u) & 1u, XTK_PROP_A11Y_HELP, props->ahelp, props->ahelp_len, change
	);
	xtk_controls_append_string(
	  patches, &count, (props->set >> 12u) & 1u, XTK_PROP_A11Y_DESCRIPTION, props->adesc, props->adesc_len, change
	);
	xtk_controls_append_string(
	  patches, &count, (props->set >> 13u) & 1u, XTK_PROP_A11Y_ITEM_STATUS, props->astatus, props->astatus_len, change
	);
	xtk_controls_append_string(
	  patches, &count, (props->set >> 14u) & 1u, XTK_PROP_A11Y_ITEM_TYPE, props->aitem, props->aitem_len, change
	);
	xtk_controls_append_string(
	  patches, &count, (props->set >> 15u) & 1u, XTK_PROP_A11Y_CONTROL_TYPE, props->actype, props->actype_len, change
	);
	xtk_controls_append_string(
	  patches, &count, (props->set >> 16u) & 1u, XTK_PROP_A11Y_ACCELERATOR, props->aaccel, props->aaccel_len, change
	);
	xtk_controls_append_string(
	  patches, &count, (props->set >> 17u) & 1u, XTK_PROP_A11Y_ACCESS_KEY, props->akey, props->akey_len, change
	);
	xtk_controls_append_enum(
	  patches, &count, (props->set >> 18u) & 1u, XTK_PROP_A11Y_LANDMARK, props->alandmark, change
	);
	xtk_controls_append_string(
	  patches, &count, (props->set >> 19u) & 1u, XTK_PROP_A11Y_LANDMARK_NAME, props->alandname, props->alandname_len,
	  change
	);
	xtk_controls_append_enum(patches, &count, (props->set >> 20u) & 1u, XTK_PROP_A11Y_LIVE, props->alive, change);
	xtk_controls_append_enum(patches, &count, (props->set >> 21u) & 1u, XTK_PROP_A11Y_HEADING, props->aheading, change);
	xtk_controls_append_enum(patches, &count, (props->set >> 22u) & 1u, XTK_PROP_A11Y_VIEW, props->aview, change);
	xtk_controls_append_bool(
	  patches, &count, (props->set >> 23u) & 1u, XTK_PROP_A11Y_REQUIRED, props->arequired, change
	);
	xtk_controls_append_bool(
	  patches, &count, (props->set >> 24u) & 1u, XTK_PROP_A11Y_DATA_VALID, props->avalid, change
	);
	xtk_controls_append_bool(
	  patches, &count, (props->set >> 25u) & 1u, XTK_PROP_A11Y_PERIPHERAL, props->aperipheral, change
	);
	xtk_controls_append_bool(patches, &count, (props->set >> 26u) & 1u, XTK_PROP_A11Y_DIALOG, props->adialog, change);
	xtk_controls_append_i32(patches, &count, (props->set >> 27u) & 1u, XTK_PROP_A11Y_POSITION, props->apos, change);
	xtk_controls_append_i32(patches, &count, (props->set >> 28u) & 1u, XTK_PROP_A11Y_SIZE, props->asize, change);
	xtk_controls_append_i32(patches, &count, (props->set >> 29u) & 1u, XTK_PROP_A11Y_LEVEL, props->alevel, change);
	xtk_controls_append_i32(patches, &count, (props->set >> 30u) & 1u, XTK_PROP_A11Y_CULTURE, props->aculture, change);
	xtk_controls_append_string(
	  patches, &count, (props->set >> 31u) & 1u, XTK_PROP_A11Y_LABELED_BY, props->alabel, props->alabel_len, change
	);
	xtk_controls_append_string(
	  patches, &count, (props->set >> 32u) & 1u, XTK_PROP_A11Y_DESCRIBED_BY, props->adescribed, props->adescribed_len,
	  change
	);
	xtk_controls_append_string(
	  patches, &count, (props->set >> 33u) & 1u, XTK_PROP_A11Y_FLOWS_TO, props->aflowsto, props->aflowsto_len, change
	);
	xtk_controls_append_string(
	  patches, &count, (props->set >> 34u) & 1u, XTK_PROP_A11Y_FLOWS_FROM, props->aflowsfrom, props->aflowsfrom_len,
	  change
	);
	xtk_controls_append_string(
	  patches, &count, (props->set >> 35u) & 1u, XTK_PROP_A11Y_CONTROLLED, props->acontrols, props->acontrols_len,
	  change
	);
	xtk_controls_append_resource(patches, &count, (props->set >> 36u) & 1u, XTK_PROP_IMAGE_SOURCE, props->src, change);
	xtk_controls_append_enum(patches, &count, (props->set >> 37u) & 1u, XTK_PROP_IMAGE_STRETCH, props->fit, change);
	xtk_controls_append_f32(patches, &count, (props->set >> 38u) & 1u, XTK_PROP_NINE_GRID_LEFT, props->nl, change);
	xtk_controls_append_f32(patches, &count, (props->set >> 39u) & 1u, XTK_PROP_NINE_GRID_TOP, props->nt, change);
	xtk_controls_append_f32(patches, &count, (props->set >> 40u) & 1u, XTK_PROP_NINE_GRID_RIGHT, props->nr, change);
	xtk_controls_append_f32(patches, &count, (props->set >> 41u) & 1u, XTK_PROP_NINE_GRID_BOTTOM, props->nb, change);
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

bool xtk_image_setaname(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change) {
	return xtk_ctrl_setstring(scene, control, XTK_PROP_A11Y_NAME, data, xtk_controls_text_len(data, len), change);
}

bool xtk_image_setaid(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change) {
	return xtk_ctrl_setstring(scene, control, XTK_PROP_A11Y_ID, data, xtk_controls_text_len(data, len), change);
}

bool xtk_image_setahelp(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change) {
	return xtk_ctrl_setstring(scene, control, XTK_PROP_A11Y_HELP, data, xtk_controls_text_len(data, len), change);
}

bool xtk_image_setadesc(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change) {
	return xtk_ctrl_setstring(
	  scene, control, XTK_PROP_A11Y_DESCRIPTION, data, xtk_controls_text_len(data, len), change
	);
}

bool xtk_image_setastatus(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change) {
	return xtk_ctrl_setstring(
	  scene, control, XTK_PROP_A11Y_ITEM_STATUS, data, xtk_controls_text_len(data, len), change
	);
}

bool xtk_image_setaitem(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change) {
	return xtk_ctrl_setstring(scene, control, XTK_PROP_A11Y_ITEM_TYPE, data, xtk_controls_text_len(data, len), change);
}

bool xtk_image_setactype(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change) {
	return xtk_ctrl_setstring(
	  scene, control, XTK_PROP_A11Y_CONTROL_TYPE, data, xtk_controls_text_len(data, len), change
	);
}

bool xtk_image_setaaccel(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change) {
	return xtk_ctrl_setstring(
	  scene, control, XTK_PROP_A11Y_ACCELERATOR, data, xtk_controls_text_len(data, len), change
	);
}

bool xtk_image_setakey(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change) {
	return xtk_ctrl_setstring(scene, control, XTK_PROP_A11Y_ACCESS_KEY, data, xtk_controls_text_len(data, len), change);
}

bool xtk_image_setalandmark(XtkScene *scene, XtkCtrl control, XtkLandmark value, XtkChangeStamp change) {
	return xtk_ctrl_setenum(scene, control, XTK_PROP_A11Y_LANDMARK, value, change);
}

bool xtk_image_setalandname(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change) {
	return xtk_ctrl_setstring(
	  scene, control, XTK_PROP_A11Y_LANDMARK_NAME, data, xtk_controls_text_len(data, len), change
	);
}

bool xtk_image_setalive(XtkScene *scene, XtkCtrl control, XtkLiveSetting value, XtkChangeStamp change) {
	return xtk_ctrl_setenum(scene, control, XTK_PROP_A11Y_LIVE, value, change);
}

bool xtk_image_setaheading(XtkScene *scene, XtkCtrl control, XtkHeadingLevel value, XtkChangeStamp change) {
	return xtk_ctrl_setenum(scene, control, XTK_PROP_A11Y_HEADING, value, change);
}

bool xtk_image_setaview(XtkScene *scene, XtkCtrl control, XtkAccessView value, XtkChangeStamp change) {
	return xtk_ctrl_setenum(scene, control, XTK_PROP_A11Y_VIEW, value, change);
}

bool xtk_image_setarequired(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change) {
	return xtk_ctrl_setbool(scene, control, XTK_PROP_A11Y_REQUIRED, value, change);
}

bool xtk_image_setavalid(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change) {
	return xtk_ctrl_setbool(scene, control, XTK_PROP_A11Y_DATA_VALID, value, change);
}

bool xtk_image_setaperipheral(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change) {
	return xtk_ctrl_setbool(scene, control, XTK_PROP_A11Y_PERIPHERAL, value, change);
}

bool xtk_image_setadialog(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change) {
	return xtk_ctrl_setbool(scene, control, XTK_PROP_A11Y_DIALOG, value, change);
}

bool xtk_image_setapos(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change) {
	return xtk_ctrl_seti32(scene, control, XTK_PROP_A11Y_POSITION, value, change);
}

bool xtk_image_setasize(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change) {
	return xtk_ctrl_seti32(scene, control, XTK_PROP_A11Y_SIZE, value, change);
}

bool xtk_image_setalevel(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change) {
	return xtk_ctrl_seti32(scene, control, XTK_PROP_A11Y_LEVEL, value, change);
}

bool xtk_image_setaculture(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change) {
	return xtk_ctrl_seti32(scene, control, XTK_PROP_A11Y_CULTURE, value, change);
}

bool xtk_image_setalabel(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change) {
	return xtk_ctrl_setstring(scene, control, XTK_PROP_A11Y_LABELED_BY, data, xtk_controls_text_len(data, len), change);
}

bool xtk_image_setadescribed(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change) {
	return xtk_ctrl_setstring(
	  scene, control, XTK_PROP_A11Y_DESCRIBED_BY, data, xtk_controls_text_len(data, len), change
	);
}

bool xtk_image_setaflowsto(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change) {
	return xtk_ctrl_setstring(scene, control, XTK_PROP_A11Y_FLOWS_TO, data, xtk_controls_text_len(data, len), change);
}

bool xtk_image_setaflowsfrom(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change) {
	return xtk_ctrl_setstring(scene, control, XTK_PROP_A11Y_FLOWS_FROM, data, xtk_controls_text_len(data, len), change);
}

bool xtk_image_setacontrols(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change) {
	return xtk_ctrl_setstring(scene, control, XTK_PROP_A11Y_CONTROLLED, data, xtk_controls_text_len(data, len), change);
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
