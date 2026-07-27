#ifndef XTK_RETAINED_INTERNAL_H
#define XTK_RETAINED_INTERNAL_H

#include <xtk/xtk_batch.h>
#include <xtk/xtk_catalog.h>

#include "xtk_retained.h"
#include <xtk/xtk_alloc.h>
#include <xtk/xtk_comp_rt.h>
#include "component/xtk_component_internal.h"

#include <string.h>
#include <xent/xent.h>

typedef struct PropEntry {
	XtkPropertyId  id;
	XtkValue       value;
	XtkChangeStamp change;
	bool           live;
} PropEntry;

typedef struct PropBucket {
	XtkCtrl    owner;
	PropEntry *entries;
	uint32_t   count;
	uint32_t   cap;
} PropBucket;

typedef struct SubEntry {
	XtkSubId   id;
	XtkCtrl    target;
	XtkEventId event;
	uint32_t   phases;
	XtkEventFn fn;
	void      *arg;
	bool       live;
} SubEntry;

typedef struct Retained {
	XtkHost     host;
	XentCtx    *ctx;
	XentNodeId  root;
	uint64_t    revision;
	XtkCtrlId  *types;
	uint32_t    types_cap;
	uint32_t   *invalidate;
	uint32_t    invalidate_cap;
	uint32_t    pending_invalidation;
	XtkCtrl     focus;
	PropBucket *prop_buckets;
	uint32_t    prop_bucket_cap;
	SubEntry   *subs;
	uint32_t    sub_count;
	uint32_t    sub_cap;
	uint64_t    next_sub;
	XtkCompRt  *comp;
} Retained;

typedef enum UndoKind
{
	UNDO_CREATE = 1,
	UNDO_PROP,
	UNDO_TOPO,
	UNDO_SUB,
} UndoKind;

typedef enum SubUndoKind
{
	SUB_UNDO_CANCEL_ADD = 0,
	SUB_UNDO_RESTORE,
} SubUndoKind;

typedef struct UndoTopo {
	XentNodeId child;
	XentNodeId old_parent;
	XentNodeId old_next;
} UndoTopo;

typedef struct UndoProp {
	XtkCtrl        control;
	XtkPropertyId  id;
	XtkValue       old_value;
	XtkChangeStamp old_change;
	bool           had_value;
} UndoProp;

typedef struct UndoSub {
	XtkSubId    id;
	SubUndoKind kind;
} UndoSub;

typedef struct Undo {
	UndoKind kind;

	union
	{
		XentNodeId created;
		UndoProp   prop;
		UndoTopo   topo;
		UndoSub    sub;
	} u;
} Undo;

typedef struct Prepare {
	Retained   *R;
	XtkBatch   *batch;
	XtkCtrl    *locals;
	uint32_t    local_count;
	Undo       *undos;
	uint32_t    undo_count;
	uint32_t    undo_cap;
	XentNodeId *deferred_destroy;
	uint32_t    destroy_count;
	uint32_t    destroy_cap;
	XtkSubId   *sub_ids;
	uint32_t    sub_id_count;
} Prepare;

static XentNodeId inline retained_as_node(XtkCtrl c) { return ( XentNodeId ) c; }

static XtkCtrl inline retained_as_control(XentNodeId n) { return ( XtkCtrl ) n; }

static Retained inline       *retained_impl(XtkHost *host) { return host ? ( Retained * ) host->impl : NULL; }

static Retained const inline *retained_impl_c(XtkHost const *host) {
	return host ? ( Retained const * ) host->impl : NULL;
}

static bool inline retained_host_live(Retained const *R, XtkCtrl control) {
	return control != XTK_CTRL_INVALID && xent_node_valid(R->ctx, retained_as_node(control));
}

/* --- props ---------------------------------------------------------------- */

void             retained_value_clear(XtkValue *v);
bool             retained_value_clone(XtkValue *dst, XtkValue const *src);
PropEntry       *retained_prop_find(Retained *R, XtkCtrl control, XtkPropertyId id);
PropEntry const *retained_prop_find_c(Retained const *R, XtkCtrl control, XtkPropertyId id);
PropEntry       *retained_prop_add(Retained *R, XtkCtrl control, XtkPropertyId id);
void             retained_clear_control_props(Retained *R, XtkCtrl control);
void             retained_props_dispose(Retained *R);
bool             retained_apply_prop(Prepare *P, XtkCtrl control, XtkPropPatch const *patch);
void             retained_rollback_prop(Retained *R, UndoProp *prop);
bool             retained_value_to_view(XtkValue const *v, XtkValueView *out);

