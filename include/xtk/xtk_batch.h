#ifndef XTK_BATCH_H
#define XTK_BATCH_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#include "xtk_descriptor.h"
#include "xtk_event.h"
#include "xtk_types.h"


/* Frozen batch wire protocol for the retained host.
 * Host implementors must not invent parallel shapes; extend only by adding
 * op kinds / value kinds with explicit version bumps. */

typedef uint64_t XtkSubId;
typedef uint32_t XtkLocalId;
typedef uint32_t XtkSubRef;

#define XTK_SUBSCRIPTION_INVALID (( XtkSubId ) 0)
#define XTK_LOCAL_INVALID        (( XtkLocalId ) UINT32_MAX)
#define XTK_SUB_TOKEN_INVALID    (( XtkSubRef ) UINT32_MAX)

/* ---- Node references: live handle vs batch-local creation token -------- */

typedef enum XtkNodeRefKind
{
	XTK_REF_NONE = 0,
	XTK_REF_EXISTING, /* committed XtkCtrl from a prior successful commit */
	XTK_REF_LOCAL,    /* XtkLocalId assigned by an earlier CREATE in this batch */
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

/* ---- Typed property values (batch-owned when copied) ------------------- */

typedef enum XtkValueKind
{
	XTK_VALUE_NONE = 0,
	XTK_VALUE_BOOL,
	XTK_VALUE_I32,
	XTK_VALUE_F32,
	XTK_VALUE_F64,
	XTK_VALUE_ENUM,
	XTK_VALUE_COLOR,
	XTK_VALUE_STRING,   /* UTF-8; storage owned by the batch after append */
	XTK_VALUE_RESOURCE, /* opaque cookie; always retained by the host on commit */
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
			char    *data; /* batch-owned copy, NUL-terminated; NULL only if len==0 */
			uint32_t len;  /* bytes without trailing NUL */
		} string;

		XtkResource resource; /* host retains on commit; no borrow encoding on the wire */

		struct {
			uint8_t *data; /* batch-owned copy; NULL only if len==0 */
			uint32_t len;
		} bytes;
	} u;
} XtkValue;

typedef struct XtkPropPatch {
	XtkPropertyId  id;
	XtkValue       value;
	XtkChangeStamp change;
} XtkPropPatch;

/* ---- Operations -------------------------------------------------------- */

typedef enum XtkBatchOpKind
{
	XTK_BATCH_OP_CREATE = 1,
	XTK_BATCH_OP_DESTROY,
	XTK_BATCH_OP_SET_PROP,
	XTK_BATCH_OP_INSERT,   /* place child under parent before sibling (append if before=NONE) */
	XTK_BATCH_OP_MOVE,     /* reorder under the same parent */
	XTK_BATCH_OP_REPARENT, /* change parent + optional before sibling */
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
	XtkNodeRef    parent; /* NONE = root/orphan slot defined by host scene */
	XtkNodeRef    before; /* NONE = append as last child */
	XtkLocalId    local;  /* assigned by builder; used as XTK_REF_LOCAL */
	XtkPropPatch *props;  /* batch-owned array */
	uint32_t      prop_count;
} XtkBatchCreate;

typedef struct XtkBatchDestroy {
	XtkNodeRef target;
} XtkBatchDestroy;

typedef struct XtkBatchSetProp {
	XtkNodeRef   target;
	XtkPropPatch patch; /* value storage owned by batch when STRING/BYTES */
} XtkBatchSetProp;

typedef struct XtkBatchInsert {
	XtkNodeRef parent;
	XtkNodeRef child;
	XtkNodeRef before; /* NONE = append */
} XtkBatchInsert;

typedef struct XtkBatchMove {
	XtkNodeRef parent; /* must be the current parent after preflight */
	XtkNodeRef child;
	XtkNodeRef before; /* NONE = move to end */
} XtkBatchMove;

typedef struct XtkBatchReparent {
	XtkNodeRef child;
	XtkNodeRef new_parent;
	XtkNodeRef before; /* NONE = append under new_parent */
} XtkBatchReparent;

typedef struct XtkBatchSubscribe {
	XtkNodeRef target;
	XtkEventId event;
	uint32_t   phases; /* XtkEventPhaseMask */
	XtkEventFn fn;
	void      *arg;
	XtkSubRef  token; /* assigned by builder; resolved in XtkBatchResult on commit */
} XtkBatchSubscribe;

typedef struct XtkBatchUnsubscribe {
	XtkSubId id; /* committed id only; not a batch-local token */
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
	uint32_t    next_local; /* next XtkLocalId to assign (0..) */
	uint32_t    next_sub;   /* next XtkSubRef to assign (0..) */
	uint64_t    revision;   /* scene revision observed at batch begin */
	bool        sealed;     /* true after successful structural preflight */
} XtkBatch;

typedef struct XtkControlMapping {
	XtkLocalId local;
	XtkCtrl    control;
} XtkControlMapping;

typedef struct XtkSubMapping {
	XtkSubRef token;
	XtkSubId  id;
} XtkSubMapping;

typedef struct XtkBatchDiag {
	XtkBatchError error;
	uint32_t      failed_op;
} XtkBatchDiag;

typedef struct XtkBatchResult {
	XtkControlMapping *controls;      /* one per CREATE, in CREATE op order */
	uint32_t           control_count;
	XtkSubMapping     *subscriptions; /* one per SUBSCRIBE, in op order */
	uint32_t           subscription_count;
} XtkBatchResult;

/* ---- Commit phases (Host) ----------------------------------------------
 *
 * 1. begin: capture scene revision into batch.revision.
 * 2. build: append ops; CREATE assigns local ids; SUBSCRIBE assigns sub tokens.
 *    STRING/BYTES values are copied into batch-owned storage at append time.
 *    Append rejects invalid kinds and len>0 with NULL data (batch unchanged).
 *    Synchronous convenience APIs that commit before return may use borrow
 *    only when explicitly documented; the batch builder path always copies.
 *    RESOURCE values are always retained by the host; borrow is not
 *    expressible on this wire format.
 * 3. preflight: pure validation of live handles + intra-batch local refs,
 *    property kinds, and topology constraints. No mutation. Sets sealed.
 *    Fails with STALE_REVISION if the scene advanced since begin.
 * 4. prepare: backend may allocate; host builds an owned XtkPrepare. Caller
 *    consumes it exactly once through commit or abort.
 * 5. commit: consumes prepare, applies every op, then backend-commits.
 *    Host apply failure => full host rollback before returning.
 *    Backend failure after host apply => host rollback; backend must undo prepare.
 *    On full success, the owned result maps each CREATE local and SUBSCRIBE
 *    token to committed handles. Destroy it with xtk_batch_result_destroy.
 *    Declarative "previous" / scene revision advances only after full success.
 *
 * Failure boundary: any error leaves the live tree, subscriptions, and
 * declarative previous state identical to pre-commit. The pointer-free
 * diagnostic names the first rejected operation when applicable. Commit
 * returns no result on failure.
 */

XtkBatch       *xtk_batch_alloc(uint64_t revision);
void            xtk_batch_free(XtkBatch *batch);
XtkBatchResult *xtk_batch_result_create(uint32_t control_count, uint32_t subscription_count);
void            xtk_batch_result_destroy(XtkBatchResult *result);

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

/* Structural preflight: local-ref resolution and op shape only (no live host). */
XtkBatchError xtk_batch_preflight(XtkBatch *batch, XtkBatchDiag *diagnostic);


#endif
