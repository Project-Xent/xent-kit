#include "xtk_batch_internal.h"
#include <xtk/xtk_batch.h>
#include <xtk/xtk_catalog.h>

#include <xtk/xtk_alloc.h>

#include <string.h>

static _Thread_local XtkBatch *capture_batch;

static bool                    batch_reserve(XtkBatch *batch) {
	if (batch->count < batch->capacity) return true;
	if (batch == capture_batch) return false;
	uint32_t new_cap = batch->capacity ? batch->capacity * 2u : 16u;
	if (new_cap <= batch->capacity) return false;
	XtkBatchOp *n = ( XtkBatchOp * ) xtk_alloc_resize(batch->ops, sizeof(*n) * ( size_t ) new_cap);
	if (!n) return false;
	batch->ops      = n;
	batch->capacity = new_cap;
	return true;
}

static bool value_copy_string(XtkValue *dst, XtkValue const *src) {
	uint32_t len = src->u.string.len;
	char    *dup = ( char * ) xtk_alloc(( size_t ) len + 1u);
	if (!dup) {
		dst->kind          = XTK_VALUE_NONE;
		dst->u.string.data = NULL;
		dst->u.string.len  = 0u;
		return false;
	}
	if (len) memcpy(dup, src->u.string.data, ( size_t ) len);
	dup [len]          = '\0';
	dst->u.string.data = dup;
	dst->u.string.len  = len;
	return true;
}

static bool value_copy_bytes(XtkValue *dst, XtkValue const *src) {
	uint32_t len = src->u.bytes.len;
	if (len == 0u) {
		dst->u.bytes.data = NULL;
		dst->u.bytes.len  = 0u;
		return true;
	}
	uint8_t *dup = ( uint8_t * ) xtk_alloc(( size_t ) len);
	if (!dup) {
		dst->kind         = XTK_VALUE_NONE;
		dst->u.bytes.data = NULL;
		dst->u.bytes.len  = 0u;
		return false;
	}
	memcpy(dup, src->u.bytes.data, ( size_t ) len);
	dst->u.bytes.data = dup;
	dst->u.bytes.len  = len;
	return true;
}

static bool value_copy(XtkValue *dst, XtkValue const *src) {
	*dst = *src;
	if (src->kind == XTK_VALUE_STRING) return value_copy_string(dst, src);
	if (src->kind == XTK_VALUE_BYTES) return value_copy_bytes(dst, src);
	return true;
}

static void value_free(XtkValue *v) {
	if (!v) return;
	if (v->kind == XTK_VALUE_STRING) xtk_alloc_free(v->u.string.data);
	if (v->kind == XTK_VALUE_BYTES) xtk_alloc_free(v->u.bytes.data);
	v->kind = XTK_VALUE_NONE;
}

static void prop_array_free(XtkPropPatch *props, uint32_t count) {
	if (!props) return;
	for (uint32_t i = 0; i < count; i++) value_free(&props [i].value);
	xtk_alloc_free(props);
}

static void op_release(XtkBatchOp *op) {
	switch (op->kind) {
	case XTK_BATCH_OP_CREATE   : prop_array_free(op->u.create.props, op->u.create.prop_count); break;
	case XTK_BATCH_OP_SET_PROP : value_free(&op->u.set_prop.patch.value); break;
	default                    : break;
	}
}

static bool props_copy(XtkPropPatch const *src, uint32_t count, XtkPropPatch **out) {
	if (count == 0u) {
		*out = NULL;
		return true;
	}
	XtkPropPatch *dst = ( XtkPropPatch * ) xtk_alloc_zero(count, sizeof(*dst));
	if (!dst) return false;
	for (uint32_t i = 0; i < count; i++) {
		dst [i].id     = src [i].id;
		dst [i].change = src [i].change;
		if (!value_copy(&dst [i].value, &src [i].value)) {
			prop_array_free(dst, i);
			return false;
		}
	}
	*out = dst;
	return true;
}

XtkBatch *xtk_batch_alloc(uint64_t revision) {
	XtkBatch *batch = ( XtkBatch * ) xtk_alloc_zero(1, sizeof(*batch));
	if (!batch) return NULL;
	batch->revision = revision;
	return batch;
}

void xtk_batch_reset(XtkBatch *batch, uint64_t revision) {
	if (!batch) return;
	for (uint32_t i = 0; i < batch->count; i++) op_release(&batch->ops [i]);
	batch->count      = 0u;
	batch->next_local = 0u;
	batch->next_sub   = 0u;
	batch->revision   = revision;
	batch->sealed     = false;
}

bool xtk_batch_capture_begin(XtkBatch *batch, XtkBatchOp *ops, uint32_t capacity) {
	if (!batch || !ops || !capacity || capture_batch) return false;
	memset(batch, 0, sizeof(*batch));
	batch->ops      = ops;
	batch->capacity = capacity;
	capture_batch   = batch;
	return true;
}

void xtk_batch_capture_end(XtkBatch *batch) {
	if (capture_batch == batch) capture_batch = NULL;
}

void xtk_batch_free(XtkBatch *batch) {
	if (!batch) return;
	xtk_batch_reset(batch, 0u);
	xtk_alloc_free(batch->ops);
	xtk_alloc_free(batch);
}

