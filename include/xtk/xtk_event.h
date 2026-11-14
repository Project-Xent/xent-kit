#ifndef XTK_EVENT_H
#define XTK_EVENT_H

#include <assert.h>

#include <stdbool.h>
#include <stdint.h>

#include "xtk_descriptor.h"

typedef uint64_t XtkSourceId;

#define XTK_SOURCE_INVALID (( XtkSourceId ) 0)

typedef struct XtkChangeStamp {
	XtkSourceId source;
	uint64_t    revision;
} XtkChangeStamp;

static bool inline xtk_changestamp_valid(XtkChangeStamp change) {
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

typedef enum XtkEventDisposition
{
	XTK_EVENT_CONTINUE         = 0,
	XTK_EVENT_HANDLED          = 1u << 0,
	XTK_EVENT_PREVENT_DEFAULT  = 1u << 1,
	XTK_EVENT_STOP_PROPAGATION = 1u << 2,
	XTK_EVENT_STOP_IMMEDIATE   = 1u << 3,
} XtkEventDisposition;

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

		struct {
			float start;
			float end;
		} range;

		struct {
			int32_t first;
			int32_t last;
			int32_t lanes;
		} window;

		struct {
			float x;
			float y;
			float max_x;
			float max_y;
		} scroll;
	} u;
} XtkEventPayload;

typedef struct XtkEvent {
	XtkEventId      id;
	XtkCtrl         source;
	XtkCtrl         target;
	XtkCtrl         current_target;
	XtkEventPhase   phase;
	XtkEventCause   cause;
	uint64_t        scene_revision;
	XtkChangeStamp  change;
	XtkEventPayload payload;
} XtkEvent;

typedef uint32_t (*XtkEventFn)(void *arg, XtkEvent const *event);

static bool inline xtk_event_phasesvalid(uint32_t phases) {
	return phases != 0u && (phases & ~( uint32_t ) XTK_EVENT_PHASE_MASK_ALL) == 0u;
}

static_assert(sizeof(XtkEventCause) == 4, "XtkEventCause crosses the ABI as int32");
static_assert(sizeof(XtkEventPhase) == 4, "XtkEventPhase crosses the ABI as int32");
static_assert(sizeof(XtkEventPhaseMask) == 4, "XtkEventPhaseMask crosses the ABI as int32");
static_assert(sizeof(XtkEventDisposition) == 4, "XtkEventDisposition crosses the ABI as int32");

#endif
