#ifndef XTK_CONTROLS_H
#define XTK_CONTROLS_H

/* Typed conveniences over the standard catalog + txn protocol.
 * Generated from tools/catalog.lua. */

#include "xtk_catalog.h"
#include "xtk_scene.h"

#include <stdint.h>

typedef struct XtkLayoutProps {
	uint64_t       set; /* presence mask: bit i = props[i] */
	XtkChangeStamp stamp;
	float          w;
	float          h;
	float          grow;
	float          shrink;
	uint32_t       self;
	float          ml;
	float          mt;
	float          mr;
	float          mb;
	char const    *tip;
	uint32_t       tip_len; /* 0 => strlen(tip) when tip != NULL */
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
	uint64_t       set; /* presence mask: bit i = props[i] */
	XtkChangeStamp stamp;
	float          w;
	float          h;
	float          grow;
	float          shrink;
	uint32_t       self;
	float          ml;
	float          mt;
	float          mr;
	float          mb;
	char const    *tip;
	uint32_t       tip_len; /* 0 => strlen(tip) when tip != NULL */
	uint32_t       dir;
	uint32_t       items;
	uint32_t       justify;
	float          gap;
	float          pl;
	float          pt;
	float          pr;
	float          pb;
	bool           fill;
	bool           fitw;
	bool           fith;
	uint32_t       wrap;
} XtkContainerProps;

#define XTK_CONTAINER_W_MASK       (1ull << 0u)
#define XTK_CONTAINER_H_MASK       (1ull << 1u)
#define XTK_CONTAINER_GROW_MASK    (1ull << 2u)
#define XTK_CONTAINER_SHRINK_MASK  (1ull << 3u)
#define XTK_CONTAINER_SELF_MASK    (1ull << 4u)
#define XTK_CONTAINER_ML_MASK      (1ull << 5u)
#define XTK_CONTAINER_MT_MASK      (1ull << 6u)
#define XTK_CONTAINER_MR_MASK      (1ull << 7u)
#define XTK_CONTAINER_MB_MASK      (1ull << 8u)
#define XTK_CONTAINER_TIP_MASK     (1ull << 9u)
#define XTK_CONTAINER_DIR_MASK     (1ull << 10u)
#define XTK_CONTAINER_ITEMS_MASK   (1ull << 11u)
#define XTK_CONTAINER_JUSTIFY_MASK (1ull << 12u)
#define XTK_CONTAINER_GAP_MASK     (1ull << 13u)
#define XTK_CONTAINER_PL_MASK      (1ull << 14u)
#define XTK_CONTAINER_PT_MASK      (1ull << 15u)
#define XTK_CONTAINER_PR_MASK      (1ull << 16u)
#define XTK_CONTAINER_PB_MASK      (1ull << 17u)
#define XTK_CONTAINER_FILL_MASK    (1ull << 18u)
#define XTK_CONTAINER_FITW_MASK    (1ull << 19u)
#define XTK_CONTAINER_FITH_MASK    (1ull << 20u)
#define XTK_CONTAINER_WRAP_MASK    (1ull << 21u)

