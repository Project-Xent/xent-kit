/**
 * @file test_xtk_list.c
 * @brief Headless reconciler test for the virtualized list: window
 * realization from the viewport, slot-key recycling on scroll (no
 * mount/unmount churn), selection patching, offset clamping after count
 * shrink, and realized-range reporting through the backend vtable.
 */
#include <xtk/xtk_reconcile.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EXPECT(cond, msg)              \
	do {                               \
		if (!(cond)) {                 \
			printf("FAIL: %s\n", msg); \
			return 1;                  \
		}                              \
	}                                  \
	while (0)

enum
{
	MSG_NONE = 0,
	MSG_SELECT,
};

/* -------------------------------------------------------------------------
 * Mock backend: real xent nodes (so append/destroy stay consistent), plus
 * counters and captures the assertions read.
 * ---------------------------------------------------------------------- */

typedef struct Mock {
	XentContext *ctx;

	bool         viewport_ready;
	float        offset;
	float        extent;

	int          realized_first;
	int          realized_last;

	int          item_creates;
	int          item_destroys;

	/* Last-frame capture of applied item props, keyed by window position. */
	int          applied_indices [256];
	bool         applied_selected [256];
	int          applied_count;
} Mock;

static void *mock_binding_create(void *ctx, XtkRuntime *rt) {
	( void ) ctx;
	XtkRuntime **b = ( XtkRuntime ** ) calloc(1, sizeof(*b));
	if (b) *b = rt;
	return b;
}

static XentNodeId mock_create(void *ctx, XentNodeId parent, XtkEl const *el, void *binding) {
	( void ) binding;
	Mock      *m  = ( Mock * ) ctx;
	XentNodeId id = xent_create_node(m->ctx);
	if (id == XENT_NODE_INVALID) return id;
	if (parent != XENT_NODE_INVALID) xent_append_child(m->ctx, parent, id);
	if (el->type == XTK_CONTROL_LIST_ITEM) m->item_creates++;
	xent_set_node_tag(m->ctx, id, ( uint8_t ) el->type);
	return id;
}

static void mock_destroy(void *ctx, XentNodeId id) {
	Mock *m = ( Mock * ) ctx;
	if (( XtkControlType ) xent_get_node_tag(m->ctx, id) == XTK_CONTROL_LIST_ITEM) m->item_destroys++;
	xent_destroy_node(m->ctx, id);
}

static void mock_pre_unmount(void *ctx, XentNodeId id) {
	( void ) ctx;
	( void ) id;
}

static void mock_mount_setup(void *ctx, XtkNode *node, XentNodeId id, XtkEl const *el) {
	( void ) ctx;
	( void ) node;
	( void ) id;
	( void ) el;
}

static void mock_apply_props(void *ctx, XtkNode *node, XtkEl const *prev, XtkEl const *el) {
	( void ) node;
	( void ) prev;
	Mock *m = ( Mock * ) ctx;
	if (el->type != XTK_CONTROL_LIST_ITEM || m->applied_count >= 256) return;
	m->applied_indices [m->applied_count]  = el->item.index;
	m->applied_selected [m->applied_count] = el->item.selected;
	m->applied_count++;
}

static bool mock_is_interactive(XtkEl const *el) { return el->type == XTK_CONTROL_LIST_ITEM; }

static void mock_request_frame(void *ctx) { ( void ) ctx; }

static void mock_node_cleanup(XtkNode *node) { free(node->binding); }

static bool mock_list_viewport(void *ctx, XentNodeId id, float *offset, float *extent, float *cross) {
	( void ) id;
	Mock *m = ( Mock * ) ctx;
	if (!m->viewport_ready) return false;
	*offset = m->offset;
	*extent = m->extent;
	*cross  = 800.0f;
	return true;
}

static void mock_list_realized(void *ctx, XentNodeId id, int first, int last, int cols) {
	( void ) id;
	( void ) cols;
	Mock *m           = ( Mock * ) ctx;
	m->realized_first = first;
	m->realized_last  = last;
}

/* -------------------------------------------------------------------------
 * App: a plain list over `count` rows.
 * ---------------------------------------------------------------------- */

typedef struct Model {
	int count;
	int selected;
} Model;

static void update(void *model, XtkMsg msg) {
	Model *mo = ( Model * ) model;
	if (msg.tag == MSG_SELECT) mo->selected = msg.i;
}

static XtkEl *row(XtkUi *ui, void *env, int index) {
	( void ) env;
	return xtk_text(ui, xtk_fmt(ui, "row %d", index), (XtkTextDesc) {0});
}

static XtkEl *view(XtkUi *ui, void *model) {
	Model *mo = ( Model * ) model;
	return xtk_list_view(
	  ui, (XtkListDesc) {
	        .count       = mo->count,
	        .item_height = 40.0f,
	        .item        = row,
	        .env         = mo,
	        .selected    = mo->selected,
	        .on_select   = xtk_msg(MSG_SELECT),
	      }
	);
}

