#ifndef XTK_ENCODE_H
#define XTK_ENCODE_H

#include <xtk/xtk.h>
#include <xtk/xtk_batch.h>
#include <xtk/xtk_catalog.h>
#include <xtk/xtk_reconcile.h>

typedef struct XtkBinding {
	XtkRt *rt;
	XtkMsg msgs [XTK_EVENT_STANDARD_COUNT];
} XtkBinding;

bool                   xtk_el_needs_binding(XtkEl const *el);
void                   xtk_binding_load_msgs(XtkBinding *b, XtkEl const *el);
bool                   xtk_binding_msgs_equal(XtkBinding const *a, XtkEl const *el);

typedef struct XtkNode XtkNode;

bool xtk_encode_create(XtkBatch *batch, XtkNodeRef parent, XtkNodeRef before, XtkEl const *el, XtkLocalId *out_local);
bool xtk_encode_props(XtkBatch *batch, XtkNodeRef target, XtkEl const *prev, XtkEl const *el);
bool xtk_encode_subscribe(XtkBatch *batch, XtkNodeRef target, XtkBinding *binding, XtkEl const *el);
bool xtk_encode_unsubscribe_all(XtkBatch *batch, XtkNode const *node);

#endif
