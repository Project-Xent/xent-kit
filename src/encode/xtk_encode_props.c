#include "xtk_encode.h"
#include "../xtk_internal.h"
#include <xtk/xtk_treemodel.h>
#include <xtk/xtk_alloc.h>
#include <xtk/xtk_catalog.h>
#include <xtk/xtk_event.h>
#include <xtk/xtk_navmodel.h>

#include <math.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

static bool streq(char const *a, char const *b) {
	if (a == b) return true;
	if (!a || !b) return false;
	return strcmp(a, b) == 0;
}

static bool str_prop_changed(char const *old_val, bool has_prev, char const *new_val) {
	if (has_prev) return !streq(old_val, new_val);
	return new_val && new_val [0];
}

static bool feq(float a, float b) { return (isnan(a) && isnan(b)) || a == b; }

static bool value_string(XtkBatch *batch, XtkNodeRef target, XtkPropertyId id, char const *text) {
	if (!text) text = "";
	XtkValue value = {
	  .kind = XTK_VALUE_STRING, .u.string = {.data = ( char * ) text, .len = ( uint32_t ) strlen(text)}
    };
	return xtk_batch_set(batch, target, id, value, (XtkChangeStamp) {0});
}

static bool value_enum(XtkBatch *batch, XtkNodeRef target, XtkPropertyId id, uint32_t v) {
	XtkValue value = {.kind = XTK_VALUE_ENUM, .u.u32 = v};
	return xtk_batch_set(batch, target, id, value, (XtkChangeStamp) {0});
}

static bool value_bool(XtkBatch *batch, XtkNodeRef target, XtkPropertyId id, bool b) {
	XtkValue value = {.kind = XTK_VALUE_BOOL, .u.b = b};
	return xtk_batch_set(batch, target, id, value, (XtkChangeStamp) {0});
}

static bool value_f32(XtkBatch *batch, XtkNodeRef target, XtkPropertyId id, float f) {
	XtkValue value = {.kind = XTK_VALUE_F32, .u.f32 = f};
	return xtk_batch_set(batch, target, id, value, (XtkChangeStamp) {0});
}

static bool value_f64(XtkBatch *batch, XtkNodeRef target, XtkPropertyId id, double d) {
	XtkValue value = {.kind = XTK_VALUE_F64, .u.f64 = d};
	return xtk_batch_set(batch, target, id, value, (XtkChangeStamp) {0});
}

static bool value_i32(XtkBatch *batch, XtkNodeRef target, XtkPropertyId id, int32_t i) {
	XtkValue value = {.kind = XTK_VALUE_I32, .u.i32 = i};
	return xtk_batch_set(batch, target, id, value, (XtkChangeStamp) {0});
}

static bool value_color(XtkBatch *batch, XtkNodeRef target, XtkPropertyId id, XtkColor color) {
	XtkValue value = {.kind = XTK_VALUE_COLOR, .u.color = color};
	return xtk_batch_set(batch, target, id, value, (XtkChangeStamp) {0});
}

static bool value_bytes(XtkBatch *batch, XtkNodeRef target, XtkPropertyId id, void const *data, uint32_t len) {
	XtkValue value = {
	  .kind = XTK_VALUE_BYTES, .u.bytes = {.data = ( uint8_t * ) ( uintptr_t ) data, .len = len}
    };
	return xtk_batch_set(batch, target, id, value, (XtkChangeStamp) {0});
}

static bool value_resource(XtkBatch *batch, XtkNodeRef target, XtkPropertyId id, XtkResource resource) {
	XtkValue value = {.kind = XTK_VALUE_RESOURCE, .u.resource = resource};
	return xtk_batch_set(batch, target, id, value, (XtkChangeStamp) {0});
}

static bool encode_string_change(
  XtkBatch *batch, XtkNodeRef target, XtkPropertyId id, bool has_prev, char const *old, char const *value
) {
	return (has_prev && streq(old, value)) || value_string(batch, target, id, value);
}

static bool
encode_bool_change(XtkBatch *batch, XtkNodeRef target, XtkPropertyId id, bool has_prev, bool old, bool value) {
	return (has_prev && old == value) || value_bool(batch, target, id, value);
}

static bool
encode_i32_change(XtkBatch *batch, XtkNodeRef target, XtkPropertyId id, bool has_prev, int32_t old, int32_t value) {
	return (has_prev && old == value) || value_i32(batch, target, id, value);
}

typedef struct F32Field {
	XtkPropertyId id;
	float         old_value;
	float         value;
	bool          emit_initial;
} F32Field;

typedef struct EnumField {
	XtkPropertyId id;
	uint32_t      old_value;
	uint32_t      value;
} EnumField;

typedef enum ScalarKind
{
	SCALAR_BOOL,
	SCALAR_I32,
	SCALAR_F32,
	SCALAR_F64,
	SCALAR_ENUM,
	SCALAR_RESOURCE,
} ScalarKind;

typedef union ScalarValue
{
	bool        b;
	int32_t     i32;
	float       f32;
	double      f64;
	uint32_t    u32;
	XtkResource resource;
} ScalarValue;

typedef struct ScalarField {
	XtkPropertyId id;
	ScalarKind    kind;
	bool          changed;
	ScalarValue   value;
} ScalarField;

typedef struct StringField {
	XtkPropertyId id;
	char const   *old_value;
	char const   *value;
} StringField;

typedef bool (*ScalarEncoder)(XtkBatch *, XtkNodeRef, XtkPropertyId, ScalarValue);

static bool  scalar_bool(XtkBatch *batch, XtkNodeRef target, XtkPropertyId id, ScalarValue value) {
	return value_bool(batch, target, id, value.b);
}

static bool scalar_i32(XtkBatch *batch, XtkNodeRef target, XtkPropertyId id, ScalarValue value) {
	return value_i32(batch, target, id, value.i32);
}

static bool scalar_f32(XtkBatch *batch, XtkNodeRef target, XtkPropertyId id, ScalarValue value) {
	return value_f32(batch, target, id, value.f32);
}

static bool scalar_f64(XtkBatch *batch, XtkNodeRef target, XtkPropertyId id, ScalarValue value) {
	return value_f64(batch, target, id, value.f64);
}

static bool scalar_enum(XtkBatch *batch, XtkNodeRef target, XtkPropertyId id, ScalarValue value) {
	return value_enum(batch, target, id, value.u32);
}

static bool scalar_resource(XtkBatch *batch, XtkNodeRef target, XtkPropertyId id, ScalarValue value) {
	return value_resource(batch, target, id, value.resource);
}

static bool encode_scalar_fields(XtkBatch *batch, XtkNodeRef target, ScalarField const *fields, uint32_t count) {
	static ScalarEncoder const encoders [] = {
	  [SCALAR_BOOL]     = scalar_bool,
	  [SCALAR_I32]      = scalar_i32,
	  [SCALAR_F32]      = scalar_f32,
	  [SCALAR_F64]      = scalar_f64,
	  [SCALAR_ENUM]     = scalar_enum,
	  [SCALAR_RESOURCE] = scalar_resource,
	};
	for (uint32_t i = 0; i < count; i++) {
		if (!fields [i].changed) continue;
		if (( unsigned ) fields [i].kind >= sizeof(encoders) / sizeof(encoders [0])) return false;
		ScalarEncoder encode = encoders [fields [i].kind];
		if (!encode || !encode(batch, target, fields [i].id, fields [i].value)) return false;
	}
	return true;
}

static bool
encode_string_fields(XtkBatch *batch, XtkNodeRef target, bool has_prev, StringField const *fields, uint32_t count) {
	for (uint32_t i = 0; i < count; i++) {
		if (has_prev && streq(fields [i].old_value, fields [i].value)) continue;
		if (!value_string(batch, target, fields [i].id, fields [i].value)) return false;
	}
	return true;
}

static bool encode_f32_fields(XtkBatch *batch, XtkNodeRef target, bool has_prev, F32Field const *fields, uint32_t n) {
	for (uint32_t i = 0; i < n; i++) {
		bool changed = has_prev ? !feq(fields [i].old_value, fields [i].value) : fields [i].emit_initial;
		if (changed && !value_f32(batch, target, fields [i].id, fields [i].value)) return false;
	}
	return true;
}

static bool encode_enum_fields(XtkBatch *batch, XtkNodeRef target, bool has_prev, EnumField const *fields, uint32_t n) {
	for (uint32_t i = 0; i < n; i++) {
		bool changed = !has_prev || fields [i].old_value != fields [i].value;
		if (changed && !value_enum(batch, target, fields [i].id, fields [i].value)) return false;
	}
	return true;
}

typedef struct AutoField {
	XtkPropertyId id;
	size_t        offset;
} AutoField;

static AutoField const kAutoText [] = {
  {XTK_PROP_A11Y_NAME,          offsetof(XtkAutomation, name)         },
  {XTK_PROP_A11Y_ID,            offsetof(XtkAutomation, id)           },
  {XTK_PROP_A11Y_HELP,          offsetof(XtkAutomation, help)         },
  {XTK_PROP_A11Y_DESCRIPTION,   offsetof(XtkAutomation, description)  },
  {XTK_PROP_A11Y_ITEM_STATUS,   offsetof(XtkAutomation, item_status)  },
  {XTK_PROP_A11Y_ITEM_TYPE,     offsetof(XtkAutomation, item_type)    },
  {XTK_PROP_A11Y_CONTROL_TYPE,  offsetof(XtkAutomation, control_type) },
  {XTK_PROP_A11Y_ACCELERATOR,   offsetof(XtkAutomation, accelerator)  },
  {XTK_PROP_A11Y_ACCESS_KEY,    offsetof(XtkAutomation, access_key)   },
  {XTK_PROP_A11Y_LANDMARK_NAME, offsetof(XtkAutomation, landmark_name)},
  {XTK_PROP_A11Y_LABELED_BY,    offsetof(XtkAutomation, labeled_by)   },
  {XTK_PROP_A11Y_DESCRIBED_BY,  offsetof(XtkAutomation, described_by) },
  {XTK_PROP_A11Y_FLOWS_TO,      offsetof(XtkAutomation, flows_to)     },
  {XTK_PROP_A11Y_FLOWS_FROM,    offsetof(XtkAutomation, flows_from)   },
  {XTK_PROP_A11Y_CONTROLLED,    offsetof(XtkAutomation, controls)     },
};
static AutoField const kAutoEnum [] = {
  {XTK_PROP_A11Y_LANDMARK, offsetof(XtkAutomation, landmark)},
  {XTK_PROP_A11Y_LIVE,     offsetof(XtkAutomation, live)    },
  {XTK_PROP_A11Y_HEADING,  offsetof(XtkAutomation, heading) },
  {XTK_PROP_A11Y_VIEW,     offsetof(XtkAutomation, view)    },
};
static AutoField const kAutoFlag [] = {
  {XTK_PROP_A11Y_REQUIRED,   offsetof(XtkAutomation, required)  },
  {XTK_PROP_A11Y_DATA_VALID, offsetof(XtkAutomation, invalid)   },
  {XTK_PROP_A11Y_PERIPHERAL, offsetof(XtkAutomation, peripheral)},
  {XTK_PROP_A11Y_DIALOG,     offsetof(XtkAutomation, dialog)    },
};
static AutoField const kAutoInt [] = {
  {XTK_PROP_A11Y_POSITION, offsetof(XtkAutomation, position)},
  {XTK_PROP_A11Y_SIZE,     offsetof(XtkAutomation, size)    },
  {XTK_PROP_A11Y_LEVEL,    offsetof(XtkAutomation, level)   },
  {XTK_PROP_A11Y_CULTURE,  offsetof(XtkAutomation, culture) },
};

#define AUTO_AT(type, a, f) (*( type const * ) (( char const * ) (a) + (f).offset))

static bool encode_auto_text(XtkBatch *batch, XtkNodeRef target, XtkAutomation const *was, XtkAutomation const *now) {
	for (size_t i = 0; i < sizeof(kAutoText) / sizeof(kAutoText [0]); i++) {
		char const *a = AUTO_AT(char const *, was, kAutoText [i]), *b = AUTO_AT(char const *, now, kAutoText [i]);
		if (!streq(a, b) && !value_string(batch, target, kAutoText [i].id, b)) return false;
	}
	return true;
}

static bool encode_auto_flags(XtkBatch *batch, XtkNodeRef target, XtkAutomation const *was, XtkAutomation const *now) {
	for (size_t i = 0; i < sizeof(kAutoFlag) / sizeof(kAutoFlag [0]); i++) {
		bool a = AUTO_AT(bool, was, kAutoFlag [i]), b = AUTO_AT(bool, now, kAutoFlag [i]);
		bool v = kAutoFlag [i].id == XTK_PROP_A11Y_DATA_VALID ? !b : b;
		if (a != b && !value_bool(batch, target, kAutoFlag [i].id, v)) return false;
	}
	return true;
}

static bool encode_auto_scalar(XtkBatch *batch, XtkNodeRef target, XtkAutomation const *was, XtkAutomation const *now) {
	for (size_t i = 0; i < sizeof(kAutoEnum) / sizeof(kAutoEnum [0]); i++) {
		uint32_t a = AUTO_AT(uint32_t, was, kAutoEnum [i]), b = AUTO_AT(uint32_t, now, kAutoEnum [i]);
		if (a != b && !value_enum(batch, target, kAutoEnum [i].id, b)) return false;
	}
	if (!encode_auto_flags(batch, target, was, now)) return false;
	for (size_t i = 0; i < sizeof(kAutoInt) / sizeof(kAutoInt [0]); i++) {
		int32_t a = AUTO_AT(int32_t, was, kAutoInt [i]), b = AUTO_AT(int32_t, now, kAutoInt [i]);
		if (a != b && !value_i32(batch, target, kAutoInt [i].id, b)) return false;
	}
	return true;
}

static bool encode_automation(XtkBatch *batch, XtkNodeRef target, XtkEl const *prev, XtkEl const *el) {
	static XtkAutomation const none = {0};
	XtkAutomation const       *was  = prev && XTK_EL_DATA(prev)->automation ? XTK_EL_DATA(prev)->automation : &none;
	XtkAutomation const       *now  = XTK_EL_DATA(el)->automation ? XTK_EL_DATA(el)->automation : &none;
	if (was == now) return true;
	return encode_auto_text(batch, target, was, now) && encode_auto_scalar(batch, target, was, now);
}

static bool encode_common_base(XtkBatch *batch, XtkNodeRef target, XtkEl const *prev, XtkEl const *el);

