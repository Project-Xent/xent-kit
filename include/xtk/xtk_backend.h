#ifndef XTK_BACKEND_H
#define XTK_BACKEND_H

#include <stdint.h>
#include <stdbool.h>

#include "xtk_descriptor.h"
#include "xtk_host.h"

#include <xent/xent_display.h>

typedef struct XtkBackend XtkBackend;

typedef struct XtkBackendVtable {
	uint32_t    abi_version;
	bool        (*replay_display_list)(XtkBackend *backend, XentDl const *list);
	void const *(*query_capability)(XtkBackend *backend, XtkCapabilityId id);
	XtkHost    *(*host)(XtkBackend *backend);
} XtkBackendVtable;

struct XtkBackend {
	XtkBackendVtable const *vt;
	void                   *impl;
};

#endif
