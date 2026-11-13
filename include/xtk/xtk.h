#ifndef XTK_H
#define XTK_H

#include "xtk_descriptor.h"
#include "xtk_msg.h"
#include <stdbool.h>
#include <stdint.h>
#include <xent/xent.h>

typedef XtkEl *(*XtkRegionBuildFn)(XtkUi *ui, void *ctx);

typedef enum XtkKeyKind
{
	XTK_KEY_NONE = 0,
	XTK_KEY_STRING,
	XTK_KEY_U64,
} XtkKeyKind;

typedef struct XtkKey {
	XtkKeyKind kind;

	union
	{
		char const *string;
		uint64_t    u64;
	} value;
} XtkKey;

extern XtkEl *const XTK_END;

#define xtk_kids(...) (( XtkEl *[] ) {__VA_ARGS__ __VA_OPT__(, ) XTK_END})

typedef struct XtkTextDesc {
	float         size;
	XtkFontWeight weight;
	XtkTextAlign  align;
	XtkColor      color;
	uint32_t      max_lines;
	XtkTextTrim   trim;
	bool          nowrap;
	bool          selectable;
} XtkTextDesc;

typedef struct XtkButtonDesc {
	XtkButtonStyle style;
	bool           disabled;
	char const    *icon;
	XtkMsg         click;
} XtkButtonDesc;

typedef struct XtkToggleDesc {
	bool   checked;
	bool   disabled;
	bool   indeterminate;
	bool   three_state;
	XtkMsg change;
	XtkMsg change_state;
} XtkToggleDesc;

typedef struct XtkSliderDesc {
	float            min;
	float            max;
	float            value;
	float            step;
	float            tick;
	XtkTickPlacement tick_placement;
	bool             snap_to_ticks;
	float            small_change;
	float            large_change;
	bool             disabled;
	bool             vertical;
	bool             range;
	float            range_start;
	float            range_end;
	XtkMsg           change;
	XtkMsg           change_range;
} XtkSliderDesc;

typedef struct XtkScrollBarDesc {
	bool   horizontal;
	double min;
	double max;
	double value;
	double viewport;
	double small_change;
	double large_change;
	bool   disabled;
	XtkMsg change;
} XtkScrollBarDesc;

typedef struct XtkTextBoxDesc {
	char const *content;
	bool        disabled;
	bool        multiline;
	bool        readonly;
	XtkMsg      change;
} XtkTextBoxDesc;

typedef struct XtkProgressDesc {
	float            value;
	float            min;
	float            max;
	bool             indeterminate;
	XtkProgressState state;
	bool             inactive;
	XentInsets       padding;
	float            border_width;
} XtkProgressDesc;

typedef struct XtkBadgeDesc {
	XtkBadgeMode mode;
	int32_t      value;
	char const  *icon;
} XtkBadgeDesc;

typedef struct XtkImageDesc {
	XtkResource     source;
	XtkImageStretch stretch;
} XtkImageDesc;

typedef struct XtkHyperlinkDesc {
	char const *url;
	bool        disabled;
	XtkMsg      click;
} XtkHyperlinkDesc;

typedef struct XtkStackDesc {
	float           gap;
	XentInsets      padding;
	XentFlexAlign   align;
	XentFlexJustify justify;
	bool            fill;
	XentFlexWrap    wrap;
} XtkStackDesc;

typedef struct XtkLoopingDesc {
	char const *const *items;
	int                nitem;
	int                sel;
	float              itemh;
	float              itemw;
	bool               loop;
	bool               disabled;
	XtkMsg             select;
} XtkLoopingDesc;

typedef enum XtkClock
{
	XTK_CLOCK_SYSTEM = 0,
	XTK_CLOCK_12H,
	XTK_CLOCK_24H,
} XtkClock;

static int32_t inline xtk_date(int year, int month, int day) { return year * 10000 + month * 100 + day; }

typedef struct XtkDatePickerDesc {
	char const *header;
	int32_t     date;
	int         minyear;
	int         maxyear;
	bool        disabled;
	XtkMsg      change;
} XtkDatePickerDesc;

