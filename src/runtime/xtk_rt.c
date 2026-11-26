#include <xtk/xtk_reconcile.h>
#include <xtk/xtk_alloc.h>

#include "xtk_rt_internal.h"
#include "../reconcile/xtk_reconcile_internal.h"
#include "../reconcile/xtk_scratch.h"
#include "xtk_hash.h"
#include "xtk_internal.h"
#include "../xtk_thread_internal.h"

#include <stdint.h>
#include <string.h>

enum
{
	REGION_EMPTY     = 0,
	REGION_OCCUPIED  = 1,
	REGION_TOMBSTONE = 2,
};

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
	xtk_batch_free(rt->batch);
	if (rt->patch_arena) {
		xtk_arena_dispose(rt->patch_arena);
		xtk_alloc_free(rt->patch_arena);
	}
	xtk_alloc_free(rt->dirty_regions);
	xtk_alloc_free(rt->regions);
	xtk_scratch_dispose(rt->plan_scratch);
	xtk_alloc_free(rt->plan_scratch);
	xtk_scratch_dispose(rt->scratch);
	xtk_alloc_free(rt->scratch);
}

static bool runtime_storage_create(XtkRt *rt) {
	if (!scratch_create(&rt->scratch)) return false;
	if (!scratch_create(&rt->plan_scratch)) return false;
	rt->batch = xtk_batch_alloc(0u);
	return rt->batch != NULL;
}

static bool region_rehash(XtkRt *rt, uint32_t new_cap) {
	if (( size_t ) new_cap > SIZE_MAX / sizeof(XtkRtRegion)) return false;
	XtkRtRegion *slots = ( XtkRtRegion * ) xtk_alloc_zero(new_cap, sizeof(XtkRtRegion));
	if (!slots) return false;
	uint32_t mask = new_cap - 1u;
	uint32_t live = 0u;
	for (uint32_t i = 0; i < rt->region_cap; i++) {
		if (rt->regions [i].state != REGION_OCCUPIED) continue;
		uint32_t slot = ( uint32_t ) xtk_hash_u64(rt->regions [i].id) & mask;
		while (slots [slot].state == REGION_OCCUPIED) slot = (slot + 1u) & mask;
		slots [slot] = rt->regions [i];
		live++;
	}
	xtk_alloc_free(rt->regions);
	rt->regions      = slots;
	rt->region_cap   = new_cap;
	rt->region_count = live;
	return true;
}

XtkRtRegion *xtk_rt_region_find(XtkRt const *rt, uint64_t id) {
	if (!rt || !id || !rt->region_cap) return NULL;
	uint32_t mask = rt->region_cap - 1u;
	uint32_t slot = ( uint32_t ) xtk_hash_u64(id) & mask;
	for (uint32_t probe = 0; probe < rt->region_cap; probe++) {
		XtkRtRegion *e = &rt->regions [slot];
		if (e->state == REGION_EMPTY) return NULL;
		if (e->state == REGION_OCCUPIED && e->id == id) return e;
		slot = (slot + 1u) & mask;
	}
	return NULL;
}

XtkNode *xtk_rt_region_lookup(XtkRt const *rt, uint64_t id, uint64_t revision) {
	XtkRtRegion const *e = xtk_rt_region_find(rt, id);
	if (!e) return NULL;
	return e->revision == revision ? e->node : NULL;
}

static bool region_ensure_cap(XtkRt *rt) {
	if (rt->region_cap && (rt->region_count + 1u) * 10u < rt->region_cap * 7u) return true;
	uint32_t next_cap = rt->region_cap ? rt->region_cap * 2u : 16u;
	return next_cap >= rt->region_cap && region_rehash(rt, next_cap);
}

static void region_write_entry(XtkRtRegion *dst, XtkNode *node) {
	*dst = (XtkRtRegion) {
	  .id       = node->region_id,
	  .revision = node->region_revision,
	  .flags    = node->region_flags,
	  .state    = REGION_OCCUPIED,
	  .dirty    = false,
	  .node     = node,
	  .build    = node->region_build,
	  .ctx      = node->region_ctx,
	};
}

static XtkRtRegion *region_find_insert(XtkRt *rt, uint64_t id, bool *is_new) {
	uint32_t     mask  = rt->region_cap - 1u;
	uint32_t     slot  = ( uint32_t ) xtk_hash_u64(id) & mask;
	XtkRtRegion *avail = NULL;
	for (uint32_t probe = 0; probe < rt->region_cap; probe++) {
		XtkRtRegion *e = &rt->regions [slot];
		if (e->state == REGION_OCCUPIED && e->id == id) {
			*is_new = false;
			return e;
		}
		if (e->state == REGION_TOMBSTONE && !avail) avail = e;
		if (e->state == REGION_EMPTY) {
			*is_new = true;
			return avail ? avail : e;
		}
		slot = (slot + 1u) & mask;
	}
	return NULL;
}

