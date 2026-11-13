#include <xtk/xtk_reconcile.h>
#include <xtk/xtk_alloc.h>

#include "xtk_rt_internal.h"
#include "../reconcile/xtk_reconcile_internal.h"
#include "../reconcile/xtk_scratch.h"
#include "batch/xtk_batch_internal.h"
#include "xtk_internal.h"
#include "../xtk_thread_internal.h"

#include <stdint.h>
#include <string.h>

static bool scratch_create(XtkScratch **out) {
	XtkScratch *scratch = ( XtkScratch * ) xtk_alloc_zero(1, sizeof(*scratch));
	if (!scratch) return false;
	if (!xtk_scratch_init(scratch, 64u * 1024u)) {
		xtk_alloc_free(scratch);
		return false;
	}
	*out = scratch;
	return true;
}

static void runtime_storage_dispose(XtkRt *rt) {
	if (!rt) return;
	xtk_batch_free(rt->batch_cache);
	xtk_scratch_dispose(rt->plan_scratch);
	xtk_alloc_free(rt->plan_scratch);
	xtk_scratch_dispose(rt->scratch);
	xtk_alloc_free(rt->scratch);
}

static bool runtime_storage_create(XtkRt *rt) {
	if (!scratch_create(&rt->scratch)) return false;
	if (!scratch_create(&rt->plan_scratch)) return false;
	rt->batch_cache = xtk_batch_alloc(0u);
	return rt->batch_cache != NULL;
}

static void request_frame(XtkRt *rt) {
	if (!rt || rt->frame_pending) return;
	rt->frame_pending = true;
	if (rt->cfg.request_frame) rt->cfg.request_frame(rt->cfg.ctx);
}

static void saturating_add(uint32_t *dst, uint32_t add) {
	if (*dst > UINT32_MAX - add) *dst = UINT32_MAX;
	else *dst += add;
}

static void note_drop(XtkRt *rt) {
	saturating_add(&rt->dropped_total, 1u);
	saturating_add(&rt->dropped_since_ack, 1u);
	rt->sticky_overflow = true;
	request_frame(rt);
}

static XtkPostStatus queue_post(XtkRt *rt, XtkMsg msg, char *owned) {
	if (!rt || msg.tag == 0) {
		xtk_alloc_free(owned);
		return XTK_POST_INVALID_MESSAGE;
	}
	if (rt->q_count >= XTK_QUEUE_CAP) {
		note_drop(rt);
		xtk_alloc_free(owned);
		return XTK_POST_FULL;
	}
	uint32_t slot          = (rt->q_head + rt->q_count) % XTK_QUEUE_CAP;
	rt->queue [slot]       = msg;
	rt->queue_owned [slot] = owned;
	rt->q_count++;
	request_frame(rt);
	return XTK_POST_ACCEPTED;
}

static bool   post_thread_ok(XtkRt const *rt) { return rt->owner_thread == xtk_thread_token(); }

XtkPostStatus xtk_rt_post(XtkRt *rt, XtkMsg msg) {
	if (rt && !post_thread_ok(rt)) return XTK_POST_WRONG_THREAD;
	return queue_post(rt, msg, NULL);
}

XtkPostStatus xtk_rt_poststring(XtkRt *rt, XtkMsg msg, char const *data, uint32_t len) {
	if (rt && !post_thread_ok(rt)) return XTK_POST_WRONG_THREAD;
	if (!rt || msg.tag == 0 || (len > 0u && !data)) return XTK_POST_INVALID_MESSAGE;
	if (rt->q_count >= XTK_QUEUE_CAP) {
		note_drop(rt);
		return XTK_POST_FULL;
	}
	if (( size_t ) len == SIZE_MAX) {
		note_drop(rt);
		return XTK_POST_OOM;
	}
	char *copy = ( char * ) xtk_alloc(( size_t ) len + 1u);
	if (!copy) {
		note_drop(rt);
		return XTK_POST_OOM;
	}
	if (len > 0u) memcpy(copy, data, len);
	copy [len] = '\0';
	msg.ptr    = copy;
	return queue_post(rt, msg, copy);
}

XtkOverflowStatus xtk_rt_overflow(XtkRt const *rt) {
	if (!rt) return (XtkOverflowStatus) {0};
	return (XtkOverflowStatus) {
	  .sticky            = rt->sticky_overflow,
	  .dropped_since_ack = rt->dropped_since_ack,
	  .dropped_total     = rt->dropped_total,
	};
}

void xtk_rt_ackoverflow(XtkRt *rt) {
	if (!rt) return;
	rt->sticky_overflow   = false;
	rt->dropped_since_ack = 0;
}

XtkNode const *xtk_rt_root(XtkRt const *rt) { return rt ? rt->root : NULL; }

XtkNode const *xtk_node_child(XtkNode const *node, int index) {
	if (!node || index < 0 || index >= node->child_count) return NULL;
	return node->children [index];
}

int        xtk_node_nchild(XtkNode const *node) { return node ? node->child_count : 0; }

