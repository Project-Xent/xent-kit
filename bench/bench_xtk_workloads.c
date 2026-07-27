#include <xtk/xtk_batch.h>
#include <xtk/xtk_catalog.h>
#include <xtk/xtk_reconcile.h>

#include "xtk_alloc_internal.h"
#include "xtk_retained.h"

#include <inttypes.h>
#include <stdio.h>
#include <time.h>

enum
{
	FORM_PAIRS         = 64,
	PAGE_ITEMS         = 128,
	CANVAS_ITEMS       = 1024,
	CANVAS_PATCHES     = 64,
	WARMUP_ITERATIONS  = 16,
	MEASURE_ITERATIONS = 100,
};

typedef enum RuntimeWork
{
	RUNTIME_FORM,
	RUNTIME_PAGE,
} RuntimeWork;

typedef struct WorkModel {
	RuntimeWork work;
	uint32_t    revision;
	bool        page;
	uint64_t    built;
} WorkModel;

typedef struct WorkCounts {
	uint64_t prepares;
	uint64_t commits;
	uint64_t creates;
	uint64_t destroys;
	uint64_t moves;
	uint64_t patches;
} WorkCounts;

typedef struct WorkHost {
	XtkHost       base;
	XtkHost      *inner;
	XtkHostVtable vt;
	WorkCounts    counts;
} WorkHost;

typedef struct RuntimeFixture {
	XtkHost  *inner;
	WorkHost  host;
	XtkRt    *runtime;
	WorkModel model;
} RuntimeFixture;

typedef struct WorkMetrics {
	uint64_t built;
	uint64_t compared;
	uint64_t skipped;
	uint64_t patches;
	uint64_t mutations;
} WorkMetrics;

static uint64_t clock_ns(void) {
	struct timespec value;
	if (timespec_get(&value, TIME_UTC) != TIME_UTC) return 0u;
	return ( uint64_t ) value.tv_sec * UINT64_C(1000000000) + ( uint64_t ) value.tv_nsec;
}

static void count_ops(WorkCounts *counts, XtkBatch const *batch) {
	for (uint32_t i = 0; i < batch->count; i++) {
		XtkBatchOpKind kind  = batch->ops [i].kind;
		counts->creates     += kind == XTK_BATCH_OP_CREATE;
		counts->destroys    += kind == XTK_BATCH_OP_DESTROY;
		counts->moves       += kind == XTK_BATCH_OP_MOVE || kind == XTK_BATCH_OP_REPARENT;
		counts->patches     += kind == XTK_BATCH_OP_SET_PROP;
	}
}

static XtkBatchError work_prepare(XtkHost *raw, XtkBatch *batch, XtkPrepare **prepare, XtkBatchDiag *diagnostic) {
	WorkHost *host = ( WorkHost * ) raw;
	host->counts.prepares++;
	count_ops(&host->counts, batch);
	return host->inner->vt->prepare(host->inner, batch, prepare, diagnostic);
}

static XtkBatchResult *work_commit(XtkHost *raw, XtkPrepare *prepare, XtkBatchDiag *diagnostic) {
	WorkHost *host = ( WorkHost * ) raw;
	host->counts.commits++;
	return host->inner->vt->commit(host->inner, prepare, diagnostic);
}

static bool work_host_init(WorkHost *host, XtkHost *inner) {
	if (!host || !inner) return false;
	*host            = (WorkHost) {0};
	host->inner      = inner;
	host->vt         = *inner->vt;
	host->vt.prepare = work_prepare;
	host->vt.commit  = work_commit;
	host->base.vt    = &host->vt;
	host->base.impl  = inner->impl;
	return true;
}

static void request_frame(void *ctx) { ( void ) ctx; }

static void noop_update(void *model, XtkMsg message) {
	( void ) model;
	( void ) message;
}

