#include "xtk_internal.h"

#include <string.h>

XtkEl *xtk_tabs(XtkUi *ui, XtkTabViewDesc desc, XtkEl *children []) {
	XtkEl *el = xtk_el_new(ui, XTK_CTRL_TABS, NULL);
	if (!el) return NULL;
	if (desc.ntab < 0) desc.ntab = 0;
	XtkTabDesc *tabs
	  = ( XtkTabDesc * ) xtk_arena_alloc(xtk_ui_arena(ui), sizeof(XtkTabDesc) * ( size_t ) (desc.ntab ? desc.ntab : 1));
	if (!tabs) return NULL;
	for (int i = 0; i < desc.ntab; i++) {
		tabs [i]       = desc.tabs [i];
		tabs [i].icon  = xtk_strdup(ui, tabs [i].icon);
		tabs [i].label = xtk_strdup(ui, tabs [i].label);
	}
	desc.tabs = tabs;
	if (!XTK_EL_STORE(el, desc)) return NULL;
	xtk_el_adopt(ui, el, children);
	return el;
}

XtkEl *xtk_dialog(XtkUi *ui, char const *title, XtkDialogDesc desc, XtkEl *children []) {
	XtkEl *el = xtk_el_new(ui, XTK_CTRL_DIALOG, title);
	if (!el) return NULL;
	desc.primary   = xtk_strdup(ui, desc.primary);
	desc.secondary = xtk_strdup(ui, desc.secondary);
	desc.close     = xtk_strdup(ui, desc.close);
	if (desc.w <= 0.0f) desc.w = 400.0f;
	if (desc.contenth <= 0.0f) desc.contenth = 120.0f;
	if (!XTK_EL_STORE(el, desc)) return NULL;
	xtk_el_adopt(ui, el, children);
	return el;
}

XtkEl *xtk_teachtip(XtkUi *ui, char const *title, XtkTeachingTipDesc desc, XtkEl *children []) {
	XtkEl *el = xtk_el_new(ui, XTK_CTRL_TEACHTIP, title);
	if (!el) return NULL;
	desc.subtitle    = xtk_strdup(ui, desc.subtitle);
	desc.icon        = xtk_strdup(ui, desc.icon);
	desc.action_text = xtk_strdup(ui, desc.action_text);
	desc.close_text  = xtk_strdup(ui, desc.close_text);
	if (!XTK_EL_STORE(el, desc)) return NULL;
	xtk_el_adopt(ui, el, children);
	return el;
}
