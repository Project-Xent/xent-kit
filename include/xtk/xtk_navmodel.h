#ifndef XTK_NAVMODEL_H
#define XTK_NAVMODEL_H

#include "xtk.h"

#include <stdbool.h>
#include <stdint.h>

enum
{
	XTK_NAV_MODEL_VERSION          = 1u,
	XTK_NAV_MODEL_WINDOW_TITLE_BAR = 1u << 0,
};

typedef struct XtkNavModelView {
	uint8_t const *data;
	uint32_t       size;
	uint32_t       count;
	uint32_t       flags;
	char const    *app_title;
} XtkNavModelView;

typedef struct XtkNavModelItemView {
	XtkNavKind  kind;
	int32_t     parent;
	char const *icon;
	char const *label;
} XtkNavModelItemView;

uint32_t xtk_navmodel_size(XtkNavDesc const *desc);
bool     xtk_navmodel_write(XtkNavDesc const *desc, void *data, uint32_t size);
bool     xtk_navmodel_open(void const *data, uint32_t size, XtkNavModelView *out);
bool     xtk_navmodel_item(XtkNavModelView const *model, uint32_t index, XtkNavModelItemView *out);

#endif
