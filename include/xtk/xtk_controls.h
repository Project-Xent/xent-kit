#ifndef XTK_CONTROLS_H
#define XTK_CONTROLS_H

#include "xtk_catalog.h"
#include "xtk_scene.h"

#include <stdint.h>

typedef struct XtkLayoutProps {
	uint64_t       set;
	XtkChangeStamp stamp;
	float          w;
	float          h;
	float          grow;
	float          shrink;
	XentFlexAlign  self;
	float          ml;
	float          mt;
	float          mr;
	float          mb;
	char const    *tip;
	uint32_t       tip_len;
} XtkLayoutProps;

#define XTK_LAYOUT_W_MASK      (1ull << 0u)
#define XTK_LAYOUT_H_MASK      (1ull << 1u)
#define XTK_LAYOUT_GROW_MASK   (1ull << 2u)
#define XTK_LAYOUT_SHRINK_MASK (1ull << 3u)
#define XTK_LAYOUT_SELF_MASK   (1ull << 4u)
#define XTK_LAYOUT_ML_MASK     (1ull << 5u)
#define XTK_LAYOUT_MT_MASK     (1ull << 6u)
#define XTK_LAYOUT_MR_MASK     (1ull << 7u)
#define XTK_LAYOUT_MB_MASK     (1ull << 8u)
#define XTK_LAYOUT_TIP_MASK    (1ull << 9u)

typedef struct XtkContainerProps {
	uint64_t          set;
	XtkChangeStamp    stamp;
	float             w;
	float             h;
	float             grow;
	float             shrink;
	XentFlexAlign     self;
	float             ml;
	float             mt;
	float             mr;
	float             mb;
	char const       *tip;
	uint32_t          tip_len;
	XtkStackDirection dir;
	XentFlexAlign     items;
	XentFlexJustify   justify;
	float             gap;
	float             pl;
	float             pt;
	float             pr;
	float             pb;
	bool              fill;
	bool              fitw;
	bool              fith;
	XentFlexWrap      wrap;
	XtkDropOperation  drop;
	char const       *dragtext;
	uint32_t          dragtext_len;
	char const       *dragfiles;
	uint32_t          dragfiles_len;
} XtkContainerProps;

#define XTK_CONTAINER_W_MASK         (1ull << 0u)
#define XTK_CONTAINER_H_MASK         (1ull << 1u)
#define XTK_CONTAINER_GROW_MASK      (1ull << 2u)
#define XTK_CONTAINER_SHRINK_MASK    (1ull << 3u)
#define XTK_CONTAINER_SELF_MASK      (1ull << 4u)
#define XTK_CONTAINER_ML_MASK        (1ull << 5u)
#define XTK_CONTAINER_MT_MASK        (1ull << 6u)
#define XTK_CONTAINER_MR_MASK        (1ull << 7u)
#define XTK_CONTAINER_MB_MASK        (1ull << 8u)
#define XTK_CONTAINER_TIP_MASK       (1ull << 9u)
#define XTK_CONTAINER_DIR_MASK       (1ull << 10u)
#define XTK_CONTAINER_ITEMS_MASK     (1ull << 11u)
#define XTK_CONTAINER_JUSTIFY_MASK   (1ull << 12u)
#define XTK_CONTAINER_GAP_MASK       (1ull << 13u)
#define XTK_CONTAINER_PL_MASK        (1ull << 14u)
#define XTK_CONTAINER_PT_MASK        (1ull << 15u)
#define XTK_CONTAINER_PR_MASK        (1ull << 16u)
#define XTK_CONTAINER_PB_MASK        (1ull << 17u)
#define XTK_CONTAINER_FILL_MASK      (1ull << 18u)
#define XTK_CONTAINER_FITW_MASK      (1ull << 19u)
#define XTK_CONTAINER_FITH_MASK      (1ull << 20u)
#define XTK_CONTAINER_WRAP_MASK      (1ull << 21u)
#define XTK_CONTAINER_DROP_MASK      (1ull << 22u)
#define XTK_CONTAINER_DRAGTEXT_MASK  (1ull << 23u)
#define XTK_CONTAINER_DRAGFILES_MASK (1ull << 24u)

typedef struct XtkScrollProps {
	uint64_t          set;
	XtkChangeStamp    stamp;
	float             w;
	float             h;
	float             grow;
	float             shrink;
	XentFlexAlign     self;
	float             ml;
	float             mt;
	float             mr;
	float             mb;
	char const       *tip;
	uint32_t          tip_len;
	XtkStackDirection dir;
	XentFlexAlign     items;
	XentFlexJustify   justify;
	float             gap;
	float             pl;
	float             pt;
	float             pr;
	float             pb;
	bool              fill;
	bool              fitw;
	bool              fith;
	XentFlexWrap      wrap;
	float             x;
	float             y;
} XtkScrollProps;

#define XTK_SCROLL_W_MASK       (1ull << 0u)
#define XTK_SCROLL_H_MASK       (1ull << 1u)
#define XTK_SCROLL_GROW_MASK    (1ull << 2u)
#define XTK_SCROLL_SHRINK_MASK  (1ull << 3u)
#define XTK_SCROLL_SELF_MASK    (1ull << 4u)
#define XTK_SCROLL_ML_MASK      (1ull << 5u)
#define XTK_SCROLL_MT_MASK      (1ull << 6u)
#define XTK_SCROLL_MR_MASK      (1ull << 7u)
#define XTK_SCROLL_MB_MASK      (1ull << 8u)
#define XTK_SCROLL_TIP_MASK     (1ull << 9u)
#define XTK_SCROLL_DIR_MASK     (1ull << 10u)
#define XTK_SCROLL_ITEMS_MASK   (1ull << 11u)
#define XTK_SCROLL_JUSTIFY_MASK (1ull << 12u)
#define XTK_SCROLL_GAP_MASK     (1ull << 13u)
#define XTK_SCROLL_PL_MASK      (1ull << 14u)
#define XTK_SCROLL_PT_MASK      (1ull << 15u)
#define XTK_SCROLL_PR_MASK      (1ull << 16u)
#define XTK_SCROLL_PB_MASK      (1ull << 17u)
#define XTK_SCROLL_FILL_MASK    (1ull << 18u)
#define XTK_SCROLL_FITW_MASK    (1ull << 19u)
#define XTK_SCROLL_FITH_MASK    (1ull << 20u)
#define XTK_SCROLL_WRAP_MASK    (1ull << 21u)
#define XTK_SCROLL_X_MASK       (1ull << 22u)
#define XTK_SCROLL_Y_MASK       (1ull << 23u)

typedef struct XtkTextProps {
	uint64_t       set;
	XtkChangeStamp stamp;
	float          w;
	float          h;
	float          grow;
	XentFlexAlign  self;
	float          ml;
	float          mt;
	float          mr;
	float          mb;
	char const    *text;
	uint32_t       text_len;
	char const    *tip;
	uint32_t       tip_len;
	float          fontsize;
	XtkFontWeight  fontweight;
	XtkTextAlign   textalign;
	XtkColor       fg;
	int32_t        maxlines;
	XtkTextTrim    trim;
	bool           textwrap;
	bool           selectable;
} XtkTextProps;

#define XTK_TEXT_W_MASK          (1ull << 0u)
#define XTK_TEXT_H_MASK          (1ull << 1u)
#define XTK_TEXT_GROW_MASK       (1ull << 2u)
#define XTK_TEXT_SELF_MASK       (1ull << 3u)
#define XTK_TEXT_ML_MASK         (1ull << 4u)
#define XTK_TEXT_MT_MASK         (1ull << 5u)
#define XTK_TEXT_MR_MASK         (1ull << 6u)
#define XTK_TEXT_MB_MASK         (1ull << 7u)
#define XTK_TEXT_TEXT_MASK       (1ull << 8u)
#define XTK_TEXT_TIP_MASK        (1ull << 9u)
#define XTK_TEXT_FONTSIZE_MASK   (1ull << 10u)
#define XTK_TEXT_FONTWEIGHT_MASK (1ull << 11u)
#define XTK_TEXT_TEXTALIGN_MASK  (1ull << 12u)
#define XTK_TEXT_FG_MASK         (1ull << 13u)
#define XTK_TEXT_MAXLINES_MASK   (1ull << 14u)
#define XTK_TEXT_TRIM_MASK       (1ull << 15u)
#define XTK_TEXT_TEXTWRAP_MASK   (1ull << 16u)
#define XTK_TEXT_SELECTABLE_MASK (1ull << 17u)

typedef struct XtkButtonProps {
	uint64_t       set;
	XtkChangeStamp stamp;
	float          w;
	float          h;
	float          grow;
	XentFlexAlign  self;
	float          ml;
	float          mt;
	float          mr;
	float          mb;
	char const    *text;
	uint32_t       text_len;
	char const    *tip;
	uint32_t       tip_len;
	bool           enabled;
	char const    *icon;
	uint32_t       icon_len;
	XtkButtonStyle style;
} XtkButtonProps;

#define XTK_BUTTON_W_MASK       (1ull << 0u)
#define XTK_BUTTON_H_MASK       (1ull << 1u)
#define XTK_BUTTON_GROW_MASK    (1ull << 2u)
#define XTK_BUTTON_SELF_MASK    (1ull << 3u)
#define XTK_BUTTON_ML_MASK      (1ull << 4u)
#define XTK_BUTTON_MT_MASK      (1ull << 5u)
#define XTK_BUTTON_MR_MASK      (1ull << 6u)
#define XTK_BUTTON_MB_MASK      (1ull << 7u)
#define XTK_BUTTON_TEXT_MASK    (1ull << 8u)
#define XTK_BUTTON_TIP_MASK     (1ull << 9u)
#define XTK_BUTTON_ENABLED_MASK (1ull << 10u)
#define XTK_BUTTON_ICON_MASK    (1ull << 11u)
#define XTK_BUTTON_STYLE_MASK   (1ull << 12u)

typedef struct XtkToggleProps {
	uint64_t       set;
	XtkChangeStamp stamp;
	float          w;
	float          h;
	float          grow;
	XentFlexAlign  self;
	float          ml;
	float          mt;
	float          mr;
	float          mb;
	char const    *text;
	uint32_t       text_len;
	char const    *tip;
	uint32_t       tip_len;
	bool           enabled;
	bool           checked;
} XtkToggleProps;

#define XTK_TOGGLE_W_MASK       (1ull << 0u)
#define XTK_TOGGLE_H_MASK       (1ull << 1u)
#define XTK_TOGGLE_GROW_MASK    (1ull << 2u)
#define XTK_TOGGLE_SELF_MASK    (1ull << 3u)
#define XTK_TOGGLE_ML_MASK      (1ull << 4u)
#define XTK_TOGGLE_MT_MASK      (1ull << 5u)
#define XTK_TOGGLE_MR_MASK      (1ull << 6u)
#define XTK_TOGGLE_MB_MASK      (1ull << 7u)
#define XTK_TOGGLE_TEXT_MASK    (1ull << 8u)
#define XTK_TOGGLE_TIP_MASK     (1ull << 9u)
#define XTK_TOGGLE_ENABLED_MASK (1ull << 10u)
#define XTK_TOGGLE_CHECKED_MASK (1ull << 11u)

typedef struct XtkCheckBoxProps {
	uint64_t       set;
	XtkChangeStamp stamp;
	float          w;
	float          h;
	float          grow;
	XentFlexAlign  self;
	float          ml;
	float          mt;
	float          mr;
	float          mb;
	char const    *text;
	uint32_t       text_len;
	char const    *tip;
	uint32_t       tip_len;
	bool           enabled;
	bool           checked;
	bool           indeterminate;
	bool           threestate;
} XtkCheckBoxProps;

#define XTK_CHECKBOX_W_MASK             (1ull << 0u)
#define XTK_CHECKBOX_H_MASK             (1ull << 1u)
#define XTK_CHECKBOX_GROW_MASK          (1ull << 2u)
#define XTK_CHECKBOX_SELF_MASK          (1ull << 3u)
#define XTK_CHECKBOX_ML_MASK            (1ull << 4u)
#define XTK_CHECKBOX_MT_MASK            (1ull << 5u)
#define XTK_CHECKBOX_MR_MASK            (1ull << 6u)
#define XTK_CHECKBOX_MB_MASK            (1ull << 7u)
#define XTK_CHECKBOX_TEXT_MASK          (1ull << 8u)
#define XTK_CHECKBOX_TIP_MASK           (1ull << 9u)
#define XTK_CHECKBOX_ENABLED_MASK       (1ull << 10u)
#define XTK_CHECKBOX_CHECKED_MASK       (1ull << 11u)
#define XTK_CHECKBOX_INDETERMINATE_MASK (1ull << 12u)
#define XTK_CHECKBOX_THREESTATE_MASK    (1ull << 13u)

typedef struct XtkSliderProps {
	uint64_t          set;
	XtkChangeStamp    stamp;
	float             w;
	float             h;
	float             grow;
	XentFlexAlign     self;
	float             ml;
	float             mt;
	float             mr;
	float             mb;
	char const       *tip;
	uint32_t          tip_len;
	bool              enabled;
	float             min;
	float             max;
	float             value;
	float             step;
	float             tick;
	XtkTickPlacement  tickplace;
	XtkSliderSnap     snapsto;
	float             smallchange;
	float             largechange;
	XtkStackDirection dir;
	bool              range;
	float             rangestart;
	float             rangeend;
} XtkSliderProps;

#define XTK_SLIDER_W_MASK           (1ull << 0u)
#define XTK_SLIDER_H_MASK           (1ull << 1u)
#define XTK_SLIDER_GROW_MASK        (1ull << 2u)
#define XTK_SLIDER_SELF_MASK        (1ull << 3u)
#define XTK_SLIDER_ML_MASK          (1ull << 4u)
#define XTK_SLIDER_MT_MASK          (1ull << 5u)
#define XTK_SLIDER_MR_MASK          (1ull << 6u)
#define XTK_SLIDER_MB_MASK          (1ull << 7u)
#define XTK_SLIDER_TIP_MASK         (1ull << 8u)
#define XTK_SLIDER_ENABLED_MASK     (1ull << 9u)
#define XTK_SLIDER_MIN_MASK         (1ull << 10u)
#define XTK_SLIDER_MAX_MASK         (1ull << 11u)
#define XTK_SLIDER_VALUE_MASK       (1ull << 12u)
#define XTK_SLIDER_STEP_MASK        (1ull << 13u)
#define XTK_SLIDER_TICK_MASK        (1ull << 14u)
#define XTK_SLIDER_TICKPLACE_MASK   (1ull << 15u)
#define XTK_SLIDER_SNAPSTO_MASK     (1ull << 16u)
#define XTK_SLIDER_SMALLCHANGE_MASK (1ull << 17u)
#define XTK_SLIDER_LARGECHANGE_MASK (1ull << 18u)
#define XTK_SLIDER_DIR_MASK         (1ull << 19u)
#define XTK_SLIDER_RANGE_MASK       (1ull << 20u)
#define XTK_SLIDER_RANGESTART_MASK  (1ull << 21u)
#define XTK_SLIDER_RANGEEND_MASK    (1ull << 22u)

typedef struct XtkInputProps {
	uint64_t       set;
	XtkChangeStamp stamp;
	float          w;
	float          h;
	float          grow;
	XentFlexAlign  self;
	float          ml;
	float          mt;
	float          mr;
	float          mb;
	char const    *text;
	uint32_t       text_len;
	char const    *tip;
	uint32_t       tip_len;
	bool           enabled;
	char const    *placeholder;
	uint32_t       placeholder_len;
} XtkInputProps;

#define XTK_INPUT_W_MASK           (1ull << 0u)
#define XTK_INPUT_H_MASK           (1ull << 1u)
#define XTK_INPUT_GROW_MASK        (1ull << 2u)
#define XTK_INPUT_SELF_MASK        (1ull << 3u)
#define XTK_INPUT_ML_MASK          (1ull << 4u)
#define XTK_INPUT_MT_MASK          (1ull << 5u)
#define XTK_INPUT_MR_MASK          (1ull << 6u)
#define XTK_INPUT_MB_MASK          (1ull << 7u)
#define XTK_INPUT_TEXT_MASK        (1ull << 8u)
#define XTK_INPUT_TIP_MASK         (1ull << 9u)
#define XTK_INPUT_ENABLED_MASK     (1ull << 10u)
#define XTK_INPUT_PLACEHOLDER_MASK (1ull << 11u)

typedef struct XtkTextBoxProps {
	uint64_t       set;
	XtkChangeStamp stamp;
	float          w;
	float          h;
	float          grow;
	XentFlexAlign  self;
	float          ml;
	float          mt;
	float          mr;
	float          mb;
	char const    *text;
	uint32_t       text_len;
	char const    *tip;
	uint32_t       tip_len;
	bool           enabled;
	char const    *placeholder;
	uint32_t       placeholder_len;
	bool           multiline;
	bool           readonly;
} XtkTextBoxProps;

#define XTK_TEXTBOX_W_MASK           (1ull << 0u)
#define XTK_TEXTBOX_H_MASK           (1ull << 1u)
#define XTK_TEXTBOX_GROW_MASK        (1ull << 2u)
#define XTK_TEXTBOX_SELF_MASK        (1ull << 3u)
#define XTK_TEXTBOX_ML_MASK          (1ull << 4u)
#define XTK_TEXTBOX_MT_MASK          (1ull << 5u)
#define XTK_TEXTBOX_MR_MASK          (1ull << 6u)
#define XTK_TEXTBOX_MB_MASK          (1ull << 7u)
#define XTK_TEXTBOX_TEXT_MASK        (1ull << 8u)
#define XTK_TEXTBOX_TIP_MASK         (1ull << 9u)
#define XTK_TEXTBOX_ENABLED_MASK     (1ull << 10u)
#define XTK_TEXTBOX_PLACEHOLDER_MASK (1ull << 11u)
#define XTK_TEXTBOX_MULTILINE_MASK   (1ull << 12u)
#define XTK_TEXTBOX_READONLY_MASK    (1ull << 13u)

