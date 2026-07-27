#ifndef XTK_IDENTITY_H
#define XTK_IDENTITY_H

#include "xtk_scratch.h"
#include <xtk/xtk_reconcile.h>

typedef enum XtkSiblingMode
{
	XTK_SIBLING_EMPTY = 0,
	XTK_SIBLING_POSITIONAL,
	XTK_SIBLING_KEYED,
} XtkSiblingMode;

XtkSiblingMode xtk_sibling_mode(XtkEl const *parent);

XtkIdentityError
xtk_identity_validate_tree(XtkHost *host, XtkEl const *root, XtkScratch *scratch, XtkIdentityDiag *out);

#endif