static XtkEl *form_view(XtkUi *ui, WorkModel *model) {
	XtkEl **items = xtk_children_alloc(ui, FORM_PAIRS * 2);
	if (!items) return NULL;
	for (int i = 0; i < FORM_PAIRS; i++) {
		items [i * 2]
		  = xtk_textbox(ui, "field", (XtkTextBoxDesc) {.content = xtk_fmt(ui, "field-%d-%u", i, model->revision)});
		items [i * 2 + 1]
		  = xtk_slider(ui, (XtkSliderDesc) {.value = ( float ) ((model->revision + ( uint32_t ) i) % 100u)});
		if (!items [i * 2] || !items [i * 2 + 1]) return NULL;
	}
	model->built += FORM_PAIRS * 2 + 1;
	return xtk_column(ui, (XtkStackDesc) {0}, items);
}

static XtkEl *page_view(XtkUi *ui, WorkModel *model) {
	XtkEl **items = xtk_children_alloc(ui, PAGE_ITEMS);
	if (!items) return NULL;
	for (int i = 0; i < PAGE_ITEMS; i++) {
		items [i]
		  = model->page ? xtk_button(ui, "command", (XtkButtonDesc) {0}) : xtk_text(ui, "document", (XtkTextDesc) {0});
		if (!items [i]) return NULL;
	}
	model->built += PAGE_ITEMS + 1;
	return model->page ? xtk_row(ui, (XtkStackDesc) {0}, items) : xtk_column(ui, (XtkStackDesc) {0}, items);
}

static XtkEl *runtime_view(XtkUi *ui, void *ctx) {
	WorkModel *model = ctx;
	return model->work == RUNTIME_FORM ? form_view(ui, model) : page_view(ui, model);
}

static bool runtime_fixture_init(RuntimeFixture *fixture, RuntimeWork work) {
	fixture->inner = xtk_retained_host_create();
	if (!fixture->inner || !work_host_init(&fixture->host, fixture->inner)) return false;
	fixture->model.work = work;
	XtkRtCfg cfg        = {.request_frame = request_frame};
	fixture->runtime    = xtk_rt_create(
	  &fixture->host.base, &cfg, ( XentNodeId ) fixture->host.base.vt->root(&fixture->host.base), &fixture->model,
	  noop_update, runtime_view
	);
	if (!fixture->runtime) xtk_retained_host_destroy(fixture->inner);
	return fixture->runtime != NULL;
}

static void runtime_fixture_dispose(RuntimeFixture *fixture) {
	xtk_rt_destroy(fixture->runtime);
	xtk_retained_host_destroy(fixture->inner);
}

static bool runtime_frame(RuntimeFixture *fixture, XtkFrameMetrics *metrics) {
	fixture->model.revision++;
	if (fixture->model.work == RUNTIME_PAGE) fixture->model.page = !fixture->model.page;
	xtk_rt_invalidate(fixture->runtime);
	XtkFrameResult result = xtk_rt_frame(fixture->runtime);
	if (metrics) *metrics = result.metrics;
	return result.status == XTK_FRAME_COMMITTED;
}

static void metrics_add(WorkMetrics *total, XtkFrameMetrics const *frame) {
	total->built     += frame->nodes_built;
	total->compared  += frame->nodes_compared;
	total->skipped   += frame->nodes_skipped;
	total->patches   += frame->property_patches;
	total->mutations += frame->mutations;
}

