#include "xtk_component_runtime_internal.h"

void xtk_comp_unmount(XtkCompRt *rt, XtkHost *host, XentCtx *ctx, XtkCtrl control) {
	XtkCompInst *in = rt ? xtk_comp_find_instance(rt, control) : NULL;
	if (!in) return;
	XtkCompHost ch = xtk_comp_make_host(rt, host, ctx, control, in->content_root, in->impl_root);
	if (in->type && in->type->ops.unmount) in->type->ops.unmount(&ch, control, in->state);
	xtk_comp_free_instance(in);
}

void xtk_comp_dropinst(XtkCompRt *rt, XtkCtrl control) {
	XtkCompInst *in = rt ? xtk_comp_find_instance(rt, control) : NULL;
	if (in) xtk_comp_free_instance(in);
}

uint32_t xtk_comp_dispatch(XtkCompRt *rt, XtkHost *host, XentCtx *ctx, XtkCtrl target, XtkEvent const *event) {
	if (!rt || !event || target == XTK_CTRL_INVALID) return XTK_EVENT_CONTINUE;
	XtkCompInst *in = xtk_comp_find_instance(rt, target);
	if (!in && event->target != XTK_CTRL_INVALID) {
		/* Walk up: event may target a node under content/impl root. */
		XentNodeId n = ( XentNodeId ) target;
		while (n != XENT_NODE_INVALID && !in) {
			in = xtk_comp_find_instance(rt, ( XtkCtrl ) n);
			n  = xent_node_parent(ctx, n);
		}
	}
	if (!in || !in->type || !in->type->ops.event) return XTK_EVENT_CONTINUE;
	XtkCompHost ch = xtk_comp_make_host(rt, host, ctx, in->control, in->content_root, in->impl_root);
	return in->type->ops.event(&ch, target, in->state, event);
}
