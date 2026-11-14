#include "xtk_encode.h"
#include "../xtk_internal.h"
#include "../runtime/xtk_rt_internal.h"
#include "../reconcile/xtk_reconcile_internal.h"
#include <xtk/xtk_catalog.h>
#include <xtk/xtk_event.h>

#include <stddef.h>
#include <string.h>

typedef struct XtkBindingSpec {
	XtkCtrlType type;
	size_t      detail_size;
	size_t      detail_offset;
	XtkEventId  event;
} XtkBindingSpec;

#define BIND(type_, desc_, field_, event_) {type_, sizeof(desc_), offsetof(desc_, field_), event_}

static XtkMsg *binding_msg(XtkBinding *binding, XtkEventId event) {
	if (!binding || event == 0 || event >= ( XtkEventId ) XTK_EVENT_STANDARD_COUNT) return NULL;
	return &binding->msgs [event];
}

static XtkMsg const *binding_msg_const(XtkBinding const *binding, XtkEventId event) {
	return binding_msg(( XtkBinding * ) binding, event);
}

static XtkBindingSpec const binding_specs [] = {
  BIND(XTK_CTRL_BUTTON, XtkButtonDesc, click, XTK_EVENT_INVOKE),
  BIND(XTK_CTRL_REPEAT, XtkButtonDesc, click, XTK_EVENT_INVOKE),
  BIND(XTK_CTRL_LINK, XtkHyperlinkDesc, click, XTK_EVENT_INVOKE),
  BIND(XTK_CTRL_CHECKBOX, XtkToggleDesc, change, XTK_EVENT_CHANGE_BOOL),
  BIND(XTK_CTRL_CHECKBOX, XtkToggleDesc, change_state, XTK_EVENT_CHANGE_I32),
  BIND(XTK_CTRL_RADIO, XtkToggleDesc, change, XTK_EVENT_CHANGE_BOOL),
  BIND(XTK_CTRL_SWITCH, XtkToggleDesc, change, XTK_EVENT_CHANGE_BOOL),
  BIND(XTK_CTRL_SLIDER, XtkSliderDesc, change, XTK_EVENT_CHANGE_F32),
  BIND(XTK_CTRL_SLIDER, XtkSliderDesc, change_range, XTK_EVENT_CHANGE_RANGE),
  BIND(XTK_CTRL_SCROLLBAR, XtkScrollBarDesc, change, XTK_EVENT_CHANGE_F64),
  BIND(XTK_CTRL_SCROLL, XtkScrollDetail, scroll.scroll, XTK_EVENT_SCROLL),
  BIND(XTK_CTRL_TEXTBOX, XtkTextBoxDesc, change, XTK_EVENT_CHANGE_STRING),
  BIND(XTK_CTRL_PASSWORD, XtkTextBoxDesc, change, XTK_EVENT_CHANGE_STRING),
  BIND(XTK_CTRL_LIST, XtkListDesc, select, XTK_EVENT_SELECT),
  BIND(XTK_CTRL_LIST, XtkListDesc, invoke, XTK_EVENT_INVOKE),
  BIND(XTK_CTRL_LISTBOX, XtkListDesc, select, XTK_EVENT_SELECT),
  BIND(XTK_CTRL_LISTBOX, XtkListDesc, invoke, XTK_EVENT_INVOKE),
  BIND(XTK_CTRL_GRIDVIEW, XtkListDesc, select, XTK_EVENT_SELECT),
  BIND(XTK_CTRL_GRIDVIEW, XtkListDesc, invoke, XTK_EVENT_INVOKE),
  BIND(XTK_CTRL_REPEATER, XtkListDesc, select, XTK_EVENT_SELECT),
  BIND(XTK_CTRL_REPEATER, XtkListDesc, invoke, XTK_EVENT_INVOKE),
  BIND(XTK_CTRL_ITEMSVIEW, XtkItemsViewDesc, select, XTK_EVENT_SELECT),
  BIND(XTK_CTRL_ITEMSVIEW, XtkItemsViewDesc, invoke, XTK_EVENT_INVOKE),
  BIND(XTK_CTRL_EXPANDER, XtkExpanderDesc, toggle, XTK_EVENT_TOGGLE),
  BIND(XTK_CTRL_INFOBAR, XtkInfoBarDesc, close, XTK_EVENT_CLOSE),
  BIND(XTK_CTRL_REFRESH, XtkRefreshDesc, on_refresh, XTK_EVENT_REFRESH),
  BIND(XTK_CTRL_RADIOGROUP, XtkRadioButtonsDesc, select, XTK_EVENT_SELECT),
  BIND(XTK_CTRL_COMBO, XtkComboDesc, select, XTK_EVENT_SELECT),
  BIND(XTK_CTRL_COMBO, XtkComboDesc, submit, XTK_EVENT_SUBMIT_STRING),
  BIND(XTK_CTRL_LOOPING, XtkLoopingDesc, select, XTK_EVENT_SELECT),
  BIND(XTK_CTRL_DATEPICKER, XtkDatePickerDesc, change, XTK_EVENT_VALUE_CHANGED),
  BIND(XTK_CTRL_TIMEPICKER, XtkTimePickerDesc, change, XTK_EVENT_VALUE_CHANGED),
  BIND(XTK_CTRL_CALENDAR, XtkCalendarDesc, select, XTK_EVENT_DATE_SELECT),
  BIND(XTK_CTRL_COLORPICKER, XtkColorPickerDesc, change, XTK_EVENT_VALUE_CHANGED),
  BIND(XTK_CTRL_SPLIT, XtkSplitDesc, click, XTK_EVENT_INVOKE),
  BIND(XTK_CTRL_TOGGLESPLIT, XtkSplitDesc, click, XTK_EVENT_INVOKE),
  BIND(XTK_CTRL_TOGGLESPLIT, XtkSplitDesc, toggle, XTK_EVENT_CHANGE_BOOL),
  BIND(XTK_CTRL_TABS, XtkTabViewDesc, select, XTK_EVENT_SELECT),
  BIND(XTK_CTRL_TABS, XtkTabViewDesc, close, XTK_EVENT_CLOSE),
  BIND(XTK_CTRL_TABS, XtkTabViewDesc, add, XTK_EVENT_INVOKE),
  BIND(XTK_CTRL_DIALOG, XtkDialogDesc, result, XTK_EVENT_CLOSE),
  BIND(XTK_CTRL_NAV, XtkNavDesc, select, XTK_EVENT_SELECT),
  BIND(XTK_CTRL_FLIP, XtkFlipDesc, select, XTK_EVENT_SELECT),
  BIND(XTK_CTRL_PIPS, XtkPipsDesc, select, XTK_EVENT_SELECT),
  BIND(XTK_CTRL_PAGER, XtkPagerDesc, select, XTK_EVENT_SELECT),
  BIND(XTK_CTRL_NUMBER, XtkNumberDesc, change, XTK_EVENT_CHANGE_F64),
  BIND(XTK_CTRL_RATING, XtkRatingDesc, change, XTK_EVENT_RATING_CHANGED),
  BIND(XTK_CTRL_SELECTOR, XtkSelectorBarDesc, select, XTK_EVENT_SELECT),
  BIND(XTK_CTRL_BREADCRUMB, XtkBreadcrumbDesc, click, XTK_EVENT_SELECT),
  BIND(XTK_CTRL_TEACHTIP, XtkTeachingTipDesc, on_action, XTK_EVENT_INVOKE),
  BIND(XTK_CTRL_TEACHTIP, XtkTeachingTipDesc, close, XTK_EVENT_CLOSE),
  BIND(XTK_CTRL_TREE, XtkTreeDesc, invoke, XTK_EVENT_INVOKE),
  BIND(XTK_CTRL_TREE, XtkTreeDesc, expand, XTK_EVENT_TREE_EXPAND),
  BIND(XTK_CTRL_TREE, XtkTreeDesc, select, XTK_EVENT_TREE_SELECT),
  BIND(XTK_CTRL_TITLEBAR, XtkTitleBarDesc, on_back, XTK_EVENT_INVOKE),
  BIND(XTK_CTRL_TITLEBAR, XtkTitleBarDesc, on_pane_toggle, XTK_EVENT_TOGGLE),
  BIND(XTK_CTRL_MENUITEM, XtkMenuItemDetail, click, XTK_EVENT_INVOKE),
  BIND(XTK_CTRL_SUGGEST, XtkAutoSuggestDesc, on_text, XTK_EVENT_CHANGE_STRING),
  BIND(XTK_CTRL_SUGGEST, XtkAutoSuggestDesc, query, XTK_EVENT_QUERY),
  BIND(XTK_CTRL_SUGGEST, XtkAutoSuggestDesc, on_chosen, XTK_EVENT_SELECT),
};