static int run_runtime(RuntimeWork work, char const *name) {
	RuntimeFixture fixture = {0};
	if (!runtime_fixture_init(&fixture, work) || !runtime_frame(&fixture, NULL)) return 1;
	for (int i = 0; i < WARMUP_ITERATIONS; i++)
		if (!runtime_frame(&fixture, NULL)) return 1;

	fixture.host.counts = (WorkCounts) {0};
	fixture.model.built = 0u;
	xtk_alloc_test_reset();
	WorkMetrics metrics = {0};
	uint64_t    begin   = clock_ns();
	for (int i = 0; i < MEASURE_ITERATIONS; i++) {
		XtkFrameMetrics frame = {0};
		if (!runtime_frame(&fixture, &frame)) return 1;
		metrics_add(&metrics, &frame);
	}
	uint64_t      elapsed = clock_ns() - begin;
	XtkAllocStats alloc   = xtk_alloc_test_stats();
	WorkCounts    counts  = fixture.host.counts;
	printf(
	  "workload=%s iterations=%d elapsed_ns=%" PRIu64 " ns_per_iteration=%" PRIu64 " nodes_built=%" PRIu64
	  " nodes_compared=%" PRIu64 " nodes_skipped=%" PRIu64 " property_patches=%" PRIu64 " mutations=%" PRIu64
	  " creates=%" PRIu64 " destroys=%" PRIu64 " moves=%" PRIu64 " prepares=%" PRIu64 " commits=%" PRIu64
	  " allocation_attempts=%" PRIu64 " allocation_peak_bytes=%zu\n",
	  name, MEASURE_ITERATIONS, elapsed, elapsed / MEASURE_ITERATIONS, metrics.built, metrics.compared, metrics.skipped,
	  metrics.patches, metrics.mutations, counts.creates, counts.destroys, counts.moves, counts.prepares,
	  counts.commits, alloc.attempts, alloc.peak_bytes
	);
	bool valid = counts.prepares == MEASURE_ITERATIONS && counts.commits == MEASURE_ITERATIONS;
	if (work == RUNTIME_FORM) valid = valid && metrics.patches >= FORM_PAIRS * 2u * MEASURE_ITERATIONS;
	else valid = valid && counts.creates > 0u && counts.destroys > 0u;
	runtime_fixture_dispose(&fixture);
	return valid ? 0 : 1;
}

static XtkBatchResult *commit_batch(XtkHost *host, XtkBatch *batch) {
	XtkPrepare  *prepare = NULL;
	XtkBatchDiag diagnostic;
	if (host->vt->prepare(host, batch, &prepare, &diagnostic) != XTK_BATCH_OK) return NULL;
	return host->vt->commit(host, prepare, &diagnostic);
}

static XtkCtrl result_control(XtkBatchResult const *result, XtkLocalId local) {
	for (uint32_t i = 0; i < result->control_count; i++)
		if (result->controls [i].local == local) return result->controls [i].control;
	return XTK_CTRL_INVALID;
}

static XtkCtrl *canvas_mount(WorkHost *host, XtkCtrl *canvas) {
	XtkBatch *batch = xtk_batch_alloc(host->base.vt->revision(&host->base));
	if (!batch) return NULL;
	XtkLocalId   root = xtk_batch_create(batch, XTK_CTRL_CANVAS, xtk_ref_none(), xtk_ref_none(), NULL, 0u);
	XtkLocalId   locals [CANVAS_ITEMS];
	XtkPropPatch text = {
	  .id    = XTK_PROP_TEXT,
	  .value = {.kind = XTK_VALUE_STRING, .u.string = {.data = "cell", .len = 4u}},
	};
	for (uint32_t i = 0; i < CANVAS_ITEMS; i++)
		locals [i] = xtk_batch_create(batch, XTK_CTRL_TEXT, xtk_ref_local(root), xtk_ref_none(), &text, 1u);
	XtkBatchResult *result = commit_batch(&host->base, batch);
	if (!result) {
		xtk_batch_free(batch);
		return NULL;
	}
	XtkCtrl *controls = xtk_alloc(sizeof(*controls) * CANVAS_ITEMS);
	if (controls) {
		*canvas = result_control(result, root);
		for (uint32_t i = 0; i < CANVAS_ITEMS; i++) controls [i] = result_control(result, locals [i]);
	}
	xtk_batch_result_destroy(result);
	xtk_batch_free(batch);
	return controls;
}

