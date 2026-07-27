#include <xtk/xtk_reconcile.h>
#include "xtk_retained.h"

#include "xtk_alloc_internal.h"
#include "xtk_internal.h"
#include "runtime/xtk_runtime_internal.h"
#include "reconcile/xtk_scratch.h"

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

enum
{
	ITEM_DELTA = 8,
};

typedef enum Workload
{
	WORKLOAD_POSITIONAL,
	WORKLOAD_KEYED_APPEND,
	WORKLOAD_KEYED_PREPEND,
	WORKLOAD_KEYED_MIDDLE_INSERT,
	WORKLOAD_KEYED_DELETE,
	WORKLOAD_KEYED_REVERSE,
	WORKLOAD_KEYED_SHUFFLE,
} Workload;

typedef struct BenchModel {
	Workload workload;
	bool     changed;
	int      nitem;
	int      depth;
	uint64_t built;
} BenchModel;

typedef struct BenchCounts {
	uint64_t creates;
	uint64_t destroys;
	uint64_t moves;
	uint64_t prepare_ns;
	uint64_t commit_ns;
} BenchCounts;

typedef struct BenchMetrics {
	uint64_t built;
	uint64_t compared;
	uint64_t skipped;
	uint64_t patches;
	uint64_t mutations;
} BenchMetrics;

typedef struct BenchHost {
	XtkHost       base;
	XtkHost      *inner;
	XtkHostVtable vt;
	BenchCounts   counts;
} BenchHost;

typedef struct Fixture {
	XtkHost   *inner;
	BenchHost  host;
	XtkRt     *runtime;
	BenchModel model;
} Fixture;

static void request_frame(void *ctx) { ( void ) ctx; }

static void noop_update(void *model, XtkMsg msg) {
	( void ) model;
	( void ) msg;
}

static int workload_count(Workload workload, bool changed, int nitem) {
	if (!changed) return nitem;
	if (workload == WORKLOAD_KEYED_APPEND
		|| workload == WORKLOAD_KEYED_PREPEND
		|| workload == WORKLOAD_KEYED_MIDDLE_INSERT)
		return nitem + ITEM_DELTA;
	if (workload == WORKLOAD_KEYED_DELETE) return nitem - ITEM_DELTA;
	return nitem;
}

static int middle_insert_id(int index, int nitem) {
	int middle = nitem / 2;
	if (index < middle) return index;
	if (index < middle + ITEM_DELTA) return nitem + index - middle;
	return index - ITEM_DELTA;
}

static int delete_id(int index, int nitem) {
	int middle = nitem / 2 - ITEM_DELTA / 2;
	return index < middle ? index : index + ITEM_DELTA;
}

static int shuffle_id(int index, int count) {
	if ((index & 1) == 0) return index + 1 < count ? index + 1 : index;
	return index - 1;
}

static int workload_id(Workload workload, bool changed, int index, int count, int nitem) {
	if (!changed) return index;
	if (workload == WORKLOAD_KEYED_PREPEND && changed) return index - ITEM_DELTA;
	if (workload == WORKLOAD_KEYED_MIDDLE_INSERT) return middle_insert_id(index, nitem);
	if (workload == WORKLOAD_KEYED_DELETE) return delete_id(index, nitem);
	if (workload == WORKLOAD_KEYED_REVERSE && changed) return count - index - 1;
	if (workload == WORKLOAD_KEYED_SHUFFLE && changed) return shuffle_id(index, count);
	return index;
}

static XtkEl *build_positional_level(XtkUi *ui, BenchModel *model, int depth) {
	XtkEl **items = xtk_children_alloc(ui, model->nitem);
	if (!items) return NULL;
	int leaf_count = depth > 1 ? model->nitem - 1 : model->nitem;
	for (int i = 0; i < leaf_count; i++) {
		items [i] = xtk_text(ui, "item", (XtkTextDesc) {0});
		if (!items [i]) return NULL;
		model->built++;
	}
	if (depth > 1) {
		items [model->nitem - 1] = build_positional_level(ui, model, depth - 1);
		if (!items [model->nitem - 1]) return NULL;
	}
	model->built++;
	return xtk_column(ui, (XtkStackDesc) {0}, items);
}

static XtkEl *build_items(XtkUi *ui, BenchModel *model) {
	Workload workload = model->workload;
	bool     changed  = model->changed;
	int      nitem    = model->nitem;
	if (workload == WORKLOAD_POSITIONAL && model->depth > 1) return build_positional_level(ui, model, model->depth);

	int     count = workload_count(workload, changed, nitem);
	XtkEl **items = xtk_children_alloc(ui, count);
	if (!items) return NULL;
	for (int i = 0; i < count; i++) {
		int    id = workload_id(workload, changed, i, count, nitem);
		XtkEl *el = xtk_text(ui, "item", (XtkTextDesc) {0});
		if (!el) return NULL;
		if (workload != WORKLOAD_POSITIONAL) el = xtk_keyed(ui, xtk_fmt(ui, "item-%d", id), el);
		if (workload != WORKLOAD_POSITIONAL && XTK_EL_DATA(el)->key.kind == XTK_KEY_NONE) return NULL;
		items [i] = el;
		model->built++;
	}
	model->built++;
	return xtk_column(ui, (XtkStackDesc) {0}, items);
}

