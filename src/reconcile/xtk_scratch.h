#ifndef XTK_SCRATCH_H
#define XTK_SCRATCH_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct XtkScratch {
	unsigned char *data;
	size_t         capacity;
	size_t         used;
} XtkScratch;

bool   xtk_scratch_init(XtkScratch *s, size_t initial);
void   xtk_scratch_dispose(XtkScratch *s);
void   xtk_scratch_reset(XtkScratch *s);
bool   xtk_scratch_ensure(XtkScratch *s, size_t capacity);
size_t xtk_scratch_mark(XtkScratch const *s);
void   xtk_scratch_rewind(XtkScratch *s, size_t mark);
void  *xtk_scratch_reserve(XtkScratch *s, size_t size, size_t align);

#endif
