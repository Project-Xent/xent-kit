/**
 * @file xtk_reconcile.c
 * @brief XTK reconciler: single-pass keyed diff of the new element tree
 * against the previous frame, applied to retained controls through the
 * XtkBackend vtable.
 */
#include <xtk/xtk_reconcile.h>

#include <stdlib.h>
#include <string.h>

static XtkNode *xtk_node_create(XentNodeId id, void *binding) {
	XtkNode *n = ( XtkNode * ) calloc(1, sizeof(*n));
	if (!n) return NULL;
	n->node    = id;
	n->host    = id;
	n->binding = binding;
	return n;
}

static void xtk_node_free_tree(XtkRuntime *rt, XtkNode *n) {
	if (!n) return;
	for (int i = 0; i < n->child_count; i++) xtk_node_free_tree(rt, n->children [i]);
	rt->backend.node_cleanup(n);
	free(n->children);
	free(n);
}

static bool xtk_node_reserve(XtkNode *n, int count) {
	if (count <= n->child_cap) return true;
	int cap = n->child_cap ? n->child_cap * 2 : 8;
	if (cap < count) cap = count;
	XtkNode **items = ( XtkNode ** ) realloc(n->children, sizeof(XtkNode *) * ( size_t ) cap);
	if (!items) return false;
	n->children  = items;
	n->child_cap = cap;
	return true;
}

static XtkNode *xtk_mount(XtkRuntime *rt, XentNodeId parent, XtkEl const *el) {
	XtkBackend *be = &rt->backend;
	void       *b  = NULL;
	if (be->is_interactive(el)) {
		b = be->binding_create(be->ctx, rt);
		if (!b) return NULL;
	}

	XentNodeId id = be->create(be->ctx, parent, el, b);
	if (id == XENT_NODE_INVALID) {
		free(b);
		return NULL;
	}

	XtkNode *n = xtk_node_create(id, b);
	if (!n) {
		be->destroy(be->ctx, id);
		free(b);
		return NULL;
	}

	be->mount_setup(be->ctx, n, id, el);

	if (el->child_count > 0 && xtk_node_reserve(n, el->child_count)) {
		for (int i = 0; i < el->child_count; i++) n->children [i] = xtk_mount(rt, n->host, el->children [i]);
		n->child_count = el->child_count;
	}
	return n;
}

static void xtk_unmount(XtkRuntime *rt, XtkNode *n) {
	if (!n) return;
	rt->backend.pre_unmount(rt->backend.ctx, n->node);
	rt->backend.destroy(rt->backend.ctx, n->node);
	xtk_node_free_tree(rt, n);
}

static bool xtk_same_identity(XtkEl const *a, XtkEl const *b) {
	if (a->type != b->type) return false;
	if (!!a->key != !!b->key) return false;
	return !a->key || strcmp(a->key, b->key) == 0;
}

static void xtk_diff(XtkRuntime *rt, XtkNode *n, XtkEl const *prev, XtkEl const *el);

static int  xtk_match_keyed(XtkEl const *prev, bool const *claimed, XtkEl const *want) {
	for (int i = 0; i < prev->child_count; i++)
		if (!claimed [i] && xtk_same_identity(prev->children [i], want)) return i;
	return -1;
}

static int xtk_match_child(XtkEl const *prev, bool const *claimed, XtkEl const *want, int *unkeyed_cursor) {
	if (want->key) return xtk_match_keyed(prev, claimed, want);
	int seen = 0;
	for (int i = 0; i < prev->child_count; i++) {
		if (prev->children [i]->key) continue;
		if (seen++ < *unkeyed_cursor) continue;
		(*unkeyed_cursor)++;
		return !claimed [i] && xtk_same_identity(prev->children [i], want) ? i : -1;
	}
	(*unkeyed_cursor)++;
	return -1;
}

static void xtk_diff_match(
  XtkRuntime *rt, XtkNode *n, XtkEl const *prev, XtkEl const *el, XtkNode **out, bool *claimed, int *last_old,
  bool *reorder
) {
	int unkeyed_cursor = 0;
	for (int i = 0; i < el->child_count; i++) {
		XtkEl const *want = el->children [i];
		int          from = xtk_match_child(prev, claimed, want, &unkeyed_cursor);
		if (from >= 0 && from < n->child_count) {
			claimed [from] = true;
			out [i]        = n->children [from];
			xtk_diff(rt, out [i], prev->children [from], want);
			*reorder  = *reorder || from < *last_old;
			*last_old = from;
		}
		else {
			out [i]  = xtk_mount(rt, n->host, want);
			*reorder = true;
		}
	}
}

static void xtk_diff_reorder(XtkRuntime *rt, XtkNode *n, XtkEl const *el) {
	for (int i = 0; i < n->child_count; i++)
		if (n->children [i] && el->children [i]->type != XTK_CONTROL_CONTENT_DIALOG)
			xent_append_child(rt->ctx, n->host, n->children [i]->node);
}

static void xtk_diff_children(XtkRuntime *rt, XtkNode *n, XtkEl const *prev, XtkEl const *el) {
	int   old_count = prev->child_count;
	bool *claimed   = old_count ? ( bool * ) calloc(( size_t ) old_count, sizeof(bool)) : NULL;
	if (old_count && !claimed) return;

	XtkNode **next_nodes
	  = el->child_count ? ( XtkNode ** ) calloc(( size_t ) el->child_count, sizeof(XtkNode *)) : NULL;
	if (el->child_count && !next_nodes) {
		free(claimed);
		return;
	}

	int  last_old = -1;
	bool reorder  = false;
	xtk_diff_match(rt, n, prev, el, next_nodes, claimed, &last_old, &reorder);

	for (int i = 0; i < old_count; i++)
		if (!claimed [i] && i < n->child_count) xtk_unmount(rt, n->children [i]);
	free(claimed);

	free(n->children);
	n->children    = next_nodes;
	n->child_count = el->child_count;
	n->child_cap   = el->child_count;

	if (reorder) xtk_diff_reorder(rt, n, el);
}

static void xtk_diff(XtkRuntime *rt, XtkNode *n, XtkEl const *prev, XtkEl const *el) {
	if (!n) return;
	rt->backend.apply_props(rt->backend.ctx, n, prev, el);
	xtk_diff_children(rt, n, prev, el);
}

static void xtk_mount_root(XtkRuntime *rt, XtkEl *next) {
	rt->root = xtk_mount(rt, rt->host, next);
	if (!rt->root) return;
	xent_set_absolute_position(rt->ctx, rt->root->node, (XentPoint) {0.0f, 0.0f});
	if (next->type != XTK_CONTROL_NAV_VIEW) xent_set_size_percent(rt->ctx, rt->root->node, (XentSize) {1.0f, 1.0f});
}

void xtk_reconcile(XtkRuntime *rt, XtkEl *next) {
	if (!next) return;
	if (!rt->root || !rt->prev_root || !xtk_same_identity(rt->prev_root, next)) {
		if (rt->root) xtk_unmount(rt, rt->root);
		xtk_mount_root(rt, next);
		rt->prev_root = next;
		return;
	}
	xtk_diff(rt, rt->root, rt->prev_root, next);
	rt->prev_root = next;
}

void xtk_unmount_all(XtkRuntime *rt) {
	if (!rt || !rt->root) return;
	xtk_unmount(rt, rt->root);
	rt->root      = NULL;
	rt->prev_root = NULL;
}
