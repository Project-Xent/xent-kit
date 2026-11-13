#ifndef XTK_RUNTIME_INTERNAL_H
#define XTK_RUNTIME_INTERNAL_H

#include <xtk/xtk_reconcile.h>

#define XTK_QUEUE_CAP 256

struct XtkRt {
	XtkHost           *host;
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
	bool               frame_pending;
	bool               in_frame;
	void const        *owner_thread;
	uint64_t           frame_sequence;

	struct XtkScratch *scratch;
	struct XtkScratch *plan_scratch;
	XtkBatch          *batch_cache;
};

#endif
