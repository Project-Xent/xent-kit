#include "xtk_reconcile_internal.h"

#include "xtk_internal.h"

#include <math.h>

int xtk_list_auto_columns(float cross, float itemw, int explicit_columns) {
	if (explicit_columns > 0) return explicit_columns;
	if (itemw <= 0.0f || cross <= 0.0f) return 1;
	int cols = ( int ) floorf(cross / itemw);
	return cols > 0 ? cols : 1;
}

static XtkListKind list_kind_for(XtkCtrlType type) {
	switch (type) {
	case XTK_CTRL_LISTBOX   : return XTK_LIST_KIND_LIST_BOX;
	case XTK_CTRL_GRIDVIEW  : return XTK_LIST_KIND_GRID;
	case XTK_CTRL_REPEATER  : return XTK_LIST_KIND_REPEATER;
	case XTK_CTRL_ITEMSVIEW : return XTK_LIST_KIND_ITEMS;
	default                 : return XTK_LIST_KIND_LIST;
	}
}

static void list_window(XtkRt *rt, XentNodeId node, XtkEl const *el, int *first, int *last, int *cols) {
	XtkListDesc const *list     = XTK_EL_DETAIL(el, XtkListDesc);
	XtkViewport        viewport = {0};
	bool               ok       = rt->cfg.viewport
	                           && node != XENT_NODE_INVALID
	                           && rt->cfg.viewport(rt->cfg.ctx, node, &viewport)
	                           && viewport.extent > 0.0f;
	if (!ok) {
		viewport.offset = 0.0f;
		viewport.extent = isnan(XTK_EL_DATA(el)->height) ? 600.0f : XTK_EL_DATA(el)->height;
		viewport.cross  = isnan(XTK_EL_DATA(el)->width) ? 0.0f : XTK_EL_DATA(el)->width;
	}
	*cols            = xtk_list_auto_columns(viewport.cross, list->itemw, list->ncol);
	int   total_rows = (list->nitem + *cols - 1) / *cols;
	float item_h     = list->itemh;
	float max_offset = ( float ) total_rows * item_h - viewport.extent;
	if (viewport.offset > max_offset) viewport.offset = max_offset;
	if (viewport.offset < 0.0f) viewport.offset = 0.0f;
	int row_first = ( int ) floorf(viewport.offset / item_h) - list->overscan;
	int row_last  = ( int ) ceilf((viewport.offset + viewport.extent) / item_h) - 1 + list->overscan;
	if (row_first < 0) row_first = 0;
	if (row_last > total_rows - 1) row_last = total_rows - 1;
	*first = row_first * *cols;
	*last  = (row_last + 1) * *cols - 1;
	if (*last > list->nitem - 1) *last = list->nitem - 1;
}

static bool list_attach(XtkUi *ui, XtkEl *wrap, XtkEl *content) {
	( void ) ui;
	if (!content) return true;
	XtkEl *child [] = {content};
	return xtk_el_set_children(wrap, child, 1);
}

static XtkEl *list_make_row(
  XtkRt *rt, XtkEl const *el, XtkListKind kind, bool single, float cell_width, int cols, int window, int i
) {
	XtkListDesc list = *XTK_EL_DETAIL(el, XtkListDesc);
	XtkEl      *row  = xtk_el_new(rt->ui, XTK_CTRL_LISTITEM, NULL);
	if (!row) return NULL;
	xtk_keyed_u64(row, ( uint64_t ) (window ? i % window : 0));
	XTK_EL_DATA(row)->height = list.itemh;
	if (cell_width > 0.0f) XTK_EL_DATA(row)->width = cell_width;
	XtkListItemDesc item = {
	  .index    = i,
	  .kind     = kind,
	  .selected = single && i == list.sel,
	  .multi    = list.sel_mode == XTK_LIST_SELECT_MULTIPLE,
	  .x        = ( float ) (i % cols) * cell_width,
	  .y        = ( float ) (i / cols) * list.itemh,
	  .w        = cell_width,
	  .h        = list.itemh,
	};
	if (!XTK_EL_STORE(row, item)) return NULL;
	if (!list_attach(rt->ui, row, list.item(rt->ui, list.env, i))) return NULL;
	return row;
}

typedef struct ListRealizeCtx {
	XtkListKind kind;
	bool        single;
	float       cell_width;
	int         cols;
	int         window;
	int         first;
	int         last;
} ListRealizeCtx;

static void list_realize_ctx(XtkRt *rt, XentNodeId node, XtkEl const *el, ListRealizeCtx *ctx) {
	XtkListDesc const *list = XTK_EL_DETAIL(el, XtkListDesc);
	ctx->first              = 0;
	ctx->last               = -1;
	ctx->cols               = 1;
	if (list->nitem > 0 && list->item) list_window(rt, node, el, &ctx->first, &ctx->last, &ctx->cols);
	ctx->window = ctx->last - ctx->first + 1;
	if (ctx->window < 0) ctx->window = 0;
	ctx->kind       = list_kind_for(XTK_EL_DATA(el)->type);
	ctx->single     = list->sel_mode == XTK_LIST_SELECT_SINGLE;
	ctx->cell_width = ctx->cols > 1 || list->itemw > 0.0f ? list->itemw : 0.0f;
}

