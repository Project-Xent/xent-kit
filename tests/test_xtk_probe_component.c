#include <stdio.h>
#include <string.h>
#include <xtk/xtk_batch.h>
#include <xtk/xtk_catalog.h>
#include <xtk/xtk_component.h>
#include <xtk/xtk_event.h>
#include "xtk_retained.h"

#include "xtk_alloc_internal.h"

#define EXPECT(cond, msg)              \
	do {                               \
		if (!(cond)) {                 \
			printf("FAIL: %s\n", msg); \
			return 1;                  \
		}                              \
	}                                  \
	while (0)

enum
{
	PROBE_ID = XTK_CTRL_ID_COMPONENT_BASE + 1u,
};

typedef struct ProbeProps {
	int32_t value;
	int32_t fail_mount;
	int32_t fail_update;
} ProbeProps;

typedef struct ProbeState {
	uint32_t   mount_count;
	uint32_t   update_count;
	uint32_t   event_count;
	uint32_t   dl_revision;
	int32_t    provider_token;
	XentNodeId private_leaf;
} ProbeState;

typedef struct ProbePrepare {
	ProbeProps  props;
	ProbeState *existing;
	ProbeState *mounted;
	XentCtx    *ctx;
	XtkCtrl     impl_root;
	bool        is_update;
	int32_t     provider_token;
} ProbePrepare;

typedef struct ProbeProvider {
	uint32_t abi_version;
	int32_t  token;
} ProbeProvider;

enum
{
	PROBE_PROVIDER_ID = 42u,
};

static uint32_t            g_unmounts;

static XtkPropertyId const probe_props []  = {XTK_PROP_COMPONENT_PROPS};
static XtkEventId const    probe_events [] = {XTK_EVENT_INVOKE};

static XtkCtrlDesc const   probe_desc      = {
  .id                  = PROBE_ID,
  .name                = "probe",
  .properties          = probe_props,
  .property_count      = 1u,
  .events              = probe_events,
  .event_count         = 1u,
  .create_invalidates  = XTK_INVALIDATE_LAYOUT | XTK_INVALIDATE_PAINT,
  .destroy_invalidates = XTK_INVALIDATE_LAYOUT | XTK_INVALIDATE_PAINT,
};

static XtkCompErr probe_prepare_mount(XtkCompHost *host, XtkCtrl node, void const *props, XtkCompPrep **out) {
	( void ) node;
	ProbeProps const *p = ( ProbeProps const * ) props;
	if (p && p->fail_mount) return XTK_COMPONENT_ERR_FAILED;
	ProbeProvider const *prov
	  = ( ProbeProvider const * ) xtk_component_query_provider(host, PROBE_PROVIDER_ID, sizeof(ProbeProvider));
	if (!prov) return XTK_COMPONENT_ERR_PROVIDER;
	ProbePrepare *prep = ( ProbePrepare * ) xtk_alloc_zero(1, sizeof(*prep));
	if (!prep) return XTK_COMPONENT_ERR_OOM;
	ProbeState *state = ( ProbeState * ) xtk_alloc_zero(1, sizeof(*state));
	if (!state) {
		xtk_alloc_free(prep);
		return XTK_COMPONENT_ERR_OOM;
	}
	if (p) prep->props = *p;
	prep->ctx             = xtk_component_context(host);
	prep->impl_root       = xtk_component_impl_root(host);
	prep->provider_token  = prov->token;
	prep->mounted         = state;
	state->mount_count    = 1u;
	state->provider_token = prep->provider_token;
	state->dl_revision    = 1u;
	state->private_leaf   = xent_node_create(prep->ctx);
	if (state->private_leaf == XENT_NODE_INVALID
		|| !xent_node_append(prep->ctx, ( XentNodeId ) prep->impl_root, state->private_leaf))
	{
		if (state->private_leaf != XENT_NODE_INVALID) xent_node_destroy(prep->ctx, state->private_leaf);
		xtk_alloc_free(state);
		xtk_alloc_free(prep);
		return XTK_COMPONENT_ERR_OOM;
	}
	*out = ( XtkCompPrep * ) prep;
	return XTK_COMPONENT_OK;
}

