#include "xtk_retained_internal.h"

static bool clone_string(XtkValue *dst, XtkValue const *src) {
	uint32_t len = src->u.string.len;
	char    *dup = ( char * ) xtk_alloc(( size_t ) len + 1u);
	if (!dup) {
		dst->u.string.data = NULL;
		return false;
	}
	if (len) memcpy(dup, src->u.string.data, len);
	dup [len]          = '\0';
	dst->u.string.data = dup;
	return true;
}

static bool clone_bytes(XtkValue *dst, XtkValue const *src) {
	uint32_t len = src->u.bytes.len;
	uint8_t *dup = len ? ( uint8_t * ) xtk_alloc(len) : NULL;
	if (len && !dup) {
		dst->u.bytes.data = NULL;
		return false;
	}
	if (len) memcpy(dup, src->u.bytes.data, len);
	dst->u.bytes.data = dup;
	return true;
}

void retained_value_clear(XtkValue *v) {
	if (!v) return;
	if (v->kind == XTK_VALUE_STRING) xtk_alloc_free(v->u.string.data);
	if (v->kind == XTK_VALUE_BYTES) xtk_alloc_free(v->u.bytes.data);
	*v = (XtkValue) {.kind = XTK_VALUE_NONE};
}

bool retained_value_clone(XtkValue *dst, XtkValue const *src) {
	*dst = *src;
	if (src->kind == XTK_VALUE_STRING) return clone_string(dst, src);
	if (src->kind == XTK_VALUE_BYTES) return clone_bytes(dst, src);
	return true;
}

static void prop_bucket_clear(PropBucket *bucket) {
	for (uint32_t i = 0; i < bucket->count; i++)
		if (bucket->entries [i].live) retained_value_clear(&bucket->entries [i].value);
	xtk_alloc_free(bucket->entries);
	*bucket = (PropBucket) {0};
}

static bool prop_buckets_ensure(Retained *R, uint32_t index) {
	if (index < R->prop_bucket_cap) return true;
	uint32_t cap = R->prop_bucket_cap ? R->prop_bucket_cap : 64u;
	while (cap <= index) {
		if (cap > UINT32_MAX / 2u) return false;
		cap *= 2u;
	}
	PropBucket *buckets = xtk_alloc_resize(R->prop_buckets, sizeof(*buckets) * cap);
	if (!buckets) return false;
	memset(buckets + R->prop_bucket_cap, 0, sizeof(*buckets) * (cap - R->prop_bucket_cap));
	R->prop_buckets    = buckets;
	R->prop_bucket_cap = cap;
	return true;
}

static PropBucket *prop_bucket(Retained *R, XtkCtrl control, bool create) {
	uint32_t index = xent_node_index(retained_as_node(control));
	if (index >= R->prop_bucket_cap && (!create || !prop_buckets_ensure(R, index))) return NULL;
	PropBucket *bucket = &R->prop_buckets [index];
	if (bucket->owner == control) return bucket;
	if (!create) return NULL;
	if (bucket->owner != XTK_CTRL_INVALID) prop_bucket_clear(bucket);
	bucket->owner = control;
	return bucket;
}

static PropEntry *prop_find(PropBucket *bucket, XtkPropertyId id) {
	if (!bucket) return NULL;
	for (uint32_t i = 0; i < bucket->count; i++) {
		PropEntry *entry = &bucket->entries [i];
		if (entry->live && entry->id == id) return entry;
	}
	return NULL;
}

PropEntry *retained_prop_find(Retained *R, XtkCtrl control, XtkPropertyId id) {
	return prop_find(prop_bucket(R, control, false), id);
}

PropEntry const *retained_prop_find_c(Retained const *R, XtkCtrl control, XtkPropertyId id) {
	return retained_prop_find(( Retained * ) R, control, id);
}

static PropEntry *prop_reuse(PropBucket *bucket, XtkPropertyId id) {
	for (uint32_t i = 0; i < bucket->count; i++)
		if (!bucket->entries [i].live) {
			bucket->entries [i].id = id;
			return &bucket->entries [i];
		}
	return NULL;
}

