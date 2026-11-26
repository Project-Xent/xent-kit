#include "xtk_prop_state.h"

#include "../batch/xtk_batch_internal.h"
#include "../xtk_internal.h"
#include "xtk_encode.h"
#include <xtk/xtk_alloc.h>
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

static void prop_view_sort(XtkPropPatch *items, uint32_t count) {
	for (uint32_t i = 1; i < count; i++) {
		XtkPropPatch key = items [i];
		uint32_t     j   = i;
		while (j > 0 && items [j - 1].id > key.id) {
			items [j] = items [j - 1];
			j--;
		}
		items [j] = key;
	}
}

static uint32_t prop_view_dedup(XtkPropPatch *items, uint32_t count) {
	if (count <= 1u) return count;
	uint32_t out = 0u;
	for (uint32_t i = 0; i < count; i++) {
		if (i + 1u < count && items [i].id == items [i + 1u].id) {
			if (items [i].value.kind == XTK_VALUE_BYTES) xtk_alloc_free(items [i].value.u.bytes.data);
			continue;
		}
		items [out++] = items [i];
	}
	return out;
}

bool xtk_prop_view_build(XtkEl const *el, XtkPropPatch *items, uint32_t capacity, bool skip_model, XtkPropView *out) {
	if (!el || !items || !capacity || !out) return false;
	*out = (XtkPropView) {0};
	XtkBatchOp ops [XTK_PROP_STANDARD_COUNT + 1u];
	if (capacity > XTK_PROP_STANDARD_COUNT + 1u) capacity = XTK_PROP_STANDARD_COUNT + 1u;
	XtkBatch capture;
	if (!xtk_batch_capture_begin(&capture, ops, capacity)) return false;
	bool ok = xtk_encode_props_view(&capture, xtk_ref_existing(( XtkCtrl ) 1u), el, skip_model);
	xtk_batch_capture_end(&capture);
	for (uint32_t i = 0; i < capture.count; i++) items [i] = capture.ops [i].u.set_prop.patch;
	if (!ok) {
		prop_view_items_destroy(items, capture.count);
		return false;
	}
	prop_view_sort(items, capture.count);
	out->items = items;
	out->count = prop_view_dedup(items, capture.count);
	return true;
}

void xtk_prop_view_destroy(XtkPropView *view) {
	if (!view) return;
	prop_view_items_destroy(view->items, view->count);
	*view = (XtkPropView) {0};
}

static XtkPropBlob *blob_create(void const *data, uint32_t len, bool nul_term) {
	size_t extra = ( size_t ) len + (nul_term ? 1u : 0u);
	if (extra > SIZE_MAX - sizeof(XtkPropBlob)) return NULL;
	XtkPropBlob *blob = ( XtkPropBlob * ) xtk_alloc(sizeof(XtkPropBlob) + extra);
	if (!blob) return NULL;
	blob->refcount = 1u;
	blob->len      = len;
	if (len) memcpy(blob->data, data, len);
	if (nul_term) blob->data [len] = '\0';
	return blob;
}

static XtkPropBlob *blob_retain(XtkPropBlob *blob) {
	if (blob) blob->refcount++;
	return blob;
}

static void blob_release(XtkPropBlob *blob) {
	if (blob && --blob->refcount == 0u) xtk_alloc_free(blob);
}

void xtk_prop_slots_release(XtkPropSlot *slots, uint32_t count) {
	if (!slots) return;
	for (uint32_t i = 0; i < count; i++) blob_release(slots [i].blob);
}

static bool slot_from_patch(XtkPropSlot *dst, XtkPropPatch const *patch) {
	*dst = (XtkPropSlot) {.id = patch->id, .value = patch->value, .blob = NULL};
	if (patch->value.kind == XTK_VALUE_STRING) {
		uint32_t len = patch->value.u.string.len;
		if (!len) {
			dst->value.u.string.data = "";
			return true;
		}
		dst->blob = blob_create(patch->value.u.string.data, len, true);
		if (!dst->blob) return false;
		dst->value.u.string.data = ( char * ) dst->blob->data;
		return true;
	}
	if (patch->value.kind == XTK_VALUE_BYTES) {
		uint32_t len = patch->value.u.bytes.len;
		if (!len) {
			dst->value.u.bytes.data = NULL;
			return true;
		}
		dst->blob = blob_create(patch->value.u.bytes.data, len, false);
		if (!dst->blob) return false;
		dst->value.u.bytes.data = dst->blob->data;
		return true;
	}
	return true;
}

