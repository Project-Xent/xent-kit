#include <xtk/xtk_catalog.h>
#include <xtk/xtk_cells.h>
#include <xtk/xtk_controls.h>

#include "xtk_alloc_internal.h"
#include "xtk_retained.h"

#include <stdio.h>
#include <string.h>

#if defined(_WIN32)
  #include <windows.h>
#endif

#define EXPECT(cond, msg)              \
	do {                               \
		if (!(cond)) {                 \
			printf("FAIL: %s\n", msg); \
			return 1;                  \
		}                              \
	}                                  \
	while (0)

typedef struct CellFixture {
	XtkHost *host;
	XtkScene scene;
	XtkCtrl  text;
	XtkCtrl  slider;
} CellFixture;

static bool fixture_create(CellFixture *fixture) {
	fixture->host = xtk_retained_host_create();
	if (!fixture->host) return false;
	fixture->scene = xtk_scene_from_host(fixture->host);
	XtkTxn txn;
	if (!xtk_txn_begin(&fixture->scene, &txn)) return false;
	XtkLocalId text = xtk_text_create(
	  &txn, xtk_ref_none(), &(XtkTextProps) {.set = XTK_TEXT_TEXT_MASK, .text = "old", .text_len = 3u}
	);
	XtkLocalId slider
	  = xtk_slider_create(&txn, xtk_ref_none(), &(XtkSliderProps) {.set = XTK_SLIDER_VALUE_MASK, .value = 1.0f});
	XtkBatchResult *created = xtk_txn_commit(&txn, NULL);
	if (!created || created->control_count != 2u || text == XTK_LOCAL_INVALID || slider == XTK_LOCAL_INVALID) {
		xtk_batch_result_destroy(created);
		return false;
	}
	fixture->text   = created->controls [text].control;
	fixture->slider = created->controls [slider].control;
	xtk_batch_result_destroy(created);
	return true;
}

static void fixture_destroy(CellFixture *fixture) {
	xtk_retained_host_destroy(fixture->host);
	*fixture = (CellFixture) {0};
}

static int test_batch_and_echo_contract(void) {
	CellFixture fixture = {0};
	EXPECT(fixture_create(&fixture), "fixture");
	uint64_t  revision = xtk_scene_revision(&fixture.scene);
	XtkCells *cells    = xtk_cells_create(fixture.scene, 77u);
	EXPECT(cells, "cells");
	XtkCellId text_cell   = xtk_cells_bind(cells, fixture.text, XTK_PROP_TEXT);
	XtkCellId slider_cell = xtk_cells_bind(cells, fixture.slider, XTK_PROP_VALUE_F32);
	EXPECT(text_cell != XTK_CELL_INVALID && slider_cell != XTK_CELL_INVALID, "bind supported properties");
	EXPECT(xtk_cells_bind(cells, fixture.text, XTK_PROP_WIDTH) == XTK_CELL_INVALID, "reject structural property");
	EXPECT(xtk_cells_bind(cells, fixture.text, XTK_PROP_TEXT) == XTK_CELL_INVALID, "reject duplicate binding");
	EXPECT(xtk_cell_set_string(cells, text_cell, "new", 3u), "set text");
	EXPECT(xtk_cell_set_f32(cells, slider_cell, 9.0f), "set slider");
	EXPECT(xtk_cells_flush(cells), "flush cells");
	EXPECT(xtk_scene_revision(&fixture.scene) == revision + 1u, "one batch revision");

	XtkValueView   value;
	XtkChangeStamp change;
	EXPECT(xtk_control_get(&fixture.scene, fixture.text, XTK_PROP_TEXT, &value, &change), "read text");
	EXPECT(value.kind == XTK_VALUE_STRING && value.u.string.len == 3u, "text value");
	EXPECT(memcmp(value.u.string.data, "new", 3u) == 0, "text bytes");
	EXPECT(change.source == 77u && change.revision == 1u, "text change token");
	EXPECT(xtk_control_get(&fixture.scene, fixture.slider, XTK_PROP_VALUE_F32, &value, &change), "read slider");
	EXPECT(value.kind == XTK_VALUE_F32 && value.u.f32 == 9.0f, "slider value");
	EXPECT(change.source == 77u && change.revision == 1u, "slider change token");

	XtkValueView event_value = {.kind = XTK_VALUE_F32, .u.f32 = 9.0f};
	EXPECT(
	  xtk_cell_accept(cells, slider_cell, &event_value, (XtkChangeStamp) {.source = 77u, .revision = 1u})
		== XTK_CELL_ECHO,
	  "ignore native echo"
	);
	event_value.u.f32 = 4.0f;
	EXPECT(
	  xtk_cell_accept(cells, slider_cell, &event_value, (XtkChangeStamp) {.source = 88u, .revision = 2u})
		== XTK_CELL_ACCEPTED,
	  "accept external change"
	);
	EXPECT(xtk_cell_get(cells, slider_cell, &value) && value.u.f32 == 4.0f, "read accepted change");
	revision = xtk_scene_revision(&fixture.scene);
	EXPECT(xtk_cells_flush(cells) && xtk_scene_revision(&fixture.scene) == revision, "accepted change is clean");
	EXPECT(xtk_cells_destroy(cells), "destroy cells");
	fixture_destroy(&fixture);
	return 0;
}