typedef struct XtkTimePickerDesc {
	char const *header;
	bool        has_time;
	int32_t     minutes;
	XtkClock    clock;
	int         step;
	bool        disabled;
	XtkMsg      change;
} XtkTimePickerDesc;

typedef enum XtkCalendarMode
{
	XTK_CALENDAR_SINGLE = 0,
	XTK_CALENDAR_NONE,
	XTK_CALENDAR_MULTIPLE,
} XtkCalendarMode;

typedef struct XtkCalendarDesc {
	int32_t         date;
	XtkCalendarMode mode;
	int32_t         mindate;
	int32_t         maxdate;
	int             firstday;
	bool            disabled;
	XtkMsg          select;
} XtkCalendarDesc;

typedef enum XtkSpectrum
{
	XTK_SPECTRUM_HUE_SATURATION = 0,
	XTK_SPECTRUM_HUE_VALUE,
	XTK_SPECTRUM_SATURATION_VALUE,
} XtkSpectrum;

typedef struct XtkColorPickerDesc {
	XtkColor    color;
	bool        alpha;
	bool        morebutton;
	XtkSpectrum spectrum;
	bool        disabled;
	XtkMsg      change;
} XtkColorPickerDesc;

typedef struct XtkComboDesc {
	char const *const *items;
	int                nitem;
	int                sel;
	bool               editable;
	char const        *content;
	XtkMsg             select;
	XtkMsg             submit;
} XtkComboDesc;

typedef struct XtkExpanderDesc {
	bool   expanded;
	float  w;
	float  contenth;
	XtkMsg toggle;
} XtkExpanderDesc;

typedef struct XtkInfoBarDesc {
	XtkInfoBarSeverity severity;
	bool               closable;
	char const        *message;
	XtkMsg             close;
} XtkInfoBarDesc;

typedef struct XtkNumberDesc {
	double min;
	double max;
	double step;
	double value;
	bool   disabled;
	bool   hide_spin;
	XtkMsg change;
} XtkNumberDesc;

typedef struct XtkMenuItemDesc {
	char const *label;
	char const *icon;
	bool        disabled;
	XtkMsg      click;
} XtkMenuItemDesc;

typedef struct XtkDropdownDesc {
	XtkButtonStyle         style;
	bool                   disabled;
	char const            *icon;
	XtkMenuItemDesc const *items;
	int                    nitem;
} XtkDropdownDesc;

typedef struct XtkSplitDesc {
	bool                   disabled;
	char const            *icon;
	XtkMsg                 click;
	XtkMenuItemDesc const *items;
	int                    nitem;
	bool                   checked;
	XtkMsg                 toggle;
} XtkSplitDesc;

typedef struct XtkTabDesc {
	char const *icon;
	char const *label;
} XtkTabDesc;

typedef struct XtkTabViewDesc {
	XtkTabDesc const *tabs;
	int               ntab;
	int               sel;
	XtkMsg            select;
	XtkMsg            close;
	XtkMsg            add;
} XtkTabViewDesc;

typedef struct XtkMenuDesc {
	char const            *title;
	XtkMenuItemDesc const *items;
	int                    nitem;
} XtkMenuDesc;

typedef struct XtkMenuBarDesc {
	XtkMenuDesc const *menus;
	int                nmenu;
} XtkMenuBarDesc;

typedef struct XtkDialogDesc {
	bool        open;
	char const *primary;
	char const *secondary;
	char const *close;
	float       w;
	float       contenth;
	XtkMsg      result;
} XtkDialogDesc;

typedef enum XtkListSelMode
{
	XTK_LIST_SELECT_SINGLE = 0,
	XTK_LIST_SELECT_NONE,
	XTK_LIST_SELECT_MULTIPLE,
	XTK_LIST_SELECT_EXTENDED,
} XtkListSelMode;

typedef enum XtkListKind
{
	XTK_LIST_KIND_LIST = 0,
	XTK_LIST_KIND_LIST_BOX,
	XTK_LIST_KIND_GRID,
	XTK_LIST_KIND_REPEATER,
	XTK_LIST_KIND_ITEMS,
} XtkListKind;

