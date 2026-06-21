#include "xtk_internal.h"

#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define XTK_FIRST_CHUNK (256u * 1024u)

XtkArena *xtk_ui_arena(XtkUi *ui) { return &ui->arenas [ui->current]; }

XtkUi    *xtk_ui_create(void) {
	XtkUi *ui = ( XtkUi * ) calloc(1, sizeof(*ui));
	if (!ui) return NULL;
	if (!xtk_arena_init(&ui->arenas [0], XTK_FIRST_CHUNK) || !xtk_arena_init(&ui->arenas [1], XTK_FIRST_CHUNK)) {
		xtk_arena_dispose(&ui->arenas [0]);
		xtk_arena_dispose(&ui->arenas [1]);
		free(ui);
		return NULL;
	}
	return ui;
}

void xtk_ui_destroy(XtkUi *ui) {
	if (!ui) return;
	xtk_arena_dispose(&ui->arenas [0]);
	xtk_arena_dispose(&ui->arenas [1]);
	free(ui);
}

/* Flip arenas: the previous frame's tree must outlive this frame's build so
 * the reconciler can diff against it. */
void xtk_ui_begin(XtkUi *ui) {
	ui->current ^= 1;
	xtk_arena_reset(xtk_ui_arena(ui));
}

char *xtk_strdup(XtkUi *ui, char const *s) {
	if (!s) return NULL;
	size_t len  = strlen(s) + 1;
	char  *copy = ( char * ) xtk_arena_alloc(xtk_ui_arena(ui), len);
	if (copy) memcpy(copy, s, len);
	return copy;
}

char *xtk_fmt(XtkUi *ui, char const *fmt, ...) {
	va_list args;
	va_start(args, fmt);
	int len = vsnprintf(NULL, 0, fmt, args);
	va_end(args);
	if (len < 0) return NULL;

	char *s = ( char * ) xtk_arena_alloc(xtk_ui_arena(ui), ( size_t ) len + 1);
	if (!s) return NULL;

	va_start(args, fmt);
	vsnprintf(s, ( size_t ) len + 1, fmt, args);
	va_end(args);
	return s;
}

XtkEl *xtk_el_new(XtkUi *ui, XtkControlType type, char const *text) {
	XtkEl *el = ( XtkEl * ) xtk_arena_alloc(xtk_ui_arena(ui), sizeof(*el));
	if (!el) return NULL;
	el->type   = type;
	el->width  = NAN;
	el->height = NAN;
	el->text   = xtk_strdup(ui, text);
	return el;
}

static XtkEl xtk_end_sentinel;
XtkEl *const XTK_END = &xtk_end_sentinel;

/* Children arrive as an XTK_END-terminated compound literal; NULL entries are
 * skipped (conditional rendering) and the survivors are copied into a dense
 * arena array. */
void         xtk_el_adopt(XtkUi *ui, XtkEl *el, XtkEl *children []) {
	if (!el || !children) return;

	int count = 0;
	for (XtkEl **c = children; *c != XTK_END; c++)
		if (*c) count++;

	el->children = ( XtkEl ** ) xtk_arena_alloc(xtk_ui_arena(ui), sizeof(XtkEl *) * ( size_t ) (count ? count : 1));
	if (!el->children) return;

	int i = 0;
	for (XtkEl **c = children; *c != XTK_END; c++)
		if (*c) el->children [i++] = *c;
	el->child_count = count;
}

XtkEl *xtk_text(XtkUi *ui, char const *content, XtkTextDesc desc) {
	XtkEl *el = xtk_el_new(ui, XTK_CONTROL_TEXT, content);
	if (el) el->text_props = desc;
	return el;
}

XtkEl *xtk_button(XtkUi *ui, char const *label, XtkButtonDesc desc) {
	XtkEl *el = xtk_el_new(ui, XTK_CONTROL_BUTTON, label);
	if (!el) return NULL;
	desc.icon  = xtk_strdup(ui, desc.icon);
	el->button = desc;
	return el;
}

static XtkEl *xtk_toggle(XtkUi *ui, XtkControlType type, char const *label, XtkToggleDesc desc) {
	XtkEl *el = xtk_el_new(ui, type, label);
	if (el) el->toggle = desc;
	return el;
}

XtkEl *xtk_checkbox(XtkUi *ui, char const *label, XtkToggleDesc desc) {
	return xtk_toggle(ui, XTK_CONTROL_CHECKBOX, label, desc);
}

XtkEl *xtk_radio(XtkUi *ui, char const *label, XtkToggleDesc desc) {
	return xtk_toggle(ui, XTK_CONTROL_RADIO, label, desc);
}

XtkEl *xtk_switch(XtkUi *ui, XtkToggleDesc desc) { return xtk_toggle(ui, XTK_CONTROL_SWITCH, NULL, desc); }

XtkEl *xtk_slider(XtkUi *ui, XtkSliderDesc desc) {
	XtkEl *el = xtk_el_new(ui, XTK_CONTROL_SLIDER, NULL);
	if (!el) return NULL;
	if (desc.max == 0.0f && desc.min == 0.0f) desc.max = 100.0f;
	if (desc.step == 0.0f) desc.step = 1.0f;
	if (desc.small_change == 0.0f) desc.small_change = 1.0f;
	if (desc.large_change == 0.0f) desc.large_change = 10.0f;
	el->slider = desc;
	return el;
}

