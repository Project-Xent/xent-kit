#include "xtk_batch_internal.h"
#include <xtk/xtk_batch.h>
#include <xtk/xtk_catalog.h>

#include <xtk/xtk_alloc.h>

#include <string.h>

typedef struct XtkLocalFact {
	XtkCtrlId type;
	bool      defined;
} XtkLocalFact;

typedef struct XtkPreflightCtx {
	XtkBatch     *batch;
	XtkLocalFact *locals;
} XtkPreflightCtx;

static bool ref_defined_at(XtkPreflightCtx const *ctx, XtkNodeRef ref, bool allow_none) {
	if (ref.kind == XTK_REF_NONE) return allow_none;
	if (ref.kind == XTK_REF_EXISTING) return ref.u.existing != XTK_CTRL_INVALID;
	if (ref.kind != XTK_REF_LOCAL) return false;
	return ref.u.local < ctx->batch->next_local && ctx->locals [ref.u.local].defined;
}

static XtkBatchError diagnose(XtkBatchDiag *diagnostic, XtkBatchError err, uint32_t op) {
	if (diagnostic) *diagnostic = (XtkBatchDiag) {.error = err, .failed_op = op};
	return err;
}

static XtkBatchError require_ref(XtkPreflightCtx const *ctx, XtkNodeRef ref, bool allow_none) {
	return ref_defined_at(ctx, ref, allow_none) ? XTK_BATCH_OK : XTK_BATCH_ERR_INVALID_LOCAL;
}

typedef XtkBatchError (*XtkPreflightFn)(XtkPreflightCtx *ctx, uint32_t i);

static XtkCtrlId      local_ref_type(XtkPreflightCtx const *ctx, XtkNodeRef ref) {
	if (ref.kind != XTK_REF_LOCAL) return XTK_CTRL_ID_INVALID;
	return ctx->locals [ref.u.local].type;
}

static bool control_id_supported(XtkCtrlId id) { return xtk_catalog_standard(id) || id >= XTK_CTRL_ID_COMPONENT_BASE; }

static bool create_properties_ok(XtkBatchCreate const *create) {
	if (!xtk_catalog_standard(create->type)) return true;
	for (uint32_t i = 0; i < create->prop_count; i++)
		if (!xtk_batch_stdprop_ok(create->type, &create->props [i])) return false;
	return true;
}

static XtkBatchError preflight_create(XtkPreflightCtx *ctx, uint32_t i) {
	XtkBatchCreate const *c = &ctx->batch->ops [i].u.create;
	if (!control_id_supported(c->type)) return XTK_BATCH_ERR_VALIDATION;
	if (require_ref(ctx, c->parent, true) != XTK_BATCH_OK) return XTK_BATCH_ERR_INVALID_LOCAL;
	if (require_ref(ctx, c->before, true) != XTK_BATCH_OK) return XTK_BATCH_ERR_INVALID_LOCAL;
	if (!create_properties_ok(c)) return XTK_BATCH_ERR_INVALID_PROPERTY;
	if (c->local >= ctx->batch->next_local || ctx->locals [c->local].defined) return XTK_BATCH_ERR_DUPLICATE_LOCAL;
	ctx->locals [c->local] = (XtkLocalFact) {.type = c->type, .defined = true};
	return XTK_BATCH_OK;
}

static XtkBatchError preflight_destroy(XtkPreflightCtx *ctx, uint32_t i) {
	return require_ref(ctx, ctx->batch->ops [i].u.destroy.target, false);
}

static XtkBatchError preflight_set_prop(XtkPreflightCtx *ctx, uint32_t i) {
	XtkBatchSetProp const *p = &ctx->batch->ops [i].u.set_prop;
	if (require_ref(ctx, p->target, false) != XTK_BATCH_OK) return XTK_BATCH_ERR_INVALID_LOCAL;
	if (p->patch.id == XTK_PROP_ID_INVALID || !xtk_batch_value_ok(&p->patch.value)) return XTK_BATCH_ERR_INVALID_VALUE;
	XtkCtrlId type = local_ref_type(ctx, p->target);
	if (xtk_catalog_standard(type) && !xtk_batch_stdprop_ok(type, &p->patch)) return XTK_BATCH_ERR_INVALID_PROPERTY;
	return XTK_BATCH_OK;
}