typedef struct MotionImplicitWire {
	uint32_t mask;
	float    opacity_dur;
	float    transform_dur;
	float    brush_dur;
} MotionImplicitWire;

typedef struct ConnectedCfgWire {
	uint32_t kind;
	uint32_t shadow;
	float    dip_x;
	float    dip_y;
	float    duration;
} ConnectedCfgWire;

static float style_f32(XtkStyle const *s, uint32_t bit, float fallback) {
	if (!s || !(s->mask & bit)) return fallback;
	if (bit == XTK_STYLE_CORNER_RADIUS) return s->corner_radius;
	if (bit == XTK_STYLE_BORDER_WIDTH) return s->border_width;
	if (bit == XTK_STYLE_OPACITY) return s->opacity;
	if (bit == XTK_STYLE_TRANSLATE_X) return s->translate_x;
	if (bit == XTK_STYLE_TRANSLATE_Y) return s->translate_y;
	if (bit == XTK_STYLE_SCALE_X) return s->scale_x;
	if (bit == XTK_STYLE_SCALE_Y) return s->scale_y;
	return s->rotation;
}

static XtkColor style_color(XtkStyle const *s, uint32_t bit) {
	if (!s || !(s->mask & bit)) return (XtkColor) {0};
	return bit == XTK_STYLE_BACKGROUND ? s->background : s->border_color;
}

static bool encode_style(XtkBatch *batch, XtkNodeRef target, XtkEl const *prev, XtkEl const *el) {
	XtkStyle const *was = prev ? XTK_EL_DATA(prev)->style : NULL;
	XtkStyle const *now = XTK_EL_DATA(el)->style;
	if (!was && !now) return true;
	if (was && now && memcmp(was, now, sizeof(*now)) == 0) return true;

	XtkColor old_bg = style_color(was, XTK_STYLE_BACKGROUND), new_bg = style_color(now, XTK_STYLE_BACKGROUND);
	if (old_bg.rgba != new_bg.rgba && !value_color(batch, target, XTK_PROP_STYLE_BG, new_bg)) return false;
	XtkColor old_bd = style_color(was, XTK_STYLE_BORDER_COLOR), new_bd = style_color(now, XTK_STYLE_BORDER_COLOR);
	if (old_bd.rgba != new_bd.rgba && !value_color(batch, target, XTK_PROP_STYLE_BORDER, new_bd)) return false;

	F32Field fields [] = {
	  {XTK_PROP_STYLE_RADIUS,   style_f32(was, XTK_STYLE_CORNER_RADIUS, 0.0f),
	   style_f32(now,                                                                         XTK_STYLE_CORNER_RADIUS, 0.0f), (now && (now->mask & XTK_STYLE_CORNER_RADIUS))},
	  {XTK_PROP_STYLE_BORDER_W, style_f32(was, XTK_STYLE_BORDER_WIDTH,  0.0f),
	   style_f32(now,                                                                         XTK_STYLE_BORDER_WIDTH,  0.0f), (now && (now->mask & XTK_STYLE_BORDER_WIDTH)) },
	  {XTK_PROP_STYLE_OPACITY,  style_f32(was, XTK_STYLE_OPACITY,       1.0f), style_f32(now, XTK_STYLE_OPACITY,       1.0f),
	   (now && (now->mask & XTK_STYLE_OPACITY))                                                                                                                             },
	  {XTK_PROP_STYLE_TX,       style_f32(was, XTK_STYLE_TRANSLATE_X,   0.0f), style_f32(now, XTK_STYLE_TRANSLATE_X,   0.0f),
	   (now && (now->mask & XTK_STYLE_TRANSLATE_X))                                                                                                                         },
	  {XTK_PROP_STYLE_TY,       style_f32(was, XTK_STYLE_TRANSLATE_Y,   0.0f), style_f32(now, XTK_STYLE_TRANSLATE_Y,   0.0f),
	   (now && (now->mask & XTK_STYLE_TRANSLATE_Y))                                                                                                                         },
	  {XTK_PROP_STYLE_SX,       style_f32(was, XTK_STYLE_SCALE_X,       1.0f), style_f32(now, XTK_STYLE_SCALE_X,       1.0f),
	   (now && (now->mask & XTK_STYLE_SCALE_X))                                                                                                                             },
	  {XTK_PROP_STYLE_SY,       style_f32(was, XTK_STYLE_SCALE_Y,       1.0f), style_f32(now, XTK_STYLE_SCALE_Y,       1.0f),
	   (now && (now->mask & XTK_STYLE_SCALE_Y))                                                                                                                             },
	  {XTK_PROP_STYLE_ROTATION, style_f32(was, XTK_STYLE_ROTATION,      0.0f), style_f32(now, XTK_STYLE_ROTATION,      0.0f),
	   (now && (now->mask & XTK_STYLE_ROTATION))                                                                                                                            },
	};
	return encode_f32_fields(batch, target, was != NULL, fields, 8u);
}

static bool encode_motion(XtkBatch *batch, XtkNodeRef target, XtkEl const *prev, XtkEl const *el) {
	static XtkMotion const none = {0};
	XtkMotion const       *was  = prev && XTK_EL_DATA(prev)->motion ? XTK_EL_DATA(prev)->motion : &none;
	XtkMotion const       *now  = XTK_EL_DATA(el)->motion ? XTK_EL_DATA(el)->motion : &none;
	if (was == now) return true;
	if (memcmp(was, now, sizeof(*now)) == 0) return true;

	MotionImplicitWire wire = {
	  .mask          = now->implicit_mask,
	  .opacity_dur   = ( float ) now->opacity_duration,
	  .transform_dur = ( float ) now->transform_duration,
	  .brush_dur     = ( float ) now->brush_duration,
	};
	if (memcmp(was, &none, offsetof(XtkMotion, enter_exit)) != memcmp(now, &none, offsetof(XtkMotion, enter_exit))
	    || was->implicit_mask != now->implicit_mask
	    || was->opacity_duration != now->opacity_duration
	    || was->transform_duration != now->transform_duration
	    || was->brush_duration != now->brush_duration)
	{
		if (!value_bytes(batch, target, XTK_PROP_MOTION_IMPLICIT, &wire, sizeof(wire))) return false;
	}
	if (was->enter_exit != now->enter_exit
	    && !value_enum(batch, target, XTK_PROP_MOTION_ENTER_EXIT, ( uint32_t ) now->enter_exit))
		return false;
	return true;
}

static bool encode_connected(XtkBatch *batch, XtkNodeRef target, XtkEl const *prev, XtkEl const *el) {
	XtkElementData const *wd = prev ? XTK_EL_DATA(prev) : NULL;
	XtkElementData const *nd = XTK_EL_DATA(el);
	if (nd->connected_cfg) {
		ConnectedCfgWire cw = {
		  .kind     = ( uint32_t ) nd->connected_cfg->kind,
		  .shadow   = nd->connected_cfg->disable_shadow ? 0u : 1u,
		  .dip_x    = nd->connected_cfg->dip_x,
		  .dip_y    = nd->connected_cfg->dip_y,
		  .duration = ( float ) nd->connected_cfg->duration,
		};
		bool same
		  = wd && wd->connected_cfg && memcmp(wd->connected_cfg, nd->connected_cfg, sizeof(XtkConnectedDesc)) == 0;
		if (!same && !value_bytes(batch, target, XTK_PROP_CONNECTED_CONFIG, &cw, sizeof(cw))) return false;
	}
	char const *ok = wd ? wd->connected_key : NULL;
	char const *nk = nd->connected_key;
	if (!streq(ok, nk) && !value_string(batch, target, XTK_PROP_CONNECTED_KEY, nk)) return false;
	char const *oc = wd ? wd->connected_coord : NULL;
	char const *nc = nd->connected_coord;
	return streq(oc, nc) || value_string(batch, target, XTK_PROP_CONNECTED_COORD, nc);
}

static bool encode_common(XtkBatch *batch, XtkNodeRef target, XtkEl const *prev, XtkEl const *el) {
	return encode_common_base(batch, target, prev, el)
	    && encode_automation(batch, target, prev, el)
	    && encode_style(batch, target, prev, el)
	    && encode_motion(batch, target, prev, el)
	    && encode_connected(batch, target, prev, el);
}

static bool encode_common_base(XtkBatch *batch, XtkNodeRef target, XtkEl const *prev, XtkEl const *el) {
	if (!prev) {
		F32Field fields [] = {
		  {XTK_PROP_WIDTH,         NAN,  XTK_EL_DATA(el)->width,         !isnan(XTK_EL_DATA(el)->width)        },
		  {XTK_PROP_HEIGHT,        NAN,  XTK_EL_DATA(el)->height,        !isnan(XTK_EL_DATA(el)->height)       },
		  {XTK_PROP_GROW,          0.0f, XTK_EL_DATA(el)->grow,          XTK_EL_DATA(el)->grow != 0.0f         },
		  {XTK_PROP_MARGIN_LEFT,   0.0f, XTK_EL_DATA(el)->margin.left,   XTK_EL_DATA(el)->margin.left != 0.0f  },
		  {XTK_PROP_MARGIN_TOP,    0.0f, XTK_EL_DATA(el)->margin.top,    XTK_EL_DATA(el)->margin.top != 0.0f   },
		  {XTK_PROP_MARGIN_RIGHT,  0.0f, XTK_EL_DATA(el)->margin.right,  XTK_EL_DATA(el)->margin.right != 0.0f },
		  {XTK_PROP_MARGIN_BOTTOM, 0.0f, XTK_EL_DATA(el)->margin.bottom, XTK_EL_DATA(el)->margin.bottom != 0.0f},
		};
		if (!encode_f32_fields(batch, target, false, fields, 7u)) return false;
		if (XTK_EL_DATA(el)->align_self != 0
		    && !value_enum(batch, target, XTK_PROP_ALIGN_SELF, ( uint32_t ) XTK_EL_DATA(el)->align_self))
			return false;
		if (XTK_EL_DATA(el)->tooltip && !value_string(batch, target, XTK_PROP_TOOLTIP, XTK_EL_DATA(el)->tooltip))
			return false;
		return !XTK_EL_DATA(el)->nav_slot || value_enum(batch, target, XTK_PROP_NAV_SLOT, XTK_EL_DATA(el)->nav_slot);
	}
	F32Field fields [] = {
	  {XTK_PROP_WIDTH,         XTK_EL_DATA(prev)->width,         XTK_EL_DATA(el)->width,         true},
	  {XTK_PROP_HEIGHT,        XTK_EL_DATA(prev)->height,        XTK_EL_DATA(el)->height,        true},
	  {XTK_PROP_GROW,          XTK_EL_DATA(prev)->grow,          XTK_EL_DATA(el)->grow,          true},
	  {XTK_PROP_MARGIN_LEFT,   XTK_EL_DATA(prev)->margin.left,   XTK_EL_DATA(el)->margin.left,   true},
	  {XTK_PROP_MARGIN_TOP,    XTK_EL_DATA(prev)->margin.top,    XTK_EL_DATA(el)->margin.top,    true},
	  {XTK_PROP_MARGIN_RIGHT,  XTK_EL_DATA(prev)->margin.right,  XTK_EL_DATA(el)->margin.right,  true},
	  {XTK_PROP_MARGIN_BOTTOM, XTK_EL_DATA(prev)->margin.bottom, XTK_EL_DATA(el)->margin.bottom, true},
	};
	if (!encode_f32_fields(batch, target, true, fields, 7u)) return false;
	if (XTK_EL_DATA(prev)->align_self != XTK_EL_DATA(el)->align_self
	    && !value_enum(batch, target, XTK_PROP_ALIGN_SELF, ( uint32_t ) XTK_EL_DATA(el)->align_self))
		return false;
	if (!streq(XTK_EL_DATA(prev)->tooltip, XTK_EL_DATA(el)->tooltip)
	    && !value_string(batch, target, XTK_PROP_TOOLTIP, XTK_EL_DATA(el)->tooltip))
		return false;
	return XTK_EL_DATA(prev)->nav_slot == XTK_EL_DATA(el)->nav_slot
	    || value_enum(batch, target, XTK_PROP_NAV_SLOT, XTK_EL_DATA(el)->nav_slot);
}

static bool stack_host(XtkCtrlType type) {
	return type == XTK_CTRL_CONTAINER || type == XTK_CTRL_CARD || type == XTK_CTRL_SCROLL;
}

static uint32_t stack_orientation(XtkEl const *el) {
	if (!el) return XTK_STACK_COLUMN;
	return XTK_EL_DATA(el)->stack_row ? XTK_STACK_ROW : XTK_STACK_COLUMN;
}

static uint32_t stack_align(XtkStackDesc const *stack) {
	if (!stack || !stack->align) return ( uint32_t ) XENT_FLEX_ALIGN_START;
	return ( uint32_t ) stack->align;
}

static bool encode_stack_flags(
  XtkBatch *batch, XtkNodeRef target, bool has_prev, XtkStackDesc const *old, XtkStackDesc const *stack
) {
	if ((!has_prev || old->fill != stack->fill) && !value_bool(batch, target, XTK_PROP_FILL, stack->fill)) return false;
	return (has_prev && old->wrap == stack->wrap) || value_enum(batch, target, XTK_PROP_WRAP, ( uint32_t ) stack->wrap);
}

static bool encode_stack(XtkBatch *batch, XtkNodeRef target, XtkEl const *prev, XtkEl const *el) {
	if (!stack_host(XTK_EL_DATA(el)->type)) return true;
	XtkStackDesc        zero  = {0};
	XtkStackDesc const *stack = XTK_EL_DETAIL(el, XtkStackDesc);
	XtkStackDesc const *old   = &zero;
	if (prev) old = XTK_EL_DETAIL(prev, XtkStackDesc);
	EnumField enums [] = {
	  {XTK_PROP_ORIENTATION,     stack_orientation(prev),   stack_orientation(el)      },
	  {XTK_PROP_ALIGN_ITEMS,     stack_align(old),          stack_align(stack)         },
	  {XTK_PROP_JUSTIFY_CONTENT, ( uint32_t ) old->justify, ( uint32_t ) stack->justify},
	};
	if (!encode_enum_fields(batch, target, prev != NULL, enums, 3u)) return false;
	F32Field fields [] = {
	  {XTK_PROP_GAP,            old ? old->gap : 0.0f,            stack->gap,            true},
	  {XTK_PROP_PADDING_LEFT,   old ? old->padding.left : 0.0f,   stack->padding.left,   true},
	  {XTK_PROP_PADDING_TOP,    old ? old->padding.top : 0.0f,    stack->padding.top,    true},
	  {XTK_PROP_PADDING_RIGHT,  old ? old->padding.right : 0.0f,  stack->padding.right,  true},
	  {XTK_PROP_PADDING_BOTTOM, old ? old->padding.bottom : 0.0f, stack->padding.bottom, true},
	};
	if (!encode_f32_fields(batch, target, prev != NULL, fields, 5u)) return false;
	return encode_stack_flags(batch, target, prev != NULL, old, stack);
}

