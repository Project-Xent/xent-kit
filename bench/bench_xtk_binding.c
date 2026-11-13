#include <xtk/xtk_reconcile.h>
#include <xtk/xtk_catalog.h>

#include "xtk_retained.h"
#include <xtk/xtk_alloc.h>
#include "xtk_internal.h"
#include "reconcile/xtk_reconcile_internal.h"
#include "runtime/xtk_rt_internal.h"

#include <inttypes.h>
#include <stdio.h>
#include <time.h>

enum
{
	ITEM_COUNT         = 1024,
	WARMUP_ITERATIONS  = 32,
	MEASURE_ITERATIONS = 400,
};

typedef enum BenchMode
{
	BENCH_FULL,
	BENCH_MEMO,
	BENCH_SINGLE,
} BenchMode;

typedef struct BenchModel {
	BenchMode mode;
	uint32_t  revision;
	uint64_t  built;
} BenchModel;

typedef struct Fixture {
	XtkHost   *host;
	XtkRt     *runtime;
	BenchModel model;
} Fixture;

static void request_frame(void *ctx) { ( void ) ctx; }

static void noop_update(void *model, XtkMsg msg) {
	( void ) model;
	( void ) msg;
}

static XtkEl *build_stable(XtkUi *ui, void *ctx) {
	BenchModel *model = ctx;
	XtkEl     **items = xtk_children_alloc(ui, ITEM_COUNT - 2);
	if (!items) return NULL;
	for (int i = 0; i < ITEM_COUNT - 2; i++) {
		items [i] = xtk_text(ui, "stable", (XtkTextDesc) {0});
		if (!items [i]) return NULL;
		model->built++;
	}
	return xtk_column(ui, (XtkStackDesc) {0}, items);
}

static XtkEl *build_full(XtkUi *ui, BenchModel *model) {
	XtkEl **items = xtk_children_alloc(ui, ITEM_COUNT);
	if (!items) return NULL;
	for (int i = 0; i < ITEM_COUNT - 2; i++) {
		items [i] = xtk_text(ui, "stable", (XtkTextDesc) {0});
		if (!items [i]) return NULL;
		model->built++;
	}
	items [ITEM_COUNT - 2]
	  = xtk_textbox(ui, "value", (XtkTextBoxDesc) {.content = xtk_fmt(ui, "value-%u", model->revision)});
	float slider_value      = model->mode == BENCH_SINGLE ? 50.0f : ( float ) (model->revision % 100u);
	items [ITEM_COUNT - 1]  = xtk_slider(ui, (XtkSliderDesc) {.value = slider_value});
	model->built           += 2u;
	return xtk_column(ui, (XtkStackDesc) {0}, items);
}

static XtkEl *build_memo(XtkUi *ui, BenchModel *model) {
	XtkEl *stable = xtk_static_region(ui, UINT64_C(0x8801), build_stable, model);
	XtkEl *text   = xtk_textbox(ui, "value", (XtkTextBoxDesc) {.content = xtk_fmt(ui, "value-%u", model->revision)});
	XtkEl *slider = xtk_slider(ui, (XtkSliderDesc) {.value = ( float ) (model->revision % 100u)});
	if (!stable || !text || !slider) return NULL;
	model->built += 2u;
	return xtk_column(ui, (XtkStackDesc) {0}, xtk_kids(stable, text, slider));
}

static XtkEl *bench_view(XtkUi *ui, void *ctx) {
	BenchModel *model = ctx;
	if (model->mode == BENCH_MEMO) return build_memo(ui, model);
	return build_full(ui, model);
}

static bool fixture_init(Fixture *fixture, BenchMode mode) {
	fixture->host = xtk_retained_host_create();
	if (!fixture->host) return false;
	fixture->model.mode = mode;
	XtkRtCfg cfg        = {.request_frame = request_frame};
	fixture->runtime    = xtk_rt_create(
	  fixture->host, &cfg, ( XentNodeId ) fixture->host->vt->root(fixture->host), &fixture->model, noop_update,
	  bench_view
	);
	if (!fixture->runtime) xtk_retained_host_destroy(fixture->host);
	return fixture->runtime != NULL;
}

static void fixture_dispose(Fixture *fixture) {
	xtk_rt_destroy(fixture->runtime);
	xtk_retained_host_destroy(fixture->host);
}

static bool reconcile_once(Fixture *fixture, XtkFrameMetrics *metrics) {
	fixture->model.revision++;
	xtk_rt_invalidate(fixture->runtime);
	XtkFrameResult result = xtk_rt_frame(fixture->runtime);
	if (metrics) *metrics = result.metrics;
	return result.status == XTK_FRAME_COMMITTED;
}

static uint64_t clock_ns(void) {
	struct timespec value;
	if (timespec_get(&value, TIME_UTC) != TIME_UTC) return 0u;
	return ( uint64_t ) value.tv_sec * UINT64_C(1000000000) + ( uint64_t ) value.tv_nsec;
}

static int run_reconcile(BenchMode mode, char const *name) {
	Fixture fixture = {0};
	if (!fixture_init(&fixture, mode) || !reconcile_once(&fixture, NULL)) return 1;
	for (int i = 0; i < WARMUP_ITERATIONS; i++)
		if (!reconcile_once(&fixture, NULL)) return 1;

	fixture.model.built = 0u;
	xtk_alloc_test_reset();
	XtkFrameMetrics metrics = {0};
	uint64_t        begin   = clock_ns();
	for (int i = 0; i < MEASURE_ITERATIONS; i++) {
		XtkFrameMetrics frame = {0};
		if (!reconcile_once(&fixture, &frame)) return 1;
		metrics.nodes_built      += frame.nodes_built;
		metrics.nodes_compared   += frame.nodes_compared;
		metrics.nodes_skipped    += frame.nodes_skipped;
		metrics.property_patches += frame.property_patches;
		metrics.mutations        += frame.mutations;
	}
	uint64_t      elapsed = clock_ns() - begin;
	XtkAllocStats alloc   = xtk_alloc_test_stats();
	printf(
	  "binding=%s iterations=%d elapsed_ns=%" PRIu64 " ns_per_iteration=%" PRIu64 " allocation_attempts=%" PRIu64
	  " nodes_built=%" PRIu64 " nodes_compared=%" PRIu64 " nodes_skipped=%" PRIu64 " property_patches=%" PRIu64
	  " mutations=%" PRIu64 " allocation_peak_bytes=%zu\n",
	  name, MEASURE_ITERATIONS, elapsed, elapsed / MEASURE_ITERATIONS, alloc.attempts, metrics.nodes_built,
	  metrics.nodes_compared, metrics.nodes_skipped, metrics.property_patches, metrics.mutations, alloc.peak_bytes
	);
	fixture_dispose(&fixture);
	return 0;
}

int main(void) {
	setvbuf(stdout, NULL, _IONBF, 0);
	printf(
	  "production_size element_handle=%zu element_header=%zu retained_node=%zu prop_patch=%zu\n", sizeof(XtkEl),
	  sizeof(XtkElementData), sizeof(XtkNode), sizeof(XtkPropPatch)
	);
	if (run_reconcile(BENCH_FULL, "full")) return 1;
	if (run_reconcile(BENCH_MEMO, "memo")) return 1;
	if (run_reconcile(BENCH_SINGLE, "declarative_single")) return 1;
	return 0;
}
