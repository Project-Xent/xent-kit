#include "xtk_internal.h"
#include <xtk/xtk_alloc.h>

#include <string.h>

#define XTK_ARENA_MIN_CHUNK (64u * 1024u)

static XtkArenaChunk *arena_chunk_create(size_t capacity) {
	if (capacity < XTK_ARENA_MIN_CHUNK) capacity = XTK_ARENA_MIN_CHUNK;
	XtkArenaChunk *chunk = ( XtkArenaChunk * ) xtk_alloc(sizeof(XtkArenaChunk) + capacity);
	if (!chunk) return NULL;
	chunk->next     = NULL;
	chunk->capacity = capacity;
	chunk->used     = 0;
	return chunk;
}

bool xtk_arena_init(XtkArena *arena, size_t first_chunk_size) {
	arena->first = arena_chunk_create(first_chunk_size);
	arena->head  = arena->first;
	return arena->first != NULL;
}

void xtk_arena_dispose(XtkArena *arena) {
	XtkArenaChunk *chunk = arena->first;
	while (chunk) {
		XtkArenaChunk *next = chunk->next;
		xtk_alloc_free(chunk);
		chunk = next;
	}
	arena->first = NULL;
	arena->head  = NULL;
}

void xtk_arena_reset(XtkArena *arena) {
	if (!arena->first) return;
	for (XtkArenaChunk *chunk = arena->first; chunk; chunk = chunk->next) chunk->used = 0;
	arena->head = arena->first;
}

static size_t align_up(size_t n) {
	size_t const a = _Alignof(XtkMaxAlign);
	return (n + a - 1) & ~(a - 1);
}

static XtkArenaChunk *arena_next_chunk(XtkArena *arena, size_t size) {
	XtkArenaChunk *chunk = arena->head->next;
	while (chunk && chunk->capacity < size) chunk = chunk->next;
	if (chunk) return chunk;
	chunk = arena_chunk_create(size);
	if (!chunk) return NULL;
	chunk->next       = arena->head->next;
	arena->head->next = chunk;
	return chunk;
}

void *xtk_arena_alloc(XtkArena *arena, size_t size) {
	if (!arena->head) return NULL;
	size = align_up(size ? size : 1);

	if (arena->head->used + size > arena->head->capacity) {
		XtkArenaChunk *chunk = arena_next_chunk(arena, size);
		if (!chunk) return NULL;
		arena->head = chunk;
	}

	void *p            = arena->head->data + arena->head->used;
	arena->head->used += size;
	memset(p, 0, size);
	return p;
}
