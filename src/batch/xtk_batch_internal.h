#ifndef XTK_BATCH_INTERNAL_H
#define XTK_BATCH_INTERNAL_H

#include <xtk/xtk_batch.h>

bool            xtk_batch_value_ok(XtkValue const *value);
bool            xtk_batch_prop_ok(XtkPropPatch const *prop);
bool            xtk_batch_props_ok(XtkPropPatch const *props, uint32_t count);
XtkPropertyKind xtk_batch_prop_kind(XtkValueKind kind);
bool            xtk_batch_stdprop_ok(XtkCtrlId control, XtkPropPatch const *patch);
bool            xtk_batch_phases_ok(XtkEventId event, uint32_t phases);

void            xtk_batch_reset(XtkBatch *batch, uint64_t revision);
bool            xtk_batch_capture_begin(XtkBatch *batch, XtkBatchOp *ops, uint32_t capacity);
void            xtk_batch_capture_end(XtkBatch *batch);

#endif
