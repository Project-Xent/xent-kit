#include "xtk_identity.h"
#include "xtk_key.h"
#include "../xtk_hash.h"
#include "../xtk_internal.h"

#include <string.h>
#include <stdio.h>

XtkSiblingMode xtk_sibling_mode(XtkEl const *parent) {
	if (!parent || XTK_EL_DATA(parent)->child_count <= 0) return XTK_SIBLING_EMPTY;
	return xtk_key_present(&XTK_EL_DATA(xtk_el_child(parent, 0))->key) ? XTK_SIBLING_KEYED : XTK_SIBLING_POSITIONAL;
}

typedef struct KeySlot {
	uint32_t hash;
	int      index;
} KeySlot;

enum
{
	XTK_IDENTITY_DEPTH_MAX = 256,
};

static void diagnostic_key(XtkIdentityDiag *out, XtkKey const *key) {
	if (!out) return;
	out->key_kind = key ? key->kind : XTK_KEY_NONE;
	out->key_u64  = key && key->kind == XTK_KEY_U64 ? key->value.u64 : 0u;
	char        number [32];
	char const *text = key && key->kind == XTK_KEY_STRING ? key->value.string : NULL;
	if (key && key->kind == XTK_KEY_U64) {
		snprintf(number, sizeof(number), "%llu", ( unsigned long long ) key->value.u64);
		text = number;
	}
	size_t len      = text ? strlen(text) : 0u;
	size_t copy_len = len < XTK_IDENTITY_KEY_MAX - 1u ? len : XTK_IDENTITY_KEY_MAX - 1u;
	if (copy_len) memcpy(out->key, text, copy_len);
	out->key [copy_len] = '\0';
	out->key_length     = len > UINT32_MAX ? UINT32_MAX : ( uint32_t ) len;
	out->key_truncated  = copy_len != len;
}

static void diagnostic_path(XtkIdentityDiag *out, int const *path, uint32_t depth) {
	if (!out) return;
	uint32_t count = depth < XTK_IDENTITY_PATH_MAX ? depth : XTK_IDENTITY_PATH_MAX;
	if (count) memcpy(out->path, path, sizeof(int) * count);
	out->path_depth     = depth;
	out->path_truncated = depth > XTK_IDENTITY_PATH_MAX;
}

static bool type_known(XtkScene const *scene, XtkCtrlId type) { return xtk_scene_ctrldesc(scene, type) != NULL; }

static bool keyed_keys_equal(XtkEl const *parent, int other, XtkKey const *key, uint32_t h, KeySlot const *slot) {
	if (slot->hash != h) return false;
	XtkKey const *other_key = &XTK_EL_DATA(xtk_el_child(parent, other))->key;
	return xtk_key_equal(other_key, key);
}

static XtkIdentityError report_dup_key(XtkEl const *parent, int other, int i, XtkKey const *key, XtkIdentityDiag *out) {
	if (out) {
		out->error       = XTK_IDENTITY_DUPLICATE_KEY;
		out->parent_type = XTK_EL_DATA(parent)->type;
		out->child_a     = other;
		out->child_b     = i;
		diagnostic_key(out, key);
	}
	return XTK_IDENTITY_DUPLICATE_KEY;
}

static XtkIdentityError keyed_insert(XtkEl const *parent, KeySlot *slots, uint32_t cap, int i, XtkIdentityDiag *out) {
	XtkKey const *key  = &XTK_EL_DATA(xtk_el_child(parent, i))->key;
	uint32_t      h    = xtk_key_hash(key);
	uint32_t      mask = cap - 1u;
	uint32_t      slot = h & mask;
	while (slots [slot].index != 0) {
		int other = slots [slot].index - 1;
		if (keyed_keys_equal(parent, other, key, h, &slots [slot])) return report_dup_key(parent, other, i, key, out);
		slot = (slot + 1u) & mask;
	}
	slots [slot].hash  = h;
	slots [slot].index = i + 1;
	return XTK_IDENTITY_OK;
}

