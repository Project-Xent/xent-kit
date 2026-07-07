/**
 * @file xtk_internal.h
 * @brief XTK internals: frame arena and build context shared by the builder
 * translation units. The reconciler and runtime live in the backend.
 */
#ifndef XTK_INTERNAL_H
#define XTK_INTERNAL_H

#include "xtk/xtk.h"
#include <stddef.h>

/* Portable max fundamental alignment (MSVC's C stddef.h omits max_align_t). */
typedef union { long long ll; long double ld; void *p; } XtkMaxAlign;

/** @brief Chunked bump allocator; reset keeps the first chunk hot. */
typedef struct XtkArenaChunk {
	struct XtkArenaChunk *next;
	size_t                capacity;
	size_t                used;
	_Alignas(XtkMaxAlign) unsigned char data [];
} XtkArenaChunk;

typedef struct XtkArena {
	XtkArenaChunk *head;  /**< Current chunk (allocation cursor). */
	XtkArenaChunk *first; /**< Retained across resets. */
} XtkArena;

bool  xtk_arena_init(XtkArena *arena, size_t first_chunk_size);
void  xtk_arena_dispose(XtkArena *arena);
void  xtk_arena_reset(XtkArena *arena);
void *xtk_arena_alloc(XtkArena *arena, size_t size);

/* Two frame arenas alternate so the previous frame's element tree stays
 * alive while the reconciler diffs the new one against it. */
struct XtkUi {
	XtkArena arenas [2];
	int      current;
};

XtkArena              *xtk_ui_arena(XtkUi *ui);

/** @brief Allocate a new element on the frame arena (NAN sizes, zeroed). */
XtkEl                 *xtk_el_new(XtkUi *ui, XtkControlType type, char const *text);

/** @brief Adopt an XTK_END-terminated child array (skips NULLs, dense copy). */
void                   xtk_el_adopt(XtkUi *ui, XtkEl *el, XtkEl *children []);

/** @brief Copy a declarative menu-item array into the frame arena. */
XtkMenuItemDesc const *xtk_menu_items_dup(XtkUi *ui, XtkMenuItemDesc const *items, int count);

#endif
