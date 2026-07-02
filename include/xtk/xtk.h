/**
 * @file xtk.h
 * @brief XTK — xent-kit declarative layer (Elm-style view description).
 *
 * Each frame the app's view function builds a throwaway XtkEl description
 * tree from per-frame arena memory; the reconciler diffs it against the
 * previous frame and applies the changes to retained controls. Interaction
 * never calls back into user code directly: controls post XtkMsg values that
 * the app's update function consumes before the next view pass.
 *
 * Conventions:
 * - Descriptor structs use designated initializers; zero is always a sensible
 *   default (e.g. `.disabled = false`, `.size = 0` meaning 14dp text).
 * - Children are compound-literal arrays terminated by XTK_END. NULL entries
 *   are skipped, so `cond ? xtk_text(...) : NULL` is conditional rendering.
 * - Every string passed in is copied into the frame arena immediately;
 *   callers may pass stack buffers. Element pointers are only valid until
 *   the next frame begins.
 *
 * @code
 * XtkEl *view(XtkUi *ui, Model const *m) {
 *     return xtk_scroll(ui, (XtkEl *[]) {
 *       xtk_column(ui, (XtkStackDesc) {.gap = 12, .padding = {32, 32, 32, 32}}, (XtkEl *[]) {
 *         xtk_text(ui, "Counter", (XtkTextDesc) {.size = 24}),
 *         xtk_text(ui, xtk_fmt(ui, "Count: %d", m->count), (XtkTextDesc) {0}),
 *         xtk_button(ui, "Increment", (XtkButtonDesc) {.on_click = xtk_msg(MSG_INCREMENT)}),
 *         m->count > 0 ? xtk_button(ui, "Reset", (XtkButtonDesc) {.on_click = xtk_msg(MSG_RESET)}) : NULL,
 *         XTK_END }),
 *       XTK_END });
 * }
 * @endcode
 */
#ifndef XTK_H
#define XTK_H

#include "xtk_types.h"
#include <stdbool.h>
#include <stdint.h>
#include <xent/xent.h>

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct XtkUi XtkUi;
typedef struct XtkEl XtkEl;

/**
 * @brief Children-array terminator. NULL cannot terminate because NULL
 * entries inside the array mean "render nothing" (conditional rendering).
 */
extern XtkEl *const  XTK_END;

/**
 * @brief A message value posted by a control interaction (Elm-style).
 *
 * Controls never invoke user callbacks; they enqueue the XtkMsg bound to them
 * and the runtime hands it to the app's update function. Tag 0 is reserved
 * for "no message" — start app message enums at 1.
 */
typedef struct XtkMsg {
	int32_t tag; /**< 0 = none. */

	union
	{
		int32_t i;
		float   f;
		double  d;
		bool    b;
		void   *ptr;
	};
} XtkMsg;

/** @brief Make a payload-less message. */
static XtkMsg inline xtk_msg(int32_t tag) { return ( XtkMsg ) {.tag = tag}; }

/** @brief Make a message carrying an int payload (e.g. a list index). */
static XtkMsg inline xtk_msg_i(int32_t tag, int32_t i) { return ( XtkMsg ) {.tag = tag, .i = i}; }

/* -------------------------------------------------------------------------
 * Descriptors (all fields optional; zero = default)
 * ---------------------------------------------------------------------- */

typedef struct XtkTextDesc {
	float         size;   /**< Font size in DIPs; 0 = 14. */
	XtkFontWeight weight; /**< 0 = regular. */
	XtkTextAlign  align;  /**< 0 = left. */
	XtkColor      color;  /**< 0 alpha = theme default. */
} XtkTextDesc;

typedef struct XtkButtonDesc {
	XtkButtonStyle style; /**< 0 = standard. */
	bool           disabled;
	char const    *icon;  /**< Segoe Fluent Icons name, or NULL. */
	XtkMsg         on_click;
} XtkButtonDesc;

typedef struct XtkToggleDesc {
	bool   checked;
	bool   disabled;
	XtkMsg on_change; /**< Delivered with .b = the new checked state. */
} XtkToggleDesc;

