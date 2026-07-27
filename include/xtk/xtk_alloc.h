#ifndef XTK_ALLOC_H
#define XTK_ALLOC_H

/* Kit-wide allocator. Hosts allocate through this family so kit fault
 * injection and accounting cover host-side buffers. xtk_alloc_free(NULL)
 * is a no-op. */

#include <stddef.h>

#include <xent/xent.h>

XENT_NODISCARD void *xtk_alloc(size_t size);
XENT_NODISCARD void *xtk_alloc_zero(size_t count, size_t size);
XENT_NODISCARD void *xtk_alloc_resize(void *ptr, size_t size);
void                 xtk_alloc_free(void *ptr);

#endif
