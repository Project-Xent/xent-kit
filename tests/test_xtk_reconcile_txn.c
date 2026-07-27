#include <xtk/xtk_reconcile.h>
#include "xtk_retained.h"
#include <xtk/xtk_catalog.h>
#include <xtk/xtk_component.h>

#include "encode/xtk_encode.h"
#include "../src/xtk_internal.h"
#include "runtime/xtk_runtime_internal.h"
#include "reconcile/xtk_reconcile_internal.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EXPECT(cond, msg)              \
	do {                               \
		if (!(cond)) {                 \
			printf("FAIL: %s\n", msg); \
			return 1;                  \
		}                              \
	}                                  \
	while (0)

typedef struct Mock {
	int  prepares;
	int  commits;
	int  creates;
	int  destroys;
	int  moves;
	int  nav_model_sets;
	bool fail_preflight;
	bool fail_prepare;
	bool fail_commit;
} Mock;

typedef struct CountingHost {
	XtkHost              base;
	XtkHost             *inner;
	XtkHostVtable        vt;
	XtkHostVtable const *inner_vt;
	Mock                *mock;
} CountingHost;

static CountingHost       *as_ch(XtkHost *host) { return ( CountingHost * ) host; }

static CountingHost const *as_ch_c(XtkHost const *host) { return ( CountingHost const * ) host; }

static void                tally(CountingHost *ch, XtkBatch *batch) {
	for (uint32_t i = 0; i < batch->count; i++) {
		switch (batch->ops [i].kind) {
		case XTK_BATCH_OP_CREATE  : ch->mock->creates++; break;
		case XTK_BATCH_OP_DESTROY : ch->mock->destroys++; break;
		case XTK_BATCH_OP_MOVE    : ch->mock->moves++; break;
		case XTK_BATCH_OP_SET_PROP :
			if (batch->ops [i].u.set_prop.patch.id == XTK_PROP_NAV_MODEL) ch->mock->nav_model_sets++;
			break;
		default : break;
		}
	}
}

static XtkBatchError counting_preflight(XtkHost *host, XtkBatch *batch, XtkBatchDiag *diagnostic) {
	if (as_ch(host)->mock->fail_preflight) return XTK_BATCH_ERR_BACKEND;
	return as_ch(host)->inner_vt->preflight(as_ch(host)->inner, batch, diagnostic);
}

static XtkBatchError
counting_prepare(XtkHost *host, XtkBatch *batch, XtkPrepare **out_prepare, XtkBatchDiag *diagnostic) {
	CountingHost *ch = as_ch(host);
	ch->mock->prepares++;
	tally(ch, batch);
	if (ch->mock->fail_prepare) {
		*out_prepare = NULL;
		return XTK_BATCH_ERR_BACKEND;
	}
	return ch->inner_vt->prepare(ch->inner, batch, out_prepare, diagnostic);
}

static XtkBatchResult *counting_commit(XtkHost *host, XtkPrepare *prepare, XtkBatchDiag *diagnostic) {
	CountingHost *ch = as_ch(host);
	ch->mock->commits++;
	if (ch->mock->fail_commit) {
		ch->inner_vt->abort(ch->inner, prepare);
		return NULL;
	}
	return ch->inner_vt->commit(ch->inner, prepare, diagnostic);
}

static void counting_abort(XtkHost *host, XtkPrepare *prepare) {
	as_ch(host)->inner_vt->abort(as_ch(host)->inner, prepare);
}

static bool counting_is_live(XtkHost const *host, XtkCtrl c) {
	return as_ch_c(host)->inner_vt->live(as_ch_c(host)->inner, c);
}

static uint64_t counting_revision(XtkHost const *host) {
	return as_ch_c(host)->inner_vt->revision(as_ch_c(host)->inner);
}

static XtkCtrl counting_scene_root(XtkHost const *host) { return as_ch_c(host)->inner_vt->root(as_ch_c(host)->inner); }

static XtkCtrlId counting_control_type(XtkHost const *host, XtkCtrl c) {
	return as_ch_c(host)->inner_vt->type(as_ch_c(host)->inner, c);
}

static XtkCtrl counting_parent(XtkHost const *host, XtkCtrl c) {
	return as_ch_c(host)->inner_vt->parent(as_ch_c(host)->inner, c);
}

static XtkCtrl counting_first_child(XtkHost const *host, XtkCtrl c) {
	return as_ch_c(host)->inner_vt->first(as_ch_c(host)->inner, c);
}

static XtkCtrl counting_next_sibling(XtkHost const *host, XtkCtrl c) {
	return as_ch_c(host)->inner_vt->next(as_ch_c(host)->inner, c);
}

static XtkCtrlDesc const *counting_descriptor(XtkHost const *host, XtkCtrlId type) {
	return as_ch_c(host)->inner_vt->desc(as_ch_c(host)->inner, type);
}

static bool
counting_get_property(XtkHost const *host, XtkCtrl c, XtkPropertyId p, XtkValueView *v, XtkChangeStamp *chstamp) {
	return as_ch_c(host)->inner_vt->prop(as_ch_c(host)->inner, c, p, v, chstamp);
}

static bool counting_resource_is_valid(XtkHost const *host, XtkResource r, XtkResourceTypeId t) {
	return as_ch_c(host)->inner_vt->res_valid(as_ch_c(host)->inner, r, t);
}

static bool counting_resource_retain(XtkHost *host, XtkResource r, XtkResourceTypeId t) {
	return as_ch(host)->inner_vt->res_retain(as_ch(host)->inner, r, t);
}

static void counting_resource_release(XtkHost *host, XtkResource r, XtkResourceTypeId t) {
	as_ch(host)->inner_vt->res_release(as_ch(host)->inner, r, t);
}

static uint32_t counting_dispatch(XtkHost *host, XtkEvent const *e) {
	return as_ch(host)->inner_vt->dispatch(as_ch(host)->inner, e);
}

static void wrap_host(CountingHost *ch, XtkHost *inner, Mock *mock) {
	ch->inner          = inner;
	ch->inner_vt       = inner->vt;
	ch->mock           = mock;
	ch->vt             = *inner->vt;
	ch->vt.preflight   = counting_preflight;
	ch->vt.prepare     = counting_prepare;
	ch->vt.commit      = counting_commit;
	ch->vt.abort       = counting_abort;
	ch->vt.live        = counting_is_live;
	ch->vt.revision    = counting_revision;
	ch->vt.root        = counting_scene_root;
	ch->vt.type        = counting_control_type;
	ch->vt.parent      = counting_parent;
	ch->vt.first       = counting_first_child;
	ch->vt.next        = counting_next_sibling;
	ch->vt.desc        = counting_descriptor;
	ch->vt.prop        = counting_get_property;
	ch->vt.res_valid   = counting_resource_is_valid;
	ch->vt.res_retain  = counting_resource_retain;
	ch->vt.res_release = counting_resource_release;
	ch->vt.dispatch    = counting_dispatch;
	ch->base.vt        = &ch->vt;
	ch->base.impl      = inner->impl;
}

static void request_frame(void *ctx) { ( void ) ctx; }

static void noop_update(void *model, XtkMsg msg) {
	( void ) model;
	( void ) msg;
}

enum
{
	TXN_COMPONENT_ID = XTK_CTRL_ID_COMPONENT_BASE + 11u,
};

typedef struct TxnComponentProps {
	int value;
} TxnComponentProps;

typedef struct TxnComponentPrepare {
	TxnComponentProps  props;
	TxnComponentProps *state;
} TxnComponentPrepare;

static int        txn_component_mounted;
static int        txn_component_updated;

static XtkCompErr txn_component_mount(XtkCompHost *host, XtkCtrl node, void const *props, XtkCompPrep **out) {
	( void ) host;
	( void ) node;
	TxnComponentPrepare *prepare = ( TxnComponentPrepare * ) malloc(sizeof(*prepare));
	if (!prepare) return XTK_COMPONENT_ERR_OOM;
	prepare->props = *( TxnComponentProps const * ) props;
	prepare->state = NULL;
	*out           = ( XtkCompPrep * ) prepare;
	return XTK_COMPONENT_OK;
}

static XtkCompErr txn_component_update(
  XtkCompHost *host, XtkCtrl node, void *state, void const *previous, void const *next, XtkCompPrep **out
) {
	( void ) host;
	( void ) node;
	( void ) previous;
	TxnComponentPrepare *prepare = ( TxnComponentPrepare * ) malloc(sizeof(*prepare));
	if (!prepare) return XTK_COMPONENT_ERR_OOM;
	prepare->props = *( TxnComponentProps const * ) next;
	prepare->state = ( TxnComponentProps * ) state;
	*out           = ( XtkCompPrep * ) prepare;
	return XTK_COMPONENT_OK;
}

