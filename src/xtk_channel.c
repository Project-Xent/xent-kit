#include <xtk/xtk_channel.h>
#include <xtk/xtk_alloc.h>

#include "batch/xtk_batch_internal.h"
#include "xtk_hash.h"

#include <string.h>

struct XtkChannel {
	XtkScene  scene;
	XtkBatch *batch;
	uint32_t *slots;
	uint32_t  cap;
	uint32_t  count;
};

static uint64_t pair_key(XtkCtrl target, XtkPropertyId id) {
	return target ^ (( uint64_t ) id * UINT64_C(0x9e3779b97f4a7c15));
}

static bool slot_matches(XtkChannel const *ch, uint32_t op_index, XtkCtrl target, XtkPropertyId id) {
	XtkBatchOp const *op = &ch->batch->ops [op_index];
	return op->kind == XTK_BATCH_OP_SET_PROP
	    && op->u.set_prop.target.kind == XTK_REF_EXISTING
	    && op->u.set_prop.target.u.existing == target
	    && op->u.set_prop.patch.id == id;
}

static bool channel_rehash(XtkChannel *ch, uint32_t new_cap) {
	if (( size_t ) new_cap > SIZE_MAX / sizeof(uint32_t)) return false;
	uint32_t *slots = ( uint32_t * ) xtk_alloc_zero(new_cap, sizeof(uint32_t));
	if (!slots) return false;
	uint32_t mask = new_cap - 1u;
	for (uint32_t i = 0; i < ch->batch->count; i++) {
		XtkBatchOp const *op = &ch->batch->ops [i];
		if (op->kind != XTK_BATCH_OP_SET_PROP || op->u.set_prop.target.kind != XTK_REF_EXISTING) continue;
		uint64_t key  = pair_key(op->u.set_prop.target.u.existing, op->u.set_prop.patch.id);
		uint32_t slot = ( uint32_t ) xtk_hash_u64(key) & mask;
		while (slots [slot]) slot = (slot + 1u) & mask;
		slots [slot] = i + 1u;
	}
	xtk_alloc_free(ch->slots);
	ch->slots = slots;
	ch->cap   = new_cap;
	return true;
}

static bool channel_ensure_slots(XtkChannel *ch) {
	if (ch->cap && (ch->count + 1u) * 10u < ch->cap * 7u) return true;
	uint32_t next_cap = ch->cap ? ch->cap * 2u : 32u;
	if (next_cap < ch->cap) return false;
	return channel_rehash(ch, next_cap);
}

static uint32_t channel_find_slot(XtkChannel const *ch, XtkCtrl target, XtkPropertyId id, uint32_t *out_empty) {
	uint32_t mask = ch->cap - 1u;
	uint32_t slot = ( uint32_t ) xtk_hash_u64(pair_key(target, id)) & mask;
	for (uint32_t probe = 0; probe < ch->cap; probe++) {
		uint32_t entry = ch->slots [slot];
		if (!entry) {
			if (out_empty) *out_empty = slot;
			return UINT32_MAX;
		}
		if (slot_matches(ch, entry - 1u, target, id)) return entry - 1u;
		slot = (slot + 1u) & mask;
	}
	return UINT32_MAX;
}

XtkChannel *xtk_channel_create(XtkScene scene) {
	if (!scene.host || !scene.host->vt) return NULL;
	XtkChannel *ch = ( XtkChannel * ) xtk_alloc_zero(1, sizeof(*ch));
	if (!ch) return NULL;
	ch->scene = scene;
	ch->batch = xtk_batch_alloc(xtk_scene_revision(&scene));
	if (!ch->batch) {
		xtk_alloc_free(ch);
		return NULL;
	}
	return ch;
}

void xtk_channel_destroy(XtkChannel *ch) {
	if (!ch) return;
	xtk_batch_free(ch->batch);
	xtk_alloc_free(ch->slots);
	xtk_alloc_free(ch);
}

uint32_t xtk_channel_pending(XtkChannel const *ch) { return ch && ch->batch ? ch->batch->count : 0u; }

void     xtk_channel_clear(XtkChannel *ch) {
	if (!ch) return;
	if (ch->batch) xtk_batch_reset(ch->batch, xtk_scene_revision(&ch->scene));
	if (ch->slots && ch->cap) memset(ch->slots, 0, sizeof(uint32_t) * ch->cap);
	ch->count = 0u;
}

