#include "xtk_internal.h"

#include <string.h>

XtkListRow xtk_list_row(int32_t const *groups, int32_t ngroup, int32_t row) {
	int32_t item = 0;
	for (int32_t g = 0; g < ngroup; g++) {
		int32_t size = groups [g] > 0 ? groups [g] : 0;
		if (row == 0) return (XtkListRow) {g, -1};
		if (row <= size) return (XtkListRow) {g, item + row - 1};
		row  -= 1 + size;
		item += size;
	}
	return (XtkListRow) {-1, row + item};
}

static bool list_groups_copy(XtkUi *ui, XtkListDesc *desc) {
	if (desc->ngroup <= 0 || !desc->groups || !desc->group_header) {
		desc->groups = NULL;
		desc->ngroup = 0;
		return true;
	}
	if (xtk_model_ver_valid(desc->version)) {
		desc->nitem = 0;
		for (int g = 0; g < desc->ngroup; g++) desc->nitem += desc->groups [g] > 0 ? desc->groups [g] : 0;
		return true;
	}
	int32_t *copy = ( int32_t * ) xtk_arena_alloc(xtk_ui_arena(ui), sizeof(*copy) * ( size_t ) desc->ngroup);
	if (!copy) return false;
	desc->nitem = 0;
	for (int g = 0; g < desc->ngroup; g++) {
		copy [g]     = desc->groups [g] > 0 ? desc->groups [g] : 0;
		desc->nitem += copy [g];
	}
	desc->groups = copy;
	return true;
}

static bool list_names_copy(XtkUi *ui, XtkListDesc *desc) {
	if (desc->nname <= 0 || !desc->names) {
		desc->names = NULL;
		desc->nname = 0;
		return true;
	}
	if (xtk_model_ver_valid(desc->version)) return true;
	char const **copy = ( char const ** ) xtk_arena_alloc(xtk_ui_arena(ui), sizeof(*copy) * ( size_t ) desc->nname);
	if (!copy) return false;
	for (int i = 0; i < desc->nname; i++) copy [i] = xtk_strdup(ui, desc->names [i]);
	desc->names = copy;
	return true;
}

static XtkEl *items_host(XtkUi *ui, XtkCtrlType type, XtkListDesc desc) {
	XtkEl *el = xtk_el_new(ui, type, NULL);
	if (!el) return NULL;
	if (desc.nitem < 0 || !desc.item) desc.nitem = 0;
	if (!list_groups_copy(ui, &desc) || !list_names_copy(ui, &desc)) return NULL;
	if (desc.itemh < 0.0f) desc.itemh = 0.0f;
	if (!XTK_EL_STORE(el, desc)) return NULL;
	XTK_EL_DATA(el)->virtualized = true;
	ui->composition.has_lists    = true;
	return el;
}

XtkEl *xtk_list(XtkUi *ui, XtkListDesc desc) { return items_host(ui, XTK_CTRL_LIST, desc); }

XtkEl *xtk_listbox(XtkUi *ui, XtkListDesc desc) { return items_host(ui, XTK_CTRL_LISTBOX, desc); }

XtkEl *xtk_gridview(XtkUi *ui, XtkListDesc desc) {
	if (desc.itemh <= 0.0f) desc.itemh = 104.0f;
	if (desc.itemw <= 0.0f) desc.itemw = desc.itemh;
	return items_host(ui, XTK_CTRL_GRIDVIEW, desc);
}

XtkEl *xtk_repeater(XtkUi *ui, XtkListDesc desc) {
	desc.sel_mode = XTK_LIST_SELECT_NONE;
	desc.sel      = -1;
	return items_host(ui, XTK_CTRL_REPEATER, desc);
}

static XtkListDesc itemsview_list_desc(XtkItemsViewDesc const *desc) {
	XtkListDesc list = {
	  .nitem                = desc->nitem,
	  .itemh                = desc->itemh,
	  .itemw                = desc->itemw,
	  .ncol                 = desc->ncol,
	  .item                 = desc->item,
	  .env                  = desc->env,
	  .sel_mode             = desc->selection_mode,
	  .sel                  = desc->sel,
	  .select               = desc->select,
	  .gap                  = desc->gap,
	  .item_invoked_enabled = desc->item_invoked_enabled,
	  .invoke               = desc->invoke,
	};
	if (list.itemh <= 0.0f) list.itemh = 40.0f;
	if (desc->layout == XTK_ITEMS_LAYOUT_STACK_V) {
		list.ncol  = 1;
		list.itemw = 0.0f;
	}
	else if (list.itemw <= 0.0f) { list.itemw = list.itemh; }
	if (list.itemw > 0.0f) list.itemw += desc->gap;
	list.itemh += desc->gap;
	return list;
}

XtkEl *xtk_itemsview(XtkUi *ui, XtkItemsViewDesc desc) {
	return items_host(ui, XTK_CTRL_ITEMSVIEW, itemsview_list_desc(&desc));
}

static XtkTreeNodeDesc const *tree_nodes_dup(XtkUi *ui, XtkTreeNodeDesc const *nodes, int32_t count) {
	if (!nodes || count <= 0) return NULL;
	XtkTreeNodeDesc *copy = ( XtkTreeNodeDesc * ) xtk_arena_alloc(xtk_ui_arena(ui), sizeof(*copy) * ( size_t ) count);
	if (!copy) return NULL;
	for (int32_t i = 0; i < count; i++) {
		copy [i]          = nodes [i];
		copy [i].text     = xtk_strdup(ui, nodes [i].text);
		copy [i].icon     = xtk_strdup(ui, nodes [i].icon);
		copy [i].children = tree_nodes_dup(ui, nodes [i].children, nodes [i].child_count);
		if (!copy [i].children) copy [i].child_count = 0;
	}
	return copy;
}

XtkEl *xtk_tree(XtkUi *ui, XtkTreeDesc desc) {
	XtkEl *el = xtk_el_new(ui, XTK_CTRL_TREE, NULL);
	if (!el) return NULL;
	if (desc.rowh <= 0.0f) desc.rowh = 32.0f;
	if (!desc.roots || desc.nroot <= 0) {
		desc.roots = NULL;
		desc.nroot = 0;
	}
	else if (!xtk_model_ver_valid(desc.version)) {
		desc.roots = tree_nodes_dup(ui, desc.roots, desc.nroot);
		if (!desc.roots) desc.nroot = 0;
	}
	if (!XTK_EL_STORE(el, desc)) return NULL;
	return el;
}