static void *txn_component_commit_mount(XtkCompPrep *raw) {
	TxnComponentPrepare *prepare = ( TxnComponentPrepare * ) raw;
	txn_component_mounted        = prepare->props.value;
	return &prepare->props;
}

static void txn_component_commit_update(XtkCompPrep *raw) {
	TxnComponentPrepare *prepare = ( TxnComponentPrepare * ) raw;
	*prepare->state              = prepare->props;
	txn_component_updated        = prepare->props.value;
	free(prepare);
}

static void txn_component_abort(XtkCompPrep *prepare) { free(prepare); }

static void txn_component_unmount(XtkCompHost *host, XtkCtrl node, void *state) {
	( void ) host;
	( void ) node;
	free(state);
}

static XtkPropertyId const txn_component_properties [] = {XTK_PROP_COMPONENT_PROPS};
static XtkCtrlDesc const   txn_component_descriptor    = {
  .id             = TXN_COMPONENT_ID,
  .name           = "transaction-component",
  .properties     = txn_component_properties,
  .property_count = 1u,
};
static XtkCompType const txn_component_type = {
	.abi_version = 1u,
	.control     = &txn_component_descriptor,
	.props_size  = sizeof(TxnComponentProps),
	.ops = {
	  .prepare_mount  = txn_component_mount,
	  .prepare_update = txn_component_update,
	  .commit_mount   = txn_component_commit_mount,
	  .commit_update  = txn_component_commit_update,
	  .abort          = txn_component_abort,
	  .unmount        = txn_component_unmount,
	},
};

static XtkEl *build_component_view(XtkUi *ui, void *model) { return xtk_component(ui, &txn_component_type, model); }

static XtkEl *build_unknown_view(XtkUi *ui, void *model) {
	( void ) model;
	XtkEl *el = xtk_text(ui, "unknown", (XtkTextDesc) {0});
	if (el) XTK_EL_DATA(el)->type = XTK_CTRL_ID_COMPONENT_BASE + 99u;
	return el;
}

static XtkEl *build_malformed_view(XtkUi *ui, void *model) {
	( void ) model;
	XtkEl *root = xtk_column(ui, (XtkStackDesc) {0}, xtk_kids(xtk_text(ui, "child", (XtkTextDesc) {0})));
	if (root) {
		XtkElementData *data                                = XTK_EL_DATA(root);
		root->ui->composition.children [data->child_offset] = UINT32_MAX;
	}
	return root;
}

typedef struct Model {
	int          count;
	bool         keyed;
	bool         reverse;
	bool         mixed;
	bool         nested_mixed;
	bool         duplicate;
	bool         duplicate_scalar;
	bool         scalar;
	int const   *order;
	char const **labels;
} Model;

static XtkEl *build_view(XtkUi *ui, void *model) {
	Model *m = ( Model * ) model;
	if (m->duplicate) {
		return xtk_column(
		  ui, (XtkStackDesc) {0},
		  (XtkEl *[]) {
			xtk_keyed(ui, "duplicate", xtk_text(ui, "a", (XtkTextDesc) {0})),
			xtk_keyed(ui, "duplicate", xtk_button(ui, "b", (XtkButtonDesc) {0})),
			XTK_END,
		  }
		);
	}
	if (m->duplicate_scalar) {
		return xtk_column(
		  ui, (XtkStackDesc) {0},
		  xtk_kids(
			xtk_keyed_u64(xtk_text(ui, "a", (XtkTextDesc) {0}), 42u),
			xtk_keyed_u64(xtk_button(ui, "b", (XtkButtonDesc) {0}), 42u)
		  )
		);
	}
	if (m->mixed) {
		return xtk_column(
		  ui, (XtkStackDesc) {0},
		  (XtkEl *[]) {
			xtk_text(ui, "a", (XtkTextDesc) {0}),
			xtk_keyed(ui, "k", xtk_text(ui, "b", (XtkTextDesc) {0})),
			XTK_END,
		  }
		);
	}
	if (m->nested_mixed) {
		XtkEl *inner = xtk_column(
		  ui, (XtkStackDesc) {0},
		  (XtkEl *[]) {
			xtk_text(ui, "a", (XtkTextDesc) {0}),
			xtk_keyed(ui, "k", xtk_text(ui, "b", (XtkTextDesc) {0})),
			XTK_END,
		  }
		);
		return xtk_column(ui, (XtkStackDesc) {0}, (XtkEl *[]) {inner, XTK_END});
	}
	XtkEl **kids = xtk_children_alloc(ui, m->count);
	if (!kids) return NULL;
	for (int i = 0; i < m->count; i++) {
		int    idx = m->order ? m->order [i] : (m->reverse ? m->count - 1 - i : i);
		XtkEl *el  = xtk_text(ui, m->labels ? m->labels [idx] : "x", (XtkTextDesc) {0});
		if (m->keyed) el = m->scalar ? xtk_keyed_u64(el, ( uint64_t ) idx) : xtk_keyed(ui, xtk_fmt(ui, "k%d", idx), el);
		kids [i] = el;
	}
	return xtk_column(ui, (XtkStackDesc) {0}, kids);
}

static int reference_lis(int const *old_order, int const *next_order, int count) {
	int position [8] = {0};
	int length [8]   = {0};
	for (int i = 0; i < count; i++) position [old_order [i]] = i;
	int best = 0;
	for (int i = 0; i < count; i++) {
		length [i] = 1;
		for (int j = 0; j < i; j++)
			if (position [next_order [j]] < position [next_order [i]] && length [j] + 1 > length [i])
				length [i] = length [j] + 1;
		if (length [i] > best) best = length [i];
	}
	return best;
}

static bool next_permutation(int *values, int count) {
	int i = count - 2;
	while (i >= 0 && values [i] >= values [i + 1]) i--;
	if (i < 0) return false;
	int j = count - 1;
	while (values [j] <= values [i]) j--;
	int tmp    = values [i];
	values [i] = values [j];
	values [j] = tmp;
	for (int a = i + 1, b = count - 1; a < b; a++, b--) {
		tmp        = values [a];
		values [a] = values [b];
		values [b] = tmp;
	}
	return true;
}

static bool order_matches(XtkRt *rt, XtkHost *host, XtkCtrl const *handles, int const *order, int count) {
	XtkCtrl child = host->vt->first(host, ( XtkCtrl ) rt->root->node);
	for (int i = 0; i < count; i++) {
		if (rt->root->children [i]->node != ( XentNodeId ) handles [order [i]]) return false;
		if (child != handles [order [i]]) return false;
		child = host->vt->next(host, child);
	}
	return child == XTK_CTRL_INVALID;
}

static void reset_mock(Mock *m) { memset(m, 0, sizeof(*m)); }

static int  test_one_prepare_per_dirty_frame(void) {
	XtkHost *inner = xtk_retained_host_create();
	EXPECT(inner, "host");
	Mock         mock = {0};
	CountingHost ch;
	wrap_host(&ch, inner, &mock);
	Model    model = {.count = 3, .keyed = false};
	XtkRtCfg cfg   = {.request_frame = request_frame};
	XtkRt   *rt
	  = xtk_rt_create(&ch.base, &cfg, ( XentNodeId ) ch.base.vt->root(&ch.base), &model, noop_update, build_view);
	EXPECT(rt, "runtime");

	XtkFrameResult fr = xtk_rt_frame(rt);
	EXPECT(fr.status == XTK_FRAME_COMMITTED, "mount");
	EXPECT(mock.prepares == 1 && mock.commits == 1, "one prepare/commit on mount");
	EXPECT(fr.metrics.nodes_built == 4u && fr.metrics.nodes_compared == 4u, "mount reports build and compare work");
	EXPECT(fr.metrics.property_patches > 0u && fr.metrics.mutations > 0u, "mount reports patches and mutations");

	reset_mock(&mock);
	fr = xtk_rt_frame(rt);
	EXPECT(fr.status == XTK_FRAME_CLEAN, "clean frame");
	EXPECT(mock.prepares == 0 && mock.commits == 0, "no host ops when clean");
	EXPECT(fr.metrics.nodes_built == 0u && fr.metrics.nodes_compared == 0u, "clean frame reports no work");

	reset_mock(&mock);
	xtk_rt_invalidate(rt);
	fr = xtk_rt_frame(rt);
	EXPECT(fr.status == XTK_FRAME_COMMITTED, "forced frame");
	EXPECT(mock.prepares <= 1 && mock.commits == mock.prepares, "at most one prepare on dirty");
	EXPECT(fr.metrics.nodes_built == 4u && fr.metrics.nodes_compared == 4u, "stable frame reports exact traversal");
	EXPECT(fr.metrics.mutations == 0u, "stable frame reports no mutations");

	xtk_rt_destroy(rt);
	xtk_retained_host_destroy(inner);
	return 0;
}

