/**
 * @file xtk_runtime.c
 * @brief XTK runtime: message queue, frame pump, and lifecycle.
 *
 * Platform-agnostic; the only platform call is backend.request_frame().
 */
#include <xtk/xtk_reconcile.h>

#include <stdlib.h>

void xtk_runtime_post(XtkRuntime *rt, XtkMsg msg) {
	if (!rt || msg.tag == 0) return;
	int next = (rt->q_tail + 1) % XTK_QUEUE_CAP;
	if (next == rt->q_head) return;
	rt->queue [rt->q_tail] = msg;
	rt->q_tail             = next;
	rt->backend.request_frame(rt->backend.ctx);
}

static bool xtk_runtime_take(XtkRuntime *rt, XtkMsg *out) {
	if (rt->q_head == rt->q_tail) return false;
	*out       = rt->queue [rt->q_head];
	rt->q_head = (rt->q_head + 1) % XTK_QUEUE_CAP;
	return true;
}

void xtk_runtime_invalidate(XtkRuntime *rt) {
	if (!rt) return;
	rt->force = true;
	rt->backend.request_frame(rt->backend.ctx);
}

void xtk_runtime_frame(XtkRuntime *rt) {
	bool   dirty = rt->q_head != rt->q_tail || !rt->root || rt->force;
	rt->force    = false;

	XtkMsg msg;
	while (xtk_runtime_take(rt, &msg)) rt->update(rt->model, msg);
	if (!dirty) return;

	xtk_ui_begin(rt->ui);
	xtk_reconcile(rt, rt->view(rt->ui, rt->model));
}

XtkRuntime *xtk_runtime_create(
  XentContext *ctx, XtkBackend const *backend, XentNodeId host, void *model, XtkUpdateFn update, XtkViewFn view
) {
	if (!ctx || !backend || host == XENT_NODE_INVALID || !update || !view) return NULL;

	XtkRuntime *rt = ( XtkRuntime * ) calloc(1, sizeof(*rt));
	if (!rt) return NULL;

	rt->ui = xtk_ui_create();
	if (!rt->ui) {
		free(rt);
		return NULL;
	}

	rt->ctx     = ctx;
	rt->backend = *backend;
	rt->host    = host;
	rt->model   = model;
	rt->update  = update;
	rt->view    = view;
	return rt;
}

void xtk_runtime_destroy(XtkRuntime *rt) {
	if (!rt) return;
	xtk_unmount_all(rt);
	xtk_ui_destroy(rt->ui);
	free(rt);
}
