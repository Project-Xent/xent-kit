/**
 * @file xtk_reconcile.c
 * @brief XTK reconciler: single-pass keyed diff of the new element tree
 * against the previous frame, applied to retained controls through the
 * XtkBackend vtable.
 */
#include <xtk/xtk_reconcile.h>

#include "xtk_internal.h"

#include <math.h>
#include <stdlib.h>
#include <string.h>

static XtkNode *xtk_node_create(XentNodeId id, void *binding) {
	XtkNode *n = ( XtkNode * ) calloc(1, sizeof(*n));
	if (!n) return NULL;
	n->node    = id;
	n->host    = id;
	n->binding = binding;
	return n;
}

static void xtk_node_free_tree(XtkRuntime *rt, XtkNode *n) {
	if (!n) return;
	for (int i = 0; i < n->child_count; i++) xtk_node_free_tree(rt, n->children [i]);
	rt->backend.node_cleanup(n);
	free(n->children);
	free(n);
}

static bool xtk_node_reserve(XtkNode *n, int count) {
	if (count <= n->child_cap) return true;
	int cap = n->child_cap ? n->child_cap * 2 : 8;
	if (cap < count) cap = count;
	XtkNode **items = ( XtkNode ** ) realloc(n->children, sizeof(XtkNode *) * ( size_t ) cap);
	if (!items) return false;
	n->children  = items;
	n->child_cap = cap;
	return true;
}

static void xtk_list_realize(XtkRuntime *rt, XentNodeId node, XtkEl *el);

static XtkNode *xtk_mount(XtkRuntime *rt, XentNodeId parent, XtkEl const *el) {
	XtkBackend *be = &rt->backend;
	void       *b  = NULL;
	if (be->is_interactive(el)) {
		b = be->binding_create(be->ctx, rt);
		if (!b) return NULL;
	}

	XentNodeId id = be->create(be->ctx, parent, el, b);
	if (id == XENT_NODE_INVALID) {
		free(b);
		return NULL;
	}

	XtkNode *n = xtk_node_create(id, b);
	if (!n) {
		be->destroy(be->ctx, id);
		free(b);
		return NULL;
	}

	be->mount_setup(be->ctx, n, id, el);

	/* Lists synthesize their visible-row children here (el trees are frame-
	 * arena scratch, so completing one in place is fair game). */
	if (xtk_is_list_type(el->type)) xtk_list_realize(rt, id, ( XtkEl * ) el);

	if (el->child_count > 0 && xtk_node_reserve(n, el->child_count)) {
		for (int i = 0; i < el->child_count; i++) n->children [i] = xtk_mount(rt, n->host, el->children [i]);
		n->child_count = el->child_count;
	}
	return n;
}

static void xtk_unmount(XtkRuntime *rt, XtkNode *n) {
	if (!n) return;
	rt->backend.pre_unmount(rt->backend.ctx, n->node);
	rt->backend.destroy(rt->backend.ctx, n->node);
	xtk_node_free_tree(rt, n);
}

/* -------------------------------------------------------------------------
 * Virtualized list realization
 *
 * A list element arrives with no children; this synthesizes LIST_ITEM
 * wrappers for exactly the rows intersecting the scroll viewport (plus
 * overscan). Keys are slot-based (index mod window size): when the window
 * shifts by k rows, the k rows leaving one edge carry the same keys as the
 * k rows entering the other, so the keyed diff patches retained controls in
 * place instead of unmount/mount churn — real recycling. Positioning is
 * backend-owned: apply_props sees item.index/height change and moves the
 * node (the reconciler never touches layout here).
 * ---------------------------------------------------------------------- */

int xtk_list_auto_columns(float cross, float item_width, int explicit_columns) {
	if (explicit_columns > 0) return explicit_columns;
	if (item_width <= 0.0f || cross <= 0.0f) return 1;
	int cols = ( int ) floorf(cross / item_width);
	return cols > 0 ? cols : 1;
}

static XtkListKind xtk_list_kind_for(XtkControlType type) {
	switch (type) {
	case XTK_CONTROL_LIST_BOX       : return XTK_LIST_KIND_LIST_BOX;
	case XTK_CONTROL_GRID_VIEW      : return XTK_LIST_KIND_GRID;
	case XTK_CONTROL_ITEMS_REPEATER : return XTK_LIST_KIND_REPEATER;
	default                         : return XTK_LIST_KIND_LIST;
	}
}