typedef struct NavModel {
	int count;
} NavModel;

static XtkEl *build_nav_view(XtkUi *ui, void *model) {
	static XtkNavItemDesc const items [] = {
	  {.kind = XTK_NAV_ITEM, .icon = "Home",    .label = "Home"   },
	  {.kind = XTK_NAV_ITEM, .icon = "Library", .label = "Library"},
	};
	NavModel *m = ( NavModel * ) model;
	return xtk_nav(
	  ui, (XtkNavDesc) {.items = items, .nitem = 2, .sel = 1, .app_title = "Nav"},
	  xtk_kids(xtk_text(ui, xtk_fmt(ui, "Update %d", m->count), (XtkTextDesc) {0}))
	);
}

static int test_byte_props_survive_capture(void) {
	XtkHost *inner = xtk_retained_host_create();
	EXPECT(inner, "byte capture host");
	Mock         mock = {0};
	CountingHost ch;
	wrap_host(&ch, inner, &mock);
	NavModel model = {0};
	XtkRtCfg cfg   = {.request_frame = request_frame};
	XtkRt   *rt
	  = xtk_rt_create(&ch.base, &cfg, ( XentNodeId ) ch.base.vt->root(&ch.base), &model, noop_update, build_nav_view);
	EXPECT(rt, "byte capture runtime");
	EXPECT(xtk_rt_frame(rt).status == XTK_FRAME_COMMITTED, "byte capture mount");

	reset_mock(&mock);
	for (int i = 1; i <= 64; i++) {
		model.count = i;
		xtk_rt_invalidate(rt);
		EXPECT(xtk_rt_frame(rt).status == XTK_FRAME_COMMITTED, "byte capture update");
	}
	EXPECT(mock.nav_model_sets == 0, "unchanged byte property is never re-emitted");

	EXPECT(xtk_rt_destroy(rt), "byte capture runtime destroy");
	xtk_retained_host_destroy(inner);
	return 0;
}

static int test_identity_rejection(void) {
	XtkHost     *inner = xtk_retained_host_create();
	Mock         mock  = {0};
	CountingHost ch;
	wrap_host(&ch, inner, &mock);
	Model    model = {.mixed = true};
	XtkRtCfg cfg   = {.request_frame = request_frame};
	XtkRt   *rt
	  = xtk_rt_create(&ch.base, &cfg, ( XentNodeId ) ch.base.vt->root(&ch.base), &model, noop_update, build_view);
	EXPECT(rt, "runtime");
	XtkFrameResult fr = xtk_rt_frame(rt);
	EXPECT(fr.status == XTK_FRAME_IDENTITY_FAILED, "mixed keys rejected");
	EXPECT(mock.prepares == 0, "no prepare on identity failure");
	EXPECT(!rt->root, "no composition published");
	EXPECT(fr.identity.error == XTK_IDENTITY_MIXED, "mixed diagnostic kind");
	EXPECT(fr.identity.child_a == 0 && fr.identity.child_b == 1, "mixed diagnostic children");
	EXPECT(fr.identity.path_depth == 0u && fr.identity.frame_sequence == 1u, "mixed diagnostic frame/path");
	EXPECT(xtk_rt_destroy(rt), "mixed runtime destroy");

	model = (Model) {.duplicate = true};
	rt    = xtk_rt_create(&ch.base, &cfg, ( XentNodeId ) ch.base.vt->root(&ch.base), &model, noop_update, build_view);
	EXPECT(rt, "duplicate runtime");
	fr = xtk_rt_frame(rt);
	EXPECT(fr.status == XTK_FRAME_IDENTITY_FAILED, "duplicate keys rejected");
	EXPECT(fr.identity.error == XTK_IDENTITY_DUPLICATE_KEY, "duplicate diagnostic kind");
	EXPECT(fr.identity.child_a == 0 && fr.identity.child_b == 1, "duplicate diagnostic children");
	EXPECT(strcmp(fr.identity.key, "duplicate") == 0, "duplicate diagnostic key copy");
	EXPECT(fr.identity.path_depth == 0u, "duplicate diagnostic root path");
	EXPECT(xtk_rt_destroy(rt), "duplicate runtime destroy");

	model = (Model) {.duplicate_scalar = true};
	rt    = xtk_rt_create(&ch.base, &cfg, ( XentNodeId ) ch.base.vt->root(&ch.base), &model, noop_update, build_view);
	EXPECT(rt, "duplicate scalar runtime");
	fr = xtk_rt_frame(rt);
	EXPECT(fr.status == XTK_FRAME_IDENTITY_FAILED, "duplicate scalar keys rejected");
	EXPECT(fr.identity.key_kind == XTK_KEY_U64 && fr.identity.key_u64 == 42u, "scalar diagnostic preserves identity");
	EXPECT(strcmp(fr.identity.key, "42") == 0, "scalar diagnostic formats identity");
	EXPECT(xtk_rt_destroy(rt), "duplicate scalar runtime destroy");

	model = (Model) {.nested_mixed = true};
	rt    = xtk_rt_create(&ch.base, &cfg, ( XentNodeId ) ch.base.vt->root(&ch.base), &model, noop_update, build_view);
	EXPECT(rt, "nested identity runtime");
	fr = xtk_rt_frame(rt);
	EXPECT(fr.status == XTK_FRAME_IDENTITY_FAILED, "nested mixed keys rejected");
	EXPECT(fr.identity.path_depth == 1u && fr.identity.path [0] == 0, "nested diagnostic parent path");
	EXPECT(xtk_rt_destroy(rt), "nested runtime destroy");

	rt = xtk_rt_create(
	  &ch.base, &cfg, ( XentNodeId ) ch.base.vt->root(&ch.base), &model, noop_update, build_unknown_view
	);
	EXPECT(rt, "unknown identity runtime");
	fr = xtk_rt_frame(rt);
	EXPECT(fr.status == XTK_FRAME_IDENTITY_FAILED, "unknown component rejected");
	EXPECT(fr.identity.error == XTK_IDENTITY_INVALID_TYPE, "unknown component diagnostic");
	EXPECT(xtk_rt_destroy(rt), "unknown identity runtime destroy");

	rt = xtk_rt_create(
	  &ch.base, &cfg, ( XentNodeId ) ch.base.vt->root(&ch.base), &model, noop_update, build_malformed_view
	);
	EXPECT(rt, "malformed identity runtime");
	fr = xtk_rt_frame(rt);
	EXPECT(fr.status == XTK_FRAME_IDENTITY_FAILED, "malformed child rejected");
	EXPECT(fr.identity.error == XTK_IDENTITY_MALFORMED, "malformed child diagnostic");
	EXPECT(mock.prepares == 0, "malformed child never reaches Host");
	EXPECT(xtk_rt_destroy(rt), "malformed identity runtime destroy");
	xtk_retained_host_destroy(inner);
	return 0;
}

static int test_component_reconcile(void) {
	XtkHost *host = xtk_retained_host_create();
	EXPECT(host, "component reconcile host");
	EXPECT(xtk_retained_register_component(host, &txn_component_type), "component registration");
	TxnComponentProps model = {.value = 7};
	XtkRtCfg          cfg   = {.request_frame = request_frame};
	XtkRt            *rt
	  = xtk_rt_create(host, &cfg, ( XentNodeId ) host->vt->root(host), &model, noop_update, build_component_view);
	EXPECT(rt, "component reconcile runtime");
	EXPECT(xtk_rt_frame(rt).status == XTK_FRAME_COMMITTED, "component mount through reconciler");
	EXPECT(rt->root->type_id == TXN_COMPONENT_ID, "component identity retained");
	EXPECT(txn_component_mounted == 7, "component CREATE owns props");
	model.value = 9;
	xtk_rt_invalidate(rt);
	EXPECT(xtk_rt_frame(rt).status == XTK_FRAME_COMMITTED, "component props update through batch");
	EXPECT(txn_component_updated == 9, "component SET_PROP owns props");
	EXPECT(xtk_rt_destroy(rt), "component reconcile unmount");
	xtk_retained_host_destroy(host);
	return 0;
}

