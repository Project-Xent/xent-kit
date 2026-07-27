/**
 * @file test_xtk_list.c
 * @brief Virtualized list through XtkRtCfg + retained Host.
 */
#include <xtk/xtk_catalog.h>
#include <xtk/xtk_reconcile.h>
#include "xtk_retained.h"

#include "runtime/xtk_runtime_internal.h"
#include "reconcile/xtk_reconcile_internal.h"

#include <stdio.h>
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

typedef struct Mock {
	bool  viewport_ready;
	float offset;
	float extent;
	int   realized_first;
	int   realized_last;
	int   prepares;
	int   commits;
	int   creates;
	int   destroys;
} Mock;

typedef struct CountingHost {
	XtkHost              base;
	XtkHost             *inner;
	XtkHostVtable        vt;
	XtkHostVtable const *inner_vt;
	Mock                *mock;
} CountingHost;

static CountingHost       *as_ch(XtkHost *host) { return ( CountingHost * ) host; }

static CountingHost const *as_ch_c(XtkHost const *host) { return ( CountingHost const * ) host; }

static XtkBatchError       counting_preflight(XtkHost *host, XtkBatch *batch, XtkBatchDiag *diagnostic) {
	CountingHost *ch = as_ch(host);
	return ch->inner_vt->preflight(ch->inner, batch, diagnostic);
}

static XtkBatchError
counting_prepare(XtkHost *host, XtkBatch *batch, XtkPrepare **out_prepare, XtkBatchDiag *diagnostic) {
	CountingHost *ch = as_ch(host);
	ch->mock->prepares++;
	for (uint32_t i = 0; i < batch->count; i++) {
		XtkBatchOp const *op = &batch->ops [i];
		if (op->kind == XTK_BATCH_OP_CREATE && op->u.create.type == XTK_CTRL_LISTITEM) ch->mock->creates++;
		if (op->kind == XTK_BATCH_OP_DESTROY && op->u.destroy.target.kind == XTK_REF_EXISTING) {
			if (ch->inner_vt->type(ch->inner, op->u.destroy.target.u.existing) == XTK_CTRL_LISTITEM)
				ch->mock->destroys++;
		}
	}
	return ch->inner_vt->prepare(ch->inner, batch, out_prepare, diagnostic);
}

static XtkBatchResult *counting_commit(XtkHost *host, XtkPrepare *prepare, XtkBatchDiag *diagnostic) {
	CountingHost *ch = as_ch(host);
	ch->mock->commits++;
	return ch->inner_vt->commit(ch->inner, prepare, diagnostic);
}

static void counting_abort(XtkHost *host, XtkPrepare *prepare) {
	as_ch(host)->inner_vt->abort(as_ch(host)->inner, prepare);
}

static bool counting_is_live(XtkHost const *host, XtkCtrl control) {
	return as_ch_c(host)->inner_vt->live(as_ch_c(host)->inner, control);
}

static uint64_t counting_revision(XtkHost const *host) {
	return as_ch_c(host)->inner_vt->revision(as_ch_c(host)->inner);
}

static XtkCtrl counting_scene_root(XtkHost const *host) { return as_ch_c(host)->inner_vt->root(as_ch_c(host)->inner); }

static XtkCtrlId counting_control_type(XtkHost const *host, XtkCtrl control) {
	return as_ch_c(host)->inner_vt->type(as_ch_c(host)->inner, control);
}

static XtkCtrl counting_parent(XtkHost const *host, XtkCtrl control) {
	return as_ch_c(host)->inner_vt->parent(as_ch_c(host)->inner, control);
}

static XtkCtrl counting_first_child(XtkHost const *host, XtkCtrl control) {
	return as_ch_c(host)->inner_vt->first(as_ch_c(host)->inner, control);
}

static XtkCtrl counting_next_sibling(XtkHost const *host, XtkCtrl control) {
	return as_ch_c(host)->inner_vt->next(as_ch_c(host)->inner, control);
}

static XtkCtrlDesc const *counting_descriptor(XtkHost const *host, XtkCtrlId type) {
	return as_ch_c(host)->inner_vt->desc(as_ch_c(host)->inner, type);
}

