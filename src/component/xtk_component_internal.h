#ifndef XTK_COMPONENT_INTERNAL_H
#define XTK_COMPONENT_INTERNAL_H

#include <xtk/xtk_component.h>
#include <xtk/xtk_host.h>
#include <xtk/xtk_alloc.h>
#include <xtk/xtk_comp_rt.h>

#include <xent/xent.h>

typedef enum XtkCompPendingKind
{
	XTK_COMP_PENDING_MOUNT = 1,
	XTK_COMP_PENDING_UPDATE,
} XtkCompPendingKind;

XtkCtrl xtk_comp_content_root(XtkCompRt const *rt, XtkCtrl control);
XtkCtrl xtk_comp_impl_root(XtkCompRt const *rt, XtkCtrl control);

#endif
