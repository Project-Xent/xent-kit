#include "xtk_encode.h"
#include "../xtk_internal.h"

#include <string.h>

typedef struct PickerField {
	XtkPropertyId id;
	XtkValueKind  kind;
	bool          changed;
	XtkValue      value;
} PickerField;

static bool        picker_streq(char const *a, char const *b) { return strcmp(a ? a : "", b ? b : "") == 0; }

static PickerField picker_i32(XtkPropertyId id, bool changed, int32_t v) {
	return (PickerField) {
	  id, XTK_VALUE_I32, changed, {.kind = XTK_VALUE_I32, .u.i32 = v}
    };
}

static PickerField picker_bool(XtkPropertyId id, bool changed, bool v) {
	return (PickerField) {
	  id, XTK_VALUE_BOOL, changed, {.kind = XTK_VALUE_BOOL, .u.b = v}
    };
}

static PickerField picker_enum(XtkPropertyId id, bool changed, uint32_t v) {
	return (PickerField) {
	  id, XTK_VALUE_ENUM, changed, {.kind = XTK_VALUE_ENUM, .u.u32 = v}
    };
}

static PickerField picker_string(XtkPropertyId id, bool changed, char const *text) {
	XtkValue value      = {.kind = XTK_VALUE_STRING};
	value.u.string.data = ( char * ) (text ? text : "");
	value.u.string.len  = ( uint32_t ) strlen(value.u.string.data);
	return (PickerField) {id, XTK_VALUE_STRING, changed, value};
}

static PickerField picker_color(XtkPropertyId id, bool changed, XtkColor c) {
	return (PickerField) {
	  id, XTK_VALUE_COLOR, changed, {.kind = XTK_VALUE_COLOR, .u.color = c}
    };
}

static bool picker_emit(XtkBatch *batch, XtkNodeRef target, PickerField const *fields, uint32_t count) {
	for (uint32_t i = 0; i < count; i++) {
		if (!fields [i].changed) continue;
		if (!xtk_batch_set(batch, target, fields [i].id, fields [i].value, (XtkChangeStamp) {0})) return false;
	}
	return true;
}

#define PICKER_EMIT(batch_, target_, fields_)                                      \
	picker_emit(batch_, target_, fields_, sizeof(fields_) / sizeof((fields_) [0]))

bool xtk_encode_date_picker(XtkBatch *batch, XtkNodeRef target, XtkEl const *prev, XtkEl const *el) {
	XtkDatePickerDesc const *d         = XTK_EL_DETAIL(el, XtkDatePickerDesc);
	XtkDatePickerDesc const *o         = prev ? XTK_EL_DETAIL(prev, XtkDatePickerDesc) : NULL;
	PickerField              fields [] = {
	  picker_string(XTK_PROP_HEADER, !o || !picker_streq(o->header, d->header), d->header),
	  picker_i32(XTK_PROP_MIN_YEAR, !o || o->minyear != d->minyear, d->minyear),
	  picker_i32(XTK_PROP_MAX_YEAR, !o || o->maxyear != d->maxyear, d->maxyear),
	  picker_i32(XTK_PROP_DATE, !o || o->date != d->date, d->date),
	  picker_bool(XTK_PROP_ENABLED, !o || o->disabled != d->disabled, !d->disabled),
	};
	return PICKER_EMIT(batch, target, fields);
}

bool xtk_encode_time_picker(XtkBatch *batch, XtkNodeRef target, XtkEl const *prev, XtkEl const *el) {
	XtkTimePickerDesc const *d         = XTK_EL_DETAIL(el, XtkTimePickerDesc);
	XtkTimePickerDesc const *o         = prev ? XTK_EL_DETAIL(prev, XtkTimePickerDesc) : NULL;
	int32_t                  now       = d->has_time ? d->minutes : -1;
	int32_t                  then      = o && o->has_time ? o->minutes : -1;
	PickerField              fields [] = {
	  picker_string(XTK_PROP_HEADER, !o || !picker_streq(o->header, d->header), d->header),
	  picker_enum(XTK_PROP_CLOCK, !o || o->clock != d->clock, ( uint32_t ) d->clock),
	  picker_i32(XTK_PROP_MINUTE_INCREMENT, !o || o->step != d->step, d->step),
	  picker_i32(XTK_PROP_TIME, !o || then != now, now),
	  picker_bool(XTK_PROP_ENABLED, !o || o->disabled != d->disabled, !d->disabled),
	};
	return PICKER_EMIT(batch, target, fields);
}

bool xtk_encode_calendar(XtkBatch *batch, XtkNodeRef target, XtkEl const *prev, XtkEl const *el) {
	XtkCalendarDesc const *d         = XTK_EL_DETAIL(el, XtkCalendarDesc);
	XtkCalendarDesc const *o         = prev ? XTK_EL_DETAIL(prev, XtkCalendarDesc) : NULL;
	PickerField            fields [] = {
	  picker_enum(XTK_PROP_SELECTION_MODE, !o || o->mode != d->mode, ( uint32_t ) d->mode),
	  picker_i32(XTK_PROP_MIN_DATE, !o || o->mindate != d->mindate, d->mindate),
	  picker_i32(XTK_PROP_MAX_DATE, !o || o->maxdate != d->maxdate, d->maxdate),
	  picker_i32(XTK_PROP_FIRST_DAY, !o || o->firstday != d->firstday, d->firstday),
	  picker_i32(XTK_PROP_DATE, !o || o->date != d->date, d->date),
	  picker_bool(XTK_PROP_ENABLED, !o || o->disabled != d->disabled, !d->disabled),
	};
	return PICKER_EMIT(batch, target, fields);
}

bool xtk_encode_color_picker(XtkBatch *batch, XtkNodeRef target, XtkEl const *prev, XtkEl const *el) {
	XtkColorPickerDesc const *d         = XTK_EL_DETAIL(el, XtkColorPickerDesc);
	XtkColorPickerDesc const *o         = prev ? XTK_EL_DETAIL(prev, XtkColorPickerDesc) : NULL;
	PickerField               fields [] = {
	  picker_enum(XTK_PROP_SPECTRUM, !o || o->spectrum != d->spectrum, ( uint32_t ) d->spectrum),
	  picker_bool(XTK_PROP_ALPHA_ENABLED, !o || o->alpha != d->alpha, d->alpha),
	  picker_bool(XTK_PROP_MORE_BUTTON_VISIBLE, !o || o->morebutton != d->morebutton, d->morebutton),
	  picker_color(XTK_PROP_COLOR, !o || o->color.rgba != d->color.rgba, d->color),
	  picker_bool(XTK_PROP_ENABLED, !o || o->disabled != d->disabled, !d->disabled),
	};
	return PICKER_EMIT(batch, target, fields);
}
