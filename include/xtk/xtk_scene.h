#ifndef XTK_SCENE_H
#define XTK_SCENE_H

/* Application-facing scene / scoped batch / typed property surface over XtkHost. */

#include "xtk_batch.h"
#include "xtk_host.h"

typedef struct XtkTxn {
	XtkScene *scene;
	XtkBatch *batch;
} XtkTxn;

XtkScene        xtk_scene_from_host(XtkHost *host);
uint64_t        xtk_scene_revision(XtkScene const *scene);
XtkCtrl         xtk_scene_root(XtkScene const *scene);

bool            xtk_txn_begin(XtkScene *scene, XtkTxn *out);
XtkBatchResult *xtk_txn_commit(XtkTxn *txn, XtkBatchDiag *diagnostic);
void            xtk_txn_abort(XtkTxn *txn);
XtkBatch       *xtk_txn_batch(XtkTxn *txn);

XtkLocalId      xtk_txn_create(
  XtkTxn *txn, XtkCtrlId type, XtkNodeRef parent, XtkNodeRef before, XtkPropPatch const *props, uint32_t prop_count
);
bool      xtk_txn_drop(XtkTxn *txn, XtkNodeRef target);
bool      xtk_txn_set(XtkTxn *txn, XtkNodeRef target, XtkPropertyId id, XtkValue value, XtkChangeStamp change);
bool      xtk_txn_insert(XtkTxn *txn, XtkNodeRef parent, XtkNodeRef child, XtkNodeRef before);
bool      xtk_txn_move(XtkTxn *txn, XtkNodeRef parent, XtkNodeRef child, XtkNodeRef before);
bool      xtk_txn_reparent(XtkTxn *txn, XtkNodeRef child, XtkNodeRef new_parent, XtkNodeRef before);
XtkSubRef xtk_txn_on(XtkTxn *txn, XtkNodeRef target, XtkEventId event, uint32_t phases, XtkEventFn fn, void *arg);
bool      xtk_txn_off(XtkTxn *txn, XtkSubId id);

/* One-op transactions: begin/commit a single mutation. */
bool      xtk_control_set(XtkScene *scene, XtkCtrl control, XtkPropertyId id, XtkValue value, XtkChangeStamp change);
bool      xtk_control_set_bool(XtkScene *scene, XtkCtrl control, XtkPropertyId id, bool value, XtkChangeStamp change);
bool      xtk_control_set_f32(XtkScene *scene, XtkCtrl control, XtkPropertyId id, float value, XtkChangeStamp change);
bool      xtk_control_set_i32(XtkScene *scene, XtkCtrl control, XtkPropertyId id, int32_t value, XtkChangeStamp change);
bool      xtk_control_set_f64(XtkScene *scene, XtkCtrl control, XtkPropertyId id, double value, XtkChangeStamp change);
bool xtk_control_set_enum(XtkScene *scene, XtkCtrl control, XtkPropertyId id, uint32_t value, XtkChangeStamp change);
bool xtk_control_set_color(XtkScene *scene, XtkCtrl control, XtkPropertyId id, XtkColor value, XtkChangeStamp change);
bool xtk_control_set_resource(
  XtkScene *scene, XtkCtrl control, XtkPropertyId id, XtkResource value, XtkChangeStamp change
);
bool xtk_control_set_string(
  XtkScene *scene, XtkCtrl control, XtkPropertyId id, char const *data, uint32_t len, XtkChangeStamp change
);
bool xtk_control_get(
  XtkScene const *scene, XtkCtrl control, XtkPropertyId id, XtkValueView *out_value, XtkChangeStamp *out_change
);


#endif