/* --- events --------------------------------------------------------------- */

void             retained_clear_control_subs(Retained *R, XtkCtrl control);
bool             retained_apply_subscribe(Prepare *P, XtkBatchSubscribe const *op);
bool             retained_apply_unsubscribe(Prepare *P, XtkSubId id);
void             retained_rollback_sub(Retained *R, UndoSub const *sub);
uint32_t         retained_dispatch_at(Retained *R, XtkEvent *event);

/* --- txn / invalidation --------------------------------------------------- */

bool             retained_types_set(Retained *R, XentNodeId node, XtkCtrlId type);
XtkCtrlId        retained_types_get(Retained const *R, XentNodeId node);
void             retained_note_invalidate(Retained *R, XtkCtrl control, uint32_t mask);
void             retained_invalidate_prop(Retained *R, XtkCtrl control, XtkPropertyId id);
void             retained_invalidate_control_lifecycle(Retained *R, XtkCtrl control, bool create);
void             retained_purge_subtree_sidecar(Retained *R, XentNodeId root);

bool             retained_undo_push(Prepare *P, Undo u);
bool             retained_defer_destroy(Prepare *P, XentNodeId node);
bool             retained_resolve_ref(Prepare const *P, XtkNodeRef ref, bool *ok, XtkCtrl *out);
void             retained_rollback(Prepare *P);
void             retained_prepare_free(Prepare *P);

XtkBatchError    retained_host_preflight(XtkHost *host, XtkBatch *batch, XtkBatchDiag *diagnostic);
XtkBatchError retained_host_prepare(XtkHost *host, XtkBatch *batch, XtkPrepare **out_prepare, XtkBatchDiag *diagnostic);
XtkBatchResult    *retained_host_commit(XtkHost *host, XtkPrepare *prepare, XtkBatchDiag *diagnostic);
void               retained_host_abort(XtkHost *host, XtkPrepare *prepare);

bool               xtk_retained_register_component(XtkHost *host, XtkCompType const *type);
bool               xtk_retained_set_providers(XtkHost *host, XtkProviderDesc const *providers, uint32_t count);
XtkCtrl            xtk_retained_component_content_root(XtkHost const *host, XtkCtrl control);
XtkCtrl            xtk_retained_component_impl_root(XtkHost const *host, XtkCtrl control);

/* --- query ---------------------------------------------------------------- */

bool               retained_host_is_live(XtkHost const *host, XtkCtrl control);
uint64_t           retained_host_revision(XtkHost const *host);
XtkCtrl            retained_host_scene_root(XtkHost const *host);
XtkCtrlId          retained_host_control_type(XtkHost const *host, XtkCtrl control);
XtkCtrl            retained_host_parent(XtkHost const *host, XtkCtrl control);
XtkCtrl            retained_host_first_child(XtkHost const *host, XtkCtrl control);
XtkCtrl            retained_host_next_sibling(XtkHost const *host, XtkCtrl control);
XtkCtrlDesc const *retained_host_descriptor(XtkHost const *host, XtkCtrlId type);
bool               retained_host_get_property(
  XtkHost const *host, XtkCtrl control, XtkPropertyId property, XtkValueView *out_value, XtkChangeStamp *out_change
);
bool     retained_host_resource_is_valid(XtkHost const *host, XtkResource resource, XtkResourceTypeId type);
bool     retained_host_resource_retain(XtkHost *host, XtkResource resource, XtkResourceTypeId type);
void     retained_host_resource_release(XtkHost *host, XtkResource resource, XtkResourceTypeId type);
uint32_t retained_host_dispatch(XtkHost *host, XtkEvent const *event);

extern XtkHostVtable const retained_host_vtable;

XtkBatchError              retained_diag(XtkBatchDiag *diagnostic, XtkBatchError error, uint32_t op);

#endif