static void xtk_list_window(XtkRuntime *rt, XentNodeId node, XtkEl const *el, int *first, int *last, int *cols) {
	XtkBackend *be     = &rt->backend;
	float       offset = 0.0f, extent = 0.0f, cross = 0.0f;
	if (!be->list_viewport || !be->list_viewport(be->ctx, node, &offset, &extent, &cross) || extent <= 0.0f) {
		/* Layout hasn't produced a viewport yet (fresh mount / headless):
		 * realize a plausible first window; the backend invalidates once the
		 * real viewport is known and the window corrects itself. */
		offset = 0.0f;
		extent = isnan(el->height) ? 600.0f : el->height;
		cross  = isnan(el->width) ? 0.0f : el->width;
	}

	*cols          = xtk_list_auto_columns(cross, el->list.item_width, el->list.columns);
	int total_rows = (el->list.count + *cols - 1) / *cols;

	/* Clamp into the content range so a stale offset (rows removed while
	 * scrolled to the end) still yields a well-formed window. */
	float item_h     = el->list.item_height;
	float max_offset = ( float ) total_rows * item_h - extent;
	if (offset > max_offset) offset = max_offset;
	if (offset < 0.0f) offset = 0.0f;

	int row_first = ( int ) floorf(offset / item_h) - el->list.overscan;
	int row_last  = ( int ) ceilf((offset + extent) / item_h) - 1 + el->list.overscan;
	if (row_first < 0) row_first = 0;
	if (row_last > total_rows - 1) row_last = total_rows - 1;

	*first = row_first * *cols;
	*last  = (row_last + 1) * *cols - 1;
	if (*last > el->list.count - 1) *last = el->list.count - 1;
}

/* Hang the per-index content element under its row wrapper; false = arena OOM. */
static bool xtk_list_attach_content(XtkUi *ui, XtkEl *wrap, XtkEl *content) {
	if (!content) return true;
	wrap->children = ( XtkEl ** ) xtk_arena_alloc(xtk_ui_arena(ui), sizeof(XtkEl *));
	if (!wrap->children) return false;
	wrap->children [0] = content;
	wrap->child_count  = 1;
	return true;
}

static void xtk_list_realize(XtkRuntime *rt, XentNodeId node, XtkEl *el) {
	int first = 0, last = -1, cols = 1;
	if (el->list.count > 0 && el->list.item) xtk_list_window(rt, node, el, &first, &last, &cols);

	int window = last - first + 1;
	if (window < 0) window = 0;

	XtkEl **rows = ( XtkEl ** ) xtk_arena_alloc(xtk_ui_arena(rt->ui), sizeof(XtkEl *) * ( size_t ) (window ? window : 1));
	if (!rows) return;

	XtkListKind kind    = xtk_list_kind_for(el->type);
	bool        single  = el->list.sel_mode == XTK_LIST_SELECT_SINGLE;
	float       cell_w  = cols > 1 || el->list.item_width > 0.0f ? el->list.item_width : 0.0f;
	int         filled  = 0;
	for (int i = first; i <= last; i++) {
		XtkEl *wrap = xtk_el_new(rt->ui, XTK_CONTROL_LIST_ITEM, NULL);
		if (!wrap) break;
		wrap->key    = xtk_fmt(rt->ui, "%d", i % window);
		wrap->height = el->list.item_height;
		if (cell_w > 0.0f) wrap->width = cell_w;
		wrap->item = (XtkListItemDesc) {
		    .index    = i,
		    .kind     = kind,
		    .selected = single && i == el->list.selected,
		    .multi    = el->list.sel_mode == XTK_LIST_SELECT_MULTIPLE,
		    .x        = ( float ) (i % cols) * cell_w,
		    .y        = ( float ) (i / cols) * el->list.item_height,
		    .w        = cell_w,
		    .h        = el->list.item_height,
		};

		if (!xtk_list_attach_content(rt->ui, wrap, el->list.item(rt->ui, el->list.env, i))) break;
		rows [filled++] = wrap;
	}

	el->children    = rows;
	el->child_count = filled;

	if (rt->backend.list_realized) rt->backend.list_realized(rt->backend.ctx, node, first, first + filled - 1, cols);
}

static bool xtk_same_identity(XtkEl const *a, XtkEl const *b) {
	if (a->type != b->type) return false;
	if (!!a->key != !!b->key) return false;
	return !a->key || strcmp(a->key, b->key) == 0;
}

static void xtk_diff(XtkRuntime *rt, XtkNode *n, XtkEl const *prev, XtkEl const *el);

