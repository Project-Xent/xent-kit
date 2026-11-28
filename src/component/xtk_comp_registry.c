#include "xtk_comp_rtinternal.h"

XtkCompRt *xtk_comp_create(void) { return ( XtkCompRt * ) xtk_alloc_zero(1, sizeof(XtkCompRt)); }

void       xtk_comp_free_instance(XtkCompInst *in) {
	xtk_alloc_free(in->props);
	in->props = NULL;
	in->state = NULL;
	in->live  = false;
}

void xtk_comp_destroy(XtkCompRt *rt) {
	if (!rt) return;
	xtk_comp_abort(rt);
	for (uint32_t i = 0; i < rt->inst_count; i++) xtk_comp_free_instance(&rt->inst [i]);
	xtk_alloc_free(rt->inst);
	xtk_alloc_free(rt->pending);
	xtk_alloc_free(rt);
}

static bool type_valid(XtkCompType const *type) {
	if (!type || !type->control || !xtk_ctrl_iscomp(type->control->id)) return false;
	if (!type->ops.prepare_mount || !type->ops.commit_mount || !type->ops.abort || !type->ops.unmount) return false;
	return !type->ops.prepare_update || type->ops.commit_update;
}

static XtkCompType const **type_slot(XtkCompRt *rt, XtkCtrlId id) {
	for (uint32_t i = 0; i < rt->type_count; i++)
		if (rt->types [i]->control->id == id) return &rt->types [i];
	return NULL;
}

bool xtk_comp_register(XtkCompRt *rt, XtkCompType const *type) {
	if (!rt || !type_valid(type) || type_slot(rt, type->control->id)) return false;
	if (rt->type_count >= XTK_COMP_TYPE_CAP) return false;
	rt->types [rt->type_count++] = type;
	return true;
}

bool xtk_comp_replace(XtkCompRt *rt, XtkCompType const *type) {
	if (!rt || !type_valid(type)) return false;
	XtkCompType const **slot = type_slot(rt, type->control->id);
	if (!slot) return xtk_comp_register(rt, type);
	*slot = type;
	return true;
}

void xtk_comp_unregister(XtkCompRt *rt, XtkCtrlId id) {
	XtkCompType const **slot = rt ? type_slot(rt, id) : NULL;
	if (!slot) return;
	*slot = rt->types [--rt->type_count];
}

XtkCompType const *xtk_comp_lookup(XtkCompRt const *rt, XtkCtrlId id) {
	if (!rt) return NULL;
	for (uint32_t i = 0; i < rt->type_count; i++)
		if (rt->types [i]->control->id == id) return rt->types [i];
	return NULL;
}

XtkCtrlDesc const *xtk_comp_desc(XtkCompRt const *rt, XtkCtrlId id) {
	XtkCompType const *t = xtk_comp_lookup(rt, id);
	return t ? t->control : NULL;
}

bool xtk_comp_setproviders(XtkCompRt *rt, XtkProviderDesc const *providers, uint32_t count) {
	if (!rt || rt->providers_locked) return false;
	if (count && !providers) return false;
	rt->providers      = providers;
	rt->provider_count = count;
	return true;
}

void xtk_comp_lockproviders(XtkCompRt *rt) {
	if (rt) rt->providers_locked = true;
}

XtkCompInst *xtk_comp_find_instance(XtkCompRt *rt, XtkCtrl control) {
	for (uint32_t i = 0; i < rt->inst_count; i++)
		if (rt->inst [i].live && rt->inst [i].control == control) return &rt->inst [i];
	return NULL;
}

XtkCompInst const *xtk_comp_findinst_const(XtkCompRt const *rt, XtkCtrl control) {
	for (uint32_t i = 0; i < rt->inst_count; i++)
		if (rt->inst [i].live && rt->inst [i].control == control) return &rt->inst [i];
	return NULL;
}

bool xtk_comp_hasinst(XtkCompRt const *rt, XtkCtrl control) {
	return rt && xtk_comp_findinst_const(rt, control) != NULL;
}

XtkCtrl xtk_comp_content_root(XtkCompRt const *rt, XtkCtrl control) {
	XtkCompInst const *in = rt ? xtk_comp_findinst_const(rt, control) : NULL;
	return in ? in->content_root : XTK_CTRL_INVALID;
}

XtkCtrl xtk_comp_impl_root(XtkCompRt const *rt, XtkCtrl control) {
	XtkCompInst const *in = rt ? xtk_comp_findinst_const(rt, control) : NULL;
	return in ? in->impl_root : XTK_CTRL_INVALID;
}

void const *xtk_comp_props(XtkCompRt const *rt, XtkCtrl control, size_t *out_size) {
	XtkCompInst const *in = rt ? xtk_comp_findinst_const(rt, control) : NULL;
	if (!in) {
		if (out_size) *out_size = 0u;
		return NULL;
	}
	if (out_size) *out_size = in->props_size;
	return in->props;
}
