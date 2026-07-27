#include <stdio.h>
#include <string.h>
#include <xtk/xtk_batch.h>
#include <xtk/xtk_catalog.h>
#include <xtk/xtk_event.h>
#include "xtk_retained.h"

#define EXPECT(cond, msg)              \
	do {                               \
		if (!(cond)) {                 \
			printf("FAIL: %s\n", msg); \
			return 1;                  \
		}                              \
	}                                  \
	while (0)

static uint32_t g_events;

static uint32_t on_invoke(void *arg, XtkEvent const *event) {
	( void ) arg;
	( void ) event;
	g_events++;
	return XTK_EVENT_HANDLED;
}

static XtkBatchResult *commit_ok(XtkHost *host, XtkBatch *batch) {
	XtkPrepare  *prepare = NULL;
	XtkBatchDiag diagnostic;
	if (host->vt->prepare(host, batch, &prepare, &diagnostic) != XTK_BATCH_OK || !prepare) {
		printf("FAIL: prepare\n");
		return NULL;
	}
	XtkBatchResult *result = host->vt->commit(host, prepare, &diagnostic);
	if (!result) printf("FAIL: commit result\n");
	return result;
}

static int test_create_prop_topology(void) {
	XtkHost *host = xtk_retained_host_create();
	EXPECT(host, "host");
	uint64_t  rev   = host->vt->revision(host);

	XtkBatch *batch = xtk_batch_alloc(rev);
	XtkValue  text  = {
	  .kind = XTK_VALUE_STRING, .u.string = {.data = "Hi", .len = 2u}
    };
	XtkPropPatch props [] = {
	  {.id = XTK_PROP_TEXT, .value = text, .change = {0}}
    };
	XtkLocalId button  = xtk_batch_create(batch, XTK_CTRL_BUTTON, xtk_ref_none(), xtk_ref_none(), props, 1u);
	XtkLocalId text_id = xtk_batch_create(batch, XTK_CTRL_TEXT, xtk_ref_none(), xtk_ref_none(), NULL, 0u);
	EXPECT(button != XTK_LOCAL_INVALID && text_id != XTK_LOCAL_INVALID, "locals");
	EXPECT(xtk_batch_insert(batch, xtk_ref_local(button), xtk_ref_local(text_id), xtk_ref_none()), "insert");

	XtkBatchResult *result = commit_ok(host, batch);
	if (!result) return 1;
	EXPECT(result->control_count == 2u, "two creates");
	XtkCtrl btn = result->controls [0].control;
	XtkCtrl txt = result->controls [1].control;
	EXPECT(host->vt->live(host, btn) && host->vt->live(host, txt), "live");
	EXPECT(host->vt->type(host, btn) == XTK_CTRL_BUTTON, "button type");
	EXPECT(host->vt->parent(host, txt) == btn, "text parent");
	EXPECT(host->vt->first(host, btn) == txt, "button child");
	EXPECT(host->vt->revision(host) == rev + 1u, "revision advanced");

	XtkValueView   view;
	XtkChangeStamp change;
	EXPECT(host->vt->prop(host, btn, XTK_PROP_TEXT, &view, &change), "get text");
	EXPECT(view.kind == XTK_VALUE_STRING && view.u.string.len == 2u, "text value");
	EXPECT(memcmp(view.u.string.data, "Hi", 2) == 0, "text bytes");

	xtk_batch_result_destroy(result);
	xtk_batch_free(batch);
	xtk_retained_host_destroy(host);
	return 0;
}

