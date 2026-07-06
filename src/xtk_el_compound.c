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

static XtkEl *xtk_split_el(XtkUi *ui, XtkControlType type, char const *label, XtkSplitDesc desc) {
	XtkEl *el = xtk_el_new(ui, type, label);
	if (!el) return NULL;
	desc.icon = xtk_strdup(ui, desc.icon);
	if (desc.item_count < 0) desc.item_count = 0;
	desc.items = xtk_menu_items_dup(ui, desc.items, desc.item_count);
	if (desc.item_count > 0 && !desc.items) return NULL;
	el->split = desc;
	return el;
}

XtkEl *xtk_split_button(XtkUi *ui, char const *label, XtkSplitDesc desc) {
	return xtk_split_el(ui, XTK_CONTROL_SPLIT_BUTTON, label, desc);
}

/* ToggleSplitButton shares XtkSplitDesc; the .checked/.on_toggle fields drive
 * the primary-zone toggle instead of .on_click. */
XtkEl *xtk_toggle_split_button(XtkUi *ui, char const *label, XtkSplitDesc desc) {
	return xtk_split_el(ui, XTK_CONTROL_TOGGLE_SPLIT_BUTTON, label, desc);
}

XtkEl *xtk_radio_buttons(XtkUi *ui, XtkRadioButtonsDesc desc) {
	XtkEl *el = xtk_el_new(ui, XTK_CONTROL_RADIO_BUTTONS, NULL);
	if (!el) return NULL;
	desc.header = xtk_strdup(ui, desc.header);
	if (desc.item_count < 0) desc.item_count = 0;
	XtkRadioItem *items = ( XtkRadioItem * ) xtk_arena_alloc(
	  xtk_ui_arena(ui), sizeof(XtkRadioItem) * ( size_t ) (desc.item_count ? desc.item_count : 1)
	);
	if (!items) return NULL;
	for (int i = 0; i < desc.item_count; i++) {
		items [i]       = desc.items [i];
		items [i].label = xtk_strdup(ui, desc.items [i].label);
	}
	desc.items         = items;
	el->radio_buttons  = desc;
	return el;
}

XtkEl *xtk_breadcrumb_bar(XtkUi *ui, XtkBreadcrumbDesc desc) {
	XtkEl *el = xtk_el_new(ui, XTK_CONTROL_BREADCRUMB_BAR, NULL);
	if (!el) return NULL;
	if (desc.count < 0) desc.count = 0;
	char const **items
	  = ( char const ** ) xtk_arena_alloc(xtk_ui_arena(ui), sizeof(char *) * ( size_t ) (desc.count ? desc.count : 1));
	if (!items) return NULL;
	for (int i = 0; i < desc.count; i++) items [i] = xtk_strdup(ui, desc.items [i]);
	desc.items     = items;
	el->breadcrumb = desc;
	return el;
}

XtkEl *xtk_selector_bar(XtkUi *ui, XtkSelectorBarDesc desc) {
	XtkEl *el = xtk_el_new(ui, XTK_CONTROL_SELECTOR_BAR, NULL);
	if (!el) return NULL;
	if (desc.item_count < 0) desc.item_count = 0;
	XtkSelectorItem *items = ( XtkSelectorItem * ) xtk_arena_alloc(
	  xtk_ui_arena(ui), sizeof(XtkSelectorItem) * ( size_t ) (desc.item_count ? desc.item_count : 1)
	);
	if (!items) return NULL;
	for (int i = 0; i < desc.item_count; i++) {
		items [i]      = desc.items [i];
		items [i].text = xtk_strdup(ui, desc.items [i].text);
		items [i].icon = xtk_strdup(ui, desc.items [i].icon);
	}
	desc.items        = items;
	el->selector_bar  = desc;
	return el;
}

