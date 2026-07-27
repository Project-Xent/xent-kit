#include <xtk/xtk_alloc.h>
#include <xtk/xtk_nav_model.h>

#include <stdio.h>
#include <string.h>

#define EXPECT(cond, msg)              \
	do {                               \
		if (!(cond)) {                 \
			printf("FAIL: %s\n", msg); \
			return 1;                  \
		}                              \
	}                                  \
	while (0)

int main(void) {
	XtkNavItemDesc items [] = {
	  {XTK_NAV_ITEM,      "Home",     "Home"    },
	  {XTK_NAV_CHILD,     "Document", "Details" },
	  {XTK_NAV_HEADER,    NULL,       "Other"   },
	  {XTK_NAV_SEPARATOR, NULL,       NULL      },
	  {XTK_NAV_FOOTER,    "Settings", "Settings"},
	};
	XtkNavDesc desc = {.items = items, .nitem = 5, .sel = 1, .window_title_bar = true, .app_title = "Gallery"};
	uint32_t   size = xtk_nav_model_size(&desc);
	uint8_t   *data = xtk_alloc(size);
	EXPECT(size > 32u && data, "model allocation");
	EXPECT(xtk_nav_model_write(&desc, data, size), "model encode");

	XtkNavModelView model;
	EXPECT(xtk_nav_model_open(data, size, &model), "model decode");
	EXPECT(model.count == 5u, "item count");
	EXPECT((model.flags & XTK_NAV_MODEL_WINDOW_TITLE_BAR) != 0u, "title bar flag");
	EXPECT(strcmp(model.app_title, "Gallery") == 0, "app title");

	XtkNavModelItemView item;
	EXPECT(xtk_nav_model_item(&model, 1u, &item), "child decode");
	EXPECT(item.kind == XTK_NAV_CHILD && item.parent == 0, "child parent");
	EXPECT(strcmp(item.icon, "Document") == 0 && strcmp(item.label, "Details") == 0, "child strings");
	EXPECT(xtk_nav_model_item(&model, 3u, &item), "separator decode");
	EXPECT(!item.icon && !item.label, "nullable strings");

	data [0] = 0u;
	EXPECT(!xtk_nav_model_open(data, size, &model), "bad magic rejected");
	xtk_alloc_free(data);
	printf("PASS: nav model wire contract\n");
	return 0;
}
