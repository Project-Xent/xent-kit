#include <xtk/xtk_batch.h>
#include <xtk/xtk_reconcile.h>
#include "xtk_retained.h"

#include <xtk/xtk_alloc.h>
#include "runtime/xtk_rt_internal.h"
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

static void noop_update(void *model, XtkMsg msg) {
	( void ) model;
	( void ) msg;
}

static XtkEl *unused_view(XtkUi *ui, void *model) {
	( void ) model;
	return xtk_text(ui, "unused", (XtkTextDesc) {0});
}

typedef struct Model {
	char const *label;
} Model;

typedef struct TreeModel {
	int  count;
	bool keyed;
	bool reverse;
} TreeModel;

static XtkEl *model_view(XtkUi *ui, void *model) {
	Model *m = ( Model * ) model;
	return xtk_column(ui, (XtkStackDesc) {0}, (XtkEl *[]) {xtk_text(ui, m->label, (XtkTextDesc) {0}), XTK_END});
}

static XtkEl *tree_view(XtkUi *ui, void *model) {
	TreeModel *m     = ( TreeModel * ) model;
	XtkEl    **items = xtk_children_alloc(ui, m->count);
	if (!items) return NULL;
	for (int i = 0; i < m->count; i++) {
		int    key = m->reverse ? m->count - 1 - i : i;
		XtkEl *el  = xtk_text(ui, "item", (XtkTextDesc) {0});
		items [i]  = m->keyed ? xtk_keyed_u64(el, ( uint64_t ) key) : el;
	}
	return xtk_column(ui, (XtkStackDesc) {0}, items);
}

static void request_frame(void *ctx) { ( void ) ctx; }

static int  test_ui_creation_failures(void) {
	for (uint64_t fail_at = 1; fail_at <= 2; fail_at++) {
		xtk_alloc_test_reset();
		xtk_alloc_fail_at(fail_at);
		XtkUi *ui = xtk_ui_create();
		EXPECT(!ui, "ui creation reports injected allocation failure");
		EXPECT(xtk_alloc_test_stats().failures == 1u, "injected failure counted once");
	}
	xtk_alloc_test_reset();
	XtkUi *ui = xtk_ui_create();
	EXPECT(ui, "ui creation recovers after fault reset");
	xtk_ui_destroy(ui);
	EXPECT(xtk_alloc_test_stats().frees == 2u, "ui allocations released");
	return 0;
}

static int test_batch_payload_failure(void) {
	xtk_alloc_test_reset();
	XtkBatch *batch = xtk_batch_alloc(1u);
	EXPECT(batch, "batch creation");

	xtk_alloc_test_reset();
	xtk_alloc_fail_at(2u);
	XtkValue value = {
	  .kind = XTK_VALUE_STRING, .u.string = {.data = "label", .len = 5u}
    };
	bool ok = xtk_batch_set(batch, xtk_ref_existing(1u), 1u, value, (XtkChangeStamp) {0});
	EXPECT(!ok, "batch operation reports payload allocation failure");
	EXPECT(batch->count == 0u, "failed operation is not published");
	EXPECT(batch->capacity > 0u, "reserve side effect remains after payload failure");

	xtk_alloc_test_reset();
	xtk_batch_free(batch);
	return 0;
}

static int test_batch_result_failures(void) {
	for (uint64_t fail_at = 1u; fail_at <= 3u; fail_at++) {
		xtk_alloc_test_reset();
		xtk_alloc_fail_at(fail_at);
		XtkBatchResult *result = xtk_batchresult_create(1u, 1u);
		EXPECT(!result, "result allocation reports injected failure");
		EXPECT(xtk_alloc_test_stats().failures == 1u, "result failure counted once");
	}
	xtk_alloc_test_reset();
	return 0;
}

static int test_allocator_peak_accounting(void) {
	xtk_alloc_test_reset();
	void *a = xtk_alloc(16u);
	void *b = xtk_alloc(32u);
	EXPECT(a && b, "peak accounting allocations");
	XtkAllocStats stats = xtk_alloc_test_stats();
	EXPECT(stats.live_bytes == 48u && stats.peak_bytes == 48u, "live and peak bytes after allocations");
	xtk_alloc_free(a);
	stats = xtk_alloc_test_stats();
	EXPECT(stats.live_bytes == 32u && stats.peak_bytes == 48u, "free lowers live but not peak bytes");
	b = xtk_alloc_resize(b, 64u);
	EXPECT(b, "peak accounting resize");
	stats = xtk_alloc_test_stats();
	EXPECT(stats.live_bytes == 64u && stats.peak_bytes == 64u, "resize updates live and peak bytes");
	xtk_alloc_free(b);
	stats = xtk_alloc_test_stats();
	EXPECT(stats.live_bytes == 0u && stats.peak_bytes == 64u, "all measured bytes released");
	return 0;
}

