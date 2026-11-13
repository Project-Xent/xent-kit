#ifndef XTK_COMP_RT_H
#define XTK_COMP_RT_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "xtk_component.h"
#include "xtk_descriptor.h"
#include "xtk_host.h"

#include <xent/xent.h>

typedef struct XtkCompRt XtkCompRt;

static bool inline xtk_ctrl_iscomp(XtkCtrlId id) { return id >= XTK_CTRL_ID_COMPONENT_BASE; }

XENT_NODISCARD XtkCompRt *xtk_comp_create(void);
void                      xtk_comp_destroy(XtkCompRt *rt);

bool                      xtk_comp_register(XtkCompRt *rt, XtkCompType const *type);
XtkCompType const        *xtk_comp_lookup(XtkCompRt const *rt, XtkCtrlId id);

bool                      xtk_comp_setproviders(XtkCompRt *rt, XtkProviderDesc const *providers, uint32_t count);
void                      xtk_comp_lockproviders(XtkCompRt *rt);

XtkCompErr                xtk_comp_prepmount(
  XtkCompRt *rt, XtkHost *host, XentCtx *ctx, XtkCtrl control, XtkCtrl content_root, XtkCtrl impl_root,
  XtkCompType const *type, void const *props_bytes, uint32_t props_len
);
XtkCompErr xtk_comp_prepupd(
  XtkCompRt *rt, XtkHost *host, XentCtx *ctx, XtkCtrl control, void const *props_bytes, uint32_t props_len
);

XtkCompErr         xtk_comp_commit(XtkCompRt *rt);
void               xtk_comp_abort(XtkCompRt *rt);

void               xtk_comp_unmount(XtkCompRt *rt, XtkHost *host, XentCtx *ctx, XtkCtrl control);
void               xtk_comp_dropinst(XtkCompRt *rt, XtkCtrl control);

bool               xtk_comp_hasinst(XtkCompRt const *rt, XtkCtrl control);
void const        *xtk_comp_props(XtkCompRt const *rt, XtkCtrl control, size_t *out_size);

uint32_t           xtk_comp_dispatch(XtkCompRt *rt, XtkHost *host, XentCtx *ctx, XtkCtrl target, XtkEvent const *event);

XtkCtrlDesc const *xtk_comp_desc(XtkCompRt const *rt, XtkCtrlId id);

#endif
