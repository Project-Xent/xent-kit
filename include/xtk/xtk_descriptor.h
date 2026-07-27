#ifndef XTK_DESCRIPTOR_H
#define XTK_DESCRIPTOR_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#include "xtk_types.h"


/* Frozen standard descriptors for the retained host. Names are stable for
 * v0.3.0 source consumers; struct layouts may still change before ABI freeze.
 * Host and declarative code share these definitions — no second control model. */

typedef uint64_t XtkCtrl;
typedef uint64_t XtkResource;
typedef uint32_t XtkCtrlId;
typedef uint32_t XtkPropertyId;
typedef uint32_t XtkEventId;
typedef uint32_t XtkCapabilityId;
typedef uint32_t XtkResourceTypeId;

#define XTK_CTRL_INVALID           (( XtkCtrl ) 0)
#define XTK_CTRL_ID_INVALID        (( XtkCtrlId ) 0)
#define XTK_PROP_ID_INVALID        (( XtkPropertyId ) 0)
#define XTK_EVENT_ID_INVALID       (( XtkEventId ) 0)
#define XTK_CAPABILITY_ID_INVALID  (( XtkCapabilityId ) 0)
#define XTK_RESOURCE_INVALID       (( XtkResource ) 0)
#define XTK_RESOURCE_TYPE_INVALID  (( XtkResourceTypeId ) 0)
#define XTK_CTRL_ID_COMPONENT_BASE (( XtkCtrlId ) UINT32_C(0x80000000))

typedef enum XtkPropertyKind
{
	XTK_PROP_KIND_BOOL = 1,
	XTK_PROP_KIND_I32,
	XTK_PROP_KIND_F32,
	XTK_PROP_KIND_F64,
	XTK_PROP_KIND_ENUM,
	XTK_PROP_KIND_COLOR,
	XTK_PROP_KIND_STRING,
	XTK_PROP_KIND_RESOURCE,
	XTK_PROP_KIND_BYTES,
} XtkPropertyKind;

typedef enum XtkPropertyFlags
{
	XTK_PROP_FLAG_NONE       = 0,
	XTK_PROP_FLAG_READONLY   = 1u << 0,
	XTK_PROP_FLAG_ANIMATABLE = 1u << 1,
} XtkPropertyFlags;

typedef enum XtkInvalidate
{
	XTK_INVALIDATE_NONE      = 0,
	XTK_INVALIDATE_LAYOUT    = 1u << 0,
	XTK_INVALIDATE_PAINT     = 1u << 1,
	XTK_INVALIDATE_HIT_TEST  = 1u << 2,
	XTK_INVALIDATE_SEMANTICS = 1u << 3,
	XTK_INVALIDATE_ACCESS    = 1u << 4,
} XtkInvalidate;

typedef struct XtkPropDesc {
	XtkPropertyId     id;
	char const       *name;
	XtkPropertyKind   kind;
	uint32_t          flags;
	uint32_t          invalidates;
	XtkResourceTypeId resource_type;
} XtkPropDesc;

typedef enum XtkEventRouting
{
	XTK_EVENT_ROUTE_TARGET = 1,
	XTK_EVENT_ROUTE_BUBBLE,
	XTK_EVENT_ROUTE_CAPTURE_BUBBLE,
} XtkEventRouting;

typedef enum XtkEventPayloadKind
{
	XTK_EVENT_PAYLOAD_NONE = 0,
	XTK_EVENT_PAYLOAD_BOOL,
	XTK_EVENT_PAYLOAD_I32,
	XTK_EVENT_PAYLOAD_F32,
	XTK_EVENT_PAYLOAD_F64,
	XTK_EVENT_PAYLOAD_STRING,
	XTK_EVENT_PAYLOAD_QUERY,
	XTK_EVENT_PAYLOAD_RATING,
	XTK_EVENT_PAYLOAD_INDEX_BOOL,
} XtkEventPayloadKind;

typedef struct XtkEventDesc {
	XtkEventId          id;
	char const         *name;
	XtkEventRouting     routing;
	XtkEventPayloadKind payload_kind;
} XtkEventDesc;

typedef enum XtkAccessRole
{
	XTK_ACCESS_ROLE_NONE = 0,
	XTK_ACCESS_ROLE_BUTTON,
	XTK_ACCESS_ROLE_CHECKBOX,
	XTK_ACCESS_ROLE_RADIO,
	XTK_ACCESS_ROLE_TEXT,
	XTK_ACCESS_ROLE_EDIT,
	XTK_ACCESS_ROLE_SLIDER,
	XTK_ACCESS_ROLE_IMAGE,
	XTK_ACCESS_ROLE_LIST,
	XTK_ACCESS_ROLE_LIST_ITEM,
	XTK_ACCESS_ROLE_GROUP,
	XTK_ACCESS_ROLE_WINDOW,
} XtkAccessRole;

typedef struct XtkAccessDesc {
	XtkAccessRole role;
	bool          focusable_default;
	bool          keyboard_navigable;
} XtkAccessDesc;

typedef struct XtkCapDesc {
	XtkCapabilityId id;
	char const     *name;
	size_t          iface_size;
} XtkCapDesc;

typedef struct XtkCtrlDesc {
	XtkCtrlId              id;
	char const            *name;
	XtkPropertyId const   *properties;
	uint32_t               property_count;
	XtkEventId const      *events;
	uint32_t               event_count;
	XtkAccessDesc          access;
	XtkCapabilityId const *capabilities;
	uint32_t               capability_count;
	uint32_t               create_invalidates;
	uint32_t               destroy_invalidates;
} XtkCtrlDesc;


#endif
