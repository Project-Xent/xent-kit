#ifndef XTK_TREE_MODEL_H
#define XTK_TREE_MODEL_H

#include "xtk.h"

#include <stdbool.h>
#include <stdint.h>

enum
{
	XTK_TREE_MODEL_VERSION  = 1u,
	XTK_TREE_MODEL_EXPANDED = 1u << 0,
	XTK_TREE_MODEL_DISABLED = 1u << 1,
};

typedef struct XtkTreeModelView {
	uint8_t const *data;
	uint32_t       size;
	uint32_t       count;
} XtkTreeModelView;

typedef struct XtkTreeModelItemView {
	int32_t     parent;
	uint32_t    flags;
	char const *text;
	char const *icon;
} XtkTreeModelItemView;

uint32_t xtk_tree_model_size(XtkTreeDesc const *desc);
bool     xtk_tree_model_write(XtkTreeDesc const *desc, void *data, uint32_t size);
bool     xtk_tree_model_open(void const *data, uint32_t size, XtkTreeModelView *out);
bool     xtk_tree_model_item(XtkTreeModelView const *model, uint32_t index, XtkTreeModelItemView *out);

#endif