static int test_positional_and_keyed_ops(void) {
	XtkHost     *inner = xtk_retained_host_create();
	Mock         mock  = {0};
	CountingHost ch;
	wrap_host(&ch, inner, &mock);
	Model    model = {.count = 4, .keyed = false};
	XtkRtCfg cfg   = {.request_frame = request_frame};
	XtkRt   *rt
	  = xtk_rt_create(&ch.base, &cfg, ( XentNodeId ) ch.base.vt->root(&ch.base), &model, noop_update, build_view);
	EXPECT(rt, "runtime");
	EXPECT(xtk_rt_frame(rt).status == XTK_FRAME_COMMITTED, "positional mount");

	reset_mock(&mock);
	model.count = 5;
	xtk_rt_invalidate(rt);
	EXPECT(xtk_rt_frame(rt).status == XTK_FRAME_COMMITTED, "positional append");
	EXPECT(mock.creates == 1 && mock.moves == 0, "append one create zero move");

	reset_mock(&mock);
	model.keyed = true;
	xtk_rt_invalidate(rt);
	EXPECT(xtk_rt_frame(rt).status == XTK_FRAME_COMMITTED, "positional to keyed transition");
	EXPECT(mock.creates == 5 && mock.destroys == 5, "identity mode transition replaces all children");

	xtk_rt_destroy(rt);

	model = (Model) {.count = 4, .keyed = true};
	reset_mock(&mock);
	rt = xtk_rt_create(&ch.base, &cfg, ( XentNodeId ) ch.base.vt->root(&ch.base), &model, noop_update, build_view);
	EXPECT(xtk_rt_frame(rt).status == XTK_FRAME_COMMITTED, "keyed mount");
	reset_mock(&mock);
	model.reverse = true;
	xtk_rt_invalidate(rt);
	EXPECT(xtk_rt_frame(rt).status == XTK_FRAME_COMMITTED, "keyed reverse");
	EXPECT(mock.creates == 0 && mock.destroys == 0, "reverse retains");
	EXPECT(mock.moves == 3, "reverse is n-1 moves");

	xtk_rt_destroy(rt);
	xtk_retained_host_destroy(inner);
	return 0;
}

static int test_all_keyed_permutations(void) {
	enum
	{
		COUNT = 8,
	};

	XtkHost *inner = xtk_retained_host_create();
	EXPECT(inner, "permutation host");
	Mock         mock = {0};
	CountingHost ch;
	wrap_host(&ch, inner, &mock);
	int      order [COUNT] = {0, 1, 2, 3, 4, 5, 6, 7};
	int      old [COUNT]   = {0, 1, 2, 3, 4, 5, 6, 7};
	Model    model         = {.count = COUNT, .keyed = true, .order = order};
	XtkRtCfg cfg           = {.request_frame = request_frame};
	XtkRt   *rt
	  = xtk_rt_create(&ch.base, &cfg, ( XentNodeId ) ch.base.vt->root(&ch.base), &model, noop_update, build_view);
	EXPECT(rt, "permutation runtime");
	EXPECT(xtk_rt_frame(rt).status == XTK_FRAME_COMMITTED, "permutation mount");
	XtkCtrl handles [COUNT];
	for (int i = 0; i < COUNT; i++) handles [i] = ( XtkCtrl ) rt->root->children [i]->node;

	do {
		int expected_moves = COUNT - reference_lis(old, order, COUNT);
		reset_mock(&mock);
		xtk_rt_invalidate(rt);
		EXPECT(xtk_rt_frame(rt).status == XTK_FRAME_COMMITTED, "permutation commit");
		EXPECT(mock.creates == 0 && mock.destroys == 0, "permutation preserves identity");
		EXPECT(mock.moves == expected_moves, "permutation uses minimum moves");
		EXPECT(order_matches(rt, &ch.base, handles, order, COUNT), "permutation host/composition order");
		memcpy(old, order, sizeof(old));
	}
	while (next_permutation(order, COUNT));

	EXPECT(xtk_rt_destroy(rt), "permutation runtime destroy");
	xtk_retained_host_destroy(inner);
	return 0;
}

static int apply_keyed_order(
  XtkRt *rt, Mock *mock, Model *model, int const *order, int count, int creates, int destroys, int moves
) {
	reset_mock(mock);
	model->order = order;
	model->count = count;
	xtk_rt_invalidate(rt);
	EXPECT(xtk_rt_frame(rt).status == XTK_FRAME_COMMITTED, "keyed edit commit");
	EXPECT(mock->creates == creates, "keyed edit create count");
	EXPECT(mock->destroys == destroys, "keyed edit destroy count");
	EXPECT(mock->moves == moves, "keyed edit move count");
	return 0;
}

static int test_keyed_edit_counts(void) {
	XtkHost *inner = xtk_retained_host_create();
	EXPECT(inner, "keyed edit host");
	Mock         mock = {0};
	CountingHost ch;
	wrap_host(&ch, inner, &mock);
	int      initial [] = {0, 1, 2, 3};
	Model    model      = {.count = 4, .keyed = true, .scalar = true, .order = initial};
	XtkRtCfg cfg        = {.request_frame = request_frame};
	XtkRt   *rt
	  = xtk_rt_create(&ch.base, &cfg, ( XentNodeId ) ch.base.vt->root(&ch.base), &model, noop_update, build_view);
	EXPECT(rt, "keyed edit runtime");
	EXPECT(xtk_rt_frame(rt).status == XTK_FRAME_COMMITTED, "keyed edit mount");

	int append [] = {0, 1, 2, 3, 4, 5};
	if (apply_keyed_order(rt, &mock, &model, append, 6, 2, 0, 0)) return 1;
	int middle_delete [] = {0, 1, 4, 5};
	if (apply_keyed_order(rt, &mock, &model, middle_delete, 4, 0, 2, 0)) return 1;
	int prepend [] = {-2, -1, 0, 1, 4, 5};
	if (apply_keyed_order(rt, &mock, &model, prepend, 6, 2, 0, 0)) return 1;
	int rotate [] = {-1, 0, 1, 4, 5, -2};
	if (apply_keyed_order(rt, &mock, &model, rotate, 6, 0, 0, 1)) return 1;
	int adjacent [] = {-1, 1, 0, 4, 5, -2};
	if (apply_keyed_order(rt, &mock, &model, adjacent, 6, 0, 0, 1)) return 1;

	EXPECT(xtk_rt_destroy(rt), "keyed edit runtime destroy");
	xtk_retained_host_destroy(inner);
	return 0;
}

static int test_overflow_snapshot_drain(void) {
	XtkHost     *inner = xtk_retained_host_create();
	CountingHost ch;
	Mock         mock = {0};
	wrap_host(&ch, inner, &mock);
	int      drained = 0;
	Model    model   = {.count = 1};
	XtkRtCfg cfg     = {.request_frame = request_frame};
	XtkRt   *rt
	  = xtk_rt_create(&ch.base, &cfg, ( XentNodeId ) ch.base.vt->root(&ch.base), &model, noop_update, build_view);
	EXPECT(rt, "runtime");
	EXPECT(xtk_rt_frame(rt).status == XTK_FRAME_COMMITTED, "mount");

	for (int i = 0; i < 10; i++) EXPECT(xtk_rt_post(rt, xtk_msg(i + 1)) == XTK_POST_ACCEPTED, "post");
	XtkFrameResult fr = xtk_rt_frame(rt);
	EXPECT(fr.messages_drained == 10u, "snapshot drains 10");
	( void ) drained;

	for (int i = 0; i < XTK_QUEUE_CAP; i++) xtk_rt_post(rt, xtk_msg(1));
	EXPECT(xtk_rt_post(rt, xtk_msg(1)) == XTK_POST_FULL, "full");
	XtkOverflowStatus ov = xtk_rt_overflow(rt);
	EXPECT(ov.sticky && ov.dropped_since_ack >= 1u, "overflow sticky");
	ov = xtk_rt_overflow(rt);
	EXPECT(ov.sticky, "inspect non-destructive");
	xtk_rt_ackoverflow(rt);
	EXPECT(!xtk_rt_overflow(rt).sticky, "ack clears");

	xtk_rt_destroy(rt);
	xtk_retained_host_destroy(inner);
	return 0;
}

typedef struct FrameBoundaryModel {
	XtkRt         *runtime;
	int            updates;
	int            views;
	int            requests;
	bool           injected;
	XtkFrameStatus nested_status;
} FrameBoundaryModel;

static void count_request(void *ctx) { (( FrameBoundaryModel * ) ctx)->requests++; }

static void boundary_update(void *model, XtkMsg msg) {
	FrameBoundaryModel *m = ( FrameBoundaryModel * ) model;
	m->updates++;
	if (m->injected || msg.tag != 1) return;
	m->injected = true;
	( void ) xtk_rt_post(m->runtime, xtk_msg(2));
	m->nested_status = xtk_rt_frame(m->runtime).status;
}

static XtkEl *boundary_view(XtkUi *ui, void *model) {
	FrameBoundaryModel *m = ( FrameBoundaryModel * ) model;
	m->views++;
	return xtk_text(ui, "frame", (XtkTextDesc) {0});
}

