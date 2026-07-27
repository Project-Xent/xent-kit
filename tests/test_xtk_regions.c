#include <xtk/xtk_reconcile.h>
#include "xtk_retained.h"

#include "runtime/xtk_runtime_internal.h"
#include "reconcile/xtk_reconcile_internal.h"

#include <stdio.h>

#define EXPECT(cond, msg)              \
	do {                               \
		if (!(cond)) {                 \
			printf("FAIL: %s\n", msg); \
			return 1;                  \
		}                              \
	}                                  \
	while (0)

typedef struct RegionModel RegionModel;

typedef struct RegionBuild {
	RegionModel *model;
	uint64_t     id;
	char const  *key;
	int         *count;
} RegionBuild;

struct RegionModel {
	uint64_t    revision [2];
	int         builds [2];
	bool        mounted [2];
	bool        reverse;
	bool        fail_build;
	RegionBuild region [2];
};

static void update(void *model, XtkMsg msg) {
	( void ) model;
	( void ) msg;
}

static XtkEl *build_region(XtkUi *ui, void *ctx) {
	RegionBuild *build = ctx;
	(*build->count)++;
	if (build->model->fail_build) return NULL;
	char *text = xtk_fmt(
	  ui, "%llu:%llu", ( unsigned long long ) build->id, ( unsigned long long ) build->model->revision [build->id - 1u]
	);
	return xtk_keyed(ui, build->key, xtk_text(ui, text, (XtkTextDesc) {0}));
}

static XtkEl *region(RegionModel *model, XtkUi *ui, int index) {
	if (!model->mounted [index]) return NULL;
	RegionBuild *build = &model->region [index];
	if (index == 1) return xtk_static_region(ui, build->id, build_region, build);
	return xtk_memo_region(ui, build->id, model->revision [index], build_region, build);
}

static XtkEl *view(XtkUi *ui, void *ctx) {
	RegionModel *model = ctx;
	XtkEl       *a     = region(model, ui, 0);
	XtkEl       *b     = region(model, ui, 1);
	return model->reverse ? xtk_column(ui, (XtkStackDesc) {0}, xtk_kids(b, a))
	                      : xtk_column(ui, (XtkStackDesc) {0}, xtk_kids(a, b));
}

static void request_frame(void *ctx) { ( void ) ctx; }

int         main(void) {
	XtkHost *host = xtk_retained_host_create();
	EXPECT(host, "retained Host");
	RegionModel model = {
	  .revision = {1u,   1u  },
	  .mounted  = {true, true},
	};
	model.region [0] = (RegionBuild) {.model = &model, .id = 1u, .key = "a", .count = &model.builds [0]};
	model.region [1] = (RegionBuild) {.model = &model, .id = 2u, .key = "b", .count = &model.builds [1]};
	XtkRtCfg cfg     = {.request_frame = request_frame};
	XtkRt   *rt      = xtk_rt_create(host, &cfg, ( XentNodeId ) host->vt->root(host), &model, update, view);
	EXPECT(rt, "runtime");

	EXPECT(xtk_rt_frame(rt).status == XTK_FRAME_COMMITTED, "initial regions commit");
	EXPECT(model.builds [0] == 1 && model.builds [1] == 1, "initial builders run once");
	XentNodeId a = rt->root->children [0]->node;
	XentNodeId b = rt->root->children [1]->node;

	for (int i = 0; i < 4; i++) {
		xtk_rt_invalidate(rt);
		EXPECT(xtk_rt_frame(rt).status == XTK_FRAME_COMMITTED, "unchanged memo frame");
	}
	EXPECT(model.builds [0] == 1 && model.builds [1] == 1, "unchanged builders skipped");
	EXPECT(rt->root->children [0]->node == a && rt->root->children [1]->node == b, "retained identity preserved");

	model.reverse = true;
	xtk_rt_invalidate(rt);
	EXPECT(xtk_rt_frame(rt).status == XTK_FRAME_COMMITTED, "keyed memo reorder commits");
	EXPECT(model.builds [0] == 1 && model.builds [1] == 1, "reorder does not rebuild regions");
	EXPECT(rt->root->children [0]->node == b && rt->root->children [1]->node == a, "keyed regions move");

	model.revision [0]++;
	xtk_rt_invalidate(rt);
	EXPECT(xtk_rt_frame(rt).status == XTK_FRAME_COMMITTED, "changed revision commits");
	EXPECT(model.builds [0] == 2 && model.builds [1] == 1, "only changed region rebuilds");
	EXPECT(rt->root->children [1]->node == a, "changed region retains control identity");

	model.revision [0]++;
	model.fail_build = true;
	xtk_rt_invalidate(rt);
	EXPECT(xtk_rt_frame(rt).status == XTK_FRAME_BUILD_FAILED, "failed region build rejects frame");
	model.fail_build = false;
	EXPECT(xtk_rt_frame(rt).status == XTK_FRAME_COMMITTED, "failed region retries same revision");
	EXPECT(model.builds [0] == 4, "failed revision was not published");

	model.mounted [1] = false;
	xtk_rt_invalidate(rt);
	EXPECT(xtk_rt_frame(rt).status == XTK_FRAME_COMMITTED, "conditional unmount commits");
	model.mounted [1] = true;
	xtk_rt_invalidate(rt);
	EXPECT(xtk_rt_frame(rt).status == XTK_FRAME_COMMITTED, "conditional remount commits");
	EXPECT(model.builds [1] == 2, "unmounted region is not retained in memo index");

	model.region [1].id = 1u;
	xtk_rt_invalidate(rt);
	XtkFrameResult duplicate = xtk_rt_frame(rt);
	EXPECT(duplicate.status == XTK_FRAME_IDENTITY_FAILED, "duplicate region rejected");
	EXPECT(duplicate.identity.error == XTK_IDENTITY_DUPLICATE_REGION, "duplicate region diagnostic");
	model.region [1].id = 2u;
	EXPECT(xtk_rt_frame(rt).status == XTK_FRAME_COMMITTED, "duplicate region retry commits");

	EXPECT(xtk_rt_destroy(rt), "runtime destroy");
	xtk_retained_host_destroy(host);
	printf("PASS: static and revisioned regions\n");
	return 0;
}