static bool prop_grow(PropBucket *bucket) {
	if (bucket->count < bucket->cap) return true;
	uint32_t cap = bucket->cap ? bucket->cap * 2u : 4u;
	if (cap < bucket->cap) return false;
	PropEntry *entries = xtk_alloc_resize(bucket->entries, sizeof(*entries) * cap);
	if (!entries) return false;
	bucket->entries = entries;
	bucket->cap     = cap;
	return true;
}

PropEntry *retained_prop_add(Retained *R, XtkCtrl control, XtkPropertyId id) {
	PropBucket *bucket = prop_bucket(R, control, true);
	if (!bucket) return NULL;
	PropEntry *reused = prop_reuse(bucket, id);
	if (reused) return reused;
	if (!prop_grow(bucket)) return NULL;
	PropEntry *entry = &bucket->entries [bucket->count++];
	*entry           = (PropEntry) {.id = id};
	return entry;
}

void retained_clear_control_props(Retained *R, XtkCtrl control) {
	PropBucket *bucket = prop_bucket(R, control, false);
	if (bucket) prop_bucket_clear(bucket);
}

void retained_props_dispose(Retained *R) {
	for (uint32_t i = 0; i < R->prop_bucket_cap; i++) prop_bucket_clear(&R->prop_buckets [i]);
	xtk_alloc_free(R->prop_buckets);
	R->prop_buckets    = NULL;
	R->prop_bucket_cap = 0u;
}

void retained_rollback_prop(Retained *R, UndoProp *prop) {
	PropEntry *e = retained_prop_find(R, prop->control, prop->id);
	if (!prop->had_value) {
		if (e) {
			retained_value_clear(&e->value);
			e->live = false;
		}
		return;
	}
	if (!e) return;
	retained_value_clear(&e->value);
	e->value             = prop->old_value;
	e->change            = prop->old_change;
	prop->old_value.kind = XTK_VALUE_NONE;
}

bool retained_apply_prop(Prepare *P, XtkCtrl control, XtkPropPatch const *patch) {
	Retained  *R     = P->R;
	PropEntry *entry = retained_prop_find(R, control, patch->id);
	bool       had   = entry != NULL;
	if (!entry) entry = retained_prop_add(R, control, patch->id);
	if (!entry) return false;

	XtkValue next;
	if (!retained_value_clone(&next, &patch->value)) return false;
	Undo u = {
	  .kind = UNDO_PROP, .u.prop = {.control = control, .id = patch->id, .had_value = had}
    };
	if (!retained_undo_push(P, u)) {
		retained_value_clear(&next);
		return false;
	}

	UndoProp *undo = &P->undos [P->undo_count - 1u].u.prop;
	if (had) {
		undo->old_value  = entry->value;
		undo->old_change = entry->change;
	}
	entry->value  = next;
	entry->change = patch->change;
	entry->live   = true;
	retained_invalidate_prop(R, control, patch->id);
	return true;
}

bool retained_value_to_view(XtkValue const *v, XtkValueView *out) {
	if (v->kind == XTK_VALUE_NONE || v->kind > XTK_VALUE_BYTES) return false;
	out->kind = v->kind;
	memcpy(&out->u, &v->u, sizeof(out->u));
	return true;
}

bool retained_host_get_property(
  XtkHost const *host, XtkCtrl control, XtkPropertyId property, XtkValueView *out_value, XtkChangeStamp *out_change
) {
	Retained const *R = retained_impl_c(host);
	if (!R || !out_value || !retained_host_is_live(host, control)) return false;
	if (property == XTK_PROP_COMPONENT_PROPS && R->comp) {
		size_t      sz   = 0u;
		void const *blob = xtk_comp_props(R->comp, control, &sz);
		if (!blob && sz != 0u) return false;
		if (out_change) *out_change = (XtkChangeStamp) {0};
		*out_value = (XtkValueView) {
		  .kind = XTK_VALUE_BYTES, .u.bytes = {.data = ( uint8_t const * ) blob, .len = ( uint32_t ) sz}
        };
		return xtk_comp_hasinst(R->comp, control);
	}
	PropEntry const *e = retained_prop_find_c(R, control, property);
	if (!e) return false;
	if (out_change) *out_change = e->change;
	return retained_value_to_view(&e->value, out_value);
}
