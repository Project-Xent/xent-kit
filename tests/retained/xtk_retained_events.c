#include "xtk_retained_internal.h"

void retained_clear_control_subs(Retained *R, XtkCtrl control) {
	for (uint32_t i = 0; i < R->sub_count; i++)
		if (R->subs [i].live && R->subs [i].target == control) R->subs [i].live = false;
}

void retained_rollback_sub(Retained *R, UndoSub const *sub) {
	for (uint32_t s = 0; s < R->sub_count; s++) {
		if (R->subs [s].id != sub->id) continue;
		R->subs [s].live = sub->kind == SUB_UNDO_RESTORE;
		return;
	}
}

bool retained_apply_subscribe(Prepare *P, XtkBatchSubscribe const *op) {
	bool    ok     = false;
	XtkCtrl target = XTK_CTRL_INVALID;
	if (!retained_resolve_ref(P, op->target, &ok, &target) || !ok || !retained_host_live(P->R, target)) return false;
	if (op->token >= P->sub_id_count) return false;

	if (P->R->sub_count == P->R->sub_cap) {
		uint32_t  cap = P->R->sub_cap ? P->R->sub_cap * 2u : 8u;
		SubEntry *n   = ( SubEntry * ) xtk_alloc_resize(P->R->subs, sizeof(*n) * cap);
		if (!n) return false;
		P->R->subs    = n;
		P->R->sub_cap = cap;
	}

	XtkSubId id = P->R->next_sub + 1u;
	if (!retained_undo_push(
		  P, (Undo) {
			   .kind = UNDO_SUB, .u.sub = {.id = id, .kind = SUB_UNDO_CANCEL_ADD}
    }
		))
		return false;

	P->R->next_sub                 = id;
	P->R->subs [P->R->sub_count++] = (SubEntry) {
	  .id = id, .target = target, .event = op->event, .phases = op->phases, .fn = op->fn, .arg = op->arg, .live = true};
	P->sub_ids [op->token] = id;
	return true;
}

bool retained_apply_unsubscribe(Prepare *P, XtkSubId id) {
	for (uint32_t i = 0; i < P->R->sub_count; i++) {
		if (!P->R->subs [i].live || P->R->subs [i].id != id) continue;
		if (!retained_undo_push(
			  P, (Undo) {
				   .kind = UNDO_SUB, .u.sub = {.id = id, .kind = SUB_UNDO_RESTORE}
        }
			))
			return false;
		P->R->subs [i].live = false;
		return true;
	}
	return false;
}

static uint32_t phase_mask_bit(XtkEventPhase phase) {
	if (phase == XTK_EVENT_PHASE_CAPTURE) return XTK_EVENT_PHASE_MASK_CAPTURE;
	if (phase == XTK_EVENT_PHASE_BUBBLE) return XTK_EVENT_PHASE_MASK_BUBBLE;
	return XTK_EVENT_PHASE_MASK_TARGET;
}

static bool sub_matches(SubEntry const *s, XtkEvent const *event) {
	if (!s->live || s->target != event->current_target || s->event != event->id) return false;
	return (s->phases & phase_mask_bit(event->phase)) != 0u;
}

static uint32_t invoke_sub(SubEntry const *s, XtkEvent const *event) {
	return s->fn ? s->fn(s->arg, event) : XTK_EVENT_CONTINUE;
}

uint32_t retained_dispatch_at(Retained *R, XtkEvent *event) {
	uint32_t flags = XTK_EVENT_CONTINUE;
	if (R->comp) {
		flags |= xtk_comp_dispatch(R->comp, &R->host, R->ctx, event->current_target, event);
		if (flags & XTK_EVENT_STOP_IMMEDIATE) return flags;
	}
	for (uint32_t i = 0; i < R->sub_count; i++) {
		if (!sub_matches(&R->subs [i], event)) continue;
		uint32_t d  = invoke_sub(&R->subs [i], event);
		flags      |= d;
		if (d & XTK_EVENT_STOP_IMMEDIATE) break;
	}
	return flags;
}

