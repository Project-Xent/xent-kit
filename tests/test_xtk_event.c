#include <stdio.h>
#include <xtk/xtk_event.h>

#define EXPECT(cond, msg)              \
	do {                               \
		if (!(cond)) {                 \
			printf("FAIL: %s\n", msg); \
			return 1;                  \
		}                              \
	}                                  \
	while (0)

static uint32_t stop_event(void *arg, XtkEvent const *event) {
	uint32_t *seen = ( uint32_t * ) arg;
	*seen          = event->payload.u.query.len;
	return XTK_EVENT_HANDLED | XTK_EVENT_STOP_PROPAGATION;
}

int main(void) {
	EXPECT(xtk_event_phases_valid(XTK_EVENT_PHASE_MASK_TARGET), "target phase valid");
	EXPECT(xtk_event_phases_valid(XTK_EVENT_PHASE_MASK_ALL), "all phases valid");
	EXPECT(!xtk_event_phases_valid(0u), "empty phases invalid");
	EXPECT(!xtk_event_phases_valid(1u << 8), "unknown phase invalid");

	XtkEvent event = {
	  .id             = 1u,
	  .source         = 10u,
	  .target         = 11u,
	  .current_target = 12u,
	  .phase          = XTK_EVENT_PHASE_CAPTURE,
	  .cause          = XTK_EVENT_CAUSE_BINDING,
	  .scene_revision = 20u,
	  .change         = {.source = 30u, .revision = 40u},
	  .payload        = {
        .kind = XTK_EVENT_PAYLOAD_QUERY,
        .u.query = {.text = "save", .len = 4u, .index = 2},
      },
	};
	uint32_t seen        = 0u;
	uint32_t disposition = stop_event(&seen, &event);
	EXPECT(seen == 4u, "borrowed query payload");
	EXPECT(event.payload.u.query.index == 2, "query carries index");
	EXPECT(event.change.source == 30u && event.change.revision == 40u, "change stamp");
	EXPECT((disposition & XTK_EVENT_HANDLED) != 0u, "handled disposition");
	EXPECT((disposition & XTK_EVENT_STOP_PROPAGATION) != 0u, "stop disposition");

	event.payload = (XtkEventPayload) {
	  .kind     = XTK_EVENT_PAYLOAD_RATING,
	  .u.rating = {.value = 4.5, .count = 5},
	};
	EXPECT(event.payload.u.rating.value == 4.5 && event.payload.u.rating.count == 5, "rating payload");
	printf("PASS: immutable event wire contract\n");
	return 0;
}
