#include "xtk_reconcile_internal.h"

#include "xtk_internal.h"

#include <math.h>

int xtk_list_autocolumns(float cross, float itemw, int explicit_columns) {
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

static void list_window_fallback(XtkEl const *el, XtkListDesc const *list, XtkRealized *w) {
	float extent = isnan(XTK_EL_DATA(el)->height) ? 600.0f : XTK_EL_DATA(el)->height;
	float cross  = isnan(XTK_EL_DATA(el)->width) ? 0.0f : XTK_EL_DATA(el)->width;
	w->lanes     = xtk_list_autocolumns(cross, list->itemw, list->ncol);
	w->first     = 0;
	float pitch  = list->itemh > 0.0f ? list->itemh : 40.0f;
	w->last      = (( int ) ceilf(extent / pitch) + 4) * w->lanes - 1;
}

static int  list_rows(XtkListDesc const *list) { return list->nitem + list->ngroup; }

static void list_window(XtkNode const *committed, XtkEl const *el, XtkRealized *w) {
	XtkListDesc const *list = XTK_EL_DETAIL(el, XtkListDesc);
	XtkBinding const  *b    = committed ? committed->binding : NULL;
	if (b && b->realized.lanes > 0) *w = b->realized;
	else list_window_fallback(el, list, w);
	if (w->last <= list_rows(list) - 1) return;
	int span  = w->last - w->first;
	w->last   = list_rows(list) - 1;
	w->first  = w->last - span > 0 ? w->last - span : 0;
	if (!list->ngroup) w->first -= w->first % w->lanes;
}

static bool list_attach(XtkEl *wrap, XtkEl *content) {
	if (!content) return true;
	XtkEl *child [] = {content};
	return xtk_el_set_children(wrap, child, 1);
}

typedef struct ListRealizeCtx {
	XtkListKind kind;
	bool        single;
	float       cell_width;
	int         window;
	XtkRealized range;
} ListRealizeCtx;

static XtkEl *list_make_header(XtkRt *rt, XtkListDesc const *list, int group) {
	XtkEl *head = xtk_el_new(rt->ui, XTK_CTRL_GROUPHEADER, NULL);
	if (!head) return NULL;
	xtk_keyed_u64(head, (1ull << 62u) | ( uint64_t ) group);
	return list_attach(head, list->group_header(rt->ui, list->env, group)) ? head : NULL;
}

static XtkEl *list_make_row(XtkRt *rt, XtkEl const *el, ListRealizeCtx const *ctx, int r) {
	XtkListDesc list = *XTK_EL_DETAIL(el, XtkListDesc);
	XtkListRow  at   = list.ngroup ? xtk_list_row(list.groups, list.ngroup, r) : (XtkListRow) {-1, r};
	if (at.item < 0) return list_make_header(rt, &list, at.group);
	int    i   = at.item;
	XtkEl *row = xtk_el_new(rt->ui, XTK_CTRL_LISTITEM, NULL);
	if (!row) return NULL;
	xtk_keyed_u64(row, ( uint64_t ) (ctx->window ? r % ctx->window : 0));
	if (list.itemh > 0.0f) XTK_EL_DATA(row)->height = list.itemh;
	if (ctx->cell_width > 0.0f) XTK_EL_DATA(row)->width = ctx->cell_width;
	XtkListItemDesc item = {
	  .index    = i,
	  .kind     = ctx->kind,
	  .selected = ctx->single && i == list.sel,
	  .multi    = list.sel_mode == XTK_LIST_SELECT_MULTIPLE,
	};
	if (!XTK_EL_STORE(row, item)) return NULL;
	if (!list_attach(row, list.item(rt->ui, list.env, i))) return NULL;
	return row;
}

static void list_realize_ctx(XtkNode const *committed, XtkEl const *el, ListRealizeCtx *ctx) {
	XtkListDesc const *list = XTK_EL_DETAIL(el, XtkListDesc);
	ctx->range              = (XtkRealized) {0, -1, 1};
	if (list_rows(list) > 0 && list->item) list_window(committed, el, &ctx->range);
	ctx->window = ctx->range.last - ctx->range.first + 1;
	if (ctx->window < 0) ctx->window = 0;
	ctx->kind       = list_kind_for(XTK_EL_DATA(el)->type);
	ctx->single     = list->sel_mode == XTK_LIST_SELECT_SINGLE;
	ctx->cell_width = ctx->range.lanes > 1 || list->itemw > 0.0f ? list->itemw : 0.0f;
}

static int list_detached(XtkListDesc const *list, int first) {
	if (!list->ngroup || first > list_rows(list) - 1) return -1;
	XtkListRow at = xtk_list_row(list->groups, list->ngroup, first);
	return at.item >= 0 ? at.group : -1;
}

static int list_fill_rows(XtkRt *rt, XtkEl const *el, ListRealizeCtx const *ctx, XtkEl **rows) {
	XtkListDesc const *list     = XTK_EL_DETAIL(el, XtkListDesc);
	int                filled   = 0;
	int                detached = ctx->window > 0 ? list_detached(list, ctx->range.first) : -1;
	if (list->header) rows [filled++] = xtk_keyed(rt->ui, "header", list->header);
	XtkEl *head = detached >= 0 ? list_make_header(rt, list, detached) : NULL;
	if (head) rows [filled++] = head;
	for (int i = ctx->range.first; i <= ctx->range.last; i++) {
		XtkEl *row = list_make_row(rt, el, ctx, i);
		if (!row) break;
		rows [filled++] = row;
	}
	return filled;
}

static bool list_realize(XtkRt *rt, XtkNode const *committed, XtkEl *el) {
	ListRealizeCtx ctx;
	list_realize_ctx(committed, el, &ctx);
	XTK_EL_DATA(el)->virtual_first = ctx.range.first;
	size_t  n                      = ( size_t ) (ctx.window ? ctx.window : 1) + 2u;
	XtkEl **rows                   = ( XtkEl ** ) xtk_arena_alloc(xtk_ui_arena(rt->ui), sizeof(XtkEl *) * n);
	if (!rows) return false;
	return xtk_el_set_children(el, rows, list_fill_rows(rt, el, &ctx, rows));
}

static XtkNode *committed_child(XtkNode *parent, XtkEl const *want, int index) {
	if (!parent || !want || index < 0 || index >= parent->child_count) return NULL;
	XtkNode *n = parent->children [index];
	return n && n->type_id == XTK_EL_DATA(want)->type ? n : NULL;
}

static bool normalize_lists(XtkRt *rt, XtkEl *el, XtkNode *committed) {
	if (!el) return true;
	if (XTK_EL_DATA(el)->virtualized && !list_realize(rt, committed, el)) return false;
	for (int i = 0; i < XTK_EL_DATA(el)->child_count; i++) {
		XtkNode *child = committed_child(committed, xtk_el_child(el, i), i);
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