typedef struct XtkSliderDesc {
	float            min;
	float            max;            /**< 0 (with min 0) = 100. */
	float            value;
	float            step;           /**< Snap grid (WinUI StepFrequency); 0 = the WinUI default of 1. */
	float            tick;           /**< Tick mark interval (WinUI TickFrequency); 0 = no ticks. */
	XtkTickPlacement tick_placement; /**< Zero = XTK_TICK_INLINE, the WinUI default. */
	bool             snap_to_ticks;  /**< Snap the value to tick multiples instead of step multiples. */
	float            small_change;   /**< Arrow-key delta; 0 = the WinUI default of 1. */
	float            large_change;   /**< PageUp/Down delta; 0 = the WinUI default of 10. */
	bool             disabled;
	XtkMsg           on_change;      /**< Delivered with .f = the new value. */
} XtkSliderDesc;

typedef struct XtkTextBoxDesc {
	char const *content;   /**< NULL = uncontrolled (keep what the user typed). */
	bool        disabled;
	XtkMsg      on_change; /**< Delivered with .ptr = transient UTF-8 text (copy to keep). */
} XtkTextBoxDesc;

typedef struct XtkProgressDesc {
	float value;
	float max; /**< 0 = 100. */
	bool  indeterminate;
} XtkProgressDesc;

typedef struct XtkBadgeDesc {
	XtkBadgeMode mode; /**< 0 = dot. */
	int32_t      value;
	char const  *icon; /**< Icon name for XTK_BADGE_ICON. */
} XtkBadgeDesc;

typedef struct XtkImageDesc {
	XtkImageStretch stretch; /**< 0 = none; XTK_IMAGE_UNIFORM recommended. */
} XtkImageDesc;

typedef struct XtkHyperlinkDesc {
	char const *url; /**< Opened on click; NULL = message only. */
	bool        disabled;
	XtkMsg      on_click;
} XtkHyperlinkDesc;

typedef struct XtkStackDesc {
	float           gap;
	XentInsets      padding;
	XentFlexAlign   align;   /**< Cross-axis alignment; 0 = start. */
	XentFlexJustify justify; /**< Main-axis distribution; 0 = start. */
	bool            fill;    /**< Fill the main axis instead of hugging content. */
} XtkStackDesc;

typedef struct XtkComboDesc {
	char const *const *items;     /**< UTF-8 item strings (copied into the arena). */
	int                count;
	int                selected;  /**< -1 = show the placeholder. */
	XtkMsg             on_select; /**< Delivered with .i = the selected index. */
} XtkComboDesc;

typedef struct XtkExpanderDesc {
	bool   expanded;
	float  width;          /**< Pinned control width in DIPs; 0 = 600. */
	float  content_height; /**< Content-region height when expanded; 0 = 120. */
	XtkMsg on_toggle;      /**< Delivered with .b = the new expanded state. */
} XtkExpanderDesc;

typedef struct XtkInfoBarDesc {
	XtkInfoBarSeverity severity; /**< 0 = informational. */
	bool               closable;
	char const        *message;  /**< Body text; set by xtk_info_bar. */
	XtkMsg             on_close; /**< Close button; hide by not rendering the bar. */
} XtkInfoBarDesc;

typedef struct XtkNumberDesc {
	double min;
	double max;  /**< 0 (with min 0) = 100. */
	double step; /**< Spin/wheel increment; 0 = 1. */
	double value;
	bool   disabled;
	bool   hide_spin; /**< Hide the +/- spin buttons. */
	XtkMsg on_change; /**< Delivered with .d = the new value. */
} XtkNumberDesc;

typedef struct XtkMenuItemDesc {
	char const *label; /**< NULL = separator. */
	char const *icon;  /**< Segoe Fluent Icons name, or NULL. */
	bool        disabled;
	XtkMsg      on_click;
} XtkMenuItemDesc;

typedef struct XtkDropdownDesc {
	XtkButtonStyle         style; /**< 0 = standard. */
	bool                   disabled;
	char const            *icon;  /**< Segoe Fluent Icons name, or NULL. */
	XtkMenuItemDesc const *items; /**< Menu shown on invoke (copied into the arena). */
	int                    item_count;
} XtkDropdownDesc;

