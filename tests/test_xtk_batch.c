/**
 * @file test_xtk_batch.c
 * @brief Pure batch protocol contract tests (no Flux, no retained host).
 */
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <xtk/xtk_batch.h>
#include <xtk/xtk_catalog.h>

#define EXPECT(cond, msg)              \
	do {                               \
		if (!(cond)) {                 \
			printf("FAIL: %s\n", msg); \
			return 1;                  \
		}                              \
	}                                  \
	while (0)

static uint32_t on_event(void *arg, XtkEvent const *event) {
	( void ) arg;
	( void ) event;
	return XTK_EVENT_CONTINUE;
}

static int test_create_local_ref_and_string_copy(void) {
	XtkBatch *batch = xtk_batch_alloc(7u);
	EXPECT(batch && batch->revision == 7u, "batch begin revision");

	char     stack_label [] = "Save";
	XtkValue label          = {
	  .kind = XTK_VALUE_STRING, .u.string = {.data = stack_label, .len = 4u}
    };
	XtkChangeStamp change   = {.source = 9u, .revision = 3u};
	XtkPropPatch   props [] = {
	  {.id = XTK_PROP_TEXT, .value = label, .change = change}
    };

	XtkLocalId local = xtk_batch_create(batch, XTK_CTRL_BUTTON, xtk_ref_none(), xtk_ref_none(), props, 1u);
	EXPECT(local != XTK_LOCAL_INVALID, "create local");
	EXPECT(local == 0u, "first local is 0");

	stack_label [0] = 'X';
	EXPECT(batch->ops [0].u.create.props [0].value.u.string.data [0] == 'S', "string copied into batch");
	EXPECT(batch->ops [0].u.create.props [0].change.source == 9u, "change stamp copied");

	XtkValue enabled = {.kind = XTK_VALUE_BOOL, .u.b = false};
	EXPECT(xtk_batch_set(batch, xtk_ref_local(local), XTK_PROP_ENABLED, enabled, change), "set prop on local");

	XtkBatchDiag diagnostic;
	EXPECT(xtk_batch_preflight(batch, &diagnostic) == XTK_BATCH_OK, "structural preflight");
	EXPECT(diagnostic.failed_op == UINT32_MAX, "no failed op");
	EXPECT(batch->sealed, "sealed after preflight");

	xtk_batch_free(batch);
	return 0;
}

static int test_reject_null_payload(void) {
	XtkBatch *batch = xtk_batch_alloc(1u);
	EXPECT(batch, "batch");

	XtkValue bad_string = {
	  .kind = XTK_VALUE_STRING, .u.string = {.data = NULL, .len = 3u}
    };
	EXPECT(
	  !xtk_batch_set(batch, xtk_ref_existing(1u), XTK_PROP_TEXT, bad_string, (XtkChangeStamp) {0}), "reject null string"
	);
	EXPECT(batch->count == 0u, "batch unchanged after bad string");

	XtkValue bad_bytes = {
	  .kind = XTK_VALUE_BYTES, .u.bytes = {.data = NULL, .len = 8u}
    };
	EXPECT(
	  !xtk_batch_set(batch, xtk_ref_existing(1u), XTK_PROP_ICON, bad_bytes, (XtkChangeStamp) {0}), "reject null bytes"
	);
	EXPECT(batch->count == 0u, "batch unchanged after bad bytes");

	XtkPropPatch bad_props [] = {
	  {.id = XTK_PROP_TEXT, .value = bad_string}
    };
	EXPECT(
	  xtk_batch_create(batch, XTK_CTRL_BUTTON, xtk_ref_none(), xtk_ref_none(), bad_props, 1u) == XTK_LOCAL_INVALID,
	  "create rejects null string prop"
	);
	EXPECT(batch->count == 0u && batch->next_local == 0u, "create did not allocate local");

	XtkValue empty_string = {
	  .kind = XTK_VALUE_STRING, .u.string = {.data = NULL, .len = 0u}
    };
	EXPECT(
	  xtk_batch_set(batch, xtk_ref_existing(1u), XTK_PROP_TEXT, empty_string, (XtkChangeStamp) {0}), "empty string ok"
	);
	EXPECT(
	  !xtk_batch_set(batch, xtk_ref_existing(1u), XTK_PROP_TEXT, empty_string, (XtkChangeStamp) {.source = 1u}),
	  "half change stamp rejected"
	);
	EXPECT(batch->count == 1u, "empty string appended");

	xtk_batch_free(batch);
	return 0;
}