typedef struct InputFields {
	char const *content;
	bool        disabled;
} InputFields;

static InputFields input_fields(XtkEl const *el) {
	if (!el) return (InputFields) {NULL, false};
	if (XTK_EL_DATA(el)->type == XTK_CTRL_SUGGEST) {
		XtkAutoSuggestDesc const *d = XTK_EL_DETAIL(el, XtkAutoSuggestDesc);
		return (InputFields) {d->content, d->disabled};
	}
	XtkTextBoxDesc const *d = XTK_EL_DETAIL(el, XtkTextBoxDesc);
	return (InputFields) {d->content, d->disabled};
}

static bool encode_dragdrop(XtkBatch *batch, XtkNodeRef target, XtkEl const *prev, XtkEl const *el) {
	XtkDragDropDesc          zero = {0};
	XtkDragDropDetail const *now  = XTK_EL_DETAIL(el, XtkDragDropDetail);
	XtkDragDropDetail const *was  = prev ? XTK_EL_DETAIL(prev, XtkDragDropDetail) : NULL;
	XtkDragDropDesc const   *dnd  = now ? &now->dnd : &zero;
	XtkDragDropDesc const   *old  = was ? &was->dnd : &zero;
	if (old->drop != dnd->drop && !value_enum(batch, target, XTK_PROP_DROP_OPERATION, ( uint32_t ) dnd->drop))
		return false;
	return encode_string_change(batch, target, XTK_PROP_DRAG_TEXT, true, old->drag_text, dnd->drag_text)
	    && encode_string_change(batch, target, XTK_PROP_DRAG_FILES, true, old->drag_files, dnd->drag_files);
}

static bool encode_textbox_mode(XtkBatch *batch, XtkNodeRef target, XtkEl const *prev, XtkEl const *el) {
	if (XTK_EL_DATA(el)->type != XTK_CTRL_TEXTBOX) return true;
	XtkTextBoxDesc const *desc = XTK_EL_DETAIL(el, XtkTextBoxDesc);
	XtkTextBoxDesc const  none = {0};
	XtkTextBoxDesc const *was  = prev ? XTK_EL_DETAIL(prev, XtkTextBoxDesc) : &none;
	return encode_bool_change(batch, target, XTK_PROP_MULTILINE, true, was->multiline, desc->multiline)
	    && encode_bool_change(batch, target, XTK_PROP_READ_ONLY, true, was->readonly, desc->readonly);
}

static bool encode_input(XtkBatch *batch, XtkNodeRef target, XtkEl const *prev, XtkEl const *el) {
	if ((!prev || !streq(XTK_EL_DATA(prev)->text, XTK_EL_DATA(el)->text))
	    && !value_string(batch, target, XTK_PROP_PLACEHOLDER, XTK_EL_DATA(el)->text))
		return false;
	InputFields now = input_fields(el);
	InputFields was = input_fields(prev);
	return encode_string_change(batch, target, XTK_PROP_TEXT, prev != NULL, was.content, now.content)
	    && encode_bool_change(batch, target, XTK_PROP_ENABLED, prev != NULL, !was.disabled, !now.disabled)
	    && encode_textbox_mode(batch, target, prev, el);
}

static bool encode_text(XtkBatch *batch, XtkNodeRef target, XtkEl const *prev, XtkEl const *el) {
	if (XTK_EL_DATA(el)->type == XTK_CTRL_IMAGE) return true;
	if (XTK_EL_DATA(el)->type == XTK_CTRL_RATING) return true;
	if (XTK_EL_DATA(el)->type == XTK_CTRL_TEXTBOX
	    || XTK_EL_DATA(el)->type == XTK_CTRL_PASSWORD
	    || XTK_EL_DATA(el)->type == XTK_CTRL_SUGGEST)
		return encode_input(batch, target, prev, el);
	if (!xtk_catalog_ctrlprop(XTK_EL_DATA(el)->type, XTK_PROP_TEXT)) return true;
	if (!prev && !XTK_EL_DATA(el)->text) return true;
	if (prev && streq(XTK_EL_DATA(prev)->text, XTK_EL_DATA(el)->text)) return true;
	return value_string(batch, target, XTK_PROP_TEXT, XTK_EL_DATA(el)->text);
}

static bool encode_check_state(XtkBatch *batch, XtkNodeRef target, XtkEl const *prev, XtkEl const *el) {
	if (XTK_EL_DATA(el)->type != XTK_CTRL_CHECKBOX) return true;
	XtkToggleDesc const *desc = XTK_EL_DETAIL(el, XtkToggleDesc);
	XtkToggleDesc const *old  = prev ? XTK_EL_DETAIL(prev, XtkToggleDesc) : NULL;
	if ((old ? old->three_state != desc->three_state : desc->three_state)
	    && !value_bool(batch, target, XTK_PROP_IS_THREE_STATE, desc->three_state))
		return false;
	return (old ? old->indeterminate == desc->indeterminate : !desc->indeterminate)
	    || value_bool(batch, target, XTK_PROP_INDETERMINATE, desc->indeterminate);
}

static bool encode_toggle(XtkBatch *batch, XtkNodeRef target, XtkEl const *prev, XtkEl const *el) {
	if (XTK_EL_DATA(el)->type != XTK_CTRL_CHECKBOX
	    && XTK_EL_DATA(el)->type != XTK_CTRL_RADIO
	    && XTK_EL_DATA(el)->type != XTK_CTRL_SWITCH)
		return true;
	if ((!prev || XTK_EL_DETAIL(prev, XtkToggleDesc)->checked != XTK_EL_DETAIL(el, XtkToggleDesc)->checked)
	    && !value_bool(batch, target, XTK_PROP_CHECKED, XTK_EL_DETAIL(el, XtkToggleDesc)->checked))
		return false;
	if (!encode_check_state(batch, target, prev, el)) return false;
	return (prev && XTK_EL_DETAIL(prev, XtkToggleDesc)->disabled == XTK_EL_DETAIL(el, XtkToggleDesc)->disabled)
	    || value_bool(batch, target, XTK_PROP_ENABLED, !XTK_EL_DETAIL(el, XtkToggleDesc)->disabled);
}

static bool
encode_icon_change(XtkBatch *batch, XtkNodeRef target, XtkEl const *prev, char const *old_icon, char const *icon) {
	if ((!prev || !streq(old_icon, icon)) && icon && !value_string(batch, target, XTK_PROP_ICON, icon)) return false;
	return !(prev && !icon && old_icon) || value_string(batch, target, XTK_PROP_ICON, "");
}

static bool encode_plain_button(XtkBatch *batch, XtkNodeRef target, XtkEl const *prev, XtkEl const *el) {
	XtkButtonDesc const *button   = XTK_EL_DETAIL(el, XtkButtonDesc);
	XtkButtonDesc const *old      = prev ? XTK_EL_DETAIL(prev, XtkButtonDesc) : NULL;
	char const          *icon     = button->icon;
	char const          *old_icon = old ? old->icon : NULL;
	bool                 enabled  = !button->disabled;
	bool                 old_en   = old ? !old->disabled : true;
	if (!encode_icon_change(batch, target, prev, old_icon, icon)) return false;
	if ((!prev || old->style != button->style)
	    && !value_enum(batch, target, XTK_PROP_BUTTON_STYLE, ( uint32_t ) button->style))
		return false;
	return (prev && old_en == enabled) || value_bool(batch, target, XTK_PROP_ENABLED, enabled);
}

static bool encode_split_button(XtkBatch *batch, XtkNodeRef target, XtkEl const *prev, XtkEl const *el) {
	XtkSplitDesc const *desc = XTK_EL_DETAIL(el, XtkSplitDesc);
	XtkSplitDesc const *old  = prev ? XTK_EL_DETAIL(prev, XtkSplitDesc) : NULL;
	if (XTK_EL_DATA(el)->type == XTK_CTRL_TOGGLESPLIT) {
		if ((!old || old->checked != desc->checked) && !value_bool(batch, target, XTK_PROP_CHECKED, desc->checked))
			return false;
	}
	if (!encode_icon_change(batch, target, prev, old ? old->icon : NULL, desc->icon)) return false;
	return encode_bool_change(
	  batch, target, XTK_PROP_ENABLED, old != NULL, old ? !old->disabled : true, !desc->disabled
	);
}

static bool encode_dropdown(XtkBatch *batch, XtkNodeRef target, XtkEl const *prev, XtkEl const *el) {
	XtkDropdownDesc const *desc = XTK_EL_DETAIL(el, XtkDropdownDesc);
	XtkDropdownDesc const *old  = prev ? XTK_EL_DETAIL(prev, XtkDropdownDesc) : NULL;
	if (!encode_icon_change(batch, target, prev, old ? old->icon : NULL, desc->icon)) return false;
	if ((!old || old->style != desc->style)
	    && !value_enum(batch, target, XTK_PROP_BUTTON_STYLE, ( uint32_t ) desc->style))
		return false;
	return encode_bool_change(
	  batch, target, XTK_PROP_ENABLED, old != NULL, old ? !old->disabled : true, !desc->disabled
	);
}

static bool encode_button(XtkBatch *batch, XtkNodeRef target, XtkEl const *prev, XtkEl const *el) {
	if (XTK_EL_DATA(el)->type == XTK_CTRL_BUTTON || XTK_EL_DATA(el)->type == XTK_CTRL_REPEAT)
		return encode_plain_button(batch, target, prev, el);
	if (XTK_EL_DATA(el)->type == XTK_CTRL_SPLIT || XTK_EL_DATA(el)->type == XTK_CTRL_TOGGLESPLIT)
		return encode_split_button(batch, target, prev, el);
	if (XTK_EL_DATA(el)->type == XTK_CTRL_DROPDOWN) return encode_dropdown(batch, target, prev, el);
	return true;
}

static bool encode_link(XtkBatch *batch, XtkNodeRef target, XtkEl const *prev, XtkEl const *el) {
	XtkHyperlinkDesc const *desc = XTK_EL_DETAIL(el, XtkHyperlinkDesc);
	XtkHyperlinkDesc const *old  = prev ? XTK_EL_DETAIL(prev, XtkHyperlinkDesc) : NULL;
	if (!encode_string_change(batch, target, XTK_PROP_URL, old != NULL, old ? old->url : NULL, desc->url)) return false;
	return encode_bool_change(
	  batch, target, XTK_PROP_ENABLED, old != NULL, old ? !old->disabled : true, !desc->disabled
	);
}

static bool encode_menu_item(XtkBatch *batch, XtkNodeRef target, XtkEl const *prev, XtkEl const *el) {
	if (XTK_EL_DATA(el)->type != XTK_CTRL_MENUITEM) return true;
	XtkMenuItemDetail const *item = XTK_EL_DETAIL(el, XtkMenuItemDetail);
	XtkMenuItemDetail const *old  = prev ? XTK_EL_DETAIL(prev, XtkMenuItemDetail) : NULL;
	if ((!old || old->disabled != item->disabled) && !value_bool(batch, target, XTK_PROP_ENABLED, !item->disabled))
		return false;
	return encode_icon_change(batch, target, prev, old ? old->icon : NULL, item->icon);
}

static bool encode_slider(XtkBatch *batch, XtkNodeRef target, XtkEl const *prev, XtkEl const *el) {
	if (XTK_EL_DATA(el)->type != XTK_CTRL_SLIDER) return true;
	XtkSliderDesc const *slider    = XTK_EL_DETAIL(el, XtkSliderDesc);
	XtkSliderDesc const *old       = prev ? XTK_EL_DETAIL(prev, XtkSliderDesc) : NULL;
	ScalarField          fields [] = {
	  {XTK_PROP_MIN_F32,         SCALAR_F32,  !old || old->min != slider->min,                       {.f32 = slider->min}        },
	  {XTK_PROP_MAX_F32,         SCALAR_F32,  !old || old->max != slider->max,                       {.f32 = slider->max}        },
	  {XTK_PROP_STEP_F32,        SCALAR_F32,  !old || old->step != slider->step,                     {.f32 = slider->step}       },
	  {XTK_PROP_VALUE_F32,       SCALAR_F32,  !old || old->value != slider->value,                   {.f32 = slider->value}      },
	  {XTK_PROP_TICK_FREQUENCY,  SCALAR_F32,  !old || old->tick != slider->tick,                     {.f32 = slider->tick}       },
	  {XTK_PROP_SMALL_CHANGE,    SCALAR_F32,  !old || old->small_change != slider->small_change,
	   {.f32 = slider->small_change}                                                                                             },
	  {XTK_PROP_LARGE_CHANGE,    SCALAR_F32,  !old || old->large_change != slider->large_change,
	   {.f32 = slider->large_change}                                                                                             },
	  {XTK_PROP_TICK_PLACEMENT,  SCALAR_ENUM, !old || old->tick_placement != slider->tick_placement,
	   {.u32 = ( uint32_t ) slider->tick_placement}                                                                              },
	  {XTK_PROP_SLIDER_SNAPS_TO, SCALAR_ENUM, !old || old->snap_to_ticks != slider->snap_to_ticks,
	   {.u32 = slider->snap_to_ticks ? 1u : 0u}                                                                                  },
	  {XTK_PROP_ENABLED,         SCALAR_BOOL, !old || old->disabled != slider->disabled,             {.b = !slider->disabled}    },
	  {XTK_PROP_ORIENTATION,     SCALAR_ENUM, !old || old->vertical != slider->vertical,
	   {.u32 = slider->vertical ? XTK_STACK_COLUMN : XTK_STACK_ROW}                                                              },
	  {XTK_PROP_IS_RANGE,        SCALAR_BOOL, !old || old->range != slider->range,                   {.b = slider->range}        },
	  {XTK_PROP_RANGE_START,     SCALAR_F32,  !old || old->range_start != slider->range_start,       {.f32 = slider->range_start}},
	  {XTK_PROP_RANGE_END,       SCALAR_F32,  !old || old->range_end != slider->range_end,           {.f32 = slider->range_end}  },
	};
	return encode_scalar_fields(batch, target, fields, sizeof(fields) / sizeof(fields [0]));
}

