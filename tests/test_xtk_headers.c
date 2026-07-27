#include <xtk/xtk.h>
#include <xtk/xtk_alloc.h>
#include <xtk/xtk_backend.h>
#include <xtk/xtk_batch.h>
#include <xtk/xtk_catalog.h>
#include <xtk/xtk_cells.h>
#include <xtk/xtk_comp_rt.h>
#include <xtk/xtk_component.h>
#include <xtk/xtk_descriptor.h>
#include <xtk/xtk_event.h>
#include <xtk/xtk_host.h>
#include <xtk/xtk_controls.h>
#include <xtk/xtk_msg.h>
#include <xtk/xtk_nav_model.h>
#include <xtk/xtk_reconcile.h>
#include <xtk/xtk_scene.h>
#include <xtk/xtk_types.h>

int main(void) {
	XtkBackend backend = {0};
	XtkRtCfg   cfg     = {0};
	XtkHost    host    = {0};
	XtkScene   scene   = {.host = &host};
	( void ) backend;
	( void ) cfg;
	( void ) scene;
	( void ) XTK_FRAME_CLEAN;
	( void ) XTK_POST_ACCEPTED;
	return 0;
}
