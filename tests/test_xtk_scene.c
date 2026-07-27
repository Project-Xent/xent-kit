#include <stdio.h>
#include <string.h>
#include <xtk/xtk_catalog.h>
#include <xtk/xtk_controls.h>
#include <xtk/xtk_scene.h>

#include "xtk_retained.h"

#define EXPECT(cond, msg)              \
	do {                               \
		if (!(cond)) {                 \
			printf("FAIL: %s\n", msg); \
			return 1;                  \
		}                              \
	}                                  \
	while (0)

typedef struct RouteLog {
	XtkEventPhase phases [8];
	XtkCtrl       currents [8];
	uint32_t      count;
} RouteLog;

static uint32_t on_route(void *arg, XtkEvent const *event) {
	RouteLog *log = ( RouteLog * ) arg;
	if (log->count < 8u) {
		log->phases [log->count]   = event->phase;
		log->currents [log->count] = event->current_target;
		log->count++;
	}
	return XTK_EVENT_CONTINUE;
}

static int test_scene_controls_and_invalidation(void) {
	XtkHost *host  = xtk_retained_host_create();
	XtkScene scene = xtk_scene_from_host(host);
	EXPECT(host && scene.host == host, "scene");
	( void ) xtk_retained_take_invalidations(host);

	XtkTxn sb;
	EXPECT(xtk_txn_begin(&scene, &sb), "begin");
	XtkLocalId button = xtk_button_create(
	  &sb, xtk_ref_none(), &(XtkButtonProps) {.set = XTK_BUTTON_ENABLED_MASK, .text = "Go", .enabled = true}
	);
	XtkLocalId label = xtk_text_create(&sb, xtk_ref_local(button), &(XtkTextProps) {.text = "L"});
	EXPECT(button != XTK_LOCAL_INVALID && label != XTK_LOCAL_INVALID, "create");
	XtkBatchResult *result = xtk_txn_commit(&sb, NULL);
	EXPECT(result && result->control_count == 2u, "commit");
	XtkCtrl btn = result->controls [0].control;
	xtk_batch_result_destroy(result);

	uint32_t pending = xtk_retained_take_invalidations(host);
	EXPECT((pending & XTK_INVALIDATE_LAYOUT) != 0u, "create invalidates layout");
	EXPECT((xtk_retained_invalidation(host, btn) & XTK_INVALIDATE_SEMANTICS) != 0u, "button create semantics");

	EXPECT(xtk_button_settext(&scene, btn, "Save", 4u, (XtkChangeStamp) {0}), "set text");
	EXPECT((xtk_retained_invalidation(host, btn) & XTK_INVALIDATE_LAYOUT) != 0u, "text invalidates layout");

	XtkValueView view;
	EXPECT(xtk_control_get(&scene, btn, XTK_PROP_TEXT, &view, NULL), "get");
	EXPECT(view.kind == XTK_VALUE_STRING && view.u.string.len == 4u, "text len");
	EXPECT(memcmp(view.u.string.data, "Save", 4) == 0, "text bytes");

	xtk_retained_host_destroy(host);
	return 0;
}

static int test_capture_bubble_route(void) {
	XtkHost *host  = xtk_retained_host_create();
	XtkScene scene = xtk_scene_from_host(host);
	XtkTxn   sb;
	EXPECT(xtk_txn_begin(&scene, &sb), "begin");
	XtkLocalId parent = xtk_button_create(&sb, xtk_ref_none(), &(XtkButtonProps) {.text = "P"});
	XtkLocalId child  = xtk_button_create(&sb, xtk_ref_local(parent), &(XtkButtonProps) {.text = "C"});
	RouteLog   log    = {0};
	EXPECT(
	  xtk_txn_on(
		&sb, xtk_ref_local(parent), XTK_EVENT_INVOKE, XTK_EVENT_PHASE_MASK_CAPTURE | XTK_EVENT_PHASE_MASK_BUBBLE,
		on_route, &log
	  ) != XTK_SUB_TOKEN_INVALID,
	  "parent sub"
	);
	EXPECT(
	  xtk_txn_on(&sb, xtk_ref_local(child), XTK_EVENT_INVOKE, XTK_EVENT_PHASE_MASK_TARGET, on_route, &log)
		!= XTK_SUB_TOKEN_INVALID,
	  "child sub"
	);
	XtkBatchResult *result = xtk_txn_commit(&sb, NULL);
	EXPECT(result && result->control_count == 2u, "commit");
	XtkCtrl parent_c = result->controls [0].control;
	XtkCtrl child_c  = result->controls [1].control;
	xtk_batch_result_destroy(result);

	XtkEvent event = {
	  .id     = XTK_EVENT_INVOKE,
	  .target = child_c,
	  .cause  = XTK_EVENT_CAUSE_USER,
	  .change = {0},
	};
	uint32_t flags = xtk_retained_route(host, &event);
	EXPECT(log.count == 3u, "capture+target+bubble");
	EXPECT(log.phases [0] == XTK_EVENT_PHASE_CAPTURE && log.currents [0] == parent_c, "capture parent");
	EXPECT(log.phases [1] == XTK_EVENT_PHASE_TARGET && log.currents [1] == child_c, "target child");
	EXPECT(log.phases [2] == XTK_EVENT_PHASE_BUBBLE && log.currents [2] == parent_c, "bubble parent");
	EXPECT(event.scene_revision == xtk_scene_revision(&scene), "revision stamped");
	( void ) flags;

	EXPECT(xtk_retained_set_focus(host, child_c), "focus");
	EXPECT(xtk_retained_focus(host) == child_c, "focus query");

	xtk_retained_host_destroy(host);
	return 0;
}

int main(void) {
	if (test_scene_controls_and_invalidation()) return 1;
	if (test_capture_bubble_route()) return 1;
	printf("PASS: scene / controls / routing / invalidation\n");
	return 0;
}
