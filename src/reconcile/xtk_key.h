#ifndef XTK_KEY_H
#define XTK_KEY_H

#include "../xtk_hash.h"
#include <xtk/xtk.h>

#include <string.h>

static bool xtk_key_present(XtkKey const *key) { return key && key->kind != XTK_KEY_NONE; }

static bool xtk_key_equal(XtkKey const *a, XtkKey const *b) {
	if (!a || !b || a->kind != b->kind) return false;
	if (a->kind == XTK_KEY_NONE) return true;
	if (a->kind == XTK_KEY_U64) return a->value.u64 == b->value.u64;
	if (!a->value.string || !b->value.string) return a->value.string == b->value.string;
	return strcmp(a->value.string, b->value.string) == 0;
}

static uint32_t xtk_key_hash(XtkKey const *key) {
	if (!key) return 0u;
	if (key->kind == XTK_KEY_U64) return ( uint32_t ) xtk_hash_u64(key->value.u64);
	char const *text = key->kind == XTK_KEY_STRING ? key->value.string : NULL;
	return xtk_hash_string(text, text ? strlen(text) : 0u);
}

#endif
