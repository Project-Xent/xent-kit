#include "xtk_internal.h"
#include "../reconcile/xtk_reconcile_internal.h"

#include <xtk/xtk_reconcile.h>

XtkNode *xtk_ui_find_region(XtkUi const *ui, uint64_t id, uint64_t revision) {
	if (!ui || !ui->rt || !id) return NULL;
	return xtk_rt_region_lookup(ui->rt, id, revision);
}

static XtkEl *region_ref(XtkUi *ui, XtkNode *node, uint64_t id, uint64_t revision, uint32_t flags) {
	XtkEl *el = xtk_el_new(ui, node->type_id, NULL);
	if (!el) return NULL;
	XtkElementData *data  = XTK_EL_DATA(el);
	data->key             = node->key;
	data->region_id       = id;
	data->region_revision = revision;
	data->region_flags    = flags | XTK_REGION_REF;
	return el;
}

XtkEl *xtk_memo_region(XtkUi *ui, uint64_t id, uint64_t revision, XtkRegionBuildFn build, void *ctx) {
	if (!ui || !id || !build) {
		xtk_ui_fail(ui);
		return NULL;
	}
	XtkNode *node = xtk_ui_find_region(ui, id, revision);
	if (node) return region_ref(ui, node, id, revision, XTK_REGION_MEMO);
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

XtkEl *xtk_sub_region(XtkUi *ui, uint64_t id, XtkRegionBuildFn build, void *ctx) {
	if (!ui || !id || !build) {
		xtk_ui_fail(ui);
		return NULL;
	}
	XtkRtRegion *reg = ui->rt ? xtk_rt_region_find(ui->rt, id) : NULL;
	if (reg && reg->node && !reg->dirty && (reg->flags & XTK_REGION_SUB)) {
		reg->build = build;
		reg->ctx   = ctx;
		return region_ref(ui, reg->node, id, 0u, XTK_REGION_SUB);
	}
	XtkEl *el = build(ui, ctx);
	if (!el) {
		xtk_ui_fail(ui);
		return NULL;
	}
	XtkElementData *data = XTK_EL_DATA(el);
	data->region_id      = id;
	data->region_flags   = XTK_REGION_SUB;
	data->region_build   = build;
	data->region_ctx     = ctx;
	return el;
}
