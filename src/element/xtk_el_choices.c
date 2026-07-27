#include "xtk_internal.h"

#include <string.h>

static XtkEl *menu_item_el(XtkUi *ui, XtkMenuItemDesc const *desc) {
	XtkEl *el = xtk_el_new(ui, XTK_CTRL_MENUITEM, desc->label);
	if (!el) return NULL;
	XtkMenuItemDetail detail = {.icon = xtk_strdup(ui, desc->icon), .disabled = desc->disabled, .click = desc->click};
	if (!XTK_EL_STORE(el, detail)) return NULL;
	return el;
}

static XtkEl *menu_flyout_el(XtkUi *ui, char const *title, XtkMenuItemDesc const *items, int count) {
	XtkEl *flyout = xtk_el_new(ui, XTK_CTRL_MENUFLY, title);
	if (!flyout) return NULL;
	XtkEl **children
	  = ( XtkEl ** ) xtk_arena_alloc(xtk_ui_arena(ui), sizeof(*children) * ( size_t ) (count ? count : 1));
	if (!children) return NULL;
	for (int i = 0; i < count; i++) {
		children [i] = menu_item_el(ui, &items [i]);
		if (!children [i]) return NULL;
	}
	return xtk_el_set_children(flyout, children, count) ? flyout : NULL;
}

XtkEl *xtk_combo(XtkUi *ui, char const *placeholder, XtkComboDesc desc) {
	XtkEl *el = xtk_el_new(ui, XTK_CTRL_COMBO, placeholder);
	if (!el) return NULL;
	if (desc.nitem < 0) desc.nitem = 0;
	char const **items
	  = ( char const ** ) xtk_arena_alloc(xtk_ui_arena(ui), sizeof(char *) * ( size_t ) (desc.nitem ? desc.nitem : 1));
	if (!items) return NULL;
	for (int i = 0; i < desc.nitem; i++) items [i] = xtk_strdup(ui, desc.items [i]);
	desc.items = items;
	if (!XTK_EL_STORE(el, desc)) return NULL;
	return el;
}

XtkEl *xtk_number(XtkUi *ui, XtkNumberDesc desc) {
	XtkEl *el = xtk_el_new(ui, XTK_CTRL_NUMBER, NULL);
	if (!el) return NULL;
	if (desc.max == 0.0 && desc.min == 0.0) desc.max = 100.0;
	if (desc.step == 0.0) desc.step = 1.0;
	if (!XTK_EL_STORE(el, desc)) return NULL;
	return el;
}

XtkEl *xtk_dropdown(XtkUi *ui, char const *label, XtkDropdownDesc desc) {
	XtkEl *el = xtk_el_new(ui, XTK_CTRL_DROPDOWN, label);
	if (!el) return NULL;
	desc.icon = xtk_strdup(ui, desc.icon);
	if (desc.nitem < 0) desc.nitem = 0;
	XtkMenuItemDesc *items = ( XtkMenuItemDesc * ) xtk_arena_alloc(
	  xtk_ui_arena(ui), sizeof(XtkMenuItemDesc) * ( size_t ) (desc.nitem ? desc.nitem : 1)
	);
	if (!items) return NULL;
	for (int i = 0; i < desc.nitem; i++) {
		items [i]       = desc.items [i];
		items [i].label = xtk_strdup(ui, items [i].label);
		items [i].icon  = xtk_strdup(ui, items [i].icon);
	}
	desc.items = items;
	if (!XTK_EL_STORE(el, desc)) return NULL;
	XtkEl *flyout = menu_flyout_el(ui, NULL, desc.items, desc.nitem);
	if (!flyout || !xtk_el_set_children(el, &flyout, 1)) return NULL;
	return el;
}

