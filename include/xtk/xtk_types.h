/**
 * @file xtk_types.h
 * @brief XTK type definitions: color, control type, and control-specific enums.
 *
 * Platform-agnostic types used by the XTK declarative layer. Backend renderers
 * (fluxent, nexent, luxent) map these to platform-specific equivalents.
 */
#ifndef XTK_TYPES_H
#define XTK_TYPES_H

#include <stdint.h>
#include <stdbool.h>
#include <assert.h> /* portable static_assert: a keyword in C23/C++, a macro in C11/C17 */

#ifdef __cplusplus
extern "C"
{
#endif

/* -------------------------------------------------------------------------
 * Color
 * ---------------------------------------------------------------------- */

/** @brief RGBA color packed as uint32_t (0xRRGGBBAA). */
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

/* -------------------------------------------------------------------------
 * UTF-8 utilities
 * ---------------------------------------------------------------------- */

static int inline xtk_utf8_len(char const *s) {
	int n = 0;
	for (; s && *s; s++)
		if ((*s & 0xc0) != 0x80) n++;
	return n;
}

/* -------------------------------------------------------------------------
 * Control type
 * ---------------------------------------------------------------------- */

typedef enum XtkControlType
{
	XTK_CONTROL_CONTAINER = 0,
	XTK_CONTROL_TEXT,
	XTK_CONTROL_BUTTON,
	XTK_CONTROL_TOGGLE_BUTTON,
	XTK_CONTROL_CHECKBOX,
	XTK_CONTROL_RADIO,
	XTK_CONTROL_SWITCH,
	XTK_CONTROL_SLIDER,
	XTK_CONTROL_TEXT_INPUT,
	XTK_CONTROL_SCROLL,
	XTK_CONTROL_IMAGE,
	XTK_CONTROL_PROGRESS,
	XTK_CONTROL_LIST,
	XTK_CONTROL_TAB,
	XTK_CONTROL_CARD,
	XTK_CONTROL_DIVIDER,
	XTK_CONTROL_CANVAS,
	XTK_CONTROL_PASSWORD_BOX,
	XTK_CONTROL_NUMBER_BOX,
	XTK_CONTROL_HYPERLINK,
	XTK_CONTROL_REPEAT_BUTTON,
	XTK_CONTROL_PROGRESS_RING,
	XTK_CONTROL_INFO_BADGE,
	XTK_CONTROL_TOOLTIP,
	XTK_CONTROL_FLYOUT,
	XTK_CONTROL_MENU_FLYOUT,
	XTK_CONTROL_DROPDOWN_BUTTON,
	XTK_CONTROL_SPLIT_BUTTON,
	XTK_CONTROL_COMBO_BOX,
	XTK_CONTROL_EXPANDER,
	XTK_CONTROL_EXPANDER_HEADER,
	XTK_CONTROL_EXPANDER_CONTENT,
	XTK_CONTROL_INFO_BAR,
	XTK_CONTROL_CONTENT_DIALOG,
	XTK_CONTROL_DIALOG_CONTENT,
	XTK_CONTROL_MENU_BAR,
	XTK_CONTROL_MENU_BAR_ITEM,
	XTK_CONTROL_NAV_VIEW,
	XTK_CONTROL_NAV_VIEW_ITEM,
	XTK_CONTROL_TAB_VIEW,
	XTK_CONTROL_TAB_VIEW_ITEM,
	XTK_CONTROL_LIST_ITEM,
	XTK_CONTROL_LIST_BOX,
	XTK_CONTROL_GRID_VIEW,
	XTK_CONTROL_ITEMS_REPEATER,
	XTK_CONTROL_ITEMS_VIEW,
	XTK_CONTROL_FLIP_VIEW,
	XTK_CONTROL_PIPS_PAGER,
	XTK_CONTROL_AUTO_SUGGEST,
	XTK_CONTROL_TOGGLE_SPLIT_BUTTON,
	XTK_CONTROL_RADIO_BUTTONS,
	XTK_CONTROL_RATING,
	XTK_CONTROL_SELECTOR_BAR,
	XTK_CONTROL_SELECTOR_BAR_ITEM,
	XTK_CONTROL_BREADCRUMB_BAR,
	XTK_CONTROL_BREADCRUMB_ITEM,
	XTK_CONTROL_TEACHING_TIP,
	XTK_CONTROL_TREE_VIEW,
	XTK_CONTROL_TREE_ITEM,
	XTK_CONTROL_REFRESH,
	XTK_CONTROL_PERSON_PICTURE,
	XTK_CONTROL_PAGER,
	XTK_CONTROL_SPLIT_VIEW,
	XTK_CONTROL_SPLIT_VIEW_PANE,
	XTK_CONTROL_SPLIT_VIEW_CONTENT,
	XTK_CONTROL_TITLE_BAR,
	XTK_CONTROL_CUSTOM,
} XtkControlType;

static_assert(XTK_CONTROL_CUSTOM < 256, "XtkControlType must stay byte-storable for backend node stores");

/** @brief True for the four virtualized items-host roots (ListView family). */
static bool inline xtk_is_list_type(XtkControlType t) {
	return t == XTK_CONTROL_LIST || t == XTK_CONTROL_LIST_BOX || t == XTK_CONTROL_GRID_VIEW
	    || t == XTK_CONTROL_ITEMS_REPEATER || t == XTK_CONTROL_ITEMS_VIEW;
}

/* -------------------------------------------------------------------------
 * Text
 * ---------------------------------------------------------------------- */

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

/* -------------------------------------------------------------------------
 * Button
 * ---------------------------------------------------------------------- */

typedef enum XtkButtonStyle
{
	XTK_BUTTON_STANDARD,
	XTK_BUTTON_SUBTLE,
	XTK_BUTTON_TEXT,
	XTK_BUTTON_ACCENT,
} XtkButtonStyle;

/* -------------------------------------------------------------------------
 * Slider
 * ---------------------------------------------------------------------- */

typedef enum XtkTickPlacement
{
	XTK_TICK_INLINE = 0,
	XTK_TICK_TOP_LEFT,
	XTK_TICK_BOTTOM_RIGHT,
	XTK_TICK_OUTSIDE,
	XTK_TICK_NONE,
} XtkTickPlacement;

/* -------------------------------------------------------------------------
 * Image
 * ---------------------------------------------------------------------- */

typedef enum XtkImageStretch
{
	XTK_IMAGE_NONE = 0,
	XTK_IMAGE_FILL,
	XTK_IMAGE_UNIFORM,
	XTK_IMAGE_UNIFORM_TO_FILL,
} XtkImageStretch;

/* -------------------------------------------------------------------------
 * Info badge
 * ---------------------------------------------------------------------- */

typedef enum XtkBadgeMode
{
	XTK_BADGE_DOT,
	XTK_BADGE_NUMBER,
	XTK_BADGE_ICON,
} XtkBadgeMode;

/* -------------------------------------------------------------------------
 * Info bar
 * ---------------------------------------------------------------------- */

typedef enum XtkInfoBarSeverity
{
	XTK_INFOBAR_INFORMATIONAL = 0,
	XTK_INFOBAR_SUCCESS,
	XTK_INFOBAR_WARNING,
	XTK_INFOBAR_ERROR,
} XtkInfoBarSeverity;

/* -------------------------------------------------------------------------
 * Content dialog
 * ---------------------------------------------------------------------- */

typedef enum XtkDialogResult
{
	XTK_DIALOG_NONE = 0,
	XTK_DIALOG_PRIMARY,
	XTK_DIALOG_SECONDARY,
} XtkDialogResult;

/* -------------------------------------------------------------------------
 * Teaching tip
 * ---------------------------------------------------------------------- */

/** @brief WinUI TeachingTipPlacementMode. Zero = Auto. */
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

/** @brief Why a teaching tip closed (WinUI TeachingTipCloseReason). */
typedef enum XtkTeachingTipCloseReason
{
	XTK_TIP_CLOSE_BUTTON = 0,
	XTK_TIP_CLOSE_LIGHT_DISMISS,
	XTK_TIP_CLOSE_PROGRAMMATIC,
} XtkTeachingTipCloseReason;

#ifdef __cplusplus
}
#endif

#endif
