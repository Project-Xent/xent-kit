#include <xtk/xtk_catalog.h>

#define COUNT_OF(a)           (( uint32_t ) (sizeof(a) / sizeof((a) [0])))
#define XTK_MIRROR_CANDIDATES 3u
#define GEOMETRY              (XTK_INVALIDATE_LAYOUT | XTK_INVALIDATE_PAINT | XTK_INVALIDATE_HIT_TEST)
#define CONTENT (XTK_INVALIDATE_LAYOUT | XTK_INVALIDATE_PAINT | XTK_INVALIDATE_SEMANTICS | XTK_INVALIDATE_ACCESS)
#define STATE   (XTK_INVALIDATE_PAINT | XTK_INVALIDATE_HIT_TEST | XTK_INVALIDATE_SEMANTICS | XTK_INVALIDATE_ACCESS)
#define TREE    (GEOMETRY | XTK_INVALIDATE_SEMANTICS | XTK_INVALIDATE_ACCESS)

static XtkPropDesc const properties [XTK_PROP_STANDARD_COUNT] = {
  [XTK_PROP_WIDTH]  = {XTK_PROP_WIDTH,                      "width",                       XTK_PROP_KIND_F32,      0u, GEOMETRY,                                                               XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_HEIGHT] = {XTK_PROP_HEIGHT,                     "height",                      XTK_PROP_KIND_F32,      0u, GEOMETRY,                                                               XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_GROW]   = {XTK_PROP_GROW,                       "grow",                        XTK_PROP_KIND_F32,      0u, XTK_INVALIDATE_LAYOUT,                                                  XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_SHRINK]
  = {XTK_PROP_SHRINK,                     "shrink",                      XTK_PROP_KIND_F32,      0u, XTK_INVALIDATE_LAYOUT,                                                  XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_ALIGN_SELF]
  = {XTK_PROP_ALIGN_SELF,                 "align-self",                  XTK_PROP_KIND_ENUM,     0u, XTK_INVALIDATE_LAYOUT,                                                  XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_MARGIN_LEFT]
  = {XTK_PROP_MARGIN_LEFT,                "margin-left",                 XTK_PROP_KIND_F32,      0u, XTK_INVALIDATE_LAYOUT,                                                  XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_MARGIN_TOP]
  = {XTK_PROP_MARGIN_TOP,                 "margin-top",                  XTK_PROP_KIND_F32,      0u, XTK_INVALIDATE_LAYOUT,                                                  XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_MARGIN_RIGHT]
  = {XTK_PROP_MARGIN_RIGHT,               "margin-right",                XTK_PROP_KIND_F32,      0u, XTK_INVALIDATE_LAYOUT,                                                  XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_MARGIN_BOTTOM]
  = {XTK_PROP_MARGIN_BOTTOM,              "margin-bottom",               XTK_PROP_KIND_F32,      0u, XTK_INVALIDATE_LAYOUT,                                                  XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_TEXT] = {XTK_PROP_TEXT,                       "text",                        XTK_PROP_KIND_STRING,   0u, CONTENT,                                                                XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_TOOLTIP]
  = {XTK_PROP_TOOLTIP,                    "tooltip",                     XTK_PROP_KIND_STRING,   0u, XTK_INVALIDATE_SEMANTICS | XTK_INVALIDATE_ACCESS,                       XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_ENABLED] = {XTK_PROP_ENABLED,                    "enabled",                     XTK_PROP_KIND_BOOL,     0u, STATE,                                                                  XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_ICON]    = {XTK_PROP_ICON,                       "icon",                        XTK_PROP_KIND_STRING,   0u, CONTENT,                                                                XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_ORIENTATION]
  = {XTK_PROP_ORIENTATION,                "orientation",                 XTK_PROP_KIND_ENUM,     0u, XTK_INVALIDATE_LAYOUT,                                                  XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_ALIGN_ITEMS]
  = {XTK_PROP_ALIGN_ITEMS,                "align-items",                 XTK_PROP_KIND_ENUM,     0u, XTK_INVALIDATE_LAYOUT,                                                  XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_JUSTIFY_CONTENT]
  = {XTK_PROP_JUSTIFY_CONTENT,            "justify-content",             XTK_PROP_KIND_ENUM,     0u, XTK_INVALIDATE_LAYOUT,                                                  XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_GAP] = {XTK_PROP_GAP,                        "gap",                         XTK_PROP_KIND_F32,      0u, XTK_INVALIDATE_LAYOUT,                                                  XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_PADDING_LEFT]
  = {XTK_PROP_PADDING_LEFT,               "padding-left",                XTK_PROP_KIND_F32,      0u, XTK_INVALIDATE_LAYOUT,                                                  XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_PADDING_TOP]
  = {XTK_PROP_PADDING_TOP,                "padding-top",                 XTK_PROP_KIND_F32,      0u, XTK_INVALIDATE_LAYOUT,                                                  XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_PADDING_RIGHT]
  = {XTK_PROP_PADDING_RIGHT,              "padding-right",               XTK_PROP_KIND_F32,      0u, XTK_INVALIDATE_LAYOUT,                                                  XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_PADDING_BOTTOM]
  = {XTK_PROP_PADDING_BOTTOM,             "padding-bottom",              XTK_PROP_KIND_F32,      0u, XTK_INVALIDATE_LAYOUT,                                                  XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_FILL] = {XTK_PROP_FILL,                       "fill",                        XTK_PROP_KIND_BOOL,     0u, XTK_INVALIDATE_LAYOUT,                                                  XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_FIT_WIDTH]
  = {XTK_PROP_FIT_WIDTH,                  "fit-width",                   XTK_PROP_KIND_BOOL,     0u, XTK_INVALIDATE_LAYOUT,                                                  XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_FIT_HEIGHT]
  = {XTK_PROP_FIT_HEIGHT,                 "fit-height",                  XTK_PROP_KIND_BOOL,     0u, XTK_INVALIDATE_LAYOUT,                                                  XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_FONT_SIZE] = {XTK_PROP_FONT_SIZE,                  "font-size",                   XTK_PROP_KIND_F32,      0u, CONTENT,                                                                XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_FONT_WEIGHT]
  = {XTK_PROP_FONT_WEIGHT,                "font-weight",                 XTK_PROP_KIND_ENUM,     0u, CONTENT,                                                                XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_TEXT_ALIGN]
  = {XTK_PROP_TEXT_ALIGN,                 "text-align",                  XTK_PROP_KIND_ENUM,     0u, XTK_INVALIDATE_LAYOUT | XTK_INVALIDATE_PAINT,                           XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_FOREGROUND]
  = {XTK_PROP_FOREGROUND,                 "foreground",                  XTK_PROP_KIND_COLOR,    0u, XTK_INVALIDATE_PAINT,                                                   XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_BUTTON_STYLE]
  = {XTK_PROP_BUTTON_STYLE,               "button-style",                XTK_PROP_KIND_ENUM,     0u, XTK_INVALIDATE_LAYOUT | XTK_INVALIDATE_PAINT,                           XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_CHECKED] = {XTK_PROP_CHECKED,                    "checked",                     XTK_PROP_KIND_BOOL,     0u, STATE,                                                                  XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_MIN_F32]
  = {XTK_PROP_MIN_F32,                    "minimum-f32",                 XTK_PROP_KIND_F32,      0u, XTK_INVALIDATE_LAYOUT | XTK_INVALIDATE_PAINT,                           XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_MAX_F32]
  = {XTK_PROP_MAX_F32,                    "maximum-f32",                 XTK_PROP_KIND_F32,      0u, XTK_INVALIDATE_LAYOUT | XTK_INVALIDATE_PAINT,                           XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_VALUE_F32]
  = {XTK_PROP_VALUE_F32,                  "value-f32",                   XTK_PROP_KIND_F32,      0u, XTK_INVALIDATE_PAINT | XTK_INVALIDATE_SEMANTICS,                        XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_STEP_F32]
  = {XTK_PROP_STEP_F32,                   "step-f32",                    XTK_PROP_KIND_F32,      0u, XTK_INVALIDATE_NONE,                                                    XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_PLACEHOLDER]
  = {XTK_PROP_PLACEHOLDER,                "placeholder",                 XTK_PROP_KIND_STRING,   0u, CONTENT,                                                                XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_IMAGE_SOURCE]
  = {XTK_PROP_IMAGE_SOURCE,               "image-source",                XTK_PROP_KIND_RESOURCE, 0u, CONTENT,                                                                XTK_RESOURCE_TYPE_IMAGE  },
  [XTK_PROP_IMAGE_STRETCH]
  = {XTK_PROP_IMAGE_STRETCH,              "image-stretch",               XTK_PROP_KIND_ENUM,     0u, GEOMETRY,                                                               XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_INDETERMINATE]
  = {XTK_PROP_INDETERMINATE,              "indeterminate",               XTK_PROP_KIND_BOOL,     0u, XTK_INVALIDATE_PAINT,                                                   XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_VALUE_F64]
  = {XTK_PROP_VALUE_F64,                  "value-f64",                   XTK_PROP_KIND_F64,      0u, XTK_INVALIDATE_PAINT | XTK_INVALIDATE_SEMANTICS,                        XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_MIN_F64]
  = {XTK_PROP_MIN_F64,                    "minimum-f64",                 XTK_PROP_KIND_F64,      0u, XTK_INVALIDATE_LAYOUT | XTK_INVALIDATE_PAINT,                           XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_MAX_F64]
  = {XTK_PROP_MAX_F64,                    "maximum-f64",                 XTK_PROP_KIND_F64,      0u, XTK_INVALIDATE_LAYOUT | XTK_INVALIDATE_PAINT,                           XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_STEP_F64]
  = {XTK_PROP_STEP_F64,                   "step-f64",                    XTK_PROP_KIND_F64,      0u, XTK_INVALIDATE_NONE,                                                    XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_SELECTED_INDEX]
  = {XTK_PROP_SELECTED_INDEX,             "selected-index",              XTK_PROP_KIND_I32,      0u, STATE,                                                                  XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_SELECTED] = {XTK_PROP_SELECTED,                   "selected",                    XTK_PROP_KIND_BOOL,     0u, STATE,                                                                  XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_ITEM_COUNT]
  = {XTK_PROP_ITEM_COUNT,                 "item-count",                  XTK_PROP_KIND_I32,      0u, XTK_INVALIDATE_LAYOUT,                                                  XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_ITEMS] = {XTK_PROP_ITEMS,                      "items",                       XTK_PROP_KIND_BYTES,    0u, CONTENT,                                                                XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_ITEM_HEIGHT]
  = {XTK_PROP_ITEM_HEIGHT,                "item-height",                 XTK_PROP_KIND_F32,      0u, XTK_INVALIDATE_LAYOUT,                                                  XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_ITEM_WIDTH]
  = {XTK_PROP_ITEM_WIDTH,                 "item-width",                  XTK_PROP_KIND_F32,      0u, XTK_INVALIDATE_LAYOUT,                                                  XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_COLUMN_COUNT]
  = {XTK_PROP_COLUMN_COUNT,               "column-count",                XTK_PROP_KIND_I32,      0u, XTK_INVALIDATE_LAYOUT,                                                  XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_SELECTION_MODE]
  = {XTK_PROP_SELECTION_MODE,             "selection-mode",              XTK_PROP_KIND_ENUM,     0u, STATE,                                                                  XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_ITEM_INVOKED_ENABLED]
  = {XTK_PROP_ITEM_INVOKED_ENABLED,       "item-invoked-enabled",        XTK_PROP_KIND_BOOL,     0u, XTK_INVALIDATE_NONE,                                                    XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_MAX_VISIBLE]
  = {XTK_PROP_MAX_VISIBLE,                "max-visible",                 XTK_PROP_KIND_I32,      0u, GEOMETRY,                                                               XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_NAV_VISIBILITY]
  = {XTK_PROP_NAV_VISIBILITY,             "navigation-visibility",       XTK_PROP_KIND_ENUM,     0u, GEOMETRY,                                                               XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_EXPANDED] = {XTK_PROP_EXPANDED,                   "expanded",                    XTK_PROP_KIND_BOOL,     0u, TREE,                                                                   XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_CONTENT_HEIGHT]
  = {XTK_PROP_CONTENT_HEIGHT,             "content-height",              XTK_PROP_KIND_F32,      0u, GEOMETRY,                                                               XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_OPEN]    = {XTK_PROP_OPEN,                       "open",                        XTK_PROP_KIND_BOOL,     0u, TREE,                                                                   XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_MESSAGE] = {XTK_PROP_MESSAGE,                    "message",                     XTK_PROP_KIND_STRING,   0u, CONTENT,                                                                XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_SEVERITY]
  = {XTK_PROP_SEVERITY,                   "severity",                    XTK_PROP_KIND_ENUM,     0u, XTK_INVALIDATE_PAINT | XTK_INVALIDATE_SEMANTICS,                        XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_CLOSABLE]
  = {XTK_PROP_CLOSABLE,                   "closable",                    XTK_PROP_KIND_BOOL,     0u, STATE | XTK_INVALIDATE_LAYOUT,                                          XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_PULL_DIRECTION]
  = {XTK_PROP_PULL_DIRECTION,             "pull-direction",              XTK_PROP_KIND_ENUM,     0u, STATE,                                                                  XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_VISUALIZER_SIZE]
  = {XTK_PROP_VISUALIZER_SIZE,            "visualizer-size",             XTK_PROP_KIND_F32,      0u, XTK_INVALIDATE_PAINT,                                                   XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_THRESHOLD_RATIO]
  = {XTK_PROP_THRESHOLD_RATIO,            "threshold-ratio",             XTK_PROP_KIND_F32,      0u, XTK_INVALIDATE_PAINT,                                                   XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_REFRESHING] = {XTK_PROP_REFRESHING,                 "refreshing",                  XTK_PROP_KIND_BOOL,     0u, STATE,                                                                  XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_NAV_MODEL]  = {XTK_PROP_NAV_MODEL,                  "nav-model",                   XTK_PROP_KIND_BYTES,    0u, TREE,                                                                   XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_COMPONENT_PROPS]
  = {XTK_PROP_COMPONENT_PROPS,            "component-props",             XTK_PROP_KIND_BYTES,    0u, TREE,                                                                   XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_TICK_FREQUENCY]
  = {XTK_PROP_TICK_FREQUENCY,             "tick-frequency",              XTK_PROP_KIND_F32,      0u, XTK_INVALIDATE_PAINT,                                                   XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_TICK_PLACEMENT]
  = {XTK_PROP_TICK_PLACEMENT,             "tick-placement",              XTK_PROP_KIND_ENUM,     0u, GEOMETRY,                                                               XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_SLIDER_SNAPS_TO]
  = {XTK_PROP_SLIDER_SNAPS_TO,            "slider-snaps-to",             XTK_PROP_KIND_ENUM,     0u, XTK_INVALIDATE_NONE,                                                    XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_SMALL_CHANGE]
  = {XTK_PROP_SMALL_CHANGE,               "small-change",                XTK_PROP_KIND_F32,      0u, XTK_INVALIDATE_NONE,                                                    XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_LARGE_CHANGE]
  = {XTK_PROP_LARGE_CHANGE,               "large-change",                XTK_PROP_KIND_F32,      0u, XTK_INVALIDATE_NONE,                                                    XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_WRAP] = {XTK_PROP_WRAP,                       "wrap",                        XTK_PROP_KIND_ENUM,     0u, XTK_INVALIDATE_LAYOUT,                                                  XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_SUBTITLE] = {XTK_PROP_SUBTITLE,                   "subtitle",                    XTK_PROP_KIND_STRING,   0u, CONTENT,                                                                XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_PRIMARY_TEXT]
  = {XTK_PROP_PRIMARY_TEXT,               "primary-text",                XTK_PROP_KIND_STRING,   0u, CONTENT,                                                                XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_SECONDARY_TEXT]
  = {XTK_PROP_SECONDARY_TEXT,             "secondary-text",              XTK_PROP_KIND_STRING,   0u, CONTENT,                                                                XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_CLOSE_TEXT]
  = {XTK_PROP_CLOSE_TEXT,                 "close-text",                  XTK_PROP_KIND_STRING,   0u, CONTENT,                                                                XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_ACTION_TEXT]
  = {XTK_PROP_ACTION_TEXT,                "action-text",                 XTK_PROP_KIND_STRING,   0u, CONTENT,                                                                XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_PREFIX]   = {XTK_PROP_PREFIX,                     "prefix",                      XTK_PROP_KIND_STRING,   0u, CONTENT,                                                                XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_SUFFIX]   = {XTK_PROP_SUFFIX,                     "suffix",                      XTK_PROP_KIND_STRING,   0u, CONTENT,                                                                XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_INITIALS] = {XTK_PROP_INITIALS,                   "initials",                    XTK_PROP_KIND_STRING,   0u, CONTENT,                                                                XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_BADGE_GLYPH]
  = {XTK_PROP_BADGE_GLYPH,                "badge-glyph",                 XTK_PROP_KIND_STRING,   0u, CONTENT,                                                                XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_BADGE_MODE]
  = {XTK_PROP_BADGE_MODE,                 "badge-mode",                  XTK_PROP_KIND_ENUM,     0u, GEOMETRY,                                                               XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_BADGE_VALUE]
  = {XTK_PROP_BADGE_VALUE,                "badge-value",                 XTK_PROP_KIND_I32,      0u, GEOMETRY,                                                               XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_DISPLAY_MODE]
  = {XTK_PROP_DISPLAY_MODE,               "display-mode",                XTK_PROP_KIND_ENUM,     0u, GEOMETRY,                                                               XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_PLACEMENT] = {XTK_PROP_PLACEMENT,                  "placement",                   XTK_PROP_KIND_ENUM,     0u, GEOMETRY,                                                               XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_TAIL_VISIBILITY]
  = {XTK_PROP_TAIL_VISIBILITY,            "tail-visibility",             XTK_PROP_KIND_ENUM,     0u, GEOMETRY,                                                               XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_FIRST_BUTTON]
  = {XTK_PROP_FIRST_BUTTON,               "first-button",                XTK_PROP_KIND_ENUM,     0u, GEOMETRY,                                                               XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_PREVIOUS_BUTTON]
  = {XTK_PROP_PREVIOUS_BUTTON,            "previous-button",             XTK_PROP_KIND_ENUM,     0u, GEOMETRY,                                                               XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_NEXT_BUTTON]
  = {XTK_PROP_NEXT_BUTTON,                "next-button",                 XTK_PROP_KIND_ENUM,     0u, GEOMETRY,                                                               XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_LAST_BUTTON]
  = {XTK_PROP_LAST_BUTTON,                "last-button",                 XTK_PROP_KIND_ENUM,     0u, GEOMETRY,                                                               XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_PANE_PLACEMENT]
  = {XTK_PROP_PANE_PLACEMENT,             "pane-placement",              XTK_PROP_KIND_ENUM,     0u, GEOMETRY,                                                               XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_ACTION_ACCENT]
  = {XTK_PROP_ACTION_ACCENT,              "action-accent",               XTK_PROP_KIND_BOOL,     0u, XTK_INVALIDATE_PAINT,                                                   XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_UNTARGETED]
  = {XTK_PROP_UNTARGETED,                 "untargeted",                  XTK_PROP_KIND_BOOL,     0u, GEOMETRY,                                                               XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_LIGHT_DISMISS]
  = {XTK_PROP_LIGHT_DISMISS,              "light-dismiss",               XTK_PROP_KIND_BOOL,     0u, STATE,                                                                  XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_IS_GROUP]
  = {XTK_PROP_IS_GROUP,                   "is-group",                    XTK_PROP_KIND_BOOL,     0u, XTK_INVALIDATE_PAINT,                                                   XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_READ_ONLY] = {XTK_PROP_READ_ONLY,                  "read-only",                   XTK_PROP_KIND_BOOL,     0u, STATE,                                                                  XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_CLEAR_ENABLED]
  = {XTK_PROP_CLEAR_ENABLED,              "clear-enabled",               XTK_PROP_KIND_BOOL,     0u, STATE,                                                                  XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_BACK_DISABLED]
  = {XTK_PROP_BACK_DISABLED,              "back-disabled",               XTK_PROP_KIND_BOOL,     0u, STATE,                                                                  XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_INTEGRATE_WINDOW]
  = {XTK_PROP_INTEGRATE_WINDOW,           "integrate-window",            XTK_PROP_KIND_BOOL,     0u, GEOMETRY,                                                               XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_HIDE_SPIN] = {XTK_PROP_HIDE_SPIN,                  "hide-spin",                   XTK_PROP_KIND_BOOL,     0u, GEOMETRY,                                                               XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_SHOW_BACK] = {XTK_PROP_SHOW_BACK,                  "show-back",                   XTK_PROP_KIND_BOOL,     0u, GEOMETRY,                                                               XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_SHOW_PANE_TOGGLE]
  = {XTK_PROP_SHOW_PANE_TOGGLE,           "show-pane-toggle",            XTK_PROP_KIND_BOOL,     0u, GEOMETRY,                                                               XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_OPEN_PANE_LENGTH]
  = {XTK_PROP_OPEN_PANE_LENGTH,           "open-pane-length",            XTK_PROP_KIND_F32,      0u, GEOMETRY,                                                               XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_COMPACT_PANE_LENGTH]
  = {XTK_PROP_COMPACT_PANE_LENGTH,        "compact-pane-length",         XTK_PROP_KIND_F32,      0u, GEOMETRY,                                                               XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_PLACEMENT_MARGIN]
  = {XTK_PROP_PLACEMENT_MARGIN,           "placement-margin",            XTK_PROP_KIND_F32,      0u, GEOMETRY,                                                               XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_PLACEHOLDER_F64]
  = {XTK_PROP_PLACEHOLDER_F64,            "placeholder-f64",             XTK_PROP_KIND_F64,      0u, XTK_INVALIDATE_PAINT,                                                   XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_INITIAL_VALUE]
  = {XTK_PROP_INITIAL_VALUE,              "initial-value",               XTK_PROP_KIND_I32,      0u, XTK_INVALIDATE_NONE,                                                    XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_URL] = {XTK_PROP_URL,                        "url",                         XTK_PROP_KIND_STRING,   0u, XTK_INVALIDATE_NONE,                                                    XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_ADD_VISIBLE]
  = {XTK_PROP_ADD_VISIBLE,                "add-visible",                 XTK_PROP_KIND_BOOL,     0u, GEOMETRY,                                                               XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_VIEWPORT_SIZE]
  = {XTK_PROP_VIEWPORT_SIZE,              "viewport-size",               XTK_PROP_KIND_F64,      0u, XTK_INVALIDATE_PAINT,                                                   XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_INDICATOR_MODE]
  = {XTK_PROP_INDICATOR_MODE,             "indicator-mode",              XTK_PROP_KIND_ENUM,     0u, XTK_INVALIDATE_PAINT,                                                   XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_SHOULD_LOOP]
  = {XTK_PROP_SHOULD_LOOP,                "should-loop",                 XTK_PROP_KIND_BOOL,     0u, XTK_INVALIDATE_LAYOUT,                                                  XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_IS_THREE_STATE]
  = {XTK_PROP_IS_THREE_STATE,             "is-three-state",              XTK_PROP_KIND_BOOL,     0u, STATE,                                                                  XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_PROGRESS_STATE]
  = {XTK_PROP_PROGRESS_STATE,             "progress-state",              XTK_PROP_KIND_ENUM,     0u, XTK_INVALIDATE_PAINT | XTK_INVALIDATE_SEMANTICS,                        XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_IS_RANGE]
  = {XTK_PROP_IS_RANGE,                   "is-range",                    XTK_PROP_KIND_BOOL,     0u, XTK_INVALIDATE_LAYOUT | XTK_INVALIDATE_PAINT,                           XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_RANGE_START]
  = {XTK_PROP_RANGE_START,                "range-start",                 XTK_PROP_KIND_F32,      0u, XTK_INVALIDATE_PAINT | XTK_INVALIDATE_SEMANTICS,                        XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_RANGE_END]
  = {XTK_PROP_RANGE_END,                  "range-end",                   XTK_PROP_KIND_F32,      0u, XTK_INVALIDATE_PAINT | XTK_INVALIDATE_SEMANTICS,                        XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_IS_EDITABLE]
  = {XTK_PROP_IS_EDITABLE,                "is-editable",                 XTK_PROP_KIND_BOOL,     0u, XTK_INVALIDATE_LAYOUT | XTK_INVALIDATE_PAINT,                           XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_HEADER] = {XTK_PROP_HEADER,                     "header",                      XTK_PROP_KIND_STRING,   0u, CONTENT,                                                                XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_DATE]   = {XTK_PROP_DATE,                       "date",                        XTK_PROP_KIND_I32,      0u, CONTENT,                                                                XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_TIME]   = {XTK_PROP_TIME,                       "time",                        XTK_PROP_KIND_I32,      0u, CONTENT,                                                                XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_MIN_YEAR]
  = {XTK_PROP_MIN_YEAR,                   "minimum-year",                XTK_PROP_KIND_I32,      0u, XTK_INVALIDATE_PAINT,                                                   XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_MAX_YEAR]
  = {XTK_PROP_MAX_YEAR,                   "maximum-year",                XTK_PROP_KIND_I32,      0u, XTK_INVALIDATE_PAINT,                                                   XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_MIN_DATE]
  = {XTK_PROP_MIN_DATE,                   "minimum-date",                XTK_PROP_KIND_I32,      0u, XTK_INVALIDATE_PAINT,                                                   XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_MAX_DATE]
  = {XTK_PROP_MAX_DATE,                   "maximum-date",                XTK_PROP_KIND_I32,      0u, XTK_INVALIDATE_PAINT,                                                   XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_FIRST_DAY]
  = {XTK_PROP_FIRST_DAY,                  "first-day-of-week",           XTK_PROP_KIND_I32,      0u, XTK_INVALIDATE_PAINT,                                                   XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_CLOCK] = {XTK_PROP_CLOCK,                      "clock",                       XTK_PROP_KIND_ENUM,     0u, CONTENT,                                                                XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_MINUTE_INCREMENT]
  = {XTK_PROP_MINUTE_INCREMENT,           "minute-increment",            XTK_PROP_KIND_I32,      0u, XTK_INVALIDATE_PAINT,                                                   XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_COLOR]
  = {XTK_PROP_COLOR,                      "color",                       XTK_PROP_KIND_COLOR,    0u, XTK_INVALIDATE_PAINT | XTK_INVALIDATE_SEMANTICS,                        XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_ALPHA_ENABLED]
  = {XTK_PROP_ALPHA_ENABLED,              "alpha-enabled",               XTK_PROP_KIND_BOOL,     0u, GEOMETRY,                                                               XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_MORE_BUTTON_VISIBLE]
  = {XTK_PROP_MORE_BUTTON_VISIBLE,        "more-button-visible",         XTK_PROP_KIND_BOOL,     0u, GEOMETRY,                                                               XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_SPECTRUM]
  = {XTK_PROP_SPECTRUM,                   "spectrum-components",         XTK_PROP_KIND_ENUM,     0u, XTK_INVALIDATE_PAINT,                                                   XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_PROGRESS_ACTIVE]
  = {XTK_PROP_PROGRESS_ACTIVE,            "is-active",                   XTK_PROP_KIND_BOOL,     0u, XTK_INVALIDATE_PAINT | XTK_INVALIDATE_SEMANTICS,                        XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_PROGRESS_BORDER_WIDTH]
  = {XTK_PROP_PROGRESS_BORDER_WIDTH,      "progress-border-width",       XTK_PROP_KIND_F32,      0u, GEOMETRY,                                                               XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_MULTILINE] = {XTK_PROP_MULTILINE,                  "multiline",                   XTK_PROP_KIND_BOOL,     0u, GEOMETRY,                                                               XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_MAX_LINES] = {XTK_PROP_MAX_LINES,                  "max-lines",                   XTK_PROP_KIND_I32,      0u, GEOMETRY,                                                               XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_TEXT_TRIM]
  = {XTK_PROP_TEXT_TRIM,                  "text-trimming",               XTK_PROP_KIND_ENUM,     0u, GEOMETRY,                                                               XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_TEXT_WRAP]
  = {XTK_PROP_TEXT_WRAP,                  "text-wrapping",               XTK_PROP_KIND_BOOL,     0u, GEOMETRY,                                                               XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_SELECTABLE]
  = {XTK_PROP_SELECTABLE,                 "is-text-selection-enabled",   XTK_PROP_KIND_BOOL,     0u, STATE,                                                                  XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_REALIZED_FIRST]
  = {XTK_PROP_REALIZED_FIRST,             "realized-first",              XTK_PROP_KIND_I32,      0u, GEOMETRY,                                                               XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_SCROLL_X]
  = {XTK_PROP_SCROLL_X,                   "horizontal-offset",           XTK_PROP_KIND_F32,      0u, XTK_INVALIDATE_PAINT | XTK_INVALIDATE_HIT_TEST,                         XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_SCROLL_Y]
  = {XTK_PROP_SCROLL_Y,                   "vertical-offset",             XTK_PROP_KIND_F32,      0u, XTK_INVALIDATE_PAINT | XTK_INVALIDATE_HIT_TEST,                         XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_MIN_WIDTH] = {XTK_PROP_MIN_WIDTH,                  "min-width",                   XTK_PROP_KIND_F32,      0u, GEOMETRY,                                                               XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_MAX_WIDTH] = {XTK_PROP_MAX_WIDTH,                  "max-width",                   XTK_PROP_KIND_F32,      0u, GEOMETRY,                                                               XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_RESIZABLE]
  = {XTK_PROP_RESIZABLE,                  "is-resizable",                XTK_PROP_KIND_BOOL,     0u, XTK_INVALIDATE_HIT_TEST,                                                XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_SORT_DIRECTION]
  = {XTK_PROP_SORT_DIRECTION,             "sort-direction",              XTK_PROP_KIND_ENUM,     0u, XTK_INVALIDATE_PAINT | XTK_INVALIDATE_SEMANTICS,                        XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_IS_STICKY] = {XTK_PROP_IS_STICKY,                  "is-sticky",                   XTK_PROP_KIND_BOOL,     0u, STATE,                                                                  XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_CLOSED_DISPLAY_MODE]
  = {XTK_PROP_CLOSED_DISPLAY_MODE,        "closed-display-mode",         XTK_PROP_KIND_ENUM,     0u, GEOMETRY,                                                               XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_DEFAULT_LABEL_POSITION]
  = {XTK_PROP_DEFAULT_LABEL_POSITION,     "default-label-position",      XTK_PROP_KIND_ENUM,     0u, GEOMETRY,                                                               XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_OVERFLOW_BUTTON_VISIBILITY]
  = {XTK_PROP_OVERFLOW_BUTTON_VISIBILITY, "overflow-button-visibility",  XTK_PROP_KIND_ENUM,     0u, GEOMETRY,                                                               XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_DYNAMIC_OVERFLOW]
  = {XTK_PROP_DYNAMIC_OVERFLOW,           "is-dynamic-overflow-enabled", XTK_PROP_KIND_BOOL,     0u, GEOMETRY,                                                               XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_SECONDARY]
  = {XTK_PROP_SECONDARY,                  "is-secondary",                XTK_PROP_KIND_BOOL,     0u, GEOMETRY,                                                               XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_DYNAMIC_OVERFLOW_ORDER]
  = {XTK_PROP_DYNAMIC_OVERFLOW_ORDER,     "dynamic-overflow-order",      XTK_PROP_KIND_I32,      0u, GEOMETRY,                                                               XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_LABEL_POSITION]
  = {XTK_PROP_LABEL_POSITION,             "label-position",              XTK_PROP_KIND_ENUM,     0u, GEOMETRY,                                                               XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_ACCELERATOR_TEXT]
  = {XTK_PROP_ACCELERATOR_TEXT,           "keyboard-accelerator-text",   XTK_PROP_KIND_STRING,   0u, GEOMETRY | XTK_INVALIDATE_PAINT,                                        XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_DROP_OPERATION]
  = {XTK_PROP_DROP_OPERATION,             "accepted-operation",          XTK_PROP_KIND_ENUM,     0u, XTK_INVALIDATE_HIT_TEST,                                                XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_DRAG_TEXT]
  = {XTK_PROP_DRAG_TEXT,                  "drag-text",                   XTK_PROP_KIND_STRING,   0u, XTK_INVALIDATE_HIT_TEST,                                                XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_DRAG_FILES]
  = {XTK_PROP_DRAG_FILES,                 "drag-files",                  XTK_PROP_KIND_STRING,   0u, XTK_INVALIDATE_HIT_TEST,                                                XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_GROUPS]
  = {XTK_PROP_GROUPS,                     "groups",                      XTK_PROP_KIND_BYTES,    0u, XTK_INVALIDATE_LAYOUT,                                                  XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_RECTANGLE_SELECTION]
  = {XTK_PROP_RECTANGLE_SELECTION,        "rectangle-selection",         XTK_PROP_KIND_BOOL,     0u, XTK_INVALIDATE_HIT_TEST,                                                XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_NINE_GRID_LEFT]
  = {XTK_PROP_NINE_GRID_LEFT,             "nine-grid-left",              XTK_PROP_KIND_F32,      0u, XTK_INVALIDATE_PAINT,                                                   XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_NINE_GRID_TOP]
  = {XTK_PROP_NINE_GRID_TOP,              "nine-grid-top",               XTK_PROP_KIND_F32,      0u, XTK_INVALIDATE_PAINT,                                                   XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_NINE_GRID_RIGHT]
  = {XTK_PROP_NINE_GRID_RIGHT,            "nine-grid-right",             XTK_PROP_KIND_F32,      0u, XTK_INVALIDATE_PAINT,                                                   XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_NINE_GRID_BOTTOM]
  = {XTK_PROP_NINE_GRID_BOTTOM,           "nine-grid-bottom",            XTK_PROP_KIND_F32,      0u, XTK_INVALIDATE_PAINT,                                                   XTK_RESOURCE_TYPE_INVALID},
  [XTK_PROP_FLOW_DIRECTION]
  = {XTK_PROP_FLOW_DIRECTION,             "flow-direction",              XTK_PROP_KIND_ENUM,     0u, XTK_INVALIDATE_LAYOUT | XTK_INVALIDATE_PAINT | XTK_INVALIDATE_HIT_TEST, XTK_RESOURCE_TYPE_INVALID},
};