typedef struct XtkSplitDesc {
	bool                   disabled;
	char const            *icon;     /**< Segoe Fluent Icons name, or NULL. */
	XtkMsg                 on_click; /**< Primary (left) zone. */
	XtkMenuItemDesc const *items;    /**< Secondary-zone menu (copied into the arena). */
	int                    item_count;
} XtkSplitDesc;

typedef struct XtkTabDesc {
	char const *icon; /**< Segoe Fluent Icons name, or NULL. */
	char const *label;
} XtkTabDesc;

/**
 * @brief TabView. Tabs are mount-time (key the element by the tab list to
 * change it); the element's children render in the selected tab's content
 * region and follow the selection — render them from the model, exactly like
 * a nav view page. Closing is model-driven: the close button only posts
 * on_close; remove the tab from the model and remount via the key.
 */
typedef struct XtkTabViewDesc {
	XtkTabDesc const *tabs; /**< Copied into the arena. */
	int               tab_count;
	int               selected;
	XtkMsg            on_select; /**< Delivered with .i = the tab index. */
	XtkMsg            on_close;  /**< Close button; .i = the tab index. */
	XtkMsg            on_add;    /**< (+) button; tag 0 hides it. */
} XtkTabViewDesc;

typedef struct XtkMenuDesc {
	char const            *title; /**< Top-level menu caption (File, Edit, ...). */
	XtkMenuItemDesc const *items;
	int                    item_count;
} XtkMenuDesc;

/** @brief Menu bar. The menu set is mount-time; item messages stay live. */
typedef struct XtkMenuBarDesc {
	XtkMenuDesc const *menus; /**< Copied into the arena. */
	int                menu_count;
} XtkMenuBarDesc;

/**
 * @brief ContentDialog (modal). Controlled by .open: shown while true, hidden
 * while false. Any button (or Escape) closes the retained dialog and posts
 * on_result — set the model's open flag false there. The element's children
 * fill the dialog body. App-hosted only (headless runtimes skip it).
 */
typedef struct XtkDialogDesc {
	bool        open;
	char const *primary;        /**< Accent button label; NULL omits it. */
	char const *secondary;      /**< NULL omits it. */
	char const *close;          /**< NULL omits it. */
	float       width;          /**< Card width, clamped to [320, 548]; 0 = 400. */
	float       content_height; /**< Body region height; 0 = 120. */
	XtkMsg      on_result;      /**< Delivered with .i = XtkDialogResult. */
} XtkDialogDesc;

/** @brief WinUI ListViewBase SelectionMode. Zero = Single. */
typedef enum XtkListSelMode
{
	XTK_LIST_SELECT_SINGLE = 0, /**< One selected item; selection follows focus. */
	XTK_LIST_SELECT_NONE,       /**< No selection; clicks still post on_invoke-style selects. */
	XTK_LIST_SELECT_MULTIPLE,   /**< Checkbox-style toggling; focus moves don't select. */
	XTK_LIST_SELECT_EXTENDED,   /**< Ctrl/Shift ranges with an anchor (desktop default). */
} XtkListSelMode;

/** @brief Which items-host flavor a synthesized row belongs to (chrome + interactivity). */
typedef enum XtkListKind
{
	XTK_LIST_KIND_LIST = 0, /**< ListViewItem chrome (pill + subtle fill). */
	XTK_LIST_KIND_LIST_BOX, /**< ListBoxItem chrome (filled selection). */
	XTK_LIST_KIND_GRID,     /**< GridViewItem chrome (border + corner check). */
	XTK_LIST_KIND_REPEATER, /**< No chrome, not interactive (pure layout). */
} XtkListKind;

/**
 * @brief Virtualized items host shared by ListView / ListBox / GridView /
 * ItemsRepeater. The view function never builds all rows: the reconciler
 * realizes only the cells intersecting the scroll viewport (plus overscan)
 * by calling @c item per visible index, and recycles the retained controls
 * as the window shifts (slot-keyed identity), so a million-row list costs
 * a viewport's worth of nodes.
 *
 * Cells are uniform (@c item_height; 0 = 40). Grids wrap indices across
 * @c columns (0 = auto from viewport width / item_width). In Single mode
 * selection is model-driven (@c selected + on_select .i); Multiple and
 * Extended selection sets are control-retained (anchors, Ctrl/Shift) and
 * on_select posts the lead index after each change.
 */
