#ifndef XTK_ALLOC_INTERNAL_H
#define XTK_ALLOC_INTERNAL_H

#include <xtk/xtk_alloc.h>

typedef struct XtkAllocStats {
	uint64_t attempts;
	uint64_t successes;
	uint64_t failures;
	uint64_t frees;
	size_t   live_bytes;
	size_t   peak_bytes;
} XtkAllocStats;

/*
 * Private fault-injection controls. A zero fail index disables injection;
 * otherwise the Nth allocation attempt after reset fails. Tests are expected
 * to call controls and allocations on the same thread; state is thread-local.
 */
void          xtk_alloc_test_reset(void);
void          xtk_alloc_fail_at(uint64_t attempt);
XtkAllocStats xtk_alloc_test_stats(void);

#endif