static int test_subscribe_token_no_out_pointer(void) {
	XtkBatch *batch = xtk_batch_alloc(2u);
	EXPECT(batch, "batch");

	XtkLocalId child = xtk_batch_create(batch, XTK_CTRL_BUTTON, xtk_ref_existing(9u), xtk_ref_none(), NULL, 0u);
	EXPECT(child != XTK_LOCAL_INVALID, "create");

	XtkSubRef a
	  = xtk_batch_on(batch, xtk_ref_local(child), XTK_EVENT_INVOKE, XTK_EVENT_PHASE_MASK_TARGET, on_event, NULL);
	XtkSubRef b
	  = xtk_batch_on(batch, xtk_ref_local(child), XTK_EVENT_INVOKE, XTK_EVENT_PHASE_MASK_BUBBLE, on_event, NULL);
	EXPECT(a == 0u && b == 1u, "monotonic sub tokens");
	EXPECT(batch->ops [1].u.subscribe.token == a, "token stored on op");
	EXPECT(batch->ops [2].u.subscribe.token == b, "second token stored");
	EXPECT(batch->ops [2].u.subscribe.phases == XTK_EVENT_PHASE_MASK_BUBBLE, "phase mask stored");
	EXPECT(batch->next_sub == 2u, "next_sub advanced");
	EXPECT(
	  xtk_batch_on(batch, xtk_ref_local(child), XTK_EVENT_INVOKE, 0u, on_event, NULL) == XTK_SUB_TOKEN_INVALID,
	  "empty phase mask rejected"
	);
	EXPECT(
	  xtk_batch_on(batch, xtk_ref_local(child), XTK_EVENT_INVOKE, 1u << 7, on_event, NULL) == XTK_SUB_TOKEN_INVALID,
	  "unknown phase bit rejected"
	);
	EXPECT(
	  xtk_batch_on(batch, xtk_ref_local(child), XTK_EVENT_INVOKE, XTK_EVENT_PHASE_MASK_TARGET, NULL, NULL)
		== XTK_SUB_TOKEN_INVALID,
	  "null callback rejected"
	);
	EXPECT(batch->next_sub == 2u, "rejected subscriptions do not consume tokens");

	XtkBatchDiag diagnostic;
	EXPECT(xtk_batch_preflight(batch, &diagnostic) == XTK_BATCH_OK, "subscribe preflight");

	xtk_batch_free(batch);
	return 0;
}

static int test_forward_local_ref_rejected(void) {
	XtkBatch *batch = xtk_batch_alloc(1u);
	EXPECT(batch, "batch");

	EXPECT(xtk_batch_drop(batch, xtk_ref_local(0u)), "append destroy");
	XtkLocalId local = xtk_batch_create(batch, XTK_CTRL_BUTTON, xtk_ref_none(), xtk_ref_none(), NULL, 0u);
	EXPECT(local == 0u, "create assigns 0");

	XtkBatchDiag diagnostic;
	EXPECT(xtk_batch_preflight(batch, &diagnostic) == XTK_BATCH_ERR_INVALID_LOCAL, "forward ref rejected");
	EXPECT(diagnostic.failed_op == 0u, "failed at destroy");

	xtk_batch_free(batch);
	return 0;
}

static int test_bytes_copy(void) {
	XtkBatch *batch = xtk_batch_alloc(1u);
	EXPECT(batch, "batch");
	uint8_t  payload [] = {1u, 2u, 3u, 4u};
	XtkValue value      = {
	  .kind = XTK_VALUE_BYTES, .u.bytes = {.data = payload, .len = sizeof(payload)}
    };
	EXPECT(xtk_batch_set(batch, xtk_ref_existing(1u), XTK_PROP_ITEMS, value, (XtkChangeStamp) {0}), "bytes append");
	payload [0] = 9u;
	EXPECT(batch->ops [0].u.set_prop.patch.value.u.bytes.data [0] == 1u, "bytes copied into batch");
	XtkBatchDiag diagnostic;
	EXPECT(xtk_batch_preflight(batch, &diagnostic) == XTK_BATCH_OK, "bytes preflight");
	xtk_batch_free(batch);
	return 0;
}

