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

XtkEl *xtk_suggest(XtkUi *ui, char const *placeholder, XtkAutoSuggestDesc desc) {
	XtkEl *el = xtk_el_new(ui, XTK_CTRL_SUGGEST, placeholder);
	if (!el) return NULL;
	desc.content    = xtk_strdup(ui, desc.content);
	desc.query_icon = xtk_strdup(ui, desc.query_icon);
	if (desc.nitem < 0) desc.nitem = 0;
	char const **items
	  = ( char const ** ) xtk_arena_alloc(xtk_ui_arena(ui), sizeof(char *) * ( size_t ) (desc.nitem ? desc.nitem : 1));
	if (!items) return NULL;
	for (int i = 0; i < desc.nitem; i++) items [i] = xtk_strdup(ui, desc.suggestions [i]);
	desc.suggestions = items;
	if (!XTK_EL_STORE(el, desc)) return NULL;
	return el;
}