typedef struct XtkListDesc {
	int            nitem;
	float          itemh;
	float          itemw;
	int            ncol;
	int            overscan;
	XtkEl         *(*item)(XtkUi *ui, void *env, int index);
	void          *env;
	XtkListSelMode sel_mode;
	int            sel;
	XtkMsg         select;
	float          gap;
	bool           item_invoked_enabled;
	XtkMsg         invoke;
} XtkListDesc;

typedef struct XtkListItemDesc {
	int         index;
	XtkListKind kind;
	bool        selected;
	bool        multi;
	bool        expanded;
	char const *icon;
	float       x, y;
	float       w, h;
} XtkListItemDesc;

typedef enum XtkItemsViewLayout
{
	XTK_ITEMS_LAYOUT_STACK_V = 0,
	XTK_ITEMS_LAYOUT_STACK_H,
	XTK_ITEMS_LAYOUT_UNIFORM_GRID,
	XTK_ITEMS_LAYOUT_FLOW,
} XtkItemsViewLayout;

typedef struct XtkItemsViewDesc {
	int                nitem;
	float              itemh;
	float              itemw;
	int                ncol;
	int                overscan;
	float              gap;
	XtkEl             *(*item)(XtkUi *ui, void *env, int index);
	void              *env;
	XtkItemsViewLayout layout;
	XtkListSelMode     selection_mode;
	int                sel;
	bool               item_invoked_enabled;
	XtkMsg             select;
	XtkMsg             invoke;
} XtkItemsViewDesc;

int xtk_list_autocolumns(float cross, float itemw, int explicit_columns);

typedef struct XtkFlipDesc {
	int    sel;
	bool   vertical;
	XtkMsg select;
} XtkFlipDesc;

typedef enum XtkPipsNavVis
{
	XTK_PIPS_NAV_COLLAPSED = 0,
	XTK_PIPS_NAV_VISIBLE,
	XTK_PIPS_NAV_ON_HOVER,
} XtkPipsNavVis;

typedef struct XtkAutoSuggestDesc {
	char const        *content;
	char const *const *suggestions;
	int                nitem;
	char const        *query_icon;
	bool               disabled;
	XtkMsg             on_text;
	XtkMsg             query;
	XtkMsg             on_chosen;
} XtkAutoSuggestDesc;

typedef enum XtkPagerDisplayMode
{
	XTK_PAGER_DISPLAY_AUTO = 0,
	XTK_PAGER_DISPLAY_NUMBER_PANEL,
	XTK_PAGER_DISPLAY_NUMBER_TEXT,
} XtkPagerDisplayMode;

typedef enum XtkPagerButtonVis
{
	XTK_PAGER_BUTTON_AUTO = 0,
	XTK_PAGER_BUTTON_ALWAYS,
	XTK_PAGER_BUTTON_HIDDEN_EDGE,
	XTK_PAGER_BUTTON_NONE,
} XtkPagerButtonVis;

typedef struct XtkPagerDesc {
	int                 nitem;
	int                 sel;
	XtkPagerDisplayMode display_mode;
	XtkPagerButtonVis   first_button;
	XtkPagerButtonVis   prev_button;
	XtkPagerButtonVis   next_button;
	XtkPagerButtonVis   last_button;
	char const         *prefix;
	char const         *suffix;
	XtkMsg              select;
} XtkPagerDesc;

typedef struct XtkPipsDesc {
	int           nitem;
	int           sel;
	int           max_visible;
	bool          vertical;
	XtkPipsNavVis nav;
	XtkMsg        select;
} XtkPipsDesc;

typedef struct XtkBreadcrumbDesc {
	char const *const *items;
	int                nitem;
	bool               disabled;
	XtkMsg             click;
} XtkBreadcrumbDesc;

typedef struct XtkSelectorItem {
	char const *text;
	char const *icon;
	bool        disabled;
} XtkSelectorItem;

