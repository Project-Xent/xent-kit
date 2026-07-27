#include "xtk_controls_internal.h"

#include <string.h>

uint32_t xtk_controls_text_len(char const *text, uint32_t len) {
	if (!text) return 0u;
	return len ? len : ( uint32_t ) strlen(text);
}

#define DEFINE_APPEND(suffix, c_type, wire_kind, field)                                                       \
	void xtk_controls_append_##suffix(                                                                        \
	  XtkPropPatch *patches, uint32_t *count, bool has, XtkPropertyId id, c_type value, XtkChangeStamp change \
	) {                                                                                                       \
		if (!has) return;                                                                                     \
		patches [(*count)++] = (XtkPropPatch) {                                                               \
		  .id     = id,                                                                                       \
		  .value  = {.kind = wire_kind, .u.field = value},                                                    \
		  .change = change,                                                                                   \
		};                                                                                                    \
	}

DEFINE_APPEND(bool, bool, XTK_VALUE_BOOL, b)
DEFINE_APPEND(i32, int32_t, XTK_VALUE_I32, i32)
DEFINE_APPEND(f32, float, XTK_VALUE_F32, f32)
DEFINE_APPEND(f64, double, XTK_VALUE_F64, f64)
DEFINE_APPEND(enum, uint32_t, XTK_VALUE_ENUM, u32)
DEFINE_APPEND(color, XtkColor, XTK_VALUE_COLOR, color)
DEFINE_APPEND(resource, XtkResource, XTK_VALUE_RESOURCE, resource)

void xtk_controls_append_string(
  XtkPropPatch *patches, uint32_t *count, bool has, XtkPropertyId id, char const *text, uint32_t len,
  XtkChangeStamp change
) {
	if (!has) return;
	patches [(*count)++] = (XtkPropPatch) {
	  .id = id,
	  .value = {
	    .kind = XTK_VALUE_STRING,
	    .u.string = {.data = ( char * ) text, .len = xtk_controls_text_len(text, len)},
	  },
	  .change = change,
	};
}