typedef struct XtkListDesc {
	int            count;                                   /**< Total item count. */
	float          item_height;                             /**< Uniform cell height in DIPs; 0 = 40. */
	float          item_width;                              /**< Grid cell width; 0 on lists = full row. */
	int            columns;                                 /**< Grid columns; 0 = auto from width. Lists: 1. */
	int            overscan;                                /**< Extra rows realized beyond the viewport; 0 = 4. */
	XtkEl        *(*item)(XtkUi *ui, void *env, int index); /**< Build cell @p index (called per realized cell). */
	void          *env;                                     /**< Passed through to @c item. */
	XtkListSelMode sel_mode;                                /**< 0 = Single. */
	int            selected;                                /**< Single mode: selected index; -1 = none. */
	XtkMsg         on_select;                               /**< Delivered with .i = the lead selected index. */
} XtkListDesc;

/**
 * @brief Synthesized per-cell wrapper (reconciler-internal; public so the
 * backend can read placement/selection when applying props and wiring
 * clicks). x/y/w/h are content-space placement computed by the reconciler;
 * w == 0 means "full host width" (single-column rows).
 */
typedef struct XtkListItemDesc {
	int         index;    /**< Item index this wrapper currently presents. */
	XtkListKind kind;     /**< Chrome/interactivity flavor. */
	bool        selected; /**< Single mode: item is the selected entry. */
	bool        multi;    /**< Multiple mode: show the checkbox + content shift. */
	float       x, y;     /**< Content-space slot origin. */
	float       w, h;     /**< Cell size; w 0 = full host width. */
} XtkListItemDesc;

/** @brief Grid column count for a given content width (shared with backends). */
int xtk_list_auto_columns(float cross, float item_width, int explicit_columns);

/**
 * @brief FlipView: one viewport-sized page at a time. The element's
 * children are the pages (mount-time set, like TabView); selection is
 * controlled — navigation posts on_select and the model drives selected.
 * Adjacent moves animate; longer jumps snap (WinUI behavior).
 */
typedef struct XtkFlipDesc {
	int    selected;
	bool   vertical;  /**< Vertical paging (default horizontal). */
	XtkMsg on_select; /**< Delivered with .i = the new page index. */
} XtkFlipDesc;

/** @brief PipsPager Previous/Next button visibility. */
typedef enum XtkPipsNavVis
{
	XTK_PIPS_NAV_COLLAPSED = 0,
	XTK_PIPS_NAV_VISIBLE,
	XTK_PIPS_NAV_ON_HOVER,
} XtkPipsNavVis;

/** @brief PipsPager (dot pager; pairs naturally with a FlipView). */
typedef struct XtkPipsDesc {
	int           count;       /**< NumberOfPages. */
	int           selected;    /**< SelectedPageIndex. */
	int           max_visible; /**< Visible pips cap; 0 = 5. */
	bool          vertical;
	XtkPipsNavVis nav;         /**< Previous/Next buttons. */
	XtkMsg        on_select;   /**< Delivered with .i = the new page index. */
} XtkPipsDesc;

typedef enum XtkNavKind
{
	XTK_NAV_ITEM = 0, /**< Selectable menu item. */
	XTK_NAV_HEADER,   /**< Section caption (not selectable). */
	XTK_NAV_SEPARATOR,
	XTK_NAV_FOOTER,   /**< Selectable footer item (e.g. Settings). */
	XTK_NAV_CHILD,    /**< Child of the nearest preceding XTK_NAV_ITEM; the parent
	                      grows a chevron and expands inline (one level deep). */
} XtkNavKind;

typedef struct XtkNavItemDesc {
	XtkNavKind  kind;
	char const *icon;  /**< Segoe Fluent Icons name, or NULL. */
	char const *label; /**< Display text (header caption for XTK_NAV_HEADER). */
} XtkNavItemDesc;

/**
 * @brief NavigationView spine. The item list is applied at mount only (the
 * retained control has no item-removal API); selection and the message stay
 * live. The element's children fill the content host beside the pane.
 */
