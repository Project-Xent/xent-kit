#ifndef XTK_CONTROLS_INTERNAL_H
#define XTK_CONTROLS_INTERNAL_H

#include <xtk/xtk_controls.h>

typedef struct XtkCtrlField {
	uint16_t offset;
	uint16_t len_offset;
	uint16_t id;
	uint8_t  bit;
	uint8_t  kind;
} XtkCtrlField;

typedef struct XtkCtrlPack {
	XtkCtrlField const *fields;
	uint16_t            a11y_offset;
	uint8_t             pre_count;
	uint8_t             field_count;
	uint8_t             a11y_bit;
	uint8_t             has_a11y;
} XtkCtrlPack;

uint32_t xtk_controls_text_len(char const *text, uint32_t len);
XtkLocalId
xtk_controls_create(XtkTxn *txn, XtkCtrlId type, XtkNodeRef parent, void const *props, XtkCtrlPack const *pack);

extern XtkCtrlPack const xtk_pack_container;
extern XtkCtrlPack const xtk_pack_text;
extern XtkCtrlPack const xtk_pack_button;
extern XtkCtrlPack const xtk_pack_toggle;
extern XtkCtrlPack const xtk_pack_checkbox;
extern XtkCtrlPack const xtk_pack_slider;
extern XtkCtrlPack const xtk_pack_textbox;
extern XtkCtrlPack const xtk_pack_scroll;
extern XtkCtrlPack const xtk_pack_image;
extern XtkCtrlPack const xtk_pack_progress;
extern XtkCtrlPack const xtk_pack_list;
extern XtkCtrlPack const xtk_pack_layout;
extern XtkCtrlPack const xtk_pack_input;
extern XtkCtrlPack const xtk_pack_number;
extern XtkCtrlPack const xtk_pack_link;
extern XtkCtrlPack const xtk_pack_progressring;
extern XtkCtrlPack const xtk_pack_badge;
extern XtkCtrlPack const xtk_pack_overlay;
extern XtkCtrlPack const xtk_pack_combo;
extern XtkCtrlPack const xtk_pack_expander;
extern XtkCtrlPack const xtk_pack_item;
extern XtkCtrlPack const xtk_pack_infobar;
extern XtkCtrlPack const xtk_pack_dialog;
extern XtkCtrlPack const xtk_pack_nav;
extern XtkCtrlPack const xtk_pack_selection;
extern XtkCtrlPack const xtk_pack_itemsview;
extern XtkCtrlPack const xtk_pack_flip;
extern XtkCtrlPack const xtk_pack_pips;
extern XtkCtrlPack const xtk_pack_suggest;
extern XtkCtrlPack const xtk_pack_radiogroup;
extern XtkCtrlPack const xtk_pack_rating;
extern XtkCtrlPack const xtk_pack_teachtip;
extern XtkCtrlPack const xtk_pack_tree;
extern XtkCtrlPack const xtk_pack_refresh;
extern XtkCtrlPack const xtk_pack_avatar;
extern XtkCtrlPack const xtk_pack_pager;
extern XtkCtrlPack const xtk_pack_splitview;
extern XtkCtrlPack const xtk_pack_titlebar;
extern XtkCtrlPack const xtk_pack_scrollbar;
extern XtkCtrlPack const xtk_pack_looping;
extern XtkCtrlPack const xtk_pack_datepicker;
extern XtkCtrlPack const xtk_pack_timepicker;
extern XtkCtrlPack const xtk_pack_calendar;
extern XtkCtrlPack const xtk_pack_colorpicker;
extern XtkCtrlPack const xtk_pack_column;
extern XtkCtrlPack const xtk_pack_commandbar;
extern XtkCtrlPack const xtk_pack_appbarbutton;
extern XtkCtrlPack const xtk_pack_appbartoggle;
extern XtkCtrlPack const xtk_pack_appbarsep;
extern XtkCtrlPack const xtk_pack_navslot;

#endif