XtkBatchResult *xtk_batchresult_create(uint32_t control_count, uint32_t subscription_count) {
	XtkBatchResult *result = ( XtkBatchResult * ) xtk_alloc_zero(1, sizeof(*result));
	if (!result) return NULL;
	if (control_count)
		result->controls = ( XtkControlMapping * ) xtk_alloc_zero(control_count, sizeof(*result->controls));
	if (subscription_count)
		result->subscriptions = ( XtkSubMapping * ) xtk_alloc_zero(subscription_count, sizeof(*result->subscriptions));
	if ((control_count && !result->controls) || (subscription_count && !result->subscriptions)) {
		xtk_batchresult_destroy(result);
		return NULL;
	}
	result->control_count      = control_count;
	result->subscription_count = subscription_count;
	return result;
}

void xtk_batchresult_destroy(XtkBatchResult *result) {
	if (!result) return;
	xtk_alloc_free(result->controls);
	xtk_alloc_free(result->subscriptions);
	xtk_alloc_free(result);
}

static XtkBatchOp *batch_push(XtkBatch *batch, XtkBatchOpKind kind) {
	if (!batch || batch->sealed || !batch_reserve(batch)) return NULL;
	XtkBatchOp *op = &batch->ops [batch->count++];
	memset(op, 0, sizeof(*op));
	op->kind = kind;
	return op;
}

XtkLocalId xtk_batch_create(
  XtkBatch *batch, XtkCtrlId type, XtkNodeRef parent, XtkNodeRef before, XtkPropPatch const *props, uint32_t prop_count
) {
	if (!batch || type == XTK_CTRL_ID_INVALID) return XTK_LOCAL_INVALID;
	if (!xtk_batch_props_ok(props, prop_count)) return XTK_LOCAL_INVALID;
	XtkBatchOp *op = batch_push(batch, XTK_BATCH_OP_CREATE);
	if (!op) return XTK_LOCAL_INVALID;
	XtkPropPatch *owned = NULL;
	if (!props_copy(props, prop_count, &owned)) {
		batch->count--;
		return XTK_LOCAL_INVALID;
	}
	XtkLocalId local        = batch->next_local++;
	op->u.create.type       = type;
	op->u.create.parent     = parent;
	op->u.create.before     = before;
	op->u.create.local      = local;
	op->u.create.props      = owned;
	op->u.create.prop_count = prop_count;
	return local;
}

bool xtk_batch_drop(XtkBatch *batch, XtkNodeRef target) {
	XtkBatchOp *op = batch_push(batch, XTK_BATCH_OP_DESTROY);
	if (!op) return false;
	op->u.destroy.target = target;
	return true;
}

static bool set_prop_value(XtkBatch *batch, XtkBatchOp *op, XtkValue const *value) {
	if (batch == capture_batch && value->kind != XTK_VALUE_BYTES) {
		op->u.set_prop.patch.value = *value;
		return true;
	}
	return value_copy(&op->u.set_prop.patch.value, value);
}

bool xtk_batch_set(XtkBatch *batch, XtkNodeRef target, XtkPropertyId id, XtkValue value, XtkChangeStamp change) {
	if (id == XTK_PROP_ID_INVALID || !xtk_batch_value_ok(&value) || !xtk_changestamp_valid(change)) return false;
	XtkBatchOp *op = batch_push(batch, XTK_BATCH_OP_SET_PROP);
	if (!op) return false;
	op->u.set_prop.target       = target;
	op->u.set_prop.patch.id     = id;
	op->u.set_prop.patch.change = change;
	if (!set_prop_value(batch, op, &value)) {
		batch->count--;
		return false;
	}
	return true;
}

bool xtk_batch_insert(XtkBatch *batch, XtkNodeRef parent, XtkNodeRef child, XtkNodeRef before) {
	XtkBatchOp *op = batch_push(batch, XTK_BATCH_OP_INSERT);
	if (!op) return false;
	op->u.insert.parent = parent;
	op->u.insert.child  = child;
	op->u.insert.before = before;
	return true;
}

bool xtk_batch_move(XtkBatch *batch, XtkNodeRef parent, XtkNodeRef child, XtkNodeRef before) {
	XtkBatchOp *op = batch_push(batch, XTK_BATCH_OP_MOVE);
	if (!op) return false;
	op->u.move.parent = parent;
	op->u.move.child  = child;
	op->u.move.before = before;
	return true;
}

bool xtk_batch_reparent(XtkBatch *batch, XtkNodeRef child, XtkNodeRef new_parent, XtkNodeRef before) {
	XtkBatchOp *op = batch_push(batch, XTK_BATCH_OP_REPARENT);
	if (!op) return false;
	op->u.reparent.child      = child;
	op->u.reparent.new_parent = new_parent;
	op->u.reparent.before     = before;
	return true;
}

XtkSubRef
xtk_batch_on(XtkBatch *batch, XtkNodeRef target, XtkEventId event, uint32_t phases, XtkEventFn fn, void *arg) {
	if (!fn || event == XTK_EVENT_ID_INVALID || !xtk_batch_phases_ok(event, phases)) return XTK_SUB_TOKEN_INVALID;
	XtkBatchOp *op = batch_push(batch, XTK_BATCH_OP_SUBSCRIBE);
	if (!op) return XTK_SUB_TOKEN_INVALID;
	XtkSubRef token        = batch->next_sub++;
	op->u.subscribe.target = target;
	op->u.subscribe.event  = event;
	op->u.subscribe.phases = phases;
	op->u.subscribe.fn     = fn;
	op->u.subscribe.arg    = arg;
	op->u.subscribe.token  = token;
	return token;
}

bool xtk_batch_off(XtkBatch *batch, XtkSubId id) {
	if (id == XTK_SUBSCRIPTION_INVALID) return false;
	XtkBatchOp *op = batch_push(batch, XTK_BATCH_OP_UNSUBSCRIBE);
	if (!op) return false;
	op->u.unsubscribe.id = id;
	return true;
}
