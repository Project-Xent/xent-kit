#include "xtk_encode.h"
#include <xtk/xtk_alloc.h>
#include <xtk/xtk_navmodel.h>
#include <xtk/xtk_scene.h>
#include <xtk/xtk_treemodel.h>

#include <string.h>

static bool set_bytes(XtkBatch *batch, XtkNodeRef target, XtkPropertyId id, void const *data, uint32_t len) {
	XtkValue value = {
	  .kind = XTK_VALUE_BYTES, .u.bytes = {.data = ( uint8_t * ) ( uintptr_t ) data, .len = len}
    };
	return xtk_batch_set(batch, target, id, value, (XtkChangeStamp) {0});
}

static bool set_strings(XtkBatch *batch, XtkNodeRef target, char const *const *strs, int count) {
	size_t size = 0u;
	for (int i = 0; i < count; i++) {
		size += strlen(strs [i] ? strs [i] : "") + 1u;
		if (size > UINT32_MAX) return false;
	}
	uint8_t *bytes = size ? ( uint8_t * ) xtk_alloc(size) : NULL;
	if (size && !bytes) return false;
	size_t at = 0u;
	for (int i = 0; i < count; i++) {
		char const *s = strs [i] ? strs [i] : "";
		size_t      n = strlen(s) + 1u;
		memcpy(bytes + at, s, n);
		at += n;
	}
	bool ok = set_bytes(batch, target, XTK_PROP_ITEMS, bytes, ( uint32_t ) size);
	xtk_alloc_free(bytes);
	return ok;
}

static bool set_fields(
  XtkBatch *batch, XtkNodeRef target, int count, int stride, void const *items, size_t size,
  void (*fill)(char const **out, void const *item)
) {
	if (count <= 0) return set_strings(batch, target, NULL, 0);
	char const **strs = ( char const ** ) xtk_alloc(sizeof(*strs) * ( size_t ) count * ( size_t ) stride);
	if (!strs) return false;
	for (int i = 0; i < count; i++) fill(strs + i * stride, ( char const * ) items + size * ( size_t ) i);
	bool ok = set_strings(batch, target, strs, count * stride);
	xtk_alloc_free(strs);
	return ok;
}

static void selector_fields(char const **out, void const *item) {
	XtkSelectorItem const *it = item;
	out [0]                   = it->icon;
	out [1]                   = it->text;
	out [2]                   = it->disabled ? "1" : "0";
}

static void tab_fields(char const **out, void const *item) {
	XtkTabDesc const *tab = item;
	out [0]               = tab->icon;
	out [1]               = tab->label;
}

bool xtk_items_strings(XtkBatch *batch, XtkNodeRef target, char const *const *items, int count) {
	return set_strings(batch, target, items, count > 0 ? count : 0);
}

bool xtk_items_selector(XtkBatch *batch, XtkNodeRef target, XtkSelectorItem const *items, int count) {
	return set_fields(batch, target, count, 3, items, sizeof(*items), selector_fields);
}

bool xtk_items_tabs(XtkBatch *batch, XtkNodeRef target, XtkTabDesc const *tabs, int count) {
	return set_fields(batch, target, count, 2, tabs, sizeof(*tabs), tab_fields);
}

bool xtk_items_tree(XtkBatch *batch, XtkNodeRef target, XtkTreeDesc const *tree) {
	uint32_t size = xtk_treemodel_size(tree);
	uint8_t *data = size ? ( uint8_t * ) xtk_alloc(size) : NULL;
	bool     ok = data && xtk_treemodel_write(tree, data, size) && set_bytes(batch, target, XTK_PROP_ITEMS, data, size);
	xtk_alloc_free(data);
	return ok;
}

bool xtk_items_nav(XtkBatch *batch, XtkNodeRef target, XtkNavDesc const *nav) {
	uint32_t size = xtk_navmodel_size(nav);
	uint8_t *data = size ? ( uint8_t * ) xtk_alloc(size) : NULL;
	bool ok = data && xtk_navmodel_write(nav, data, size) && set_bytes(batch, target, XTK_PROP_NAV_MODEL, data, size);
	xtk_alloc_free(data);
	return ok;
}

bool xtk_txn_setitems(XtkTxn *txn, XtkNodeRef target, char const *const *items, int count) {
	return xtk_items_strings(xtk_txn_batch(txn), target, items, count);
}

bool xtk_txn_setselitems(XtkTxn *txn, XtkNodeRef target, XtkSelectorItem const *items, int count) {
	return xtk_items_selector(xtk_txn_batch(txn), target, items, count);
}

bool xtk_txn_settabs(XtkTxn *txn, XtkNodeRef target, XtkTabDesc const *tabs, int count) {
	return xtk_items_tabs(xtk_txn_batch(txn), target, tabs, count);
}

bool xtk_txn_settree(XtkTxn *txn, XtkNodeRef target, XtkTreeDesc const *tree) {
	return xtk_items_tree(xtk_txn_batch(txn), target, tree);
}

bool xtk_txn_setnav(XtkTxn *txn, XtkNodeRef target, XtkNavDesc const *nav) {
	return xtk_items_nav(xtk_txn_batch(txn), target, nav);
}

bool xtk_ctrl_setitems(XtkScene *scene, XtkCtrl control, char const *const *items, int count) {
	XtkTxn txn;
	if (!xtk_txn_begin(scene, &txn)) return false;
	if (!xtk_txn_setitems(&txn, xtk_ref_existing(control), items, count)) {
		xtk_txn_abort(&txn);
		return false;
	}
	XtkBatchResult *result = xtk_txn_commit(&txn, NULL);
	if (!result) return false;
	xtk_batchresult_destroy(result);
	return true;
}