typedef struct XtkNavDesc {
	XtkNavItemDesc const *items;     /**< Copied into the arena. */
	int                   item_count;
	int                   selected;  /**< Index into items[] (headers/separators count). */
	XtkMsg                on_select; /**< Delivered with .i = the selected item index. */
} XtkNavDesc;

/* -------------------------------------------------------------------------
 * Element tree (public for the reconciler and tests; treat as read-only)
 * ---------------------------------------------------------------------- */

struct XtkEl {
	XtkControlType type;
	char const    *key;    /**< Arena copy; NULL = positional matching. */

	float          width;  /**< NAN = auto. */
	float          height; /**< NAN = auto. */
	float          grow;   /**< Flex grow factor; 0 = none. */
	XentFlexAlign  align_self;
	XentInsets     margin;

	char const    *text;      /**< Primary string: content/label/placeholder/source. */
	char const    *tooltip;   /**< Hover tooltip text, or NULL (xtk_tooltip). */
	bool           stack_row; /**< Container main axis is horizontal. */

	union
	{
		XtkTextDesc      text_props;
		XtkButtonDesc    button;
		XtkToggleDesc    toggle;
		XtkSliderDesc    slider;
		XtkTextBoxDesc   textbox;
		XtkProgressDesc  progress;
		XtkBadgeDesc     badge;
		XtkImageDesc     image;
		XtkHyperlinkDesc hyperlink;
		XtkStackDesc     stack;
		XtkComboDesc     combo;
		XtkExpanderDesc  expander;
		XtkInfoBarDesc   info_bar;
		XtkNumberDesc    number;
		XtkDropdownDesc  dropdown;
		XtkSplitDesc     split;
		XtkTabViewDesc   tab_view;
		XtkMenuBarDesc   menu_bar;
		XtkDialogDesc    dialog;
		XtkNavDesc       nav;
		XtkListDesc      list;
		XtkListItemDesc  item;
		XtkFlipDesc      flip;
		XtkPipsDesc      pips;
	};

	XtkEl **children; /**< Arena array of child_count valid pointers. */
	int     child_count;
};

/* -------------------------------------------------------------------------
 * Frame context
 * ---------------------------------------------------------------------- */

/** @brief Create a build context (owns the frame arena). */
XtkUi         *xtk_ui_create(void);

/** @brief Destroy the build context and its arena. */
void           xtk_ui_destroy(XtkUi *ui);

/** @brief Start a frame: resets the arena; all prior XtkEl pointers die. */
void           xtk_ui_begin(XtkUi *ui);

/** @brief Copy a string into the frame arena (NULL passes through). */
char          *xtk_strdup(XtkUi *ui, char const *s);

/** @brief printf into the frame arena — for transient labels. */
char          *xtk_fmt(XtkUi *ui, char const *fmt, ...);

/* -------------------------------------------------------------------------
 * Builders
 * ---------------------------------------------------------------------- */

