#include "xtk_comp_rtinternal.h"

XtkCtrl     xtk_comp_control(XtkCompHost const *h) { return h ? h->control : XTK_CTRL_INVALID; }

XtkCtrl     xtk_comp_contentroot(XtkCompHost const *h) { return h ? h->content_root : XTK_CTRL_INVALID; }

XtkCtrl     xtk_comp_implroot(XtkCompHost const *h) { return h ? h->impl_root : XTK_CTRL_INVALID; }

XentCtx    *xtk_comp_context(XtkCompHost const *h) { return h ? h->ctx : NULL; }

XtkHost    *xtk_comp_host(XtkCompHost const *h) { return h ? h->host : NULL; }

void const *xtk_comp_queryprovider(XtkCompHost const *h, XtkProviderId id, size_t minimum_size) {
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
