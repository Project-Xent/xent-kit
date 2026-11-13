#include <xtk/xtk_alloc.h>

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

typedef union XtkAllocHeader
{
	struct {
		size_t size;
	} value;

	long double align_ld;
	long long   align_ll;
	void       *align_ptr;
} XtkAllocHeader;

typedef struct XtkAllocState {
	XtkAllocStats stats;
	uint64_t      fail_at;
	size_t        current_bytes;
	size_t        baseline_bytes;
} XtkAllocState;

static _Thread_local XtkAllocState xtk_alloc_state;

static bool                        alloc_should_fail(void) {
	xtk_alloc_state.stats.attempts++;
	if (xtk_alloc_state.fail_at != xtk_alloc_state.stats.attempts) return false;
	xtk_alloc_state.stats.failures++;
	return true;
}

static void alloc_update_peak(void) {
	size_t live                      = xtk_alloc_state.current_bytes > xtk_alloc_state.baseline_bytes
	                                   ? xtk_alloc_state.current_bytes - xtk_alloc_state.baseline_bytes
	                                   : 0u;
	xtk_alloc_state.stats.live_bytes = live;
	if (live > xtk_alloc_state.stats.peak_bytes) xtk_alloc_state.stats.peak_bytes = live;
}

static void *alloc_new(size_t size, bool zero) {
	if (size > SIZE_MAX - sizeof(XtkAllocHeader)) {
		xtk_alloc_state.stats.failures++;
		return NULL;
	}
	size_t          total  = sizeof(XtkAllocHeader) + size;
	XtkAllocHeader *header = zero ? calloc(1u, total) : malloc(total);
	if (!header) {
		xtk_alloc_state.stats.failures++;
		return NULL;
	}
	header->value.size = size;
	xtk_alloc_state.stats.successes++;
	xtk_alloc_state.current_bytes += size;
	alloc_update_peak();
	return header + 1;
}

void *xtk_alloc(size_t size) {
	if (alloc_should_fail()) return NULL;
	return alloc_new(size, false);
}

void *xtk_alloc_zero(size_t count, size_t size) {
	if (alloc_should_fail()) return NULL;
	if (count && size > SIZE_MAX / count) {
		xtk_alloc_state.stats.failures++;
		return NULL;
	}
	return alloc_new(count * size, true);
}

void *xtk_alloc_resize(void *ptr, size_t size) {
	if (alloc_should_fail()) return NULL;
	if (!ptr) return alloc_new(size, false);
	if (size > SIZE_MAX - sizeof(XtkAllocHeader)) {
		xtk_alloc_state.stats.failures++;
		return NULL;
	}

	XtkAllocHeader *old      = ( XtkAllocHeader * ) ptr - 1;
	size_t          old_size = old->value.size;
	XtkAllocHeader *header   = realloc(old, sizeof(XtkAllocHeader) + size);
	if (!header) {
		xtk_alloc_state.stats.failures++;
		return NULL;
	}
	header->value.size = size;
	xtk_alloc_state.stats.successes++;
	xtk_alloc_state.current_bytes -= old_size;
	xtk_alloc_state.current_bytes += size;
	alloc_update_peak();
	return header + 1;
}

void xtk_alloc_free(void *ptr) {
	if (!ptr) return;
	XtkAllocHeader *header         = ( XtkAllocHeader * ) ptr - 1;
	xtk_alloc_state.current_bytes -= header->value.size;
	alloc_update_peak();
	xtk_alloc_state.stats.frees++;
	free(header);
}

void xtk_alloc_test_reset(void) {
	size_t current                 = xtk_alloc_state.current_bytes;
	xtk_alloc_state                = (XtkAllocState) {0};
	xtk_alloc_state.current_bytes  = current;
	xtk_alloc_state.baseline_bytes = current;
}

void          xtk_alloc_fail_at(uint64_t attempt) { xtk_alloc_state.fail_at = attempt; }

XtkAllocStats xtk_alloc_test_stats(void) { return xtk_alloc_state.stats; }