static void frame_reset(Mock *m) {
	m->applied_count = 0;
	m->item_creates  = 0;
	m->item_destroys = 0;
}

static bool applied_has(Mock const *m, int index, bool selected) {
	for (int i = 0; i < m->applied_count; i++)
		if (m->applied_indices [i] == index && m->applied_selected [i] == selected) return true;
	return false;
}

int main(void) {
	XentContext *ctx = xent_create_context(NULL);
	EXPECT(ctx, "xent context");
	XentNodeId host = xent_create_node(ctx);
	EXPECT(host != XENT_NODE_INVALID, "host node");

	Mock       mock = {.ctx = ctx, .realized_first = -100, .realized_last = -100};
	XtkBackend be   = {
	    .ctx            = &mock,
	    .binding_create = mock_binding_create,
	    .create         = mock_create,
	    .destroy        = mock_destroy,
	    .pre_unmount    = mock_pre_unmount,
	    .mount_setup    = mock_mount_setup,
	    .apply_props    = mock_apply_props,
	    .is_interactive = mock_is_interactive,
	    .request_frame  = mock_request_frame,
	    .node_cleanup   = mock_node_cleanup,
	    .list_viewport  = mock_list_viewport,
	    .list_realized  = mock_list_realized,
	};

	Model       model = {.count = 1000, .selected = -1};
	XtkRuntime *rt    = xtk_runtime_create(ctx, &be, host, &model, update, view);
	EXPECT(rt, "runtime");

	/* 1. Mount with no viewport yet: fallback 600px window at offset 0.
	 * item_height 40, overscan 4 -> rows 0 .. ceil(600/40)-1+4 = 18. */
	xtk_runtime_frame(rt);
	EXPECT(mock.realized_first == 0 && mock.realized_last == 18, "fallback window 0..18");
	EXPECT(mock.item_creates == 19, "19 rows mounted");
	EXPECT(mock.item_destroys == 0, "no rows destroyed at mount");

	/* 2. Real viewport appears: 400px at offset 400 -> first floor(400/40)-4=6,
	 * last ceil(800/40)-1+4=23. Window shrinks 19 -> 18: slot keys shift, at
	 * most one row remounts; the rest patch in place. */
	mock.viewport_ready = true;
	mock.offset         = 400.0f;
	mock.extent         = 400.0f;
	frame_reset(&mock);
	xtk_runtime_invalidate(rt);
	xtk_runtime_frame(rt);
	EXPECT(mock.realized_first == 6 && mock.realized_last == 23, "window 6..23");
	EXPECT(mock.item_destroys - mock.item_creates == 1, "window shrink retires exactly one row");
	EXPECT(mock.item_creates <= 1, "window shrink recycles the rest");
	EXPECT(applied_has(&mock, 23, false), "row 23 content applied");

	/* 3. Same-size window shift: offset 800 -> 16..33. Slot keys rotate over
	 * the same set, so every retained row is patched — zero churn. */
	mock.offset = 800.0f;
	frame_reset(&mock);
	xtk_runtime_invalidate(rt);
	xtk_runtime_frame(rt);
	EXPECT(mock.realized_first == 16 && mock.realized_last == 33, "window 16..33");
	EXPECT(mock.item_creates == 0 && mock.item_destroys == 0, "same-size shift fully recycles");
	EXPECT(applied_has(&mock, 33, false), "row 33 patched in");

	/* 4. Selection is a per-row prop patch, not a rebuild. */
	frame_reset(&mock);
	xtk_runtime_post(rt, xtk_msg_i(MSG_SELECT, 20));
	xtk_runtime_frame(rt);
	EXPECT(model.selected == 20, "update consumed selection");
	EXPECT(mock.item_creates == 0 && mock.item_destroys == 0, "selection does not remount");
	EXPECT(applied_has(&mock, 20, true), "row 20 applied as selected");
	EXPECT(applied_has(&mock, 21, false), "row 21 stays unselected");

	/* 5. Count shrinks under the scroll position: offset clamps into the new
	 * content range and the window stays well-formed. */
	model.count = 10;
	frame_reset(&mock);
	xtk_runtime_invalidate(rt);
	xtk_runtime_frame(rt);
	EXPECT(mock.realized_first == 0 && mock.realized_last == 9, "count shrink clamps window to 0..9");

	/* 6. Empty list realizes nothing. */
	model.count = 0;
	frame_reset(&mock);
	xtk_runtime_invalidate(rt);
	xtk_runtime_frame(rt);
	EXPECT(mock.realized_first == 0 && mock.realized_last == -1, "empty list reports 0..-1");

	xtk_runtime_destroy(rt);
	xent_destroy_context(ctx);
	printf("PASS: xtk virtualized list\n");
	return 0;
}
