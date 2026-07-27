/**
 * @file xtk_reconcile.h
 * @brief Declarative runtime: one message drain, one view, one Host batch.
 */
#ifndef XTK_RECONCILE_H
#define XTK_RECONCILE_H

#include "xtk_host.h"
#include "xtk_batch.h"

#include <xtk/xtk.h>

typedef struct XtkNode XtkNode;
typedef struct XtkRt   XtkRt;

typedef enum XtkFrameStatus
{
	XTK_FRAME_CLEAN = 0,
	XTK_FRAME_COMMITTED,
	XTK_FRAME_BUILD_FAILED,
	XTK_FRAME_IDENTITY_FAILED,
	XTK_FRAME_PREFLIGHT_FAILED,
	XTK_FRAME_PREPARE_FAILED,
	XTK_FRAME_COMMIT_FAILED,
	XTK_FRAME_DEFERRED,
} XtkFrameStatus;

typedef enum XtkPostStatus
{
	XTK_POST_ACCEPTED = 0,
	XTK_POST_INVALID_MESSAGE,
	XTK_POST_FULL,
	XTK_POST_OOM,
} XtkPostStatus;

typedef enum XtkIdentityError
{
	XTK_IDENTITY_OK = 0,
	XTK_IDENTITY_MIXED,
	XTK_IDENTITY_DUPLICATE_KEY,
	XTK_IDENTITY_DUPLICATE_REGION,
	XTK_IDENTITY_INVALID_TYPE,
	XTK_IDENTITY_INVALID_COUNT,
	XTK_IDENTITY_MALFORMED,
	XTK_IDENTITY_OOM,
} XtkIdentityError;

#define XTK_IDENTITY_PATH_MAX 32
#define XTK_IDENTITY_KEY_MAX  64

typedef struct XtkIdentityDiag {
	XtkIdentityError error;
	XtkCtrlId        parent_type;
	int              child_a;
	int              child_b;
	uint32_t         path_depth;
	int              path [XTK_IDENTITY_PATH_MAX];
	bool             path_truncated;
	uint32_t         key_length;
	char             key [XTK_IDENTITY_KEY_MAX];
	bool             key_truncated;
	XtkKeyKind       key_kind;
	uint64_t         key_u64;
	uint64_t         region_id;
	uint64_t         frame_sequence;
} XtkIdentityDiag;

typedef struct XtkFrameMetrics {
	uint64_t nodes_built;
	uint64_t nodes_compared;
	uint64_t nodes_skipped;
	uint64_t property_patches;
	uint64_t mutations;
} XtkFrameMetrics;

typedef struct XtkFrameResult {
	XtkFrameStatus  status;
	uint32_t        messages_drained;
	uint32_t        dropped_since_ack;
	uint32_t        dropped_total;
	XtkBatchDiag    diagnostic;
	XtkIdentityDiag identity;
	XtkFrameMetrics metrics;
	uint64_t        revision_before;
	uint64_t        revision_after;
	bool            pending;
} XtkFrameResult;

typedef struct XtkOverflowStatus {
	bool     sticky;
	uint32_t dropped_since_ack;
	uint32_t dropped_total;
} XtkOverflowStatus;

typedef struct XtkViewport {
	float offset;
	float extent;
	float cross;
} XtkViewport;

typedef struct XtkVirtualRange {
	int first;
	int last;
	int lanes;
} XtkVirtualRange;

typedef struct XtkRtCfg {
	void *ctx;
	void  (*request_frame)(void *ctx);
	/* Optional. arg is the host sidecar attached as node ext; the node binding is kit-owned. */
	void  (*node_cleanup)(void *ctx, XentNodeId id, void *arg);
	/* General virtual-region seam. The runtime queries host geometry, then
	 * publishes the child window it materialized; neither callback is tied to
	 * a control type or item representation. */
	bool  (*viewport)(void *ctx, XentNodeId id, XtkViewport *out);
	void  (*virtual_range)(void *ctx, XentNodeId id, XtkVirtualRange const *range);
	void  (*on_diagnostic)(void *ctx, XtkFrameResult const *result); /* optional notify only */
} XtkRtCfg;

XtkRt *xtk_rt_create(
  XtkHost *host, XtkRtCfg const *cfg, XentNodeId host_root, void *model, XtkUpdateFn update, XtkViewFn view
);
/** Destroy after an atomic Host unmount; false leaves the runtime intact for retry. */
bool              xtk_rt_destroy(XtkRt *rt);
XtkFrameResult    xtk_rt_frame(XtkRt *rt);
XtkPostStatus     xtk_rt_post(XtkRt *rt, XtkMsg msg);
void              xtk_rt_invalidate(XtkRt *rt);

XtkOverflowStatus xtk_rt_overflow(XtkRt const *rt);
void              xtk_rt_ackoverflow(XtkRt *rt);

XtkNode const    *xtk_rt_root(XtkRt const *rt);
XtkNode const    *xtk_node_child(XtkNode const *node, int index);
int               xtk_node_nchild(XtkNode const *node);
XentNodeId        xtk_node_id(XtkNode const *node);

#endif
