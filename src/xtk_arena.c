#include "xtk_internal.h"

#include <stdlib.h>
#include <string.h>

#define XTK_ARENA_MIN_CHUNK (64u * 1024u)

static XtkArenaChunk *xtk_arena_chunk_create(size_t capacity) {
	if (capacity < XTK_ARENA_MIN_CHUNK) capacity = XTK_ARENA_MIN_CHUNK;
	XtkArenaChunk *chunk = ( XtkArenaChunk * ) malloc(sizeof(XtkArenaChunk) + capacity);
	if (!chunk) return NULL;
	chunk->next     = NULL;
	chunk->capacity = capacity;
	chunk->used     = 0;
	return chunk;
}

bool xtk_arena_init(XtkArena *arena, size_t first_chunk_size) {
	arena->first = xtk_arena_chunk_create(first_chunk_size);
	arena->head  = arena->first;
	return arena->first != NULL;
}

void xtk_arena_dispose(XtkArena *arena) {
	XtkArenaChunk *chunk = arena->first;
	while (chunk) {
		XtkArenaChunk *next = chunk->next;
		free(chunk);
		chunk = next;
	}
	arena->first = NULL;
	arena->head  = NULL;
}

/* Overflow chunks are released on reset; a frame that ballooned once does not
 * pin its high-water mark forever. */
void xtk_arena_reset(XtkArena *arena) {
	if (!arena->first) return;
	XtkArenaChunk *chunk = arena->first->next;
	while (chunk) {
		XtkArenaChunk *next = chunk->next;
		free(chunk);
		chunk = next;
	}
	arena->first->next = NULL;
	arena->first->used = 0;
	arena->head        = arena->first;
}

static size_t xtk_align_up(size_t n) {
	size_t const a = _Alignof(XtkMaxAlign);
	return (n + a - 1) & ~(a - 1);
}

void *xtk_arena_alloc(XtkArena *arena, size_t size) {
	if (!arena->head) return NULL;
	size = xtk_align_up(size ? size : 1);

	if (arena->head->used + size > arena->head->capacity) {
		XtkArenaChunk *chunk = xtk_arena_chunk_create(size);
		if (!chunk) return NULL;
		chunk->next       = arena->head->next;
		arena->head->next = chunk;
		arena->head       = chunk;
	}

	void *p            = arena->head->data + arena->head->used;
	arena->head->used += size;
	memset(p, 0, size);
	return p;
}
