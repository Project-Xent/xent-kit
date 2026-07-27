#include "comp_bench.h"

enum
{
	REGION_COUNT = 8,
	PROVIDER_ID  = 42,
};

char const *comp_workload_name(CompWorkload workload) {
	static char const *const names [COMP_WORKLOAD_COUNT] = {
	  "stable",
	  "single_prop",
	  "conditional",
	  "keyed_reorder",
	  "regions",
	  "component",
	};
	return workload < COMP_WORKLOAD_COUNT ? names [workload] : "invalid";
}

static bool emit_node(CompSink *sink, uint32_t key, uint32_t value, uint32_t region) {
	CompNode node = {.key = key, .type = 1u, .value = value, .region = region};
	return sink->node(sink->ctx, node);
}

static bool emit_linear(CompSink *sink, uint32_t width, uint32_t frame, bool change, bool reverse) {
	for (uint32_t i = 0; i < width; i++) {
		uint32_t key   = reverse && (frame & 1u) ? width - i : i + 1u;
		uint32_t value = change && i == frame % width ? width + frame : key;
		if (!emit_node(sink, key, value, 0u)) return false;
	}
	return true;
}

static bool emit_conditional(CompSink *sink, uint32_t width, uint32_t frame) {
	uint32_t base = width - width / 4u;
	if (!emit_linear(sink, base, frame, false, false)) return false;
	if (!(frame & 1u)) return true;
	for (uint32_t i = base; i < width; i++) {
		CompNode node = {.key = i + 1u, .parent = base, .type = 1u, .value = i};
		if (!sink->node(sink->ctx, node)) return false;
	}
	return true;
}

static bool emit_region_nodes(CompSink *sink, uint32_t region, uint32_t per, uint64_t revision) {
	for (uint32_t i = 0; i < per; i++) {
		uint32_t key = (region - 1u) * per + i + 1u;
		if (!emit_node(sink, key, key + ( uint32_t ) revision, region)) return false;
	}
	return true;
}

static bool emit_region(CompSink *sink, uint32_t region, uint32_t per, uint32_t frame) {
	uint64_t revision = region <= 2u ? 0u : 1u + (frame + REGION_COUNT - region) / REGION_COUNT;
	bool     build    = sink->begin_region(sink->ctx, region, revision, per);
	if (build && !emit_region_nodes(sink, region, per, revision)) return false;
	return sink->end_region(sink->ctx, region, revision);
}

static bool emit_regions(CompSink *sink, uint32_t width, uint32_t frame) {
	uint32_t per = width / REGION_COUNT;
	for (uint32_t region = 1; region <= REGION_COUNT; region++)
		if (!emit_region(sink, region, per, frame)) return false;
	return true;
}

static CompNode component_item(uint32_t width, uint32_t frame, uint32_t index, uint32_t *builtin) {
	uint32_t component_at = frame & 1u ? width / 3u : width * 2u / 3u;
	if (index != component_at) {
		(*builtin)++;
		return (CompNode) {.key = *builtin, .type = 1u, .value = *builtin};
	}
	return (CompNode) {
	  .key      = width,
	  .type     = UINT32_C(0x80000001),
	  .value    = frame / 8u,
	  .flags    = COMP_NODE_COMPONENT | COMP_NODE_OPAQUE,
	  .provider = PROVIDER_ID,
	};
}

static bool emit_component(CompSink *sink, uint32_t width, uint32_t frame) {
	uint32_t builtin = 0u;
	for (uint32_t i = 0; i < width; i++) {
		CompNode node = component_item(width, frame, i, &builtin);
		if (!sink->node(sink->ctx, node)) return false;
	}
	return true;
}

bool comp_emit_workload(CompWorkload workload, uint32_t width, uint32_t frame, CompSink *sink) {
	if (!sink || !sink->begin_frame || !sink->node || !sink->end_frame) return false;
	if (!sink->begin_frame(sink->ctx, frame)) return false;
	bool ok = false;
	switch (workload) {
	case COMP_STABLE         : ok = emit_linear(sink, width, frame, false, false); break;
	case COMP_SINGLE_PROP    : ok = emit_linear(sink, width, frame, true, false); break;
	case COMP_CONDITIONAL    : ok = emit_conditional(sink, width, frame); break;
	case COMP_KEYED_REORDER  : ok = emit_linear(sink, width, frame, false, true); break;
	case COMP_REGIONS        : ok = emit_regions(sink, width, frame); break;
	case COMP_COMPONENT      : ok = emit_component(sink, width, frame); break;
	case COMP_WORKLOAD_COUNT : break;
	}
	return ok && sink->end_frame(sink->ctx);
}
