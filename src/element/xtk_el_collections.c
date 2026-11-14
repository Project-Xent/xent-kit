#include "xtk_internal.h"

#include <string.h>

static XtkEl *items_host(XtkUi *ui, XtkCtrlType type, XtkListDesc desc) {
	XtkEl *el = xtk_el_new(ui, type, NULL);
	if (!el) return NULL;
	if (desc.nitem < 0 || !desc.item) desc.nitem = 0;
	if (desc.itemh <= 0.0f) desc.itemh = 40.0f;
	if (!XTK_EL_STORE(el, desc)) return NULL;
	XTK_EL_DATA(el)->virtualized = true;
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
	desc.roots = tree_nodes_dup(ui, desc.roots, desc.nroot);
	if (!desc.roots) desc.nroot = 0;
	if (!XTK_EL_STORE(el, desc)) return NULL;
	return el;
}
