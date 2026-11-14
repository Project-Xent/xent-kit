#ifndef XTK_CATALOG_H
#define XTK_CATALOG_H

#include <assert.h>

#include "xtk_descriptor.h"

typedef enum XtkStackDirection
{
	XTK_STACK_COLUMN = 0,
	XTK_STACK_ROW    = 1,
} XtkStackDirection;

#define XTK_MIRROR_MAX 2u

typedef enum XtkStandardResourceTypeId
{
	XTK_RESOURCE_TYPE_IMAGE = 1,
	XTK_RESOURCE_TYPE_DISPLAY_LIST,
} XtkStandardResourceTypeId;

XtkCtrlDesc const  *xtk_catalog_control(XtkCtrlId id);
XtkPropDesc const  *xtk_catalog_property(XtkPropertyId id);
XtkEventDesc const *xtk_catalog_event(XtkEventId id);
XtkPropDesc const  *xtk_catalog_ctrlprop(XtkCtrlId control, XtkPropertyId property);
XtkEventDesc const *xtk_catalog_ctrlevent(XtkCtrlId control, XtkEventId event);
bool                xtk_catalog_standard(XtkCtrlId id);
uint32_t            xtk_catalog_mirrors(XtkCtrlId control, XtkEventId event, XtkPropertyId *out);

static_assert(sizeof(XtkStackDirection) == 4, "XtkStackDirection crosses the ABI as int32");
static_assert(sizeof(XtkStandardResourceTypeId) == 4, "XtkStandardResourceTypeId crosses the ABI as int32");

#endif