static XtkIdentityError validate_keyed_keys(XtkEl const *parent, XtkScratch *scratch, XtkIdentityDiag *out) {
	int n = XTK_EL_DATA(parent)->child_count;
	if (n <= 1) return XTK_IDENTITY_OK;

	uint32_t cap = 1u;
	while (cap < ( uint32_t ) n * 2u) {
		if (cap > UINT32_MAX / 2u) return XTK_IDENTITY_OOM;
		cap *= 2u;
	}
	KeySlot *slots = ( KeySlot * ) xtk_scratch_reserve(scratch, sizeof(KeySlot) * cap, _Alignof(KeySlot));
	if (!slots) return XTK_IDENTITY_OOM;
	memset(slots, 0, sizeof(KeySlot) * cap);

	for (int i = 0; i < n; i++) {
		XtkIdentityError err = keyed_insert(parent, slots, cap, i, out);
		if (err != XTK_IDENTITY_OK) return err;
	}
	return XTK_IDENTITY_OK;
}

static XtkIdentityError sibling_type_or_mode(
  XtkScene const *scene, XtkEl const *parent, XtkEl const *child, int i, bool keyed, XtkIdentityDiag *out
) {
	if (!child) {
		if (out) {
			out->error       = XTK_IDENTITY_MALFORMED;
			out->parent_type = XTK_EL_DATA(parent)->type;
			out->child_a     = i;
		}
		return XTK_IDENTITY_MALFORMED;
	}
	if (!type_known(scene, XTK_EL_DATA(child)->type)) {
		if (out) {
			out->error       = XTK_IDENTITY_INVALID_TYPE;
			out->parent_type = XTK_EL_DATA(parent)->type;
			out->child_a     = i;
		}
		return XTK_IDENTITY_INVALID_TYPE;
	}
	if (xtk_key_present(&XTK_EL_DATA(child)->key) == keyed) return XTK_IDENTITY_OK;
	if (out) {
		out->error       = XTK_IDENTITY_MIXED;
		out->parent_type = XTK_EL_DATA(parent)->type;
		out->child_a     = 0;
		out->child_b     = i;
	}
	return XTK_IDENTITY_MIXED;
}

static XtkIdentityError report_parent_error(XtkEl const *parent, XtkIdentityDiag *out, XtkIdentityError error) {
	if (out) {
		out->error       = error;
		out->parent_type = XTK_EL_DATA(parent)->type;
	}
	return error;
}

static XtkIdentityError
validate_siblings(XtkScene const *scene, XtkEl const *parent, XtkScratch *scratch, XtkIdentityDiag *out) {
	if (XTK_EL_DATA(parent)->child_count < 0) return report_parent_error(parent, out, XTK_IDENTITY_INVALID_COUNT);
	if (XTK_EL_DATA(parent)->child_count == 0) return XTK_IDENTITY_OK;
	if (!xtk_el_child(parent, 0)) return report_parent_error(parent, out, XTK_IDENTITY_MALFORMED);

	bool keyed = xtk_key_present(&XTK_EL_DATA(xtk_el_child(parent, 0))->key);
	for (int i = 0; i < XTK_EL_DATA(parent)->child_count; i++) {
		XtkIdentityError err = sibling_type_or_mode(scene, parent, xtk_el_child(parent, i), i, keyed, out);
		if (err != XTK_IDENTITY_OK) return err;
	}
	if (keyed) return validate_keyed_keys(parent, scratch, out);
	return XTK_IDENTITY_OK;
}

typedef struct IdentityWalk {
	XtkScene const  *scene;
	XtkScratch      *scratch;
	XtkIdentityDiag *out;
	uint64_t        *regions;
	uint32_t         region_capacity;
	uint32_t         order;
	int              path [XTK_IDENTITY_PATH_MAX];
} IdentityWalk;

static bool prepare_regions(IdentityWalk *ctx, XtkEl const *root) {
	if (!root->ui) return false;
	uint32_t count = root->ui->composition.element_count;
	if (!count) return true;
	if (count > UINT32_MAX / 2u) return false;
	uint32_t need     = count * 2u;
	uint32_t capacity = 8u;
	while (capacity < need) {
		if (capacity > UINT32_MAX / 2u) return false;
		capacity *= 2u;
	}
	ctx->regions = xtk_scratch_reserve(ctx->scratch, sizeof(*ctx->regions) * capacity, _Alignof(uint64_t));
	if (!ctx->regions) return false;
	memset(ctx->regions, 0, sizeof(*ctx->regions) * capacity);
	ctx->region_capacity = capacity;
	return true;
}

