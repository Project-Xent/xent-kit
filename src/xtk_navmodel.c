#include <xtk/xtk_navmodel.h>

#include <limits.h>
#include <stddef.h>
#include <string.h>

enum
{
	NAV_MAGIC       = 0x56414e58u,
	NAV_HEADER_SIZE = 32u,
	NAV_ITEM_SIZE   = 28u,
};

static uint32_t load_u32(uint8_t const *p) {
	return ( uint32_t ) p [0] | ( uint32_t ) p [1] << 8u | ( uint32_t ) p [2] << 16u | ( uint32_t ) p [3] << 24u;
}

static void store_u32(uint8_t *p, uint32_t value) {
	p [0] = ( uint8_t ) value;
	p [1] = ( uint8_t ) (value >> 8u);
	p [2] = ( uint8_t ) (value >> 16u);
	p [3] = ( uint8_t ) (value >> 24u);
}

static bool size_add(uint32_t *size, size_t add) {
	if (add > UINT32_MAX || *size > UINT32_MAX - ( uint32_t ) add) return false;
	*size += ( uint32_t ) add;
	return true;
}

static bool add_string_size(uint32_t *size, char const *text) { return !text || size_add(size, strlen(text) + 1u); }

static bool nav_item_size(XtkNavItemDesc const *item, int *parent, int index, uint32_t *size) {
	if (( unsigned ) item->kind > XTK_NAV_CHILD) return false;
	if (item->kind == XTK_NAV_CHILD && *parent < 0) return false;
	if (item->kind == XTK_NAV_ITEM) *parent = index;
	return add_string_size(size, item->icon) && add_string_size(size, item->label);
}

uint32_t xtk_navmodel_size(XtkNavDesc const *desc) {
	if (!desc || desc->nitem < 0 || (desc->nitem && !desc->items)) return 0u;
	if (( uint32_t ) desc->nitem > (UINT32_MAX - NAV_HEADER_SIZE) / NAV_ITEM_SIZE) return 0u;
	uint32_t size = NAV_HEADER_SIZE + ( uint32_t ) desc->nitem * NAV_ITEM_SIZE;
	if (!add_string_size(&size, desc->app_title)) return 0u;
	int parent = -1;
	for (int i = 0; i < desc->nitem; i++)
		if (!nav_item_size(&desc->items [i], &parent, i, &size)) return 0u;
	return size;
}

static void write_string(uint8_t *data, uint32_t *cursor, char const *text, uint32_t *offset, uint32_t *length) {
	*offset = 0u;
	*length = 0u;
	if (!text) return;
	*offset = *cursor;
	*length = ( uint32_t ) strlen(text);
	memcpy(data + *cursor, text, ( size_t ) *length + 1u);
	*cursor += *length + 1u;
}

bool xtk_navmodel_write(XtkNavDesc const *desc, void *buffer, uint32_t size) {
	uint32_t required = xtk_navmodel_size(desc);
	if (!required || !buffer || size != required) return false;
	uint8_t *data = ( uint8_t * ) buffer;
	memset(data, 0, size);
	store_u32(data, NAV_MAGIC);
	store_u32(data + 4u, XTK_NAV_MODEL_VERSION);
	store_u32(data + 8u, size);
	store_u32(data + 12u, ( uint32_t ) desc->nitem);
	store_u32(data + 16u, desc->window_title_bar ? XTK_NAV_MODEL_WINDOW_TITLE_BAR : 0u);
	uint32_t cursor = NAV_HEADER_SIZE + ( uint32_t ) desc->nitem * NAV_ITEM_SIZE;
	uint32_t offset;
	uint32_t length;
	write_string(data, &cursor, desc->app_title, &offset, &length);
	store_u32(data + 20u, offset);
	store_u32(data + 24u, length);
	int parent = -1;
	for (int i = 0; i < desc->nitem; i++) {
		XtkNavItemDesc const *item = &desc->items [i];
		if (item->kind == XTK_NAV_ITEM) parent = i;
		uint8_t *wire = data + NAV_HEADER_SIZE + ( uint32_t ) i * NAV_ITEM_SIZE;
		store_u32(wire, ( uint32_t ) item->kind);
		store_u32(wire + 4u, item->kind == XTK_NAV_CHILD ? ( uint32_t ) parent : UINT32_MAX);
		write_string(data, &cursor, item->icon, &offset, &length);
		store_u32(wire + 8u, offset);
		store_u32(wire + 12u, length);
		write_string(data, &cursor, item->label, &offset, &length);
		store_u32(wire + 16u, offset);
		store_u32(wire + 20u, length);
	}
	return cursor == size;
}

