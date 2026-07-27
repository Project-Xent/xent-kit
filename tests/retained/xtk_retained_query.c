#include "xtk_retained_internal.h"

static bool types_ensure(Retained *R, uint32_t index) {
	if (index < R->types_cap) return true;
	uint32_t cap = R->types_cap ? R->types_cap * 2u : 64u;
	while (cap <= index) {
		if (cap > UINT32_MAX / 2u) return false;
		cap *= 2u;
	}
	XtkCtrlId *n = ( XtkCtrlId * ) xtk_alloc_resize(R->types, sizeof(*n) * cap);
	if (!n) return false;
	memset(n + R->types_cap, 0, sizeof(*n) * (cap - R->types_cap));
	R->types     = n;
	R->types_cap = cap;
	return true;
}

bool retained_types_set(Retained *R, XentNodeId node, XtkCtrlId type) {
	uint32_t index = xent_node_index(node);
	if (!types_ensure(R, index)) return false;
	R->types [index] = type;
	return true;
}

XtkCtrlId retained_types_get(Retained const *R, XentNodeId node) {
	uint32_t index = xent_node_index(node);
	if (index >= R->types_cap) return XTK_CTRL_ID_INVALID;
	return R->types [index];
}

static bool invalidate_ensure(Retained *R, uint32_t index) {
	if (index < R->invalidate_cap) return true;
	uint32_t cap = R->invalidate_cap ? R->invalidate_cap * 2u : 64u;
	while (cap <= index) {
		if (cap > UINT32_MAX / 2u) return false;
		cap *= 2u;
	}
	uint32_t *n = ( uint32_t * ) xtk_alloc_resize(R->invalidate, sizeof(*n) * cap);
	if (!n) return false;
	memset(n + R->invalidate_cap, 0, sizeof(*n) * (cap - R->invalidate_cap));
	R->invalidate     = n;
	R->invalidate_cap = cap;
	return true;
}

void retained_note_invalidate(Retained *R, XtkCtrl control, uint32_t mask) {
	if (!mask || control == XTK_CTRL_INVALID) return;
	uint32_t index = xent_node_index(retained_as_node(control));
	if (!invalidate_ensure(R, index)) return;
	R->invalidate [index]   |= mask;
	R->pending_invalidation |= mask;
}

void retained_invalidate_prop(Retained *R, XtkCtrl control, XtkPropertyId id) {
	XtkPropDesc const *prop = xtk_catalog_property(id);
	if (prop) retained_note_invalidate(R, control, prop->invalidates);
}

void retained_invalidate_control_lifecycle(Retained *R, XtkCtrl control, bool create) {
	XtkCtrlId          type = retained_types_get(R, retained_as_node(control));
	XtkCtrlDesc const *desc = xtk_catalog_control(type);
	if (!desc && R->comp) desc = xtk_comp_desc(R->comp, type);
	if (!desc) return;
	retained_note_invalidate(R, control, create ? desc->create_invalidates : desc->destroy_invalidates);
}

static void purge_sidecar_node(Retained *R, XtkCtrl control) {
	if (R->focus == control) R->focus = XTK_CTRL_INVALID;
	if (R->comp) xtk_comp_dropinst(R->comp, control);
	retained_clear_control_props(R, control);
	retained_clear_control_subs(R, control);
	uint32_t index = xent_node_index(retained_as_node(control));
	if (index < R->invalidate_cap) R->invalidate [index] = 0u;
}

static void purge_subtree_walk(Retained *R, XentNodeId node) {
	for (XentNodeId child = xent_node_first(R->ctx, node); child != XENT_NODE_INVALID;
	  child               = xent_node_next(R->ctx, child))
		purge_subtree_walk(R, child);
	purge_sidecar_node(R, retained_as_control(node));
}

void retained_purge_subtree_sidecar(Retained *R, XentNodeId root) { purge_subtree_walk(R, root); }

bool retained_host_is_live(XtkHost const *host, XtkCtrl control) {
	Retained const *R = retained_impl_c(host);
	return R && retained_host_live(R, control);
}

uint64_t retained_host_revision(XtkHost const *host) {
	Retained const *R = retained_impl_c(host);
	return R ? R->revision : 0u;
}

XtkCtrl retained_host_scene_root(XtkHost const *host) {
	Retained const *R = retained_impl_c(host);
	return R ? retained_as_control(R->root) : XTK_CTRL_INVALID;
}

XtkCtrlId retained_host_control_type(XtkHost const *host, XtkCtrl control) {
	Retained const *R = retained_impl_c(host);
	if (!R || !retained_host_live(R, control)) return XTK_CTRL_ID_INVALID;
	return retained_types_get(R, retained_as_node(control));
}

XtkCtrl retained_host_parent(XtkHost const *host, XtkCtrl control) {
	Retained const *R = retained_impl_c(host);
	if (!R || !retained_host_live(R, control)) return XTK_CTRL_INVALID;
	return retained_as_control(xent_node_parent(R->ctx, retained_as_node(control)));
}

XtkCtrl retained_host_first_child(XtkHost const *host, XtkCtrl control) {
	Retained const *R = retained_impl_c(host);
	if (!R || !retained_host_live(R, control)) return XTK_CTRL_INVALID;
	return retained_as_control(xent_node_first(R->ctx, retained_as_node(control)));
}

