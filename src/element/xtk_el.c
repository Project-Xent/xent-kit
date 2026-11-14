#include "xtk_internal.h"
#include <xtk/xtk_alloc.h>

#include <math.h>
#include <limits.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#define XTK_FIRST_CHUNK (256u * 1024u)

static bool grow_capacity(uint32_t current, uint32_t need, uint32_t *out) {
	uint32_t capacity = current ? current : 256u;
	while (capacity < need) {
		if (capacity > UINT32_MAX / 2u) {
			capacity = need;
			break;
		}
		capacity *= 2u;
	}
	*out = capacity;
	return capacity >= need;
}

static bool reserve_elements(XtkComposition *composition, uint32_t need) {
	if (need <= composition->element_capacity) return true;
	uint32_t capacity;
	if (!grow_capacity(composition->element_capacity, need, &capacity)) return false;
	if (( size_t ) capacity > SIZE_MAX / sizeof(*composition->elements)) return false;
	XtkElementData *items = xtk_alloc_resize(composition->elements, sizeof(*items) * capacity);
	if (!items) return false;
	composition->elements         = items;
	composition->element_capacity = capacity;
	return true;
}

static bool reserve_children(XtkComposition *composition, uint32_t need) {
	if (need <= composition->child_capacity) return true;
	uint32_t capacity;
	if (!grow_capacity(composition->child_capacity, need, &capacity)) return false;
	if (( size_t ) capacity > SIZE_MAX / sizeof(*composition->children)) return false;
	uint32_t *items = xtk_alloc_resize(composition->children, sizeof(*items) * capacity);
	if (!items) return false;
	composition->children       = items;
	composition->child_capacity = capacity;
	return true;
}

static bool reserve_details(XtkComposition *composition, uint32_t need) {
	if (need <= composition->detail_capacity) return true;
	uint32_t capacity;
	if (!grow_capacity(composition->detail_capacity, need, &capacity)) return false;
	unsigned char *bytes = xtk_alloc_resize(composition->details, capacity);
	if (!bytes) return false;
	composition->details         = bytes;
	composition->detail_capacity = capacity;
	return true;
}

static void composition_dispose(XtkComposition *composition) {
	xtk_alloc_free(composition->details);
	xtk_alloc_free(composition->children);
	xtk_alloc_free(composition->elements);
}

static void composition_reset(XtkComposition *composition) {
	composition->element_count = 0u;
	composition->child_count   = 0u;
	composition->detail_count  = 0u;
	composition->failed        = false;
}

XtkArena              *xtk_ui_arena(XtkUi *ui) { return &ui->arena; }

static XtkComposition *el_composition(XtkEl const *el) {
	if (!el || !el->ui) return NULL;
	return &el->ui->composition;
}

XtkElementData *xtk_el_data(XtkEl const *el) {
	XtkComposition *composition = el_composition(el);
	if (!composition || el->index >= composition->element_count) return NULL;
	return &composition->elements [el->index];
}

void *xtk_el_detail(XtkEl const *el, size_t size) {
	XtkComposition *composition = el_composition(el);
	XtkElementData *data        = xtk_el_data(el);
	if (!composition || !data || size > data->detail_size) return NULL;
	return composition->details + data->detail_offset;
}

bool xtk_el_detail_set(XtkEl *el, void const *value, size_t size) {
	XtkComposition *composition = el_composition(el);
	XtkElementData *data        = xtk_el_data(el);
	if (!composition || !data || !value || size > UINT32_MAX) return false;
	size_t align = _Alignof(XtkMaxAlign);
	size_t start = (composition->detail_count + align - 1u) & ~(align - 1u);
	if (start > UINT32_MAX || size > UINT32_MAX - start) return false;
	uint32_t end = ( uint32_t ) (start + size);
	if (!reserve_details(composition, end)) {
		composition->failed = true;
		return false;
	}
	memcpy(composition->details + start, value, size);
	data->detail_offset       = ( uint32_t ) start;
	data->detail_size         = ( uint32_t ) size;
	composition->detail_count = end;
	return true;
}