static int  xtk_match_keyed(XtkEl const *prev, bool const *claimed, XtkEl const *want) {
	for (int i = 0; i < prev->child_count; i++)
		if (!claimed [i] && xtk_same_identity(prev->children [i], want)) return i;
	return -1;
}

static int xtk_match_child(XtkEl const *prev, bool const *claimed, XtkEl const *want, int *unkeyed_cursor) {
	if (want->key) return xtk_match_keyed(prev, claimed, want);
	int seen = 0;
	for (int i = 0; i < prev->child_count; i++) {
		if (prev->children [i]->key) continue;
		if (seen++ < *unkeyed_cursor) continue;
		(*unkeyed_cursor)++;
		return !claimed [i] && xtk_same_identity(prev->children [i], want) ? i : -1;
	}
	(*unkeyed_cursor)++;
	return -1;
}

static void xtk_diff_match(
  XtkRuntime *rt, XtkNode *n, XtkEl const *prev, XtkEl const *el, XtkNode **out, bool *claimed, int *last_old,
  bool *reorder
) {
	int unkeyed_cursor = 0;
	for (int i = 0; i < el->child_count; i++) {
		XtkEl const *want = el->children [i];
		int          from = xtk_match_child(prev, claimed, want, &unkeyed_cursor);
		if (from >= 0 && from < n->child_count) {
			claimed [from] = true;
			out [i]        = n->children [from];
			xtk_diff(rt, out [i], prev->children [from], want);
			*reorder  = *reorder || from < *last_old;
			*last_old = from;
		}
		else {
			out [i]  = xtk_mount(rt, n->host, want);
			*reorder = true;
		}
	}
}

static void xtk_diff_reorder(XtkRuntime *rt, XtkNode *n, XtkEl const *el) {
	for (int i = 0; i < n->child_count; i++)
		if (n->children [i] && el->children [i]->type != XTK_CONTROL_CONTENT_DIALOG)
			xent_append_child(rt->ctx, n->host, n->children [i]->node);
}

static void xtk_diff_children(XtkRuntime *rt, XtkNode *n, XtkEl const *prev, XtkEl const *el) {
	int   old_count = prev->child_count;
	bool *claimed   = old_count ? ( bool * ) calloc(( size_t ) old_count, sizeof(bool)) : NULL;
	if (old_count && !claimed) return;

	XtkNode **next_nodes
	  = el->child_count ? ( XtkNode ** ) calloc(( size_t ) el->child_count, sizeof(XtkNode *)) : NULL;
	if (el->child_count && !next_nodes) {
		free(claimed);
		return;
	}

	int  last_old = -1;
	bool reorder  = false;
	xtk_diff_match(rt, n, prev, el, next_nodes, claimed, &last_old, &reorder);

	for (int i = 0; i < old_count; i++)
		if (!claimed [i] && i < n->child_count) xtk_unmount(rt, n->children [i]);
	free(claimed);

	free(n->children);
	n->children    = next_nodes;
	n->child_count = el->child_count;
	n->child_cap   = el->child_count;

	if (reorder) xtk_diff_reorder(rt, n, el);
}

static void xtk_diff(XtkRuntime *rt, XtkNode *n, XtkEl const *prev, XtkEl const *el) {
	if (!n) return;
	rt->backend.apply_props(rt->backend.ctx, n, prev, el);
	if (xtk_is_list_type(el->type)) xtk_list_realize(rt, n->node, ( XtkEl * ) el);
	xtk_diff_children(rt, n, prev, el);
}

static void xtk_mount_root(XtkRuntime *rt, XtkEl *next) {
	rt->root = xtk_mount(rt, rt->host, next);
	if (!rt->root) return;
	xent_set_absolute_position(rt->ctx, rt->root->node, (XentPoint) {0.0f, 0.0f});
	if (next->type != XTK_CONTROL_NAV_VIEW) xent_set_size_percent(rt->ctx, rt->root->node, (XentSize) {1.0f, 1.0f});
}

void xtk_reconcile(XtkRuntime *rt, XtkEl *next) {
	if (!next) return;
	if (!rt->root || !rt->prev_root || !xtk_same_identity(rt->prev_root, next)) {
		if (rt->root) xtk_unmount(rt, rt->root);
		xtk_mount_root(rt, next);
		rt->prev_root = next;
		return;
	}
	xtk_diff(rt, rt->root, rt->prev_root, next);
	rt->prev_root = next;
}

void xtk_unmount_all(XtkRuntime *rt) {
	if (!rt || !rt->root) return;
	xtk_unmount(rt, rt->root);
	rt->root      = NULL;
	rt->prev_root = NULL;
}