static bool encode_scroll_bar(XtkBatch *batch, XtkNodeRef target, XtkEl const *prev, XtkEl const *el) {
	XtkScrollBarDesc const *bar       = XTK_EL_DETAIL(el, XtkScrollBarDesc);
	XtkScrollBarDesc const *old       = prev ? XTK_EL_DETAIL(prev, XtkScrollBarDesc) : NULL;
	ScalarField             fields [] = {
	  {XTK_PROP_MIN_F64,       SCALAR_F64,  !old || old->min != bar->min,                   {.f64 = bar->min}       },
	  {XTK_PROP_MAX_F64,       SCALAR_F64,  !old || old->max != bar->max,                   {.f64 = bar->max}       },
	  {XTK_PROP_VALUE_F64,     SCALAR_F64,  !old || old->value != bar->value,               {.f64 = bar->value}     },
	  {XTK_PROP_VIEWPORT_SIZE, SCALAR_F64,  !old || old->viewport != bar->viewport,         {.f64 = bar->viewport}  },
	  {XTK_PROP_SMALL_CHANGE,  SCALAR_F32,  !old || old->small_change != bar->small_change,
	   {.f32 = ( float ) bar->small_change}                                                                         },
	  {XTK_PROP_LARGE_CHANGE,  SCALAR_F32,  !old || old->large_change != bar->large_change,
	   {.f32 = ( float ) bar->large_change}                                                                         },
	  {XTK_PROP_ORIENTATION,   SCALAR_ENUM, !old || old->horizontal != bar->horizontal,     {.u32 = bar->horizontal}},
	  {XTK_PROP_ENABLED,       SCALAR_BOOL, !old || old->disabled != bar->disabled,         {.b = !bar->disabled}   },
	};
	return encode_scalar_fields(batch, target, fields, sizeof(fields) / sizeof(fields [0]));
}

static bool encode_colitem(XtkBatch *batch, XtkNodeRef target, XtkEl const *prev, XtkEl const *el) {
	XtkColItemDesc const *col       = XTK_EL_DETAIL(el, XtkColItemDesc);
	XtkColItemDesc const *old       = prev ? XTK_EL_DETAIL(prev, XtkColItemDesc) : NULL;
	ScalarField           fields [] = {
	  {XTK_PROP_WIDTH,          SCALAR_F32,  !old || old->width != col->width,           {.f32 = col->width}             },
	  {XTK_PROP_MIN_WIDTH,      SCALAR_F32,  !old || old->min_width != col->min_width,   {.f32 = col->min_width}         },
	  {XTK_PROP_MAX_WIDTH,      SCALAR_F32,  !old || old->max_width != col->max_width,   {.f32 = col->max_width}         },
	  {XTK_PROP_TEXT_ALIGN,     SCALAR_ENUM, !old || old->align != col->align,           {.u32 = ( uint32_t ) col->align}},
	  {XTK_PROP_SORT_DIRECTION, SCALAR_ENUM, !old || old->sort != col->sort,             {.u32 = ( uint32_t ) col->sort} },
	  {XTK_PROP_ENABLED,        SCALAR_BOOL, !old || old->unsortable != col->unsortable, {.b = !col->unsortable}         },
	  {XTK_PROP_RESIZABLE,      SCALAR_BOOL, !old || old->fixed != col->fixed,           {.b = !col->fixed}              },
	};
	return encode_scalar_fields(batch, target, fields, sizeof(fields) / sizeof(fields [0]));
}

static bool encode_commandbar(XtkBatch *batch, XtkNodeRef target, XtkEl const *prev, XtkEl const *el) {
	XtkCommandBarDesc const *bar       = XTK_EL_DETAIL(el, XtkCommandBarDesc);
	XtkCommandBarDesc const *old       = prev ? XTK_EL_DETAIL(prev, XtkCommandBarDesc) : NULL;
	ScalarField              fields [] = {
	  {XTK_PROP_OPEN,                       SCALAR_BOOL, !old || old->open != bar->open,         {.b = bar->open}               },
	  {XTK_PROP_IS_STICKY,                  SCALAR_BOOL, !old || old->sticky != bar->sticky,     {.b = bar->sticky}             },
	  {XTK_PROP_DYNAMIC_OVERFLOW,           SCALAR_BOOL, !old || old->dynamic != bar->dynamic,   {.b = bar->dynamic}            },
	  {XTK_PROP_ENABLED,                    SCALAR_BOOL, !old || old->disabled != bar->disabled, {.b = !bar->disabled}          },
	  {XTK_PROP_CLOSED_DISPLAY_MODE,        SCALAR_ENUM, !old || old->mode != bar->mode,         {.u32 = ( uint32_t ) bar->mode}},
	  {XTK_PROP_DEFAULT_LABEL_POSITION,     SCALAR_ENUM, !old || old->labels != bar->labels,
	   {.u32 = ( uint32_t ) bar->labels}                                                                                        },
	  {XTK_PROP_OVERFLOW_BUTTON_VISIBILITY, SCALAR_ENUM, !old || old->more != bar->more,
	   {.u32 = ( uint32_t ) bar->more}                                                                                          },
	};
	return encode_scalar_fields(batch, target, fields, sizeof(fields) / sizeof(fields [0]));
}

static bool encode_appbar(XtkBatch *batch, XtkNodeRef target, XtkEl const *prev, XtkEl const *el) {
	XtkAppBarDesc const *d          = XTK_EL_DETAIL(el, XtkAppBarDesc);
	XtkAppBarDesc const *old        = prev ? XTK_EL_DETAIL(prev, XtkAppBarDesc) : NULL;
	StringField          strings [] = {
	  {XTK_PROP_ICON,             old ? old->icon : NULL,  d->icon },
	  {XTK_PROP_ACCELERATOR_TEXT, old ? old->accel : NULL, d->accel},
	};
	if (XTK_EL_DATA(el)->type != XTK_CTRL_APPBARSEP && !encode_string_fields(batch, target, old != NULL, strings, 2u))
		return false;
	ScalarField fields [] = {
	  {XTK_PROP_SECONDARY,              SCALAR_BOOL, !old || old->secondary != d->secondary,             {.b = d->secondary}},
	  {XTK_PROP_DYNAMIC_OVERFLOW_ORDER, SCALAR_I32,  !old || old->order != d->order,                     {.i32 = d->order}  },
	  {XTK_PROP_ENABLED,                SCALAR_BOOL, !old || old->disabled != d->disabled,               {.b = !d->disabled}},
	  {XTK_PROP_LABEL_POSITION,         SCALAR_ENUM, !old || old->label_collapsed != d->label_collapsed,
	   {.u32 = d->label_collapsed ? XTK_ELEMENT_LABEL_COLLAPSED : XTK_ELEMENT_LABEL_DEFAULT}                                },
	  {XTK_PROP_CHECKED,                SCALAR_BOOL, !old || old->checked != d->checked,                 {.b = d->checked}  },
	};
	uint32_t n = XTK_EL_DATA(el)->type == XTK_CTRL_APPBARSEP    ? 2u
	           : XTK_EL_DATA(el)->type == XTK_CTRL_APPBARTOGGLE ? 5u
	                                                            : 4u;
	return encode_scalar_fields(batch, target, fields, n);
}

static bool
encode_progress_bar_style(XtkBatch *batch, XtkNodeRef target, XtkProgressDesc const *old, XtkProgressDesc const *desc) {
	XtkProgressDesc const  defaults  = {0};
	XtkProgressDesc const *before    = old ? old : &defaults;
	F32Field               fields [] = {
	  {XTK_PROP_PADDING_LEFT,          before->padding.left,   desc->padding.left,   desc->padding.left != 0.0f  },
	  {XTK_PROP_PADDING_TOP,           before->padding.top,    desc->padding.top,    desc->padding.top != 0.0f   },
	  {XTK_PROP_PADDING_RIGHT,         before->padding.right,  desc->padding.right,  desc->padding.right != 0.0f },
	  {XTK_PROP_PADDING_BOTTOM,        before->padding.bottom, desc->padding.bottom, desc->padding.bottom != 0.0f},
	  {XTK_PROP_PROGRESS_BORDER_WIDTH, before->border_width,   desc->border_width,   desc->border_width != 0.0f  },
	};
	if (!encode_f32_fields(batch, target, old != NULL, fields, 5u)) return false;
	return (old && old->state == desc->state)
	    || value_enum(batch, target, XTK_PROP_PROGRESS_STATE, ( uint32_t ) desc->state);
}

static bool encode_progress(XtkBatch *batch, XtkNodeRef target, XtkEl const *prev, XtkEl const *el) {
	XtkCtrlType            type      = XTK_EL_DATA(el)->type;
	XtkProgressDesc const *progress  = XTK_EL_DETAIL(el, XtkProgressDesc);
	XtkProgressDesc const *old       = prev ? XTK_EL_DETAIL(prev, XtkProgressDesc) : NULL;
	F32Field               fields [] = {
	  {XTK_PROP_MIN_F32,   old ? old->min : 0.0f,   progress->min,   true},
	  {XTK_PROP_MAX_F32,   old ? old->max : 0.0f,   progress->max,   true},
	  {XTK_PROP_VALUE_F32, old ? old->value : 0.0f, progress->value, true},
	};
	if (!encode_f32_fields(batch, target, prev != NULL, fields, 3u)) return false;
	if ((!old || old->indeterminate != progress->indeterminate)
	    && !value_bool(batch, target, XTK_PROP_INDETERMINATE, progress->indeterminate))
		return false;
	if (type == XTK_CTRL_PROGRESS) return encode_progress_bar_style(batch, target, old, progress);
	return (old && old->inactive == progress->inactive)
	    || value_bool(batch, target, XTK_PROP_PROGRESS_ACTIVE, !progress->inactive);
}

static bool encode_number(XtkBatch *batch, XtkNodeRef target, XtkEl const *prev, XtkEl const *el) {
	XtkNumberDesc const *desc      = XTK_EL_DETAIL(el, XtkNumberDesc);
	XtkNumberDesc const *old       = prev ? XTK_EL_DETAIL(prev, XtkNumberDesc) : NULL;
	ScalarField          fields [] = {
	  {XTK_PROP_MIN_F64,   SCALAR_F64,  !old || old->min != desc->min,             {.f64 = desc->min}    },
	  {XTK_PROP_MAX_F64,   SCALAR_F64,  !old || old->max != desc->max,             {.f64 = desc->max}    },
	  {XTK_PROP_STEP_F64,  SCALAR_F64,  !old || old->step != desc->step,           {.f64 = desc->step}   },
	  {XTK_PROP_VALUE_F64, SCALAR_F64,  !old || old->value != desc->value,         {.f64 = desc->value}  },
	  {XTK_PROP_ENABLED,   SCALAR_BOOL, !old || old->disabled != desc->disabled,   {.b = !desc->disabled}},
	  {XTK_PROP_HIDE_SPIN, SCALAR_BOOL, !old || old->hide_spin != desc->hide_spin, {.b = desc->hide_spin}},
	};
	return encode_scalar_fields(batch, target, fields, sizeof(fields) / sizeof(fields [0]));
}

static bool encode_image(XtkBatch *batch, XtkNodeRef target, XtkEl const *prev, XtkEl const *el) {
	XtkImageDesc const *desc = XTK_EL_DETAIL(el, XtkImageDesc);
	XtkImageDesc const *old  = prev ? XTK_EL_DETAIL(prev, XtkImageDesc) : NULL;
	if ((!old || old->source != desc->source) && !value_resource(batch, target, XTK_PROP_IMAGE_SOURCE, desc->source))
		return false;
	if ((!old || old->stretch != desc->stretch)
	    && !value_enum(batch, target, XTK_PROP_IMAGE_STRETCH, ( uint32_t ) desc->stretch))
		return false;
	XentInsets const n = desc->nine, o = old ? old->nine : (XentInsets) {0};
	return (n.left == o.left || value_f32(batch, target, XTK_PROP_NINE_GRID_LEFT, n.left))
	    && (n.top == o.top || value_f32(batch, target, XTK_PROP_NINE_GRID_TOP, n.top))
	    && (n.right == o.right || value_f32(batch, target, XTK_PROP_NINE_GRID_RIGHT, n.right))
	    && (n.bottom == o.bottom || value_f32(batch, target, XTK_PROP_NINE_GRID_BOTTOM, n.bottom));
}

static bool encode_badge(XtkBatch *batch, XtkNodeRef target, XtkEl const *prev, XtkEl const *el) {
	XtkBadgeDesc const *desc = XTK_EL_DETAIL(el, XtkBadgeDesc);
	XtkBadgeDesc const *old  = prev ? XTK_EL_DETAIL(prev, XtkBadgeDesc) : NULL;
	if ((!old || old->mode != desc->mode) && !value_enum(batch, target, XTK_PROP_BADGE_MODE, ( uint32_t ) desc->mode))
		return false;
	if (!encode_i32_change(batch, target, XTK_PROP_BADGE_VALUE, old != NULL, old ? old->value : 0, desc->value))
		return false;
	return encode_string_change(batch, target, XTK_PROP_ICON, old != NULL, old ? old->icon : NULL, desc->icon);
}

static bool encode_text_font(XtkBatch *batch, XtkNodeRef target, XtkTextDesc const *old, XtkTextDesc const *text) {
	XtkTextDesc const  zero = {0};
	XtkTextDesc const *was  = old ? old : &zero;
	if (str_prop_changed(was->font_family, old != NULL, text->font_family)
	    && !value_string(batch, target, XTK_PROP_FONT_FAMILY, text->font_family))
		return false;
	ScalarField const fields [] = {
	  {XTK_PROP_FONT_SIZE,   SCALAR_F32,  was->size != text->size,           {.f32 = text->size > 0.0f ? text->size : 0.0f}},
	  {XTK_PROP_FONT_WEIGHT, SCALAR_ENUM, was->weight != text->weight,       {.u32 = ( uint32_t ) text->weight}            },
	  {XTK_PROP_TEXT_ALIGN,  SCALAR_ENUM, !old || was->align != text->align, {.u32 = ( uint32_t ) text->align}             },
	};
	if (!encode_scalar_fields(batch, target, fields, 3u)) return false;
	return (old && was->color.rgba == text->color.rgba) || value_color(batch, target, XTK_PROP_FOREGROUND, text->color);
}

