#include "xtk_retained_internal.h"

static bool pending_destroy_subtree(Prepare const *P, XtkCtrl control) {
	if (control == XTK_CTRL_INVALID) return true;
	XentNodeId node = retained_as_node(control);
	for (uint32_t i = 0; i < P->destroy_count; i++) {
		XentNodeId root = P->deferred_destroy [i];
		for (XentNodeId cur = node; cur != XENT_NODE_INVALID; cur = xent_node_parent(P->R->ctx, cur))
			if (cur == root) return true;
	}
	return false;
}

static bool capture_topo(Prepare *P, XentNodeId child) {
	XentNodeId parent = xent_node_parent(P->R->ctx, child);
	Undo       u      = {
	  .kind   = UNDO_TOPO,
	  .u.topo = {
				 .child      = child,
				 .old_parent = parent,
				 .old_next   = parent == XENT_NODE_INVALID ? XENT_NODE_INVALID : xent_node_next(P->R->ctx, child),
				 }
    };
	return retained_undo_push(P, u);
}

static bool place(Prepare *P, XentNodeId parent, XentNodeId child, XentNodeId before) {
	if (!capture_topo(P, child)) return false;
	XentNodeId cur = xent_node_parent(P->R->ctx, child);
	bool       ok  = false;
	if (cur == XENT_NODE_INVALID) ok = xent_node_insert(P->R->ctx, parent, child, before);
	else if (cur == parent) ok = xent_node_move(P->R->ctx, parent, child, before);
	else ok = xent_node_reparent(P->R->ctx, parent, child, before);
	if (!ok) return false;
	retained_note_invalidate(
	  P->R, retained_as_control(parent), XTK_INVALIDATE_LAYOUT | XTK_INVALIDATE_HIT_TEST | XTK_INVALIDATE_PAINT
	);
	if (cur != XENT_NODE_INVALID && cur != parent)
		retained_note_invalidate(
		  P->R, retained_as_control(cur), XTK_INVALIDATE_LAYOUT | XTK_INVALIDATE_HIT_TEST | XTK_INVALIDATE_PAINT
		);
	return true;
}

static bool create_node(Prepare *P, XtkCtrlId type, XtkLocalId local, XentNodeId *out) {
	XentNodeId node = xent_node_create(P->R->ctx);
	if (node == XENT_NODE_INVALID) return false;
	if (!retained_types_set(P->R, node, type)
		|| !retained_undo_push(P, (Undo) {.kind = UNDO_CREATE, .u.created = node}))
	{
		xent_node_destroy(P->R->ctx, node);
		return false;
	}
	P->locals [local] = retained_as_control(node);
	*out              = node;
	return true;
}

static bool place_refs(Prepare *P, XtkNodeRef parent_ref, XtkNodeRef before_ref, XentNodeId child) {
	bool    ok     = false;
	XtkCtrl parent = XTK_CTRL_INVALID;
	XtkCtrl before = XTK_CTRL_INVALID;
	if (!retained_resolve_ref(P, parent_ref, &ok, &parent) || !ok) return false;
	if (!retained_resolve_ref(P, before_ref, &ok, &before) || !ok) return false;
	XentNodeId parent_node = parent == XTK_CTRL_INVALID ? P->R->root : retained_as_node(parent);
	XentNodeId before_node = before == XTK_CTRL_INVALID ? XENT_NODE_INVALID : retained_as_node(before);
	return place(P, parent_node, child, before_node);
}

static bool create_child_root(Prepare *P, XentNodeId parent, XentNodeId *out) {
	XentNodeId node = xent_node_create(P->R->ctx);
	if (node == XENT_NODE_INVALID) return false;
	if (!retained_types_set(P->R, node, XTK_CTRL_CONTAINER)
		|| !retained_undo_push(P, (Undo) {.kind = UNDO_CREATE, .u.created = node}))
	{
		xent_node_destroy(P->R->ctx, node);
		return false;
	}
	if (!xent_node_append(P->R->ctx, parent, node)) return false;
	*out = node;
	return true;
}

static XtkPropPatch const *find_component_props(XtkBatchCreate const *op) {
	for (uint32_t i = 0; i < op->prop_count; i++)
		if (op->props [i].id == XTK_PROP_COMPONENT_PROPS) return &op->props [i];
	return NULL;
}

static bool create_component_roots(Prepare *P, XentNodeId node, XentNodeId roots [2]) {
	return create_child_root(P, node, &roots [0]) && create_child_root(P, node, &roots [1]);
}

