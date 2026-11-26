#include "xtk_internal.h"

#include <string.h>

static XtkEl *stack(XtkUi *ui, XtkCtrlType type, bool row, XtkStackDesc desc, XtkEl *children []) {
	XtkEl *el = xtk_el_new(ui, type, NULL);
	if (!el) return NULL;
	XTK_EL_DATA(el)->stack_row = row;
	if (!XTK_EL_STORE(el, desc)) return NULL;
	xtk_el_adopt(ui, el, children);
	return el;
}

XtkEl *xtk_column(XtkUi *ui, XtkStackDesc desc, XtkEl *children []) {
	return stack(ui, XTK_CTRL_CONTAINER, false, desc, children);
}

XtkEl *xtk_row(XtkUi *ui, XtkStackDesc desc, XtkEl *children []) {
	return stack(ui, XTK_CTRL_CONTAINER, true, desc, children);
}

XtkEl *xtk_card(XtkUi *ui, XtkStackDesc desc, XtkEl *children []) {
	XentInsets const none = {0};
	if (memcmp(&desc.padding, &none, sizeof(none)) == 0) desc.padding = (XentInsets) {16.0f, 16.0f, 16.0f, 16.0f};
	if (desc.gap == 0.0f) desc.gap = 8.0f;
	return stack(ui, XTK_CTRL_CARD, false, desc, children);
}

XtkEl *xtk_dragdrop(XtkUi *ui, XtkDragDropDesc desc, XtkEl *child) {
	XtkEl *el = xtk_el_new(ui, XTK_CTRL_CONTAINER, NULL);
	if (!el) return NULL;
	desc.drag_text           = xtk_strdup(ui, desc.drag_text);
	desc.drag_files          = xtk_strdup(ui, desc.drag_files);
	XtkDragDropDetail detail = {.stack = {.align = XENT_FLEX_ALIGN_STRETCH}, .dnd = desc};
	if (!XTK_EL_STORE(el, detail)) return NULL;
	xtk_el_adopt(ui, el, xtk_kids(child));
	return el;
}

XtkEl *xtk_scroll(XtkUi *ui, XtkScrollDesc desc, XtkEl *children []) {
	XtkEl *el = xtk_el_new(ui, XTK_CTRL_SCROLL, NULL);
	if (!el) return NULL;
	XtkScrollDetail detail = {
	  .stack  = {.fill = true, .align = XENT_FLEX_ALIGN_STRETCH},
	  .scroll = desc,
	};
	if (!XTK_EL_STORE(el, detail)) return NULL;
	xtk_el_adopt(ui, el, children);
	return el;
}

XtkEl *xtk_colheader(XtkUi *ui, XtkEl *children []) {
	XtkEl *el = xtk_el_new(ui, XTK_CTRL_COLHEADER, NULL);
	if (el) xtk_el_adopt(ui, el, children);
	return el;
}

XtkEl *xtk_colitem(XtkUi *ui, char const *label, XtkColItemDesc desc) {
	XtkEl *el = xtk_el_new(ui, XTK_CTRL_COLITEM, label);
	if (!el) return NULL;
	if (desc.width <= 0.0f) desc.width = 200.0f;
	if (desc.min_width <= 0.0f) desc.min_width = 50.0f;
	if (desc.max_width <= 0.0f) desc.max_width = 800.0f;
	return XTK_EL_STORE(el, desc) ? el : NULL;
}

XtkEl *xtk_commandbar(XtkUi *ui, XtkCommandBarDesc desc, XtkEl *children []) {
	XtkEl *el = xtk_el_new(ui, XTK_CTRL_COMMANDBAR, NULL);
	if (!el || !XTK_EL_STORE(el, desc)) return NULL;
	xtk_el_adopt(ui, el, children);
	return el;
}

