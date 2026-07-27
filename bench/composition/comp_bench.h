#ifndef COMP_BENCH_H
#define COMP_BENCH_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

typedef enum CompWorkload
{
	COMP_STABLE,
	COMP_SINGLE_PROP,
	COMP_CONDITIONAL,
	COMP_KEYED_REORDER,
	COMP_REGIONS,
	COMP_COMPONENT,
	COMP_WORKLOAD_COUNT,
} CompWorkload;

typedef enum CompNodeFlags
{
	COMP_NODE_COMPONENT = 1u << 0,
	COMP_NODE_OPAQUE    = 1u << 1,
} CompNodeFlags;

typedef struct CompNode {
	uint32_t key;
	uint32_t parent;
	uint32_t type;
	uint32_t value;
	uint32_t region;
	uint32_t flags;
	uint32_t provider;
} CompNode;

typedef struct CompMetrics {
	uint64_t frames;
	uint64_t nodes_built;
	uint64_t nodes_compared;
	uint64_t nodes_skipped;
	uint64_t creates;
	uint64_t destroys;
	uint64_t moves;
	uint64_t patches;
	uint64_t allocations;
	uint64_t elapsed_ns;
	size_t   transient_peak;
	size_t   persistent_bytes;
	uint64_t checksum;
} CompMetrics;

typedef struct CompSink {
	void *ctx;
	bool  (*begin_frame)(void *ctx, uint32_t frame);
	bool  (*begin_region)(void *ctx, uint32_t id, uint64_t revision, uint32_t descendants);
	bool  (*node)(void *ctx, CompNode node);
	bool  (*end_region)(void *ctx, uint32_t id, uint64_t revision);
	bool  (*end_frame)(void *ctx);
} CompSink;

char const *comp_workload_name(CompWorkload workload);
bool        comp_emit_workload(CompWorkload workload, uint32_t width, uint32_t frame, CompSink *sink);
bool        comp_run_tree(CompWorkload workload, uint32_t width, uint32_t frames, CompMetrics *metrics);
bool        comp_run_slots(CompWorkload workload, uint32_t width, uint32_t frames, CompMetrics *metrics);

#endif
