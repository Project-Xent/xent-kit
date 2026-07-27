/**
 * @file test_xtk_el.c
 * @brief Headless test for the xtk element layer: tree shape, conditional
 * rendering, arena string ownership, zero-value defaults, and frame reuse.
 */
#include <xtk/xtk.h>
#include "../src/xtk_internal.h"
#include <math.h>
#include <stdio.h>
#include <string.h>

enum
{
	MSG_NONE = 0,
	MSG_CLICK,
	MSG_TOGGLE,
};

#define EXPECT(cond, msg)              \
	do {                               \
		if (!(cond)) {                 \
			printf("FAIL: %s\n", msg); \
			return 1;                  \
		}                              \
	}                                  \
	while (0)

static XtkEl *build(XtkUi *ui, bool show_reset, char const *transient) {
	return xtk_scroll(
	  ui, (XtkEl *[]) {
			xtk_column(
			  ui, (XtkStackDesc) {.gap = 12, .padding = {32, 32, 32, 32}},
			  (XtkEl *[]) {
								  xtk_text(ui, transient, (XtkTextDesc) {.size = 24}),
								  xtk_button(ui, "Increment", (XtkButtonDesc) {.click = xtk_msg_i(MSG_CLICK, 7)}),
								  show_reset ? xtk_button(ui, "Reset", (XtkButtonDesc) {.disabled = true}) : NULL,
								  xtk_keyed(
				  ui, "row-1",
								  xtk_row(
					ui, (XtkStackDesc) {.gap = 8},
								  (XtkEl *[]) {
					  xtk_checkbox(ui, "Check", (XtkToggleDesc) {.checked = true, .change = xtk_msg(MSG_TOGGLE)}),
					  xtk_slider(ui, (XtkSliderDesc) {0}), XTK_END}
				  )
				), XTK_END}
			),
			XTK_END
    }
	);
}

int main(void) {
	XtkUi *ui = xtk_ui_create();
	EXPECT(ui, "ui creation");

	xtk_ui_begin(ui);

	char transient [32];
	snprintf(transient, sizeof(transient), "Frame %d", 1);
	XtkEl *root = build(ui, false, transient);
	memset(transient, 'X', sizeof(transient) - 1);

	EXPECT(root && XTK_EL_DATA(root)->type == XTK_CTRL_SCROLL, "root is a scroll");
	EXPECT(XTK_EL_DATA(root)->child_count == 1, "scroll has one child");

	XtkEl *col = xtk_el_child(root, 0);
	EXPECT(XTK_EL_DATA(col)->type == XTK_CTRL_CONTAINER && !XTK_EL_DATA(col)->stack_row, "column container");
	EXPECT(XTK_EL_DATA(col)->child_count == 3, "NULL conditional skipped");
	XtkStackDesc *stack = XTK_EL_DETAIL(col, XtkStackDesc);
	EXPECT(stack->gap == 12.0f && stack->padding.left == 32.0f, "stack desc carried");

	XtkEl *title = xtk_el_child(col, 0);
	EXPECT(strcmp(XTK_EL_DATA(title)->text, "Frame 1") == 0, "string copied into arena, not borrowed");
	EXPECT(XTK_EL_DATA(title)->text != ( char const * ) transient, "arena copy is a distinct pointer");
	EXPECT(XTK_EL_DETAIL(title, XtkTextDesc)->size == 24.0f, "text size carried");
	EXPECT(isnan(XTK_EL_DATA(title)->width) && isnan(XTK_EL_DATA(title)->height), "size defaults to auto");

	XtkEl         *inc    = xtk_el_child(col, 1);
	XtkButtonDesc *button = XTK_EL_DETAIL(inc, XtkButtonDesc);
	EXPECT(XTK_EL_DATA(inc)->type == XTK_CTRL_BUTTON && !button->disabled, "button enabled by default");
	EXPECT(button->click.tag == MSG_CLICK && button->click.i == 7, "message payload carried");

	XtkEl *row = xtk_el_child(col, 2);
	EXPECT(
	  XTK_EL_DATA(row)->key.kind == XTK_KEY_STRING && strcmp(XTK_EL_DATA(row)->key.value.string, "row-1") == 0,
	  "key copied"
	);
	EXPECT(XTK_EL_DATA(row)->stack_row && XTK_EL_DATA(row)->child_count == 2, "row with two children");
	EXPECT(XTK_EL_DETAIL(xtk_el_child(row, 1), XtkSliderDesc)->max == 100.0f, "slider {0} defaults to 0..100");

	XtkEl *again = build(ui, true, "second");
	EXPECT(XTK_EL_DATA(xtk_el_child(again, 0))->child_count == 4, "conditional included when true");

	XtkEl **list = xtk_children_alloc(ui, 8);
	list [0]     = xtk_text(ui, "a", (XtkTextDesc) {0});
	list [5]     = xtk_text(ui, "b", (XtkTextDesc) {0});
	XtkEl *holes = xtk_column(ui, (XtkStackDesc) {0}, list);
	EXPECT(XTK_EL_DATA(holes)->child_count == 2, "children_alloc holes skipped");

	char *fmt = xtk_fmt(ui, "%s-%04d", "id", 42);
	EXPECT(fmt && strcmp(fmt, "id-0042") == 0, "xtk_fmt formats into arena");

	XtkMenuItemDesc menu_items [] = {
	  {.label = "Open",   .icon = "OpenFile", .click = xtk_msg_i(MSG_CLICK, 1)},
	  {.label = "Locked", .disabled = true,   .click = xtk_msg_i(MSG_CLICK, 2)},
	};
	XtkEl *dropdown = xtk_dropdown(ui, "Actions", (XtkDropdownDesc) {.items = menu_items, .nitem = 2});
	XtkEl *fly      = xtk_el_child(dropdown, 0);
	EXPECT(fly && XTK_EL_DATA(fly)->type == XTK_CTRL_MENUFLY, "dropdown retains its menu flyout");
	EXPECT(XTK_EL_DATA(fly)->child_count == 2, "menu flyout retains its items");
	XtkEl *locked = xtk_el_child(fly, 1);
	EXPECT(XTK_EL_DATA(locked)->type == XTK_CTRL_MENUITEM, "menu item control type");
	EXPECT(XTK_EL_DETAIL(locked, XtkMenuItemDetail)->disabled, "menu item disabled state");

	for (int frame = 0; frame < 5000; frame++) {
		xtk_ui_begin(ui);
		XtkEl *r = build(ui, frame & 1, "loop");
		if (!r) return 1;
	}

	xtk_ui_destroy(ui);
	printf("PASS: xtk element layer\n");
	return 0;
}
