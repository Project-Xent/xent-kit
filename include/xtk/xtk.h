#ifndef XTK_H
#define XTK_H

#include <assert.h>

#include "xtk_descriptor.h"
#include "xtk_msg.h"
#include <stdbool.h>
#include <stdint.h>
#include <xent/xent.h>

typedef XtkEl *(*XtkRegionBuildFn)(XtkUi *ui, void *ctx);

typedef struct XtkModelVer {
	void const *ptr;
	uint64_t    revision;
} XtkModelVer;

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

#define XTK_END       (( XtkEl * ) ( uintptr_t ) 1u)

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
	XentInsets      nine;
	XtkMsg          opened;
	XtkMsg          failed;
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

typedef struct XtkScrollDesc {
	float  x;
	float  y;
	XtkMsg scroll;
} XtkScrollDesc;

typedef struct XtkDragDropDesc {
	XtkDropOperation drop;
	char const      *drag_text;
	char const      *drag_files;
	XtkMsg           hover;
	XtkMsg           drop_files;
	XtkMsg           drop_text;
	XtkMsg           dragged;
} XtkDragDropDesc;

typedef struct XtkLoopingDesc {
	char const *const *items;
	int                nitem;
	int                sel;
	float              itemh;
	float              itemw;
	bool               loop;
	bool               disabled;
	XtkMsg             select;
	XtkModelVer        version;
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
	XtkModelVer        version;
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
	XtkModelVer       version;
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
	bool            open;
	char const     *primary;
	char const     *secondary;
	char const     *close;
	float           w;
	float           contenth;
	XtkMsg          result;
	XtkDialogButton default_button;
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
	int                nitem;
	float              itemh;
	float              itemw;
	int                ncol;
	XtkEl             *(*item)(XtkUi *ui, void *env, int index);
	void              *env;
	XtkListSelMode     sel_mode;
	int                sel;
	XtkMsg             select;
	float              gap;
	bool               item_invoked_enabled;
	XtkMsg             invoke;
	XtkEl             *header;
	int32_t const     *groups;
	int                ngroup;
	XtkEl             *(*group_header)(XtkUi *ui, void *env, int group);
	bool               rect_select;
	char const *const *names;
	int                nname;
	XtkModelVer        version;
} XtkListDesc;

typedef struct XtkListRow {
	int32_t group;
	int32_t item;
} XtkListRow;

typedef struct XtkListItemDesc {
	int         index;
	XtkListKind kind;
	bool        selected;
	bool        multi;
	bool        expanded;
	char const *icon;
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
	XtkModelVer        version;
} XtkAutoSuggestDesc;

typedef enum XtkPagerDisplayMode
{
	XTK_PAGER_DISPLAY_AUTO = 0,
	XTK_PAGER_DISPLAY_COMBO_BOX,
	XTK_PAGER_DISPLAY_NUMBER_BOX,
	XTK_PAGER_DISPLAY_BUTTON_PANEL,
} XtkPagerDisplayMode;

typedef enum XtkPagerButtonVis
{
	XTK_PAGER_BUTTON_VISIBLE = 0,
	XTK_PAGER_BUTTON_HIDDEN_ON_EDGE,
	XTK_PAGER_BUTTON_HIDDEN,
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
	bool                hide_ends;
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
	XtkModelVer        version;
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
	XtkModelVer            version;
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
	XTK_NAV_FOOTER_HEADER,
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
	XtkModelVer            version;
} XtkTreeDesc;

typedef enum XtkNavPaneMode
{
	XTK_NAV_PANE_AUTO = 0,
	XTK_NAV_PANE_LEFT,
	XTK_NAV_PANE_TOP,
	XTK_NAV_PANE_LEFT_COMPACT,
	XTK_NAV_PANE_LEFT_MINIMAL,
} XtkNavPaneMode;

enum
{
	XTK_NAV_SETTINGS = -2,
};

typedef enum XtkNavSlot
{
	XTK_NAV_SLOT_CONTENT = 0,
	XTK_NAV_SLOT_HEADER,
	XTK_NAV_SLOT_CUSTOM,
	XTK_NAV_SLOT_FOOTER,
	XTK_NAV_SLOT_SEARCH,
	XTK_NAV_SLOT_PAGE_HEADER = 8,
	XTK_NAV_SLOT_CONTENT_OVERLAY,
} XtkNavSlot;

typedef enum XtkNavTitleBar
{
	XTK_NAV_TITLE_BAR_NONE,
	XTK_NAV_TITLE_BAR_COMPACT,
	XTK_NAV_TITLE_BAR_TALL,
} XtkNavTitleBar;

