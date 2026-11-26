#include "xtk_internal.h"

#include <string.h>

XtkEl *xtk_flip(XtkUi *ui, XtkFlipDesc desc, XtkEl *children []) {
	XtkEl *el = xtk_el_new(ui, XTK_CTRL_FLIP, NULL);
	if (!el) return NULL;
	if (!XTK_EL_STORE(el, desc)) return NULL;
	xtk_el_adopt(ui, el, children);
	return el;
}

XtkEl *xtk_pips(XtkUi *ui, XtkPipsDesc desc) {
	XtkEl *el = xtk_el_new(ui, XTK_CTRL_PIPS, NULL);
	if (!el) return NULL;
	if (desc.nitem < 0) desc.nitem = 0;
	if (desc.max_visible <= 0) desc.max_visible = 5;
	if (!XTK_EL_STORE(el, desc)) return NULL;
	return el;
}

XtkEl *xtk_avatar(XtkUi *ui, XtkPersonPictureDesc desc) {
	XtkEl *el = xtk_el_new(ui, XTK_CTRL_AVATAR, NULL);
	if (!el) return NULL;
	desc.display_name = xtk_strdup(ui, desc.display_name);
	desc.initials     = xtk_strdup(ui, desc.initials);
	desc.badge_glyph  = xtk_strdup(ui, desc.badge_glyph);
	desc.badge_text   = xtk_strdup(ui, desc.badge_text);
	if (!XTK_EL_STORE(el, desc)) return NULL;
	return el;
}

XtkEl *xtk_splitview(XtkUi *ui, XtkSplitViewDesc desc, XtkEl *pane, XtkEl *content) {
	XtkEl *el = xtk_el_new(ui, XTK_CTRL_SPLITVIEW, NULL);
	if (!el) return NULL;
	if (!XTK_EL_STORE(el, desc)) return NULL;

	XtkEl *cw = xtk_el_new(ui, XTK_CTRL_SPLITBODY, NULL);
	XtkEl *pw = xtk_el_new(ui, XTK_CTRL_SPLITPANE, NULL);
	if (!cw || !pw) return NULL;
	if (content) xtk_el_adopt(ui, cw, (XtkEl *[]) {content, XTK_END});
	if (pane) xtk_el_adopt(ui, pw, (XtkEl *[]) {pane, XTK_END});
	xtk_el_adopt(ui, el, (XtkEl *[]) {cw, pw, XTK_END});
	return el;
}

XtkEl *xtk_titlebar(XtkUi *ui, char const *title, XtkTitleBarDesc desc) {
	XtkEl *el = xtk_el_new(ui, XTK_CTRL_TITLEBAR, NULL);
	if (!el) return NULL;
	XTK_EL_DATA(el)->text = xtk_strdup(ui, title);
	desc.subtitle         = xtk_strdup(ui, desc.subtitle);
	desc.icon             = xtk_strdup(ui, desc.icon);
	if (!XTK_EL_STORE(el, desc)) return NULL;
	return el;
}

XtkEl *xtk_titlebar_slots(
  XtkUi *ui, char const *title, XtkTitleBarDesc desc, XtkEl *left_header, XtkEl *content, XtkEl *right_header
) {
	XtkEl *el = xtk_titlebar(ui, title, desc);
	if (!el) return NULL;
	XtkEl      *parts [] = {left_header, content, right_header};
	char const *keys []  = {"left-header", "content", "right-header"};
	XtkEl      *kids [4] = {0};
	unsigned    n        = 0;
	for (unsigned i = 0; i < 3; i++) {
		if (!parts [i]) continue;
		unsigned slot    = XTK_TITLE_BAR_SLOT_LEFT_HEADER + i;
		XtkEl   *wrapper = xtk_nav_slot(ui, ( XtkNavSlot ) slot, parts [i]);
		if (!wrapper) return NULL;
		kids [n++] = xtk_keyed(ui, keys [i], wrapper);
	}
	kids [n] = XTK_END;
	xtk_el_adopt(ui, el, kids);
	return el;
}

XtkEl *xtk_pager(XtkUi *ui, XtkPagerDesc desc) {
	XtkEl *el = xtk_el_new(ui, XTK_CTRL_PAGER, NULL);
	if (!el) return NULL;
	if (desc.nitem < 1) desc.nitem = 1;
	if (desc.sel < 0) desc.sel = 0;
	if (desc.sel > desc.nitem - 1) desc.sel = desc.nitem - 1;
	desc.prefix = xtk_strdup(ui, desc.prefix);
	desc.suffix = xtk_strdup(ui, desc.suffix);
	if (!XTK_EL_STORE(el, desc)) return NULL;
	return el;
}

static bool suggest_dup_items(XtkUi *ui, XtkAutoSuggestDesc *desc) {
	if (desc->nitem <= 0 || !desc->suggestions) {
		desc->suggestions = NULL;
		desc->nitem       = 0;
		return true;
	}
	if (xtk_model_ver_valid(desc->version)) return true;
	char const **items = ( char const ** ) xtk_arena_alloc(xtk_ui_arena(ui), sizeof(char *) * ( size_t ) desc->nitem);
	if (!items) return false;
	for (int i = 0; i < desc->nitem; i++) items [i] = xtk_strdup(ui, desc->suggestions [i]);
	desc->suggestions = items;
	return true;
}

XtkEl *xtk_suggest(XtkUi *ui, char const *placeholder, XtkAutoSuggestDesc desc) {
	XtkEl *el = xtk_el_new(ui, XTK_CTRL_SUGGEST, placeholder);
	if (!el || !suggest_dup_items(ui, &desc)) return NULL;
	desc.content    = xtk_strdup(ui, desc.content);
	desc.query_icon = xtk_strdup(ui, desc.query_icon);
	if (!XTK_EL_STORE(el, desc)) return NULL;
	return el;
}