typedef struct XtkImageProps {
	uint64_t        set;
	XtkChangeStamp  stamp;
	float           w;
	float           h;
	float           grow;
	XentFlexAlign   self;
	float           ml;
	float           mt;
	float           mr;
	float           mb;
	char const     *tip;
	uint32_t        tip_len;
	XtkResource     src;
	XtkImageStretch fit;
} XtkImageProps;

#define XTK_IMAGE_W_MASK    (1ull << 0u)
#define XTK_IMAGE_H_MASK    (1ull << 1u)
#define XTK_IMAGE_GROW_MASK (1ull << 2u)
#define XTK_IMAGE_SELF_MASK (1ull << 3u)
#define XTK_IMAGE_ML_MASK   (1ull << 4u)
#define XTK_IMAGE_MT_MASK   (1ull << 5u)
#define XTK_IMAGE_MR_MASK   (1ull << 6u)
#define XTK_IMAGE_MB_MASK   (1ull << 7u)
#define XTK_IMAGE_TIP_MASK  (1ull << 8u)
#define XTK_IMAGE_SRC_MASK  (1ull << 9u)
#define XTK_IMAGE_FIT_MASK  (1ull << 10u)

typedef struct XtkProgressProps {
	uint64_t         set;
	XtkChangeStamp   stamp;
	float            w;
	float            h;
	float            grow;
	XentFlexAlign    self;
	float            ml;
	float            mt;
	float            mr;
	float            mb;
	char const      *tip;
	uint32_t         tip_len;
	float            min;
	float            max;
	float            value;
	bool             indeterminate;
	XtkProgressState state;
	bool             active;
	float            pl;
	float            pt;
	float            pr;
	float            pb;
	float            border_width;
} XtkProgressProps;

#define XTK_PROGRESS_W_MASK             (1ull << 0u)
#define XTK_PROGRESS_H_MASK             (1ull << 1u)
#define XTK_PROGRESS_GROW_MASK          (1ull << 2u)
#define XTK_PROGRESS_SELF_MASK          (1ull << 3u)
#define XTK_PROGRESS_ML_MASK            (1ull << 4u)
#define XTK_PROGRESS_MT_MASK            (1ull << 5u)
#define XTK_PROGRESS_MR_MASK            (1ull << 6u)
#define XTK_PROGRESS_MB_MASK            (1ull << 7u)
#define XTK_PROGRESS_TIP_MASK           (1ull << 8u)
#define XTK_PROGRESS_MIN_MASK           (1ull << 9u)
#define XTK_PROGRESS_MAX_MASK           (1ull << 10u)
#define XTK_PROGRESS_VALUE_MASK         (1ull << 11u)
#define XTK_PROGRESS_INDETERMINATE_MASK (1ull << 12u)
#define XTK_PROGRESS_STATE_MASK         (1ull << 13u)
#define XTK_PROGRESS_ACTIVE_MASK        (1ull << 14u)
#define XTK_PROGRESS_PL_MASK            (1ull << 15u)
#define XTK_PROGRESS_PT_MASK            (1ull << 16u)
#define XTK_PROGRESS_PR_MASK            (1ull << 17u)
#define XTK_PROGRESS_PB_MASK            (1ull << 18u)
#define XTK_PROGRESS_BORDER_WIDTH_MASK  (1ull << 19u)

typedef struct XtkNumberProps {
	uint64_t       set;
	XtkChangeStamp stamp;
	float          w;
	float          h;
	float          grow;
	XentFlexAlign  self;
	float          ml;
	float          mt;
	float          mr;
	float          mb;
	char const    *tip;
	uint32_t       tip_len;
	bool           enabled;
	double         value;
	double         min;
	double         max;
	double         step;
	bool           hidespin;
} XtkNumberProps;

#define XTK_NUMBER_W_MASK        (1ull << 0u)
#define XTK_NUMBER_H_MASK        (1ull << 1u)
#define XTK_NUMBER_GROW_MASK     (1ull << 2u)
#define XTK_NUMBER_SELF_MASK     (1ull << 3u)
#define XTK_NUMBER_ML_MASK       (1ull << 4u)
#define XTK_NUMBER_MT_MASK       (1ull << 5u)
#define XTK_NUMBER_MR_MASK       (1ull << 6u)
#define XTK_NUMBER_MB_MASK       (1ull << 7u)
#define XTK_NUMBER_TIP_MASK      (1ull << 8u)
#define XTK_NUMBER_ENABLED_MASK  (1ull << 9u)
#define XTK_NUMBER_VALUE_MASK    (1ull << 10u)
#define XTK_NUMBER_MIN_MASK      (1ull << 11u)
#define XTK_NUMBER_MAX_MASK      (1ull << 12u)
#define XTK_NUMBER_STEP_MASK     (1ull << 13u)
#define XTK_NUMBER_HIDESPIN_MASK (1ull << 14u)

typedef struct XtkItemProps {
	uint64_t       set;
	XtkChangeStamp stamp;
	float          w;
	float          h;
	float          grow;
	XentFlexAlign  self;
	float          ml;
	float          mt;
	float          mr;
	float          mb;
	char const    *text;
	uint32_t       text_len;
	char const    *tip;
	uint32_t       tip_len;
	char const    *icon;
	uint32_t       icon_len;
	bool           enabled;
	bool           selected;
	bool           expanded;
} XtkItemProps;

#define XTK_ITEM_W_MASK        (1ull << 0u)
#define XTK_ITEM_H_MASK        (1ull << 1u)
#define XTK_ITEM_GROW_MASK     (1ull << 2u)
#define XTK_ITEM_SELF_MASK     (1ull << 3u)
#define XTK_ITEM_ML_MASK       (1ull << 4u)
#define XTK_ITEM_MT_MASK       (1ull << 5u)
#define XTK_ITEM_MR_MASK       (1ull << 6u)
#define XTK_ITEM_MB_MASK       (1ull << 7u)
#define XTK_ITEM_TEXT_MASK     (1ull << 8u)
#define XTK_ITEM_TIP_MASK      (1ull << 9u)
#define XTK_ITEM_ICON_MASK     (1ull << 10u)
#define XTK_ITEM_ENABLED_MASK  (1ull << 11u)
#define XTK_ITEM_SELECTED_MASK (1ull << 12u)
#define XTK_ITEM_EXPANDED_MASK (1ull << 13u)

typedef struct XtkSelectionProps {
	uint64_t       set;
	XtkChangeStamp stamp;
	float          w;
	float          h;
	float          grow;
	XentFlexAlign  self;
	float          ml;
	float          mt;
	float          mr;
	float          mb;
	char const    *tip;
	uint32_t       tip_len;
	bool           enabled;
	int32_t        sel;
	int32_t        nitem;
} XtkSelectionProps;

#define XTK_SELECTION_W_MASK       (1ull << 0u)
#define XTK_SELECTION_H_MASK       (1ull << 1u)
#define XTK_SELECTION_GROW_MASK    (1ull << 2u)
#define XTK_SELECTION_SELF_MASK    (1ull << 3u)
#define XTK_SELECTION_ML_MASK      (1ull << 4u)
#define XTK_SELECTION_MT_MASK      (1ull << 5u)
#define XTK_SELECTION_MR_MASK      (1ull << 6u)
#define XTK_SELECTION_MB_MASK      (1ull << 7u)
#define XTK_SELECTION_TIP_MASK     (1ull << 8u)
#define XTK_SELECTION_ENABLED_MASK (1ull << 9u)
#define XTK_SELECTION_SEL_MASK     (1ull << 10u)
#define XTK_SELECTION_NITEM_MASK   (1ull << 11u)

typedef struct XtkNavProps {
	uint64_t       set;
	XtkChangeStamp stamp;
	float          w;
	float          h;
	float          grow;
	XentFlexAlign  self;
	float          ml;
	float          mt;
	float          mr;
	float          mb;
	char const    *tip;
	uint32_t       tip_len;
	bool           enabled;
	int32_t        sel;
} XtkNavProps;

#define XTK_NAV_W_MASK       (1ull << 0u)
#define XTK_NAV_H_MASK       (1ull << 1u)
#define XTK_NAV_GROW_MASK    (1ull << 2u)
#define XTK_NAV_SELF_MASK    (1ull << 3u)
#define XTK_NAV_ML_MASK      (1ull << 4u)
#define XTK_NAV_MT_MASK      (1ull << 5u)
#define XTK_NAV_MR_MASK      (1ull << 6u)
#define XTK_NAV_MB_MASK      (1ull << 7u)
#define XTK_NAV_TIP_MASK     (1ull << 8u)
#define XTK_NAV_ENABLED_MASK (1ull << 9u)
#define XTK_NAV_SEL_MASK     (1ull << 10u)

typedef struct XtkListProps {
	uint64_t       set;
	XtkChangeStamp stamp;
	float          w;
	float          h;
	float          grow;
	XentFlexAlign  self;
	float          ml;
	float          mt;
	float          mr;
	float          mb;
	char const    *tip;
	uint32_t       tip_len;
	bool           enabled;
	int32_t        sel;
	int32_t        nitem;
	float          itemh;
	float          itemw;
	int32_t        ncol;
	XtkListSelMode mode;
	int32_t        first;
} XtkListProps;

#define XTK_LIST_W_MASK       (1ull << 0u)
#define XTK_LIST_H_MASK       (1ull << 1u)
#define XTK_LIST_GROW_MASK    (1ull << 2u)
#define XTK_LIST_SELF_MASK    (1ull << 3u)
#define XTK_LIST_ML_MASK      (1ull << 4u)
#define XTK_LIST_MT_MASK      (1ull << 5u)
#define XTK_LIST_MR_MASK      (1ull << 6u)
#define XTK_LIST_MB_MASK      (1ull << 7u)
#define XTK_LIST_TIP_MASK     (1ull << 8u)
#define XTK_LIST_ENABLED_MASK (1ull << 9u)
#define XTK_LIST_SEL_MASK     (1ull << 10u)
#define XTK_LIST_NITEM_MASK   (1ull << 11u)
#define XTK_LIST_ITEMH_MASK   (1ull << 12u)
#define XTK_LIST_ITEMW_MASK   (1ull << 13u)
#define XTK_LIST_NCOL_MASK    (1ull << 14u)
#define XTK_LIST_MODE_MASK    (1ull << 15u)
#define XTK_LIST_FIRST_MASK   (1ull << 16u)

typedef struct XtkRadioGroupProps {
	uint64_t       set;
	XtkChangeStamp stamp;
	float          w;
	float          h;
	float          grow;
	XentFlexAlign  self;
	float          ml;
	float          mt;
	float          mr;
	float          mb;
	char const    *tip;
	uint32_t       tip_len;
	bool           enabled;
	int32_t        sel;
	int32_t        nitem;
	int32_t        ncol;
} XtkRadioGroupProps;

#define XTK_RADIOGROUP_W_MASK       (1ull << 0u)
#define XTK_RADIOGROUP_H_MASK       (1ull << 1u)
#define XTK_RADIOGROUP_GROW_MASK    (1ull << 2u)
#define XTK_RADIOGROUP_SELF_MASK    (1ull << 3u)
#define XTK_RADIOGROUP_ML_MASK      (1ull << 4u)
#define XTK_RADIOGROUP_MT_MASK      (1ull << 5u)
#define XTK_RADIOGROUP_MR_MASK      (1ull << 6u)
#define XTK_RADIOGROUP_MB_MASK      (1ull << 7u)
#define XTK_RADIOGROUP_TIP_MASK     (1ull << 8u)
#define XTK_RADIOGROUP_ENABLED_MASK (1ull << 9u)
#define XTK_RADIOGROUP_SEL_MASK     (1ull << 10u)
#define XTK_RADIOGROUP_NITEM_MASK   (1ull << 11u)
#define XTK_RADIOGROUP_NCOL_MASK    (1ull << 12u)

typedef struct XtkTreeProps {
	uint64_t       set;
	XtkChangeStamp stamp;
	float          w;
	float          h;
	float          grow;
	XentFlexAlign  self;
	float          ml;
	float          mt;
	float          mr;
	float          mb;
	char const    *tip;
	uint32_t       tip_len;
	bool           enabled;
	int32_t        sel;
	int32_t        nitem;
	float          itemh;
} XtkTreeProps;

#define XTK_TREE_W_MASK       (1ull << 0u)
#define XTK_TREE_H_MASK       (1ull << 1u)
#define XTK_TREE_GROW_MASK    (1ull << 2u)
#define XTK_TREE_SELF_MASK    (1ull << 3u)
#define XTK_TREE_ML_MASK      (1ull << 4u)
#define XTK_TREE_MT_MASK      (1ull << 5u)
#define XTK_TREE_MR_MASK      (1ull << 6u)
#define XTK_TREE_MB_MASK      (1ull << 7u)
#define XTK_TREE_TIP_MASK     (1ull << 8u)
#define XTK_TREE_ENABLED_MASK (1ull << 9u)
#define XTK_TREE_SEL_MASK     (1ull << 10u)
#define XTK_TREE_NITEM_MASK   (1ull << 11u)
#define XTK_TREE_ITEMH_MASK   (1ull << 12u)

typedef struct XtkComboProps {
	uint64_t       set;
	XtkChangeStamp stamp;
	float          w;
	float          h;
	float          grow;
	XentFlexAlign  self;
	float          ml;
	float          mt;
	float          mr;
	float          mb;
	char const    *tip;
	uint32_t       tip_len;
	bool           enabled;
	char const    *placeholder;
	uint32_t       placeholder_len;
	int32_t        sel;
	char const    *text;
	uint32_t       text_len;
	bool           editable;
} XtkComboProps;

#define XTK_COMBO_W_MASK           (1ull << 0u)
#define XTK_COMBO_H_MASK           (1ull << 1u)
#define XTK_COMBO_GROW_MASK        (1ull << 2u)
#define XTK_COMBO_SELF_MASK        (1ull << 3u)
#define XTK_COMBO_ML_MASK          (1ull << 4u)
#define XTK_COMBO_MT_MASK          (1ull << 5u)
#define XTK_COMBO_MR_MASK          (1ull << 6u)
#define XTK_COMBO_MB_MASK          (1ull << 7u)
#define XTK_COMBO_TIP_MASK         (1ull << 8u)
#define XTK_COMBO_ENABLED_MASK     (1ull << 9u)
#define XTK_COMBO_PLACEHOLDER_MASK (1ull << 10u)
#define XTK_COMBO_SEL_MASK         (1ull << 11u)
#define XTK_COMBO_TEXT_MASK        (1ull << 12u)
#define XTK_COMBO_EDITABLE_MASK    (1ull << 13u)

typedef struct XtkOverlayProps {
	uint64_t       set;
	XtkChangeStamp stamp;
	float          w;
	float          h;
	float          grow;
	XentFlexAlign  self;
	float          ml;
	float          mt;
	float          mr;
	float          mb;
	char const    *text;
	uint32_t       text_len;
	char const    *tip;
	uint32_t       tip_len;
	bool           open;
	bool           enabled;
} XtkOverlayProps;

#define XTK_OVERLAY_W_MASK       (1ull << 0u)
#define XTK_OVERLAY_H_MASK       (1ull << 1u)
#define XTK_OVERLAY_GROW_MASK    (1ull << 2u)
#define XTK_OVERLAY_SELF_MASK    (1ull << 3u)
#define XTK_OVERLAY_ML_MASK      (1ull << 4u)
#define XTK_OVERLAY_MT_MASK      (1ull << 5u)
#define XTK_OVERLAY_MR_MASK      (1ull << 6u)
#define XTK_OVERLAY_MB_MASK      (1ull << 7u)
#define XTK_OVERLAY_TEXT_MASK    (1ull << 8u)
#define XTK_OVERLAY_TIP_MASK     (1ull << 9u)
#define XTK_OVERLAY_OPEN_MASK    (1ull << 10u)
#define XTK_OVERLAY_ENABLED_MASK (1ull << 11u)

typedef struct XtkItemsViewProps {
	uint64_t       set;
	XtkChangeStamp stamp;
	float          w;
	float          h;
	float          grow;
	XentFlexAlign  self;
	float          ml;
	float          mt;
	float          mr;
	float          mb;
	char const    *tip;
	uint32_t       tip_len;
	bool           enabled;
	int32_t        sel;
	int32_t        nitem;
	float          itemh;
	float          itemw;
	int32_t        ncol;
	XtkListSelMode mode;
	bool           invoked;
	int32_t        first;
} XtkItemsViewProps;

#define XTK_ITEMSVIEW_W_MASK       (1ull << 0u)
#define XTK_ITEMSVIEW_H_MASK       (1ull << 1u)
#define XTK_ITEMSVIEW_GROW_MASK    (1ull << 2u)
#define XTK_ITEMSVIEW_SELF_MASK    (1ull << 3u)
#define XTK_ITEMSVIEW_ML_MASK      (1ull << 4u)
#define XTK_ITEMSVIEW_MT_MASK      (1ull << 5u)
#define XTK_ITEMSVIEW_MR_MASK      (1ull << 6u)
#define XTK_ITEMSVIEW_MB_MASK      (1ull << 7u)
#define XTK_ITEMSVIEW_TIP_MASK     (1ull << 8u)
#define XTK_ITEMSVIEW_ENABLED_MASK (1ull << 9u)
#define XTK_ITEMSVIEW_SEL_MASK     (1ull << 10u)
#define XTK_ITEMSVIEW_NITEM_MASK   (1ull << 11u)
#define XTK_ITEMSVIEW_ITEMH_MASK   (1ull << 12u)
#define XTK_ITEMSVIEW_ITEMW_MASK   (1ull << 13u)
#define XTK_ITEMSVIEW_NCOL_MASK    (1ull << 14u)
#define XTK_ITEMSVIEW_MODE_MASK    (1ull << 15u)
#define XTK_ITEMSVIEW_INVOKED_MASK (1ull << 16u)
#define XTK_ITEMSVIEW_FIRST_MASK   (1ull << 17u)

typedef struct XtkExpanderProps {
	uint64_t       set;
	XtkChangeStamp stamp;
	float          w;
	float          h;
	float          grow;
	XentFlexAlign  self;
	float          ml;
	float          mt;
	float          mr;
	float          mb;
	char const    *text;
	uint32_t       text_len;
	char const    *tip;
	uint32_t       tip_len;
	bool           expanded;
	float          contenth;
} XtkExpanderProps;

