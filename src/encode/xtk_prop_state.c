#include "xtk_prop_state.h"

#include "../batch/xtk_batch_internal.h"
#include <xtk/xtk_alloc.h>
#include "xtk_encode.h"

#include <xtk/xtk_catalog.h>

#include <math.h>
#include <string.h>

static void prop_view_items_destroy(XtkPropPatch *items, uint32_t count) {
	for (uint32_t i = 0; i < count; i++) {
		if (items [i].value.kind != XTK_VALUE_BYTES) continue;
		xtk_alloc_free(items [i].value.u.bytes.data);
		items [i].value.u.bytes.data = NULL;
		items [i].value.u.bytes.len  = 0u;
	}
}

bool xtk_prop_view_build(XtkEl const *el, XtkPropPatch *items, uint32_t capacity, XtkPropView *out) {
	if (!el || !items || !capacity || !out) return false;
	*out                                          = (XtkPropView) {0};
	XtkBatchOp ops [XTK_PROP_STANDARD_COUNT + 1u] = {0};
	if (capacity > XTK_PROP_STANDARD_COUNT + 1u) capacity = XTK_PROP_STANDARD_COUNT + 1u;
	XtkBatch capture;
	if (!xtk_batch_capture_begin(&capture, ops, capacity)) return false;
	bool ok = xtk_encode_props(&capture, xtk_ref_existing(( XtkCtrl ) 1u), NULL, el);
	xtk_batch_capture_end(&capture);
	for (uint32_t i = 0; i < capture.count; i++) items [i] = capture.ops [i].u.set_prop.patch;
	if (!ok) {
		prop_view_items_destroy(items, capture.count);
		return false;
	}
	out->items = items;
	out->count = capture.count;
	return true;
}

void xtk_prop_view_destroy(XtkPropView *view) {
	if (!view) return;
	prop_view_items_destroy(view->items, view->count);
	*view = (XtkPropView) {0};
}

static bool size_add(size_t *total, size_t add) {
	if (add > SIZE_MAX - *total) return false;
	*total += add;
	return true;
}

static bool state_size(XtkPropView view, size_t *out) {
	if (view.count > (SIZE_MAX - sizeof(XtkPropState)) / sizeof(XtkPropPatch)) return false;
	size_t total = sizeof(XtkPropState) + ( size_t ) view.count * sizeof(XtkPropPatch);
	for (uint32_t i = 0; i < view.count; i++) {
		XtkValue const *value = &view.items [i].value;
		if (value->kind == XTK_VALUE_STRING && !size_add(&total, ( size_t ) value->u.string.len + 1u)) return false;
		if (value->kind == XTK_VALUE_BYTES && !size_add(&total, value->u.bytes.len)) return false;
	}
	*out = total;
	return true;
}

static void copy_value_data(XtkValue *value, unsigned char **cursor) {
	if (value->kind == XTK_VALUE_STRING) {
		uint32_t len = value->u.string.len;
		if (len) memcpy(*cursor, value->u.string.data, len);
		(*cursor) [len]       = '\0';
		value->u.string.data  = ( char * ) *cursor;
		*cursor              += ( size_t ) len + 1u;
	}
	if (value->kind == XTK_VALUE_BYTES) {
		uint32_t len = value->u.bytes.len;
		if (len) memcpy(*cursor, value->u.bytes.data, len);
		value->u.bytes.data  = len ? *cursor : NULL;
		*cursor             += len;
	}
}

XtkPropState *xtk_prop_state_copy(XtkPropView view) {
	size_t bytes;
	if (!state_size(view, &bytes)) return NULL;
	XtkPropState *state = xtk_alloc(bytes);
	if (!state) return NULL;
	state->count          = view.count;
	unsigned char *cursor = ( unsigned char * ) (state->items + view.count);
	for (uint32_t i = 0; i < view.count; i++) {
		state->items [i] = view.items [i];
		copy_value_data(&state->items [i].value, &cursor);
	}
	return state;
}