static int test_stale_revision_and_abort(void) {
	XtkHost *host = xtk_retained_host_create();
	EXPECT(host, "host");
	XtkBatch *batch = xtk_batch_alloc(host->vt->revision(host));
	EXPECT(
	  xtk_batch_create(batch, XTK_CTRL_BUTTON, xtk_ref_none(), xtk_ref_none(), NULL, 0u) != XTK_LOCAL_INVALID, "create"
	);

	XtkBatch *stale = xtk_batch_alloc(0u);
	EXPECT(
	  xtk_batch_create(stale, XTK_CTRL_TEXT, xtk_ref_none(), xtk_ref_none(), NULL, 0u) != XTK_LOCAL_INVALID,
	  "stale create"
	);
	XtkPrepare  *prepare = NULL;
	XtkBatchDiag diagnostic;
	EXPECT(host->vt->prepare(host, stale, &prepare, &diagnostic) == XTK_BATCH_ERR_STALE_REVISION, "stale");
	EXPECT(prepare == NULL, "no prepare");

	EXPECT(host->vt->prepare(host, batch, &prepare, &diagnostic) == XTK_BATCH_OK, "prepare ok");
	host->vt->abort(host, prepare);
	EXPECT(host->vt->first(host, host->vt->root(host)) == XTK_CTRL_INVALID, "abort no mutate");
	EXPECT(host->vt->revision(host) == 1u, "revision unchanged");

	xtk_batch_free(stale);
	xtk_batch_free(batch);
	xtk_retained_host_destroy(host);
	return 0;
}

static int test_failed_commit_rolls_back(void) {
	XtkHost *host = xtk_retained_host_create();
	EXPECT(host, "host");
	uint64_t        rev   = host->vt->revision(host);

	XtkBatch       *ok    = xtk_batch_alloc(rev);
	XtkLocalId      a     = xtk_batch_create(ok, XTK_CTRL_BUTTON, xtk_ref_none(), xtk_ref_none(), NULL, 0u);
	XtkBatchResult *first = commit_ok(host, ok);
	if (!first) return 1;
	XtkCtrl live = first->controls [0].control;
	xtk_batch_result_destroy(first);
	xtk_batch_free(ok);

	XtkBatch  *bad = xtk_batch_alloc(host->vt->revision(host));
	XtkLocalId b   = xtk_batch_create(bad, XTK_CTRL_TEXT, xtk_ref_none(), xtk_ref_none(), NULL, 0u);
	EXPECT(a != XTK_LOCAL_INVALID && b != XTK_LOCAL_INVALID, "locals");
	EXPECT(
	  xtk_batch_insert(bad, xtk_ref_existing(live), xtk_ref_local(b), xtk_ref_existing(host->vt->root(host))),
	  "queue bad insert"
	);

	XtkPrepare  *prepare = NULL;
	XtkBatchDiag diagnostic;
	EXPECT(host->vt->prepare(host, bad, &prepare, &diagnostic) == XTK_BATCH_OK, "prepare");
	XtkBatchResult *result = host->vt->commit(host, prepare, &diagnostic);
	EXPECT(result == NULL, "commit fails");
	EXPECT(host->vt->revision(host) == rev + 1u, "revision not advanced on failure");
	EXPECT(host->vt->live(host, live), "prior control intact");
	EXPECT(host->vt->first(host, live) == XTK_CTRL_INVALID, "no leaked grandchild");

	xtk_batch_free(bad);
	xtk_retained_host_destroy(host);
	return 0;
}

static int test_create_destroy_same_local(void) {
	XtkHost *host = xtk_retained_host_create();
	EXPECT(host, "host");
	XtkBatch  *batch = xtk_batch_alloc(host->vt->revision(host));
	XtkLocalId local = xtk_batch_create(batch, XTK_CTRL_BUTTON, xtk_ref_none(), xtk_ref_none(), NULL, 0u);
	EXPECT(xtk_batch_drop(batch, xtk_ref_local(local)), "destroy local");
	XtkBatchResult *result = commit_ok(host, batch);
	if (!result) return 1;
	EXPECT(result->control_count == 1u, "one mapping");
	EXPECT(result->controls [0].control == XTK_CTRL_INVALID, "destroyed local maps invalid");
	EXPECT(!host->vt->live(host, result->controls [0].control), "not live");
	xtk_batch_result_destroy(result);
	xtk_batch_free(batch);
	xtk_retained_host_destroy(host);
	return 0;
}