#define XTK_EXPANDER_W_MASK        (1ull << 0u)
#define XTK_EXPANDER_H_MASK        (1ull << 1u)
#define XTK_EXPANDER_GROW_MASK     (1ull << 2u)
#define XTK_EXPANDER_SELF_MASK     (1ull << 3u)
#define XTK_EXPANDER_ML_MASK       (1ull << 4u)
#define XTK_EXPANDER_MT_MASK       (1ull << 5u)
#define XTK_EXPANDER_MR_MASK       (1ull << 6u)
#define XTK_EXPANDER_MB_MASK       (1ull << 7u)
#define XTK_EXPANDER_TEXT_MASK     (1ull << 8u)
#define XTK_EXPANDER_TIP_MASK      (1ull << 9u)
#define XTK_EXPANDER_EXPANDED_MASK (1ull << 10u)
#define XTK_EXPANDER_CONTENTH_MASK (1ull << 11u)

typedef struct XtkInfoBarProps {
	uint64_t           set;
	XtkChangeStamp     stamp;
	float              w;
	float              h;
	float              grow;
	XentFlexAlign      self;
	float              ml;
	float              mt;
	float              mr;
	float              mb;
	char const        *text;
	uint32_t           text_len;
	char const        *message;
	uint32_t           message_len;
	char const        *tip;
	uint32_t           tip_len;
	XtkInfoBarSeverity severity;
	bool               closable;
} XtkInfoBarProps;

#define XTK_INFOBAR_W_MASK        (1ull << 0u)
#define XTK_INFOBAR_H_MASK        (1ull << 1u)
#define XTK_INFOBAR_GROW_MASK     (1ull << 2u)
#define XTK_INFOBAR_SELF_MASK     (1ull << 3u)
#define XTK_INFOBAR_ML_MASK       (1ull << 4u)
#define XTK_INFOBAR_MT_MASK       (1ull << 5u)
#define XTK_INFOBAR_MR_MASK       (1ull << 6u)
#define XTK_INFOBAR_MB_MASK       (1ull << 7u)
#define XTK_INFOBAR_TEXT_MASK     (1ull << 8u)
#define XTK_INFOBAR_MESSAGE_MASK  (1ull << 9u)
#define XTK_INFOBAR_TIP_MASK      (1ull << 10u)
#define XTK_INFOBAR_SEVERITY_MASK (1ull << 11u)
#define XTK_INFOBAR_CLOSABLE_MASK (1ull << 12u)

typedef struct XtkRefreshProps {
	uint64_t         set;
	XtkChangeStamp   stamp;
	float            w;
	float            h;
	float            grow;
	XentFlexAlign    self;
	float            ml;
	float            mt;
	float            mr;
	float            mb;
	char const      *tip;
	uint32_t         tip_len;
	XtkPullDirection direction;
	float            visualizer;
	float            threshold;
	bool             refreshing;
} XtkRefreshProps;

#define XTK_REFRESH_W_MASK          (1ull << 0u)
#define XTK_REFRESH_H_MASK          (1ull << 1u)
#define XTK_REFRESH_GROW_MASK       (1ull << 2u)
#define XTK_REFRESH_SELF_MASK       (1ull << 3u)
#define XTK_REFRESH_ML_MASK         (1ull << 4u)
#define XTK_REFRESH_MT_MASK         (1ull << 5u)
#define XTK_REFRESH_MR_MASK         (1ull << 6u)
#define XTK_REFRESH_MB_MASK         (1ull << 7u)
#define XTK_REFRESH_TIP_MASK        (1ull << 8u)
#define XTK_REFRESH_DIRECTION_MASK  (1ull << 9u)
#define XTK_REFRESH_VISUALIZER_MASK (1ull << 10u)
#define XTK_REFRESH_THRESHOLD_MASK  (1ull << 11u)
#define XTK_REFRESH_REFRESHING_MASK (1ull << 12u)

typedef struct XtkFlipProps {
	uint64_t          set;
	XtkChangeStamp    stamp;
	float             w;
	float             h;
	float             grow;
	XentFlexAlign     self;
	float             ml;
	float             mt;
	float             mr;
	float             mb;
	char const       *tip;
	uint32_t          tip_len;
	int32_t           sel;
	XtkStackDirection dir;
} XtkFlipProps;

#define XTK_FLIP_W_MASK    (1ull << 0u)
#define XTK_FLIP_H_MASK    (1ull << 1u)
#define XTK_FLIP_GROW_MASK (1ull << 2u)
#define XTK_FLIP_SELF_MASK (1ull << 3u)
#define XTK_FLIP_ML_MASK   (1ull << 4u)
#define XTK_FLIP_MT_MASK   (1ull << 5u)
#define XTK_FLIP_MR_MASK   (1ull << 6u)
#define XTK_FLIP_MB_MASK   (1ull << 7u)
#define XTK_FLIP_TIP_MASK  (1ull << 8u)
#define XTK_FLIP_SEL_MASK  (1ull << 9u)
#define XTK_FLIP_DIR_MASK  (1ull << 10u)

typedef struct XtkPipsProps {
	uint64_t          set;
	XtkChangeStamp    stamp;
	float             w;
	float             h;
	float             grow;
	XentFlexAlign     self;
	float             ml;
	float             mt;
	float             mr;
	float             mb;
	char const       *tip;
	uint32_t          tip_len;
	int32_t           sel;
	int32_t           nitem;
	XtkStackDirection dir;
	int32_t           maxvisible;
	XtkPipsNavVis     nav;
} XtkPipsProps;

#define XTK_PIPS_W_MASK          (1ull << 0u)
#define XTK_PIPS_H_MASK          (1ull << 1u)
#define XTK_PIPS_GROW_MASK       (1ull << 2u)
#define XTK_PIPS_SELF_MASK       (1ull << 3u)
#define XTK_PIPS_ML_MASK         (1ull << 4u)
#define XTK_PIPS_MT_MASK         (1ull << 5u)
#define XTK_PIPS_MR_MASK         (1ull << 6u)
#define XTK_PIPS_MB_MASK         (1ull << 7u)
#define XTK_PIPS_TIP_MASK        (1ull << 8u)
#define XTK_PIPS_SEL_MASK        (1ull << 9u)
#define XTK_PIPS_NITEM_MASK      (1ull << 10u)
#define XTK_PIPS_DIR_MASK        (1ull << 11u)
#define XTK_PIPS_MAXVISIBLE_MASK (1ull << 12u)
#define XTK_PIPS_NAV_MASK        (1ull << 13u)

typedef struct XtkSuggestProps {
	uint64_t       set;
	XtkChangeStamp stamp;
	float          w;
	float          h;
	float          grow;
	XentFlexAlign  self;
	float          ml;
	float          mt;
	float          mr;
	float          mb;
	char const    *text;
	uint32_t       text_len;
	char const    *tip;
	uint32_t       tip_len;
	bool           enabled;
	char const    *placeholder;
	uint32_t       placeholder_len;
	char const    *icon;
	uint32_t       icon_len;
} XtkSuggestProps;

#define XTK_SUGGEST_W_MASK           (1ull << 0u)
#define XTK_SUGGEST_H_MASK           (1ull << 1u)
#define XTK_SUGGEST_GROW_MASK        (1ull << 2u)
#define XTK_SUGGEST_SELF_MASK        (1ull << 3u)
#define XTK_SUGGEST_ML_MASK          (1ull << 4u)
#define XTK_SUGGEST_MT_MASK          (1ull << 5u)
#define XTK_SUGGEST_MR_MASK          (1ull << 6u)
#define XTK_SUGGEST_MB_MASK          (1ull << 7u)
#define XTK_SUGGEST_TEXT_MASK        (1ull << 8u)
#define XTK_SUGGEST_TIP_MASK         (1ull << 9u)
#define XTK_SUGGEST_ENABLED_MASK     (1ull << 10u)
#define XTK_SUGGEST_PLACEHOLDER_MASK (1ull << 11u)
#define XTK_SUGGEST_ICON_MASK        (1ull << 12u)

typedef struct XtkBadgeProps {
	uint64_t       set;
	XtkChangeStamp stamp;
	float          w;
	float          h;
	float          grow;
	float          shrink;
	XentFlexAlign  self;
	float          ml;
	float          mt;
	float          mr;
	float          mb;
	char const    *tip;
	uint32_t       tip_len;
	XtkBadgeMode   badgemode;
	int32_t        value;
	char const    *icon;
	uint32_t       icon_len;
} XtkBadgeProps;

#define XTK_BADGE_W_MASK         (1ull << 0u)
#define XTK_BADGE_H_MASK         (1ull << 1u)
#define XTK_BADGE_GROW_MASK      (1ull << 2u)
#define XTK_BADGE_SHRINK_MASK    (1ull << 3u)
#define XTK_BADGE_SELF_MASK      (1ull << 4u)
#define XTK_BADGE_ML_MASK        (1ull << 5u)
#define XTK_BADGE_MT_MASK        (1ull << 6u)
#define XTK_BADGE_MR_MASK        (1ull << 7u)
#define XTK_BADGE_MB_MASK        (1ull << 8u)
#define XTK_BADGE_TIP_MASK       (1ull << 9u)
#define XTK_BADGE_BADGEMODE_MASK (1ull << 10u)
#define XTK_BADGE_VALUE_MASK     (1ull << 11u)
#define XTK_BADGE_ICON_MASK      (1ull << 12u)

typedef struct XtkDialogProps {
	uint64_t       set;
	XtkChangeStamp stamp;
	float          w;
	float          h;
	float          grow;
	float          shrink;
	XentFlexAlign  self;
	float          ml;
	float          mt;
	float          mr;
	float          mb;
	char const    *tip;
	uint32_t       tip_len;
	char const    *text;
	uint32_t       text_len;
	char const    *primary;
	uint32_t       primary_len;
	char const    *secondary;
	uint32_t       secondary_len;
	char const    *close;
	uint32_t       close_len;
	float          contenth;
	bool           open;
} XtkDialogProps;

#define XTK_DIALOG_W_MASK         (1ull << 0u)
#define XTK_DIALOG_H_MASK         (1ull << 1u)
#define XTK_DIALOG_GROW_MASK      (1ull << 2u)
#define XTK_DIALOG_SHRINK_MASK    (1ull << 3u)
#define XTK_DIALOG_SELF_MASK      (1ull << 4u)
#define XTK_DIALOG_ML_MASK        (1ull << 5u)
#define XTK_DIALOG_MT_MASK        (1ull << 6u)
#define XTK_DIALOG_MR_MASK        (1ull << 7u)
#define XTK_DIALOG_MB_MASK        (1ull << 8u)
#define XTK_DIALOG_TIP_MASK       (1ull << 9u)
#define XTK_DIALOG_TEXT_MASK      (1ull << 10u)
#define XTK_DIALOG_PRIMARY_MASK   (1ull << 11u)
#define XTK_DIALOG_SECONDARY_MASK (1ull << 12u)
#define XTK_DIALOG_CLOSE_MASK     (1ull << 13u)
#define XTK_DIALOG_CONTENTH_MASK  (1ull << 14u)
#define XTK_DIALOG_OPEN_MASK      (1ull << 15u)

typedef struct XtkTeachingTipProps {
	uint64_t                set;
	XtkChangeStamp          stamp;
	float                   w;
	float                   h;
	float                   grow;
	float                   shrink;
	XentFlexAlign           self;
	float                   ml;
	float                   mt;
	float                   mr;
	float                   mb;
	char const             *tip;
	uint32_t                tip_len;
	char const             *text;
	uint32_t                text_len;
	char const             *subtitle;
	uint32_t                subtitle_len;
	char const             *icon;
	uint32_t                icon_len;
	char const             *action;
	uint32_t                action_len;
	bool                    actionaccent;
	char const             *close;
	uint32_t                close_len;
	XtkTeachingTipPlacement placement;
	bool                    untargeted;
	bool                    lightdismiss;
	XtkTeachingTipTail      tail;
	float                   placementmargin;
	bool                    open;
} XtkTeachingTipProps;

#define XTK_TEACHTIP_W_MASK               (1ull << 0u)
#define XTK_TEACHTIP_H_MASK               (1ull << 1u)
#define XTK_TEACHTIP_GROW_MASK            (1ull << 2u)
#define XTK_TEACHTIP_SHRINK_MASK          (1ull << 3u)
#define XTK_TEACHTIP_SELF_MASK            (1ull << 4u)
#define XTK_TEACHTIP_ML_MASK              (1ull << 5u)
#define XTK_TEACHTIP_MT_MASK              (1ull << 6u)
#define XTK_TEACHTIP_MR_MASK              (1ull << 7u)
#define XTK_TEACHTIP_MB_MASK              (1ull << 8u)
#define XTK_TEACHTIP_TIP_MASK             (1ull << 9u)
#define XTK_TEACHTIP_TEXT_MASK            (1ull << 10u)
#define XTK_TEACHTIP_SUBTITLE_MASK        (1ull << 11u)
#define XTK_TEACHTIP_ICON_MASK            (1ull << 12u)
#define XTK_TEACHTIP_ACTION_MASK          (1ull << 13u)
#define XTK_TEACHTIP_ACTIONACCENT_MASK    (1ull << 14u)
#define XTK_TEACHTIP_CLOSE_MASK           (1ull << 15u)
#define XTK_TEACHTIP_PLACEMENT_MASK       (1ull << 16u)
#define XTK_TEACHTIP_UNTARGETED_MASK      (1ull << 17u)
#define XTK_TEACHTIP_LIGHTDISMISS_MASK    (1ull << 18u)
#define XTK_TEACHTIP_TAIL_MASK            (1ull << 19u)
#define XTK_TEACHTIP_PLACEMENTMARGIN_MASK (1ull << 20u)
#define XTK_TEACHTIP_OPEN_MASK            (1ull << 21u)

typedef struct XtkAvatarProps {
	uint64_t       set;
	XtkChangeStamp stamp;
	float          w;
	float          h;
	float          grow;
	float          shrink;
	XentFlexAlign  self;
	float          ml;
	float          mt;
	float          mr;
	float          mb;
	char const    *tip;
	uint32_t       tip_len;
	char const    *text;
	uint32_t       text_len;
	char const    *initials;
	uint32_t       initials_len;
	XtkResource    src;
	char const    *badgeglyph;
	uint32_t       badgeglyph_len;
	int32_t        badgevalue;
	bool           group;
} XtkAvatarProps;

#define XTK_AVATAR_W_MASK          (1ull << 0u)
#define XTK_AVATAR_H_MASK          (1ull << 1u)
#define XTK_AVATAR_GROW_MASK       (1ull << 2u)
#define XTK_AVATAR_SHRINK_MASK     (1ull << 3u)
#define XTK_AVATAR_SELF_MASK       (1ull << 4u)
#define XTK_AVATAR_ML_MASK         (1ull << 5u)
#define XTK_AVATAR_MT_MASK         (1ull << 6u)
#define XTK_AVATAR_MR_MASK         (1ull << 7u)
#define XTK_AVATAR_MB_MASK         (1ull << 8u)
#define XTK_AVATAR_TIP_MASK        (1ull << 9u)
#define XTK_AVATAR_TEXT_MASK       (1ull << 10u)
#define XTK_AVATAR_INITIALS_MASK   (1ull << 11u)
#define XTK_AVATAR_SRC_MASK        (1ull << 12u)
#define XTK_AVATAR_BADGEGLYPH_MASK (1ull << 13u)
#define XTK_AVATAR_BADGEVALUE_MASK (1ull << 14u)
#define XTK_AVATAR_GROUP_MASK      (1ull << 15u)

typedef struct XtkPagerProps {
	uint64_t            set;
	XtkChangeStamp      stamp;
	float               w;
	float               h;
	float               grow;
	float               shrink;
	XentFlexAlign       self;
	float               ml;
	float               mt;
	float               mr;
	float               mb;
	char const         *tip;
	uint32_t            tip_len;
	int32_t             sel;
	int32_t             nitem;
	XtkPagerDisplayMode display;
	XtkPagerButtonVis   first;
	XtkPagerButtonVis   prev;
	XtkPagerButtonVis   next;
	XtkPagerButtonVis   last;
	char const         *prefix;
	uint32_t            prefix_len;
	char const         *suffix;
	uint32_t            suffix_len;
} XtkPagerProps;

#define XTK_PAGER_W_MASK       (1ull << 0u)
#define XTK_PAGER_H_MASK       (1ull << 1u)
#define XTK_PAGER_GROW_MASK    (1ull << 2u)
#define XTK_PAGER_SHRINK_MASK  (1ull << 3u)
#define XTK_PAGER_SELF_MASK    (1ull << 4u)
#define XTK_PAGER_ML_MASK      (1ull << 5u)
#define XTK_PAGER_MT_MASK      (1ull << 6u)
#define XTK_PAGER_MR_MASK      (1ull << 7u)
#define XTK_PAGER_MB_MASK      (1ull << 8u)
#define XTK_PAGER_TIP_MASK     (1ull << 9u)
#define XTK_PAGER_SEL_MASK     (1ull << 10u)
#define XTK_PAGER_NITEM_MASK   (1ull << 11u)
#define XTK_PAGER_DISPLAY_MASK (1ull << 12u)
#define XTK_PAGER_FIRST_MASK   (1ull << 13u)
#define XTK_PAGER_PREV_MASK    (1ull << 14u)
#define XTK_PAGER_NEXT_MASK    (1ull << 15u)
#define XTK_PAGER_LAST_MASK    (1ull << 16u)
#define XTK_PAGER_PREFIX_MASK  (1ull << 17u)
#define XTK_PAGER_SUFFIX_MASK  (1ull << 18u)

typedef struct XtkSplitViewProps {
	uint64_t                  set;
	XtkChangeStamp            stamp;
	float                     w;
	float                     h;
	float                     grow;
	float                     shrink;
	XentFlexAlign             self;
	float                     ml;
	float                     mt;
	float                     mr;
	float                     mb;
	char const               *tip;
	uint32_t                  tip_len;
	XtkStackDirection         dir;
	float                     gap;
	float                     pl;
	float                     pt;
	float                     pr;
	float                     pb;
	bool                      fill;
	bool                      open;
	XtkSplitViewDisplayMode   display;
	XtkSplitViewPanePlacement placement;
	float                     openlen;
	float                     compactlen;
} XtkSplitViewProps;