typedef enum XtkNavBackButton
{
	XTK_NAV_BACK_AUTO,
	XTK_NAV_BACK_VISIBLE,
	XTK_NAV_BACK_COLLAPSED,
} XtkNavBackButton;

typedef XtkEl *(*XtkNavHeaderTemplate)(XtkUi *ui, void const *header);

typedef struct XtkNavDesc {
	XtkNavItemDesc const *items;
	int                   nitem;
	int                   sel;
	XtkNavPaneMode        pane_mode;
	uint8_t               window_title_bar;
	char const           *app_title;
	XtkMsg                select;
	bool                  hide_settings;
	char const           *pane_title;
	bool                  hide_header;
	XtkNavBackButton      back_button;
	bool                  back_enabled;
	XtkMsg                back_requested;
	XtkModelVer           version;
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
	XtkResource badge_image;
	char const *badge_text;
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
	XtkMsg                    change;
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

typedef enum XtkTitleBarSlot
{
	XTK_TITLE_BAR_SLOT_LEFT_HEADER = XTK_NAV_SLOT_SEARCH + 1,
	XTK_TITLE_BAR_SLOT_CONTENT,
	XTK_TITLE_BAR_SLOT_RIGHT_HEADER,
} XtkTitleBarSlot;

typedef struct XtkColItemDesc {
	float            width;
	float            min_width;
	float            max_width;
	XtkTextAlign     align;
	XtkSortDirection sort;
	bool             unsortable;
	bool             fixed;
	XtkMsg           click;
	XtkMsg           resize;
	XtkMsg           fit;
	XtkMsg           reorder;
} XtkColItemDesc;

typedef struct XtkCommandBarDesc {
	bool              open;
	bool              sticky;
	bool              dynamic;
	bool              disabled;
	XtkAppBarMode     mode;
	XtkLabelPosition  labels;
	XtkOverflowButton more;
	XtkMsg            change;
} XtkCommandBarDesc;

typedef struct XtkAppBarDesc {
	char const *icon;
	char const *accel;
	bool        disabled;
	bool        checked;
	bool        secondary;
	bool        label_collapsed;
	int32_t     order;
	XtkMsg      click;
	XtkMsg      change;
} XtkAppBarDesc;

typedef enum XtkNavTransitionKind
{
	XTK_NAV_TRANSITION_ENTRANCE = 0,
	XTK_NAV_TRANSITION_SLIDE_RIGHT,
	XTK_NAV_TRANSITION_SLIDE_LEFT,
	XTK_NAV_TRANSITION_SLIDE_BOTTOM,
	XTK_NAV_TRANSITION_DRILL_IN,
	XTK_NAV_TRANSITION_SUPPRESS,
} XtkNavTransitionKind;

typedef enum XtkThemeTransitionKind
{
	XTK_THEME_TRANSITION_NONE = 0,
	XTK_THEME_TRANSITION_ENTRANCE,
	XTK_THEME_TRANSITION_ADD_DELETE,
	XTK_THEME_TRANSITION_CONTENT,
	XTK_THEME_TRANSITION_REORDER,
	XTK_THEME_TRANSITION_POPUP,
} XtkThemeTransitionKind;

typedef enum XtkConnectedKind
{
	XTK_CONNECTED_GRAVITY = 0,
	XTK_CONNECTED_DIRECT,
	XTK_CONNECTED_BASIC,
} XtkConnectedKind;

typedef struct XtkFrameDesc {
	XtkNavTransitionKind transition;
	bool                 is_back;
	int32_t              page_key;
} XtkFrameDesc;

enum
{
	XTK_STYLE_BACKGROUND    = 1u << 0,
	XTK_STYLE_BORDER_COLOR  = 1u << 1,
	XTK_STYLE_CORNER_RADIUS = 1u << 2,
	XTK_STYLE_BORDER_WIDTH  = 1u << 3,
	XTK_STYLE_OPACITY       = 1u << 4,
	XTK_STYLE_TRANSLATE_X   = 1u << 5,
	XTK_STYLE_TRANSLATE_Y   = 1u << 6,
	XTK_STYLE_SCALE_X       = 1u << 7,
	XTK_STYLE_SCALE_Y       = 1u << 8,
	XTK_STYLE_ROTATION      = 1u << 9,
};

enum
{
	XTK_MOTION_OPACITY       = 1u << 0,
	XTK_MOTION_TRANSLATE_X   = 1u << 1,
	XTK_MOTION_TRANSLATE_Y   = 1u << 2,
	XTK_MOTION_SCALE_X       = 1u << 3,
	XTK_MOTION_SCALE_Y       = 1u << 4,
	XTK_MOTION_ROTATION      = 1u << 5,
	XTK_MOTION_BACKGROUND    = 1u << 6,
	XTK_MOTION_BORDER_COLOR  = 1u << 7,
	XTK_MOTION_CORNER_RADIUS = 1u << 8,
	XTK_MOTION_TRANSLATE     = (1u << 1) | (1u << 2),
	XTK_MOTION_SCALE         = (1u << 3) | (1u << 4),
	XTK_MOTION_ALL           = 0x1ffu,
};

typedef struct XtkStyle {
	uint32_t mask;
	XtkColor background;
	XtkColor border_color;
	float    corner_radius;
	float    border_width;
	float    opacity;
	float    translate_x;
	float    translate_y;
	float    scale_x;
	float    scale_y;
	float    rotation;
} XtkStyle;

typedef struct XtkMotion {
	uint32_t               implicit_mask;
	double                 opacity_duration;
	double                 transform_duration;
	double                 brush_duration;
	XtkThemeTransitionKind enter_exit;
} XtkMotion;

typedef struct XtkConnectedDesc {
	XtkConnectedKind kind;
	bool             disable_shadow;
	float            dip_x;
	float            dip_y;
	double           duration;
} XtkConnectedDesc;

XENT_NODISCARD XtkUi *xtk_ui_create(void);

void                  xtk_ui_destroy(XtkUi *ui);

void                  xtk_ui_begin(XtkUi *ui);

XENT_NODISCARD char  *xtk_strdup(XtkUi *ui, char const *s);

XENT_NODISCARD char  *xtk_fmt(XtkUi *ui, char const *fmt, ...);

XENT_NODISCARD XtkEl *xtk_static_region(XtkUi *ui, uint64_t id, XtkRegionBuildFn build, void *ctx);

XENT_NODISCARD XtkEl *xtk_memo_region(XtkUi *ui, uint64_t id, uint64_t revision, XtkRegionBuildFn build, void *ctx);

XENT_NODISCARD XtkEl *xtk_sub_region(XtkUi *ui, uint64_t id, XtkRegionBuildFn build, void *ctx);

XtkEl                *xtk_text(XtkUi *ui, char const *content, XtkTextDesc desc);
XtkEl                *xtk_button(XtkUi *ui, char const *label, XtkButtonDesc desc);
XtkEl                *xtk_checkbox(XtkUi *ui, char const *label, XtkToggleDesc desc);
XtkEl                *xtk_radio(XtkUi *ui, char const *label, XtkToggleDesc desc);
XtkEl                *xtk_switch(XtkUi *ui, XtkToggleDesc desc);
XtkEl                *xtk_slider(XtkUi *ui, XtkSliderDesc desc);
XtkEl                *xtk_scroll_bar(XtkUi *ui, XtkScrollBarDesc desc);
XtkEl                *xtk_textbox(XtkUi *ui, char const *placeholder, XtkTextBoxDesc desc);
XtkEl                *xtk_password(XtkUi *ui, char const *placeholder, XtkTextBoxDesc desc);
XtkEl                *xtk_progress(XtkUi *ui, XtkProgressDesc desc);
XtkEl                *xtk_progressring(XtkUi *ui, XtkProgressDesc desc);
XtkEl                *xtk_badge(XtkUi *ui, XtkBadgeDesc desc);
XtkEl                *xtk_image(XtkUi *ui, XtkImageDesc desc);
XtkEl                *xtk_link(XtkUi *ui, char const *label, XtkHyperlinkDesc desc);
XtkEl                *xtk_divider(XtkUi *ui);
XtkEl                *xtk_spacer(XtkUi *ui);
XtkEl                *xtk_repeat(XtkUi *ui, char const *label, XtkButtonDesc desc);
XtkEl                *xtk_combo(XtkUi *ui, char const *placeholder, XtkComboDesc desc);
XtkEl                *xtk_looping_selector(XtkUi *ui, XtkLoopingDesc desc);
XtkEl                *xtk_date_picker(XtkUi *ui, XtkDatePickerDesc desc);
XtkEl                *xtk_time_picker(XtkUi *ui, XtkTimePickerDesc desc);
XtkEl                *xtk_calendar_view(XtkUi *ui, XtkCalendarDesc desc);
XtkEl                *xtk_color_picker(XtkUi *ui, XtkColorPickerDesc desc);
XtkEl                *xtk_infobar(XtkUi *ui, char const *title, char const *message, XtkInfoBarDesc desc);
XtkEl                *xtk_number(XtkUi *ui, XtkNumberDesc desc);
XtkEl                *xtk_dropdown(XtkUi *ui, char const *label, XtkDropdownDesc desc);
XtkEl                *xtk_split(XtkUi *ui, char const *label, XtkSplitDesc desc);
XtkEl                *xtk_togglesplit(XtkUi *ui, char const *label, XtkSplitDesc desc);
XtkEl                *xtk_radiogroup(XtkUi *ui, XtkRadioButtonsDesc desc);
XtkEl                *xtk_rating(XtkUi *ui, XtkRatingDesc desc);
XtkEl                *xtk_selector(XtkUi *ui, XtkSelectorBarDesc desc);
XtkEl                *xtk_breadcrumb(XtkUi *ui, XtkBreadcrumbDesc desc);
XtkEl                *xtk_menubar(XtkUi *ui, XtkMenuBarDesc desc);
XtkEl                *xtk_list(XtkUi *ui, XtkListDesc desc);
XtkListRow            xtk_list_row(int32_t const *groups, int32_t ngroup, int32_t row);
XtkEl                *xtk_listbox(XtkUi *ui, XtkListDesc desc);
XtkEl                *xtk_gridview(XtkUi *ui, XtkListDesc desc);
XtkEl                *xtk_repeater(XtkUi *ui, XtkListDesc desc);
XtkEl                *xtk_itemsview(XtkUi *ui, XtkItemsViewDesc desc);
XtkEl                *xtk_tree(XtkUi *ui, XtkTreeDesc desc);
XtkEl                *xtk_pips(XtkUi *ui, XtkPipsDesc desc);
XtkEl                *xtk_avatar(XtkUi *ui, XtkPersonPictureDesc desc);
XtkEl                *xtk_pager(XtkUi *ui, XtkPagerDesc desc);
XtkEl                *xtk_suggest(XtkUi *ui, char const *placeholder, XtkAutoSuggestDesc desc);
XtkEl                *xtk_colitem(XtkUi *ui, char const *label, XtkColItemDesc desc);
XtkEl                *xtk_appbarbutton(XtkUi *ui, char const *label, XtkAppBarDesc desc);
XtkEl                *xtk_appbartoggle(XtkUi *ui, char const *label, XtkAppBarDesc desc);
XtkEl                *xtk_appbarsep(XtkUi *ui, XtkAppBarDesc desc);

XtkEl                *xtk_column(XtkUi *ui, XtkStackDesc desc, XtkEl *children []);
XtkEl                *xtk_row(XtkUi *ui, XtkStackDesc desc, XtkEl *children []);
XtkEl                *xtk_card(XtkUi *ui, XtkStackDesc desc, XtkEl *children []);
XtkEl                *xtk_dragdrop(XtkUi *ui, XtkDragDropDesc desc, XtkEl *child);
XtkEl                *xtk_scroll(XtkUi *ui, XtkScrollDesc desc, XtkEl *children []);
XtkEl                *xtk_expander(XtkUi *ui, char const *header, XtkExpanderDesc desc, XtkEl *children []);
XtkEl                *xtk_nav(XtkUi *ui, XtkNavDesc desc, XtkEl *children []);
XtkEl                *xtk_nav_slot(XtkUi *ui, XtkNavSlot slot, XtkEl *child);
XtkEl                *xtk_nav_header_template(XtkUi *ui, void const *header, XtkNavHeaderTemplate render);
XtkEl                *xtk_tabs(XtkUi *ui, XtkTabViewDesc desc, XtkEl *children []);
XtkEl                *xtk_flip(XtkUi *ui, XtkFlipDesc desc, XtkEl *children []);
XtkEl                *xtk_dialog(XtkUi *ui, char const *title, XtkDialogDesc desc, XtkEl *children []);
XtkEl                *xtk_teachtip(XtkUi *ui, char const *title, XtkTeachingTipDesc desc, XtkEl *children []);
XtkEl                *xtk_splitview(XtkUi *ui, XtkSplitViewDesc desc, XtkEl *pane, XtkEl *content);
XtkEl                *xtk_titlebar(XtkUi *ui, char const *title, XtkTitleBarDesc desc);
XtkEl                *xtk_titlebar_slots(
  XtkUi *ui, char const *title, XtkTitleBarDesc desc, XtkEl *left_header, XtkEl *content, XtkEl *right_header
);
XtkEl                 *xtk_commandbar(XtkUi *ui, XtkCommandBarDesc desc, XtkEl *children []);
XtkEl                 *xtk_refresh(XtkUi *ui, XtkRefreshDesc desc, XtkEl *children []);
XtkEl                 *xtk_colheader(XtkUi *ui, XtkEl *children []);
XtkEl                 *xtk_frame(XtkUi *ui, XtkFrameDesc desc, XtkEl *child);
XtkNavTransitionKind   xtk_nav_recommended_transition(int prev_index, int next_index, XtkNavPaneMode mode);

XENT_NODISCARD XtkEl **xtk_children_alloc(XtkUi *ui, int capacity);

XtkEl                 *xtk_keyed(XtkUi *ui, char const *key, XtkEl *el);
XtkEl                 *xtk_keyed_u64(XtkEl *el, uint64_t key);

XtkEl                 *xtk_tooltip(XtkUi *ui, XtkEl *el, char const *text);

typedef struct XtkAutomation {
	char const     *name;
	char const     *id;
	char const     *help;
	char const     *description;
	char const     *item_status;
	char const     *item_type;
	char const     *control_type;
	char const     *accelerator;
	char const     *access_key;
	char const     *landmark_name;
	char const     *labeled_by;
	char const     *described_by;
	char const     *flows_to;
	char const     *flows_from;
	char const     *controls;
	XtkLandmark     landmark;
	XtkLiveSetting  live;
	XtkHeadingLevel heading;
	XtkAccessView   view;
	bool            required;
	bool            invalid;
	bool            peripheral;
	bool            dialog;
	int32_t         position;
	int32_t         size;
	int32_t         level;
	int32_t         culture;
} XtkAutomation;

XtkEl *xtk_automation(XtkUi *ui, XtkEl *el, XtkAutomation const *automation);

XtkEl *xtk_style(XtkUi *ui, XtkEl *el, XtkStyle const *style);
XtkEl *xtk_motion(XtkUi *ui, XtkEl *el, XtkMotion const *motion);
XtkEl *xtk_connected(XtkUi *ui, XtkEl *el, char const *key, XtkConnectedDesc const *cfg);
XtkEl *xtk_connected_coord(XtkUi *ui, XtkEl *el, char const *key);

XtkEl *xtk_sized(XtkEl *el, float width, float height);

XtkEl *xtk_grow(XtkEl *el, float grow);
XtkEl *xtk_align(XtkEl *el, XentFlexAlign align_self);
XtkEl *xtk_margin(XtkEl *el, XentInsets margin);

static_assert(sizeof(XtkKeyKind) == 4, "XtkKeyKind crosses the ABI as int32");
static_assert(sizeof(XtkClock) == 4, "XtkClock crosses the ABI as int32");
static_assert(sizeof(XtkCalendarMode) == 4, "XtkCalendarMode crosses the ABI as int32");
static_assert(sizeof(XtkSpectrum) == 4, "XtkSpectrum crosses the ABI as int32");
static_assert(sizeof(XtkListSelMode) == 4, "XtkListSelMode crosses the ABI as int32");
static_assert(sizeof(XtkListKind) == 4, "XtkListKind crosses the ABI as int32");
static_assert(sizeof(XtkItemsViewLayout) == 4, "XtkItemsViewLayout crosses the ABI as int32");
static_assert(sizeof(XtkPipsNavVis) == 4, "XtkPipsNavVis crosses the ABI as int32");
static_assert(sizeof(XtkPagerDisplayMode) == 4, "XtkPagerDisplayMode crosses the ABI as int32");
static_assert(sizeof(XtkPagerButtonVis) == 4, "XtkPagerButtonVis crosses the ABI as int32");
static_assert(sizeof(XtkNavKind) == 4, "XtkNavKind crosses the ABI as int32");
static_assert(sizeof(XtkNavPaneMode) == 4, "XtkNavPaneMode crosses the ABI as int32");
static_assert(sizeof(XtkPullDirection) == 4, "XtkPullDirection crosses the ABI as int32");
static_assert(sizeof(XtkTreeSelMode) == 4, "XtkTreeSelMode crosses the ABI as int32");
static_assert(sizeof(XtkSplitViewDisplayMode) == 4, "XtkSplitViewDisplayMode crosses the ABI as int32");
static_assert(sizeof(XtkSplitViewPanePlacement) == 4, "XtkSplitViewPanePlacement crosses the ABI as int32");
static_assert(sizeof(XtkNavTransitionKind) == 4, "XtkNavTransitionKind crosses the ABI as int32");
static_assert(sizeof(XtkThemeTransitionKind) == 4, "XtkThemeTransitionKind crosses the ABI as int32");
static_assert(sizeof(XtkConnectedKind) == 4, "XtkConnectedKind crosses the ABI as int32");

#endif
