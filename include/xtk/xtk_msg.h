#ifndef XTK_MSG_H
#define XTK_MSG_H

#include <stdbool.h>
#include <stdint.h>

typedef struct XtkUi XtkUi;
typedef struct XtkEl XtkEl;

typedef struct XtkMsg {
	int32_t tag;
	int32_t i;
	float   f;
	double  d;
	bool    b;
	void   *ptr;
} XtkMsg;

static XtkMsg inline xtk_msg(int32_t tag) { return ( XtkMsg ) {.tag = tag}; }

static XtkMsg inline xtk_msg_i(int32_t tag, int32_t i) { return ( XtkMsg ) {.tag = tag, .i = i}; }

typedef void   (*XtkUpdateFn)(void *model, XtkMsg msg);

typedef XtkEl *(*XtkViewFn)(XtkUi *ui, void *model);

#endif