static bool copy_inline_value(XtkValue *value, unsigned char **cursor) {
	if (value->kind == XTK_VALUE_STRING) {
		uint32_t len = value->u.string.len;
		if (!len) {
			value->u.string.data = "";
			return true;
		}
		memcpy(*cursor, value->u.string.data, len);
		(*cursor) [len]       = '\0';
		value->u.string.data  = ( char * ) *cursor;
		*cursor              += ( size_t ) len + 1u;
	}
	else if (value->kind == XTK_VALUE_BYTES) {
		uint32_t len = value->u.bytes.len;
		if (len) memcpy(*cursor, value->u.bytes.data, len);
		value->u.bytes.data  = len ? *cursor : NULL;
		*cursor             += len;
	}
	return true;
}

static size_t inline_payload_bytes(XtkPropView view) {
	size_t extra = 0u;
	for (uint32_t i = 0; i < view.count; i++) {
		XtkValue const *v = &view.items [i].value;
		if (v->kind == XTK_VALUE_STRING && v->u.string.len) extra += ( size_t ) v->u.string.len + 1u;
		else if (v->kind == XTK_VALUE_BYTES) extra += v->u.bytes.len;
	}
	return extra;
}

XtkPropState *xtk_prop_state_copy(XtkPropView view, XtkModelVer model_ver) {
	if (( size_t ) view.count > (SIZE_MAX - sizeof(XtkPropState)) / sizeof(XtkPropSlot)) return NULL;
	size_t head  = sizeof(XtkPropState) + ( size_t ) view.count * sizeof(XtkPropSlot);
	size_t extra = inline_payload_bytes(view);
	if (extra > SIZE_MAX - head) return NULL;
	XtkPropState *state = ( XtkPropState * ) xtk_alloc(head + extra);
	if (!state) return NULL;
	*state = (XtkPropState) {
	  .refcount  = 1u,
	  .count     = view.count,
	  .capacity  = view.count,
	  .revision  = 1u,
	  .model_ver = model_ver,
	  .items     = ( XtkPropSlot * ) (state + 1),
	};
	unsigned char *cursor = ( unsigned char * ) state + head;
	for (uint32_t i = 0; i < view.count; i++) {
		state->items [i] = (XtkPropSlot) {.id = view.items [i].id, .value = view.items [i].value, .blob = NULL};
		copy_inline_value(&state->items [i].value, &cursor);
	}
	return state;
}

XtkPropState *xtk_prop_state_retain(XtkPropState *state) {
	if (state) state->refcount++;
	return state;
}

void xtk_prop_state_destroy(XtkPropState *state) {
	if (!state || --state->refcount > 0u) return;
	xtk_prop_slots_release(state->items, state->count);
	xtk_alloc_free(state);
}

XtkPropSlot const *xtk_prop_state_find(XtkPropState const *state, XtkPropertyId id) {
	if (!state || !state->count) return NULL;
	uint32_t lo = 0u, hi = state->count;
	while (lo < hi) {
		uint32_t      mid    = lo + (hi - lo) / 2u;
		XtkPropertyId mid_id = state->items [mid].id;
		if (mid_id == id) return &state->items [mid];
		if (mid_id < id) lo = mid + 1u;
		else hi = mid;
	}
	return NULL;
}

static bool bytes_equal(void const *a, uint32_t an, void const *b, uint32_t bn) {
	return an == bn && (an == 0u || memcmp(a, b, an) == 0);
}

static bool real_equal(double a, double b) { return a == b || (isnan(a) && isnan(b)); }

static bool scalar_equal(XtkValue const *a, XtkValue const *b) {
	switch (a->kind) {
	case XTK_VALUE_BOOL  : return a->u.b == b->u.b;
	case XTK_VALUE_I32   : return a->u.i32 == b->u.i32;
	case XTK_VALUE_F32   : return real_equal(a->u.f32, b->u.f32);
	case XTK_VALUE_F64   : return real_equal(a->u.f64, b->u.f64);
	case XTK_VALUE_ENUM  : return a->u.u32 == b->u.u32;
	case XTK_VALUE_COLOR : return a->u.color.rgba == b->u.color.rgba;
	default              : return false;
	}
}

static bool value_equal(XtkValue const *a, XtkValue const *b) {
	if (a->kind != b->kind) return false;
	if (a->kind == XTK_VALUE_NONE) return true;
	if (a->kind == XTK_VALUE_RESOURCE) return a->u.resource == b->u.resource;
	if (a->kind == XTK_VALUE_STRING)
		return bytes_equal(a->u.string.data, a->u.string.len, b->u.string.data, b->u.string.len);
	if (a->kind == XTK_VALUE_BYTES)
		return bytes_equal(a->u.bytes.data, a->u.bytes.len, b->u.bytes.data, b->u.bytes.len);
	return scalar_equal(a, b);
}

static bool is_model_prop(XtkPropertyId id) {
	return id == XTK_PROP_ITEMS || id == XTK_PROP_NAV_MODEL || id == XTK_PROP_GROUPS;
}