static XtkEl *bench_view(XtkUi *ui, void *model) {
	BenchModel *m = ( BenchModel * ) model;
	return build_items(ui, m);
}

static void count_ops(BenchHost *host, XtkBatch const *batch) {
	for (uint32_t i = 0; i < batch->count; i++) {
		switch (batch->ops [i].kind) {
		case XTK_BATCH_OP_CREATE  : host->counts.creates++; break;
		case XTK_BATCH_OP_DESTROY : host->counts.destroys++; break;
		case XTK_BATCH_OP_MOVE    : host->counts.moves++; break;
		default                   : break;
		}
	}
}

static uint64_t      clock_ns(void);

static XtkBatchError bench_prepare(XtkHost *raw, XtkBatch *batch, XtkPrepare **prepare, XtkBatchDiag *diagnostic) {
	BenchHost *host = ( BenchHost * ) raw;
	count_ops(host, batch);
	uint64_t      begin      = clock_ns();
	XtkBatchError error      = host->inner->vt->prepare(host->inner, batch, prepare, diagnostic);
	host->counts.prepare_ns += clock_ns() - begin;
	return error;
}

static XtkBatchResult *bench_commit(XtkHost *raw, XtkPrepare *prepare, XtkBatchDiag *diagnostic) {
	BenchHost      *host    = ( BenchHost * ) raw;
	uint64_t        begin   = clock_ns();
	XtkBatchResult *result  = host->inner->vt->commit(host->inner, prepare, diagnostic);
	host->counts.commit_ns += clock_ns() - begin;
	return result;
}

static bool bench_host_init(BenchHost *host, XtkHost *inner) {
	if (!host || !inner) return false;
	*host            = (BenchHost) {0};
	host->inner      = inner;
	host->vt         = *inner->vt;
	host->vt.prepare = bench_prepare;
	host->vt.commit  = bench_commit;
	host->base.vt    = &host->vt;
	host->base.impl  = inner->impl;
	return true;
}

static bool fixture_init(Fixture *fixture) {
	fixture->inner = xtk_retained_host_create();
	if (!fixture->inner || !bench_host_init(&fixture->host, fixture->inner)) return false;
	XentNodeId host_root = ( XentNodeId ) fixture->host.base.vt->root(&fixture->host.base);
	XtkRtCfg   cfg       = {.request_frame = request_frame};
	fixture->runtime = xtk_rt_create(&fixture->host.base, &cfg, host_root, &fixture->model, noop_update, bench_view);
	if (!fixture->runtime) xtk_retained_host_destroy(fixture->inner);
	return fixture->runtime != NULL;
}

static void fixture_dispose(Fixture *fixture) {
	xtk_rt_destroy(fixture->runtime);
	xtk_retained_host_destroy(fixture->inner);
}

static bool reconcile_phase(Fixture *fixture, Workload workload, bool changed, XtkFrameMetrics *metrics) {
	fixture->model.workload = workload;
	fixture->model.changed  = changed;
	xtk_rt_invalidate(fixture->runtime);
	XtkFrameResult fr = xtk_rt_frame(fixture->runtime);
	if (metrics) *metrics = fr.metrics;
	return fr.status == XTK_FRAME_COMMITTED;
}

static uint64_t clock_ns(void) {
	struct timespec value;
	if (timespec_get(&value, TIME_UTC) != TIME_UTC) return 0u;
	return ( uint64_t ) value.tv_sec * UINT64_C(1000000000) + ( uint64_t ) value.tv_nsec;
}

static int warmup_iterations(int nodes) {
	if (nodes >= 1024) return 1;
	return 2;
}

static int measure_iterations(int nodes) {
	if (nodes >= 10000) return 1;
	if (nodes >= 1024) return 4;
	return 16;
}

static char const *workload_name(Workload workload) {
	static char const *const names [] = {
	  "stable_positional",
	  "keyed_append",
	  "keyed_prepend",
	  "keyed_middle_insert",
	  "keyed_delete",
	  "keyed_reverse",
	  "keyed_shuffle",
	};
	return names [workload];
}

static bool workload_parse(char const *name, Workload *out) {
	for (Workload workload = WORKLOAD_POSITIONAL; workload <= WORKLOAD_KEYED_SHUFFLE;
	  workload             = ( Workload ) (workload + 1))
		if (strcmp(name, workload_name(workload)) == 0) {
			*out = workload;
			return true;
		}
	return false;
}

static void metrics_add(BenchMetrics *total, XtkFrameMetrics const *frame) {
	total->built     += frame->nodes_built;
	total->compared  += frame->nodes_compared;
	total->skipped   += frame->nodes_skipped;
	total->patches   += frame->property_patches;
	total->mutations += frame->mutations;
}

