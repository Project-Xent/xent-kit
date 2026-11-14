#ifndef XTK_BATCH_H
#define XTK_BATCH_H

#include <assert.h>

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#include "xtk_descriptor.h"
#include "xtk_event.h"
#include "xtk_types.h"

typedef uint64_t XtkSubId;
typedef uint32_t XtkLocalId;
typedef uint32_t XtkSubRef;

#define XTK_SUBSCRIPTION_INVALID (( XtkSubId ) 0)
#define XTK_LOCAL_INVALID        (( XtkLocalId ) UINT32_MAX)
#define XTK_SUB_TOKEN_INVALID    (( XtkSubRef ) UINT32_MAX)

typedef enum XtkNodeRefKind
{
	XTK_REF_NONE = 0,
	XTK_REF_EXISTING,
	XTK_REF_LOCAL,
} XtkNodeRefKind;

typedef struct XtkNodeRef {
	XtkNodeRefKind kind;

	union
	{
		XtkCtrl    existing;
		XtkLocalId local;
	} u;
} XtkNodeRef;

static XtkNodeRef inline xtk_ref_none(void) { return ( XtkNodeRef ) {.kind = XTK_REF_NONE}; }

static XtkNodeRef inline xtk_ref_existing(XtkCtrl control) {
	return ( XtkNodeRef ) {.kind = XTK_REF_EXISTING, .u.existing = control};
}

static XtkNodeRef inline xtk_ref_local(XtkLocalId local) {
	return ( XtkNodeRef ) {.kind = XTK_REF_LOCAL, .u.local = local};
}

typedef enum XtkValueKind
{
	XTK_VALUE_NONE = 0,
	XTK_VALUE_BOOL,
	XTK_VALUE_I32,
	XTK_VALUE_F32,
	XTK_VALUE_F64,
	XTK_VALUE_ENUM,
	XTK_VALUE_COLOR,
	XTK_VALUE_STRING,
	XTK_VALUE_RESOURCE,
	XTK_VALUE_BYTES,
} XtkValueKind;

typedef struct XtkValue {
	XtkValueKind kind;

	union
	{
		bool     b;
		int32_t  i32;
		float    f32;
		double   f64;
		uint32_t u32;
		XtkColor color;

		struct {
			char    *data;
			uint32_t len;
		} string;

		XtkResource resource;

		struct {
			uint8_t *data;
			uint32_t len;
		} bytes;
	} u;
} XtkValue;

typedef struct XtkPropPatch {
	XtkPropertyId  id;
	XtkValue       value;
	XtkChangeStamp change;
} XtkPropPatch;

typedef enum XtkBatchOpKind
{
	XTK_BATCH_OP_CREATE = 1,
	XTK_BATCH_OP_DESTROY,
	XTK_BATCH_OP_SET_PROP,
	XTK_BATCH_OP_INSERT,
	XTK_BATCH_OP_MOVE,
	XTK_BATCH_OP_REPARENT,
	XTK_BATCH_OP_SUBSCRIBE,
	XTK_BATCH_OP_UNSUBSCRIBE,
} XtkBatchOpKind;

typedef enum XtkBatchError
{
	XTK_BATCH_OK = 0,
	XTK_BATCH_ERR_OOM,
	XTK_BATCH_ERR_INVALID_HANDLE,
	XTK_BATCH_ERR_INVALID_LOCAL,
	XTK_BATCH_ERR_INVALID_PARENT,
	XTK_BATCH_ERR_INVALID_PROPERTY,
	XTK_BATCH_ERR_INVALID_ORDER,
	XTK_BATCH_ERR_INVALID_VALUE,
	XTK_BATCH_ERR_DUPLICATE_LOCAL,
	XTK_BATCH_ERR_STALE_REVISION,
	XTK_BATCH_ERR_VALIDATION,
	XTK_BATCH_ERR_BACKEND,
} XtkBatchError;

typedef struct XtkBatchCreate {
	XtkCtrlId     type;
	XtkNodeRef    parent;
	XtkNodeRef    before;
	XtkLocalId    local;
	XtkPropPatch *props;
	uint32_t      prop_count;
} XtkBatchCreate;

typedef struct XtkBatchDestroy {
	XtkNodeRef target;
} XtkBatchDestroy;

typedef struct XtkBatchSetProp {
	XtkNodeRef   target;
	XtkPropPatch patch;
} XtkBatchSetProp;

typedef struct XtkBatchInsert {
	XtkNodeRef parent;
	XtkNodeRef child;
	XtkNodeRef before;
} XtkBatchInsert;

