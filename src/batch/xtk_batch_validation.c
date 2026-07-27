#include <xtk/xtk_batch.h>
#include <xtk/xtk_catalog.h>

#include <string.h>

bool xtk_batch_value_ok(XtkValue const *v) {
	if (!v || v->kind == XTK_VALUE_NONE || v->kind > XTK_VALUE_BYTES) return false;
	if (v->kind == XTK_VALUE_STRING) return v->u.string.len == 0u || v->u.string.data != NULL;
	if (v->kind == XTK_VALUE_BYTES) return v->u.bytes.len == 0u || v->u.bytes.data != NULL;
	return true;
}

bool xtk_batch_prop_ok(XtkPropPatch const *prop) {
	return prop->id != XTK_PROP_ID_INVALID && xtk_batch_value_ok(&prop->value) && xtk_change_stamp_valid(prop->change);
}

bool xtk_batch_props_ok(XtkPropPatch const *props, uint32_t count) {
	if (count == 0u) return true;
	if (!props) return false;
	for (uint32_t i = 0; i < count; i++)
		if (!xtk_batch_prop_ok(&props [i])) return false;
	return true;
}

XtkPropertyKind xtk_batch_prop_kind(XtkValueKind kind) {
	static XtkPropertyKind const kinds [] = {
	  [XTK_VALUE_BOOL]     = XTK_PROP_KIND_BOOL,
	  [XTK_VALUE_I32]      = XTK_PROP_KIND_I32,
	  [XTK_VALUE_F32]      = XTK_PROP_KIND_F32,
	  [XTK_VALUE_F64]      = XTK_PROP_KIND_F64,
	  [XTK_VALUE_ENUM]     = XTK_PROP_KIND_ENUM,
	  [XTK_VALUE_COLOR]    = XTK_PROP_KIND_COLOR,
	  [XTK_VALUE_STRING]   = XTK_PROP_KIND_STRING,
	  [XTK_VALUE_RESOURCE] = XTK_PROP_KIND_RESOURCE,
	  [XTK_VALUE_BYTES]    = XTK_PROP_KIND_BYTES,
	};
	if (( unsigned ) kind >= sizeof(kinds) / sizeof(kinds [0])) return 0;
	return kinds [kind];
}

bool xtk_batch_stdprop_ok(XtkCtrlId control, XtkPropPatch const *patch) {
	XtkPropDesc const *property = xtk_catalog_control_property(control, patch->id);
	return property && property->kind == xtk_batch_prop_kind(patch->value.kind);
}

bool xtk_batch_phases_ok(XtkEventId event, uint32_t phases) {
	if (!xtk_event_phases_valid(phases)) return false;
	XtkEventDesc const *descriptor = xtk_catalog_event(event);
	if (!descriptor) return true;
	uint32_t allowed = XTK_EVENT_PHASE_MASK_TARGET;
	if (descriptor->routing == XTK_EVENT_ROUTE_BUBBLE) allowed |= XTK_EVENT_PHASE_MASK_BUBBLE;
	if (descriptor->routing == XTK_EVENT_ROUTE_CAPTURE_BUBBLE) allowed = XTK_EVENT_PHASE_MASK_ALL;
	return (phases & ~allowed) == 0u;
}