static void binding_load_spec(XtkBinding *binding, XtkEl const *el, XtkBindingSpec const *spec) {
	if (XTK_EL_DATA(el)->type != spec->type) return;
	char const *detail = ( char const * ) xtk_el_detail(el, spec->detail_size);
	if (!detail) return;
	XtkMsg *msg = binding_msg(binding, spec->event);
	if (msg) memcpy(msg, detail + spec->detail_offset, sizeof(*msg));
}

void xtk_binding_load_msgs(XtkBinding *binding, XtkEl const *el) {
	*binding = (XtkBinding) {
	  .rt = binding->rt, .realized = binding->realized, .echo = binding->echo, .user_events = binding->user_events};
	for (size_t i = 0; i < sizeof(binding_specs) / sizeof(binding_specs [0]); i++)
		binding_load_spec(binding, el, &binding_specs [i]);
}

bool xtk_el_needs_binding(XtkEl const *el) {
	if (!el) return false;
	if (XTK_EL_DATA(el)->virtualized) return true;
	XtkBinding tmp = {0};
	xtk_binding_load_msgs(&tmp, el);
	for (XtkEventId event = 1; event < ( XtkEventId ) XTK_EVENT_STANDARD_COUNT; event++) {
		XtkMsg const *msg = binding_msg_const(&tmp, event);
		if (msg && msg->tag) return true;
	}
	return false;
}