static bool encode_text_flow(XtkBatch *batch, XtkNodeRef target, XtkTextDesc const *old, XtkTextDesc const *text) {
	XtkTextDesc const  none = {0};
	XtkTextDesc const *was  = old ? old : &none;
	if (was->max_lines != text->max_lines && !value_i32(batch, target, XTK_PROP_MAX_LINES, ( int32_t ) text->max_lines))
		return false;
	if (was->trim != text->trim && !value_enum(batch, target, XTK_PROP_TEXT_TRIM, ( uint32_t ) text->trim))
		return false;
	return encode_bool_change(batch, target, XTK_PROP_TEXT_WRAP, true, !was->nowrap, !text->nowrap)
	    && encode_bool_change(batch, target, XTK_PROP_SELECTABLE, true, was->selectable, text->selectable);
}

static bool encode_text_style(XtkBatch *batch, XtkNodeRef target, XtkEl const *prev, XtkEl const *el) {
	if (XTK_EL_DATA(el)->type != XTK_CTRL_TEXT) return true;
	XtkTextDesc const *text = XTK_EL_DETAIL(el, XtkTextDesc);
	XtkTextDesc const *old  = prev ? XTK_EL_DETAIL(prev, XtkTextDesc) : NULL;
	return encode_text_font(batch, target, old, text) && encode_text_flow(batch, target, old, text);
}

static bool encode_list_item(XtkBatch *batch, XtkNodeRef target, XtkEl const *prev, XtkEl const *el) {
	if (XTK_EL_DATA(el)->type != XTK_CTRL_LISTITEM) return true;
	return (prev && XTK_EL_DETAIL(prev, XtkListItemDesc)->selected == XTK_EL_DETAIL(el, XtkListItemDesc)->selected)
	    || value_bool(batch, target, XTK_PROP_SELECTED, XTK_EL_DETAIL(el, XtkListItemDesc)->selected);
}

static bool encode_scroll(XtkBatch *batch, XtkNodeRef target, XtkEl const *prev, XtkEl const *el) {
	( void ) prev;
	XtkScrollDesc const *scroll = &XTK_EL_DETAIL(el, XtkScrollDetail)->scroll;
	if (!scroll->scroll.tag) return true;
	return value_f32(batch, target, XTK_PROP_SCROLL_X, scroll->x)
	    && value_f32(batch, target, XTK_PROP_SCROLL_Y, scroll->y);
}

static bool encode_list_selection(XtkBatch *batch, XtkNodeRef target, XtkEl const *prev, XtkEl const *el);

static bool should_skip_model(XtkEl const *prev, bool skip_model) { return !prev && skip_model; }

static bool list_groups_equal(XtkListDesc const *a, XtkListDesc const *b) {
	if (a->ngroup != b->ngroup) return false;
	return a->ngroup == 0 || memcmp(a->groups, b->groups, sizeof(int32_t) * ( size_t ) a->ngroup) == 0;
}

static bool
encode_list_groups(XtkBatch *batch, XtkNodeRef target, XtkEl const *prev, XtkEl const *el, bool skip_model) {
	XtkListDesc const *desc = XTK_EL_DETAIL(el, XtkListDesc);
	if (XTK_EL_DATA(el)->type != XTK_CTRL_LIST && XTK_EL_DATA(el)->type != XTK_CTRL_GRIDVIEW) return true;
	if (should_skip_model(prev, skip_model)) return true;
	if (prev ? list_groups_equal(XTK_EL_DETAIL(prev, XtkListDesc), desc) : desc->ngroup == 0) return true;
	return value_bytes(batch, target, XTK_PROP_GROUPS, desc->groups, sizeof(int32_t) * ( uint32_t ) desc->ngroup);
}

static bool encode_string_items(
  XtkBatch *batch, XtkNodeRef target, char const *const *old_items, int old_count, char const *const *items, int count
);

static bool encode_list_names(XtkBatch *batch, XtkNodeRef target, XtkEl const *prev, XtkEl const *el, bool skip_model) {
	XtkListDesc const *desc = XTK_EL_DETAIL(el, XtkListDesc);
	XtkListDesc const *old  = prev ? XTK_EL_DETAIL(prev, XtkListDesc) : NULL;
	if (XTK_EL_DATA(el)->type == XTK_CTRL_REPEATER || XTK_EL_DATA(el)->type == XTK_CTRL_ITEMSVIEW) return true;
	if (should_skip_model(prev, skip_model)) return true;
	if (!old && desc->nname == 0) return true;
	return encode_string_items(batch, target, old ? old->names : NULL, old ? old->nname : 0, desc->names, desc->nname);
}

static bool
encode_list_host_opt(XtkBatch *batch, XtkNodeRef target, XtkEl const *prev, XtkEl const *el, bool skip_model) {
	if (!xtk_ctrl_islist(XTK_EL_DATA(el)->type)) return true;
	if ((!prev || XTK_EL_DETAIL(prev, XtkListDesc)->nitem != XTK_EL_DETAIL(el, XtkListDesc)->nitem)
	    && !value_i32(batch, target, XTK_PROP_ITEM_COUNT, XTK_EL_DETAIL(el, XtkListDesc)->nitem))
		return false;
	if ((!prev || XTK_EL_DETAIL(prev, XtkListDesc)->itemh != XTK_EL_DETAIL(el, XtkListDesc)->itemh)
	    && !value_f32(batch, target, XTK_PROP_ITEM_HEIGHT, XTK_EL_DETAIL(el, XtkListDesc)->itemh))
		return false;
	if ((!prev || XTK_EL_DETAIL(prev, XtkListDesc)->itemw != XTK_EL_DETAIL(el, XtkListDesc)->itemw)
	    && !value_f32(batch, target, XTK_PROP_ITEM_WIDTH, XTK_EL_DETAIL(el, XtkListDesc)->itemw))
		return false;
	if ((!prev || XTK_EL_DETAIL(prev, XtkListDesc)->ncol != XTK_EL_DETAIL(el, XtkListDesc)->ncol)
	    && !value_i32(batch, target, XTK_PROP_COLUMN_COUNT, XTK_EL_DETAIL(el, XtkListDesc)->ncol))
		return false;
	if (!encode_list_groups(batch, target, prev, el, skip_model)
	    || !encode_list_names(batch, target, prev, el, skip_model))
		return false;
	if ((prev ? XTK_EL_DETAIL(prev, XtkListDesc)->rect_select != XTK_EL_DETAIL(el, XtkListDesc)->rect_select
	          : XTK_EL_DETAIL(el, XtkListDesc)->rect_select)
	    && !value_bool(batch, target, XTK_PROP_RECTANGLE_SELECTION, XTK_EL_DETAIL(el, XtkListDesc)->rect_select))
		return false;
	return encode_list_selection(batch, target, prev, el);
}

static bool encode_list_host(XtkBatch *batch, XtkNodeRef target, XtkEl const *prev, XtkEl const *el) {
	return encode_list_host_opt(batch, target, prev, el, false);
}

static bool encode_list_selection(XtkBatch *batch, XtkNodeRef target, XtkEl const *prev, XtkEl const *el) {
	if ((!prev || XTK_EL_DETAIL(prev, XtkListDesc)->sel_mode != XTK_EL_DETAIL(el, XtkListDesc)->sel_mode)
	    && !value_enum(batch, target, XTK_PROP_SELECTION_MODE, ( uint32_t ) XTK_EL_DETAIL(el, XtkListDesc)->sel_mode))
		return false;
	if ((!prev || XTK_EL_DETAIL(prev, XtkListDesc)->sel != XTK_EL_DETAIL(el, XtkListDesc)->sel)
	    && !value_i32(batch, target, XTK_PROP_SELECTED_INDEX, XTK_EL_DETAIL(el, XtkListDesc)->sel))
		return false;
	if ((!prev || XTK_EL_DATA(prev)->virtual_first != XTK_EL_DATA(el)->virtual_first)
	    && !value_i32(batch, target, XTK_PROP_REALIZED_FIRST, XTK_EL_DATA(el)->virtual_first))
		return false;
	if (XTK_EL_DATA(el)->type != XTK_CTRL_ITEMSVIEW) return true;
	return (prev
	         && XTK_EL_DETAIL(prev, XtkListDesc)->item_invoked_enabled
	              == XTK_EL_DETAIL(el, XtkListDesc)->item_invoked_enabled)
	    || value_bool(
		  batch, target, XTK_PROP_ITEM_INVOKED_ENABLED, XTK_EL_DETAIL(el, XtkListDesc)->item_invoked_enabled
		);
}

static bool encode_expander(XtkBatch *batch, XtkNodeRef target, XtkEl const *prev, XtkEl const *el) {
	XtkExpanderDesc const *desc = XTK_EL_DETAIL(el, XtkExpanderDesc);
	XtkExpanderDesc const *old  = prev ? XTK_EL_DETAIL(prev, XtkExpanderDesc) : NULL;
	if ((!old || old->w != desc->w) && !value_f32(batch, target, XTK_PROP_WIDTH, desc->w)) return false;
	if ((!old || old->contenth != desc->contenth) && !value_f32(batch, target, XTK_PROP_CONTENT_HEIGHT, desc->contenth))
		return false;
	return (old && old->expanded == desc->expanded) || value_bool(batch, target, XTK_PROP_EXPANDED, desc->expanded);
}

static bool encode_info_bar(XtkBatch *batch, XtkNodeRef target, XtkEl const *prev, XtkEl const *el) {
	XtkInfoBarDesc const *desc = XTK_EL_DETAIL(el, XtkInfoBarDesc);
	XtkInfoBarDesc const *old  = prev ? XTK_EL_DETAIL(prev, XtkInfoBarDesc) : NULL;
	if ((!old || !streq(old->message, desc->message)) && !value_string(batch, target, XTK_PROP_MESSAGE, desc->message))
		return false;
	if ((!old || old->severity != desc->severity)
	    && !value_enum(batch, target, XTK_PROP_SEVERITY, ( uint32_t ) desc->severity))
		return false;
	return (old && old->closable == desc->closable) || value_bool(batch, target, XTK_PROP_CLOSABLE, desc->closable);
}

static bool encode_dialog(XtkBatch *batch, XtkNodeRef target, XtkEl const *prev, XtkEl const *el) {
	XtkDialogDesc const *desc       = XTK_EL_DETAIL(el, XtkDialogDesc);
	XtkDialogDesc const *old        = prev ? XTK_EL_DETAIL(prev, XtkDialogDesc) : NULL;
	StringField          strings [] = {
	  {XTK_PROP_PRIMARY_TEXT,   old ? old->primary : NULL,   desc->primary  },
	  {XTK_PROP_SECONDARY_TEXT, old ? old->secondary : NULL, desc->secondary},
	  {XTK_PROP_CLOSE_TEXT,     old ? old->close : NULL,     desc->close    },
	};
	if (!encode_string_fields(batch, target, old != NULL, strings, 3u)) return false;
	ScalarField scalars [] = {
	  {XTK_PROP_WIDTH,                 SCALAR_F32,  !old || old->w != desc->w,                           {.f32 = desc->w}       },
	  {XTK_PROP_CONTENT_HEIGHT,        SCALAR_F32,  !old || old->contenth != desc->contenth,             {.f32 = desc->contenth}},
	  {XTK_PROP_DIALOG_DEFAULT_BUTTON, SCALAR_ENUM, !old || old->default_button != desc->default_button,
	   {.u32 = ( uint32_t ) desc->default_button}                                                                               },
	  {XTK_PROP_OPEN,                  SCALAR_BOOL, !old || old->open != desc->open,                     {.b = desc->open}      },
	};
	return encode_scalar_fields(batch, target, scalars, sizeof(scalars) / sizeof(scalars [0]));
}

static bool encode_teaching_tip(XtkBatch *batch, XtkNodeRef target, XtkEl const *prev, XtkEl const *el) {
	XtkTeachingTipDesc const *desc       = XTK_EL_DETAIL(el, XtkTeachingTipDesc);
	XtkTeachingTipDesc const *old        = prev ? XTK_EL_DETAIL(prev, XtkTeachingTipDesc) : NULL;
	StringField               strings [] = {
	  {XTK_PROP_SUBTITLE,    old ? old->subtitle : NULL,    desc->subtitle   },
	  {XTK_PROP_ICON,        old ? old->icon : NULL,        desc->icon       },
	  {XTK_PROP_ACTION_TEXT, old ? old->action_text : NULL, desc->action_text},
	  {XTK_PROP_CLOSE_TEXT,  old ? old->close_text : NULL,  desc->close_text },
	};
	if (!encode_string_fields(batch, target, old != NULL, strings, 4u)) return false;
	ScalarField scalars [] = {
	  {XTK_PROP_PLACEMENT,        SCALAR_ENUM, !old || old->placement != desc->placement,
	   {.u32 = ( uint32_t ) desc->placement}                                                                                            },
	  {XTK_PROP_TAIL_VISIBILITY,  SCALAR_ENUM, !old || old->tail != desc->tail,                         {.u32 = ( uint32_t ) desc->tail}},
	  {XTK_PROP_ACTION_ACCENT,    SCALAR_BOOL, !old || old->action_accent != desc->action_accent,
	   {.b = desc->action_accent}                                                                                                       },
	  {XTK_PROP_UNTARGETED,       SCALAR_BOOL, !old || old->untargeted != desc->untargeted,             {.b = desc->untargeted}         },
	  {XTK_PROP_LIGHT_DISMISS,    SCALAR_BOOL, !old || old->light_dismiss != desc->light_dismiss,
	   {.b = desc->light_dismiss}                                                                                                       },
	  {XTK_PROP_PLACEMENT_MARGIN, SCALAR_F32,  !old || old->placement_margin != desc->placement_margin,
	   {.f32 = desc->placement_margin}                                                                                                  },
	  {XTK_PROP_OPEN,             SCALAR_BOOL, !old || old->open != desc->open,                         {.b = desc->open}               },
	};
	return encode_scalar_fields(batch, target, scalars, sizeof(scalars) / sizeof(scalars [0]));
}

