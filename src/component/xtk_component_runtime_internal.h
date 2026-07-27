#ifndef XTK_COMPONENT_RUNTIME_INTERNAL_H
#define XTK_COMPONENT_RUNTIME_INTERNAL_H

#include "xtk_component_internal.h"

enum
{
	XTK_COMP_TYPE_CAP = 32u,
	XTK_COMP_INST_CAP = 16u,
	XTK_COMP_PEND_CAP = 8u,
};

typedef struct XtkCompInst {
	XtkCtrl            control;
	XtkCtrl            content_root;
	XtkCtrl            impl_root;
	XtkCompType const *type;
	void              *state;
	void              *props;
	size_t             props_size;
	bool               live;
} XtkCompInst;

typedef struct CompPending {
	XtkCompPendingKind kind;
	XtkCtrl            control;
	XtkCtrl            content_root;
	XtkCtrl            impl_root;
	XtkCompType const *type;
	void              *props_next;
	size_t             props_size;
	XtkCompPrep       *prepare;
	XtkHost           *host;
	XentCtx           *ctx;
} CompPending;

struct XtkCompRt {
	XtkCompType const     *types [XTK_COMP_TYPE_CAP];
	uint32_t               type_count;
	XtkCompInst           *inst;
	uint32_t               inst_count;
	uint32_t               inst_cap;
	CompPending           *pending;
	uint32_t               pending_count;
	uint32_t               pending_cap;
	XtkProviderDesc const *providers;
	uint32_t               provider_count;
	bool                   providers_locked;
};

struct XtkCompHost {
	XtkHost               *host;
	XentCtx               *ctx;
	XtkCtrl                control;
	XtkCtrl                content_root;
	XtkCtrl                impl_root;
	XtkProviderDesc const *providers;
	uint32_t               provider_count;
};

void               xtk_comp_free_instance(XtkCompInst *instance);
XtkCompInst       *xtk_comp_find_instance(XtkCompRt *rt, XtkCtrl control);
XtkCompInst const *xtk_comp_findinst_const(XtkCompRt const *rt, XtkCtrl control);
XtkCompHost
xtk_comp_make_host(XtkCompRt *rt, XtkHost *host, XentCtx *ctx, XtkCtrl control, XtkCtrl content, XtkCtrl impl);

#endif