XtkEl         *xtk_text(XtkUi *ui, char const *content, XtkTextDesc desc);
XtkEl         *xtk_button(XtkUi *ui, char const *label, XtkButtonDesc desc);
XtkEl         *xtk_checkbox(XtkUi *ui, char const *label, XtkToggleDesc desc);
XtkEl         *xtk_radio(XtkUi *ui, char const *label, XtkToggleDesc desc);
XtkEl         *xtk_switch(XtkUi *ui, XtkToggleDesc desc);
XtkEl         *xtk_slider(XtkUi *ui, XtkSliderDesc desc);
XtkEl         *xtk_textbox(XtkUi *ui, char const *placeholder, XtkTextBoxDesc desc);
XtkEl         *xtk_password(XtkUi *ui, char const *placeholder, XtkTextBoxDesc desc);
XtkEl         *xtk_progress(XtkUi *ui, XtkProgressDesc desc);
XtkEl         *xtk_progress_ring(XtkUi *ui, XtkProgressDesc desc);
XtkEl         *xtk_badge(XtkUi *ui, XtkBadgeDesc desc);
XtkEl         *xtk_image(XtkUi *ui, char const *source, XtkImageDesc desc);
XtkEl         *xtk_hyperlink(XtkUi *ui, char const *label, XtkHyperlinkDesc desc);
XtkEl         *xtk_divider(XtkUi *ui);
XtkEl         *xtk_spacer(XtkUi *ui);
XtkEl         *xtk_repeat_button(XtkUi *ui, char const *label, XtkButtonDesc desc);
XtkEl         *xtk_combo_box(XtkUi *ui, char const *placeholder, XtkComboDesc desc);
XtkEl         *xtk_info_bar(XtkUi *ui, char const *title, char const *message, XtkInfoBarDesc desc);
XtkEl         *xtk_number_box(XtkUi *ui, XtkNumberDesc desc);
XtkEl         *xtk_dropdown_button(XtkUi *ui, char const *label, XtkDropdownDesc desc);
XtkEl         *xtk_split_button(XtkUi *ui, char const *label, XtkSplitDesc desc);
XtkEl         *xtk_menu_bar(XtkUi *ui, XtkMenuBarDesc desc);
XtkEl         *xtk_list_view(XtkUi *ui, XtkListDesc desc);
XtkEl         *xtk_list_box(XtkUi *ui, XtkListDesc desc);
XtkEl         *xtk_grid_view(XtkUi *ui, XtkListDesc desc);
XtkEl         *xtk_items_repeater(XtkUi *ui, XtkListDesc desc);
XtkEl         *xtk_pips_pager(XtkUi *ui, XtkPipsDesc desc);

XtkEl         *xtk_column(XtkUi *ui, XtkStackDesc desc, XtkEl *children []);
XtkEl         *xtk_row(XtkUi *ui, XtkStackDesc desc, XtkEl *children []);
XtkEl         *xtk_card(XtkUi *ui, XtkStackDesc desc, XtkEl *children []);
XtkEl         *xtk_scroll(XtkUi *ui, XtkEl *children []);
XtkEl         *xtk_expander(XtkUi *ui, char const *header, XtkExpanderDesc desc, XtkEl *children []);
XtkEl         *xtk_nav_view(XtkUi *ui, XtkNavDesc desc, XtkEl *children []);
XtkEl         *xtk_tab_view(XtkUi *ui, XtkTabViewDesc desc, XtkEl *children []);
XtkEl         *xtk_flip_view(XtkUi *ui, XtkFlipDesc desc, XtkEl *children []);
XtkEl         *xtk_content_dialog(XtkUi *ui, char const *title, XtkDialogDesc desc, XtkEl *children []);

/**
 * @brief Allocate a children buffer for loop-built lists: capacity + 1 slots,
 * NULL-filled with XTK_END pre-placed in the last slot. Fill any subset of
 * [0..capacity); remaining NULL slots are skipped like conditionals.
 */
XtkEl        **xtk_children_alloc(XtkUi *ui, int capacity);

/* -------------------------------------------------------------------------
 * Modifiers (return the same element)
 * ---------------------------------------------------------------------- */

/** @brief Stable identity for keyed reconciliation (list items). */
XtkEl         *xtk_keyed(XtkUi *ui, char const *key, XtkEl *el);

/** @brief Attach a hover tooltip to any element. */
XtkEl         *xtk_tooltip(XtkUi *ui, XtkEl *el, char const *text);

/** @brief Explicit size; pass NAN to keep an axis automatic. */
XtkEl         *xtk_sized(XtkEl *el, float width, float height);

XtkEl         *xtk_grow(XtkEl *el, float grow);
XtkEl         *xtk_align(XtkEl *el, XentFlexAlign align_self);
XtkEl         *xtk_margin(XtkEl *el, XentInsets margin);

/* -------------------------------------------------------------------------
 * Runtime function types (backends provide the actual app runner)
 * ---------------------------------------------------------------------- */

/** @brief Consume one message and evolve the model. */
typedef void   (*XtkUpdateFn)(void *model, XtkMsg msg);

/** @brief Build the whole UI for the current model (pure; runs per change). */
typedef XtkEl *(*XtkViewFn)(XtkUi *ui, void *model);

#ifdef __cplusplus
}
#endif

#endif