static bool encode_refresh(XtkBatch *batch, XtkNodeRef target, XtkEl const *prev, XtkEl const *el) {
	XtkRefreshDesc const *desc           = XTK_EL_DETAIL(el, XtkRefreshDesc);
	XtkRefreshDesc const *old            = prev ? XTK_EL_DETAIL(prev, XtkRefreshDesc) : NULL;
	float                 visualizer     = desc->visualizer_size > 0.0f ? desc->visualizer_size : 100.0f;
	float                 old_visualizer = old && old->visualizer_size > 0.0f ? old->visualizer_size : 100.0f;
	float                 threshold      = desc->threshold_ratio > 0.0f ? desc->threshold_ratio : 0.8f;
	float                 old_threshold  = old && old->threshold_ratio > 0.0f ? old->threshold_ratio : 0.8f;
	if ((!old || old->direction != desc->direction)
	    && !value_enum(batch, target, XTK_PROP_PULL_DIRECTION, ( uint32_t ) desc->direction))
		return false;
	if ((!old || old_visualizer != visualizer) && !value_f32(batch, target, XTK_PROP_VISUALIZER_SIZE, visualizer))
		return false;
	if ((!old || old_threshold != threshold) && !value_f32(batch, target, XTK_PROP_THRESHOLD_RATIO, threshold))
		return false;
	return (old && old->is_refreshing == desc->is_refreshing)
	    || value_bool(batch, target, XTK_PROP_REFRESHING, desc->is_refreshing);
}

static bool encode_radio_buttons(XtkBatch *batch, XtkNodeRef target, XtkEl const *prev, XtkEl const *el) {
	if (XTK_EL_DATA(el)->type != XTK_CTRL_RADIOGROUP) return true;
	if ((!prev || XTK_EL_DETAIL(prev, XtkRadioButtonsDesc)->sel != XTK_EL_DETAIL(el, XtkRadioButtonsDesc)->sel)
	    && !value_i32(batch, target, XTK_PROP_SELECTED_INDEX, XTK_EL_DETAIL(el, XtkRadioButtonsDesc)->sel))
		return false;
	int cols      = XTK_EL_DETAIL(el, XtkRadioButtonsDesc)->max_columns > 0
	                ? XTK_EL_DETAIL(el, XtkRadioButtonsDesc)->max_columns
	                : 1;
	int prev_cols = prev && XTK_EL_DETAIL(prev, XtkRadioButtonsDesc)->max_columns > 0
	                ? XTK_EL_DETAIL(prev, XtkRadioButtonsDesc)->max_columns
	                : 1;
	if ((!prev || prev_cols != cols) && !value_i32(batch, target, XTK_PROP_COLUMN_COUNT, cols)) return false;
	return encode_bool_change(
	  batch, target, XTK_PROP_ENABLED, prev != NULL, prev ? !XTK_EL_DETAIL(prev, XtkRadioButtonsDesc)->disabled : true,
	  !XTK_EL_DETAIL(el, XtkRadioButtonsDesc)->disabled
	);
}

static bool string_items_equal(char const *const *a, int na, char const *const *b, int nb) {
	if (na != nb) return false;
	if (na <= 0) return true;
	if (!a || !b) return false;
	for (int i = 0; i < na; i++)
		if (!streq(a [i], b [i])) return false;
	return true;
}

static bool encode_string_items(
  XtkBatch *batch, XtkNodeRef target, char const *const *old_items, int old_count, char const *const *items, int count
) {
	if (string_items_equal(old_items, old_count, items, count)) return true;
	return xtk_items_strings(batch, target, items, count);
}

static bool selector_items_equal(XtkSelectorBarDesc const *a, XtkSelectorBarDesc const *b) {
	if (!a || !b || a->nitem != b->nitem) return false;
	for (int i = 0; i < a->nitem; i++)
		if (!streq(a->items [i].icon, b->items [i].icon)
		    || !streq(a->items [i].text, b->items [i].text)
		    || a->items [i].disabled != b->items [i].disabled)
			return false;
	return true;
}

static bool
encode_selector_bar_opt(XtkBatch *batch, XtkNodeRef target, XtkEl const *prev, XtkEl const *el, bool skip_model) {
	XtkSelectorBarDesc const *desc = XTK_EL_DETAIL(el, XtkSelectorBarDesc);
	XtkSelectorBarDesc const *old  = prev ? XTK_EL_DETAIL(prev, XtkSelectorBarDesc) : NULL;
	if (!should_skip_model(prev, skip_model)
	    && (!old || !selector_items_equal(old, desc))
	    && !xtk_items_selector(batch, target, desc->items, desc->nitem))
		return false;
	if ((!old || old->nitem != desc->nitem) && !value_i32(batch, target, XTK_PROP_ITEM_COUNT, desc->nitem))
		return false;
	return (old && old->sel == desc->sel) || value_i32(batch, target, XTK_PROP_SELECTED_INDEX, desc->sel);
}

static bool encode_selector_bar(XtkBatch *batch, XtkNodeRef target, XtkEl const *prev, XtkEl const *el) {
	return encode_selector_bar_opt(batch, target, prev, el, false);
}

static bool
encode_breadcrumb_opt(XtkBatch *batch, XtkNodeRef target, XtkEl const *prev, XtkEl const *el, bool skip_model) {
	XtkBreadcrumbDesc const *desc = XTK_EL_DETAIL(el, XtkBreadcrumbDesc);
	XtkBreadcrumbDesc const *old  = prev ? XTK_EL_DETAIL(prev, XtkBreadcrumbDesc) : NULL;
	if (!should_skip_model(prev, skip_model)
	    && !encode_string_items(
		  batch, target, old ? old->items : NULL, old ? old->nitem : -1, desc->items, desc->nitem
		))
		return false;
	if ((!old || old->nitem != desc->nitem) && !value_i32(batch, target, XTK_PROP_ITEM_COUNT, desc->nitem))
		return false;
	return encode_bool_change(
	  batch, target, XTK_PROP_ENABLED, old != NULL, old ? !old->disabled : true, !desc->disabled
	);
}

static bool encode_breadcrumb(XtkBatch *batch, XtkNodeRef target, XtkEl const *prev, XtkEl const *el) {
	return encode_breadcrumb_opt(batch, target, prev, el, false);
}

static bool encode_combo_edit(XtkBatch *batch, XtkNodeRef target, XtkComboDesc const *old, XtkComboDesc const *combo) {
	if ((old ? old->editable != combo->editable : combo->editable)
	    && !value_bool(batch, target, XTK_PROP_IS_EDITABLE, combo->editable))
		return false;
	return !combo->content
	    || streq(old ? old->content : NULL, combo->content)
	    || value_string(batch, target, XTK_PROP_TEXT, combo->content);
}

static bool encode_combo_opt(XtkBatch *batch, XtkNodeRef target, XtkEl const *prev, XtkEl const *el, bool skip_model) {
	if (XTK_EL_DATA(el)->type != XTK_CTRL_COMBO) return true;
	XtkComboDesc const *combo = XTK_EL_DETAIL(el, XtkComboDesc);
	XtkComboDesc const *old   = prev ? XTK_EL_DETAIL(prev, XtkComboDesc) : NULL;
	if (!should_skip_model(prev, skip_model)
	    && !encode_string_items(
		  batch, target, old ? old->items : NULL, old ? old->nitem : -1, combo->items, combo->nitem
		))
		return false;
	if ((!prev || old->sel != combo->sel) && !value_i32(batch, target, XTK_PROP_SELECTED_INDEX, combo->sel))
		return false;
	if (!encode_combo_edit(batch, target, old, combo)) return false;
	return (prev && streq(XTK_EL_DATA(prev)->text, XTK_EL_DATA(el)->text))
	    || value_string(batch, target, XTK_PROP_PLACEHOLDER, XTK_EL_DATA(el)->text);
}

static bool encode_combo(XtkBatch *batch, XtkNodeRef target, XtkEl const *prev, XtkEl const *el) {
	return encode_combo_opt(batch, target, prev, el, false);
}

static bool
encode_looping_opt(XtkBatch *batch, XtkNodeRef target, XtkEl const *prev, XtkEl const *el, bool skip_model) {
	XtkLoopingDesc const *wheel = XTK_EL_DETAIL(el, XtkLoopingDesc);
	XtkLoopingDesc const *old   = prev ? XTK_EL_DETAIL(prev, XtkLoopingDesc) : NULL;
	if (!should_skip_model(prev, skip_model)
	    && !encode_string_items(
		  batch, target, old ? old->items : NULL, old ? old->nitem : -1, wheel->items, wheel->nitem
		))
		return false;

	ScalarField fields [] = {
	  {XTK_PROP_ITEM_HEIGHT,    SCALAR_F32,  !old || old->itemh != wheel->itemh,       {.f32 = wheel->itemh}  },
	  {XTK_PROP_ITEM_WIDTH,     SCALAR_F32,  !old || old->itemw != wheel->itemw,       {.f32 = wheel->itemw}  },
	  {XTK_PROP_SHOULD_LOOP,    SCALAR_BOOL, !old || old->loop != wheel->loop,         {.b = wheel->loop}     },
	  {XTK_PROP_SELECTED_INDEX, SCALAR_I32,  !old || old->sel != wheel->sel,           {.i32 = wheel->sel}    },
	  {XTK_PROP_ENABLED,        SCALAR_BOOL, !old || old->disabled != wheel->disabled, {.b = !wheel->disabled}},
	};
	return encode_scalar_fields(batch, target, fields, sizeof(fields) / sizeof(fields [0]));
}

static bool encode_looping(XtkBatch *batch, XtkNodeRef target, XtkEl const *prev, XtkEl const *el) {
	return encode_looping_opt(batch, target, prev, el, false);
}

static bool
encode_suggest_opt(XtkBatch *batch, XtkNodeRef target, XtkEl const *prev, XtkEl const *el, bool skip_model) {
	XtkAutoSuggestDesc const *desc = XTK_EL_DETAIL(el, XtkAutoSuggestDesc);
	XtkAutoSuggestDesc const *old  = prev ? XTK_EL_DETAIL(prev, XtkAutoSuggestDesc) : NULL;
	if (!should_skip_model(prev, skip_model)
	    && !encode_string_items(
		  batch, target, old ? old->suggestions : NULL, old ? old->nitem : -1, desc->suggestions, desc->nitem
		))
		return false;
	if ((!old || !streq(old->query_icon, desc->query_icon))
	    && !value_string(batch, target, XTK_PROP_ICON, desc->query_icon))
		return false;
	return (old && old->disabled == desc->disabled) || value_bool(batch, target, XTK_PROP_ENABLED, !desc->disabled);
}

static bool encode_suggest(XtkBatch *batch, XtkNodeRef target, XtkEl const *prev, XtkEl const *el) {
	return encode_suggest_opt(batch, target, prev, el, false);
}

static bool encode_flip(XtkBatch *batch, XtkNodeRef target, XtkEl const *prev, XtkEl const *el) {
	XtkFlipDesc const *desc = XTK_EL_DETAIL(el, XtkFlipDesc);
	XtkFlipDesc const *old  = prev ? XTK_EL_DETAIL(prev, XtkFlipDesc) : NULL;
	if ((!old || old->sel != desc->sel) && !value_i32(batch, target, XTK_PROP_SELECTED_INDEX, desc->sel)) return false;
	return (old && old->vertical == desc->vertical)
	    || value_enum(batch, target, XTK_PROP_ORIENTATION, desc->vertical ? 1u : 0u);
}

static bool tab_desc_equal(XtkTabViewDesc const *a, XtkTabViewDesc const *b) {
	if (a->ntab != b->ntab) return false;
	for (int i = 0; i < a->ntab; i++)
		if (!streq(a->tabs [i].icon, b->tabs [i].icon) || !streq(a->tabs [i].label, b->tabs [i].label)) return false;
	return true;
}

static bool encode_tabs_opt(XtkBatch *batch, XtkNodeRef target, XtkEl const *prev, XtkEl const *el, bool skip_model) {
	XtkTabViewDesc const *desc = XTK_EL_DETAIL(el, XtkTabViewDesc);
	XtkTabViewDesc const *old  = prev ? XTK_EL_DETAIL(prev, XtkTabViewDesc) : NULL;
	if (!should_skip_model(prev, skip_model)
	    && (!old || !tab_desc_equal(old, desc))
	    && !xtk_items_tabs(batch, target, desc->tabs, desc->ntab))
		return false;
	if ((!old || old->ntab != desc->ntab) && !value_i32(batch, target, XTK_PROP_ITEM_COUNT, desc->ntab)) return false;
	bool add_visible     = desc->add.tag != 0;
	bool old_add_visible = old && old->add.tag != 0;
	if ((!old || old_add_visible != add_visible) && !value_bool(batch, target, XTK_PROP_ADD_VISIBLE, add_visible))
		return false;
	return (old && old->sel == desc->sel) || value_i32(batch, target, XTK_PROP_SELECTED_INDEX, desc->sel);
}

static bool encode_tabs(XtkBatch *batch, XtkNodeRef target, XtkEl const *prev, XtkEl const *el) {
	return encode_tabs_opt(batch, target, prev, el, false);
}

static bool encode_pips(XtkBatch *batch, XtkNodeRef target, XtkEl const *prev, XtkEl const *el) {
	XtkPipsDesc const *desc = XTK_EL_DETAIL(el, XtkPipsDesc);
	XtkPipsDesc const *old  = prev ? XTK_EL_DETAIL(prev, XtkPipsDesc) : NULL;
	if ((!old || old->nitem != desc->nitem) && !value_i32(batch, target, XTK_PROP_ITEM_COUNT, desc->nitem))
		return false;
	if ((!old || old->sel != desc->sel) && !value_i32(batch, target, XTK_PROP_SELECTED_INDEX, desc->sel)) return false;
	if ((!old || old->max_visible != desc->max_visible)
	    && !value_i32(batch, target, XTK_PROP_MAX_VISIBLE, desc->max_visible))
		return false;
	if ((!old || old->vertical != desc->vertical)
	    && !value_enum(batch, target, XTK_PROP_ORIENTATION, desc->vertical ? 1u : 0u))
		return false;
	return (old && old->nav == desc->nav) || value_enum(batch, target, XTK_PROP_NAV_VISIBILITY, ( uint32_t ) desc->nav);
}

