#include "xtk_controls_internal.h"

XtkLocalId xtk_avatar_create(XtkTxn *txn, XtkNodeRef parent, XtkAvatarProps const *props) {
	if (!props) return xtk_txn_create(txn, XTK_CTRL_AVATAR, parent, xtk_ref_none(), NULL, 0u);
	XtkPropPatch   patches [16];
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
	xtk_controls_append_string(
	  patches, &count, (props->set >> 10u) & 1u, XTK_PROP_TEXT, props->text, props->text_len, change
	);
	xtk_controls_append_string(
	  patches, &count, (props->set >> 11u) & 1u, XTK_PROP_INITIALS, props->initials, props->initials_len, change
	);
	xtk_controls_append_resource(patches, &count, (props->set >> 12u) & 1u, XTK_PROP_IMAGE_SOURCE, props->src, change);
	xtk_controls_append_string(
	  patches, &count, (props->set >> 13u) & 1u, XTK_PROP_BADGE_GLYPH, props->badgeglyph, props->badgeglyph_len, change
	);
	xtk_controls_append_i32(patches, &count, (props->set >> 14u) & 1u, XTK_PROP_BADGE_VALUE, props->badgevalue, change);
	xtk_controls_append_bool(patches, &count, (props->set >> 15u) & 1u, XTK_PROP_IS_GROUP, props->group, change);
	return xtk_txn_create(txn, XTK_CTRL_AVATAR, parent, xtk_ref_none(), patches, count);
}

bool xtk_avatar_setw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_control_set_f32(scene, control, XTK_PROP_WIDTH, value, change);
}

bool xtk_avatar_seth(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_control_set_f32(scene, control, XTK_PROP_HEIGHT, value, change);
}

bool xtk_avatar_setgrow(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_control_set_f32(scene, control, XTK_PROP_GROW, value, change);
}

bool xtk_avatar_setshrink(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_control_set_f32(scene, control, XTK_PROP_SHRINK, value, change);
}

bool xtk_avatar_setself(XtkScene *scene, XtkCtrl control, uint32_t value, XtkChangeStamp change) {
	return xtk_control_set_enum(scene, control, XTK_PROP_ALIGN_SELF, value, change);
}

bool xtk_avatar_setml(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_control_set_f32(scene, control, XTK_PROP_MARGIN_LEFT, value, change);
}

bool xtk_avatar_setmt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_control_set_f32(scene, control, XTK_PROP_MARGIN_TOP, value, change);
}

bool xtk_avatar_setmr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_control_set_f32(scene, control, XTK_PROP_MARGIN_RIGHT, value, change);
}

bool xtk_avatar_setmb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_control_set_f32(scene, control, XTK_PROP_MARGIN_BOTTOM, value, change);
}

bool xtk_avatar_settip(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change) {
	return xtk_control_set_string(scene, control, XTK_PROP_TOOLTIP, data, xtk_controls_text_len(data, len), change);
}

bool xtk_avatar_settext(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change) {
	return xtk_control_set_string(scene, control, XTK_PROP_TEXT, data, xtk_controls_text_len(data, len), change);
}

bool xtk_avatar_setinitials(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change) {
	return xtk_control_set_string(scene, control, XTK_PROP_INITIALS, data, xtk_controls_text_len(data, len), change);
}

bool xtk_avatar_setsrc(XtkScene *scene, XtkCtrl control, XtkResource value, XtkChangeStamp change) {
	return xtk_control_set_resource(scene, control, XTK_PROP_IMAGE_SOURCE, value, change);
}

bool xtk_avatar_setbadgeglyph(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change) {
	return xtk_control_set_string(scene, control, XTK_PROP_BADGE_GLYPH, data, xtk_controls_text_len(data, len), change);
}

bool xtk_avatar_setbadgevalue(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change) {
	return xtk_control_set_i32(scene, control, XTK_PROP_BADGE_VALUE, value, change);
}

bool xtk_avatar_setgroup(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change) {
	return xtk_control_set_bool(scene, control, XTK_PROP_IS_GROUP, value, change);
}