static XtkEventDesc const events [XTK_EVENT_STANDARD_COUNT] = {
  [XTK_EVENT_INVOKE] = {XTK_EVENT_INVOKE,         "invoke",         XTK_EVENT_ROUTE_CAPTURE_BUBBLE, XTK_EVENT_PAYLOAD_NONE      },
  [XTK_EVENT_CHANGE_BOOL]
  = {XTK_EVENT_CHANGE_BOOL,    "change-bool",    XTK_EVENT_ROUTE_CAPTURE_BUBBLE, XTK_EVENT_PAYLOAD_BOOL      },
  [XTK_EVENT_CHANGE_F32] = {XTK_EVENT_CHANGE_F32,     "change-f32",     XTK_EVENT_ROUTE_CAPTURE_BUBBLE, XTK_EVENT_PAYLOAD_F32       },
  [XTK_EVENT_CHANGE_F64] = {XTK_EVENT_CHANGE_F64,     "change-f64",     XTK_EVENT_ROUTE_CAPTURE_BUBBLE, XTK_EVENT_PAYLOAD_F64       },
  [XTK_EVENT_CHANGE_STRING]
  = {XTK_EVENT_CHANGE_STRING,  "change-string",  XTK_EVENT_ROUTE_CAPTURE_BUBBLE, XTK_EVENT_PAYLOAD_STRING    },
  [XTK_EVENT_SELECT] = {XTK_EVENT_SELECT,         "select",         XTK_EVENT_ROUTE_CAPTURE_BUBBLE, XTK_EVENT_PAYLOAD_I32       },
  [XTK_EVENT_CLOSE]  = {XTK_EVENT_CLOSE,          "close",          XTK_EVENT_ROUTE_CAPTURE_BUBBLE, XTK_EVENT_PAYLOAD_I32       },
  [XTK_EVENT_TOGGLE] = {XTK_EVENT_TOGGLE,         "toggle",         XTK_EVENT_ROUTE_CAPTURE_BUBBLE, XTK_EVENT_PAYLOAD_BOOL      },
  [XTK_EVENT_QUERY]  = {XTK_EVENT_QUERY,          "query",          XTK_EVENT_ROUTE_CAPTURE_BUBBLE, XTK_EVENT_PAYLOAD_QUERY     },
  [XTK_EVENT_RATING_CHANGED]
  = {XTK_EVENT_RATING_CHANGED, "rating-changed", XTK_EVENT_ROUTE_CAPTURE_BUBBLE, XTK_EVENT_PAYLOAD_RATING    },
  [XTK_EVENT_REFRESH] = {XTK_EVENT_REFRESH,        "refresh",        XTK_EVENT_ROUTE_CAPTURE_BUBBLE, XTK_EVENT_PAYLOAD_I32       },
  [XTK_EVENT_TREE_EXPAND]
  = {XTK_EVENT_TREE_EXPAND,    "tree-expand",    XTK_EVENT_ROUTE_CAPTURE_BUBBLE, XTK_EVENT_PAYLOAD_INDEX_BOOL},
  [XTK_EVENT_TREE_SELECT]
  = {XTK_EVENT_TREE_SELECT,    "tree-select",    XTK_EVENT_ROUTE_CAPTURE_BUBBLE, XTK_EVENT_PAYLOAD_INDEX_BOOL},
  [XTK_EVENT_CHANGE_I32] = {XTK_EVENT_CHANGE_I32,     "change-i32",     XTK_EVENT_ROUTE_CAPTURE_BUBBLE, XTK_EVENT_PAYLOAD_I32       },
  [XTK_EVENT_CHANGE_RANGE]
  = {XTK_EVENT_CHANGE_RANGE,   "change-range",   XTK_EVENT_ROUTE_CAPTURE_BUBBLE, XTK_EVENT_PAYLOAD_RANGE     },
  [XTK_EVENT_SUBMIT_STRING]
  = {XTK_EVENT_SUBMIT_STRING,  "submit-string",  XTK_EVENT_ROUTE_CAPTURE_BUBBLE, XTK_EVENT_PAYLOAD_STRING    },
  [XTK_EVENT_VALUE_CHANGED]
  = {XTK_EVENT_VALUE_CHANGED,  "value-changed",  XTK_EVENT_ROUTE_CAPTURE_BUBBLE, XTK_EVENT_PAYLOAD_I32       },
  [XTK_EVENT_DATE_SELECT]
  = {XTK_EVENT_DATE_SELECT,    "date-select",    XTK_EVENT_ROUTE_CAPTURE_BUBBLE, XTK_EVENT_PAYLOAD_INDEX_BOOL},
  [XTK_EVENT_REALIZE]    = {XTK_EVENT_REALIZE,        "realize",        XTK_EVENT_ROUTE_TARGET,         XTK_EVENT_PAYLOAD_WINDOW    },
  [XTK_EVENT_SCROLL]     = {XTK_EVENT_SCROLL,         "scroll",         XTK_EVENT_ROUTE_TARGET,         XTK_EVENT_PAYLOAD_SCROLL    },
  [XTK_EVENT_RESIZE]     = {XTK_EVENT_RESIZE,         "resize",         XTK_EVENT_ROUTE_CAPTURE_BUBBLE, XTK_EVENT_PAYLOAD_F32       },
  [XTK_EVENT_FIT]        = {XTK_EVENT_FIT,            "fit",            XTK_EVENT_ROUTE_CAPTURE_BUBBLE, XTK_EVENT_PAYLOAD_NONE      },
  [XTK_EVENT_REORDER]    = {XTK_EVENT_REORDER,        "reorder",        XTK_EVENT_ROUTE_CAPTURE_BUBBLE, XTK_EVENT_PAYLOAD_I32       },
  [XTK_EVENT_OPEN]       = {XTK_EVENT_OPEN,           "open",           XTK_EVENT_ROUTE_CAPTURE_BUBBLE, XTK_EVENT_PAYLOAD_BOOL      },
  [XTK_EVENT_DRAG_HOVER] = {XTK_EVENT_DRAG_HOVER,     "drag-hover",     XTK_EVENT_ROUTE_TARGET,         XTK_EVENT_PAYLOAD_BOOL      },
  [XTK_EVENT_DROP_FILES] = {XTK_EVENT_DROP_FILES,     "drop-files",     XTK_EVENT_ROUTE_TARGET,         XTK_EVENT_PAYLOAD_STRING    },
  [XTK_EVENT_DROP_TEXT]  = {XTK_EVENT_DROP_TEXT,      "drop-text",      XTK_EVENT_ROUTE_TARGET,         XTK_EVENT_PAYLOAD_STRING    },
  [XTK_EVENT_DRAG_COMPLETED]
  = {XTK_EVENT_DRAG_COMPLETED, "drag-completed", XTK_EVENT_ROUTE_TARGET,         XTK_EVENT_PAYLOAD_I32       },
  [XTK_EVENT_IMAGE_OPENED]
  = {XTK_EVENT_IMAGE_OPENED,   "image-opened",   XTK_EVENT_ROUTE_CAPTURE_BUBBLE, XTK_EVENT_PAYLOAD_NONE      },
  [XTK_EVENT_IMAGE_FAILED]
  = {XTK_EVENT_IMAGE_FAILED,   "image-failed",   XTK_EVENT_ROUTE_CAPTURE_BUBBLE, XTK_EVENT_PAYLOAD_NONE      },
};