typedef struct XtkTextProps {
	uint64_t       set; /* presence mask: bit i = props[i] */
	XtkChangeStamp stamp;
	float          w;
	float          h;
	float          grow;
	uint32_t       self;
	float          ml;
	float          mt;
	float          mr;
	float          mb;
	char const    *text;
	uint32_t       text_len; /* 0 => strlen(text) when text != NULL */
	char const    *tip;
	uint32_t       tip_len;  /* 0 => strlen(tip) when tip != NULL */
	float          fontsize;
	uint32_t       fontweight;
	uint32_t       textalign;
	XtkColor       fg;
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

typedef struct XtkButtonProps {
	uint64_t       set; /* presence mask: bit i = props[i] */
	XtkChangeStamp stamp;
	float          w;
	float          h;
	float          grow;
	uint32_t       self;
	float          ml;
	float          mt;
	float          mr;
	float          mb;
	char const    *text;
	uint32_t       text_len; /* 0 => strlen(text) when text != NULL */
	char const    *tip;
	uint32_t       tip_len;  /* 0 => strlen(tip) when tip != NULL */
	bool           enabled;
	char const    *icon;
	uint32_t       icon_len; /* 0 => strlen(icon) when icon != NULL */
	uint32_t       style;
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
	uint64_t       set; /* presence mask: bit i = props[i] */
	XtkChangeStamp stamp;
	float          w;
	float          h;
	float          grow;
	uint32_t       self;
	float          ml;
	float          mt;
	float          mr;
	float          mb;
	char const    *text;
	uint32_t       text_len; /* 0 => strlen(text) when text != NULL */
	char const    *tip;
	uint32_t       tip_len;  /* 0 => strlen(tip) when tip != NULL */
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

typedef struct XtkSliderProps {
	uint64_t       set; /* presence mask: bit i = props[i] */
	XtkChangeStamp stamp;
	float          w;
	float          h;
	float          grow;
	uint32_t       self;
	float          ml;
	float          mt;
	float          mr;
	float          mb;
	char const    *tip;
	uint32_t       tip_len; /* 0 => strlen(tip) when tip != NULL */
	bool           enabled;
	float          min;
	float          max;
	float          value;
	float          step;
	float          tick;
	uint32_t       tickplace;
	uint32_t       snapsto;
	float          smallchange;
	float          largechange;
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

typedef struct XtkInputProps {
	uint64_t       set; /* presence mask: bit i = props[i] */
	XtkChangeStamp stamp;
	float          w;
	float          h;
	float          grow;
	uint32_t       self;
	float          ml;
	float          mt;
	float          mr;
	float          mb;
	char const    *text;
	uint32_t       text_len; /* 0 => strlen(text) when text != NULL */
	char const    *tip;
	uint32_t       tip_len;  /* 0 => strlen(tip) when tip != NULL */
	bool           enabled;
	char const    *placeholder;
	uint32_t       placeholder_len; /* 0 => strlen(placeholder) when placeholder != NULL */
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

typedef struct XtkImageProps {
	uint64_t       set; /* presence mask: bit i = props[i] */
	XtkChangeStamp stamp;
	float          w;
	float          h;
	float          grow;
	uint32_t       self;
	float          ml;
	float          mt;
	float          mr;
	float          mb;
	char const    *tip;
	uint32_t       tip_len; /* 0 => strlen(tip) when tip != NULL */
	XtkResource    src;
	uint32_t       fit;
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
	uint64_t       set; /* presence mask: bit i = props[i] */
	XtkChangeStamp stamp;
	float          w;
	float          h;
	float          grow;
	uint32_t       self;
	float          ml;
	float          mt;
	float          mr;
	float          mb;
	char const    *tip;
	uint32_t       tip_len; /* 0 => strlen(tip) when tip != NULL */
	float          min;
	float          max;
	float          value;
	bool           indeterminate;
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

typedef struct XtkNumberProps {
	uint64_t       set; /* presence mask: bit i = props[i] */
	XtkChangeStamp stamp;
	float          w;
	float          h;
	float          grow;
	uint32_t       self;
	float          ml;
	float          mt;
	float          mr;
	float          mb;
	char const    *tip;
	uint32_t       tip_len; /* 0 => strlen(tip) when tip != NULL */
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
	uint64_t       set; /* presence mask: bit i = props[i] */
	XtkChangeStamp stamp;
	float          w;
	float          h;
	float          grow;
	uint32_t       self;
	float          ml;
	float          mt;
	float          mr;
	float          mb;
	char const    *text;
	uint32_t       text_len; /* 0 => strlen(text) when text != NULL */
	char const    *tip;
	uint32_t       tip_len;  /* 0 => strlen(tip) when tip != NULL */
	char const    *icon;
	uint32_t       icon_len; /* 0 => strlen(icon) when icon != NULL */
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
	uint64_t       set; /* presence mask: bit i = props[i] */
	XtkChangeStamp stamp;
	float          w;
	float          h;
	float          grow;
	uint32_t       self;
	float          ml;
	float          mt;
	float          mr;
	float          mb;
	char const    *tip;
	uint32_t       tip_len; /* 0 => strlen(tip) when tip != NULL */
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

typedef struct XtkListProps {
	uint64_t       set; /* presence mask: bit i = props[i] */
	XtkChangeStamp stamp;
	float          w;
	float          h;
	float          grow;
	uint32_t       self;
	float          ml;
	float          mt;
	float          mr;
	float          mb;
	char const    *tip;
	uint32_t       tip_len; /* 0 => strlen(tip) when tip != NULL */
	bool           enabled;
	int32_t        sel;
	int32_t        nitem;
	float          itemh;
	float          itemw;
	int32_t        ncol;
	uint32_t       mode;
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

typedef struct XtkRadioGroupProps {
	uint64_t       set; /* presence mask: bit i = props[i] */
	XtkChangeStamp stamp;
	float          w;
	float          h;
	float          grow;
	uint32_t       self;
	float          ml;
	float          mt;
	float          mr;
	float          mb;
	char const    *tip;
	uint32_t       tip_len; /* 0 => strlen(tip) when tip != NULL */
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
	uint64_t       set; /* presence mask: bit i = props[i] */
	XtkChangeStamp stamp;
	float          w;
	float          h;
	float          grow;
	uint32_t       self;
	float          ml;
	float          mt;
	float          mr;
	float          mb;
	char const    *tip;
	uint32_t       tip_len; /* 0 => strlen(tip) when tip != NULL */
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
	uint64_t       set; /* presence mask: bit i = props[i] */
	XtkChangeStamp stamp;
	float          w;
	float          h;
	float          grow;
	uint32_t       self;
	float          ml;
	float          mt;
	float          mr;
	float          mb;
	char const    *tip;
	uint32_t       tip_len; /* 0 => strlen(tip) when tip != NULL */
	bool           enabled;
	char const    *placeholder;
	uint32_t       placeholder_len; /* 0 => strlen(placeholder) when placeholder != NULL */
	int32_t        sel;
	int32_t        nitem;
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
#define XTK_COMBO_NITEM_MASK       (1ull << 12u)

typedef struct XtkOverlayProps {
	uint64_t       set; /* presence mask: bit i = props[i] */
	XtkChangeStamp stamp;
	float          w;
	float          h;
	float          grow;
	uint32_t       self;
	float          ml;
	float          mt;
	float          mr;
	float          mb;
	char const    *text;
	uint32_t       text_len; /* 0 => strlen(text) when text != NULL */
	char const    *tip;
	uint32_t       tip_len;  /* 0 => strlen(tip) when tip != NULL */
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
	uint64_t       set; /* presence mask: bit i = props[i] */
	XtkChangeStamp stamp;
	float          w;
	float          h;
	float          grow;
	uint32_t       self;
	float          ml;
	float          mt;
	float          mr;
	float          mb;
	char const    *tip;
	uint32_t       tip_len; /* 0 => strlen(tip) when tip != NULL */
	bool           enabled;
	int32_t        sel;
	int32_t        nitem;
	float          itemh;
	float          itemw;
	int32_t        ncol;
	uint32_t       mode;
	bool           invoked;
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

typedef struct XtkExpanderProps {
	uint64_t       set; /* presence mask: bit i = props[i] */
	XtkChangeStamp stamp;
	float          w;
	float          h;
	float          grow;
	uint32_t       self;
	float          ml;
	float          mt;
	float          mr;
	float          mb;
	char const    *text;
	uint32_t       text_len; /* 0 => strlen(text) when text != NULL */
	char const    *tip;
	uint32_t       tip_len;  /* 0 => strlen(tip) when tip != NULL */
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
	uint64_t       set; /* presence mask: bit i = props[i] */
	XtkChangeStamp stamp;
	float          w;
	float          h;
	float          grow;
	uint32_t       self;
	float          ml;
	float          mt;
	float          mr;
	float          mb;
	char const    *text;
	uint32_t       text_len;    /* 0 => strlen(text) when text != NULL */
	char const    *message;
	uint32_t       message_len; /* 0 => strlen(message) when message != NULL */
	char const    *tip;
	uint32_t       tip_len;     /* 0 => strlen(tip) when tip != NULL */
	uint32_t       severity;
	bool           closable;
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
	uint64_t       set; /* presence mask: bit i = props[i] */
	XtkChangeStamp stamp;
	float          w;
	float          h;
	float          grow;
	uint32_t       self;
	float          ml;
	float          mt;
	float          mr;
	float          mb;
	char const    *tip;
	uint32_t       tip_len; /* 0 => strlen(tip) when tip != NULL */
	uint32_t       direction;
	float          visualizer;
	float          threshold;
	bool           refreshing;
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
	uint64_t       set; /* presence mask: bit i = props[i] */
	XtkChangeStamp stamp;
	float          w;
	float          h;
	float          grow;
	uint32_t       self;
	float          ml;
	float          mt;
	float          mr;
	float          mb;
	char const    *tip;
	uint32_t       tip_len; /* 0 => strlen(tip) when tip != NULL */
	int32_t        sel;
	uint32_t       dir;
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
	uint64_t       set; /* presence mask: bit i = props[i] */
	XtkChangeStamp stamp;
	float          w;
	float          h;
	float          grow;
	uint32_t       self;
	float          ml;
	float          mt;
	float          mr;
	float          mb;
	char const    *tip;
	uint32_t       tip_len; /* 0 => strlen(tip) when tip != NULL */
	int32_t        sel;
	int32_t        nitem;
	uint32_t       dir;
	int32_t        maxvisible;
	uint32_t       nav;
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
	uint64_t       set; /* presence mask: bit i = props[i] */
	XtkChangeStamp stamp;
	float          w;
	float          h;
	float          grow;
	uint32_t       self;
	float          ml;
	float          mt;
	float          mr;
	float          mb;
	char const    *text;
	uint32_t       text_len; /* 0 => strlen(text) when text != NULL */
	char const    *tip;
	uint32_t       tip_len;  /* 0 => strlen(tip) when tip != NULL */
	bool           enabled;
	char const    *placeholder;
	uint32_t       placeholder_len; /* 0 => strlen(placeholder) when placeholder != NULL */
	char const    *icon;
	uint32_t       icon_len;        /* 0 => strlen(icon) when icon != NULL */
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
	uint64_t       set; /* presence mask: bit i = props[i] */
	XtkChangeStamp stamp;
	float          w;
	float          h;
	float          grow;
	float          shrink;
	uint32_t       self;
	float          ml;
	float          mt;
	float          mr;
	float          mb;
	char const    *tip;
	uint32_t       tip_len; /* 0 => strlen(tip) when tip != NULL */
	uint32_t       badgemode;
	int32_t        value;
	char const    *icon;
	uint32_t       icon_len; /* 0 => strlen(icon) when icon != NULL */
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
	uint64_t       set; /* presence mask: bit i = props[i] */
	XtkChangeStamp stamp;
	float          w;
	float          h;
	float          grow;
	float          shrink;
	uint32_t       self;
	float          ml;
	float          mt;
	float          mr;
	float          mb;
	char const    *tip;
	uint32_t       tip_len;       /* 0 => strlen(tip) when tip != NULL */
	char const    *text;
	uint32_t       text_len;      /* 0 => strlen(text) when text != NULL */
	char const    *primary;
	uint32_t       primary_len;   /* 0 => strlen(primary) when primary != NULL */
	char const    *secondary;
	uint32_t       secondary_len; /* 0 => strlen(secondary) when secondary != NULL */
	char const    *close;
	uint32_t       close_len;     /* 0 => strlen(close) when close != NULL */
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
	uint64_t       set; /* presence mask: bit i = props[i] */
	XtkChangeStamp stamp;
	float          w;
	float          h;
	float          grow;
	float          shrink;
	uint32_t       self;
	float          ml;
	float          mt;
	float          mr;
	float          mb;
	char const    *tip;
	uint32_t       tip_len;      /* 0 => strlen(tip) when tip != NULL */
	char const    *text;
	uint32_t       text_len;     /* 0 => strlen(text) when text != NULL */
	char const    *subtitle;
	uint32_t       subtitle_len; /* 0 => strlen(subtitle) when subtitle != NULL */
	char const    *icon;
	uint32_t       icon_len;     /* 0 => strlen(icon) when icon != NULL */
	char const    *action;
	uint32_t       action_len;   /* 0 => strlen(action) when action != NULL */
	bool           actionaccent;
	char const    *close;
	uint32_t       close_len; /* 0 => strlen(close) when close != NULL */
	uint32_t       placement;
	bool           untargeted;
	bool           lightdismiss;
	uint32_t       tail;
	float          placementmargin;
	bool           open;
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
	uint64_t       set; /* presence mask: bit i = props[i] */
	XtkChangeStamp stamp;
	float          w;
	float          h;
	float          grow;
	float          shrink;
	uint32_t       self;
	float          ml;
	float          mt;
	float          mr;
	float          mb;
	char const    *tip;
	uint32_t       tip_len;      /* 0 => strlen(tip) when tip != NULL */
	char const    *text;
	uint32_t       text_len;     /* 0 => strlen(text) when text != NULL */
	char const    *initials;
	uint32_t       initials_len; /* 0 => strlen(initials) when initials != NULL */
	XtkResource    src;
	char const    *badgeglyph;
	uint32_t       badgeglyph_len; /* 0 => strlen(badgeglyph) when badgeglyph != NULL */
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
	uint64_t       set; /* presence mask: bit i = props[i] */
	XtkChangeStamp stamp;
	float          w;
	float          h;
	float          grow;
	float          shrink;
	uint32_t       self;
	float          ml;
	float          mt;
	float          mr;
	float          mb;
	char const    *tip;
	uint32_t       tip_len; /* 0 => strlen(tip) when tip != NULL */
	int32_t        sel;
	int32_t        nitem;
	uint32_t       display;
	uint32_t       first;
	uint32_t       prev;
	uint32_t       next;
	uint32_t       last;
	char const    *prefix;
	uint32_t       prefix_len; /* 0 => strlen(prefix) when prefix != NULL */
	char const    *suffix;
	uint32_t       suffix_len; /* 0 => strlen(suffix) when suffix != NULL */
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
	uint64_t       set; /* presence mask: bit i = props[i] */
	XtkChangeStamp stamp;
	float          w;
	float          h;
	float          grow;
	float          shrink;
	uint32_t       self;
	float          ml;
	float          mt;
	float          mr;
	float          mb;
	char const    *tip;
	uint32_t       tip_len; /* 0 => strlen(tip) when tip != NULL */
	uint32_t       dir;
	uint32_t       items;
	uint32_t       justify;
	float          gap;
	float          pl;
	float          pt;
	float          pr;
	float          pb;
	bool           fill;
	bool           fitw;
	bool           fith;
	uint32_t       wrap;
	bool           open;
	uint32_t       display;
	uint32_t       placement;
	float          openlen;
	float          compactlen;
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
#define XTK_SPLITVIEW_ITEMS_MASK      (1ull << 11u)
#define XTK_SPLITVIEW_JUSTIFY_MASK    (1ull << 12u)
#define XTK_SPLITVIEW_GAP_MASK        (1ull << 13u)
#define XTK_SPLITVIEW_PL_MASK         (1ull << 14u)
#define XTK_SPLITVIEW_PT_MASK         (1ull << 15u)
#define XTK_SPLITVIEW_PR_MASK         (1ull << 16u)
#define XTK_SPLITVIEW_PB_MASK         (1ull << 17u)
#define XTK_SPLITVIEW_FILL_MASK       (1ull << 18u)
#define XTK_SPLITVIEW_FITW_MASK       (1ull << 19u)
#define XTK_SPLITVIEW_FITH_MASK       (1ull << 20u)
#define XTK_SPLITVIEW_WRAP_MASK       (1ull << 21u)
#define XTK_SPLITVIEW_OPEN_MASK       (1ull << 22u)
#define XTK_SPLITVIEW_DISPLAY_MASK    (1ull << 23u)
#define XTK_SPLITVIEW_PLACEMENT_MASK  (1ull << 24u)
#define XTK_SPLITVIEW_OPENLEN_MASK    (1ull << 25u)
#define XTK_SPLITVIEW_COMPACTLEN_MASK (1ull << 26u)

typedef struct XtkTitleBarProps {
	uint64_t       set; /* presence mask: bit i = props[i] */
	XtkChangeStamp stamp;
	float          w;
	float          h;
	float          grow;
	float          shrink;
	uint32_t       self;
	float          ml;
	float          mt;
	float          mr;
	float          mb;
	char const    *tip;
	uint32_t       tip_len;      /* 0 => strlen(tip) when tip != NULL */
	char const    *text;
	uint32_t       text_len;     /* 0 => strlen(text) when text != NULL */
	char const    *subtitle;
	uint32_t       subtitle_len; /* 0 => strlen(subtitle) when subtitle != NULL */
	char const    *icon;
	uint32_t       icon_len;     /* 0 => strlen(icon) when icon != NULL */
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
	uint64_t       set; /* presence mask: bit i = props[i] */
	XtkChangeStamp stamp;
	float          w;
	float          h;
	float          grow;
	float          shrink;
	uint32_t       self;
	float          ml;
	float          mt;
	float          mr;
	float          mb;
	char const    *tip;
	uint32_t       tip_len; /* 0 => strlen(tip) when tip != NULL */
	double         value;
	double         max;
	char const    *text;
	uint32_t       text_len; /* 0 => strlen(text) when text != NULL */
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
	uint64_t       set; /* presence mask: bit i = props[i] */
	XtkChangeStamp stamp;
	float          w;
	float          h;
	float          grow;
	uint32_t       self;
	float          ml;
	float          mt;
	float          mr;
	float          mb;
	char const    *text;
	uint32_t       text_len; /* 0 => strlen(text) when text != NULL */
	char const    *tip;
	uint32_t       tip_len;  /* 0 => strlen(tip) when tip != NULL */
	bool           enabled;
	char const    *url;
	uint32_t       url_len; /* 0 => strlen(url) when url != NULL */
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

XtkLocalId xtk_container_create(XtkTxn *txn, XtkNodeRef parent, XtkContainerProps const *props);
XtkLocalId xtk_text_create(XtkTxn *txn, XtkNodeRef parent, XtkTextProps const *props);
XtkLocalId xtk_button_create(XtkTxn *txn, XtkNodeRef parent, XtkButtonProps const *props);
XtkLocalId xtk_toggle_create(XtkTxn *txn, XtkNodeRef parent, XtkToggleProps const *props);
XtkLocalId xtk_checkbox_create(XtkTxn *txn, XtkNodeRef parent, XtkToggleProps const *props);
XtkLocalId xtk_radio_create(XtkTxn *txn, XtkNodeRef parent, XtkToggleProps const *props);
XtkLocalId xtk_switch_create(XtkTxn *txn, XtkNodeRef parent, XtkToggleProps const *props);
XtkLocalId xtk_slider_create(XtkTxn *txn, XtkNodeRef parent, XtkSliderProps const *props);
XtkLocalId xtk_textbox_create(XtkTxn *txn, XtkNodeRef parent, XtkInputProps const *props);
XtkLocalId xtk_scroll_create(XtkTxn *txn, XtkNodeRef parent, XtkContainerProps const *props);
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
XtkLocalId xtk_nav_create(XtkTxn *txn, XtkNodeRef parent, XtkSelectionProps const *props);
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
bool       xtk_container_setw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool       xtk_container_seth(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool       xtk_container_setgrow(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool       xtk_container_setshrink(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool       xtk_container_setself(XtkScene *scene, XtkCtrl control, uint32_t value, XtkChangeStamp change);
bool       xtk_container_setml(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool       xtk_container_setmt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool       xtk_container_setmr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool       xtk_container_setmb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_container_settip(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_container_setdir(XtkScene *scene, XtkCtrl control, uint32_t value, XtkChangeStamp change);
bool      xtk_container_setitems(XtkScene *scene, XtkCtrl control, uint32_t value, XtkChangeStamp change);
bool      xtk_container_setjustify(XtkScene *scene, XtkCtrl control, uint32_t value, XtkChangeStamp change);
bool      xtk_container_setgap(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_container_setpl(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_container_setpt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_container_setpr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_container_setpb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_container_setfill(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool      xtk_container_setfitw(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool      xtk_container_setfith(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool      xtk_container_setwrap(XtkScene *scene, XtkCtrl control, uint32_t value, XtkChangeStamp change);
bool      xtk_text_setw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_text_seth(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_text_setgrow(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_text_setself(XtkScene *scene, XtkCtrl control, uint32_t value, XtkChangeStamp change);
bool      xtk_text_setml(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_text_setmt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_text_setmr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_text_setmb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_text_settext(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_text_settip(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_text_setfontsize(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_text_setfontweight(XtkScene *scene, XtkCtrl control, uint32_t value, XtkChangeStamp change);
bool      xtk_text_settextalign(XtkScene *scene, XtkCtrl control, uint32_t value, XtkChangeStamp change);
bool      xtk_text_setfg(XtkScene *scene, XtkCtrl control, XtkColor value, XtkChangeStamp change);
bool      xtk_button_setw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_button_seth(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_button_setgrow(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_button_setself(XtkScene *scene, XtkCtrl control, uint32_t value, XtkChangeStamp change);
bool      xtk_button_setml(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_button_setmt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_button_setmr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_button_setmb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_button_settext(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_button_settip(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_button_setenabled(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool      xtk_button_seticon(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_button_setstyle(XtkScene *scene, XtkCtrl control, uint32_t value, XtkChangeStamp change);
XtkSubRef xtk_button_oninvoke(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg);
bool      xtk_toggle_setw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_toggle_seth(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_toggle_setgrow(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_toggle_setself(XtkScene *scene, XtkCtrl control, uint32_t value, XtkChangeStamp change);
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
bool      xtk_checkbox_setself(XtkScene *scene, XtkCtrl control, uint32_t value, XtkChangeStamp change);
bool      xtk_checkbox_setml(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_checkbox_setmt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_checkbox_setmr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_checkbox_setmb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_checkbox_settext(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_checkbox_settip(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_checkbox_setenabled(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool      xtk_checkbox_setchecked(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
XtkSubRef xtk_checkbox_onchange(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg);
bool      xtk_radio_setw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_radio_seth(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_radio_setgrow(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_radio_setself(XtkScene *scene, XtkCtrl control, uint32_t value, XtkChangeStamp change);
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
bool      xtk_switch_setself(XtkScene *scene, XtkCtrl control, uint32_t value, XtkChangeStamp change);
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
bool      xtk_slider_setself(XtkScene *scene, XtkCtrl control, uint32_t value, XtkChangeStamp change);
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
bool      xtk_slider_settickplace(XtkScene *scene, XtkCtrl control, uint32_t value, XtkChangeStamp change);
bool      xtk_slider_setsnapsto(XtkScene *scene, XtkCtrl control, uint32_t value, XtkChangeStamp change);
bool      xtk_slider_setsmallchange(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_slider_setlargechange(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
XtkSubRef xtk_slider_onchange(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg);
bool      xtk_textbox_setw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_textbox_seth(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_textbox_setgrow(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_textbox_setself(XtkScene *scene, XtkCtrl control, uint32_t value, XtkChangeStamp change);
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
XtkSubRef xtk_textbox_onchange(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg);
bool      xtk_scroll_setw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_scroll_seth(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_scroll_setgrow(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_scroll_setshrink(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_scroll_setself(XtkScene *scene, XtkCtrl control, uint32_t value, XtkChangeStamp change);
bool      xtk_scroll_setml(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_scroll_setmt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_scroll_setmr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_scroll_setmb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_scroll_settip(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_scroll_setdir(XtkScene *scene, XtkCtrl control, uint32_t value, XtkChangeStamp change);
bool      xtk_scroll_setitems(XtkScene *scene, XtkCtrl control, uint32_t value, XtkChangeStamp change);
bool      xtk_scroll_setjustify(XtkScene *scene, XtkCtrl control, uint32_t value, XtkChangeStamp change);
bool      xtk_scroll_setgap(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_scroll_setpl(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_scroll_setpt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_scroll_setpr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_scroll_setpb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_scroll_setfill(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool      xtk_scroll_setfitw(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool      xtk_scroll_setfith(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool      xtk_scroll_setwrap(XtkScene *scene, XtkCtrl control, uint32_t value, XtkChangeStamp change);
bool      xtk_image_setw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_image_seth(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_image_setgrow(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_image_setself(XtkScene *scene, XtkCtrl control, uint32_t value, XtkChangeStamp change);
bool      xtk_image_setml(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_image_setmt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_image_setmr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_image_setmb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_image_settip(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_image_setsrc(XtkScene *scene, XtkCtrl control, XtkResource value, XtkChangeStamp change);
bool      xtk_image_setfit(XtkScene *scene, XtkCtrl control, uint32_t value, XtkChangeStamp change);
bool      xtk_progress_setw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_progress_seth(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_progress_setgrow(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_progress_setself(XtkScene *scene, XtkCtrl control, uint32_t value, XtkChangeStamp change);
bool      xtk_progress_setml(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_progress_setmt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_progress_setmr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_progress_setmb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_progress_settip(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_progress_setmin(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_progress_setmax(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_progress_setvalue(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_progress_setindeterminate(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool      xtk_list_setw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_list_seth(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_list_setgrow(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_list_setself(XtkScene *scene, XtkCtrl control, uint32_t value, XtkChangeStamp change);
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
bool      xtk_list_setmode(XtkScene *scene, XtkCtrl control, uint32_t value, XtkChangeStamp change);
XtkSubRef xtk_list_onselect(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg);
XtkSubRef xtk_list_oninvoke(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg);
bool      xtk_tab_setw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_tab_seth(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_tab_setgrow(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_tab_setshrink(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_tab_setself(XtkScene *scene, XtkCtrl control, uint32_t value, XtkChangeStamp change);
bool      xtk_tab_setml(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_tab_setmt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_tab_setmr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_tab_setmb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_tab_settip(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_card_setw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_card_seth(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_card_setgrow(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_card_setshrink(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_card_setself(XtkScene *scene, XtkCtrl control, uint32_t value, XtkChangeStamp change);
bool      xtk_card_setml(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_card_setmt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_card_setmr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_card_setmb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_card_settip(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_card_setdir(XtkScene *scene, XtkCtrl control, uint32_t value, XtkChangeStamp change);
bool      xtk_card_setitems(XtkScene *scene, XtkCtrl control, uint32_t value, XtkChangeStamp change);
bool      xtk_card_setjustify(XtkScene *scene, XtkCtrl control, uint32_t value, XtkChangeStamp change);
bool      xtk_card_setgap(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_card_setpl(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_card_setpt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_card_setpr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_card_setpb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_card_setfill(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool      xtk_card_setfitw(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool      xtk_card_setfith(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool      xtk_card_setwrap(XtkScene *scene, XtkCtrl control, uint32_t value, XtkChangeStamp change);
bool      xtk_divider_setw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_divider_seth(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_divider_setgrow(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_divider_setshrink(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_divider_setself(XtkScene *scene, XtkCtrl control, uint32_t value, XtkChangeStamp change);
bool      xtk_divider_setml(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_divider_setmt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_divider_setmr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_divider_setmb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_divider_settip(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_canvas_setw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_canvas_seth(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_canvas_setgrow(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_canvas_setshrink(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_canvas_setself(XtkScene *scene, XtkCtrl control, uint32_t value, XtkChangeStamp change);
bool      xtk_canvas_setml(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_canvas_setmt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_canvas_setmr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_canvas_setmb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_canvas_settip(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_password_setw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_password_seth(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_password_setgrow(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_password_setself(XtkScene *scene, XtkCtrl control, uint32_t value, XtkChangeStamp change);
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
bool      xtk_number_setself(XtkScene *scene, XtkCtrl control, uint32_t value, XtkChangeStamp change);
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
bool      xtk_link_setself(XtkScene *scene, XtkCtrl control, uint32_t value, XtkChangeStamp change);
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
bool      xtk_repeat_setself(XtkScene *scene, XtkCtrl control, uint32_t value, XtkChangeStamp change);
bool      xtk_repeat_setml(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_repeat_setmt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_repeat_setmr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_repeat_setmb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_repeat_settext(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_repeat_settip(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_repeat_setenabled(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool      xtk_repeat_seticon(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_repeat_setstyle(XtkScene *scene, XtkCtrl control, uint32_t value, XtkChangeStamp change);
XtkSubRef xtk_repeat_oninvoke(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg);
bool      xtk_progressring_setw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_progressring_seth(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_progressring_setgrow(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_progressring_setself(XtkScene *scene, XtkCtrl control, uint32_t value, XtkChangeStamp change);
bool      xtk_progressring_setml(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_progressring_setmt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_progressring_setmr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_progressring_setmb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_progressring_settip(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_progressring_setmin(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_progressring_setmax(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_progressring_setvalue(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_progressring_setindeterminate(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_badge_setw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_badge_seth(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_badge_setgrow(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_badge_setshrink(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_badge_setself(XtkScene *scene, XtkCtrl control, uint32_t value, XtkChangeStamp change);
bool xtk_badge_setml(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_badge_setmt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_badge_setmr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_badge_setmb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_badge_settip(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_badge_setbadgemode(XtkScene *scene, XtkCtrl control, uint32_t value, XtkChangeStamp change);
bool xtk_badge_setvalue(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_badge_seticon(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_tooltip_setw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_tooltip_seth(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_tooltip_setgrow(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_tooltip_setself(XtkScene *scene, XtkCtrl control, uint32_t value, XtkChangeStamp change);
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
bool xtk_flyout_setself(XtkScene *scene, XtkCtrl control, uint32_t value, XtkChangeStamp change);
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
bool xtk_menufly_setself(XtkScene *scene, XtkCtrl control, uint32_t value, XtkChangeStamp change);
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
bool xtk_dropdown_setself(XtkScene *scene, XtkCtrl control, uint32_t value, XtkChangeStamp change);
bool xtk_dropdown_setml(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_dropdown_setmt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_dropdown_setmr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_dropdown_setmb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_dropdown_settext(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_dropdown_settip(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_dropdown_setenabled(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_dropdown_seticon(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_dropdown_setstyle(XtkScene *scene, XtkCtrl control, uint32_t value, XtkChangeStamp change);
XtkSubRef xtk_dropdown_oninvoke(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg);
bool      xtk_split_setw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_split_seth(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_split_setgrow(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_split_setself(XtkScene *scene, XtkCtrl control, uint32_t value, XtkChangeStamp change);
bool      xtk_split_setml(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_split_setmt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_split_setmr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_split_setmb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_split_settext(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_split_settip(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_split_setenabled(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool      xtk_split_seticon(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_split_setstyle(XtkScene *scene, XtkCtrl control, uint32_t value, XtkChangeStamp change);
XtkSubRef xtk_split_oninvoke(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg);
bool      xtk_combo_setw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_combo_seth(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_combo_setgrow(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_combo_setself(XtkScene *scene, XtkCtrl control, uint32_t value, XtkChangeStamp change);
bool      xtk_combo_setml(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_combo_setmt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_combo_setmr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_combo_setmb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_combo_settip(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_combo_setenabled(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_combo_setplaceholder(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_combo_setsel(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_combo_setnitem(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
XtkSubRef xtk_combo_onselect(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg);
XtkSubRef xtk_combo_oninvoke(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg);
bool      xtk_expander_setw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_expander_seth(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_expander_setgrow(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_expander_setself(XtkScene *scene, XtkCtrl control, uint32_t value, XtkChangeStamp change);
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
bool      xtk_exphead_setself(XtkScene *scene, XtkCtrl control, uint32_t value, XtkChangeStamp change);
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
bool      xtk_expbody_setself(XtkScene *scene, XtkCtrl control, uint32_t value, XtkChangeStamp change);
bool      xtk_expbody_setml(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_expbody_setmt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_expbody_setmr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_expbody_setmb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_expbody_settip(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_expbody_setdir(XtkScene *scene, XtkCtrl control, uint32_t value, XtkChangeStamp change);
bool      xtk_expbody_setitems(XtkScene *scene, XtkCtrl control, uint32_t value, XtkChangeStamp change);
bool      xtk_expbody_setjustify(XtkScene *scene, XtkCtrl control, uint32_t value, XtkChangeStamp change);
bool      xtk_expbody_setgap(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_expbody_setpl(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_expbody_setpt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_expbody_setpr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_expbody_setpb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_expbody_setfill(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool      xtk_expbody_setfitw(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool      xtk_expbody_setfith(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool      xtk_expbody_setwrap(XtkScene *scene, XtkCtrl control, uint32_t value, XtkChangeStamp change);
bool      xtk_infobar_setw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_infobar_seth(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_infobar_setgrow(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_infobar_setself(XtkScene *scene, XtkCtrl control, uint32_t value, XtkChangeStamp change);
bool      xtk_infobar_setml(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_infobar_setmt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_infobar_setmr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_infobar_setmb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_infobar_settext(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_infobar_setmessage(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_infobar_settip(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_infobar_setseverity(XtkScene *scene, XtkCtrl control, uint32_t value, XtkChangeStamp change);
bool xtk_infobar_setclosable(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
XtkSubRef xtk_infobar_onclose(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg);
bool      xtk_dialog_setw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_dialog_seth(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_dialog_setgrow(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_dialog_setshrink(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_dialog_setself(XtkScene *scene, XtkCtrl control, uint32_t value, XtkChangeStamp change);
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
bool      xtk_dialogbody_setself(XtkScene *scene, XtkCtrl control, uint32_t value, XtkChangeStamp change);
bool      xtk_dialogbody_setml(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_dialogbody_setmt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_dialogbody_setmr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_dialogbody_setmb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_dialogbody_settip(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_dialogbody_setdir(XtkScene *scene, XtkCtrl control, uint32_t value, XtkChangeStamp change);
bool xtk_dialogbody_setitems(XtkScene *scene, XtkCtrl control, uint32_t value, XtkChangeStamp change);
bool xtk_dialogbody_setjustify(XtkScene *scene, XtkCtrl control, uint32_t value, XtkChangeStamp change);
bool xtk_dialogbody_setgap(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_dialogbody_setpl(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_dialogbody_setpt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_dialogbody_setpr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_dialogbody_setpb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_dialogbody_setfill(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_dialogbody_setfitw(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_dialogbody_setfith(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_dialogbody_setwrap(XtkScene *scene, XtkCtrl control, uint32_t value, XtkChangeStamp change);
bool xtk_menubar_setw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_menubar_seth(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_menubar_setgrow(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_menubar_setshrink(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_menubar_setself(XtkScene *scene, XtkCtrl control, uint32_t value, XtkChangeStamp change);
bool xtk_menubar_setml(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_menubar_setmt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_menubar_setmr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_menubar_setmb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_menubar_settip(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_menuitem_setw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_menuitem_seth(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_menuitem_setgrow(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_menuitem_setself(XtkScene *scene, XtkCtrl control, uint32_t value, XtkChangeStamp change);
bool xtk_menuitem_setml(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_menuitem_setmt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_menuitem_setmr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_menuitem_setmb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_menuitem_settext(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_menuitem_settip(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_menuitem_seticon(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_menuitem_setenabled(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_menuitem_setselected(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_menuitem_setexpanded(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
XtkSubRef xtk_menuitem_oninvoke(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg);
bool      xtk_nav_setw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_nav_seth(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_nav_setgrow(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_nav_setself(XtkScene *scene, XtkCtrl control, uint32_t value, XtkChangeStamp change);
bool      xtk_nav_setml(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_nav_setmt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_nav_setmr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_nav_setmb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_nav_settip(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_nav_setenabled(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool      xtk_nav_setsel(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool      xtk_nav_setnitem(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
XtkSubRef xtk_nav_onselect(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg);
XtkSubRef xtk_nav_oninvoke(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg);
bool      xtk_navitem_setw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_navitem_seth(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_navitem_setgrow(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_navitem_setself(XtkScene *scene, XtkCtrl control, uint32_t value, XtkChangeStamp change);
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
bool      xtk_tabs_setself(XtkScene *scene, XtkCtrl control, uint32_t value, XtkChangeStamp change);
bool      xtk_tabs_setml(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_tabs_setmt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_tabs_setmr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_tabs_setmb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_tabs_settip(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_tabs_setenabled(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool      xtk_tabs_setsel(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool      xtk_tabs_setnitem(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
XtkSubRef xtk_tabs_onselect(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg);
XtkSubRef xtk_tabs_oninvoke(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg);
bool      xtk_tabitem_setw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_tabitem_seth(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_tabitem_setgrow(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_tabitem_setself(XtkScene *scene, XtkCtrl control, uint32_t value, XtkChangeStamp change);
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
bool      xtk_listitem_setself(XtkScene *scene, XtkCtrl control, uint32_t value, XtkChangeStamp change);
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
bool      xtk_listbox_setself(XtkScene *scene, XtkCtrl control, uint32_t value, XtkChangeStamp change);
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
bool      xtk_listbox_setmode(XtkScene *scene, XtkCtrl control, uint32_t value, XtkChangeStamp change);
XtkSubRef xtk_listbox_onselect(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg);
XtkSubRef xtk_listbox_oninvoke(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg);
bool      xtk_gridview_setw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_gridview_seth(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_gridview_setgrow(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_gridview_setself(XtkScene *scene, XtkCtrl control, uint32_t value, XtkChangeStamp change);
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
bool      xtk_gridview_setmode(XtkScene *scene, XtkCtrl control, uint32_t value, XtkChangeStamp change);
XtkSubRef xtk_gridview_onselect(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg);
XtkSubRef xtk_gridview_oninvoke(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg);
bool      xtk_repeater_setw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_repeater_seth(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_repeater_setgrow(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_repeater_setself(XtkScene *scene, XtkCtrl control, uint32_t value, XtkChangeStamp change);
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
bool      xtk_repeater_setmode(XtkScene *scene, XtkCtrl control, uint32_t value, XtkChangeStamp change);
bool      xtk_itemsview_setw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_itemsview_seth(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_itemsview_setgrow(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_itemsview_setself(XtkScene *scene, XtkCtrl control, uint32_t value, XtkChangeStamp change);
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
bool      xtk_itemsview_setmode(XtkScene *scene, XtkCtrl control, uint32_t value, XtkChangeStamp change);
bool      xtk_itemsview_setinvoked(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
XtkSubRef xtk_itemsview_onselect(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg);
XtkSubRef xtk_itemsview_oninvoke(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg);
bool      xtk_flip_setw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_flip_seth(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_flip_setgrow(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_flip_setself(XtkScene *scene, XtkCtrl control, uint32_t value, XtkChangeStamp change);
bool      xtk_flip_setml(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_flip_setmt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_flip_setmr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_flip_setmb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_flip_settip(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_flip_setsel(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool      xtk_flip_setdir(XtkScene *scene, XtkCtrl control, uint32_t value, XtkChangeStamp change);
XtkSubRef xtk_flip_onselect(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg);
bool      xtk_pips_setw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_pips_seth(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_pips_setgrow(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_pips_setself(XtkScene *scene, XtkCtrl control, uint32_t value, XtkChangeStamp change);
bool      xtk_pips_setml(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_pips_setmt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_pips_setmr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_pips_setmb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_pips_settip(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_pips_setsel(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool      xtk_pips_setnitem(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool      xtk_pips_setdir(XtkScene *scene, XtkCtrl control, uint32_t value, XtkChangeStamp change);
bool      xtk_pips_setmaxvisible(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool      xtk_pips_setnav(XtkScene *scene, XtkCtrl control, uint32_t value, XtkChangeStamp change);
XtkSubRef xtk_pips_onselect(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg);
bool      xtk_suggest_setw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_suggest_seth(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_suggest_setgrow(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_suggest_setself(XtkScene *scene, XtkCtrl control, uint32_t value, XtkChangeStamp change);
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
bool      xtk_togglesplit_setself(XtkScene *scene, XtkCtrl control, uint32_t value, XtkChangeStamp change);
bool      xtk_togglesplit_setml(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_togglesplit_setmt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_togglesplit_setmr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_togglesplit_setmb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_togglesplit_settext(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_togglesplit_settip(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_togglesplit_setenabled(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_togglesplit_setchecked(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
XtkSubRef xtk_togglesplit_onchange(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg);
bool      xtk_radiogroup_setw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_radiogroup_seth(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_radiogroup_setgrow(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_radiogroup_setself(XtkScene *scene, XtkCtrl control, uint32_t value, XtkChangeStamp change);
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
bool      xtk_rating_setself(XtkScene *scene, XtkCtrl control, uint32_t value, XtkChangeStamp change);
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
bool      xtk_selector_setself(XtkScene *scene, XtkCtrl control, uint32_t value, XtkChangeStamp change);
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
bool      xtk_selectoritem_setself(XtkScene *scene, XtkCtrl control, uint32_t value, XtkChangeStamp change);
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
bool      xtk_breadcrumb_setself(XtkScene *scene, XtkCtrl control, uint32_t value, XtkChangeStamp change);
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
bool      xtk_crumb_setself(XtkScene *scene, XtkCtrl control, uint32_t value, XtkChangeStamp change);
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
bool      xtk_teachtip_setself(XtkScene *scene, XtkCtrl control, uint32_t value, XtkChangeStamp change);
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
bool xtk_teachtip_setplacement(XtkScene *scene, XtkCtrl control, uint32_t value, XtkChangeStamp change);
bool xtk_teachtip_setuntargeted(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_teachtip_setlightdismiss(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_teachtip_settail(XtkScene *scene, XtkCtrl control, uint32_t value, XtkChangeStamp change);
bool xtk_teachtip_setplacementmargin(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_teachtip_setopen(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
XtkSubRef xtk_teachtip_onclose(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg);
XtkSubRef xtk_teachtip_oninvoke(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg);
bool      xtk_tree_setw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_tree_seth(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_tree_setgrow(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_tree_setself(XtkScene *scene, XtkCtrl control, uint32_t value, XtkChangeStamp change);
bool      xtk_tree_setml(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_tree_setmt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_tree_setmr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_tree_setmb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_tree_settip(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_tree_setenabled(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool      xtk_tree_setsel(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool      xtk_tree_setnitem(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool      xtk_tree_setitemh(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
XtkSubRef xtk_tree_onselect(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg);
XtkSubRef xtk_tree_oninvoke(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg);
bool      xtk_treeitem_setw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_treeitem_seth(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_treeitem_setgrow(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_treeitem_setself(XtkScene *scene, XtkCtrl control, uint32_t value, XtkChangeStamp change);
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
bool      xtk_refresh_setself(XtkScene *scene, XtkCtrl control, uint32_t value, XtkChangeStamp change);
bool      xtk_refresh_setml(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_refresh_setmt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_refresh_setmr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_refresh_setmb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_refresh_settip(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_refresh_setdirection(XtkScene *scene, XtkCtrl control, uint32_t value, XtkChangeStamp change);
bool      xtk_refresh_setvisualizer(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_refresh_setthreshold(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_refresh_setrefreshing(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
XtkSubRef xtk_refresh_onrefresh(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg);
bool      xtk_avatar_setw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_avatar_seth(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_avatar_setgrow(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_avatar_setshrink(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_avatar_setself(XtkScene *scene, XtkCtrl control, uint32_t value, XtkChangeStamp change);
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
bool xtk_pager_setself(XtkScene *scene, XtkCtrl control, uint32_t value, XtkChangeStamp change);
bool xtk_pager_setml(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_pager_setmt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_pager_setmr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_pager_setmb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_pager_settip(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_pager_setsel(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_pager_setnitem(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_pager_setdisplay(XtkScene *scene, XtkCtrl control, uint32_t value, XtkChangeStamp change);
bool xtk_pager_setfirst(XtkScene *scene, XtkCtrl control, uint32_t value, XtkChangeStamp change);
bool xtk_pager_setprev(XtkScene *scene, XtkCtrl control, uint32_t value, XtkChangeStamp change);
bool xtk_pager_setnext(XtkScene *scene, XtkCtrl control, uint32_t value, XtkChangeStamp change);
bool xtk_pager_setlast(XtkScene *scene, XtkCtrl control, uint32_t value, XtkChangeStamp change);
bool xtk_pager_setprefix(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_pager_setsuffix(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
XtkSubRef xtk_pager_onselect(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg);
XtkSubRef xtk_pager_oninvoke(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg);
bool      xtk_splitview_setw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_splitview_seth(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_splitview_setgrow(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_splitview_setshrink(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_splitview_setself(XtkScene *scene, XtkCtrl control, uint32_t value, XtkChangeStamp change);
bool      xtk_splitview_setml(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_splitview_setmt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_splitview_setmr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_splitview_setmb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_splitview_settip(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_splitview_setdir(XtkScene *scene, XtkCtrl control, uint32_t value, XtkChangeStamp change);
bool      xtk_splitview_setitems(XtkScene *scene, XtkCtrl control, uint32_t value, XtkChangeStamp change);
bool      xtk_splitview_setjustify(XtkScene *scene, XtkCtrl control, uint32_t value, XtkChangeStamp change);
bool      xtk_splitview_setgap(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_splitview_setpl(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_splitview_setpt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_splitview_setpr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_splitview_setpb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_splitview_setfill(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool      xtk_splitview_setfitw(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool      xtk_splitview_setfith(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool      xtk_splitview_setwrap(XtkScene *scene, XtkCtrl control, uint32_t value, XtkChangeStamp change);
bool      xtk_splitview_setopen(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool      xtk_splitview_setdisplay(XtkScene *scene, XtkCtrl control, uint32_t value, XtkChangeStamp change);
bool      xtk_splitview_setplacement(XtkScene *scene, XtkCtrl control, uint32_t value, XtkChangeStamp change);
bool      xtk_splitview_setopenlen(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_splitview_setcompactlen(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_splitpane_setw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_splitpane_seth(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_splitpane_setgrow(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_splitpane_setshrink(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_splitpane_setself(XtkScene *scene, XtkCtrl control, uint32_t value, XtkChangeStamp change);
bool      xtk_splitpane_setml(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_splitpane_setmt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_splitpane_setmr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_splitpane_setmb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_splitpane_settip(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_splitpane_setdir(XtkScene *scene, XtkCtrl control, uint32_t value, XtkChangeStamp change);
bool      xtk_splitpane_setitems(XtkScene *scene, XtkCtrl control, uint32_t value, XtkChangeStamp change);
bool      xtk_splitpane_setjustify(XtkScene *scene, XtkCtrl control, uint32_t value, XtkChangeStamp change);
bool      xtk_splitpane_setgap(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_splitpane_setpl(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_splitpane_setpt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_splitpane_setpr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_splitpane_setpb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_splitpane_setfill(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool      xtk_splitpane_setfitw(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool      xtk_splitpane_setfith(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool      xtk_splitpane_setwrap(XtkScene *scene, XtkCtrl control, uint32_t value, XtkChangeStamp change);
bool      xtk_splitbody_setw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_splitbody_seth(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_splitbody_setgrow(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_splitbody_setshrink(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_splitbody_setself(XtkScene *scene, XtkCtrl control, uint32_t value, XtkChangeStamp change);
bool      xtk_splitbody_setml(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_splitbody_setmt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_splitbody_setmr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_splitbody_setmb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_splitbody_settip(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_splitbody_setdir(XtkScene *scene, XtkCtrl control, uint32_t value, XtkChangeStamp change);
bool      xtk_splitbody_setitems(XtkScene *scene, XtkCtrl control, uint32_t value, XtkChangeStamp change);
bool      xtk_splitbody_setjustify(XtkScene *scene, XtkCtrl control, uint32_t value, XtkChangeStamp change);
bool      xtk_splitbody_setgap(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_splitbody_setpl(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_splitbody_setpt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_splitbody_setpr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_splitbody_setpb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_splitbody_setfill(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool      xtk_splitbody_setfitw(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool      xtk_splitbody_setfith(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool      xtk_splitbody_setwrap(XtkScene *scene, XtkCtrl control, uint32_t value, XtkChangeStamp change);
bool      xtk_titlebar_setw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_titlebar_seth(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_titlebar_setgrow(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_titlebar_setshrink(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_titlebar_setself(XtkScene *scene, XtkCtrl control, uint32_t value, XtkChangeStamp change);
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

#endif
