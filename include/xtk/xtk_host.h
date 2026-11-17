#ifndef XTK_HOST_H
#define XTK_HOST_H

#include "xtk_batch.h"
#include "xtk_descriptor.h"

typedef struct XtkHost    XtkHost;
typedef struct XtkScene   XtkScene;
typedef struct XtkPrepare XtkPrepare;

#define XTK_HOST_ABI_VERSION 1u

/** `string` and `bytes` point at the host's stored copy, until that property changes or the host is destroyed. */
typedef struct XtkValueView {
	XtkValueKind kind;

	union
	{
		bool     b;
		int32_t  i32;
		float    f32;
		double   f64;
		uint32_t u32;
		XtkColor color;

		struct {
			char const *data;
			uint32_t    len;
		} string;

		XtkResource resource;

		struct {
			uint8_t const *data;
			uint32_t       len;
		} bytes;
	} u;
} XtkValueView;

typedef struct XtkHostVtable {
	uint32_t           abi;
	XtkBatchError      (*preflight)(XtkHost *host, XtkBatch *batch, XtkBatchDiag *diagnostic);
	XtkBatchError      (*prepare)(XtkHost *host, XtkBatch *batch, XtkPrepare **out_prepare, XtkBatchDiag *diagnostic);
	XtkBatchResult    *(*commit)(XtkHost *host, XtkPrepare *prepare, XtkBatchDiag *diagnostic);
	void               (*abort)(XtkHost *host, XtkPrepare *prepare);

	bool               (*live)(XtkHost const *host, XtkCtrl control);
	uint64_t           (*revision)(XtkHost const *host);
	XtkCtrl            (*root)(XtkHost const *host);
	XtkCtrlId          (*type)(XtkHost const *host, XtkCtrl control);
	XtkCtrl            (*parent)(XtkHost const *host, XtkCtrl control);
	XtkCtrl            (*first)(XtkHost const *host, XtkCtrl control);
	XtkCtrl            (*next)(XtkHost const *host, XtkCtrl control);
	XtkCtrlDesc const *(*desc)(XtkHost const *host, XtkCtrlId type);
	bool               (*prop)(
	  XtkHost const *host, XtkCtrl control, XtkPropertyId property, XtkValueView *out_value, XtkChangeStamp *out_change
	);
	bool     (*res_valid)(XtkHost const *host, XtkResource resource, XtkResourceTypeId type);
	/** Batch commit copies the id and does not call this. */
	bool     (*res_retain)(XtkHost *host, XtkResource resource, XtkResourceTypeId type);
	/** Batch commit copies the id and does not call this. */
	void     (*res_release)(XtkHost *host, XtkResource resource, XtkResourceTypeId type);
	uint32_t (*dispatch)(XtkHost *host, XtkEvent const *event);
} XtkHostVtable;

struct XtkHost {
	XtkHostVtable const *vt;
	void                *impl;
};

struct XtkScene {
	XtkHost *host;
};

#endif
