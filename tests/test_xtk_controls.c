#include <stdio.h>
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

static int test_catalog_create_coverage(void) {
	XtkHost *host  = xtk_retained_host_create();
	XtkScene scene = xtk_scene_from_host(host);
	EXPECT(host, "host");

	XtkTxn sb;
	EXPECT(xtk_txn_begin(&scene, &sb), "begin");

	EXPECT(xtk_container_create(&sb, xtk_ref_none(), NULL) != XTK_LOCAL_INVALID, "container");
	EXPECT(
	  xtk_button_create(
		&sb, xtk_ref_none(), &(XtkButtonProps) {.set = XTK_BUTTON_ENABLED_MASK, .text = "Go", .enabled = true}
	  ) != XTK_LOCAL_INVALID,
	  "button"
	);
	EXPECT(
	  xtk_slider_create(&sb, xtk_ref_none(), &(XtkSliderProps) {.set = XTK_SLIDER_VALUE_MASK, .value = 0.5f})
		!= XTK_LOCAL_INVALID,
	  "slider"
	);
	EXPECT(
	  xtk_list_create(&sb, xtk_ref_none(), &(XtkListProps) {.set = XTK_LIST_NITEM_MASK, .nitem = 3})
		!= XTK_LOCAL_INVALID,
	  "list"
	);
	EXPECT(xtk_nav_create(&sb, xtk_ref_none(), NULL) != XTK_LOCAL_INVALID, "nav_view");
	EXPECT(xtk_titlebar_create(&sb, xtk_ref_none(), NULL) != XTK_LOCAL_INVALID, "title_bar");
	EXPECT(xtk_divider_create(&sb, xtk_ref_none(), NULL) != XTK_LOCAL_INVALID, "divider");

	XtkBatchResult *result = xtk_txn_commit(&sb, NULL);
	EXPECT(result && result->control_count == 7u, "commit");
	xtk_batch_result_destroy(result);
	xtk_retained_host_destroy(host);
	return 0;
}

static uint32_t noop_event(void *arg, XtkEvent const *event) {
	( void ) arg;
	( void ) event;
	return XTK_EVENT_CONTINUE;
}

static int test_setter_and_event_symbols(void) {
	XtkHost *host  = xtk_retained_host_create();
	XtkScene scene = xtk_scene_from_host(host);
	XtkTxn   sb;
	EXPECT(xtk_txn_begin(&scene, &sb), "begin");
	XtkLocalId local = xtk_checkbox_create(
	  &sb, xtk_ref_none(), &(XtkToggleProps) {.set = XTK_TOGGLE_CHECKED_MASK, .text = "x", .checked = true}
	);
	EXPECT(local != XTK_LOCAL_INVALID, "checkbox");
	EXPECT(xtk_checkbox_onchange(&sb, xtk_ref_local(local), noop_event, NULL) != XTK_SUB_TOKEN_INVALID, "change");
	XtkBatchResult *result = xtk_txn_commit(&sb, NULL);
	EXPECT(result, "commit");
	XtkCtrl box = result->controls [0].control;
	xtk_batch_result_destroy(result);

	EXPECT(xtk_checkbox_setchecked(&scene, box, false, (XtkChangeStamp) {0}), "set checked");
	EXPECT(xtk_text_settext(&scene, box, "y", 1u, (XtkChangeStamp) {0}), "text_set_content alias");

	xtk_retained_host_destroy(host);
	return 0;
}

static int test_standard_control_count(void) {
	uint32_t n = 0u;
	for (XtkCtrlId id = 1u; id < ( XtkCtrlId ) XTK_CTRL_TYPE_COUNT; id++)
		if (xtk_catalog_control(id)) n += 1u;
	EXPECT(n + 1u == ( uint32_t ) XTK_CTRL_TYPE_COUNT, "catalog covers standard range");
	return 0;
}

int main(void) {
	if (test_standard_control_count()) return 1;
	if (test_catalog_create_coverage()) return 1;
	if (test_setter_and_event_symbols()) return 1;
	printf("PASS: xtk_controls catalog coverage\n");
	return 0;
}