static int test_subscribe_rollback_on_failure(void) {
	XtkHost *host = xtk_retained_host_create();
	EXPECT(host, "host");
	XtkBatch       *setup   = xtk_batch_alloc(host->vt->revision(host));
	XtkLocalId      btn     = xtk_batch_create(setup, XTK_CTRL_BUTTON, xtk_ref_none(), xtk_ref_none(), NULL, 0u);
	XtkBatchResult *created = commit_ok(host, setup);
	if (!created) return 1;
	XtkCtrl button = created->controls [0].control;
	xtk_batch_result_destroy(created);
	xtk_batch_free(setup);

	XtkBatch *bad = xtk_batch_alloc(host->vt->revision(host));
	EXPECT(
	  xtk_batch_on(bad, xtk_ref_existing(button), XTK_EVENT_INVOKE, XTK_EVENT_PHASE_MASK_TARGET, on_invoke, NULL)
		!= XTK_SUB_TOKEN_INVALID,
	  "subscribe"
	);
	XtkLocalId orphan = xtk_batch_create(bad, XTK_CTRL_TEXT, xtk_ref_none(), xtk_ref_none(), NULL, 0u);
	EXPECT(
	  xtk_batch_insert(bad, xtk_ref_existing(button), xtk_ref_local(orphan), xtk_ref_existing(host->vt->root(host))),
	  "bad insert"
	);
	XtkPrepare  *prepare = NULL;
	XtkBatchDiag diagnostic;
	EXPECT(host->vt->prepare(host, bad, &prepare, &diagnostic) == XTK_BATCH_OK, "prepare");
	EXPECT(host->vt->commit(host, prepare, &diagnostic) == NULL, "commit fails");

	g_events       = 0u;
	XtkEvent event = {
	  .id             = XTK_EVENT_INVOKE,
	  .phase          = XTK_EVENT_PHASE_TARGET,
	  .target         = button,
	  .current_target = button,
	  .source         = button};
	host->vt->dispatch(host, &event);
	EXPECT(g_events == 0u, "subscribe rolled back");

	xtk_batch_free(bad);
	xtk_retained_host_destroy(host);
	return 0;
}

static int test_destroy_subtree_sidecar(void) {
	XtkHost *host = xtk_retained_host_create();
	EXPECT(host, "host");
	XtkBatch  *batch  = xtk_batch_alloc(host->vt->revision(host));
	XtkLocalId parent = xtk_batch_create(batch, XTK_CTRL_CONTAINER, xtk_ref_none(), xtk_ref_none(), NULL, 0u);
	XtkLocalId child  = xtk_batch_create(batch, XTK_CTRL_BUTTON, xtk_ref_local(parent), xtk_ref_none(), NULL, 0u);
	XtkSubRef  token
	  = xtk_batch_on(batch, xtk_ref_local(child), XTK_EVENT_INVOKE, XTK_EVENT_PHASE_MASK_TARGET, on_invoke, NULL);
	EXPECT(token != XTK_SUB_TOKEN_INVALID, "child sub");
	EXPECT(xtk_batch_drop(batch, xtk_ref_local(parent)), "destroy parent");
	XtkBatchResult *result = commit_ok(host, batch);
	if (!result) return 1;
	EXPECT(result->control_count == 2u, "two creates");
	EXPECT(result->controls [0].control == XTK_CTRL_INVALID, "parent destroyed");
	EXPECT(result->controls [1].control == XTK_CTRL_INVALID, "child destroyed with subtree");

	g_events       = 0u;
	XtkEvent event = {
	  .id             = XTK_EVENT_INVOKE,
	  .phase          = XTK_EVENT_PHASE_TARGET,
	  .target         = result->controls [1].control,
	  .current_target = result->controls [1].control,
	  .source         = result->controls [1].control,
	};
	host->vt->dispatch(host, &event);
	EXPECT(g_events == 0u, "child subscription purged");

	xtk_batch_result_destroy(result);
	xtk_batch_free(batch);
	xtk_retained_host_destroy(host);
	return 0;
}

