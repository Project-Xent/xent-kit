#ifndef XTK_MSG_H
#define XTK_MSG_H

/* Elm message/runtime protocol: controls post XtkMsg values, the runtime
 * hands them to the app's update function, and the view function rebuilds
 * the UI from the evolved model. Application code includes xtk.h, which
 * re-exports this surface. */

#include <stdbool.h>
#include <stdint.h>

typedef struct XtkUi XtkUi;
typedef struct XtkEl XtkEl;

/**
 * @brief A message value posted by a control interaction (Elm-style).
 *
 * Controls never invoke user callbacks; they enqueue the XtkMsg bound to them
 * and the runtime hands it to the app's update function. Tag 0 is reserved
 * for "no message" — start app message enums at 1.
 */
typedef struct XtkMsg {
	int32_t  tag; /**< 0 = none. */
	int32_t  i;
	float    f;
	double   d;
	bool     b;
	void    *ptr;
	uint64_t trace_id;
} XtkMsg;

/** @brief Make a payload-less message. */
static XtkMsg inline xtk_msg(int32_t tag) { return ( XtkMsg ) {.tag = tag}; }

/** @brief Make a message carrying an int payload (e.g. a list index). */
static XtkMsg inline xtk_msg_i(int32_t tag, int32_t i) { return ( XtkMsg ) {.tag = tag, .i = i}; }

/** @brief Consume one message and evolve the model. */
typedef void   (*XtkUpdateFn)(void *model, XtkMsg msg);

/** @brief Build the whole UI for the current model (pure; runs per change). */
typedef XtkEl *(*XtkViewFn)(XtkUi *ui, void *model);

#endif