static bool counting_get_property(
  XtkHost const *host, XtkCtrl control, XtkPropertyId property, XtkValueView *out_value, XtkChangeStamp *out_change
) {
	return as_ch_c(host)->inner_vt->prop(as_ch_c(host)->inner, control, property, out_value, out_change);
}

static bool counting_resource_is_valid(XtkHost const *host, XtkResource resource, XtkResourceTypeId type) {
	return as_ch_c(host)->inner_vt->res_valid(as_ch_c(host)->inner, resource, type);
}

static bool counting_resource_retain(XtkHost *host, XtkResource resource, XtkResourceTypeId type) {
	return as_ch(host)->inner_vt->res_retain(as_ch(host)->inner, resource, type);
}

static void counting_resource_release(XtkHost *host, XtkResource resource, XtkResourceTypeId type) {
	as_ch(host)->inner_vt->res_release(as_ch(host)->inner, resource, type);
}

static uint32_t counting_dispatch(XtkHost *host, XtkEvent const *event) {
	return as_ch(host)->inner_vt->dispatch(as_ch(host)->inner, event);
}

static void wrap_host(CountingHost *ch, XtkHost *inner, Mock *mock) {
	ch->inner          = inner;
	ch->inner_vt       = inner->vt;
	ch->mock           = mock;
	ch->vt             = *inner->vt;
	ch->vt.preflight   = counting_preflight;
	ch->vt.prepare     = counting_prepare;
	ch->vt.commit      = counting_commit;
	ch->vt.abort       = counting_abort;
	ch->vt.live        = counting_is_live;
	ch->vt.revision    = counting_revision;
	ch->vt.root        = counting_scene_root;
	ch->vt.type        = counting_control_type;
	ch->vt.parent      = counting_parent;
	ch->vt.first       = counting_first_child;
	ch->vt.next        = counting_next_sibling;
	ch->vt.desc        = counting_descriptor;
	ch->vt.prop        = counting_get_property;
	ch->vt.res_valid   = counting_resource_is_valid;
	ch->vt.res_retain  = counting_resource_retain;
	ch->vt.res_release = counting_resource_release;
	ch->vt.dispatch    = counting_dispatch;
	ch->base.vt        = &ch->vt;
	ch->base.impl      = inner->impl;
}

static bool mock_viewport(void *ctx, XentNodeId id, XtkViewport *out) {
	( void ) id;
	Mock *m = ( Mock * ) ctx;
	if (!m->viewport_ready) return false;
	out->offset = m->offset;
	out->extent = m->extent;
	out->cross  = 800.0f;
	return true;
}

static void mock_virtual_range(void *ctx, XentNodeId id, XtkVirtualRange const *range) {
	( void ) id;
	Mock *m           = ( Mock * ) ctx;
	m->realized_first = range->first;
	m->realized_last  = range->last;
}

static void mock_request_frame(void *ctx) { ( void ) ctx; }

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
	return xtk_list(
	  ui, (XtkListDesc) {
			.nitem  = mo->count,
			.itemh  = 40.0f,
			.item   = row,
			.env    = mo,
			.sel    = mo->selected,
			.select = xtk_msg(MSG_SELECT),
		  }
	);
}

static void frame_reset(Mock *m) {
	m->creates  = 0;
	m->destroys = 0;
	m->prepares = 0;
	m->commits  = 0;
}

static bool list_item_selected(XtkHost *host, XtkRt *rt, int index) {
	XtkNode *list = rt->root;
	if (!list || list->child_count <= 0) return false;
	uint64_t key = ( uint64_t ) (index % list->child_count);
	for (int i = 0; i < list->child_count; i++) {
		XtkNode *child = list->children [i];
		if (child->key.kind != XTK_KEY_U64 || child->key.value.u64 != key) continue;
		XtkValueView   sel    = {0};
		XtkChangeStamp change = {0};
		if (!host->vt->prop(host, ( XtkCtrl ) child->node, XTK_PROP_SELECTED, &sel, &change)) return false;
		return sel.kind == XTK_VALUE_BOOL && sel.u.b;
	}
	return false;
}