typedef struct XtkBatchMove {
	XtkNodeRef parent;
	XtkNodeRef child;
	XtkNodeRef before;
} XtkBatchMove;

typedef struct XtkBatchReparent {
	XtkNodeRef child;
	XtkNodeRef new_parent;
	XtkNodeRef before;
} XtkBatchReparent;

typedef struct XtkBatchSubscribe {
	XtkNodeRef target;
	XtkEventId event;
	uint32_t   phases;
	XtkEventFn fn;
	void      *arg;
	XtkSubRef  token;
} XtkBatchSubscribe;

typedef struct XtkBatchUnsubscribe {
	XtkSubId id;
} XtkBatchUnsubscribe;

typedef struct XtkBatchOp {
	XtkBatchOpKind kind;

	union
	{
		XtkBatchCreate      create;
		XtkBatchDestroy     destroy;
		XtkBatchSetProp     set_prop;
		XtkBatchInsert      insert;
		XtkBatchMove        move;
		XtkBatchReparent    reparent;
		XtkBatchSubscribe   subscribe;
		XtkBatchUnsubscribe unsubscribe;
	} u;
} XtkBatchOp;

typedef struct XtkBatch {
	XtkBatchOp *ops;
	uint32_t    count;
	uint32_t    capacity;
	uint32_t    next_local;
	uint32_t    next_sub;
	uint64_t    revision;
	bool        sealed;
} XtkBatch;

typedef struct XtkControlMapping {
	XtkLocalId local;
	XtkCtrl    control;
} XtkControlMapping;

typedef struct XtkSubMapping {
	XtkSubRef token;
	XtkSubId  id;
} XtkSubMapping;

typedef enum XtkBatchStage
{
	XTK_BATCH_STAGE_VALIDATE = 0,
	XTK_BATCH_STAGE_PREFLIGHT,
	XTK_BATCH_STAGE_PREPARE,
	XTK_BATCH_STAGE_COMMIT,
} XtkBatchStage;

typedef struct XtkBatchDiag {
	XtkBatchError error;
	uint32_t      failed_op;
	XtkBatchStage stage;
} XtkBatchDiag;

typedef struct XtkBatchResult {
	XtkControlMapping *controls;
	uint32_t           control_count;
	XtkSubMapping     *subscriptions;
	uint32_t           subscription_count;
} XtkBatchResult;

XtkBatch       *xtk_batch_alloc(uint64_t revision);
void            xtk_batch_free(XtkBatch *batch);
XtkBatchResult *xtk_batchresult_create(uint32_t control_count, uint32_t subscription_count);
void            xtk_batchresult_destroy(XtkBatchResult *result);

XtkLocalId      xtk_batch_create(
  XtkBatch *batch, XtkCtrlId type, XtkNodeRef parent, XtkNodeRef before, XtkPropPatch const *props, uint32_t prop_count
);
bool      xtk_batch_drop(XtkBatch *batch, XtkNodeRef target);
bool      xtk_batch_set(XtkBatch *batch, XtkNodeRef target, XtkPropertyId id, XtkValue value, XtkChangeStamp change);
bool      xtk_batch_insert(XtkBatch *batch, XtkNodeRef parent, XtkNodeRef child, XtkNodeRef before);
bool      xtk_batch_move(XtkBatch *batch, XtkNodeRef parent, XtkNodeRef child, XtkNodeRef before);
bool      xtk_batch_reparent(XtkBatch *batch, XtkNodeRef child, XtkNodeRef new_parent, XtkNodeRef before);
XtkSubRef xtk_batch_on(XtkBatch *batch, XtkNodeRef target, XtkEventId event, uint32_t phases, XtkEventFn fn, void *arg);
bool      xtk_batch_off(XtkBatch *batch, XtkSubId id);

XtkBatchError xtk_batch_preflight(XtkBatch *batch, XtkBatchDiag *diagnostic);

static_assert(sizeof(XtkNodeRefKind) == 4, "XtkNodeRefKind crosses the ABI as int32");
static_assert(sizeof(XtkValueKind) == 4, "XtkValueKind crosses the ABI as int32");
static_assert(sizeof(XtkBatchStage) == 4, "XtkBatchStage crosses the ABI as int32");
static_assert(sizeof(XtkBatchOpKind) == 4, "XtkBatchOpKind crosses the ABI as int32");
static_assert(sizeof(XtkBatchError) == 4, "XtkBatchError crosses the ABI as int32");

#endif