static XtkEl *xtk_text_input(XtkUi *ui, XtkControlType type, char const *placeholder, XtkTextBoxDesc desc) {
	XtkEl *el = xtk_el_new(ui, type, placeholder);
	if (!el) return NULL;
	desc.content = xtk_strdup(ui, desc.content);
	el->textbox  = desc;
	return el;
}

XtkEl *xtk_textbox(XtkUi *ui, char const *placeholder, XtkTextBoxDesc desc) {
	return xtk_text_input(ui, XTK_CONTROL_TEXT_INPUT, placeholder, desc);
}

XtkEl *xtk_password(XtkUi *ui, char const *placeholder, XtkTextBoxDesc desc) {
	return xtk_text_input(ui, XTK_CONTROL_PASSWORD_BOX, placeholder, desc);
}

static XtkEl *xtk_progress_el(XtkUi *ui, XtkControlType type, XtkProgressDesc desc) {
	XtkEl *el = xtk_el_new(ui, type, NULL);
	if (!el) return NULL;
	if (desc.max == 0.0f) desc.max = 100.0f;
	el->progress = desc;
	return el;
}

XtkEl *xtk_progress(XtkUi *ui, XtkProgressDesc desc) { return xtk_progress_el(ui, XTK_CONTROL_PROGRESS, desc); }

XtkEl *xtk_progress_ring(XtkUi *ui, XtkProgressDesc desc) {
	return xtk_progress_el(ui, XTK_CONTROL_PROGRESS_RING, desc);
}

XtkEl *xtk_badge(XtkUi *ui, XtkBadgeDesc desc) {
	XtkEl *el = xtk_el_new(ui, XTK_CONTROL_INFO_BADGE, NULL);
	if (!el) return NULL;
	desc.icon = xtk_strdup(ui, desc.icon);
	el->badge = desc;
	return el;
}

XtkEl *xtk_image(XtkUi *ui, char const *source, XtkImageDesc desc) {
	XtkEl *el = xtk_el_new(ui, XTK_CONTROL_IMAGE, source);
	if (el) el->image = desc;
	return el;
}

XtkEl *xtk_hyperlink(XtkUi *ui, char const *label, XtkHyperlinkDesc desc) {
	XtkEl *el = xtk_el_new(ui, XTK_CONTROL_HYPERLINK, label);
	if (!el) return NULL;
	desc.url      = xtk_strdup(ui, desc.url);
	el->hyperlink = desc;
	return el;
}

XtkEl *xtk_divider(XtkUi *ui) { return xtk_el_new(ui, XTK_CONTROL_DIVIDER, NULL); }

XtkEl *xtk_repeat_button(XtkUi *ui, char const *label, XtkButtonDesc desc) {
	XtkEl *el = xtk_el_new(ui, XTK_CONTROL_REPEAT_BUTTON, label);
	if (!el) return NULL;
	desc.icon  = xtk_strdup(ui, desc.icon);
	el->button = desc;
	return el;
}

XtkEl *xtk_info_bar(XtkUi *ui, char const *title, char const *message, XtkInfoBarDesc desc) {
	XtkEl *el = xtk_el_new(ui, XTK_CONTROL_INFO_BAR, title);
	if (!el) return NULL;
	desc.message = xtk_strdup(ui, message);
	el->info_bar = desc;
	return el;
}

XtkEl *xtk_tooltip(XtkUi *ui, XtkEl *el, char const *text) {
	if (el) el->tooltip = xtk_strdup(ui, text);
	return el;
}

XtkEl *xtk_spacer(XtkUi *ui) {
	XtkEl *el = xtk_el_new(ui, XTK_CONTROL_CONTAINER, NULL);
	if (el) el->grow = 1.0f;
	return el;
}

XtkEl **xtk_children_alloc(XtkUi *ui, int capacity) {
	if (capacity < 0) capacity = 0;
	XtkEl **buf = ( XtkEl ** ) xtk_arena_alloc(xtk_ui_arena(ui), sizeof(XtkEl *) * (( size_t ) capacity + 1));
	if (buf) buf [capacity] = XTK_END;
	return buf;
}

XtkEl *xtk_keyed(XtkUi *ui, char const *key, XtkEl *el) {
	if (el) el->key = xtk_strdup(ui, key);
	return el;
}

XtkEl *xtk_sized(XtkEl *el, float width, float height) {
	if (!el) return NULL;
	el->width  = width;
	el->height = height;
	return el;
}

XtkEl *xtk_grow(XtkEl *el, float grow) {
	if (el) el->grow = grow;
	return el;
}

XtkEl *xtk_align(XtkEl *el, XentFlexAlign align_self) {
	if (el) el->align_self = align_self;
	return el;
}

XtkEl *xtk_margin(XtkEl *el, XentInsets margin) {
	if (el) el->margin = margin;
	return el;
}
