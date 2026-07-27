#include <xtk/xtk_tree_model.h>

#include <limits.h>
#include <stddef.h>
#include <string.h>

enum
{
	TREE_MAGIC       = 0x45525458u,
	TREE_HEADER_SIZE = 16u,
	TREE_ITEM_SIZE   = 24u,
	TREE_DEPTH_MAX   = 256,
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

static bool measure_node(XtkTreeNodeDesc const *node, int depth, uint32_t *count, uint32_t *strings) {
	if (!node || depth > TREE_DEPTH_MAX || node->child_count < 0) return false;
	if (*count == UINT32_MAX || !size_add(strings, strlen(node->text ? node->text : "") + 1u)) return false;
	if (node->icon && !size_add(strings, strlen(node->icon) + 1u)) return false;
	(*count)++;
	if (node->child_count && !node->children) return false;
	for (int i = 0; i < node->child_count; i++)
		if (!measure_node(&node->children [i], depth + 1, count, strings)) return false;
	return true;
}

static bool measure_desc(XtkTreeDesc const *desc, uint32_t *count, uint32_t *strings) {
	if (!desc || desc->nroot < 0 || (desc->nroot && !desc->roots)) return false;
	*count   = 0u;
	*strings = 0u;
	for (int i = 0; i < desc->nroot; i++)
		if (!measure_node(&desc->roots [i], 0, count, strings)) return false;
	return true;
}

uint32_t xtk_tree_model_size(XtkTreeDesc const *desc) {
	uint32_t count;
	uint32_t strings;
	if (!measure_desc(desc, &count, &strings)) return 0u;
	if (count > (UINT32_MAX - TREE_HEADER_SIZE) / TREE_ITEM_SIZE) return 0u;
	uint32_t size = TREE_HEADER_SIZE + count * TREE_ITEM_SIZE;
	return size_add(&size, strings) ? size : 0u;
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

static bool write_node(
  uint8_t *data, uint32_t size, uint32_t *index, uint32_t *cursor, XtkTreeNodeDesc const *node, int32_t parent,
  int depth
) {
	if (depth > TREE_DEPTH_MAX || *index >= (size - TREE_HEADER_SIZE) / TREE_ITEM_SIZE) return false;
	uint32_t self = (*index)++;
	uint8_t *wire = data + TREE_HEADER_SIZE + self * TREE_ITEM_SIZE;
	store_u32(wire, ( uint32_t ) parent);
	uint32_t flags = (node->expanded ? XTK_TREE_MODEL_EXPANDED : 0u) | (node->disabled ? XTK_TREE_MODEL_DISABLED : 0u);
	store_u32(wire + 4u, flags);
	uint32_t offset;
	uint32_t length;
	write_string(data, cursor, node->text ? node->text : "", &offset, &length);
	store_u32(wire + 8u, offset);
	store_u32(wire + 12u, length);
	write_string(data, cursor, node->icon, &offset, &length);
	store_u32(wire + 16u, offset);
	store_u32(wire + 20u, length);
	for (int i = 0; i < node->child_count; i++)
		if (!write_node(data, size, index, cursor, &node->children [i], ( int32_t ) self, depth + 1)) return false;
	return true;
}

bool xtk_tree_model_write(XtkTreeDesc const *desc, void *buffer, uint32_t size) {
	uint32_t required = xtk_tree_model_size(desc);
	if (!required || !buffer || size != required) return false;
	uint8_t *data = ( uint8_t * ) buffer;
	memset(data, 0, size);
	store_u32(data, TREE_MAGIC);
	store_u32(data + 4u, XTK_TREE_MODEL_VERSION);
	store_u32(data + 8u, size);
	uint32_t count;
	uint32_t strings;
	if (!measure_desc(desc, &count, &strings)) return false;
	store_u32(data + 12u, count);
	uint32_t index  = 0u;
	uint32_t cursor = TREE_HEADER_SIZE + count * TREE_ITEM_SIZE;
	for (int i = 0; i < desc->nroot; i++)
		if (!write_node(data, size, &index, &cursor, &desc->roots [i], -1, 0)) return false;
	return index == count && cursor == size;
}

static bool
read_string(uint8_t const *data, uint32_t size, uint32_t floor, uint32_t offset, uint32_t length, char const **out) {
	if (!offset && !length) {
		*out = NULL;
		return true;
	}
	if (offset < floor || offset >= size || length >= size - offset) return false;
	if (data [offset + length] != '\0' || memchr(data + offset, '\0', length)) return false;
	*out = ( char const * ) data + offset;
	return true;
}

bool xtk_tree_model_item(XtkTreeModelView const *model, uint32_t index, XtkTreeModelItemView *out) {
	if (!model || !model->data || !out || index >= model->count) return false;
	uint32_t       floor  = TREE_HEADER_SIZE + model->count * TREE_ITEM_SIZE;
	uint8_t const *wire   = model->data + TREE_HEADER_SIZE + index * TREE_ITEM_SIZE;
	int32_t        parent = ( int32_t ) load_u32(wire);
	uint32_t       flags  = load_u32(wire + 4u);
	if (parent >= 0 && ( uint32_t ) parent >= index) return false;
	if (flags & ~(XTK_TREE_MODEL_EXPANDED | XTK_TREE_MODEL_DISABLED)) return false;
	char const *text;
	char const *icon;
	if (!read_string(model->data, model->size, floor, load_u32(wire + 8u), load_u32(wire + 12u), &text)) return false;
	if (!read_string(model->data, model->size, floor, load_u32(wire + 16u), load_u32(wire + 20u), &icon)) return false;
	*out = (XtkTreeModelItemView) {.parent = parent, .flags = flags, .text = text, .icon = icon};
	return true;
}

bool xtk_tree_model_open(void const *buffer, uint32_t size, XtkTreeModelView *out) {
	if (!buffer || !out || size < TREE_HEADER_SIZE) return false;
	uint8_t const *data  = ( uint8_t const * ) buffer;
	uint32_t       count = load_u32(data + 12u);
	if (load_u32(data) != TREE_MAGIC || load_u32(data + 4u) != XTK_TREE_MODEL_VERSION) return false;
	if (load_u32(data + 8u) != size || count > (size - TREE_HEADER_SIZE) / TREE_ITEM_SIZE) return false;
	*out = (XtkTreeModelView) {.data = data, .size = size, .count = count};
	XtkTreeModelItemView item;
	for (uint32_t i = 0; i < count; i++)
		if (!xtk_tree_model_item(out, i, &item)) return false;
	return true;
}
