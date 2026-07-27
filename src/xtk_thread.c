#include "xtk_thread_internal.h"

void const *xtk_thread_token(void) {
	static _Thread_local unsigned char token;
	return &token;
}