static XtkCompErr probe_prepare_update(
  XtkCompHost *host, XtkCtrl node, void *state, void const *previous_props, void const *next_props, XtkCompPrep **out
) {
	( void ) node;
	( void ) previous_props;
	ProbeProps const *p = ( ProbeProps const * ) next_props;
	if (p && p->fail_update) return XTK_COMPONENT_ERR_FAILED;
	ProbePrepare *prep = ( ProbePrepare * ) xtk_alloc_zero(1, sizeof(*prep));
	if (!prep) return XTK_COMPONENT_ERR_OOM;
	if (p) prep->props = *p;
	prep->existing  = ( ProbeState * ) state;
	prep->ctx       = xtk_component_context(host);
	prep->impl_root = xtk_component_impl_root(host);
	prep->is_update = true;
	*out            = ( XtkCompPrep * ) prep;
	return XTK_COMPONENT_OK;
}

static void *probe_commit_mount(XtkCompPrep *raw) {
	ProbePrepare *prep  = ( ProbePrepare * ) raw;
	ProbeState   *state = prep->mounted;
	prep->mounted       = NULL;
	xtk_alloc_free(prep);
	return state;
}

static void probe_commit_update(XtkCompPrep *raw) {
	ProbePrepare *prep = ( ProbePrepare * ) raw;
	if (prep->existing) {
		prep->existing->update_count += 1u;
		prep->existing->dl_revision  += 1u;
	}
	xtk_alloc_free(prep);
}

static void probe_abort(XtkCompPrep *raw) {
	ProbePrepare *prep = ( ProbePrepare * ) raw;
	if (prep->mounted) {
		if (prep->mounted->private_leaf != XENT_NODE_INVALID) xent_node_destroy(prep->ctx, prep->mounted->private_leaf);
		xtk_alloc_free(prep->mounted);
	}
	xtk_alloc_free(prep);
}

static uint32_t probe_event(XtkCompHost *host, XtkCtrl target, void *state, XtkEvent const *event) {
	( void ) host;
	( void ) target;
	ProbeState *st = ( ProbeState * ) state;
	if (st && event && event->id == XTK_EVENT_INVOKE) st->event_count += 1u;
	return XTK_EVENT_HANDLED;
}

static void probe_unmount(XtkCompHost *host, XtkCtrl node, void *state) {
	( void ) host;
	( void ) node;
	g_unmounts += 1u;
	xtk_alloc_free(state);
}

static XtkCompType const probe_type = {
  .abi_version = 1u,
  .control     = &probe_desc,
  .props_size  = sizeof(ProbeProps),
  .copy_props  = NULL,
  .ops =
	{
	  .prepare_mount  = probe_prepare_mount,
	  .prepare_update = probe_prepare_update,
	  .commit_mount   = probe_commit_mount,
	  .commit_update  = probe_commit_update,
	  .abort          = probe_abort,
	  .event          = probe_event,
	  .unmount        = probe_unmount,
	},
};

static XtkBatchResult *commit_ok(XtkHost *host, XtkBatch *batch) {
	XtkPrepare  *prepare = NULL;
	XtkBatchDiag diagnostic;
	if (host->vt->prepare(host, batch, &prepare, &diagnostic) != XTK_BATCH_OK || !prepare) return NULL;
	return host->vt->commit(host, prepare, &diagnostic);
}

static XtkValue props_value(ProbeProps const *p) {
	return (XtkValue) {
	  .kind = XTK_VALUE_BYTES, .u.bytes = {.data = ( uint8_t * ) ( uintptr_t ) p, .len = ( uint32_t ) sizeof(*p)}
    };
}

static XtkHost *probe_host_create(void) {
	static ProbeProvider const   provider     = {.abi_version = 1u, .token = 1};
	static XtkProviderDesc const providers [] = {
	  {.id = PROBE_PROVIDER_ID, .abi_version = 1u, .iface_size = sizeof(provider), .iface = &provider}
    };
	XtkHost *host = xtk_retained_host_create();
	if (!host) return NULL;
	if (xtk_retained_register_component(host, &probe_type) && xtk_retained_set_providers(host, providers, 1u))
		return host;
	xtk_retained_host_destroy(host);
	return NULL;
}