static int test_frame_boundary_and_scheduler(void) {
	XtkHost           *host  = xtk_retained_host_create();
	FrameBoundaryModel model = {0};
	XtkRtCfg           cfg   = {.ctx = &model, .request_frame = count_request};
	XtkRt *rt = xtk_rt_create(host, &cfg, ( XentNodeId ) host->vt->root(host), &model, boundary_update, boundary_view);
	EXPECT(rt, "boundary runtime");
	model.runtime = rt;
	EXPECT(xtk_rt_frame(rt).status == XTK_FRAME_COMMITTED, "boundary mount");
	int views      = model.views;

	model.requests = 0;
	EXPECT(xtk_rt_post(rt, xtk_msg(1)) == XTK_POST_ACCEPTED, "boundary first post");
	EXPECT(xtk_rt_post(rt, xtk_msg(3)) == XTK_POST_ACCEPTED, "boundary coalesced post");
	EXPECT(model.requests == 1, "scheduler coalesces queued posts");
	XtkFrameResult first = xtk_rt_frame(rt);
	EXPECT(first.messages_drained == 2u, "frame drains entry snapshot only");
	EXPECT(model.updates == 2, "entry messages updated");
	EXPECT(model.nested_status == XTK_FRAME_DEFERRED, "nested frame deferred");
	EXPECT(first.pending, "message posted during update remains pending");
	EXPECT(model.views == views + 1, "one view for snapshot frame");

	XtkFrameResult second = xtk_rt_frame(rt);
	EXPECT(second.messages_drained == 1u, "next frame drains injected message");
	EXPECT(model.updates == 3, "injected message updated once");
	EXPECT(model.views == views + 2, "one view for next frame");

	for (int i = 0; i < XTK_QUEUE_CAP; i++) EXPECT(xtk_rt_post(rt, xtk_msg(4)) == XTK_POST_ACCEPTED, "fill queue");
	rt->dropped_total     = UINT32_MAX - 1u;
	rt->dropped_since_ack = UINT32_MAX - 1u;
	EXPECT(xtk_rt_post(rt, xtk_msg(4)) == XTK_POST_FULL, "first saturating drop");
	EXPECT(xtk_rt_post(rt, xtk_msg(4)) == XTK_POST_FULL, "second saturating drop");
	XtkOverflowStatus overflow = xtk_rt_overflow(rt);
	EXPECT(overflow.dropped_total == UINT32_MAX, "drop total saturates");
	EXPECT(overflow.dropped_since_ack == UINT32_MAX, "drop acknowledgement count saturates");

	EXPECT(xtk_rt_destroy(rt), "boundary runtime destroy");
	xtk_retained_host_destroy(host);
	return 0;
}

static XtkEl *visual_props_view(XtkUi *ui, void *model) {
	( void ) model;
	static char const *const items [] = {"Blue", "Green"};
	return xtk_row(
	  ui,
	  (XtkStackDesc) {
		.align   = XENT_FLEX_ALIGN_CENTER,
		.justify = XENT_FLEX_JUSTIFY_SPACE_BETWEEN,
	  },
	  xtk_kids(
		xtk_button(ui, "Accent", (XtkButtonDesc) {.style = XTK_BUTTON_ACCENT}),
		xtk_text(
		  ui, "Styled",
		  (XtkTextDesc) {
			.size   = 20.0f,
			.weight = XTK_FONT_SEMI_BOLD,
			.align  = XTK_TEXT_CENTER,
			.color  = {.rgba = 0x336699ffu},
		  }
		),
		xtk_slider(
		  ui,
		  (XtkSliderDesc) {
			.min            = 500.0f,
			.max            = 1000.0f,
			.value          = 650.0f,
			.step           = 10.0f,
			.tick           = 20.0f,
			.tick_placement = XTK_TICK_OUTSIDE,
			.snap_to_ticks  = true,
			.small_change   = 10.0f,
			.large_change   = 100.0f}
		),
		xtk_progress(ui, (XtkProgressDesc) {.value = 75.0f, .min = 25.0f, .max = 125.0f}),
		xtk_combo(ui, "Pick", (XtkComboDesc) {.items = items, .nitem = 2, .sel = 1})
	  )
	);
}

static bool prop_is_u32(XtkHost *host, XtkCtrl control, XtkPropertyId id, XtkValueKind kind, uint32_t value) {
	XtkValueView view;
	if (!host->vt->prop(host, control, id, &view, NULL) || view.kind != kind) return false;
	return kind == XTK_VALUE_COLOR ? view.u.color.rgba == value : view.u.u32 == value;
}

static bool prop_is_f32(XtkHost *host, XtkCtrl control, XtkPropertyId id, float value);

static int  test_visual_props_are_encoded(void) {
	XtkHost *host = xtk_retained_host_create();
	EXPECT(host, "visual props host");
	XtkRtCfg cfg = {0};
	XtkRt   *rt  = xtk_rt_create(host, &cfg, ( XentNodeId ) host->vt->root(host), NULL, noop_update, visual_props_view);
	EXPECT(rt && xtk_rt_frame(rt).status == XTK_FRAME_COMMITTED, "visual props mount");
	XtkCtrl root     = ( XtkCtrl ) xtk_node_id(rt->root);
	XtkCtrl button   = host->vt->first(host, root);
	XtkCtrl text     = host->vt->next(host, button);
	XtkCtrl slider   = host->vt->next(host, text);
	XtkCtrl progress = host->vt->next(host, slider);
	XtkCtrl combo    = host->vt->next(host, progress);
	EXPECT(
	  prop_is_u32(host, root, XTK_PROP_ALIGN_ITEMS, XTK_VALUE_ENUM, XENT_FLEX_ALIGN_CENTER), "stack align encoded"
	);
	EXPECT(
	  prop_is_u32(host, root, XTK_PROP_JUSTIFY_CONTENT, XTK_VALUE_ENUM, XENT_FLEX_JUSTIFY_SPACE_BETWEEN),
	  "stack justify encoded"
	);
	EXPECT(prop_is_u32(host, button, XTK_PROP_BUTTON_STYLE, XTK_VALUE_ENUM, XTK_BUTTON_ACCENT), "button style encoded");
	EXPECT(prop_is_u32(host, text, XTK_PROP_FONT_WEIGHT, XTK_VALUE_ENUM, XTK_FONT_SEMI_BOLD), "text weight encoded");
	EXPECT(prop_is_u32(host, text, XTK_PROP_TEXT_ALIGN, XTK_VALUE_ENUM, XTK_TEXT_CENTER), "text alignment encoded");
	EXPECT(prop_is_u32(host, text, XTK_PROP_FOREGROUND, XTK_VALUE_COLOR, 0x336699ffu), "text color encoded");
	EXPECT(prop_is_f32(host, slider, XTK_PROP_MIN_F32, 500.0f), "slider minimum encoded");
	EXPECT(prop_is_f32(host, slider, XTK_PROP_MAX_F32, 1000.0f), "slider maximum encoded");
	EXPECT(prop_is_f32(host, slider, XTK_PROP_VALUE_F32, 650.0f), "slider value encoded");
	EXPECT(prop_is_f32(host, slider, XTK_PROP_STEP_F32, 10.0f), "slider step encoded");
	EXPECT(prop_is_f32(host, slider, XTK_PROP_TICK_FREQUENCY, 20.0f), "slider tick frequency encoded");
	EXPECT(
	  prop_is_u32(host, slider, XTK_PROP_TICK_PLACEMENT, XTK_VALUE_ENUM, XTK_TICK_OUTSIDE),
	  "slider tick placement encoded"
	);
	EXPECT(prop_is_u32(host, slider, XTK_PROP_SLIDER_SNAPS_TO, XTK_VALUE_ENUM, 1u), "slider snap grid encoded");
	EXPECT(prop_is_f32(host, slider, XTK_PROP_SMALL_CHANGE, 10.0f), "slider small change encoded");
	EXPECT(prop_is_f32(host, slider, XTK_PROP_LARGE_CHANGE, 100.0f), "slider large change encoded");
	EXPECT(prop_is_f32(host, progress, XTK_PROP_MIN_F32, 25.0f), "progress minimum encoded");
	EXPECT(prop_is_f32(host, progress, XTK_PROP_MAX_F32, 125.0f), "progress maximum encoded");
	EXPECT(prop_is_f32(host, progress, XTK_PROP_VALUE_F32, 75.0f), "progress value encoded");
	XtkValueView placeholder;
	XtkValueView selected;
	XtkValueView items;
	EXPECT(
	  host->vt->prop(host, combo, XTK_PROP_PLACEHOLDER, &placeholder, NULL)
		&& placeholder.kind == XTK_VALUE_STRING
		&& placeholder.u.string.len == 4u
		&& memcmp(placeholder.u.string.data, "Pick", 4u) == 0,
	  "combo placeholder encoded"
	);
	EXPECT(
	  host->vt->prop(host, combo, XTK_PROP_SELECTED_INDEX, &selected, NULL)
		&& selected.kind == XTK_VALUE_I32
		&& selected.u.i32 == 1,
	  "combo selection encoded"
	);
	EXPECT(
	  host->vt->prop(host, combo, XTK_PROP_ITEMS, &items, NULL)
		&& items.kind == XTK_VALUE_BYTES
		&& items.u.bytes.len == 11u
		&& memcmp(items.u.bytes.data, "Blue\0Green\0", 11u) == 0,
	  "combo items encoded"
	);
	EXPECT(host->vt->first(host, combo) == XTK_CTRL_INVALID, "combo items are data, not retained children");
	EXPECT(xtk_rt_destroy(rt), "visual props destroy");
	xtk_retained_host_destroy(host);
	return 0;
}