#define XTK_SPLITVIEW_W_MASK          (1ull << 0u)
#define XTK_SPLITVIEW_H_MASK          (1ull << 1u)
#define XTK_SPLITVIEW_GROW_MASK       (1ull << 2u)
#define XTK_SPLITVIEW_SHRINK_MASK     (1ull << 3u)
#define XTK_SPLITVIEW_SELF_MASK       (1ull << 4u)
#define XTK_SPLITVIEW_ML_MASK         (1ull << 5u)
#define XTK_SPLITVIEW_MT_MASK         (1ull << 6u)
#define XTK_SPLITVIEW_MR_MASK         (1ull << 7u)
#define XTK_SPLITVIEW_MB_MASK         (1ull << 8u)
#define XTK_SPLITVIEW_TIP_MASK        (1ull << 9u)
#define XTK_SPLITVIEW_DIR_MASK        (1ull << 10u)
#define XTK_SPLITVIEW_GAP_MASK        (1ull << 11u)
#define XTK_SPLITVIEW_PL_MASK         (1ull << 12u)
#define XTK_SPLITVIEW_PT_MASK         (1ull << 13u)
#define XTK_SPLITVIEW_PR_MASK         (1ull << 14u)
#define XTK_SPLITVIEW_PB_MASK         (1ull << 15u)
#define XTK_SPLITVIEW_FILL_MASK       (1ull << 16u)
#define XTK_SPLITVIEW_OPEN_MASK       (1ull << 17u)
#define XTK_SPLITVIEW_DISPLAY_MASK    (1ull << 18u)
#define XTK_SPLITVIEW_PLACEMENT_MASK  (1ull << 19u)
#define XTK_SPLITVIEW_OPENLEN_MASK    (1ull << 20u)
#define XTK_SPLITVIEW_COMPACTLEN_MASK (1ull << 21u)

typedef struct XtkTitleBarProps {
	uint64_t       set;
	XtkChangeStamp stamp;
	float          w;
	float          h;
	float          grow;
	float          shrink;
	XentFlexAlign  self;
	float          ml;
	float          mt;
	float          mr;
	float          mb;
	char const    *tip;
	uint32_t       tip_len;
	char const    *text;
	uint32_t       text_len;
	char const    *subtitle;
	uint32_t       subtitle_len;
	char const    *icon;
	uint32_t       icon_len;
	bool           showback;
	bool           backdisabled;
	bool           showtoggle;
	bool           integrate;
} XtkTitleBarProps;

#define XTK_TITLEBAR_W_MASK            (1ull << 0u)
#define XTK_TITLEBAR_H_MASK            (1ull << 1u)
#define XTK_TITLEBAR_GROW_MASK         (1ull << 2u)
#define XTK_TITLEBAR_SHRINK_MASK       (1ull << 3u)
#define XTK_TITLEBAR_SELF_MASK         (1ull << 4u)
#define XTK_TITLEBAR_ML_MASK           (1ull << 5u)
#define XTK_TITLEBAR_MT_MASK           (1ull << 6u)
#define XTK_TITLEBAR_MR_MASK           (1ull << 7u)
#define XTK_TITLEBAR_MB_MASK           (1ull << 8u)
#define XTK_TITLEBAR_TIP_MASK          (1ull << 9u)
#define XTK_TITLEBAR_TEXT_MASK         (1ull << 10u)
#define XTK_TITLEBAR_SUBTITLE_MASK     (1ull << 11u)
#define XTK_TITLEBAR_ICON_MASK         (1ull << 12u)
#define XTK_TITLEBAR_SHOWBACK_MASK     (1ull << 13u)
#define XTK_TITLEBAR_BACKDISABLED_MASK (1ull << 14u)
#define XTK_TITLEBAR_SHOWTOGGLE_MASK   (1ull << 15u)
#define XTK_TITLEBAR_INTEGRATE_MASK    (1ull << 16u)

typedef struct XtkRatingProps {
	uint64_t       set;
	XtkChangeStamp stamp;
	float          w;
	float          h;
	float          grow;
	float          shrink;
	XentFlexAlign  self;
	float          ml;
	float          mt;
	float          mr;
	float          mb;
	char const    *tip;
	uint32_t       tip_len;
	double         value;
	double         max;
	char const    *text;
	uint32_t       text_len;
	double         placeholder;
	int32_t        initial;
	bool           clear;
	bool           readonly;
} XtkRatingProps;

#define XTK_RATING_W_MASK           (1ull << 0u)
#define XTK_RATING_H_MASK           (1ull << 1u)
#define XTK_RATING_GROW_MASK        (1ull << 2u)
#define XTK_RATING_SHRINK_MASK      (1ull << 3u)
#define XTK_RATING_SELF_MASK        (1ull << 4u)
#define XTK_RATING_ML_MASK          (1ull << 5u)
#define XTK_RATING_MT_MASK          (1ull << 6u)
#define XTK_RATING_MR_MASK          (1ull << 7u)
#define XTK_RATING_MB_MASK          (1ull << 8u)
#define XTK_RATING_TIP_MASK         (1ull << 9u)
#define XTK_RATING_VALUE_MASK       (1ull << 10u)
#define XTK_RATING_MAX_MASK         (1ull << 11u)
#define XTK_RATING_TEXT_MASK        (1ull << 12u)
#define XTK_RATING_PLACEHOLDER_MASK (1ull << 13u)
#define XTK_RATING_INITIAL_MASK     (1ull << 14u)
#define XTK_RATING_CLEAR_MASK       (1ull << 15u)
#define XTK_RATING_READONLY_MASK    (1ull << 16u)

typedef struct XtkLinkProps {
	uint64_t       set;
	XtkChangeStamp stamp;
	float          w;
	float          h;
	float          grow;
	XentFlexAlign  self;
	float          ml;
	float          mt;
	float          mr;
	float          mb;
	char const    *text;
	uint32_t       text_len;
	char const    *tip;
	uint32_t       tip_len;
	bool           enabled;
	char const    *url;
	uint32_t       url_len;
} XtkLinkProps;

#define XTK_LINK_W_MASK       (1ull << 0u)
#define XTK_LINK_H_MASK       (1ull << 1u)
#define XTK_LINK_GROW_MASK    (1ull << 2u)
#define XTK_LINK_SELF_MASK    (1ull << 3u)
#define XTK_LINK_ML_MASK      (1ull << 4u)
#define XTK_LINK_MT_MASK      (1ull << 5u)
#define XTK_LINK_MR_MASK      (1ull << 6u)
#define XTK_LINK_MB_MASK      (1ull << 7u)
#define XTK_LINK_TEXT_MASK    (1ull << 8u)
#define XTK_LINK_TIP_MASK     (1ull << 9u)
#define XTK_LINK_ENABLED_MASK (1ull << 10u)
#define XTK_LINK_URL_MASK     (1ull << 11u)

typedef struct XtkScrollBarProps {
	uint64_t              set;
	XtkChangeStamp        stamp;
	float                 w;
	float                 h;
	float                 grow;
	XentFlexAlign         self;
	float                 ml;
	float                 mt;
	float                 mr;
	float                 mb;
	char const           *tip;
	uint32_t              tip_len;
	bool                  enabled;
	XtkStackDirection     dir;
	double                min;
	double                max;
	double                value;
	double                viewport;
	float                 smallchange;
	float                 largechange;
	XtkScrollBarIndicator indicator;
} XtkScrollBarProps;

#define XTK_SCROLLBAR_W_MASK           (1ull << 0u)
#define XTK_SCROLLBAR_H_MASK           (1ull << 1u)
#define XTK_SCROLLBAR_GROW_MASK        (1ull << 2u)
#define XTK_SCROLLBAR_SELF_MASK        (1ull << 3u)
#define XTK_SCROLLBAR_ML_MASK          (1ull << 4u)
#define XTK_SCROLLBAR_MT_MASK          (1ull << 5u)
#define XTK_SCROLLBAR_MR_MASK          (1ull << 6u)
#define XTK_SCROLLBAR_MB_MASK          (1ull << 7u)
#define XTK_SCROLLBAR_TIP_MASK         (1ull << 8u)
#define XTK_SCROLLBAR_ENABLED_MASK     (1ull << 9u)
#define XTK_SCROLLBAR_DIR_MASK         (1ull << 10u)
#define XTK_SCROLLBAR_MIN_MASK         (1ull << 11u)
#define XTK_SCROLLBAR_MAX_MASK         (1ull << 12u)
#define XTK_SCROLLBAR_VALUE_MASK       (1ull << 13u)
#define XTK_SCROLLBAR_VIEWPORT_MASK    (1ull << 14u)
#define XTK_SCROLLBAR_SMALLCHANGE_MASK (1ull << 15u)
#define XTK_SCROLLBAR_LARGECHANGE_MASK (1ull << 16u)
#define XTK_SCROLLBAR_INDICATOR_MASK   (1ull << 17u)

typedef struct XtkLoopingProps {
	uint64_t       set;
	XtkChangeStamp stamp;
	float          w;
	float          h;
	float          grow;
	XentFlexAlign  self;
	float          ml;
	float          mt;
	float          mr;
	float          mb;
	char const    *tip;
	uint32_t       tip_len;
	bool           enabled;
	int32_t        nitem;
	int32_t        sel;
	float          itemh;
	float          itemw;
	bool           loop;
} XtkLoopingProps;

#define XTK_LOOPING_W_MASK       (1ull << 0u)
#define XTK_LOOPING_H_MASK       (1ull << 1u)
#define XTK_LOOPING_GROW_MASK    (1ull << 2u)
#define XTK_LOOPING_SELF_MASK    (1ull << 3u)
#define XTK_LOOPING_ML_MASK      (1ull << 4u)
#define XTK_LOOPING_MT_MASK      (1ull << 5u)
#define XTK_LOOPING_MR_MASK      (1ull << 6u)
#define XTK_LOOPING_MB_MASK      (1ull << 7u)
#define XTK_LOOPING_TIP_MASK     (1ull << 8u)
#define XTK_LOOPING_ENABLED_MASK (1ull << 9u)
#define XTK_LOOPING_NITEM_MASK   (1ull << 10u)
#define XTK_LOOPING_SEL_MASK     (1ull << 11u)
#define XTK_LOOPING_ITEMH_MASK   (1ull << 12u)
#define XTK_LOOPING_ITEMW_MASK   (1ull << 13u)
#define XTK_LOOPING_LOOP_MASK    (1ull << 14u)

typedef struct XtkDatePickerProps {
	uint64_t       set;
	XtkChangeStamp stamp;
	float          w;
	float          h;
	float          grow;
	XentFlexAlign  self;
	float          ml;
	float          mt;
	float          mr;
	float          mb;
	char const    *tip;
	uint32_t       tip_len;
	bool           enabled;
	char const    *header;
	uint32_t       header_len;
	int32_t        date;
	int32_t        minyear;
	int32_t        maxyear;
} XtkDatePickerProps;

#define XTK_DATEPICKER_W_MASK       (1ull << 0u)
#define XTK_DATEPICKER_H_MASK       (1ull << 1u)
#define XTK_DATEPICKER_GROW_MASK    (1ull << 2u)
#define XTK_DATEPICKER_SELF_MASK    (1ull << 3u)
#define XTK_DATEPICKER_ML_MASK      (1ull << 4u)
#define XTK_DATEPICKER_MT_MASK      (1ull << 5u)
#define XTK_DATEPICKER_MR_MASK      (1ull << 6u)
#define XTK_DATEPICKER_MB_MASK      (1ull << 7u)
#define XTK_DATEPICKER_TIP_MASK     (1ull << 8u)
#define XTK_DATEPICKER_ENABLED_MASK (1ull << 9u)
#define XTK_DATEPICKER_HEADER_MASK  (1ull << 10u)
#define XTK_DATEPICKER_DATE_MASK    (1ull << 11u)
#define XTK_DATEPICKER_MINYEAR_MASK (1ull << 12u)
#define XTK_DATEPICKER_MAXYEAR_MASK (1ull << 13u)

typedef struct XtkTimePickerProps {
	uint64_t       set;
	XtkChangeStamp stamp;
	float          w;
	float          h;
	float          grow;
	XentFlexAlign  self;
	float          ml;
	float          mt;
	float          mr;
	float          mb;
	char const    *tip;
	uint32_t       tip_len;
	bool           enabled;
	char const    *header;
	uint32_t       header_len;
	int32_t        time;
	XtkClock       clock;
	int32_t        step;
} XtkTimePickerProps;

#define XTK_TIMEPICKER_W_MASK       (1ull << 0u)
#define XTK_TIMEPICKER_H_MASK       (1ull << 1u)
#define XTK_TIMEPICKER_GROW_MASK    (1ull << 2u)
#define XTK_TIMEPICKER_SELF_MASK    (1ull << 3u)
#define XTK_TIMEPICKER_ML_MASK      (1ull << 4u)
#define XTK_TIMEPICKER_MT_MASK      (1ull << 5u)
#define XTK_TIMEPICKER_MR_MASK      (1ull << 6u)
#define XTK_TIMEPICKER_MB_MASK      (1ull << 7u)
#define XTK_TIMEPICKER_TIP_MASK     (1ull << 8u)
#define XTK_TIMEPICKER_ENABLED_MASK (1ull << 9u)
#define XTK_TIMEPICKER_HEADER_MASK  (1ull << 10u)
#define XTK_TIMEPICKER_TIME_MASK    (1ull << 11u)
#define XTK_TIMEPICKER_CLOCK_MASK   (1ull << 12u)
#define XTK_TIMEPICKER_STEP_MASK    (1ull << 13u)

typedef struct XtkCalendarProps {
	uint64_t        set;
	XtkChangeStamp  stamp;
	float           w;
	float           h;
	float           grow;
	XentFlexAlign   self;
	float           ml;
	float           mt;
	float           mr;
	float           mb;
	char const     *tip;
	uint32_t        tip_len;
	bool            enabled;
	int32_t         date;
	XtkCalendarMode mode;
	int32_t         mindate;
	int32_t         maxdate;
	int32_t         firstday;
} XtkCalendarProps;

#define XTK_CALENDAR_W_MASK        (1ull << 0u)
#define XTK_CALENDAR_H_MASK        (1ull << 1u)
#define XTK_CALENDAR_GROW_MASK     (1ull << 2u)
#define XTK_CALENDAR_SELF_MASK     (1ull << 3u)
#define XTK_CALENDAR_ML_MASK       (1ull << 4u)
#define XTK_CALENDAR_MT_MASK       (1ull << 5u)
#define XTK_CALENDAR_MR_MASK       (1ull << 6u)
#define XTK_CALENDAR_MB_MASK       (1ull << 7u)
#define XTK_CALENDAR_TIP_MASK      (1ull << 8u)
#define XTK_CALENDAR_ENABLED_MASK  (1ull << 9u)
#define XTK_CALENDAR_DATE_MASK     (1ull << 10u)
#define XTK_CALENDAR_MODE_MASK     (1ull << 11u)
#define XTK_CALENDAR_MINDATE_MASK  (1ull << 12u)
#define XTK_CALENDAR_MAXDATE_MASK  (1ull << 13u)
#define XTK_CALENDAR_FIRSTDAY_MASK (1ull << 14u)

typedef struct XtkColorPickerProps {
	uint64_t       set;
	XtkChangeStamp stamp;
	float          w;
	float          h;
	float          grow;
	XentFlexAlign  self;
	float          ml;
	float          mt;
	float          mr;
	float          mb;
	char const    *tip;
	uint32_t       tip_len;
	bool           enabled;
	XtkColor       color;
	bool           alpha;
	bool           morebutton;
	XtkSpectrum    spectrum;
} XtkColorPickerProps;

#define XTK_COLORPICKER_W_MASK          (1ull << 0u)
#define XTK_COLORPICKER_H_MASK          (1ull << 1u)
#define XTK_COLORPICKER_GROW_MASK       (1ull << 2u)
#define XTK_COLORPICKER_SELF_MASK       (1ull << 3u)
#define XTK_COLORPICKER_ML_MASK         (1ull << 4u)
#define XTK_COLORPICKER_MT_MASK         (1ull << 5u)
#define XTK_COLORPICKER_MR_MASK         (1ull << 6u)
#define XTK_COLORPICKER_MB_MASK         (1ull << 7u)
#define XTK_COLORPICKER_TIP_MASK        (1ull << 8u)
#define XTK_COLORPICKER_ENABLED_MASK    (1ull << 9u)
#define XTK_COLORPICKER_COLOR_MASK      (1ull << 10u)
#define XTK_COLORPICKER_ALPHA_MASK      (1ull << 11u)
#define XTK_COLORPICKER_MOREBUTTON_MASK (1ull << 12u)
#define XTK_COLORPICKER_SPECTRUM_MASK   (1ull << 13u)

typedef struct XtkColumnProps {
	uint64_t         set;
	XtkChangeStamp   stamp;
	float            w;
	float            minw;
	float            maxw;
	char const      *text;
	uint32_t         text_len;
	char const      *tip;
	uint32_t         tip_len;
	XtkTextAlign     align;
	bool             enabled;
	bool             resizable;
	XtkSortDirection sort;
} XtkColumnProps;

#define XTK_COLUMN_W_MASK         (1ull << 0u)
#define XTK_COLUMN_MINW_MASK      (1ull << 1u)
#define XTK_COLUMN_MAXW_MASK      (1ull << 2u)
#define XTK_COLUMN_TEXT_MASK      (1ull << 3u)
#define XTK_COLUMN_TIP_MASK       (1ull << 4u)
#define XTK_COLUMN_ALIGN_MASK     (1ull << 5u)
#define XTK_COLUMN_ENABLED_MASK   (1ull << 6u)
#define XTK_COLUMN_RESIZABLE_MASK (1ull << 7u)
#define XTK_COLUMN_SORT_MASK      (1ull << 8u)

typedef struct XtkCommandBarProps {
	uint64_t          set;
	XtkChangeStamp    stamp;
	float             w;
	float             h;
	float             grow;
	XentFlexAlign     self;
	float             ml;
	float             mt;
	float             mr;
	float             mb;
	char const       *tip;
	uint32_t          tip_len;
	bool              enabled;
	bool              open;
	bool              sticky;
	XtkAppBarMode     mode;
	XtkLabelPosition  labels;
	XtkOverflowButton more;
	bool              dynamic;
} XtkCommandBarProps;