bool xtk_channel_set(XtkChannel *ch, XtkCtrl target, XtkPropertyId id, XtkValue value, XtkChangeStamp change) {
	if (!ch || !ch->batch || target == XTK_CTRL_INVALID) return false;
	if (!channel_ensure_slots(ch)) return false;
	uint32_t empty = 0u;
	uint32_t found = channel_find_slot(ch, target, id, &empty);
	if (found != UINT32_MAX) return xtk_batch_replace_prop(ch->batch, found, &value, change);
	uint32_t idx = ch->batch->count;
	if (!xtk_batch_set(ch->batch, xtk_ref_existing(target), id, value, change)) return false;
	ch->slots [empty] = idx + 1u;
	ch->count++;
	return true;
}

bool xtk_channel_set_bool(XtkChannel *ch, XtkCtrl target, XtkPropertyId id, bool value, XtkChangeStamp change) {
	return xtk_channel_set(ch, target, id, (XtkValue) {.kind = XTK_VALUE_BOOL, .u.b = value}, change);
}

bool xtk_channel_set_i32(XtkChannel *ch, XtkCtrl target, XtkPropertyId id, int32_t value, XtkChangeStamp change) {
	return xtk_channel_set(ch, target, id, (XtkValue) {.kind = XTK_VALUE_I32, .u.i32 = value}, change);
}

bool xtk_channel_set_f32(XtkChannel *ch, XtkCtrl target, XtkPropertyId id, float value, XtkChangeStamp change) {
	return xtk_channel_set(ch, target, id, (XtkValue) {.kind = XTK_VALUE_F32, .u.f32 = value}, change);
}

bool xtk_channel_set_f64(XtkChannel *ch, XtkCtrl target, XtkPropertyId id, double value, XtkChangeStamp change) {
	return xtk_channel_set(ch, target, id, (XtkValue) {.kind = XTK_VALUE_F64, .u.f64 = value}, change);
}

bool xtk_channel_set_enum(XtkChannel *ch, XtkCtrl target, XtkPropertyId id, uint32_t value, XtkChangeStamp change) {
	return xtk_channel_set(ch, target, id, (XtkValue) {.kind = XTK_VALUE_ENUM, .u.u32 = value}, change);
}

bool xtk_channel_set_color(XtkChannel *ch, XtkCtrl target, XtkPropertyId id, XtkColor value, XtkChangeStamp change) {
	return xtk_channel_set(ch, target, id, (XtkValue) {.kind = XTK_VALUE_COLOR, .u.color = value}, change);
}

bool xtk_channel_set_resource(
  XtkChannel *ch, XtkCtrl target, XtkPropertyId id, XtkResource value, XtkChangeStamp change
) {
	return xtk_channel_set(ch, target, id, (XtkValue) {.kind = XTK_VALUE_RESOURCE, .u.resource = value}, change);
}

bool xtk_channel_set_string(
  XtkChannel *ch, XtkCtrl target, XtkPropertyId id, char const *data, uint32_t len, XtkChangeStamp change
) {
	XtkValue value = {
	  .kind = XTK_VALUE_STRING, .u.string = {.data = ( char * ) ( uintptr_t ) data, .len = len}
    };
	return xtk_channel_set(ch, target, id, value, change);
}

XtkBatchResult *xtk_channel_flush(XtkChannel *ch, XtkBatchDiag *diagnostic) {
	if (!ch || !ch->batch || ch->batch->count == 0u) {
		if (diagnostic) *diagnostic = (XtkBatchDiag) {.error = XTK_BATCH_OK};
		return NULL;
	}
	ch->batch->revision = xtk_scene_revision(&ch->scene);
	XtkTxn          txn = {.scene = &ch->scene, .batch = ch->batch, .borrowed = true};
	XtkBatchResult *res = xtk_txn_commit(&txn, diagnostic);
	if (ch->slots && ch->cap) memset(ch->slots, 0, sizeof(uint32_t) * ch->cap);
	ch->count = 0u;
	return res;
}

bool xtk_channel_commit(XtkChannel *ch, XtkBatchDiag *diagnostic) {
	if (!ch || !ch->batch || ch->batch->count == 0u) {
		if (diagnostic) *diagnostic = (XtkBatchDiag) {.error = XTK_BATCH_OK};
		return true;
	}
	XtkBatchResult *res = xtk_channel_flush(ch, diagnostic);
	if (!res) return false;
	xtk_batchresult_destroy(res);
	return true;
}