static XtkEl *host_contract_props_view(XtkUi *ui, void *model) {
	( void ) model;
	static char const *const suggestions [] = {"Amsterdam", "Athens"};
	return xtk_column(
	  ui, (XtkStackDesc) {0},
	  xtk_kids(
		xtk_infobar(
		  ui, "Network", "Connection restored.", (XtkInfoBarDesc) {.severity = XTK_INFOBAR_SUCCESS, .closable = true}
		),
		xtk_expander(
		  ui, "Details", (XtkExpanderDesc) {.expanded = true, .w = 320.0f, .contenth = 96.0f},
		  xtk_kids(xtk_text(ui, "Body", (XtkTextDesc) {0}))
		),
		xtk_refresh(
		  ui,
		  (XtkRefreshDesc) {
			.direction       = XTK_PULL_LEFT_TO_RIGHT,
			.visualizer_size = 144.0f,
			.threshold_ratio = 0.65f,
			.is_refreshing   = true,
		  },
		  xtk_kids(xtk_text(ui, "Rows", (XtkTextDesc) {0}))
		),
		xtk_flip(
		  ui, (XtkFlipDesc) {.sel = 1, .vertical = true},
		  xtk_kids(xtk_text(ui, "One", (XtkTextDesc) {0}), xtk_text(ui, "Two", (XtkTextDesc) {0}))
		),
		xtk_pips(
		  ui, (XtkPipsDesc) {.nitem = 9, .sel = 6, .max_visible = 5, .vertical = true, .nav = XTK_PIPS_NAV_VISIBLE}
		),
		xtk_suggest(
		  ui, "Search cities",
		  (XtkAutoSuggestDesc) {
			.content = "Am", .suggestions = suggestions, .nitem = 2, .query_icon = "Find", .disabled = true}
		)
	  )
	);
}

static bool prop_is_bool(XtkHost *host, XtkCtrl control, XtkPropertyId id, bool value) {
	XtkValueView view;
	return host->vt->prop(host, control, id, &view, NULL) && view.kind == XTK_VALUE_BOOL && view.u.b == value;
}

static bool prop_is_i32(XtkHost *host, XtkCtrl control, XtkPropertyId id, int32_t value) {
	XtkValueView view;
	return host->vt->prop(host, control, id, &view, NULL) && view.kind == XTK_VALUE_I32 && view.u.i32 == value;
}

static bool prop_is_f32(XtkHost *host, XtkCtrl control, XtkPropertyId id, float value) {
	XtkValueView view;
	return host->vt->prop(host, control, id, &view, NULL) && view.kind == XTK_VALUE_F32 && view.u.f32 == value;
}

static bool prop_is_f64(XtkHost *host, XtkCtrl control, XtkPropertyId id, double value) {
	XtkValueView view;
	return host->vt->prop(host, control, id, &view, NULL) && view.kind == XTK_VALUE_F64 && view.u.f64 == value;
}

static bool prop_is_resource(XtkHost *host, XtkCtrl control, XtkPropertyId id, XtkResource value) {
	XtkValueView view;
	return host->vt->prop(host, control, id, &view, NULL)
	    && view.kind == XTK_VALUE_RESOURCE
	    && view.u.resource == value;
}

static bool prop_is_string(XtkHost *host, XtkCtrl control, XtkPropertyId id, char const *value) {
	XtkValueView view;
	size_t       len = strlen(value);
	return host->vt->prop(host, control, id, &view, NULL)
	    && view.kind == XTK_VALUE_STRING
	    && view.u.string.len == len
	    && memcmp(view.u.string.data, value, len) == 0;
}

static int test_host_contract_props_are_encoded(void) {
	XtkHost *host = xtk_retained_host_create();
	EXPECT(host, "host contract props host");
	XtkRtCfg cfg = {0};
	XtkRt   *rt
	  = xtk_rt_create(host, &cfg, ( XentNodeId ) host->vt->root(host), NULL, noop_update, host_contract_props_view);
	EXPECT(rt && xtk_rt_frame(rt).status == XTK_FRAME_COMMITTED, "host contract props mount");
	XtkCtrl root     = ( XtkCtrl ) xtk_node_id(rt->root);
	XtkCtrl info     = host->vt->first(host, root);
	XtkCtrl expander = host->vt->next(host, info);
	XtkCtrl refresh  = host->vt->next(host, expander);
	XtkCtrl flip     = host->vt->next(host, refresh);
	XtkCtrl pips     = host->vt->next(host, flip);
	XtkCtrl suggest  = host->vt->next(host, pips);

	EXPECT(prop_is_string(host, info, XTK_PROP_TEXT, "Network"), "info title encoded");
	EXPECT(prop_is_string(host, info, XTK_PROP_MESSAGE, "Connection restored."), "info message encoded");
	EXPECT(prop_is_u32(host, info, XTK_PROP_SEVERITY, XTK_VALUE_ENUM, XTK_INFOBAR_SUCCESS), "info severity");
	EXPECT(prop_is_bool(host, info, XTK_PROP_CLOSABLE, true), "info closable");
	EXPECT(prop_is_string(host, expander, XTK_PROP_TEXT, "Details"), "expander header encoded");
	EXPECT(prop_is_f32(host, expander, XTK_PROP_WIDTH, 320.0f), "expander width");
	EXPECT(prop_is_f32(host, expander, XTK_PROP_CONTENT_HEIGHT, 96.0f), "expander content height");
	EXPECT(prop_is_bool(host, expander, XTK_PROP_EXPANDED, true), "expander expanded");
	EXPECT(
	  prop_is_u32(host, refresh, XTK_PROP_PULL_DIRECTION, XTK_VALUE_ENUM, XTK_PULL_LEFT_TO_RIGHT), "refresh direction"
	);
	EXPECT(prop_is_f32(host, refresh, XTK_PROP_VISUALIZER_SIZE, 144.0f), "refresh visualizer size");
	EXPECT(prop_is_f32(host, refresh, XTK_PROP_THRESHOLD_RATIO, 0.65f), "refresh threshold");
	EXPECT(prop_is_bool(host, refresh, XTK_PROP_REFRESHING, true), "refresh state");
	EXPECT(prop_is_i32(host, flip, XTK_PROP_SELECTED_INDEX, 1), "flip selection");
	EXPECT(prop_is_u32(host, flip, XTK_PROP_ORIENTATION, XTK_VALUE_ENUM, 1u), "flip orientation");
	EXPECT(prop_is_i32(host, pips, XTK_PROP_ITEM_COUNT, 9), "pips count");
	EXPECT(prop_is_i32(host, pips, XTK_PROP_SELECTED_INDEX, 6), "pips selection");
	EXPECT(prop_is_i32(host, pips, XTK_PROP_MAX_VISIBLE, 5), "pips visible count");
	EXPECT(prop_is_u32(host, pips, XTK_PROP_NAV_VISIBILITY, XTK_VALUE_ENUM, XTK_PIPS_NAV_VISIBLE), "pips nav");
	EXPECT(prop_is_string(host, suggest, XTK_PROP_PLACEHOLDER, "Search cities"), "suggest placeholder");
	EXPECT(prop_is_string(host, suggest, XTK_PROP_TEXT, "Am"), "suggest content");
	EXPECT(prop_is_string(host, suggest, XTK_PROP_ICON, "Find"), "suggest query icon");
	EXPECT(prop_is_bool(host, suggest, XTK_PROP_ENABLED, false), "suggest enabled state");
	XtkValueView items;
	EXPECT(
	  host->vt->prop(host, suggest, XTK_PROP_ITEMS, &items, NULL)
		&& items.kind == XTK_VALUE_BYTES
		&& items.u.bytes.len == 17u
		&& memcmp(items.u.bytes.data, "Amsterdam\0Athens\0", 17u) == 0,
	  "suggestions encoded"
	);

	EXPECT(xtk_rt_destroy(rt), "host contract props destroy");
	xtk_retained_host_destroy(host);
	return 0;
}

