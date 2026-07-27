#include <stdio.h>
#include <string.h>
#include <xtk/xtk_catalog.h>

#define EXPECT(cond, msg)              \
	do {                               \
		if (!(cond)) {                 \
			printf("FAIL: %s\n", msg); \
			return 1;                  \
		}                              \
	}                                  \
	while (0)

static XtkPropertyId const layout_properties [] = {
  XTK_PROP_WIDTH,
  XTK_PROP_HEIGHT,
  XTK_PROP_GROW,
  XTK_PROP_ALIGN_SELF,
  XTK_PROP_MARGIN_LEFT,
  XTK_PROP_MARGIN_TOP,
  XTK_PROP_MARGIN_RIGHT,
  XTK_PROP_MARGIN_BOTTOM,
  XTK_PROP_TOOLTIP,
};

int main(void) {
	EXPECT(XTK_CTRL_INVALID == 0u, "control handle zero invalid");
	EXPECT(XTK_CTRL_INVALID == XTK_CTRL_ID_INVALID, "handle and type invalid agree");
	EXPECT(XTK_CTRL_CONTAINER == 1, "first built-in starts at one");
	EXPECT(XTK_CTRL_ID_COMPONENT_BASE > ( XtkCtrlId ) XTK_CTRL_TYPE_COUNT, "component range disjoint");

	for (XtkCtrlId id = 1u; id < ( XtkCtrlId ) XTK_CTRL_TYPE_COUNT; id++) {
		XtkCtrlDesc const *control = xtk_catalog_control(id);
		EXPECT(control, "every built-in has descriptor");
		EXPECT(control->id == id, "descriptor id matches index");
		EXPECT(control->name && control->name [0], "descriptor has name");
		EXPECT(control->create_invalidates != XTK_INVALIDATE_NONE, "create invalidates");
		EXPECT(control->destroy_invalidates != XTK_INVALIDATE_NONE, "destroy invalidates");
		for (uint32_t i = 0; i < sizeof(layout_properties) / sizeof(layout_properties [0]); i++)
			EXPECT(
			  xtk_catalog_control_property(id, layout_properties [i]),
			  "every built-in supports element layout properties"
			);
	}
	EXPECT(!xtk_catalog_control(XTK_CTRL_ID_COMPONENT_BASE), "components are not standard catalog entries");
	for (XtkPropertyId id = 1u; id < ( XtkPropertyId ) XTK_PROP_STANDARD_COUNT; id++)
		EXPECT(xtk_catalog_property(id), "every standard property has descriptor");
	for (XtkEventId id = 1u; id < ( XtkEventId ) XTK_EVENT_STANDARD_COUNT; id++)
		EXPECT(xtk_catalog_event(id), "every standard event has descriptor");

	XtkPropDesc const *text = xtk_catalog_property(XTK_PROP_TEXT);
	EXPECT(text && text->kind == XTK_PROP_KIND_STRING, "text kind");
	EXPECT((text->invalidates & XTK_INVALIDATE_LAYOUT) != 0u, "text invalidates layout");
	EXPECT(xtk_catalog_control_property(XTK_CTRL_BUTTON, XTK_PROP_TEXT), "button supports text");
	EXPECT(!xtk_catalog_control_property(XTK_CTRL_BUTTON, XTK_PROP_VALUE_F64), "absent property fails");
	EXPECT(xtk_catalog_control_property(XTK_CTRL_SLIDER, XTK_PROP_TICK_FREQUENCY), "slider supports tick frequency");
	EXPECT(xtk_catalog_control_property(XTK_CTRL_SLIDER, XTK_PROP_TICK_PLACEMENT), "slider supports tick placement");
	EXPECT(xtk_catalog_control_property(XTK_CTRL_SLIDER, XTK_PROP_SLIDER_SNAPS_TO), "slider supports snap selection");
	EXPECT(!xtk_catalog_control_property(XTK_CTRL_PROGRESS, XTK_PROP_SMALL_CHANGE), "progress rejects slider stepping");

	XtkPropDesc const *image = xtk_catalog_property(XTK_PROP_IMAGE_SOURCE);
	EXPECT(image && image->kind == XTK_PROP_KIND_RESOURCE, "image is resource");
	EXPECT(image->resource_type == XTK_RESOURCE_TYPE_IMAGE, "image resource type");

	XtkEventDesc const *query = xtk_catalog_event(XTK_EVENT_QUERY);
	EXPECT(query && query->payload_kind == XTK_EVENT_PAYLOAD_QUERY, "query payload type");
	EXPECT(xtk_catalog_control_event(XTK_CTRL_SUGGEST, XTK_EVENT_QUERY), "auto suggest query event");
	EXPECT(!xtk_catalog_control_event(XTK_CTRL_TEXT, XTK_EVENT_INVOKE), "absent event fails");
	printf("PASS: exhaustive standard catalog contract\n");
	return 0;
}
