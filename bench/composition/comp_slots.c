#include "comp_bench.h"

#include <stdlib.h>
#include <string.h>
#include <time.h>

enum
{
	SLOT_REGION_REF = 1u << 31,
	SLOT_REGIONS    = 16,
	SLOT_WARMUP     = 32,
};

typedef struct SlotState {
	CompNode node;
	uint32_t seen;
	bool     live;
} SlotState;

typedef struct SlotBlock {
	uint32_t key;
	uint32_t value;
	uint32_t type;
	uint32_t meta;
} SlotBlock;

typedef struct SlotRun {
	CompWorkload workload;
	CompMetrics *metrics;
	SlotBlock   *blocks;
	SlotState   *state;
	uint32_t    *old_order;
	uint32_t    *next_order;
	uint32_t    *positions;
	uint32_t    *tails;
	uint64_t     region_revision [SLOT_REGIONS];
	uint64_t     next_region_revision [SLOT_REGIONS];
	bool         region_skip [SLOT_REGIONS];
	uint32_t     width;
	uint32_t     count;
	uint32_t     order_count;
	uint32_t     old_count;
	uint32_t     epoch;
	bool         measuring;
	bool         failed;
} SlotRun;

static uint64_t clock_ns(void) {
	struct timespec value;
	if (timespec_get(&value, TIME_UTC) != TIME_UTC) return 0u;
	return ( uint64_t ) value.tv_sec * UINT64_C(1000000000) + ( uint64_t ) value.tv_nsec;
}

static uint32_t pack_meta(CompNode node) {
	return (node.region & 0xffu) | ((node.flags & 0xffu) << 8u) | ((node.provider & 0xffffu) << 16u);
}

static CompNode unpack_block(SlotBlock block) {
	return (CompNode) {
	  .key      = block.key,
	  .type     = block.type,
	  .value    = block.value,
	  .region   = block.meta & 0xffu,
	  .flags    = (block.meta >> 8u) & 0xffu,
	  .provider = block.meta >> 16u,
	};
}

static bool slot_begin_frame(void *ctx, uint32_t frame) {
	SlotRun *run = ( SlotRun * ) ctx;
	( void ) frame;
	run->count       = 0u;
	run->order_count = 0u;
	run->failed      = false;
	run->epoch++;
	memset(run->region_skip, 0, sizeof(run->region_skip));
	memcpy(run->next_region_revision, run->region_revision, sizeof(run->region_revision));
	return true;
}

static bool slot_push(SlotRun *run, CompNode node) {
	if (run->count >= run->width + SLOT_REGIONS) {
		run->failed = true;
		return false;
	}
	run->blocks [run->count++] = (SlotBlock) {
	  .key   = node.key,
	  .value = node.value,
	  .type  = node.type,
	  .meta  = pack_meta(node),
	};
	if (node.key) run->next_order [run->order_count++] = node.key;
	if (run->measuring) run->metrics->nodes_built++;
	return true;
}

static bool slot_begin_region(void *ctx, uint32_t id, uint64_t revision, uint32_t descendants) {
	SlotRun *run = ( SlotRun * ) ctx;
	if (id >= SLOT_REGIONS) return false;
	run->next_region_revision [id] = revision;
	if (run->region_revision [id] != revision || run->epoch <= 1u) return true;
	run->region_skip [id] = true;
	CompNode ref          = {.region = id, .flags = SLOT_REGION_REF, .value = descendants};
	if (run->measuring) run->metrics->nodes_skipped += descendants;
	( void ) slot_push(run, ref);
	return false;
}

static bool slot_node(void *ctx, CompNode node) { return slot_push(( SlotRun * ) ctx, node); }

