#include "xtk_internal.h"
#include "../reconcile/xtk_reconcile_internal.h"
#include "../xtk_hash.h"

#include <xtk/xtk_reconcile.h>
#include <xtk/xtk_alloc.h>

#include <limits.h>
#include <string.h>

static bool count_regions(XtkNode const *node, uint32_t depth, uint32_t *count) {
	if (!node) return true;
	if (depth > 256u) return false;
	if (node->region_id) {
		if (*count == UINT32_MAX) return false;
		(*count)++;
	}
	for (int i = 0; i < node->child_count; i++)
		if (!count_regions(node->children [i], depth + 1u, count)) return false;
	return true;
}

static bool region_capacity(uint32_t count, uint32_t *out) {
	uint32_t need = count < 4u ? 8u : count * 2u;
	if (need < count) return false;
	uint32_t capacity = 8u;
	while (capacity < need) {
		if (capacity > UINT32_MAX / 2u) return false;
		capacity *= 2u;
	}
	*out = capacity;
	return true;
}

static bool region_reserve(XtkUi *ui, uint32_t count) {
	uint32_t capacity;
	if (!region_capacity(count, &capacity)) return false;
	if (capacity <= ui->region_capacity) return true;
	if (( size_t ) capacity > SIZE_MAX / sizeof(*ui->regions)) return false;
	XtkRegionEntry *entries = xtk_alloc_resize(ui->regions, sizeof(*entries) * capacity);
	if (!entries) return false;
	ui->regions         = entries;
	ui->region_capacity = capacity;
	return true;
}

static bool region_insert(XtkUi *ui, XtkNode *node) {
	uint32_t mask = ui->region_capacity - 1u;
	uint32_t slot = ( uint32_t ) xtk_hash_u64(node->region_id) & mask;
	while (ui->regions [slot].id) {
		if (ui->regions [slot].id == node->region_id) return false;
		slot = (slot + 1u) & mask;
	}
	ui->regions [slot] = (XtkRegionEntry) {.id = node->region_id, .revision = node->region_revision, .node = node};
	ui->region_count++;
	return true;
}

static bool fill_regions(XtkUi *ui, XtkNode *node) {
	if (!node) return true;
	if (node->region_id && !region_insert(ui, node)) return false;
	for (int i = 0; i < node->child_count; i++)
		if (!fill_regions(ui, node->children [i])) return false;
	return true;
}

bool xtk_ui_prepare_regions(XtkUi *ui, XtkNode *root) {
	if (!ui) return false;
	uint32_t count = 0u;
	if (!count_regions(root, 0u, &count)) return false;
	if (!count) {
		if (ui->regions) memset(ui->regions, 0, sizeof(*ui->regions) * ui->region_capacity);
		ui->region_count = 0u;
		return true;
	}
	if (!region_reserve(ui, count)) return false;
	memset(ui->regions, 0, sizeof(*ui->regions) * ui->region_capacity);
	ui->region_count = 0u;
	return fill_regions(ui, root);
}

XtkNode *xtk_ui_find_region(XtkUi const *ui, uint64_t id, uint64_t revision) {
	if (!ui || !id || !ui->region_capacity) return NULL;
	uint32_t mask = ui->region_capacity - 1u;
	uint32_t slot = ( uint32_t ) xtk_hash_u64(id) & mask;
	while (ui->regions [slot].id) {
		XtkRegionEntry const *entry = &ui->regions [slot];
		if (entry->id == id) return entry->revision == revision ? entry->node : NULL;
		slot = (slot + 1u) & mask;
	}
	return NULL;
}

static XtkEl *region_ref(XtkUi *ui, XtkNode *node, uint64_t id, uint64_t revision) {
	XtkEl *el = xtk_el_new(ui, node->type_id, NULL);
	if (!el) return NULL;
	XtkElementData *data  = XTK_EL_DATA(el);
	data->key             = node->key;
	data->region_id       = id;
	data->region_revision = revision;
	data->region_flags    = XTK_REGION_MEMO | XTK_REGION_REF;
	return el;
}

XtkEl *xtk_memo_region(XtkUi *ui, uint64_t id, uint64_t revision, XtkRegionBuildFn build, void *ctx) {
	if (!ui || !id || !build) {
		xtk_ui_fail(ui);
		return NULL;
	}
	XtkNode *node = xtk_ui_find_region(ui, id, revision);
	if (node) return region_ref(ui, node, id, revision);
	XtkEl *el = build(ui, ctx);
	if (!el) {
		xtk_ui_fail(ui);
		return NULL;
	}
	XtkElementData *data  = XTK_EL_DATA(el);
	data->region_id       = id;
	data->region_revision = revision;
	data->region_flags    = XTK_REGION_MEMO;
	return el;
}

XtkEl *xtk_static_region(XtkUi *ui, uint64_t id, XtkRegionBuildFn build, void *ctx) {
	return xtk_memo_region(ui, id, 0u, build, ctx);
}
