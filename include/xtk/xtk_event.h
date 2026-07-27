#ifndef XTK_EVENT_H
#define XTK_EVENT_H

#include <stdbool.h>
#include <stdint.h>

#include "xtk_descriptor.h"


typedef uint64_t XtkSourceId;

#define XTK_SOURCE_INVALID (( XtkSourceId ) 0)

typedef struct XtkChangeStamp {
	XtkSourceId source;
	uint64_t    revision;
} XtkChangeStamp;

static bool inline xtk_change_stamp_valid(XtkChangeStamp change) {
	return (change.source == XTK_SOURCE_INVALID) == (change.revision == 0u);
}

typedef enum XtkEventCause
{
	XTK_EVENT_CAUSE_USER = 1,
	XTK_EVENT_CAUSE_PROGRAM,
	XTK_EVENT_CAUSE_BINDING,
	XTK_EVENT_CAUSE_ACCESSIBILITY,
} XtkEventCause;

typedef enum XtkEventPhase
{
	XTK_EVENT_PHASE_CAPTURE = 1,
	XTK_EVENT_PHASE_TARGET,
	XTK_EVENT_PHASE_BUBBLE,
} XtkEventPhase;

typedef enum XtkEventPhaseMask
{
	XTK_EVENT_PHASE_MASK_CAPTURE = 1u << 0,
	XTK_EVENT_PHASE_MASK_TARGET  = 1u << 1,
	XTK_EVENT_PHASE_MASK_BUBBLE  = 1u << 2,
	XTK_EVENT_PHASE_MASK_ALL = XTK_EVENT_PHASE_MASK_CAPTURE | XTK_EVENT_PHASE_MASK_TARGET | XTK_EVENT_PHASE_MASK_BUBBLE,
} XtkEventPhaseMask;

/* Capture visits root through target parent, target visits only target, and
 * bubble visits target parent through root. Subscriptions at each node run in
 * successful commit order. */
typedef enum XtkEventDisposition
{
	XTK_EVENT_CONTINUE         = 0,
	XTK_EVENT_HANDLED          = 1u << 0,
	XTK_EVENT_PREVENT_DEFAULT  = 1u << 1,
	XTK_EVENT_STOP_PROPAGATION = 1u << 2,
	XTK_EVENT_STOP_IMMEDIATE   = 1u << 3,
} XtkEventDisposition;

/* HANDLED accumulates without stopping routing. PREVENT_DEFAULT suppresses
 * the host default action. STOP_PROPAGATION finishes the current target;
 * STOP_IMMEDIATE also skips remaining callbacks on that target. */

typedef struct XtkEventPayload {
	XtkEventPayloadKind kind;

	union
	{
		bool    b;
		int32_t i32;
		float   f32;
		double  f64;

		struct {
			char const *data;
			uint32_t    len;
		} string;

		struct {
			char const *text;
			uint32_t    len;
			int32_t     index;
		} query;

		struct {
			double  value;
			int32_t count;
		} rating;

		struct {
			int32_t index;
			bool    value;
		} index_bool;
	} u;
} XtkEventPayload;

typedef struct XtkEvent {
	XtkEventId      id;
	XtkCtrl         source;
	XtkCtrl         target;
	XtkCtrl         current_target;
	XtkEventPhase   phase;
	XtkEventCause   cause;
	uint64_t        trace_id;
	uint64_t        scene_revision;
	XtkChangeStamp  change;
	XtkEventPayload payload;
} XtkEvent;

/* Event and borrowed payload storage are immutable and call-scoped. */
typedef uint32_t (*XtkEventFn)(void *arg, XtkEvent const *event);

static bool inline xtk_event_phases_valid(uint32_t phases) {
	return phases != 0u && (phases & ~( uint32_t ) XTK_EVENT_PHASE_MASK_ALL) == 0u;
}


#endif