static int test_existing_and_topology_ops(void) {
	XtkBatch *batch = xtk_batch_alloc(3u);
	EXPECT(batch, "batch");

	XtkCtrl    parent = 42u;
	XtkLocalId child  = xtk_batch_create(batch, XTK_CTRL_BUTTON, xtk_ref_existing(parent), xtk_ref_none(), NULL, 0u);
	EXPECT(child != XTK_LOCAL_INVALID, "create under existing");
	EXPECT(xtk_batch_insert(batch, xtk_ref_existing(parent), xtk_ref_local(child), xtk_ref_none()), "insert");
	EXPECT(xtk_batch_move(batch, xtk_ref_existing(parent), xtk_ref_local(child), xtk_ref_none()), "move");
	EXPECT(xtk_batch_reparent(batch, xtk_ref_local(child), xtk_ref_existing(parent), xtk_ref_none()), "reparent");
	XtkSubRef token
	  = xtk_batch_on(batch, xtk_ref_local(child), XTK_EVENT_INVOKE, XTK_EVENT_PHASE_MASK_TARGET, on_event, NULL);
	EXPECT(token != XTK_SUB_TOKEN_INVALID, "subscribe");

	XtkBatchDiag diagnostic;
	EXPECT(xtk_batch_preflight(batch, &diagnostic) == XTK_BATCH_OK, "topology preflight");

	xtk_batch_free(batch);
	return 0;
}

static int test_invalid_existing_rejected(void) {
	XtkBatch *batch = xtk_batch_alloc(0u);
	EXPECT(batch, "batch");
	EXPECT(xtk_batch_drop(batch, xtk_ref_existing(XTK_CTRL_INVALID)), "destroy invalid");

	XtkBatchDiag diagnostic;
	EXPECT(xtk_batch_preflight(batch, &diagnostic) == XTK_BATCH_ERR_INVALID_LOCAL, "invalid existing");
	xtk_batch_free(batch);
	return 0;
}

static int test_f64_stamp_and_catalog_validation(void) {
	XtkBatch *batch = xtk_batch_alloc(4u);
	EXPECT(batch, "batch");
	XtkChangeStamp change   = {.source = 17u, .revision = 22u};
	XtkValue       value    = {.kind = XTK_VALUE_F64, .u.f64 = 3.5};
	XtkPropPatch   props [] = {
	  {.id = XTK_PROP_VALUE_F64, .value = value, .change = change}
    };
	XtkLocalId number = xtk_batch_create(batch, XTK_CTRL_NUMBER, xtk_ref_none(), xtk_ref_none(), props, 1u);
	EXPECT(number == 0u, "number create");
	EXPECT(batch->ops [0].u.create.props [0].value.u.f64 == 3.5, "f64 copied");
	EXPECT(batch->ops [0].u.create.props [0].change.revision == 22u, "revision copied");

	XtkBatchDiag diagnostic;
	EXPECT(xtk_batch_preflight(batch, &diagnostic) == XTK_BATCH_OK, "number property valid");
	xtk_batch_free(batch);

	batch = xtk_batch_alloc(4u);
	EXPECT(batch, "second batch");
	EXPECT(
	  xtk_batch_create(batch, XTK_CTRL_BUTTON, xtk_ref_none(), xtk_ref_none(), props, 1u) == 0u,
	  "builder accepts structurally valid property"
	);
	EXPECT(
	  xtk_batch_preflight(batch, &diagnostic) == XTK_BATCH_ERR_INVALID_PROPERTY,
	  "catalog rejects property absent from control"
	);
	xtk_batch_free(batch);
	return 0;
}

static int test_heap_owned_result(void) {
	XtkBatchResult *result = xtk_batch_result_create(2u, 1u);
	EXPECT(result, "result allocation");
	EXPECT(result->control_count == 2u && result->subscription_count == 1u, "result counts");
	result->controls [0]      = (XtkControlMapping) {.local = 0u, .control = 101u};
	result->subscriptions [0] = (XtkSubMapping) {.token = 0u, .id = 201u};
	EXPECT(result->controls [0].control == 101u, "control mapping writable by host");
	EXPECT(result->subscriptions [0].id == 201u, "subscription mapping writable by host");
	xtk_batch_result_destroy(result);
	xtk_batch_result_destroy(NULL);
	return 0;
}

int main(void) {
	if (test_create_local_ref_and_string_copy()) return 1;
	if (test_reject_null_payload()) return 1;
	if (test_subscribe_token_no_out_pointer()) return 1;
	if (test_forward_local_ref_rejected()) return 1;
	if (test_bytes_copy()) return 1;
	if (test_existing_and_topology_ops()) return 1;
	if (test_invalid_existing_rejected()) return 1;
	if (test_f64_stamp_and_catalog_validation()) return 1;
	if (test_heap_owned_result()) return 1;
	printf("PASS: xtk batch protocol contract\n");
	return 0;
}
