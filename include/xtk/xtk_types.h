#ifndef XTK_TYPES_H
#define XTK_TYPES_H

#include <stdint.h>
#include <stdbool.h>
#include <assert.h>

typedef struct XtkColor {
	uint32_t rgba;
} XtkColor;

static_assert(sizeof(XtkColor) == 4, "XtkColor is a packed 0xRRGGBBAA word");

static XtkColor inline xtk_color_rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
	XtkColor c = {(( uint32_t ) r << 24) | (( uint32_t ) g << 16) | (( uint32_t ) b << 8) | a};
	return c;
}

static XtkColor inline xtk_color_rgb(uint8_t r, uint8_t g, uint8_t b) { return xtk_color_rgba(r, g, b, 255); }

static XtkColor inline xtk_color_hex(uint32_t hex) {
	uint8_t r = (hex >> 16) & 0xff;
	uint8_t g = (hex >> 8) & 0xff;
	uint8_t b = hex & 0xff;
	return xtk_color_rgb(r, g, b);
}

static float inline xtk_color_rf(XtkColor c) { return ((c.rgba >> 24) & 0xff) / 255.0f; }

static float inline xtk_color_gf(XtkColor c) { return ((c.rgba >> 16) & 0xff) / 255.0f; }

static float inline xtk_color_bf(XtkColor c) { return ((c.rgba >> 8) & 0xff) / 255.0f; }

static float inline xtk_color_af(XtkColor c) { return (c.rgba & 0xff) / 255.0f; }

static int inline xtk_utf8_len(char const *s) {
	int n = 0;
	for (; s && *s; s++)
		if ((*s & 0xc0) != 0x80) n++;
	return n;
}

typedef enum XtkCtrlType
{
	XTK_CTRL_INVALID = 0,
	XTK_CTRL_CONTAINER,
	XTK_CTRL_TEXT,
	XTK_CTRL_BUTTON,
	XTK_CTRL_TOGGLE,
	XTK_CTRL_CHECKBOX,
	XTK_CTRL_RADIO,
	XTK_CTRL_SWITCH,
	XTK_CTRL_SLIDER,
	XTK_CTRL_TEXTBOX,
	XTK_CTRL_SCROLL,
	XTK_CTRL_IMAGE,
	XTK_CTRL_PROGRESS,
	XTK_CTRL_LIST,
	XTK_CTRL_TAB,
	XTK_CTRL_CARD,
	XTK_CTRL_DIVIDER,
	XTK_CTRL_CANVAS,
	XTK_CTRL_PASSWORD,
	XTK_CTRL_NUMBER,
	XTK_CTRL_LINK,
	XTK_CTRL_REPEAT,
	XTK_CTRL_PROGRESSRING,
	XTK_CTRL_BADGE,
	XTK_CTRL_TOOLTIP,
	XTK_CTRL_FLYOUT,
	XTK_CTRL_MENUFLY,
	XTK_CTRL_DROPDOWN,
	XTK_CTRL_SPLIT,
	XTK_CTRL_COMBO,
	XTK_CTRL_EXPANDER,
	XTK_CTRL_EXPHEAD,
	XTK_CTRL_EXPBODY,
	XTK_CTRL_INFOBAR,
	XTK_CTRL_DIALOG,
	XTK_CTRL_DIALOGBODY,
	XTK_CTRL_MENUBAR,
	XTK_CTRL_MENUITEM,
	XTK_CTRL_NAV,
	XTK_CTRL_NAVITEM,
	XTK_CTRL_TABS,
	XTK_CTRL_TABITEM,
	XTK_CTRL_LISTITEM,
	XTK_CTRL_LISTBOX,
	XTK_CTRL_GRIDVIEW,
	XTK_CTRL_REPEATER,
	XTK_CTRL_ITEMSVIEW,
	XTK_CTRL_FLIP,
	XTK_CTRL_PIPS,
	XTK_CTRL_SUGGEST,
	XTK_CTRL_TOGGLESPLIT,
	XTK_CTRL_RADIOGROUP,
	XTK_CTRL_RATING,
	XTK_CTRL_SELECTOR,
	XTK_CTRL_SELECTORITEM,
	XTK_CTRL_BREADCRUMB,
	XTK_CTRL_CRUMB,
	XTK_CTRL_TEACHTIP,
	XTK_CTRL_TREE,
	XTK_CTRL_TREEITEM,
	XTK_CTRL_REFRESH,
	XTK_CTRL_AVATAR,
	XTK_CTRL_PAGER,
	XTK_CTRL_SPLITVIEW,
	XTK_CTRL_SPLITPANE,
	XTK_CTRL_SPLITBODY,
	XTK_CTRL_TITLEBAR,
	XTK_CTRL_SCROLLBAR,
	XTK_CTRL_LOOPING,
	XTK_CTRL_LOOPITEM,
	XTK_CTRL_DATEPICKER,
	XTK_CTRL_TIMEPICKER,
	XTK_CTRL_PICKERFLYOUT,
	XTK_CTRL_CALENDAR,
	XTK_CTRL_CALDAY,
	XTK_CTRL_COLORPICKER,
	XTK_CTRL_COLORSPECTRUM,
	XTK_CTRL_COLORSLIDER,
	XTK_CTRL_TYPE_COUNT,
} XtkCtrlType;

