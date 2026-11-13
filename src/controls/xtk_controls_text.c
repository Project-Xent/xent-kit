#include "xtk_controls_internal.h"

XtkLocalId xtk_text_create(XtkTxn *txn, XtkNodeRef parent, XtkTextProps const *props) {
	if (!props) return xtk_txn_create(txn, XTK_CTRL_TEXT, parent, xtk_ref_none(), NULL, 0u);
	XtkPropPatch   patches [18];
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
	  patches, &count, (props->set >> 8u) & 1u, XTK_PROP_TEXT, props->text, props->text_len, change
	);
	xtk_controls_append_string(
	  patches, &count, (props->set >> 9u) & 1u, XTK_PROP_TOOLTIP, props->tip, props->tip_len, change
	);
	xtk_controls_append_f32(patches, &count, (props->set >> 10u) & 1u, XTK_PROP_FONT_SIZE, props->fontsize, change);
	xtk_controls_append_enum(
	  patches, &count, (props->set >> 11u) & 1u, XTK_PROP_FONT_WEIGHT, props->fontweight, change
	);
	xtk_controls_append_enum(patches, &count, (props->set >> 12u) & 1u, XTK_PROP_TEXT_ALIGN, props->textalign, change);
	xtk_controls_append_color(patches, &count, (props->set >> 13u) & 1u, XTK_PROP_FOREGROUND, props->fg, change);
	xtk_controls_append_i32(patches, &count, (props->set >> 14u) & 1u, XTK_PROP_MAX_LINES, props->maxlines, change);
	xtk_controls_append_enum(patches, &count, (props->set >> 15u) & 1u, XTK_PROP_TEXT_TRIM, props->trim, change);
	xtk_controls_append_bool(patches, &count, (props->set >> 16u) & 1u, XTK_PROP_TEXT_WRAP, props->textwrap, change);
	xtk_controls_append_bool(patches, &count, (props->set >> 17u) & 1u, XTK_PROP_SELECTABLE, props->selectable, change);
	return xtk_txn_create(txn, XTK_CTRL_TEXT, parent, xtk_ref_none(), patches, count);
}

bool xtk_text_setw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_ctrl_setf32(scene, control, XTK_PROP_WIDTH, value, change);
}

bool xtk_text_seth(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_ctrl_setf32(scene, control, XTK_PROP_HEIGHT, value, change);
}

bool xtk_text_setgrow(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_ctrl_setf32(scene, control, XTK_PROP_GROW, value, change);
}

bool xtk_text_setself(XtkScene *scene, XtkCtrl control, uint32_t value, XtkChangeStamp change) {
	return xtk_ctrl_setenum(scene, control, XTK_PROP_ALIGN_SELF, value, change);
}

bool xtk_text_setml(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_ctrl_setf32(scene, control, XTK_PROP_MARGIN_LEFT, value, change);
}

bool xtk_text_setmt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_ctrl_setf32(scene, control, XTK_PROP_MARGIN_TOP, value, change);
}

bool xtk_text_setmr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_ctrl_setf32(scene, control, XTK_PROP_MARGIN_RIGHT, value, change);
}

bool xtk_text_setmb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_ctrl_setf32(scene, control, XTK_PROP_MARGIN_BOTTOM, value, change);
}

bool xtk_text_settext(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change) {
	return xtk_ctrl_setstring(scene, control, XTK_PROP_TEXT, data, xtk_controls_text_len(data, len), change);
}

bool xtk_text_settip(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change) {
	return xtk_ctrl_setstring(scene, control, XTK_PROP_TOOLTIP, data, xtk_controls_text_len(data, len), change);
}

bool xtk_text_setfontsize(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change) {
	return xtk_ctrl_setf32(scene, control, XTK_PROP_FONT_SIZE, value, change);
}

bool xtk_text_setfontweight(XtkScene *scene, XtkCtrl control, uint32_t value, XtkChangeStamp change) {
	return xtk_ctrl_setenum(scene, control, XTK_PROP_FONT_WEIGHT, value, change);
}

bool xtk_text_settextalign(XtkScene *scene, XtkCtrl control, uint32_t value, XtkChangeStamp change) {
	return xtk_ctrl_setenum(scene, control, XTK_PROP_TEXT_ALIGN, value, change);
}

bool xtk_text_setfg(XtkScene *scene, XtkCtrl control, XtkColor value, XtkChangeStamp change) {
	return xtk_ctrl_setcolor(scene, control, XTK_PROP_FOREGROUND, value, change);
}

bool xtk_text_setmaxlines(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change) {
	return xtk_ctrl_seti32(scene, control, XTK_PROP_MAX_LINES, value, change);
}

bool xtk_text_settrim(XtkScene *scene, XtkCtrl control, uint32_t value, XtkChangeStamp change) {
	return xtk_ctrl_setenum(scene, control, XTK_PROP_TEXT_TRIM, value, change);
}

bool xtk_text_settextwrap(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change) {
	return xtk_ctrl_setbool(scene, control, XTK_PROP_TEXT_WRAP, value, change);
}

bool xtk_text_setselectable(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change) {
	return xtk_ctrl_setbool(scene, control, XTK_PROP_SELECTABLE, value, change);
}
