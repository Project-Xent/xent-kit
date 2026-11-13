#include "xtk_internal.h"

XtkEl *xtk_date_picker(XtkUi *ui, XtkDatePickerDesc desc) {
	XtkEl *el = xtk_el_new(ui, XTK_CTRL_DATEPICKER, NULL);
	if (!el) return NULL;
	desc.header = xtk_strdup(ui, desc.header);
	return XTK_EL_STORE(el, desc) ? el : NULL;
}

XtkEl *xtk_time_picker(XtkUi *ui, XtkTimePickerDesc desc) {
	XtkEl *el = xtk_el_new(ui, XTK_CTRL_TIMEPICKER, NULL);
	if (!el) return NULL;
	desc.header = xtk_strdup(ui, desc.header);
	return XTK_EL_STORE(el, desc) ? el : NULL;
}

XtkEl *xtk_calendar_view(XtkUi *ui, XtkCalendarDesc desc) {
	XtkEl *el = xtk_el_new(ui, XTK_CTRL_CALENDAR, NULL);
	return el && XTK_EL_STORE(el, desc) ? el : NULL;
}

XtkEl *xtk_color_picker(XtkUi *ui, XtkColorPickerDesc desc) {
	XtkEl *el = xtk_el_new(ui, XTK_CTRL_COLORPICKER, NULL);
	return el && XTK_EL_STORE(el, desc) ? el : NULL;
}
