#include "xtk_retained_internal.h"

static bool value_ok(XtkValue const *v) {
	if (!v || v->kind == XTK_VALUE_NONE || v->kind > XTK_VALUE_BYTES) return false;
	if (v->kind == XTK_VALUE_STRING) return v->u.string.len == 0u || v->u.string.data != NULL;
	if (v->kind == XTK_VALUE_BYTES) return v->u.bytes.len == 0u || v->u.bytes.data != NULL;
	return true;
}

static XtkPropertyKind value_property_kind(XtkValueKind kind) {
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

static bool standard_property_ok(XtkCtrlId control, XtkPropPatch const *patch) {
	XtkPropDesc const *property = xtk_catalog_ctrlprop(control, patch->id);
	return property && property->kind == value_property_kind(patch->value.kind);
}

static bool event_phases_ok(XtkEventId event, uint32_t phases) {
	if (!xtk_event_phasesvalid(phases)) return false;
	XtkEventDesc const *descriptor = xtk_catalog_event(event);
	if (!descriptor) return true;
	uint32_t allowed = XTK_EVENT_PHASE_MASK_TARGET;
	if (descriptor->routing == XTK_EVENT_ROUTE_BUBBLE) allowed |= XTK_EVENT_PHASE_MASK_BUBBLE;
	if (descriptor->routing == XTK_EVENT_ROUTE_CAPTURE_BUBBLE) allowed = XTK_EVENT_PHASE_MASK_ALL;
	return (phases & ~allowed) == 0u;
}

typedef struct PreflightCtx {
	Retained *R;
	XtkBatch *batch;

	struct LocalFact {
		XtkCtrlId type;
		bool      defined;
		bool      destroyed;
	}       *locals;

	XtkCtrl *destroyed;
	uint32_t destroyed_count;
	uint32_t destroyed_cap;
} PreflightCtx;

static bool pf_destroyed(PreflightCtx const *ctx, XtkCtrl control) {
	for (uint32_t i = 0; i < ctx->destroyed_count; i++)
		if (ctx->destroyed [i] == control) return true;
	return false;
}

static bool pf_mark_destroyed(PreflightCtx *ctx, XtkCtrl control) {
	if (control == XTK_CTRL_INVALID || pf_destroyed(ctx, control)) return true;
	if (ctx->destroyed_count == ctx->destroyed_cap) {
		uint32_t cap = ctx->destroyed_cap ? ctx->destroyed_cap * 2u : 8u;
		XtkCtrl *n   = ( XtkCtrl * ) xtk_alloc_resize(ctx->destroyed, sizeof(*n) * cap);
		if (!n) return false;
		ctx->destroyed     = n;
		ctx->destroyed_cap = cap;
	}
	ctx->destroyed [ctx->destroyed_count++] = control;
	return true;
}

static XtkCtrlId pf_ref_type(PreflightCtx const *ctx, XtkNodeRef ref) {
	if (ref.kind == XTK_REF_EXISTING) return retained_types_get(ctx->R, retained_as_node(ref.u.existing));
	if (ref.kind == XTK_REF_LOCAL) return ctx->locals [ref.u.local].type;
	return XTK_CTRL_ID_INVALID;
}

static XtkBatchError pf_ref(PreflightCtx *ctx, XtkNodeRef ref, bool allow_none) {
	if (ref.kind == XTK_REF_NONE) return allow_none ? XTK_BATCH_OK : XTK_BATCH_ERR_INVALID_LOCAL;
	if (ref.kind == XTK_REF_EXISTING) {
		if (ref.u.existing == XTK_CTRL_INVALID
		    || !retained_host_live(ctx->R, ref.u.existing)
		    || pf_destroyed(ctx, ref.u.existing))
			return XTK_BATCH_ERR_INVALID_HANDLE;
		return XTK_BATCH_OK;
	}
	if (ref.kind != XTK_REF_LOCAL) return XTK_BATCH_ERR_INVALID_LOCAL;
	if (ref.u.local >= ctx->batch->next_local
	    || !ctx->locals [ref.u.local].defined
	    || ctx->locals [ref.u.local].destroyed)
		return XTK_BATCH_ERR_INVALID_LOCAL;
	return XTK_BATCH_OK;
}

static XtkBatchError pf_refs(PreflightCtx *ctx, XtkNodeRef a, XtkNodeRef b, XtkNodeRef before) {
	XtkBatchError err = pf_ref(ctx, a, false);
	if (err != XTK_BATCH_OK) return err;
	err = pf_ref(ctx, b, false);
	if (err != XTK_BATCH_OK) return err;
	return pf_ref(ctx, before, true);
}

static bool prop_id_in_control(XtkCtrlDesc const *desc, XtkPropertyId id) {
	if (!desc || !desc->properties) return false;
	for (uint32_t i = 0; i < desc->property_count; i++)
		if (desc->properties [i] == id) return true;
	return false;
}

static XtkBatchError pf_component_patch(XtkCompType const *type, XtkPropPatch const *patch) {
	if (!value_ok(&patch->value) || !xtk_changestamp_valid(patch->change)) return XTK_BATCH_ERR_INVALID_VALUE;
	if (patch->id == XTK_PROP_COMPONENT_PROPS) {
		if (patch->value.kind != XTK_VALUE_BYTES) return XTK_BATCH_ERR_INVALID_VALUE;
		if (patch->value.u.bytes.len != ( uint32_t ) type->props_size) return XTK_BATCH_ERR_INVALID_VALUE;
		return XTK_BATCH_OK;
	}
	if (!prop_id_in_control(type->control, patch->id)) return XTK_BATCH_ERR_INVALID_PROPERTY;
	XtkPropDesc const *pd = xtk_catalog_property(patch->id);
	if (!pd || pd->kind != value_property_kind(patch->value.kind)) return XTK_BATCH_ERR_INVALID_PROPERTY;
	return XTK_BATCH_OK;
}

static XtkBatchError pf_create_type(PreflightCtx *ctx, XtkCtrlId id, XtkCompType const **out) {
	*out = NULL;
	if (xtk_catalog_standard(id)) return XTK_BATCH_OK;
	if (!xtk_ctrl_iscomp(id) || !ctx->R->comp) return XTK_BATCH_ERR_VALIDATION;
	*out = xtk_comp_lookup(ctx->R->comp, id);
	return *out ? XTK_BATCH_OK : XTK_BATCH_ERR_VALIDATION;
}

static XtkBatchError pf_create_patch(XtkBatchCreate const *op, XtkCompType const *ctype, XtkPropPatch const *patch) {
	if (ctype) return pf_component_patch(ctype, patch);
	if (!xtk_catalog_ctrlprop(op->type, patch->id)) return XTK_BATCH_ERR_INVALID_PROPERTY;
	if (!value_ok(&patch->value) || !xtk_changestamp_valid(patch->change)) return XTK_BATCH_ERR_INVALID_VALUE;
	return standard_property_ok(op->type, patch) ? XTK_BATCH_OK : XTK_BATCH_ERR_INVALID_PROPERTY;
}

static XtkBatchError pf_create_props(XtkBatchCreate const *op, XtkCompType const *ctype) {
	for (uint32_t i = 0; i < op->prop_count; i++) {
		XtkBatchError err = pf_create_patch(op, ctype, &op->props [i]);
		if (err != XTK_BATCH_OK) return err;
	}
	return XTK_BATCH_OK;
}

static XtkBatchError pf_create(PreflightCtx *ctx, uint32_t op_index) {
	XtkBatchCreate const *op    = &ctx->batch->ops [op_index].u.create;
	XtkCompType const    *ctype = NULL;
	XtkBatchError         err   = pf_create_type(ctx, op->type, &ctype);
	if (err != XTK_BATCH_OK) return err;
	err = pf_ref(ctx, op->parent, true);
	if (err != XTK_BATCH_OK) return err;
	err = pf_ref(ctx, op->before, true);
	if (err != XTK_BATCH_OK) return err;
	err = pf_create_props(op, ctype);
	if (err != XTK_BATCH_OK) return err;
	if (op->local >= ctx->batch->next_local || ctx->locals [op->local].defined) return XTK_BATCH_ERR_DUPLICATE_LOCAL;
	ctx->locals [op->local].type    = op->type;
	ctx->locals [op->local].defined = true;
	return XTK_BATCH_OK;
}

static XtkBatchError pf_set_prop(PreflightCtx *ctx, uint32_t op_index) {
	XtkBatchSetProp const *op  = &ctx->batch->ops [op_index].u.set_prop;
	XtkBatchError          err = pf_ref(ctx, op->target, false);
	if (err != XTK_BATCH_OK) return err;
	if (op->patch.id == XTK_PROP_ID_INVALID || !value_ok(&op->patch.value) || !xtk_changestamp_valid(op->patch.change))
		return XTK_BATCH_ERR_INVALID_VALUE;
	XtkCtrlId type = pf_ref_type(ctx, op->target);
	if (xtk_ctrl_iscomp(type)) {
		XtkCompType const *ctype = ctx->R->comp ? xtk_comp_lookup(ctx->R->comp, type) : NULL;
		if (!ctype) return XTK_BATCH_ERR_VALIDATION;
		return pf_component_patch(ctype, &op->patch);
	}
	if (!xtk_catalog_ctrlprop(type, op->patch.id)) return XTK_BATCH_ERR_INVALID_PROPERTY;
	if (xtk_catalog_standard(type) && !standard_property_ok(type, &op->patch)) return XTK_BATCH_ERR_INVALID_PROPERTY;
	return XTK_BATCH_OK;
}

static XtkBatchError pf_destroy(PreflightCtx *ctx, uint32_t op_index) {
	XtkNodeRef    target = ctx->batch->ops [op_index].u.destroy.target;
	XtkBatchError err    = pf_ref(ctx, target, false);
	if (err != XTK_BATCH_OK) return err;
	if (target.kind == XTK_REF_LOCAL) {
		ctx->locals [target.u.local].destroyed = true;
		return XTK_BATCH_OK;
	}
	return pf_mark_destroyed(ctx, target.u.existing) ? XTK_BATCH_OK : XTK_BATCH_ERR_OOM;
}

static XtkBatchError pf_subscribe(PreflightCtx *ctx, uint32_t op_index) {
	XtkBatchSubscribe const *op  = &ctx->batch->ops [op_index].u.subscribe;
	XtkBatchError            err = pf_ref(ctx, op->target, false);
	if (err != XTK_BATCH_OK) return err;
	if (!op->fn || !event_phases_ok(op->event, op->phases) || op->token >= ctx->batch->next_sub)
		return XTK_BATCH_ERR_VALIDATION;
	XtkCtrlId type = pf_ref_type(ctx, op->target);
	if (xtk_catalog_standard(type) && !xtk_catalog_ctrlevent(type, op->event)) return XTK_BATCH_ERR_VALIDATION;
	return XTK_BATCH_OK;
}

static XtkBatchError pf_unsubscribe(PreflightCtx *ctx, uint32_t op_index) {
	XtkSubId id = ctx->batch->ops [op_index].u.unsubscribe.id;
	for (uint32_t i = 0; i < ctx->R->sub_count; i++)
		if (ctx->R->subs [i].live && ctx->R->subs [i].id == id) return XTK_BATCH_OK;
	return XTK_BATCH_ERR_INVALID_HANDLE;
}

static XtkBatchError pf_insert(PreflightCtx *ctx, uint32_t op_index) {
	XtkBatchInsert const *op = &ctx->batch->ops [op_index].u.insert;
	return pf_refs(ctx, op->parent, op->child, op->before);
}

static XtkBatchError pf_move(PreflightCtx *ctx, uint32_t op_index) {
	XtkBatchMove const *op = &ctx->batch->ops [op_index].u.move;
	return pf_refs(ctx, op->parent, op->child, op->before);
}

static XtkBatchError pf_reparent(PreflightCtx *ctx, uint32_t op_index) {
	XtkBatchReparent const *op = &ctx->batch->ops [op_index].u.reparent;
	return pf_refs(ctx, op->new_parent, op->child, op->before);
}

static XtkBatchError pf_op(PreflightCtx *ctx, uint32_t op_index) {
	XtkBatchOpKind kind = ctx->batch->ops [op_index].kind;
	if (kind == XTK_BATCH_OP_CREATE) return pf_create(ctx, op_index);
	if (kind == XTK_BATCH_OP_DESTROY) return pf_destroy(ctx, op_index);
	if (kind == XTK_BATCH_OP_SET_PROP) return pf_set_prop(ctx, op_index);
	if (kind == XTK_BATCH_OP_INSERT) return pf_insert(ctx, op_index);
	if (kind == XTK_BATCH_OP_MOVE) return pf_move(ctx, op_index);
	if (kind == XTK_BATCH_OP_REPARENT) return pf_reparent(ctx, op_index);
	if (kind == XTK_BATCH_OP_SUBSCRIBE) return pf_subscribe(ctx, op_index);
	if (kind == XTK_BATCH_OP_UNSUBSCRIBE) return pf_unsubscribe(ctx, op_index);
	return XTK_BATCH_ERR_VALIDATION;
}

XtkBatchError retained_host_preflight(XtkHost *host, XtkBatch *batch, XtkBatchDiag *diagnostic) {
	Retained *R = retained_impl(host);
	if (!R || !batch) return retained_diag(diagnostic, XTK_BATCH_ERR_VALIDATION, UINT32_MAX);
	if (batch->revision != R->revision) return retained_diag(diagnostic, XTK_BATCH_ERR_STALE_REVISION, UINT32_MAX);

	XtkBatchError structural = xtk_batch_preflight(batch, diagnostic);
	if (structural != XTK_BATCH_OK) return structural;

	PreflightCtx ctx = {.R = R, .batch = batch};
	if (batch->next_local) {
		ctx.locals = xtk_alloc_zero(batch->next_local, sizeof(*ctx.locals));
		if (!ctx.locals) return retained_diag(diagnostic, XTK_BATCH_ERR_OOM, UINT32_MAX);
	}

	for (uint32_t i = 0; i < batch->count; i++) {
		XtkBatchError err = pf_op(&ctx, i);
		if (err != XTK_BATCH_OK) {
			xtk_alloc_free(ctx.locals);
			xtk_alloc_free(ctx.destroyed);
			return retained_diag(diagnostic, err, i);
		}
	}

	xtk_alloc_free(ctx.locals);
	xtk_alloc_free(ctx.destroyed);
	return retained_diag(diagnostic, XTK_BATCH_OK, UINT32_MAX);
}

XtkBatchError
retained_host_prepare(XtkHost *host, XtkBatch *batch, XtkPrepare **out_prepare, XtkBatchDiag *diagnostic) {
	*out_prepare      = NULL;
	XtkBatchError err = retained_host_preflight(host, batch, diagnostic);
	if (err != XTK_BATCH_OK) return err;

	Retained *R = retained_impl(host);
	Prepare  *P = ( Prepare * ) xtk_alloc_zero(1, sizeof(Prepare));
	if (!P) return retained_diag(diagnostic, XTK_BATCH_ERR_OOM, UINT32_MAX);
	P->R            = R;
	P->batch        = batch;
	P->local_count  = batch->next_local;
	P->sub_id_count = batch->next_sub;
	if (P->local_count) {
		P->locals = ( XtkCtrl * ) xtk_alloc_zero(P->local_count, sizeof(XtkCtrl));
		if (!P->locals) {
			retained_prepare_free(P);
			return retained_diag(diagnostic, XTK_BATCH_ERR_OOM, UINT32_MAX);
		}
	}
	if (P->sub_id_count) {
		P->sub_ids = ( XtkSubId * ) xtk_alloc_zero(P->sub_id_count, sizeof(XtkSubId));
		if (!P->sub_ids) {
			retained_prepare_free(P);
			return retained_diag(diagnostic, XTK_BATCH_ERR_OOM, UINT32_MAX);
		}
	}
	if (R->comp) xtk_comp_lockproviders(R->comp);
	*out_prepare = ( XtkPrepare * ) P;
	return retained_diag(diagnostic, XTK_BATCH_OK, UINT32_MAX);
}