static bool slot_end_region(void *ctx, uint32_t id, uint64_t revision) {
	( void ) ctx;
	( void ) id;
	( void ) revision;
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

static uint32_t slot_move_count(SlotRun *run) {
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

static void slot_apply_node(SlotRun *run, CompNode node) {
	SlotState *state = &run->state [node.key];
	if (run->measuring) run->metrics->nodes_compared++;
	if (!state->live) {
		if (run->measuring) run->metrics->creates++;
	}
	else if (memcmp(&state->node, &node, sizeof(node)) != 0 && run->measuring) { run->metrics->patches++; }
	state->node = node;
	state->seen = run->epoch;
	state->live = true;
}

static void slot_destroy_missing(SlotRun *run) {
	for (uint32_t key = 1u; key <= run->width; key++) {
		SlotState *state = &run->state [key];
		if (!state->live || state->seen == run->epoch) continue;
		uint32_t region = state->node.region;
		if (region < SLOT_REGIONS && run->region_skip [region]) continue;
		state->live = false;
		if (run->measuring) run->metrics->destroys++;
	}
}

static bool slot_end_frame(void *ctx) {
	SlotRun *run = ( SlotRun * ) ctx;
	if (run->failed) return false;
	for (uint32_t i = 0; i < run->count; i++) {
		CompNode node = unpack_block(run->blocks [i]);
		if (!node.key) continue;
		slot_apply_node(run, node);
	}
	slot_destroy_missing(run);
	if (run->workload != COMP_REGIONS && run->measuring) run->metrics->moves += slot_move_count(run);
	if (run->workload != COMP_REGIONS) {
		memcpy(run->old_order, run->next_order, sizeof(*run->old_order) * run->order_count);
		run->old_count = run->order_count;
	}
	memcpy(run->region_revision, run->next_region_revision, sizeof(run->region_revision));
	return true;
}

static void slot_checksum(SlotRun *run) {
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

static bool slot_init(SlotRun *run, CompWorkload workload, uint32_t width, CompMetrics *metrics) {
	*run            = (SlotRun) {.workload = workload, .metrics = metrics, .width = width};
	run->blocks     = ( SlotBlock * ) calloc(width + SLOT_REGIONS, sizeof(*run->blocks));
	run->state      = ( SlotState * ) calloc(width + 1u, sizeof(*run->state));
	run->old_order  = ( uint32_t * ) calloc(width, sizeof(*run->old_order));
	run->next_order = ( uint32_t * ) calloc(width, sizeof(*run->next_order));
	run->positions  = ( uint32_t * ) calloc(width + 1u, sizeof(*run->positions));
	run->tails      = ( uint32_t * ) calloc(width, sizeof(*run->tails));
	return run->blocks && run->state && run->old_order && run->next_order && run->positions && run->tails;
}

static void slot_dispose(SlotRun *run) {
	free(run->tails);
	free(run->positions);
	free(run->next_order);
	free(run->old_order);
	free(run->state);
	free(run->blocks);
}

bool comp_run_slots(CompWorkload workload, uint32_t width, uint32_t frames, CompMetrics *metrics) {
	if (!metrics || !width || !frames) return false;
	*metrics = (CompMetrics) {0};
	SlotRun run;
	if (!slot_init(&run, workload, width, metrics)) {
		slot_dispose(&run);
		return false;
	}
	CompSink sink = {
	  .ctx          = &run,
	  .begin_frame  = slot_begin_frame,
	  .begin_region = slot_begin_region,
	  .node         = slot_node,
	  .end_region   = slot_end_region,
	  .end_frame    = slot_end_frame,
	};
	for (uint32_t i = 0; i < SLOT_WARMUP; i++)
		if (!comp_emit_workload(workload, width, i, &sink)) return false;
	run.measuring  = true;
	uint64_t begin = clock_ns();
	for (uint32_t i = 0; i < frames; i++)
		if (!comp_emit_workload(workload, width, i + SLOT_WARMUP, &sink)) return false;
	metrics->elapsed_ns       = clock_ns() - begin;
	metrics->frames           = frames;
	metrics->transient_peak   = sizeof(SlotBlock) * (width + SLOT_REGIONS) + sizeof(uint32_t) * width;
	metrics->persistent_bytes = sizeof(SlotState) * (width + 1u) + sizeof(uint32_t) * (3u * width + 1u);
	slot_checksum(&run);
	slot_dispose(&run);
	return true;
}