XtkEl *xtk_rating(XtkUi *ui, XtkRatingDesc desc) {
	XtkEl *el = xtk_el_new(ui, XTK_CONTROL_RATING, NULL);
	if (!el) return NULL;
	desc.caption = xtk_strdup(ui, desc.caption);
	el->rating   = desc;
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

XtkEl *xtk_teaching_tip(XtkUi *ui, char const *title, XtkTeachingTipDesc desc, XtkEl *children []) {
	XtkEl *el = xtk_el_new(ui, XTK_CONTROL_TEACHING_TIP, title);
	if (!el) return NULL;
	desc.subtitle    = xtk_strdup(ui, desc.subtitle);
	desc.icon        = xtk_strdup(ui, desc.icon);
	desc.action_text = xtk_strdup(ui, desc.action_text);
	desc.close_text  = xtk_strdup(ui, desc.close_text);
	el->teaching_tip = desc;
	xtk_el_adopt(ui, el, children);
	return el;
}

/* No children here: the reconciler realizes the visible cell window itself
 * (xtk_list_realize), so the desc tree stays O(viewport), not O(count). */
static XtkEl *xtk_items_host(XtkUi *ui, XtkControlType type, XtkListDesc desc) {
	XtkEl *el = xtk_el_new(ui, type, NULL);
	if (!el) return NULL;
	if (desc.count < 0 || !desc.item) desc.count = 0;
	if (desc.item_height <= 0.0f) desc.item_height = 40.0f;
	if (desc.overscan <= 0) desc.overscan = 4;
	el->list = desc;
	return el;
}

XtkEl *xtk_list_view(XtkUi *ui, XtkListDesc desc) { return xtk_items_host(ui, XTK_CONTROL_LIST, desc); }

XtkEl *xtk_list_box(XtkUi *ui, XtkListDesc desc) { return xtk_items_host(ui, XTK_CONTROL_LIST_BOX, desc); }

XtkEl *xtk_grid_view(XtkUi *ui, XtkListDesc desc) {
	/* GridView defaults to WinUI's 4px-gapped fixed cells; item_width is
	 * required for wrapping — default to a square cell when omitted. */
	if (desc.item_height <= 0.0f) desc.item_height = 104.0f;
	if (desc.item_width <= 0.0f) desc.item_width = desc.item_height;
	return xtk_items_host(ui, XTK_CONTROL_GRID_VIEW, desc);
}

XtkEl *xtk_items_repeater(XtkUi *ui, XtkListDesc desc) {
	desc.sel_mode = XTK_LIST_SELECT_NONE;
	desc.selected = -1;
	return xtk_items_host(ui, XTK_CONTROL_ITEMS_REPEATER, desc);
}

XtkEl *xtk_items_view(XtkUi *ui, XtkItemsViewDesc desc) {
	XtkListDesc list = {
	  .count                = desc.count,
	  .item_height          = desc.item_height,
	  .item_width           = desc.item_width,
	  .columns              = desc.columns,
	  .overscan             = desc.overscan,
	  .item                 = desc.item,
	  .env                  = desc.env,
	  .sel_mode             = desc.selection_mode,
	  .selected             = desc.selected,
	  .on_select            = desc.on_select,
	  .item_spacing         = desc.item_spacing,
	  .item_invoked_enabled = desc.item_invoked_enabled,
	  .on_invoke            = desc.on_invoke,
	};
	if (list.item_height <= 0.0f) list.item_height = 40.0f;
	if (desc.layout == XTK_ITEMS_LAYOUT_STACK_V) {
		list.columns    = 1;
		list.item_width = 0.0f;
	}
	else if (list.item_width <= 0.0f) {
		list.item_width = list.item_height;
	}
	if (list.item_width > 0.0f) list.item_width += desc.item_spacing;
	list.item_height += desc.item_spacing;

	XtkEl *el = xtk_el_new(ui, XTK_CONTROL_ITEMS_VIEW, NULL);
	if (!el) return NULL;
	if (list.count < 0 || !list.item) list.count = 0;
	if (list.overscan <= 0) list.overscan = 4;
	el->list = list;
	return el;
}

static XtkTreeNodeDesc const *xtk_tree_nodes_dup(XtkUi *ui, XtkTreeNodeDesc const *nodes, int32_t count) {
	if (!nodes || count <= 0) return NULL;
	XtkTreeNodeDesc *copy = ( XtkTreeNodeDesc * ) xtk_arena_alloc(xtk_ui_arena(ui), sizeof(*copy) * ( size_t ) count);
	if (!copy) return NULL;
	for (int32_t i = 0; i < count; i++) {
		copy [i]          = nodes [i];
		copy [i].text     = xtk_strdup(ui, nodes [i].text);
		copy [i].icon     = xtk_strdup(ui, nodes [i].icon);
		copy [i].children = xtk_tree_nodes_dup(ui, nodes [i].children, nodes [i].child_count);
		if (!copy [i].children) copy [i].child_count = 0;
	}
	return copy;
}

XtkEl *xtk_tree_view(XtkUi *ui, XtkTreeDesc desc) {
	XtkEl *el = xtk_el_new(ui, XTK_CONTROL_TREE_VIEW, NULL);
	if (!el) return NULL;
	if (desc.row_height <= 0.0f) desc.row_height = 28.0f;
	desc.roots = xtk_tree_nodes_dup(ui, desc.roots, desc.root_count);
	if (!desc.roots) desc.root_count = 0;
	el->tree_view = desc;
	return el;
}

XtkEl *xtk_flip_view(XtkUi *ui, XtkFlipDesc desc, XtkEl *children []) {
	XtkEl *el = xtk_el_new(ui, XTK_CONTROL_FLIP_VIEW, NULL);
	if (!el) return NULL;
	el->flip = desc;
	xtk_el_adopt(ui, el, children);
	return el;
}

XtkEl *xtk_pips_pager(XtkUi *ui, XtkPipsDesc desc) {
	XtkEl *el = xtk_el_new(ui, XTK_CONTROL_PIPS_PAGER, NULL);
	if (!el) return NULL;
	if (desc.count < 0) desc.count = 0;
	if (desc.max_visible <= 0) desc.max_visible = 5;
	el->pips = desc;
	return el;
}

XtkEl *xtk_person_picture(XtkUi *ui, XtkPersonPictureDesc desc) {
	XtkEl *el = xtk_el_new(ui, XTK_CONTROL_PERSON_PICTURE, NULL);
	if (!el) return NULL;
	desc.display_name  = xtk_strdup(ui, desc.display_name);
	desc.initials      = xtk_strdup(ui, desc.initials);
	desc.image         = xtk_strdup(ui, desc.image);
	desc.badge_glyph   = xtk_strdup(ui, desc.badge_glyph);
	el->person_picture = desc;
	return el;
}

XtkEl *xtk_split_view(XtkUi *ui, XtkSplitViewDesc desc, XtkEl *pane, XtkEl *content) {
	XtkEl *el = xtk_el_new(ui, XTK_CONTROL_SPLIT_VIEW, NULL);
	if (!el) return NULL;
	el->split_view = desc;

	/* Internal wrappers: content mounts first (drawn under), pane second (on top
	 * for overlay). The SplitView positions the two wrappers each frame. */
	XtkEl *cw = xtk_el_new(ui, XTK_CONTROL_SPLIT_VIEW_CONTENT, NULL);
	XtkEl *pw = xtk_el_new(ui, XTK_CONTROL_SPLIT_VIEW_PANE, NULL);
	if (!cw || !pw) return NULL;
	if (content) xtk_el_adopt(ui, cw, (XtkEl *[]) {content, XTK_END});
	if (pane) xtk_el_adopt(ui, pw, (XtkEl *[]) {pane, XTK_END});
	xtk_el_adopt(ui, el, (XtkEl *[]) {cw, pw, XTK_END});
	return el;
}

XtkEl *xtk_pager(XtkUi *ui, XtkPagerDesc desc) {
	XtkEl *el = xtk_el_new(ui, XTK_CONTROL_PAGER, NULL);
	if (!el) return NULL;
	if (desc.count < 1) desc.count = 1;
	if (desc.selected < 0) desc.selected = 0;
	if (desc.selected > desc.count - 1) desc.selected = desc.count - 1;
	desc.prefix = xtk_strdup(ui, desc.prefix);
	desc.suffix = xtk_strdup(ui, desc.suffix);
	el->pager   = desc;
	return el;
}

XtkEl *xtk_auto_suggest(XtkUi *ui, char const *placeholder, XtkAutoSuggestDesc desc) {
	XtkEl *el = xtk_el_new(ui, XTK_CONTROL_AUTO_SUGGEST, placeholder);
	if (!el) return NULL;
	desc.content    = xtk_strdup(ui, desc.content);
	desc.query_icon = xtk_strdup(ui, desc.query_icon);
	if (desc.count < 0) desc.count = 0;
	char const **items
	  = ( char const ** ) xtk_arena_alloc(xtk_ui_arena(ui), sizeof(char *) * ( size_t ) (desc.count ? desc.count : 1));
	if (!items) return NULL;
	for (int i = 0; i < desc.count; i++) items [i] = xtk_strdup(ui, desc.suggestions [i]);
	desc.suggestions = items;
	el->suggest      = desc;
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

XtkEl *xtk_refresh_container(XtkUi *ui, XtkRefreshDesc desc, XtkEl *children []) {
	XtkEl *el = xtk_el_new(ui, XTK_CONTROL_REFRESH, NULL);
	if (!el) return NULL;
	el->refresh = desc;
	xtk_el_adopt(ui, el, children);
	return el;
}