XentNodeId xtk_node_id(XtkNode const *node) { return node ? node->node : XENT_NODE_INVALID; }

void       xtk_rt_invalidate(XtkRt *rt) {
	if (!rt) return;
	rt->force = true;
	request_frame(rt);
}

static void notify(XtkRt *rt, XtkFrameResult const *result) {
	if (rt->cfg.on_diagnostic) rt->cfg.on_diagnostic(rt->cfg.ctx, result);
}

static void drain_messages(XtkRt *rt, XtkFrameResult *result, uint32_t count) {
	for (uint32_t i = 0; i < count; i++) {
		uint32_t slot          = rt->q_head;
		XtkMsg   msg           = rt->queue [slot];
		char    *owned         = rt->queue_owned [slot];
		rt->queue_owned [slot] = NULL;
		rt->q_head             = (rt->q_head + 1u) % XTK_QUEUE_CAP;
		rt->q_count--;
		rt->update(rt->model, msg);
		xtk_alloc_free(owned);
		result->messages_drained++;
	}
}

static XtkFrameResult clean_frame(XtkRt *rt, XtkFrameResult result) {
	result.status         = XTK_FRAME_CLEAN;
	result.revision_after = result.revision_before;
	result.pending        = rt->q_count > 0 || rt->force;
	rt->in_frame          = false;
	if (result.pending) request_frame(rt);
	return result;
}

static void finish_frame(XtkRt *rt, XtkFrameResult *result, XtkFrameStatus status) {
	result->status         = status;
	result->revision_after = rt->host->vt->revision(rt->host);
	result->pending        = rt->q_count > 0 || rt->force || rt->frame_pending;
	if (status != XTK_FRAME_COMMITTED && status != XTK_FRAME_CLEAN) {
		rt->force         = true;
		rt->frame_pending = true;
		result->pending   = true;
		notify(rt, result);
	}
	rt->in_frame = false;
	if (result->pending) request_frame(rt);
}

XtkFrameResult xtk_rt_frame(XtkRt *rt) {
	XtkFrameResult result = {0};
	if (!rt) {
		result.status = XTK_FRAME_BUILD_FAILED;
		return result;
	}
	if (rt->in_frame) {
		result.status     = XTK_FRAME_DEFERRED;
		result.pending    = true;
		rt->frame_pending = true;
		return result;
	}
	rt->in_frame             = true;
	rt->frame_pending        = false;

	result.revision_before   = rt->host->vt->revision(rt->host);
	result.dropped_since_ack = rt->dropped_since_ack;
	result.dropped_total     = rt->dropped_total;

	uint32_t snapshot        = rt->q_count;
	bool     dirty           = snapshot > 0 || !rt->root || rt->force;
	rt->force                = false;
	drain_messages(rt, &result, snapshot);
	if (!dirty) return clean_frame(rt, result);

	xtk_ui_begin(rt->ui);
	if (!xtk_ui_prepare_regions(rt->ui, rt->root)) xtk_ui_fail(rt->ui);
	rt->frame_sequence++;
	XtkEl *view                = rt->view(rt->ui, rt->model);
	result.metrics.nodes_built = rt->ui->composition.element_count;
	XtkBatchDiag   diag        = {0};
	XtkFrameStatus st          = xtk_reconcile_run(rt, view, &diag, &result.identity, &result.metrics);
	result.metrics.nodes_built = rt->ui->composition.element_count;
	result.diagnostic          = diag;
	finish_frame(rt, &result, st);
	return result;
}

XtkRt *xtk_rt_create(
  XtkHost *host, XtkRtCfg const *cfg, XentNodeId host_root, void *model, XtkUpdateFn update, XtkViewFn view
) {
	if (!host || !cfg || host_root == XENT_NODE_INVALID || !update || !view) return NULL;

	XtkRt *rt = ( XtkRt * ) xtk_alloc_zero(1, sizeof(*rt));
	if (!rt) return NULL;

	rt->ui = xtk_ui_create();
	if (!rt->ui) {
		xtk_alloc_free(rt);
		return NULL;
	}

	if (!runtime_storage_create(rt)) {
		runtime_storage_dispose(rt);
		xtk_ui_destroy(rt->ui);
		xtk_alloc_free(rt);
		return NULL;
	}

	rt->host         = host;
	rt->cfg          = *cfg;
	rt->host_root    = host_root;
	rt->model        = model;
	rt->update       = update;
	rt->view         = view;
	rt->force        = true;
	rt->owner_thread = xtk_thread_token();
	return rt;
}

bool xtk_rt_destroy(XtkRt *rt) {
	if (!rt) return true;
	if (!xtk_unmount_all(rt)) return false;
	for (uint32_t i = 0; i < XTK_QUEUE_CAP; i++) xtk_alloc_free(rt->queue_owned [i]);
	runtime_storage_dispose(rt);
	xtk_ui_destroy(rt->ui);
	xtk_alloc_free(rt);
	return true;
}
