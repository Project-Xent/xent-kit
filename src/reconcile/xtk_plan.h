#ifndef XTK_PLAN_H
#define XTK_PLAN_H

#include "xtk_identity.h"
#include "xtk_scratch.h"
#include <xtk/xtk.h>

typedef struct XtkNode XtkNode;

/** out_old[i] = old index for next child i, or -1 for CREATE. Returns false on OOM. */
bool                   xtk_plan_match_positional(XtkNode const *old_node, XtkEl const *next_el, int *out_old);

typedef struct XtkKeyedMatch {
	int  *old;
	bool *move;
	int  *retire;
	int   retire_count;
	int   moves_needed;
} XtkKeyedMatch;

bool xtk_plan_match_keyed(XtkNode const *old_node, XtkEl const *next_el, XtkScratch *scratch, XtkKeyedMatch *match);

/** Same-type check used by matchers. */
bool xtk_plan_same_type(XtkNode const *old_node, XtkEl const *next_el);

#endif
