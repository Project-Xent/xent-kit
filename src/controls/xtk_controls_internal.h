#ifndef XTK_CONTROLS_INTERNAL_H
#define XTK_CONTROLS_INTERNAL_H

#include <xtk/xtk_controls.h>

uint32_t xtk_controls_text_len(char const *text, uint32_t len);
void     xtk_controls_append_bool(
  XtkPropPatch *patches, uint32_t *count, bool has, XtkPropertyId id, bool value, XtkChangeStamp change
);
void xtk_controls_append_i32(
  XtkPropPatch *patches, uint32_t *count, bool has, XtkPropertyId id, int32_t value, XtkChangeStamp change
);
void xtk_controls_append_f32(
  XtkPropPatch *patches, uint32_t *count, bool has, XtkPropertyId id, float value, XtkChangeStamp change
);
void xtk_controls_append_f64(
  XtkPropPatch *patches, uint32_t *count, bool has, XtkPropertyId id, double value, XtkChangeStamp change
);
void xtk_controls_append_enum(
  XtkPropPatch *patches, uint32_t *count, bool has, XtkPropertyId id, uint32_t value, XtkChangeStamp change
);
void xtk_controls_append_color(
  XtkPropPatch *patches, uint32_t *count, bool has, XtkPropertyId id, XtkColor value, XtkChangeStamp change
);
void xtk_controls_append_resource(
  XtkPropPatch *patches, uint32_t *count, bool has, XtkPropertyId id, XtkResource value, XtkChangeStamp change
);
void xtk_controls_append_string(
  XtkPropPatch *patches, uint32_t *count, bool has, XtkPropertyId id, char const *text, uint32_t len,
  XtkChangeStamp change
);

#endif
