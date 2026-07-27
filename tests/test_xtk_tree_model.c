#include <xtk/xtk_tree_model.h>

#include <stdio.h>
#include <stdlib.h>
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
	XtkTreeNodeDesc children [] = {
	  {.text = "Alpha", .disabled = true  },
	  {.text = "Beta",  .icon = "Document"},
	};
	XtkTreeNodeDesc roots [] = {
	  {.text = "Folder", .icon = "Folder", .expanded = true, .children = children, .child_count = 2},
	  {.text = "Music", .icon = "MusicNote"},
	};
	XtkTreeDesc desc = {.roots = roots, .nroot = 2};
	uint32_t    size = xtk_tree_model_size(&desc);
	EXPECT(size > 16u, "model size");
	uint8_t *data = ( uint8_t * ) malloc(size);
	EXPECT(data && xtk_tree_model_write(&desc, data, size), "model write");

	XtkTreeModelView model;
	EXPECT(xtk_tree_model_open(data, size, &model), "model open");
	EXPECT(model.count == 4u, "flat item count");
	int32_t     parents [] = {-1, 0, 0, -1};
	char const *texts []   = {"Folder", "Alpha", "Beta", "Music"};
	for (uint32_t i = 0; i < model.count; i++) {
		XtkTreeModelItemView item;
		EXPECT(xtk_tree_model_item(&model, i, &item), "item decode");
		EXPECT(item.parent == parents [i] && strcmp(item.text, texts [i]) == 0, "preorder and parent");
	}
	XtkTreeModelItemView folder;
	XtkTreeModelItemView alpha;
	EXPECT(xtk_tree_model_item(&model, 0u, &folder), "folder item");
	EXPECT(xtk_tree_model_item(&model, 1u, &alpha), "alpha item");
	EXPECT((folder.flags & XTK_TREE_MODEL_EXPANDED) != 0u, "expanded flag");
	EXPECT((alpha.flags & XTK_TREE_MODEL_DISABLED) != 0u, "disabled flag");

	uint8_t saved  = data [0];
	data [0]      ^= 0xffu;
	EXPECT(!xtk_tree_model_open(data, size, &model), "reject bad magic");
	data [0]  = saved;
	data [40] = 1u;
	data [41] = data [42] = data [43] = 0u;
	EXPECT(!xtk_tree_model_open(data, size, &model), "reject forward parent");

	free(data);
	printf("PASS: tree model wire contract\n");
	return 0;
}
