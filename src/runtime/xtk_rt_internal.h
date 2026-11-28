#ifndef XTK_RUNTIME_INTERNAL_H
#define XTK_RUNTIME_INTERNAL_H

#include <xtk/xtk_reconcile.h>
#include <xtk/xtk_scene.h>

enum
{
	XTK_QUEUE_CAP   = 256,
	XTK_RETRY_CAP   = 4,
	XTK_REMOUNT_CAP = 32,
};

typedef struct XtkRtRegion {
	uint64_t         id;
	uint64_t         revision;
	uint32_t         flags;
	uint8_t          state;
	bool             dirty;
	struct XtkNode  *node;
	XtkRegionBuildFn build;
	void            *ctx;
} XtkRtRegion;

struct XtkRt {
	XtkScene           scene;
	XtkRtCfg           cfg;
	XentCtx           *ctx;
	XentNodeId         host_root;

	XtkUi             *ui;
	void              *model;
	XtkUpdateFn        update;
	XtkViewFn          view;

	struct XtkNode    *root;

	XtkMsg             queue [XTK_QUEUE_CAP];
	char              *queue_owned [XTK_QUEUE_CAP];
	uint32_t           q_head;
	uint32_t           q_count;

	uint32_t           dropped_total;
	uint32_t           dropped_since_ack;
	bool               sticky_overflow;

	bool               force;
	bool               regions_stale;
	uint32_t           remount_count;
	XtkCtrlId          remount [XTK_REMOUNT_CAP];
	bool               frame_pending;
	bool               in_frame;
	uint8_t            fail_retries;
	void const        *owner_thread;
	uint64_t           frame_sequence;
	uint32_t           committed_count;

	XtkRtRegion       *regions;
	uint32_t           region_cap;
	uint32_t           region_count;
	uint64_t          *dirty_regions;
	uint32_t           dirty_region_count;
	uint32_t           dirty_region_cap;

	struct XtkScratch *scratch;
	struct XtkScratch *plan_scratch;
	struct XtkArena   *patch_arena;
	XtkBatch          *batch;
};

struct XtkRtRegion *xtk_rt_region_find(struct XtkRt const *rt, uint64_t id);
struct XtkRtRegion *xtk_rt_region_reusable(struct XtkRt const *rt, uint64_t id);
bool                xtk_rt_remounting(struct XtkRt const *rt, XtkCtrlId type);
struct XtkNode     *xtk_rt_region_lookup(struct XtkRt const *rt, uint64_t id, uint64_t revision);
bool                xtk_rt_region_register(struct XtkRt *rt, struct XtkNode *node);
void                xtk_rt_region_remove(struct XtkRt *rt, struct XtkNode const *node);

#endif
