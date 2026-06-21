/**
 * @file xtk_el_compound.c
 * @brief Element builders for compound controls: combo box, number box,
 * dropdown/split button, menu bar, tab view, content dialog, nav view,
 * and stack-based containers (column, row, card, scroll, expander).
 */
#include "xtk_internal.h"

#include <string.h>

XtkEl *xtk_combo_box(XtkUi *ui, char const *placeholder, XtkComboDesc desc) {
	XtkEl *el = xtk_el_new(ui, XTK_CONTROL_COMBO_BOX, placeholder);
	if (!el) return NULL;
	if (desc.count < 0) desc.count = 0;
	char const **items
	  = ( char const ** ) xtk_arena_alloc(xtk_ui_arena(ui), sizeof(char *) * ( size_t ) (desc.count ? desc.count : 1));
	if (!items) return NULL;
	for (int i = 0; i < desc.count; i++) items [i] = xtk_strdup(ui, desc.items [i]);
	desc.items = items;
	el->combo  = desc;
	return el;
}

XtkEl *xtk_number_box(XtkUi *ui, XtkNumberDesc desc) {
	XtkEl *el = xtk_el_new(ui, XTK_CONTROL_NUMBER_BOX, NULL);
	if (!el) return NULL;
	if (desc.max == 0.0 && desc.min == 0.0) desc.max = 100.0;
	if (desc.step == 0.0) desc.step = 1.0;
	el->number = desc;
	return el;
}

XtkEl *xtk_dropdown_button(XtkUi *ui, char const *label, XtkDropdownDesc desc) {
	XtkEl *el = xtk_el_new(ui, XTK_CONTROL_DROPDOWN_BUTTON, label);
	if (!el) return NULL;
	desc.icon = xtk_strdup(ui, desc.icon);
	if (desc.item_count < 0) desc.item_count = 0;
	XtkMenuItemDesc *items = ( XtkMenuItemDesc * ) xtk_arena_alloc(
	  xtk_ui_arena(ui), sizeof(XtkMenuItemDesc) * ( size_t ) (desc.item_count ? desc.item_count : 1)
	);
	if (!items) return NULL;
	for (int i = 0; i < desc.item_count; i++) {
		items [i]       = desc.items [i];
		items [i].label = xtk_strdup(ui, items [i].label);
		items [i].icon  = xtk_strdup(ui, items [i].icon);
	}
	desc.items   = items;
	el->dropdown = desc;
	return el;
}

/* Copy a declarative menu-item array into the frame arena. */
XtkMenuItemDesc const *xtk_menu_items_dup(XtkUi *ui, XtkMenuItemDesc const *items, int count) {
	XtkMenuItemDesc *copy = ( XtkMenuItemDesc * ) xtk_arena_alloc(
	  xtk_ui_arena(ui), sizeof(XtkMenuItemDesc) * ( size_t ) (count ? count : 1)
	);
	if (!copy) return NULL;
	for (int i = 0; i < count; i++) {
		copy [i]       = items [i];
		copy [i].label = xtk_strdup(ui, copy [i].label);
		copy [i].icon  = xtk_strdup(ui, copy [i].icon);
	}
	return copy;
}

XtkEl *xtk_split_button(XtkUi *ui, char const *label, XtkSplitDesc desc) {
	XtkEl *el = xtk_el_new(ui, XTK_CONTROL_SPLIT_BUTTON, label);
	if (!el) return NULL;
	desc.icon = xtk_strdup(ui, desc.icon);
	if (desc.item_count < 0) desc.item_count = 0;
	desc.items = xtk_menu_items_dup(ui, desc.items, desc.item_count);
	if (desc.item_count > 0 && !desc.items) return NULL;
	el->split = desc;
	return el;
}

XtkEl *xtk_menu_bar(XtkUi *ui, XtkMenuBarDesc desc) {
	XtkEl *el = xtk_el_new(ui, XTK_CONTROL_MENU_BAR, NULL);
	if (!el) return NULL;
	if (desc.menu_count < 0) desc.menu_count = 0;
	XtkMenuDesc *menus = ( XtkMenuDesc * ) xtk_arena_alloc(
	  xtk_ui_arena(ui), sizeof(XtkMenuDesc) * ( size_t ) (desc.menu_count ? desc.menu_count : 1)
	);
	if (!menus) return NULL;
	for (int i = 0; i < desc.menu_count; i++) {
		menus [i]       = desc.menus [i];
		menus [i].title = xtk_strdup(ui, menus [i].title);
		if (menus [i].item_count < 0) menus [i].item_count = 0;
		menus [i].items = xtk_menu_items_dup(ui, menus [i].items, menus [i].item_count);
	}
	desc.menus   = menus;
	el->menu_bar = desc;
	return el;
}

