#include "xtk_scratch.h"
#include <xtk/xtk_alloc.h>

#include <string.h>

bool xtk_scratch_init(XtkScratch *s, size_t initial) {
	if (!s) return false;
	memset(s, 0, sizeof(*s));
	if (initial == 0) initial = 4096u;
	s->data = ( unsigned char * ) xtk_alloc(initial);
	if (!s->data) return false;
	s->capacity = initial;
	return true;
}

void xtk_scratch_dispose(XtkScratch *s) {
	if (!s) return;
	xtk_alloc_free(s->data);
	memset(s, 0, sizeof(*s));
}

void xtk_scratch_reset(XtkScratch *s) {
	if (s) s->used = 0;
}

bool xtk_scratch_ensure(XtkScratch *s, size_t capacity) {
	if (!s) return false;
	if (capacity <= s->capacity) return true;
	size_t cap = s->capacity ? s->capacity : 4096u;
	while (cap < capacity) {
		if (cap > SIZE_MAX / 2u) return false;
		cap *= 2u;
	}
	unsigned char *data = ( unsigned char * ) xtk_alloc_resize(s->data, cap);
	if (!data) return false;
	s->data     = data;
	s->capacity = cap;
	return true;
}

size_t xtk_scratch_mark(XtkScratch const *s) { return s ? s->used : 0; }

void   xtk_scratch_rewind(XtkScratch *s, size_t mark) {
	if (s && mark <= s->used) s->used = mark;
}

static size_t align_up(size_t value, size_t align) { return (value + (align - 1u)) & ~(align - 1u); }

void         *xtk_scratch_reserve(XtkScratch *s, size_t size, size_t align) {
	if (!s || align == 0 || (align & (align - 1u)) != 0) return NULL;
	size_t offset = align_up(s->used, align);
	if (size > SIZE_MAX - offset) return NULL;
	size_t need = offset + size;
	if (!xtk_scratch_ensure(s, need)) return NULL;
	s->used = need;
	return s->data + offset;
}