bool xtk_rt_region_register(XtkRt *rt, XtkNode *node) {
	if (!rt || !node || !node->region_id) return true;
	if (!region_ensure_cap(rt)) return false;
	bool         is_new = false;
	XtkRtRegion *dst    = region_find_insert(rt, node->region_id, &is_new);
	if (!dst) return false;
	region_write_entry(dst, node);
	if (is_new) rt->region_count++;
	return true;
}

void xtk_rt_region_remove(XtkRt *rt, XtkNode const *node) {
	if (!rt || !node || !node->region_id) return;
	XtkRtRegion *e = xtk_rt_region_find(rt, node->region_id);
	if (!e || e->node != node) return;
	*e = (XtkRtRegion) {.state = REGION_TOMBSTONE};
	if (rt->region_count > 0u) rt->region_count--;
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
	rt->fail_retries = 0u;
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
	rt->fail_retries = 0u;
	rt->force        = true;
	request_frame(rt);
}

static bool dirty_regions_push(XtkRt *rt, uint64_t id) {
	if (rt->dirty_region_count == rt->dirty_region_cap) {
		uint32_t cap = rt->dirty_region_cap ? rt->dirty_region_cap * 2u : 8u;
		if (cap < rt->dirty_region_cap || ( size_t ) cap > SIZE_MAX / sizeof(uint64_t)) return false;
		uint64_t *next = ( uint64_t * ) xtk_alloc_resize(rt->dirty_regions, sizeof(*next) * cap);
		if (!next) return false;
		rt->dirty_regions    = next;
		rt->dirty_region_cap = cap;
	}
	rt->dirty_regions [rt->dirty_region_count++] = id;
	return true;
}

void xtk_rt_invalidate_region(XtkRt *rt, uint64_t id) {
	if (!rt || !id) return;
	XtkRtRegion *reg = xtk_rt_region_find(rt, id);
	if (!reg || !reg->node || !(reg->flags & XTK_REGION_SUB)) {
		xtk_rt_invalidate(rt);
		return;
	}
	rt->fail_retries = 0u;
	if (!reg->dirty) {
		if (!dirty_regions_push(rt, id)) {
			xtk_rt_invalidate(rt);
			return;
		}
		reg->dirty = true;
	}
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
	rt->fail_retries      = 0u;
	result.status         = XTK_FRAME_CLEAN;
	result.revision_after = result.revision_before;
	result.pending        = rt->q_count > 0 || rt->force || rt->dirty_region_count > 0;
	rt->in_frame          = false;
	if (result.pending) request_frame(rt);
	return result;
}

static void finish_frame(XtkRt *rt, XtkFrameResult *result, XtkFrameStatus status) {
	result->status         = status;
	result->revision_after = xtk_scene_revision(&rt->scene);
	if (status == XTK_FRAME_COMMITTED || status == XTK_FRAME_CLEAN) rt->fail_retries = 0u;
	else notify(rt, result);
	result->pending = rt->q_count > 0 || rt->force || rt->dirty_region_count > 0 || rt->frame_pending;
	rt->in_frame    = false;
	if (result->pending) request_frame(rt);
}

static XtkFrameStatus run_region_frame(XtkRt *rt, XtkFrameResult *result) {
	rt->frame_sequence++;
	XtkBatchDiag   diag = {0};
	XtkFrameStatus st   = xtk_reconcile_regions(
	  rt, rt->dirty_regions, rt->dirty_region_count, &diag, &result->identity, &result->metrics
	);
	result->metrics.nodes_built = rt->ui->composition.element_count;
	result->diagnostic          = diag;
	return st;
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
	result.revision_before   = xtk_scene_revision(&rt->scene);
	result.dropped_since_ack = rt->dropped_since_ack;
	result.dropped_total     = rt->dropped_total;

	uint32_t snapshot        = rt->q_count;
	bool     full_dirty      = snapshot > 0 || !rt->root || rt->force;
	bool     region_dirty    = !full_dirty && rt->dirty_region_count > 0u;
	rt->force                = false;
	drain_messages(rt, &result, snapshot);
	if (!full_dirty && !region_dirty) return clean_frame(rt, result);
	if (region_dirty) {
		XtkFrameStatus st = run_region_frame(rt, &result);
		finish_frame(rt, &result, st);
		return result;
	}

	xtk_ui_begin(rt->ui);
	rt->frame_sequence++;
	XtkEl *view                = rt->view(rt->ui, rt->model);
	result.metrics.nodes_built = rt->ui->composition.element_count;
	XtkBatchDiag   diag        = {0};
	XtkFrameStatus st          = xtk_reconcile_run(rt, view, &diag, &result.identity, &result.metrics);
	result.metrics.nodes_built = rt->ui->composition.element_count;
	result.diagnostic          = diag;
	if (st == XTK_FRAME_COMMITTED) rt->dirty_region_count = 0u;
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
	xtk_ui_attach_rt(rt->ui, rt);

	if (!runtime_storage_create(rt)) {
		runtime_storage_dispose(rt);
		xtk_ui_destroy(rt->ui);
		xtk_alloc_free(rt);
		return NULL;
	}

	rt->scene        = xtk_scene_fromhost(host);
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