XtkEl *xtk_el_child(XtkEl const *el, int index) {
	XtkComposition *composition = el_composition(el);
	XtkElementData *data        = xtk_el_data(el);
	if (!composition || !data || index < 0 || index >= data->child_count) return NULL;
	uint32_t child = composition->children [data->child_offset + ( uint32_t ) index];
	if (child >= composition->element_count) return NULL;
	return composition->elements [child].handle;
}

bool xtk_el_set_children(XtkEl *el, XtkEl *const children [], int count) {
	XtkComposition *composition = el_composition(el);
	XtkElementData *data        = xtk_el_data(el);
	if (!composition || !data || count < 0 || (count && !children)) return false;
	if (( uint32_t ) count > UINT32_MAX - composition->child_count) {
		composition->failed = true;
		return false;
	}
	uint32_t start = composition->child_count;
	if (!reserve_children(composition, start + ( uint32_t ) count)) {
		composition->failed = true;
		return false;
	}
	for (int i = 0; i < count; i++) {
		XtkEl *child = children [i];
		if (!child || child->ui != el->ui) {
			composition->failed = true;
			return false;
		}
		composition->children [start + ( uint32_t ) i] = child->index;
	}
	composition->child_count = start + ( uint32_t ) count;
	data->child_offset       = start;
	data->child_count        = count;
	return true;
}

bool xtk_ui_failed(XtkUi const *ui) { return !ui || ui->composition.failed; }

void xtk_ui_fail(XtkUi *ui) {
	if (ui) ui->composition.failed = true;
}

XtkUi *xtk_ui_create(void) {
	XtkUi *ui = ( XtkUi * ) xtk_alloc_zero(1, sizeof(*ui));
	if (!ui) return NULL;
	if (!xtk_arena_init(&ui->arena, XTK_FIRST_CHUNK)) {
		xtk_arena_dispose(&ui->arena);
		xtk_alloc_free(ui);
		return NULL;
	}
	return ui;
}

void xtk_ui_destroy(XtkUi *ui) {
	if (!ui) return;
	composition_dispose(&ui->composition);
	xtk_alloc_free(ui->regions);
	xtk_arena_dispose(&ui->arena);
	xtk_alloc_free(ui);
}

void xtk_ui_begin(XtkUi *ui) {
	if (!ui) return;
	xtk_arena_reset(&ui->arena);
	composition_reset(&ui->composition);
}