static XtkEl *appbar(XtkUi *ui, XtkCtrlType type, char const *label, XtkAppBarDesc desc) {
	XtkEl *el = xtk_el_new(ui, type, label);
	if (!el) return NULL;
	desc.icon  = xtk_strdup(ui, desc.icon);
	desc.accel = xtk_strdup(ui, desc.accel);
	return XTK_EL_STORE(el, desc) ? el : NULL;
}

XtkEl *xtk_appbarbutton(XtkUi *ui, char const *label, XtkAppBarDesc desc) {
	return appbar(ui, XTK_CTRL_APPBARBUTTON, label, desc);
}

XtkEl *xtk_appbartoggle(XtkUi *ui, char const *label, XtkAppBarDesc desc) {
	return appbar(ui, XTK_CTRL_APPBARTOGGLE, label, desc);
}

XtkEl *xtk_appbarsep(XtkUi *ui, XtkAppBarDesc desc) { return appbar(ui, XTK_CTRL_APPBARSEP, NULL, desc); }

XtkEl *xtk_expander(XtkUi *ui, char const *header, XtkExpanderDesc desc, XtkEl *children []) {
	XtkEl *el = xtk_el_new(ui, XTK_CTRL_EXPANDER, header);
	if (!el) return NULL;
	if (!XTK_EL_STORE(el, desc)) return NULL;
	xtk_el_adopt(ui, el, children);
	return el;
}

static bool nav_dup_items(XtkUi *ui, XtkNavDesc *desc) {
	if (desc->nitem < 0 || !desc->items) {
		desc->items = NULL;
		desc->nitem = 0;
		return true;
	}
	if (xtk_model_ver_valid(desc->version)) return true;
	XtkNavItemDesc *items
	  = ( XtkNavItemDesc * ) xtk_arena_alloc(xtk_ui_arena(ui), sizeof(XtkNavItemDesc) * ( size_t ) desc->nitem);
	if (!items) return false;
	for (int i = 0; i < desc->nitem; i++) {
		items [i]       = desc->items [i];
		items [i].icon  = xtk_strdup(ui, items [i].icon);
		items [i].label = xtk_strdup(ui, items [i].label);
	}
	desc->items = items;
	return true;
}

XtkEl *xtk_nav(XtkUi *ui, XtkNavDesc desc, XtkEl *children []) {
	XtkEl *el = xtk_el_new(ui, XTK_CTRL_NAV, NULL);
	if (!el || !nav_dup_items(ui, &desc)) return NULL;
	desc.app_title  = xtk_strdup(ui, desc.app_title);
	desc.pane_title = xtk_strdup(ui, desc.pane_title);
	if (!XTK_EL_STORE(el, desc)) return NULL;
	xtk_el_adopt(ui, el, children);
	return el;
}

XtkEl *xtk_nav_slot(XtkUi *ui, XtkNavSlot slot, XtkEl *child) {
	XtkEl *el = xtk_el_new(ui, XTK_CTRL_NAVSLOT, NULL);
	if (!el) return NULL;
	if (slot != XTK_NAV_SLOT_CONTENT) XTK_EL_DATA(el)->nav_slot = ( uint8_t ) slot;
	if (child) xtk_el_adopt(ui, el, xtk_kids(child));
	return el;
}

XtkEl *xtk_nav_header_template(XtkUi *ui, void const *header, XtkNavHeaderTemplate render) {
	if (!header || !render) return NULL;
	XtkEl *content = render(ui, header);
	return content ? xtk_nav_slot(ui, XTK_NAV_SLOT_PAGE_HEADER, content) : NULL;
}

XtkEl *xtk_refresh(XtkUi *ui, XtkRefreshDesc desc, XtkEl *children []) {
	XtkEl *el = xtk_el_new(ui, XTK_CTRL_REFRESH, NULL);
	if (!el) return NULL;
	if (!XTK_EL_STORE(el, desc)) return NULL;
	xtk_el_adopt(ui, el, children);
	return el;
}