void        xtk_prop_state_destroy(XtkPropState *state) { xtk_alloc_free(state); }

static bool bytes_equal(void const *a, uint32_t an, void const *b, uint32_t bn) {
	return an == bn && (an == 0u || memcmp(a, b, an) == 0);
}

static bool value_equal(XtkValue const *a, XtkValue const *b) {
	if (a->kind != b->kind) return false;
	switch (a->kind) {
	case XTK_VALUE_NONE     : return true;
	case XTK_VALUE_BOOL     : return a->u.b == b->u.b;
	case XTK_VALUE_I32      : return a->u.i32 == b->u.i32;
	case XTK_VALUE_F32      : return a->u.f32 == b->u.f32 || (isnan(a->u.f32) && isnan(b->u.f32));
	case XTK_VALUE_F64      : return a->u.f64 == b->u.f64 || (isnan(a->u.f64) && isnan(b->u.f64));
	case XTK_VALUE_ENUM     : return a->u.u32 == b->u.u32;
	case XTK_VALUE_COLOR    : return a->u.color.rgba == b->u.color.rgba;
	case XTK_VALUE_STRING   : return bytes_equal(a->u.string.data, a->u.string.len, b->u.string.data, b->u.string.len);
	case XTK_VALUE_RESOURCE : return a->u.resource == b->u.resource;
	case XTK_VALUE_BYTES    : return bytes_equal(a->u.bytes.data, a->u.bytes.len, b->u.bytes.data, b->u.bytes.len);
	}
	return false;
}

static XtkPropPatch const *find_prop(XtkPropPatch const *items, uint32_t count, XtkPropertyId id) {
	for (uint32_t i = 0; i < count; i++)
		if (items [i].id == id) return &items [i];
	return NULL;
}

static XtkValue default_value(XtkPropertyId id, XtkValueKind kind) {
	XtkValue value = {.kind = kind};
	if (id == XTK_PROP_WIDTH || id == XTK_PROP_HEIGHT) value.u.f32 = NAN;
	if (id == XTK_PROP_ENABLED) value.u.b = true;
	if (kind == XTK_VALUE_STRING) {
		value.u.string.data = "";
		value.u.string.len  = 0u;
	}
	return value;
}

static bool forced(XtkEcho const *echo, XtkPropertyId id) {
	for (uint32_t i = 0; i < echo->nforce; i++)
		if (echo->force [i] == id) return true;
	return false;
}

static bool emit_changed(
  XtkBatch *batch, XtkNodeRef target, XtkPropPatch const *old, XtkPropPatch const *next, XtkEcho const *echo,
  bool *changed
) {
	if (old && value_equal(&old->value, &next->value) && !forced(echo, next->id)) return true;
	*changed = true;
	return xtk_batch_set(batch, target, next->id, next->value, echo->stamp);
}

static bool emit_removed(XtkBatch *batch, XtkNodeRef target, XtkPropPatch const *old, XtkPropView next, bool *changed) {
	if (find_prop(next.items, next.count, old->id)) return true;
	*changed       = true;
	XtkValue value = default_value(old->id, old->value.kind);
	return xtk_batch_set(batch, target, old->id, value, (XtkChangeStamp) {0});
}

bool xtk_prop_state_diff(
  XtkBatch *batch, XtkNodeRef target, XtkPropState const *old, XtkPropView next, XtkEcho const *echo, bool *changed
) {
	if (!batch || !changed) return false;
	*changed = false;
	for (uint32_t i = 0; i < next.count; i++) {
		XtkPropPatch const *prior = old ? find_prop(old->items, old->count, next.items [i].id) : NULL;
		if (!emit_changed(batch, target, prior, &next.items [i], echo, changed)) return false;
	}
	if (!old) return true;
	for (uint32_t i = 0; i < old->count; i++)
		if (!emit_removed(batch, target, &old->items [i], next, changed)) return false;
	return true;
}