typedef struct XtkSelectorBarDesc {
	XtkSelectorItem const *items;
	int                    nitem;
	int                    sel;
	XtkMsg                 select;
} XtkSelectorBarDesc;

typedef struct XtkRatingDesc {
	double      value;
	int         max_rating;
	double      placeholder_value;
	int         initial_set_value;
	bool        is_clear_enabled;
	bool        is_read_only;
	char const *caption;
	XtkMsg      change;
} XtkRatingDesc;

typedef struct XtkRadioItem {
	char const *label;
	bool        disabled;
} XtkRadioItem;

typedef struct XtkRadioButtonsDesc {
	char const         *header;
	XtkRadioItem const *items;
	int                 nitem;
	int                 sel;
	int                 max_columns;
	bool                disabled;
	XtkMsg              select;
} XtkRadioButtonsDesc;

typedef enum XtkNavKind
{
	XTK_NAV_ITEM = 0,
	XTK_NAV_HEADER,
	XTK_NAV_SEPARATOR,
	XTK_NAV_FOOTER,
	XTK_NAV_CHILD,
} XtkNavKind;

typedef struct XtkNavItemDesc {
	XtkNavKind  kind;
	char const *icon;
	char const *label;
} XtkNavItemDesc;

typedef enum XtkPullDirection
{
	XTK_PULL_TOP_TO_BOTTOM = 0,
	XTK_PULL_LEFT_TO_RIGHT,
	XTK_PULL_RIGHT_TO_LEFT,
	XTK_PULL_BOTTOM_TO_TOP,
} XtkPullDirection;

typedef struct XtkRefreshDesc {
	XtkPullDirection direction;
	float            visualizer_size;
	float            threshold_ratio;
	bool             is_refreshing;
	XtkMsg           on_refresh;
} XtkRefreshDesc;

typedef enum XtkTreeSelMode
{
	XTK_TREE_SELECT_SINGLE = 0,
	XTK_TREE_SELECT_NONE,
	XTK_TREE_SELECT_MULTIPLE,
} XtkTreeSelMode;

typedef struct XtkTreeNodeDesc {
	char const                   *text;
	char const                   *icon;
	bool                          expanded;
	bool                          disabled;
	bool                          checked;
	struct XtkTreeNodeDesc const *children;
	int32_t                       child_count;
} XtkTreeNodeDesc;

typedef struct XtkTreeDesc {
	XtkTreeNodeDesc const *roots;
	int32_t                nroot;
	XtkTreeSelMode         sel_mode;
	int32_t                sel;
	float                  rowh;
	XtkMsg                 invoke;
	XtkMsg                 expand;
	XtkMsg                 select;
} XtkTreeDesc;

typedef struct XtkNavDesc {
	XtkNavItemDesc const *items;
	int                   nitem;
	int                   sel;
	bool                  window_title_bar;
	char const           *app_title;
	XtkMsg                select;
} XtkNavDesc;

typedef struct XtkTeachingTipDesc {
	bool                    open;
	char const             *subtitle;
	char const             *icon;
	char const             *action_text;
	bool                    action_accent;
	char const             *close_text;
	XtkTeachingTipPlacement placement;
	bool                    untargeted;
	bool                    light_dismiss;
	int8_t                  tail;
	float                   placement_margin;
	XtkMsg                  on_action;
	XtkMsg                  close;
} XtkTeachingTipDesc;

typedef struct XtkPersonPictureDesc {
	char const *display_name;
	char const *initials;
	XtkResource image;
	char const *badge_glyph;
	int32_t     badge_number;
	float       size;
	bool        is_group;
} XtkPersonPictureDesc;

typedef enum XtkSplitViewDisplayMode
{
	XTK_SPLITVIEW_INLINE = 0,
	XTK_SPLITVIEW_COMPACT_INLINE,
	XTK_SPLITVIEW_OVERLAY,
	XTK_SPLITVIEW_COMPACT_OVERLAY,
} XtkSplitViewDisplayMode;

