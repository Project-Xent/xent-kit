#include "comp_bench.h"

#include <stdlib.h>
#include <string.h>
#include <time.h>

enum
{
	TREE_REGION_REF = 1u << 31,
	TREE_REGIONS    = 16,
	TREE_WARMUP     = 32,
};

typedef struct TreeState {
	CompNode node;
	uint32_t seen;
	bool     live;
} TreeState;

typedef struct TreeRecord {
	CompNode node;
	uint32_t subtree_end;
} TreeRecord;

typedef struct TreeRun {
	CompWorkload workload;
	CompMetrics *metrics;
	TreeRecord  *records;
	TreeState   *state;
	uint32_t    *old_order;
	uint32_t    *next_order;
	uint32_t    *positions;
	uint32_t    *tails;
	uint64_t     region_revision [TREE_REGIONS];
	uint64_t     next_region_revision [TREE_REGIONS];
	bool         region_skip [TREE_REGIONS];
	uint32_t     width;
	uint32_t     count;
	uint32_t     order_count;
	uint32_t     old_count;
	uint32_t     epoch;
	uint32_t     region_start;
	bool         measuring;
	bool         failed;
} TreeRun;

static uint64_t clock_ns(void) {
	struct timespec value;
	if (timespec_get(&value, TIME_UTC) != TIME_UTC) return 0u;
	return ( uint64_t ) value.tv_sec * UINT64_C(1000000000) + ( uint64_t ) value.tv_nsec;
}

static bool tree_begin_frame(void *ctx, uint32_t frame) {
	TreeRun *run = ( TreeRun * ) ctx;
	( void ) frame;
	run->count       = 0u;
	run->order_count = 0u;
	run->failed      = false;
	run->epoch++;
	memset(run->region_skip, 0, sizeof(run->region_skip));
	memcpy(run->next_region_revision, run->region_revision, sizeof(run->region_revision));
	return true;
}

static bool tree_push(TreeRun *run, CompNode node) {
	if (run->count >= run->width + TREE_REGIONS) {
		run->failed = true;
		return false;
	}
	run->records [run->count++] = (TreeRecord) {.node = node};
	if (node.key) run->next_order [run->order_count++] = node.key;
	if (run->measuring) run->metrics->nodes_built++;
	return true;
}

static bool tree_begin_region(void *ctx, uint32_t id, uint64_t revision, uint32_t descendants) {
	TreeRun *run = ( TreeRun * ) ctx;
	if (id >= TREE_REGIONS) return false;
	run->next_region_revision [id] = revision;
	if (run->region_revision [id] == revision && run->epoch > 1u) {
		run->region_skip [id] = true;
		CompNode ref          = {.region = id, .flags = TREE_REGION_REF, .value = descendants};
		if (run->measuring) run->metrics->nodes_skipped += descendants;
		( void ) tree_push(run, ref);
		return false;
	}
	run->region_start = run->count;
	return true;
}

static bool tree_node(void *ctx, CompNode node) { return tree_push(( TreeRun * ) ctx, node); }

static bool tree_end_region(void *ctx, uint32_t id, uint64_t revision) {
	TreeRun *run = ( TreeRun * ) ctx;
	( void ) revision;
	if (run->region_skip [id]) return true;
	for (uint32_t i = run->region_start; i < run->count; i++) run->records [i].subtree_end = run->count;
	return true;
}

static uint32_t lower_bound(uint32_t const *tails, uint32_t count, uint32_t value) {
	uint32_t lo = 0u, hi = count;
	while (lo < hi) {
		uint32_t mid = lo + (hi - lo) / 2u;
		if (tails [mid] < value) lo = mid + 1u;
		else hi = mid;
	}
	return lo;
}

static uint32_t tree_move_count(TreeRun *run) {
	for (uint32_t i = 0; i < run->old_count; i++) run->positions [run->old_order [i]] = i + 1u;
	uint32_t lis = 0u, matched = 0u;
	for (uint32_t i = 0; i < run->order_count; i++) {
		uint32_t pos = run->positions [run->next_order [i]];
		if (!pos) continue;
		uint32_t at     = lower_bound(run->tails, lis, pos);
		run->tails [at] = pos;
		if (at == lis) lis++;
		matched++;
	}
	memset(run->positions, 0, sizeof(*run->positions) * (run->width + 1u));
	return matched - lis;
}

