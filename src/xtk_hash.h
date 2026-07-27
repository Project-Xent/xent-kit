#ifndef XTK_HASH_H
#define XTK_HASH_H

#include <stddef.h>
#include <stdint.h>

/* Never returns 0: consumers use 0 as the open-addressing empty-slot marker. */
static uint32_t inline xtk_hash_string(char const *data, size_t len) {
	uint32_t h = 2166136261u;
	for (size_t i = 0; i < len; i++) {
		h ^= ( unsigned char ) data [i];
		h *= 16777619u;
	}
	return h ? h : 1u;
}

static uint64_t inline xtk_hash_u64(uint64_t id) {
	id ^= id >> 33u;
	id *= UINT64_C(0xff51afd7ed558ccd);
	id ^= id >> 33u;
	return id;
}

#endif