static bool msg_equal(XtkMsg const *a, XtkMsg const *b) {
	return a->tag == b->tag && a->i == b->i && a->f == b->f && a->d == b->d && a->b == b->b && a->ptr == b->ptr;
}

bool xtk_binding_msgs_equal(XtkBinding const *a, XtkEl const *el) {
	XtkBinding b = {0};
	xtk_binding_load_msgs(&b, el);
	for (XtkEventId event = 1; event < ( XtkEventId ) XTK_EVENT_STANDARD_COUNT; event++) {
		XtkMsg const *old  = binding_msg_const(a, event);
		XtkMsg const *next = binding_msg_const(&b, event);
		if (old && next && !msg_equal(old, next)) return false;
	}
	return true;
}

static XtkMsg msg_from_pair(XtkMsg msg, XtkEvent const *event) {
	switch (event->payload.kind) {
	case XTK_EVENT_PAYLOAD_QUERY :
		msg.ptr = ( void * ) event->payload.u.query.text;
		msg.i   = event->payload.u.query.index;
		break;
	case XTK_EVENT_PAYLOAD_RATING :
		msg.d = event->payload.u.rating.value;
		msg.i = event->payload.u.rating.count;
		break;
	case XTK_EVENT_PAYLOAD_INDEX_BOOL :
		msg.i = event->payload.u.index_bool.index;
		msg.b = event->payload.u.index_bool.value;
		break;
	case XTK_EVENT_PAYLOAD_RANGE :
		msg.f = event->payload.u.range.start;
		msg.d = event->payload.u.range.end;
		break;
	case XTK_EVENT_PAYLOAD_SCROLL :
		msg.f = event->payload.u.scroll.y;
		msg.d = event->payload.u.scroll.max_y;
		msg.b = event->payload.u.scroll.y >= event->payload.u.scroll.max_y - 1.0f;
		break;
	default : break;
	}
	return msg;
}