static bool
read_string(uint8_t const *data, uint32_t size, uint32_t floor, uint32_t offset, uint32_t length, char const **out) {
	if (!offset && !length) {
		*out = NULL;
		return true;
	}
	if (offset < floor || offset >= size || length >= size - offset) return false;
	if (data [offset + length] != '\0') return false;
	if (memchr(data + offset, '\0', length)) return false;
	*out = ( char const * ) data + offset;
	return true;
}

bool xtk_navmodel_open(void const *buffer, uint32_t size, XtkNavModelView *out) {
	if (!buffer || !out || size < NAV_HEADER_SIZE) return false;
	uint8_t const *data  = ( uint8_t const * ) buffer;
	uint32_t       count = load_u32(data + 12u);
	if (load_u32(data) != NAV_MAGIC || load_u32(data + 4u) != XTK_NAV_MODEL_VERSION) return false;
	if (load_u32(data + 8u) != size || count > (size - NAV_HEADER_SIZE) / NAV_ITEM_SIZE) return false;
	if ((load_u32(data + 16u) & ~XTK_NAV_MODEL_WINDOW_TITLE_BAR) != 0u || load_u32(data + 28u) != 0u) return false;
	uint32_t    floor = NAV_HEADER_SIZE + count * NAV_ITEM_SIZE;
	char const *title;
	if (!read_string(data, size, floor, load_u32(data + 20u), load_u32(data + 24u), &title)) return false;
	*out = (XtkNavModelView) {
	  .data = data, .size = size, .count = count, .flags = load_u32(data + 16u), .app_title = title};
	XtkNavModelItemView item;
	for (uint32_t i = 0; i < count; i++)
		if (!xtk_navmodel_item(out, i, &item)) return false;
	return true;
}

bool xtk_navmodel_item(XtkNavModelView const *model, uint32_t index, XtkNavModelItemView *out) {
	if (!model || !model->data || !out || index >= model->count) return false;
	uint32_t       floor  = NAV_HEADER_SIZE + model->count * NAV_ITEM_SIZE;
	uint8_t const *wire   = model->data + NAV_HEADER_SIZE + index * NAV_ITEM_SIZE;
	uint32_t       kind   = load_u32(wire);
	int32_t        parent = ( int32_t ) load_u32(wire + 4u);
	if (kind > XTK_NAV_CHILD || load_u32(wire + 24u) != 0u) return false;
	if (kind == XTK_NAV_CHILD && (parent < 0 || ( uint32_t ) parent >= index)) return false;
	if (kind == XTK_NAV_CHILD
	    && load_u32(model->data + NAV_HEADER_SIZE + ( uint32_t ) parent * NAV_ITEM_SIZE) != XTK_NAV_ITEM)
		return false;
	if (kind != XTK_NAV_CHILD && parent != -1) return false;
	char const *icon;
	char const *label;
	if (!read_string(model->data, model->size, floor, load_u32(wire + 8u), load_u32(wire + 12u), &icon)) return false;
	if (!read_string(model->data, model->size, floor, load_u32(wire + 16u), load_u32(wire + 20u), &label)) return false;
	*out = (XtkNavModelItemView) {.kind = ( XtkNavKind ) kind, .parent = parent, .icon = icon, .label = label};
	return true;
}