static XtkCtrl probe_try_mount(XtkHost *host, ProbeProps const *props) {
	XtkBatch *batch = xtk_batch_alloc(host->vt->revision(host));
	if (!batch) return XTK_CTRL_INVALID;
	XtkPropPatch    patch   = {.id = XTK_PROP_COMPONENT_PROPS, .value = props_value(props), .change = {0}};
	XtkLocalId      local   = xtk_batch_create(batch, PROBE_ID, xtk_ref_none(), xtk_ref_none(), &patch, 1u);
	XtkBatchResult *result  = local == XTK_LOCAL_INVALID ? NULL : commit_ok(host, batch);
	XtkCtrl         control = result && result->control_count == 1u ? result->controls [0].control : XTK_CTRL_INVALID;
	xtk_batch_result_destroy(result);
	xtk_batch_free(batch);
	return control;
}

static bool probe_try_update(XtkHost *host, XtkCtrl control, ProbeProps const *props) {
	XtkBatch *batch = xtk_batch_alloc(host->vt->revision(host));
	if (!batch) return false;
	XtkValue value = props_value(props);
	bool     pushed
	  = xtk_batch_set(batch, xtk_ref_existing(control), XTK_PROP_COMPONENT_PROPS, value, (XtkChangeStamp) {0});
	XtkBatchResult *result = pushed ? commit_ok(host, batch) : NULL;
	xtk_batch_free(batch);
	if (!result) return false;
	xtk_batch_result_destroy(result);
	return true;
}

static bool probe_try_drop(XtkHost *host, XtkCtrl control) {
	XtkBatch *batch = xtk_batch_alloc(host->vt->revision(host));
	if (!batch) return false;
	XtkBatchResult *result = xtk_batch_drop(batch, xtk_ref_existing(control)) ? commit_ok(host, batch) : NULL;
	xtk_batch_free(batch);
	if (!result) return false;
	xtk_batch_result_destroy(result);
	return true;
}

static int test_mount_update_destroy(void) {
	g_unmounts                   = 0u;
	ProbeProvider   provider     = {.abi_version = 1u, .token = 99};
	XtkProviderDesc providers [] = {
	  {.id = PROBE_PROVIDER_ID, .abi_version = 1u, .iface_size = sizeof(provider), .iface = &provider}
    };

	XtkHost *host = xtk_retained_host_create();
	EXPECT(host, "host");
	EXPECT(xtk_retained_register_component(host, &probe_type), "register");
	EXPECT(xtk_retained_set_providers(host, providers, 1u), "providers");

	ProbeProps   props = {.value = 1};
	XtkPropPatch patch = {.id = XTK_PROP_COMPONENT_PROPS, .value = props_value(&props), .change = {0}};
	XtkBatch    *batch = xtk_batch_alloc(host->vt->revision(host));
	XtkLocalId   local = xtk_batch_create(batch, PROBE_ID, xtk_ref_none(), xtk_ref_none(), &patch, 1u);
	EXPECT(local != XTK_LOCAL_INVALID, "create local");
	XtkBatchResult *result = commit_ok(host, batch);
	EXPECT(result && result->control_count == 1u, "commit create");
	XtkCtrl probe = result->controls [0].control;
	EXPECT(host->vt->live(host, probe), "live");
	EXPECT(xtk_retained_component_content_root(host, probe) != XTK_CTRL_INVALID, "content root");
	EXPECT(xtk_retained_component_impl_root(host, probe) != XTK_CTRL_INVALID, "impl root");
	XtkCtrl impl = xtk_retained_component_impl_root(host, probe);
	EXPECT(host->vt->first(host, impl) != XTK_CTRL_INVALID, "private leaf");

	xtk_batch_result_destroy(result);
	xtk_batch_free(batch);

	ProbeProps   next = {.value = 2};
	XtkPropPatch up   = {.id = XTK_PROP_COMPONENT_PROPS, .value = props_value(&next), .change = {0}};
	batch             = xtk_batch_alloc(host->vt->revision(host));
	EXPECT(xtk_batch_set(batch, xtk_ref_existing(probe), up.id, up.value, up.change), "set props");
	result = commit_ok(host, batch);
	EXPECT(result, "commit update");
	xtk_batch_result_destroy(result);
	xtk_batch_free(batch);

	XtkEvent ev = {
	  .id     = XTK_EVENT_INVOKE,
	  .target = probe,
	  .source = probe,
	  .phase  = XTK_EVENT_PHASE_TARGET,
	};
	EXPECT(xtk_retained_route(host, &ev) & XTK_EVENT_HANDLED, "event");

	batch = xtk_batch_alloc(host->vt->revision(host));
	EXPECT(xtk_batch_drop(batch, xtk_ref_existing(probe)), "destroy");
	result = commit_ok(host, batch);
	EXPECT(result, "commit destroy");
	EXPECT(g_unmounts == 1u, "unmounted once");
	EXPECT(!host->vt->live(host, probe), "dead");
	xtk_batch_result_destroy(result);
	xtk_batch_free(batch);
	xtk_retained_host_destroy(host);
	return 0;
}

