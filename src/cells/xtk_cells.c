#include <xtk/xtk_cells.h>
#include <xtk/xtk_catalog.h>

#include "../batch/xtk_batch_internal.h"
#include "../xtk_alloc_internal.h"
#include "../xtk_thread_internal.h"

#include <string.h>

typedef struct XtkCell {
	XtkCtrl       target;
	XtkPropertyId property;
	XtkValue      value;
	uint32_t      string_capacity;
	uint64_t      revision;
	bool          has_value;
	bool          dirty;
} XtkCell;

struct XtkCells {
	XtkScene    scene;
	XtkCell    *items;
	XtkBatch   *batch;
	uint32_t    count;
	uint32_t    capacity;
	XtkSourceId source;
	void const *owner_thread;
	bool        flushing;
};

static bool supported_property(XtkPropertyId property, XtkPropertyKind kind) {
	if (property == XTK_PROP_TEXT) return kind == XTK_PROP_KIND_STRING;
	if (property == XTK_PROP_VALUE_F32) return kind == XTK_PROP_KIND_F32;
	if (property == XTK_PROP_VALUE_F64) return kind == XTK_PROP_KIND_F64;
	return false;
}

static bool     cells_thread_ok(XtkCells const *cells) { return cells && cells->owner_thread == xtk_thread_token(); }

static XtkCell *cell_at(XtkCells *cells, XtkCellId id) {
	if (!cells_thread_ok(cells) || id >= cells->count) return NULL;
	return &cells->items [id];
}

static XtkCell const *cell_at_const(XtkCells const *cells, XtkCellId id) {
	if (!cells_thread_ok(cells) || id >= cells->count) return NULL;
	return &cells->items [id];
}

static bool cells_reserve(XtkCells *cells) {
	if (cells->count < cells->capacity) return true;
	uint32_t capacity = cells->capacity ? cells->capacity * 2u : 8u;
	if (capacity <= cells->capacity || ( size_t ) capacity > SIZE_MAX / sizeof(*cells->items)) return false;
	XtkCell *items = xtk_alloc_resize(cells->items, ( size_t ) capacity * sizeof(*items));
	if (!items) return false;
	cells->items    = items;
	cells->capacity = capacity;
	return true;
}

XtkCells *xtk_cells_create(XtkScene scene, XtkSourceId source) {
	if (!scene.host || !scene.host->vt || source == XTK_SOURCE_INVALID) return NULL;
	XtkCells *cells = xtk_alloc_zero(1u, sizeof(*cells));
	if (!cells) return NULL;
	cells->scene        = scene;
	cells->source       = source;
	cells->owner_thread = xtk_thread_token();
	cells->batch        = xtk_batch_alloc(scene.host->vt->revision(scene.host));
	if (cells->batch) return cells;
	xtk_alloc_free(cells);
	return NULL;
}

bool xtk_cells_destroy(XtkCells *cells) {
	if (!cells) return true;
	if (!cells_thread_ok(cells) || cells->flushing) return false;
	for (uint32_t i = 0; i < cells->count; i++)
		if (cells->items [i].value.kind == XTK_VALUE_STRING) xtk_alloc_free(cells->items [i].value.u.string.data);
	xtk_batch_free(cells->batch);
	xtk_alloc_free(cells->items);
	xtk_alloc_free(cells);
	return true;
}

static bool duplicate_binding(XtkCells const *cells, XtkCtrl target, XtkPropertyId property) {
	for (uint32_t i = 0; i < cells->count; i++)
		if (cells->items [i].target == target && cells->items [i].property == property) return true;
	return false;
}

XtkCellId xtk_cells_bind(XtkCells *cells, XtkCtrl target, XtkPropertyId property) {
	if (!cells_thread_ok(cells) || cells->flushing || !cells->scene.host->vt->live(cells->scene.host, target))
		return XTK_CELL_INVALID;
	XtkCtrlId          type = cells->scene.host->vt->type(cells->scene.host, target);
	XtkPropDesc const *desc = xtk_catalog_control_property(type, property);
	if (!desc || !supported_property(property, desc->kind)) return XTK_CELL_INVALID;
	if (duplicate_binding(cells, target, property) || !cells_reserve(cells)) return XTK_CELL_INVALID;
	XtkCellId id      = cells->count++;
	cells->items [id] = (XtkCell) {.target = target, .property = property};
	return id;
}

static bool mark_value(XtkCells *cells, XtkCell *cell, XtkValue value) {
	if (cells->flushing || cell->revision == UINT64_MAX) return false;
	cell->value = value;
	cell->revision++;
	cell->has_value = true;
	cell->dirty     = true;
	return true;
}

bool xtk_cell_set_f32(XtkCells *cells, XtkCellId id, float value) {
	XtkCell *cell = cell_at(cells, id);
	if (!cell || cell->property != XTK_PROP_VALUE_F32) return false;
	return mark_value(cells, cell, (XtkValue) {.kind = XTK_VALUE_F32, .u.f32 = value});
}

bool xtk_cell_set_f64(XtkCells *cells, XtkCellId id, double value) {
	XtkCell *cell = cell_at(cells, id);
	if (!cell || cell->property != XTK_PROP_VALUE_F64) return false;
	return mark_value(cells, cell, (XtkValue) {.kind = XTK_VALUE_F64, .u.f64 = value});
}

