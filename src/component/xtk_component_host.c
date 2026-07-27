#include "xtk_component_runtime_internal.h"

XtkCtrl     xtk_component_control(XtkCompHost const *h) { return h ? h->control : XTK_CTRL_INVALID; }

XtkCtrl     xtk_component_content_root(XtkCompHost const *h) { return h ? h->content_root : XTK_CTRL_INVALID; }

XtkCtrl     xtk_component_impl_root(XtkCompHost const *h) { return h ? h->impl_root : XTK_CTRL_INVALID; }

XentCtx    *xtk_component_context(XtkCompHost const *h) { return h ? h->ctx : NULL; }

XtkHost    *xtk_component_host(XtkCompHost const *h) { return h ? h->host : NULL; }

void const *xtk_component_query_provider(XtkCompHost const *h, XtkProviderId id, size_t minimum_size) {
	if (!h || id == XTK_PROVIDER_ID_INVALID) return NULL;
	for (uint32_t i = 0; i < h->provider_count; i++) {
		XtkProviderDesc const *p = &h->providers [i];
		if (p->id != id) continue;
		if (p->iface_size < minimum_size || !p->iface) return NULL;
		return p->iface;
	}
	return NULL;
}

XtkCompHost
xtk_comp_make_host(XtkCompRt *rt, XtkHost *host, XentCtx *ctx, XtkCtrl control, XtkCtrl content, XtkCtrl impl) {
	return (XtkCompHost) {
	  .host           = host,
	  .ctx            = ctx,
	  .control        = control,
	  .content_root   = content,
	  .impl_root      = impl,
	  .providers      = rt->providers,
	  .provider_count = rt->provider_count,
	};
}
