#ifndef XTK_PROP_STATE_H
#define XTK_PROP_STATE_H

#include <xtk/xtk.h>
#include <xtk/xtk_batch.h>

typedef struct XtkEl    XtkEl;
typedef struct XtkArena XtkArena;

typedef struct XtkPropBlob {
	uint32_t refcount;
	uint32_t len;
	uint8_t  data [];
} XtkPropBlob;

typedef struct XtkPropSlot {
	XtkPropertyId id;
	XtkValue      value;
	XtkPropBlob  *blob;
} XtkPropSlot;

typedef struct XtkPropState {
	uint32_t     refcount;
	uint32_t     count;
	uint32_t     capacity;
	uint64_t     revision;
	XtkModelVer  model_ver;
	XtkPropSlot *items;
} XtkPropState;

typedef struct XtkPropView {
	XtkPropPatch *items;
	uint32_t      count;
} XtkPropView;

bool xtk_prop_view_build(XtkEl const *el, XtkPropPatch *items, uint32_t capacity, bool skip_model, XtkPropView *out);
void xtk_prop_view_destroy(XtkPropView *view);
XtkPropState      *xtk_prop_state_copy(XtkPropView view, XtkModelVer model_ver);
XtkPropState      *xtk_prop_state_retain(XtkPropState *state);
void               xtk_prop_state_destroy(XtkPropState *state);
XtkPropSlot const *xtk_prop_state_find(XtkPropState const *state, XtkPropertyId id);
void               xtk_prop_slots_release(XtkPropSlot *slots, uint32_t count);
void xtk_prop_state_apply_patch(XtkPropState *state, XtkPropSlot const *slots, uint32_t count, XtkModelVer model_ver);

typedef struct XtkEcho {
	XtkChangeStamp stamp;
	XtkPropertyId  force [8];
	uint32_t       nforce;
} XtkEcho;

bool xtk_prop_state_diff(
  XtkBatch *batch, XtkNodeRef target, XtkPropState const *old, XtkPropView next, bool skip_model, XtkEcho const *echo,
  bool *changed
);
bool xtk_prop_state_prepare(
  XtkPropState *old, XtkPropView next, XtkModelVer model_ver, bool skip_model, XtkArena *patch_arena,
  XtkPropState **out_new, XtkPropSlot **out_patch, uint32_t *out_count
);

#endif
