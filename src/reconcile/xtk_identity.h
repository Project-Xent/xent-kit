#ifndef XTK_IDENTITY_H
#define XTK_IDENTITY_H

#include "xtk_scratch.h"
#include <xtk/xtk_reconcile.h>
#include <xtk/xtk_scene.h>

typedef enum XtkSiblingMode
{
	XTK_SIBLING_EMPTY = 0,
	XTK_SIBLING_POSITIONAL,
	XTK_SIBLING_KEYED,
} XtkSiblingMode;

XtkSiblingMode xtk_sibling_mode(XtkEl const *parent);

bool           xtk_identity_type_known(XtkScene const *scene, XtkCtrlId type);
bool           xtk_identity_alloc_regions(XtkScratch *scratch, uint32_t count, uint64_t **out_slots, uint32_t *out_cap);
XtkIdentityError xtk_identity_check_node(
  XtkScene const *scene, XtkEl const *el, uint32_t depth, int const *path, uint64_t *regions, uint32_t region_capacity,
  XtkIdentityDiag *out
);
XtkIdentityError xtk_identity_check_siblings(
  XtkScene const *scene, XtkEl const *parent, XtkScratch *scratch, uint32_t depth, int const *path, XtkIdentityDiag *out
);

#endif