static int list_fill_rows(XtkRt *rt, XtkEl const *el, ListRealizeCtx const *ctx, XtkEl **rows) {
	int filled = 0;
	for (int i = ctx->first; i <= ctx->last; i++) {
		XtkEl *row = list_make_row(rt, el, ctx->kind, ctx->single, ctx->cell_width, ctx->cols, ctx->window, i);
		if (!row) break;
		rows [filled++] = row;
	}
	return filled;
}

static bool list_realize(XtkRt *rt, XentNodeId node, XtkEl *el) {
	ListRealizeCtx ctx;
	list_realize_ctx(rt, node, el, &ctx);
	XtkElementData *data = XTK_EL_DATA(el);
	data->virtual_first  = ctx.first;
	data->virtual_last   = ctx.last;
	data->virtual_lanes  = ctx.cols;
	size_t  n            = ( size_t ) (ctx.window ? ctx.window : 1);
	XtkEl **rows         = ( XtkEl ** ) xtk_arena_alloc(xtk_ui_arena(rt->ui), sizeof(XtkEl *) * n);
	if (!rows) return false;
	int filled = list_fill_rows(rt, el, &ctx, rows);
	if (!xtk_el_set_children(el, rows, filled)) return false;
	if (rt->cfg.virtual_range) {
		XtkVirtualRange range = {ctx.first, ctx.first + filled - 1, ctx.cols};
		rt->cfg.virtual_range(rt->cfg.ctx, node, &range);
	}
	return true;
}

static XtkNode *find_child_for_viewport(XtkNode *parent, XtkEl const *want, int index) {
	if (!parent || !want || index < 0 || index >= parent->child_count) return NULL;
	XtkNode *n = parent->children [index];
	return n && n->type_id == XTK_EL_DATA(want)->type ? n : NULL;
}

static bool normalize_lists(XtkRt *rt, XtkEl *el, XtkNode *committed) {
	if (!el) return true;
	if (XTK_EL_DATA(el)->virtualized) {
		XentNodeId id = committed ? committed->node : XENT_NODE_INVALID;
		if (!list_realize(rt, id, el)) return false;
	}
	for (int i = 0; i < XTK_EL_DATA(el)->child_count; i++) {
		XtkNode *child = find_child_for_viewport(committed, xtk_el_child(el, i), i);
		if (!normalize_lists(rt, xtk_el_child(el, i), child)) return false;
	}
	return true;
}

static bool radio_fill_kids(XtkUi *ui, XtkRadioButtonsDesc const *d, XtkEl **kids, int n, int extra) {
	int k = 0;
	if (extra) {
		kids [k] = xtk_text(ui, d->header, (XtkTextDesc) {0});
		if (!kids [k++]) return false;
	}
	for (int i = 0; i < n; i++) {
		kids [k]
		  = xtk_radio(ui, d->items [i].label, (XtkToggleDesc) {.disabled = d->disabled || d->items [i].disabled});
		if (!kids [k++]) return false;
	}
	return true;
}

static bool normalize_radio_buttons(XtkUi *ui, XtkEl *el) {
	if (XTK_EL_DATA(el)->type != XTK_CTRL_RADIOGROUP || XTK_EL_DATA(el)->child_count > 0) return true;
	XtkRadioButtonsDesc d     = *XTK_EL_DETAIL(el, XtkRadioButtonsDesc);
	int                 n     = d.nitem < 0 ? 0 : d.nitem;
	int                 extra = (d.header && d.header [0]) ? 1 : 0;
	int                 total = n + extra;
	XtkEl **kids = ( XtkEl ** ) xtk_arena_alloc(xtk_ui_arena(ui), sizeof(XtkEl *) * ( size_t ) (total > 0 ? total : 1));
	if (!kids) return false;
	if (!radio_fill_kids(ui, &d, kids, n, extra)) return false;
	return xtk_el_set_children(el, kids, n + extra);
}

static bool normalize_one(XtkUi *ui, XtkEl *el) { return normalize_radio_buttons(ui, el); }

static bool normalize_compounds(XtkUi *ui, XtkEl *el) {
	if (!el) return true;
	if (!normalize_one(ui, el)) return false;
	for (int i = 0; i < XTK_EL_DATA(el)->child_count; i++)
		if (!normalize_compounds(ui, xtk_el_child(el, i))) return false;
	return true;
}

bool xtk_normalize_tree(XtkRt *rt, XtkEl *next) {
	return normalize_compounds(rt->ui, next) && normalize_lists(rt, next, rt->root);
}