static int test_fail_mount_rolls_back(void) {
	ProbeProvider   provider     = {.abi_version = 1u, .token = 1};
	XtkProviderDesc providers [] = {
	  {.id = PROBE_PROVIDER_ID, .abi_version = 1u, .iface_size = sizeof(provider), .iface = &provider}
    };
	XtkHost *host = xtk_retained_host_create();
	EXPECT(xtk_retained_register_component(host, &probe_type), "register");
	EXPECT(xtk_retained_set_providers(host, providers, 1u), "providers");
	uint64_t     rev   = host->vt->revision(host);

	ProbeProps   props = {.fail_mount = 1};
	XtkPropPatch patch = {.id = XTK_PROP_COMPONENT_PROPS, .value = props_value(&props), .change = {0}};
	XtkBatch    *batch = xtk_batch_alloc(rev);
	xtk_batch_create(batch, PROBE_ID, xtk_ref_none(), xtk_ref_none(), &patch, 1u);
	XtkPrepare  *prepare = NULL;
	XtkBatchDiag diagnostic;
	EXPECT(host->vt->prepare(host, batch, &prepare, &diagnostic) == XTK_BATCH_OK, "prepare ok");
	EXPECT(host->vt->commit(host, prepare, &diagnostic) == NULL, "commit fails");
	EXPECT(host->vt->revision(host) == rev, "revision unchanged");
	EXPECT(host->vt->first(host, host->vt->root(host)) == XTK_CTRL_INVALID, "no child");
	xtk_batch_free(batch);
	xtk_retained_host_destroy(host);
	return 0;
}

static int test_fail_update_rolls_back(void) {
	ProbeProvider   provider     = {.abi_version = 1u, .token = 1};
	XtkProviderDesc providers [] = {
	  {.id = PROBE_PROVIDER_ID, .abi_version = 1u, .iface_size = sizeof(provider), .iface = &provider}
    };
	XtkHost *host = xtk_retained_host_create();
	EXPECT(xtk_retained_register_component(host, &probe_type), "register");
	EXPECT(xtk_retained_set_providers(host, providers, 1u), "providers");

	ProbeProps   props = {.value = 3};
	XtkPropPatch patch = {.id = XTK_PROP_COMPONENT_PROPS, .value = props_value(&props), .change = {0}};
	XtkBatch    *batch = xtk_batch_alloc(host->vt->revision(host));
	xtk_batch_create(batch, PROBE_ID, xtk_ref_none(), xtk_ref_none(), &patch, 1u);
	XtkBatchResult *result = commit_ok(host, batch);
	EXPECT(result, "create");
	XtkCtrl probe = result->controls [0].control;
	xtk_batch_result_destroy(result);
	xtk_batch_free(batch);

	uint64_t     rev = host->vt->revision(host);
	ProbeProps   bad = {.fail_update = 1};
	XtkPropPatch up  = {.id = XTK_PROP_COMPONENT_PROPS, .value = props_value(&bad), .change = {0}};
	batch            = xtk_batch_alloc(rev);
	xtk_batch_set(batch, xtk_ref_existing(probe), up.id, up.value, up.change);
	XtkPrepare  *prepare = NULL;
	XtkBatchDiag diagnostic;
	EXPECT(host->vt->prepare(host, batch, &prepare, &diagnostic) == XTK_BATCH_OK, "prepare");
	EXPECT(host->vt->commit(host, prepare, &diagnostic) == NULL, "commit fails");
	EXPECT(host->vt->revision(host) == rev, "rev");
	EXPECT(host->vt->live(host, probe), "still live");
	xtk_batch_free(batch);
	xtk_retained_host_destroy(host);
	return 0;
}