static int test_host_preflight_schema(void) {
	XtkHost *host = xtk_retained_host_create();
	EXPECT(host, "host");
	XtkBatch       *setup   = xtk_batch_alloc(host->vt->revision(host));
	XtkLocalId      btn     = xtk_batch_create(setup, XTK_CTRL_BUTTON, xtk_ref_none(), xtk_ref_none(), NULL, 0u);
	XtkBatchResult *created = commit_ok(host, setup);
	if (!created) return 1;
	XtkCtrl button = created->controls [0].control;
	xtk_batch_result_destroy(created);
	xtk_batch_free(setup);

	XtkBatch    *batch = xtk_batch_alloc(host->vt->revision(host));
	XtkBatchDiag diagnostic;
	EXPECT(
	  xtk_batch_set(
		batch, xtk_ref_existing(button), XTK_PROP_TEXT, (XtkValue) {.kind = XTK_VALUE_F32, .u.f32 = 1.f},
		(XtkChangeStamp) {0}
	  ),
	  "queue wrong kind"
	);
	EXPECT(host->vt->preflight(host, batch, &diagnostic) == XTK_BATCH_ERR_INVALID_PROPERTY, "value kind");
	xtk_batch_free(batch);

	batch = xtk_batch_alloc(host->vt->revision(host));
	EXPECT(
	  xtk_batch_on(batch, xtk_ref_existing(button), XTK_EVENT_QUERY, XTK_EVENT_PHASE_MASK_TARGET, on_invoke, NULL)
		!= XTK_SUB_TOKEN_INVALID,
	  "queue unsupported event"
	);
	EXPECT(host->vt->preflight(host, batch, &diagnostic) == XTK_BATCH_ERR_VALIDATION, "event schema");
	xtk_batch_free(batch);

	xtk_retained_host_destroy(host);
	return 0;
}

static int test_subscribe_dispatch(void) {
	XtkHost *host = xtk_retained_host_create();
	EXPECT(host, "host");
	XtkBatch  *batch  = xtk_batch_alloc(host->vt->revision(host));
	XtkLocalId button = xtk_batch_create(batch, XTK_CTRL_BUTTON, xtk_ref_none(), xtk_ref_none(), NULL, 0u);
	XtkSubRef  token
	  = xtk_batch_on(batch, xtk_ref_local(button), XTK_EVENT_INVOKE, XTK_EVENT_PHASE_MASK_TARGET, on_invoke, NULL);
	EXPECT(token != XTK_SUB_TOKEN_INVALID, "token");
	XtkBatchResult *result = commit_ok(host, batch);
	if (!result) return 1;
	EXPECT(result->subscription_count == 1u, "one sub");
	EXPECT(result->subscriptions [0].id != XTK_SUBSCRIPTION_INVALID, "sub id");

	XtkEvent event = {
	  .id             = XTK_EVENT_INVOKE,
	  .phase          = XTK_EVENT_PHASE_TARGET,
	  .target         = result->controls [0].control,
	  .current_target = result->controls [0].control,
	  .source         = result->controls [0].control,
	};
	g_events       = 0u;
	uint32_t flags = host->vt->dispatch(host, &event);
	EXPECT(g_events == 1u, "callback");
	EXPECT(flags & XTK_EVENT_HANDLED, "handled");

	xtk_batch_result_destroy(result);
	xtk_batch_free(batch);
	xtk_retained_host_destroy(host);
	return 0;
}

int main(void) {
	if (test_create_prop_topology()) return 1;
	if (test_stale_revision_and_abort()) return 1;
	if (test_failed_commit_rolls_back()) return 1;
	if (test_create_destroy_same_local()) return 1;
	if (test_subscribe_rollback_on_failure()) return 1;
	if (test_destroy_subtree_sidecar()) return 1;
	if (test_host_preflight_schema()) return 1;
	if (test_subscribe_dispatch()) return 1;
	printf("PASS: retained host contract\n");
	return 0;
}
