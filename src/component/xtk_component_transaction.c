#include "xtk_component_runtime_internal.h"

#include <string.h>

static bool copy_props_blob(XtkCompType const *type, void *dst, void const *src) {
	if (!type->props_size) return true;
	if (!src || !dst) return false;
	if (type->copy_props) {
		type->copy_props(NULL, dst, src);
		return true;
	}
	memcpy(dst, src, type->props_size);
	return true;
}

static void *dup_props(XtkCompType const *type, void const *src, uint32_t len) {
	if (type->props_size == 0u) return NULL;
	if (!src || len != ( uint32_t ) type->props_size) return NULL;
	void *dst = xtk_alloc(type->props_size);
	if (!dst) return NULL;
	if (!copy_props_blob(type, dst, src)) {
		xtk_alloc_free(dst);
		return NULL;
	}
	return dst;
}

static bool pending_grow(XtkCompRt *rt) {
	if (rt->pending_count < rt->pending_cap) return true;
	uint32_t     cap = rt->pending_cap ? rt->pending_cap * 2u : XTK_COMP_PEND_CAP;
	CompPending *n   = ( CompPending * ) xtk_alloc_resize(rt->pending, sizeof(*n) * cap);
	if (!n) return false;
	rt->pending     = n;
	rt->pending_cap = cap;
	return true;
}

static bool inst_grow(XtkCompRt *rt) {
	if (rt->inst_count < rt->inst_cap) return true;
	uint32_t     cap = rt->inst_cap ? rt->inst_cap * 2u : XTK_COMP_INST_CAP;
	XtkCompInst *n   = ( XtkCompInst * ) xtk_alloc_resize(rt->inst, sizeof(*n) * cap);
	if (!n) return false;
	rt->inst     = n;
	rt->inst_cap = cap;
	return true;
}

static void abort_one(CompPending *p) {
	if (p->prepare && p->type && p->type->ops.abort) p->type->ops.abort(p->prepare);
	p->prepare = NULL;
	xtk_alloc_free(p->props_next);
	p->props_next = NULL;
}

void xtk_comp_abort(XtkCompRt *rt) {
	if (!rt) return;
	for (uint32_t i = 0; i < rt->pending_count; i++) abort_one(&rt->pending [i]);
	rt->pending_count = 0u;
}

XtkCompErr xtk_comp_prepmount(
  XtkCompRt *rt, XtkHost *host, XentCtx *ctx, XtkCtrl control, XtkCtrl content_root, XtkCtrl impl_root,
  XtkCompType const *type, void const *props_bytes, uint32_t props_len
) {
	if (!rt || !host || !ctx || !type || control == XTK_CTRL_INVALID) return XTK_COMPONENT_ERR_FAILED;
	if (type->props_size && (!props_bytes || props_len != ( uint32_t ) type->props_size))
		return XTK_COMPONENT_ERR_INVALID_PROPS;
	if (!type->props_size && props_len != 0u) return XTK_COMPONENT_ERR_INVALID_PROPS;
	if (!pending_grow(rt)) return XTK_COMPONENT_ERR_OOM;

	void *props = dup_props(type, props_bytes, props_len);
	if (type->props_size && !props) return XTK_COMPONENT_ERR_OOM;

	XtkCompHost  ch   = xtk_comp_make_host(rt, host, ctx, control, content_root, impl_root);
	XtkCompPrep *prep = NULL;
	XtkCompErr   err  = type->ops.prepare_mount(&ch, control, props, &prep);
	if (err != XTK_COMPONENT_OK || !prep) {
		xtk_alloc_free(props);
		return err == XTK_COMPONENT_OK ? XTK_COMPONENT_ERR_FAILED : err;
	}

	rt->pending [rt->pending_count++] = (CompPending) {
	  .kind         = XTK_COMP_PENDING_MOUNT,
	  .control      = control,
	  .content_root = content_root,
	  .impl_root    = impl_root,
	  .type         = type,
	  .props_next   = props,
	  .props_size   = type->props_size,
	  .prepare      = prep,
	  .host         = host,
	  .ctx          = ctx,
	};
	return XTK_COMPONENT_OK;
}