static bool encode_rating(XtkBatch *batch, XtkNodeRef target, XtkEl const *prev, XtkEl const *el) {
	if (XTK_EL_DATA(el)->type != XTK_CTRL_RATING) return true;
	XtkRatingDesc const *desc       = XTK_EL_DETAIL(el, XtkRatingDesc);
	XtkRatingDesc const *old        = prev ? XTK_EL_DETAIL(prev, XtkRatingDesc) : NULL;
	int                  max_r      = desc->max_rating > 0 ? desc->max_rating : 5;
	int                  prev_max   = old && old->max_rating > 0 ? old->max_rating : 5;
	ScalarField          scalars [] = {
	  {XTK_PROP_VALUE_F64,       SCALAR_F64,  !old || old->value != desc->value,                         {.f64 = desc->value}     },
	  {XTK_PROP_MAX_F64,         SCALAR_F64,  !old || prev_max != max_r,                                 {.f64 = ( double ) max_r}},
	  {XTK_PROP_PLACEHOLDER_F64, SCALAR_F64,  !old || old->placeholder_value != desc->placeholder_value,
	   {.f64 = desc->placeholder_value}                                                                                           },
	  {XTK_PROP_INITIAL_VALUE,   SCALAR_I32,  !old || old->initial_set_value != desc->initial_set_value,
	   {.i32 = desc->initial_set_value}                                                                                           },
	  {XTK_PROP_CLEAR_ENABLED,   SCALAR_BOOL, !old || old->is_clear_enabled != desc->is_clear_enabled,
	   {.b = desc->is_clear_enabled}                                                                                              },
	  {XTK_PROP_READ_ONLY,       SCALAR_BOOL, !old || old->is_read_only != desc->is_read_only,           {.b = desc->is_read_only}},
	};
	if (!encode_scalar_fields(batch, target, scalars, sizeof(scalars) / sizeof(scalars [0]))) return false;
	return encode_string_change(batch, target, XTK_PROP_TEXT, old != NULL, old ? old->caption : NULL, desc->caption);
}

static bool encode_tree_item(XtkBatch *batch, XtkNodeRef target, XtkEl const *prev, XtkEl const *el) {
	if (XTK_EL_DATA(el)->type != XTK_CTRL_TREEITEM) return true;
	if ((!prev || XTK_EL_DETAIL(prev, XtkListItemDesc)->expanded != XTK_EL_DETAIL(el, XtkListItemDesc)->expanded)
	    && !value_bool(batch, target, XTK_PROP_EXPANDED, XTK_EL_DETAIL(el, XtkListItemDesc)->expanded))
		return false;
	return !((!prev || !streq(XTK_EL_DETAIL(prev, XtkListItemDesc)->icon, XTK_EL_DETAIL(el, XtkListItemDesc)->icon))
	         && XTK_EL_DETAIL(el, XtkListItemDesc)->icon)
	    || value_string(batch, target, XTK_PROP_ICON, XTK_EL_DETAIL(el, XtkListItemDesc)->icon);
}

static bool tree_nodes_equal(XtkTreeNodeDesc const *a, XtkTreeNodeDesc const *b, int32_t count) {
	if (count <= 0) return true;
	if (!a || !b) return false;
	for (int32_t i = 0; i < count; i++)
		if (!streq(a [i].text, b [i].text)
		    || !streq(a [i].icon, b [i].icon)
		    || a [i].expanded != b [i].expanded
		    || a [i].disabled != b [i].disabled
		    || a [i].checked != b [i].checked
		    || a [i].child_count != b [i].child_count
		    || !tree_nodes_equal(a [i].children, b [i].children, a [i].child_count))
			return false;
	return true;
}

static bool tree_desc_equal(XtkTreeDesc const *a, XtkTreeDesc const *b) {
	return a && b && a->nroot == b->nroot && tree_nodes_equal(a->roots, b->roots, a->nroot);
}

static bool encode_tree_selection(XtkBatch *batch, XtkNodeRef target, XtkTreeDesc const *old, XtkTreeDesc const *desc) {
	if (desc->sel_mode != XTK_TREE_SELECT_SINGLE) return true;
	bool same = old ? old->sel == desc->sel && old->sel_mode == desc->sel_mode : desc->sel == 0;
	return same || value_i32(batch, target, XTK_PROP_SELECTED_INDEX, desc->sel > 0 ? desc->sel - 1 : -1);
}

static bool
encode_tree_view_opt(XtkBatch *batch, XtkNodeRef target, XtkEl const *prev, XtkEl const *el, bool skip_model) {
	XtkTreeDesc const *desc  = XTK_EL_DETAIL(el, XtkTreeDesc);
	XtkTreeDesc const *old   = prev ? XTK_EL_DETAIL(prev, XtkTreeDesc) : NULL;
	float              h     = desc->rowh > 0.0f ? desc->rowh : 32.0f;
	float              old_h = old && old->rowh > 0.0f ? old->rowh : 32.0f;
	if ((!prev || old_h != h) && !value_f32(batch, target, XTK_PROP_ITEM_HEIGHT, h)) return false;
	if ((!prev || old->sel_mode != desc->sel_mode)
	    && !value_enum(batch, target, XTK_PROP_SELECTION_MODE, ( uint32_t ) desc->sel_mode))
		return false;
	if (!should_skip_model(prev, skip_model) && !tree_desc_equal(old, desc) && !xtk_items_tree(batch, target, desc))
		return false;
	return encode_tree_selection(batch, target, old, desc);
}

static bool encode_tree_view(XtkBatch *batch, XtkNodeRef target, XtkEl const *prev, XtkEl const *el) {
	return encode_tree_view_opt(batch, target, prev, el, false);
}

static float person_picture_size(XtkPersonPictureDesc const *desc) {
	return desc && desc->size > 0.0f ? desc->size : 96.0f;
}

static bool encode_person_picture(XtkBatch *batch, XtkNodeRef target, XtkEl const *prev, XtkEl const *el) {
	if (XTK_EL_DATA(el)->type != XTK_CTRL_AVATAR) return true;
	XtkPersonPictureDesc const *desc       = XTK_EL_DETAIL(el, XtkPersonPictureDesc);
	XtkPersonPictureDesc const *old        = prev ? XTK_EL_DETAIL(prev, XtkPersonPictureDesc) : NULL;
	StringField                 strings [] = {
	  {XTK_PROP_TEXT,        old ? old->display_name : NULL, desc->display_name},
	  {XTK_PROP_INITIALS,    old ? old->initials : NULL,     desc->initials    },
	  {XTK_PROP_BADGE_GLYPH, old ? old->badge_glyph : NULL,  desc->badge_glyph },
	  {XTK_PROP_BADGE_TEXT,  old ? old->badge_text : NULL,   desc->badge_text  },
	};
	if (!encode_string_fields(batch, target, old != NULL, strings, sizeof(strings) / sizeof(strings [0]))) return false;
	float       size       = person_picture_size(desc);
	float       prev_size  = person_picture_size(old);
	ScalarField scalars [] = {
	  {XTK_PROP_IMAGE_SOURCE,       SCALAR_RESOURCE, !old || old->image != desc->image,               {.resource = desc->image}  },
	  {XTK_PROP_BADGE_IMAGE_SOURCE, SCALAR_RESOURCE, !old || old->badge_image != desc->badge_image,
	   {.resource = desc->badge_image}                                                                                           },
	  {XTK_PROP_WIDTH,              SCALAR_F32,      !old || prev_size != size,                       {.f32 = size}              },
	  {XTK_PROP_HEIGHT,             SCALAR_F32,      !old || prev_size != size,                       {.f32 = size}              },
	  {XTK_PROP_BADGE_VALUE,        SCALAR_I32,      !old || old->badge_number != desc->badge_number, {.i32 = desc->badge_number}},
	  {XTK_PROP_IS_GROUP,           SCALAR_BOOL,     !old || old->is_group != desc->is_group,         {.b = desc->is_group}      },
	};
	return encode_scalar_fields(batch, target, scalars, sizeof(scalars) / sizeof(scalars [0]));
}

static bool encode_pager(XtkBatch *batch, XtkNodeRef target, XtkEl const *prev, XtkEl const *el) {
	if (XTK_EL_DATA(el)->type != XTK_CTRL_PAGER) return true;
	XtkPagerDesc const *desc       = XTK_EL_DETAIL(el, XtkPagerDesc);
	XtkPagerDesc const *old        = prev ? XTK_EL_DETAIL(prev, XtkPagerDesc) : NULL;
	ScalarField         scalars [] = {
	  {XTK_PROP_ITEM_COUNT,      SCALAR_I32,  !old || old->nitem != desc->nitem,               {.i32 = desc->nitem}  },
	  {XTK_PROP_SELECTED_INDEX,  SCALAR_I32,  !old || old->sel != desc->sel,                   {.i32 = desc->sel}    },
	  {XTK_PROP_DISPLAY_MODE,    SCALAR_ENUM, !old || old->display_mode != desc->display_mode,
	   {.u32 = ( uint32_t ) desc->display_mode}                                                                      },
	  {XTK_PROP_FIRST_BUTTON,    SCALAR_ENUM, !old || old->first_button != desc->first_button,
	   {.u32 = ( uint32_t ) desc->first_button}                                                                      },
	  {XTK_PROP_PREVIOUS_BUTTON, SCALAR_ENUM, !old || old->prev_button != desc->prev_button,
	   {.u32 = ( uint32_t ) desc->prev_button}                                                                       },
	  {XTK_PROP_NEXT_BUTTON,     SCALAR_ENUM, !old || old->next_button != desc->next_button,
	   {.u32 = ( uint32_t ) desc->next_button}                                                                       },
	  {XTK_PROP_LAST_BUTTON,     SCALAR_ENUM, !old || old->last_button != desc->last_button,
	   {.u32 = ( uint32_t ) desc->last_button}                                                                       },
	  {XTK_PROP_HIDE_ENDS,       SCALAR_BOOL, !old || old->hide_ends != desc->hide_ends,       {.b = desc->hide_ends}},
	};
	if (!encode_scalar_fields(batch, target, scalars, sizeof(scalars) / sizeof(scalars [0]))) return false;
	StringField strings [] = {
	  {XTK_PROP_PREFIX, old ? old->prefix : NULL, desc->prefix},
	  {XTK_PROP_SUFFIX, old ? old->suffix : NULL, desc->suffix},
	};
	return encode_string_fields(batch, target, old != NULL, strings, 2u);
}

static bool encode_split_view(XtkBatch *batch, XtkNodeRef target, XtkEl const *prev, XtkEl const *el) {
	if (XTK_EL_DATA(el)->type != XTK_CTRL_SPLITVIEW) return true;
	XtkSplitViewDesc const *desc     = XTK_EL_DETAIL(el, XtkSplitViewDesc);
	XtkSplitViewDesc const *old      = prev ? XTK_EL_DETAIL(prev, XtkSplitViewDesc) : NULL;
	EnumField               enums [] = {
	  {XTK_PROP_DISPLAY_MODE,   old ? ( uint32_t ) old->display_mode : 0u,   ( uint32_t ) desc->display_mode  },
	  {XTK_PROP_PANE_PLACEMENT, old ? ( uint32_t ) old->pane_placement : 0u, ( uint32_t ) desc->pane_placement},
	};
	if (!encode_enum_fields(batch, target, old != NULL, enums, 2u)) return false;
	F32Field fields [] = {
	  {XTK_PROP_OPEN_PANE_LENGTH,    old ? old->open_pane_length : 0.0f,    desc->open_pane_length,    true},
	  {XTK_PROP_COMPACT_PANE_LENGTH, old ? old->compact_pane_length : 0.0f, desc->compact_pane_length, true},
	};
	if (!encode_f32_fields(batch, target, old != NULL, fields, 2u)) return false;
	return encode_bool_change(batch, target, XTK_PROP_OPEN, old != NULL, old ? old->pane_open : false, desc->pane_open);
}

static bool encode_title_bar(XtkBatch *batch, XtkNodeRef target, XtkEl const *prev, XtkEl const *el) {
	if (XTK_EL_DATA(el)->type != XTK_CTRL_TITLEBAR) return true;
	XtkTitleBarDesc const *desc = XTK_EL_DETAIL(el, XtkTitleBarDesc);
	XtkTitleBarDesc const *old  = prev ? XTK_EL_DETAIL(prev, XtkTitleBarDesc) : NULL;
	if (!encode_string_change(batch, target, XTK_PROP_ICON, old != NULL, old ? old->icon : NULL, desc->icon)
	    || !encode_string_change(
		  batch, target, XTK_PROP_SUBTITLE, old != NULL, old ? old->subtitle : NULL, desc->subtitle
		)
	    || !encode_bool_change(
		  batch, target, XTK_PROP_SHOW_BACK, old != NULL, old ? old->show_back : false, desc->show_back
		)
	    || !encode_bool_change(
		  batch, target, XTK_PROP_BACK_DISABLED, old != NULL, old ? old->back_disabled : false, desc->back_disabled
		)
	    || !encode_bool_change(
		  batch, target, XTK_PROP_SHOW_PANE_TOGGLE, old != NULL, old ? old->show_pane_toggle : false,
		  desc->show_pane_toggle
		)
	    || !encode_bool_change(
		  batch, target, XTK_PROP_INTEGRATE_WINDOW, old != NULL, old ? old->integrate_window : false,
		  desc->integrate_window
		))
		return false;
	return true;
}

static bool encode_nav_chrome(XtkBatch *batch, XtkNodeRef target, XtkNavDesc const *old, XtkNavDesc const *desc) {
	if (old->hide_settings != desc->hide_settings
	    && !value_bool(batch, target, XTK_PROP_SETTINGS_VISIBLE, !desc->hide_settings))
		return false;
	if (old->hide_header != desc->hide_header
	    && !value_bool(batch, target, XTK_PROP_ALWAYS_SHOW_HEADER, !desc->hide_header))
		return false;
	if (old->back_button != desc->back_button
	    && !value_enum(batch, target, XTK_PROP_NAV_BACK_BUTTON, desc->back_button))
		return false;
	if (old->back_enabled != desc->back_enabled
	    && !value_bool(batch, target, XTK_PROP_NAV_BACK_ENABLED, desc->back_enabled))
		return false;
	return encode_string_change(batch, target, XTK_PROP_PANE_TITLE, true, old->pane_title, desc->pane_title);
}

static bool encode_nav_opt(XtkBatch *batch, XtkNodeRef target, XtkEl const *prev, XtkEl const *el, bool skip_model) {
	XtkNavDesc const *desc = XTK_EL_DETAIL(el, XtkNavDesc);
	XtkNavDesc const *old  = prev ? XTK_EL_DETAIL(prev, XtkNavDesc) : &(XtkNavDesc) {.sel = -1};
	if (!prev && !skip_model && !xtk_items_nav(batch, target, desc)) return false;
	if (old->pane_mode != desc->pane_mode
	    && !value_enum(batch, target, XTK_PROP_DISPLAY_MODE, ( uint32_t ) desc->pane_mode))
		return false;
	if ((!prev || old->sel != desc->sel) && !value_i32(batch, target, XTK_PROP_SELECTED_INDEX, desc->sel)) return false;
	return encode_nav_chrome(batch, target, old, desc);
}

static bool encode_nav(XtkBatch *batch, XtkNodeRef target, XtkEl const *prev, XtkEl const *el) {
	return encode_nav_opt(batch, target, prev, el, false);
}