static int run_workload(Workload workload, int nitem, int depth) {
	if (workload < WORKLOAD_POSITIONAL || workload > WORKLOAD_KEYED_SHUFFLE || nitem < 1 || depth < 1) return 2;
	if (workload != WORKLOAD_POSITIONAL && nitem < ITEM_DELTA * 2) return 2;
	Fixture fixture = {0};
	if (!fixture_init(&fixture)) return 1;
	fixture.model.nitem    = nitem;
	fixture.model.depth    = depth;
	fixture.host.counts    = (BenchCounts) {0};
	uint64_t initial_begin = clock_ns();
	if (!reconcile_phase(&fixture, workload, false, NULL)) {
		fixture_dispose(&fixture);
		return 1;
	}
	uint64_t    initial_ns     = clock_ns() - initial_begin;
	BenchCounts initial_counts = fixture.host.counts;

	int         nodes          = nitem * depth;
	int         warmup         = warmup_iterations(nodes);
	int         iterations     = measure_iterations(nodes);
	for (int i = 0; i < warmup; i++)
		if (!reconcile_phase(&fixture, workload, (i & 1) == 0, NULL)) {
			fixture_dispose(&fixture);
			return 1;
		}
	if (!reconcile_phase(&fixture, workload, false, NULL)) {
		fixture_dispose(&fixture);
		return 1;
	}

	xtk_alloc_test_reset();
	fixture.host.counts  = (BenchCounts) {0};
	fixture.model.built  = 0u;
	BenchMetrics metrics = {0};
	uint64_t     begin   = clock_ns();
	for (int i = 0; i < iterations; i++) {
		XtkFrameMetrics frame = {0};
		if (!reconcile_phase(&fixture, workload, (i & 1) == 0, &frame)) {
			fixture_dispose(&fixture);
			return 1;
		}
		metrics_add(&metrics, &frame);
	}
	uint64_t      elapsed        = clock_ns() - begin;
	XtkAllocStats allocations    = xtk_alloc_test_stats();
	size_t        plan_capacity  = fixture.runtime->plan_scratch->capacity;
	size_t        match_capacity = fixture.runtime->scratch->capacity;

	printf(
	  "workload=%s width=%d depth=%d delta=%d iterations=%d elapsed_ns=%" PRIu64 " ns_per_iteration=%" PRIu64
	  " allocation_attempts=%" PRIu64 " creates=%" PRIu64 " destroys=%" PRIu64 " moves=%" PRIu64 " nodes_built=%" PRIu64
	  " nodes_compared=%" PRIu64 " nodes_skipped=%" PRIu64 " property_patches=%" PRIu64 " mutations=%" PRIu64
	  " allocation_peak_bytes=%zu initial_ns=%" PRIu64 " initial_prepare_ns=%" PRIu64 " initial_commit_ns=%" PRIu64
	  " plan_capacity=%zu match_capacity=%zu\n",
	  workload_name(workload), nitem, depth,
	  workload == WORKLOAD_KEYED_APPEND
		  || workload == WORKLOAD_KEYED_PREPEND
		  || workload == WORKLOAD_KEYED_MIDDLE_INSERT
		  || workload == WORKLOAD_KEYED_DELETE
		? ITEM_DELTA
		: 0,
	  iterations, elapsed, elapsed / ( uint64_t ) iterations, allocations.attempts, fixture.host.counts.creates,
	  fixture.host.counts.destroys, fixture.host.counts.moves, metrics.built, metrics.compared, metrics.skipped,
	  metrics.patches, metrics.mutations, allocations.peak_bytes, initial_ns, initial_counts.prepare_ns,
	  initial_counts.commit_ns, plan_capacity, match_capacity
	);
	if (workload == WORKLOAD_POSITIONAL && allocations.attempts != 0u) {
		fixture_dispose(&fixture);
		return 1;
	}
	fixture_dispose(&fixture);
	return 0;
}

int main(int argc, char **argv) {
	setvbuf(stdout, NULL, _IONBF, 0);
	if (argc == 4) {
		Workload workload;
		if (!workload_parse(argv [1], &workload)) return 2;
		return run_workload(workload, atoi(argv [2]), atoi(argv [3]));
	}
	if (argc != 1) return 2;
	static int const sizes [] = {128, 1024, 10000};
	for (size_t s = 0; s < sizeof(sizes) / sizeof(sizes [0]); s++) {
		for (Workload workload = WORKLOAD_POSITIONAL; workload <= WORKLOAD_KEYED_SHUFFLE;
		  workload             = ( Workload ) (workload + 1))
			if (run_workload(workload, sizes [s], 1)) {
				printf("error=benchmark_failed workload=%s items=%d\n", workload_name(workload), sizes [s]);
				return 1;
			}
	}

	static struct {
		int width;
		int depth;
	} const shapes [] = {
	  {4,   4},
      {8,   8},
      {32,  4},
      {128, 8}
    };

	for (size_t i = 0; i < sizeof(shapes) / sizeof(shapes [0]); i++)
		if (run_workload(WORKLOAD_POSITIONAL, shapes [i].width, shapes [i].depth)) return 1;
	return 0;
}