int main(void) {
	XtkHost *inner = xtk_retained_host_create();
	EXPECT(inner, "retained host");
	Mock         mock = {.realized_first = -100, .realized_last = -100};
	CountingHost counted;
	wrap_host(&counted, inner, &mock);

	XentNodeId host_root = ( XentNodeId ) counted.base.vt->root(&counted.base);
	XtkRtCfg   cfg       = {
	  .ctx           = &mock,
	  .request_frame = mock_request_frame,
	  .viewport      = mock_viewport,
	  .virtual_range = mock_virtual_range,
	};
	Model  model = {.count = 1000, .selected = -1};
	XtkRt *rt    = xtk_rt_create(&counted.base, &cfg, host_root, &model, update, view);
	EXPECT(rt, "runtime");

	for (int i = 0; i < XTK_QUEUE_CAP; i++)
		EXPECT(xtk_rt_post(rt, xtk_msg(MSG_SELECT)) == XTK_POST_ACCEPTED, "queue accepts capacity");
	EXPECT(xtk_rt_post(rt, xtk_msg(MSG_SELECT)) == XTK_POST_FULL, "queue reports overflow");
	XtkOverflowStatus ov = xtk_rt_overflow(rt);
	EXPECT(ov.dropped_since_ack == 1u && ov.sticky, "overflow status sticky");
	xtk_rt_ackoverflow(rt);
	ov = xtk_rt_overflow(rt);
	EXPECT(!ov.sticky && ov.dropped_since_ack == 0u, "acknowledge clears sticky");
	while (rt->q_count) {
		rt->q_head = (rt->q_head + 1u) % XTK_QUEUE_CAP;
		rt->q_count--;
	}

	XtkFrameResult fr = xtk_rt_frame(rt);
	EXPECT(fr.status == XTK_FRAME_COMMITTED, "mount commits");
	EXPECT(mock.realized_first == 0 && mock.realized_last == 18, "fallback window 0..18");
	EXPECT(mock.creates == 19, "19 rows mounted");
	EXPECT(mock.destroys == 0, "no rows destroyed at mount");
	EXPECT(mock.prepares == 1 && mock.commits == 1, "one prepare/commit");

	mock.viewport_ready = true;
	mock.offset         = 400.0f;
	mock.extent         = 400.0f;
	frame_reset(&mock);
	xtk_rt_invalidate(rt);
	fr = xtk_rt_frame(rt);
	EXPECT(fr.status == XTK_FRAME_COMMITTED, "viewport frame");
	EXPECT(mock.realized_first == 6 && mock.realized_last == 23, "window 6..23");
	EXPECT(mock.destroys - mock.creates == 1, "window shrink retires exactly one row");
	EXPECT(mock.creates <= 1, "window shrink recycles the rest");

	mock.offset = 800.0f;
	frame_reset(&mock);
	xtk_rt_invalidate(rt);
	fr = xtk_rt_frame(rt);
	EXPECT(mock.realized_first == 16 && mock.realized_last == 33, "window 16..33");
	EXPECT(mock.creates == 0 && mock.destroys == 0, "same-size shift fully recycles");

	frame_reset(&mock);
	xtk_rt_post(rt, xtk_msg_i(MSG_SELECT, 20));
	fr = xtk_rt_frame(rt);
	EXPECT(model.selected == 20, "update consumed selection");
	EXPECT(mock.creates == 0 && mock.destroys == 0, "selection does not remount");
	EXPECT(list_item_selected(&counted.base, rt, 20), "row 20 selected");

	model.count = 10;
	frame_reset(&mock);
	xtk_rt_invalidate(rt);
	fr = xtk_rt_frame(rt);
	EXPECT(mock.realized_first == 0 && mock.realized_last == 9, "count shrink clamps window to 0..9");

	model.count = 0;
	frame_reset(&mock);
	xtk_rt_invalidate(rt);
	fr = xtk_rt_frame(rt);
	EXPECT(mock.realized_first == 0 && mock.realized_last == -1, "empty list reports 0..-1");

	xtk_rt_destroy(rt);
	xtk_retained_host_destroy(inner);
	printf("PASS: xtk virtualized list\n");
	return 0;
}