static int test_failed_reconcile_preserves_committed(void) {
	bool saw_failure = false;
	bool saw_success = false;
	for (uint64_t fail_at = 1u; fail_at <= 128u; fail_at++) {
		xtk_alloc_test_reset();
		XtkHost *host = xtk_retained_host_create();
		EXPECT(host, "retained host");
		XentNodeId host_root = ( XentNodeId ) host->vt->root(host);
		XtkRtCfg   cfg       = {.ctx = NULL, .request_frame = request_frame};
		Model      model     = {.label = "before"};
		XtkRt     *rt        = xtk_rt_create(host, &cfg, host_root, &model, noop_update, model_view);
		EXPECT(rt, "runtime creation");
		EXPECT(xtk_rt_frame(rt).status == XTK_FRAME_COMMITTED, "initial mount commits");

		XtkNode   *root_before      = rt->root;
		XentNodeId child_id         = rt->root->children [0]->node;
		uint64_t   props_rev_before = rt->root->children [0]->props ? rt->root->children [0]->props->revision : 0u;
		uint64_t   rev_before       = host->vt->revision(host);
		model.label                 = "after";
		xtk_rt_invalidate(rt);
		xtk_alloc_test_reset();
		xtk_alloc_fail_at(fail_at);
		XtkFrameResult failed = xtk_rt_frame(rt);
		if (failed.status == XTK_FRAME_COMMITTED) {
			saw_success = true;
			xtk_alloc_test_reset();
			EXPECT(xtk_rt_destroy(rt), "successful sweep runtime destroy");
			xtk_retained_host_destroy(host);
			break;
		}

		saw_failure = true;
		EXPECT(rt->root == root_before, "committed root unchanged");
		EXPECT(
		  (rt->root->children [0]->props ? rt->root->children [0]->props->revision : 0u) == props_rev_before,
		  "retained props not advanced on failure"
		);
		EXPECT(rt->root->children [0]->node == child_id, "composition child handle unchanged");
		EXPECT(host->vt->revision(host) == rev_before, "Host revision unchanged");
		xtk_alloc_test_reset();
		XtkFrameResult retry = xtk_rt_frame(rt);
		EXPECT(retry.status == XTK_FRAME_COMMITTED, "retry commits entire candidate");
		EXPECT(
		  (rt->root->children [0]->props ? rt->root->children [0]->props->revision : 0u) != props_rev_before,
		  "retained props advance after retry"
		);
		EXPECT(rt->root->children [0]->node == child_id, "retry retains child identity");
		EXPECT(xtk_rt_destroy(rt), "failed sweep runtime destroy");
		xtk_retained_host_destroy(host);
	}
	EXPECT(saw_failure && saw_success, "allocation sweep reaches every update allocation");
	return 0;
}

static int test_mount_rejects_partial_children(void) {
	for (uint64_t fail_at = 1u; fail_at <= 64u; fail_at++) {
		xtk_alloc_test_reset();
		XtkHost *host = xtk_retained_host_create();
		EXPECT(host, "retained host for mount fault sweep");
		XentNodeId host_root = ( XentNodeId ) host->vt->root(host);
		XtkRtCfg   cfg       = {.request_frame = request_frame};
		Model      model     = {.label = "child"};
		XtkRt     *rt        = xtk_rt_create(host, &cfg, host_root, &model, noop_update, model_view);
		EXPECT(rt, "runtime for mount fault sweep");

		xtk_alloc_test_reset();
		xtk_alloc_fail_at(fail_at);
		XtkFrameResult fr = xtk_rt_frame(rt);
		if (fr.status == XTK_FRAME_COMMITTED)
			EXPECT(rt->root && rt->root->child_count == 1, "mount never publishes partial children");
		else EXPECT(!rt->root, "failed mount leaves no root");

		xtk_alloc_test_reset();
		xtk_rt_destroy(rt);
		xtk_retained_host_destroy(host);
	}
	return 0;
}

typedef struct SweepFixture {
	XtkHost  *host;
	XtkRt    *rt;
	TreeModel model;
} SweepFixture;