typedef enum XtkSplitViewPanePlacement
{
	XTK_SPLITVIEW_LEFT = 0,
	XTK_SPLITVIEW_RIGHT,
} XtkSplitViewPanePlacement;

typedef struct XtkSplitViewDesc {
	bool                      pane_open;
	XtkSplitViewDisplayMode   display_mode;
	XtkSplitViewPanePlacement pane_placement;
	float                     open_pane_length;
	float                     compact_pane_length;
} XtkSplitViewDesc;

typedef struct XtkTitleBarDesc {
	char const *subtitle;
	char const *icon;
	bool        show_back;
	bool        back_disabled;
	bool        show_pane_toggle;
	bool        integrate_window;
	XtkMsg      on_back;
	XtkMsg      on_pane_toggle;
} XtkTitleBarDesc;

XENT_NODISCARD XtkUi  *xtk_ui_create(void);

void                   xtk_ui_destroy(XtkUi *ui);

void                   xtk_ui_begin(XtkUi *ui);

XENT_NODISCARD char   *xtk_strdup(XtkUi *ui, char const *s);

XENT_NODISCARD char   *xtk_fmt(XtkUi *ui, char const *fmt, ...);

XENT_NODISCARD XtkEl  *xtk_static_region(XtkUi *ui, uint64_t id, XtkRegionBuildFn build, void *ctx);

XENT_NODISCARD XtkEl  *xtk_memo_region(XtkUi *ui, uint64_t id, uint64_t revision, XtkRegionBuildFn build, void *ctx);

XtkEl                 *xtk_text(XtkUi *ui, char const *content, XtkTextDesc desc);
XtkEl                 *xtk_button(XtkUi *ui, char const *label, XtkButtonDesc desc);
XtkEl                 *xtk_checkbox(XtkUi *ui, char const *label, XtkToggleDesc desc);
XtkEl                 *xtk_radio(XtkUi *ui, char const *label, XtkToggleDesc desc);
XtkEl                 *xtk_switch(XtkUi *ui, XtkToggleDesc desc);
XtkEl                 *xtk_slider(XtkUi *ui, XtkSliderDesc desc);
XtkEl                 *xtk_scroll_bar(XtkUi *ui, XtkScrollBarDesc desc);
XtkEl                 *xtk_textbox(XtkUi *ui, char const *placeholder, XtkTextBoxDesc desc);
XtkEl                 *xtk_password(XtkUi *ui, char const *placeholder, XtkTextBoxDesc desc);
XtkEl                 *xtk_progress(XtkUi *ui, XtkProgressDesc desc);
XtkEl                 *xtk_progressring(XtkUi *ui, XtkProgressDesc desc);
XtkEl                 *xtk_badge(XtkUi *ui, XtkBadgeDesc desc);
XtkEl                 *xtk_image(XtkUi *ui, XtkImageDesc desc);
XtkEl                 *xtk_link(XtkUi *ui, char const *label, XtkHyperlinkDesc desc);
XtkEl                 *xtk_divider(XtkUi *ui);
XtkEl                 *xtk_spacer(XtkUi *ui);
XtkEl                 *xtk_repeat(XtkUi *ui, char const *label, XtkButtonDesc desc);
XtkEl                 *xtk_combo(XtkUi *ui, char const *placeholder, XtkComboDesc desc);
XtkEl                 *xtk_looping_selector(XtkUi *ui, XtkLoopingDesc desc);
XtkEl                 *xtk_date_picker(XtkUi *ui, XtkDatePickerDesc desc);
XtkEl                 *xtk_time_picker(XtkUi *ui, XtkTimePickerDesc desc);
XtkEl                 *xtk_calendar_view(XtkUi *ui, XtkCalendarDesc desc);
XtkEl                 *xtk_color_picker(XtkUi *ui, XtkColorPickerDesc desc);
XtkEl                 *xtk_infobar(XtkUi *ui, char const *title, char const *message, XtkInfoBarDesc desc);
XtkEl                 *xtk_number(XtkUi *ui, XtkNumberDesc desc);
XtkEl                 *xtk_dropdown(XtkUi *ui, char const *label, XtkDropdownDesc desc);
XtkEl                 *xtk_split(XtkUi *ui, char const *label, XtkSplitDesc desc);
XtkEl                 *xtk_togglesplit(XtkUi *ui, char const *label, XtkSplitDesc desc);
XtkEl                 *xtk_radiogroup(XtkUi *ui, XtkRadioButtonsDesc desc);
XtkEl                 *xtk_rating(XtkUi *ui, XtkRatingDesc desc);
XtkEl                 *xtk_selector(XtkUi *ui, XtkSelectorBarDesc desc);
XtkEl                 *xtk_breadcrumb(XtkUi *ui, XtkBreadcrumbDesc desc);
XtkEl                 *xtk_menubar(XtkUi *ui, XtkMenuBarDesc desc);
XtkEl                 *xtk_list(XtkUi *ui, XtkListDesc desc);
XtkEl                 *xtk_listbox(XtkUi *ui, XtkListDesc desc);
XtkEl                 *xtk_gridview(XtkUi *ui, XtkListDesc desc);
XtkEl                 *xtk_repeater(XtkUi *ui, XtkListDesc desc);
XtkEl                 *xtk_itemsview(XtkUi *ui, XtkItemsViewDesc desc);
XtkEl                 *xtk_tree(XtkUi *ui, XtkTreeDesc desc);
XtkEl                 *xtk_pips(XtkUi *ui, XtkPipsDesc desc);
XtkEl                 *xtk_avatar(XtkUi *ui, XtkPersonPictureDesc desc);
XtkEl                 *xtk_pager(XtkUi *ui, XtkPagerDesc desc);
XtkEl                 *xtk_suggest(XtkUi *ui, char const *placeholder, XtkAutoSuggestDesc desc);