static XtkEl *extended_contract_props_view(XtkUi *ui, void *model) {
	( void ) model;
	static XtkTreeNodeDesc const roots [] = {
	  {.text = "Root"},
	};
	return xtk_column(
	  ui, (XtkStackDesc) {0},
	  xtk_kids(
		xtk_link(ui, "Project", (XtkHyperlinkDesc) {.url = "https://xent.dev", .disabled = true}),
		xtk_image(ui, (XtkImageDesc) {.source = 17u, .stretch = XTK_IMAGE_UNIFORM}),
		xtk_badge(ui, (XtkBadgeDesc) {.mode = XTK_BADGE_ICON, .value = 7, .icon = "Mail"}),
		xtk_dialog(
		  ui, "Confirm",
		  (XtkDialogDesc) {
			.open = true, .primary = "Save", .secondary = "Later", .close = "Cancel", .w = 480.0f, .contenth = 180.0f},
		  xtk_kids(xtk_text(ui, "Body", (XtkTextDesc) {0}))
		),
		xtk_teachtip(
		  ui, "Hint",
		  (XtkTeachingTipDesc) {
			.open             = true,
			.subtitle         = "Details",
			.icon             = "Info",
			.action_text      = "Apply",
			.action_accent    = true,
			.close_text       = "Dismiss",
			.placement        = XTK_TIP_PLACE_BOTTOM,
			.untargeted       = true,
			.light_dismiss    = true,
			.tail             = 2,
			.placement_margin = 12.0f},
		  xtk_kids()
		),
		xtk_avatar(
		  ui,
		  (XtkPersonPictureDesc) {
			.display_name = "Ada Lovelace",
			.initials     = "AL",
			.image        = 23u,
			.badge_glyph  = "Star",
			.badge_number = 9,
			.size         = 88.0f,
			.is_group     = true}
		),
		xtk_pager(
		  ui,
		  (XtkPagerDesc) {
			.nitem        = 12,
			.sel          = 3,
			.display_mode = XTK_PAGER_DISPLAY_NUMBER_TEXT,
			.first_button = XTK_PAGER_BUTTON_ALWAYS,
			.prev_button  = XTK_PAGER_BUTTON_HIDDEN_EDGE,
			.next_button  = XTK_PAGER_BUTTON_NONE,
			.last_button  = XTK_PAGER_BUTTON_ALWAYS,
			.prefix       = "Page",
			.suffix       = "of"}
		),
		xtk_splitview(
		  ui,
		  (XtkSplitViewDesc) {
			.pane_open           = true,
			.display_mode        = XTK_SPLITVIEW_COMPACT_OVERLAY,
			.pane_placement      = XTK_SPLITVIEW_RIGHT,
			.open_pane_length    = 280.0f,
			.compact_pane_length = 52.0f},
		  xtk_text(ui, "Pane", (XtkTextDesc) {0}), xtk_text(ui, "Content", (XtkTextDesc) {0})
		),
		xtk_titlebar(
		  ui, "Xent",
		  (XtkTitleBarDesc) {
			.subtitle         = "Editor",
			.icon             = "App",
			.show_back        = true,
			.back_disabled    = true,
			.show_pane_toggle = true,
			.integrate_window = true}
		),
		xtk_rating(
		  ui,
		  (XtkRatingDesc) {
			.value             = 3.5,
			.max_rating        = 7,
			.placeholder_value = 2.5,
			.initial_set_value = 2,
			.is_clear_enabled  = true,
			.is_read_only      = true,
			.caption           = "Good"}
		),
		xtk_number(
		  ui, (XtkNumberDesc) {.min = -5.0, .max = 15.0, .step = 0.5, .value = 4.5, .disabled = true, .hide_spin = true}
		),
		xtk_tree(ui, (XtkTreeDesc) {.roots = roots, .nroot = 1, .sel = 0})
	  )
	);
}

static XtkCtrl next_control(XtkHost *host, XtkCtrl control) { return host->vt->next(host, control); }

static int     test_extended_contract_props_are_encoded(void) {
	XtkHost *host = xtk_retained_host_create();
	EXPECT(host, "extended contract host");
	XtkRtCfg cfg = {0};
	XtkRt   *rt
	  = xtk_rt_create(host, &cfg, ( XentNodeId ) host->vt->root(host), NULL, noop_update, extended_contract_props_view);
	EXPECT(rt && xtk_rt_frame(rt).status == XTK_FRAME_COMMITTED, "extended contract mount");
	XtkCtrl controls [12];
	controls [0] = host->vt->first(host, ( XtkCtrl ) xtk_node_id(rt->root));
	for (int i = 1; i < 12; i++) controls [i] = next_control(host, controls [i - 1]);

	EXPECT(prop_is_string(host, controls [0], XTK_PROP_URL, "https://xent.dev"), "hyperlink url");
	EXPECT(prop_is_bool(host, controls [0], XTK_PROP_ENABLED, false), "hyperlink disabled");
	EXPECT(prop_is_resource(host, controls [1], XTK_PROP_IMAGE_SOURCE, 17u), "image resource");
	EXPECT(prop_is_u32(host, controls [1], XTK_PROP_IMAGE_STRETCH, XTK_VALUE_ENUM, XTK_IMAGE_UNIFORM), "image stretch");
	EXPECT(prop_is_u32(host, controls [2], XTK_PROP_BADGE_MODE, XTK_VALUE_ENUM, XTK_BADGE_ICON), "badge mode");
	EXPECT(prop_is_i32(host, controls [2], XTK_PROP_BADGE_VALUE, 7), "badge value");
	EXPECT(prop_is_string(host, controls [3], XTK_PROP_PRIMARY_TEXT, "Save"), "dialog primary");
	EXPECT(prop_is_string(host, controls [3], XTK_PROP_SECONDARY_TEXT, "Later"), "dialog secondary");
	EXPECT(prop_is_string(host, controls [3], XTK_PROP_CLOSE_TEXT, "Cancel"), "dialog close");
	EXPECT(prop_is_bool(host, controls [3], XTK_PROP_OPEN, true), "dialog open");
	EXPECT(prop_is_string(host, controls [4], XTK_PROP_SUBTITLE, "Details"), "teaching tip subtitle");
	EXPECT(prop_is_string(host, controls [4], XTK_PROP_ACTION_TEXT, "Apply"), "teaching tip action");
	EXPECT(prop_is_bool(host, controls [4], XTK_PROP_UNTARGETED, true), "teaching tip untargeted");
	EXPECT(prop_is_f32(host, controls [4], XTK_PROP_PLACEMENT_MARGIN, 12.0f), "teaching tip margin");
	EXPECT(prop_is_string(host, controls [5], XTK_PROP_INITIALS, "AL"), "avatar initials");
	EXPECT(prop_is_resource(host, controls [5], XTK_PROP_IMAGE_SOURCE, 23u), "avatar resource");
	EXPECT(prop_is_i32(host, controls [5], XTK_PROP_BADGE_VALUE, 9), "avatar badge");
	EXPECT(prop_is_bool(host, controls [5], XTK_PROP_IS_GROUP, true), "avatar group");
	EXPECT(prop_is_i32(host, controls [6], XTK_PROP_ITEM_COUNT, 12), "pager count");
	EXPECT(prop_is_string(host, controls [6], XTK_PROP_PREFIX, "Page"), "pager prefix");
	EXPECT(prop_is_string(host, controls [6], XTK_PROP_SUFFIX, "of"), "pager suffix");
	EXPECT(prop_is_bool(host, controls [7], XTK_PROP_OPEN, true), "split view open");
	EXPECT(
	  prop_is_u32(host, controls [7], XTK_PROP_PANE_PLACEMENT, XTK_VALUE_ENUM, XTK_SPLITVIEW_RIGHT),
	  "split view placement"
	);
	EXPECT(prop_is_string(host, controls [8], XTK_PROP_SUBTITLE, "Editor"), "title bar subtitle");
	EXPECT(prop_is_bool(host, controls [8], XTK_PROP_INTEGRATE_WINDOW, true), "title bar integration");
	EXPECT(prop_is_f64(host, controls [9], XTK_PROP_PLACEHOLDER_F64, 2.5), "rating placeholder");
	EXPECT(prop_is_bool(host, controls [9], XTK_PROP_READ_ONLY, true), "rating read only");
	EXPECT(prop_is_bool(host, controls [10], XTK_PROP_HIDE_SPIN, true), "number hide spin");
	EXPECT(prop_is_bool(host, controls [10], XTK_PROP_ENABLED, false), "number disabled");
	EXPECT(prop_is_i32(host, controls [11], XTK_PROP_SELECTED_INDEX, 0), "tree selected index");

	EXPECT(xtk_rt_destroy(rt), "extended contract destroy");
	xtk_retained_host_destroy(host);
	return 0;
}

typedef struct BindingModel {
	XtkMsg invoke;
} BindingModel;