static XtkMsg msg_from_event(XtkMsg base, XtkEvent const *event) {
	XtkMsg msg = base;
	switch (event->payload.kind) {
	case XTK_EVENT_PAYLOAD_BOOL   : msg.b = event->payload.u.b; break;
	case XTK_EVENT_PAYLOAD_F32    : msg.f = event->payload.u.f32; break;
	case XTK_EVENT_PAYLOAD_F64    : msg.d = event->payload.u.f64; break;
	case XTK_EVENT_PAYLOAD_I32    : msg.i = event->payload.u.i32; break;
	case XTK_EVENT_PAYLOAD_STRING : msg.ptr = ( void * ) event->payload.u.string.data; break;
	default                       : msg = msg_from_pair(msg, event); break;
	}
	return msg;
}

static uint32_t realize(XtkBinding *b, XtkEvent const *event) {
	b->realized
	  = (XtkRealized) {event->payload.u.window.first, event->payload.u.window.last, event->payload.u.window.lanes};
	xtk_rt_invalidate(b->rt);
	return XTK_EVENT_HANDLED;
}

static void note_user(XtkBinding *b, XtkEvent const *event) {
	if (event->change.revision > b->echo.revision) b->echo = event->change;
	if (event->cause == XTK_EVENT_CAUSE_USER) b->user_events |= 1u << event->id;
}

static void post_msg(XtkRt *rt, XtkMsg msg, XtkEventPayload const *p) {
	if (p->kind == XTK_EVENT_PAYLOAD_STRING) ( void ) xtk_rt_poststring(rt, msg, p->u.string.data, p->u.string.len);
	else if (p->kind == XTK_EVENT_PAYLOAD_QUERY) ( void ) xtk_rt_poststring(rt, msg, p->u.query.text, p->u.query.len);
	else ( void ) xtk_rt_post(rt, msg);
}

static uint32_t trampoline(void *arg, XtkEvent const *event) {
	XtkBinding *b = ( XtkBinding * ) arg;
	if (!b || !b->rt || !event) return XTK_EVENT_CONTINUE;
	if (event->id == XTK_EVENT_REALIZE) return realize(b, event);
	note_user(b, event);
	XtkMsg const *bound = binding_msg_const(b, event->id);
	if (!bound || bound->tag == 0) return XTK_EVENT_CONTINUE;
	post_msg(b->rt, msg_from_event(*bound, event), &event->payload);
	return XTK_EVENT_HANDLED;
}

static bool subscribe_one(XtkBatch *batch, XtkNodeRef target, XtkEventId event, XtkMsg msg, XtkBinding *binding) {
	if (msg.tag == 0) return true;
	return xtk_batch_on(batch, target, event, XTK_EVENT_PHASE_MASK_TARGET, trampoline, binding)
	    != XTK_SUB_TOKEN_INVALID;
}

bool xtk_encode_subscribe(XtkBatch *batch, XtkNodeRef target, XtkBinding *binding, XtkEl const *el) {
	xtk_binding_load_msgs(binding, el);
	for (XtkEventId event = 1; event < ( XtkEventId ) XTK_EVENT_STANDARD_COUNT; event++) {
		XtkMsg const *msg = binding_msg_const(binding, event);
		if (msg && !subscribe_one(batch, target, event, *msg, binding)) return false;
	}
	if (!XTK_EL_DATA(el)->virtualized) return true;
	return xtk_batch_on(batch, target, XTK_EVENT_REALIZE, XTK_EVENT_PHASE_MASK_TARGET, trampoline, binding)
	    != XTK_SUB_TOKEN_INVALID;
}

bool xtk_encode_unsubscribe_all(XtkBatch *batch, XtkNode const *node) {
	for (int i = 0; i < node->sub_count; i++) {
		if (node->sub_ids [i] == XTK_SUBSCRIPTION_INVALID) continue;
		if (!xtk_batch_off(batch, node->sub_ids [i])) return false;
	}
	return true;
}