XtkEl                 *xtk_column(XtkUi *ui, XtkStackDesc desc, XtkEl *children []);
XtkEl                 *xtk_row(XtkUi *ui, XtkStackDesc desc, XtkEl *children []);
XtkEl                 *xtk_card(XtkUi *ui, XtkStackDesc desc, XtkEl *children []);
XtkEl                 *xtk_scroll(XtkUi *ui, XtkEl *children []);
XtkEl                 *xtk_expander(XtkUi *ui, char const *header, XtkExpanderDesc desc, XtkEl *children []);
XtkEl                 *xtk_nav(XtkUi *ui, XtkNavDesc desc, XtkEl *children []);
XtkEl                 *xtk_tabs(XtkUi *ui, XtkTabViewDesc desc, XtkEl *children []);
XtkEl                 *xtk_flip(XtkUi *ui, XtkFlipDesc desc, XtkEl *children []);
XtkEl                 *xtk_dialog(XtkUi *ui, char const *title, XtkDialogDesc desc, XtkEl *children []);
XtkEl                 *xtk_teachtip(XtkUi *ui, char const *title, XtkTeachingTipDesc desc, XtkEl *children []);
XtkEl                 *xtk_splitview(XtkUi *ui, XtkSplitViewDesc desc, XtkEl *pane, XtkEl *content);
XtkEl                 *xtk_titlebar(XtkUi *ui, char const *title, XtkTitleBarDesc desc);
XtkEl                 *xtk_refresh(XtkUi *ui, XtkRefreshDesc desc, XtkEl *children []);

XENT_NODISCARD XtkEl **xtk_children_alloc(XtkUi *ui, int capacity);

XtkEl                 *xtk_keyed(XtkUi *ui, char const *key, XtkEl *el);
XtkEl                 *xtk_keyed_u64(XtkEl *el, uint64_t key);

XtkEl                 *xtk_tooltip(XtkUi *ui, XtkEl *el, char const *text);

XtkEl                 *xtk_sized(XtkEl *el, float width, float height);

XtkEl                 *xtk_grow(XtkEl *el, float grow);
XtkEl                 *xtk_align(XtkEl *el, XentFlexAlign align_self);
XtkEl                 *xtk_margin(XtkEl *el, XentInsets margin);

#endif
