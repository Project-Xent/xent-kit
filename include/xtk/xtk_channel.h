#ifndef XTK_CHANNEL_H
#define XTK_CHANNEL_H

#include "xtk_scene.h"

typedef struct XtkChannel XtkChannel;

XtkChannel               *xtk_channel_create(XtkScene scene);
void                      xtk_channel_destroy(XtkChannel *ch);
uint32_t                  xtk_channel_pending(XtkChannel const *ch);
void                      xtk_channel_clear(XtkChannel *ch);

bool xtk_channel_set(XtkChannel *ch, XtkCtrl target, XtkPropertyId id, XtkValue value, XtkChangeStamp change);
bool xtk_channel_set_bool(XtkChannel *ch, XtkCtrl target, XtkPropertyId id, bool value, XtkChangeStamp change);
bool xtk_channel_set_i32(XtkChannel *ch, XtkCtrl target, XtkPropertyId id, int32_t value, XtkChangeStamp change);
bool xtk_channel_set_f32(XtkChannel *ch, XtkCtrl target, XtkPropertyId id, float value, XtkChangeStamp change);
bool xtk_channel_set_f64(XtkChannel *ch, XtkCtrl target, XtkPropertyId id, double value, XtkChangeStamp change);
bool xtk_channel_set_enum(XtkChannel *ch, XtkCtrl target, XtkPropertyId id, uint32_t value, XtkChangeStamp change);
bool xtk_channel_set_color(XtkChannel *ch, XtkCtrl target, XtkPropertyId id, XtkColor value, XtkChangeStamp change);
bool xtk_channel_set_resource(
  XtkChannel *ch, XtkCtrl target, XtkPropertyId id, XtkResource value, XtkChangeStamp change
);
bool xtk_channel_set_string(
  XtkChannel *ch, XtkCtrl target, XtkPropertyId id, char const *data, uint32_t len, XtkChangeStamp change
);

XtkBatchResult *xtk_channel_flush(XtkChannel *ch, XtkBatchDiag *diagnostic);
bool            xtk_channel_commit(XtkChannel *ch, XtkBatchDiag *diagnostic);

#endif