#define XTK_COMMANDBAR_W_MASK       (1ull << 0u)
#define XTK_COMMANDBAR_H_MASK       (1ull << 1u)
#define XTK_COMMANDBAR_GROW_MASK    (1ull << 2u)
#define XTK_COMMANDBAR_SELF_MASK    (1ull << 3u)
#define XTK_COMMANDBAR_ML_MASK      (1ull << 4u)
#define XTK_COMMANDBAR_MT_MASK      (1ull << 5u)
#define XTK_COMMANDBAR_MR_MASK      (1ull << 6u)
#define XTK_COMMANDBAR_MB_MASK      (1ull << 7u)
#define XTK_COMMANDBAR_TIP_MASK     (1ull << 8u)
#define XTK_COMMANDBAR_ENABLED_MASK (1ull << 9u)
#define XTK_COMMANDBAR_OPEN_MASK    (1ull << 10u)
#define XTK_COMMANDBAR_STICKY_MASK  (1ull << 11u)
#define XTK_COMMANDBAR_MODE_MASK    (1ull << 12u)
#define XTK_COMMANDBAR_LABELS_MASK  (1ull << 13u)
#define XTK_COMMANDBAR_MORE_MASK    (1ull << 14u)
#define XTK_COMMANDBAR_DYNAMIC_MASK (1ull << 15u)

typedef struct XtkAppBarButtonProps {
	uint64_t        set;
	XtkChangeStamp  stamp;
	float           w;
	float           h;
	float           grow;
	XentFlexAlign   self;
	float           ml;
	float           mt;
	float           mr;
	float           mb;
	char const     *tip;
	uint32_t        tip_len;
	char const     *text;
	uint32_t        text_len;
	char const     *icon;
	uint32_t        icon_len;
	bool            enabled;
	XtkElementLabel labelpos;
	char const     *accel;
	uint32_t        accel_len;
	bool            secondary;
	int32_t         order;
} XtkAppBarButtonProps;

#define XTK_APPBARBUTTON_W_MASK         (1ull << 0u)
#define XTK_APPBARBUTTON_H_MASK         (1ull << 1u)
#define XTK_APPBARBUTTON_GROW_MASK      (1ull << 2u)
#define XTK_APPBARBUTTON_SELF_MASK      (1ull << 3u)
#define XTK_APPBARBUTTON_ML_MASK        (1ull << 4u)
#define XTK_APPBARBUTTON_MT_MASK        (1ull << 5u)
#define XTK_APPBARBUTTON_MR_MASK        (1ull << 6u)
#define XTK_APPBARBUTTON_MB_MASK        (1ull << 7u)
#define XTK_APPBARBUTTON_TIP_MASK       (1ull << 8u)
#define XTK_APPBARBUTTON_TEXT_MASK      (1ull << 9u)
#define XTK_APPBARBUTTON_ICON_MASK      (1ull << 10u)
#define XTK_APPBARBUTTON_ENABLED_MASK   (1ull << 11u)
#define XTK_APPBARBUTTON_LABELPOS_MASK  (1ull << 12u)
#define XTK_APPBARBUTTON_ACCEL_MASK     (1ull << 13u)
#define XTK_APPBARBUTTON_SECONDARY_MASK (1ull << 14u)
#define XTK_APPBARBUTTON_ORDER_MASK     (1ull << 15u)

typedef struct XtkAppBarToggleProps {
	uint64_t        set;
	XtkChangeStamp  stamp;
	float           w;
	float           h;
	float           grow;
	XentFlexAlign   self;
	float           ml;
	float           mt;
	float           mr;
	float           mb;
	char const     *tip;
	uint32_t        tip_len;
	char const     *text;
	uint32_t        text_len;
	char const     *icon;
	uint32_t        icon_len;
	bool            enabled;
	XtkElementLabel labelpos;
	char const     *accel;
	uint32_t        accel_len;
	bool            checked;
	bool            secondary;
	int32_t         order;
} XtkAppBarToggleProps;

#define XTK_APPBARTOGGLE_W_MASK         (1ull << 0u)
#define XTK_APPBARTOGGLE_H_MASK         (1ull << 1u)
#define XTK_APPBARTOGGLE_GROW_MASK      (1ull << 2u)
#define XTK_APPBARTOGGLE_SELF_MASK      (1ull << 3u)
#define XTK_APPBARTOGGLE_ML_MASK        (1ull << 4u)
#define XTK_APPBARTOGGLE_MT_MASK        (1ull << 5u)
#define XTK_APPBARTOGGLE_MR_MASK        (1ull << 6u)
#define XTK_APPBARTOGGLE_MB_MASK        (1ull << 7u)
#define XTK_APPBARTOGGLE_TIP_MASK       (1ull << 8u)
#define XTK_APPBARTOGGLE_TEXT_MASK      (1ull << 9u)
#define XTK_APPBARTOGGLE_ICON_MASK      (1ull << 10u)
#define XTK_APPBARTOGGLE_ENABLED_MASK   (1ull << 11u)
#define XTK_APPBARTOGGLE_LABELPOS_MASK  (1ull << 12u)
#define XTK_APPBARTOGGLE_ACCEL_MASK     (1ull << 13u)
#define XTK_APPBARTOGGLE_CHECKED_MASK   (1ull << 14u)
#define XTK_APPBARTOGGLE_SECONDARY_MASK (1ull << 15u)
#define XTK_APPBARTOGGLE_ORDER_MASK     (1ull << 16u)

typedef struct XtkAppBarSeparatorProps {
	uint64_t       set;
	XtkChangeStamp stamp;
	float          w;
	float          h;
	float          grow;
	XentFlexAlign  self;
	float          ml;
	float          mt;
	float          mr;
	float          mb;
	char const    *tip;
	uint32_t       tip_len;
	bool           secondary;
	int32_t        order;
} XtkAppBarSeparatorProps;

#define XTK_APPBARSEP_W_MASK         (1ull << 0u)
#define XTK_APPBARSEP_H_MASK         (1ull << 1u)
#define XTK_APPBARSEP_GROW_MASK      (1ull << 2u)
#define XTK_APPBARSEP_SELF_MASK      (1ull << 3u)
#define XTK_APPBARSEP_ML_MASK        (1ull << 4u)
#define XTK_APPBARSEP_MT_MASK        (1ull << 5u)
#define XTK_APPBARSEP_MR_MASK        (1ull << 6u)
#define XTK_APPBARSEP_MB_MASK        (1ull << 7u)
#define XTK_APPBARSEP_TIP_MASK       (1ull << 8u)
#define XTK_APPBARSEP_SECONDARY_MASK (1ull << 9u)
#define XTK_APPBARSEP_ORDER_MASK     (1ull << 10u)

