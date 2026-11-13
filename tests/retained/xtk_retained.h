#ifndef XTK_RETAINED_H
#define XTK_RETAINED_H

#include <xtk/xtk_descriptor.h>
#include <xtk/xtk_event.h>
#include <xtk/xtk_host.h>
#include <xtk/xtk_component.h>

#include <xent/xent.h>

XtkHost *xtk_retained_host_create(void);
void     xtk_retained_host_destroy(XtkHost *host);
XentCtx *xtk_retained_host_context(XtkHost *host);

static XtkScene inline xtk_retained_scene(XtkHost *host) { return ( XtkScene ) {.host = host}; }

bool     xtk_retained_register_component(XtkHost *host, XtkCompType const *type);
bool     xtk_retained_set_providers(XtkHost *host, XtkProviderDesc const *providers, uint32_t count);
XtkCtrl  xtk_retained_component_content_root(XtkHost const *host, XtkCtrl control);
XtkCtrl  xtk_retained_component_impl_root(XtkHost const *host, XtkCtrl control);

uint32_t xtk_retained_invalidation(XtkHost const *host, XtkCtrl control);
uint32_t xtk_retained_take_invalidations(XtkHost *host);

bool     xtk_retained_set_focus(XtkHost *host, XtkCtrl control);
XtkCtrl  xtk_retained_focus(XtkHost const *host);

uint32_t xtk_retained_route(XtkHost *host, XtkEvent *event);

#endif
