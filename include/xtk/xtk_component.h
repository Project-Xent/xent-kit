#ifndef XTK_COMPONENT_H
#define XTK_COMPONENT_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#include "xtk_host.h"
#include "xtk_event.h"

#include <xent/xent.h>


/* Component-author ABI. Ops never receive backend render objects.
 * Failible work runs in prepare_*; commit_* must not fail; abort frees prepare. */

typedef struct XtkUi       XtkUi;
typedef struct XtkEl       XtkEl;
typedef struct XtkCompHost XtkCompHost;
typedef struct XtkCompPrep XtkCompPrep;

typedef enum XtkCompErr
{
	XTK_COMPONENT_OK = 0,
	XTK_COMPONENT_ERR_OOM,
	XTK_COMPONENT_ERR_INVALID_PROPS,
	XTK_COMPONENT_ERR_PROVIDER,
	XTK_COMPONENT_ERR_UNSUPPORTED,
	XTK_COMPONENT_ERR_FAILED,
} XtkCompErr;

typedef struct XtkCompOps {
	XtkCompErr (*prepare_mount)(XtkCompHost *host, XtkCtrl node, void const *props, XtkCompPrep **out);
	XtkCompErr (*prepare_update)(
	  XtkCompHost *host, XtkCtrl node, void *state, void const *previous_props, void const *next_props,
	  XtkCompPrep **out
	);
	void    *(*commit_mount)(XtkCompPrep *prepare);
	void     (*commit_update)(XtkCompPrep *prepare);
	void     (*abort)(XtkCompPrep *prepare);
	uint32_t (*event)(XtkCompHost *host, XtkCtrl target, void *state, XtkEvent const *event);
	void     (*unmount)(XtkCompHost *host, XtkCtrl node, void *state);
} XtkCompOps;

typedef struct XtkCompType {
	uint32_t           abi_version;
	XtkCtrlDesc const *control;                                              /* id >= XTK_CTRL_ID_COMPONENT_BASE */
	size_t             props_size;
	void               (*copy_props)(XtkUi *ui, void *dst, void const *src); /* NULL => memcpy */
	XtkCompOps         ops;
} XtkCompType;

XtkEl           *xtk_component(XtkUi *ui, XtkCompType const *type, void const *props);

typedef uint32_t XtkProviderId;
#define XTK_PROVIDER_ID_INVALID (( XtkProviderId ) 0)

typedef struct XtkProviderDesc {
	XtkProviderId id;
	uint32_t      abi_version;
	size_t        iface_size;
	void const   *iface; /* borrowed for the duration of the Component op */
} XtkProviderDesc;

XtkCtrl     xtk_component_control(XtkCompHost const *host);
XtkCtrl     xtk_component_content_root(XtkCompHost const *host);
XtkCtrl     xtk_component_impl_root(XtkCompHost const *host);
XentCtx    *xtk_component_context(XtkCompHost const *host);
XtkHost    *xtk_component_host(XtkCompHost const *host);
void const *xtk_component_query_provider(XtkCompHost const *host, XtkProviderId id, size_t minimum_size);


#endif
