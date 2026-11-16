#ifndef XTK_TYPES_H
#define XTK_TYPES_H

#include <stdint.h>
#include <stdbool.h>
#include <assert.h>

#include "xtk_ids.h"

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

static bool inline xtk_ctrl_islist(XtkCtrlType t) {
	return t == XTK_CTRL_LIST
	    || t == XTK_CTRL_LISTBOX
	    || t == XTK_CTRL_GRIDVIEW
	    || t == XTK_CTRL_REPEATER
	    || t == XTK_CTRL_ITEMSVIEW;
}

typedef enum XtkFontWeight
{
	XTK_FONT_INHERIT     = 0,
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
	XTK_TRIM_PATH_ELLIPSIS,
} XtkTextTrim;

typedef enum XtkDropOperation
{
	XTK_DROP_NONE,
	XTK_DROP_COPY,
	XTK_DROP_MOVE,
	XTK_DROP_LINK,
} XtkDropOperation;

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

typedef enum XtkTeachingTipTail
{
	XTK_TIP_TAIL_AUTO = 0,
	XTK_TIP_TAIL_VISIBLE,
	XTK_TIP_TAIL_COLLAPSED,
} XtkTeachingTipTail;

typedef enum XtkScrollBarIndicator
{
	XTK_SCROLLBAR_INDICATOR_NONE = 0,
	XTK_SCROLLBAR_INDICATOR_TOUCH,
	XTK_SCROLLBAR_INDICATOR_MOUSE,
} XtkScrollBarIndicator;

typedef enum XtkSortDirection
{
	XTK_SORT_NONE = 0,
	XTK_SORT_ASCENDING,
	XTK_SORT_DESCENDING,
} XtkSortDirection;

typedef enum XtkAppBarMode
{
	XTK_APPBAR_COMPACT = 0,
	XTK_APPBAR_MINIMAL,
	XTK_APPBAR_HIDDEN,
} XtkAppBarMode;

typedef enum XtkLabelPosition
{
	XTK_LABEL_BOTTOM = 0,
	XTK_LABEL_RIGHT,
	XTK_LABEL_COLLAPSED,
} XtkLabelPosition;

typedef enum XtkElementLabel
{
	XTK_ELEMENT_LABEL_DEFAULT = 0,
	XTK_ELEMENT_LABEL_COLLAPSED,
} XtkElementLabel;

typedef enum XtkOverflowButton
{
	XTK_OVERFLOW_BUTTON_AUTO = 0,
	XTK_OVERFLOW_BUTTON_VISIBLE,
	XTK_OVERFLOW_BUTTON_COLLAPSED,
} XtkOverflowButton;

typedef enum XtkTeachingTipCloseReason
{
	XTK_TIP_CLOSE_BUTTON = 0,
	XTK_TIP_CLOSE_LIGHT_DISMISS,
	XTK_TIP_CLOSE_PROGRAMMATIC,
} XtkTeachingTipCloseReason;

static_assert(sizeof(XtkFontWeight) == 4, "XtkFontWeight crosses the ABI as int32");
static_assert(sizeof(XtkTextAlign) == 4, "XtkTextAlign crosses the ABI as int32");
static_assert(sizeof(XtkTextTrim) == 4, "XtkTextTrim crosses the ABI as int32");
static_assert(sizeof(XtkButtonStyle) == 4, "XtkButtonStyle crosses the ABI as int32");
static_assert(sizeof(XtkTickPlacement) == 4, "XtkTickPlacement crosses the ABI as int32");
static_assert(sizeof(XtkSliderSnap) == 4, "XtkSliderSnap crosses the ABI as int32");
static_assert(sizeof(XtkCheckState) == 4, "XtkCheckState crosses the ABI as int32");
static_assert(sizeof(XtkProgressState) == 4, "XtkProgressState crosses the ABI as int32");
static_assert(sizeof(XtkImageStretch) == 4, "XtkImageStretch crosses the ABI as int32");
static_assert(sizeof(XtkBadgeMode) == 4, "XtkBadgeMode crosses the ABI as int32");
static_assert(sizeof(XtkInfoBarSeverity) == 4, "XtkInfoBarSeverity crosses the ABI as int32");
static_assert(sizeof(XtkDialogResult) == 4, "XtkDialogResult crosses the ABI as int32");
static_assert(sizeof(XtkTeachingTipPlacement) == 4, "XtkTeachingTipPlacement crosses the ABI as int32");
static_assert(sizeof(XtkTeachingTipTail) == 4, "XtkTeachingTipTail crosses the ABI as int32");
static_assert(sizeof(XtkScrollBarIndicator) == 4, "XtkScrollBarIndicator crosses the ABI as int32");
static_assert(sizeof(XtkSortDirection) == 4, "XtkSortDirection crosses the ABI as int32");
static_assert(sizeof(XtkAppBarMode) == 4, "XtkAppBarMode crosses the ABI as int32");
static_assert(sizeof(XtkLabelPosition) == 4, "XtkLabelPosition crosses the ABI as int32");
static_assert(sizeof(XtkElementLabel) == 4, "XtkElementLabel crosses the ABI as int32");
static_assert(sizeof(XtkOverflowButton) == 4, "XtkOverflowButton crosses the ABI as int32");
static_assert(sizeof(XtkTeachingTipCloseReason) == 4, "XtkTeachingTipCloseReason crosses the ABI as int32");

#endif