static XtkBatchError preflight_trio(XtkPreflightCtx *ctx, XtkNodeRef a, XtkNodeRef b, XtkNodeRef before) {
	if (require_ref(ctx, a, false) != XTK_BATCH_OK) return XTK_BATCH_ERR_INVALID_LOCAL;
	if (require_ref(ctx, b, false) != XTK_BATCH_OK) return XTK_BATCH_ERR_INVALID_LOCAL;
	return require_ref(ctx, before, true);
}

static XtkBatchError preflight_insert(XtkPreflightCtx *ctx, uint32_t i) {
	XtkBatchInsert const *op = &ctx->batch->ops [i].u.insert;
	return preflight_trio(ctx, op->parent, op->child, op->before);
}

static XtkBatchError preflight_move(XtkPreflightCtx *ctx, uint32_t i) {
	XtkBatchMove const *op = &ctx->batch->ops [i].u.move;
	return preflight_trio(ctx, op->parent, op->child, op->before);
}

static XtkBatchError preflight_reparent(XtkPreflightCtx *ctx, uint32_t i) {
	XtkBatchReparent const *op = &ctx->batch->ops [i].u.reparent;
	return preflight_trio(ctx, op->child, op->new_parent, op->before);
}

static XtkBatchError preflight_subscribe(XtkPreflightCtx *ctx, uint32_t i) {
	XtkBatchSubscribe const *op = &ctx->batch->ops [i].u.subscribe;
	if (require_ref(ctx, op->target, false) != XTK_BATCH_OK) return XTK_BATCH_ERR_INVALID_LOCAL;
	if (!op->fn || !xtk_batch_phases_ok(op->event, op->phases) || op->token >= ctx->batch->next_sub)
		return XTK_BATCH_ERR_VALIDATION;
	XtkCtrlId type = local_ref_type(ctx, op->target);
	if (xtk_catalog_standard(type) && !xtk_catalog_ctrlevent(type, op->event)) return XTK_BATCH_ERR_VALIDATION;
	return XTK_BATCH_OK;
}

static XtkBatchError preflight_unsubscribe(XtkPreflightCtx *ctx, uint32_t i) {
	return ctx->batch->ops [i].u.unsubscribe.id != XTK_SUBSCRIPTION_INVALID ? XTK_BATCH_OK : XTK_BATCH_ERR_VALIDATION;
}

static XtkBatchError preflight_op(XtkPreflightCtx *ctx, uint32_t i) {
	static XtkPreflightFn const table [] = {
	  [XTK_BATCH_OP_CREATE]      = preflight_create,
	  [XTK_BATCH_OP_DESTROY]     = preflight_destroy,
	  [XTK_BATCH_OP_SET_PROP]    = preflight_set_prop,
	  [XTK_BATCH_OP_INSERT]      = preflight_insert,
	  [XTK_BATCH_OP_MOVE]        = preflight_move,
	  [XTK_BATCH_OP_REPARENT]    = preflight_reparent,
	  [XTK_BATCH_OP_SUBSCRIBE]   = preflight_subscribe,
	  [XTK_BATCH_OP_UNSUBSCRIBE] = preflight_unsubscribe,
	};
	XtkBatchOpKind kind = ctx->batch->ops [i].kind;
	if (( unsigned ) kind >= ( unsigned ) (sizeof(table) / sizeof(table [0])) || !table [kind])
		return XTK_BATCH_ERR_VALIDATION;
	return table [kind](ctx, i);
}

XtkBatchError xtk_batch_preflight(XtkBatch *batch, XtkBatchDiag *diagnostic) {
	if (!batch) return diagnose(diagnostic, XTK_BATCH_ERR_VALIDATION, UINT32_MAX);
	diagnose(diagnostic, XTK_BATCH_OK, UINT32_MAX);

	XtkPreflightCtx ctx = {.batch = batch};
	if (batch->next_local) {
		ctx.locals = ( XtkLocalFact * ) xtk_alloc_zero(batch->next_local, sizeof(*ctx.locals));
		if (!ctx.locals) return diagnose(diagnostic, XTK_BATCH_ERR_OOM, UINT32_MAX);
	}

	for (uint32_t i = 0; i < batch->count; i++) {
		XtkBatchError err = preflight_op(&ctx, i);
		if (err != XTK_BATCH_OK) {
			xtk_alloc_free(ctx.locals);
			return diagnose(diagnostic, err, i);
		}
	}

	xtk_alloc_free(ctx.locals);
	batch->sealed = true;
	return XTK_BATCH_OK;
}