static bool sweep_open(SweepFixture *fixture, int count, bool keyed) {
	memset(fixture, 0, sizeof(*fixture));
	fixture->host = xtk_retained_host_create();
	if (!fixture->host) return false;
	fixture->model = (TreeModel) {.count = count, .keyed = keyed};
	XtkRtCfg cfg   = {.request_frame = request_frame};
	fixture->rt    = xtk_rt_create(
	  fixture->host, &cfg, ( XentNodeId ) fixture->host->vt->root(fixture->host), &fixture->model, noop_update,
	  tree_view
	);
	if (!fixture->rt) {
		xtk_retained_host_destroy(fixture->host);
		fixture->host = NULL;
		return false;
	}
	if (xtk_rt_frame(fixture->rt).status == XTK_FRAME_COMMITTED) return true;
	xtk_rt_destroy(fixture->rt);
	xtk_retained_host_destroy(fixture->host);
	fixture->rt   = NULL;
	fixture->host = NULL;
	return false;
}

static void sweep_close(SweepFixture *fixture) {
	xtk_alloc_test_reset();
	xtk_rt_destroy(fixture->rt);
	xtk_retained_host_destroy(fixture->host);
}

static int test_child_growth_fault_sweep(void) {
	bool saw_failure = false;
	bool saw_success = false;
	for (uint64_t fail_at = 1u; fail_at <= 2048u; fail_at++) {
		xtk_alloc_test_reset();
		SweepFixture fixture;
		EXPECT(sweep_open(&fixture, 1, false), "growth sweep baseline");
		XtkNode *root_before = fixture.rt->root;
		uint64_t rev_before  = fixture.host->vt->revision(fixture.host);

		fixture.model.count  = 128;
		xtk_rt_invalidate(fixture.rt);
		xtk_alloc_test_reset();
		xtk_alloc_fail_at(fail_at);
		XtkFrameResult frame = xtk_rt_frame(fixture.rt);
		if (frame.status == XTK_FRAME_COMMITTED) {
			saw_success = true;
			sweep_close(&fixture);
			break;
		}

		saw_failure = true;
		EXPECT(fixture.rt->root == root_before, "growth failure preserves composition");
		EXPECT(fixture.host->vt->revision(fixture.host) == rev_before, "growth failure preserves Host");
		xtk_alloc_test_reset();
		EXPECT(xtk_rt_frame(fixture.rt).status == XTK_FRAME_COMMITTED, "growth retry commits");
		EXPECT(fixture.rt->root->child_count == 128, "growth retry publishes every child");
		sweep_close(&fixture);
	}
	EXPECT(saw_failure && saw_success, "growth sweep reaches every allocation");
	return 0;
}

static int test_keyed_match_map_failure(void) {
	xtk_alloc_test_reset();
	SweepFixture fixture;
	EXPECT(sweep_open(&fixture, 2048, true), "keyed map baseline");
	XtkNode *root_before  = fixture.rt->root;
	uint64_t rev_before   = fixture.host->vt->revision(fixture.host);

	fixture.model.reverse = true;
	xtk_rt_invalidate(fixture.rt);
	xtk_alloc_test_reset();
	xtk_alloc_fail_at(1u);
	XtkFrameResult frame = xtk_rt_frame(fixture.rt);
	EXPECT(frame.status != XTK_FRAME_COMMITTED, "matching-map allocation failure rejects frame");
	EXPECT(xtk_alloc_test_stats().failures == 1u, "matching-map allocation was faulted");
	EXPECT(fixture.rt->root == root_before, "matching-map failure preserves composition");
	EXPECT(fixture.host->vt->revision(fixture.host) == rev_before, "matching-map failure preserves Host");

	xtk_alloc_test_reset();
	EXPECT(xtk_rt_frame(fixture.rt).status == XTK_FRAME_COMMITTED, "matching-map retry commits");
	EXPECT(fixture.rt->root->child_count == 2048, "matching-map retry preserves cardinality");
	sweep_close(&fixture);
	return 0;
}

int main(void) {
	( void ) unused_view;
	if (test_ui_creation_failures()) return 1;
	if (test_batch_payload_failure()) return 1;
	if (test_batch_result_failures()) return 1;
	if (test_allocator_peak_accounting()) return 1;
	if (test_mount_rejects_partial_children()) return 1;
	if (test_failed_reconcile_preserves_committed()) return 1;
	if (test_child_growth_fault_sweep()) return 1;
	if (test_keyed_match_map_failure()) return 1;
	printf("PASS: allocation failures preserve committed composition\n");
	return 0;
}