static int test_missing_provider(void) {
	XtkHost *host = xtk_retained_host_create();
	EXPECT(xtk_retained_register_component(host, &probe_type), "register");
	ProbeProps   props = {0};
	XtkPropPatch patch = {.id = XTK_PROP_COMPONENT_PROPS, .value = props_value(&props), .change = {0}};
	XtkBatch    *batch = xtk_batch_alloc(host->vt->revision(host));
	xtk_batch_create(batch, PROBE_ID, xtk_ref_none(), xtk_ref_none(), &patch, 1u);
	XtkPrepare  *prepare = NULL;
	XtkBatchDiag diagnostic;
	EXPECT(host->vt->prepare(host, batch, &prepare, &diagnostic) == XTK_BATCH_OK, "prepare");
	EXPECT(host->vt->commit(host, prepare, &diagnostic) == NULL, "no provider");
	xtk_batch_free(batch);
	xtk_retained_host_destroy(host);
	return 0;
}

static int test_mount_allocation_sweep(void) {
	bool saw_failure = false;
	bool saw_success = false;
	for (uint64_t fail_at = 1u; fail_at <= 256u; fail_at++) {
		xtk_alloc_test_reset();
		XtkHost *host = probe_host_create();
		EXPECT(host, "mount sweep host");
		uint64_t   rev   = host->vt->revision(host);
		ProbeProps props = {.value = 1};
		xtk_alloc_test_reset();
		xtk_alloc_fail_at(fail_at);
		XtkCtrl       control = probe_try_mount(host, &props);
		XtkAllocStats stats   = xtk_alloc_test_stats();
		xtk_alloc_test_reset();
		if (control != XTK_CTRL_INVALID) {
			EXPECT(stats.failures == 0u, "mount never commits after injected failure");
			saw_success = true;
			xtk_retained_host_destroy(host);
			break;
		}
		saw_failure = true;
		EXPECT(stats.failures == 1u, "mount sweep faults one allocation");
		EXPECT(host->vt->revision(host) == rev, "failed mount preserves revision");
		EXPECT(host->vt->first(host, host->vt->root(host)) == XTK_CTRL_INVALID, "failed mount publishes nothing");
		xtk_retained_host_destroy(host);
	}
	EXPECT(saw_failure && saw_success, "mount sweep reaches every allocation");
	return 0;
}

static int test_update_allocation_sweep(void) {
	bool saw_failure = false;
	bool saw_success = false;
	for (uint64_t fail_at = 1u; fail_at <= 256u; fail_at++) {
		xtk_alloc_test_reset();
		XtkHost *host = probe_host_create();
		EXPECT(host, "update sweep host");
		ProbeProps before  = {.value = 1};
		XtkCtrl    control = probe_try_mount(host, &before);
		EXPECT(control != XTK_CTRL_INVALID, "update sweep mount");
		uint64_t   rev   = host->vt->revision(host);

		ProbeProps after = {.value = 2};
		xtk_alloc_test_reset();
		xtk_alloc_fail_at(fail_at);
		bool          updated = probe_try_update(host, control, &after);
		XtkAllocStats stats   = xtk_alloc_test_stats();
		xtk_alloc_test_reset();
		if (updated) {
			EXPECT(stats.failures == 0u, "update never commits after injected failure");
			saw_success = true;
			xtk_retained_host_destroy(host);
			break;
		}
		saw_failure = true;
		EXPECT(stats.failures == 1u, "update sweep faults one allocation");
		EXPECT(host->vt->revision(host) == rev && host->vt->live(host, control), "failed update is atomic");
		EXPECT(probe_try_update(host, control, &after), "failed update retries");
		xtk_retained_host_destroy(host);
	}
	EXPECT(saw_failure && saw_success, "update sweep reaches every allocation");
	return 0;
}