static bool canvas_patch(WorkHost *host, XtkCtrl const *controls, uint32_t revision) {
	XtkBatch *batch = xtk_batch_alloc(host->base.vt->revision(&host->base));
	if (!batch) return false;
	char text [32];
	int  len = snprintf(text, sizeof(text), "edit-%u", revision);
	if (len < 0) {
		xtk_batch_free(batch);
		return false;
	}
	XtkValue value = {
	  .kind = XTK_VALUE_STRING, .u.string = {.data = text, .len = ( uint32_t ) len}
    };
	XtkChangeStamp change = {.source = 1u, .revision = revision + 1u};
	for (uint32_t i = 0; i < CANVAS_PATCHES; i++) {
		uint32_t index = (revision * CANVAS_PATCHES + i) % CANVAS_ITEMS;
		if (!xtk_batch_set(batch, xtk_ref_existing(controls [index]), XTK_PROP_TEXT, value, change)) {
			xtk_batch_free(batch);
			return false;
		}
	}
	XtkBatchResult *result = commit_batch(&host->base, batch);
	xtk_batch_free(batch);
	if (!result) return false;
	xtk_batch_result_destroy(result);
	return true;
}

static int run_canvas(void) {
	XtkHost *inner = xtk_retained_host_create();
	WorkHost host;
	if (!inner || !work_host_init(&host, inner)) return 1;
	XtkCtrl  canvas   = XTK_CTRL_INVALID;
	XtkCtrl *controls = canvas_mount(&host, &canvas);
	if (!controls || canvas == XTK_CTRL_INVALID) return 1;
	for (uint32_t i = 0; i < WARMUP_ITERATIONS; i++)
		if (!canvas_patch(&host, controls, i)) return 1;

	host.counts = (WorkCounts) {0};
	xtk_alloc_test_reset();
	uint64_t begin = clock_ns();
	for (uint32_t i = 0; i < MEASURE_ITERATIONS; i++)
		if (!canvas_patch(&host, controls, i + WARMUP_ITERATIONS)) return 1;
	uint64_t      elapsed = clock_ns() - begin;
	XtkAllocStats alloc   = xtk_alloc_test_stats();
	printf(
	  "workload=imperative_canvas iterations=%d elapsed_ns=%" PRIu64 " ns_per_iteration=%" PRIu64
	  " nodes_built=0 nodes_compared=0 nodes_skipped=0 property_patches=%" PRIu64 " mutations=%" PRIu64
	  " creates=%" PRIu64 " destroys=%" PRIu64 " moves=%" PRIu64 " prepares=%" PRIu64 " commits=%" PRIu64
	  " allocation_attempts=%" PRIu64 " allocation_peak_bytes=%zu\n",
	  MEASURE_ITERATIONS, elapsed, elapsed / MEASURE_ITERATIONS, host.counts.patches, host.counts.patches,
	  host.counts.creates, host.counts.destroys, host.counts.moves, host.counts.prepares, host.counts.commits,
	  alloc.attempts, alloc.peak_bytes
	);
	bool      valid = host.counts.patches == CANVAS_PATCHES * MEASURE_ITERATIONS
	               && host.counts.prepares == MEASURE_ITERATIONS
	               && host.counts.commits == MEASURE_ITERATIONS;
	XtkBatch *drop  = xtk_batch_alloc(host.base.vt->revision(&host.base));
	if (!drop || !xtk_batch_drop(drop, xtk_ref_existing(canvas))) valid = false;
	XtkBatchResult *result = drop ? commit_batch(&host.base, drop) : NULL;
	if (!result) valid = false;
	xtk_batch_result_destroy(result);
	xtk_batch_free(drop);
	xtk_alloc_free(controls);
	xtk_retained_host_destroy(inner);
	return valid ? 0 : 1;
}

int main(void) {
	setvbuf(stdout, NULL, _IONBF, 0);
	if (run_runtime(RUNTIME_FORM, "batched_form")) return 1;
	if (run_runtime(RUNTIME_PAGE, "page_switch")) return 1;
	if (run_canvas()) return 1;
	return 0;
}