typedef bool (*EncodeStep)(XtkBatch *, XtkNodeRef, XtkEl const *, XtkEl const *);
typedef bool (*EncodeOptStep)(XtkBatch *, XtkNodeRef, XtkEl const *, XtkEl const *, bool);

static bool  encode_model_skipped(XtkBatch *batch, XtkNodeRef target, XtkEl const *el, bool *handled) {
	static EncodeOptStep const kSkipModel [XTK_CTRL_TYPE_COUNT] = {
	  [XTK_CTRL_LIST]       = encode_list_host_opt,
	  [XTK_CTRL_LISTBOX]    = encode_list_host_opt,
	  [XTK_CTRL_GRIDVIEW]   = encode_list_host_opt,
	  [XTK_CTRL_REPEATER]   = encode_list_host_opt,
	  [XTK_CTRL_ITEMSVIEW]  = encode_list_host_opt,
	  [XTK_CTRL_SUGGEST]    = encode_suggest_opt,
	  [XTK_CTRL_TABS]       = encode_tabs_opt,
	  [XTK_CTRL_COMBO]      = encode_combo_opt,
	  [XTK_CTRL_LOOPING]    = encode_looping_opt,
	  [XTK_CTRL_SELECTOR]   = encode_selector_bar_opt,
	  [XTK_CTRL_BREADCRUMB] = encode_breadcrumb_opt,
	  [XTK_CTRL_TREE]       = encode_tree_view_opt,
	  [XTK_CTRL_NAV]        = encode_nav_opt,
	};
	XtkCtrlType   type = XTK_EL_DATA(el)->type;
	EncodeOptStep step = type < XTK_CTRL_TYPE_COUNT ? kSkipModel [type] : NULL;
	*handled           = step != NULL;
	return !step || step(batch, target, NULL, el, true);
}

static bool encode_fonticon_strings(
  XtkBatch *batch, XtkNodeRef target, XtkEl const *prev, XtkEl const *el, XtkFontIconDesc const *was,
  XtkFontIconDesc const *now
) {
	char const *prev_glyph = prev ? XTK_EL_DATA(prev)->text : NULL;
	if (str_prop_changed(prev_glyph, prev != NULL, XTK_EL_DATA(el)->text)
	    && !value_string(batch, target, XTK_PROP_ICON, XTK_EL_DATA(el)->text))
		return false;
	return !str_prop_changed(was->font_family, prev != NULL, now->font_family)
	    || value_string(batch, target, XTK_PROP_FONT_FAMILY, now->font_family);
}

static bool encode_fonticon(XtkBatch *batch, XtkNodeRef target, XtkEl const *prev, XtkEl const *el) {
	XtkFontIconDesc const  zero = {0};
	XtkFontIconDesc const *was  = prev ? XTK_EL_DETAIL(prev, XtkFontIconDesc) : &zero;
	XtkFontIconDesc const *now  = XTK_EL_DETAIL(el, XtkFontIconDesc);
	if (!now) now = &zero;
	if (!encode_fonticon_strings(batch, target, prev, el, was, now)) return false;
	if (was->color.rgba != now->color.rgba && !value_color(batch, target, XTK_PROP_FOREGROUND, now->color))
		return false;
	ScalarField const fields [] = {
	  {XTK_PROP_FONT_SIZE,   SCALAR_F32,  was->size != now->size,                           {.f32 = now->size > 0.0f ? now->size : 0.0f}},
	  {XTK_PROP_FONT_WEIGHT, SCALAR_ENUM, was->weight != now->weight,                       {.u32 = ( uint32_t ) now->weight}           },
	  {XTK_PROP_MIRROR_RTL,  SCALAR_BOOL, was->mirrored_when_rtl != now->mirrored_when_rtl,
	   {.b = now->mirrored_when_rtl}                                                                                                    },
	};
	return encode_scalar_fields(batch, target, fields, 3u);
}

static bool encode_frame(XtkBatch *batch, XtkNodeRef target, XtkEl const *prev, XtkEl const *el) {
	XtkFrameDesc        zero = {0};
	XtkFrameDesc const *was  = prev ? XTK_EL_DETAIL(prev, XtkFrameDesc) : &zero;
	XtkFrameDesc const *now  = XTK_EL_DETAIL(el, XtkFrameDesc);
	if (!now) now = &zero;
	if ((!prev || was->transition != now->transition)
	    && !value_enum(batch, target, XTK_PROP_FRAME_TRANSITION, ( uint32_t ) now->transition))
		return false;
	if ((!prev || was->is_back != now->is_back) && !value_bool(batch, target, XTK_PROP_FRAME_BACK, now->is_back))
		return false;
	return (!prev && now->page_key == 0)
	    || (was->page_key == now->page_key)
	    || value_i32(batch, target, XTK_PROP_FRAME_PAGE_KEY, now->page_key);
}

static bool
encode_element_props_opt(XtkBatch *batch, XtkNodeRef target, XtkEl const *prev, XtkEl const *el, bool skip_model) {
	static EncodeStep const specialized [XTK_CTRL_TYPE_COUNT] = {
	  [XTK_CTRL_BUTTON]       = encode_button,
	  [XTK_CTRL_REPEAT]       = encode_button,
	  [XTK_CTRL_SPLIT]        = encode_button,
	  [XTK_CTRL_TOGGLESPLIT]  = encode_button,
	  [XTK_CTRL_DROPDOWN]     = encode_button,
	  [XTK_CTRL_LINK]         = encode_link,
	  [XTK_CTRL_MENUITEM]     = encode_menu_item,
	  [XTK_CTRL_CHECKBOX]     = encode_toggle,
	  [XTK_CTRL_RADIO]        = encode_toggle,
	  [XTK_CTRL_SWITCH]       = encode_toggle,
	  [XTK_CTRL_SLIDER]       = encode_slider,
	  [XTK_CTRL_SCROLLBAR]    = encode_scroll_bar,
	  [XTK_CTRL_COLITEM]      = encode_colitem,
	  [XTK_CTRL_COMMANDBAR]   = encode_commandbar,
	  [XTK_CTRL_APPBARBUTTON] = encode_appbar,
	  [XTK_CTRL_APPBARTOGGLE] = encode_appbar,
	  [XTK_CTRL_APPBARSEP]    = encode_appbar,
	  [XTK_CTRL_SCROLL]       = encode_scroll,
	  [XTK_CTRL_NUMBER]       = encode_number,
	  [XTK_CTRL_IMAGE]        = encode_image,
	  [XTK_CTRL_BADGE]        = encode_badge,
	  [XTK_CTRL_PROGRESS]     = encode_progress,
	  [XTK_CTRL_PROGRESSRING] = encode_progress,
	  [XTK_CTRL_TEXT]         = encode_text_style,
	  [XTK_CTRL_LISTITEM]     = encode_list_item,
	  [XTK_CTRL_LIST]         = encode_list_host,
	  [XTK_CTRL_LISTBOX]      = encode_list_host,
	  [XTK_CTRL_GRIDVIEW]     = encode_list_host,
	  [XTK_CTRL_REPEATER]     = encode_list_host,
	  [XTK_CTRL_ITEMSVIEW]    = encode_list_host,
	  [XTK_CTRL_EXPANDER]     = encode_expander,
	  [XTK_CTRL_INFOBAR]      = encode_info_bar,
	  [XTK_CTRL_DIALOG]       = encode_dialog,
	  [XTK_CTRL_TEACHTIP]     = encode_teaching_tip,
	  [XTK_CTRL_REFRESH]      = encode_refresh,
	  [XTK_CTRL_SUGGEST]      = encode_suggest,
	  [XTK_CTRL_FLIP]         = encode_flip,
	  [XTK_CTRL_TABS]         = encode_tabs,
	  [XTK_CTRL_PIPS]         = encode_pips,
	  [XTK_CTRL_RADIOGROUP]   = encode_radio_buttons,
	  [XTK_CTRL_COMBO]        = encode_combo,
	  [XTK_CTRL_LOOPING]      = encode_looping,
	  [XTK_CTRL_SELECTOR]     = encode_selector_bar,
	  [XTK_CTRL_BREADCRUMB]   = encode_breadcrumb,
	  [XTK_CTRL_RATING]       = encode_rating,
	  [XTK_CTRL_TREEITEM]     = encode_tree_item,
	  [XTK_CTRL_TREE]         = encode_tree_view,
	  [XTK_CTRL_AVATAR]       = encode_person_picture,
	  [XTK_CTRL_PAGER]        = encode_pager,
	  [XTK_CTRL_SPLITVIEW]    = encode_split_view,
	  [XTK_CTRL_TITLEBAR]     = encode_title_bar,
	  [XTK_CTRL_NAV]          = encode_nav,
	  [XTK_CTRL_DATEPICKER]   = xtk_encode_date_picker,
	  [XTK_CTRL_TIMEPICKER]   = xtk_encode_time_picker,
	  [XTK_CTRL_CALENDAR]     = xtk_encode_calendar,
	  [XTK_CTRL_COLORPICKER]  = xtk_encode_color_picker,
	  [XTK_CTRL_CONTAINER]    = encode_dragdrop,
	  [XTK_CTRL_FRAME]        = encode_frame,
	  [XTK_CTRL_FONTICON]     = encode_fonticon,
	};
	if (!encode_common(batch, target, prev, el)) return false;
	if (!encode_stack(batch, target, prev, el)) return false;
	if (!encode_text(batch, target, prev, el)) return false;
	if (skip_model && !prev) {
		bool handled = false;
		bool ok      = encode_model_skipped(batch, target, el, &handled);
		if (handled) return ok;
	}
	EncodeStep step = XTK_EL_DATA(el)->type < XTK_CTRL_TYPE_COUNT ? specialized [XTK_EL_DATA(el)->type] : NULL;
	return !step || step(batch, target, prev, el);
}

static bool encode_element_props(XtkBatch *batch, XtkNodeRef target, XtkEl const *prev, XtkEl const *el) {
	return encode_element_props_opt(batch, target, prev, el, false);
}

typedef struct ModelVerSlot {
	uint16_t size;
	uint16_t off;
} ModelVerSlot;

#define VER_SLOT(T) {( uint16_t ) sizeof(T), ( uint16_t ) offsetof(T, version)}

XtkModelVer xtk_el_model_ver(XtkEl const *el) {
	static ModelVerSlot const kVerSlots [XTK_CTRL_TYPE_COUNT] = {
	  [XTK_CTRL_LIST]       = VER_SLOT(XtkListDesc),
	  [XTK_CTRL_LISTBOX]    = VER_SLOT(XtkListDesc),
	  [XTK_CTRL_GRIDVIEW]   = VER_SLOT(XtkListDesc),
	  [XTK_CTRL_REPEATER]   = VER_SLOT(XtkListDesc),
	  [XTK_CTRL_ITEMSVIEW]  = VER_SLOT(XtkListDesc),
	  [XTK_CTRL_TREE]       = VER_SLOT(XtkTreeDesc),
	  [XTK_CTRL_NAV]        = VER_SLOT(XtkNavDesc),
	  [XTK_CTRL_COMBO]      = VER_SLOT(XtkComboDesc),
	  [XTK_CTRL_LOOPING]    = VER_SLOT(XtkLoopingDesc),
	  [XTK_CTRL_SUGGEST]    = VER_SLOT(XtkAutoSuggestDesc),
	  [XTK_CTRL_TABS]       = VER_SLOT(XtkTabViewDesc),
	  [XTK_CTRL_SELECTOR]   = VER_SLOT(XtkSelectorBarDesc),
	  [XTK_CTRL_BREADCRUMB] = VER_SLOT(XtkBreadcrumbDesc),
	};
	if (!el) return (XtkModelVer) {0};
	XtkCtrlType  type   = XTK_EL_DATA(el)->type;
	ModelVerSlot s      = type < XTK_CTRL_TYPE_COUNT ? kVerSlots [type] : (ModelVerSlot) {0};
	void const  *detail = s.size ? xtk_el_detail(el, s.size) : NULL;
	if (!detail) return (XtkModelVer) {0};
	XtkModelVer ver;
	memcpy(&ver, ( char const * ) detail + s.off, sizeof(ver));
	return ver;
}

#undef VER_SLOT

bool xtk_encode_props_view(XtkBatch *batch, XtkNodeRef target, XtkEl const *el, bool skip_model) {
	return encode_element_props_opt(batch, target, NULL, el, skip_model);
}

static bool component_props_equal(XtkEl const *prev, XtkEl const *el) {
	if (!prev || XTK_EL_DATA(prev)->component_props_size != XTK_EL_DATA(el)->component_props_size) return false;
	if (!XTK_EL_DATA(el)->component_props_size) return true;
	return memcmp(
			 XTK_EL_DATA(prev)->component_props, XTK_EL_DATA(el)->component_props, XTK_EL_DATA(el)->component_props_size
		   )
	    == 0;
}

bool xtk_encode_props(XtkBatch *batch, XtkNodeRef target, XtkEl const *prev, XtkEl const *el) {
	if (!encode_element_props(batch, target, prev, el)) return false;
	if (XTK_EL_DATA(el)->type < XTK_CTRL_ID_COMPONENT_BASE || component_props_equal(prev, el)) return true;
	return value_bytes(
	  batch, target, XTK_PROP_COMPONENT_PROPS, XTK_EL_DATA(el)->component_props, XTK_EL_DATA(el)->component_props_size
	);
}

bool xtk_encode_create(XtkBatch *batch, XtkNodeRef parent, XtkNodeRef before, XtkEl const *el, XtkLocalId *out_local) {
	XtkPropPatch component = {
	  .id = XTK_PROP_COMPONENT_PROPS,
	  .value = {
	    .kind = XTK_VALUE_BYTES,
	    .u.bytes = {.data = ( uint8_t * ) ( uintptr_t ) XTK_EL_DATA(el)->component_props, .len = XTK_EL_DATA(el)->component_props_size},
	  },
	};
	bool has_component_props
	  = XTK_EL_DATA(el)->type >= XTK_CTRL_ID_COMPONENT_BASE && XTK_EL_DATA(el)->component_props_size > 0u;
	XtkLocalId local = xtk_batch_create(
	  batch, XTK_EL_DATA(el)->type, parent, before, has_component_props ? &component : NULL,
	  has_component_props ? 1u : 0u
	);
	if (local == XTK_LOCAL_INVALID) return false;
	if (!encode_element_props(batch, xtk_ref_local(local), NULL, el)) return false;
	*out_local = local;
	return true;
}