static XtkMenuItemDesc const *menu_items_dup(XtkUi *ui, XtkMenuItemDesc const *items, int count) {
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

static XtkEl *split_el(XtkUi *ui, XtkCtrlType type, char const *label, XtkSplitDesc desc) {
	XtkEl *el = xtk_el_new(ui, type, label);
	if (!el) return NULL;
	desc.icon = xtk_strdup(ui, desc.icon);
	if (desc.nitem < 0) desc.nitem = 0;
	desc.items = menu_items_dup(ui, desc.items, desc.nitem);
	if (desc.nitem > 0 && !desc.items) return NULL;
	if (!XTK_EL_STORE(el, desc)) return NULL;
	XtkEl *flyout = menu_flyout_el(ui, NULL, desc.items, desc.nitem);
	if (!flyout || !xtk_el_set_children(el, &flyout, 1)) return NULL;
	return el;
}

XtkEl *xtk_split(XtkUi *ui, char const *label, XtkSplitDesc desc) { return split_el(ui, XTK_CTRL_SPLIT, label, desc); }

/* ToggleSplitButton shares XtkSplitDesc; the .checked/.on_toggle fields drive
 * the primary-zone toggle instead of .click. */
XtkEl *xtk_togglesplit(XtkUi *ui, char const *label, XtkSplitDesc desc) {
	return split_el(ui, XTK_CTRL_TOGGLESPLIT, label, desc);
}

XtkEl *xtk_radiogroup(XtkUi *ui, XtkRadioButtonsDesc desc) {
	XtkEl *el = xtk_el_new(ui, XTK_CTRL_RADIOGROUP, NULL);
	if (!el) return NULL;
	desc.header = xtk_strdup(ui, desc.header);
	if (desc.nitem < 0) desc.nitem = 0;
	XtkRadioItem *items = ( XtkRadioItem * ) xtk_arena_alloc(
	  xtk_ui_arena(ui), sizeof(XtkRadioItem) * ( size_t ) (desc.nitem ? desc.nitem : 1)
	);
	if (!items) return NULL;
	for (int i = 0; i < desc.nitem; i++) {
		items [i]       = desc.items [i];
		items [i].label = xtk_strdup(ui, desc.items [i].label);
	}
	desc.items = items;
	if (!XTK_EL_STORE(el, desc)) return NULL;
	return el;
}

XtkEl *xtk_breadcrumb(XtkUi *ui, XtkBreadcrumbDesc desc) {
	XtkEl *el = xtk_el_new(ui, XTK_CTRL_BREADCRUMB, NULL);
	if (!el) return NULL;
	if (desc.nitem < 0) desc.nitem = 0;
	char const **items
	  = ( char const ** ) xtk_arena_alloc(xtk_ui_arena(ui), sizeof(char *) * ( size_t ) (desc.nitem ? desc.nitem : 1));
	if (!items) return NULL;
	for (int i = 0; i < desc.nitem; i++) items [i] = xtk_strdup(ui, desc.items [i]);
	desc.items = items;
	if (!XTK_EL_STORE(el, desc)) return NULL;
	return el;
}

XtkEl *xtk_selector(XtkUi *ui, XtkSelectorBarDesc desc) {
	XtkEl *el = xtk_el_new(ui, XTK_CTRL_SELECTOR, NULL);
	if (!el) return NULL;
	if (desc.nitem < 0) desc.nitem = 0;
	XtkSelectorItem *items = ( XtkSelectorItem * ) xtk_arena_alloc(
	  xtk_ui_arena(ui), sizeof(XtkSelectorItem) * ( size_t ) (desc.nitem ? desc.nitem : 1)
	);
	if (!items) return NULL;
	for (int i = 0; i < desc.nitem; i++) {
		items [i]      = desc.items [i];
		items [i].text = xtk_strdup(ui, desc.items [i].text);
		items [i].icon = xtk_strdup(ui, desc.items [i].icon);
	}
	desc.items = items;
	if (!XTK_EL_STORE(el, desc)) return NULL;
	return el;
}

XtkEl *xtk_rating(XtkUi *ui, XtkRatingDesc desc) {
	XtkEl *el = xtk_el_new(ui, XTK_CTRL_RATING, NULL);
	if (!el) return NULL;
	desc.caption = xtk_strdup(ui, desc.caption);
	if (!XTK_EL_STORE(el, desc)) return NULL;
	return el;
}

static XtkMenuDesc *menu_descs_dup(XtkUi *ui, XtkMenuBarDesc *desc) {
	XtkMenuDesc *menus = ( XtkMenuDesc * ) xtk_arena_alloc(
	  xtk_ui_arena(ui), sizeof(XtkMenuDesc) * ( size_t ) (desc->nmenu ? desc->nmenu : 1)
	);
	if (!menus) return NULL;
	for (int i = 0; i < desc->nmenu; i++) {
		menus [i]       = desc->menus [i];
		menus [i].title = xtk_strdup(ui, menus [i].title);
		if (menus [i].nitem < 0) menus [i].nitem = 0;
		menus [i].items = menu_items_dup(ui, menus [i].items, menus [i].nitem);
	}
	return menus;
}

static bool menubar_set_flyouts(XtkUi *ui, XtkEl *el, XtkMenuBarDesc const *desc) {
	XtkEl **flyouts
	  = ( XtkEl ** ) xtk_arena_alloc(xtk_ui_arena(ui), sizeof(*flyouts) * ( size_t ) (desc->nmenu ? desc->nmenu : 1));
	if (!flyouts) return false;
	for (int i = 0; i < desc->nmenu; i++) {
		flyouts [i] = menu_flyout_el(ui, desc->menus [i].title, desc->menus [i].items, desc->menus [i].nitem);
		if (!flyouts [i]) return false;
	}
	return xtk_el_set_children(el, flyouts, desc->nmenu);
}

XtkEl *xtk_menubar(XtkUi *ui, XtkMenuBarDesc desc) {
	XtkEl *el = xtk_el_new(ui, XTK_CTRL_MENUBAR, NULL);
	if (!el) return NULL;
	if (desc.nmenu < 0) desc.nmenu = 0;
	desc.menus = menu_descs_dup(ui, &desc);
	if (!desc.menus || !XTK_EL_STORE(el, desc)) return NULL;
	if (!menubar_set_flyouts(ui, el, &desc)) return NULL;
	return el;
}