static XtkPropertyId const mirrors [XTK_EVENT_STANDARD_COUNT][XTK_MIRROR_CANDIDATES] = {
  [XTK_EVENT_CHANGE_BOOL]    = {XTK_PROP_CHECKED},
  [XTK_EVENT_CHANGE_F32]     = {XTK_PROP_VALUE_F32},
  [XTK_EVENT_CHANGE_F64]     = {XTK_PROP_VALUE_F64},
  [XTK_EVENT_CHANGE_STRING]  = {XTK_PROP_TEXT},
  [XTK_EVENT_SELECT]         = {XTK_PROP_SELECTED_INDEX},
  [XTK_EVENT_CLOSE]          = {XTK_PROP_OPEN},
  [XTK_EVENT_TOGGLE]         = {XTK_PROP_EXPANDED},
  [XTK_EVENT_RATING_CHANGED] = {XTK_PROP_VALUE_F64},
  [XTK_EVENT_CHANGE_I32]     = {XTK_PROP_CHECKED, XTK_PROP_INDETERMINATE},
  [XTK_EVENT_CHANGE_RANGE]   = {XTK_PROP_RANGE_START, XTK_PROP_RANGE_END},
  [XTK_EVENT_VALUE_CHANGED]  = {XTK_PROP_DATE, XTK_PROP_TIME, XTK_PROP_COLOR},
  [XTK_EVENT_SCROLL]         = {XTK_PROP_SCROLL_X, XTK_PROP_SCROLL_Y},
  [XTK_EVENT_RESIZE]         = {XTK_PROP_WIDTH},
  [XTK_EVENT_OPEN]           = {XTK_PROP_OPEN},
};