XtkLocalId xtk_container_create(XtkTxn *txn, XtkNodeRef parent, XtkContainerProps const *props);
XtkLocalId xtk_text_create(XtkTxn *txn, XtkNodeRef parent, XtkTextProps const *props);
XtkLocalId xtk_button_create(XtkTxn *txn, XtkNodeRef parent, XtkButtonProps const *props);
XtkLocalId xtk_toggle_create(XtkTxn *txn, XtkNodeRef parent, XtkToggleProps const *props);
XtkLocalId xtk_checkbox_create(XtkTxn *txn, XtkNodeRef parent, XtkCheckBoxProps const *props);
XtkLocalId xtk_radio_create(XtkTxn *txn, XtkNodeRef parent, XtkToggleProps const *props);
XtkLocalId xtk_switch_create(XtkTxn *txn, XtkNodeRef parent, XtkToggleProps const *props);
XtkLocalId xtk_slider_create(XtkTxn *txn, XtkNodeRef parent, XtkSliderProps const *props);
XtkLocalId xtk_textbox_create(XtkTxn *txn, XtkNodeRef parent, XtkTextBoxProps const *props);
XtkLocalId xtk_scroll_create(XtkTxn *txn, XtkNodeRef parent, XtkScrollProps const *props);
XtkLocalId xtk_image_create(XtkTxn *txn, XtkNodeRef parent, XtkImageProps const *props);
XtkLocalId xtk_progress_create(XtkTxn *txn, XtkNodeRef parent, XtkProgressProps const *props);
XtkLocalId xtk_list_create(XtkTxn *txn, XtkNodeRef parent, XtkListProps const *props);
XtkLocalId xtk_tab_create(XtkTxn *txn, XtkNodeRef parent, XtkLayoutProps const *props);
XtkLocalId xtk_card_create(XtkTxn *txn, XtkNodeRef parent, XtkContainerProps const *props);
XtkLocalId xtk_divider_create(XtkTxn *txn, XtkNodeRef parent, XtkLayoutProps const *props);
XtkLocalId xtk_canvas_create(XtkTxn *txn, XtkNodeRef parent, XtkLayoutProps const *props);
XtkLocalId xtk_password_create(XtkTxn *txn, XtkNodeRef parent, XtkInputProps const *props);
XtkLocalId xtk_number_create(XtkTxn *txn, XtkNodeRef parent, XtkNumberProps const *props);
XtkLocalId xtk_link_create(XtkTxn *txn, XtkNodeRef parent, XtkLinkProps const *props);
XtkLocalId xtk_repeat_create(XtkTxn *txn, XtkNodeRef parent, XtkButtonProps const *props);
XtkLocalId xtk_progressring_create(XtkTxn *txn, XtkNodeRef parent, XtkProgressProps const *props);
XtkLocalId xtk_badge_create(XtkTxn *txn, XtkNodeRef parent, XtkBadgeProps const *props);
XtkLocalId xtk_tooltip_create(XtkTxn *txn, XtkNodeRef parent, XtkOverlayProps const *props);
XtkLocalId xtk_flyout_create(XtkTxn *txn, XtkNodeRef parent, XtkOverlayProps const *props);
XtkLocalId xtk_menufly_create(XtkTxn *txn, XtkNodeRef parent, XtkOverlayProps const *props);
XtkLocalId xtk_dropdown_create(XtkTxn *txn, XtkNodeRef parent, XtkButtonProps const *props);
XtkLocalId xtk_split_create(XtkTxn *txn, XtkNodeRef parent, XtkButtonProps const *props);
XtkLocalId xtk_combo_create(XtkTxn *txn, XtkNodeRef parent, XtkComboProps const *props);
XtkLocalId xtk_expander_create(XtkTxn *txn, XtkNodeRef parent, XtkExpanderProps const *props);
XtkLocalId xtk_exphead_create(XtkTxn *txn, XtkNodeRef parent, XtkItemProps const *props);
XtkLocalId xtk_expbody_create(XtkTxn *txn, XtkNodeRef parent, XtkContainerProps const *props);
XtkLocalId xtk_infobar_create(XtkTxn *txn, XtkNodeRef parent, XtkInfoBarProps const *props);
XtkLocalId xtk_dialog_create(XtkTxn *txn, XtkNodeRef parent, XtkDialogProps const *props);
XtkLocalId xtk_dialogbody_create(XtkTxn *txn, XtkNodeRef parent, XtkContainerProps const *props);
XtkLocalId xtk_menubar_create(XtkTxn *txn, XtkNodeRef parent, XtkLayoutProps const *props);
XtkLocalId xtk_menuitem_create(XtkTxn *txn, XtkNodeRef parent, XtkItemProps const *props);
XtkLocalId xtk_nav_create(XtkTxn *txn, XtkNodeRef parent, XtkNavProps const *props);
XtkLocalId xtk_navitem_create(XtkTxn *txn, XtkNodeRef parent, XtkItemProps const *props);
XtkLocalId xtk_tabs_create(XtkTxn *txn, XtkNodeRef parent, XtkSelectionProps const *props);
XtkLocalId xtk_tabitem_create(XtkTxn *txn, XtkNodeRef parent, XtkItemProps const *props);
XtkLocalId xtk_listitem_create(XtkTxn *txn, XtkNodeRef parent, XtkItemProps const *props);
XtkLocalId xtk_listbox_create(XtkTxn *txn, XtkNodeRef parent, XtkListProps const *props);
XtkLocalId xtk_gridview_create(XtkTxn *txn, XtkNodeRef parent, XtkListProps const *props);
XtkLocalId xtk_repeater_create(XtkTxn *txn, XtkNodeRef parent, XtkListProps const *props);
XtkLocalId xtk_itemsview_create(XtkTxn *txn, XtkNodeRef parent, XtkItemsViewProps const *props);
XtkLocalId xtk_flip_create(XtkTxn *txn, XtkNodeRef parent, XtkFlipProps const *props);
XtkLocalId xtk_pips_create(XtkTxn *txn, XtkNodeRef parent, XtkPipsProps const *props);
XtkLocalId xtk_suggest_create(XtkTxn *txn, XtkNodeRef parent, XtkSuggestProps const *props);
XtkLocalId xtk_togglesplit_create(XtkTxn *txn, XtkNodeRef parent, XtkToggleProps const *props);
XtkLocalId xtk_radiogroup_create(XtkTxn *txn, XtkNodeRef parent, XtkRadioGroupProps const *props);
XtkLocalId xtk_rating_create(XtkTxn *txn, XtkNodeRef parent, XtkRatingProps const *props);
XtkLocalId xtk_selector_create(XtkTxn *txn, XtkNodeRef parent, XtkSelectionProps const *props);
XtkLocalId xtk_selectoritem_create(XtkTxn *txn, XtkNodeRef parent, XtkItemProps const *props);
XtkLocalId xtk_breadcrumb_create(XtkTxn *txn, XtkNodeRef parent, XtkSelectionProps const *props);
XtkLocalId xtk_crumb_create(XtkTxn *txn, XtkNodeRef parent, XtkItemProps const *props);
XtkLocalId xtk_teachtip_create(XtkTxn *txn, XtkNodeRef parent, XtkTeachingTipProps const *props);
XtkLocalId xtk_tree_create(XtkTxn *txn, XtkNodeRef parent, XtkTreeProps const *props);
XtkLocalId xtk_treeitem_create(XtkTxn *txn, XtkNodeRef parent, XtkItemProps const *props);
XtkLocalId xtk_refresh_create(XtkTxn *txn, XtkNodeRef parent, XtkRefreshProps const *props);
XtkLocalId xtk_avatar_create(XtkTxn *txn, XtkNodeRef parent, XtkAvatarProps const *props);
XtkLocalId xtk_pager_create(XtkTxn *txn, XtkNodeRef parent, XtkPagerProps const *props);
XtkLocalId xtk_splitview_create(XtkTxn *txn, XtkNodeRef parent, XtkSplitViewProps const *props);
XtkLocalId xtk_splitpane_create(XtkTxn *txn, XtkNodeRef parent, XtkContainerProps const *props);
XtkLocalId xtk_splitbody_create(XtkTxn *txn, XtkNodeRef parent, XtkContainerProps const *props);
XtkLocalId xtk_titlebar_create(XtkTxn *txn, XtkNodeRef parent, XtkTitleBarProps const *props);
XtkLocalId xtk_scrollbar_create(XtkTxn *txn, XtkNodeRef parent, XtkScrollBarProps const *props);
XtkLocalId xtk_looping_create(XtkTxn *txn, XtkNodeRef parent, XtkLoopingProps const *props);
XtkLocalId xtk_datepicker_create(XtkTxn *txn, XtkNodeRef parent, XtkDatePickerProps const *props);
XtkLocalId xtk_timepicker_create(XtkTxn *txn, XtkNodeRef parent, XtkTimePickerProps const *props);
XtkLocalId xtk_calendar_create(XtkTxn *txn, XtkNodeRef parent, XtkCalendarProps const *props);
XtkLocalId xtk_colorpicker_create(XtkTxn *txn, XtkNodeRef parent, XtkColorPickerProps const *props);
XtkLocalId xtk_colheader_create(XtkTxn *txn, XtkNodeRef parent, XtkLayoutProps const *props);
XtkLocalId xtk_colitem_create(XtkTxn *txn, XtkNodeRef parent, XtkColumnProps const *props);
XtkLocalId xtk_commandbar_create(XtkTxn *txn, XtkNodeRef parent, XtkCommandBarProps const *props);
XtkLocalId xtk_appbarbutton_create(XtkTxn *txn, XtkNodeRef parent, XtkAppBarButtonProps const *props);
XtkLocalId xtk_appbartoggle_create(XtkTxn *txn, XtkNodeRef parent, XtkAppBarToggleProps const *props);
XtkLocalId xtk_appbarsep_create(XtkTxn *txn, XtkNodeRef parent, XtkAppBarSeparatorProps const *props);
bool       xtk_container_setw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool       xtk_container_seth(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool       xtk_container_setgrow(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool       xtk_container_setshrink(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool       xtk_container_setself(XtkScene *scene, XtkCtrl control, XentFlexAlign value, XtkChangeStamp change);
bool       xtk_container_setml(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool       xtk_container_setmt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool       xtk_container_setmr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool       xtk_container_setmb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_container_settip(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_container_setdir(XtkScene *scene, XtkCtrl control, XtkStackDirection value, XtkChangeStamp change);
bool xtk_container_setitems(XtkScene *scene, XtkCtrl control, XentFlexAlign value, XtkChangeStamp change);
bool xtk_container_setjustify(XtkScene *scene, XtkCtrl control, XentFlexJustify value, XtkChangeStamp change);
bool xtk_container_setgap(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_container_setpl(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_container_setpt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_container_setpr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_container_setpb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_container_setfill(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_container_setfitw(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_container_setfith(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_container_setwrap(XtkScene *scene, XtkCtrl control, XentFlexWrap value, XtkChangeStamp change);
bool xtk_container_setdrop(XtkScene *scene, XtkCtrl control, XtkDropOperation value, XtkChangeStamp change);
bool xtk_container_setdragtext(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_container_setdragfiles(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
);
XtkSubRef xtk_container_ondraghover(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg);
XtkSubRef xtk_container_ondropfiles(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg);
XtkSubRef xtk_container_ondroptext(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg);
XtkSubRef xtk_container_ondragcompleted(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg);
bool      xtk_text_setw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_text_seth(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_text_setgrow(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_text_setself(XtkScene *scene, XtkCtrl control, XentFlexAlign value, XtkChangeStamp change);
bool      xtk_text_setml(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_text_setmt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_text_setmr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_text_setmb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_text_settext(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_text_settip(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_text_setfontsize(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_text_setfontweight(XtkScene *scene, XtkCtrl control, XtkFontWeight value, XtkChangeStamp change);
bool      xtk_text_settextalign(XtkScene *scene, XtkCtrl control, XtkTextAlign value, XtkChangeStamp change);
bool      xtk_text_setfg(XtkScene *scene, XtkCtrl control, XtkColor value, XtkChangeStamp change);
bool      xtk_text_setmaxlines(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool      xtk_text_settrim(XtkScene *scene, XtkCtrl control, XtkTextTrim value, XtkChangeStamp change);
bool      xtk_text_settextwrap(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool      xtk_text_setselectable(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool      xtk_button_setw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_button_seth(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_button_setgrow(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_button_setself(XtkScene *scene, XtkCtrl control, XentFlexAlign value, XtkChangeStamp change);
bool      xtk_button_setml(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_button_setmt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_button_setmr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_button_setmb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_button_settext(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_button_settip(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_button_setenabled(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool      xtk_button_seticon(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_button_setstyle(XtkScene *scene, XtkCtrl control, XtkButtonStyle value, XtkChangeStamp change);
XtkSubRef xtk_button_oninvoke(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg);
bool      xtk_toggle_setw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_toggle_seth(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_toggle_setgrow(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_toggle_setself(XtkScene *scene, XtkCtrl control, XentFlexAlign value, XtkChangeStamp change);
bool      xtk_toggle_setml(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_toggle_setmt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_toggle_setmr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_toggle_setmb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_toggle_settext(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_toggle_settip(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_toggle_setenabled(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool      xtk_toggle_setchecked(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
XtkSubRef xtk_toggle_onchange(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg);
bool      xtk_checkbox_setw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_checkbox_seth(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_checkbox_setgrow(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_checkbox_setself(XtkScene *scene, XtkCtrl control, XentFlexAlign value, XtkChangeStamp change);
bool      xtk_checkbox_setml(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_checkbox_setmt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_checkbox_setmr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_checkbox_setmb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_checkbox_settext(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_checkbox_settip(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_checkbox_setenabled(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool      xtk_checkbox_setchecked(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool      xtk_checkbox_setindeterminate(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool      xtk_checkbox_setthreestate(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
XtkSubRef xtk_checkbox_onchange(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg);
XtkSubRef xtk_checkbox_onstate(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg);
bool      xtk_radio_setw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_radio_seth(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_radio_setgrow(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_radio_setself(XtkScene *scene, XtkCtrl control, XentFlexAlign value, XtkChangeStamp change);
bool      xtk_radio_setml(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_radio_setmt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_radio_setmr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_radio_setmb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_radio_settext(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_radio_settip(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_radio_setenabled(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool      xtk_radio_setchecked(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
XtkSubRef xtk_radio_onchange(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg);
bool      xtk_switch_setw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_switch_seth(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_switch_setgrow(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_switch_setself(XtkScene *scene, XtkCtrl control, XentFlexAlign value, XtkChangeStamp change);
bool      xtk_switch_setml(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_switch_setmt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_switch_setmr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_switch_setmb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_switch_settext(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_switch_settip(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_switch_setenabled(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool      xtk_switch_setchecked(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
XtkSubRef xtk_switch_onchange(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg);
bool      xtk_slider_setw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_slider_seth(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_slider_setgrow(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_slider_setself(XtkScene *scene, XtkCtrl control, XentFlexAlign value, XtkChangeStamp change);
bool      xtk_slider_setml(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_slider_setmt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_slider_setmr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_slider_setmb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_slider_settip(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_slider_setenabled(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool      xtk_slider_setmin(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_slider_setmax(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_slider_setvalue(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_slider_setstep(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_slider_settick(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_slider_settickplace(XtkScene *scene, XtkCtrl control, XtkTickPlacement value, XtkChangeStamp change);
bool      xtk_slider_setsnapsto(XtkScene *scene, XtkCtrl control, XtkSliderSnap value, XtkChangeStamp change);
bool      xtk_slider_setsmallchange(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_slider_setlargechange(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_slider_setdir(XtkScene *scene, XtkCtrl control, XtkStackDirection value, XtkChangeStamp change);
bool      xtk_slider_setrange(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool      xtk_slider_setrangestart(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_slider_setrangeend(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
XtkSubRef xtk_slider_onchange(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg);
XtkSubRef xtk_slider_onrange(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg);
bool      xtk_textbox_setw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_textbox_seth(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_textbox_setgrow(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_textbox_setself(XtkScene *scene, XtkCtrl control, XentFlexAlign value, XtkChangeStamp change);
bool      xtk_textbox_setml(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_textbox_setmt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_textbox_setmr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_textbox_setmb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_textbox_settext(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_textbox_settip(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_textbox_setenabled(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool      xtk_textbox_setplaceholder(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
);
bool      xtk_textbox_setmultiline(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool      xtk_textbox_setreadonly(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
XtkSubRef xtk_textbox_onchange(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg);
bool      xtk_scroll_setw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_scroll_seth(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_scroll_setgrow(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_scroll_setshrink(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_scroll_setself(XtkScene *scene, XtkCtrl control, XentFlexAlign value, XtkChangeStamp change);
bool      xtk_scroll_setml(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_scroll_setmt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_scroll_setmr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_scroll_setmb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_scroll_settip(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_scroll_setdir(XtkScene *scene, XtkCtrl control, XtkStackDirection value, XtkChangeStamp change);
bool      xtk_scroll_setitems(XtkScene *scene, XtkCtrl control, XentFlexAlign value, XtkChangeStamp change);
bool      xtk_scroll_setjustify(XtkScene *scene, XtkCtrl control, XentFlexJustify value, XtkChangeStamp change);
bool      xtk_scroll_setgap(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_scroll_setpl(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_scroll_setpt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_scroll_setpr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_scroll_setpb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_scroll_setfill(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool      xtk_scroll_setfitw(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool      xtk_scroll_setfith(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool      xtk_scroll_setwrap(XtkScene *scene, XtkCtrl control, XentFlexWrap value, XtkChangeStamp change);
bool      xtk_scroll_setx(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_scroll_sety(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
XtkSubRef xtk_scroll_onscroll(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg);
bool      xtk_image_setw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_image_seth(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_image_setgrow(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_image_setself(XtkScene *scene, XtkCtrl control, XentFlexAlign value, XtkChangeStamp change);
bool      xtk_image_setml(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_image_setmt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_image_setmr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_image_setmb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_image_settip(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_image_setsrc(XtkScene *scene, XtkCtrl control, XtkResource value, XtkChangeStamp change);
bool      xtk_image_setfit(XtkScene *scene, XtkCtrl control, XtkImageStretch value, XtkChangeStamp change);
bool      xtk_progress_setw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_progress_seth(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_progress_setgrow(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_progress_setself(XtkScene *scene, XtkCtrl control, XentFlexAlign value, XtkChangeStamp change);
bool      xtk_progress_setml(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_progress_setmt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_progress_setmr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_progress_setmb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_progress_settip(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_progress_setmin(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_progress_setmax(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_progress_setvalue(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_progress_setindeterminate(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool      xtk_progress_setstate(XtkScene *scene, XtkCtrl control, XtkProgressState value, XtkChangeStamp change);
bool      xtk_progress_setpl(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_progress_setpt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_progress_setpr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_progress_setpb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_progress_setborder_width(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_list_setw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_list_seth(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_list_setgrow(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_list_setself(XtkScene *scene, XtkCtrl control, XentFlexAlign value, XtkChangeStamp change);
bool      xtk_list_setml(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_list_setmt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_list_setmr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_list_setmb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_list_settip(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_list_setenabled(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool      xtk_list_setsel(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool      xtk_list_setnitem(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool      xtk_list_setitemh(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_list_setitemw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_list_setncol(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool      xtk_list_setmode(XtkScene *scene, XtkCtrl control, XtkListSelMode value, XtkChangeStamp change);
bool      xtk_list_setfirst(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
XtkSubRef xtk_list_onselect(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg);
XtkSubRef xtk_list_oninvoke(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg);
XtkSubRef xtk_list_onrealize(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg);
bool      xtk_tab_setw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_tab_seth(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_tab_setgrow(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_tab_setshrink(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_tab_setself(XtkScene *scene, XtkCtrl control, XentFlexAlign value, XtkChangeStamp change);
bool      xtk_tab_setml(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_tab_setmt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_tab_setmr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_tab_setmb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_tab_settip(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_card_setw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_card_seth(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_card_setgrow(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_card_setshrink(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_card_setself(XtkScene *scene, XtkCtrl control, XentFlexAlign value, XtkChangeStamp change);
bool      xtk_card_setml(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_card_setmt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_card_setmr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_card_setmb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_card_settip(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_card_setdir(XtkScene *scene, XtkCtrl control, XtkStackDirection value, XtkChangeStamp change);
bool      xtk_card_setitems(XtkScene *scene, XtkCtrl control, XentFlexAlign value, XtkChangeStamp change);
bool      xtk_card_setjustify(XtkScene *scene, XtkCtrl control, XentFlexJustify value, XtkChangeStamp change);
bool      xtk_card_setgap(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_card_setpl(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_card_setpt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_card_setpr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_card_setpb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_card_setfill(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool      xtk_card_setfitw(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool      xtk_card_setfith(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool      xtk_card_setwrap(XtkScene *scene, XtkCtrl control, XentFlexWrap value, XtkChangeStamp change);
bool      xtk_card_setdrop(XtkScene *scene, XtkCtrl control, XtkDropOperation value, XtkChangeStamp change);
bool      xtk_card_setdragtext(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_card_setdragfiles(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
XtkSubRef xtk_card_ondraghover(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg);
XtkSubRef xtk_card_ondropfiles(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg);
XtkSubRef xtk_card_ondroptext(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg);
XtkSubRef xtk_card_ondragcompleted(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg);
bool      xtk_divider_setw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_divider_seth(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_divider_setgrow(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_divider_setshrink(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_divider_setself(XtkScene *scene, XtkCtrl control, XentFlexAlign value, XtkChangeStamp change);
bool      xtk_divider_setml(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_divider_setmt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_divider_setmr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_divider_setmb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_divider_settip(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_canvas_setw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_canvas_seth(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_canvas_setgrow(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_canvas_setshrink(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_canvas_setself(XtkScene *scene, XtkCtrl control, XentFlexAlign value, XtkChangeStamp change);
bool      xtk_canvas_setml(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_canvas_setmt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_canvas_setmr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_canvas_setmb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_canvas_settip(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_password_setw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_password_seth(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_password_setgrow(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_password_setself(XtkScene *scene, XtkCtrl control, XentFlexAlign value, XtkChangeStamp change);
bool      xtk_password_setml(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_password_setmt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_password_setmr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_password_setmb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_password_settext(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_password_settip(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_password_setenabled(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool      xtk_password_setplaceholder(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
);
XtkSubRef xtk_password_onchange(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg);
bool      xtk_number_setw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_number_seth(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_number_setgrow(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_number_setself(XtkScene *scene, XtkCtrl control, XentFlexAlign value, XtkChangeStamp change);
bool      xtk_number_setml(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_number_setmt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_number_setmr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_number_setmb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_number_settip(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_number_setenabled(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool      xtk_number_setvalue(XtkScene *scene, XtkCtrl control, double value, XtkChangeStamp change);
bool      xtk_number_setmin(XtkScene *scene, XtkCtrl control, double value, XtkChangeStamp change);
bool      xtk_number_setmax(XtkScene *scene, XtkCtrl control, double value, XtkChangeStamp change);
bool      xtk_number_setstep(XtkScene *scene, XtkCtrl control, double value, XtkChangeStamp change);
bool      xtk_number_sethidespin(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
XtkSubRef xtk_number_onchange(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg);
bool      xtk_link_setw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_link_seth(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_link_setgrow(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_link_setself(XtkScene *scene, XtkCtrl control, XentFlexAlign value, XtkChangeStamp change);
bool      xtk_link_setml(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_link_setmt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_link_setmr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_link_setmb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_link_settext(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_link_settip(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_link_setenabled(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool      xtk_link_seturl(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
XtkSubRef xtk_link_oninvoke(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg);
bool      xtk_repeat_setw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_repeat_seth(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_repeat_setgrow(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_repeat_setself(XtkScene *scene, XtkCtrl control, XentFlexAlign value, XtkChangeStamp change);
bool      xtk_repeat_setml(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_repeat_setmt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_repeat_setmr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_repeat_setmb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_repeat_settext(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_repeat_settip(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_repeat_setenabled(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool      xtk_repeat_seticon(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_repeat_setstyle(XtkScene *scene, XtkCtrl control, XtkButtonStyle value, XtkChangeStamp change);
XtkSubRef xtk_repeat_oninvoke(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg);
bool      xtk_progressring_setw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_progressring_seth(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_progressring_setgrow(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_progressring_setself(XtkScene *scene, XtkCtrl control, XentFlexAlign value, XtkChangeStamp change);
bool      xtk_progressring_setml(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_progressring_setmt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_progressring_setmr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_progressring_setmb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_progressring_settip(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_progressring_setmin(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_progressring_setmax(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_progressring_setvalue(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_progressring_setindeterminate(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_progressring_setstate(XtkScene *scene, XtkCtrl control, XtkProgressState value, XtkChangeStamp change);
bool xtk_progressring_setactive(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_badge_setw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_badge_seth(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_badge_setgrow(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_badge_setshrink(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_badge_setself(XtkScene *scene, XtkCtrl control, XentFlexAlign value, XtkChangeStamp change);
bool xtk_badge_setml(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_badge_setmt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_badge_setmr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_badge_setmb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_badge_settip(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_badge_setbadgemode(XtkScene *scene, XtkCtrl control, XtkBadgeMode value, XtkChangeStamp change);
bool xtk_badge_setvalue(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_badge_seticon(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_tooltip_setw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_tooltip_seth(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_tooltip_setgrow(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_tooltip_setself(XtkScene *scene, XtkCtrl control, XentFlexAlign value, XtkChangeStamp change);
bool xtk_tooltip_setml(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_tooltip_setmt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_tooltip_setmr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_tooltip_setmb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_tooltip_settext(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_tooltip_settip(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_tooltip_setopen(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_tooltip_setenabled(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_flyout_setw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_flyout_seth(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_flyout_setgrow(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_flyout_setself(XtkScene *scene, XtkCtrl control, XentFlexAlign value, XtkChangeStamp change);
bool xtk_flyout_setml(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_flyout_setmt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_flyout_setmr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_flyout_setmb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_flyout_settext(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_flyout_settip(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_flyout_setopen(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_flyout_setenabled(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_menufly_setw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_menufly_seth(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_menufly_setgrow(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_menufly_setself(XtkScene *scene, XtkCtrl control, XentFlexAlign value, XtkChangeStamp change);
bool xtk_menufly_setml(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_menufly_setmt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_menufly_setmr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_menufly_setmb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_menufly_settext(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_menufly_settip(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_menufly_setopen(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_menufly_setenabled(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_dropdown_setw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_dropdown_seth(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_dropdown_setgrow(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_dropdown_setself(XtkScene *scene, XtkCtrl control, XentFlexAlign value, XtkChangeStamp change);
bool xtk_dropdown_setml(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_dropdown_setmt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_dropdown_setmr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_dropdown_setmb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_dropdown_settext(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_dropdown_settip(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_dropdown_setenabled(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_dropdown_seticon(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_dropdown_setstyle(XtkScene *scene, XtkCtrl control, XtkButtonStyle value, XtkChangeStamp change);
XtkSubRef xtk_dropdown_oninvoke(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg);
bool      xtk_split_setw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_split_seth(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_split_setgrow(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_split_setself(XtkScene *scene, XtkCtrl control, XentFlexAlign value, XtkChangeStamp change);
bool      xtk_split_setml(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_split_setmt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_split_setmr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_split_setmb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_split_settext(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_split_settip(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_split_setenabled(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool      xtk_split_seticon(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_split_setstyle(XtkScene *scene, XtkCtrl control, XtkButtonStyle value, XtkChangeStamp change);
XtkSubRef xtk_split_oninvoke(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg);
bool      xtk_combo_setw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_combo_seth(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_combo_setgrow(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_combo_setself(XtkScene *scene, XtkCtrl control, XentFlexAlign value, XtkChangeStamp change);
bool      xtk_combo_setml(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_combo_setmt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_combo_setmr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_combo_setmb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_combo_settip(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_combo_setenabled(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_combo_setplaceholder(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_combo_setsel(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_combo_settext(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_combo_seteditable(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
XtkSubRef xtk_combo_onselect(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg);
XtkSubRef xtk_combo_oninvoke(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg);
XtkSubRef xtk_combo_onsubmit(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg);
bool      xtk_expander_setw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_expander_seth(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_expander_setgrow(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_expander_setself(XtkScene *scene, XtkCtrl control, XentFlexAlign value, XtkChangeStamp change);
bool      xtk_expander_setml(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_expander_setmt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_expander_setmr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_expander_setmb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_expander_settext(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_expander_settip(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_expander_setexpanded(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool      xtk_expander_setcontenth(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
XtkSubRef xtk_expander_ontoggle(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg);
bool      xtk_exphead_setw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_exphead_seth(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_exphead_setgrow(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_exphead_setself(XtkScene *scene, XtkCtrl control, XentFlexAlign value, XtkChangeStamp change);
bool      xtk_exphead_setml(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_exphead_setmt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_exphead_setmr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_exphead_setmb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_exphead_settext(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_exphead_settip(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_exphead_seticon(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_exphead_setenabled(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool      xtk_exphead_setselected(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool      xtk_exphead_setexpanded(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool      xtk_expbody_setw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_expbody_seth(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_expbody_setgrow(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_expbody_setshrink(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_expbody_setself(XtkScene *scene, XtkCtrl control, XentFlexAlign value, XtkChangeStamp change);
bool      xtk_expbody_setml(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_expbody_setmt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_expbody_setmr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_expbody_setmb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_expbody_settip(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_expbody_setdir(XtkScene *scene, XtkCtrl control, XtkStackDirection value, XtkChangeStamp change);
bool      xtk_expbody_setitems(XtkScene *scene, XtkCtrl control, XentFlexAlign value, XtkChangeStamp change);
bool      xtk_expbody_setjustify(XtkScene *scene, XtkCtrl control, XentFlexJustify value, XtkChangeStamp change);
bool      xtk_expbody_setgap(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_expbody_setpl(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_expbody_setpt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_expbody_setpr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_expbody_setpb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_expbody_setfill(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool      xtk_expbody_setfitw(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool      xtk_expbody_setfith(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool      xtk_expbody_setwrap(XtkScene *scene, XtkCtrl control, XentFlexWrap value, XtkChangeStamp change);
bool      xtk_expbody_setdrop(XtkScene *scene, XtkCtrl control, XtkDropOperation value, XtkChangeStamp change);
bool xtk_expbody_setdragtext(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_expbody_setdragfiles(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
XtkSubRef xtk_expbody_ondraghover(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg);
XtkSubRef xtk_expbody_ondropfiles(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg);
XtkSubRef xtk_expbody_ondroptext(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg);
XtkSubRef xtk_expbody_ondragcompleted(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg);
bool      xtk_infobar_setw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_infobar_seth(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_infobar_setgrow(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_infobar_setself(XtkScene *scene, XtkCtrl control, XentFlexAlign value, XtkChangeStamp change);
bool      xtk_infobar_setml(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_infobar_setmt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_infobar_setmr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_infobar_setmb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_infobar_settext(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_infobar_setmessage(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_infobar_settip(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_infobar_setseverity(XtkScene *scene, XtkCtrl control, XtkInfoBarSeverity value, XtkChangeStamp change);
bool xtk_infobar_setclosable(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
XtkSubRef xtk_infobar_onclose(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg);
bool      xtk_dialog_setw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_dialog_seth(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_dialog_setgrow(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_dialog_setshrink(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_dialog_setself(XtkScene *scene, XtkCtrl control, XentFlexAlign value, XtkChangeStamp change);
bool      xtk_dialog_setml(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_dialog_setmt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_dialog_setmr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_dialog_setmb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_dialog_settip(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_dialog_settext(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_dialog_setprimary(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_dialog_setsecondary(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_dialog_setclose(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_dialog_setcontenth(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_dialog_setopen(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
XtkSubRef xtk_dialog_onclose(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg);
XtkSubRef xtk_dialog_oninvoke(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg);
bool      xtk_dialogbody_setw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_dialogbody_seth(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_dialogbody_setgrow(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_dialogbody_setshrink(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_dialogbody_setself(XtkScene *scene, XtkCtrl control, XentFlexAlign value, XtkChangeStamp change);
bool      xtk_dialogbody_setml(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_dialogbody_setmt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_dialogbody_setmr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_dialogbody_setmb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_dialogbody_settip(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_dialogbody_setdir(XtkScene *scene, XtkCtrl control, XtkStackDirection value, XtkChangeStamp change);
bool xtk_dialogbody_setitems(XtkScene *scene, XtkCtrl control, XentFlexAlign value, XtkChangeStamp change);
bool xtk_dialogbody_setjustify(XtkScene *scene, XtkCtrl control, XentFlexJustify value, XtkChangeStamp change);
bool xtk_dialogbody_setgap(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_dialogbody_setpl(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_dialogbody_setpt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_dialogbody_setpr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_dialogbody_setpb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_dialogbody_setfill(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_dialogbody_setfitw(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_dialogbody_setfith(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_dialogbody_setwrap(XtkScene *scene, XtkCtrl control, XentFlexWrap value, XtkChangeStamp change);
bool xtk_dialogbody_setdrop(XtkScene *scene, XtkCtrl control, XtkDropOperation value, XtkChangeStamp change);
bool xtk_dialogbody_setdragtext(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
);
bool xtk_dialogbody_setdragfiles(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
);
XtkSubRef xtk_dialogbody_ondraghover(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg);
XtkSubRef xtk_dialogbody_ondropfiles(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg);
XtkSubRef xtk_dialogbody_ondroptext(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg);
XtkSubRef xtk_dialogbody_ondragcompleted(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg);
bool      xtk_menubar_setw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_menubar_seth(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_menubar_setgrow(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_menubar_setshrink(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_menubar_setself(XtkScene *scene, XtkCtrl control, XentFlexAlign value, XtkChangeStamp change);
bool      xtk_menubar_setml(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_menubar_setmt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_menubar_setmr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_menubar_setmb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_menubar_settip(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_menuitem_setw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_menuitem_seth(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_menuitem_setgrow(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_menuitem_setself(XtkScene *scene, XtkCtrl control, XentFlexAlign value, XtkChangeStamp change);
bool      xtk_menuitem_setml(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_menuitem_setmt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_menuitem_setmr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_menuitem_setmb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_menuitem_settext(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_menuitem_settip(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_menuitem_seticon(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_menuitem_setenabled(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool      xtk_menuitem_setselected(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool      xtk_menuitem_setexpanded(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
XtkSubRef xtk_menuitem_oninvoke(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg);
bool      xtk_nav_setw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_nav_seth(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_nav_setgrow(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_nav_setself(XtkScene *scene, XtkCtrl control, XentFlexAlign value, XtkChangeStamp change);
bool      xtk_nav_setml(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_nav_setmt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_nav_setmr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_nav_setmb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_nav_settip(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_nav_setenabled(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool      xtk_nav_setsel(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
XtkSubRef xtk_nav_onselect(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg);
XtkSubRef xtk_nav_oninvoke(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg);
bool      xtk_navitem_setw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_navitem_seth(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_navitem_setgrow(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_navitem_setself(XtkScene *scene, XtkCtrl control, XentFlexAlign value, XtkChangeStamp change);
bool      xtk_navitem_setml(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_navitem_setmt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_navitem_setmr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_navitem_setmb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_navitem_settext(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_navitem_settip(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_navitem_seticon(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_navitem_setenabled(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool      xtk_navitem_setselected(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool      xtk_navitem_setexpanded(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
XtkSubRef xtk_navitem_oninvoke(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg);
bool      xtk_tabs_setw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_tabs_seth(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_tabs_setgrow(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_tabs_setself(XtkScene *scene, XtkCtrl control, XentFlexAlign value, XtkChangeStamp change);
bool      xtk_tabs_setml(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_tabs_setmt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_tabs_setmr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_tabs_setmb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_tabs_settip(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_tabs_setenabled(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool      xtk_tabs_setsel(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool      xtk_tabs_setnitem(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
XtkSubRef xtk_tabs_onselect(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg);
XtkSubRef xtk_tabs_onclose(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg);
XtkSubRef xtk_tabs_oninvoke(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg);
bool      xtk_tabitem_setw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_tabitem_seth(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_tabitem_setgrow(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_tabitem_setself(XtkScene *scene, XtkCtrl control, XentFlexAlign value, XtkChangeStamp change);
bool      xtk_tabitem_setml(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_tabitem_setmt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_tabitem_setmr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_tabitem_setmb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_tabitem_settext(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_tabitem_settip(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_tabitem_seticon(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_tabitem_setenabled(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool      xtk_tabitem_setselected(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool      xtk_tabitem_setexpanded(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
XtkSubRef xtk_tabitem_oninvoke(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg);
bool      xtk_listitem_setw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_listitem_seth(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_listitem_setgrow(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_listitem_setself(XtkScene *scene, XtkCtrl control, XentFlexAlign value, XtkChangeStamp change);
bool      xtk_listitem_setml(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_listitem_setmt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_listitem_setmr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_listitem_setmb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_listitem_settext(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_listitem_settip(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_listitem_seticon(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_listitem_setenabled(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool      xtk_listitem_setselected(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool      xtk_listitem_setexpanded(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
XtkSubRef xtk_listitem_oninvoke(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg);
bool      xtk_listbox_setw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_listbox_seth(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_listbox_setgrow(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_listbox_setself(XtkScene *scene, XtkCtrl control, XentFlexAlign value, XtkChangeStamp change);
bool      xtk_listbox_setml(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_listbox_setmt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_listbox_setmr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_listbox_setmb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_listbox_settip(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_listbox_setenabled(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool      xtk_listbox_setsel(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool      xtk_listbox_setnitem(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool      xtk_listbox_setitemh(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_listbox_setitemw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_listbox_setncol(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool      xtk_listbox_setmode(XtkScene *scene, XtkCtrl control, XtkListSelMode value, XtkChangeStamp change);
bool      xtk_listbox_setfirst(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
XtkSubRef xtk_listbox_onselect(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg);
XtkSubRef xtk_listbox_oninvoke(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg);
XtkSubRef xtk_listbox_onrealize(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg);
bool      xtk_gridview_setw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_gridview_seth(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_gridview_setgrow(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_gridview_setself(XtkScene *scene, XtkCtrl control, XentFlexAlign value, XtkChangeStamp change);
bool      xtk_gridview_setml(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_gridview_setmt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_gridview_setmr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_gridview_setmb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_gridview_settip(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_gridview_setenabled(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool      xtk_gridview_setsel(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool      xtk_gridview_setnitem(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool      xtk_gridview_setitemh(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_gridview_setitemw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_gridview_setncol(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool      xtk_gridview_setmode(XtkScene *scene, XtkCtrl control, XtkListSelMode value, XtkChangeStamp change);
bool      xtk_gridview_setfirst(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
XtkSubRef xtk_gridview_onselect(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg);
XtkSubRef xtk_gridview_oninvoke(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg);
XtkSubRef xtk_gridview_onrealize(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg);
bool      xtk_repeater_setw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_repeater_seth(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_repeater_setgrow(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_repeater_setself(XtkScene *scene, XtkCtrl control, XentFlexAlign value, XtkChangeStamp change);
bool      xtk_repeater_setml(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_repeater_setmt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_repeater_setmr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_repeater_setmb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_repeater_settip(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_repeater_setenabled(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool      xtk_repeater_setsel(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool      xtk_repeater_setnitem(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool      xtk_repeater_setitemh(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_repeater_setitemw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_repeater_setncol(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool      xtk_repeater_setmode(XtkScene *scene, XtkCtrl control, XtkListSelMode value, XtkChangeStamp change);
bool      xtk_repeater_setfirst(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
XtkSubRef xtk_repeater_onrealize(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg);
bool      xtk_itemsview_setw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_itemsview_seth(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_itemsview_setgrow(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_itemsview_setself(XtkScene *scene, XtkCtrl control, XentFlexAlign value, XtkChangeStamp change);
bool      xtk_itemsview_setml(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_itemsview_setmt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_itemsview_setmr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_itemsview_setmb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_itemsview_settip(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_itemsview_setenabled(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool      xtk_itemsview_setsel(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool      xtk_itemsview_setnitem(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool      xtk_itemsview_setitemh(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_itemsview_setitemw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_itemsview_setncol(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool      xtk_itemsview_setmode(XtkScene *scene, XtkCtrl control, XtkListSelMode value, XtkChangeStamp change);
bool      xtk_itemsview_setinvoked(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool      xtk_itemsview_setfirst(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
XtkSubRef xtk_itemsview_onselect(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg);
XtkSubRef xtk_itemsview_oninvoke(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg);
XtkSubRef xtk_itemsview_onrealize(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg);
bool      xtk_flip_setw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_flip_seth(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_flip_setgrow(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_flip_setself(XtkScene *scene, XtkCtrl control, XentFlexAlign value, XtkChangeStamp change);
bool      xtk_flip_setml(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_flip_setmt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_flip_setmr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_flip_setmb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_flip_settip(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_flip_setsel(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool      xtk_flip_setdir(XtkScene *scene, XtkCtrl control, XtkStackDirection value, XtkChangeStamp change);
XtkSubRef xtk_flip_onselect(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg);
XtkSubRef xtk_flip_oninvoke(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg);
bool      xtk_pips_setw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_pips_seth(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_pips_setgrow(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_pips_setself(XtkScene *scene, XtkCtrl control, XentFlexAlign value, XtkChangeStamp change);
bool      xtk_pips_setml(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_pips_setmt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_pips_setmr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_pips_setmb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_pips_settip(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_pips_setsel(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool      xtk_pips_setnitem(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool      xtk_pips_setdir(XtkScene *scene, XtkCtrl control, XtkStackDirection value, XtkChangeStamp change);
bool      xtk_pips_setmaxvisible(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool      xtk_pips_setnav(XtkScene *scene, XtkCtrl control, XtkPipsNavVis value, XtkChangeStamp change);
XtkSubRef xtk_pips_onselect(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg);
XtkSubRef xtk_pips_oninvoke(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg);
bool      xtk_suggest_setw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_suggest_seth(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_suggest_setgrow(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_suggest_setself(XtkScene *scene, XtkCtrl control, XentFlexAlign value, XtkChangeStamp change);
bool      xtk_suggest_setml(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_suggest_setmt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_suggest_setmr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_suggest_setmb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_suggest_settext(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_suggest_settip(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_suggest_setenabled(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool      xtk_suggest_setplaceholder(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
);
bool      xtk_suggest_seticon(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
XtkSubRef xtk_suggest_onchange(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg);
XtkSubRef xtk_suggest_onquery(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg);
XtkSubRef xtk_suggest_onselect(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg);
bool      xtk_togglesplit_setw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_togglesplit_seth(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_togglesplit_setgrow(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_togglesplit_setself(XtkScene *scene, XtkCtrl control, XentFlexAlign value, XtkChangeStamp change);
bool      xtk_togglesplit_setml(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_togglesplit_setmt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_togglesplit_setmr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_togglesplit_setmb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_togglesplit_settext(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_togglesplit_settip(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_togglesplit_setenabled(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_togglesplit_setchecked(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
XtkSubRef xtk_togglesplit_oninvoke(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg);
XtkSubRef xtk_togglesplit_onchange(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg);
bool      xtk_radiogroup_setw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_radiogroup_seth(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_radiogroup_setgrow(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_radiogroup_setself(XtkScene *scene, XtkCtrl control, XentFlexAlign value, XtkChangeStamp change);
bool      xtk_radiogroup_setml(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_radiogroup_setmt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_radiogroup_setmr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_radiogroup_setmb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_radiogroup_settip(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_radiogroup_setenabled(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_radiogroup_setsel(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_radiogroup_setnitem(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_radiogroup_setncol(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
XtkSubRef xtk_radiogroup_onselect(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg);
XtkSubRef xtk_radiogroup_oninvoke(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg);
bool      xtk_rating_setw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_rating_seth(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_rating_setgrow(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_rating_setshrink(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_rating_setself(XtkScene *scene, XtkCtrl control, XentFlexAlign value, XtkChangeStamp change);
bool      xtk_rating_setml(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_rating_setmt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_rating_setmr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_rating_setmb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_rating_settip(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_rating_setvalue(XtkScene *scene, XtkCtrl control, double value, XtkChangeStamp change);
bool      xtk_rating_setmax(XtkScene *scene, XtkCtrl control, double value, XtkChangeStamp change);
bool      xtk_rating_settext(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_rating_setplaceholder(XtkScene *scene, XtkCtrl control, double value, XtkChangeStamp change);
bool      xtk_rating_setinitial(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool      xtk_rating_setclear(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool      xtk_rating_setreadonly(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
XtkSubRef xtk_rating_onrating(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg);
bool      xtk_selector_setw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_selector_seth(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_selector_setgrow(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_selector_setself(XtkScene *scene, XtkCtrl control, XentFlexAlign value, XtkChangeStamp change);
bool      xtk_selector_setml(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_selector_setmt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_selector_setmr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_selector_setmb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_selector_settip(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_selector_setenabled(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool      xtk_selector_setsel(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool      xtk_selector_setnitem(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
XtkSubRef xtk_selector_onselect(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg);
XtkSubRef xtk_selector_oninvoke(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg);
bool      xtk_selectoritem_setw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_selectoritem_seth(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_selectoritem_setgrow(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_selectoritem_setself(XtkScene *scene, XtkCtrl control, XentFlexAlign value, XtkChangeStamp change);
bool      xtk_selectoritem_setml(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_selectoritem_setmt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_selectoritem_setmr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_selectoritem_setmb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_selectoritem_settext(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_selectoritem_settip(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_selectoritem_seticon(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_selectoritem_setenabled(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_selectoritem_setselected(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_selectoritem_setexpanded(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
XtkSubRef xtk_selectoritem_oninvoke(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg);
bool      xtk_breadcrumb_setw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_breadcrumb_seth(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_breadcrumb_setgrow(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_breadcrumb_setself(XtkScene *scene, XtkCtrl control, XentFlexAlign value, XtkChangeStamp change);
bool      xtk_breadcrumb_setml(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_breadcrumb_setmt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_breadcrumb_setmr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_breadcrumb_setmb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_breadcrumb_settip(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_breadcrumb_setenabled(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_breadcrumb_setsel(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_breadcrumb_setnitem(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
XtkSubRef xtk_breadcrumb_onselect(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg);
XtkSubRef xtk_breadcrumb_oninvoke(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg);
bool      xtk_crumb_setw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_crumb_seth(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_crumb_setgrow(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_crumb_setself(XtkScene *scene, XtkCtrl control, XentFlexAlign value, XtkChangeStamp change);
bool      xtk_crumb_setml(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_crumb_setmt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_crumb_setmr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_crumb_setmb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_crumb_settext(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_crumb_settip(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_crumb_seticon(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_crumb_setenabled(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool      xtk_crumb_setselected(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool      xtk_crumb_setexpanded(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
XtkSubRef xtk_crumb_oninvoke(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg);
bool      xtk_teachtip_setw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_teachtip_seth(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_teachtip_setgrow(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_teachtip_setshrink(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_teachtip_setself(XtkScene *scene, XtkCtrl control, XentFlexAlign value, XtkChangeStamp change);
bool      xtk_teachtip_setml(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_teachtip_setmt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_teachtip_setmr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_teachtip_setmb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_teachtip_settip(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_teachtip_settext(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_teachtip_setsubtitle(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_teachtip_seticon(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_teachtip_setaction(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_teachtip_setactionaccent(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_teachtip_setclose(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_teachtip_setplacement(XtkScene *scene, XtkCtrl control, XtkTeachingTipPlacement value, XtkChangeStamp change);
bool xtk_teachtip_setuntargeted(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_teachtip_setlightdismiss(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_teachtip_settail(XtkScene *scene, XtkCtrl control, XtkTeachingTipTail value, XtkChangeStamp change);
bool xtk_teachtip_setplacementmargin(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_teachtip_setopen(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
XtkSubRef xtk_teachtip_onclose(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg);
XtkSubRef xtk_teachtip_oninvoke(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg);
bool      xtk_tree_setw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_tree_seth(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_tree_setgrow(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_tree_setself(XtkScene *scene, XtkCtrl control, XentFlexAlign value, XtkChangeStamp change);
bool      xtk_tree_setml(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_tree_setmt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_tree_setmr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_tree_setmb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_tree_settip(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_tree_setenabled(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool      xtk_tree_setsel(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool      xtk_tree_setnitem(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool      xtk_tree_setitemh(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
XtkSubRef xtk_tree_oninvoke(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg);
XtkSubRef xtk_tree_onexpand(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg);
XtkSubRef xtk_tree_onselect(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg);
bool      xtk_treeitem_setw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_treeitem_seth(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_treeitem_setgrow(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_treeitem_setself(XtkScene *scene, XtkCtrl control, XentFlexAlign value, XtkChangeStamp change);
bool      xtk_treeitem_setml(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_treeitem_setmt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_treeitem_setmr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_treeitem_setmb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_treeitem_settext(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_treeitem_settip(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_treeitem_seticon(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_treeitem_setenabled(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool      xtk_treeitem_setselected(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool      xtk_treeitem_setexpanded(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
XtkSubRef xtk_treeitem_onselect(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg);
XtkSubRef xtk_treeitem_oninvoke(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg);
bool      xtk_refresh_setw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_refresh_seth(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_refresh_setgrow(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_refresh_setself(XtkScene *scene, XtkCtrl control, XentFlexAlign value, XtkChangeStamp change);
bool      xtk_refresh_setml(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_refresh_setmt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_refresh_setmr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_refresh_setmb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_refresh_settip(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_refresh_setdirection(XtkScene *scene, XtkCtrl control, XtkPullDirection value, XtkChangeStamp change);
bool      xtk_refresh_setvisualizer(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_refresh_setthreshold(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_refresh_setrefreshing(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
XtkSubRef xtk_refresh_onrefresh(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg);
bool      xtk_avatar_setw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_avatar_seth(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_avatar_setgrow(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_avatar_setshrink(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_avatar_setself(XtkScene *scene, XtkCtrl control, XentFlexAlign value, XtkChangeStamp change);
bool      xtk_avatar_setml(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_avatar_setmt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_avatar_setmr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_avatar_setmb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_avatar_settip(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_avatar_settext(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_avatar_setinitials(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_avatar_setsrc(XtkScene *scene, XtkCtrl control, XtkResource value, XtkChangeStamp change);
bool xtk_avatar_setbadgeglyph(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_avatar_setbadgevalue(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_avatar_setgroup(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_pager_setw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_pager_seth(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_pager_setgrow(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_pager_setshrink(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_pager_setself(XtkScene *scene, XtkCtrl control, XentFlexAlign value, XtkChangeStamp change);
bool xtk_pager_setml(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_pager_setmt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_pager_setmr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_pager_setmb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_pager_settip(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_pager_setsel(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_pager_setnitem(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_pager_setdisplay(XtkScene *scene, XtkCtrl control, XtkPagerDisplayMode value, XtkChangeStamp change);
bool xtk_pager_setfirst(XtkScene *scene, XtkCtrl control, XtkPagerButtonVis value, XtkChangeStamp change);
bool xtk_pager_setprev(XtkScene *scene, XtkCtrl control, XtkPagerButtonVis value, XtkChangeStamp change);
bool xtk_pager_setnext(XtkScene *scene, XtkCtrl control, XtkPagerButtonVis value, XtkChangeStamp change);
bool xtk_pager_setlast(XtkScene *scene, XtkCtrl control, XtkPagerButtonVis value, XtkChangeStamp change);
bool xtk_pager_setprefix(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_pager_setsuffix(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
XtkSubRef xtk_pager_onselect(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg);
XtkSubRef xtk_pager_oninvoke(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg);
bool      xtk_splitview_setw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_splitview_seth(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_splitview_setgrow(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_splitview_setshrink(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_splitview_setself(XtkScene *scene, XtkCtrl control, XentFlexAlign value, XtkChangeStamp change);
bool      xtk_splitview_setml(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_splitview_setmt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_splitview_setmr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_splitview_setmb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_splitview_settip(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_splitview_setdir(XtkScene *scene, XtkCtrl control, XtkStackDirection value, XtkChangeStamp change);
bool      xtk_splitview_setgap(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_splitview_setpl(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_splitview_setpt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_splitview_setpr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_splitview_setpb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_splitview_setfill(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool      xtk_splitview_setopen(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_splitview_setdisplay(XtkScene *scene, XtkCtrl control, XtkSplitViewDisplayMode value, XtkChangeStamp change);
bool xtk_splitview_setplacement(
  XtkScene *scene, XtkCtrl control, XtkSplitViewPanePlacement value, XtkChangeStamp change
);
bool xtk_splitview_setopenlen(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_splitview_setcompactlen(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_splitpane_setw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_splitpane_seth(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_splitpane_setgrow(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_splitpane_setshrink(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_splitpane_setself(XtkScene *scene, XtkCtrl control, XentFlexAlign value, XtkChangeStamp change);
bool xtk_splitpane_setml(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_splitpane_setmt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_splitpane_setmr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_splitpane_setmb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_splitpane_settip(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_splitpane_setdir(XtkScene *scene, XtkCtrl control, XtkStackDirection value, XtkChangeStamp change);
bool xtk_splitpane_setitems(XtkScene *scene, XtkCtrl control, XentFlexAlign value, XtkChangeStamp change);
bool xtk_splitpane_setjustify(XtkScene *scene, XtkCtrl control, XentFlexJustify value, XtkChangeStamp change);
bool xtk_splitpane_setgap(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_splitpane_setpl(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_splitpane_setpt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_splitpane_setpr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_splitpane_setpb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_splitpane_setfill(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_splitpane_setfitw(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_splitpane_setfith(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_splitpane_setwrap(XtkScene *scene, XtkCtrl control, XentFlexWrap value, XtkChangeStamp change);
bool xtk_splitpane_setdrop(XtkScene *scene, XtkCtrl control, XtkDropOperation value, XtkChangeStamp change);
bool xtk_splitpane_setdragtext(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_splitpane_setdragfiles(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
);
XtkSubRef xtk_splitpane_ondraghover(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg);
XtkSubRef xtk_splitpane_ondropfiles(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg);
XtkSubRef xtk_splitpane_ondroptext(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg);
XtkSubRef xtk_splitpane_ondragcompleted(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg);
bool      xtk_splitbody_setw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_splitbody_seth(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_splitbody_setgrow(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_splitbody_setshrink(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_splitbody_setself(XtkScene *scene, XtkCtrl control, XentFlexAlign value, XtkChangeStamp change);
bool      xtk_splitbody_setml(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_splitbody_setmt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_splitbody_setmr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_splitbody_setmb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_splitbody_settip(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_splitbody_setdir(XtkScene *scene, XtkCtrl control, XtkStackDirection value, XtkChangeStamp change);
bool      xtk_splitbody_setitems(XtkScene *scene, XtkCtrl control, XentFlexAlign value, XtkChangeStamp change);
bool      xtk_splitbody_setjustify(XtkScene *scene, XtkCtrl control, XentFlexJustify value, XtkChangeStamp change);
bool      xtk_splitbody_setgap(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_splitbody_setpl(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_splitbody_setpt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_splitbody_setpr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_splitbody_setpb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_splitbody_setfill(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool      xtk_splitbody_setfitw(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool      xtk_splitbody_setfith(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool      xtk_splitbody_setwrap(XtkScene *scene, XtkCtrl control, XentFlexWrap value, XtkChangeStamp change);
bool      xtk_splitbody_setdrop(XtkScene *scene, XtkCtrl control, XtkDropOperation value, XtkChangeStamp change);
bool xtk_splitbody_setdragtext(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_splitbody_setdragfiles(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
);
XtkSubRef xtk_splitbody_ondraghover(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg);
XtkSubRef xtk_splitbody_ondropfiles(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg);
XtkSubRef xtk_splitbody_ondroptext(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg);
XtkSubRef xtk_splitbody_ondragcompleted(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg);
bool      xtk_titlebar_setw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_titlebar_seth(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_titlebar_setgrow(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_titlebar_setshrink(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_titlebar_setself(XtkScene *scene, XtkCtrl control, XentFlexAlign value, XtkChangeStamp change);
bool      xtk_titlebar_setml(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_titlebar_setmt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_titlebar_setmr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_titlebar_setmb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_titlebar_settip(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_titlebar_settext(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_titlebar_setsubtitle(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_titlebar_seticon(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_titlebar_setshowback(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_titlebar_setbackdisabled(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_titlebar_setshowtoggle(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_titlebar_setintegrate(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
XtkSubRef xtk_titlebar_oninvoke(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg);
XtkSubRef xtk_titlebar_ontoggle(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg);
bool      xtk_scrollbar_setw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_scrollbar_seth(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_scrollbar_setgrow(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_scrollbar_setself(XtkScene *scene, XtkCtrl control, XentFlexAlign value, XtkChangeStamp change);
bool      xtk_scrollbar_setml(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_scrollbar_setmt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_scrollbar_setmr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_scrollbar_setmb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_scrollbar_settip(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_scrollbar_setenabled(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool      xtk_scrollbar_setdir(XtkScene *scene, XtkCtrl control, XtkStackDirection value, XtkChangeStamp change);
bool      xtk_scrollbar_setmin(XtkScene *scene, XtkCtrl control, double value, XtkChangeStamp change);
bool      xtk_scrollbar_setmax(XtkScene *scene, XtkCtrl control, double value, XtkChangeStamp change);
bool      xtk_scrollbar_setvalue(XtkScene *scene, XtkCtrl control, double value, XtkChangeStamp change);
bool      xtk_scrollbar_setviewport(XtkScene *scene, XtkCtrl control, double value, XtkChangeStamp change);
bool      xtk_scrollbar_setsmallchange(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_scrollbar_setlargechange(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_scrollbar_setindicator(XtkScene *scene, XtkCtrl control, XtkScrollBarIndicator value, XtkChangeStamp change);
XtkSubRef xtk_scrollbar_onchange(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg);
bool      xtk_looping_setw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_looping_seth(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_looping_setgrow(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_looping_setself(XtkScene *scene, XtkCtrl control, XentFlexAlign value, XtkChangeStamp change);
bool      xtk_looping_setml(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_looping_setmt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_looping_setmr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_looping_setmb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_looping_settip(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_looping_setenabled(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool      xtk_looping_setnitem(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool      xtk_looping_setsel(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool      xtk_looping_setitemh(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_looping_setitemw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_looping_setloop(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
XtkSubRef xtk_looping_onselect(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg);
XtkSubRef xtk_looping_oninvoke(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg);
bool      xtk_datepicker_setw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_datepicker_seth(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_datepicker_setgrow(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_datepicker_setself(XtkScene *scene, XtkCtrl control, XentFlexAlign value, XtkChangeStamp change);
bool      xtk_datepicker_setml(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_datepicker_setmt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_datepicker_setmr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_datepicker_setmb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_datepicker_settip(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_datepicker_setenabled(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_datepicker_setheader(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_datepicker_setdate(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_datepicker_setminyear(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_datepicker_setmaxyear(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
XtkSubRef xtk_datepicker_onvalue(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg);
bool      xtk_timepicker_setw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_timepicker_seth(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_timepicker_setgrow(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_timepicker_setself(XtkScene *scene, XtkCtrl control, XentFlexAlign value, XtkChangeStamp change);
bool      xtk_timepicker_setml(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_timepicker_setmt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_timepicker_setmr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_timepicker_setmb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_timepicker_settip(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_timepicker_setenabled(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_timepicker_setheader(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_timepicker_settime(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_timepicker_setclock(XtkScene *scene, XtkCtrl control, XtkClock value, XtkChangeStamp change);
bool xtk_timepicker_setstep(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
XtkSubRef xtk_timepicker_onvalue(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg);
bool      xtk_calendar_setw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_calendar_seth(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_calendar_setgrow(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_calendar_setself(XtkScene *scene, XtkCtrl control, XentFlexAlign value, XtkChangeStamp change);
bool      xtk_calendar_setml(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_calendar_setmt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_calendar_setmr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_calendar_setmb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_calendar_settip(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_calendar_setenabled(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool      xtk_calendar_setdate(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool      xtk_calendar_setmode(XtkScene *scene, XtkCtrl control, XtkCalendarMode value, XtkChangeStamp change);
bool      xtk_calendar_setmindate(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool      xtk_calendar_setmaxdate(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool      xtk_calendar_setfirstday(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
XtkSubRef xtk_calendar_ondate(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg);
bool      xtk_colorpicker_setw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_colorpicker_seth(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_colorpicker_setgrow(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_colorpicker_setself(XtkScene *scene, XtkCtrl control, XentFlexAlign value, XtkChangeStamp change);
bool      xtk_colorpicker_setml(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_colorpicker_setmt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_colorpicker_setmr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_colorpicker_setmb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_colorpicker_settip(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_colorpicker_setenabled(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_colorpicker_setcolor(XtkScene *scene, XtkCtrl control, XtkColor value, XtkChangeStamp change);
bool xtk_colorpicker_setalpha(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_colorpicker_setmorebutton(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_colorpicker_setspectrum(XtkScene *scene, XtkCtrl control, XtkSpectrum value, XtkChangeStamp change);
XtkSubRef xtk_colorpicker_onvalue(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg);
bool      xtk_colheader_setw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_colheader_seth(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_colheader_setgrow(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_colheader_setshrink(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_colheader_setself(XtkScene *scene, XtkCtrl control, XentFlexAlign value, XtkChangeStamp change);
bool      xtk_colheader_setml(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_colheader_setmt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_colheader_setmr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_colheader_setmb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_colheader_settip(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_colitem_setw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_colitem_setminw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_colitem_setmaxw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_colitem_settext(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_colitem_settip(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_colitem_setalign(XtkScene *scene, XtkCtrl control, XtkTextAlign value, XtkChangeStamp change);
bool      xtk_colitem_setenabled(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool      xtk_colitem_setresizable(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool      xtk_colitem_setsort(XtkScene *scene, XtkCtrl control, XtkSortDirection value, XtkChangeStamp change);
XtkSubRef xtk_colitem_oninvoke(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg);
XtkSubRef xtk_colitem_onresize(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg);
XtkSubRef xtk_colitem_onfit(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg);
XtkSubRef xtk_colitem_onreorder(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg);
bool      xtk_commandbar_setw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_commandbar_seth(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_commandbar_setgrow(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_commandbar_setself(XtkScene *scene, XtkCtrl control, XentFlexAlign value, XtkChangeStamp change);
bool      xtk_commandbar_setml(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_commandbar_setmt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_commandbar_setmr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_commandbar_setmb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_commandbar_settip(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_commandbar_setenabled(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_commandbar_setopen(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_commandbar_setsticky(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_commandbar_setmode(XtkScene *scene, XtkCtrl control, XtkAppBarMode value, XtkChangeStamp change);
bool xtk_commandbar_setlabels(XtkScene *scene, XtkCtrl control, XtkLabelPosition value, XtkChangeStamp change);
bool xtk_commandbar_setmore(XtkScene *scene, XtkCtrl control, XtkOverflowButton value, XtkChangeStamp change);
bool xtk_commandbar_setdynamic(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
XtkSubRef xtk_commandbar_onopen(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg);
bool      xtk_appbarbutton_setw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_appbarbutton_seth(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_appbarbutton_setgrow(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_appbarbutton_setself(XtkScene *scene, XtkCtrl control, XentFlexAlign value, XtkChangeStamp change);
bool      xtk_appbarbutton_setml(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_appbarbutton_setmt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_appbarbutton_setmr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_appbarbutton_setmb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_appbarbutton_settip(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_appbarbutton_settext(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_appbarbutton_seticon(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_appbarbutton_setenabled(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_appbarbutton_setlabelpos(XtkScene *scene, XtkCtrl control, XtkElementLabel value, XtkChangeStamp change);
bool xtk_appbarbutton_setaccel(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_appbarbutton_setsecondary(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_appbarbutton_setorder(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
XtkSubRef xtk_appbarbutton_oninvoke(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg);
bool      xtk_appbartoggle_setw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_appbartoggle_seth(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_appbartoggle_setgrow(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_appbartoggle_setself(XtkScene *scene, XtkCtrl control, XentFlexAlign value, XtkChangeStamp change);
bool      xtk_appbartoggle_setml(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_appbartoggle_setmt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_appbartoggle_setmr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_appbartoggle_setmb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_appbartoggle_settip(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_appbartoggle_settext(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_appbartoggle_seticon(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_appbartoggle_setenabled(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_appbartoggle_setlabelpos(XtkScene *scene, XtkCtrl control, XtkElementLabel value, XtkChangeStamp change);
bool xtk_appbartoggle_setaccel(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_appbartoggle_setchecked(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_appbartoggle_setsecondary(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_appbartoggle_setorder(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
XtkSubRef xtk_appbartoggle_onchange(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg);
bool      xtk_appbarsep_setw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_appbarsep_seth(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_appbarsep_setgrow(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_appbarsep_setself(XtkScene *scene, XtkCtrl control, XentFlexAlign value, XtkChangeStamp change);
bool      xtk_appbarsep_setml(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_appbarsep_setmt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_appbarsep_setmr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_appbarsep_setmb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_appbarsep_settip(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_appbarsep_setsecondary(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool      xtk_appbarsep_setorder(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);

#endif