static void tree_apply_node(TreeRun *run, CompNode node) {
	TreeState *state = &run->state [node.key];
	if (run->measuring) run->metrics->nodes_compared++;
	if (!state->live) {
		if (run->measuring) run->metrics->creates++;
	}
	else if (memcmp(&state->node, &node, sizeof(node)) != 0 && run->measuring) { run->metrics->patches++; }
	state->node = node;
	state->seen = run->epoch;
	state->live = true;
}

static void tree_destroy_missing(TreeRun *run) {
	for (uint32_t key = 1u; key <= run->width; key++) {
		TreeState *state = &run->state [key];
		if (!state->live || state->seen == run->epoch) continue;
		uint32_t region = state->node.region;
		if (region < TREE_REGIONS && run->region_skip [region]) continue;
		state->live = false;
		if (run->measuring) run->metrics->destroys++;
	}
}

static bool tree_end_frame(void *ctx) {
	TreeRun *run = ( TreeRun * ) ctx;
	if (run->failed) return false;
	for (uint32_t i = 0; i < run->count; i++) {
		CompNode node = run->records [i].node;
		if (!node.key) continue;
		tree_apply_node(run, node);
	}
	tree_destroy_missing(run);
	if (run->workload != COMP_REGIONS && run->measuring) run->metrics->moves += tree_move_count(run);
	if (run->workload != COMP_REGIONS) {
		memcpy(run->old_order, run->next_order, sizeof(*run->old_order) * run->order_count);
		run->old_count = run->order_count;
	}
	memcpy(run->region_revision, run->next_region_revision, sizeof(run->region_revision));
	return true;
}

static void tree_checksum(TreeRun *run) {
	uint64_t hash = UINT64_C(1469598103934665603);
	for (uint32_t key = 1u; key <= run->width; key++) {
		if (!run->state [key].live) continue;
		hash ^= key;
		hash *= UINT64_C(1099511628211);
		hash ^= run->state [key].node.value;
		hash *= UINT64_C(1099511628211);
	}
	run->metrics->checksum = hash;
}

static bool tree_init(TreeRun *run, CompWorkload workload, uint32_t width, CompMetrics *metrics) {
	*run            = (TreeRun) {.workload = workload, .metrics = metrics, .width = width};
	run->records    = ( TreeRecord * ) calloc(width + TREE_REGIONS, sizeof(*run->records));
	run->state      = ( TreeState * ) calloc(width + 1u, sizeof(*run->state));
	run->old_order  = ( uint32_t * ) calloc(width, sizeof(*run->old_order));
	run->next_order = ( uint32_t * ) calloc(width, sizeof(*run->next_order));
	run->positions  = ( uint32_t * ) calloc(width + 1u, sizeof(*run->positions));
	run->tails      = ( uint32_t * ) calloc(width, sizeof(*run->tails));
	return run->records && run->state && run->old_order && run->next_order && run->positions && run->tails;
}

static void tree_dispose(TreeRun *run) {
	free(run->tails);
	free(run->positions);
	free(run->next_order);
	free(run->old_order);
	free(run->state);
	free(run->records);
}

bool comp_run_tree(CompWorkload workload, uint32_t width, uint32_t frames, CompMetrics *metrics) {
	if (!metrics || !width || !frames) return false;
	*metrics = (CompMetrics) {0};
	TreeRun run;
	if (!tree_init(&run, workload, width, metrics)) {
		tree_dispose(&run);
		return false;
	}
	CompSink sink = {
	  .ctx          = &run,
	  .begin_frame  = tree_begin_frame,
	  .begin_region = tree_begin_region,
	  .node         = tree_node,
	  .end_region   = tree_end_region,
	  .end_frame    = tree_end_frame,
	};
	for (uint32_t i = 0; i < TREE_WARMUP; i++)
		if (!comp_emit_workload(workload, width, i, &sink)) return false;
	run.measuring  = true;
	uint64_t begin = clock_ns();
	for (uint32_t i = 0; i < frames; i++)
		if (!comp_emit_workload(workload, width, i + TREE_WARMUP, &sink)) return false;
	metrics->elapsed_ns       = clock_ns() - begin;
	metrics->frames           = frames;
	metrics->transient_peak   = sizeof(TreeRecord) * (width + TREE_REGIONS) + sizeof(uint32_t) * width;
	metrics->persistent_bytes = sizeof(TreeState) * (width + 1u) + sizeof(uint32_t) * (3u * width + 1u);
	tree_checksum(&run);
	tree_dispose(&run);
	return true;
}