void xtk_ui_abort_candidate(XtkUi *ui) {
	if (!ui) return;
	xtk_arena_reset(&ui->arena);
	composition_reset(&ui->composition);
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

XtkEl *xtk_el_new(XtkUi *ui, XtkCtrlId type, char const *text) {
	if (!ui) return NULL;
	XtkComposition *composition = &ui->composition;
	if (!reserve_elements(composition, composition->element_count + 1u)) {
		composition->failed = true;
		return NULL;
	}
	XtkEl *el = ( XtkEl * ) xtk_arena_alloc(xtk_ui_arena(ui), sizeof(*el));
	if (!el) {
		composition->failed = true;
		return NULL;
	}
	uint32_t index       = composition->element_count++;
	*el                  = (XtkEl) {.ui = ui, .index = index};
	XtkElementData *data = &composition->elements [index];
	*data                = (XtkElementData) {.handle = el, .type = type, .width = NAN, .height = NAN};
	data->text           = xtk_strdup(ui, text);
	if (text && !data->text) {
		composition->failed = true;
		return NULL;
	}
	return el;
}

void xtk_el_adopt(XtkUi *ui, XtkEl *el, XtkEl *children []) {
	if (!el || !children) return;

	int count = 0;
	for (XtkEl **c = children; *c != XTK_END; c++)
		if (*c) count++;

	XtkEl **dense = ( XtkEl ** ) xtk_arena_alloc(xtk_ui_arena(ui), sizeof(*dense) * ( size_t ) (count ? count : 1));
	if (!dense) {
		ui->composition.failed = true;
		return;
	}
	int i = 0;
	for (XtkEl **c = children; *c != XTK_END; c++)
		if (*c) dense [i++] = *c;
	( void ) xtk_el_set_children(el, dense, count);
}

XtkEl *xtk_text(XtkUi *ui, char const *content, XtkTextDesc desc) {
	XtkEl *el = xtk_el_new(ui, XTK_CTRL_TEXT, content);
	if (el && !XTK_EL_STORE(el, desc)) return NULL;
	return el;
}

XtkEl *xtk_button(XtkUi *ui, char const *label, XtkButtonDesc desc) {
	XtkEl *el = xtk_el_new(ui, XTK_CTRL_BUTTON, label);
	if (!el) return NULL;
	desc.icon = xtk_strdup(ui, desc.icon);
	if (!XTK_EL_STORE(el, desc)) return NULL;
	return el;
}

static XtkEl *toggle(XtkUi *ui, XtkCtrlType type, char const *label, XtkToggleDesc desc) {
	XtkEl *el = xtk_el_new(ui, type, label);
	if (el && !XTK_EL_STORE(el, desc)) return NULL;
	return el;
}

XtkEl *xtk_checkbox(XtkUi *ui, char const *label, XtkToggleDesc desc) {
	return toggle(ui, XTK_CTRL_CHECKBOX, label, desc);
}

XtkEl *xtk_radio(XtkUi *ui, char const *label, XtkToggleDesc desc) { return toggle(ui, XTK_CTRL_RADIO, label, desc); }

XtkEl *xtk_switch(XtkUi *ui, XtkToggleDesc desc) { return toggle(ui, XTK_CTRL_SWITCH, NULL, desc); }

XtkEl *xtk_slider(XtkUi *ui, XtkSliderDesc desc) {
	XtkEl *el = xtk_el_new(ui, XTK_CTRL_SLIDER, NULL);
	if (!el) return NULL;
	if (desc.max == 0.0f && desc.min == 0.0f) desc.max = 100.0f;
	if (desc.step == 0.0f) desc.step = 1.0f;
	if (desc.small_change == 0.0f) desc.small_change = 1.0f;
	if (desc.large_change == 0.0f) desc.large_change = 10.0f;
	if (desc.range && desc.range_start == 0.0f && desc.range_end == 0.0f) desc.range_end = desc.max;
	if (!XTK_EL_STORE(el, desc)) return NULL;
	return el;
}

XtkEl *xtk_scroll_bar(XtkUi *ui, XtkScrollBarDesc desc) {
	XtkEl *el = xtk_el_new(ui, XTK_CTRL_SCROLLBAR, NULL);
	if (!el) return NULL;
	if (desc.max == 0.0 && desc.min == 0.0) desc.max = 100.0;
	if (desc.small_change == 0.0) desc.small_change = 1.0;
	if (desc.large_change == 0.0) desc.large_change = 10.0;
	if (!XTK_EL_STORE(el, desc)) return NULL;
	return el;
}

static XtkEl *text_input(XtkUi *ui, XtkCtrlType type, char const *placeholder, XtkTextBoxDesc desc) {
	XtkEl *el = xtk_el_new(ui, type, placeholder);
	if (!el) return NULL;
	desc.content = xtk_strdup(ui, desc.content);
	if (!XTK_EL_STORE(el, desc)) return NULL;
	return el;
}

XtkEl *xtk_textbox(XtkUi *ui, char const *placeholder, XtkTextBoxDesc desc) {
	return text_input(ui, XTK_CTRL_TEXTBOX, placeholder, desc);
}

XtkEl *xtk_password(XtkUi *ui, char const *placeholder, XtkTextBoxDesc desc) {
	return text_input(ui, XTK_CTRL_PASSWORD, placeholder, desc);
}

static XtkEl *progress_el(XtkUi *ui, XtkCtrlType type, XtkProgressDesc desc) {
	XtkEl *el = xtk_el_new(ui, type, NULL);
	if (!el) return NULL;
	if (desc.max == 0.0f) desc.max = 100.0f;
	if (!XTK_EL_STORE(el, desc)) return NULL;
	return el;
}

XtkEl *xtk_progress(XtkUi *ui, XtkProgressDesc desc) { return progress_el(ui, XTK_CTRL_PROGRESS, desc); }

XtkEl *xtk_progressring(XtkUi *ui, XtkProgressDesc desc) { return progress_el(ui, XTK_CTRL_PROGRESSRING, desc); }

XtkEl *xtk_badge(XtkUi *ui, XtkBadgeDesc desc) {
	XtkEl *el = xtk_el_new(ui, XTK_CTRL_BADGE, NULL);
	if (!el) return NULL;
	desc.icon = xtk_strdup(ui, desc.icon);
	if (!XTK_EL_STORE(el, desc)) return NULL;
	return el;
}

XtkEl *xtk_image(XtkUi *ui, XtkImageDesc desc) {
	XtkEl *el = xtk_el_new(ui, XTK_CTRL_IMAGE, NULL);
	if (el && !XTK_EL_STORE(el, desc)) return NULL;
	return el;
}

XtkEl *xtk_link(XtkUi *ui, char const *label, XtkHyperlinkDesc desc) {
	XtkEl *el = xtk_el_new(ui, XTK_CTRL_LINK, label);
	if (!el) return NULL;
	desc.url = xtk_strdup(ui, desc.url);
	if (!XTK_EL_STORE(el, desc)) return NULL;
	return el;
}

XtkEl *xtk_divider(XtkUi *ui) { return xtk_el_new(ui, XTK_CTRL_DIVIDER, NULL); }

XtkEl *xtk_repeat(XtkUi *ui, char const *label, XtkButtonDesc desc) {
	XtkEl *el = xtk_el_new(ui, XTK_CTRL_REPEAT, label);
	if (!el) return NULL;
	desc.icon = xtk_strdup(ui, desc.icon);
	if (!XTK_EL_STORE(el, desc)) return NULL;
	return el;
}

XtkEl *xtk_infobar(XtkUi *ui, char const *title, char const *message, XtkInfoBarDesc desc) {
	XtkEl *el = xtk_el_new(ui, XTK_CTRL_INFOBAR, title);
	if (!el) return NULL;
	desc.message = xtk_strdup(ui, message);
	if (!XTK_EL_STORE(el, desc)) return NULL;
	return el;
}

XtkEl *xtk_tooltip(XtkUi *ui, XtkEl *el, char const *text) {
	if (el) XTK_EL_DATA(el)->tooltip = xtk_strdup(ui, text);
	return el;
}

XtkEl *xtk_spacer(XtkUi *ui) {
	XtkEl *el = xtk_el_new(ui, XTK_CTRL_CONTAINER, NULL);
	if (!el) return NULL;
	XtkStackDesc desc = {0};
	if (!XTK_EL_STORE(el, desc)) return NULL;
	XTK_EL_DATA(el)->grow = 1.0f;
	return el;
}

XtkEl **xtk_children_alloc(XtkUi *ui, int capacity) {
	if (capacity < 0) capacity = 0;
	XtkEl **buf = ( XtkEl ** ) xtk_arena_alloc(xtk_ui_arena(ui), sizeof(XtkEl *) * (( size_t ) capacity + 1));
	if (buf) buf [capacity] = XTK_END;
	return buf;
}

XtkEl *xtk_keyed(XtkUi *ui, char const *key, XtkEl *el) {
	if (el && key) {
		XTK_EL_DATA(el)->key.kind         = XTK_KEY_STRING;
		XTK_EL_DATA(el)->key.value.string = xtk_strdup(ui, key);
	}
	return el;
}

XtkEl *xtk_keyed_u64(XtkEl *el, uint64_t key) {
	if (el) {
		XTK_EL_DATA(el)->key.kind      = XTK_KEY_U64;
		XTK_EL_DATA(el)->key.value.u64 = key;
	}
	return el;
}

XtkEl *xtk_sized(XtkEl *el, float width, float height) {
	if (!el) return NULL;
	XTK_EL_DATA(el)->width  = width;
	XTK_EL_DATA(el)->height = height;
	return el;
}

XtkEl *xtk_grow(XtkEl *el, float grow) {
	if (el) XTK_EL_DATA(el)->grow = grow;
	return el;
}

XtkEl *xtk_align(XtkEl *el, XentFlexAlign align_self) {
	if (el) XTK_EL_DATA(el)->align_self = align_self;
	return el;
}

XtkEl *xtk_margin(XtkEl *el, XentInsets margin) {
	if (el) XTK_EL_DATA(el)->margin = margin;
	return el;
}