static XtkEl *build_binding_view(XtkUi *ui, void *model) {
	BindingModel *m = ( BindingModel * ) model;
	return xtk_button(ui, "invoke", (XtkButtonDesc) {.click = m->invoke});
}

static int test_binding_publication_is_atomic(void) {
	XtkHost *inner = xtk_retained_host_create();
	EXPECT(inner, "binding host");
	Mock         mock = {0};
	CountingHost ch;
	wrap_host(&ch, inner, &mock);
	BindingModel model = {.invoke = xtk_msg_i(7, 1)};
	XtkRtCfg     cfg   = {.request_frame = request_frame};
	XtkRt       *rt    = xtk_rt_create(
	  &ch.base, &cfg, ( XentNodeId ) ch.base.vt->root(&ch.base), &model, noop_update, build_binding_view
	);
	EXPECT(rt, "binding runtime");
	EXPECT(xtk_rt_frame(rt).status == XTK_FRAME_COMMITTED, "binding mount");

	XtkBinding *committed = ( XtkBinding * ) rt->root->binding;
	int         sub_count = rt->root->sub_count;
	EXPECT(committed && committed->msgs [XTK_EVENT_INVOKE].i == 1, "initial binding payload");
	EXPECT(sub_count == 1, "initial subscription");

	model.invoke      = xtk_msg_i(7, 2);
	mock.fail_prepare = true;
	xtk_rt_invalidate(rt);
	EXPECT(xtk_rt_frame(rt).status == XTK_FRAME_PREPARE_FAILED, "binding update fails");
	EXPECT(rt->root->binding == committed, "failed frame preserves binding pointer");
	EXPECT((( XtkBinding * ) rt->root->binding)->msgs [XTK_EVENT_INVOKE].i == 1, "failed frame preserves payload");
	EXPECT(rt->root->sub_count == sub_count, "failed frame preserves subscriptions");

	mock.fail_prepare = false;
	EXPECT(xtk_rt_frame(rt).status == XTK_FRAME_COMMITTED, "binding retry commits");
	EXPECT(rt->root->binding != committed, "binding published after commit");
	EXPECT((( XtkBinding * ) rt->root->binding)->msgs [XTK_EVENT_INVOKE].i == 2, "payload-only change published");

	model.invoke = xtk_msg(0);
	xtk_rt_invalidate(rt);
	EXPECT(xtk_rt_frame(rt).status == XTK_FRAME_COMMITTED, "binding removal commits");
	EXPECT(!rt->root->binding, "binding removed");
	EXPECT(rt->root->sub_count == 0, "subscription count cleared");

	model.invoke = xtk_msg_i(7, 3);
	xtk_rt_invalidate(rt);
	EXPECT(xtk_rt_frame(rt).status == XTK_FRAME_COMMITTED, "binding recreation commits");
	EXPECT(rt->root->binding, "binding recreated");
	EXPECT(rt->root->sub_count == 1, "subscription recreated");

	XtkNode *root     = rt->root;
	mock.fail_prepare = true;
	EXPECT(!xtk_rt_destroy(rt), "failed unmount preserves runtime");
	EXPECT(rt->root == root && rt->root->binding, "failed unmount preserves composition");
	mock.fail_prepare = false;
	EXPECT(xtk_rt_destroy(rt), "unmount retry destroys runtime");
	xtk_retained_host_destroy(inner);
	return 0;
}

static int test_host_phase_failures_are_atomic(void) {
	XtkHost *inner = xtk_retained_host_create();
	EXPECT(inner, "phase host");
	Mock         mock = {0};
	CountingHost ch;
	wrap_host(&ch, inner, &mock);
	char const *before [] = {"before"};
	char const *after []  = {"after"};
	Model       model     = {.count = 1, .labels = before};
	XtkRtCfg    cfg       = {.request_frame = request_frame};
	XtkRt      *rt
	  = xtk_rt_create(&ch.base, &cfg, ( XentNodeId ) ch.base.vt->root(&ch.base), &model, noop_update, build_view);
	EXPECT(rt, "phase runtime");
	EXPECT(xtk_rt_frame(rt).status == XTK_FRAME_COMMITTED, "phase mount");
	XtkNode *root  = rt->root;
	void    *props = rt->root->children [0]->props;
	uint64_t rev   = ch.base.vt->revision(&ch.base);
	model.labels   = after;

	reset_mock(&mock);
	mock.fail_preflight = true;
	xtk_rt_invalidate(rt);
	EXPECT(xtk_rt_frame(rt).status == XTK_FRAME_PREFLIGHT_FAILED, "Host preflight failure reported");
	EXPECT(rt->root == root && rt->root->children [0]->props == props, "preflight failure preserves composition");
	EXPECT(ch.base.vt->revision(&ch.base) == rev, "preflight failure preserves Host");

	reset_mock(&mock);
	EXPECT(xtk_rt_frame(rt).status == XTK_FRAME_COMMITTED, "preflight retry commits");
	props        = rt->root->children [0]->props;
	rev          = ch.base.vt->revision(&ch.base);
	model.labels = before;

	reset_mock(&mock);
	mock.fail_commit = true;
	xtk_rt_invalidate(rt);
	EXPECT(xtk_rt_frame(rt).status == XTK_FRAME_COMMIT_FAILED, "Host commit failure reported");
	EXPECT(rt->root == root && rt->root->children [0]->props == props, "commit failure preserves composition");
	EXPECT(ch.base.vt->revision(&ch.base) == rev, "commit failure preserves Host");

	reset_mock(&mock);
	EXPECT(xtk_rt_frame(rt).status == XTK_FRAME_COMMITTED, "commit retry commits");
	EXPECT(xtk_rt_destroy(rt), "phase runtime destroy");
	xtk_retained_host_destroy(inner);
	return 0;
}

typedef struct EventModel {
	char text [16];
	int  index;
} EventModel;

static void capture_query(void *model, XtkMsg msg) {
	EventModel *m = ( EventModel * ) model;
	if (msg.tag != 9) return;
	snprintf(m->text, sizeof(m->text), "%s", ( char const * ) msg.ptr);
	m->index = msg.i;
}

static XtkEl *build_query_view(XtkUi *ui, void *model) {
	( void ) model;
	return xtk_suggest(ui, "query", (XtkAutoSuggestDesc) {.query = xtk_msg(9)});
}

static int test_event_payload_survives_queue(void) {
	XtkHost *host = xtk_retained_host_create();
	EXPECT(host, "event host");
	EventModel model = {0};
	XtkRtCfg   cfg   = {.request_frame = request_frame};
	XtkRt *rt = xtk_rt_create(host, &cfg, ( XentNodeId ) host->vt->root(host), &model, capture_query, build_query_view);
	EXPECT(rt, "event runtime");
	EXPECT(xtk_rt_frame(rt).status == XTK_FRAME_COMMITTED, "event mount");

	char    query [] = "save";
	XtkCtrl control  = ( XtkCtrl ) rt->root->node;
	XtkEvent event = {
	  .id             = XTK_EVENT_QUERY,
	  .source         = control,
	  .target         = control,
	  .current_target = control,
	  .phase          = XTK_EVENT_PHASE_TARGET,
	  .payload        = {
	    .kind    = XTK_EVENT_PAYLOAD_QUERY,
	    .u.query = {.text = query, .len = 4u, .index = 2},
	  },
	};
	EXPECT(host->vt->dispatch(host, &event) & XTK_EVENT_HANDLED, "query dispatched");
	query [0] = 'X';
	EXPECT(xtk_rt_frame(rt).status == XTK_FRAME_COMMITTED, "query frame");
	EXPECT(strcmp(model.text, "save") == 0, "queued query owns text");
	EXPECT(model.index == 2, "queued query keeps index");

	xtk_rt_destroy(rt);
	xtk_retained_host_destroy(host);
	return 0;
}

int main(void) {
	if (test_one_prepare_per_dirty_frame()) return 1;
	if (test_byte_props_survive_capture()) return 1;
	if (test_identity_rejection()) return 1;
	if (test_component_reconcile()) return 1;
	if (test_positional_and_keyed_ops()) return 1;
	if (test_all_keyed_permutations()) return 1;
	if (test_keyed_edit_counts()) return 1;
	if (test_overflow_snapshot_drain()) return 1;
	if (test_frame_boundary_and_scheduler()) return 1;
	if (test_visual_props_are_encoded()) return 1;
	if (test_host_contract_props_are_encoded()) return 1;
	if (test_extended_contract_props_are_encoded()) return 1;
	if (test_binding_publication_is_atomic()) return 1;
	if (test_host_phase_failures_are_atomic()) return 1;
	if (test_event_payload_survives_queue()) return 1;
	printf("PASS: xtk reconcile transaction\n");
	return 0;
}