static XtkValue default_value(XtkPropertyId id, XtkValueKind kind) {
	XtkValue value = {.kind = kind};
	if (id == XTK_PROP_WIDTH || id == XTK_PROP_HEIGHT) value.u.f32 = NAN;
	if (id == XTK_PROP_ENABLED || id == XTK_PROP_SETTINGS_VISIBLE || id == XTK_PROP_ALWAYS_SHOW_HEADER)
		value.u.b = true;
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

static bool emit_same_id(
  XtkBatch *batch, XtkNodeRef target, XtkPropSlot const *old, XtkPropPatch const *next, XtkEcho const *echo,
  bool *changed
) {
	if (value_equal(&old->value, &next->value) && !forced(echo, next->id)) return true;
	*changed = true;
	return xtk_batch_set(batch, target, next->id, next->value, echo->stamp);
}

static bool emit_removed(XtkBatch *batch, XtkNodeRef target, XtkPropSlot const *old, bool skip_model, bool *changed) {
	if (skip_model && is_model_prop(old->id)) return true;
	*changed       = true;
	XtkValue value = default_value(old->id, old->value.kind);
	return xtk_batch_set(batch, target, old->id, value, (XtkChangeStamp) {0});
}

static bool
emit_added(XtkBatch *batch, XtkNodeRef target, XtkPropPatch const *next, XtkEcho const *echo, bool *changed) {
	*changed = true;
	return xtk_batch_set(batch, target, next->id, next->value, echo->stamp);
}

static bool diff_step(
  XtkBatch *batch, XtkNodeRef target, XtkPropState const *old, uint32_t old_count, XtkPropView next, bool skip_model,
  XtkEcho const *echo, uint32_t *pi, uint32_t *pj, bool *changed
) {
	XtkPropertyId oid = old->items [*pi].id;
	XtkPropertyId nid = next.items [*pj].id;
	if (oid == nid) {
		if (!emit_same_id(batch, target, &old->items [*pi], &next.items [*pj], echo, changed)) return false;
		(*pi)++;
		(*pj)++;
		return true;
	}
	if (oid < nid) return emit_removed(batch, target, &old->items [(*pi)++], skip_model, changed);
	return emit_added(batch, target, &next.items [(*pj)++], echo, changed);
	( void ) old_count;
}

static bool diff_drain_tails(
  XtkBatch *batch, XtkNodeRef target, XtkPropState const *old, uint32_t old_count, XtkPropView next, bool skip_model,
  XtkEcho const *echo, uint32_t i, uint32_t j, bool *changed
) {
	while (i < old_count)
		if (!emit_removed(batch, target, &old->items [i++], skip_model, changed)) return false;
	while (j < next.count)
		if (!emit_added(batch, target, &next.items [j++], echo, changed)) return false;
	return true;
}

bool xtk_prop_state_diff(
  XtkBatch *batch, XtkNodeRef target, XtkPropState const *old, XtkPropView next, bool skip_model, XtkEcho const *echo,
  bool *changed
) {
	if (!batch || !changed) return false;
	*changed           = false;
	uint32_t old_count = old ? old->count : 0u;
	uint32_t i = 0u, j = 0u;
	while (i < old_count && j < next.count)
		if (!diff_step(batch, target, old, old_count, next, skip_model, echo, &i, &j, changed)) return false;
	return diff_drain_tails(batch, target, old, old_count, next, skip_model, echo, i, j, changed);
}

static bool detach_inline_blob(XtkPropSlot *dst, XtkPropSlot const *src) {
	if (src->value.kind == XTK_VALUE_STRING) {
		if (!src->value.u.string.len) return true;
		dst->blob = blob_create(src->value.u.string.data, src->value.u.string.len, true);
		if (!dst->blob) return false;
		dst->value.u.string.data = ( char * ) dst->blob->data;
		return true;
	}
	if (src->value.kind != XTK_VALUE_BYTES || !src->value.u.bytes.len) return true;
	dst->blob = blob_create(src->value.u.bytes.data, src->value.u.bytes.len, false);
	if (!dst->blob) return false;
	dst->value.u.bytes.data = dst->blob->data;
	return true;
}

static bool retain_slot(XtkPropSlot *dst, XtkPropSlot const *src, bool detach_inline) {
	*dst = *src;
	if (src->blob) {
		blob_retain(dst->blob);
		return true;
	}
	return !detach_inline || detach_inline_blob(dst, src);
}

static bool merge_slot(XtkPropSlot *dst, XtkPropSlot const *old, XtkPropPatch const *next, bool detach_inline) {
	if (old && value_equal(&old->value, &next->value)) return retain_slot(dst, old, detach_inline);
	return slot_from_patch(dst, next);
}

static bool merge_emit(XtkPropSlot *out, uint32_t *pk, XtkPropPatch const *patch) {
	if (!slot_from_patch(&out [*pk], patch)) return false;
	(*pk)++;
	return true;
}

static bool merge_step(
  XtkPropState const *old, XtkPropView next, bool skip_model, bool detach_inline, XtkPropSlot *out, uint32_t *pi,
  uint32_t *pj, uint32_t *pk
) {
	XtkPropertyId oid = old->items [*pi].id;
	XtkPropertyId nid = next.items [*pj].id;
	if (oid == nid) {
		if (!merge_slot(&out [*pk], &old->items [*pi], &next.items [*pj], detach_inline)) return false;
		(*pk)++;
		(*pi)++;
		(*pj)++;
		return true;
	}
	if (oid > nid) return merge_emit(out, pk, &next.items [(*pj)++]);
	uint32_t oi = (*pi)++;
	if (!skip_model || !is_model_prop(oid)) return true;
	if (!retain_slot(&out [*pk], &old->items [oi], detach_inline)) return false;
	(*pk)++;
	return true;
}

static bool merge_slots(
  XtkPropState const *old, XtkPropView next, bool skip_model, bool detach_inline, XtkPropSlot *out, uint32_t *out_count
) {
	uint32_t old_count = old ? old->count : 0u;
	uint32_t i = 0u, j = 0u, k = 0u;
	while (i < old_count && j < next.count)
		if (!merge_step(old, next, skip_model, detach_inline, out, &i, &j, &k)) goto fail;
	while (i < old_count) {
		if (skip_model && is_model_prop(old->items [i].id) && !retain_slot(&out [k++], &old->items [i], detach_inline))
		{
			k--;
			goto fail;
		}
		i++;
	}
	while (j < next.count) {
		if (!slot_from_patch(&out [k], &next.items [j])) goto fail;
		k++;
		j++;
	}
	*out_count = k;
	return true;
fail:
	xtk_prop_slots_release(out, k);
	return false;
}

static XtkPropState *
state_alloc_slots(XtkPropSlot const *slots, uint32_t count, uint64_t revision, XtkModelVer model_ver) {
	if (( size_t ) count > (SIZE_MAX - sizeof(XtkPropState)) / sizeof(XtkPropSlot)) return NULL;
	XtkPropState *state = ( XtkPropState * ) xtk_alloc(sizeof(XtkPropState) + ( size_t ) count * sizeof(XtkPropSlot));
	if (!state) return NULL;
	*state = (XtkPropState) {
	  .refcount  = 1u,
	  .count     = count,
	  .capacity  = count,
	  .revision  = revision,
	  .model_ver = model_ver,
	  .items     = ( XtkPropSlot * ) (state + 1),
	};
	if (count) memcpy(state->items, slots, ( size_t ) count * sizeof(XtkPropSlot));
	return state;
}

static bool stage_in_place_patch(
  XtkArena *patch_arena, XtkPropSlot *merged, uint32_t count, XtkPropSlot **out_patch, uint32_t *out_count
) {
	XtkPropSlot *staged
	  = count ? ( XtkPropSlot * ) xtk_arena_alloc(patch_arena, ( size_t ) count * sizeof(*staged)) : NULL;
	if (count && !staged) {
		xtk_prop_slots_release(merged, count);
		return false;
	}
	if (count) memcpy(staged, merged, ( size_t ) count * sizeof(*staged));
	*out_patch = staged;
	*out_count = count;
	return true;
}

bool xtk_prop_state_prepare(
  XtkPropState *old, XtkPropView next, XtkModelVer model_ver, bool skip_model, XtkArena *patch_arena,
  XtkPropState **out_new, XtkPropSlot **out_patch, uint32_t *out_count
) {
	*out_new              = NULL;
	*out_patch            = NULL;
	*out_count            = 0u;
	uint32_t    max_count = next.count + (skip_model ? 2u : 0u);
	bool        in_place  = old && old->refcount == 1u && max_count <= old->capacity && patch_arena;
	XtkPropSlot merged [XTK_PROP_STANDARD_COUNT + 4u];
	uint32_t    count = 0u;
	if (!merge_slots(old, next, skip_model, !in_place, merged, &count)) return false;
	if (in_place) return stage_in_place_patch(patch_arena, merged, count, out_patch, out_count);
	XtkPropState *state = state_alloc_slots(merged, count, old ? old->revision + 1u : 1u, model_ver);
	if (!state) {
		xtk_prop_slots_release(merged, count);
		return false;
	}
	*out_new = state;
	return true;
}

void xtk_prop_state_apply_patch(XtkPropState *state, XtkPropSlot const *slots, uint32_t count, XtkModelVer model_ver) {
	if (!state) return;
	xtk_prop_slots_release(state->items, state->count);
	if (count) memcpy(state->items, slots, ( size_t ) count * sizeof(XtkPropSlot));
	state->count     = count;
	state->model_ver = model_ver;
	state->revision++;
}