static int test_failed_flush_retries(void) {
	CellFixture fixture = {0};
	EXPECT(fixture_create(&fixture), "retry fixture");
	XtkCells *cells = xtk_cells_create(fixture.scene, 91u);
	EXPECT(cells, "retry cells");
	XtkCellId text_cell = xtk_cells_bind(cells, fixture.text, XTK_PROP_TEXT);
	EXPECT(text_cell != XTK_CELL_INVALID, "retry binding");
	EXPECT(xtk_cell_set_string(cells, text_cell, "retry", 5u), "set retry text");
	xtk_alloc_test_reset();
	xtk_alloc_fail_at(1u);
	EXPECT(!xtk_cells_flush(cells), "failed flush");
	xtk_alloc_test_reset();
	EXPECT(xtk_cells_flush(cells), "retry dirty flush");
	XtkValueView   value;
	XtkChangeStamp change;
	EXPECT(xtk_control_get(&fixture.scene, fixture.text, XTK_PROP_TEXT, &value, &change), "read retry text");
	EXPECT(value.u.string.len == 5u && memcmp(value.u.string.data, "retry", 5u) == 0, "retry value");
	EXPECT(xtk_cells_destroy(cells), "destroy retry cells");
	fixture_destroy(&fixture);
	return 0;
}

#if defined(_WIN32)
typedef struct WrongThreadProbe {
	XtkCells *cells;
	XtkCellId cell;
	bool      rejected;
} WrongThreadProbe;

static DWORD WINAPI wrong_thread(void *arg) {
	WrongThreadProbe *probe = arg;
	XtkValueView      value;
	probe->rejected = !xtk_cell_set_f32(probe->cells, probe->cell, 2.0f)
	               && !xtk_cell_get(probe->cells, probe->cell, &value)
	               && !xtk_cells_flush(probe->cells)
	               && !xtk_cells_destroy(probe->cells);
	return 0u;
}

static int test_wrong_thread_is_rejected(void) {
	CellFixture fixture = {0};
	EXPECT(fixture_create(&fixture), "thread fixture");
	XtkCells *cells = xtk_cells_create(fixture.scene, 92u);
	EXPECT(cells, "thread cells");
	XtkCellId slider = xtk_cells_bind(cells, fixture.slider, XTK_PROP_VALUE_F32);
	EXPECT(slider != XTK_CELL_INVALID, "thread binding");
	WrongThreadProbe probe  = {.cells = cells, .cell = slider};
	HANDLE           thread = CreateThread(NULL, 0u, wrong_thread, &probe, 0u, NULL);
	EXPECT(thread, "create wrong thread");
	EXPECT(WaitForSingleObject(thread, INFINITE) == WAIT_OBJECT_0, "join wrong thread");
	CloseHandle(thread);
	EXPECT(probe.rejected, "wrong-thread cell operations rejected");
	EXPECT(xtk_cells_destroy(cells), "owner thread destroys cells");
	fixture_destroy(&fixture);
	return 0;
}
#endif

int main(void) {
	if (test_batch_and_echo_contract()) return 1;
	if (test_failed_flush_retries()) return 1;
#if defined(_WIN32)
	if (test_wrong_thread_is_rejected()) return 1;
#endif
	printf("PASS: restricted property cells\n");
	return 0;
}