static int test_unmount_allocation_sweep(void) {
	bool saw_failure = false;
	bool saw_success = false;
	for (uint64_t fail_at = 1u; fail_at <= 256u; fail_at++) {
		xtk_alloc_test_reset();
		XtkHost *host = probe_host_create();
		EXPECT(host, "unmount sweep host");
		ProbeProps props   = {.value = 1};
		XtkCtrl    control = probe_try_mount(host, &props);
		EXPECT(control != XTK_CTRL_INVALID, "unmount sweep mount");
		uint64_t rev = host->vt->revision(host);
		g_unmounts   = 0u;

		xtk_alloc_test_reset();
		xtk_alloc_fail_at(fail_at);
		bool          dropped = probe_try_drop(host, control);
		XtkAllocStats stats   = xtk_alloc_test_stats();
		xtk_alloc_test_reset();
		if (dropped) {
			EXPECT(stats.failures == 0u && g_unmounts == 1u, "unmount commits exactly once");
			saw_success = true;
			xtk_retained_host_destroy(host);
			break;
		}
		saw_failure = true;
		EXPECT(stats.failures == 1u, "unmount sweep faults one allocation");
		EXPECT(host->vt->revision(host) == rev && host->vt->live(host, control), "failed unmount is atomic");
		EXPECT(g_unmounts == 0u, "failed unmount does not call component");
		EXPECT(probe_try_drop(host, control) && g_unmounts == 1u, "failed unmount retries once");
		xtk_retained_host_destroy(host);
	}
	EXPECT(saw_failure && saw_success, "unmount sweep reaches every allocation");
	return 0;
}

static int test_providers_lock_after_prepare(void) {
	ProbeProvider   provider     = {.abi_version = 1u, .token = 1};
	XtkProviderDesc providers [] = {
	  {.id = PROBE_PROVIDER_ID, .abi_version = 1u, .iface_size = sizeof(provider), .iface = &provider}
    };
	XtkHost *host = xtk_retained_host_create();
	EXPECT(xtk_retained_register_component(host, &probe_type), "register");
	EXPECT(xtk_retained_set_providers(host, providers, 1u), "providers before prepare");

	XtkBatch    *batch   = xtk_batch_alloc(host->vt->revision(host));
	XtkPrepare  *prepare = NULL;
	XtkBatchDiag diagnostic;
	EXPECT(host->vt->prepare(host, batch, &prepare, &diagnostic) == XTK_BATCH_OK, "prepare");
	EXPECT(prepare, "prepare object");
	EXPECT(!xtk_retained_set_providers(host, providers, 1u), "providers locked after prepare");
	host->vt->abort(host, prepare);
	EXPECT(!xtk_retained_set_providers(host, providers, 1u), "providers stay locked after abort");
	xtk_batch_free(batch);
	xtk_retained_host_destroy(host);
	return 0;
}

static int test_create_destroy_same_batch(void) {
	g_unmounts                   = 0u;
	ProbeProvider   provider     = {.abi_version = 1u, .token = 7};
	XtkProviderDesc providers [] = {
	  {.id = PROBE_PROVIDER_ID, .abi_version = 1u, .iface_size = sizeof(provider), .iface = &provider}
    };
	XtkHost *host = xtk_retained_host_create();
	EXPECT(xtk_retained_register_component(host, &probe_type), "register");
	EXPECT(xtk_retained_set_providers(host, providers, 1u), "providers");

	ProbeProps   props = {.value = 1};
	XtkPropPatch patch = {.id = XTK_PROP_COMPONENT_PROPS, .value = props_value(&props), .change = {0}};
	XtkBatch    *batch = xtk_batch_alloc(host->vt->revision(host));
	XtkLocalId   local = xtk_batch_create(batch, PROBE_ID, xtk_ref_none(), xtk_ref_none(), &patch, 1u);
	EXPECT(local != XTK_LOCAL_INVALID, "create");
	EXPECT(xtk_batch_drop(batch, xtk_ref_local(local)), "destroy same batch");
	XtkBatchResult *result = commit_ok(host, batch);
	EXPECT(result, "commit");
	EXPECT(g_unmounts == 1u, "unmounted after mount+destroy");
	EXPECT(result->control_count == 1u, "one mapping");
	EXPECT(result->controls [0].control == XTK_CTRL_INVALID, "destroyed create maps invalid");
	xtk_batch_result_destroy(result);
	xtk_batch_free(batch);
	xtk_retained_host_destroy(host);
	return 0;
}

