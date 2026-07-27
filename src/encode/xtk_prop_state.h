#ifndef XTK_PROP_STATE_H
#define XTK_PROP_STATE_H

#include <xtk/xtk_batch.h>

typedef struct XtkEl XtkEl;

typedef struct XtkPropState {
	uint32_t     count;
	XtkPropPatch items [];
} XtkPropState;

typedef struct XtkPropView {
	XtkPropPatch *items;
	uint32_t      count;
} XtkPropView;

bool          xtk_prop_view_build(XtkEl const *el, XtkPropPatch *items, uint32_t capacity, XtkPropView *out);
void          xtk_prop_view_destroy(XtkPropView *view);
XtkPropState *xtk_prop_state_copy(XtkPropView view);
void          xtk_prop_state_destroy(XtkPropState *state);
bool xtk_prop_state_diff(XtkBatch *batch, XtkNodeRef target, XtkPropState const *old, XtkPropView next, bool *changed);

#endif