static XtkIdentityError report_duplicate_region(IdentityWalk *ctx, uint64_t id) {
	if (ctx->out) {
		ctx->out->error     = XTK_IDENTITY_DUPLICATE_REGION;
		ctx->out->region_id = id;
	}
	return XTK_IDENTITY_DUPLICATE_REGION;
}

static XtkIdentityError validate_region(IdentityWalk *ctx, XtkEl const *el) {
	uint64_t id = XTK_EL_DATA(el)->region_id;
	if (!id) return XTK_IDENTITY_OK;
	uint32_t mask = ctx->region_capacity - 1u;
	uint32_t slot = ( uint32_t ) xtk_hash_u64(id) & mask;
	while (ctx->regions [slot]) {
		if (ctx->regions [slot] == id) return report_duplicate_region(ctx, id);
		slot = (slot + 1u) & mask;
	}
	ctx->regions [slot] = id;
	return XTK_IDENTITY_OK;
}

static XtkIdentityError walk(IdentityWalk *ctx, XtkEl const *el, uint32_t depth);

static XtkIdentityError walk_node(IdentityWalk *ctx, XtkEl const *el, uint32_t depth) {
	if (depth > XTK_IDENTITY_DEPTH_MAX) {
		if (ctx->out) {
			ctx->out->error       = XTK_IDENTITY_INVALID_COUNT;
			ctx->out->parent_type = el ? XTK_EL_DATA(el)->type : XTK_CTRL_ID_INVALID;
			diagnostic_path(ctx->out, ctx->path, depth);
		}
		return XTK_IDENTITY_INVALID_COUNT;
	}
	if (!type_known(ctx->scene, XTK_EL_DATA(el)->type)) {
		if (ctx->out) {
			ctx->out->error       = XTK_IDENTITY_INVALID_TYPE;
			ctx->out->parent_type = XTK_EL_DATA(el)->type;
			diagnostic_path(ctx->out, ctx->path, depth);
		}
		return XTK_IDENTITY_INVALID_TYPE;
	}
	XtkIdentityError region = validate_region(ctx, el);
	if (region != XTK_IDENTITY_OK) {
		diagnostic_path(ctx->out, ctx->path, depth);
		return region;
	}
	size_t           mark = xtk_scratch_mark(ctx->scratch);
	XtkIdentityError err  = validate_siblings(ctx->scene, el, ctx->scratch, ctx->out);
	xtk_scratch_rewind(ctx->scratch, mark);
	if (err != XTK_IDENTITY_OK) {
		diagnostic_path(ctx->out, ctx->path, depth);
		return err;
	}
	return XTK_IDENTITY_OK;
}

static XtkIdentityError walk_children(IdentityWalk *ctx, XtkEl const *el, uint32_t depth) {
	for (int i = 0; i < XTK_EL_DATA(el)->child_count; i++) {
		if (depth < XTK_IDENTITY_PATH_MAX) ctx->path [depth] = i;
		XtkIdentityError err = walk(ctx, xtk_el_child(el, i), depth + 1u);
		if (err != XTK_IDENTITY_OK) return err;
	}
	return XTK_IDENTITY_OK;
}

static XtkIdentityError walk(IdentityWalk *ctx, XtkEl const *el, uint32_t depth) {
	XTK_EL_DATA(el)->subtree_begin = ctx->order++;
	XtkIdentityError err           = walk_node(ctx, el, depth);
	if (err != XTK_IDENTITY_OK) return err;
	err = walk_children(ctx, el, depth);
	if (err == XTK_IDENTITY_OK) XTK_EL_DATA(el)->subtree_end = ctx->order;
	return err;
}

XtkIdentityError
xtk_identity_validate_tree(XtkScene const *scene, XtkEl const *root, XtkScratch *scratch, XtkIdentityDiag *out) {
	if (out) memset(out, 0, sizeof(*out));
	if (!scene || !root || !scratch) return XTK_IDENTITY_INVALID_TYPE;
	IdentityWalk ctx = {.scene = scene, .scratch = scratch, .out = out};
	if (!prepare_regions(&ctx, root)) return XTK_IDENTITY_OOM;
	return walk(&ctx, root, 0u);
}
