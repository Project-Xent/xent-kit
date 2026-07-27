#include <xtk/xtk_component.h>

#include "xtk_internal.h"

#include <limits.h>
#include <string.h>

XtkEl *xtk_component(XtkUi *ui, XtkCompType const *type, void const *props) {
	if (!ui || !type || !type->control) return NULL;
	if (type->control->id < XTK_CTRL_ID_COMPONENT_BASE) return NULL;
	if (type->props_size > UINT32_MAX || (type->props_size && !props)) return NULL;

	XtkEl *el = xtk_el_new(ui, type->control->id, NULL);
	if (!el) return NULL;
	XTK_EL_DATA(el)->region_flags = XTK_REGION_OPAQUE;
	if (!type->props_size) return el;
	void *copy = xtk_arena_alloc(xtk_ui_arena(ui), type->props_size);
	if (!copy) return NULL;
	if (type->copy_props) type->copy_props(ui, copy, props);
	else memcpy(copy, props, type->props_size);
	XTK_EL_DATA(el)->component_props      = copy;
	XTK_EL_DATA(el)->component_props_size = ( uint32_t ) type->props_size;
	return el;
}