static bool inline xtk_ctrl_islist(XtkCtrlType t) {
	return t == XTK_CTRL_LIST
	    || t == XTK_CTRL_LISTBOX
	    || t == XTK_CTRL_GRIDVIEW
	    || t == XTK_CTRL_REPEATER
	    || t == XTK_CTRL_ITEMSVIEW;
}

typedef enum XtkFontWeight
{
	XTK_FONT_THIN        = 100,
	XTK_FONT_EXTRA_LIGHT = 200,
	XTK_FONT_LIGHT       = 300,
	XTK_FONT_REGULAR     = 400,
	XTK_FONT_MEDIUM      = 500,
	XTK_FONT_SEMI_BOLD   = 600,
	XTK_FONT_BOLD        = 700,
	XTK_FONT_EXTRA_BOLD  = 800,
	XTK_FONT_BLACK       = 900,
} XtkFontWeight;

typedef enum XtkTextAlign
{
	XTK_TEXT_LEFT,
	XTK_TEXT_CENTER,
	XTK_TEXT_RIGHT,
	XTK_TEXT_JUSTIFY,
} XtkTextAlign;

typedef enum XtkTextTrim
{
	XTK_TRIM_NONE,
	XTK_TRIM_CHAR,
	XTK_TRIM_CHAR_ELLIPSIS,
	XTK_TRIM_WORD,
	XTK_TRIM_WORD_ELLIPSIS,
} XtkTextTrim;

typedef enum XtkButtonStyle
{
	XTK_BUTTON_STANDARD,
	XTK_BUTTON_SUBTLE,
	XTK_BUTTON_TEXT,
	XTK_BUTTON_ACCENT,
} XtkButtonStyle;

typedef enum XtkTickPlacement
{
	XTK_TICK_INLINE = 0,
	XTK_TICK_TOP_LEFT,
	XTK_TICK_BOTTOM_RIGHT,
	XTK_TICK_OUTSIDE,
	XTK_TICK_NONE,
} XtkTickPlacement;

typedef enum XtkSliderSnap
{
	XTK_SLIDER_SNAP_STEP = 0,
	XTK_SLIDER_SNAP_TICKS,
} XtkSliderSnap;

typedef enum XtkCheckState
{
	XTK_CHECK_UNCHECKED = 0,
	XTK_CHECK_CHECKED,
	XTK_CHECK_INDETERMINATE,
} XtkCheckState;

typedef enum XtkProgressState
{
	XTK_PROGRESS_NORMAL = 0,
	XTK_PROGRESS_PAUSED,
	XTK_PROGRESS_ERROR,
} XtkProgressState;

typedef enum XtkImageStretch
{
	XTK_IMAGE_NONE = 0,
	XTK_IMAGE_FILL,
	XTK_IMAGE_UNIFORM,
	XTK_IMAGE_UNIFORM_TO_FILL,
} XtkImageStretch;

typedef enum XtkBadgeMode
{
	XTK_BADGE_DOT,
	XTK_BADGE_NUMBER,
	XTK_BADGE_ICON,
} XtkBadgeMode;

typedef enum XtkInfoBarSeverity
{
	XTK_INFOBAR_INFORMATIONAL = 0,
	XTK_INFOBAR_SUCCESS,
	XTK_INFOBAR_WARNING,
	XTK_INFOBAR_ERROR,
} XtkInfoBarSeverity;

typedef enum XtkDialogResult
{
	XTK_DIALOG_NONE = 0,
	XTK_DIALOG_PRIMARY,
	XTK_DIALOG_SECONDARY,
} XtkDialogResult;

typedef enum XtkTeachingTipPlacement
{
	XTK_TIP_PLACE_AUTO = 0,
	XTK_TIP_PLACE_TOP,
	XTK_TIP_PLACE_BOTTOM,
	XTK_TIP_PLACE_LEFT,
	XTK_TIP_PLACE_RIGHT,
	XTK_TIP_PLACE_TOP_RIGHT,
	XTK_TIP_PLACE_TOP_LEFT,
	XTK_TIP_PLACE_BOTTOM_RIGHT,
	XTK_TIP_PLACE_BOTTOM_LEFT,
	XTK_TIP_PLACE_LEFT_TOP,
	XTK_TIP_PLACE_LEFT_BOTTOM,
	XTK_TIP_PLACE_RIGHT_TOP,
	XTK_TIP_PLACE_RIGHT_BOTTOM,
	XTK_TIP_PLACE_CENTER,
} XtkTeachingTipPlacement;

typedef enum XtkTeachingTipCloseReason
{
	XTK_TIP_CLOSE_BUTTON = 0,
	XTK_TIP_CLOSE_LIGHT_DISMISS,
	XTK_TIP_CLOSE_PROGRAMMATIC,
} XtkTeachingTipCloseReason;

#endif
