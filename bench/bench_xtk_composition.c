#include "composition/comp_bench.h"

#include <inttypes.h>
#include <stdio.h>

enum
{
	FRAMES      = 400,
	REPETITIONS = 7,
};

typedef bool (*RunCandidate)(CompWorkload, uint32_t, uint32_t, CompMetrics *);

static bool  semantic_equal(CompMetrics const *tree, CompMetrics const *slots) {
	return tree->creates == slots->creates
	    && tree->destroys == slots->destroys
	    && tree->moves == slots->moves
	    && tree->patches == slots->patches
	    && tree->checksum == slots->checksum;
}

static void print_metrics(char const *candidate, CompWorkload workload, uint32_t width, CompMetrics const *m) {
	printf(
	  "candidate=%s workload=%s width=%u frames=%" PRIu64 " elapsed_ns=%" PRIu64 " ns_per_frame=%" PRIu64
	  " transient_peak=%zu persistent_bytes=%zu allocations=%" PRIu64 " built=%" PRIu64 " compared=%" PRIu64
	  " skipped=%" PRIu64 " creates=%" PRIu64 " destroys=%" PRIu64 " moves=%" PRIu64 " patches=%" PRIu64
	  " checksum=%" PRIu64 "\n",
	  candidate, comp_workload_name(workload), width, m->frames, m->elapsed_ns, m->elapsed_ns / m->frames,
	  m->transient_peak, m->persistent_bytes, m->allocations, m->nodes_built, m->nodes_compared, m->nodes_skipped,
	  m->creates, m->destroys, m->moves, m->patches, m->checksum
	);
}

static void sort_metrics(CompMetrics runs [REPETITIONS]) {
	for (size_t i = 1; i < REPETITIONS; i++) {
		CompMetrics current = runs [i];
		size_t      at      = i;
		while (at && runs [at - 1u].elapsed_ns > current.elapsed_ns) {
			runs [at] = runs [at - 1u];
			at--;
		}
		runs [at] = current;
	}
}

static bool run_candidate(RunCandidate run, CompWorkload workload, uint32_t width, CompMetrics *out) {
	CompMetrics runs [REPETITIONS];
	for (size_t i = 0; i < REPETITIONS; i++)
		if (!run(workload, width, FRAMES, &runs [i])) return false;
	sort_metrics(runs);
	*out = runs [REPETITIONS / 2u];
	return true;
}

static int run_one(CompWorkload workload, uint32_t width) {
	CompMetrics tree, slots;
	if (!run_candidate(comp_run_tree, workload, width, &tree)) return 1;
	if (!run_candidate(comp_run_slots, workload, width, &slots)) return 1;
	print_metrics("indexed_tree", workload, width, &tree);
	print_metrics("block_slots", workload, width, &slots);
	if (semantic_equal(&tree, &slots)) return 0;
	printf("error=semantic_mismatch workload=%s width=%u\n", comp_workload_name(workload), width);
	return 1;
}

int main(void) {
	setvbuf(stdout, NULL, _IONBF, 0);
	static uint32_t const stable_sizes [] = {128u, 1024u, 10000u};
	for (size_t i = 0; i < sizeof(stable_sizes) / sizeof(stable_sizes [0]); i++)
		if (run_one(COMP_STABLE, stable_sizes [i])) return 1;
	for (CompWorkload workload = COMP_SINGLE_PROP; workload < COMP_WORKLOAD_COUNT; workload++)
		if (run_one(workload, 1024u)) return 1;
	return 0;
}