uint32_t retained_host_dispatch(XtkHost *host, XtkEvent const *event) {
	Retained *R = retained_impl(host);
	if (!R || !event) return XTK_EVENT_CONTINUE;
	XtkEvent copy = *event;
	return retained_dispatch_at(R, &copy);
}

static uint32_t ancestor_chain(Retained *R, XtkCtrl target, XtkCtrl *out, uint32_t cap) {
	uint32_t count  = 0u;
	XtkCtrl  cursor = retained_host_parent(&R->host, target);
	while (cursor != XTK_CTRL_INVALID && count < cap) {
		out [count++] = cursor;
		cursor        = retained_host_parent(&R->host, cursor);
	}
	return count;
}

static uint32_t route_capture(Retained *R, XtkEvent *event, XtkCtrl const *chain, uint32_t depth) {
	uint32_t flags = XTK_EVENT_CONTINUE;
	event->phase   = XTK_EVENT_PHASE_CAPTURE;
	for (uint32_t i = depth; i > 0u;) {
		event->current_target  = chain [--i];
		flags                 |= retained_dispatch_at(R, event);
		if (flags & (XTK_EVENT_STOP_PROPAGATION | XTK_EVENT_STOP_IMMEDIATE)) break;
	}
	return flags;
}

static uint32_t route_bubble(Retained *R, XtkEvent *event, XtkCtrl const *chain, uint32_t depth) {
	uint32_t flags = XTK_EVENT_CONTINUE;
	event->phase   = XTK_EVENT_PHASE_BUBBLE;
	for (uint32_t i = 0; i < depth; i++) {
		event->current_target  = chain [i];
		flags                 |= retained_dispatch_at(R, event);
		if (flags & (XTK_EVENT_STOP_PROPAGATION | XTK_EVENT_STOP_IMMEDIATE)) break;
	}
	return flags;
}

uint32_t xtk_retained_route(XtkHost *host, XtkEvent *event) {
	Retained *R = retained_impl(host);
	if (!R || !event || !retained_host_is_live(host, event->target)) return XTK_EVENT_CONTINUE;
	event->scene_revision = R->revision;
	if (event->source == XTK_CTRL_INVALID) event->source = event->target;

	XtkEventDesc const *desc    = xtk_catalog_event(event->id);
	XtkEventRouting     routing = desc ? desc->routing : XTK_EVENT_ROUTE_TARGET;
	XtkCtrl             chain [64];
	uint32_t            depth = ancestor_chain(R, event->target, chain, 64u);
	uint32_t            flags = XTK_EVENT_CONTINUE;

	if (routing == XTK_EVENT_ROUTE_CAPTURE_BUBBLE) {
		flags |= route_capture(R, event, chain, depth);
		if (flags & (XTK_EVENT_STOP_PROPAGATION | XTK_EVENT_STOP_IMMEDIATE)) return flags;
	}

	event->phase           = XTK_EVENT_PHASE_TARGET;
	event->current_target  = event->target;
	flags                 |= retained_dispatch_at(R, event);
	if (flags & (XTK_EVENT_STOP_PROPAGATION | XTK_EVENT_STOP_IMMEDIATE)) return flags;

	if (routing == XTK_EVENT_ROUTE_BUBBLE || routing == XTK_EVENT_ROUTE_CAPTURE_BUBBLE)
		flags |= route_bubble(R, event, chain, depth);
	return flags;
}

bool xtk_retained_set_focus(XtkHost *host, XtkCtrl control) {
	Retained *R = retained_impl(host);
	if (!R) return false;
	if (control != XTK_CTRL_INVALID && !retained_host_is_live(host, control)) return false;
	R->focus = control;
	retained_note_invalidate(R, control, XTK_INVALIDATE_ACCESS | XTK_INVALIDATE_SEMANTICS);
	return true;
}

XtkCtrl xtk_retained_focus(XtkHost const *host) {
	Retained const *R = retained_impl_c(host);
	return R ? R->focus : XTK_CTRL_INVALID;
}
