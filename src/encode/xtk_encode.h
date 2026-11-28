#ifndef XTK_ENCODE_H
#define XTK_ENCODE_H

#include <xtk/xtk.h>
#include <xtk/xtk_batch.h>
#include <xtk/xtk_catalog.h>
#include <xtk/xtk_reconcile.h>

typedef struct XtkRealized {
	int first;
	int last;
	int lanes;
} XtkRealized;

static_assert(XTK_EVENT_STANDARD_COUNT <= 64, "XtkBinding.user_events is a 64-bit event mask");

typedef struct XtkBinding {
	XtkRt         *rt;
	XtkRealized    realized;
	XtkChangeStamp echo;
	uint64_t       user_events;
	XtkMsg         msgs [XTK_EVENT_STANDARD_COUNT];
} XtkBinding;

bool                   xtk_el_needs_binding(XtkEl const *el);
void                   xtk_binding_load_msgs(XtkBinding *b, XtkEl const *el);
bool                   xtk_binding_msgs_equal(XtkBinding const *a, XtkEl const *el);

typedef struct XtkNode XtkNode;

bool xtk_encode_create(XtkBatch *batch, XtkNodeRef parent, XtkNodeRef before, XtkEl const *el, XtkLocalId *out_local);
bool xtk_encode_props_view(XtkBatch *batch, XtkNodeRef target, XtkEl const *el, bool skip_model);
XtkModelVer xtk_el_model_ver(XtkEl const *el);
bool        xtk_encode_subscribe(XtkBatch *batch, XtkNodeRef target, XtkBinding *binding, XtkEl const *el);
bool        xtk_encode_unsubscribe_all(XtkBatch *batch, XtkNode const *node);

bool        xtk_encode_date_picker(XtkBatch *batch, XtkNodeRef target, XtkEl const *prev, XtkEl const *el);
bool        xtk_encode_time_picker(XtkBatch *batch, XtkNodeRef target, XtkEl const *prev, XtkEl const *el);
bool        xtk_encode_calendar(XtkBatch *batch, XtkNodeRef target, XtkEl const *prev, XtkEl const *el);
bool        xtk_encode_color_picker(XtkBatch *batch, XtkNodeRef target, XtkEl const *prev, XtkEl const *el);

bool        xtk_items_strings(XtkBatch *batch, XtkNodeRef target, char const *const *items, int count);
bool        xtk_items_selector(XtkBatch *batch, XtkNodeRef target, XtkSelectorItem const *items, int count);
bool        xtk_items_tabs(XtkBatch *batch, XtkNodeRef target, XtkTabDesc const *tabs, int count);
bool        xtk_items_tree(XtkBatch *batch, XtkNodeRef target, XtkTreeDesc const *tree);
bool        xtk_items_nav(XtkBatch *batch, XtkNodeRef target, XtkNavDesc const *nav);

#endif