static int test_update_then_destroy_same_batch(void) {
	g_unmounts                   = 0u;
	ProbeProvider   provider     = {.abi_version = 1u, .token = 3};
	XtkProviderDesc providers [] = {
	  {.id = PROBE_PROVIDER_ID, .abi_version = 1u, .iface_size = sizeof(provider), .iface = &provider}
    };
	XtkHost *host = xtk_retained_host_create();
	EXPECT(xtk_retained_register_component(host, &probe_type), "register");
	EXPECT(xtk_retained_set_providers(host, providers, 1u), "providers");

	ProbeProps   props = {.value = 1};
	XtkPropPatch patch = {.id = XTK_PROP_COMPONENT_PROPS, .value = props_value(&props), .change = {0}};
	XtkBatch    *batch = xtk_batch_alloc(host->vt->revision(host));
	xtk_batch_create(batch, PROBE_ID, xtk_ref_none(), xtk_ref_none(), &patch, 1u);
	XtkBatchResult *result = commit_ok(host, batch);
	EXPECT(result, "create");
	XtkCtrl probe = result->controls [0].control;
	xtk_batch_result_destroy(result);
	xtk_batch_free(batch);

	ProbeProps   next = {.value = 9};
	XtkPropPatch up   = {.id = XTK_PROP_COMPONENT_PROPS, .value = props_value(&next), .change = {0}};
	batch             = xtk_batch_alloc(host->vt->revision(host));
	EXPECT(xtk_batch_set(batch, xtk_ref_existing(probe), up.id, up.value, up.change), "update");
	EXPECT(xtk_batch_drop(batch, xtk_ref_existing(probe)), "destroy");
	result = commit_ok(host, batch);
	EXPECT(result, "commit update+destroy");
	EXPECT(g_unmounts == 1u, "unmounted once");
	EXPECT(!host->vt->live(host, probe), "dead");
	xtk_batch_result_destroy(result);
	xtk_batch_free(batch);
	xtk_retained_host_destroy(host);
	return 0;
}

static int test_abort_prepare_clears_no_pending(void) {
	ProbeProvider   provider     = {.abi_version = 1u, .token = 1};
	XtkProviderDesc providers [] = {
	  {.id = PROBE_PROVIDER_ID, .abi_version = 1u, .iface_size = sizeof(provider), .iface = &provider}
    };
	XtkHost *host = xtk_retained_host_create();
	EXPECT(xtk_retained_register_component(host, &probe_type), "register");
	EXPECT(xtk_retained_set_providers(host, providers, 1u), "providers");
	uint64_t     rev   = host->vt->revision(host);

	ProbeProps   props = {.value = 1};
	XtkPropPatch patch = {.id = XTK_PROP_COMPONENT_PROPS, .value = props_value(&props), .change = {0}};
	XtkBatch    *batch = xtk_batch_alloc(rev);
	xtk_batch_create(batch, PROBE_ID, xtk_ref_none(), xtk_ref_none(), &patch, 1u);
	XtkPrepare  *prepare = NULL;
	XtkBatchDiag diagnostic;
	EXPECT(host->vt->prepare(host, batch, &prepare, &diagnostic) == XTK_BATCH_OK, "prepare");
	host->vt->abort(host, prepare);
	EXPECT(host->vt->revision(host) == rev, "revision unchanged");
	EXPECT(host->vt->first(host, host->vt->root(host)) == XTK_CTRL_INVALID, "no child");
	xtk_batch_free(batch);
	xtk_retained_host_destroy(host);
	return 0;
}

int main(void) {
	if (test_mount_update_destroy()) return 1;
	if (test_fail_mount_rolls_back()) return 1;
	if (test_fail_update_rolls_back()) return 1;
	if (test_missing_provider()) return 1;
	if (test_mount_allocation_sweep()) return 1;
	if (test_update_allocation_sweep()) return 1;
	if (test_unmount_allocation_sweep()) return 1;
	if (test_providers_lock_after_prepare()) return 1;
	if (test_create_destroy_same_batch()) return 1;
	if (test_update_then_destroy_same_batch()) return 1;
	if (test_abort_prepare_clears_no_pending()) return 1;
	printf("ok\n");
	return 0;
}