static XtkPropertyId const container_props [] = {
  XTK_PROP_WIDTH,
  XTK_PROP_HEIGHT,
  XTK_PROP_GROW,
  XTK_PROP_SHRINK,
  XTK_PROP_ALIGN_SELF,
  XTK_PROP_MARGIN_LEFT,
  XTK_PROP_MARGIN_TOP,
  XTK_PROP_MARGIN_RIGHT,
  XTK_PROP_MARGIN_BOTTOM,
  XTK_PROP_TOOLTIP,
  XTK_PROP_ORIENTATION,
  XTK_PROP_ALIGN_ITEMS,
  XTK_PROP_JUSTIFY_CONTENT,
  XTK_PROP_GAP,
  XTK_PROP_PADDING_LEFT,
  XTK_PROP_PADDING_TOP,
  XTK_PROP_PADDING_RIGHT,
  XTK_PROP_PADDING_BOTTOM,
  XTK_PROP_FILL,
  XTK_PROP_FIT_WIDTH,
  XTK_PROP_FIT_HEIGHT,
  XTK_PROP_WRAP,
  XTK_PROP_DROP_OPERATION,
  XTK_PROP_DRAG_TEXT,
  XTK_PROP_DRAG_FILES,
  XTK_PROP_FLOW_DIRECTION,
};
static XtkEventId const container_events [] = {
  XTK_EVENT_DRAG_HOVER,
  XTK_EVENT_DROP_FILES,
  XTK_EVENT_DROP_TEXT,
  XTK_EVENT_DRAG_COMPLETED,
};
static XtkPropertyId const text_props [] = {
  XTK_PROP_WIDTH,
  XTK_PROP_HEIGHT,
  XTK_PROP_GROW,
  XTK_PROP_ALIGN_SELF,
  XTK_PROP_MARGIN_LEFT,
  XTK_PROP_MARGIN_TOP,
  XTK_PROP_MARGIN_RIGHT,
  XTK_PROP_MARGIN_BOTTOM,
  XTK_PROP_TEXT,
  XTK_PROP_TOOLTIP,
  XTK_PROP_FONT_SIZE,
  XTK_PROP_FONT_WEIGHT,
  XTK_PROP_TEXT_ALIGN,
  XTK_PROP_FOREGROUND,
  XTK_PROP_MAX_LINES,
  XTK_PROP_TEXT_TRIM,
  XTK_PROP_TEXT_WRAP,
  XTK_PROP_SELECTABLE,
};
static XtkPropertyId const button_props [] = {
  XTK_PROP_WIDTH,
  XTK_PROP_HEIGHT,
  XTK_PROP_GROW,
  XTK_PROP_ALIGN_SELF,
  XTK_PROP_MARGIN_LEFT,
  XTK_PROP_MARGIN_TOP,
  XTK_PROP_MARGIN_RIGHT,
  XTK_PROP_MARGIN_BOTTOM,
  XTK_PROP_TEXT,
  XTK_PROP_TOOLTIP,
  XTK_PROP_ENABLED,
  XTK_PROP_ICON,
  XTK_PROP_BUTTON_STYLE,
};
static XtkEventId const button_events [] = {
  XTK_EVENT_INVOKE,
};
static XtkPropertyId const toggle_props [] = {
  XTK_PROP_WIDTH,
  XTK_PROP_HEIGHT,
  XTK_PROP_GROW,
  XTK_PROP_ALIGN_SELF,
  XTK_PROP_MARGIN_LEFT,
  XTK_PROP_MARGIN_TOP,
  XTK_PROP_MARGIN_RIGHT,
  XTK_PROP_MARGIN_BOTTOM,
  XTK_PROP_TEXT,
  XTK_PROP_TOOLTIP,
  XTK_PROP_ENABLED,
  XTK_PROP_CHECKED,
  XTK_PROP_ICON,
};
static XtkEventId const toggle_events [] = {
  XTK_EVENT_CHANGE_BOOL,
};
static XtkPropertyId const checkbox_props [] = {
  XTK_PROP_WIDTH,
  XTK_PROP_HEIGHT,
  XTK_PROP_GROW,
  XTK_PROP_ALIGN_SELF,
  XTK_PROP_MARGIN_LEFT,
  XTK_PROP_MARGIN_TOP,
  XTK_PROP_MARGIN_RIGHT,
  XTK_PROP_MARGIN_BOTTOM,
  XTK_PROP_TEXT,
  XTK_PROP_TOOLTIP,
  XTK_PROP_ENABLED,
  XTK_PROP_CHECKED,
  XTK_PROP_INDETERMINATE,
  XTK_PROP_IS_THREE_STATE,
  XTK_PROP_ICON,
};
static XtkEventId const checkbox_events [] = {
  XTK_EVENT_CHANGE_BOOL,
  XTK_EVENT_CHANGE_I32,
};
static XtkPropertyId const radio_props [] = {
  XTK_PROP_WIDTH,
  XTK_PROP_HEIGHT,
  XTK_PROP_GROW,
  XTK_PROP_ALIGN_SELF,
  XTK_PROP_MARGIN_LEFT,
  XTK_PROP_MARGIN_TOP,
  XTK_PROP_MARGIN_RIGHT,
  XTK_PROP_MARGIN_BOTTOM,
  XTK_PROP_TEXT,
  XTK_PROP_TOOLTIP,
  XTK_PROP_ENABLED,
  XTK_PROP_CHECKED,
  XTK_PROP_ICON,
};
static XtkEventId const radio_events [] = {
  XTK_EVENT_CHANGE_BOOL,
};
static XtkPropertyId const switch_props [] = {
  XTK_PROP_WIDTH,
  XTK_PROP_HEIGHT,
  XTK_PROP_GROW,
  XTK_PROP_ALIGN_SELF,
  XTK_PROP_MARGIN_LEFT,
  XTK_PROP_MARGIN_TOP,
  XTK_PROP_MARGIN_RIGHT,
  XTK_PROP_MARGIN_BOTTOM,
  XTK_PROP_TEXT,
  XTK_PROP_TOOLTIP,
  XTK_PROP_ENABLED,
  XTK_PROP_CHECKED,
  XTK_PROP_ICON,
};
static XtkEventId const switch_events [] = {
  XTK_EVENT_CHANGE_BOOL,
};
static XtkPropertyId const slider_props [] = {
  XTK_PROP_WIDTH,
  XTK_PROP_HEIGHT,
  XTK_PROP_GROW,
  XTK_PROP_ALIGN_SELF,
  XTK_PROP_MARGIN_LEFT,
  XTK_PROP_MARGIN_TOP,
  XTK_PROP_MARGIN_RIGHT,
  XTK_PROP_MARGIN_BOTTOM,
  XTK_PROP_TOOLTIP,
  XTK_PROP_ENABLED,
  XTK_PROP_MIN_F32,
  XTK_PROP_MAX_F32,
  XTK_PROP_VALUE_F32,
  XTK_PROP_STEP_F32,
  XTK_PROP_TICK_FREQUENCY,
  XTK_PROP_TICK_PLACEMENT,
  XTK_PROP_SLIDER_SNAPS_TO,
  XTK_PROP_SMALL_CHANGE,
  XTK_PROP_LARGE_CHANGE,
  XTK_PROP_ORIENTATION,
  XTK_PROP_IS_RANGE,
  XTK_PROP_RANGE_START,
  XTK_PROP_RANGE_END,
};
static XtkEventId const slider_events [] = {
  XTK_EVENT_CHANGE_F32,
  XTK_EVENT_CHANGE_RANGE,
};
static XtkPropertyId const textbox_props [] = {
  XTK_PROP_WIDTH,
  XTK_PROP_HEIGHT,
  XTK_PROP_GROW,
  XTK_PROP_ALIGN_SELF,
  XTK_PROP_MARGIN_LEFT,
  XTK_PROP_MARGIN_TOP,
  XTK_PROP_MARGIN_RIGHT,
  XTK_PROP_MARGIN_BOTTOM,
  XTK_PROP_TEXT,
  XTK_PROP_TOOLTIP,
  XTK_PROP_ENABLED,
  XTK_PROP_PLACEHOLDER,
  XTK_PROP_MULTILINE,
  XTK_PROP_READ_ONLY,
};
static XtkEventId const textbox_events [] = {
  XTK_EVENT_CHANGE_STRING,
};
static XtkPropertyId const scroll_props [] = {
  XTK_PROP_WIDTH,
  XTK_PROP_HEIGHT,
  XTK_PROP_GROW,
  XTK_PROP_SHRINK,
  XTK_PROP_ALIGN_SELF,
  XTK_PROP_MARGIN_LEFT,
  XTK_PROP_MARGIN_TOP,
  XTK_PROP_MARGIN_RIGHT,
  XTK_PROP_MARGIN_BOTTOM,
  XTK_PROP_TOOLTIP,
  XTK_PROP_ORIENTATION,
  XTK_PROP_ALIGN_ITEMS,
  XTK_PROP_JUSTIFY_CONTENT,
  XTK_PROP_GAP,
  XTK_PROP_PADDING_LEFT,
  XTK_PROP_PADDING_TOP,
  XTK_PROP_PADDING_RIGHT,
  XTK_PROP_PADDING_BOTTOM,
  XTK_PROP_FILL,
  XTK_PROP_FIT_WIDTH,
  XTK_PROP_FIT_HEIGHT,
  XTK_PROP_WRAP,
  XTK_PROP_SCROLL_X,
  XTK_PROP_SCROLL_Y,
};
static XtkEventId const scroll_events [] = {
  XTK_EVENT_SCROLL,
};
static XtkPropertyId const image_props [] = {
  XTK_PROP_WIDTH,
  XTK_PROP_HEIGHT,
  XTK_PROP_GROW,
  XTK_PROP_ALIGN_SELF,
  XTK_PROP_MARGIN_LEFT,
  XTK_PROP_MARGIN_TOP,
  XTK_PROP_MARGIN_RIGHT,
  XTK_PROP_MARGIN_BOTTOM,
  XTK_PROP_TOOLTIP,
  XTK_PROP_IMAGE_SOURCE,
  XTK_PROP_IMAGE_STRETCH,
  XTK_PROP_NINE_GRID_LEFT,
  XTK_PROP_NINE_GRID_TOP,
  XTK_PROP_NINE_GRID_RIGHT,
  XTK_PROP_NINE_GRID_BOTTOM,
};
static XtkEventId const image_events [] = {
  XTK_EVENT_IMAGE_OPENED,
  XTK_EVENT_IMAGE_FAILED,
};
static XtkPropertyId const progress_props [] = {
  XTK_PROP_WIDTH,
  XTK_PROP_HEIGHT,
  XTK_PROP_GROW,
  XTK_PROP_ALIGN_SELF,
  XTK_PROP_MARGIN_LEFT,
  XTK_PROP_MARGIN_TOP,
  XTK_PROP_MARGIN_RIGHT,
  XTK_PROP_MARGIN_BOTTOM,
  XTK_PROP_TOOLTIP,
  XTK_PROP_MIN_F32,
  XTK_PROP_MAX_F32,
  XTK_PROP_VALUE_F32,
  XTK_PROP_INDETERMINATE,
  XTK_PROP_PROGRESS_STATE,
  XTK_PROP_PADDING_LEFT,
  XTK_PROP_PADDING_TOP,
  XTK_PROP_PADDING_RIGHT,
  XTK_PROP_PADDING_BOTTOM,
  XTK_PROP_PROGRESS_BORDER_WIDTH,
};
static XtkPropertyId const list_props [] = {
  XTK_PROP_WIDTH,
  XTK_PROP_HEIGHT,
  XTK_PROP_GROW,
  XTK_PROP_ALIGN_SELF,
  XTK_PROP_MARGIN_LEFT,
  XTK_PROP_MARGIN_TOP,
  XTK_PROP_MARGIN_RIGHT,
  XTK_PROP_MARGIN_BOTTOM,
  XTK_PROP_TOOLTIP,
  XTK_PROP_ENABLED,
  XTK_PROP_SELECTED_INDEX,
  XTK_PROP_ITEM_COUNT,
  XTK_PROP_ITEM_HEIGHT,
  XTK_PROP_ITEM_WIDTH,
  XTK_PROP_COLUMN_COUNT,
  XTK_PROP_SELECTION_MODE,
  XTK_PROP_REALIZED_FIRST,
  XTK_PROP_RECTANGLE_SELECTION,
  XTK_PROP_GROUPS,
};
static XtkEventId const list_events [] = {
  XTK_EVENT_SELECT,
  XTK_EVENT_INVOKE,
  XTK_EVENT_REALIZE,
};
static XtkPropertyId const tab_props [] = {
  XTK_PROP_WIDTH,
  XTK_PROP_HEIGHT,
  XTK_PROP_GROW,
  XTK_PROP_SHRINK,
  XTK_PROP_ALIGN_SELF,
  XTK_PROP_MARGIN_LEFT,
  XTK_PROP_MARGIN_TOP,
  XTK_PROP_MARGIN_RIGHT,
  XTK_PROP_MARGIN_BOTTOM,
  XTK_PROP_TOOLTIP,
};
static XtkPropertyId const card_props [] = {
  XTK_PROP_WIDTH,
  XTK_PROP_HEIGHT,
  XTK_PROP_GROW,
  XTK_PROP_SHRINK,
  XTK_PROP_ALIGN_SELF,
  XTK_PROP_MARGIN_LEFT,
  XTK_PROP_MARGIN_TOP,
  XTK_PROP_MARGIN_RIGHT,
  XTK_PROP_MARGIN_BOTTOM,
  XTK_PROP_TOOLTIP,
  XTK_PROP_ORIENTATION,
  XTK_PROP_ALIGN_ITEMS,
  XTK_PROP_JUSTIFY_CONTENT,
  XTK_PROP_GAP,
  XTK_PROP_PADDING_LEFT,
  XTK_PROP_PADDING_TOP,
  XTK_PROP_PADDING_RIGHT,
  XTK_PROP_PADDING_BOTTOM,
  XTK_PROP_FILL,
  XTK_PROP_FIT_WIDTH,
  XTK_PROP_FIT_HEIGHT,
  XTK_PROP_WRAP,
  XTK_PROP_DROP_OPERATION,
  XTK_PROP_DRAG_TEXT,
  XTK_PROP_DRAG_FILES,
  XTK_PROP_FLOW_DIRECTION,
};
static XtkEventId const card_events [] = {
  XTK_EVENT_DRAG_HOVER,
  XTK_EVENT_DROP_FILES,
  XTK_EVENT_DROP_TEXT,
  XTK_EVENT_DRAG_COMPLETED,
};
static XtkPropertyId const divider_props [] = {
  XTK_PROP_WIDTH,
  XTK_PROP_HEIGHT,
  XTK_PROP_GROW,
  XTK_PROP_SHRINK,
  XTK_PROP_ALIGN_SELF,
  XTK_PROP_MARGIN_LEFT,
  XTK_PROP_MARGIN_TOP,
  XTK_PROP_MARGIN_RIGHT,
  XTK_PROP_MARGIN_BOTTOM,
  XTK_PROP_TOOLTIP,
};
static XtkPropertyId const canvas_props [] = {
  XTK_PROP_WIDTH,
  XTK_PROP_HEIGHT,
  XTK_PROP_GROW,
  XTK_PROP_SHRINK,
  XTK_PROP_ALIGN_SELF,
  XTK_PROP_MARGIN_LEFT,
  XTK_PROP_MARGIN_TOP,
  XTK_PROP_MARGIN_RIGHT,
  XTK_PROP_MARGIN_BOTTOM,
  XTK_PROP_TOOLTIP,
};
static XtkPropertyId const password_props [] = {
  XTK_PROP_WIDTH,
  XTK_PROP_HEIGHT,
  XTK_PROP_GROW,
  XTK_PROP_ALIGN_SELF,
  XTK_PROP_MARGIN_LEFT,
  XTK_PROP_MARGIN_TOP,
  XTK_PROP_MARGIN_RIGHT,
  XTK_PROP_MARGIN_BOTTOM,
  XTK_PROP_TEXT,
  XTK_PROP_TOOLTIP,
  XTK_PROP_ENABLED,
  XTK_PROP_PLACEHOLDER,
};
static XtkEventId const password_events [] = {
  XTK_EVENT_CHANGE_STRING,
};
static XtkPropertyId const number_props [] = {
  XTK_PROP_WIDTH,
  XTK_PROP_HEIGHT,
  XTK_PROP_GROW,
  XTK_PROP_ALIGN_SELF,
  XTK_PROP_MARGIN_LEFT,
  XTK_PROP_MARGIN_TOP,
  XTK_PROP_MARGIN_RIGHT,
  XTK_PROP_MARGIN_BOTTOM,
  XTK_PROP_TOOLTIP,
  XTK_PROP_ENABLED,
  XTK_PROP_VALUE_F64,
  XTK_PROP_MIN_F64,
  XTK_PROP_MAX_F64,
  XTK_PROP_STEP_F64,
  XTK_PROP_HIDE_SPIN,
};
static XtkEventId const number_events [] = {
  XTK_EVENT_CHANGE_F64,
};
static XtkPropertyId const link_props [] = {
  XTK_PROP_WIDTH,
  XTK_PROP_HEIGHT,
  XTK_PROP_GROW,
  XTK_PROP_ALIGN_SELF,
  XTK_PROP_MARGIN_LEFT,
  XTK_PROP_MARGIN_TOP,
  XTK_PROP_MARGIN_RIGHT,
  XTK_PROP_MARGIN_BOTTOM,
  XTK_PROP_TEXT,
  XTK_PROP_TOOLTIP,
  XTK_PROP_ENABLED,
  XTK_PROP_URL,
};
static XtkEventId const link_events [] = {
  XTK_EVENT_INVOKE,
};
static XtkPropertyId const repeat_props [] = {
  XTK_PROP_WIDTH,
  XTK_PROP_HEIGHT,
  XTK_PROP_GROW,
  XTK_PROP_ALIGN_SELF,
  XTK_PROP_MARGIN_LEFT,
  XTK_PROP_MARGIN_TOP,
  XTK_PROP_MARGIN_RIGHT,
  XTK_PROP_MARGIN_BOTTOM,
  XTK_PROP_TEXT,
  XTK_PROP_TOOLTIP,
  XTK_PROP_ENABLED,
  XTK_PROP_ICON,
  XTK_PROP_BUTTON_STYLE,
};
static XtkEventId const repeat_events [] = {
  XTK_EVENT_INVOKE,
};
static XtkPropertyId const progressring_props [] = {
  XTK_PROP_WIDTH,
  XTK_PROP_HEIGHT,
  XTK_PROP_GROW,
  XTK_PROP_ALIGN_SELF,
  XTK_PROP_MARGIN_LEFT,
  XTK_PROP_MARGIN_TOP,
  XTK_PROP_MARGIN_RIGHT,
  XTK_PROP_MARGIN_BOTTOM,
  XTK_PROP_TOOLTIP,
  XTK_PROP_MIN_F32,
  XTK_PROP_MAX_F32,
  XTK_PROP_VALUE_F32,
  XTK_PROP_INDETERMINATE,
  XTK_PROP_PROGRESS_STATE,
  XTK_PROP_PROGRESS_ACTIVE,
};
static XtkPropertyId const badge_props [] = {
  XTK_PROP_WIDTH,
  XTK_PROP_HEIGHT,
  XTK_PROP_GROW,
  XTK_PROP_SHRINK,
  XTK_PROP_ALIGN_SELF,
  XTK_PROP_MARGIN_LEFT,
  XTK_PROP_MARGIN_TOP,
  XTK_PROP_MARGIN_RIGHT,
  XTK_PROP_MARGIN_BOTTOM,
  XTK_PROP_TOOLTIP,
  XTK_PROP_BADGE_MODE,
  XTK_PROP_BADGE_VALUE,
  XTK_PROP_ICON,
};
static XtkPropertyId const tooltip_props [] = {
  XTK_PROP_WIDTH,
  XTK_PROP_HEIGHT,
  XTK_PROP_GROW,
  XTK_PROP_ALIGN_SELF,
  XTK_PROP_MARGIN_LEFT,
  XTK_PROP_MARGIN_TOP,
  XTK_PROP_MARGIN_RIGHT,
  XTK_PROP_MARGIN_BOTTOM,
  XTK_PROP_TEXT,
  XTK_PROP_TOOLTIP,
  XTK_PROP_OPEN,
  XTK_PROP_ENABLED,
};
static XtkPropertyId const flyout_props [] = {
  XTK_PROP_WIDTH,
  XTK_PROP_HEIGHT,
  XTK_PROP_GROW,
  XTK_PROP_ALIGN_SELF,
  XTK_PROP_MARGIN_LEFT,
  XTK_PROP_MARGIN_TOP,
  XTK_PROP_MARGIN_RIGHT,
  XTK_PROP_MARGIN_BOTTOM,
  XTK_PROP_TEXT,
  XTK_PROP_TOOLTIP,
  XTK_PROP_OPEN,
  XTK_PROP_ENABLED,
};
static XtkPropertyId const menufly_props [] = {
  XTK_PROP_WIDTH,
  XTK_PROP_HEIGHT,
  XTK_PROP_GROW,
  XTK_PROP_ALIGN_SELF,
  XTK_PROP_MARGIN_LEFT,
  XTK_PROP_MARGIN_TOP,
  XTK_PROP_MARGIN_RIGHT,
  XTK_PROP_MARGIN_BOTTOM,
  XTK_PROP_TEXT,
  XTK_PROP_TOOLTIP,
  XTK_PROP_OPEN,
  XTK_PROP_ENABLED,
};
static XtkPropertyId const dropdown_props [] = {
  XTK_PROP_WIDTH,
  XTK_PROP_HEIGHT,
  XTK_PROP_GROW,
  XTK_PROP_ALIGN_SELF,
  XTK_PROP_MARGIN_LEFT,
  XTK_PROP_MARGIN_TOP,
  XTK_PROP_MARGIN_RIGHT,
  XTK_PROP_MARGIN_BOTTOM,
  XTK_PROP_TEXT,
  XTK_PROP_TOOLTIP,
  XTK_PROP_ENABLED,
  XTK_PROP_ICON,
  XTK_PROP_BUTTON_STYLE,
};
static XtkEventId const dropdown_events [] = {
  XTK_EVENT_INVOKE,
};
static XtkPropertyId const split_props [] = {
  XTK_PROP_WIDTH,
  XTK_PROP_HEIGHT,
  XTK_PROP_GROW,
  XTK_PROP_ALIGN_SELF,
  XTK_PROP_MARGIN_LEFT,
  XTK_PROP_MARGIN_TOP,
  XTK_PROP_MARGIN_RIGHT,
  XTK_PROP_MARGIN_BOTTOM,
  XTK_PROP_TEXT,
  XTK_PROP_TOOLTIP,
  XTK_PROP_ENABLED,
  XTK_PROP_ICON,
  XTK_PROP_BUTTON_STYLE,
};
static XtkEventId const split_events [] = {
  XTK_EVENT_INVOKE,
};
static XtkPropertyId const combo_props [] = {
  XTK_PROP_WIDTH,
  XTK_PROP_HEIGHT,
  XTK_PROP_GROW,
  XTK_PROP_ALIGN_SELF,
  XTK_PROP_MARGIN_LEFT,
  XTK_PROP_MARGIN_TOP,
  XTK_PROP_MARGIN_RIGHT,
  XTK_PROP_MARGIN_BOTTOM,
  XTK_PROP_TOOLTIP,
  XTK_PROP_ENABLED,
  XTK_PROP_PLACEHOLDER,
  XTK_PROP_SELECTED_INDEX,
  XTK_PROP_TEXT,
  XTK_PROP_IS_EDITABLE,
  XTK_PROP_ITEMS,
};
static XtkEventId const combo_events [] = {
  XTK_EVENT_SELECT,
  XTK_EVENT_INVOKE,
  XTK_EVENT_SUBMIT_STRING,
};
static XtkPropertyId const expander_props [] = {
  XTK_PROP_WIDTH,
  XTK_PROP_HEIGHT,
  XTK_PROP_GROW,
  XTK_PROP_ALIGN_SELF,
  XTK_PROP_MARGIN_LEFT,
  XTK_PROP_MARGIN_TOP,
  XTK_PROP_MARGIN_RIGHT,
  XTK_PROP_MARGIN_BOTTOM,
  XTK_PROP_TEXT,
  XTK_PROP_TOOLTIP,
  XTK_PROP_EXPANDED,
  XTK_PROP_CONTENT_HEIGHT,
};
static XtkEventId const expander_events [] = {
  XTK_EVENT_TOGGLE,
};
static XtkPropertyId const exphead_props [] = {
  XTK_PROP_WIDTH,
  XTK_PROP_HEIGHT,
  XTK_PROP_GROW,
  XTK_PROP_ALIGN_SELF,
  XTK_PROP_MARGIN_LEFT,
  XTK_PROP_MARGIN_TOP,
  XTK_PROP_MARGIN_RIGHT,
  XTK_PROP_MARGIN_BOTTOM,
  XTK_PROP_TEXT,
  XTK_PROP_TOOLTIP,
  XTK_PROP_ICON,
  XTK_PROP_ENABLED,
  XTK_PROP_SELECTED,
  XTK_PROP_EXPANDED,
};
static XtkPropertyId const expbody_props [] = {
  XTK_PROP_WIDTH,
  XTK_PROP_HEIGHT,
  XTK_PROP_GROW,
  XTK_PROP_SHRINK,
  XTK_PROP_ALIGN_SELF,
  XTK_PROP_MARGIN_LEFT,
  XTK_PROP_MARGIN_TOP,
  XTK_PROP_MARGIN_RIGHT,
  XTK_PROP_MARGIN_BOTTOM,
  XTK_PROP_TOOLTIP,
  XTK_PROP_ORIENTATION,
  XTK_PROP_ALIGN_ITEMS,
  XTK_PROP_JUSTIFY_CONTENT,
  XTK_PROP_GAP,
  XTK_PROP_PADDING_LEFT,
  XTK_PROP_PADDING_TOP,
  XTK_PROP_PADDING_RIGHT,
  XTK_PROP_PADDING_BOTTOM,
  XTK_PROP_FILL,
  XTK_PROP_FIT_WIDTH,
  XTK_PROP_FIT_HEIGHT,
  XTK_PROP_WRAP,
  XTK_PROP_DROP_OPERATION,
  XTK_PROP_DRAG_TEXT,
  XTK_PROP_DRAG_FILES,
  XTK_PROP_FLOW_DIRECTION,
};
static XtkEventId const expbody_events [] = {
  XTK_EVENT_DRAG_HOVER,
  XTK_EVENT_DROP_FILES,
  XTK_EVENT_DROP_TEXT,
  XTK_EVENT_DRAG_COMPLETED,
};
static XtkPropertyId const infobar_props [] = {
  XTK_PROP_WIDTH,
  XTK_PROP_HEIGHT,
  XTK_PROP_GROW,
  XTK_PROP_ALIGN_SELF,
  XTK_PROP_MARGIN_LEFT,
  XTK_PROP_MARGIN_TOP,
  XTK_PROP_MARGIN_RIGHT,
  XTK_PROP_MARGIN_BOTTOM,
  XTK_PROP_TEXT,
  XTK_PROP_MESSAGE,
  XTK_PROP_TOOLTIP,
  XTK_PROP_SEVERITY,
  XTK_PROP_CLOSABLE,
};
static XtkEventId const infobar_events [] = {
  XTK_EVENT_CLOSE,
};
static XtkPropertyId const dialog_props [] = {
  XTK_PROP_WIDTH,
  XTK_PROP_HEIGHT,
  XTK_PROP_GROW,
  XTK_PROP_SHRINK,
  XTK_PROP_ALIGN_SELF,
  XTK_PROP_MARGIN_LEFT,
  XTK_PROP_MARGIN_TOP,
  XTK_PROP_MARGIN_RIGHT,
  XTK_PROP_MARGIN_BOTTOM,
  XTK_PROP_TOOLTIP,
  XTK_PROP_TEXT,
  XTK_PROP_PRIMARY_TEXT,
  XTK_PROP_SECONDARY_TEXT,
  XTK_PROP_CLOSE_TEXT,
  XTK_PROP_CONTENT_HEIGHT,
  XTK_PROP_OPEN,
};
static XtkEventId const dialog_events [] = {
  XTK_EVENT_CLOSE,
  XTK_EVENT_INVOKE,
};
static XtkPropertyId const dialogbody_props [] = {
  XTK_PROP_WIDTH,
  XTK_PROP_HEIGHT,
  XTK_PROP_GROW,
  XTK_PROP_SHRINK,
  XTK_PROP_ALIGN_SELF,
  XTK_PROP_MARGIN_LEFT,
  XTK_PROP_MARGIN_TOP,
  XTK_PROP_MARGIN_RIGHT,
  XTK_PROP_MARGIN_BOTTOM,
  XTK_PROP_TOOLTIP,
  XTK_PROP_ORIENTATION,
  XTK_PROP_ALIGN_ITEMS,
  XTK_PROP_JUSTIFY_CONTENT,
  XTK_PROP_GAP,
  XTK_PROP_PADDING_LEFT,
  XTK_PROP_PADDING_TOP,
  XTK_PROP_PADDING_RIGHT,
  XTK_PROP_PADDING_BOTTOM,
  XTK_PROP_FILL,
  XTK_PROP_FIT_WIDTH,
  XTK_PROP_FIT_HEIGHT,
  XTK_PROP_WRAP,
  XTK_PROP_DROP_OPERATION,
  XTK_PROP_DRAG_TEXT,
  XTK_PROP_DRAG_FILES,
  XTK_PROP_FLOW_DIRECTION,
};
static XtkEventId const dialogbody_events [] = {
  XTK_EVENT_DRAG_HOVER,
  XTK_EVENT_DROP_FILES,
  XTK_EVENT_DROP_TEXT,
  XTK_EVENT_DRAG_COMPLETED,
};
static XtkPropertyId const menubar_props [] = {
  XTK_PROP_WIDTH,
  XTK_PROP_HEIGHT,
  XTK_PROP_GROW,
  XTK_PROP_SHRINK,
  XTK_PROP_ALIGN_SELF,
  XTK_PROP_MARGIN_LEFT,
  XTK_PROP_MARGIN_TOP,
  XTK_PROP_MARGIN_RIGHT,
  XTK_PROP_MARGIN_BOTTOM,
  XTK_PROP_TOOLTIP,
};
static XtkPropertyId const menuitem_props [] = {
  XTK_PROP_WIDTH,
  XTK_PROP_HEIGHT,
  XTK_PROP_GROW,
  XTK_PROP_ALIGN_SELF,
  XTK_PROP_MARGIN_LEFT,
  XTK_PROP_MARGIN_TOP,
  XTK_PROP_MARGIN_RIGHT,
  XTK_PROP_MARGIN_BOTTOM,
  XTK_PROP_TEXT,
  XTK_PROP_TOOLTIP,
  XTK_PROP_ICON,
  XTK_PROP_ENABLED,
  XTK_PROP_SELECTED,
  XTK_PROP_EXPANDED,
};
static XtkEventId const menuitem_events [] = {
  XTK_EVENT_INVOKE,
};
static XtkPropertyId const nav_props [] = {
  XTK_PROP_WIDTH,
  XTK_PROP_HEIGHT,
  XTK_PROP_GROW,
  XTK_PROP_ALIGN_SELF,
  XTK_PROP_MARGIN_LEFT,
  XTK_PROP_MARGIN_TOP,
  XTK_PROP_MARGIN_RIGHT,
  XTK_PROP_MARGIN_BOTTOM,
  XTK_PROP_TOOLTIP,
  XTK_PROP_ENABLED,
  XTK_PROP_SELECTED_INDEX,
  XTK_PROP_NAV_MODEL,
};
static XtkEventId const nav_events [] = {
  XTK_EVENT_SELECT,
  XTK_EVENT_INVOKE,
};
static XtkPropertyId const navitem_props [] = {
  XTK_PROP_WIDTH,
  XTK_PROP_HEIGHT,
  XTK_PROP_GROW,
  XTK_PROP_ALIGN_SELF,
  XTK_PROP_MARGIN_LEFT,
  XTK_PROP_MARGIN_TOP,
  XTK_PROP_MARGIN_RIGHT,
  XTK_PROP_MARGIN_BOTTOM,
  XTK_PROP_TEXT,
  XTK_PROP_TOOLTIP,
  XTK_PROP_ICON,
  XTK_PROP_ENABLED,
  XTK_PROP_SELECTED,
  XTK_PROP_EXPANDED,
};
static XtkEventId const navitem_events [] = {
  XTK_EVENT_INVOKE,
};
static XtkPropertyId const tabs_props [] = {
  XTK_PROP_WIDTH,
  XTK_PROP_HEIGHT,
  XTK_PROP_GROW,
  XTK_PROP_ALIGN_SELF,
  XTK_PROP_MARGIN_LEFT,
  XTK_PROP_MARGIN_TOP,
  XTK_PROP_MARGIN_RIGHT,
  XTK_PROP_MARGIN_BOTTOM,
  XTK_PROP_TOOLTIP,
  XTK_PROP_ENABLED,
  XTK_PROP_SELECTED_INDEX,
  XTK_PROP_ITEM_COUNT,
  XTK_PROP_ITEMS,
  XTK_PROP_ADD_VISIBLE,
};
static XtkEventId const tabs_events [] = {
  XTK_EVENT_SELECT,
  XTK_EVENT_CLOSE,
  XTK_EVENT_INVOKE,
};
static XtkPropertyId const tabitem_props [] = {
  XTK_PROP_WIDTH,
  XTK_PROP_HEIGHT,
  XTK_PROP_GROW,
  XTK_PROP_ALIGN_SELF,
  XTK_PROP_MARGIN_LEFT,
  XTK_PROP_MARGIN_TOP,
  XTK_PROP_MARGIN_RIGHT,
  XTK_PROP_MARGIN_BOTTOM,
  XTK_PROP_TEXT,
  XTK_PROP_TOOLTIP,
  XTK_PROP_ICON,
  XTK_PROP_ENABLED,
  XTK_PROP_SELECTED,
  XTK_PROP_EXPANDED,
};
static XtkEventId const tabitem_events [] = {
  XTK_EVENT_INVOKE,
};
static XtkPropertyId const listitem_props [] = {
  XTK_PROP_WIDTH,
  XTK_PROP_HEIGHT,
  XTK_PROP_GROW,
  XTK_PROP_ALIGN_SELF,
  XTK_PROP_MARGIN_LEFT,
  XTK_PROP_MARGIN_TOP,
  XTK_PROP_MARGIN_RIGHT,
  XTK_PROP_MARGIN_BOTTOM,
  XTK_PROP_TEXT,
  XTK_PROP_TOOLTIP,
  XTK_PROP_ICON,
  XTK_PROP_ENABLED,
  XTK_PROP_SELECTED,
  XTK_PROP_EXPANDED,
};
static XtkEventId const listitem_events [] = {
  XTK_EVENT_INVOKE,
};
static XtkPropertyId const listbox_props [] = {
  XTK_PROP_WIDTH,
  XTK_PROP_HEIGHT,
  XTK_PROP_GROW,
  XTK_PROP_ALIGN_SELF,
  XTK_PROP_MARGIN_LEFT,
  XTK_PROP_MARGIN_TOP,
  XTK_PROP_MARGIN_RIGHT,
  XTK_PROP_MARGIN_BOTTOM,
  XTK_PROP_TOOLTIP,
  XTK_PROP_ENABLED,
  XTK_PROP_SELECTED_INDEX,
  XTK_PROP_ITEM_COUNT,
  XTK_PROP_ITEM_HEIGHT,
  XTK_PROP_ITEM_WIDTH,
  XTK_PROP_COLUMN_COUNT,
  XTK_PROP_SELECTION_MODE,
  XTK_PROP_REALIZED_FIRST,
  XTK_PROP_RECTANGLE_SELECTION,
};
static XtkEventId const listbox_events [] = {
  XTK_EVENT_SELECT,
  XTK_EVENT_INVOKE,
  XTK_EVENT_REALIZE,
};
static XtkPropertyId const gridview_props [] = {
  XTK_PROP_WIDTH,
  XTK_PROP_HEIGHT,
  XTK_PROP_GROW,
  XTK_PROP_ALIGN_SELF,
  XTK_PROP_MARGIN_LEFT,
  XTK_PROP_MARGIN_TOP,
  XTK_PROP_MARGIN_RIGHT,
  XTK_PROP_MARGIN_BOTTOM,
  XTK_PROP_TOOLTIP,
  XTK_PROP_ENABLED,
  XTK_PROP_SELECTED_INDEX,
  XTK_PROP_ITEM_COUNT,
  XTK_PROP_ITEM_HEIGHT,
  XTK_PROP_ITEM_WIDTH,
  XTK_PROP_COLUMN_COUNT,
  XTK_PROP_SELECTION_MODE,
  XTK_PROP_REALIZED_FIRST,
  XTK_PROP_RECTANGLE_SELECTION,
  XTK_PROP_GROUPS,
};
static XtkEventId const gridview_events [] = {
  XTK_EVENT_SELECT,
  XTK_EVENT_INVOKE,
  XTK_EVENT_REALIZE,
};
static XtkPropertyId const repeater_props [] = {
  XTK_PROP_WIDTH,
  XTK_PROP_HEIGHT,
  XTK_PROP_GROW,
  XTK_PROP_ALIGN_SELF,
  XTK_PROP_MARGIN_LEFT,
  XTK_PROP_MARGIN_TOP,
  XTK_PROP_MARGIN_RIGHT,
  XTK_PROP_MARGIN_BOTTOM,
  XTK_PROP_TOOLTIP,
  XTK_PROP_ENABLED,
  XTK_PROP_SELECTED_INDEX,
  XTK_PROP_ITEM_COUNT,
  XTK_PROP_ITEM_HEIGHT,
  XTK_PROP_ITEM_WIDTH,
  XTK_PROP_COLUMN_COUNT,
  XTK_PROP_SELECTION_MODE,
  XTK_PROP_REALIZED_FIRST,
  XTK_PROP_RECTANGLE_SELECTION,
};
static XtkEventId const repeater_events [] = {
  XTK_EVENT_REALIZE,
};
static XtkPropertyId const itemsview_props [] = {
  XTK_PROP_WIDTH,
  XTK_PROP_HEIGHT,
  XTK_PROP_GROW,
  XTK_PROP_ALIGN_SELF,
  XTK_PROP_MARGIN_LEFT,
  XTK_PROP_MARGIN_TOP,
  XTK_PROP_MARGIN_RIGHT,
  XTK_PROP_MARGIN_BOTTOM,
  XTK_PROP_TOOLTIP,
  XTK_PROP_ENABLED,
  XTK_PROP_SELECTED_INDEX,
  XTK_PROP_ITEM_COUNT,
  XTK_PROP_ITEM_HEIGHT,
  XTK_PROP_ITEM_WIDTH,
  XTK_PROP_COLUMN_COUNT,
  XTK_PROP_SELECTION_MODE,
  XTK_PROP_ITEM_INVOKED_ENABLED,
  XTK_PROP_REALIZED_FIRST,
};
static XtkEventId const itemsview_events [] = {
  XTK_EVENT_SELECT,
  XTK_EVENT_INVOKE,
  XTK_EVENT_REALIZE,
};
static XtkPropertyId const flip_props [] = {
  XTK_PROP_WIDTH,
  XTK_PROP_HEIGHT,
  XTK_PROP_GROW,
  XTK_PROP_ALIGN_SELF,
  XTK_PROP_MARGIN_LEFT,
  XTK_PROP_MARGIN_TOP,
  XTK_PROP_MARGIN_RIGHT,
  XTK_PROP_MARGIN_BOTTOM,
  XTK_PROP_TOOLTIP,
  XTK_PROP_SELECTED_INDEX,
  XTK_PROP_ORIENTATION,
};
static XtkEventId const flip_events [] = {
  XTK_EVENT_SELECT,
  XTK_EVENT_INVOKE,
};
static XtkPropertyId const pips_props [] = {
  XTK_PROP_WIDTH,
  XTK_PROP_HEIGHT,
  XTK_PROP_GROW,
  XTK_PROP_ALIGN_SELF,
  XTK_PROP_MARGIN_LEFT,
  XTK_PROP_MARGIN_TOP,
  XTK_PROP_MARGIN_RIGHT,
  XTK_PROP_MARGIN_BOTTOM,
  XTK_PROP_TOOLTIP,
  XTK_PROP_SELECTED_INDEX,
  XTK_PROP_ITEM_COUNT,
  XTK_PROP_ORIENTATION,
  XTK_PROP_MAX_VISIBLE,
  XTK_PROP_NAV_VISIBILITY,
};
static XtkEventId const pips_events [] = {
  XTK_EVENT_SELECT,
  XTK_EVENT_INVOKE,
};
static XtkPropertyId const suggest_props [] = {
  XTK_PROP_WIDTH,
  XTK_PROP_HEIGHT,
  XTK_PROP_GROW,
  XTK_PROP_ALIGN_SELF,
  XTK_PROP_MARGIN_LEFT,
  XTK_PROP_MARGIN_TOP,
  XTK_PROP_MARGIN_RIGHT,
  XTK_PROP_MARGIN_BOTTOM,
  XTK_PROP_TEXT,
  XTK_PROP_TOOLTIP,
  XTK_PROP_ENABLED,
  XTK_PROP_PLACEHOLDER,
  XTK_PROP_ICON,
  XTK_PROP_ITEMS,
};
static XtkEventId const suggest_events [] = {
  XTK_EVENT_CHANGE_STRING,
  XTK_EVENT_QUERY,
  XTK_EVENT_SELECT,
};
static XtkPropertyId const togglesplit_props [] = {
  XTK_PROP_WIDTH,
  XTK_PROP_HEIGHT,
  XTK_PROP_GROW,
  XTK_PROP_ALIGN_SELF,
  XTK_PROP_MARGIN_LEFT,
  XTK_PROP_MARGIN_TOP,
  XTK_PROP_MARGIN_RIGHT,
  XTK_PROP_MARGIN_BOTTOM,
  XTK_PROP_TEXT,
  XTK_PROP_TOOLTIP,
  XTK_PROP_ENABLED,
  XTK_PROP_CHECKED,
  XTK_PROP_ICON,
};
static XtkEventId const togglesplit_events [] = {
  XTK_EVENT_INVOKE,
  XTK_EVENT_CHANGE_BOOL,
};
static XtkPropertyId const radiogroup_props [] = {
  XTK_PROP_WIDTH,
  XTK_PROP_HEIGHT,
  XTK_PROP_GROW,
  XTK_PROP_ALIGN_SELF,
  XTK_PROP_MARGIN_LEFT,
  XTK_PROP_MARGIN_TOP,
  XTK_PROP_MARGIN_RIGHT,
  XTK_PROP_MARGIN_BOTTOM,
  XTK_PROP_TOOLTIP,
  XTK_PROP_ENABLED,
  XTK_PROP_SELECTED_INDEX,
  XTK_PROP_ITEM_COUNT,
  XTK_PROP_COLUMN_COUNT,
};
static XtkEventId const radiogroup_events [] = {
  XTK_EVENT_SELECT,
  XTK_EVENT_INVOKE,
};
static XtkPropertyId const rating_props [] = {
  XTK_PROP_WIDTH,
  XTK_PROP_HEIGHT,
  XTK_PROP_GROW,
  XTK_PROP_SHRINK,
  XTK_PROP_ALIGN_SELF,
  XTK_PROP_MARGIN_LEFT,
  XTK_PROP_MARGIN_TOP,
  XTK_PROP_MARGIN_RIGHT,
  XTK_PROP_MARGIN_BOTTOM,
  XTK_PROP_TOOLTIP,
  XTK_PROP_VALUE_F64,
  XTK_PROP_MAX_F64,
  XTK_PROP_TEXT,
  XTK_PROP_PLACEHOLDER_F64,
  XTK_PROP_INITIAL_VALUE,
  XTK_PROP_CLEAR_ENABLED,
  XTK_PROP_READ_ONLY,
  XTK_PROP_ENABLED,
};
static XtkEventId const rating_events [] = {
  XTK_EVENT_RATING_CHANGED,
};
static XtkPropertyId const selector_props [] = {
  XTK_PROP_WIDTH,
  XTK_PROP_HEIGHT,
  XTK_PROP_GROW,
  XTK_PROP_ALIGN_SELF,
  XTK_PROP_MARGIN_LEFT,
  XTK_PROP_MARGIN_TOP,
  XTK_PROP_MARGIN_RIGHT,
  XTK_PROP_MARGIN_BOTTOM,
  XTK_PROP_TOOLTIP,
  XTK_PROP_ENABLED,
  XTK_PROP_SELECTED_INDEX,
  XTK_PROP_ITEM_COUNT,
  XTK_PROP_ITEMS,
};
static XtkEventId const selector_events [] = {
  XTK_EVENT_SELECT,
  XTK_EVENT_INVOKE,
};
static XtkPropertyId const selectoritem_props [] = {
  XTK_PROP_WIDTH,
  XTK_PROP_HEIGHT,
  XTK_PROP_GROW,
  XTK_PROP_ALIGN_SELF,
  XTK_PROP_MARGIN_LEFT,
  XTK_PROP_MARGIN_TOP,
  XTK_PROP_MARGIN_RIGHT,
  XTK_PROP_MARGIN_BOTTOM,
  XTK_PROP_TEXT,
  XTK_PROP_TOOLTIP,
  XTK_PROP_ICON,
  XTK_PROP_ENABLED,
  XTK_PROP_SELECTED,
  XTK_PROP_EXPANDED,
};
static XtkEventId const selectoritem_events [] = {
  XTK_EVENT_INVOKE,
};
static XtkPropertyId const breadcrumb_props [] = {
  XTK_PROP_WIDTH,
  XTK_PROP_HEIGHT,
  XTK_PROP_GROW,
  XTK_PROP_ALIGN_SELF,
  XTK_PROP_MARGIN_LEFT,
  XTK_PROP_MARGIN_TOP,
  XTK_PROP_MARGIN_RIGHT,
  XTK_PROP_MARGIN_BOTTOM,
  XTK_PROP_TOOLTIP,
  XTK_PROP_ENABLED,
  XTK_PROP_SELECTED_INDEX,
  XTK_PROP_ITEM_COUNT,
  XTK_PROP_ITEMS,
};
static XtkEventId const breadcrumb_events [] = {
  XTK_EVENT_SELECT,
  XTK_EVENT_INVOKE,
};
static XtkPropertyId const crumb_props [] = {
  XTK_PROP_WIDTH,
  XTK_PROP_HEIGHT,
  XTK_PROP_GROW,
  XTK_PROP_ALIGN_SELF,
  XTK_PROP_MARGIN_LEFT,
  XTK_PROP_MARGIN_TOP,
  XTK_PROP_MARGIN_RIGHT,
  XTK_PROP_MARGIN_BOTTOM,
  XTK_PROP_TEXT,
  XTK_PROP_TOOLTIP,
  XTK_PROP_ICON,
  XTK_PROP_ENABLED,
  XTK_PROP_SELECTED,
  XTK_PROP_EXPANDED,
};
static XtkEventId const crumb_events [] = {
  XTK_EVENT_INVOKE,
};
static XtkPropertyId const teachtip_props [] = {
  XTK_PROP_WIDTH,
  XTK_PROP_HEIGHT,
  XTK_PROP_GROW,
  XTK_PROP_SHRINK,
  XTK_PROP_ALIGN_SELF,
  XTK_PROP_MARGIN_LEFT,
  XTK_PROP_MARGIN_TOP,
  XTK_PROP_MARGIN_RIGHT,
  XTK_PROP_MARGIN_BOTTOM,
  XTK_PROP_TOOLTIP,
  XTK_PROP_TEXT,
  XTK_PROP_SUBTITLE,
  XTK_PROP_ICON,
  XTK_PROP_ACTION_TEXT,
  XTK_PROP_ACTION_ACCENT,
  XTK_PROP_CLOSE_TEXT,
  XTK_PROP_PLACEMENT,
  XTK_PROP_UNTARGETED,
  XTK_PROP_LIGHT_DISMISS,
  XTK_PROP_TAIL_VISIBILITY,
  XTK_PROP_PLACEMENT_MARGIN,
  XTK_PROP_OPEN,
};
static XtkEventId const teachtip_events [] = {
  XTK_EVENT_CLOSE,
  XTK_EVENT_INVOKE,
};
static XtkPropertyId const tree_props [] = {
  XTK_PROP_WIDTH,
  XTK_PROP_HEIGHT,
  XTK_PROP_GROW,
  XTK_PROP_ALIGN_SELF,
  XTK_PROP_MARGIN_LEFT,
  XTK_PROP_MARGIN_TOP,
  XTK_PROP_MARGIN_RIGHT,
  XTK_PROP_MARGIN_BOTTOM,
  XTK_PROP_TOOLTIP,
  XTK_PROP_ENABLED,
  XTK_PROP_SELECTED_INDEX,
  XTK_PROP_ITEM_COUNT,
  XTK_PROP_ITEM_HEIGHT,
  XTK_PROP_SELECTION_MODE,
  XTK_PROP_ITEMS,
};
static XtkEventId const tree_events [] = {
  XTK_EVENT_INVOKE,
  XTK_EVENT_TREE_EXPAND,
  XTK_EVENT_TREE_SELECT,
};
static XtkPropertyId const treeitem_props [] = {
  XTK_PROP_WIDTH,
  XTK_PROP_HEIGHT,
  XTK_PROP_GROW,
  XTK_PROP_ALIGN_SELF,
  XTK_PROP_MARGIN_LEFT,
  XTK_PROP_MARGIN_TOP,
  XTK_PROP_MARGIN_RIGHT,
  XTK_PROP_MARGIN_BOTTOM,
  XTK_PROP_TEXT,
  XTK_PROP_TOOLTIP,
  XTK_PROP_ICON,
  XTK_PROP_ENABLED,
  XTK_PROP_SELECTED,
  XTK_PROP_EXPANDED,
};
static XtkEventId const treeitem_events [] = {
  XTK_EVENT_SELECT,
  XTK_EVENT_INVOKE,
};
static XtkPropertyId const refresh_props [] = {
  XTK_PROP_WIDTH,
  XTK_PROP_HEIGHT,
  XTK_PROP_GROW,
  XTK_PROP_ALIGN_SELF,
  XTK_PROP_MARGIN_LEFT,
  XTK_PROP_MARGIN_TOP,
  XTK_PROP_MARGIN_RIGHT,
  XTK_PROP_MARGIN_BOTTOM,
  XTK_PROP_TOOLTIP,
  XTK_PROP_PULL_DIRECTION,
  XTK_PROP_VISUALIZER_SIZE,
  XTK_PROP_THRESHOLD_RATIO,
  XTK_PROP_REFRESHING,
};
static XtkEventId const refresh_events [] = {
  XTK_EVENT_REFRESH,
};
static XtkPropertyId const avatar_props [] = {
  XTK_PROP_WIDTH,
  XTK_PROP_HEIGHT,
  XTK_PROP_GROW,
  XTK_PROP_SHRINK,
  XTK_PROP_ALIGN_SELF,
  XTK_PROP_MARGIN_LEFT,
  XTK_PROP_MARGIN_TOP,
  XTK_PROP_MARGIN_RIGHT,
  XTK_PROP_MARGIN_BOTTOM,
  XTK_PROP_TOOLTIP,
  XTK_PROP_TEXT,
  XTK_PROP_INITIALS,
  XTK_PROP_IMAGE_SOURCE,
  XTK_PROP_BADGE_GLYPH,
  XTK_PROP_BADGE_VALUE,
  XTK_PROP_IS_GROUP,
  XTK_PROP_IMAGE_STRETCH,
};
static XtkPropertyId const pager_props [] = {
  XTK_PROP_WIDTH,
  XTK_PROP_HEIGHT,
  XTK_PROP_GROW,
  XTK_PROP_SHRINK,
  XTK_PROP_ALIGN_SELF,
  XTK_PROP_MARGIN_LEFT,
  XTK_PROP_MARGIN_TOP,
  XTK_PROP_MARGIN_RIGHT,
  XTK_PROP_MARGIN_BOTTOM,
  XTK_PROP_TOOLTIP,
  XTK_PROP_SELECTED_INDEX,
  XTK_PROP_ITEM_COUNT,
  XTK_PROP_DISPLAY_MODE,
  XTK_PROP_FIRST_BUTTON,
  XTK_PROP_PREVIOUS_BUTTON,
  XTK_PROP_NEXT_BUTTON,
  XTK_PROP_LAST_BUTTON,
  XTK_PROP_PREFIX,
  XTK_PROP_SUFFIX,
};
static XtkEventId const pager_events [] = {
  XTK_EVENT_SELECT,
  XTK_EVENT_INVOKE,
};
static XtkPropertyId const splitview_props [] = {
  XTK_PROP_WIDTH,
  XTK_PROP_HEIGHT,
  XTK_PROP_GROW,
  XTK_PROP_SHRINK,
  XTK_PROP_ALIGN_SELF,
  XTK_PROP_MARGIN_LEFT,
  XTK_PROP_MARGIN_TOP,
  XTK_PROP_MARGIN_RIGHT,
  XTK_PROP_MARGIN_BOTTOM,
  XTK_PROP_TOOLTIP,
  XTK_PROP_ORIENTATION,
  XTK_PROP_GAP,
  XTK_PROP_PADDING_LEFT,
  XTK_PROP_PADDING_TOP,
  XTK_PROP_PADDING_RIGHT,
  XTK_PROP_PADDING_BOTTOM,
  XTK_PROP_FILL,
  XTK_PROP_OPEN,
  XTK_PROP_DISPLAY_MODE,
  XTK_PROP_PANE_PLACEMENT,
  XTK_PROP_OPEN_PANE_LENGTH,
  XTK_PROP_COMPACT_PANE_LENGTH,
};
static XtkPropertyId const splitpane_props [] = {
  XTK_PROP_WIDTH,
  XTK_PROP_HEIGHT,
  XTK_PROP_GROW,
  XTK_PROP_SHRINK,
  XTK_PROP_ALIGN_SELF,
  XTK_PROP_MARGIN_LEFT,
  XTK_PROP_MARGIN_TOP,
  XTK_PROP_MARGIN_RIGHT,
  XTK_PROP_MARGIN_BOTTOM,
  XTK_PROP_TOOLTIP,
  XTK_PROP_ORIENTATION,
  XTK_PROP_ALIGN_ITEMS,
  XTK_PROP_JUSTIFY_CONTENT,
  XTK_PROP_GAP,
  XTK_PROP_PADDING_LEFT,
  XTK_PROP_PADDING_TOP,
  XTK_PROP_PADDING_RIGHT,
  XTK_PROP_PADDING_BOTTOM,
  XTK_PROP_FILL,
  XTK_PROP_FIT_WIDTH,
  XTK_PROP_FIT_HEIGHT,
  XTK_PROP_WRAP,
  XTK_PROP_DROP_OPERATION,
  XTK_PROP_DRAG_TEXT,
  XTK_PROP_DRAG_FILES,
  XTK_PROP_FLOW_DIRECTION,
};
static XtkEventId const splitpane_events [] = {
  XTK_EVENT_DRAG_HOVER,
  XTK_EVENT_DROP_FILES,
  XTK_EVENT_DROP_TEXT,
  XTK_EVENT_DRAG_COMPLETED,
};
static XtkPropertyId const splitbody_props [] = {
  XTK_PROP_WIDTH,
  XTK_PROP_HEIGHT,
  XTK_PROP_GROW,
  XTK_PROP_SHRINK,
  XTK_PROP_ALIGN_SELF,
  XTK_PROP_MARGIN_LEFT,
  XTK_PROP_MARGIN_TOP,
  XTK_PROP_MARGIN_RIGHT,
  XTK_PROP_MARGIN_BOTTOM,
  XTK_PROP_TOOLTIP,
  XTK_PROP_ORIENTATION,
  XTK_PROP_ALIGN_ITEMS,
  XTK_PROP_JUSTIFY_CONTENT,
  XTK_PROP_GAP,
  XTK_PROP_PADDING_LEFT,
  XTK_PROP_PADDING_TOP,
  XTK_PROP_PADDING_RIGHT,
  XTK_PROP_PADDING_BOTTOM,
  XTK_PROP_FILL,
  XTK_PROP_FIT_WIDTH,
  XTK_PROP_FIT_HEIGHT,
  XTK_PROP_WRAP,
  XTK_PROP_DROP_OPERATION,
  XTK_PROP_DRAG_TEXT,
  XTK_PROP_DRAG_FILES,
  XTK_PROP_FLOW_DIRECTION,
};
static XtkEventId const splitbody_events [] = {
  XTK_EVENT_DRAG_HOVER,
  XTK_EVENT_DROP_FILES,
  XTK_EVENT_DROP_TEXT,
  XTK_EVENT_DRAG_COMPLETED,
};
static XtkPropertyId const titlebar_props [] = {
  XTK_PROP_WIDTH,
  XTK_PROP_HEIGHT,
  XTK_PROP_GROW,
  XTK_PROP_SHRINK,
  XTK_PROP_ALIGN_SELF,
  XTK_PROP_MARGIN_LEFT,
  XTK_PROP_MARGIN_TOP,
  XTK_PROP_MARGIN_RIGHT,
  XTK_PROP_MARGIN_BOTTOM,
  XTK_PROP_TOOLTIP,
  XTK_PROP_TEXT,
  XTK_PROP_SUBTITLE,
  XTK_PROP_ICON,
  XTK_PROP_SHOW_BACK,
  XTK_PROP_BACK_DISABLED,
  XTK_PROP_SHOW_PANE_TOGGLE,
  XTK_PROP_INTEGRATE_WINDOW,
  XTK_PROP_ENABLED,
};
static XtkEventId const titlebar_events [] = {
  XTK_EVENT_INVOKE,
  XTK_EVENT_TOGGLE,
};
static XtkPropertyId const scrollbar_props [] = {
  XTK_PROP_WIDTH,
  XTK_PROP_HEIGHT,
  XTK_PROP_GROW,
  XTK_PROP_ALIGN_SELF,
  XTK_PROP_MARGIN_LEFT,
  XTK_PROP_MARGIN_TOP,
  XTK_PROP_MARGIN_RIGHT,
  XTK_PROP_MARGIN_BOTTOM,
  XTK_PROP_TOOLTIP,
  XTK_PROP_ENABLED,
  XTK_PROP_ORIENTATION,
  XTK_PROP_MIN_F64,
  XTK_PROP_MAX_F64,
  XTK_PROP_VALUE_F64,
  XTK_PROP_VIEWPORT_SIZE,
  XTK_PROP_SMALL_CHANGE,
  XTK_PROP_LARGE_CHANGE,
  XTK_PROP_INDICATOR_MODE,
};
static XtkEventId const scrollbar_events [] = {
  XTK_EVENT_CHANGE_F64,
};
static XtkPropertyId const looping_props [] = {
  XTK_PROP_WIDTH,
  XTK_PROP_HEIGHT,
  XTK_PROP_GROW,
  XTK_PROP_ALIGN_SELF,
  XTK_PROP_MARGIN_LEFT,
  XTK_PROP_MARGIN_TOP,
  XTK_PROP_MARGIN_RIGHT,
  XTK_PROP_MARGIN_BOTTOM,
  XTK_PROP_TOOLTIP,
  XTK_PROP_ENABLED,
  XTK_PROP_ITEM_COUNT,
  XTK_PROP_SELECTED_INDEX,
  XTK_PROP_ITEM_HEIGHT,
  XTK_PROP_ITEM_WIDTH,
  XTK_PROP_SHOULD_LOOP,
  XTK_PROP_ITEMS,
};
static XtkEventId const looping_events [] = {
  XTK_EVENT_SELECT,
  XTK_EVENT_INVOKE,
};
static XtkPropertyId const loopitem_props [] = {
  XTK_PROP_WIDTH,
  XTK_PROP_HEIGHT,
  XTK_PROP_GROW,
  XTK_PROP_ALIGN_SELF,
  XTK_PROP_MARGIN_LEFT,
  XTK_PROP_MARGIN_TOP,
  XTK_PROP_MARGIN_RIGHT,
  XTK_PROP_MARGIN_BOTTOM,
  XTK_PROP_TEXT,
  XTK_PROP_TOOLTIP,
  XTK_PROP_ICON,
  XTK_PROP_ENABLED,
  XTK_PROP_SELECTED,
  XTK_PROP_EXPANDED,
};
static XtkPropertyId const datepicker_props [] = {
  XTK_PROP_WIDTH,
  XTK_PROP_HEIGHT,
  XTK_PROP_GROW,
  XTK_PROP_ALIGN_SELF,
  XTK_PROP_MARGIN_LEFT,
  XTK_PROP_MARGIN_TOP,
  XTK_PROP_MARGIN_RIGHT,
  XTK_PROP_MARGIN_BOTTOM,
  XTK_PROP_TOOLTIP,
  XTK_PROP_ENABLED,
  XTK_PROP_HEADER,
  XTK_PROP_DATE,
  XTK_PROP_MIN_YEAR,
  XTK_PROP_MAX_YEAR,
};
static XtkEventId const datepicker_events [] = {
  XTK_EVENT_VALUE_CHANGED,
};
static XtkPropertyId const timepicker_props [] = {
  XTK_PROP_WIDTH,
  XTK_PROP_HEIGHT,
  XTK_PROP_GROW,
  XTK_PROP_ALIGN_SELF,
  XTK_PROP_MARGIN_LEFT,
  XTK_PROP_MARGIN_TOP,
  XTK_PROP_MARGIN_RIGHT,
  XTK_PROP_MARGIN_BOTTOM,
  XTK_PROP_TOOLTIP,
  XTK_PROP_ENABLED,
  XTK_PROP_HEADER,
  XTK_PROP_TIME,
  XTK_PROP_CLOCK,
  XTK_PROP_MINUTE_INCREMENT,
};
static XtkEventId const timepicker_events [] = {
  XTK_EVENT_VALUE_CHANGED,
};
static XtkPropertyId const pickerflyout_props [] = {
  XTK_PROP_WIDTH,
  XTK_PROP_HEIGHT,
  XTK_PROP_GROW,
  XTK_PROP_ALIGN_SELF,
  XTK_PROP_MARGIN_LEFT,
  XTK_PROP_MARGIN_TOP,
  XTK_PROP_MARGIN_RIGHT,
  XTK_PROP_MARGIN_BOTTOM,
  XTK_PROP_TEXT,
  XTK_PROP_TOOLTIP,
  XTK_PROP_ICON,
  XTK_PROP_ENABLED,
  XTK_PROP_SELECTED,
  XTK_PROP_EXPANDED,
};
static XtkPropertyId const calendar_props [] = {
  XTK_PROP_WIDTH,
  XTK_PROP_HEIGHT,
  XTK_PROP_GROW,
  XTK_PROP_ALIGN_SELF,
  XTK_PROP_MARGIN_LEFT,
  XTK_PROP_MARGIN_TOP,
  XTK_PROP_MARGIN_RIGHT,
  XTK_PROP_MARGIN_BOTTOM,
  XTK_PROP_TOOLTIP,
  XTK_PROP_ENABLED,
  XTK_PROP_DATE,
  XTK_PROP_SELECTION_MODE,
  XTK_PROP_MIN_DATE,
  XTK_PROP_MAX_DATE,
  XTK_PROP_FIRST_DAY,
};
static XtkEventId const calendar_events [] = {
  XTK_EVENT_DATE_SELECT,
};
static XtkPropertyId const calday_props [] = {
  XTK_PROP_WIDTH,
  XTK_PROP_HEIGHT,
  XTK_PROP_GROW,
  XTK_PROP_ALIGN_SELF,
  XTK_PROP_MARGIN_LEFT,
  XTK_PROP_MARGIN_TOP,
  XTK_PROP_MARGIN_RIGHT,
  XTK_PROP_MARGIN_BOTTOM,
  XTK_PROP_TEXT,
  XTK_PROP_TOOLTIP,
  XTK_PROP_ICON,
  XTK_PROP_ENABLED,
  XTK_PROP_SELECTED,
  XTK_PROP_EXPANDED,
};
static XtkPropertyId const colorpicker_props [] = {
  XTK_PROP_WIDTH,
  XTK_PROP_HEIGHT,
  XTK_PROP_GROW,
  XTK_PROP_ALIGN_SELF,
  XTK_PROP_MARGIN_LEFT,
  XTK_PROP_MARGIN_TOP,
  XTK_PROP_MARGIN_RIGHT,
  XTK_PROP_MARGIN_BOTTOM,
  XTK_PROP_TOOLTIP,
  XTK_PROP_ENABLED,
  XTK_PROP_COLOR,
  XTK_PROP_ALPHA_ENABLED,
  XTK_PROP_MORE_BUTTON_VISIBLE,
  XTK_PROP_SPECTRUM,
};
static XtkEventId const colorpicker_events [] = {
  XTK_EVENT_VALUE_CHANGED,
};
static XtkPropertyId const colorspectrum_props [] = {
  XTK_PROP_WIDTH,
  XTK_PROP_HEIGHT,
  XTK_PROP_GROW,
  XTK_PROP_ALIGN_SELF,
  XTK_PROP_MARGIN_LEFT,
  XTK_PROP_MARGIN_TOP,
  XTK_PROP_MARGIN_RIGHT,
  XTK_PROP_MARGIN_BOTTOM,
  XTK_PROP_TEXT,
  XTK_PROP_TOOLTIP,
  XTK_PROP_ICON,
  XTK_PROP_ENABLED,
  XTK_PROP_SELECTED,
  XTK_PROP_EXPANDED,
};
static XtkPropertyId const colorslider_props [] = {
  XTK_PROP_WIDTH,
  XTK_PROP_HEIGHT,
  XTK_PROP_GROW,
  XTK_PROP_ALIGN_SELF,
  XTK_PROP_MARGIN_LEFT,
  XTK_PROP_MARGIN_TOP,
  XTK_PROP_MARGIN_RIGHT,
  XTK_PROP_MARGIN_BOTTOM,
  XTK_PROP_TEXT,
  XTK_PROP_TOOLTIP,
  XTK_PROP_ICON,
  XTK_PROP_ENABLED,
  XTK_PROP_SELECTED,
  XTK_PROP_EXPANDED,
};
static XtkPropertyId const colheader_props [] = {
  XTK_PROP_WIDTH,
  XTK_PROP_HEIGHT,
  XTK_PROP_GROW,
  XTK_PROP_SHRINK,
  XTK_PROP_ALIGN_SELF,
  XTK_PROP_MARGIN_LEFT,
  XTK_PROP_MARGIN_TOP,
  XTK_PROP_MARGIN_RIGHT,
  XTK_PROP_MARGIN_BOTTOM,
  XTK_PROP_TOOLTIP,
};
static XtkPropertyId const colitem_props [] = {
  XTK_PROP_WIDTH,
  XTK_PROP_MIN_WIDTH,
  XTK_PROP_MAX_WIDTH,
  XTK_PROP_TEXT,
  XTK_PROP_TOOLTIP,
  XTK_PROP_TEXT_ALIGN,
  XTK_PROP_ENABLED,
  XTK_PROP_RESIZABLE,
  XTK_PROP_SORT_DIRECTION,
};
static XtkEventId const colitem_events [] = {
  XTK_EVENT_INVOKE,
  XTK_EVENT_RESIZE,
  XTK_EVENT_FIT,
  XTK_EVENT_REORDER,
};
static XtkPropertyId const commandbar_props [] = {
  XTK_PROP_WIDTH,
  XTK_PROP_HEIGHT,
  XTK_PROP_GROW,
  XTK_PROP_ALIGN_SELF,
  XTK_PROP_MARGIN_LEFT,
  XTK_PROP_MARGIN_TOP,
  XTK_PROP_MARGIN_RIGHT,
  XTK_PROP_MARGIN_BOTTOM,
  XTK_PROP_TOOLTIP,
  XTK_PROP_ENABLED,
  XTK_PROP_OPEN,
  XTK_PROP_IS_STICKY,
  XTK_PROP_CLOSED_DISPLAY_MODE,
  XTK_PROP_DEFAULT_LABEL_POSITION,
  XTK_PROP_OVERFLOW_BUTTON_VISIBILITY,
  XTK_PROP_DYNAMIC_OVERFLOW,
};
static XtkEventId const commandbar_events [] = {
  XTK_EVENT_OPEN,
};
static XtkPropertyId const appbarbutton_props [] = {
  XTK_PROP_WIDTH,
  XTK_PROP_HEIGHT,
  XTK_PROP_GROW,
  XTK_PROP_ALIGN_SELF,
  XTK_PROP_MARGIN_LEFT,
  XTK_PROP_MARGIN_TOP,
  XTK_PROP_MARGIN_RIGHT,
  XTK_PROP_MARGIN_BOTTOM,
  XTK_PROP_TOOLTIP,
  XTK_PROP_TEXT,
  XTK_PROP_ICON,
  XTK_PROP_ENABLED,
  XTK_PROP_LABEL_POSITION,
  XTK_PROP_ACCELERATOR_TEXT,
  XTK_PROP_SECONDARY,
  XTK_PROP_DYNAMIC_OVERFLOW_ORDER,
};
static XtkEventId const appbarbutton_events [] = {
  XTK_EVENT_INVOKE,
};
static XtkPropertyId const appbartoggle_props [] = {
  XTK_PROP_WIDTH,
  XTK_PROP_HEIGHT,
  XTK_PROP_GROW,
  XTK_PROP_ALIGN_SELF,
  XTK_PROP_MARGIN_LEFT,
  XTK_PROP_MARGIN_TOP,
  XTK_PROP_MARGIN_RIGHT,
  XTK_PROP_MARGIN_BOTTOM,
  XTK_PROP_TOOLTIP,
  XTK_PROP_TEXT,
  XTK_PROP_ICON,
  XTK_PROP_ENABLED,
  XTK_PROP_LABEL_POSITION,
  XTK_PROP_ACCELERATOR_TEXT,
  XTK_PROP_CHECKED,
  XTK_PROP_SECONDARY,
  XTK_PROP_DYNAMIC_OVERFLOW_ORDER,
};
static XtkEventId const appbartoggle_events [] = {
  XTK_EVENT_CHANGE_BOOL,
};
static XtkPropertyId const appbarsep_props [] = {
  XTK_PROP_WIDTH,
  XTK_PROP_HEIGHT,
  XTK_PROP_GROW,
  XTK_PROP_ALIGN_SELF,
  XTK_PROP_MARGIN_LEFT,
  XTK_PROP_MARGIN_TOP,
  XTK_PROP_MARGIN_RIGHT,
  XTK_PROP_MARGIN_BOTTOM,
  XTK_PROP_TOOLTIP,
  XTK_PROP_SECONDARY,
  XTK_PROP_DYNAMIC_OVERFLOW_ORDER,
};
static XtkPropertyId const cmdmore_props [] = {
  XTK_PROP_WIDTH,
  XTK_PROP_HEIGHT,
  XTK_PROP_GROW,
  XTK_PROP_ALIGN_SELF,
  XTK_PROP_MARGIN_LEFT,
  XTK_PROP_MARGIN_TOP,
  XTK_PROP_MARGIN_RIGHT,
  XTK_PROP_MARGIN_BOTTOM,
  XTK_PROP_TOOLTIP,
};
static XtkPropertyId const colbutton_props [] = {
  XTK_PROP_WIDTH,
  XTK_PROP_HEIGHT,
  XTK_PROP_GROW,
  XTK_PROP_ALIGN_SELF,
  XTK_PROP_MARGIN_LEFT,
  XTK_PROP_MARGIN_TOP,
  XTK_PROP_MARGIN_RIGHT,
  XTK_PROP_MARGIN_BOTTOM,
  XTK_PROP_TOOLTIP,
};
static XtkPropertyId const groupheader_props [] = {
  XTK_PROP_WIDTH,
  XTK_PROP_HEIGHT,
  XTK_PROP_GROW,
  XTK_PROP_SHRINK,
  XTK_PROP_ALIGN_SELF,
  XTK_PROP_MARGIN_LEFT,
  XTK_PROP_MARGIN_TOP,
  XTK_PROP_MARGIN_RIGHT,
  XTK_PROP_MARGIN_BOTTOM,
  XTK_PROP_TOOLTIP,
};