XtkCompErr xtk_comp_prepupd(
  XtkCompRt *rt, XtkHost *host, XentCtx *ctx, XtkCtrl control, void const *props_bytes, uint32_t props_len
) {
	XtkCompInst *in = rt ? xtk_comp_find_instance(rt, control) : NULL;
	if (!in || !in->type || !in->type->ops.prepare_update) return XTK_COMPONENT_ERR_UNSUPPORTED;
	if (in->type->props_size && (!props_bytes || props_len != ( uint32_t ) in->type->props_size))
		return XTK_COMPONENT_ERR_INVALID_PROPS;
	if (!pending_grow(rt)) return XTK_COMPONENT_ERR_OOM;

	void *props = dup_props(in->type, props_bytes, props_len);
	if (in->type->props_size && !props) return XTK_COMPONENT_ERR_OOM;

	XtkCompHost  ch   = xtk_comp_make_host(rt, host, ctx, control, in->content_root, in->impl_root);
	XtkCompPrep *prep = NULL;
	XtkCompErr   err  = in->type->ops.prepare_update(&ch, control, in->state, in->props, props, &prep);
	if (err != XTK_COMPONENT_OK || !prep) {
		xtk_alloc_free(props);
		return err == XTK_COMPONENT_OK ? XTK_COMPONENT_ERR_FAILED : err;
	}

	rt->pending [rt->pending_count++] = (CompPending) {
	  .kind         = XTK_COMP_PENDING_UPDATE,
	  .control      = control,
	  .content_root = in->content_root,
	  .impl_root    = in->impl_root,
	  .type         = in->type,
	  .props_next   = props,
	  .props_size   = in->type->props_size,
	  .prepare      = prep,
	  .host         = host,
	  .ctx          = ctx,
	};
	return XTK_COMPONENT_OK;
}

static bool commit_mount(XtkCompRt *rt, CompPending *p) {
	void *state                 = p->type->ops.commit_mount(p->prepare);
	p->prepare                  = NULL;
	rt->inst [rt->inst_count++] = (XtkCompInst) {
	  .control      = p->control,
	  .content_root = p->content_root,
	  .impl_root    = p->impl_root,
	  .type         = p->type,
	  .state        = state,
	  .props        = p->props_next,
	  .props_size   = p->props_size,
	  .live         = true,
	};
	p->props_next = NULL;
	return true;
}

static void commit_update(CompPending *p, XtkCompInst *in) {
	p->type->ops.commit_update(p->prepare);
	p->prepare = NULL;
	xtk_alloc_free(in->props);
	in->props      = p->props_next;
	in->props_size = p->props_size;
	p->props_next  = NULL;
}

static uint32_t pending_mount_count(XtkCompRt const *rt) {
	uint32_t count = 0u;
	for (uint32_t i = 0; i < rt->pending_count; i++) count += rt->pending [i].kind == XTK_COMP_PENDING_MOUNT;
	return count;
}

static bool reserve_instances(XtkCompRt *rt, uint32_t count) {
	while (rt->inst_count + count > rt->inst_cap)
		if (!inst_grow(rt)) return false;
	return true;
}

static bool commit_pending(XtkCompRt *rt, CompPending *p) {
	if (p->kind == XTK_COMP_PENDING_MOUNT) return commit_mount(rt, p);
	XtkCompInst *in = xtk_comp_find_instance(rt, p->control);
	if (!in) return false;
	commit_update(p, in);
	return true;
}

XtkCompErr xtk_comp_commit(XtkCompRt *rt) {
	if (!rt) return XTK_COMPONENT_OK;
	if (!reserve_instances(rt, pending_mount_count(rt))) {
		xtk_comp_abort(rt);
		return XTK_COMPONENT_ERR_OOM;
	}
	for (uint32_t i = 0; i < rt->pending_count; i++)
		if (!commit_pending(rt, &rt->pending [i])) {
			xtk_comp_abort(rt);
			return XTK_COMPONENT_ERR_FAILED;
		}
	rt->pending_count = 0u;
	return XTK_COMPONENT_OK;
}