static bool string_reserve(XtkCell *cell, uint32_t len) {
	if (len == UINT32_MAX) return false;
	uint32_t need = len + 1u;
	if (need <= cell->string_capacity) return true;
	char *data = xtk_alloc_resize(cell->value.u.string.data, need);
	if (!data) return false;
	cell->value.u.string.data = data;
	cell->string_capacity     = need;
	return true;
}

bool xtk_cell_set_string(XtkCells *cells, XtkCellId id, char const *data, uint32_t len) {
	XtkCell *cell = cell_at(cells, id);
	if (!cell || cell->property != XTK_PROP_TEXT || (len && !data) || cells->flushing) return false;
	if (cell->revision == UINT64_MAX || !string_reserve(cell, len)) return false;
	if (len) memcpy(cell->value.u.string.data, data, len);
	cell->value.u.string.data [len] = '\0';
	cell->value.kind                = XTK_VALUE_STRING;
	cell->value.u.string.len        = len;
	cell->revision++;
	cell->has_value = true;
	cell->dirty     = true;
	return true;
}

static bool append_dirty(XtkCells *cells) {
	for (uint32_t i = 0; i < cells->count; i++) {
		XtkCell *cell = &cells->items [i];
		if (!cell->dirty) continue;
		XtkChangeStamp change = {.source = cells->source, .revision = cell->revision};
		if (!xtk_batch_set(cells->batch, xtk_ref_existing(cell->target), cell->property, cell->value, change))
			return false;
	}
	return true;
}

static bool has_dirty(XtkCells const *cells) {
	for (uint32_t i = 0; i < cells->count; i++)
		if (cells->items [i].dirty) return true;
	return false;
}

static XtkBatchResult *commit_cells(XtkCells *cells) {
	XtkHost      *host       = cells->scene.host;
	XtkPrepare   *prepare    = NULL;
	XtkBatchDiag  diagnostic = {0};
	XtkBatchError error      = host->vt->prepare(host, cells->batch, &prepare, &diagnostic);
	if (error == XTK_BATCH_OK && prepare) return host->vt->commit(host, prepare, &diagnostic);
	if (prepare) host->vt->abort(host, prepare);
	return NULL;
}

bool xtk_cells_flush(XtkCells *cells) {
	if (!cells_thread_ok(cells) || cells->flushing) return false;
	if (!has_dirty(cells)) return true;
	cells->flushing = true;
	XtkHost *host   = cells->scene.host;
	xtk_batch_reset(cells->batch, host->vt->revision(host));
	XtkBatchResult *result = append_dirty(cells) ? commit_cells(cells) : NULL;
	if (result) {
		for (uint32_t i = 0; i < cells->count; i++) cells->items [i].dirty = false;
		xtk_batch_result_destroy(result);
	}
	xtk_batch_reset(cells->batch, host->vt->revision(host));
	cells->flushing = false;
	return result != NULL;
}

static bool view_kind_matches(XtkCell const *cell, XtkValueView const *value) {
	if (cell->property == XTK_PROP_TEXT) return value->kind == XTK_VALUE_STRING;
	if (cell->property == XTK_PROP_VALUE_F32) return value->kind == XTK_VALUE_F32;
	if (cell->property == XTK_PROP_VALUE_F64) return value->kind == XTK_VALUE_F64;
	return false;
}

static XtkCellAccept accept_string(XtkCells *cells, XtkCellId id, XtkCell *cell, XtkValueView const *value) {
	if (!xtk_cell_set_string(cells, id, value->u.string.data, value->u.string.len)) return XTK_CELL_REJECTED;
	cell->dirty = false;
	return XTK_CELL_ACCEPTED;
}

static XtkCellAccept accept_number(XtkCell *cell, XtkValueView const *value) {
	cell->value.kind = value->kind;
	if (value->kind == XTK_VALUE_F32) cell->value.u.f32 = value->u.f32;
	else cell->value.u.f64 = value->u.f64;
	cell->has_value = true;
	cell->dirty     = false;
	return XTK_CELL_ACCEPTED;
}

XtkCellAccept xtk_cell_accept(XtkCells *cells, XtkCellId id, XtkValueView const *value, XtkChangeStamp change) {
	XtkCell *cell = cell_at(cells, id);
	if (!cell || !value || cells->flushing || !xtk_change_stamp_valid(change) || !view_kind_matches(cell, value))
		return XTK_CELL_REJECTED;
	if (change.source == cells->source && change.revision <= cell->revision) return XTK_CELL_ECHO;
	if (value->kind == XTK_VALUE_STRING) return accept_string(cells, id, cell, value);
	return accept_number(cell, value);
}

bool xtk_cell_get(XtkCells const *cells, XtkCellId id, XtkValueView *out) {
	XtkCell const *cell = cell_at_const(cells, id);
	if (!cell || !cell->has_value || !out) return false;
	memset(out, 0, sizeof(*out));
	out->kind = cell->value.kind;
	if (out->kind == XTK_VALUE_F32) out->u.f32 = cell->value.u.f32;
	if (out->kind == XTK_VALUE_F64) out->u.f64 = cell->value.u.f64;
	if (out->kind == XTK_VALUE_STRING) {
		out->u.string.data = cell->value.u.string.data;
		out->u.string.len  = cell->value.u.string.len;
	}
	return true;
}