XtkEl *xtk_tab_view(XtkUi *ui, XtkTabViewDesc desc, XtkEl *children []) {
	XtkEl *el = xtk_el_new(ui, XTK_CONTROL_TAB_VIEW, NULL);
	if (!el) return NULL;
	if (desc.tab_count < 0) desc.tab_count = 0;
	XtkTabDesc *tabs = ( XtkTabDesc * ) xtk_arena_alloc(
	  xtk_ui_arena(ui), sizeof(XtkTabDesc) * ( size_t ) (desc.tab_count ? desc.tab_count : 1)
	);
	if (!tabs) return NULL;
	for (int i = 0; i < desc.tab_count; i++) {
		tabs [i]       = desc.tabs [i];
		tabs [i].icon  = xtk_strdup(ui, tabs [i].icon);
		tabs [i].label = xtk_strdup(ui, tabs [i].label);
	}
	desc.tabs    = tabs;
	el->tab_view = desc;
	xtk_el_adopt(ui, el, children);
	return el;
}

XtkEl *xtk_content_dialog(XtkUi *ui, char const *title, XtkDialogDesc desc, XtkEl *children []) {
	XtkEl *el = xtk_el_new(ui, XTK_CONTROL_CONTENT_DIALOG, title);
	if (!el) return NULL;
	desc.primary   = xtk_strdup(ui, desc.primary);
	desc.secondary = xtk_strdup(ui, desc.secondary);
	desc.close     = xtk_strdup(ui, desc.close);
	if (desc.width <= 0.0f) desc.width = 400.0f;
	if (desc.content_height <= 0.0f) desc.content_height = 120.0f;
	el->dialog = desc;
	xtk_el_adopt(ui, el, children);
	return el;
}

static XtkEl *xtk_stack(XtkUi *ui, XtkControlType type, bool row, XtkStackDesc desc, XtkEl *children []) {
	XtkEl *el = xtk_el_new(ui, type, NULL);
	if (!el) return NULL;
	el->stack_row = row;
	el->stack     = desc;
	xtk_el_adopt(ui, el, children);
	return el;
}

XtkEl *xtk_column(XtkUi *ui, XtkStackDesc desc, XtkEl *children []) {
	return xtk_stack(ui, XTK_CONTROL_CONTAINER, false, desc, children);
}

XtkEl *xtk_row(XtkUi *ui, XtkStackDesc desc, XtkEl *children []) {
	return xtk_stack(ui, XTK_CONTROL_CONTAINER, true, desc, children);
}

/* A zero desc means "default WinUI card chrome", not a zero-padded card. */
XtkEl *xtk_card(XtkUi *ui, XtkStackDesc desc, XtkEl *children []) {
	XentInsets const none = {0};
	if (memcmp(&desc.padding, &none, sizeof(none)) == 0) desc.padding = (XentInsets) {16.0f, 16.0f, 16.0f, 16.0f};
	if (desc.gap == 0.0f) desc.gap = 8.0f;
	return xtk_stack(ui, XTK_CONTROL_CARD, false, desc, children);
}

XtkEl *xtk_scroll(XtkUi *ui, XtkEl *children []) {
	return xtk_stack(
	  ui, XTK_CONTROL_SCROLL, false, (XtkStackDesc) {.fill = true, .align = XENT_FLEX_ALIGN_STRETCH}, children
	);
}

XtkEl *xtk_expander(XtkUi *ui, char const *header, XtkExpanderDesc desc, XtkEl *children []) {
	XtkEl *el = xtk_el_new(ui, XTK_CONTROL_EXPANDER, header);
	if (!el) return NULL;
	if (desc.width <= 0.0f) desc.width = 600.0f;
	if (desc.content_height <= 0.0f) desc.content_height = 120.0f;
	el->expander = desc;
	xtk_el_adopt(ui, el, children);
	return el;
}

XtkEl *xtk_nav_view(XtkUi *ui, XtkNavDesc desc, XtkEl *children []) {
	XtkEl *el = xtk_el_new(ui, XTK_CONTROL_NAV_VIEW, NULL);
	if (!el) return NULL;
	if (desc.item_count < 0) desc.item_count = 0;
	XtkNavItemDesc *items = ( XtkNavItemDesc * ) xtk_arena_alloc(
	  xtk_ui_arena(ui), sizeof(XtkNavItemDesc) * ( size_t ) (desc.item_count ? desc.item_count : 1)
	);
	if (!items) return NULL;
	for (int i = 0; i < desc.item_count; i++) {
		items [i]       = desc.items [i];
		items [i].icon  = xtk_strdup(ui, items [i].icon);
		items [i].label = xtk_strdup(ui, items [i].label);
	}
	desc.items = items;
	el->nav    = desc;
	xtk_el_adopt(ui, el, children);
	return el;
}
