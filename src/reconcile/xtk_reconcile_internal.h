#ifndef XTK_RECONCILE_INTERNAL_H
#define XTK_RECONCILE_INTERNAL_H

#include <xtk/xtk_reconcile.h>

#include "../runtime/xtk_rt_internal.h"
#include "../encode/xtk_encode.h"
#include "../encode/xtk_prop_state.h"
#include "xtk_plan.h"

typedef struct XtkNode {
	XentNodeId           node;
	XentNodeId           host;
	struct XtkNode      *parent;
	XtkBinding          *binding;
	struct XtkNode     **children;
	int                  child_count;
	int                  child_cap;
	XtkCtrlId            type_id;
	struct XtkPropState *props;
	XtkKey               key;
	uint64_t             region_id;
	uint64_t             region_revision;
	uint32_t             region_flags;
	XtkRegionBuildFn     region_build;
	void                *region_ctx;
	XtkSubId            *sub_ids;
	int                  sub_count;
	int                  sub_cap;
} XtkNode;

typedef struct XtkPlanRec XtkPlanRec;

typedef struct XtkStagedChild {
	XtkEl const *el;
	XtkPlanRec  *plan;
	int          old_index;
	bool         do_move;
} XtkStagedChild;

struct XtkPlanRec {
	XtkEl const    *el;
	XtkNode        *committed;
	XtkNode        *fresh;
	XtkBinding     *next_binding;
	XtkPropState   *next_props;
	XtkPropSlot    *patch_slots;
	uint32_t        patch_count;
	XtkModelVer     next_model_ver;
	XtkKey          next_key;
	XtkNodeRef      ref;
	XtkLocalId      local;
	XtkSubRef      *sub_tokens;
	int             sub_token_count;
	XtkStagedChild *children;
	int             child_count;
	bool            binding_changed;
	bool            key_changed;
	bool            children_changed;
	bool            subtree_dirty;
	bool            region_skip;
	bool            is_create;
	bool            retire;
	XtkPlanRec     *parent;
};

typedef struct XtkReconcileTxn {
	XtkRt           *rt;
	XtkBatch        *batch;
	XtkScratch      *scratch;
	XtkScratch      *plans;
	XtkPlanRec      *root_plan;
	XtkNode        **retire_nodes;
	int              retire_count;
	int              retire_cap;
	uint64_t        *seen_regions;
	uint32_t         seen_region_cap;
	int              walk_path [XTK_IDENTITY_PATH_MAX];
	bool             identity_failed;
	XtkFrameStatus   status;
	XtkBatchDiag     diagnostic;
	XtkIdentityDiag  identity;
	XtkFrameMetrics *metrics;
	XtkTxn           xtxn;
} XtkReconcileTxn;

XtkFrameStatus
xtk_reconcile_run(XtkRt *rt, XtkEl *next, XtkBatchDiag *diag, XtkIdentityDiag *identity, XtkFrameMetrics *metrics);
XtkFrameStatus xtk_reconcile_regions(
  XtkRt *rt, uint64_t const *ids, uint32_t count, XtkBatchDiag *diag, XtkIdentityDiag *identity,
  XtkFrameMetrics *metrics
);
bool xtk_unmount_all(XtkRt *rt);

bool xtk_normalize_tree(XtkRt *rt, XtkEl *next, XtkNode *committed);

bool xtk_plan_prepare(XtkReconcileTxn *txn, XtkEl const *next);
void xtk_plan_free(XtkPlanRec *plan);
void xtk_plan_abort_fresh(XtkPlanRec *plan);
bool xtk_plan_root(XtkReconcileTxn *txn, XtkEl *next, XtkPlanRec **root);
bool xtk_plan_subtree(
  XtkReconcileTxn *txn, XtkEl *next, XtkNode *committed, XtkNodeRef parent_ref, XtkNodeRef before, XtkPlanRec **root
);

bool xtk_node_reserve(XtkNode *n, int count);
bool xtk_node_reserve_subs(XtkNode *n, int sub_token_count);
void xtk_publication_verify_result(
  XtkPlanRec const *plan, XtkBatchResult const *result, uint32_t locals, uint32_t subs
);
XtkNode *xtk_publication_resolve(XtkRt *rt, XtkPlanRec *plan, XtkBatchResult const *result);
void     xtk_publication_retire(XtkRt *rt, XtkReconcileTxn *txn);

#endif