static bool stage_component_mount(
  Prepare *P, XtkBatchCreate const *op, XtkCompType const *type, XentNodeId node, XentNodeId const roots [2]
) {
	XtkPropPatch const *props = find_component_props(op);
	void const         *bytes = props ? props->value.u.bytes.data : NULL;
	uint32_t            len   = props ? props->value.u.bytes.len : 0u;
	return xtk_comp_prepmount(
			 P->R->comp, &P->R->host, P->R->ctx, retained_as_control(node), retained_as_control(roots [0]),
			 retained_as_control(roots [1]), type, bytes, len
		   )
	    == XTK_COMPONENT_OK;
}

static bool apply_component_props(Prepare *P, XtkBatchCreate const *op, XentNodeId node) {
	for (uint32_t i = 0; i < op->prop_count; i++) {
		if (op->props [i].id == XTK_PROP_COMPONENT_PROPS) continue;
		if (!retained_apply_prop(P, retained_as_control(node), &op->props [i])) return false;
	}
	return true;
}

static bool apply_create_component(Prepare *P, XtkBatchCreate const *op, XtkLocalId local) {
	XtkCompType const *type = xtk_comp_lookup(P->R->comp, op->type);
	if (!type) return false;
	XentNodeId node;
	if (!create_node(P, op->type, local, &node)) return false;
	if (!place_refs(P, op->parent, op->before, node)) return false;
	XentNodeId roots [2] = {XENT_NODE_INVALID, XENT_NODE_INVALID};
	if (!create_component_roots(P, node, roots) || !stage_component_mount(P, op, type, node, roots)) return false;
	retained_invalidate_control_lifecycle(P->R, retained_as_control(node), true);
	return apply_component_props(P, op, node);
}

static bool apply_create(Prepare *P, XtkBatchCreate const *op, XtkLocalId local) {
	if (xtk_ctrl_is_component(op->type)) return apply_create_component(P, op, local);
	XentNodeId node;
	if (!create_node(P, op->type, local, &node)) return false;
	if (!place_refs(P, op->parent, op->before, node)) return false;
	retained_invalidate_control_lifecycle(P->R, retained_as_control(node), true);
	for (uint32_t i = 0; i < op->prop_count; i++)
		if (!retained_apply_prop(P, retained_as_control(node), &op->props [i])) return false;
	return true;
}

static bool apply_topo_op(Prepare *P, XtkNodeRef pref, XtkNodeRef cref, XtkNodeRef bref) {
	bool    ok     = false;
	XtkCtrl parent = XTK_CTRL_INVALID;
	XtkCtrl child  = XTK_CTRL_INVALID;
	XtkCtrl before = XTK_CTRL_INVALID;
	if (!retained_resolve_ref(P, pref, &ok, &parent) || !ok) return false;
	if (!retained_resolve_ref(P, cref, &ok, &child) || !ok) return false;
	if (!retained_resolve_ref(P, bref, &ok, &before) || !ok) return false;
	XentNodeId p = parent == XTK_CTRL_INVALID ? P->R->root : retained_as_node(parent);
	XentNodeId b = before == XTK_CTRL_INVALID ? XENT_NODE_INVALID : retained_as_node(before);
	return place(P, p, retained_as_node(child), b);
}

static bool apply_destroy(Prepare *P, XtkBatchOp const *op) {
	bool    ok     = false;
	XtkCtrl target = XTK_CTRL_INVALID;
	if (!retained_resolve_ref(P, op->u.destroy.target, &ok, &target) || !ok || !retained_host_live(P->R, target))
		return false;
	return retained_defer_destroy(P, retained_as_node(target));
}

static bool apply_set_prop(Prepare *P, XtkBatchOp const *op) {
	bool    ok     = false;
	XtkCtrl target = XTK_CTRL_INVALID;
	if (!retained_resolve_ref(P, op->u.set_prop.target, &ok, &target) || !ok) return false;
	XtkCtrlId type = retained_types_get(P->R, retained_as_node(target));
	if (op->u.set_prop.patch.id == XTK_PROP_COMPONENT_PROPS && xtk_ctrl_is_component(type)) {
		XtkValue const *v = &op->u.set_prop.patch.value;
		return xtk_comp_prepupd(P->R->comp, &P->R->host, P->R->ctx, target, v->u.bytes.data, v->u.bytes.len)
		    == XTK_COMPONENT_OK;
	}
	return retained_apply_prop(P, target, &op->u.set_prop.patch);
}

