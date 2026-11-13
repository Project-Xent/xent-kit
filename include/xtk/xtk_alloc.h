#ifndef XTK_ALLOC_H
#define XTK_ALLOC_H

#include <stddef.h>
#include <stdint.h>

#include <xent/xent.h>

XENT_NODISCARD void *xtk_alloc(size_t size);
XENT_NODISCARD void *xtk_alloc_zero(size_t count, size_t size);
XENT_NODISCARD void *xtk_alloc_resize(void *ptr, size_t size);
void                 xtk_alloc_free(void *ptr);

typedef struct XtkAllocStats {
	uint64_t attempts;
	uint64_t successes;
	uint64_t failures;
	uint64_t frees;
	size_t   live_bytes;
	size_t   peak_bytes;
} XtkAllocStats;

void          xtk_alloc_test_reset(void);
void          xtk_alloc_fail_at(uint64_t attempt);
XtkAllocStats xtk_alloc_test_stats(void);

#endif
