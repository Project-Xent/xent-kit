#ifndef XTK_INTERNAL_H
#define XTK_INTERNAL_H

#include "xtk/xtk.h"
#include <stddef.h>

typedef union
{
	long long   ll;
	long double ld;
	void       *p;
} XtkMaxAlign;

typedef struct XtkArenaChunk {
	struct XtkArenaChunk *next;
	size_t                capacity;
	size_t                used;
	_Alignas(XtkMaxAlign) unsigned char data [];
} XtkArenaChunk;

typedef struct XtkArena {
	XtkArenaChunk *head;
	XtkArenaChunk *first;
} XtkArena;

typedef struct XtkElementData {
	XtkEl               *handle;
	XtkCtrlId            type;
	XtkKey               key;
	void                *component_props;
	uint32_t             component_props_size;
	float                width;
	float                height;
	float                grow;
	XentFlexAlign        align_self;
	XentInsets           margin;
	char const          *text;
	char const          *tooltip;
	XtkAutomation const *automation;
	uint32_t             child_offset;
	int                  child_count;
	uint32_t             detail_offset;
	uint32_t             detail_size;
	uint32_t             subtree_begin;
	uint32_t             subtree_end;
	uint32_t             region_flags;
	uint64_t             region_id;
	uint64_t             region_revision;
	int                  virtual_first;
	bool                 virtualized;
	bool                 stack_row;
	uint8_t              nav_slot;
} XtkElementData;

typedef struct XtkScrollDetail {
	XtkStackDesc  stack;
	XtkScrollDesc scroll;
} XtkScrollDetail;

typedef struct XtkDragDropDetail {
	XtkStackDesc    stack;
	XtkDragDropDesc dnd;
} XtkDragDropDetail;

typedef struct XtkMenuItemDetail {
	char const *icon;
	bool        disabled;
	XtkMsg      click;
} XtkMenuItemDetail;

typedef struct XtkComposition {
	XtkElementData *elements;
	uint32_t       *children;
	unsigned char  *details;
	uint32_t        element_count;
	uint32_t        element_capacity;
	uint32_t        child_count;
	uint32_t        child_capacity;
	uint32_t        detail_count;
	uint32_t        detail_capacity;
	bool            failed;
} XtkComposition;

typedef struct XtkRegionEntry {
	uint64_t        id;
	uint64_t        revision;
	struct XtkNode *node;
} XtkRegionEntry;

enum
{
	XTK_REGION_MEMO   = 1u << 0,
	XTK_REGION_OPAQUE = 1u << 1,
	XTK_REGION_REF    = 1u << 31,
};

struct XtkEl {
	XtkUi   *ui;
	uint32_t index;
};

bool  xtk_arena_init(XtkArena *arena, size_t first_chunk_size);
void  xtk_arena_dispose(XtkArena *arena);
void  xtk_arena_reset(XtkArena *arena);
void *xtk_arena_alloc(XtkArena *arena, size_t size);

struct XtkUi {
	XtkArena        arena;
	XtkComposition  composition;
	XtkRegionEntry *regions;
	uint32_t        region_capacity;
	uint32_t        region_count;
};

XtkArena       *xtk_ui_arena(XtkUi *ui);
XtkElementData *xtk_el_data(XtkEl const *el);
void           *xtk_el_detail(XtkEl const *el, size_t size);
bool            xtk_el_detail_set(XtkEl *el, void const *data, size_t size);
XtkEl          *xtk_el_child(XtkEl const *el, int index);
bool            xtk_el_set_children(XtkEl *el, XtkEl *const children [], int count);
bool            xtk_ui_failed(XtkUi const *ui);
void            xtk_ui_fail(XtkUi *ui);
bool            xtk_ui_prepare_regions(XtkUi *ui, struct XtkNode *root);
struct XtkNode *xtk_ui_find_region(XtkUi const *ui, uint64_t id, uint64_t revision);

#define XTK_EL_DATA(el_)      xtk_el_data(el_)
#define XTK_EL_DETAIL(el_, t) (( t * ) xtk_el_detail((el_), sizeof(t)))
#define XTK_EL_STORE(el_, v_) xtk_el_detail_set((el_), &(v_), sizeof(v_))

void   xtk_ui_abort_candidate(XtkUi *ui);

XtkEl *xtk_el_new(XtkUi *ui, XtkCtrlId type, char const *text);
void   xtk_el_adopt(XtkUi *ui, XtkEl *el, XtkEl *children []);

#endif