static bool apply_op(Prepare *P, XtkBatchOp const *op) {
	if (op->kind == XTK_BATCH_OP_CREATE) return apply_create(P, &op->u.create, op->u.create.local);
	if (op->kind == XTK_BATCH_OP_DESTROY) return apply_destroy(P, op);
	if (op->kind == XTK_BATCH_OP_SET_PROP) return apply_set_prop(P, op);
	if (op->kind == XTK_BATCH_OP_INSERT)
		return apply_topo_op(P, op->u.insert.parent, op->u.insert.child, op->u.insert.before);
	if (op->kind == XTK_BATCH_OP_MOVE) return apply_topo_op(P, op->u.move.parent, op->u.move.child, op->u.move.before);
	if (op->kind == XTK_BATCH_OP_REPARENT)
		return apply_topo_op(P, op->u.reparent.new_parent, op->u.reparent.child, op->u.reparent.before);
	if (op->kind == XTK_BATCH_OP_SUBSCRIBE) return retained_apply_subscribe(P, &op->u.subscribe);
	if (op->kind == XTK_BATCH_OP_UNSUBSCRIBE) return retained_apply_unsubscribe(P, op->u.unsubscribe.id);
	return false;
}

static void finish_destroys(Prepare *P) {
	for (uint32_t i = 0; i < P->destroy_count; i++) {
		XentNodeId node = P->deferred_destroy [i];
		if (!xent_node_valid(P->R->ctx, node)) continue;
		XtkCtrl control = retained_as_control(node);
		retained_invalidate_control_lifecycle(P->R, control, false);
		if (P->R->comp && xtk_comp_hasinst(P->R->comp, control))
			xtk_comp_unmount(P->R->comp, &P->R->host, P->R->ctx, control);
		retained_purge_subtree_sidecar(P->R, node);
		xent_node_destroy(P->R->ctx, node);
	}
}

static void count_result_slots(XtkBatch const *batch, uint32_t *creates, uint32_t *subs) {
	*creates = 0u;
	*subs    = 0u;
	for (uint32_t i = 0; i < batch->count; i++) {
		*creates += batch->ops [i].kind == XTK_BATCH_OP_CREATE;
		*subs    += batch->ops [i].kind == XTK_BATCH_OP_SUBSCRIBE;
	}
}

static void fill_mappings(Prepare const *P, XtkBatchResult *result) {
	uint32_t ci = 0u, si = 0u;
	for (uint32_t i = 0; i < P->batch->count; i++) {
		XtkBatchOp const *op = &P->batch->ops [i];
		if (op->kind == XTK_BATCH_OP_CREATE) {
			XtkCtrl mapped = P->locals [op->u.create.local];
			if (pending_destroy_subtree(P, mapped)) mapped = XTK_CTRL_INVALID;
			result->controls [ci++] = (XtkControlMapping) {.local = op->u.create.local, .control = mapped};
			continue;
		}
		if (op->kind != XTK_BATCH_OP_SUBSCRIBE) continue;
		result->subscriptions [si++]
		  = (XtkSubMapping) {.token = op->u.subscribe.token, .id = P->sub_ids [op->u.subscribe.token]};
	}
}

static XtkBatchResult *fill_result(Prepare *P) {
	uint32_t creates = 0u, subs = 0u;
	count_result_slots(P->batch, &creates, &subs);
	XtkBatchResult *result = xtk_batch_result_create(creates, subs);
	if (!result) return NULL;
	fill_mappings(P, result);
	return result;
}

XtkBatchResult *retained_host_commit(XtkHost *host, XtkPrepare *prepare, XtkBatchDiag *diagnostic) {
	( void ) host;
	Prepare *P = ( Prepare * ) prepare;
	if (!P) return NULL;

	for (uint32_t i = 0; i < P->batch->count; i++) {
		if (apply_op(P, &P->batch->ops [i])) continue;
		retained_rollback(P);
		retained_diag(diagnostic, XTK_BATCH_ERR_VALIDATION, i);
		retained_prepare_free(P);
		return NULL;
	}

	if (xtk_comp_commit(P->R->comp) != XTK_COMPONENT_OK) {
		retained_rollback(P);
		retained_diag(diagnostic, XTK_BATCH_ERR_VALIDATION, UINT32_MAX);
		retained_prepare_free(P);
		return NULL;
	}

	XtkBatchResult *result = fill_result(P);
	if (!result) {
		retained_rollback(P);
		retained_diag(diagnostic, XTK_BATCH_ERR_OOM, UINT32_MAX);
		retained_prepare_free(P);
		return NULL;
	}

	finish_destroys(P);
	P->R->revision += 1u;
	P->undo_count   = 0u;
	retained_prepare_free(P);
	return result;
}

void retained_host_abort(XtkHost *host, XtkPrepare *prepare) {
	( void ) host;
	Prepare *P = ( Prepare * ) prepare;
	if (!P) return;
	retained_rollback(P);
	retained_prepare_free(P);
}
