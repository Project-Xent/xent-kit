#ifndef XTK_HOT_H
#define XTK_HOT_H

#include <stdalign.h>
#include <stdint.h>

#include "xtk_component.h"
#include "xtk_msg.h"
#include "xtk_scene.h"

#define XTK_HOT_ABI    1u
#define XTK_HOT_SYMBOL "xtk_hot_module"

enum
{
	XTK_HOT_UNLOADABLE = 1u << 0,
};

typedef struct XtkHotModule {
	uint32_t                  abi;
	uint32_t                  flags;
	uint32_t                  model_size;
	uint32_t                  model_align;
	uint32_t                  model_version;
	XtkUpdateFn               update;
	XtkViewFn                 view;
	XtkCompType const *const *comps;
	uint32_t                  comp_count;
	bool                      (*page_build)(XtkScene *scene, XtkTxn *txn, XtkNodeRef slot, void *model, void **page);
	void                      (*page_adopt)(void *page, XtkBatchResult const *result);
	void                      (*page_release)(void *page);
	void                      (*on_load)(void *host);
	void                      (*on_unload)(void);
} XtkHotModule;

typedef XtkHotModule const *(*XtkHotEntryFn)(void);

typedef enum XtkHotCompat
{
	XTK_HOT_COMPATIBLE = 0,
	XTK_HOT_BAD_MODULE,
	XTK_HOT_ABI_CHANGED,
	XTK_HOT_MODEL_CHANGED,
} XtkHotCompat;

static XtkHotCompat inline xtk_hot_compat(XtkHotModule const *current, XtkHotModule const *next) {
	if (!next || (!(next->update && next->view) && !next->page_build)) return XTK_HOT_BAD_MODULE;
	if (next->abi != XTK_HOT_ABI || (current && current->abi != next->abi)) return XTK_HOT_ABI_CHANGED;
	if (!current) return XTK_HOT_COMPATIBLE;
	if (current->model_size != next->model_size
	    || current->model_align != next->model_align
	    || current->model_version != next->model_version)
		return XTK_HOT_MODEL_CHANGED;
	return XTK_HOT_COMPATIBLE;
}

#if defined(_WIN32)
  #define XTK_HOT_EXPORT __declspec(dllexport)
#else
  #define XTK_HOT_EXPORT __attribute__((visibility("default")))
#endif

#define XTK_HOT_EXPORT_MODULE(Model, version, flag_bits, ...) \
	XTK_HOT_EXPORT XtkHotModule const *xtk_hot_module(void) { \
		static XtkHotModule const module = {                  \
		  .abi           = XTK_HOT_ABI,                       \
		  .flags         = (flag_bits),                       \
		  .model_size    = ( uint32_t ) sizeof(Model),        \
		  .model_align   = ( uint32_t ) alignof(Model),       \
		  .model_version = (version),                         \
		  __VA_ARGS__};                                       \
		return &module;                                       \
	}

#define XTK_HOT_MODULE(Model, version, flag_bits, update_fn, view_fn)                          \
	XTK_HOT_EXPORT_MODULE(Model, version, flag_bits, .update = (update_fn), .view = (view_fn))

#define XTK_HOT_MODULE_COMPS(Model, version, flag_bits, update_fn, view_fn, comp_list, comp_n)   \
	XTK_HOT_EXPORT_MODULE(                                                                       \
	  Model, version, flag_bits, .update = (update_fn), .view = (view_fn), .comps = (comp_list), \
	  .comp_count = (comp_n)                                                                     \
	)

#define XTK_HOT_PAGE(Model, version, flag_bits, build_fn, adopt_fn, release_fn)                                   \
	XTK_HOT_EXPORT_MODULE(                                                                                        \
	  Model, version, flag_bits, .page_build = (build_fn), .page_adopt = (adopt_fn), .page_release = (release_fn) \
	)

#endif
