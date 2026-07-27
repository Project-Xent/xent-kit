#ifndef XTK_RETAINED_H
#define XTK_RETAINED_H

/* Headless retained host: atomic batch commit over xent-core topology.
 * No Flux dependency. Suitable for contract tests and reconciler clients. */

#include <xtk/xtk_descriptor.h>
#include <xtk/xtk_event.h>
#include <xtk/xtk_host.h>
#include <xtk/xtk_component.h>

#include <xent/xent.h>


/** Create a host with an empty scene root (XTK_CTRL_CONTAINER). */
XtkHost *xtk_retained_host_create(void);
void     xtk_retained_host_destroy(XtkHost *host);
XentCtx *xtk_retained_host_context(XtkHost *host);

static XtkScene inline xtk_retained_scene(XtkHost *host) { return ( XtkScene ) {.host = host}; }

bool     xtk_retained_register_component(XtkHost *host, XtkCompType const *type);
bool     xtk_retained_set_providers(XtkHost *host, XtkProviderDesc const *providers, uint32_t count);
XtkCtrl  xtk_retained_component_content_root(XtkHost const *host, XtkCtrl control);
XtkCtrl  xtk_retained_component_impl_root(XtkHost const *host, XtkCtrl control);

/** Pending invalidation mask for one control (catalog-driven). */
uint32_t xtk_retained_invalidation(XtkHost const *host, XtkCtrl control);
/** OR of all pending masks since last take; clears the aggregate. */
uint32_t xtk_retained_take_invalidations(XtkHost *host);

bool     xtk_retained_set_focus(XtkHost *host, XtkCtrl control);
XtkCtrl  xtk_retained_focus(XtkHost const *host);

/**
 * Route an event through capture → target → bubble using catalog routing.
 * `event->target` must be live; `phase` / `current_target` / `scene_revision`
 * are filled by the host. Returns accumulated disposition flags.
 */
uint32_t xtk_retained_route(XtkHost *host, XtkEvent *event);


#endif
