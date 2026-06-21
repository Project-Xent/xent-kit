/**
 * @file xtk_reconcile.h
 * @brief Platform-agnostic reconciler and runtime for XTK.
 *
 * XtkBackend is a vtable that each platform backend (fluxent, nexent, luxent)
 * implements. The reconciler diffs XtkEl trees against retained controls
 * through this interface — written once, used everywhere.
 */
#ifndef XTK_RECONCILE_H
#define XTK_RECONCILE_H

#include <xtk/xtk.h>

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct XtkNode {
	XentNodeId       node;
	XentNodeId       host;
	void            *binding;
	void            *ext;
	struct XtkNode **children;
	int              child_count;
	int              child_cap;
} XtkNode;

#define XTK_QUEUE_CAP 256

typedef struct XtkRuntime XtkRuntime;

typedef struct XtkBackend {
	void      *ctx;
	void      *(*binding_create)(void *ctx, XtkRuntime *rt);
	XentNodeId (*create)(void *ctx, XentNodeId parent, XtkEl const *el, void *binding);
	void       (*destroy)(void *ctx, XentNodeId id);
	void       (*pre_unmount)(void *ctx, XentNodeId id);
	void       (*mount_setup)(void *ctx, XtkNode *node, XentNodeId id, XtkEl const *el);
	void       (*apply_props)(void *ctx, XtkNode *node, XtkEl const *prev, XtkEl const *el);
	bool       (*is_interactive)(XtkEl const *el);
	void       (*request_frame)(void *ctx);
	void       (*node_cleanup)(XtkNode *node);
} XtkBackend;

struct XtkRuntime {
	XentContext *ctx;
	XtkBackend   backend;
	XentNodeId   host;

	XtkUi       *ui;
	void        *model;
	XtkUpdateFn  update;
	XtkViewFn    view;

	XtkEl       *prev_root;
	XtkNode     *root;

	XtkMsg       queue [XTK_QUEUE_CAP];
	int          q_head;
	int          q_tail;
};

XtkRuntime *xtk_runtime_create(
  XentContext *ctx, XtkBackend const *backend, XentNodeId host, void *model, XtkUpdateFn update, XtkViewFn view
);
void xtk_runtime_destroy(XtkRuntime *rt);
void xtk_runtime_frame(XtkRuntime *rt);
void xtk_runtime_post(XtkRuntime *rt, XtkMsg msg);

void xtk_reconcile(XtkRuntime *rt, XtkEl *next);
void xtk_unmount_all(XtkRuntime *rt);

#ifdef __cplusplus
}
#endif

#endif