static XtkCtrlDesc const
			controls
			  [XTK_CTRL_TYPE_COUNT] = {
				[XTK_CTRL_CONTAINER]
                = {XTK_CTRL_CONTAINER,     "container",               container_props,     COUNT_OF(container_props),     container_events,    COUNT_OF(container_events),    {XTK_ACCESS_ROLE_GROUP, false, false},     NULL, 0u, TREE, TREE},
				[XTK_CTRL_TEXT]
                = {XTK_CTRL_TEXT,          "text",                    text_props,          COUNT_OF(text_props),          NULL,                0u,                            {XTK_ACCESS_ROLE_TEXT, false, false},      NULL, 0u, TREE, TREE},
				[XTK_CTRL_BUTTON]
                = {XTK_CTRL_BUTTON,        "button",                  button_props,        COUNT_OF(button_props),        button_events,       COUNT_OF(button_events),       {XTK_ACCESS_ROLE_BUTTON, true, true},      NULL, 0u, TREE, TREE},
				[XTK_CTRL_TOGGLE]
                = {XTK_CTRL_TOGGLE,        "toggle-button",           toggle_props,        COUNT_OF(toggle_props),        toggle_events,       COUNT_OF(toggle_events),       {XTK_ACCESS_ROLE_BUTTON, true, true},      NULL, 0u, TREE, TREE},
				[XTK_CTRL_CHECKBOX]
                = {XTK_CTRL_CHECKBOX,      "checkbox",                checkbox_props,      COUNT_OF(checkbox_props),      checkbox_events,     COUNT_OF(checkbox_events),     {XTK_ACCESS_ROLE_CHECKBOX, true, true},    NULL, 0u, TREE, TREE},
				[XTK_CTRL_RADIO]
                = {XTK_CTRL_RADIO,         "radio",                   radio_props,         COUNT_OF(radio_props),         radio_events,        COUNT_OF(radio_events),        {XTK_ACCESS_ROLE_RADIO, true, true},       NULL, 0u, TREE, TREE},
				[XTK_CTRL_SWITCH]
                = {XTK_CTRL_SWITCH,        "switch",                  switch_props,        COUNT_OF(switch_props),        switch_events,       COUNT_OF(switch_events),       {XTK_ACCESS_ROLE_CHECKBOX, true, true},    NULL, 0u, TREE, TREE},
				[XTK_CTRL_SLIDER] = {XTK_CTRL_SLIDER,        "slider",                  slider_props,        COUNT_OF(slider_props),        slider_events,       COUNT_OF(slider_events),       {XTK_ACCESS_ROLE_SLIDER, true, true},      NULL, 0u, TREE, TREE},
				[XTK_CTRL_TEXTBOX]
                = {XTK_CTRL_TEXTBOX,       "text-input",              textbox_props,       COUNT_OF(textbox_props),       textbox_events,      COUNT_OF(textbox_events),      {XTK_ACCESS_ROLE_EDIT, true, true},        NULL, 0u, TREE, TREE},
				[XTK_CTRL_SCROLL]
                = {XTK_CTRL_SCROLL,        "scroll",                  scroll_props,        COUNT_OF(scroll_props),        scroll_events,       COUNT_OF(scroll_events),       {XTK_ACCESS_ROLE_GROUP, true, true},       NULL, 0u, TREE, TREE},
				[XTK_CTRL_IMAGE]
                = {XTK_CTRL_IMAGE,         "image",                   image_props,         COUNT_OF(image_props),         image_events,        COUNT_OF(image_events),        {XTK_ACCESS_ROLE_IMAGE, false, false},     NULL, 0u, TREE, TREE},
				[XTK_CTRL_PROGRESS]
                = {XTK_CTRL_PROGRESS,      "progress",                progress_props,      COUNT_OF(progress_props),      NULL,                0u,                            {XTK_ACCESS_ROLE_NONE, false, false},      NULL, 0u, TREE, TREE},
				[XTK_CTRL_LIST]
                = {XTK_CTRL_LIST,          "list",                    list_props,          COUNT_OF(list_props),          list_events,         COUNT_OF(list_events),         {XTK_ACCESS_ROLE_LIST, true, true},        NULL, 0u, TREE, TREE},
				[XTK_CTRL_TAB]
                = {XTK_CTRL_TAB,           "tab",                     tab_props,           COUNT_OF(tab_props),           NULL,                0u,                            {XTK_ACCESS_ROLE_GROUP, true, true},       NULL, 0u, TREE, TREE},
				[XTK_CTRL_CARD]
                = {XTK_CTRL_CARD,          "card",                    card_props,          COUNT_OF(card_props),          card_events,         COUNT_OF(card_events),         {XTK_ACCESS_ROLE_GROUP, false, false},     NULL, 0u, TREE, TREE},
				[XTK_CTRL_DIVIDER]
                = {XTK_CTRL_DIVIDER,       "divider",                 divider_props,       COUNT_OF(divider_props),       NULL,                0u,                            {XTK_ACCESS_ROLE_NONE, false, false},      NULL, 0u, TREE, TREE},
				[XTK_CTRL_CANVAS]
                = {XTK_CTRL_CANVAS,        "canvas",                  canvas_props,        COUNT_OF(canvas_props),        NULL,                0u,                            {XTK_ACCESS_ROLE_NONE, false, false},      NULL, 0u, TREE, TREE},
				[XTK_CTRL_PASSWORD]
                = {XTK_CTRL_PASSWORD,      "password-box",            password_props,      COUNT_OF(password_props),      password_events,     COUNT_OF(password_events),     {XTK_ACCESS_ROLE_EDIT, true, true},        NULL, 0u, TREE, TREE},
				[XTK_CTRL_NUMBER]
                = {XTK_CTRL_NUMBER,        "number-box",              number_props,        COUNT_OF(number_props),        number_events,       COUNT_OF(number_events),       {XTK_ACCESS_ROLE_EDIT, true, true},        NULL, 0u, TREE, TREE},
				[XTK_CTRL_LINK]
                = {XTK_CTRL_LINK,          "hyperlink",               link_props,          COUNT_OF(link_props),          link_events,         COUNT_OF(link_events),         {XTK_ACCESS_ROLE_BUTTON, true, true},      NULL, 0u, TREE, TREE},
				[XTK_CTRL_REPEAT]
                = {XTK_CTRL_REPEAT,        "repeat-button",           repeat_props,        COUNT_OF(repeat_props),        repeat_events,       COUNT_OF(repeat_events),       {XTK_ACCESS_ROLE_BUTTON, true, true},      NULL, 0u, TREE, TREE},
				[XTK_CTRL_PROGRESSRING]
                = {XTK_CTRL_PROGRESSRING,  "progress-ring",           progressring_props,  COUNT_OF(progressring_props),  NULL,                0u,                            {XTK_ACCESS_ROLE_NONE, false, false},      NULL, 0u, TREE, TREE},
				[XTK_CTRL_BADGE]
                = {XTK_CTRL_BADGE,         "info-badge",              badge_props,         COUNT_OF(badge_props),         NULL,                0u,                            {XTK_ACCESS_ROLE_TEXT, false, false},      NULL, 0u, TREE, TREE},
				[XTK_CTRL_TOOLTIP]
                = {XTK_CTRL_TOOLTIP,       "tooltip",                 tooltip_props,       COUNT_OF(tooltip_props),       NULL,                0u,                            {XTK_ACCESS_ROLE_NONE, false, false},      NULL, 0u, TREE, TREE},
				[XTK_CTRL_FLYOUT]
                = {XTK_CTRL_FLYOUT,        "flyout",                  flyout_props,        COUNT_OF(flyout_props),        NULL,                0u,                            {XTK_ACCESS_ROLE_GROUP, true, true},       NULL, 0u, TREE, TREE},
				[XTK_CTRL_MENUFLY]
                = {XTK_CTRL_MENUFLY,       "menu-flyout",             menufly_props,       COUNT_OF(menufly_props),       NULL,                0u,                            {XTK_ACCESS_ROLE_GROUP, true, true},       NULL, 0u, TREE, TREE},
				[XTK_CTRL_DROPDOWN] = {XTK_CTRL_DROPDOWN,      "dropdown-button",         dropdown_props,      COUNT_OF(dropdown_props),      dropdown_events,     COUNT_OF(dropdown_events),     {XTK_ACCESS_ROLE_BUTTON, true, true},      NULL, 0u, TREE, TREE},
				[XTK_CTRL_SPLIT]
                = {XTK_CTRL_SPLIT,         "split-button",            split_props,         COUNT_OF(split_props),         split_events,        COUNT_OF(split_events),        {XTK_ACCESS_ROLE_BUTTON, true, true},      NULL, 0u, TREE, TREE},
				[XTK_CTRL_COMBO]
                = {XTK_CTRL_COMBO,         "combo-box",               combo_props,         COUNT_OF(combo_props),         combo_events,        COUNT_OF(combo_events),        {XTK_ACCESS_ROLE_EDIT, true, true},        NULL, 0u, TREE, TREE},
				[XTK_CTRL_EXPANDER]
                = {XTK_CTRL_EXPANDER,      "expander",                expander_props,      COUNT_OF(expander_props),      expander_events,     COUNT_OF(expander_events),     {XTK_ACCESS_ROLE_GROUP, true, true},       NULL, 0u, TREE, TREE},
				[XTK_CTRL_EXPHEAD]
                = {XTK_CTRL_EXPHEAD,       "expander-header",         exphead_props,       COUNT_OF(exphead_props),       NULL,                0u,                            {XTK_ACCESS_ROLE_BUTTON, true, true},      NULL, 0u, TREE, TREE},
				[XTK_CTRL_EXPBODY]
                = {XTK_CTRL_EXPBODY,       "expander-content",        expbody_props,       COUNT_OF(expbody_props),       expbody_events,      COUNT_OF(expbody_events),      {XTK_ACCESS_ROLE_GROUP, false, false},     NULL, 0u, TREE, TREE},
				[XTK_CTRL_INFOBAR]
                = {XTK_CTRL_INFOBAR,       "info-bar",                infobar_props,       COUNT_OF(infobar_props),       infobar_events,      COUNT_OF(infobar_events),      {XTK_ACCESS_ROLE_GROUP, true, true},       NULL, 0u, TREE, TREE},
				[XTK_CTRL_DIALOG]
                = {XTK_CTRL_DIALOG,        "content-dialog",          dialog_props,        COUNT_OF(dialog_props),        dialog_events,       COUNT_OF(dialog_events),       {XTK_ACCESS_ROLE_GROUP, true, true},       NULL, 0u, TREE, TREE},
				[XTK_CTRL_DIALOGBODY]
                = {XTK_CTRL_DIALOGBODY,    "dialog-content",          dialogbody_props,    COUNT_OF(dialogbody_props),    dialogbody_events,   COUNT_OF(dialogbody_events),   {XTK_ACCESS_ROLE_GROUP, false, false},     NULL, 0u, TREE, TREE},
				[XTK_CTRL_MENUBAR]
                = {XTK_CTRL_MENUBAR,       "menu-bar",                menubar_props,       COUNT_OF(menubar_props),       NULL,                0u,                            {XTK_ACCESS_ROLE_GROUP, true, true},       NULL, 0u, TREE, TREE},
				[XTK_CTRL_MENUITEM]
                = {XTK_CTRL_MENUITEM,      "menu-flyout-item",        menuitem_props,      COUNT_OF(menuitem_props),      menuitem_events,     COUNT_OF(menuitem_events),     {XTK_ACCESS_ROLE_BUTTON, true, true},      NULL, 0u, TREE, TREE},
				[XTK_CTRL_NAV]
                = {XTK_CTRL_NAV,           "nav-view",                nav_props,           COUNT_OF(nav_props),           nav_events,          COUNT_OF(nav_events),          {XTK_ACCESS_ROLE_GROUP, true, true},       NULL, 0u, TREE, TREE},
				[XTK_CTRL_NAVITEM]
                = {XTK_CTRL_NAVITEM,       "nav-view-item",           navitem_props,       COUNT_OF(navitem_props),       navitem_events,      COUNT_OF(navitem_events),      {XTK_ACCESS_ROLE_LIST_ITEM, true, true},   NULL, 0u, TREE, TREE},
				[XTK_CTRL_TABS]
                = {XTK_CTRL_TABS,          "tab-view",                tabs_props,          COUNT_OF(tabs_props),          tabs_events,         COUNT_OF(tabs_events),         {XTK_ACCESS_ROLE_GROUP, true, true},       NULL, 0u, TREE, TREE},
				[XTK_CTRL_TABITEM]
                = {XTK_CTRL_TABITEM,       "tab-view-item",           tabitem_props,       COUNT_OF(tabitem_props),       tabitem_events,      COUNT_OF(tabitem_events),      {XTK_ACCESS_ROLE_LIST_ITEM, true, true},   NULL, 0u, TREE, TREE},
				[XTK_CTRL_LISTITEM]
                = {XTK_CTRL_LISTITEM,      "list-item",               listitem_props,      COUNT_OF(listitem_props),      listitem_events,     COUNT_OF(listitem_events),     {XTK_ACCESS_ROLE_LIST_ITEM, true, true},   NULL, 0u, TREE, TREE},
				[XTK_CTRL_LISTBOX]
                = {XTK_CTRL_LISTBOX,       "list-box",                listbox_props,       COUNT_OF(listbox_props),       listbox_events,      COUNT_OF(listbox_events),      {XTK_ACCESS_ROLE_LIST, true, true},        NULL, 0u, TREE, TREE},
				[XTK_CTRL_GRIDVIEW]
                = {XTK_CTRL_GRIDVIEW,      "grid-view",               gridview_props,      COUNT_OF(gridview_props),      gridview_events,     COUNT_OF(gridview_events),     {XTK_ACCESS_ROLE_LIST, true, true},        NULL, 0u, TREE, TREE},
				[XTK_CTRL_REPEATER]
                = {XTK_CTRL_REPEATER,      "items-repeater",          repeater_props,      COUNT_OF(repeater_props),      repeater_events,     COUNT_OF(repeater_events),     {XTK_ACCESS_ROLE_LIST, false, false},      NULL, 0u, TREE, TREE},
				[XTK_CTRL_ITEMSVIEW] = {XTK_CTRL_ITEMSVIEW,     "items-view",              itemsview_props,     COUNT_OF(itemsview_props),     itemsview_events,    COUNT_OF(itemsview_events),    {XTK_ACCESS_ROLE_LIST, true, true},        NULL, 0u, TREE, TREE},
				[XTK_CTRL_FLIP]
                = {XTK_CTRL_FLIP,          "flip-view",               flip_props,          COUNT_OF(flip_props),          flip_events,         COUNT_OF(flip_events),         {XTK_ACCESS_ROLE_GROUP, true, true},       NULL, 0u, TREE, TREE},
				[XTK_CTRL_PIPS]
                = {XTK_CTRL_PIPS,          "pips-pager",              pips_props,          COUNT_OF(pips_props),          pips_events,         COUNT_OF(pips_events),         {XTK_ACCESS_ROLE_GROUP, true, true},       NULL, 0u, TREE, TREE},
				[XTK_CTRL_SUGGEST]
                = {XTK_CTRL_SUGGEST,       "auto-suggest",            suggest_props,       COUNT_OF(suggest_props),       suggest_events,      COUNT_OF(suggest_events),      {XTK_ACCESS_ROLE_EDIT, true, true},        NULL, 0u, TREE, TREE},
				[XTK_CTRL_TOGGLESPLIT]
                = {XTK_CTRL_TOGGLESPLIT,   "toggle-split-button",     togglesplit_props,   COUNT_OF(togglesplit_props),   togglesplit_events,  COUNT_OF(togglesplit_events),  {XTK_ACCESS_ROLE_BUTTON, true, true},      NULL, 0u, TREE, TREE},
				[XTK_CTRL_RADIOGROUP]
                = {XTK_CTRL_RADIOGROUP,    "radio-buttons",           radiogroup_props,    COUNT_OF(radiogroup_props),    radiogroup_events,   COUNT_OF(radiogroup_events),   {XTK_ACCESS_ROLE_GROUP, true, true},       NULL, 0u, TREE, TREE},
				[XTK_CTRL_RATING]
                = {XTK_CTRL_RATING,        "rating",                  rating_props,        COUNT_OF(rating_props),        rating_events,       COUNT_OF(rating_events),       {XTK_ACCESS_ROLE_SLIDER, true, true},      NULL, 0u, TREE, TREE},
				[XTK_CTRL_SELECTOR]
                = {XTK_CTRL_SELECTOR,      "selector-bar",            selector_props,      COUNT_OF(selector_props),      selector_events,     COUNT_OF(selector_events),     {XTK_ACCESS_ROLE_GROUP, true, true},       NULL, 0u, TREE, TREE},
				[XTK_CTRL_SELECTORITEM]
                = {XTK_CTRL_SELECTORITEM,  "selector-bar-item",       selectoritem_props,  COUNT_OF(selectoritem_props),  selectoritem_events, COUNT_OF(selectoritem_events), {XTK_ACCESS_ROLE_LIST_ITEM, true, true},   NULL, 0u, TREE, TREE},
				[XTK_CTRL_BREADCRUMB]
                = {XTK_CTRL_BREADCRUMB,    "breadcrumb-bar",          breadcrumb_props,    COUNT_OF(breadcrumb_props),    breadcrumb_events,   COUNT_OF(breadcrumb_events),   {XTK_ACCESS_ROLE_GROUP, true, true},       NULL, 0u, TREE, TREE},
				[XTK_CTRL_CRUMB]
                = {XTK_CTRL_CRUMB,         "breadcrumb-item",         crumb_props,         COUNT_OF(crumb_props),         crumb_events,        COUNT_OF(crumb_events),        {XTK_ACCESS_ROLE_LIST_ITEM, true, true},   NULL, 0u, TREE, TREE},
				[XTK_CTRL_TEACHTIP]
                = {XTK_CTRL_TEACHTIP,      "teaching-tip",            teachtip_props,      COUNT_OF(teachtip_props),      teachtip_events,     COUNT_OF(teachtip_events),     {XTK_ACCESS_ROLE_GROUP, true, true},       NULL, 0u, TREE, TREE},
				[XTK_CTRL_TREE]
                = {XTK_CTRL_TREE,          "tree-view",               tree_props,          COUNT_OF(tree_props),          tree_events,         COUNT_OF(tree_events),         {XTK_ACCESS_ROLE_LIST, true, true},        NULL, 0u, TREE, TREE},
				[XTK_CTRL_TREEITEM]
                = {XTK_CTRL_TREEITEM,      "tree-item",               treeitem_props,      COUNT_OF(treeitem_props),      treeitem_events,     COUNT_OF(treeitem_events),     {XTK_ACCESS_ROLE_LIST_ITEM, true, true},   NULL, 0u, TREE, TREE},
				[XTK_CTRL_REFRESH]
                = {XTK_CTRL_REFRESH,       "refresh",                 refresh_props,       COUNT_OF(refresh_props),       refresh_events,      COUNT_OF(refresh_events),      {XTK_ACCESS_ROLE_GROUP, true, true},       NULL, 0u, TREE, TREE},
				[XTK_CTRL_AVATAR] = {XTK_CTRL_AVATAR,        "person-picture",          avatar_props,        COUNT_OF(avatar_props),        NULL,                0u,                            {XTK_ACCESS_ROLE_IMAGE, false, false},     NULL, 0u, TREE, TREE},
				[XTK_CTRL_PAGER]
                = {XTK_CTRL_PAGER,         "pager",                   pager_props,         COUNT_OF(pager_props),         pager_events,        COUNT_OF(pager_events),        {XTK_ACCESS_ROLE_GROUP, true, true},       NULL, 0u, TREE, TREE},
				[XTK_CTRL_SPLITVIEW]
                = {XTK_CTRL_SPLITVIEW,     "split-view",              splitview_props,     COUNT_OF(splitview_props),     NULL,                0u,                            {XTK_ACCESS_ROLE_GROUP, false, false},     NULL, 0u, TREE, TREE},
				[XTK_CTRL_SPLITPANE]
                = {XTK_CTRL_SPLITPANE,     "split-view-pane",         splitpane_props,     COUNT_OF(splitpane_props),     splitpane_events,    COUNT_OF(splitpane_events),    {XTK_ACCESS_ROLE_GROUP, false, false},     NULL, 0u, TREE, TREE},
				[XTK_CTRL_SPLITBODY]
                = {XTK_CTRL_SPLITBODY,     "split-view-content",      splitbody_props,     COUNT_OF(splitbody_props),     splitbody_events,    COUNT_OF(splitbody_events),    {XTK_ACCESS_ROLE_GROUP, false, false},     NULL, 0u, TREE, TREE},
				[XTK_CTRL_TITLEBAR]
                = {XTK_CTRL_TITLEBAR,      "title-bar",               titlebar_props,      COUNT_OF(titlebar_props),      titlebar_events,     COUNT_OF(titlebar_events),     {XTK_ACCESS_ROLE_GROUP, true, true},       NULL, 0u, TREE, TREE},
				[XTK_CTRL_SCROLLBAR] = {XTK_CTRL_SCROLLBAR,     "scroll-bar",              scrollbar_props,     COUNT_OF(scrollbar_props),     scrollbar_events,    COUNT_OF(scrollbar_events),    {XTK_ACCESS_ROLE_SCROLLBAR, false, false}, NULL, 0u, TREE, TREE},
				[XTK_CTRL_LOOPING]
                = {XTK_CTRL_LOOPING,       "looping-selector",        looping_props,       COUNT_OF(looping_props),       looping_events,      COUNT_OF(looping_events),      {XTK_ACCESS_ROLE_LIST, true, true},        NULL, 0u, TREE, TREE},
				[XTK_CTRL_LOOPITEM]
                = {XTK_CTRL_LOOPITEM,      "looping-selector-item",   loopitem_props,      COUNT_OF(loopitem_props),      NULL,                0u,                            {XTK_ACCESS_ROLE_LIST_ITEM, false, false}, NULL, 0u, TREE, TREE},
				[XTK_CTRL_DATEPICKER]
                = {XTK_CTRL_DATEPICKER,    "date-picker",             datepicker_props,    COUNT_OF(datepicker_props),    datepicker_events,   COUNT_OF(datepicker_events),   {XTK_ACCESS_ROLE_BUTTON, true, true},      NULL, 0u, TREE, TREE},
				[XTK_CTRL_TIMEPICKER] = {XTK_CTRL_TIMEPICKER,    "time-picker",             timepicker_props,    COUNT_OF(timepicker_props),    timepicker_events,   COUNT_OF(timepicker_events),   {XTK_ACCESS_ROLE_BUTTON, true, true},      NULL, 0u, TREE, TREE},
				[XTK_CTRL_PICKERFLYOUT]
                = {XTK_CTRL_PICKERFLYOUT,  "picker-flyout",           pickerflyout_props,  COUNT_OF(pickerflyout_props),  NULL,                0u,                            {XTK_ACCESS_ROLE_GROUP, false, false},     NULL, 0u, TREE, TREE},
				[XTK_CTRL_CALENDAR]
                = {XTK_CTRL_CALENDAR,      "calendar-view",           calendar_props,      COUNT_OF(calendar_props),      calendar_events,     COUNT_OF(calendar_events),     {XTK_ACCESS_ROLE_LIST, true, true},        NULL, 0u, TREE, TREE},
				[XTK_CTRL_CALDAY]
                = {XTK_CTRL_CALDAY,        "calendar-view-day-item",  calday_props,        COUNT_OF(calday_props),        NULL,                0u,                            {XTK_ACCESS_ROLE_LIST_ITEM, false, false}, NULL, 0u, TREE, TREE},
				[XTK_CTRL_COLORPICKER]
                = {XTK_CTRL_COLORPICKER,   "color-picker",            colorpicker_props,   COUNT_OF(colorpicker_props),   colorpicker_events,  COUNT_OF(colorpicker_events),  {XTK_ACCESS_ROLE_GROUP, false, false},     NULL, 0u, TREE, TREE},
				[XTK_CTRL_COLORSPECTRUM]
                = {XTK_CTRL_COLORSPECTRUM, "color-spectrum",          colorspectrum_props, COUNT_OF(colorspectrum_props), NULL,                0u,                            {XTK_ACCESS_ROLE_SLIDER, true, true},      NULL, 0u, TREE, TREE},
				[XTK_CTRL_COLORSLIDER]
                = {XTK_CTRL_COLORSLIDER,   "color-picker-slider",     colorslider_props,   COUNT_OF(colorslider_props),   NULL,                0u,                            {XTK_ACCESS_ROLE_SLIDER, true, true},      NULL, 0u, TREE, TREE},
				[XTK_CTRL_COLHEADER]
                = {XTK_CTRL_COLHEADER,     "column-header",           colheader_props,     COUNT_OF(colheader_props),     NULL,                0u,                            {XTK_ACCESS_ROLE_GROUP, false, false},     NULL, 0u, TREE, TREE},
				[XTK_CTRL_COLITEM]
                = {XTK_CTRL_COLITEM,       "column-header-item",      colitem_props,       COUNT_OF(colitem_props),       colitem_events,      COUNT_OF(colitem_events),      {XTK_ACCESS_ROLE_BUTTON, true, true},      NULL, 0u, TREE, TREE},
				[XTK_CTRL_COMMANDBAR]
                = {XTK_CTRL_COMMANDBAR,    "command-bar",             commandbar_props,    COUNT_OF(commandbar_props),    commandbar_events,   COUNT_OF(commandbar_events),   {XTK_ACCESS_ROLE_GROUP, false, false},     NULL, 0u, TREE, TREE},
				[XTK_CTRL_APPBARBUTTON]
                = {XTK_CTRL_APPBARBUTTON,  "app-bar-button",          appbarbutton_props,  COUNT_OF(appbarbutton_props),  appbarbutton_events, COUNT_OF(appbarbutton_events), {XTK_ACCESS_ROLE_BUTTON, true, true},      NULL, 0u, TREE, TREE},
				[XTK_CTRL_APPBARTOGGLE]
                = {XTK_CTRL_APPBARTOGGLE,  "app-bar-toggle-button",   appbartoggle_props,  COUNT_OF(appbartoggle_props),  appbartoggle_events, COUNT_OF(appbartoggle_events), {XTK_ACCESS_ROLE_CHECKBOX, true, true},    NULL, 0u, TREE, TREE},
				[XTK_CTRL_APPBARSEP]
                = {XTK_CTRL_APPBARSEP,     "app-bar-separator",       appbarsep_props,     COUNT_OF(appbarsep_props),     NULL,                0u,                            {XTK_ACCESS_ROLE_NONE, false, false},      NULL, 0u, TREE, TREE},
				[XTK_CTRL_CMDMORE]
                = {XTK_CTRL_CMDMORE,       "command-bar-more-button", cmdmore_props,       COUNT_OF(cmdmore_props),       NULL,                0u,                            {XTK_ACCESS_ROLE_BUTTON, true, true},      NULL, 0u, TREE, TREE},
				[XTK_CTRL_COLBUTTON]
                = {XTK_CTRL_COLBUTTON,     "column-header-button",    colbutton_props,     COUNT_OF(colbutton_props),     NULL,                0u,                            {XTK_ACCESS_ROLE_NONE, false, false},      NULL, 0u, TREE, TREE},
				[XTK_CTRL_GROUPHEADER]
                = {XTK_CTRL_GROUPHEADER,   "group-header",            groupheader_props,   COUNT_OF(groupheader_props),   NULL,                0u,                            {XTK_ACCESS_ROLE_GROUP, true, true},       NULL, 0u, TREE, TREE},
};