XtkCtrl retained_host_next_sibling(XtkHost const *host, XtkCtrl control) {
	Retained const *R = retained_impl_c(host);
	if (!R || !retained_host_live(R, control)) return XTK_CTRL_INVALID;
	return retained_as_control(xent_node_next(R->ctx, retained_as_node(control)));
}

XtkCtrlDesc const *retained_host_descriptor(XtkHost const *host, XtkCtrlId type) {
	XtkCtrlDesc const *d = xtk_catalog_control(type);
	if (d) return d;
	Retained const *R = retained_impl_c(host);
	return R && R->comp ? xtk_comp_desc(R->comp, type) : NULL;
}

bool retained_host_resource_is_valid(XtkHost const *host, XtkResource resource, XtkResourceTypeId type) {
	( void ) host;
	( void ) type;
	return resource != XTK_RESOURCE_INVALID;
}

bool retained_host_resource_retain(XtkHost *host, XtkResource resource, XtkResourceTypeId type) {
	( void ) host;
	( void ) type;
	return resource != XTK_RESOURCE_INVALID;
}

void retained_host_resource_release(XtkHost *host, XtkResource resource, XtkResourceTypeId type) {
	( void ) host;
	( void ) resource;
	( void ) type;
}

uint32_t xtk_retained_invalidation(XtkHost const *host, XtkCtrl control) {
	Retained const *R = retained_impl_c(host);
	if (!R || !retained_host_live(R, control)) return XTK_INVALIDATE_NONE;
	uint32_t index = xent_node_index(retained_as_node(control));
	if (index >= R->invalidate_cap) return XTK_INVALIDATE_NONE;
	return R->invalidate [index];
}

uint32_t xtk_retained_take_invalidations(XtkHost *host) {
	Retained *R = retained_impl(host);
	if (!R) return XTK_INVALIDATE_NONE;
	uint32_t mask           = R->pending_invalidation;
	R->pending_invalidation = 0u;
	return mask;
}

XtkHost *xtk_retained_host_create(void) {
	Retained *R = ( Retained * ) xtk_alloc_zero(1, sizeof(Retained));
	if (!R) return NULL;
	R->comp = xtk_comp_create();
	R->ctx  = xent_ctx_create(NULL);
	if (!R->ctx || !R->comp) {
		xtk_comp_destroy(R->comp);
		if (R->ctx) xent_ctx_destroy(R->ctx);
		xtk_alloc_free(R);
		return NULL;
	}
	R->root = xent_node_create(R->ctx);
	if (R->root == XENT_NODE_INVALID || !retained_types_set(R, R->root, XTK_CTRL_CONTAINER)) {
		xtk_comp_destroy(R->comp);
		xent_ctx_destroy(R->ctx);
		xtk_alloc_free(R);
		return NULL;
	}
	R->host.vt   = &retained_host_vtable;
	R->host.impl = R;
	R->revision  = 1u;
	R->next_sub  = 0u;
	R->focus     = XTK_CTRL_INVALID;
	retained_invalidate_control_lifecycle(R, retained_as_control(R->root), true);
	return &R->host;
}

XentCtx *xtk_retained_host_context(XtkHost *host) {
	Retained *R = retained_impl(host);
	return R ? R->ctx : NULL;
}

void xtk_retained_host_destroy(XtkHost *host) {
	Retained *R = retained_impl(host);
	if (!R) return;
	retained_props_dispose(R);
	xtk_alloc_free(R->subs);
	xtk_alloc_free(R->types);
	xtk_alloc_free(R->invalidate);
	xtk_comp_destroy(R->comp);
	xent_ctx_destroy(R->ctx);
	xtk_alloc_free(R);
}

bool xtk_retained_register_component(XtkHost *host, XtkCompType const *type) {
	Retained *R = retained_impl(host);
	return R && R->comp && xtk_comp_register(R->comp, type);
}

bool xtk_retained_set_providers(XtkHost *host, XtkProviderDesc const *providers, uint32_t count) {
	Retained *R = retained_impl(host);
	return R && R->comp && xtk_comp_setproviders(R->comp, providers, count);
}

XtkCtrl xtk_retained_component_content_root(XtkHost const *host, XtkCtrl control) {
	Retained const *R = retained_impl_c(host);
	return R && R->comp ? xtk_comp_content_root(R->comp, control) : XTK_CTRL_INVALID;
}

XtkCtrl xtk_retained_component_impl_root(XtkHost const *host, XtkCtrl control) {
	Retained const *R = retained_impl_c(host);
	return R && R->comp ? xtk_comp_impl_root(R->comp, control) : XTK_CTRL_INVALID;
}

XtkHostVtable const retained_host_vtable = {
  .abi         = XTK_HOST_ABI_VERSION,
  .preflight   = retained_host_preflight,
  .prepare     = retained_host_prepare,
  .commit      = retained_host_commit,
  .abort       = retained_host_abort,
  .live        = retained_host_is_live,
  .revision    = retained_host_revision,
  .root        = retained_host_scene_root,
  .type        = retained_host_control_type,
  .parent      = retained_host_parent,
  .first       = retained_host_first_child,
  .next        = retained_host_next_sibling,
  .desc        = retained_host_descriptor,
  .prop        = retained_host_get_property,
  .res_valid   = retained_host_resource_is_valid,
  .res_retain  = retained_host_resource_retain,
  .res_release = retained_host_resource_release,
  .dispatch    = retained_host_dispatch,
};
