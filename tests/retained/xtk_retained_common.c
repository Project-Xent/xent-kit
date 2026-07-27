#include "xtk_retained_internal.h"

bool retained_undo_push(Prepare *P, Undo u) {
	if (P->undo_count == P->undo_cap) {
		uint32_t cap = P->undo_cap ? P->undo_cap * 2u : 16u;
		Undo    *n   = ( Undo * ) xtk_alloc_resize(P->undos, sizeof(*n) * cap);
		if (!n) return false;
		P->undos    = n;
		P->undo_cap = cap;
	}
	P->undos [P->undo_count++] = u;
	return true;
}

bool retained_defer_destroy(Prepare *P, XentNodeId node) {
	if (P->destroy_count == P->destroy_cap) {
		uint32_t    cap = P->destroy_cap ? P->destroy_cap * 2u : 8u;
		XentNodeId *n   = ( XentNodeId * ) xtk_alloc_resize(P->deferred_destroy, sizeof(*n) * cap);
		if (!n) return false;
		P->deferred_destroy = n;
		P->destroy_cap      = cap;
	}
	P->deferred_destroy [P->destroy_count++] = node;
	return true;
}

bool retained_resolve_ref(Prepare const *P, XtkNodeRef ref, bool *ok, XtkCtrl *out) {
	*ok = false;
	if (out) *out = XTK_CTRL_INVALID;
	if (ref.kind == XTK_REF_NONE) {
		*ok = true;
		return true;
	}
	if (ref.kind == XTK_REF_EXISTING) {
		*ok = retained_host_live(P->R, ref.u.existing);
		if (out) *out = ref.u.existing;
		return true;
	}
	if (ref.kind == XTK_REF_LOCAL && ref.u.local < P->local_count && P->locals [ref.u.local] != XTK_CTRL_INVALID) {
		*ok = true;
		if (out) *out = P->locals [ref.u.local];
		return true;
	}
	return true;
}

static void rollback_topo(Retained *R, UndoTopo const *t) {
	if (t->old_parent == XENT_NODE_INVALID) {
		XentNodeId parent = xent_node_parent(R->ctx, t->child);
		if (parent != XENT_NODE_INVALID) xent_node_remove(R->ctx, parent, t->child);
		return;
	}
	xent_node_reparent(R->ctx, t->old_parent, t->child, t->old_next);
}

static void rollback_one(Retained *R, Undo *u) {
	if (u->kind == UNDO_CREATE) {
		retained_purge_subtree_sidecar(R, u->u.created);
		xent_node_destroy(R->ctx, u->u.created);
		return;
	}
	if (u->kind == UNDO_PROP) {
		retained_rollback_prop(R, &u->u.prop);
		return;
	}
	if (u->kind == UNDO_TOPO) {
		rollback_topo(R, &u->u.topo);
		return;
	}
	if (u->kind == UNDO_SUB) retained_rollback_sub(R, &u->u.sub);
}

void retained_rollback(Prepare *P) {
	xtk_comp_abort(P->R->comp);
	for (uint32_t i = P->undo_count; i > 0u;) rollback_one(P->R, &P->undos [--i]);
	P->undo_count = 0u;
}

void retained_prepare_free(Prepare *P) {
	if (!P) return;
	xtk_alloc_free(P->locals);
	xtk_alloc_free(P->undos);
	xtk_alloc_free(P->deferred_destroy);
	xtk_alloc_free(P->sub_ids);
	xtk_alloc_free(P);
}

XtkBatchError retained_diag(XtkBatchDiag *d, XtkBatchError err, uint32_t op) {
	if (d) {
		d->error     = err;
		d->failed_op = op;
	}
	return err;
}