static bool id_in(uint32_t id, uint32_t const *ids, uint32_t count) {
	for (uint32_t i = 0; i < count; i++)
		if (ids [i] == id) return true;
	return false;
}

bool xtk_catalog_standard(XtkCtrlId id) { return id > XTK_CTRL_ID_INVALID && id < ( XtkCtrlId ) XTK_CTRL_TYPE_COUNT; }

XtkCtrlDesc const *xtk_catalog_control(XtkCtrlId id) { return xtk_catalog_standard(id) ? &controls [id] : NULL; }

XtkPropDesc const *xtk_catalog_property(XtkPropertyId id) {
	if (id == XTK_PROP_ID_INVALID || id >= ( XtkPropertyId ) XTK_PROP_STANDARD_COUNT) return NULL;
	return &properties [id];
}

XtkEventDesc const *xtk_catalog_event(XtkEventId id) {
	if (id == XTK_EVENT_ID_INVALID || id >= ( XtkEventId ) XTK_EVENT_STANDARD_COUNT) return NULL;
	return &events [id];
}

XtkPropDesc const *xtk_catalog_ctrlprop(XtkCtrlId control, XtkPropertyId property) {
	XtkCtrlDesc const *desc = xtk_catalog_control(control);
	if (!desc || !id_in(property, desc->properties, desc->property_count)) return NULL;
	return xtk_catalog_property(property);
}

XtkEventDesc const *xtk_catalog_ctrlevent(XtkCtrlId control, XtkEventId event) {
	XtkCtrlDesc const *desc = xtk_catalog_control(control);
	if (!desc || !id_in(event, desc->events, desc->event_count)) return NULL;
	return xtk_catalog_event(event);
}

uint32_t xtk_catalog_mirrors(XtkCtrlId control, XtkEventId event, XtkPropertyId *out) {
	if (event == XTK_EVENT_ID_INVALID || event >= ( XtkEventId ) XTK_EVENT_STANDARD_COUNT) return 0u;
	uint32_t kept = 0u;
	for (uint32_t i = 0; i < XTK_MIRROR_CANDIDATES && kept < XTK_MIRROR_MAX; i++) {
		XtkPropertyId id = mirrors [event][i];
		if (id != XTK_PROP_INVALID && xtk_catalog_ctrlprop(control, id)) out [kept++] = id;
	}
	return kept;
}
