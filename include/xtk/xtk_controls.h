#ifndef XTK_CONTROLS_H
#define XTK_CONTROLS_H

#include "xtk_catalog.h"
#include "xtk_scene.h"

#include <stdint.h>

typedef struct XtkLayoutProps {
	uint64_t        set;
	XtkChangeStamp  stamp;
	float           w;
	float           h;
	float           grow;
	float           shrink;
	XentFlexAlign   self;
	float           ml;
	float           mt;
	float           mr;
	float           mb;
	char const     *tip;
	uint32_t        tip_len;
	char const     *aname;
	uint32_t        aname_len;
	char const     *aid;
	uint32_t        aid_len;
	char const     *ahelp;
	uint32_t        ahelp_len;
	char const     *adesc;
	uint32_t        adesc_len;
	char const     *astatus;
	uint32_t        astatus_len;
	char const     *aitem;
	uint32_t        aitem_len;
	char const     *actype;
	uint32_t        actype_len;
	char const     *aaccel;
	uint32_t        aaccel_len;
	char const     *akey;
	uint32_t        akey_len;
	XtkLandmark     alandmark;
	char const     *alandname;
	uint32_t        alandname_len;
	XtkLiveSetting  alive;
	XtkHeadingLevel aheading;
	XtkAccessView   aview;
	bool            arequired;
	bool            avalid;
	bool            aperipheral;
	bool            adialog;
	int32_t         apos;
	int32_t         asize;
	int32_t         alevel;
	int32_t         aculture;
	char const     *alabel;
	uint32_t        alabel_len;
	char const     *adescribed;
	uint32_t        adescribed_len;
	char const     *aflowsto;
	uint32_t        aflowsto_len;
	char const     *aflowsfrom;
	uint32_t        aflowsfrom_len;
	char const     *acontrols;
	uint32_t        acontrols_len;
} XtkLayoutProps;

#define XTK_LAYOUT_W_MASK           (1ull << 0u)
#define XTK_LAYOUT_H_MASK           (1ull << 1u)
#define XTK_LAYOUT_GROW_MASK        (1ull << 2u)
#define XTK_LAYOUT_SHRINK_MASK      (1ull << 3u)
#define XTK_LAYOUT_SELF_MASK        (1ull << 4u)
#define XTK_LAYOUT_ML_MASK          (1ull << 5u)
#define XTK_LAYOUT_MT_MASK          (1ull << 6u)
#define XTK_LAYOUT_MR_MASK          (1ull << 7u)
#define XTK_LAYOUT_MB_MASK          (1ull << 8u)
#define XTK_LAYOUT_TIP_MASK         (1ull << 9u)
#define XTK_LAYOUT_ANAME_MASK       (1ull << 10u)
#define XTK_LAYOUT_AID_MASK         (1ull << 11u)
#define XTK_LAYOUT_AHELP_MASK       (1ull << 12u)
#define XTK_LAYOUT_ADESC_MASK       (1ull << 13u)
#define XTK_LAYOUT_ASTATUS_MASK     (1ull << 14u)
#define XTK_LAYOUT_AITEM_MASK       (1ull << 15u)
#define XTK_LAYOUT_ACTYPE_MASK      (1ull << 16u)
#define XTK_LAYOUT_AACCEL_MASK      (1ull << 17u)
#define XTK_LAYOUT_AKEY_MASK        (1ull << 18u)
#define XTK_LAYOUT_ALANDMARK_MASK   (1ull << 19u)
#define XTK_LAYOUT_ALANDNAME_MASK   (1ull << 20u)
#define XTK_LAYOUT_ALIVE_MASK       (1ull << 21u)
#define XTK_LAYOUT_AHEADING_MASK    (1ull << 22u)
#define XTK_LAYOUT_AVIEW_MASK       (1ull << 23u)
#define XTK_LAYOUT_AREQUIRED_MASK   (1ull << 24u)
#define XTK_LAYOUT_AVALID_MASK      (1ull << 25u)
#define XTK_LAYOUT_APERIPHERAL_MASK (1ull << 26u)
#define XTK_LAYOUT_ADIALOG_MASK     (1ull << 27u)
#define XTK_LAYOUT_APOS_MASK        (1ull << 28u)
#define XTK_LAYOUT_ASIZE_MASK       (1ull << 29u)
#define XTK_LAYOUT_ALEVEL_MASK      (1ull << 30u)
#define XTK_LAYOUT_ACULTURE_MASK    (1ull << 31u)
#define XTK_LAYOUT_ALABEL_MASK      (1ull << 32u)
#define XTK_LAYOUT_ADESCRIBED_MASK  (1ull << 33u)
#define XTK_LAYOUT_AFLOWSTO_MASK    (1ull << 34u)
#define XTK_LAYOUT_AFLOWSFROM_MASK  (1ull << 35u)
#define XTK_LAYOUT_ACONTROLS_MASK   (1ull << 36u)

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
	char const       *aname;
	uint32_t          aname_len;
	char const       *aid;
	uint32_t          aid_len;
	char const       *ahelp;
	uint32_t          ahelp_len;
	char const       *adesc;
	uint32_t          adesc_len;
	char const       *astatus;
	uint32_t          astatus_len;
	char const       *aitem;
	uint32_t          aitem_len;
	char const       *actype;
	uint32_t          actype_len;
	char const       *aaccel;
	uint32_t          aaccel_len;
	char const       *akey;
	uint32_t          akey_len;
	XtkLandmark       alandmark;
	char const       *alandname;
	uint32_t          alandname_len;
	XtkLiveSetting    alive;
	XtkHeadingLevel   aheading;
	XtkAccessView     aview;
	bool              arequired;
	bool              avalid;
	bool              aperipheral;
	bool              adialog;
	int32_t           apos;
	int32_t           asize;
	int32_t           alevel;
	int32_t           aculture;
	char const       *alabel;
	uint32_t          alabel_len;
	char const       *adescribed;
	uint32_t          adescribed_len;
	char const       *aflowsto;
	uint32_t          aflowsto_len;
	char const       *aflowsfrom;
	uint32_t          aflowsfrom_len;
	char const       *acontrols;
	uint32_t          acontrols_len;
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
	XentDirection     flow;
} XtkContainerProps;

#define XTK_CONTAINER_W_MASK           (1ull << 0u)
#define XTK_CONTAINER_H_MASK           (1ull << 1u)
#define XTK_CONTAINER_GROW_MASK        (1ull << 2u)
#define XTK_CONTAINER_SHRINK_MASK      (1ull << 3u)
#define XTK_CONTAINER_SELF_MASK        (1ull << 4u)
#define XTK_CONTAINER_ML_MASK          (1ull << 5u)
#define XTK_CONTAINER_MT_MASK          (1ull << 6u)
#define XTK_CONTAINER_MR_MASK          (1ull << 7u)
#define XTK_CONTAINER_MB_MASK          (1ull << 8u)
#define XTK_CONTAINER_TIP_MASK         (1ull << 9u)
#define XTK_CONTAINER_ANAME_MASK       (1ull << 10u)
#define XTK_CONTAINER_AID_MASK         (1ull << 11u)
#define XTK_CONTAINER_AHELP_MASK       (1ull << 12u)
#define XTK_CONTAINER_ADESC_MASK       (1ull << 13u)
#define XTK_CONTAINER_ASTATUS_MASK     (1ull << 14u)
#define XTK_CONTAINER_AITEM_MASK       (1ull << 15u)
#define XTK_CONTAINER_ACTYPE_MASK      (1ull << 16u)
#define XTK_CONTAINER_AACCEL_MASK      (1ull << 17u)
#define XTK_CONTAINER_AKEY_MASK        (1ull << 18u)
#define XTK_CONTAINER_ALANDMARK_MASK   (1ull << 19u)
#define XTK_CONTAINER_ALANDNAME_MASK   (1ull << 20u)
#define XTK_CONTAINER_ALIVE_MASK       (1ull << 21u)
#define XTK_CONTAINER_AHEADING_MASK    (1ull << 22u)
#define XTK_CONTAINER_AVIEW_MASK       (1ull << 23u)
#define XTK_CONTAINER_AREQUIRED_MASK   (1ull << 24u)
#define XTK_CONTAINER_AVALID_MASK      (1ull << 25u)
#define XTK_CONTAINER_APERIPHERAL_MASK (1ull << 26u)
#define XTK_CONTAINER_ADIALOG_MASK     (1ull << 27u)
#define XTK_CONTAINER_APOS_MASK        (1ull << 28u)
#define XTK_CONTAINER_ASIZE_MASK       (1ull << 29u)
#define XTK_CONTAINER_ALEVEL_MASK      (1ull << 30u)
#define XTK_CONTAINER_ACULTURE_MASK    (1ull << 31u)
#define XTK_CONTAINER_ALABEL_MASK      (1ull << 32u)
#define XTK_CONTAINER_ADESCRIBED_MASK  (1ull << 33u)
#define XTK_CONTAINER_AFLOWSTO_MASK    (1ull << 34u)
#define XTK_CONTAINER_AFLOWSFROM_MASK  (1ull << 35u)
#define XTK_CONTAINER_ACONTROLS_MASK   (1ull << 36u)
#define XTK_CONTAINER_DIR_MASK         (1ull << 37u)
#define XTK_CONTAINER_ITEMS_MASK       (1ull << 38u)
#define XTK_CONTAINER_JUSTIFY_MASK     (1ull << 39u)
#define XTK_CONTAINER_GAP_MASK         (1ull << 40u)
#define XTK_CONTAINER_PL_MASK          (1ull << 41u)
#define XTK_CONTAINER_PT_MASK          (1ull << 42u)
#define XTK_CONTAINER_PR_MASK          (1ull << 43u)
#define XTK_CONTAINER_PB_MASK          (1ull << 44u)
#define XTK_CONTAINER_FILL_MASK        (1ull << 45u)
#define XTK_CONTAINER_FITW_MASK        (1ull << 46u)
#define XTK_CONTAINER_FITH_MASK        (1ull << 47u)
#define XTK_CONTAINER_WRAP_MASK        (1ull << 48u)
#define XTK_CONTAINER_DROP_MASK        (1ull << 49u)
#define XTK_CONTAINER_DRAGTEXT_MASK    (1ull << 50u)
#define XTK_CONTAINER_DRAGFILES_MASK   (1ull << 51u)
#define XTK_CONTAINER_FLOW_MASK        (1ull << 52u)

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
	char const       *aname;
	uint32_t          aname_len;
	char const       *aid;
	uint32_t          aid_len;
	char const       *ahelp;
	uint32_t          ahelp_len;
	char const       *adesc;
	uint32_t          adesc_len;
	char const       *astatus;
	uint32_t          astatus_len;
	char const       *aitem;
	uint32_t          aitem_len;
	char const       *actype;
	uint32_t          actype_len;
	char const       *aaccel;
	uint32_t          aaccel_len;
	char const       *akey;
	uint32_t          akey_len;
	XtkLandmark       alandmark;
	char const       *alandname;
	uint32_t          alandname_len;
	XtkLiveSetting    alive;
	XtkHeadingLevel   aheading;
	XtkAccessView     aview;
	bool              arequired;
	bool              avalid;
	bool              aperipheral;
	bool              adialog;
	int32_t           apos;
	int32_t           asize;
	int32_t           alevel;
	int32_t           aculture;
	char const       *alabel;
	uint32_t          alabel_len;
	char const       *adescribed;
	uint32_t          adescribed_len;
	char const       *aflowsto;
	uint32_t          aflowsto_len;
	char const       *aflowsfrom;
	uint32_t          aflowsfrom_len;
	char const       *acontrols;
	uint32_t          acontrols_len;
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

#define XTK_SCROLL_W_MASK           (1ull << 0u)
#define XTK_SCROLL_H_MASK           (1ull << 1u)
#define XTK_SCROLL_GROW_MASK        (1ull << 2u)
#define XTK_SCROLL_SHRINK_MASK      (1ull << 3u)
#define XTK_SCROLL_SELF_MASK        (1ull << 4u)
#define XTK_SCROLL_ML_MASK          (1ull << 5u)
#define XTK_SCROLL_MT_MASK          (1ull << 6u)
#define XTK_SCROLL_MR_MASK          (1ull << 7u)
#define XTK_SCROLL_MB_MASK          (1ull << 8u)
#define XTK_SCROLL_TIP_MASK         (1ull << 9u)
#define XTK_SCROLL_ANAME_MASK       (1ull << 10u)
#define XTK_SCROLL_AID_MASK         (1ull << 11u)
#define XTK_SCROLL_AHELP_MASK       (1ull << 12u)
#define XTK_SCROLL_ADESC_MASK       (1ull << 13u)
#define XTK_SCROLL_ASTATUS_MASK     (1ull << 14u)
#define XTK_SCROLL_AITEM_MASK       (1ull << 15u)
#define XTK_SCROLL_ACTYPE_MASK      (1ull << 16u)
#define XTK_SCROLL_AACCEL_MASK      (1ull << 17u)
#define XTK_SCROLL_AKEY_MASK        (1ull << 18u)
#define XTK_SCROLL_ALANDMARK_MASK   (1ull << 19u)
#define XTK_SCROLL_ALANDNAME_MASK   (1ull << 20u)
#define XTK_SCROLL_ALIVE_MASK       (1ull << 21u)
#define XTK_SCROLL_AHEADING_MASK    (1ull << 22u)
#define XTK_SCROLL_AVIEW_MASK       (1ull << 23u)
#define XTK_SCROLL_AREQUIRED_MASK   (1ull << 24u)
#define XTK_SCROLL_AVALID_MASK      (1ull << 25u)
#define XTK_SCROLL_APERIPHERAL_MASK (1ull << 26u)
#define XTK_SCROLL_ADIALOG_MASK     (1ull << 27u)
#define XTK_SCROLL_APOS_MASK        (1ull << 28u)
#define XTK_SCROLL_ASIZE_MASK       (1ull << 29u)
#define XTK_SCROLL_ALEVEL_MASK      (1ull << 30u)
#define XTK_SCROLL_ACULTURE_MASK    (1ull << 31u)
#define XTK_SCROLL_ALABEL_MASK      (1ull << 32u)
#define XTK_SCROLL_ADESCRIBED_MASK  (1ull << 33u)
#define XTK_SCROLL_AFLOWSTO_MASK    (1ull << 34u)
#define XTK_SCROLL_AFLOWSFROM_MASK  (1ull << 35u)
#define XTK_SCROLL_ACONTROLS_MASK   (1ull << 36u)
#define XTK_SCROLL_DIR_MASK         (1ull << 37u)
#define XTK_SCROLL_ITEMS_MASK       (1ull << 38u)
#define XTK_SCROLL_JUSTIFY_MASK     (1ull << 39u)
#define XTK_SCROLL_GAP_MASK         (1ull << 40u)
#define XTK_SCROLL_PL_MASK          (1ull << 41u)
#define XTK_SCROLL_PT_MASK          (1ull << 42u)
#define XTK_SCROLL_PR_MASK          (1ull << 43u)
#define XTK_SCROLL_PB_MASK          (1ull << 44u)
#define XTK_SCROLL_FILL_MASK        (1ull << 45u)
#define XTK_SCROLL_FITW_MASK        (1ull << 46u)
#define XTK_SCROLL_FITH_MASK        (1ull << 47u)
#define XTK_SCROLL_WRAP_MASK        (1ull << 48u)
#define XTK_SCROLL_X_MASK           (1ull << 49u)
#define XTK_SCROLL_Y_MASK           (1ull << 50u)

typedef struct XtkTextProps {
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
	char const     *text;
	uint32_t        text_len;
	char const     *tip;
	uint32_t        tip_len;
	char const     *aname;
	uint32_t        aname_len;
	char const     *aid;
	uint32_t        aid_len;
	char const     *ahelp;
	uint32_t        ahelp_len;
	char const     *adesc;
	uint32_t        adesc_len;
	char const     *astatus;
	uint32_t        astatus_len;
	char const     *aitem;
	uint32_t        aitem_len;
	char const     *actype;
	uint32_t        actype_len;
	char const     *aaccel;
	uint32_t        aaccel_len;
	char const     *akey;
	uint32_t        akey_len;
	XtkLandmark     alandmark;
	char const     *alandname;
	uint32_t        alandname_len;
	XtkLiveSetting  alive;
	XtkHeadingLevel aheading;
	XtkAccessView   aview;
	bool            arequired;
	bool            avalid;
	bool            aperipheral;
	bool            adialog;
	int32_t         apos;
	int32_t         asize;
	int32_t         alevel;
	int32_t         aculture;
	char const     *alabel;
	uint32_t        alabel_len;
	char const     *adescribed;
	uint32_t        adescribed_len;
	char const     *aflowsto;
	uint32_t        aflowsto_len;
	char const     *aflowsfrom;
	uint32_t        aflowsfrom_len;
	char const     *acontrols;
	uint32_t        acontrols_len;
	float           fontsize;
	XtkFontWeight   fontweight;
	XtkTextAlign    textalign;
	XtkColor        fg;
	int32_t         maxlines;
	XtkTextTrim     trim;
	bool            textwrap;
	bool            selectable;
} XtkTextProps;

#define XTK_TEXT_W_MASK           (1ull << 0u)
#define XTK_TEXT_H_MASK           (1ull << 1u)
#define XTK_TEXT_GROW_MASK        (1ull << 2u)
#define XTK_TEXT_SELF_MASK        (1ull << 3u)
#define XTK_TEXT_ML_MASK          (1ull << 4u)
#define XTK_TEXT_MT_MASK          (1ull << 5u)
#define XTK_TEXT_MR_MASK          (1ull << 6u)
#define XTK_TEXT_MB_MASK          (1ull << 7u)
#define XTK_TEXT_TEXT_MASK        (1ull << 8u)
#define XTK_TEXT_TIP_MASK         (1ull << 9u)
#define XTK_TEXT_ANAME_MASK       (1ull << 10u)
#define XTK_TEXT_AID_MASK         (1ull << 11u)
#define XTK_TEXT_AHELP_MASK       (1ull << 12u)
#define XTK_TEXT_ADESC_MASK       (1ull << 13u)
#define XTK_TEXT_ASTATUS_MASK     (1ull << 14u)
#define XTK_TEXT_AITEM_MASK       (1ull << 15u)
#define XTK_TEXT_ACTYPE_MASK      (1ull << 16u)
#define XTK_TEXT_AACCEL_MASK      (1ull << 17u)
#define XTK_TEXT_AKEY_MASK        (1ull << 18u)
#define XTK_TEXT_ALANDMARK_MASK   (1ull << 19u)
#define XTK_TEXT_ALANDNAME_MASK   (1ull << 20u)
#define XTK_TEXT_ALIVE_MASK       (1ull << 21u)
#define XTK_TEXT_AHEADING_MASK    (1ull << 22u)
#define XTK_TEXT_AVIEW_MASK       (1ull << 23u)
#define XTK_TEXT_AREQUIRED_MASK   (1ull << 24u)
#define XTK_TEXT_AVALID_MASK      (1ull << 25u)
#define XTK_TEXT_APERIPHERAL_MASK (1ull << 26u)
#define XTK_TEXT_ADIALOG_MASK     (1ull << 27u)
#define XTK_TEXT_APOS_MASK        (1ull << 28u)
#define XTK_TEXT_ASIZE_MASK       (1ull << 29u)
#define XTK_TEXT_ALEVEL_MASK      (1ull << 30u)
#define XTK_TEXT_ACULTURE_MASK    (1ull << 31u)
#define XTK_TEXT_ALABEL_MASK      (1ull << 32u)
#define XTK_TEXT_ADESCRIBED_MASK  (1ull << 33u)
#define XTK_TEXT_AFLOWSTO_MASK    (1ull << 34u)
#define XTK_TEXT_AFLOWSFROM_MASK  (1ull << 35u)
#define XTK_TEXT_ACONTROLS_MASK   (1ull << 36u)
#define XTK_TEXT_FONTSIZE_MASK    (1ull << 37u)
#define XTK_TEXT_FONTWEIGHT_MASK  (1ull << 38u)
#define XTK_TEXT_TEXTALIGN_MASK   (1ull << 39u)
#define XTK_TEXT_FG_MASK          (1ull << 40u)
#define XTK_TEXT_MAXLINES_MASK    (1ull << 41u)
#define XTK_TEXT_TRIM_MASK        (1ull << 42u)
#define XTK_TEXT_TEXTWRAP_MASK    (1ull << 43u)
#define XTK_TEXT_SELECTABLE_MASK  (1ull << 44u)

typedef struct XtkButtonProps {
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
	char const     *text;
	uint32_t        text_len;
	char const     *tip;
	uint32_t        tip_len;
	char const     *aname;
	uint32_t        aname_len;
	char const     *aid;
	uint32_t        aid_len;
	char const     *ahelp;
	uint32_t        ahelp_len;
	char const     *adesc;
	uint32_t        adesc_len;
	char const     *astatus;
	uint32_t        astatus_len;
	char const     *aitem;
	uint32_t        aitem_len;
	char const     *actype;
	uint32_t        actype_len;
	char const     *aaccel;
	uint32_t        aaccel_len;
	char const     *akey;
	uint32_t        akey_len;
	XtkLandmark     alandmark;
	char const     *alandname;
	uint32_t        alandname_len;
	XtkLiveSetting  alive;
	XtkHeadingLevel aheading;
	XtkAccessView   aview;
	bool            arequired;
	bool            avalid;
	bool            aperipheral;
	bool            adialog;
	int32_t         apos;
	int32_t         asize;
	int32_t         alevel;
	int32_t         aculture;
	char const     *alabel;
	uint32_t        alabel_len;
	char const     *adescribed;
	uint32_t        adescribed_len;
	char const     *aflowsto;
	uint32_t        aflowsto_len;
	char const     *aflowsfrom;
	uint32_t        aflowsfrom_len;
	char const     *acontrols;
	uint32_t        acontrols_len;
	bool            enabled;
	char const     *icon;
	uint32_t        icon_len;
	XtkButtonStyle  style;
} XtkButtonProps;

#define XTK_BUTTON_W_MASK           (1ull << 0u)
#define XTK_BUTTON_H_MASK           (1ull << 1u)
#define XTK_BUTTON_GROW_MASK        (1ull << 2u)
#define XTK_BUTTON_SELF_MASK        (1ull << 3u)
#define XTK_BUTTON_ML_MASK          (1ull << 4u)
#define XTK_BUTTON_MT_MASK          (1ull << 5u)
#define XTK_BUTTON_MR_MASK          (1ull << 6u)
#define XTK_BUTTON_MB_MASK          (1ull << 7u)
#define XTK_BUTTON_TEXT_MASK        (1ull << 8u)
#define XTK_BUTTON_TIP_MASK         (1ull << 9u)
#define XTK_BUTTON_ANAME_MASK       (1ull << 10u)
#define XTK_BUTTON_AID_MASK         (1ull << 11u)
#define XTK_BUTTON_AHELP_MASK       (1ull << 12u)
#define XTK_BUTTON_ADESC_MASK       (1ull << 13u)
#define XTK_BUTTON_ASTATUS_MASK     (1ull << 14u)
#define XTK_BUTTON_AITEM_MASK       (1ull << 15u)
#define XTK_BUTTON_ACTYPE_MASK      (1ull << 16u)
#define XTK_BUTTON_AACCEL_MASK      (1ull << 17u)
#define XTK_BUTTON_AKEY_MASK        (1ull << 18u)
#define XTK_BUTTON_ALANDMARK_MASK   (1ull << 19u)
#define XTK_BUTTON_ALANDNAME_MASK   (1ull << 20u)
#define XTK_BUTTON_ALIVE_MASK       (1ull << 21u)
#define XTK_BUTTON_AHEADING_MASK    (1ull << 22u)
#define XTK_BUTTON_AVIEW_MASK       (1ull << 23u)
#define XTK_BUTTON_AREQUIRED_MASK   (1ull << 24u)
#define XTK_BUTTON_AVALID_MASK      (1ull << 25u)
#define XTK_BUTTON_APERIPHERAL_MASK (1ull << 26u)
#define XTK_BUTTON_ADIALOG_MASK     (1ull << 27u)
#define XTK_BUTTON_APOS_MASK        (1ull << 28u)
#define XTK_BUTTON_ASIZE_MASK       (1ull << 29u)
#define XTK_BUTTON_ALEVEL_MASK      (1ull << 30u)
#define XTK_BUTTON_ACULTURE_MASK    (1ull << 31u)
#define XTK_BUTTON_ALABEL_MASK      (1ull << 32u)
#define XTK_BUTTON_ADESCRIBED_MASK  (1ull << 33u)
#define XTK_BUTTON_AFLOWSTO_MASK    (1ull << 34u)
#define XTK_BUTTON_AFLOWSFROM_MASK  (1ull << 35u)
#define XTK_BUTTON_ACONTROLS_MASK   (1ull << 36u)
#define XTK_BUTTON_ENABLED_MASK     (1ull << 37u)
#define XTK_BUTTON_ICON_MASK        (1ull << 38u)
#define XTK_BUTTON_STYLE_MASK       (1ull << 39u)

typedef struct XtkToggleProps {
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
	char const     *text;
	uint32_t        text_len;
	char const     *tip;
	uint32_t        tip_len;
	char const     *aname;
	uint32_t        aname_len;
	char const     *aid;
	uint32_t        aid_len;
	char const     *ahelp;
	uint32_t        ahelp_len;
	char const     *adesc;
	uint32_t        adesc_len;
	char const     *astatus;
	uint32_t        astatus_len;
	char const     *aitem;
	uint32_t        aitem_len;
	char const     *actype;
	uint32_t        actype_len;
	char const     *aaccel;
	uint32_t        aaccel_len;
	char const     *akey;
	uint32_t        akey_len;
	XtkLandmark     alandmark;
	char const     *alandname;
	uint32_t        alandname_len;
	XtkLiveSetting  alive;
	XtkHeadingLevel aheading;
	XtkAccessView   aview;
	bool            arequired;
	bool            avalid;
	bool            aperipheral;
	bool            adialog;
	int32_t         apos;
	int32_t         asize;
	int32_t         alevel;
	int32_t         aculture;
	char const     *alabel;
	uint32_t        alabel_len;
	char const     *adescribed;
	uint32_t        adescribed_len;
	char const     *aflowsto;
	uint32_t        aflowsto_len;
	char const     *aflowsfrom;
	uint32_t        aflowsfrom_len;
	char const     *acontrols;
	uint32_t        acontrols_len;
	bool            enabled;
	bool            checked;
} XtkToggleProps;

#define XTK_TOGGLE_W_MASK           (1ull << 0u)
#define XTK_TOGGLE_H_MASK           (1ull << 1u)
#define XTK_TOGGLE_GROW_MASK        (1ull << 2u)
#define XTK_TOGGLE_SELF_MASK        (1ull << 3u)
#define XTK_TOGGLE_ML_MASK          (1ull << 4u)
#define XTK_TOGGLE_MT_MASK          (1ull << 5u)
#define XTK_TOGGLE_MR_MASK          (1ull << 6u)
#define XTK_TOGGLE_MB_MASK          (1ull << 7u)
#define XTK_TOGGLE_TEXT_MASK        (1ull << 8u)
#define XTK_TOGGLE_TIP_MASK         (1ull << 9u)
#define XTK_TOGGLE_ANAME_MASK       (1ull << 10u)
#define XTK_TOGGLE_AID_MASK         (1ull << 11u)
#define XTK_TOGGLE_AHELP_MASK       (1ull << 12u)
#define XTK_TOGGLE_ADESC_MASK       (1ull << 13u)
#define XTK_TOGGLE_ASTATUS_MASK     (1ull << 14u)
#define XTK_TOGGLE_AITEM_MASK       (1ull << 15u)
#define XTK_TOGGLE_ACTYPE_MASK      (1ull << 16u)
#define XTK_TOGGLE_AACCEL_MASK      (1ull << 17u)
#define XTK_TOGGLE_AKEY_MASK        (1ull << 18u)
#define XTK_TOGGLE_ALANDMARK_MASK   (1ull << 19u)
#define XTK_TOGGLE_ALANDNAME_MASK   (1ull << 20u)
#define XTK_TOGGLE_ALIVE_MASK       (1ull << 21u)
#define XTK_TOGGLE_AHEADING_MASK    (1ull << 22u)
#define XTK_TOGGLE_AVIEW_MASK       (1ull << 23u)
#define XTK_TOGGLE_AREQUIRED_MASK   (1ull << 24u)
#define XTK_TOGGLE_AVALID_MASK      (1ull << 25u)
#define XTK_TOGGLE_APERIPHERAL_MASK (1ull << 26u)
#define XTK_TOGGLE_ADIALOG_MASK     (1ull << 27u)
#define XTK_TOGGLE_APOS_MASK        (1ull << 28u)
#define XTK_TOGGLE_ASIZE_MASK       (1ull << 29u)
#define XTK_TOGGLE_ALEVEL_MASK      (1ull << 30u)
#define XTK_TOGGLE_ACULTURE_MASK    (1ull << 31u)
#define XTK_TOGGLE_ALABEL_MASK      (1ull << 32u)
#define XTK_TOGGLE_ADESCRIBED_MASK  (1ull << 33u)
#define XTK_TOGGLE_AFLOWSTO_MASK    (1ull << 34u)
#define XTK_TOGGLE_AFLOWSFROM_MASK  (1ull << 35u)
#define XTK_TOGGLE_ACONTROLS_MASK   (1ull << 36u)
#define XTK_TOGGLE_ENABLED_MASK     (1ull << 37u)
#define XTK_TOGGLE_CHECKED_MASK     (1ull << 38u)

typedef struct XtkCheckBoxProps {
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
	char const     *text;
	uint32_t        text_len;
	char const     *tip;
	uint32_t        tip_len;
	char const     *aname;
	uint32_t        aname_len;
	char const     *aid;
	uint32_t        aid_len;
	char const     *ahelp;
	uint32_t        ahelp_len;
	char const     *adesc;
	uint32_t        adesc_len;
	char const     *astatus;
	uint32_t        astatus_len;
	char const     *aitem;
	uint32_t        aitem_len;
	char const     *actype;
	uint32_t        actype_len;
	char const     *aaccel;
	uint32_t        aaccel_len;
	char const     *akey;
	uint32_t        akey_len;
	XtkLandmark     alandmark;
	char const     *alandname;
	uint32_t        alandname_len;
	XtkLiveSetting  alive;
	XtkHeadingLevel aheading;
	XtkAccessView   aview;
	bool            arequired;
	bool            avalid;
	bool            aperipheral;
	bool            adialog;
	int32_t         apos;
	int32_t         asize;
	int32_t         alevel;
	int32_t         aculture;
	char const     *alabel;
	uint32_t        alabel_len;
	char const     *adescribed;
	uint32_t        adescribed_len;
	char const     *aflowsto;
	uint32_t        aflowsto_len;
	char const     *aflowsfrom;
	uint32_t        aflowsfrom_len;
	char const     *acontrols;
	uint32_t        acontrols_len;
	bool            enabled;
	bool            checked;
	bool            indeterminate;
	bool            threestate;
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
#define XTK_CHECKBOX_ANAME_MASK         (1ull << 10u)
#define XTK_CHECKBOX_AID_MASK           (1ull << 11u)
#define XTK_CHECKBOX_AHELP_MASK         (1ull << 12u)
#define XTK_CHECKBOX_ADESC_MASK         (1ull << 13u)
#define XTK_CHECKBOX_ASTATUS_MASK       (1ull << 14u)
#define XTK_CHECKBOX_AITEM_MASK         (1ull << 15u)
#define XTK_CHECKBOX_ACTYPE_MASK        (1ull << 16u)
#define XTK_CHECKBOX_AACCEL_MASK        (1ull << 17u)
#define XTK_CHECKBOX_AKEY_MASK          (1ull << 18u)
#define XTK_CHECKBOX_ALANDMARK_MASK     (1ull << 19u)
#define XTK_CHECKBOX_ALANDNAME_MASK     (1ull << 20u)
#define XTK_CHECKBOX_ALIVE_MASK         (1ull << 21u)
#define XTK_CHECKBOX_AHEADING_MASK      (1ull << 22u)
#define XTK_CHECKBOX_AVIEW_MASK         (1ull << 23u)
#define XTK_CHECKBOX_AREQUIRED_MASK     (1ull << 24u)
#define XTK_CHECKBOX_AVALID_MASK        (1ull << 25u)
#define XTK_CHECKBOX_APERIPHERAL_MASK   (1ull << 26u)
#define XTK_CHECKBOX_ADIALOG_MASK       (1ull << 27u)
#define XTK_CHECKBOX_APOS_MASK          (1ull << 28u)
#define XTK_CHECKBOX_ASIZE_MASK         (1ull << 29u)
#define XTK_CHECKBOX_ALEVEL_MASK        (1ull << 30u)
#define XTK_CHECKBOX_ACULTURE_MASK      (1ull << 31u)
#define XTK_CHECKBOX_ALABEL_MASK        (1ull << 32u)
#define XTK_CHECKBOX_ADESCRIBED_MASK    (1ull << 33u)
#define XTK_CHECKBOX_AFLOWSTO_MASK      (1ull << 34u)
#define XTK_CHECKBOX_AFLOWSFROM_MASK    (1ull << 35u)
#define XTK_CHECKBOX_ACONTROLS_MASK     (1ull << 36u)
#define XTK_CHECKBOX_ENABLED_MASK       (1ull << 37u)
#define XTK_CHECKBOX_CHECKED_MASK       (1ull << 38u)
#define XTK_CHECKBOX_INDETERMINATE_MASK (1ull << 39u)
#define XTK_CHECKBOX_THREESTATE_MASK    (1ull << 40u)

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
	char const       *aname;
	uint32_t          aname_len;
	char const       *aid;
	uint32_t          aid_len;
	char const       *ahelp;
	uint32_t          ahelp_len;
	char const       *adesc;
	uint32_t          adesc_len;
	char const       *astatus;
	uint32_t          astatus_len;
	char const       *aitem;
	uint32_t          aitem_len;
	char const       *actype;
	uint32_t          actype_len;
	char const       *aaccel;
	uint32_t          aaccel_len;
	char const       *akey;
	uint32_t          akey_len;
	XtkLandmark       alandmark;
	char const       *alandname;
	uint32_t          alandname_len;
	XtkLiveSetting    alive;
	XtkHeadingLevel   aheading;
	XtkAccessView     aview;
	bool              arequired;
	bool              avalid;
	bool              aperipheral;
	bool              adialog;
	int32_t           apos;
	int32_t           asize;
	int32_t           alevel;
	int32_t           aculture;
	char const       *alabel;
	uint32_t          alabel_len;
	char const       *adescribed;
	uint32_t          adescribed_len;
	char const       *aflowsto;
	uint32_t          aflowsto_len;
	char const       *aflowsfrom;
	uint32_t          aflowsfrom_len;
	char const       *acontrols;
	uint32_t          acontrols_len;
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
#define XTK_SLIDER_ANAME_MASK       (1ull << 9u)
#define XTK_SLIDER_AID_MASK         (1ull << 10u)
#define XTK_SLIDER_AHELP_MASK       (1ull << 11u)
#define XTK_SLIDER_ADESC_MASK       (1ull << 12u)
#define XTK_SLIDER_ASTATUS_MASK     (1ull << 13u)
#define XTK_SLIDER_AITEM_MASK       (1ull << 14u)
#define XTK_SLIDER_ACTYPE_MASK      (1ull << 15u)
#define XTK_SLIDER_AACCEL_MASK      (1ull << 16u)
#define XTK_SLIDER_AKEY_MASK        (1ull << 17u)
#define XTK_SLIDER_ALANDMARK_MASK   (1ull << 18u)
#define XTK_SLIDER_ALANDNAME_MASK   (1ull << 19u)
#define XTK_SLIDER_ALIVE_MASK       (1ull << 20u)
#define XTK_SLIDER_AHEADING_MASK    (1ull << 21u)
#define XTK_SLIDER_AVIEW_MASK       (1ull << 22u)
#define XTK_SLIDER_AREQUIRED_MASK   (1ull << 23u)
#define XTK_SLIDER_AVALID_MASK      (1ull << 24u)
#define XTK_SLIDER_APERIPHERAL_MASK (1ull << 25u)
#define XTK_SLIDER_ADIALOG_MASK     (1ull << 26u)
#define XTK_SLIDER_APOS_MASK        (1ull << 27u)
#define XTK_SLIDER_ASIZE_MASK       (1ull << 28u)
#define XTK_SLIDER_ALEVEL_MASK      (1ull << 29u)
#define XTK_SLIDER_ACULTURE_MASK    (1ull << 30u)
#define XTK_SLIDER_ALABEL_MASK      (1ull << 31u)
#define XTK_SLIDER_ADESCRIBED_MASK  (1ull << 32u)
#define XTK_SLIDER_AFLOWSTO_MASK    (1ull << 33u)
#define XTK_SLIDER_AFLOWSFROM_MASK  (1ull << 34u)
#define XTK_SLIDER_ACONTROLS_MASK   (1ull << 35u)
#define XTK_SLIDER_ENABLED_MASK     (1ull << 36u)
#define XTK_SLIDER_MIN_MASK         (1ull << 37u)
#define XTK_SLIDER_MAX_MASK         (1ull << 38u)
#define XTK_SLIDER_VALUE_MASK       (1ull << 39u)
#define XTK_SLIDER_STEP_MASK        (1ull << 40u)
#define XTK_SLIDER_TICK_MASK        (1ull << 41u)
#define XTK_SLIDER_TICKPLACE_MASK   (1ull << 42u)
#define XTK_SLIDER_SNAPSTO_MASK     (1ull << 43u)
#define XTK_SLIDER_SMALLCHANGE_MASK (1ull << 44u)
#define XTK_SLIDER_LARGECHANGE_MASK (1ull << 45u)
#define XTK_SLIDER_DIR_MASK         (1ull << 46u)
#define XTK_SLIDER_RANGE_MASK       (1ull << 47u)
#define XTK_SLIDER_RANGESTART_MASK  (1ull << 48u)
#define XTK_SLIDER_RANGEEND_MASK    (1ull << 49u)

typedef struct XtkInputProps {
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
	char const     *text;
	uint32_t        text_len;
	char const     *tip;
	uint32_t        tip_len;
	char const     *aname;
	uint32_t        aname_len;
	char const     *aid;
	uint32_t        aid_len;
	char const     *ahelp;
	uint32_t        ahelp_len;
	char const     *adesc;
	uint32_t        adesc_len;
	char const     *astatus;
	uint32_t        astatus_len;
	char const     *aitem;
	uint32_t        aitem_len;
	char const     *actype;
	uint32_t        actype_len;
	char const     *aaccel;
	uint32_t        aaccel_len;
	char const     *akey;
	uint32_t        akey_len;
	XtkLandmark     alandmark;
	char const     *alandname;
	uint32_t        alandname_len;
	XtkLiveSetting  alive;
	XtkHeadingLevel aheading;
	XtkAccessView   aview;
	bool            arequired;
	bool            avalid;
	bool            aperipheral;
	bool            adialog;
	int32_t         apos;
	int32_t         asize;
	int32_t         alevel;
	int32_t         aculture;
	char const     *alabel;
	uint32_t        alabel_len;
	char const     *adescribed;
	uint32_t        adescribed_len;
	char const     *aflowsto;
	uint32_t        aflowsto_len;
	char const     *aflowsfrom;
	uint32_t        aflowsfrom_len;
	char const     *acontrols;
	uint32_t        acontrols_len;
	bool            enabled;
	char const     *placeholder;
	uint32_t        placeholder_len;
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
#define XTK_INPUT_ANAME_MASK       (1ull << 10u)
#define XTK_INPUT_AID_MASK         (1ull << 11u)
#define XTK_INPUT_AHELP_MASK       (1ull << 12u)
#define XTK_INPUT_ADESC_MASK       (1ull << 13u)
#define XTK_INPUT_ASTATUS_MASK     (1ull << 14u)
#define XTK_INPUT_AITEM_MASK       (1ull << 15u)
#define XTK_INPUT_ACTYPE_MASK      (1ull << 16u)
#define XTK_INPUT_AACCEL_MASK      (1ull << 17u)
#define XTK_INPUT_AKEY_MASK        (1ull << 18u)
#define XTK_INPUT_ALANDMARK_MASK   (1ull << 19u)
#define XTK_INPUT_ALANDNAME_MASK   (1ull << 20u)
#define XTK_INPUT_ALIVE_MASK       (1ull << 21u)
#define XTK_INPUT_AHEADING_MASK    (1ull << 22u)
#define XTK_INPUT_AVIEW_MASK       (1ull << 23u)
#define XTK_INPUT_AREQUIRED_MASK   (1ull << 24u)
#define XTK_INPUT_AVALID_MASK      (1ull << 25u)
#define XTK_INPUT_APERIPHERAL_MASK (1ull << 26u)
#define XTK_INPUT_ADIALOG_MASK     (1ull << 27u)
#define XTK_INPUT_APOS_MASK        (1ull << 28u)
#define XTK_INPUT_ASIZE_MASK       (1ull << 29u)
#define XTK_INPUT_ALEVEL_MASK      (1ull << 30u)
#define XTK_INPUT_ACULTURE_MASK    (1ull << 31u)
#define XTK_INPUT_ALABEL_MASK      (1ull << 32u)
#define XTK_INPUT_ADESCRIBED_MASK  (1ull << 33u)
#define XTK_INPUT_AFLOWSTO_MASK    (1ull << 34u)
#define XTK_INPUT_AFLOWSFROM_MASK  (1ull << 35u)
#define XTK_INPUT_ACONTROLS_MASK   (1ull << 36u)
#define XTK_INPUT_ENABLED_MASK     (1ull << 37u)
#define XTK_INPUT_PLACEHOLDER_MASK (1ull << 38u)

typedef struct XtkTextBoxProps {
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
	char const     *text;
	uint32_t        text_len;
	char const     *tip;
	uint32_t        tip_len;
	char const     *aname;
	uint32_t        aname_len;
	char const     *aid;
	uint32_t        aid_len;
	char const     *ahelp;
	uint32_t        ahelp_len;
	char const     *adesc;
	uint32_t        adesc_len;
	char const     *astatus;
	uint32_t        astatus_len;
	char const     *aitem;
	uint32_t        aitem_len;
	char const     *actype;
	uint32_t        actype_len;
	char const     *aaccel;
	uint32_t        aaccel_len;
	char const     *akey;
	uint32_t        akey_len;
	XtkLandmark     alandmark;
	char const     *alandname;
	uint32_t        alandname_len;
	XtkLiveSetting  alive;
	XtkHeadingLevel aheading;
	XtkAccessView   aview;
	bool            arequired;
	bool            avalid;
	bool            aperipheral;
	bool            adialog;
	int32_t         apos;
	int32_t         asize;
	int32_t         alevel;
	int32_t         aculture;
	char const     *alabel;
	uint32_t        alabel_len;
	char const     *adescribed;
	uint32_t        adescribed_len;
	char const     *aflowsto;
	uint32_t        aflowsto_len;
	char const     *aflowsfrom;
	uint32_t        aflowsfrom_len;
	char const     *acontrols;
	uint32_t        acontrols_len;
	bool            enabled;
	char const     *placeholder;
	uint32_t        placeholder_len;
	bool            multiline;
	bool            readonly;
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
#define XTK_TEXTBOX_ANAME_MASK       (1ull << 10u)
#define XTK_TEXTBOX_AID_MASK         (1ull << 11u)
#define XTK_TEXTBOX_AHELP_MASK       (1ull << 12u)
#define XTK_TEXTBOX_ADESC_MASK       (1ull << 13u)
#define XTK_TEXTBOX_ASTATUS_MASK     (1ull << 14u)
#define XTK_TEXTBOX_AITEM_MASK       (1ull << 15u)
#define XTK_TEXTBOX_ACTYPE_MASK      (1ull << 16u)
#define XTK_TEXTBOX_AACCEL_MASK      (1ull << 17u)
#define XTK_TEXTBOX_AKEY_MASK        (1ull << 18u)
#define XTK_TEXTBOX_ALANDMARK_MASK   (1ull << 19u)
#define XTK_TEXTBOX_ALANDNAME_MASK   (1ull << 20u)
#define XTK_TEXTBOX_ALIVE_MASK       (1ull << 21u)
#define XTK_TEXTBOX_AHEADING_MASK    (1ull << 22u)
#define XTK_TEXTBOX_AVIEW_MASK       (1ull << 23u)
#define XTK_TEXTBOX_AREQUIRED_MASK   (1ull << 24u)
#define XTK_TEXTBOX_AVALID_MASK      (1ull << 25u)
#define XTK_TEXTBOX_APERIPHERAL_MASK (1ull << 26u)
#define XTK_TEXTBOX_ADIALOG_MASK     (1ull << 27u)
#define XTK_TEXTBOX_APOS_MASK        (1ull << 28u)
#define XTK_TEXTBOX_ASIZE_MASK       (1ull << 29u)
#define XTK_TEXTBOX_ALEVEL_MASK      (1ull << 30u)
#define XTK_TEXTBOX_ACULTURE_MASK    (1ull << 31u)
#define XTK_TEXTBOX_ALABEL_MASK      (1ull << 32u)
#define XTK_TEXTBOX_ADESCRIBED_MASK  (1ull << 33u)
#define XTK_TEXTBOX_AFLOWSTO_MASK    (1ull << 34u)
#define XTK_TEXTBOX_AFLOWSFROM_MASK  (1ull << 35u)
#define XTK_TEXTBOX_ACONTROLS_MASK   (1ull << 36u)
#define XTK_TEXTBOX_ENABLED_MASK     (1ull << 37u)
#define XTK_TEXTBOX_PLACEHOLDER_MASK (1ull << 38u)
#define XTK_TEXTBOX_MULTILINE_MASK   (1ull << 39u)
#define XTK_TEXTBOX_READONLY_MASK    (1ull << 40u)

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
	char const     *aname;
	uint32_t        aname_len;
	char const     *aid;
	uint32_t        aid_len;
	char const     *ahelp;
	uint32_t        ahelp_len;
	char const     *adesc;
	uint32_t        adesc_len;
	char const     *astatus;
	uint32_t        astatus_len;
	char const     *aitem;
	uint32_t        aitem_len;
	char const     *actype;
	uint32_t        actype_len;
	char const     *aaccel;
	uint32_t        aaccel_len;
	char const     *akey;
	uint32_t        akey_len;
	XtkLandmark     alandmark;
	char const     *alandname;
	uint32_t        alandname_len;
	XtkLiveSetting  alive;
	XtkHeadingLevel aheading;
	XtkAccessView   aview;
	bool            arequired;
	bool            avalid;
	bool            aperipheral;
	bool            adialog;
	int32_t         apos;
	int32_t         asize;
	int32_t         alevel;
	int32_t         aculture;
	char const     *alabel;
	uint32_t        alabel_len;
	char const     *adescribed;
	uint32_t        adescribed_len;
	char const     *aflowsto;
	uint32_t        aflowsto_len;
	char const     *aflowsfrom;
	uint32_t        aflowsfrom_len;
	char const     *acontrols;
	uint32_t        acontrols_len;
	XtkResource     src;
	XtkImageStretch fit;
	float           nl;
	float           nt;
	float           nr;
	float           nb;
} XtkImageProps;

#define XTK_IMAGE_W_MASK           (1ull << 0u)
#define XTK_IMAGE_H_MASK           (1ull << 1u)
#define XTK_IMAGE_GROW_MASK        (1ull << 2u)
#define XTK_IMAGE_SELF_MASK        (1ull << 3u)
#define XTK_IMAGE_ML_MASK          (1ull << 4u)
#define XTK_IMAGE_MT_MASK          (1ull << 5u)
#define XTK_IMAGE_MR_MASK          (1ull << 6u)
#define XTK_IMAGE_MB_MASK          (1ull << 7u)
#define XTK_IMAGE_TIP_MASK         (1ull << 8u)
#define XTK_IMAGE_ANAME_MASK       (1ull << 9u)
#define XTK_IMAGE_AID_MASK         (1ull << 10u)
#define XTK_IMAGE_AHELP_MASK       (1ull << 11u)
#define XTK_IMAGE_ADESC_MASK       (1ull << 12u)
#define XTK_IMAGE_ASTATUS_MASK     (1ull << 13u)
#define XTK_IMAGE_AITEM_MASK       (1ull << 14u)
#define XTK_IMAGE_ACTYPE_MASK      (1ull << 15u)
#define XTK_IMAGE_AACCEL_MASK      (1ull << 16u)
#define XTK_IMAGE_AKEY_MASK        (1ull << 17u)
#define XTK_IMAGE_ALANDMARK_MASK   (1ull << 18u)
#define XTK_IMAGE_ALANDNAME_MASK   (1ull << 19u)
#define XTK_IMAGE_ALIVE_MASK       (1ull << 20u)
#define XTK_IMAGE_AHEADING_MASK    (1ull << 21u)
#define XTK_IMAGE_AVIEW_MASK       (1ull << 22u)
#define XTK_IMAGE_AREQUIRED_MASK   (1ull << 23u)
#define XTK_IMAGE_AVALID_MASK      (1ull << 24u)
#define XTK_IMAGE_APERIPHERAL_MASK (1ull << 25u)
#define XTK_IMAGE_ADIALOG_MASK     (1ull << 26u)
#define XTK_IMAGE_APOS_MASK        (1ull << 27u)
#define XTK_IMAGE_ASIZE_MASK       (1ull << 28u)
#define XTK_IMAGE_ALEVEL_MASK      (1ull << 29u)
#define XTK_IMAGE_ACULTURE_MASK    (1ull << 30u)
#define XTK_IMAGE_ALABEL_MASK      (1ull << 31u)
#define XTK_IMAGE_ADESCRIBED_MASK  (1ull << 32u)
#define XTK_IMAGE_AFLOWSTO_MASK    (1ull << 33u)
#define XTK_IMAGE_AFLOWSFROM_MASK  (1ull << 34u)
#define XTK_IMAGE_ACONTROLS_MASK   (1ull << 35u)
#define XTK_IMAGE_SRC_MASK         (1ull << 36u)
#define XTK_IMAGE_FIT_MASK         (1ull << 37u)
#define XTK_IMAGE_NL_MASK          (1ull << 38u)
#define XTK_IMAGE_NT_MASK          (1ull << 39u)
#define XTK_IMAGE_NR_MASK          (1ull << 40u)
#define XTK_IMAGE_NB_MASK          (1ull << 41u)

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
	char const      *aname;
	uint32_t         aname_len;
	char const      *aid;
	uint32_t         aid_len;
	char const      *ahelp;
	uint32_t         ahelp_len;
	char const      *adesc;
	uint32_t         adesc_len;
	char const      *astatus;
	uint32_t         astatus_len;
	char const      *aitem;
	uint32_t         aitem_len;
	char const      *actype;
	uint32_t         actype_len;
	char const      *aaccel;
	uint32_t         aaccel_len;
	char const      *akey;
	uint32_t         akey_len;
	XtkLandmark      alandmark;
	char const      *alandname;
	uint32_t         alandname_len;
	XtkLiveSetting   alive;
	XtkHeadingLevel  aheading;
	XtkAccessView    aview;
	bool             arequired;
	bool             avalid;
	bool             aperipheral;
	bool             adialog;
	int32_t          apos;
	int32_t          asize;
	int32_t          alevel;
	int32_t          aculture;
	char const      *alabel;
	uint32_t         alabel_len;
	char const      *adescribed;
	uint32_t         adescribed_len;
	char const      *aflowsto;
	uint32_t         aflowsto_len;
	char const      *aflowsfrom;
	uint32_t         aflowsfrom_len;
	char const      *acontrols;
	uint32_t         acontrols_len;
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
#define XTK_PROGRESS_ANAME_MASK         (1ull << 9u)
#define XTK_PROGRESS_AID_MASK           (1ull << 10u)
#define XTK_PROGRESS_AHELP_MASK         (1ull << 11u)
#define XTK_PROGRESS_ADESC_MASK         (1ull << 12u)
#define XTK_PROGRESS_ASTATUS_MASK       (1ull << 13u)
#define XTK_PROGRESS_AITEM_MASK         (1ull << 14u)
#define XTK_PROGRESS_ACTYPE_MASK        (1ull << 15u)
#define XTK_PROGRESS_AACCEL_MASK        (1ull << 16u)
#define XTK_PROGRESS_AKEY_MASK          (1ull << 17u)
#define XTK_PROGRESS_ALANDMARK_MASK     (1ull << 18u)
#define XTK_PROGRESS_ALANDNAME_MASK     (1ull << 19u)
#define XTK_PROGRESS_ALIVE_MASK         (1ull << 20u)
#define XTK_PROGRESS_AHEADING_MASK      (1ull << 21u)
#define XTK_PROGRESS_AVIEW_MASK         (1ull << 22u)
#define XTK_PROGRESS_AREQUIRED_MASK     (1ull << 23u)
#define XTK_PROGRESS_AVALID_MASK        (1ull << 24u)
#define XTK_PROGRESS_APERIPHERAL_MASK   (1ull << 25u)
#define XTK_PROGRESS_ADIALOG_MASK       (1ull << 26u)
#define XTK_PROGRESS_APOS_MASK          (1ull << 27u)
#define XTK_PROGRESS_ASIZE_MASK         (1ull << 28u)
#define XTK_PROGRESS_ALEVEL_MASK        (1ull << 29u)
#define XTK_PROGRESS_ACULTURE_MASK      (1ull << 30u)
#define XTK_PROGRESS_ALABEL_MASK        (1ull << 31u)
#define XTK_PROGRESS_ADESCRIBED_MASK    (1ull << 32u)
#define XTK_PROGRESS_AFLOWSTO_MASK      (1ull << 33u)
#define XTK_PROGRESS_AFLOWSFROM_MASK    (1ull << 34u)
#define XTK_PROGRESS_ACONTROLS_MASK     (1ull << 35u)
#define XTK_PROGRESS_MIN_MASK           (1ull << 36u)
#define XTK_PROGRESS_MAX_MASK           (1ull << 37u)
#define XTK_PROGRESS_VALUE_MASK         (1ull << 38u)
#define XTK_PROGRESS_INDETERMINATE_MASK (1ull << 39u)
#define XTK_PROGRESS_STATE_MASK         (1ull << 40u)
#define XTK_PROGRESS_ACTIVE_MASK        (1ull << 41u)
#define XTK_PROGRESS_PL_MASK            (1ull << 42u)
#define XTK_PROGRESS_PT_MASK            (1ull << 43u)
#define XTK_PROGRESS_PR_MASK            (1ull << 44u)
#define XTK_PROGRESS_PB_MASK            (1ull << 45u)
#define XTK_PROGRESS_BORDER_WIDTH_MASK  (1ull << 46u)

typedef struct XtkNumberProps {
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
	char const     *aname;
	uint32_t        aname_len;
	char const     *aid;
	uint32_t        aid_len;
	char const     *ahelp;
	uint32_t        ahelp_len;
	char const     *adesc;
	uint32_t        adesc_len;
	char const     *astatus;
	uint32_t        astatus_len;
	char const     *aitem;
	uint32_t        aitem_len;
	char const     *actype;
	uint32_t        actype_len;
	char const     *aaccel;
	uint32_t        aaccel_len;
	char const     *akey;
	uint32_t        akey_len;
	XtkLandmark     alandmark;
	char const     *alandname;
	uint32_t        alandname_len;
	XtkLiveSetting  alive;
	XtkHeadingLevel aheading;
	XtkAccessView   aview;
	bool            arequired;
	bool            avalid;
	bool            aperipheral;
	bool            adialog;
	int32_t         apos;
	int32_t         asize;
	int32_t         alevel;
	int32_t         aculture;
	char const     *alabel;
	uint32_t        alabel_len;
	char const     *adescribed;
	uint32_t        adescribed_len;
	char const     *aflowsto;
	uint32_t        aflowsto_len;
	char const     *aflowsfrom;
	uint32_t        aflowsfrom_len;
	char const     *acontrols;
	uint32_t        acontrols_len;
	bool            enabled;
	double          value;
	double          min;
	double          max;
	double          step;
	bool            hidespin;
} XtkNumberProps;

#define XTK_NUMBER_W_MASK           (1ull << 0u)
#define XTK_NUMBER_H_MASK           (1ull << 1u)
#define XTK_NUMBER_GROW_MASK        (1ull << 2u)
#define XTK_NUMBER_SELF_MASK        (1ull << 3u)
#define XTK_NUMBER_ML_MASK          (1ull << 4u)
#define XTK_NUMBER_MT_MASK          (1ull << 5u)
#define XTK_NUMBER_MR_MASK          (1ull << 6u)
#define XTK_NUMBER_MB_MASK          (1ull << 7u)
#define XTK_NUMBER_TIP_MASK         (1ull << 8u)
#define XTK_NUMBER_ANAME_MASK       (1ull << 9u)
#define XTK_NUMBER_AID_MASK         (1ull << 10u)
#define XTK_NUMBER_AHELP_MASK       (1ull << 11u)
#define XTK_NUMBER_ADESC_MASK       (1ull << 12u)
#define XTK_NUMBER_ASTATUS_MASK     (1ull << 13u)
#define XTK_NUMBER_AITEM_MASK       (1ull << 14u)
#define XTK_NUMBER_ACTYPE_MASK      (1ull << 15u)
#define XTK_NUMBER_AACCEL_MASK      (1ull << 16u)
#define XTK_NUMBER_AKEY_MASK        (1ull << 17u)
#define XTK_NUMBER_ALANDMARK_MASK   (1ull << 18u)
#define XTK_NUMBER_ALANDNAME_MASK   (1ull << 19u)
#define XTK_NUMBER_ALIVE_MASK       (1ull << 20u)
#define XTK_NUMBER_AHEADING_MASK    (1ull << 21u)
#define XTK_NUMBER_AVIEW_MASK       (1ull << 22u)
#define XTK_NUMBER_AREQUIRED_MASK   (1ull << 23u)
#define XTK_NUMBER_AVALID_MASK      (1ull << 24u)
#define XTK_NUMBER_APERIPHERAL_MASK (1ull << 25u)
#define XTK_NUMBER_ADIALOG_MASK     (1ull << 26u)
#define XTK_NUMBER_APOS_MASK        (1ull << 27u)
#define XTK_NUMBER_ASIZE_MASK       (1ull << 28u)
#define XTK_NUMBER_ALEVEL_MASK      (1ull << 29u)
#define XTK_NUMBER_ACULTURE_MASK    (1ull << 30u)
#define XTK_NUMBER_ALABEL_MASK      (1ull << 31u)
#define XTK_NUMBER_ADESCRIBED_MASK  (1ull << 32u)
#define XTK_NUMBER_AFLOWSTO_MASK    (1ull << 33u)
#define XTK_NUMBER_AFLOWSFROM_MASK  (1ull << 34u)
#define XTK_NUMBER_ACONTROLS_MASK   (1ull << 35u)
#define XTK_NUMBER_ENABLED_MASK     (1ull << 36u)
#define XTK_NUMBER_VALUE_MASK       (1ull << 37u)
#define XTK_NUMBER_MIN_MASK         (1ull << 38u)
#define XTK_NUMBER_MAX_MASK         (1ull << 39u)
#define XTK_NUMBER_STEP_MASK        (1ull << 40u)
#define XTK_NUMBER_HIDESPIN_MASK    (1ull << 41u)

typedef struct XtkItemProps {
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
	char const     *text;
	uint32_t        text_len;
	char const     *tip;
	uint32_t        tip_len;
	char const     *aname;
	uint32_t        aname_len;
	char const     *aid;
	uint32_t        aid_len;
	char const     *ahelp;
	uint32_t        ahelp_len;
	char const     *adesc;
	uint32_t        adesc_len;
	char const     *astatus;
	uint32_t        astatus_len;
	char const     *aitem;
	uint32_t        aitem_len;
	char const     *actype;
	uint32_t        actype_len;
	char const     *aaccel;
	uint32_t        aaccel_len;
	char const     *akey;
	uint32_t        akey_len;
	XtkLandmark     alandmark;
	char const     *alandname;
	uint32_t        alandname_len;
	XtkLiveSetting  alive;
	XtkHeadingLevel aheading;
	XtkAccessView   aview;
	bool            arequired;
	bool            avalid;
	bool            aperipheral;
	bool            adialog;
	int32_t         apos;
	int32_t         asize;
	int32_t         alevel;
	int32_t         aculture;
	char const     *alabel;
	uint32_t        alabel_len;
	char const     *adescribed;
	uint32_t        adescribed_len;
	char const     *aflowsto;
	uint32_t        aflowsto_len;
	char const     *aflowsfrom;
	uint32_t        aflowsfrom_len;
	char const     *acontrols;
	uint32_t        acontrols_len;
	char const     *icon;
	uint32_t        icon_len;
	bool            enabled;
	bool            selected;
	bool            expanded;
} XtkItemProps;

#define XTK_ITEM_W_MASK           (1ull << 0u)
#define XTK_ITEM_H_MASK           (1ull << 1u)
#define XTK_ITEM_GROW_MASK        (1ull << 2u)
#define XTK_ITEM_SELF_MASK        (1ull << 3u)
#define XTK_ITEM_ML_MASK          (1ull << 4u)
#define XTK_ITEM_MT_MASK          (1ull << 5u)
#define XTK_ITEM_MR_MASK          (1ull << 6u)
#define XTK_ITEM_MB_MASK          (1ull << 7u)
#define XTK_ITEM_TEXT_MASK        (1ull << 8u)
#define XTK_ITEM_TIP_MASK         (1ull << 9u)
#define XTK_ITEM_ANAME_MASK       (1ull << 10u)
#define XTK_ITEM_AID_MASK         (1ull << 11u)
#define XTK_ITEM_AHELP_MASK       (1ull << 12u)
#define XTK_ITEM_ADESC_MASK       (1ull << 13u)
#define XTK_ITEM_ASTATUS_MASK     (1ull << 14u)
#define XTK_ITEM_AITEM_MASK       (1ull << 15u)
#define XTK_ITEM_ACTYPE_MASK      (1ull << 16u)
#define XTK_ITEM_AACCEL_MASK      (1ull << 17u)
#define XTK_ITEM_AKEY_MASK        (1ull << 18u)
#define XTK_ITEM_ALANDMARK_MASK   (1ull << 19u)
#define XTK_ITEM_ALANDNAME_MASK   (1ull << 20u)
#define XTK_ITEM_ALIVE_MASK       (1ull << 21u)
#define XTK_ITEM_AHEADING_MASK    (1ull << 22u)
#define XTK_ITEM_AVIEW_MASK       (1ull << 23u)
#define XTK_ITEM_AREQUIRED_MASK   (1ull << 24u)
#define XTK_ITEM_AVALID_MASK      (1ull << 25u)
#define XTK_ITEM_APERIPHERAL_MASK (1ull << 26u)
#define XTK_ITEM_ADIALOG_MASK     (1ull << 27u)
#define XTK_ITEM_APOS_MASK        (1ull << 28u)
#define XTK_ITEM_ASIZE_MASK       (1ull << 29u)
#define XTK_ITEM_ALEVEL_MASK      (1ull << 30u)
#define XTK_ITEM_ACULTURE_MASK    (1ull << 31u)
#define XTK_ITEM_ALABEL_MASK      (1ull << 32u)
#define XTK_ITEM_ADESCRIBED_MASK  (1ull << 33u)
#define XTK_ITEM_AFLOWSTO_MASK    (1ull << 34u)
#define XTK_ITEM_AFLOWSFROM_MASK  (1ull << 35u)
#define XTK_ITEM_ACONTROLS_MASK   (1ull << 36u)
#define XTK_ITEM_ICON_MASK        (1ull << 37u)
#define XTK_ITEM_ENABLED_MASK     (1ull << 38u)
#define XTK_ITEM_SELECTED_MASK    (1ull << 39u)
#define XTK_ITEM_EXPANDED_MASK    (1ull << 40u)

typedef struct XtkSelectionProps {
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
	char const     *aname;
	uint32_t        aname_len;
	char const     *aid;
	uint32_t        aid_len;
	char const     *ahelp;
	uint32_t        ahelp_len;
	char const     *adesc;
	uint32_t        adesc_len;
	char const     *astatus;
	uint32_t        astatus_len;
	char const     *aitem;
	uint32_t        aitem_len;
	char const     *actype;
	uint32_t        actype_len;
	char const     *aaccel;
	uint32_t        aaccel_len;
	char const     *akey;
	uint32_t        akey_len;
	XtkLandmark     alandmark;
	char const     *alandname;
	uint32_t        alandname_len;
	XtkLiveSetting  alive;
	XtkHeadingLevel aheading;
	XtkAccessView   aview;
	bool            arequired;
	bool            avalid;
	bool            aperipheral;
	bool            adialog;
	int32_t         apos;
	int32_t         asize;
	int32_t         alevel;
	int32_t         aculture;
	char const     *alabel;
	uint32_t        alabel_len;
	char const     *adescribed;
	uint32_t        adescribed_len;
	char const     *aflowsto;
	uint32_t        aflowsto_len;
	char const     *aflowsfrom;
	uint32_t        aflowsfrom_len;
	char const     *acontrols;
	uint32_t        acontrols_len;
	bool            enabled;
	int32_t         sel;
	int32_t         nitem;
} XtkSelectionProps;

#define XTK_SELECTION_W_MASK           (1ull << 0u)
#define XTK_SELECTION_H_MASK           (1ull << 1u)
#define XTK_SELECTION_GROW_MASK        (1ull << 2u)
#define XTK_SELECTION_SELF_MASK        (1ull << 3u)
#define XTK_SELECTION_ML_MASK          (1ull << 4u)
#define XTK_SELECTION_MT_MASK          (1ull << 5u)
#define XTK_SELECTION_MR_MASK          (1ull << 6u)
#define XTK_SELECTION_MB_MASK          (1ull << 7u)
#define XTK_SELECTION_TIP_MASK         (1ull << 8u)
#define XTK_SELECTION_ANAME_MASK       (1ull << 9u)
#define XTK_SELECTION_AID_MASK         (1ull << 10u)
#define XTK_SELECTION_AHELP_MASK       (1ull << 11u)
#define XTK_SELECTION_ADESC_MASK       (1ull << 12u)
#define XTK_SELECTION_ASTATUS_MASK     (1ull << 13u)
#define XTK_SELECTION_AITEM_MASK       (1ull << 14u)
#define XTK_SELECTION_ACTYPE_MASK      (1ull << 15u)
#define XTK_SELECTION_AACCEL_MASK      (1ull << 16u)
#define XTK_SELECTION_AKEY_MASK        (1ull << 17u)
#define XTK_SELECTION_ALANDMARK_MASK   (1ull << 18u)
#define XTK_SELECTION_ALANDNAME_MASK   (1ull << 19u)
#define XTK_SELECTION_ALIVE_MASK       (1ull << 20u)
#define XTK_SELECTION_AHEADING_MASK    (1ull << 21u)
#define XTK_SELECTION_AVIEW_MASK       (1ull << 22u)
#define XTK_SELECTION_AREQUIRED_MASK   (1ull << 23u)
#define XTK_SELECTION_AVALID_MASK      (1ull << 24u)
#define XTK_SELECTION_APERIPHERAL_MASK (1ull << 25u)
#define XTK_SELECTION_ADIALOG_MASK     (1ull << 26u)
#define XTK_SELECTION_APOS_MASK        (1ull << 27u)
#define XTK_SELECTION_ASIZE_MASK       (1ull << 28u)
#define XTK_SELECTION_ALEVEL_MASK      (1ull << 29u)
#define XTK_SELECTION_ACULTURE_MASK    (1ull << 30u)
#define XTK_SELECTION_ALABEL_MASK      (1ull << 31u)
#define XTK_SELECTION_ADESCRIBED_MASK  (1ull << 32u)
#define XTK_SELECTION_AFLOWSTO_MASK    (1ull << 33u)
#define XTK_SELECTION_AFLOWSFROM_MASK  (1ull << 34u)
#define XTK_SELECTION_ACONTROLS_MASK   (1ull << 35u)
#define XTK_SELECTION_ENABLED_MASK     (1ull << 36u)
#define XTK_SELECTION_SEL_MASK         (1ull << 37u)
#define XTK_SELECTION_NITEM_MASK       (1ull << 38u)

typedef struct XtkNavProps {
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
	char const      *aname;
	uint32_t         aname_len;
	char const      *aid;
	uint32_t         aid_len;
	char const      *ahelp;
	uint32_t         ahelp_len;
	char const      *adesc;
	uint32_t         adesc_len;
	char const      *astatus;
	uint32_t         astatus_len;
	char const      *aitem;
	uint32_t         aitem_len;
	char const      *actype;
	uint32_t         actype_len;
	char const      *aaccel;
	uint32_t         aaccel_len;
	char const      *akey;
	uint32_t         akey_len;
	XtkLandmark      alandmark;
	char const      *alandname;
	uint32_t         alandname_len;
	XtkLiveSetting   alive;
	XtkHeadingLevel  aheading;
	XtkAccessView    aview;
	bool             arequired;
	bool             avalid;
	bool             aperipheral;
	bool             adialog;
	int32_t          apos;
	int32_t          asize;
	int32_t          alevel;
	int32_t          aculture;
	char const      *alabel;
	uint32_t         alabel_len;
	char const      *adescribed;
	uint32_t         adescribed_len;
	char const      *aflowsto;
	uint32_t         aflowsto_len;
	char const      *aflowsfrom;
	uint32_t         aflowsfrom_len;
	char const      *acontrols;
	uint32_t         acontrols_len;
	bool             enabled;
	int32_t          sel;
	XtkNavPaneMode   display;
	bool             settings_visible;
	char const      *pane_title;
	uint32_t         pane_title_len;
	bool             always_show_header;
	XtkNavBackButton back_button;
	bool             back_enabled;
} XtkNavProps;

#define XTK_NAV_W_MASK                  (1ull << 0u)
#define XTK_NAV_H_MASK                  (1ull << 1u)
#define XTK_NAV_GROW_MASK               (1ull << 2u)
#define XTK_NAV_SELF_MASK               (1ull << 3u)
#define XTK_NAV_ML_MASK                 (1ull << 4u)
#define XTK_NAV_MT_MASK                 (1ull << 5u)
#define XTK_NAV_MR_MASK                 (1ull << 6u)
#define XTK_NAV_MB_MASK                 (1ull << 7u)
#define XTK_NAV_TIP_MASK                (1ull << 8u)
#define XTK_NAV_ANAME_MASK              (1ull << 9u)
#define XTK_NAV_AID_MASK                (1ull << 10u)
#define XTK_NAV_AHELP_MASK              (1ull << 11u)
#define XTK_NAV_ADESC_MASK              (1ull << 12u)
#define XTK_NAV_ASTATUS_MASK            (1ull << 13u)
#define XTK_NAV_AITEM_MASK              (1ull << 14u)
#define XTK_NAV_ACTYPE_MASK             (1ull << 15u)
#define XTK_NAV_AACCEL_MASK             (1ull << 16u)
#define XTK_NAV_AKEY_MASK               (1ull << 17u)
#define XTK_NAV_ALANDMARK_MASK          (1ull << 18u)
#define XTK_NAV_ALANDNAME_MASK          (1ull << 19u)
#define XTK_NAV_ALIVE_MASK              (1ull << 20u)
#define XTK_NAV_AHEADING_MASK           (1ull << 21u)
#define XTK_NAV_AVIEW_MASK              (1ull << 22u)
#define XTK_NAV_AREQUIRED_MASK          (1ull << 23u)
#define XTK_NAV_AVALID_MASK             (1ull << 24u)
#define XTK_NAV_APERIPHERAL_MASK        (1ull << 25u)
#define XTK_NAV_ADIALOG_MASK            (1ull << 26u)
#define XTK_NAV_APOS_MASK               (1ull << 27u)
#define XTK_NAV_ASIZE_MASK              (1ull << 28u)
#define XTK_NAV_ALEVEL_MASK             (1ull << 29u)
#define XTK_NAV_ACULTURE_MASK           (1ull << 30u)
#define XTK_NAV_ALABEL_MASK             (1ull << 31u)
#define XTK_NAV_ADESCRIBED_MASK         (1ull << 32u)
#define XTK_NAV_AFLOWSTO_MASK           (1ull << 33u)
#define XTK_NAV_AFLOWSFROM_MASK         (1ull << 34u)
#define XTK_NAV_ACONTROLS_MASK          (1ull << 35u)
#define XTK_NAV_ENABLED_MASK            (1ull << 36u)
#define XTK_NAV_SEL_MASK                (1ull << 37u)
#define XTK_NAV_DISPLAY_MASK            (1ull << 38u)
#define XTK_NAV_SETTINGS_VISIBLE_MASK   (1ull << 39u)
#define XTK_NAV_PANE_TITLE_MASK         (1ull << 40u)
#define XTK_NAV_ALWAYS_SHOW_HEADER_MASK (1ull << 41u)
#define XTK_NAV_BACK_BUTTON_MASK        (1ull << 42u)
#define XTK_NAV_BACK_ENABLED_MASK       (1ull << 43u)

typedef struct XtkListProps {
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
	char const     *aname;
	uint32_t        aname_len;
	char const     *aid;
	uint32_t        aid_len;
	char const     *ahelp;
	uint32_t        ahelp_len;
	char const     *adesc;
	uint32_t        adesc_len;
	char const     *astatus;
	uint32_t        astatus_len;
	char const     *aitem;
	uint32_t        aitem_len;
	char const     *actype;
	uint32_t        actype_len;
	char const     *aaccel;
	uint32_t        aaccel_len;
	char const     *akey;
	uint32_t        akey_len;
	XtkLandmark     alandmark;
	char const     *alandname;
	uint32_t        alandname_len;
	XtkLiveSetting  alive;
	XtkHeadingLevel aheading;
	XtkAccessView   aview;
	bool            arequired;
	bool            avalid;
	bool            aperipheral;
	bool            adialog;
	int32_t         apos;
	int32_t         asize;
	int32_t         alevel;
	int32_t         aculture;
	char const     *alabel;
	uint32_t        alabel_len;
	char const     *adescribed;
	uint32_t        adescribed_len;
	char const     *aflowsto;
	uint32_t        aflowsto_len;
	char const     *aflowsfrom;
	uint32_t        aflowsfrom_len;
	char const     *acontrols;
	uint32_t        acontrols_len;
	bool            enabled;
	int32_t         sel;
	int32_t         nitem;
	float           itemh;
	float           itemw;
	int32_t         ncol;
	XtkListSelMode  mode;
	int32_t         first;
	bool            rectsel;
} XtkListProps;

#define XTK_LIST_W_MASK           (1ull << 0u)
#define XTK_LIST_H_MASK           (1ull << 1u)
#define XTK_LIST_GROW_MASK        (1ull << 2u)
#define XTK_LIST_SELF_MASK        (1ull << 3u)
#define XTK_LIST_ML_MASK          (1ull << 4u)
#define XTK_LIST_MT_MASK          (1ull << 5u)
#define XTK_LIST_MR_MASK          (1ull << 6u)
#define XTK_LIST_MB_MASK          (1ull << 7u)
#define XTK_LIST_TIP_MASK         (1ull << 8u)
#define XTK_LIST_ANAME_MASK       (1ull << 9u)
#define XTK_LIST_AID_MASK         (1ull << 10u)
#define XTK_LIST_AHELP_MASK       (1ull << 11u)
#define XTK_LIST_ADESC_MASK       (1ull << 12u)
#define XTK_LIST_ASTATUS_MASK     (1ull << 13u)
#define XTK_LIST_AITEM_MASK       (1ull << 14u)
#define XTK_LIST_ACTYPE_MASK      (1ull << 15u)
#define XTK_LIST_AACCEL_MASK      (1ull << 16u)
#define XTK_LIST_AKEY_MASK        (1ull << 17u)
#define XTK_LIST_ALANDMARK_MASK   (1ull << 18u)
#define XTK_LIST_ALANDNAME_MASK   (1ull << 19u)
#define XTK_LIST_ALIVE_MASK       (1ull << 20u)
#define XTK_LIST_AHEADING_MASK    (1ull << 21u)
#define XTK_LIST_AVIEW_MASK       (1ull << 22u)
#define XTK_LIST_AREQUIRED_MASK   (1ull << 23u)
#define XTK_LIST_AVALID_MASK      (1ull << 24u)
#define XTK_LIST_APERIPHERAL_MASK (1ull << 25u)
#define XTK_LIST_ADIALOG_MASK     (1ull << 26u)
#define XTK_LIST_APOS_MASK        (1ull << 27u)
#define XTK_LIST_ASIZE_MASK       (1ull << 28u)
#define XTK_LIST_ALEVEL_MASK      (1ull << 29u)
#define XTK_LIST_ACULTURE_MASK    (1ull << 30u)
#define XTK_LIST_ALABEL_MASK      (1ull << 31u)
#define XTK_LIST_ADESCRIBED_MASK  (1ull << 32u)
#define XTK_LIST_AFLOWSTO_MASK    (1ull << 33u)
#define XTK_LIST_AFLOWSFROM_MASK  (1ull << 34u)
#define XTK_LIST_ACONTROLS_MASK   (1ull << 35u)
#define XTK_LIST_ENABLED_MASK     (1ull << 36u)
#define XTK_LIST_SEL_MASK         (1ull << 37u)
#define XTK_LIST_NITEM_MASK       (1ull << 38u)
#define XTK_LIST_ITEMH_MASK       (1ull << 39u)
#define XTK_LIST_ITEMW_MASK       (1ull << 40u)
#define XTK_LIST_NCOL_MASK        (1ull << 41u)
#define XTK_LIST_MODE_MASK        (1ull << 42u)
#define XTK_LIST_FIRST_MASK       (1ull << 43u)
#define XTK_LIST_RECTSEL_MASK     (1ull << 44u)

typedef struct XtkRadioGroupProps {
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
	char const     *aname;
	uint32_t        aname_len;
	char const     *aid;
	uint32_t        aid_len;
	char const     *ahelp;
	uint32_t        ahelp_len;
	char const     *adesc;
	uint32_t        adesc_len;
	char const     *astatus;
	uint32_t        astatus_len;
	char const     *aitem;
	uint32_t        aitem_len;
	char const     *actype;
	uint32_t        actype_len;
	char const     *aaccel;
	uint32_t        aaccel_len;
	char const     *akey;
	uint32_t        akey_len;
	XtkLandmark     alandmark;
	char const     *alandname;
	uint32_t        alandname_len;
	XtkLiveSetting  alive;
	XtkHeadingLevel aheading;
	XtkAccessView   aview;
	bool            arequired;
	bool            avalid;
	bool            aperipheral;
	bool            adialog;
	int32_t         apos;
	int32_t         asize;
	int32_t         alevel;
	int32_t         aculture;
	char const     *alabel;
	uint32_t        alabel_len;
	char const     *adescribed;
	uint32_t        adescribed_len;
	char const     *aflowsto;
	uint32_t        aflowsto_len;
	char const     *aflowsfrom;
	uint32_t        aflowsfrom_len;
	char const     *acontrols;
	uint32_t        acontrols_len;
	bool            enabled;
	int32_t         sel;
	int32_t         nitem;
	int32_t         ncol;
} XtkRadioGroupProps;

#define XTK_RADIOGROUP_W_MASK           (1ull << 0u)
#define XTK_RADIOGROUP_H_MASK           (1ull << 1u)
#define XTK_RADIOGROUP_GROW_MASK        (1ull << 2u)
#define XTK_RADIOGROUP_SELF_MASK        (1ull << 3u)
#define XTK_RADIOGROUP_ML_MASK          (1ull << 4u)
#define XTK_RADIOGROUP_MT_MASK          (1ull << 5u)
#define XTK_RADIOGROUP_MR_MASK          (1ull << 6u)
#define XTK_RADIOGROUP_MB_MASK          (1ull << 7u)
#define XTK_RADIOGROUP_TIP_MASK         (1ull << 8u)
#define XTK_RADIOGROUP_ANAME_MASK       (1ull << 9u)
#define XTK_RADIOGROUP_AID_MASK         (1ull << 10u)
#define XTK_RADIOGROUP_AHELP_MASK       (1ull << 11u)
#define XTK_RADIOGROUP_ADESC_MASK       (1ull << 12u)
#define XTK_RADIOGROUP_ASTATUS_MASK     (1ull << 13u)
#define XTK_RADIOGROUP_AITEM_MASK       (1ull << 14u)
#define XTK_RADIOGROUP_ACTYPE_MASK      (1ull << 15u)
#define XTK_RADIOGROUP_AACCEL_MASK      (1ull << 16u)
#define XTK_RADIOGROUP_AKEY_MASK        (1ull << 17u)
#define XTK_RADIOGROUP_ALANDMARK_MASK   (1ull << 18u)
#define XTK_RADIOGROUP_ALANDNAME_MASK   (1ull << 19u)
#define XTK_RADIOGROUP_ALIVE_MASK       (1ull << 20u)
#define XTK_RADIOGROUP_AHEADING_MASK    (1ull << 21u)
#define XTK_RADIOGROUP_AVIEW_MASK       (1ull << 22u)
#define XTK_RADIOGROUP_AREQUIRED_MASK   (1ull << 23u)
#define XTK_RADIOGROUP_AVALID_MASK      (1ull << 24u)
#define XTK_RADIOGROUP_APERIPHERAL_MASK (1ull << 25u)
#define XTK_RADIOGROUP_ADIALOG_MASK     (1ull << 26u)
#define XTK_RADIOGROUP_APOS_MASK        (1ull << 27u)
#define XTK_RADIOGROUP_ASIZE_MASK       (1ull << 28u)
#define XTK_RADIOGROUP_ALEVEL_MASK      (1ull << 29u)
#define XTK_RADIOGROUP_ACULTURE_MASK    (1ull << 30u)
#define XTK_RADIOGROUP_ALABEL_MASK      (1ull << 31u)
#define XTK_RADIOGROUP_ADESCRIBED_MASK  (1ull << 32u)
#define XTK_RADIOGROUP_AFLOWSTO_MASK    (1ull << 33u)
#define XTK_RADIOGROUP_AFLOWSFROM_MASK  (1ull << 34u)
#define XTK_RADIOGROUP_ACONTROLS_MASK   (1ull << 35u)
#define XTK_RADIOGROUP_ENABLED_MASK     (1ull << 36u)
#define XTK_RADIOGROUP_SEL_MASK         (1ull << 37u)
#define XTK_RADIOGROUP_NITEM_MASK       (1ull << 38u)
#define XTK_RADIOGROUP_NCOL_MASK        (1ull << 39u)

typedef struct XtkTreeProps {
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
	char const     *aname;
	uint32_t        aname_len;
	char const     *aid;
	uint32_t        aid_len;
	char const     *ahelp;
	uint32_t        ahelp_len;
	char const     *adesc;
	uint32_t        adesc_len;
	char const     *astatus;
	uint32_t        astatus_len;
	char const     *aitem;
	uint32_t        aitem_len;
	char const     *actype;
	uint32_t        actype_len;
	char const     *aaccel;
	uint32_t        aaccel_len;
	char const     *akey;
	uint32_t        akey_len;
	XtkLandmark     alandmark;
	char const     *alandname;
	uint32_t        alandname_len;
	XtkLiveSetting  alive;
	XtkHeadingLevel aheading;
	XtkAccessView   aview;
	bool            arequired;
	bool            avalid;
	bool            aperipheral;
	bool            adialog;
	int32_t         apos;
	int32_t         asize;
	int32_t         alevel;
	int32_t         aculture;
	char const     *alabel;
	uint32_t        alabel_len;
	char const     *adescribed;
	uint32_t        adescribed_len;
	char const     *aflowsto;
	uint32_t        aflowsto_len;
	char const     *aflowsfrom;
	uint32_t        aflowsfrom_len;
	char const     *acontrols;
	uint32_t        acontrols_len;
	bool            enabled;
	int32_t         sel;
	int32_t         nitem;
	float           itemh;
} XtkTreeProps;

#define XTK_TREE_W_MASK           (1ull << 0u)
#define XTK_TREE_H_MASK           (1ull << 1u)
#define XTK_TREE_GROW_MASK        (1ull << 2u)
#define XTK_TREE_SELF_MASK        (1ull << 3u)
#define XTK_TREE_ML_MASK          (1ull << 4u)
#define XTK_TREE_MT_MASK          (1ull << 5u)
#define XTK_TREE_MR_MASK          (1ull << 6u)
#define XTK_TREE_MB_MASK          (1ull << 7u)
#define XTK_TREE_TIP_MASK         (1ull << 8u)
#define XTK_TREE_ANAME_MASK       (1ull << 9u)
#define XTK_TREE_AID_MASK         (1ull << 10u)
#define XTK_TREE_AHELP_MASK       (1ull << 11u)
#define XTK_TREE_ADESC_MASK       (1ull << 12u)
#define XTK_TREE_ASTATUS_MASK     (1ull << 13u)
#define XTK_TREE_AITEM_MASK       (1ull << 14u)
#define XTK_TREE_ACTYPE_MASK      (1ull << 15u)
#define XTK_TREE_AACCEL_MASK      (1ull << 16u)
#define XTK_TREE_AKEY_MASK        (1ull << 17u)
#define XTK_TREE_ALANDMARK_MASK   (1ull << 18u)
#define XTK_TREE_ALANDNAME_MASK   (1ull << 19u)
#define XTK_TREE_ALIVE_MASK       (1ull << 20u)
#define XTK_TREE_AHEADING_MASK    (1ull << 21u)
#define XTK_TREE_AVIEW_MASK       (1ull << 22u)
#define XTK_TREE_AREQUIRED_MASK   (1ull << 23u)
#define XTK_TREE_AVALID_MASK      (1ull << 24u)
#define XTK_TREE_APERIPHERAL_MASK (1ull << 25u)
#define XTK_TREE_ADIALOG_MASK     (1ull << 26u)
#define XTK_TREE_APOS_MASK        (1ull << 27u)
#define XTK_TREE_ASIZE_MASK       (1ull << 28u)
#define XTK_TREE_ALEVEL_MASK      (1ull << 29u)
#define XTK_TREE_ACULTURE_MASK    (1ull << 30u)
#define XTK_TREE_ALABEL_MASK      (1ull << 31u)
#define XTK_TREE_ADESCRIBED_MASK  (1ull << 32u)
#define XTK_TREE_AFLOWSTO_MASK    (1ull << 33u)
#define XTK_TREE_AFLOWSFROM_MASK  (1ull << 34u)
#define XTK_TREE_ACONTROLS_MASK   (1ull << 35u)
#define XTK_TREE_ENABLED_MASK     (1ull << 36u)
#define XTK_TREE_SEL_MASK         (1ull << 37u)
#define XTK_TREE_NITEM_MASK       (1ull << 38u)
#define XTK_TREE_ITEMH_MASK       (1ull << 39u)

typedef struct XtkComboProps {
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
	char const     *aname;
	uint32_t        aname_len;
	char const     *aid;
	uint32_t        aid_len;
	char const     *ahelp;
	uint32_t        ahelp_len;
	char const     *adesc;
	uint32_t        adesc_len;
	char const     *astatus;
	uint32_t        astatus_len;
	char const     *aitem;
	uint32_t        aitem_len;
	char const     *actype;
	uint32_t        actype_len;
	char const     *aaccel;
	uint32_t        aaccel_len;
	char const     *akey;
	uint32_t        akey_len;
	XtkLandmark     alandmark;
	char const     *alandname;
	uint32_t        alandname_len;
	XtkLiveSetting  alive;
	XtkHeadingLevel aheading;
	XtkAccessView   aview;
	bool            arequired;
	bool            avalid;
	bool            aperipheral;
	bool            adialog;
	int32_t         apos;
	int32_t         asize;
	int32_t         alevel;
	int32_t         aculture;
	char const     *alabel;
	uint32_t        alabel_len;
	char const     *adescribed;
	uint32_t        adescribed_len;
	char const     *aflowsto;
	uint32_t        aflowsto_len;
	char const     *aflowsfrom;
	uint32_t        aflowsfrom_len;
	char const     *acontrols;
	uint32_t        acontrols_len;
	bool            enabled;
	char const     *placeholder;
	uint32_t        placeholder_len;
	int32_t         sel;
	char const     *text;
	uint32_t        text_len;
	bool            editable;
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
#define XTK_COMBO_ANAME_MASK       (1ull << 9u)
#define XTK_COMBO_AID_MASK         (1ull << 10u)
#define XTK_COMBO_AHELP_MASK       (1ull << 11u)
#define XTK_COMBO_ADESC_MASK       (1ull << 12u)
#define XTK_COMBO_ASTATUS_MASK     (1ull << 13u)
#define XTK_COMBO_AITEM_MASK       (1ull << 14u)
#define XTK_COMBO_ACTYPE_MASK      (1ull << 15u)
#define XTK_COMBO_AACCEL_MASK      (1ull << 16u)
#define XTK_COMBO_AKEY_MASK        (1ull << 17u)
#define XTK_COMBO_ALANDMARK_MASK   (1ull << 18u)
#define XTK_COMBO_ALANDNAME_MASK   (1ull << 19u)
#define XTK_COMBO_ALIVE_MASK       (1ull << 20u)
#define XTK_COMBO_AHEADING_MASK    (1ull << 21u)
#define XTK_COMBO_AVIEW_MASK       (1ull << 22u)
#define XTK_COMBO_AREQUIRED_MASK   (1ull << 23u)
#define XTK_COMBO_AVALID_MASK      (1ull << 24u)
#define XTK_COMBO_APERIPHERAL_MASK (1ull << 25u)
#define XTK_COMBO_ADIALOG_MASK     (1ull << 26u)
#define XTK_COMBO_APOS_MASK        (1ull << 27u)
#define XTK_COMBO_ASIZE_MASK       (1ull << 28u)
#define XTK_COMBO_ALEVEL_MASK      (1ull << 29u)
#define XTK_COMBO_ACULTURE_MASK    (1ull << 30u)
#define XTK_COMBO_ALABEL_MASK      (1ull << 31u)
#define XTK_COMBO_ADESCRIBED_MASK  (1ull << 32u)
#define XTK_COMBO_AFLOWSTO_MASK    (1ull << 33u)
#define XTK_COMBO_AFLOWSFROM_MASK  (1ull << 34u)
#define XTK_COMBO_ACONTROLS_MASK   (1ull << 35u)
#define XTK_COMBO_ENABLED_MASK     (1ull << 36u)
#define XTK_COMBO_PLACEHOLDER_MASK (1ull << 37u)
#define XTK_COMBO_SEL_MASK         (1ull << 38u)
#define XTK_COMBO_TEXT_MASK        (1ull << 39u)
#define XTK_COMBO_EDITABLE_MASK    (1ull << 40u)

typedef struct XtkOverlayProps {
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
	char const     *text;
	uint32_t        text_len;
	char const     *tip;
	uint32_t        tip_len;
	char const     *aname;
	uint32_t        aname_len;
	char const     *aid;
	uint32_t        aid_len;
	char const     *ahelp;
	uint32_t        ahelp_len;
	char const     *adesc;
	uint32_t        adesc_len;
	char const     *astatus;
	uint32_t        astatus_len;
	char const     *aitem;
	uint32_t        aitem_len;
	char const     *actype;
	uint32_t        actype_len;
	char const     *aaccel;
	uint32_t        aaccel_len;
	char const     *akey;
	uint32_t        akey_len;
	XtkLandmark     alandmark;
	char const     *alandname;
	uint32_t        alandname_len;
	XtkLiveSetting  alive;
	XtkHeadingLevel aheading;
	XtkAccessView   aview;
	bool            arequired;
	bool            avalid;
	bool            aperipheral;
	bool            adialog;
	int32_t         apos;
	int32_t         asize;
	int32_t         alevel;
	int32_t         aculture;
	char const     *alabel;
	uint32_t        alabel_len;
	char const     *adescribed;
	uint32_t        adescribed_len;
	char const     *aflowsto;
	uint32_t        aflowsto_len;
	char const     *aflowsfrom;
	uint32_t        aflowsfrom_len;
	char const     *acontrols;
	uint32_t        acontrols_len;
	bool            open;
	bool            enabled;
} XtkOverlayProps;

#define XTK_OVERLAY_W_MASK           (1ull << 0u)
#define XTK_OVERLAY_H_MASK           (1ull << 1u)
#define XTK_OVERLAY_GROW_MASK        (1ull << 2u)
#define XTK_OVERLAY_SELF_MASK        (1ull << 3u)
#define XTK_OVERLAY_ML_MASK          (1ull << 4u)
#define XTK_OVERLAY_MT_MASK          (1ull << 5u)
#define XTK_OVERLAY_MR_MASK          (1ull << 6u)
#define XTK_OVERLAY_MB_MASK          (1ull << 7u)
#define XTK_OVERLAY_TEXT_MASK        (1ull << 8u)
#define XTK_OVERLAY_TIP_MASK         (1ull << 9u)
#define XTK_OVERLAY_ANAME_MASK       (1ull << 10u)
#define XTK_OVERLAY_AID_MASK         (1ull << 11u)
#define XTK_OVERLAY_AHELP_MASK       (1ull << 12u)
#define XTK_OVERLAY_ADESC_MASK       (1ull << 13u)
#define XTK_OVERLAY_ASTATUS_MASK     (1ull << 14u)
#define XTK_OVERLAY_AITEM_MASK       (1ull << 15u)
#define XTK_OVERLAY_ACTYPE_MASK      (1ull << 16u)
#define XTK_OVERLAY_AACCEL_MASK      (1ull << 17u)
#define XTK_OVERLAY_AKEY_MASK        (1ull << 18u)
#define XTK_OVERLAY_ALANDMARK_MASK   (1ull << 19u)
#define XTK_OVERLAY_ALANDNAME_MASK   (1ull << 20u)
#define XTK_OVERLAY_ALIVE_MASK       (1ull << 21u)
#define XTK_OVERLAY_AHEADING_MASK    (1ull << 22u)
#define XTK_OVERLAY_AVIEW_MASK       (1ull << 23u)
#define XTK_OVERLAY_AREQUIRED_MASK   (1ull << 24u)
#define XTK_OVERLAY_AVALID_MASK      (1ull << 25u)
#define XTK_OVERLAY_APERIPHERAL_MASK (1ull << 26u)
#define XTK_OVERLAY_ADIALOG_MASK     (1ull << 27u)
#define XTK_OVERLAY_APOS_MASK        (1ull << 28u)
#define XTK_OVERLAY_ASIZE_MASK       (1ull << 29u)
#define XTK_OVERLAY_ALEVEL_MASK      (1ull << 30u)
#define XTK_OVERLAY_ACULTURE_MASK    (1ull << 31u)
#define XTK_OVERLAY_ALABEL_MASK      (1ull << 32u)
#define XTK_OVERLAY_ADESCRIBED_MASK  (1ull << 33u)
#define XTK_OVERLAY_AFLOWSTO_MASK    (1ull << 34u)
#define XTK_OVERLAY_AFLOWSFROM_MASK  (1ull << 35u)
#define XTK_OVERLAY_ACONTROLS_MASK   (1ull << 36u)
#define XTK_OVERLAY_OPEN_MASK        (1ull << 37u)
#define XTK_OVERLAY_ENABLED_MASK     (1ull << 38u)

typedef struct XtkItemsViewProps {
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
	char const     *aname;
	uint32_t        aname_len;
	char const     *aid;
	uint32_t        aid_len;
	char const     *ahelp;
	uint32_t        ahelp_len;
	char const     *adesc;
	uint32_t        adesc_len;
	char const     *astatus;
	uint32_t        astatus_len;
	char const     *aitem;
	uint32_t        aitem_len;
	char const     *actype;
	uint32_t        actype_len;
	char const     *aaccel;
	uint32_t        aaccel_len;
	char const     *akey;
	uint32_t        akey_len;
	XtkLandmark     alandmark;
	char const     *alandname;
	uint32_t        alandname_len;
	XtkLiveSetting  alive;
	XtkHeadingLevel aheading;
	XtkAccessView   aview;
	bool            arequired;
	bool            avalid;
	bool            aperipheral;
	bool            adialog;
	int32_t         apos;
	int32_t         asize;
	int32_t         alevel;
	int32_t         aculture;
	char const     *alabel;
	uint32_t        alabel_len;
	char const     *adescribed;
	uint32_t        adescribed_len;
	char const     *aflowsto;
	uint32_t        aflowsto_len;
	char const     *aflowsfrom;
	uint32_t        aflowsfrom_len;
	char const     *acontrols;
	uint32_t        acontrols_len;
	bool            enabled;
	int32_t         sel;
	int32_t         nitem;
	float           itemh;
	float           itemw;
	int32_t         ncol;
	XtkListSelMode  mode;
	bool            invoked;
	int32_t         first;
} XtkItemsViewProps;

#define XTK_ITEMSVIEW_W_MASK           (1ull << 0u)
#define XTK_ITEMSVIEW_H_MASK           (1ull << 1u)
#define XTK_ITEMSVIEW_GROW_MASK        (1ull << 2u)
#define XTK_ITEMSVIEW_SELF_MASK        (1ull << 3u)
#define XTK_ITEMSVIEW_ML_MASK          (1ull << 4u)
#define XTK_ITEMSVIEW_MT_MASK          (1ull << 5u)
#define XTK_ITEMSVIEW_MR_MASK          (1ull << 6u)
#define XTK_ITEMSVIEW_MB_MASK          (1ull << 7u)
#define XTK_ITEMSVIEW_TIP_MASK         (1ull << 8u)
#define XTK_ITEMSVIEW_ANAME_MASK       (1ull << 9u)
#define XTK_ITEMSVIEW_AID_MASK         (1ull << 10u)
#define XTK_ITEMSVIEW_AHELP_MASK       (1ull << 11u)
#define XTK_ITEMSVIEW_ADESC_MASK       (1ull << 12u)
#define XTK_ITEMSVIEW_ASTATUS_MASK     (1ull << 13u)
#define XTK_ITEMSVIEW_AITEM_MASK       (1ull << 14u)
#define XTK_ITEMSVIEW_ACTYPE_MASK      (1ull << 15u)
#define XTK_ITEMSVIEW_AACCEL_MASK      (1ull << 16u)
#define XTK_ITEMSVIEW_AKEY_MASK        (1ull << 17u)
#define XTK_ITEMSVIEW_ALANDMARK_MASK   (1ull << 18u)
#define XTK_ITEMSVIEW_ALANDNAME_MASK   (1ull << 19u)
#define XTK_ITEMSVIEW_ALIVE_MASK       (1ull << 20u)
#define XTK_ITEMSVIEW_AHEADING_MASK    (1ull << 21u)
#define XTK_ITEMSVIEW_AVIEW_MASK       (1ull << 22u)
#define XTK_ITEMSVIEW_AREQUIRED_MASK   (1ull << 23u)
#define XTK_ITEMSVIEW_AVALID_MASK      (1ull << 24u)
#define XTK_ITEMSVIEW_APERIPHERAL_MASK (1ull << 25u)
#define XTK_ITEMSVIEW_ADIALOG_MASK     (1ull << 26u)
#define XTK_ITEMSVIEW_APOS_MASK        (1ull << 27u)
#define XTK_ITEMSVIEW_ASIZE_MASK       (1ull << 28u)
#define XTK_ITEMSVIEW_ALEVEL_MASK      (1ull << 29u)
#define XTK_ITEMSVIEW_ACULTURE_MASK    (1ull << 30u)
#define XTK_ITEMSVIEW_ALABEL_MASK      (1ull << 31u)
#define XTK_ITEMSVIEW_ADESCRIBED_MASK  (1ull << 32u)
#define XTK_ITEMSVIEW_AFLOWSTO_MASK    (1ull << 33u)
#define XTK_ITEMSVIEW_AFLOWSFROM_MASK  (1ull << 34u)
#define XTK_ITEMSVIEW_ACONTROLS_MASK   (1ull << 35u)
#define XTK_ITEMSVIEW_ENABLED_MASK     (1ull << 36u)
#define XTK_ITEMSVIEW_SEL_MASK         (1ull << 37u)
#define XTK_ITEMSVIEW_NITEM_MASK       (1ull << 38u)
#define XTK_ITEMSVIEW_ITEMH_MASK       (1ull << 39u)
#define XTK_ITEMSVIEW_ITEMW_MASK       (1ull << 40u)
#define XTK_ITEMSVIEW_NCOL_MASK        (1ull << 41u)
#define XTK_ITEMSVIEW_MODE_MASK        (1ull << 42u)
#define XTK_ITEMSVIEW_INVOKED_MASK     (1ull << 43u)
#define XTK_ITEMSVIEW_FIRST_MASK       (1ull << 44u)

typedef struct XtkExpanderProps {
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
	char const     *text;
	uint32_t        text_len;
	char const     *tip;
	uint32_t        tip_len;
	char const     *aname;
	uint32_t        aname_len;
	char const     *aid;
	uint32_t        aid_len;
	char const     *ahelp;
	uint32_t        ahelp_len;
	char const     *adesc;
	uint32_t        adesc_len;
	char const     *astatus;
	uint32_t        astatus_len;
	char const     *aitem;
	uint32_t        aitem_len;
	char const     *actype;
	uint32_t        actype_len;
	char const     *aaccel;
	uint32_t        aaccel_len;
	char const     *akey;
	uint32_t        akey_len;
	XtkLandmark     alandmark;
	char const     *alandname;
	uint32_t        alandname_len;
	XtkLiveSetting  alive;
	XtkHeadingLevel aheading;
	XtkAccessView   aview;
	bool            arequired;
	bool            avalid;
	bool            aperipheral;
	bool            adialog;
	int32_t         apos;
	int32_t         asize;
	int32_t         alevel;
	int32_t         aculture;
	char const     *alabel;
	uint32_t        alabel_len;
	char const     *adescribed;
	uint32_t        adescribed_len;
	char const     *aflowsto;
	uint32_t        aflowsto_len;
	char const     *aflowsfrom;
	uint32_t        aflowsfrom_len;
	char const     *acontrols;
	uint32_t        acontrols_len;
	bool            expanded;
	float           contenth;
} XtkExpanderProps;

#define XTK_EXPANDER_W_MASK           (1ull << 0u)
#define XTK_EXPANDER_H_MASK           (1ull << 1u)
#define XTK_EXPANDER_GROW_MASK        (1ull << 2u)
#define XTK_EXPANDER_SELF_MASK        (1ull << 3u)
#define XTK_EXPANDER_ML_MASK          (1ull << 4u)
#define XTK_EXPANDER_MT_MASK          (1ull << 5u)
#define XTK_EXPANDER_MR_MASK          (1ull << 6u)
#define XTK_EXPANDER_MB_MASK          (1ull << 7u)
#define XTK_EXPANDER_TEXT_MASK        (1ull << 8u)
#define XTK_EXPANDER_TIP_MASK         (1ull << 9u)
#define XTK_EXPANDER_ANAME_MASK       (1ull << 10u)
#define XTK_EXPANDER_AID_MASK         (1ull << 11u)
#define XTK_EXPANDER_AHELP_MASK       (1ull << 12u)
#define XTK_EXPANDER_ADESC_MASK       (1ull << 13u)
#define XTK_EXPANDER_ASTATUS_MASK     (1ull << 14u)
#define XTK_EXPANDER_AITEM_MASK       (1ull << 15u)
#define XTK_EXPANDER_ACTYPE_MASK      (1ull << 16u)
#define XTK_EXPANDER_AACCEL_MASK      (1ull << 17u)
#define XTK_EXPANDER_AKEY_MASK        (1ull << 18u)
#define XTK_EXPANDER_ALANDMARK_MASK   (1ull << 19u)
#define XTK_EXPANDER_ALANDNAME_MASK   (1ull << 20u)
#define XTK_EXPANDER_ALIVE_MASK       (1ull << 21u)
#define XTK_EXPANDER_AHEADING_MASK    (1ull << 22u)
#define XTK_EXPANDER_AVIEW_MASK       (1ull << 23u)
#define XTK_EXPANDER_AREQUIRED_MASK   (1ull << 24u)
#define XTK_EXPANDER_AVALID_MASK      (1ull << 25u)
#define XTK_EXPANDER_APERIPHERAL_MASK (1ull << 26u)
#define XTK_EXPANDER_ADIALOG_MASK     (1ull << 27u)
#define XTK_EXPANDER_APOS_MASK        (1ull << 28u)
#define XTK_EXPANDER_ASIZE_MASK       (1ull << 29u)
#define XTK_EXPANDER_ALEVEL_MASK      (1ull << 30u)
#define XTK_EXPANDER_ACULTURE_MASK    (1ull << 31u)
#define XTK_EXPANDER_ALABEL_MASK      (1ull << 32u)
#define XTK_EXPANDER_ADESCRIBED_MASK  (1ull << 33u)
#define XTK_EXPANDER_AFLOWSTO_MASK    (1ull << 34u)
#define XTK_EXPANDER_AFLOWSFROM_MASK  (1ull << 35u)
#define XTK_EXPANDER_ACONTROLS_MASK   (1ull << 36u)
#define XTK_EXPANDER_EXPANDED_MASK    (1ull << 37u)
#define XTK_EXPANDER_CONTENTH_MASK    (1ull << 38u)

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
	char const        *aname;
	uint32_t           aname_len;
	char const        *aid;
	uint32_t           aid_len;
	char const        *ahelp;
	uint32_t           ahelp_len;
	char const        *adesc;
	uint32_t           adesc_len;
	char const        *astatus;
	uint32_t           astatus_len;
	char const        *aitem;
	uint32_t           aitem_len;
	char const        *actype;
	uint32_t           actype_len;
	char const        *aaccel;
	uint32_t           aaccel_len;
	char const        *akey;
	uint32_t           akey_len;
	XtkLandmark        alandmark;
	char const        *alandname;
	uint32_t           alandname_len;
	XtkLiveSetting     alive;
	XtkHeadingLevel    aheading;
	XtkAccessView      aview;
	bool               arequired;
	bool               avalid;
	bool               aperipheral;
	bool               adialog;
	int32_t            apos;
	int32_t            asize;
	int32_t            alevel;
	int32_t            aculture;
	char const        *alabel;
	uint32_t           alabel_len;
	char const        *adescribed;
	uint32_t           adescribed_len;
	char const        *aflowsto;
	uint32_t           aflowsto_len;
	char const        *aflowsfrom;
	uint32_t           aflowsfrom_len;
	char const        *acontrols;
	uint32_t           acontrols_len;
	XtkInfoBarSeverity severity;
	bool               closable;
} XtkInfoBarProps;

#define XTK_INFOBAR_W_MASK           (1ull << 0u)
#define XTK_INFOBAR_H_MASK           (1ull << 1u)
#define XTK_INFOBAR_GROW_MASK        (1ull << 2u)
#define XTK_INFOBAR_SELF_MASK        (1ull << 3u)
#define XTK_INFOBAR_ML_MASK          (1ull << 4u)
#define XTK_INFOBAR_MT_MASK          (1ull << 5u)
#define XTK_INFOBAR_MR_MASK          (1ull << 6u)
#define XTK_INFOBAR_MB_MASK          (1ull << 7u)
#define XTK_INFOBAR_TEXT_MASK        (1ull << 8u)
#define XTK_INFOBAR_MESSAGE_MASK     (1ull << 9u)
#define XTK_INFOBAR_TIP_MASK         (1ull << 10u)
#define XTK_INFOBAR_ANAME_MASK       (1ull << 11u)
#define XTK_INFOBAR_AID_MASK         (1ull << 12u)
#define XTK_INFOBAR_AHELP_MASK       (1ull << 13u)
#define XTK_INFOBAR_ADESC_MASK       (1ull << 14u)
#define XTK_INFOBAR_ASTATUS_MASK     (1ull << 15u)
#define XTK_INFOBAR_AITEM_MASK       (1ull << 16u)
#define XTK_INFOBAR_ACTYPE_MASK      (1ull << 17u)
#define XTK_INFOBAR_AACCEL_MASK      (1ull << 18u)
#define XTK_INFOBAR_AKEY_MASK        (1ull << 19u)
#define XTK_INFOBAR_ALANDMARK_MASK   (1ull << 20u)
#define XTK_INFOBAR_ALANDNAME_MASK   (1ull << 21u)
#define XTK_INFOBAR_ALIVE_MASK       (1ull << 22u)
#define XTK_INFOBAR_AHEADING_MASK    (1ull << 23u)
#define XTK_INFOBAR_AVIEW_MASK       (1ull << 24u)
#define XTK_INFOBAR_AREQUIRED_MASK   (1ull << 25u)
#define XTK_INFOBAR_AVALID_MASK      (1ull << 26u)
#define XTK_INFOBAR_APERIPHERAL_MASK (1ull << 27u)
#define XTK_INFOBAR_ADIALOG_MASK     (1ull << 28u)
#define XTK_INFOBAR_APOS_MASK        (1ull << 29u)
#define XTK_INFOBAR_ASIZE_MASK       (1ull << 30u)
#define XTK_INFOBAR_ALEVEL_MASK      (1ull << 31u)
#define XTK_INFOBAR_ACULTURE_MASK    (1ull << 32u)
#define XTK_INFOBAR_ALABEL_MASK      (1ull << 33u)
#define XTK_INFOBAR_ADESCRIBED_MASK  (1ull << 34u)
#define XTK_INFOBAR_AFLOWSTO_MASK    (1ull << 35u)
#define XTK_INFOBAR_AFLOWSFROM_MASK  (1ull << 36u)
#define XTK_INFOBAR_ACONTROLS_MASK   (1ull << 37u)
#define XTK_INFOBAR_SEVERITY_MASK    (1ull << 38u)
#define XTK_INFOBAR_CLOSABLE_MASK    (1ull << 39u)

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
	char const      *aname;
	uint32_t         aname_len;
	char const      *aid;
	uint32_t         aid_len;
	char const      *ahelp;
	uint32_t         ahelp_len;
	char const      *adesc;
	uint32_t         adesc_len;
	char const      *astatus;
	uint32_t         astatus_len;
	char const      *aitem;
	uint32_t         aitem_len;
	char const      *actype;
	uint32_t         actype_len;
	char const      *aaccel;
	uint32_t         aaccel_len;
	char const      *akey;
	uint32_t         akey_len;
	XtkLandmark      alandmark;
	char const      *alandname;
	uint32_t         alandname_len;
	XtkLiveSetting   alive;
	XtkHeadingLevel  aheading;
	XtkAccessView    aview;
	bool             arequired;
	bool             avalid;
	bool             aperipheral;
	bool             adialog;
	int32_t          apos;
	int32_t          asize;
	int32_t          alevel;
	int32_t          aculture;
	char const      *alabel;
	uint32_t         alabel_len;
	char const      *adescribed;
	uint32_t         adescribed_len;
	char const      *aflowsto;
	uint32_t         aflowsto_len;
	char const      *aflowsfrom;
	uint32_t         aflowsfrom_len;
	char const      *acontrols;
	uint32_t         acontrols_len;
	XtkPullDirection direction;
	float            visualizer;
	float            threshold;
	bool             refreshing;
} XtkRefreshProps;

#define XTK_REFRESH_W_MASK           (1ull << 0u)
#define XTK_REFRESH_H_MASK           (1ull << 1u)
#define XTK_REFRESH_GROW_MASK        (1ull << 2u)
#define XTK_REFRESH_SELF_MASK        (1ull << 3u)
#define XTK_REFRESH_ML_MASK          (1ull << 4u)
#define XTK_REFRESH_MT_MASK          (1ull << 5u)
#define XTK_REFRESH_MR_MASK          (1ull << 6u)
#define XTK_REFRESH_MB_MASK          (1ull << 7u)
#define XTK_REFRESH_TIP_MASK         (1ull << 8u)
#define XTK_REFRESH_ANAME_MASK       (1ull << 9u)
#define XTK_REFRESH_AID_MASK         (1ull << 10u)
#define XTK_REFRESH_AHELP_MASK       (1ull << 11u)
#define XTK_REFRESH_ADESC_MASK       (1ull << 12u)
#define XTK_REFRESH_ASTATUS_MASK     (1ull << 13u)
#define XTK_REFRESH_AITEM_MASK       (1ull << 14u)
#define XTK_REFRESH_ACTYPE_MASK      (1ull << 15u)
#define XTK_REFRESH_AACCEL_MASK      (1ull << 16u)
#define XTK_REFRESH_AKEY_MASK        (1ull << 17u)
#define XTK_REFRESH_ALANDMARK_MASK   (1ull << 18u)
#define XTK_REFRESH_ALANDNAME_MASK   (1ull << 19u)
#define XTK_REFRESH_ALIVE_MASK       (1ull << 20u)
#define XTK_REFRESH_AHEADING_MASK    (1ull << 21u)
#define XTK_REFRESH_AVIEW_MASK       (1ull << 22u)
#define XTK_REFRESH_AREQUIRED_MASK   (1ull << 23u)
#define XTK_REFRESH_AVALID_MASK      (1ull << 24u)
#define XTK_REFRESH_APERIPHERAL_MASK (1ull << 25u)
#define XTK_REFRESH_ADIALOG_MASK     (1ull << 26u)
#define XTK_REFRESH_APOS_MASK        (1ull << 27u)
#define XTK_REFRESH_ASIZE_MASK       (1ull << 28u)
#define XTK_REFRESH_ALEVEL_MASK      (1ull << 29u)
#define XTK_REFRESH_ACULTURE_MASK    (1ull << 30u)
#define XTK_REFRESH_ALABEL_MASK      (1ull << 31u)
#define XTK_REFRESH_ADESCRIBED_MASK  (1ull << 32u)
#define XTK_REFRESH_AFLOWSTO_MASK    (1ull << 33u)
#define XTK_REFRESH_AFLOWSFROM_MASK  (1ull << 34u)
#define XTK_REFRESH_ACONTROLS_MASK   (1ull << 35u)
#define XTK_REFRESH_DIRECTION_MASK   (1ull << 36u)
#define XTK_REFRESH_VISUALIZER_MASK  (1ull << 37u)
#define XTK_REFRESH_THRESHOLD_MASK   (1ull << 38u)
#define XTK_REFRESH_REFRESHING_MASK  (1ull << 39u)

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
	char const       *aname;
	uint32_t          aname_len;
	char const       *aid;
	uint32_t          aid_len;
	char const       *ahelp;
	uint32_t          ahelp_len;
	char const       *adesc;
	uint32_t          adesc_len;
	char const       *astatus;
	uint32_t          astatus_len;
	char const       *aitem;
	uint32_t          aitem_len;
	char const       *actype;
	uint32_t          actype_len;
	char const       *aaccel;
	uint32_t          aaccel_len;
	char const       *akey;
	uint32_t          akey_len;
	XtkLandmark       alandmark;
	char const       *alandname;
	uint32_t          alandname_len;
	XtkLiveSetting    alive;
	XtkHeadingLevel   aheading;
	XtkAccessView     aview;
	bool              arequired;
	bool              avalid;
	bool              aperipheral;
	bool              adialog;
	int32_t           apos;
	int32_t           asize;
	int32_t           alevel;
	int32_t           aculture;
	char const       *alabel;
	uint32_t          alabel_len;
	char const       *adescribed;
	uint32_t          adescribed_len;
	char const       *aflowsto;
	uint32_t          aflowsto_len;
	char const       *aflowsfrom;
	uint32_t          aflowsfrom_len;
	char const       *acontrols;
	uint32_t          acontrols_len;
	int32_t           sel;
	XtkStackDirection dir;
} XtkFlipProps;

#define XTK_FLIP_W_MASK           (1ull << 0u)
#define XTK_FLIP_H_MASK           (1ull << 1u)
#define XTK_FLIP_GROW_MASK        (1ull << 2u)
#define XTK_FLIP_SELF_MASK        (1ull << 3u)
#define XTK_FLIP_ML_MASK          (1ull << 4u)
#define XTK_FLIP_MT_MASK          (1ull << 5u)
#define XTK_FLIP_MR_MASK          (1ull << 6u)
#define XTK_FLIP_MB_MASK          (1ull << 7u)
#define XTK_FLIP_TIP_MASK         (1ull << 8u)
#define XTK_FLIP_ANAME_MASK       (1ull << 9u)
#define XTK_FLIP_AID_MASK         (1ull << 10u)
#define XTK_FLIP_AHELP_MASK       (1ull << 11u)
#define XTK_FLIP_ADESC_MASK       (1ull << 12u)
#define XTK_FLIP_ASTATUS_MASK     (1ull << 13u)
#define XTK_FLIP_AITEM_MASK       (1ull << 14u)
#define XTK_FLIP_ACTYPE_MASK      (1ull << 15u)
#define XTK_FLIP_AACCEL_MASK      (1ull << 16u)
#define XTK_FLIP_AKEY_MASK        (1ull << 17u)
#define XTK_FLIP_ALANDMARK_MASK   (1ull << 18u)
#define XTK_FLIP_ALANDNAME_MASK   (1ull << 19u)
#define XTK_FLIP_ALIVE_MASK       (1ull << 20u)
#define XTK_FLIP_AHEADING_MASK    (1ull << 21u)
#define XTK_FLIP_AVIEW_MASK       (1ull << 22u)
#define XTK_FLIP_AREQUIRED_MASK   (1ull << 23u)
#define XTK_FLIP_AVALID_MASK      (1ull << 24u)
#define XTK_FLIP_APERIPHERAL_MASK (1ull << 25u)
#define XTK_FLIP_ADIALOG_MASK     (1ull << 26u)
#define XTK_FLIP_APOS_MASK        (1ull << 27u)
#define XTK_FLIP_ASIZE_MASK       (1ull << 28u)
#define XTK_FLIP_ALEVEL_MASK      (1ull << 29u)
#define XTK_FLIP_ACULTURE_MASK    (1ull << 30u)
#define XTK_FLIP_ALABEL_MASK      (1ull << 31u)
#define XTK_FLIP_ADESCRIBED_MASK  (1ull << 32u)
#define XTK_FLIP_AFLOWSTO_MASK    (1ull << 33u)
#define XTK_FLIP_AFLOWSFROM_MASK  (1ull << 34u)
#define XTK_FLIP_ACONTROLS_MASK   (1ull << 35u)
#define XTK_FLIP_SEL_MASK         (1ull << 36u)
#define XTK_FLIP_DIR_MASK         (1ull << 37u)

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
	char const       *aname;
	uint32_t          aname_len;
	char const       *aid;
	uint32_t          aid_len;
	char const       *ahelp;
	uint32_t          ahelp_len;
	char const       *adesc;
	uint32_t          adesc_len;
	char const       *astatus;
	uint32_t          astatus_len;
	char const       *aitem;
	uint32_t          aitem_len;
	char const       *actype;
	uint32_t          actype_len;
	char const       *aaccel;
	uint32_t          aaccel_len;
	char const       *akey;
	uint32_t          akey_len;
	XtkLandmark       alandmark;
	char const       *alandname;
	uint32_t          alandname_len;
	XtkLiveSetting    alive;
	XtkHeadingLevel   aheading;
	XtkAccessView     aview;
	bool              arequired;
	bool              avalid;
	bool              aperipheral;
	bool              adialog;
	int32_t           apos;
	int32_t           asize;
	int32_t           alevel;
	int32_t           aculture;
	char const       *alabel;
	uint32_t          alabel_len;
	char const       *adescribed;
	uint32_t          adescribed_len;
	char const       *aflowsto;
	uint32_t          aflowsto_len;
	char const       *aflowsfrom;
	uint32_t          aflowsfrom_len;
	char const       *acontrols;
	uint32_t          acontrols_len;
	int32_t           sel;
	int32_t           nitem;
	XtkStackDirection dir;
	int32_t           maxvisible;
	XtkPipsNavVis     nav;
} XtkPipsProps;

#define XTK_PIPS_W_MASK           (1ull << 0u)
#define XTK_PIPS_H_MASK           (1ull << 1u)
#define XTK_PIPS_GROW_MASK        (1ull << 2u)
#define XTK_PIPS_SELF_MASK        (1ull << 3u)
#define XTK_PIPS_ML_MASK          (1ull << 4u)
#define XTK_PIPS_MT_MASK          (1ull << 5u)
#define XTK_PIPS_MR_MASK          (1ull << 6u)
#define XTK_PIPS_MB_MASK          (1ull << 7u)
#define XTK_PIPS_TIP_MASK         (1ull << 8u)
#define XTK_PIPS_ANAME_MASK       (1ull << 9u)
#define XTK_PIPS_AID_MASK         (1ull << 10u)
#define XTK_PIPS_AHELP_MASK       (1ull << 11u)
#define XTK_PIPS_ADESC_MASK       (1ull << 12u)
#define XTK_PIPS_ASTATUS_MASK     (1ull << 13u)
#define XTK_PIPS_AITEM_MASK       (1ull << 14u)
#define XTK_PIPS_ACTYPE_MASK      (1ull << 15u)
#define XTK_PIPS_AACCEL_MASK      (1ull << 16u)
#define XTK_PIPS_AKEY_MASK        (1ull << 17u)
#define XTK_PIPS_ALANDMARK_MASK   (1ull << 18u)
#define XTK_PIPS_ALANDNAME_MASK   (1ull << 19u)
#define XTK_PIPS_ALIVE_MASK       (1ull << 20u)
#define XTK_PIPS_AHEADING_MASK    (1ull << 21u)
#define XTK_PIPS_AVIEW_MASK       (1ull << 22u)
#define XTK_PIPS_AREQUIRED_MASK   (1ull << 23u)
#define XTK_PIPS_AVALID_MASK      (1ull << 24u)
#define XTK_PIPS_APERIPHERAL_MASK (1ull << 25u)
#define XTK_PIPS_ADIALOG_MASK     (1ull << 26u)
#define XTK_PIPS_APOS_MASK        (1ull << 27u)
#define XTK_PIPS_ASIZE_MASK       (1ull << 28u)
#define XTK_PIPS_ALEVEL_MASK      (1ull << 29u)
#define XTK_PIPS_ACULTURE_MASK    (1ull << 30u)
#define XTK_PIPS_ALABEL_MASK      (1ull << 31u)
#define XTK_PIPS_ADESCRIBED_MASK  (1ull << 32u)
#define XTK_PIPS_AFLOWSTO_MASK    (1ull << 33u)
#define XTK_PIPS_AFLOWSFROM_MASK  (1ull << 34u)
#define XTK_PIPS_ACONTROLS_MASK   (1ull << 35u)
#define XTK_PIPS_SEL_MASK         (1ull << 36u)
#define XTK_PIPS_NITEM_MASK       (1ull << 37u)
#define XTK_PIPS_DIR_MASK         (1ull << 38u)
#define XTK_PIPS_MAXVISIBLE_MASK  (1ull << 39u)
#define XTK_PIPS_NAV_MASK         (1ull << 40u)

typedef struct XtkSuggestProps {
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
	char const     *text;
	uint32_t        text_len;
	char const     *tip;
	uint32_t        tip_len;
	char const     *aname;
	uint32_t        aname_len;
	char const     *aid;
	uint32_t        aid_len;
	char const     *ahelp;
	uint32_t        ahelp_len;
	char const     *adesc;
	uint32_t        adesc_len;
	char const     *astatus;
	uint32_t        astatus_len;
	char const     *aitem;
	uint32_t        aitem_len;
	char const     *actype;
	uint32_t        actype_len;
	char const     *aaccel;
	uint32_t        aaccel_len;
	char const     *akey;
	uint32_t        akey_len;
	XtkLandmark     alandmark;
	char const     *alandname;
	uint32_t        alandname_len;
	XtkLiveSetting  alive;
	XtkHeadingLevel aheading;
	XtkAccessView   aview;
	bool            arequired;
	bool            avalid;
	bool            aperipheral;
	bool            adialog;
	int32_t         apos;
	int32_t         asize;
	int32_t         alevel;
	int32_t         aculture;
	char const     *alabel;
	uint32_t        alabel_len;
	char const     *adescribed;
	uint32_t        adescribed_len;
	char const     *aflowsto;
	uint32_t        aflowsto_len;
	char const     *aflowsfrom;
	uint32_t        aflowsfrom_len;
	char const     *acontrols;
	uint32_t        acontrols_len;
	bool            enabled;
	char const     *placeholder;
	uint32_t        placeholder_len;
	char const     *icon;
	uint32_t        icon_len;
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
#define XTK_SUGGEST_ANAME_MASK       (1ull << 10u)
#define XTK_SUGGEST_AID_MASK         (1ull << 11u)
#define XTK_SUGGEST_AHELP_MASK       (1ull << 12u)
#define XTK_SUGGEST_ADESC_MASK       (1ull << 13u)
#define XTK_SUGGEST_ASTATUS_MASK     (1ull << 14u)
#define XTK_SUGGEST_AITEM_MASK       (1ull << 15u)
#define XTK_SUGGEST_ACTYPE_MASK      (1ull << 16u)
#define XTK_SUGGEST_AACCEL_MASK      (1ull << 17u)
#define XTK_SUGGEST_AKEY_MASK        (1ull << 18u)
#define XTK_SUGGEST_ALANDMARK_MASK   (1ull << 19u)
#define XTK_SUGGEST_ALANDNAME_MASK   (1ull << 20u)
#define XTK_SUGGEST_ALIVE_MASK       (1ull << 21u)
#define XTK_SUGGEST_AHEADING_MASK    (1ull << 22u)
#define XTK_SUGGEST_AVIEW_MASK       (1ull << 23u)
#define XTK_SUGGEST_AREQUIRED_MASK   (1ull << 24u)
#define XTK_SUGGEST_AVALID_MASK      (1ull << 25u)
#define XTK_SUGGEST_APERIPHERAL_MASK (1ull << 26u)
#define XTK_SUGGEST_ADIALOG_MASK     (1ull << 27u)
#define XTK_SUGGEST_APOS_MASK        (1ull << 28u)
#define XTK_SUGGEST_ASIZE_MASK       (1ull << 29u)
#define XTK_SUGGEST_ALEVEL_MASK      (1ull << 30u)
#define XTK_SUGGEST_ACULTURE_MASK    (1ull << 31u)
#define XTK_SUGGEST_ALABEL_MASK      (1ull << 32u)
#define XTK_SUGGEST_ADESCRIBED_MASK  (1ull << 33u)
#define XTK_SUGGEST_AFLOWSTO_MASK    (1ull << 34u)
#define XTK_SUGGEST_AFLOWSFROM_MASK  (1ull << 35u)
#define XTK_SUGGEST_ACONTROLS_MASK   (1ull << 36u)
#define XTK_SUGGEST_ENABLED_MASK     (1ull << 37u)
#define XTK_SUGGEST_PLACEHOLDER_MASK (1ull << 38u)
#define XTK_SUGGEST_ICON_MASK        (1ull << 39u)

typedef struct XtkBadgeProps {
	uint64_t        set;
	XtkChangeStamp  stamp;
	float           w;
	float           h;
	float           grow;
	float           shrink;
	XentFlexAlign   self;
	float           ml;
	float           mt;
	float           mr;
	float           mb;
	char const     *tip;
	uint32_t        tip_len;
	char const     *aname;
	uint32_t        aname_len;
	char const     *aid;
	uint32_t        aid_len;
	char const     *ahelp;
	uint32_t        ahelp_len;
	char const     *adesc;
	uint32_t        adesc_len;
	char const     *astatus;
	uint32_t        astatus_len;
	char const     *aitem;
	uint32_t        aitem_len;
	char const     *actype;
	uint32_t        actype_len;
	char const     *aaccel;
	uint32_t        aaccel_len;
	char const     *akey;
	uint32_t        akey_len;
	XtkLandmark     alandmark;
	char const     *alandname;
	uint32_t        alandname_len;
	XtkLiveSetting  alive;
	XtkHeadingLevel aheading;
	XtkAccessView   aview;
	bool            arequired;
	bool            avalid;
	bool            aperipheral;
	bool            adialog;
	int32_t         apos;
	int32_t         asize;
	int32_t         alevel;
	int32_t         aculture;
	char const     *alabel;
	uint32_t        alabel_len;
	char const     *adescribed;
	uint32_t        adescribed_len;
	char const     *aflowsto;
	uint32_t        aflowsto_len;
	char const     *aflowsfrom;
	uint32_t        aflowsfrom_len;
	char const     *acontrols;
	uint32_t        acontrols_len;
	XtkBadgeMode    badgemode;
	int32_t         value;
	char const     *icon;
	uint32_t        icon_len;
} XtkBadgeProps;

#define XTK_BADGE_W_MASK           (1ull << 0u)
#define XTK_BADGE_H_MASK           (1ull << 1u)
#define XTK_BADGE_GROW_MASK        (1ull << 2u)
#define XTK_BADGE_SHRINK_MASK      (1ull << 3u)
#define XTK_BADGE_SELF_MASK        (1ull << 4u)
#define XTK_BADGE_ML_MASK          (1ull << 5u)
#define XTK_BADGE_MT_MASK          (1ull << 6u)
#define XTK_BADGE_MR_MASK          (1ull << 7u)
#define XTK_BADGE_MB_MASK          (1ull << 8u)
#define XTK_BADGE_TIP_MASK         (1ull << 9u)
#define XTK_BADGE_ANAME_MASK       (1ull << 10u)
#define XTK_BADGE_AID_MASK         (1ull << 11u)
#define XTK_BADGE_AHELP_MASK       (1ull << 12u)
#define XTK_BADGE_ADESC_MASK       (1ull << 13u)
#define XTK_BADGE_ASTATUS_MASK     (1ull << 14u)
#define XTK_BADGE_AITEM_MASK       (1ull << 15u)
#define XTK_BADGE_ACTYPE_MASK      (1ull << 16u)
#define XTK_BADGE_AACCEL_MASK      (1ull << 17u)
#define XTK_BADGE_AKEY_MASK        (1ull << 18u)
#define XTK_BADGE_ALANDMARK_MASK   (1ull << 19u)
#define XTK_BADGE_ALANDNAME_MASK   (1ull << 20u)
#define XTK_BADGE_ALIVE_MASK       (1ull << 21u)
#define XTK_BADGE_AHEADING_MASK    (1ull << 22u)
#define XTK_BADGE_AVIEW_MASK       (1ull << 23u)
#define XTK_BADGE_AREQUIRED_MASK   (1ull << 24u)
#define XTK_BADGE_AVALID_MASK      (1ull << 25u)
#define XTK_BADGE_APERIPHERAL_MASK (1ull << 26u)
#define XTK_BADGE_ADIALOG_MASK     (1ull << 27u)
#define XTK_BADGE_APOS_MASK        (1ull << 28u)
#define XTK_BADGE_ASIZE_MASK       (1ull << 29u)
#define XTK_BADGE_ALEVEL_MASK      (1ull << 30u)
#define XTK_BADGE_ACULTURE_MASK    (1ull << 31u)
#define XTK_BADGE_ALABEL_MASK      (1ull << 32u)
#define XTK_BADGE_ADESCRIBED_MASK  (1ull << 33u)
#define XTK_BADGE_AFLOWSTO_MASK    (1ull << 34u)
#define XTK_BADGE_AFLOWSFROM_MASK  (1ull << 35u)
#define XTK_BADGE_ACONTROLS_MASK   (1ull << 36u)
#define XTK_BADGE_BADGEMODE_MASK   (1ull << 37u)
#define XTK_BADGE_VALUE_MASK       (1ull << 38u)
#define XTK_BADGE_ICON_MASK        (1ull << 39u)

typedef struct XtkDialogProps {
	uint64_t        set;
	XtkChangeStamp  stamp;
	float           w;
	float           h;
	float           grow;
	float           shrink;
	XentFlexAlign   self;
	float           ml;
	float           mt;
	float           mr;
	float           mb;
	char const     *tip;
	uint32_t        tip_len;
	char const     *aname;
	uint32_t        aname_len;
	char const     *aid;
	uint32_t        aid_len;
	char const     *ahelp;
	uint32_t        ahelp_len;
	char const     *adesc;
	uint32_t        adesc_len;
	char const     *astatus;
	uint32_t        astatus_len;
	char const     *aitem;
	uint32_t        aitem_len;
	char const     *actype;
	uint32_t        actype_len;
	char const     *aaccel;
	uint32_t        aaccel_len;
	char const     *akey;
	uint32_t        akey_len;
	XtkLandmark     alandmark;
	char const     *alandname;
	uint32_t        alandname_len;
	XtkLiveSetting  alive;
	XtkHeadingLevel aheading;
	XtkAccessView   aview;
	bool            arequired;
	bool            avalid;
	bool            aperipheral;
	bool            adialog;
	int32_t         apos;
	int32_t         asize;
	int32_t         alevel;
	int32_t         aculture;
	char const     *alabel;
	uint32_t        alabel_len;
	char const     *adescribed;
	uint32_t        adescribed_len;
	char const     *aflowsto;
	uint32_t        aflowsto_len;
	char const     *aflowsfrom;
	uint32_t        aflowsfrom_len;
	char const     *acontrols;
	uint32_t        acontrols_len;
	char const     *text;
	uint32_t        text_len;
	char const     *primary;
	uint32_t        primary_len;
	char const     *secondary;
	uint32_t        secondary_len;
	char const     *close;
	uint32_t        close_len;
	float           contenth;
	XtkDialogButton default_button;
	bool            open;
} XtkDialogProps;

#define XTK_DIALOG_W_MASK              (1ull << 0u)
#define XTK_DIALOG_H_MASK              (1ull << 1u)
#define XTK_DIALOG_GROW_MASK           (1ull << 2u)
#define XTK_DIALOG_SHRINK_MASK         (1ull << 3u)
#define XTK_DIALOG_SELF_MASK           (1ull << 4u)
#define XTK_DIALOG_ML_MASK             (1ull << 5u)
#define XTK_DIALOG_MT_MASK             (1ull << 6u)
#define XTK_DIALOG_MR_MASK             (1ull << 7u)
#define XTK_DIALOG_MB_MASK             (1ull << 8u)
#define XTK_DIALOG_TIP_MASK            (1ull << 9u)
#define XTK_DIALOG_ANAME_MASK          (1ull << 10u)
#define XTK_DIALOG_AID_MASK            (1ull << 11u)
#define XTK_DIALOG_AHELP_MASK          (1ull << 12u)
#define XTK_DIALOG_ADESC_MASK          (1ull << 13u)
#define XTK_DIALOG_ASTATUS_MASK        (1ull << 14u)
#define XTK_DIALOG_AITEM_MASK          (1ull << 15u)
#define XTK_DIALOG_ACTYPE_MASK         (1ull << 16u)
#define XTK_DIALOG_AACCEL_MASK         (1ull << 17u)
#define XTK_DIALOG_AKEY_MASK           (1ull << 18u)
#define XTK_DIALOG_ALANDMARK_MASK      (1ull << 19u)
#define XTK_DIALOG_ALANDNAME_MASK      (1ull << 20u)
#define XTK_DIALOG_ALIVE_MASK          (1ull << 21u)
#define XTK_DIALOG_AHEADING_MASK       (1ull << 22u)
#define XTK_DIALOG_AVIEW_MASK          (1ull << 23u)
#define XTK_DIALOG_AREQUIRED_MASK      (1ull << 24u)
#define XTK_DIALOG_AVALID_MASK         (1ull << 25u)
#define XTK_DIALOG_APERIPHERAL_MASK    (1ull << 26u)
#define XTK_DIALOG_ADIALOG_MASK        (1ull << 27u)
#define XTK_DIALOG_APOS_MASK           (1ull << 28u)
#define XTK_DIALOG_ASIZE_MASK          (1ull << 29u)
#define XTK_DIALOG_ALEVEL_MASK         (1ull << 30u)
#define XTK_DIALOG_ACULTURE_MASK       (1ull << 31u)
#define XTK_DIALOG_ALABEL_MASK         (1ull << 32u)
#define XTK_DIALOG_ADESCRIBED_MASK     (1ull << 33u)
#define XTK_DIALOG_AFLOWSTO_MASK       (1ull << 34u)
#define XTK_DIALOG_AFLOWSFROM_MASK     (1ull << 35u)
#define XTK_DIALOG_ACONTROLS_MASK      (1ull << 36u)
#define XTK_DIALOG_TEXT_MASK           (1ull << 37u)
#define XTK_DIALOG_PRIMARY_MASK        (1ull << 38u)
#define XTK_DIALOG_SECONDARY_MASK      (1ull << 39u)
#define XTK_DIALOG_CLOSE_MASK          (1ull << 40u)
#define XTK_DIALOG_CONTENTH_MASK       (1ull << 41u)
#define XTK_DIALOG_DEFAULT_BUTTON_MASK (1ull << 42u)
#define XTK_DIALOG_OPEN_MASK           (1ull << 43u)

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
	char const             *aname;
	uint32_t                aname_len;
	char const             *aid;
	uint32_t                aid_len;
	char const             *ahelp;
	uint32_t                ahelp_len;
	char const             *adesc;
	uint32_t                adesc_len;
	char const             *astatus;
	uint32_t                astatus_len;
	char const             *aitem;
	uint32_t                aitem_len;
	char const             *actype;
	uint32_t                actype_len;
	char const             *aaccel;
	uint32_t                aaccel_len;
	char const             *akey;
	uint32_t                akey_len;
	XtkLandmark             alandmark;
	char const             *alandname;
	uint32_t                alandname_len;
	XtkLiveSetting          alive;
	XtkHeadingLevel         aheading;
	XtkAccessView           aview;
	bool                    arequired;
	bool                    avalid;
	bool                    aperipheral;
	bool                    adialog;
	int32_t                 apos;
	int32_t                 asize;
	int32_t                 alevel;
	int32_t                 aculture;
	char const             *alabel;
	uint32_t                alabel_len;
	char const             *adescribed;
	uint32_t                adescribed_len;
	char const             *aflowsto;
	uint32_t                aflowsto_len;
	char const             *aflowsfrom;
	uint32_t                aflowsfrom_len;
	char const             *acontrols;
	uint32_t                acontrols_len;
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
#define XTK_TEACHTIP_ANAME_MASK           (1ull << 10u)
#define XTK_TEACHTIP_AID_MASK             (1ull << 11u)
#define XTK_TEACHTIP_AHELP_MASK           (1ull << 12u)
#define XTK_TEACHTIP_ADESC_MASK           (1ull << 13u)
#define XTK_TEACHTIP_ASTATUS_MASK         (1ull << 14u)
#define XTK_TEACHTIP_AITEM_MASK           (1ull << 15u)
#define XTK_TEACHTIP_ACTYPE_MASK          (1ull << 16u)
#define XTK_TEACHTIP_AACCEL_MASK          (1ull << 17u)
#define XTK_TEACHTIP_AKEY_MASK            (1ull << 18u)
#define XTK_TEACHTIP_ALANDMARK_MASK       (1ull << 19u)
#define XTK_TEACHTIP_ALANDNAME_MASK       (1ull << 20u)
#define XTK_TEACHTIP_ALIVE_MASK           (1ull << 21u)
#define XTK_TEACHTIP_AHEADING_MASK        (1ull << 22u)
#define XTK_TEACHTIP_AVIEW_MASK           (1ull << 23u)
#define XTK_TEACHTIP_AREQUIRED_MASK       (1ull << 24u)
#define XTK_TEACHTIP_AVALID_MASK          (1ull << 25u)
#define XTK_TEACHTIP_APERIPHERAL_MASK     (1ull << 26u)
#define XTK_TEACHTIP_ADIALOG_MASK         (1ull << 27u)
#define XTK_TEACHTIP_APOS_MASK            (1ull << 28u)
#define XTK_TEACHTIP_ASIZE_MASK           (1ull << 29u)
#define XTK_TEACHTIP_ALEVEL_MASK          (1ull << 30u)
#define XTK_TEACHTIP_ACULTURE_MASK        (1ull << 31u)
#define XTK_TEACHTIP_ALABEL_MASK          (1ull << 32u)
#define XTK_TEACHTIP_ADESCRIBED_MASK      (1ull << 33u)
#define XTK_TEACHTIP_AFLOWSTO_MASK        (1ull << 34u)
#define XTK_TEACHTIP_AFLOWSFROM_MASK      (1ull << 35u)
#define XTK_TEACHTIP_ACONTROLS_MASK       (1ull << 36u)
#define XTK_TEACHTIP_TEXT_MASK            (1ull << 37u)
#define XTK_TEACHTIP_SUBTITLE_MASK        (1ull << 38u)
#define XTK_TEACHTIP_ICON_MASK            (1ull << 39u)
#define XTK_TEACHTIP_ACTION_MASK          (1ull << 40u)
#define XTK_TEACHTIP_ACTIONACCENT_MASK    (1ull << 41u)
#define XTK_TEACHTIP_CLOSE_MASK           (1ull << 42u)
#define XTK_TEACHTIP_PLACEMENT_MASK       (1ull << 43u)
#define XTK_TEACHTIP_UNTARGETED_MASK      (1ull << 44u)
#define XTK_TEACHTIP_LIGHTDISMISS_MASK    (1ull << 45u)
#define XTK_TEACHTIP_TAIL_MASK            (1ull << 46u)
#define XTK_TEACHTIP_PLACEMENTMARGIN_MASK (1ull << 47u)
#define XTK_TEACHTIP_OPEN_MASK            (1ull << 48u)

typedef struct XtkAvatarProps {
	uint64_t        set;
	XtkChangeStamp  stamp;
	float           w;
	float           h;
	float           grow;
	float           shrink;
	XentFlexAlign   self;
	float           ml;
	float           mt;
	float           mr;
	float           mb;
	char const     *tip;
	uint32_t        tip_len;
	char const     *aname;
	uint32_t        aname_len;
	char const     *aid;
	uint32_t        aid_len;
	char const     *ahelp;
	uint32_t        ahelp_len;
	char const     *adesc;
	uint32_t        adesc_len;
	char const     *astatus;
	uint32_t        astatus_len;
	char const     *aitem;
	uint32_t        aitem_len;
	char const     *actype;
	uint32_t        actype_len;
	char const     *aaccel;
	uint32_t        aaccel_len;
	char const     *akey;
	uint32_t        akey_len;
	XtkLandmark     alandmark;
	char const     *alandname;
	uint32_t        alandname_len;
	XtkLiveSetting  alive;
	XtkHeadingLevel aheading;
	XtkAccessView   aview;
	bool            arequired;
	bool            avalid;
	bool            aperipheral;
	bool            adialog;
	int32_t         apos;
	int32_t         asize;
	int32_t         alevel;
	int32_t         aculture;
	char const     *alabel;
	uint32_t        alabel_len;
	char const     *adescribed;
	uint32_t        adescribed_len;
	char const     *aflowsto;
	uint32_t        aflowsto_len;
	char const     *aflowsfrom;
	uint32_t        aflowsfrom_len;
	char const     *acontrols;
	uint32_t        acontrols_len;
	char const     *text;
	uint32_t        text_len;
	char const     *initials;
	uint32_t        initials_len;
	XtkResource     src;
	char const     *badgeglyph;
	uint32_t        badgeglyph_len;
	int32_t         badgevalue;
	XtkResource     badgeimage;
	char const     *badgetext;
	uint32_t        badgetext_len;
	bool            group;
} XtkAvatarProps;

#define XTK_AVATAR_W_MASK           (1ull << 0u)
#define XTK_AVATAR_H_MASK           (1ull << 1u)
#define XTK_AVATAR_GROW_MASK        (1ull << 2u)
#define XTK_AVATAR_SHRINK_MASK      (1ull << 3u)
#define XTK_AVATAR_SELF_MASK        (1ull << 4u)
#define XTK_AVATAR_ML_MASK          (1ull << 5u)
#define XTK_AVATAR_MT_MASK          (1ull << 6u)
#define XTK_AVATAR_MR_MASK          (1ull << 7u)
#define XTK_AVATAR_MB_MASK          (1ull << 8u)
#define XTK_AVATAR_TIP_MASK         (1ull << 9u)
#define XTK_AVATAR_ANAME_MASK       (1ull << 10u)
#define XTK_AVATAR_AID_MASK         (1ull << 11u)
#define XTK_AVATAR_AHELP_MASK       (1ull << 12u)
#define XTK_AVATAR_ADESC_MASK       (1ull << 13u)
#define XTK_AVATAR_ASTATUS_MASK     (1ull << 14u)
#define XTK_AVATAR_AITEM_MASK       (1ull << 15u)
#define XTK_AVATAR_ACTYPE_MASK      (1ull << 16u)
#define XTK_AVATAR_AACCEL_MASK      (1ull << 17u)
#define XTK_AVATAR_AKEY_MASK        (1ull << 18u)
#define XTK_AVATAR_ALANDMARK_MASK   (1ull << 19u)
#define XTK_AVATAR_ALANDNAME_MASK   (1ull << 20u)
#define XTK_AVATAR_ALIVE_MASK       (1ull << 21u)
#define XTK_AVATAR_AHEADING_MASK    (1ull << 22u)
#define XTK_AVATAR_AVIEW_MASK       (1ull << 23u)
#define XTK_AVATAR_AREQUIRED_MASK   (1ull << 24u)
#define XTK_AVATAR_AVALID_MASK      (1ull << 25u)
#define XTK_AVATAR_APERIPHERAL_MASK (1ull << 26u)
#define XTK_AVATAR_ADIALOG_MASK     (1ull << 27u)
#define XTK_AVATAR_APOS_MASK        (1ull << 28u)
#define XTK_AVATAR_ASIZE_MASK       (1ull << 29u)
#define XTK_AVATAR_ALEVEL_MASK      (1ull << 30u)
#define XTK_AVATAR_ACULTURE_MASK    (1ull << 31u)
#define XTK_AVATAR_ALABEL_MASK      (1ull << 32u)
#define XTK_AVATAR_ADESCRIBED_MASK  (1ull << 33u)
#define XTK_AVATAR_AFLOWSTO_MASK    (1ull << 34u)
#define XTK_AVATAR_AFLOWSFROM_MASK  (1ull << 35u)
#define XTK_AVATAR_ACONTROLS_MASK   (1ull << 36u)
#define XTK_AVATAR_TEXT_MASK        (1ull << 37u)
#define XTK_AVATAR_INITIALS_MASK    (1ull << 38u)
#define XTK_AVATAR_SRC_MASK         (1ull << 39u)
#define XTK_AVATAR_BADGEGLYPH_MASK  (1ull << 40u)
#define XTK_AVATAR_BADGEVALUE_MASK  (1ull << 41u)
#define XTK_AVATAR_BADGEIMAGE_MASK  (1ull << 42u)
#define XTK_AVATAR_BADGETEXT_MASK   (1ull << 43u)
#define XTK_AVATAR_GROUP_MASK       (1ull << 44u)

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
	char const         *aname;
	uint32_t            aname_len;
	char const         *aid;
	uint32_t            aid_len;
	char const         *ahelp;
	uint32_t            ahelp_len;
	char const         *adesc;
	uint32_t            adesc_len;
	char const         *astatus;
	uint32_t            astatus_len;
	char const         *aitem;
	uint32_t            aitem_len;
	char const         *actype;
	uint32_t            actype_len;
	char const         *aaccel;
	uint32_t            aaccel_len;
	char const         *akey;
	uint32_t            akey_len;
	XtkLandmark         alandmark;
	char const         *alandname;
	uint32_t            alandname_len;
	XtkLiveSetting      alive;
	XtkHeadingLevel     aheading;
	XtkAccessView       aview;
	bool                arequired;
	bool                avalid;
	bool                aperipheral;
	bool                adialog;
	int32_t             apos;
	int32_t             asize;
	int32_t             alevel;
	int32_t             aculture;
	char const         *alabel;
	uint32_t            alabel_len;
	char const         *adescribed;
	uint32_t            adescribed_len;
	char const         *aflowsto;
	uint32_t            aflowsto_len;
	char const         *aflowsfrom;
	uint32_t            aflowsfrom_len;
	char const         *acontrols;
	uint32_t            acontrols_len;
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
	bool                hideends;
} XtkPagerProps;

#define XTK_PAGER_W_MASK           (1ull << 0u)
#define XTK_PAGER_H_MASK           (1ull << 1u)
#define XTK_PAGER_GROW_MASK        (1ull << 2u)
#define XTK_PAGER_SHRINK_MASK      (1ull << 3u)
#define XTK_PAGER_SELF_MASK        (1ull << 4u)
#define XTK_PAGER_ML_MASK          (1ull << 5u)
#define XTK_PAGER_MT_MASK          (1ull << 6u)
#define XTK_PAGER_MR_MASK          (1ull << 7u)
#define XTK_PAGER_MB_MASK          (1ull << 8u)
#define XTK_PAGER_TIP_MASK         (1ull << 9u)
#define XTK_PAGER_ANAME_MASK       (1ull << 10u)
#define XTK_PAGER_AID_MASK         (1ull << 11u)
#define XTK_PAGER_AHELP_MASK       (1ull << 12u)
#define XTK_PAGER_ADESC_MASK       (1ull << 13u)
#define XTK_PAGER_ASTATUS_MASK     (1ull << 14u)
#define XTK_PAGER_AITEM_MASK       (1ull << 15u)
#define XTK_PAGER_ACTYPE_MASK      (1ull << 16u)
#define XTK_PAGER_AACCEL_MASK      (1ull << 17u)
#define XTK_PAGER_AKEY_MASK        (1ull << 18u)
#define XTK_PAGER_ALANDMARK_MASK   (1ull << 19u)
#define XTK_PAGER_ALANDNAME_MASK   (1ull << 20u)
#define XTK_PAGER_ALIVE_MASK       (1ull << 21u)
#define XTK_PAGER_AHEADING_MASK    (1ull << 22u)
#define XTK_PAGER_AVIEW_MASK       (1ull << 23u)
#define XTK_PAGER_AREQUIRED_MASK   (1ull << 24u)
#define XTK_PAGER_AVALID_MASK      (1ull << 25u)
#define XTK_PAGER_APERIPHERAL_MASK (1ull << 26u)
#define XTK_PAGER_ADIALOG_MASK     (1ull << 27u)
#define XTK_PAGER_APOS_MASK        (1ull << 28u)
#define XTK_PAGER_ASIZE_MASK       (1ull << 29u)
#define XTK_PAGER_ALEVEL_MASK      (1ull << 30u)
#define XTK_PAGER_ACULTURE_MASK    (1ull << 31u)
#define XTK_PAGER_ALABEL_MASK      (1ull << 32u)
#define XTK_PAGER_ADESCRIBED_MASK  (1ull << 33u)
#define XTK_PAGER_AFLOWSTO_MASK    (1ull << 34u)
#define XTK_PAGER_AFLOWSFROM_MASK  (1ull << 35u)
#define XTK_PAGER_ACONTROLS_MASK   (1ull << 36u)
#define XTK_PAGER_SEL_MASK         (1ull << 37u)
#define XTK_PAGER_NITEM_MASK       (1ull << 38u)
#define XTK_PAGER_DISPLAY_MASK     (1ull << 39u)
#define XTK_PAGER_FIRST_MASK       (1ull << 40u)
#define XTK_PAGER_PREV_MASK        (1ull << 41u)
#define XTK_PAGER_NEXT_MASK        (1ull << 42u)
#define XTK_PAGER_LAST_MASK        (1ull << 43u)
#define XTK_PAGER_PREFIX_MASK      (1ull << 44u)
#define XTK_PAGER_SUFFIX_MASK      (1ull << 45u)
#define XTK_PAGER_HIDEENDS_MASK    (1ull << 46u)

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
	char const               *aname;
	uint32_t                  aname_len;
	char const               *aid;
	uint32_t                  aid_len;
	char const               *ahelp;
	uint32_t                  ahelp_len;
	char const               *adesc;
	uint32_t                  adesc_len;
	char const               *astatus;
	uint32_t                  astatus_len;
	char const               *aitem;
	uint32_t                  aitem_len;
	char const               *actype;
	uint32_t                  actype_len;
	char const               *aaccel;
	uint32_t                  aaccel_len;
	char const               *akey;
	uint32_t                  akey_len;
	XtkLandmark               alandmark;
	char const               *alandname;
	uint32_t                  alandname_len;
	XtkLiveSetting            alive;
	XtkHeadingLevel           aheading;
	XtkAccessView             aview;
	bool                      arequired;
	bool                      avalid;
	bool                      aperipheral;
	bool                      adialog;
	int32_t                   apos;
	int32_t                   asize;
	int32_t                   alevel;
	int32_t                   aculture;
	char const               *alabel;
	uint32_t                  alabel_len;
	char const               *adescribed;
	uint32_t                  adescribed_len;
	char const               *aflowsto;
	uint32_t                  aflowsto_len;
	char const               *aflowsfrom;
	uint32_t                  aflowsfrom_len;
	char const               *acontrols;
	uint32_t                  acontrols_len;
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

#define XTK_SPLITVIEW_W_MASK           (1ull << 0u)
#define XTK_SPLITVIEW_H_MASK           (1ull << 1u)
#define XTK_SPLITVIEW_GROW_MASK        (1ull << 2u)
#define XTK_SPLITVIEW_SHRINK_MASK      (1ull << 3u)
#define XTK_SPLITVIEW_SELF_MASK        (1ull << 4u)
#define XTK_SPLITVIEW_ML_MASK          (1ull << 5u)
#define XTK_SPLITVIEW_MT_MASK          (1ull << 6u)
#define XTK_SPLITVIEW_MR_MASK          (1ull << 7u)
#define XTK_SPLITVIEW_MB_MASK          (1ull << 8u)
#define XTK_SPLITVIEW_TIP_MASK         (1ull << 9u)
#define XTK_SPLITVIEW_ANAME_MASK       (1ull << 10u)
#define XTK_SPLITVIEW_AID_MASK         (1ull << 11u)
#define XTK_SPLITVIEW_AHELP_MASK       (1ull << 12u)
#define XTK_SPLITVIEW_ADESC_MASK       (1ull << 13u)
#define XTK_SPLITVIEW_ASTATUS_MASK     (1ull << 14u)
#define XTK_SPLITVIEW_AITEM_MASK       (1ull << 15u)
#define XTK_SPLITVIEW_ACTYPE_MASK      (1ull << 16u)
#define XTK_SPLITVIEW_AACCEL_MASK      (1ull << 17u)
#define XTK_SPLITVIEW_AKEY_MASK        (1ull << 18u)
#define XTK_SPLITVIEW_ALANDMARK_MASK   (1ull << 19u)
#define XTK_SPLITVIEW_ALANDNAME_MASK   (1ull << 20u)
#define XTK_SPLITVIEW_ALIVE_MASK       (1ull << 21u)
#define XTK_SPLITVIEW_AHEADING_MASK    (1ull << 22u)
#define XTK_SPLITVIEW_AVIEW_MASK       (1ull << 23u)
#define XTK_SPLITVIEW_AREQUIRED_MASK   (1ull << 24u)
#define XTK_SPLITVIEW_AVALID_MASK      (1ull << 25u)
#define XTK_SPLITVIEW_APERIPHERAL_MASK (1ull << 26u)
#define XTK_SPLITVIEW_ADIALOG_MASK     (1ull << 27u)
#define XTK_SPLITVIEW_APOS_MASK        (1ull << 28u)
#define XTK_SPLITVIEW_ASIZE_MASK       (1ull << 29u)
#define XTK_SPLITVIEW_ALEVEL_MASK      (1ull << 30u)
#define XTK_SPLITVIEW_ACULTURE_MASK    (1ull << 31u)
#define XTK_SPLITVIEW_ALABEL_MASK      (1ull << 32u)
#define XTK_SPLITVIEW_ADESCRIBED_MASK  (1ull << 33u)
#define XTK_SPLITVIEW_AFLOWSTO_MASK    (1ull << 34u)
#define XTK_SPLITVIEW_AFLOWSFROM_MASK  (1ull << 35u)
#define XTK_SPLITVIEW_ACONTROLS_MASK   (1ull << 36u)
#define XTK_SPLITVIEW_DIR_MASK         (1ull << 37u)
#define XTK_SPLITVIEW_GAP_MASK         (1ull << 38u)
#define XTK_SPLITVIEW_PL_MASK          (1ull << 39u)
#define XTK_SPLITVIEW_PT_MASK          (1ull << 40u)
#define XTK_SPLITVIEW_PR_MASK          (1ull << 41u)
#define XTK_SPLITVIEW_PB_MASK          (1ull << 42u)
#define XTK_SPLITVIEW_FILL_MASK        (1ull << 43u)
#define XTK_SPLITVIEW_OPEN_MASK        (1ull << 44u)
#define XTK_SPLITVIEW_DISPLAY_MASK     (1ull << 45u)
#define XTK_SPLITVIEW_PLACEMENT_MASK   (1ull << 46u)
#define XTK_SPLITVIEW_OPENLEN_MASK     (1ull << 47u)
#define XTK_SPLITVIEW_COMPACTLEN_MASK  (1ull << 48u)

typedef struct XtkTitleBarProps {
	uint64_t        set;
	XtkChangeStamp  stamp;
	float           w;
	float           h;
	float           grow;
	float           shrink;
	XentFlexAlign   self;
	float           ml;
	float           mt;
	float           mr;
	float           mb;
	char const     *tip;
	uint32_t        tip_len;
	char const     *aname;
	uint32_t        aname_len;
	char const     *aid;
	uint32_t        aid_len;
	char const     *ahelp;
	uint32_t        ahelp_len;
	char const     *adesc;
	uint32_t        adesc_len;
	char const     *astatus;
	uint32_t        astatus_len;
	char const     *aitem;
	uint32_t        aitem_len;
	char const     *actype;
	uint32_t        actype_len;
	char const     *aaccel;
	uint32_t        aaccel_len;
	char const     *akey;
	uint32_t        akey_len;
	XtkLandmark     alandmark;
	char const     *alandname;
	uint32_t        alandname_len;
	XtkLiveSetting  alive;
	XtkHeadingLevel aheading;
	XtkAccessView   aview;
	bool            arequired;
	bool            avalid;
	bool            aperipheral;
	bool            adialog;
	int32_t         apos;
	int32_t         asize;
	int32_t         alevel;
	int32_t         aculture;
	char const     *alabel;
	uint32_t        alabel_len;
	char const     *adescribed;
	uint32_t        adescribed_len;
	char const     *aflowsto;
	uint32_t        aflowsto_len;
	char const     *aflowsfrom;
	uint32_t        aflowsfrom_len;
	char const     *acontrols;
	uint32_t        acontrols_len;
	char const     *text;
	uint32_t        text_len;
	char const     *subtitle;
	uint32_t        subtitle_len;
	char const     *icon;
	uint32_t        icon_len;
	bool            showback;
	bool            backdisabled;
	bool            showtoggle;
	bool            integrate;
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
#define XTK_TITLEBAR_ANAME_MASK        (1ull << 10u)
#define XTK_TITLEBAR_AID_MASK          (1ull << 11u)
#define XTK_TITLEBAR_AHELP_MASK        (1ull << 12u)
#define XTK_TITLEBAR_ADESC_MASK        (1ull << 13u)
#define XTK_TITLEBAR_ASTATUS_MASK      (1ull << 14u)
#define XTK_TITLEBAR_AITEM_MASK        (1ull << 15u)
#define XTK_TITLEBAR_ACTYPE_MASK       (1ull << 16u)
#define XTK_TITLEBAR_AACCEL_MASK       (1ull << 17u)
#define XTK_TITLEBAR_AKEY_MASK         (1ull << 18u)
#define XTK_TITLEBAR_ALANDMARK_MASK    (1ull << 19u)
#define XTK_TITLEBAR_ALANDNAME_MASK    (1ull << 20u)
#define XTK_TITLEBAR_ALIVE_MASK        (1ull << 21u)
#define XTK_TITLEBAR_AHEADING_MASK     (1ull << 22u)
#define XTK_TITLEBAR_AVIEW_MASK        (1ull << 23u)
#define XTK_TITLEBAR_AREQUIRED_MASK    (1ull << 24u)
#define XTK_TITLEBAR_AVALID_MASK       (1ull << 25u)
#define XTK_TITLEBAR_APERIPHERAL_MASK  (1ull << 26u)
#define XTK_TITLEBAR_ADIALOG_MASK      (1ull << 27u)
#define XTK_TITLEBAR_APOS_MASK         (1ull << 28u)
#define XTK_TITLEBAR_ASIZE_MASK        (1ull << 29u)
#define XTK_TITLEBAR_ALEVEL_MASK       (1ull << 30u)
#define XTK_TITLEBAR_ACULTURE_MASK     (1ull << 31u)
#define XTK_TITLEBAR_ALABEL_MASK       (1ull << 32u)
#define XTK_TITLEBAR_ADESCRIBED_MASK   (1ull << 33u)
#define XTK_TITLEBAR_AFLOWSTO_MASK     (1ull << 34u)
#define XTK_TITLEBAR_AFLOWSFROM_MASK   (1ull << 35u)
#define XTK_TITLEBAR_ACONTROLS_MASK    (1ull << 36u)
#define XTK_TITLEBAR_TEXT_MASK         (1ull << 37u)
#define XTK_TITLEBAR_SUBTITLE_MASK     (1ull << 38u)
#define XTK_TITLEBAR_ICON_MASK         (1ull << 39u)
#define XTK_TITLEBAR_SHOWBACK_MASK     (1ull << 40u)
#define XTK_TITLEBAR_BACKDISABLED_MASK (1ull << 41u)
#define XTK_TITLEBAR_SHOWTOGGLE_MASK   (1ull << 42u)
#define XTK_TITLEBAR_INTEGRATE_MASK    (1ull << 43u)

typedef struct XtkRatingProps {
	uint64_t        set;
	XtkChangeStamp  stamp;
	float           w;
	float           h;
	float           grow;
	float           shrink;
	XentFlexAlign   self;
	float           ml;
	float           mt;
	float           mr;
	float           mb;
	char const     *tip;
	uint32_t        tip_len;
	char const     *aname;
	uint32_t        aname_len;
	char const     *aid;
	uint32_t        aid_len;
	char const     *ahelp;
	uint32_t        ahelp_len;
	char const     *adesc;
	uint32_t        adesc_len;
	char const     *astatus;
	uint32_t        astatus_len;
	char const     *aitem;
	uint32_t        aitem_len;
	char const     *actype;
	uint32_t        actype_len;
	char const     *aaccel;
	uint32_t        aaccel_len;
	char const     *akey;
	uint32_t        akey_len;
	XtkLandmark     alandmark;
	char const     *alandname;
	uint32_t        alandname_len;
	XtkLiveSetting  alive;
	XtkHeadingLevel aheading;
	XtkAccessView   aview;
	bool            arequired;
	bool            avalid;
	bool            aperipheral;
	bool            adialog;
	int32_t         apos;
	int32_t         asize;
	int32_t         alevel;
	int32_t         aculture;
	char const     *alabel;
	uint32_t        alabel_len;
	char const     *adescribed;
	uint32_t        adescribed_len;
	char const     *aflowsto;
	uint32_t        aflowsto_len;
	char const     *aflowsfrom;
	uint32_t        aflowsfrom_len;
	char const     *acontrols;
	uint32_t        acontrols_len;
	double          value;
	double          max;
	char const     *text;
	uint32_t        text_len;
	double          placeholder;
	int32_t         initial;
	bool            clear;
	bool            readonly;
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
#define XTK_RATING_ANAME_MASK       (1ull << 10u)
#define XTK_RATING_AID_MASK         (1ull << 11u)
#define XTK_RATING_AHELP_MASK       (1ull << 12u)
#define XTK_RATING_ADESC_MASK       (1ull << 13u)
#define XTK_RATING_ASTATUS_MASK     (1ull << 14u)
#define XTK_RATING_AITEM_MASK       (1ull << 15u)
#define XTK_RATING_ACTYPE_MASK      (1ull << 16u)
#define XTK_RATING_AACCEL_MASK      (1ull << 17u)
#define XTK_RATING_AKEY_MASK        (1ull << 18u)
#define XTK_RATING_ALANDMARK_MASK   (1ull << 19u)
#define XTK_RATING_ALANDNAME_MASK   (1ull << 20u)
#define XTK_RATING_ALIVE_MASK       (1ull << 21u)
#define XTK_RATING_AHEADING_MASK    (1ull << 22u)
#define XTK_RATING_AVIEW_MASK       (1ull << 23u)
#define XTK_RATING_AREQUIRED_MASK   (1ull << 24u)
#define XTK_RATING_AVALID_MASK      (1ull << 25u)
#define XTK_RATING_APERIPHERAL_MASK (1ull << 26u)
#define XTK_RATING_ADIALOG_MASK     (1ull << 27u)
#define XTK_RATING_APOS_MASK        (1ull << 28u)
#define XTK_RATING_ASIZE_MASK       (1ull << 29u)
#define XTK_RATING_ALEVEL_MASK      (1ull << 30u)
#define XTK_RATING_ACULTURE_MASK    (1ull << 31u)
#define XTK_RATING_ALABEL_MASK      (1ull << 32u)
#define XTK_RATING_ADESCRIBED_MASK  (1ull << 33u)
#define XTK_RATING_AFLOWSTO_MASK    (1ull << 34u)
#define XTK_RATING_AFLOWSFROM_MASK  (1ull << 35u)
#define XTK_RATING_ACONTROLS_MASK   (1ull << 36u)
#define XTK_RATING_VALUE_MASK       (1ull << 37u)
#define XTK_RATING_MAX_MASK         (1ull << 38u)
#define XTK_RATING_TEXT_MASK        (1ull << 39u)
#define XTK_RATING_PLACEHOLDER_MASK (1ull << 40u)
#define XTK_RATING_INITIAL_MASK     (1ull << 41u)
#define XTK_RATING_CLEAR_MASK       (1ull << 42u)
#define XTK_RATING_READONLY_MASK    (1ull << 43u)

typedef struct XtkLinkProps {
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
	char const     *text;
	uint32_t        text_len;
	char const     *tip;
	uint32_t        tip_len;
	char const     *aname;
	uint32_t        aname_len;
	char const     *aid;
	uint32_t        aid_len;
	char const     *ahelp;
	uint32_t        ahelp_len;
	char const     *adesc;
	uint32_t        adesc_len;
	char const     *astatus;
	uint32_t        astatus_len;
	char const     *aitem;
	uint32_t        aitem_len;
	char const     *actype;
	uint32_t        actype_len;
	char const     *aaccel;
	uint32_t        aaccel_len;
	char const     *akey;
	uint32_t        akey_len;
	XtkLandmark     alandmark;
	char const     *alandname;
	uint32_t        alandname_len;
	XtkLiveSetting  alive;
	XtkHeadingLevel aheading;
	XtkAccessView   aview;
	bool            arequired;
	bool            avalid;
	bool            aperipheral;
	bool            adialog;
	int32_t         apos;
	int32_t         asize;
	int32_t         alevel;
	int32_t         aculture;
	char const     *alabel;
	uint32_t        alabel_len;
	char const     *adescribed;
	uint32_t        adescribed_len;
	char const     *aflowsto;
	uint32_t        aflowsto_len;
	char const     *aflowsfrom;
	uint32_t        aflowsfrom_len;
	char const     *acontrols;
	uint32_t        acontrols_len;
	bool            enabled;
	char const     *url;
	uint32_t        url_len;
} XtkLinkProps;

#define XTK_LINK_W_MASK           (1ull << 0u)
#define XTK_LINK_H_MASK           (1ull << 1u)
#define XTK_LINK_GROW_MASK        (1ull << 2u)
#define XTK_LINK_SELF_MASK        (1ull << 3u)
#define XTK_LINK_ML_MASK          (1ull << 4u)
#define XTK_LINK_MT_MASK          (1ull << 5u)
#define XTK_LINK_MR_MASK          (1ull << 6u)
#define XTK_LINK_MB_MASK          (1ull << 7u)
#define XTK_LINK_TEXT_MASK        (1ull << 8u)
#define XTK_LINK_TIP_MASK         (1ull << 9u)
#define XTK_LINK_ANAME_MASK       (1ull << 10u)
#define XTK_LINK_AID_MASK         (1ull << 11u)
#define XTK_LINK_AHELP_MASK       (1ull << 12u)
#define XTK_LINK_ADESC_MASK       (1ull << 13u)
#define XTK_LINK_ASTATUS_MASK     (1ull << 14u)
#define XTK_LINK_AITEM_MASK       (1ull << 15u)
#define XTK_LINK_ACTYPE_MASK      (1ull << 16u)
#define XTK_LINK_AACCEL_MASK      (1ull << 17u)
#define XTK_LINK_AKEY_MASK        (1ull << 18u)
#define XTK_LINK_ALANDMARK_MASK   (1ull << 19u)
#define XTK_LINK_ALANDNAME_MASK   (1ull << 20u)
#define XTK_LINK_ALIVE_MASK       (1ull << 21u)
#define XTK_LINK_AHEADING_MASK    (1ull << 22u)
#define XTK_LINK_AVIEW_MASK       (1ull << 23u)
#define XTK_LINK_AREQUIRED_MASK   (1ull << 24u)
#define XTK_LINK_AVALID_MASK      (1ull << 25u)
#define XTK_LINK_APERIPHERAL_MASK (1ull << 26u)
#define XTK_LINK_ADIALOG_MASK     (1ull << 27u)
#define XTK_LINK_APOS_MASK        (1ull << 28u)
#define XTK_LINK_ASIZE_MASK       (1ull << 29u)
#define XTK_LINK_ALEVEL_MASK      (1ull << 30u)
#define XTK_LINK_ACULTURE_MASK    (1ull << 31u)
#define XTK_LINK_ALABEL_MASK      (1ull << 32u)
#define XTK_LINK_ADESCRIBED_MASK  (1ull << 33u)
#define XTK_LINK_AFLOWSTO_MASK    (1ull << 34u)
#define XTK_LINK_AFLOWSFROM_MASK  (1ull << 35u)
#define XTK_LINK_ACONTROLS_MASK   (1ull << 36u)
#define XTK_LINK_ENABLED_MASK     (1ull << 37u)
#define XTK_LINK_URL_MASK         (1ull << 38u)

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
	char const           *aname;
	uint32_t              aname_len;
	char const           *aid;
	uint32_t              aid_len;
	char const           *ahelp;
	uint32_t              ahelp_len;
	char const           *adesc;
	uint32_t              adesc_len;
	char const           *astatus;
	uint32_t              astatus_len;
	char const           *aitem;
	uint32_t              aitem_len;
	char const           *actype;
	uint32_t              actype_len;
	char const           *aaccel;
	uint32_t              aaccel_len;
	char const           *akey;
	uint32_t              akey_len;
	XtkLandmark           alandmark;
	char const           *alandname;
	uint32_t              alandname_len;
	XtkLiveSetting        alive;
	XtkHeadingLevel       aheading;
	XtkAccessView         aview;
	bool                  arequired;
	bool                  avalid;
	bool                  aperipheral;
	bool                  adialog;
	int32_t               apos;
	int32_t               asize;
	int32_t               alevel;
	int32_t               aculture;
	char const           *alabel;
	uint32_t              alabel_len;
	char const           *adescribed;
	uint32_t              adescribed_len;
	char const           *aflowsto;
	uint32_t              aflowsto_len;
	char const           *aflowsfrom;
	uint32_t              aflowsfrom_len;
	char const           *acontrols;
	uint32_t              acontrols_len;
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
#define XTK_SCROLLBAR_ANAME_MASK       (1ull << 9u)
#define XTK_SCROLLBAR_AID_MASK         (1ull << 10u)
#define XTK_SCROLLBAR_AHELP_MASK       (1ull << 11u)
#define XTK_SCROLLBAR_ADESC_MASK       (1ull << 12u)
#define XTK_SCROLLBAR_ASTATUS_MASK     (1ull << 13u)
#define XTK_SCROLLBAR_AITEM_MASK       (1ull << 14u)
#define XTK_SCROLLBAR_ACTYPE_MASK      (1ull << 15u)
#define XTK_SCROLLBAR_AACCEL_MASK      (1ull << 16u)
#define XTK_SCROLLBAR_AKEY_MASK        (1ull << 17u)
#define XTK_SCROLLBAR_ALANDMARK_MASK   (1ull << 18u)
#define XTK_SCROLLBAR_ALANDNAME_MASK   (1ull << 19u)
#define XTK_SCROLLBAR_ALIVE_MASK       (1ull << 20u)
#define XTK_SCROLLBAR_AHEADING_MASK    (1ull << 21u)
#define XTK_SCROLLBAR_AVIEW_MASK       (1ull << 22u)
#define XTK_SCROLLBAR_AREQUIRED_MASK   (1ull << 23u)
#define XTK_SCROLLBAR_AVALID_MASK      (1ull << 24u)
#define XTK_SCROLLBAR_APERIPHERAL_MASK (1ull << 25u)
#define XTK_SCROLLBAR_ADIALOG_MASK     (1ull << 26u)
#define XTK_SCROLLBAR_APOS_MASK        (1ull << 27u)
#define XTK_SCROLLBAR_ASIZE_MASK       (1ull << 28u)
#define XTK_SCROLLBAR_ALEVEL_MASK      (1ull << 29u)
#define XTK_SCROLLBAR_ACULTURE_MASK    (1ull << 30u)
#define XTK_SCROLLBAR_ALABEL_MASK      (1ull << 31u)
#define XTK_SCROLLBAR_ADESCRIBED_MASK  (1ull << 32u)
#define XTK_SCROLLBAR_AFLOWSTO_MASK    (1ull << 33u)
#define XTK_SCROLLBAR_AFLOWSFROM_MASK  (1ull << 34u)
#define XTK_SCROLLBAR_ACONTROLS_MASK   (1ull << 35u)
#define XTK_SCROLLBAR_ENABLED_MASK     (1ull << 36u)
#define XTK_SCROLLBAR_DIR_MASK         (1ull << 37u)
#define XTK_SCROLLBAR_MIN_MASK         (1ull << 38u)
#define XTK_SCROLLBAR_MAX_MASK         (1ull << 39u)
#define XTK_SCROLLBAR_VALUE_MASK       (1ull << 40u)
#define XTK_SCROLLBAR_VIEWPORT_MASK    (1ull << 41u)
#define XTK_SCROLLBAR_SMALLCHANGE_MASK (1ull << 42u)
#define XTK_SCROLLBAR_LARGECHANGE_MASK (1ull << 43u)
#define XTK_SCROLLBAR_INDICATOR_MASK   (1ull << 44u)

typedef struct XtkLoopingProps {
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
	char const     *aname;
	uint32_t        aname_len;
	char const     *aid;
	uint32_t        aid_len;
	char const     *ahelp;
	uint32_t        ahelp_len;
	char const     *adesc;
	uint32_t        adesc_len;
	char const     *astatus;
	uint32_t        astatus_len;
	char const     *aitem;
	uint32_t        aitem_len;
	char const     *actype;
	uint32_t        actype_len;
	char const     *aaccel;
	uint32_t        aaccel_len;
	char const     *akey;
	uint32_t        akey_len;
	XtkLandmark     alandmark;
	char const     *alandname;
	uint32_t        alandname_len;
	XtkLiveSetting  alive;
	XtkHeadingLevel aheading;
	XtkAccessView   aview;
	bool            arequired;
	bool            avalid;
	bool            aperipheral;
	bool            adialog;
	int32_t         apos;
	int32_t         asize;
	int32_t         alevel;
	int32_t         aculture;
	char const     *alabel;
	uint32_t        alabel_len;
	char const     *adescribed;
	uint32_t        adescribed_len;
	char const     *aflowsto;
	uint32_t        aflowsto_len;
	char const     *aflowsfrom;
	uint32_t        aflowsfrom_len;
	char const     *acontrols;
	uint32_t        acontrols_len;
	bool            enabled;
	int32_t         nitem;
	int32_t         sel;
	float           itemh;
	float           itemw;
	bool            loop;
} XtkLoopingProps;

#define XTK_LOOPING_W_MASK           (1ull << 0u)
#define XTK_LOOPING_H_MASK           (1ull << 1u)
#define XTK_LOOPING_GROW_MASK        (1ull << 2u)
#define XTK_LOOPING_SELF_MASK        (1ull << 3u)
#define XTK_LOOPING_ML_MASK          (1ull << 4u)
#define XTK_LOOPING_MT_MASK          (1ull << 5u)
#define XTK_LOOPING_MR_MASK          (1ull << 6u)
#define XTK_LOOPING_MB_MASK          (1ull << 7u)
#define XTK_LOOPING_TIP_MASK         (1ull << 8u)
#define XTK_LOOPING_ANAME_MASK       (1ull << 9u)
#define XTK_LOOPING_AID_MASK         (1ull << 10u)
#define XTK_LOOPING_AHELP_MASK       (1ull << 11u)
#define XTK_LOOPING_ADESC_MASK       (1ull << 12u)
#define XTK_LOOPING_ASTATUS_MASK     (1ull << 13u)
#define XTK_LOOPING_AITEM_MASK       (1ull << 14u)
#define XTK_LOOPING_ACTYPE_MASK      (1ull << 15u)
#define XTK_LOOPING_AACCEL_MASK      (1ull << 16u)
#define XTK_LOOPING_AKEY_MASK        (1ull << 17u)
#define XTK_LOOPING_ALANDMARK_MASK   (1ull << 18u)
#define XTK_LOOPING_ALANDNAME_MASK   (1ull << 19u)
#define XTK_LOOPING_ALIVE_MASK       (1ull << 20u)
#define XTK_LOOPING_AHEADING_MASK    (1ull << 21u)
#define XTK_LOOPING_AVIEW_MASK       (1ull << 22u)
#define XTK_LOOPING_AREQUIRED_MASK   (1ull << 23u)
#define XTK_LOOPING_AVALID_MASK      (1ull << 24u)
#define XTK_LOOPING_APERIPHERAL_MASK (1ull << 25u)
#define XTK_LOOPING_ADIALOG_MASK     (1ull << 26u)
#define XTK_LOOPING_APOS_MASK        (1ull << 27u)
#define XTK_LOOPING_ASIZE_MASK       (1ull << 28u)
#define XTK_LOOPING_ALEVEL_MASK      (1ull << 29u)
#define XTK_LOOPING_ACULTURE_MASK    (1ull << 30u)
#define XTK_LOOPING_ALABEL_MASK      (1ull << 31u)
#define XTK_LOOPING_ADESCRIBED_MASK  (1ull << 32u)
#define XTK_LOOPING_AFLOWSTO_MASK    (1ull << 33u)
#define XTK_LOOPING_AFLOWSFROM_MASK  (1ull << 34u)
#define XTK_LOOPING_ACONTROLS_MASK   (1ull << 35u)
#define XTK_LOOPING_ENABLED_MASK     (1ull << 36u)
#define XTK_LOOPING_NITEM_MASK       (1ull << 37u)
#define XTK_LOOPING_SEL_MASK         (1ull << 38u)
#define XTK_LOOPING_ITEMH_MASK       (1ull << 39u)
#define XTK_LOOPING_ITEMW_MASK       (1ull << 40u)
#define XTK_LOOPING_LOOP_MASK        (1ull << 41u)

typedef struct XtkDatePickerProps {
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
	char const     *aname;
	uint32_t        aname_len;
	char const     *aid;
	uint32_t        aid_len;
	char const     *ahelp;
	uint32_t        ahelp_len;
	char const     *adesc;
	uint32_t        adesc_len;
	char const     *astatus;
	uint32_t        astatus_len;
	char const     *aitem;
	uint32_t        aitem_len;
	char const     *actype;
	uint32_t        actype_len;
	char const     *aaccel;
	uint32_t        aaccel_len;
	char const     *akey;
	uint32_t        akey_len;
	XtkLandmark     alandmark;
	char const     *alandname;
	uint32_t        alandname_len;
	XtkLiveSetting  alive;
	XtkHeadingLevel aheading;
	XtkAccessView   aview;
	bool            arequired;
	bool            avalid;
	bool            aperipheral;
	bool            adialog;
	int32_t         apos;
	int32_t         asize;
	int32_t         alevel;
	int32_t         aculture;
	char const     *alabel;
	uint32_t        alabel_len;
	char const     *adescribed;
	uint32_t        adescribed_len;
	char const     *aflowsto;
	uint32_t        aflowsto_len;
	char const     *aflowsfrom;
	uint32_t        aflowsfrom_len;
	char const     *acontrols;
	uint32_t        acontrols_len;
	bool            enabled;
	char const     *header;
	uint32_t        header_len;
	int32_t         date;
	int32_t         minyear;
	int32_t         maxyear;
} XtkDatePickerProps;

#define XTK_DATEPICKER_W_MASK           (1ull << 0u)
#define XTK_DATEPICKER_H_MASK           (1ull << 1u)
#define XTK_DATEPICKER_GROW_MASK        (1ull << 2u)
#define XTK_DATEPICKER_SELF_MASK        (1ull << 3u)
#define XTK_DATEPICKER_ML_MASK          (1ull << 4u)
#define XTK_DATEPICKER_MT_MASK          (1ull << 5u)
#define XTK_DATEPICKER_MR_MASK          (1ull << 6u)
#define XTK_DATEPICKER_MB_MASK          (1ull << 7u)
#define XTK_DATEPICKER_TIP_MASK         (1ull << 8u)
#define XTK_DATEPICKER_ANAME_MASK       (1ull << 9u)
#define XTK_DATEPICKER_AID_MASK         (1ull << 10u)
#define XTK_DATEPICKER_AHELP_MASK       (1ull << 11u)
#define XTK_DATEPICKER_ADESC_MASK       (1ull << 12u)
#define XTK_DATEPICKER_ASTATUS_MASK     (1ull << 13u)
#define XTK_DATEPICKER_AITEM_MASK       (1ull << 14u)
#define XTK_DATEPICKER_ACTYPE_MASK      (1ull << 15u)
#define XTK_DATEPICKER_AACCEL_MASK      (1ull << 16u)
#define XTK_DATEPICKER_AKEY_MASK        (1ull << 17u)
#define XTK_DATEPICKER_ALANDMARK_MASK   (1ull << 18u)
#define XTK_DATEPICKER_ALANDNAME_MASK   (1ull << 19u)
#define XTK_DATEPICKER_ALIVE_MASK       (1ull << 20u)
#define XTK_DATEPICKER_AHEADING_MASK    (1ull << 21u)
#define XTK_DATEPICKER_AVIEW_MASK       (1ull << 22u)
#define XTK_DATEPICKER_AREQUIRED_MASK   (1ull << 23u)
#define XTK_DATEPICKER_AVALID_MASK      (1ull << 24u)
#define XTK_DATEPICKER_APERIPHERAL_MASK (1ull << 25u)
#define XTK_DATEPICKER_ADIALOG_MASK     (1ull << 26u)
#define XTK_DATEPICKER_APOS_MASK        (1ull << 27u)
#define XTK_DATEPICKER_ASIZE_MASK       (1ull << 28u)
#define XTK_DATEPICKER_ALEVEL_MASK      (1ull << 29u)
#define XTK_DATEPICKER_ACULTURE_MASK    (1ull << 30u)
#define XTK_DATEPICKER_ALABEL_MASK      (1ull << 31u)
#define XTK_DATEPICKER_ADESCRIBED_MASK  (1ull << 32u)
#define XTK_DATEPICKER_AFLOWSTO_MASK    (1ull << 33u)
#define XTK_DATEPICKER_AFLOWSFROM_MASK  (1ull << 34u)
#define XTK_DATEPICKER_ACONTROLS_MASK   (1ull << 35u)
#define XTK_DATEPICKER_ENABLED_MASK     (1ull << 36u)
#define XTK_DATEPICKER_HEADER_MASK      (1ull << 37u)
#define XTK_DATEPICKER_DATE_MASK        (1ull << 38u)
#define XTK_DATEPICKER_MINYEAR_MASK     (1ull << 39u)
#define XTK_DATEPICKER_MAXYEAR_MASK     (1ull << 40u)

typedef struct XtkTimePickerProps {
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
	char const     *aname;
	uint32_t        aname_len;
	char const     *aid;
	uint32_t        aid_len;
	char const     *ahelp;
	uint32_t        ahelp_len;
	char const     *adesc;
	uint32_t        adesc_len;
	char const     *astatus;
	uint32_t        astatus_len;
	char const     *aitem;
	uint32_t        aitem_len;
	char const     *actype;
	uint32_t        actype_len;
	char const     *aaccel;
	uint32_t        aaccel_len;
	char const     *akey;
	uint32_t        akey_len;
	XtkLandmark     alandmark;
	char const     *alandname;
	uint32_t        alandname_len;
	XtkLiveSetting  alive;
	XtkHeadingLevel aheading;
	XtkAccessView   aview;
	bool            arequired;
	bool            avalid;
	bool            aperipheral;
	bool            adialog;
	int32_t         apos;
	int32_t         asize;
	int32_t         alevel;
	int32_t         aculture;
	char const     *alabel;
	uint32_t        alabel_len;
	char const     *adescribed;
	uint32_t        adescribed_len;
	char const     *aflowsto;
	uint32_t        aflowsto_len;
	char const     *aflowsfrom;
	uint32_t        aflowsfrom_len;
	char const     *acontrols;
	uint32_t        acontrols_len;
	bool            enabled;
	char const     *header;
	uint32_t        header_len;
	int32_t         time;
	XtkClock        clock;
	int32_t         step;
} XtkTimePickerProps;

#define XTK_TIMEPICKER_W_MASK           (1ull << 0u)
#define XTK_TIMEPICKER_H_MASK           (1ull << 1u)
#define XTK_TIMEPICKER_GROW_MASK        (1ull << 2u)
#define XTK_TIMEPICKER_SELF_MASK        (1ull << 3u)
#define XTK_TIMEPICKER_ML_MASK          (1ull << 4u)
#define XTK_TIMEPICKER_MT_MASK          (1ull << 5u)
#define XTK_TIMEPICKER_MR_MASK          (1ull << 6u)
#define XTK_TIMEPICKER_MB_MASK          (1ull << 7u)
#define XTK_TIMEPICKER_TIP_MASK         (1ull << 8u)
#define XTK_TIMEPICKER_ANAME_MASK       (1ull << 9u)
#define XTK_TIMEPICKER_AID_MASK         (1ull << 10u)
#define XTK_TIMEPICKER_AHELP_MASK       (1ull << 11u)
#define XTK_TIMEPICKER_ADESC_MASK       (1ull << 12u)
#define XTK_TIMEPICKER_ASTATUS_MASK     (1ull << 13u)
#define XTK_TIMEPICKER_AITEM_MASK       (1ull << 14u)
#define XTK_TIMEPICKER_ACTYPE_MASK      (1ull << 15u)
#define XTK_TIMEPICKER_AACCEL_MASK      (1ull << 16u)
#define XTK_TIMEPICKER_AKEY_MASK        (1ull << 17u)
#define XTK_TIMEPICKER_ALANDMARK_MASK   (1ull << 18u)
#define XTK_TIMEPICKER_ALANDNAME_MASK   (1ull << 19u)
#define XTK_TIMEPICKER_ALIVE_MASK       (1ull << 20u)
#define XTK_TIMEPICKER_AHEADING_MASK    (1ull << 21u)
#define XTK_TIMEPICKER_AVIEW_MASK       (1ull << 22u)
#define XTK_TIMEPICKER_AREQUIRED_MASK   (1ull << 23u)
#define XTK_TIMEPICKER_AVALID_MASK      (1ull << 24u)
#define XTK_TIMEPICKER_APERIPHERAL_MASK (1ull << 25u)
#define XTK_TIMEPICKER_ADIALOG_MASK     (1ull << 26u)
#define XTK_TIMEPICKER_APOS_MASK        (1ull << 27u)
#define XTK_TIMEPICKER_ASIZE_MASK       (1ull << 28u)
#define XTK_TIMEPICKER_ALEVEL_MASK      (1ull << 29u)
#define XTK_TIMEPICKER_ACULTURE_MASK    (1ull << 30u)
#define XTK_TIMEPICKER_ALABEL_MASK      (1ull << 31u)
#define XTK_TIMEPICKER_ADESCRIBED_MASK  (1ull << 32u)
#define XTK_TIMEPICKER_AFLOWSTO_MASK    (1ull << 33u)
#define XTK_TIMEPICKER_AFLOWSFROM_MASK  (1ull << 34u)
#define XTK_TIMEPICKER_ACONTROLS_MASK   (1ull << 35u)
#define XTK_TIMEPICKER_ENABLED_MASK     (1ull << 36u)
#define XTK_TIMEPICKER_HEADER_MASK      (1ull << 37u)
#define XTK_TIMEPICKER_TIME_MASK        (1ull << 38u)
#define XTK_TIMEPICKER_CLOCK_MASK       (1ull << 39u)
#define XTK_TIMEPICKER_STEP_MASK        (1ull << 40u)

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
	char const     *aname;
	uint32_t        aname_len;
	char const     *aid;
	uint32_t        aid_len;
	char const     *ahelp;
	uint32_t        ahelp_len;
	char const     *adesc;
	uint32_t        adesc_len;
	char const     *astatus;
	uint32_t        astatus_len;
	char const     *aitem;
	uint32_t        aitem_len;
	char const     *actype;
	uint32_t        actype_len;
	char const     *aaccel;
	uint32_t        aaccel_len;
	char const     *akey;
	uint32_t        akey_len;
	XtkLandmark     alandmark;
	char const     *alandname;
	uint32_t        alandname_len;
	XtkLiveSetting  alive;
	XtkHeadingLevel aheading;
	XtkAccessView   aview;
	bool            arequired;
	bool            avalid;
	bool            aperipheral;
	bool            adialog;
	int32_t         apos;
	int32_t         asize;
	int32_t         alevel;
	int32_t         aculture;
	char const     *alabel;
	uint32_t        alabel_len;
	char const     *adescribed;
	uint32_t        adescribed_len;
	char const     *aflowsto;
	uint32_t        aflowsto_len;
	char const     *aflowsfrom;
	uint32_t        aflowsfrom_len;
	char const     *acontrols;
	uint32_t        acontrols_len;
	bool            enabled;
	int32_t         date;
	XtkCalendarMode mode;
	int32_t         mindate;
	int32_t         maxdate;
	int32_t         firstday;
} XtkCalendarProps;

#define XTK_CALENDAR_W_MASK           (1ull << 0u)
#define XTK_CALENDAR_H_MASK           (1ull << 1u)
#define XTK_CALENDAR_GROW_MASK        (1ull << 2u)
#define XTK_CALENDAR_SELF_MASK        (1ull << 3u)
#define XTK_CALENDAR_ML_MASK          (1ull << 4u)
#define XTK_CALENDAR_MT_MASK          (1ull << 5u)
#define XTK_CALENDAR_MR_MASK          (1ull << 6u)
#define XTK_CALENDAR_MB_MASK          (1ull << 7u)
#define XTK_CALENDAR_TIP_MASK         (1ull << 8u)
#define XTK_CALENDAR_ANAME_MASK       (1ull << 9u)
#define XTK_CALENDAR_AID_MASK         (1ull << 10u)
#define XTK_CALENDAR_AHELP_MASK       (1ull << 11u)
#define XTK_CALENDAR_ADESC_MASK       (1ull << 12u)
#define XTK_CALENDAR_ASTATUS_MASK     (1ull << 13u)
#define XTK_CALENDAR_AITEM_MASK       (1ull << 14u)
#define XTK_CALENDAR_ACTYPE_MASK      (1ull << 15u)
#define XTK_CALENDAR_AACCEL_MASK      (1ull << 16u)
#define XTK_CALENDAR_AKEY_MASK        (1ull << 17u)
#define XTK_CALENDAR_ALANDMARK_MASK   (1ull << 18u)
#define XTK_CALENDAR_ALANDNAME_MASK   (1ull << 19u)
#define XTK_CALENDAR_ALIVE_MASK       (1ull << 20u)
#define XTK_CALENDAR_AHEADING_MASK    (1ull << 21u)
#define XTK_CALENDAR_AVIEW_MASK       (1ull << 22u)
#define XTK_CALENDAR_AREQUIRED_MASK   (1ull << 23u)
#define XTK_CALENDAR_AVALID_MASK      (1ull << 24u)
#define XTK_CALENDAR_APERIPHERAL_MASK (1ull << 25u)
#define XTK_CALENDAR_ADIALOG_MASK     (1ull << 26u)
#define XTK_CALENDAR_APOS_MASK        (1ull << 27u)
#define XTK_CALENDAR_ASIZE_MASK       (1ull << 28u)
#define XTK_CALENDAR_ALEVEL_MASK      (1ull << 29u)
#define XTK_CALENDAR_ACULTURE_MASK    (1ull << 30u)
#define XTK_CALENDAR_ALABEL_MASK      (1ull << 31u)
#define XTK_CALENDAR_ADESCRIBED_MASK  (1ull << 32u)
#define XTK_CALENDAR_AFLOWSTO_MASK    (1ull << 33u)
#define XTK_CALENDAR_AFLOWSFROM_MASK  (1ull << 34u)
#define XTK_CALENDAR_ACONTROLS_MASK   (1ull << 35u)
#define XTK_CALENDAR_ENABLED_MASK     (1ull << 36u)
#define XTK_CALENDAR_DATE_MASK        (1ull << 37u)
#define XTK_CALENDAR_MODE_MASK        (1ull << 38u)
#define XTK_CALENDAR_MINDATE_MASK     (1ull << 39u)
#define XTK_CALENDAR_MAXDATE_MASK     (1ull << 40u)
#define XTK_CALENDAR_FIRSTDAY_MASK    (1ull << 41u)

typedef struct XtkColorPickerProps {
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
	char const     *aname;
	uint32_t        aname_len;
	char const     *aid;
	uint32_t        aid_len;
	char const     *ahelp;
	uint32_t        ahelp_len;
	char const     *adesc;
	uint32_t        adesc_len;
	char const     *astatus;
	uint32_t        astatus_len;
	char const     *aitem;
	uint32_t        aitem_len;
	char const     *actype;
	uint32_t        actype_len;
	char const     *aaccel;
	uint32_t        aaccel_len;
	char const     *akey;
	uint32_t        akey_len;
	XtkLandmark     alandmark;
	char const     *alandname;
	uint32_t        alandname_len;
	XtkLiveSetting  alive;
	XtkHeadingLevel aheading;
	XtkAccessView   aview;
	bool            arequired;
	bool            avalid;
	bool            aperipheral;
	bool            adialog;
	int32_t         apos;
	int32_t         asize;
	int32_t         alevel;
	int32_t         aculture;
	char const     *alabel;
	uint32_t        alabel_len;
	char const     *adescribed;
	uint32_t        adescribed_len;
	char const     *aflowsto;
	uint32_t        aflowsto_len;
	char const     *aflowsfrom;
	uint32_t        aflowsfrom_len;
	char const     *acontrols;
	uint32_t        acontrols_len;
	bool            enabled;
	XtkColor        color;
	bool            alpha;
	bool            morebutton;
	XtkSpectrum     spectrum;
} XtkColorPickerProps;

#define XTK_COLORPICKER_W_MASK           (1ull << 0u)
#define XTK_COLORPICKER_H_MASK           (1ull << 1u)
#define XTK_COLORPICKER_GROW_MASK        (1ull << 2u)
#define XTK_COLORPICKER_SELF_MASK        (1ull << 3u)
#define XTK_COLORPICKER_ML_MASK          (1ull << 4u)
#define XTK_COLORPICKER_MT_MASK          (1ull << 5u)
#define XTK_COLORPICKER_MR_MASK          (1ull << 6u)
#define XTK_COLORPICKER_MB_MASK          (1ull << 7u)
#define XTK_COLORPICKER_TIP_MASK         (1ull << 8u)
#define XTK_COLORPICKER_ANAME_MASK       (1ull << 9u)
#define XTK_COLORPICKER_AID_MASK         (1ull << 10u)
#define XTK_COLORPICKER_AHELP_MASK       (1ull << 11u)
#define XTK_COLORPICKER_ADESC_MASK       (1ull << 12u)
#define XTK_COLORPICKER_ASTATUS_MASK     (1ull << 13u)
#define XTK_COLORPICKER_AITEM_MASK       (1ull << 14u)
#define XTK_COLORPICKER_ACTYPE_MASK      (1ull << 15u)
#define XTK_COLORPICKER_AACCEL_MASK      (1ull << 16u)
#define XTK_COLORPICKER_AKEY_MASK        (1ull << 17u)
#define XTK_COLORPICKER_ALANDMARK_MASK   (1ull << 18u)
#define XTK_COLORPICKER_ALANDNAME_MASK   (1ull << 19u)
#define XTK_COLORPICKER_ALIVE_MASK       (1ull << 20u)
#define XTK_COLORPICKER_AHEADING_MASK    (1ull << 21u)
#define XTK_COLORPICKER_AVIEW_MASK       (1ull << 22u)
#define XTK_COLORPICKER_AREQUIRED_MASK   (1ull << 23u)
#define XTK_COLORPICKER_AVALID_MASK      (1ull << 24u)
#define XTK_COLORPICKER_APERIPHERAL_MASK (1ull << 25u)
#define XTK_COLORPICKER_ADIALOG_MASK     (1ull << 26u)
#define XTK_COLORPICKER_APOS_MASK        (1ull << 27u)
#define XTK_COLORPICKER_ASIZE_MASK       (1ull << 28u)
#define XTK_COLORPICKER_ALEVEL_MASK      (1ull << 29u)
#define XTK_COLORPICKER_ACULTURE_MASK    (1ull << 30u)
#define XTK_COLORPICKER_ALABEL_MASK      (1ull << 31u)
#define XTK_COLORPICKER_ADESCRIBED_MASK  (1ull << 32u)
#define XTK_COLORPICKER_AFLOWSTO_MASK    (1ull << 33u)
#define XTK_COLORPICKER_AFLOWSFROM_MASK  (1ull << 34u)
#define XTK_COLORPICKER_ACONTROLS_MASK   (1ull << 35u)
#define XTK_COLORPICKER_ENABLED_MASK     (1ull << 36u)
#define XTK_COLORPICKER_COLOR_MASK       (1ull << 37u)
#define XTK_COLORPICKER_ALPHA_MASK       (1ull << 38u)
#define XTK_COLORPICKER_MOREBUTTON_MASK  (1ull << 39u)
#define XTK_COLORPICKER_SPECTRUM_MASK    (1ull << 40u)

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
	char const      *aname;
	uint32_t         aname_len;
	char const      *aid;
	uint32_t         aid_len;
	char const      *ahelp;
	uint32_t         ahelp_len;
	char const      *adesc;
	uint32_t         adesc_len;
	char const      *astatus;
	uint32_t         astatus_len;
	char const      *aitem;
	uint32_t         aitem_len;
	char const      *actype;
	uint32_t         actype_len;
	char const      *aaccel;
	uint32_t         aaccel_len;
	char const      *akey;
	uint32_t         akey_len;
	XtkLandmark      alandmark;
	char const      *alandname;
	uint32_t         alandname_len;
	XtkLiveSetting   alive;
	XtkHeadingLevel  aheading;
	XtkAccessView    aview;
	bool             arequired;
	bool             avalid;
	bool             aperipheral;
	bool             adialog;
	int32_t          apos;
	int32_t          asize;
	int32_t          alevel;
	int32_t          aculture;
	char const      *alabel;
	uint32_t         alabel_len;
	char const      *adescribed;
	uint32_t         adescribed_len;
	char const      *aflowsto;
	uint32_t         aflowsto_len;
	char const      *aflowsfrom;
	uint32_t         aflowsfrom_len;
	char const      *acontrols;
	uint32_t         acontrols_len;
	XtkTextAlign     align;
	bool             enabled;
	bool             resizable;
	XtkSortDirection sort;
} XtkColumnProps;

#define XTK_COLUMN_W_MASK           (1ull << 0u)
#define XTK_COLUMN_MINW_MASK        (1ull << 1u)
#define XTK_COLUMN_MAXW_MASK        (1ull << 2u)
#define XTK_COLUMN_TEXT_MASK        (1ull << 3u)
#define XTK_COLUMN_TIP_MASK         (1ull << 4u)
#define XTK_COLUMN_ANAME_MASK       (1ull << 5u)
#define XTK_COLUMN_AID_MASK         (1ull << 6u)
#define XTK_COLUMN_AHELP_MASK       (1ull << 7u)
#define XTK_COLUMN_ADESC_MASK       (1ull << 8u)
#define XTK_COLUMN_ASTATUS_MASK     (1ull << 9u)
#define XTK_COLUMN_AITEM_MASK       (1ull << 10u)
#define XTK_COLUMN_ACTYPE_MASK      (1ull << 11u)
#define XTK_COLUMN_AACCEL_MASK      (1ull << 12u)
#define XTK_COLUMN_AKEY_MASK        (1ull << 13u)
#define XTK_COLUMN_ALANDMARK_MASK   (1ull << 14u)
#define XTK_COLUMN_ALANDNAME_MASK   (1ull << 15u)
#define XTK_COLUMN_ALIVE_MASK       (1ull << 16u)
#define XTK_COLUMN_AHEADING_MASK    (1ull << 17u)
#define XTK_COLUMN_AVIEW_MASK       (1ull << 18u)
#define XTK_COLUMN_AREQUIRED_MASK   (1ull << 19u)
#define XTK_COLUMN_AVALID_MASK      (1ull << 20u)
#define XTK_COLUMN_APERIPHERAL_MASK (1ull << 21u)
#define XTK_COLUMN_ADIALOG_MASK     (1ull << 22u)
#define XTK_COLUMN_APOS_MASK        (1ull << 23u)
#define XTK_COLUMN_ASIZE_MASK       (1ull << 24u)
#define XTK_COLUMN_ALEVEL_MASK      (1ull << 25u)
#define XTK_COLUMN_ACULTURE_MASK    (1ull << 26u)
#define XTK_COLUMN_ALABEL_MASK      (1ull << 27u)
#define XTK_COLUMN_ADESCRIBED_MASK  (1ull << 28u)
#define XTK_COLUMN_AFLOWSTO_MASK    (1ull << 29u)
#define XTK_COLUMN_AFLOWSFROM_MASK  (1ull << 30u)
#define XTK_COLUMN_ACONTROLS_MASK   (1ull << 31u)
#define XTK_COLUMN_ALIGN_MASK       (1ull << 32u)
#define XTK_COLUMN_ENABLED_MASK     (1ull << 33u)
#define XTK_COLUMN_RESIZABLE_MASK   (1ull << 34u)
#define XTK_COLUMN_SORT_MASK        (1ull << 35u)

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
	char const       *aname;
	uint32_t          aname_len;
	char const       *aid;
	uint32_t          aid_len;
	char const       *ahelp;
	uint32_t          ahelp_len;
	char const       *adesc;
	uint32_t          adesc_len;
	char const       *astatus;
	uint32_t          astatus_len;
	char const       *aitem;
	uint32_t          aitem_len;
	char const       *actype;
	uint32_t          actype_len;
	char const       *aaccel;
	uint32_t          aaccel_len;
	char const       *akey;
	uint32_t          akey_len;
	XtkLandmark       alandmark;
	char const       *alandname;
	uint32_t          alandname_len;
	XtkLiveSetting    alive;
	XtkHeadingLevel   aheading;
	XtkAccessView     aview;
	bool              arequired;
	bool              avalid;
	bool              aperipheral;
	bool              adialog;
	int32_t           apos;
	int32_t           asize;
	int32_t           alevel;
	int32_t           aculture;
	char const       *alabel;
	uint32_t          alabel_len;
	char const       *adescribed;
	uint32_t          adescribed_len;
	char const       *aflowsto;
	uint32_t          aflowsto_len;
	char const       *aflowsfrom;
	uint32_t          aflowsfrom_len;
	char const       *acontrols;
	uint32_t          acontrols_len;
	bool              enabled;
	bool              open;
	bool              sticky;
	XtkAppBarMode     mode;
	XtkLabelPosition  labels;
	XtkOverflowButton more;
	bool              dynamic;
} XtkCommandBarProps;

#define XTK_COMMANDBAR_W_MASK           (1ull << 0u)
#define XTK_COMMANDBAR_H_MASK           (1ull << 1u)
#define XTK_COMMANDBAR_GROW_MASK        (1ull << 2u)
#define XTK_COMMANDBAR_SELF_MASK        (1ull << 3u)
#define XTK_COMMANDBAR_ML_MASK          (1ull << 4u)
#define XTK_COMMANDBAR_MT_MASK          (1ull << 5u)
#define XTK_COMMANDBAR_MR_MASK          (1ull << 6u)
#define XTK_COMMANDBAR_MB_MASK          (1ull << 7u)
#define XTK_COMMANDBAR_TIP_MASK         (1ull << 8u)
#define XTK_COMMANDBAR_ANAME_MASK       (1ull << 9u)
#define XTK_COMMANDBAR_AID_MASK         (1ull << 10u)
#define XTK_COMMANDBAR_AHELP_MASK       (1ull << 11u)
#define XTK_COMMANDBAR_ADESC_MASK       (1ull << 12u)
#define XTK_COMMANDBAR_ASTATUS_MASK     (1ull << 13u)
#define XTK_COMMANDBAR_AITEM_MASK       (1ull << 14u)
#define XTK_COMMANDBAR_ACTYPE_MASK      (1ull << 15u)
#define XTK_COMMANDBAR_AACCEL_MASK      (1ull << 16u)
#define XTK_COMMANDBAR_AKEY_MASK        (1ull << 17u)
#define XTK_COMMANDBAR_ALANDMARK_MASK   (1ull << 18u)
#define XTK_COMMANDBAR_ALANDNAME_MASK   (1ull << 19u)
#define XTK_COMMANDBAR_ALIVE_MASK       (1ull << 20u)
#define XTK_COMMANDBAR_AHEADING_MASK    (1ull << 21u)
#define XTK_COMMANDBAR_AVIEW_MASK       (1ull << 22u)
#define XTK_COMMANDBAR_AREQUIRED_MASK   (1ull << 23u)
#define XTK_COMMANDBAR_AVALID_MASK      (1ull << 24u)
#define XTK_COMMANDBAR_APERIPHERAL_MASK (1ull << 25u)
#define XTK_COMMANDBAR_ADIALOG_MASK     (1ull << 26u)
#define XTK_COMMANDBAR_APOS_MASK        (1ull << 27u)
#define XTK_COMMANDBAR_ASIZE_MASK       (1ull << 28u)
#define XTK_COMMANDBAR_ALEVEL_MASK      (1ull << 29u)
#define XTK_COMMANDBAR_ACULTURE_MASK    (1ull << 30u)
#define XTK_COMMANDBAR_ALABEL_MASK      (1ull << 31u)
#define XTK_COMMANDBAR_ADESCRIBED_MASK  (1ull << 32u)
#define XTK_COMMANDBAR_AFLOWSTO_MASK    (1ull << 33u)
#define XTK_COMMANDBAR_AFLOWSFROM_MASK  (1ull << 34u)
#define XTK_COMMANDBAR_ACONTROLS_MASK   (1ull << 35u)
#define XTK_COMMANDBAR_ENABLED_MASK     (1ull << 36u)
#define XTK_COMMANDBAR_OPEN_MASK        (1ull << 37u)
#define XTK_COMMANDBAR_STICKY_MASK      (1ull << 38u)
#define XTK_COMMANDBAR_MODE_MASK        (1ull << 39u)
#define XTK_COMMANDBAR_LABELS_MASK      (1ull << 40u)
#define XTK_COMMANDBAR_MORE_MASK        (1ull << 41u)
#define XTK_COMMANDBAR_DYNAMIC_MASK     (1ull << 42u)

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
	char const     *aname;
	uint32_t        aname_len;
	char const     *aid;
	uint32_t        aid_len;
	char const     *ahelp;
	uint32_t        ahelp_len;
	char const     *adesc;
	uint32_t        adesc_len;
	char const     *astatus;
	uint32_t        astatus_len;
	char const     *aitem;
	uint32_t        aitem_len;
	char const     *actype;
	uint32_t        actype_len;
	char const     *aaccel;
	uint32_t        aaccel_len;
	char const     *akey;
	uint32_t        akey_len;
	XtkLandmark     alandmark;
	char const     *alandname;
	uint32_t        alandname_len;
	XtkLiveSetting  alive;
	XtkHeadingLevel aheading;
	XtkAccessView   aview;
	bool            arequired;
	bool            avalid;
	bool            aperipheral;
	bool            adialog;
	int32_t         apos;
	int32_t         asize;
	int32_t         alevel;
	int32_t         aculture;
	char const     *alabel;
	uint32_t        alabel_len;
	char const     *adescribed;
	uint32_t        adescribed_len;
	char const     *aflowsto;
	uint32_t        aflowsto_len;
	char const     *aflowsfrom;
	uint32_t        aflowsfrom_len;
	char const     *acontrols;
	uint32_t        acontrols_len;
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

#define XTK_APPBARBUTTON_W_MASK           (1ull << 0u)
#define XTK_APPBARBUTTON_H_MASK           (1ull << 1u)
#define XTK_APPBARBUTTON_GROW_MASK        (1ull << 2u)
#define XTK_APPBARBUTTON_SELF_MASK        (1ull << 3u)
#define XTK_APPBARBUTTON_ML_MASK          (1ull << 4u)
#define XTK_APPBARBUTTON_MT_MASK          (1ull << 5u)
#define XTK_APPBARBUTTON_MR_MASK          (1ull << 6u)
#define XTK_APPBARBUTTON_MB_MASK          (1ull << 7u)
#define XTK_APPBARBUTTON_TIP_MASK         (1ull << 8u)
#define XTK_APPBARBUTTON_ANAME_MASK       (1ull << 9u)
#define XTK_APPBARBUTTON_AID_MASK         (1ull << 10u)
#define XTK_APPBARBUTTON_AHELP_MASK       (1ull << 11u)
#define XTK_APPBARBUTTON_ADESC_MASK       (1ull << 12u)
#define XTK_APPBARBUTTON_ASTATUS_MASK     (1ull << 13u)
#define XTK_APPBARBUTTON_AITEM_MASK       (1ull << 14u)
#define XTK_APPBARBUTTON_ACTYPE_MASK      (1ull << 15u)
#define XTK_APPBARBUTTON_AACCEL_MASK      (1ull << 16u)
#define XTK_APPBARBUTTON_AKEY_MASK        (1ull << 17u)
#define XTK_APPBARBUTTON_ALANDMARK_MASK   (1ull << 18u)
#define XTK_APPBARBUTTON_ALANDNAME_MASK   (1ull << 19u)
#define XTK_APPBARBUTTON_ALIVE_MASK       (1ull << 20u)
#define XTK_APPBARBUTTON_AHEADING_MASK    (1ull << 21u)
#define XTK_APPBARBUTTON_AVIEW_MASK       (1ull << 22u)
#define XTK_APPBARBUTTON_AREQUIRED_MASK   (1ull << 23u)
#define XTK_APPBARBUTTON_AVALID_MASK      (1ull << 24u)
#define XTK_APPBARBUTTON_APERIPHERAL_MASK (1ull << 25u)
#define XTK_APPBARBUTTON_ADIALOG_MASK     (1ull << 26u)
#define XTK_APPBARBUTTON_APOS_MASK        (1ull << 27u)
#define XTK_APPBARBUTTON_ASIZE_MASK       (1ull << 28u)
#define XTK_APPBARBUTTON_ALEVEL_MASK      (1ull << 29u)
#define XTK_APPBARBUTTON_ACULTURE_MASK    (1ull << 30u)
#define XTK_APPBARBUTTON_ALABEL_MASK      (1ull << 31u)
#define XTK_APPBARBUTTON_ADESCRIBED_MASK  (1ull << 32u)
#define XTK_APPBARBUTTON_AFLOWSTO_MASK    (1ull << 33u)
#define XTK_APPBARBUTTON_AFLOWSFROM_MASK  (1ull << 34u)
#define XTK_APPBARBUTTON_ACONTROLS_MASK   (1ull << 35u)
#define XTK_APPBARBUTTON_TEXT_MASK        (1ull << 36u)
#define XTK_APPBARBUTTON_ICON_MASK        (1ull << 37u)
#define XTK_APPBARBUTTON_ENABLED_MASK     (1ull << 38u)
#define XTK_APPBARBUTTON_LABELPOS_MASK    (1ull << 39u)
#define XTK_APPBARBUTTON_ACCEL_MASK       (1ull << 40u)
#define XTK_APPBARBUTTON_SECONDARY_MASK   (1ull << 41u)
#define XTK_APPBARBUTTON_ORDER_MASK       (1ull << 42u)

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
	char const     *aname;
	uint32_t        aname_len;
	char const     *aid;
	uint32_t        aid_len;
	char const     *ahelp;
	uint32_t        ahelp_len;
	char const     *adesc;
	uint32_t        adesc_len;
	char const     *astatus;
	uint32_t        astatus_len;
	char const     *aitem;
	uint32_t        aitem_len;
	char const     *actype;
	uint32_t        actype_len;
	char const     *aaccel;
	uint32_t        aaccel_len;
	char const     *akey;
	uint32_t        akey_len;
	XtkLandmark     alandmark;
	char const     *alandname;
	uint32_t        alandname_len;
	XtkLiveSetting  alive;
	XtkHeadingLevel aheading;
	XtkAccessView   aview;
	bool            arequired;
	bool            avalid;
	bool            aperipheral;
	bool            adialog;
	int32_t         apos;
	int32_t         asize;
	int32_t         alevel;
	int32_t         aculture;
	char const     *alabel;
	uint32_t        alabel_len;
	char const     *adescribed;
	uint32_t        adescribed_len;
	char const     *aflowsto;
	uint32_t        aflowsto_len;
	char const     *aflowsfrom;
	uint32_t        aflowsfrom_len;
	char const     *acontrols;
	uint32_t        acontrols_len;
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

#define XTK_APPBARTOGGLE_W_MASK           (1ull << 0u)
#define XTK_APPBARTOGGLE_H_MASK           (1ull << 1u)
#define XTK_APPBARTOGGLE_GROW_MASK        (1ull << 2u)
#define XTK_APPBARTOGGLE_SELF_MASK        (1ull << 3u)
#define XTK_APPBARTOGGLE_ML_MASK          (1ull << 4u)
#define XTK_APPBARTOGGLE_MT_MASK          (1ull << 5u)
#define XTK_APPBARTOGGLE_MR_MASK          (1ull << 6u)
#define XTK_APPBARTOGGLE_MB_MASK          (1ull << 7u)
#define XTK_APPBARTOGGLE_TIP_MASK         (1ull << 8u)
#define XTK_APPBARTOGGLE_ANAME_MASK       (1ull << 9u)
#define XTK_APPBARTOGGLE_AID_MASK         (1ull << 10u)
#define XTK_APPBARTOGGLE_AHELP_MASK       (1ull << 11u)
#define XTK_APPBARTOGGLE_ADESC_MASK       (1ull << 12u)
#define XTK_APPBARTOGGLE_ASTATUS_MASK     (1ull << 13u)
#define XTK_APPBARTOGGLE_AITEM_MASK       (1ull << 14u)
#define XTK_APPBARTOGGLE_ACTYPE_MASK      (1ull << 15u)
#define XTK_APPBARTOGGLE_AACCEL_MASK      (1ull << 16u)
#define XTK_APPBARTOGGLE_AKEY_MASK        (1ull << 17u)
#define XTK_APPBARTOGGLE_ALANDMARK_MASK   (1ull << 18u)
#define XTK_APPBARTOGGLE_ALANDNAME_MASK   (1ull << 19u)
#define XTK_APPBARTOGGLE_ALIVE_MASK       (1ull << 20u)
#define XTK_APPBARTOGGLE_AHEADING_MASK    (1ull << 21u)
#define XTK_APPBARTOGGLE_AVIEW_MASK       (1ull << 22u)
#define XTK_APPBARTOGGLE_AREQUIRED_MASK   (1ull << 23u)
#define XTK_APPBARTOGGLE_AVALID_MASK      (1ull << 24u)
#define XTK_APPBARTOGGLE_APERIPHERAL_MASK (1ull << 25u)
#define XTK_APPBARTOGGLE_ADIALOG_MASK     (1ull << 26u)
#define XTK_APPBARTOGGLE_APOS_MASK        (1ull << 27u)
#define XTK_APPBARTOGGLE_ASIZE_MASK       (1ull << 28u)
#define XTK_APPBARTOGGLE_ALEVEL_MASK      (1ull << 29u)
#define XTK_APPBARTOGGLE_ACULTURE_MASK    (1ull << 30u)
#define XTK_APPBARTOGGLE_ALABEL_MASK      (1ull << 31u)
#define XTK_APPBARTOGGLE_ADESCRIBED_MASK  (1ull << 32u)
#define XTK_APPBARTOGGLE_AFLOWSTO_MASK    (1ull << 33u)
#define XTK_APPBARTOGGLE_AFLOWSFROM_MASK  (1ull << 34u)
#define XTK_APPBARTOGGLE_ACONTROLS_MASK   (1ull << 35u)
#define XTK_APPBARTOGGLE_TEXT_MASK        (1ull << 36u)
#define XTK_APPBARTOGGLE_ICON_MASK        (1ull << 37u)
#define XTK_APPBARTOGGLE_ENABLED_MASK     (1ull << 38u)
#define XTK_APPBARTOGGLE_LABELPOS_MASK    (1ull << 39u)
#define XTK_APPBARTOGGLE_ACCEL_MASK       (1ull << 40u)
#define XTK_APPBARTOGGLE_CHECKED_MASK     (1ull << 41u)
#define XTK_APPBARTOGGLE_SECONDARY_MASK   (1ull << 42u)
#define XTK_APPBARTOGGLE_ORDER_MASK       (1ull << 43u)

typedef struct XtkAppBarSeparatorProps {
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
	char const     *aname;
	uint32_t        aname_len;
	char const     *aid;
	uint32_t        aid_len;
	char const     *ahelp;
	uint32_t        ahelp_len;
	char const     *adesc;
	uint32_t        adesc_len;
	char const     *astatus;
	uint32_t        astatus_len;
	char const     *aitem;
	uint32_t        aitem_len;
	char const     *actype;
	uint32_t        actype_len;
	char const     *aaccel;
	uint32_t        aaccel_len;
	char const     *akey;
	uint32_t        akey_len;
	XtkLandmark     alandmark;
	char const     *alandname;
	uint32_t        alandname_len;
	XtkLiveSetting  alive;
	XtkHeadingLevel aheading;
	XtkAccessView   aview;
	bool            arequired;
	bool            avalid;
	bool            aperipheral;
	bool            adialog;
	int32_t         apos;
	int32_t         asize;
	int32_t         alevel;
	int32_t         aculture;
	char const     *alabel;
	uint32_t        alabel_len;
	char const     *adescribed;
	uint32_t        adescribed_len;
	char const     *aflowsto;
	uint32_t        aflowsto_len;
	char const     *aflowsfrom;
	uint32_t        aflowsfrom_len;
	char const     *acontrols;
	uint32_t        acontrols_len;
	bool            secondary;
	int32_t         order;
} XtkAppBarSeparatorProps;

#define XTK_APPBARSEP_W_MASK           (1ull << 0u)
#define XTK_APPBARSEP_H_MASK           (1ull << 1u)
#define XTK_APPBARSEP_GROW_MASK        (1ull << 2u)
#define XTK_APPBARSEP_SELF_MASK        (1ull << 3u)
#define XTK_APPBARSEP_ML_MASK          (1ull << 4u)
#define XTK_APPBARSEP_MT_MASK          (1ull << 5u)
#define XTK_APPBARSEP_MR_MASK          (1ull << 6u)
#define XTK_APPBARSEP_MB_MASK          (1ull << 7u)
#define XTK_APPBARSEP_TIP_MASK         (1ull << 8u)
#define XTK_APPBARSEP_ANAME_MASK       (1ull << 9u)
#define XTK_APPBARSEP_AID_MASK         (1ull << 10u)
#define XTK_APPBARSEP_AHELP_MASK       (1ull << 11u)
#define XTK_APPBARSEP_ADESC_MASK       (1ull << 12u)
#define XTK_APPBARSEP_ASTATUS_MASK     (1ull << 13u)
#define XTK_APPBARSEP_AITEM_MASK       (1ull << 14u)
#define XTK_APPBARSEP_ACTYPE_MASK      (1ull << 15u)
#define XTK_APPBARSEP_AACCEL_MASK      (1ull << 16u)
#define XTK_APPBARSEP_AKEY_MASK        (1ull << 17u)
#define XTK_APPBARSEP_ALANDMARK_MASK   (1ull << 18u)
#define XTK_APPBARSEP_ALANDNAME_MASK   (1ull << 19u)
#define XTK_APPBARSEP_ALIVE_MASK       (1ull << 20u)
#define XTK_APPBARSEP_AHEADING_MASK    (1ull << 21u)
#define XTK_APPBARSEP_AVIEW_MASK       (1ull << 22u)
#define XTK_APPBARSEP_AREQUIRED_MASK   (1ull << 23u)
#define XTK_APPBARSEP_AVALID_MASK      (1ull << 24u)
#define XTK_APPBARSEP_APERIPHERAL_MASK (1ull << 25u)
#define XTK_APPBARSEP_ADIALOG_MASK     (1ull << 26u)
#define XTK_APPBARSEP_APOS_MASK        (1ull << 27u)
#define XTK_APPBARSEP_ASIZE_MASK       (1ull << 28u)
#define XTK_APPBARSEP_ALEVEL_MASK      (1ull << 29u)
#define XTK_APPBARSEP_ACULTURE_MASK    (1ull << 30u)
#define XTK_APPBARSEP_ALABEL_MASK      (1ull << 31u)
#define XTK_APPBARSEP_ADESCRIBED_MASK  (1ull << 32u)
#define XTK_APPBARSEP_AFLOWSTO_MASK    (1ull << 33u)
#define XTK_APPBARSEP_AFLOWSFROM_MASK  (1ull << 34u)
#define XTK_APPBARSEP_ACONTROLS_MASK   (1ull << 35u)
#define XTK_APPBARSEP_SECONDARY_MASK   (1ull << 36u)
#define XTK_APPBARSEP_ORDER_MASK       (1ull << 37u)

typedef struct XtkNavSlotProps {
	uint64_t       set;
	XtkChangeStamp stamp;
	float          w;
	float          h;
	float          grow;
	float          shrink;
	XentFlexAlign  self;
	XtkNavSlot     slot;
} XtkNavSlotProps;

#define XTK_NAVSLOT_W_MASK      (1ull << 0u)
#define XTK_NAVSLOT_H_MASK      (1ull << 1u)
#define XTK_NAVSLOT_GROW_MASK   (1ull << 2u)
#define XTK_NAVSLOT_SHRINK_MASK (1ull << 3u)
#define XTK_NAVSLOT_SELF_MASK   (1ull << 4u)
#define XTK_NAVSLOT_SLOT_MASK   (1ull << 5u)

typedef struct XtkFrameProps {
	uint64_t             set;
	XtkChangeStamp       stamp;
	float                w;
	float                h;
	float                grow;
	float                shrink;
	XentFlexAlign        self;
	XtkNavTransitionKind transition;
	bool                 is_back;
	int32_t              page_key;
} XtkFrameProps;

#define XTK_FRAME_W_MASK          (1ull << 0u)
#define XTK_FRAME_H_MASK          (1ull << 1u)
#define XTK_FRAME_GROW_MASK       (1ull << 2u)
#define XTK_FRAME_SHRINK_MASK     (1ull << 3u)
#define XTK_FRAME_SELF_MASK       (1ull << 4u)
#define XTK_FRAME_TRANSITION_MASK (1ull << 5u)
#define XTK_FRAME_IS_BACK_MASK    (1ull << 6u)
#define XTK_FRAME_PAGE_KEY_MASK   (1ull << 7u)

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
XtkLocalId xtk_groupheader_create(XtkTxn *txn, XtkNodeRef parent, XtkLayoutProps const *props);
XtkLocalId xtk_navslot_create(XtkTxn *txn, XtkNodeRef parent, XtkNavSlotProps const *props);
XtkLocalId xtk_frame_create(XtkTxn *txn, XtkNodeRef parent, XtkFrameProps const *props);
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
bool xtk_container_setaname(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_container_setaid(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_container_setahelp(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_container_setadesc(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_container_setastatus(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_container_setaitem(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_container_setactype(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_container_setaaccel(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_container_setakey(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_container_setalandmark(XtkScene *scene, XtkCtrl control, XtkLandmark value, XtkChangeStamp change);
bool xtk_container_setalandname(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
);
bool xtk_container_setalive(XtkScene *scene, XtkCtrl control, XtkLiveSetting value, XtkChangeStamp change);
bool xtk_container_setaheading(XtkScene *scene, XtkCtrl control, XtkHeadingLevel value, XtkChangeStamp change);
bool xtk_container_setaview(XtkScene *scene, XtkCtrl control, XtkAccessView value, XtkChangeStamp change);
bool xtk_container_setarequired(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_container_setavalid(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_container_setaperipheral(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_container_setadialog(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_container_setapos(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_container_setasize(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_container_setalevel(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_container_setaculture(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_container_setalabel(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_container_setadescribed(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
);
bool xtk_container_setaflowsto(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_container_setaflowsfrom(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
);
bool xtk_container_setacontrols(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
);
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
bool      xtk_container_setflow(XtkScene *scene, XtkCtrl control, XentDirection value, XtkChangeStamp change);
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
bool      xtk_text_setaname(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_text_setaid(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_text_setahelp(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_text_setadesc(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_text_setastatus(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_text_setaitem(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_text_setactype(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_text_setaaccel(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_text_setakey(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_text_setalandmark(XtkScene *scene, XtkCtrl control, XtkLandmark value, XtkChangeStamp change);
bool xtk_text_setalandname(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_text_setalive(XtkScene *scene, XtkCtrl control, XtkLiveSetting value, XtkChangeStamp change);
bool xtk_text_setaheading(XtkScene *scene, XtkCtrl control, XtkHeadingLevel value, XtkChangeStamp change);
bool xtk_text_setaview(XtkScene *scene, XtkCtrl control, XtkAccessView value, XtkChangeStamp change);
bool xtk_text_setarequired(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_text_setavalid(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_text_setaperipheral(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_text_setadialog(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_text_setapos(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_text_setasize(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_text_setalevel(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_text_setaculture(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_text_setalabel(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_text_setadescribed(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_text_setaflowsto(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_text_setaflowsfrom(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_text_setacontrols(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_text_setfontsize(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_text_setfontweight(XtkScene *scene, XtkCtrl control, XtkFontWeight value, XtkChangeStamp change);
bool xtk_text_settextalign(XtkScene *scene, XtkCtrl control, XtkTextAlign value, XtkChangeStamp change);
bool xtk_text_setfg(XtkScene *scene, XtkCtrl control, XtkColor value, XtkChangeStamp change);
bool xtk_text_setmaxlines(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_text_settrim(XtkScene *scene, XtkCtrl control, XtkTextTrim value, XtkChangeStamp change);
bool xtk_text_settextwrap(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_text_setselectable(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_button_setw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_button_seth(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_button_setgrow(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_button_setself(XtkScene *scene, XtkCtrl control, XentFlexAlign value, XtkChangeStamp change);
bool xtk_button_setml(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_button_setmt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_button_setmr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_button_setmb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_button_settext(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_button_settip(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_button_setaname(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_button_setaid(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_button_setahelp(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_button_setadesc(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_button_setastatus(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_button_setaitem(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_button_setactype(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_button_setaaccel(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_button_setakey(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_button_setalandmark(XtkScene *scene, XtkCtrl control, XtkLandmark value, XtkChangeStamp change);
bool xtk_button_setalandname(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_button_setalive(XtkScene *scene, XtkCtrl control, XtkLiveSetting value, XtkChangeStamp change);
bool xtk_button_setaheading(XtkScene *scene, XtkCtrl control, XtkHeadingLevel value, XtkChangeStamp change);
bool xtk_button_setaview(XtkScene *scene, XtkCtrl control, XtkAccessView value, XtkChangeStamp change);
bool xtk_button_setarequired(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_button_setavalid(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_button_setaperipheral(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_button_setadialog(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_button_setapos(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_button_setasize(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_button_setalevel(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_button_setaculture(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_button_setalabel(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_button_setadescribed(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_button_setaflowsto(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_button_setaflowsfrom(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_button_setacontrols(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_button_setenabled(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_button_seticon(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_button_setstyle(XtkScene *scene, XtkCtrl control, XtkButtonStyle value, XtkChangeStamp change);
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
bool      xtk_toggle_setaname(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_toggle_setaid(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_toggle_setahelp(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_toggle_setadesc(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_toggle_setastatus(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_toggle_setaitem(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_toggle_setactype(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_toggle_setaaccel(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_toggle_setakey(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_toggle_setalandmark(XtkScene *scene, XtkCtrl control, XtkLandmark value, XtkChangeStamp change);
bool xtk_toggle_setalandname(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_toggle_setalive(XtkScene *scene, XtkCtrl control, XtkLiveSetting value, XtkChangeStamp change);
bool xtk_toggle_setaheading(XtkScene *scene, XtkCtrl control, XtkHeadingLevel value, XtkChangeStamp change);
bool xtk_toggle_setaview(XtkScene *scene, XtkCtrl control, XtkAccessView value, XtkChangeStamp change);
bool xtk_toggle_setarequired(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_toggle_setavalid(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_toggle_setaperipheral(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_toggle_setadialog(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_toggle_setapos(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_toggle_setasize(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_toggle_setalevel(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_toggle_setaculture(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_toggle_setalabel(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_toggle_setadescribed(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_toggle_setaflowsto(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_toggle_setaflowsfrom(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_toggle_setacontrols(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_toggle_setenabled(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_toggle_setchecked(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
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
bool xtk_checkbox_setaname(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_checkbox_setaid(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_checkbox_setahelp(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_checkbox_setadesc(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_checkbox_setastatus(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_checkbox_setaitem(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_checkbox_setactype(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_checkbox_setaaccel(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_checkbox_setakey(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_checkbox_setalandmark(XtkScene *scene, XtkCtrl control, XtkLandmark value, XtkChangeStamp change);
bool xtk_checkbox_setalandname(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_checkbox_setalive(XtkScene *scene, XtkCtrl control, XtkLiveSetting value, XtkChangeStamp change);
bool xtk_checkbox_setaheading(XtkScene *scene, XtkCtrl control, XtkHeadingLevel value, XtkChangeStamp change);
bool xtk_checkbox_setaview(XtkScene *scene, XtkCtrl control, XtkAccessView value, XtkChangeStamp change);
bool xtk_checkbox_setarequired(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_checkbox_setavalid(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_checkbox_setaperipheral(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_checkbox_setadialog(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_checkbox_setapos(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_checkbox_setasize(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_checkbox_setalevel(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_checkbox_setaculture(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_checkbox_setalabel(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_checkbox_setadescribed(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
);
bool xtk_checkbox_setaflowsto(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_checkbox_setaflowsfrom(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
);
bool xtk_checkbox_setacontrols(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_checkbox_setenabled(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_checkbox_setchecked(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_checkbox_setindeterminate(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_checkbox_setthreestate(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
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
bool      xtk_radio_setaname(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_radio_setaid(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_radio_setahelp(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_radio_setadesc(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_radio_setastatus(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_radio_setaitem(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_radio_setactype(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_radio_setaaccel(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_radio_setakey(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_radio_setalandmark(XtkScene *scene, XtkCtrl control, XtkLandmark value, XtkChangeStamp change);
bool xtk_radio_setalandname(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_radio_setalive(XtkScene *scene, XtkCtrl control, XtkLiveSetting value, XtkChangeStamp change);
bool xtk_radio_setaheading(XtkScene *scene, XtkCtrl control, XtkHeadingLevel value, XtkChangeStamp change);
bool xtk_radio_setaview(XtkScene *scene, XtkCtrl control, XtkAccessView value, XtkChangeStamp change);
bool xtk_radio_setarequired(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_radio_setavalid(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_radio_setaperipheral(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_radio_setadialog(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_radio_setapos(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_radio_setasize(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_radio_setalevel(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_radio_setaculture(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_radio_setalabel(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_radio_setadescribed(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_radio_setaflowsto(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_radio_setaflowsfrom(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_radio_setacontrols(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_radio_setenabled(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_radio_setchecked(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
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
bool      xtk_switch_setaname(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_switch_setaid(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_switch_setahelp(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_switch_setadesc(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_switch_setastatus(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_switch_setaitem(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_switch_setactype(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_switch_setaaccel(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_switch_setakey(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_switch_setalandmark(XtkScene *scene, XtkCtrl control, XtkLandmark value, XtkChangeStamp change);
bool xtk_switch_setalandname(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_switch_setalive(XtkScene *scene, XtkCtrl control, XtkLiveSetting value, XtkChangeStamp change);
bool xtk_switch_setaheading(XtkScene *scene, XtkCtrl control, XtkHeadingLevel value, XtkChangeStamp change);
bool xtk_switch_setaview(XtkScene *scene, XtkCtrl control, XtkAccessView value, XtkChangeStamp change);
bool xtk_switch_setarequired(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_switch_setavalid(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_switch_setaperipheral(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_switch_setadialog(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_switch_setapos(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_switch_setasize(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_switch_setalevel(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_switch_setaculture(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_switch_setalabel(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_switch_setadescribed(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_switch_setaflowsto(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_switch_setaflowsfrom(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_switch_setacontrols(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_switch_setenabled(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_switch_setchecked(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
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
bool      xtk_slider_setaname(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_slider_setaid(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_slider_setahelp(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_slider_setadesc(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_slider_setastatus(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_slider_setaitem(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_slider_setactype(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_slider_setaaccel(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_slider_setakey(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_slider_setalandmark(XtkScene *scene, XtkCtrl control, XtkLandmark value, XtkChangeStamp change);
bool xtk_slider_setalandname(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_slider_setalive(XtkScene *scene, XtkCtrl control, XtkLiveSetting value, XtkChangeStamp change);
bool xtk_slider_setaheading(XtkScene *scene, XtkCtrl control, XtkHeadingLevel value, XtkChangeStamp change);
bool xtk_slider_setaview(XtkScene *scene, XtkCtrl control, XtkAccessView value, XtkChangeStamp change);
bool xtk_slider_setarequired(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_slider_setavalid(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_slider_setaperipheral(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_slider_setadialog(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_slider_setapos(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_slider_setasize(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_slider_setalevel(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_slider_setaculture(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_slider_setalabel(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_slider_setadescribed(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_slider_setaflowsto(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_slider_setaflowsfrom(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_slider_setacontrols(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_slider_setenabled(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_slider_setmin(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_slider_setmax(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_slider_setvalue(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_slider_setstep(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_slider_settick(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_slider_settickplace(XtkScene *scene, XtkCtrl control, XtkTickPlacement value, XtkChangeStamp change);
bool xtk_slider_setsnapsto(XtkScene *scene, XtkCtrl control, XtkSliderSnap value, XtkChangeStamp change);
bool xtk_slider_setsmallchange(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_slider_setlargechange(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_slider_setdir(XtkScene *scene, XtkCtrl control, XtkStackDirection value, XtkChangeStamp change);
bool xtk_slider_setrange(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_slider_setrangestart(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_slider_setrangeend(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
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
bool      xtk_textbox_setaname(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_textbox_setaid(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_textbox_setahelp(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_textbox_setadesc(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_textbox_setastatus(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_textbox_setaitem(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_textbox_setactype(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_textbox_setaaccel(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_textbox_setakey(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_textbox_setalandmark(XtkScene *scene, XtkCtrl control, XtkLandmark value, XtkChangeStamp change);
bool xtk_textbox_setalandname(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_textbox_setalive(XtkScene *scene, XtkCtrl control, XtkLiveSetting value, XtkChangeStamp change);
bool xtk_textbox_setaheading(XtkScene *scene, XtkCtrl control, XtkHeadingLevel value, XtkChangeStamp change);
bool xtk_textbox_setaview(XtkScene *scene, XtkCtrl control, XtkAccessView value, XtkChangeStamp change);
bool xtk_textbox_setarequired(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_textbox_setavalid(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_textbox_setaperipheral(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_textbox_setadialog(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_textbox_setapos(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_textbox_setasize(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_textbox_setalevel(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_textbox_setaculture(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_textbox_setalabel(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_textbox_setadescribed(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_textbox_setaflowsto(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_textbox_setaflowsfrom(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_textbox_setacontrols(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_textbox_setenabled(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_textbox_setplaceholder(
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
bool      xtk_scroll_setaname(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_scroll_setaid(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_scroll_setahelp(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_scroll_setadesc(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_scroll_setastatus(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_scroll_setaitem(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_scroll_setactype(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_scroll_setaaccel(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_scroll_setakey(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_scroll_setalandmark(XtkScene *scene, XtkCtrl control, XtkLandmark value, XtkChangeStamp change);
bool xtk_scroll_setalandname(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_scroll_setalive(XtkScene *scene, XtkCtrl control, XtkLiveSetting value, XtkChangeStamp change);
bool xtk_scroll_setaheading(XtkScene *scene, XtkCtrl control, XtkHeadingLevel value, XtkChangeStamp change);
bool xtk_scroll_setaview(XtkScene *scene, XtkCtrl control, XtkAccessView value, XtkChangeStamp change);
bool xtk_scroll_setarequired(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_scroll_setavalid(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_scroll_setaperipheral(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_scroll_setadialog(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_scroll_setapos(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_scroll_setasize(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_scroll_setalevel(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_scroll_setaculture(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_scroll_setalabel(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_scroll_setadescribed(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_scroll_setaflowsto(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_scroll_setaflowsfrom(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_scroll_setacontrols(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_scroll_setdir(XtkScene *scene, XtkCtrl control, XtkStackDirection value, XtkChangeStamp change);
bool xtk_scroll_setitems(XtkScene *scene, XtkCtrl control, XentFlexAlign value, XtkChangeStamp change);
bool xtk_scroll_setjustify(XtkScene *scene, XtkCtrl control, XentFlexJustify value, XtkChangeStamp change);
bool xtk_scroll_setgap(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_scroll_setpl(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_scroll_setpt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_scroll_setpr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_scroll_setpb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_scroll_setfill(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_scroll_setfitw(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_scroll_setfith(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_scroll_setwrap(XtkScene *scene, XtkCtrl control, XentFlexWrap value, XtkChangeStamp change);
bool xtk_scroll_setx(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_scroll_sety(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
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
bool      xtk_image_setaname(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_image_setaid(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_image_setahelp(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_image_setadesc(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_image_setastatus(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_image_setaitem(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_image_setactype(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_image_setaaccel(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_image_setakey(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_image_setalandmark(XtkScene *scene, XtkCtrl control, XtkLandmark value, XtkChangeStamp change);
bool xtk_image_setalandname(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_image_setalive(XtkScene *scene, XtkCtrl control, XtkLiveSetting value, XtkChangeStamp change);
bool xtk_image_setaheading(XtkScene *scene, XtkCtrl control, XtkHeadingLevel value, XtkChangeStamp change);
bool xtk_image_setaview(XtkScene *scene, XtkCtrl control, XtkAccessView value, XtkChangeStamp change);
bool xtk_image_setarequired(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_image_setavalid(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_image_setaperipheral(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_image_setadialog(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_image_setapos(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_image_setasize(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_image_setalevel(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_image_setaculture(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_image_setalabel(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_image_setadescribed(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_image_setaflowsto(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_image_setaflowsfrom(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_image_setacontrols(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_image_setsrc(XtkScene *scene, XtkCtrl control, XtkResource value, XtkChangeStamp change);
bool xtk_image_setfit(XtkScene *scene, XtkCtrl control, XtkImageStretch value, XtkChangeStamp change);
bool xtk_image_setnl(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_image_setnt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_image_setnr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_image_setnb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
XtkSubRef xtk_image_onopened(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg);
XtkSubRef xtk_image_onfailed(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg);
bool      xtk_progress_setw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_progress_seth(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_progress_setgrow(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_progress_setself(XtkScene *scene, XtkCtrl control, XentFlexAlign value, XtkChangeStamp change);
bool      xtk_progress_setml(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_progress_setmt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_progress_setmr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_progress_setmb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_progress_settip(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_progress_setaname(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_progress_setaid(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_progress_setahelp(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_progress_setadesc(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_progress_setastatus(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_progress_setaitem(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_progress_setactype(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_progress_setaaccel(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_progress_setakey(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_progress_setalandmark(XtkScene *scene, XtkCtrl control, XtkLandmark value, XtkChangeStamp change);
bool xtk_progress_setalandname(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_progress_setalive(XtkScene *scene, XtkCtrl control, XtkLiveSetting value, XtkChangeStamp change);
bool xtk_progress_setaheading(XtkScene *scene, XtkCtrl control, XtkHeadingLevel value, XtkChangeStamp change);
bool xtk_progress_setaview(XtkScene *scene, XtkCtrl control, XtkAccessView value, XtkChangeStamp change);
bool xtk_progress_setarequired(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_progress_setavalid(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_progress_setaperipheral(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_progress_setadialog(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_progress_setapos(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_progress_setasize(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_progress_setalevel(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_progress_setaculture(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_progress_setalabel(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_progress_setadescribed(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
);
bool xtk_progress_setaflowsto(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_progress_setaflowsfrom(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
);
bool xtk_progress_setacontrols(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_progress_setmin(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_progress_setmax(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_progress_setvalue(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_progress_setindeterminate(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_progress_setstate(XtkScene *scene, XtkCtrl control, XtkProgressState value, XtkChangeStamp change);
bool xtk_progress_setpl(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_progress_setpt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_progress_setpr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_progress_setpb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_progress_setborder_width(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_list_setw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_list_seth(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_list_setgrow(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_list_setself(XtkScene *scene, XtkCtrl control, XentFlexAlign value, XtkChangeStamp change);
bool xtk_list_setml(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_list_setmt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_list_setmr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_list_setmb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_list_settip(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_list_setaname(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_list_setaid(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_list_setahelp(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_list_setadesc(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_list_setastatus(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_list_setaitem(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_list_setactype(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_list_setaaccel(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_list_setakey(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_list_setalandmark(XtkScene *scene, XtkCtrl control, XtkLandmark value, XtkChangeStamp change);
bool xtk_list_setalandname(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_list_setalive(XtkScene *scene, XtkCtrl control, XtkLiveSetting value, XtkChangeStamp change);
bool xtk_list_setaheading(XtkScene *scene, XtkCtrl control, XtkHeadingLevel value, XtkChangeStamp change);
bool xtk_list_setaview(XtkScene *scene, XtkCtrl control, XtkAccessView value, XtkChangeStamp change);
bool xtk_list_setarequired(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_list_setavalid(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_list_setaperipheral(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_list_setadialog(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_list_setapos(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_list_setasize(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_list_setalevel(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_list_setaculture(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_list_setalabel(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_list_setadescribed(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_list_setaflowsto(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_list_setaflowsfrom(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_list_setacontrols(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_list_setenabled(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_list_setsel(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_list_setnitem(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_list_setitemh(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_list_setitemw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_list_setncol(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_list_setmode(XtkScene *scene, XtkCtrl control, XtkListSelMode value, XtkChangeStamp change);
bool xtk_list_setfirst(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_list_setrectsel(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
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
bool      xtk_tab_setaname(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_tab_setaid(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_tab_setahelp(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_tab_setadesc(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_tab_setastatus(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_tab_setaitem(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_tab_setactype(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_tab_setaaccel(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_tab_setakey(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_tab_setalandmark(XtkScene *scene, XtkCtrl control, XtkLandmark value, XtkChangeStamp change);
bool      xtk_tab_setalandname(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_tab_setalive(XtkScene *scene, XtkCtrl control, XtkLiveSetting value, XtkChangeStamp change);
bool      xtk_tab_setaheading(XtkScene *scene, XtkCtrl control, XtkHeadingLevel value, XtkChangeStamp change);
bool      xtk_tab_setaview(XtkScene *scene, XtkCtrl control, XtkAccessView value, XtkChangeStamp change);
bool      xtk_tab_setarequired(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool      xtk_tab_setavalid(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool      xtk_tab_setaperipheral(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool      xtk_tab_setadialog(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool      xtk_tab_setapos(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool      xtk_tab_setasize(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool      xtk_tab_setalevel(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool      xtk_tab_setaculture(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool      xtk_tab_setalabel(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_tab_setadescribed(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_tab_setaflowsto(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_tab_setaflowsfrom(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_tab_setacontrols(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_card_setw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_card_seth(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_card_setgrow(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_card_setshrink(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_card_setself(XtkScene *scene, XtkCtrl control, XentFlexAlign value, XtkChangeStamp change);
bool xtk_card_setml(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_card_setmt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_card_setmr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_card_setmb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_card_settip(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_card_setaname(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_card_setaid(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_card_setahelp(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_card_setadesc(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_card_setastatus(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_card_setaitem(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_card_setactype(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_card_setaaccel(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_card_setakey(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_card_setalandmark(XtkScene *scene, XtkCtrl control, XtkLandmark value, XtkChangeStamp change);
bool xtk_card_setalandname(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_card_setalive(XtkScene *scene, XtkCtrl control, XtkLiveSetting value, XtkChangeStamp change);
bool xtk_card_setaheading(XtkScene *scene, XtkCtrl control, XtkHeadingLevel value, XtkChangeStamp change);
bool xtk_card_setaview(XtkScene *scene, XtkCtrl control, XtkAccessView value, XtkChangeStamp change);
bool xtk_card_setarequired(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_card_setavalid(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_card_setaperipheral(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_card_setadialog(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_card_setapos(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_card_setasize(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_card_setalevel(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_card_setaculture(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_card_setalabel(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_card_setadescribed(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_card_setaflowsto(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_card_setaflowsfrom(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_card_setacontrols(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_card_setdir(XtkScene *scene, XtkCtrl control, XtkStackDirection value, XtkChangeStamp change);
bool xtk_card_setitems(XtkScene *scene, XtkCtrl control, XentFlexAlign value, XtkChangeStamp change);
bool xtk_card_setjustify(XtkScene *scene, XtkCtrl control, XentFlexJustify value, XtkChangeStamp change);
bool xtk_card_setgap(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_card_setpl(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_card_setpt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_card_setpr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_card_setpb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_card_setfill(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_card_setfitw(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_card_setfith(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_card_setwrap(XtkScene *scene, XtkCtrl control, XentFlexWrap value, XtkChangeStamp change);
bool xtk_card_setdrop(XtkScene *scene, XtkCtrl control, XtkDropOperation value, XtkChangeStamp change);
bool xtk_card_setdragtext(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_card_setdragfiles(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_card_setflow(XtkScene *scene, XtkCtrl control, XentDirection value, XtkChangeStamp change);
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
bool      xtk_divider_setaname(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_divider_setaid(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_divider_setahelp(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_divider_setadesc(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_divider_setastatus(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_divider_setaitem(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_divider_setactype(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_divider_setaaccel(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_divider_setakey(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_divider_setalandmark(XtkScene *scene, XtkCtrl control, XtkLandmark value, XtkChangeStamp change);
bool xtk_divider_setalandname(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_divider_setalive(XtkScene *scene, XtkCtrl control, XtkLiveSetting value, XtkChangeStamp change);
bool xtk_divider_setaheading(XtkScene *scene, XtkCtrl control, XtkHeadingLevel value, XtkChangeStamp change);
bool xtk_divider_setaview(XtkScene *scene, XtkCtrl control, XtkAccessView value, XtkChangeStamp change);
bool xtk_divider_setarequired(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_divider_setavalid(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_divider_setaperipheral(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_divider_setadialog(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_divider_setapos(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_divider_setasize(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_divider_setalevel(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_divider_setaculture(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_divider_setalabel(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_divider_setadescribed(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_divider_setaflowsto(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_divider_setaflowsfrom(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_divider_setacontrols(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_canvas_setw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_canvas_seth(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_canvas_setgrow(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_canvas_setshrink(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_canvas_setself(XtkScene *scene, XtkCtrl control, XentFlexAlign value, XtkChangeStamp change);
bool xtk_canvas_setml(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_canvas_setmt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_canvas_setmr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_canvas_setmb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_canvas_settip(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_canvas_setaname(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_canvas_setaid(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_canvas_setahelp(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_canvas_setadesc(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_canvas_setastatus(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_canvas_setaitem(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_canvas_setactype(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_canvas_setaaccel(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_canvas_setakey(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_canvas_setalandmark(XtkScene *scene, XtkCtrl control, XtkLandmark value, XtkChangeStamp change);
bool xtk_canvas_setalandname(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_canvas_setalive(XtkScene *scene, XtkCtrl control, XtkLiveSetting value, XtkChangeStamp change);
bool xtk_canvas_setaheading(XtkScene *scene, XtkCtrl control, XtkHeadingLevel value, XtkChangeStamp change);
bool xtk_canvas_setaview(XtkScene *scene, XtkCtrl control, XtkAccessView value, XtkChangeStamp change);
bool xtk_canvas_setarequired(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_canvas_setavalid(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_canvas_setaperipheral(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_canvas_setadialog(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_canvas_setapos(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_canvas_setasize(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_canvas_setalevel(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_canvas_setaculture(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_canvas_setalabel(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_canvas_setadescribed(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_canvas_setaflowsto(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_canvas_setaflowsfrom(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_canvas_setacontrols(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_password_setw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_password_seth(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_password_setgrow(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_password_setself(XtkScene *scene, XtkCtrl control, XentFlexAlign value, XtkChangeStamp change);
bool xtk_password_setml(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_password_setmt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_password_setmr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_password_setmb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_password_settext(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_password_settip(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_password_setaname(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_password_setaid(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_password_setahelp(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_password_setadesc(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_password_setastatus(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_password_setaitem(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_password_setactype(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_password_setaaccel(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_password_setakey(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_password_setalandmark(XtkScene *scene, XtkCtrl control, XtkLandmark value, XtkChangeStamp change);
bool xtk_password_setalandname(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_password_setalive(XtkScene *scene, XtkCtrl control, XtkLiveSetting value, XtkChangeStamp change);
bool xtk_password_setaheading(XtkScene *scene, XtkCtrl control, XtkHeadingLevel value, XtkChangeStamp change);
bool xtk_password_setaview(XtkScene *scene, XtkCtrl control, XtkAccessView value, XtkChangeStamp change);
bool xtk_password_setarequired(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_password_setavalid(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_password_setaperipheral(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_password_setadialog(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_password_setapos(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_password_setasize(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_password_setalevel(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_password_setaculture(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_password_setalabel(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_password_setadescribed(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
);
bool xtk_password_setaflowsto(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_password_setaflowsfrom(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
);
bool xtk_password_setacontrols(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_password_setenabled(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_password_setplaceholder(
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
bool      xtk_number_setaname(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_number_setaid(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_number_setahelp(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_number_setadesc(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_number_setastatus(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_number_setaitem(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_number_setactype(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_number_setaaccel(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_number_setakey(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_number_setalandmark(XtkScene *scene, XtkCtrl control, XtkLandmark value, XtkChangeStamp change);
bool xtk_number_setalandname(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_number_setalive(XtkScene *scene, XtkCtrl control, XtkLiveSetting value, XtkChangeStamp change);
bool xtk_number_setaheading(XtkScene *scene, XtkCtrl control, XtkHeadingLevel value, XtkChangeStamp change);
bool xtk_number_setaview(XtkScene *scene, XtkCtrl control, XtkAccessView value, XtkChangeStamp change);
bool xtk_number_setarequired(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_number_setavalid(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_number_setaperipheral(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_number_setadialog(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_number_setapos(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_number_setasize(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_number_setalevel(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_number_setaculture(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_number_setalabel(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_number_setadescribed(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_number_setaflowsto(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_number_setaflowsfrom(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_number_setacontrols(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_number_setenabled(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_number_setvalue(XtkScene *scene, XtkCtrl control, double value, XtkChangeStamp change);
bool xtk_number_setmin(XtkScene *scene, XtkCtrl control, double value, XtkChangeStamp change);
bool xtk_number_setmax(XtkScene *scene, XtkCtrl control, double value, XtkChangeStamp change);
bool xtk_number_setstep(XtkScene *scene, XtkCtrl control, double value, XtkChangeStamp change);
bool xtk_number_sethidespin(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
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
bool      xtk_link_setaname(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_link_setaid(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_link_setahelp(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_link_setadesc(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_link_setastatus(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_link_setaitem(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_link_setactype(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_link_setaaccel(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_link_setakey(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_link_setalandmark(XtkScene *scene, XtkCtrl control, XtkLandmark value, XtkChangeStamp change);
bool xtk_link_setalandname(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_link_setalive(XtkScene *scene, XtkCtrl control, XtkLiveSetting value, XtkChangeStamp change);
bool xtk_link_setaheading(XtkScene *scene, XtkCtrl control, XtkHeadingLevel value, XtkChangeStamp change);
bool xtk_link_setaview(XtkScene *scene, XtkCtrl control, XtkAccessView value, XtkChangeStamp change);
bool xtk_link_setarequired(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_link_setavalid(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_link_setaperipheral(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_link_setadialog(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_link_setapos(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_link_setasize(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_link_setalevel(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_link_setaculture(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_link_setalabel(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_link_setadescribed(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_link_setaflowsto(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_link_setaflowsfrom(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_link_setacontrols(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_link_setenabled(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_link_seturl(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
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
bool      xtk_repeat_setaname(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_repeat_setaid(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_repeat_setahelp(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_repeat_setadesc(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_repeat_setastatus(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_repeat_setaitem(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_repeat_setactype(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_repeat_setaaccel(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_repeat_setakey(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_repeat_setalandmark(XtkScene *scene, XtkCtrl control, XtkLandmark value, XtkChangeStamp change);
bool xtk_repeat_setalandname(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_repeat_setalive(XtkScene *scene, XtkCtrl control, XtkLiveSetting value, XtkChangeStamp change);
bool xtk_repeat_setaheading(XtkScene *scene, XtkCtrl control, XtkHeadingLevel value, XtkChangeStamp change);
bool xtk_repeat_setaview(XtkScene *scene, XtkCtrl control, XtkAccessView value, XtkChangeStamp change);
bool xtk_repeat_setarequired(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_repeat_setavalid(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_repeat_setaperipheral(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_repeat_setadialog(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_repeat_setapos(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_repeat_setasize(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_repeat_setalevel(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_repeat_setaculture(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_repeat_setalabel(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_repeat_setadescribed(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_repeat_setaflowsto(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_repeat_setaflowsfrom(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_repeat_setacontrols(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_repeat_setenabled(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_repeat_seticon(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_repeat_setstyle(XtkScene *scene, XtkCtrl control, XtkButtonStyle value, XtkChangeStamp change);
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
bool xtk_progressring_setaname(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_progressring_setaid(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_progressring_setahelp(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_progressring_setadesc(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_progressring_setastatus(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
);
bool xtk_progressring_setaitem(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_progressring_setactype(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
);
bool xtk_progressring_setaaccel(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
);
bool xtk_progressring_setakey(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_progressring_setalandmark(XtkScene *scene, XtkCtrl control, XtkLandmark value, XtkChangeStamp change);
bool xtk_progressring_setalandname(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
);
bool xtk_progressring_setalive(XtkScene *scene, XtkCtrl control, XtkLiveSetting value, XtkChangeStamp change);
bool xtk_progressring_setaheading(XtkScene *scene, XtkCtrl control, XtkHeadingLevel value, XtkChangeStamp change);
bool xtk_progressring_setaview(XtkScene *scene, XtkCtrl control, XtkAccessView value, XtkChangeStamp change);
bool xtk_progressring_setarequired(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_progressring_setavalid(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_progressring_setaperipheral(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_progressring_setadialog(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_progressring_setapos(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_progressring_setasize(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_progressring_setalevel(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_progressring_setaculture(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_progressring_setalabel(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
);
bool xtk_progressring_setadescribed(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
);
bool xtk_progressring_setaflowsto(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
);
bool xtk_progressring_setaflowsfrom(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
);
bool xtk_progressring_setacontrols(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
);
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
bool xtk_badge_setaname(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_badge_setaid(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_badge_setahelp(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_badge_setadesc(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_badge_setastatus(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_badge_setaitem(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_badge_setactype(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_badge_setaaccel(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_badge_setakey(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_badge_setalandmark(XtkScene *scene, XtkCtrl control, XtkLandmark value, XtkChangeStamp change);
bool xtk_badge_setalandname(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_badge_setalive(XtkScene *scene, XtkCtrl control, XtkLiveSetting value, XtkChangeStamp change);
bool xtk_badge_setaheading(XtkScene *scene, XtkCtrl control, XtkHeadingLevel value, XtkChangeStamp change);
bool xtk_badge_setaview(XtkScene *scene, XtkCtrl control, XtkAccessView value, XtkChangeStamp change);
bool xtk_badge_setarequired(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_badge_setavalid(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_badge_setaperipheral(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_badge_setadialog(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_badge_setapos(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_badge_setasize(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_badge_setalevel(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_badge_setaculture(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_badge_setalabel(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_badge_setadescribed(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_badge_setaflowsto(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_badge_setaflowsfrom(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_badge_setacontrols(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
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
bool xtk_tooltip_setaname(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_tooltip_setaid(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_tooltip_setahelp(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_tooltip_setadesc(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_tooltip_setastatus(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_tooltip_setaitem(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_tooltip_setactype(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_tooltip_setaaccel(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_tooltip_setakey(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_tooltip_setalandmark(XtkScene *scene, XtkCtrl control, XtkLandmark value, XtkChangeStamp change);
bool xtk_tooltip_setalandname(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_tooltip_setalive(XtkScene *scene, XtkCtrl control, XtkLiveSetting value, XtkChangeStamp change);
bool xtk_tooltip_setaheading(XtkScene *scene, XtkCtrl control, XtkHeadingLevel value, XtkChangeStamp change);
bool xtk_tooltip_setaview(XtkScene *scene, XtkCtrl control, XtkAccessView value, XtkChangeStamp change);
bool xtk_tooltip_setarequired(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_tooltip_setavalid(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_tooltip_setaperipheral(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_tooltip_setadialog(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_tooltip_setapos(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_tooltip_setasize(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_tooltip_setalevel(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_tooltip_setaculture(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_tooltip_setalabel(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_tooltip_setadescribed(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_tooltip_setaflowsto(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_tooltip_setaflowsfrom(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_tooltip_setacontrols(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
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
bool xtk_flyout_setaname(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_flyout_setaid(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_flyout_setahelp(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_flyout_setadesc(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_flyout_setastatus(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_flyout_setaitem(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_flyout_setactype(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_flyout_setaaccel(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_flyout_setakey(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_flyout_setalandmark(XtkScene *scene, XtkCtrl control, XtkLandmark value, XtkChangeStamp change);
bool xtk_flyout_setalandname(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_flyout_setalive(XtkScene *scene, XtkCtrl control, XtkLiveSetting value, XtkChangeStamp change);
bool xtk_flyout_setaheading(XtkScene *scene, XtkCtrl control, XtkHeadingLevel value, XtkChangeStamp change);
bool xtk_flyout_setaview(XtkScene *scene, XtkCtrl control, XtkAccessView value, XtkChangeStamp change);
bool xtk_flyout_setarequired(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_flyout_setavalid(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_flyout_setaperipheral(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_flyout_setadialog(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_flyout_setapos(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_flyout_setasize(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_flyout_setalevel(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_flyout_setaculture(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_flyout_setalabel(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_flyout_setadescribed(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_flyout_setaflowsto(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_flyout_setaflowsfrom(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_flyout_setacontrols(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
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
bool xtk_menufly_setaname(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_menufly_setaid(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_menufly_setahelp(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_menufly_setadesc(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_menufly_setastatus(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_menufly_setaitem(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_menufly_setactype(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_menufly_setaaccel(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_menufly_setakey(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_menufly_setalandmark(XtkScene *scene, XtkCtrl control, XtkLandmark value, XtkChangeStamp change);
bool xtk_menufly_setalandname(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_menufly_setalive(XtkScene *scene, XtkCtrl control, XtkLiveSetting value, XtkChangeStamp change);
bool xtk_menufly_setaheading(XtkScene *scene, XtkCtrl control, XtkHeadingLevel value, XtkChangeStamp change);
bool xtk_menufly_setaview(XtkScene *scene, XtkCtrl control, XtkAccessView value, XtkChangeStamp change);
bool xtk_menufly_setarequired(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_menufly_setavalid(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_menufly_setaperipheral(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_menufly_setadialog(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_menufly_setapos(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_menufly_setasize(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_menufly_setalevel(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_menufly_setaculture(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_menufly_setalabel(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_menufly_setadescribed(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_menufly_setaflowsto(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_menufly_setaflowsfrom(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_menufly_setacontrols(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
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
bool xtk_dropdown_setaname(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_dropdown_setaid(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_dropdown_setahelp(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_dropdown_setadesc(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_dropdown_setastatus(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_dropdown_setaitem(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_dropdown_setactype(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_dropdown_setaaccel(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_dropdown_setakey(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_dropdown_setalandmark(XtkScene *scene, XtkCtrl control, XtkLandmark value, XtkChangeStamp change);
bool xtk_dropdown_setalandname(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_dropdown_setalive(XtkScene *scene, XtkCtrl control, XtkLiveSetting value, XtkChangeStamp change);
bool xtk_dropdown_setaheading(XtkScene *scene, XtkCtrl control, XtkHeadingLevel value, XtkChangeStamp change);
bool xtk_dropdown_setaview(XtkScene *scene, XtkCtrl control, XtkAccessView value, XtkChangeStamp change);
bool xtk_dropdown_setarequired(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_dropdown_setavalid(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_dropdown_setaperipheral(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_dropdown_setadialog(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_dropdown_setapos(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_dropdown_setasize(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_dropdown_setalevel(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_dropdown_setaculture(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_dropdown_setalabel(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_dropdown_setadescribed(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
);
bool xtk_dropdown_setaflowsto(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_dropdown_setaflowsfrom(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
);
bool xtk_dropdown_setacontrols(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
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
bool      xtk_split_setaname(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_split_setaid(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_split_setahelp(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_split_setadesc(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_split_setastatus(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_split_setaitem(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_split_setactype(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_split_setaaccel(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_split_setakey(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_split_setalandmark(XtkScene *scene, XtkCtrl control, XtkLandmark value, XtkChangeStamp change);
bool xtk_split_setalandname(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_split_setalive(XtkScene *scene, XtkCtrl control, XtkLiveSetting value, XtkChangeStamp change);
bool xtk_split_setaheading(XtkScene *scene, XtkCtrl control, XtkHeadingLevel value, XtkChangeStamp change);
bool xtk_split_setaview(XtkScene *scene, XtkCtrl control, XtkAccessView value, XtkChangeStamp change);
bool xtk_split_setarequired(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_split_setavalid(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_split_setaperipheral(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_split_setadialog(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_split_setapos(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_split_setasize(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_split_setalevel(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_split_setaculture(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_split_setalabel(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_split_setadescribed(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_split_setaflowsto(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_split_setaflowsfrom(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_split_setacontrols(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_split_setenabled(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_split_seticon(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_split_setstyle(XtkScene *scene, XtkCtrl control, XtkButtonStyle value, XtkChangeStamp change);
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
bool      xtk_combo_setaname(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_combo_setaid(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_combo_setahelp(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_combo_setadesc(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_combo_setastatus(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_combo_setaitem(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_combo_setactype(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_combo_setaaccel(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_combo_setakey(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_combo_setalandmark(XtkScene *scene, XtkCtrl control, XtkLandmark value, XtkChangeStamp change);
bool xtk_combo_setalandname(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_combo_setalive(XtkScene *scene, XtkCtrl control, XtkLiveSetting value, XtkChangeStamp change);
bool xtk_combo_setaheading(XtkScene *scene, XtkCtrl control, XtkHeadingLevel value, XtkChangeStamp change);
bool xtk_combo_setaview(XtkScene *scene, XtkCtrl control, XtkAccessView value, XtkChangeStamp change);
bool xtk_combo_setarequired(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_combo_setavalid(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_combo_setaperipheral(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_combo_setadialog(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_combo_setapos(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_combo_setasize(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_combo_setalevel(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_combo_setaculture(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_combo_setalabel(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_combo_setadescribed(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_combo_setaflowsto(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_combo_setaflowsfrom(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_combo_setacontrols(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_combo_setenabled(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
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
bool xtk_expander_setaname(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_expander_setaid(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_expander_setahelp(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_expander_setadesc(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_expander_setastatus(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_expander_setaitem(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_expander_setactype(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_expander_setaaccel(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_expander_setakey(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_expander_setalandmark(XtkScene *scene, XtkCtrl control, XtkLandmark value, XtkChangeStamp change);
bool xtk_expander_setalandname(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_expander_setalive(XtkScene *scene, XtkCtrl control, XtkLiveSetting value, XtkChangeStamp change);
bool xtk_expander_setaheading(XtkScene *scene, XtkCtrl control, XtkHeadingLevel value, XtkChangeStamp change);
bool xtk_expander_setaview(XtkScene *scene, XtkCtrl control, XtkAccessView value, XtkChangeStamp change);
bool xtk_expander_setarequired(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_expander_setavalid(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_expander_setaperipheral(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_expander_setadialog(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_expander_setapos(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_expander_setasize(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_expander_setalevel(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_expander_setaculture(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_expander_setalabel(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_expander_setadescribed(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
);
bool xtk_expander_setaflowsto(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_expander_setaflowsfrom(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
);
bool xtk_expander_setacontrols(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_expander_setexpanded(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_expander_setcontenth(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
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
bool      xtk_exphead_setaname(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_exphead_setaid(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_exphead_setahelp(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_exphead_setadesc(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_exphead_setastatus(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_exphead_setaitem(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_exphead_setactype(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_exphead_setaaccel(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_exphead_setakey(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_exphead_setalandmark(XtkScene *scene, XtkCtrl control, XtkLandmark value, XtkChangeStamp change);
bool xtk_exphead_setalandname(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_exphead_setalive(XtkScene *scene, XtkCtrl control, XtkLiveSetting value, XtkChangeStamp change);
bool xtk_exphead_setaheading(XtkScene *scene, XtkCtrl control, XtkHeadingLevel value, XtkChangeStamp change);
bool xtk_exphead_setaview(XtkScene *scene, XtkCtrl control, XtkAccessView value, XtkChangeStamp change);
bool xtk_exphead_setarequired(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_exphead_setavalid(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_exphead_setaperipheral(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_exphead_setadialog(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_exphead_setapos(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_exphead_setasize(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_exphead_setalevel(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_exphead_setaculture(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_exphead_setalabel(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_exphead_setadescribed(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_exphead_setaflowsto(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_exphead_setaflowsfrom(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_exphead_setacontrols(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_exphead_seticon(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_exphead_setenabled(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_exphead_setselected(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_exphead_setexpanded(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_expbody_setw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_expbody_seth(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_expbody_setgrow(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_expbody_setshrink(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_expbody_setself(XtkScene *scene, XtkCtrl control, XentFlexAlign value, XtkChangeStamp change);
bool xtk_expbody_setml(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_expbody_setmt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_expbody_setmr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_expbody_setmb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_expbody_settip(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_expbody_setaname(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_expbody_setaid(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_expbody_setahelp(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_expbody_setadesc(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_expbody_setastatus(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_expbody_setaitem(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_expbody_setactype(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_expbody_setaaccel(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_expbody_setakey(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_expbody_setalandmark(XtkScene *scene, XtkCtrl control, XtkLandmark value, XtkChangeStamp change);
bool xtk_expbody_setalandname(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_expbody_setalive(XtkScene *scene, XtkCtrl control, XtkLiveSetting value, XtkChangeStamp change);
bool xtk_expbody_setaheading(XtkScene *scene, XtkCtrl control, XtkHeadingLevel value, XtkChangeStamp change);
bool xtk_expbody_setaview(XtkScene *scene, XtkCtrl control, XtkAccessView value, XtkChangeStamp change);
bool xtk_expbody_setarequired(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_expbody_setavalid(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_expbody_setaperipheral(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_expbody_setadialog(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_expbody_setapos(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_expbody_setasize(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_expbody_setalevel(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_expbody_setaculture(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_expbody_setalabel(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_expbody_setadescribed(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_expbody_setaflowsto(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_expbody_setaflowsfrom(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_expbody_setacontrols(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_expbody_setdir(XtkScene *scene, XtkCtrl control, XtkStackDirection value, XtkChangeStamp change);
bool xtk_expbody_setitems(XtkScene *scene, XtkCtrl control, XentFlexAlign value, XtkChangeStamp change);
bool xtk_expbody_setjustify(XtkScene *scene, XtkCtrl control, XentFlexJustify value, XtkChangeStamp change);
bool xtk_expbody_setgap(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_expbody_setpl(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_expbody_setpt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_expbody_setpr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_expbody_setpb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_expbody_setfill(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_expbody_setfitw(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_expbody_setfith(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_expbody_setwrap(XtkScene *scene, XtkCtrl control, XentFlexWrap value, XtkChangeStamp change);
bool xtk_expbody_setdrop(XtkScene *scene, XtkCtrl control, XtkDropOperation value, XtkChangeStamp change);
bool xtk_expbody_setdragtext(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_expbody_setdragfiles(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_expbody_setflow(XtkScene *scene, XtkCtrl control, XentDirection value, XtkChangeStamp change);
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
bool xtk_infobar_setaname(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_infobar_setaid(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_infobar_setahelp(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_infobar_setadesc(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_infobar_setastatus(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_infobar_setaitem(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_infobar_setactype(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_infobar_setaaccel(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_infobar_setakey(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_infobar_setalandmark(XtkScene *scene, XtkCtrl control, XtkLandmark value, XtkChangeStamp change);
bool xtk_infobar_setalandname(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_infobar_setalive(XtkScene *scene, XtkCtrl control, XtkLiveSetting value, XtkChangeStamp change);
bool xtk_infobar_setaheading(XtkScene *scene, XtkCtrl control, XtkHeadingLevel value, XtkChangeStamp change);
bool xtk_infobar_setaview(XtkScene *scene, XtkCtrl control, XtkAccessView value, XtkChangeStamp change);
bool xtk_infobar_setarequired(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_infobar_setavalid(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_infobar_setaperipheral(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_infobar_setadialog(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_infobar_setapos(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_infobar_setasize(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_infobar_setalevel(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_infobar_setaculture(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_infobar_setalabel(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_infobar_setadescribed(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_infobar_setaflowsto(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_infobar_setaflowsfrom(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_infobar_setacontrols(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
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
bool      xtk_dialog_setaname(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_dialog_setaid(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_dialog_setahelp(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_dialog_setadesc(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_dialog_setastatus(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_dialog_setaitem(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_dialog_setactype(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_dialog_setaaccel(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_dialog_setakey(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_dialog_setalandmark(XtkScene *scene, XtkCtrl control, XtkLandmark value, XtkChangeStamp change);
bool xtk_dialog_setalandname(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_dialog_setalive(XtkScene *scene, XtkCtrl control, XtkLiveSetting value, XtkChangeStamp change);
bool xtk_dialog_setaheading(XtkScene *scene, XtkCtrl control, XtkHeadingLevel value, XtkChangeStamp change);
bool xtk_dialog_setaview(XtkScene *scene, XtkCtrl control, XtkAccessView value, XtkChangeStamp change);
bool xtk_dialog_setarequired(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_dialog_setavalid(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_dialog_setaperipheral(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_dialog_setadialog(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_dialog_setapos(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_dialog_setasize(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_dialog_setalevel(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_dialog_setaculture(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_dialog_setalabel(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_dialog_setadescribed(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_dialog_setaflowsto(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_dialog_setaflowsfrom(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_dialog_setacontrols(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_dialog_settext(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_dialog_setprimary(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_dialog_setsecondary(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_dialog_setclose(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_dialog_setcontenth(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_dialog_setdefault_button(XtkScene *scene, XtkCtrl control, XtkDialogButton value, XtkChangeStamp change);
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
bool xtk_dialogbody_setaname(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_dialogbody_setaid(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_dialogbody_setahelp(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_dialogbody_setadesc(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_dialogbody_setastatus(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_dialogbody_setaitem(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_dialogbody_setactype(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_dialogbody_setaaccel(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_dialogbody_setakey(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_dialogbody_setalandmark(XtkScene *scene, XtkCtrl control, XtkLandmark value, XtkChangeStamp change);
bool xtk_dialogbody_setalandname(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
);
bool xtk_dialogbody_setalive(XtkScene *scene, XtkCtrl control, XtkLiveSetting value, XtkChangeStamp change);
bool xtk_dialogbody_setaheading(XtkScene *scene, XtkCtrl control, XtkHeadingLevel value, XtkChangeStamp change);
bool xtk_dialogbody_setaview(XtkScene *scene, XtkCtrl control, XtkAccessView value, XtkChangeStamp change);
bool xtk_dialogbody_setarequired(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_dialogbody_setavalid(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_dialogbody_setaperipheral(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_dialogbody_setadialog(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_dialogbody_setapos(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_dialogbody_setasize(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_dialogbody_setalevel(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_dialogbody_setaculture(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_dialogbody_setalabel(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_dialogbody_setadescribed(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
);
bool xtk_dialogbody_setaflowsto(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
);
bool xtk_dialogbody_setaflowsfrom(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
);
bool xtk_dialogbody_setacontrols(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
);
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
bool      xtk_dialogbody_setflow(XtkScene *scene, XtkCtrl control, XentDirection value, XtkChangeStamp change);
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
bool      xtk_menubar_setaname(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_menubar_setaid(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_menubar_setahelp(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_menubar_setadesc(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_menubar_setastatus(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_menubar_setaitem(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_menubar_setactype(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_menubar_setaaccel(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_menubar_setakey(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_menubar_setalandmark(XtkScene *scene, XtkCtrl control, XtkLandmark value, XtkChangeStamp change);
bool xtk_menubar_setalandname(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_menubar_setalive(XtkScene *scene, XtkCtrl control, XtkLiveSetting value, XtkChangeStamp change);
bool xtk_menubar_setaheading(XtkScene *scene, XtkCtrl control, XtkHeadingLevel value, XtkChangeStamp change);
bool xtk_menubar_setaview(XtkScene *scene, XtkCtrl control, XtkAccessView value, XtkChangeStamp change);
bool xtk_menubar_setarequired(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_menubar_setavalid(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_menubar_setaperipheral(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_menubar_setadialog(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_menubar_setapos(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_menubar_setasize(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_menubar_setalevel(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_menubar_setaculture(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_menubar_setalabel(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_menubar_setadescribed(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_menubar_setaflowsto(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_menubar_setaflowsfrom(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_menubar_setacontrols(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_menuitem_setw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_menuitem_seth(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_menuitem_setgrow(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_menuitem_setself(XtkScene *scene, XtkCtrl control, XentFlexAlign value, XtkChangeStamp change);
bool xtk_menuitem_setml(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_menuitem_setmt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_menuitem_setmr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_menuitem_setmb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_menuitem_settext(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_menuitem_settip(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_menuitem_setaname(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_menuitem_setaid(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_menuitem_setahelp(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_menuitem_setadesc(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_menuitem_setastatus(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_menuitem_setaitem(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_menuitem_setactype(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_menuitem_setaaccel(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_menuitem_setakey(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_menuitem_setalandmark(XtkScene *scene, XtkCtrl control, XtkLandmark value, XtkChangeStamp change);
bool xtk_menuitem_setalandname(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_menuitem_setalive(XtkScene *scene, XtkCtrl control, XtkLiveSetting value, XtkChangeStamp change);
bool xtk_menuitem_setaheading(XtkScene *scene, XtkCtrl control, XtkHeadingLevel value, XtkChangeStamp change);
bool xtk_menuitem_setaview(XtkScene *scene, XtkCtrl control, XtkAccessView value, XtkChangeStamp change);
bool xtk_menuitem_setarequired(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_menuitem_setavalid(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_menuitem_setaperipheral(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_menuitem_setadialog(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_menuitem_setapos(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_menuitem_setasize(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_menuitem_setalevel(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_menuitem_setaculture(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_menuitem_setalabel(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_menuitem_setadescribed(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
);
bool xtk_menuitem_setaflowsto(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_menuitem_setaflowsfrom(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
);
bool xtk_menuitem_setacontrols(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_menuitem_seticon(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_menuitem_setenabled(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_menuitem_setselected(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_menuitem_setexpanded(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
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
bool      xtk_nav_setaname(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_nav_setaid(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_nav_setahelp(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_nav_setadesc(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_nav_setastatus(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_nav_setaitem(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_nav_setactype(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_nav_setaaccel(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_nav_setakey(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_nav_setalandmark(XtkScene *scene, XtkCtrl control, XtkLandmark value, XtkChangeStamp change);
bool      xtk_nav_setalandname(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_nav_setalive(XtkScene *scene, XtkCtrl control, XtkLiveSetting value, XtkChangeStamp change);
bool      xtk_nav_setaheading(XtkScene *scene, XtkCtrl control, XtkHeadingLevel value, XtkChangeStamp change);
bool      xtk_nav_setaview(XtkScene *scene, XtkCtrl control, XtkAccessView value, XtkChangeStamp change);
bool      xtk_nav_setarequired(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool      xtk_nav_setavalid(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool      xtk_nav_setaperipheral(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool      xtk_nav_setadialog(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool      xtk_nav_setapos(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool      xtk_nav_setasize(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool      xtk_nav_setalevel(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool      xtk_nav_setaculture(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool      xtk_nav_setalabel(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_nav_setadescribed(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_nav_setaflowsto(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_nav_setaflowsfrom(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_nav_setacontrols(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_nav_setenabled(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_nav_setsel(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_nav_setdisplay(XtkScene *scene, XtkCtrl control, XtkNavPaneMode value, XtkChangeStamp change);
bool xtk_nav_setsettings_visible(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_nav_setpane_title(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_nav_setalways_show_header(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_nav_setback_button(XtkScene *scene, XtkCtrl control, XtkNavBackButton value, XtkChangeStamp change);
bool xtk_nav_setback_enabled(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
XtkSubRef xtk_nav_onselect(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg);
XtkSubRef xtk_nav_oninvoke(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg);
XtkSubRef xtk_nav_onbackrequested(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg);
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
bool      xtk_navitem_setaname(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_navitem_setaid(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_navitem_setahelp(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_navitem_setadesc(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_navitem_setastatus(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_navitem_setaitem(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_navitem_setactype(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_navitem_setaaccel(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_navitem_setakey(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_navitem_setalandmark(XtkScene *scene, XtkCtrl control, XtkLandmark value, XtkChangeStamp change);
bool xtk_navitem_setalandname(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_navitem_setalive(XtkScene *scene, XtkCtrl control, XtkLiveSetting value, XtkChangeStamp change);
bool xtk_navitem_setaheading(XtkScene *scene, XtkCtrl control, XtkHeadingLevel value, XtkChangeStamp change);
bool xtk_navitem_setaview(XtkScene *scene, XtkCtrl control, XtkAccessView value, XtkChangeStamp change);
bool xtk_navitem_setarequired(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_navitem_setavalid(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_navitem_setaperipheral(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_navitem_setadialog(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_navitem_setapos(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_navitem_setasize(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_navitem_setalevel(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_navitem_setaculture(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_navitem_setalabel(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_navitem_setadescribed(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_navitem_setaflowsto(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_navitem_setaflowsfrom(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_navitem_setacontrols(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_navitem_seticon(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_navitem_setenabled(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_navitem_setselected(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_navitem_setexpanded(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
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
bool      xtk_tabs_setaname(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_tabs_setaid(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_tabs_setahelp(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_tabs_setadesc(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_tabs_setastatus(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_tabs_setaitem(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_tabs_setactype(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_tabs_setaaccel(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_tabs_setakey(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_tabs_setalandmark(XtkScene *scene, XtkCtrl control, XtkLandmark value, XtkChangeStamp change);
bool xtk_tabs_setalandname(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_tabs_setalive(XtkScene *scene, XtkCtrl control, XtkLiveSetting value, XtkChangeStamp change);
bool xtk_tabs_setaheading(XtkScene *scene, XtkCtrl control, XtkHeadingLevel value, XtkChangeStamp change);
bool xtk_tabs_setaview(XtkScene *scene, XtkCtrl control, XtkAccessView value, XtkChangeStamp change);
bool xtk_tabs_setarequired(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_tabs_setavalid(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_tabs_setaperipheral(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_tabs_setadialog(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_tabs_setapos(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_tabs_setasize(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_tabs_setalevel(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_tabs_setaculture(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_tabs_setalabel(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_tabs_setadescribed(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_tabs_setaflowsto(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_tabs_setaflowsfrom(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_tabs_setacontrols(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_tabs_setenabled(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_tabs_setsel(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_tabs_setnitem(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
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
bool      xtk_tabitem_setaname(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_tabitem_setaid(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_tabitem_setahelp(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_tabitem_setadesc(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_tabitem_setastatus(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_tabitem_setaitem(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_tabitem_setactype(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_tabitem_setaaccel(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_tabitem_setakey(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_tabitem_setalandmark(XtkScene *scene, XtkCtrl control, XtkLandmark value, XtkChangeStamp change);
bool xtk_tabitem_setalandname(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_tabitem_setalive(XtkScene *scene, XtkCtrl control, XtkLiveSetting value, XtkChangeStamp change);
bool xtk_tabitem_setaheading(XtkScene *scene, XtkCtrl control, XtkHeadingLevel value, XtkChangeStamp change);
bool xtk_tabitem_setaview(XtkScene *scene, XtkCtrl control, XtkAccessView value, XtkChangeStamp change);
bool xtk_tabitem_setarequired(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_tabitem_setavalid(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_tabitem_setaperipheral(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_tabitem_setadialog(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_tabitem_setapos(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_tabitem_setasize(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_tabitem_setalevel(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_tabitem_setaculture(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_tabitem_setalabel(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_tabitem_setadescribed(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_tabitem_setaflowsto(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_tabitem_setaflowsfrom(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_tabitem_setacontrols(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_tabitem_seticon(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_tabitem_setenabled(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_tabitem_setselected(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_tabitem_setexpanded(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
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
bool xtk_listitem_setaname(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_listitem_setaid(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_listitem_setahelp(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_listitem_setadesc(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_listitem_setastatus(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_listitem_setaitem(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_listitem_setactype(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_listitem_setaaccel(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_listitem_setakey(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_listitem_setalandmark(XtkScene *scene, XtkCtrl control, XtkLandmark value, XtkChangeStamp change);
bool xtk_listitem_setalandname(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_listitem_setalive(XtkScene *scene, XtkCtrl control, XtkLiveSetting value, XtkChangeStamp change);
bool xtk_listitem_setaheading(XtkScene *scene, XtkCtrl control, XtkHeadingLevel value, XtkChangeStamp change);
bool xtk_listitem_setaview(XtkScene *scene, XtkCtrl control, XtkAccessView value, XtkChangeStamp change);
bool xtk_listitem_setarequired(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_listitem_setavalid(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_listitem_setaperipheral(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_listitem_setadialog(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_listitem_setapos(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_listitem_setasize(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_listitem_setalevel(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_listitem_setaculture(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_listitem_setalabel(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_listitem_setadescribed(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
);
bool xtk_listitem_setaflowsto(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_listitem_setaflowsfrom(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
);
bool xtk_listitem_setacontrols(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_listitem_seticon(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_listitem_setenabled(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_listitem_setselected(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_listitem_setexpanded(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
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
bool      xtk_listbox_setaname(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_listbox_setaid(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_listbox_setahelp(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_listbox_setadesc(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_listbox_setastatus(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_listbox_setaitem(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_listbox_setactype(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_listbox_setaaccel(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_listbox_setakey(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_listbox_setalandmark(XtkScene *scene, XtkCtrl control, XtkLandmark value, XtkChangeStamp change);
bool xtk_listbox_setalandname(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_listbox_setalive(XtkScene *scene, XtkCtrl control, XtkLiveSetting value, XtkChangeStamp change);
bool xtk_listbox_setaheading(XtkScene *scene, XtkCtrl control, XtkHeadingLevel value, XtkChangeStamp change);
bool xtk_listbox_setaview(XtkScene *scene, XtkCtrl control, XtkAccessView value, XtkChangeStamp change);
bool xtk_listbox_setarequired(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_listbox_setavalid(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_listbox_setaperipheral(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_listbox_setadialog(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_listbox_setapos(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_listbox_setasize(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_listbox_setalevel(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_listbox_setaculture(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_listbox_setalabel(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_listbox_setadescribed(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_listbox_setaflowsto(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_listbox_setaflowsfrom(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_listbox_setacontrols(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_listbox_setenabled(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_listbox_setsel(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_listbox_setnitem(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_listbox_setitemh(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_listbox_setitemw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_listbox_setncol(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_listbox_setmode(XtkScene *scene, XtkCtrl control, XtkListSelMode value, XtkChangeStamp change);
bool xtk_listbox_setfirst(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_listbox_setrectsel(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
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
bool xtk_gridview_setaname(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_gridview_setaid(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_gridview_setahelp(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_gridview_setadesc(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_gridview_setastatus(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_gridview_setaitem(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_gridview_setactype(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_gridview_setaaccel(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_gridview_setakey(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_gridview_setalandmark(XtkScene *scene, XtkCtrl control, XtkLandmark value, XtkChangeStamp change);
bool xtk_gridview_setalandname(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_gridview_setalive(XtkScene *scene, XtkCtrl control, XtkLiveSetting value, XtkChangeStamp change);
bool xtk_gridview_setaheading(XtkScene *scene, XtkCtrl control, XtkHeadingLevel value, XtkChangeStamp change);
bool xtk_gridview_setaview(XtkScene *scene, XtkCtrl control, XtkAccessView value, XtkChangeStamp change);
bool xtk_gridview_setarequired(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_gridview_setavalid(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_gridview_setaperipheral(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_gridview_setadialog(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_gridview_setapos(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_gridview_setasize(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_gridview_setalevel(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_gridview_setaculture(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_gridview_setalabel(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_gridview_setadescribed(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
);
bool xtk_gridview_setaflowsto(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_gridview_setaflowsfrom(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
);
bool xtk_gridview_setacontrols(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_gridview_setenabled(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_gridview_setsel(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_gridview_setnitem(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_gridview_setitemh(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_gridview_setitemw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_gridview_setncol(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_gridview_setmode(XtkScene *scene, XtkCtrl control, XtkListSelMode value, XtkChangeStamp change);
bool xtk_gridview_setfirst(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_gridview_setrectsel(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
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
bool xtk_repeater_setaname(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_repeater_setaid(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_repeater_setahelp(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_repeater_setadesc(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_repeater_setastatus(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_repeater_setaitem(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_repeater_setactype(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_repeater_setaaccel(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_repeater_setakey(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_repeater_setalandmark(XtkScene *scene, XtkCtrl control, XtkLandmark value, XtkChangeStamp change);
bool xtk_repeater_setalandname(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_repeater_setalive(XtkScene *scene, XtkCtrl control, XtkLiveSetting value, XtkChangeStamp change);
bool xtk_repeater_setaheading(XtkScene *scene, XtkCtrl control, XtkHeadingLevel value, XtkChangeStamp change);
bool xtk_repeater_setaview(XtkScene *scene, XtkCtrl control, XtkAccessView value, XtkChangeStamp change);
bool xtk_repeater_setarequired(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_repeater_setavalid(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_repeater_setaperipheral(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_repeater_setadialog(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_repeater_setapos(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_repeater_setasize(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_repeater_setalevel(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_repeater_setaculture(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_repeater_setalabel(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_repeater_setadescribed(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
);
bool xtk_repeater_setaflowsto(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_repeater_setaflowsfrom(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
);
bool xtk_repeater_setacontrols(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_repeater_setenabled(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_repeater_setsel(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_repeater_setnitem(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_repeater_setitemh(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_repeater_setitemw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_repeater_setncol(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_repeater_setmode(XtkScene *scene, XtkCtrl control, XtkListSelMode value, XtkChangeStamp change);
bool xtk_repeater_setfirst(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_repeater_setrectsel(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
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
bool xtk_itemsview_setaname(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_itemsview_setaid(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_itemsview_setahelp(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_itemsview_setadesc(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_itemsview_setastatus(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_itemsview_setaitem(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_itemsview_setactype(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_itemsview_setaaccel(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_itemsview_setakey(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_itemsview_setalandmark(XtkScene *scene, XtkCtrl control, XtkLandmark value, XtkChangeStamp change);
bool xtk_itemsview_setalandname(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
);
bool xtk_itemsview_setalive(XtkScene *scene, XtkCtrl control, XtkLiveSetting value, XtkChangeStamp change);
bool xtk_itemsview_setaheading(XtkScene *scene, XtkCtrl control, XtkHeadingLevel value, XtkChangeStamp change);
bool xtk_itemsview_setaview(XtkScene *scene, XtkCtrl control, XtkAccessView value, XtkChangeStamp change);
bool xtk_itemsview_setarequired(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_itemsview_setavalid(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_itemsview_setaperipheral(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_itemsview_setadialog(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_itemsview_setapos(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_itemsview_setasize(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_itemsview_setalevel(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_itemsview_setaculture(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_itemsview_setalabel(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_itemsview_setadescribed(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
);
bool xtk_itemsview_setaflowsto(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_itemsview_setaflowsfrom(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
);
bool xtk_itemsview_setacontrols(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
);
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
bool      xtk_flip_setaname(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_flip_setaid(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_flip_setahelp(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_flip_setadesc(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_flip_setastatus(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_flip_setaitem(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_flip_setactype(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_flip_setaaccel(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_flip_setakey(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_flip_setalandmark(XtkScene *scene, XtkCtrl control, XtkLandmark value, XtkChangeStamp change);
bool xtk_flip_setalandname(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_flip_setalive(XtkScene *scene, XtkCtrl control, XtkLiveSetting value, XtkChangeStamp change);
bool xtk_flip_setaheading(XtkScene *scene, XtkCtrl control, XtkHeadingLevel value, XtkChangeStamp change);
bool xtk_flip_setaview(XtkScene *scene, XtkCtrl control, XtkAccessView value, XtkChangeStamp change);
bool xtk_flip_setarequired(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_flip_setavalid(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_flip_setaperipheral(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_flip_setadialog(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_flip_setapos(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_flip_setasize(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_flip_setalevel(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_flip_setaculture(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_flip_setalabel(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_flip_setadescribed(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_flip_setaflowsto(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_flip_setaflowsfrom(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_flip_setacontrols(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_flip_setsel(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_flip_setdir(XtkScene *scene, XtkCtrl control, XtkStackDirection value, XtkChangeStamp change);
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
bool      xtk_pips_setaname(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_pips_setaid(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_pips_setahelp(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_pips_setadesc(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_pips_setastatus(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_pips_setaitem(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_pips_setactype(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_pips_setaaccel(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_pips_setakey(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_pips_setalandmark(XtkScene *scene, XtkCtrl control, XtkLandmark value, XtkChangeStamp change);
bool xtk_pips_setalandname(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_pips_setalive(XtkScene *scene, XtkCtrl control, XtkLiveSetting value, XtkChangeStamp change);
bool xtk_pips_setaheading(XtkScene *scene, XtkCtrl control, XtkHeadingLevel value, XtkChangeStamp change);
bool xtk_pips_setaview(XtkScene *scene, XtkCtrl control, XtkAccessView value, XtkChangeStamp change);
bool xtk_pips_setarequired(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_pips_setavalid(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_pips_setaperipheral(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_pips_setadialog(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_pips_setapos(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_pips_setasize(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_pips_setalevel(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_pips_setaculture(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_pips_setalabel(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_pips_setadescribed(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_pips_setaflowsto(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_pips_setaflowsfrom(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_pips_setacontrols(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_pips_setsel(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_pips_setnitem(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_pips_setdir(XtkScene *scene, XtkCtrl control, XtkStackDirection value, XtkChangeStamp change);
bool xtk_pips_setmaxvisible(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_pips_setnav(XtkScene *scene, XtkCtrl control, XtkPipsNavVis value, XtkChangeStamp change);
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
bool      xtk_suggest_setaname(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_suggest_setaid(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_suggest_setahelp(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_suggest_setadesc(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_suggest_setastatus(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_suggest_setaitem(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_suggest_setactype(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_suggest_setaaccel(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_suggest_setakey(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_suggest_setalandmark(XtkScene *scene, XtkCtrl control, XtkLandmark value, XtkChangeStamp change);
bool xtk_suggest_setalandname(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_suggest_setalive(XtkScene *scene, XtkCtrl control, XtkLiveSetting value, XtkChangeStamp change);
bool xtk_suggest_setaheading(XtkScene *scene, XtkCtrl control, XtkHeadingLevel value, XtkChangeStamp change);
bool xtk_suggest_setaview(XtkScene *scene, XtkCtrl control, XtkAccessView value, XtkChangeStamp change);
bool xtk_suggest_setarequired(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_suggest_setavalid(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_suggest_setaperipheral(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_suggest_setadialog(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_suggest_setapos(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_suggest_setasize(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_suggest_setalevel(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_suggest_setaculture(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_suggest_setalabel(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_suggest_setadescribed(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_suggest_setaflowsto(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_suggest_setaflowsfrom(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_suggest_setacontrols(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_suggest_setenabled(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_suggest_setplaceholder(
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
bool xtk_togglesplit_setaname(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_togglesplit_setaid(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_togglesplit_setahelp(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_togglesplit_setadesc(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_togglesplit_setastatus(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
);
bool xtk_togglesplit_setaitem(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_togglesplit_setactype(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_togglesplit_setaaccel(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_togglesplit_setakey(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_togglesplit_setalandmark(XtkScene *scene, XtkCtrl control, XtkLandmark value, XtkChangeStamp change);
bool xtk_togglesplit_setalandname(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
);
bool xtk_togglesplit_setalive(XtkScene *scene, XtkCtrl control, XtkLiveSetting value, XtkChangeStamp change);
bool xtk_togglesplit_setaheading(XtkScene *scene, XtkCtrl control, XtkHeadingLevel value, XtkChangeStamp change);
bool xtk_togglesplit_setaview(XtkScene *scene, XtkCtrl control, XtkAccessView value, XtkChangeStamp change);
bool xtk_togglesplit_setarequired(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_togglesplit_setavalid(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_togglesplit_setaperipheral(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_togglesplit_setadialog(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_togglesplit_setapos(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_togglesplit_setasize(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_togglesplit_setalevel(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_togglesplit_setaculture(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_togglesplit_setalabel(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_togglesplit_setadescribed(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
);
bool xtk_togglesplit_setaflowsto(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
);
bool xtk_togglesplit_setaflowsfrom(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
);
bool xtk_togglesplit_setacontrols(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
);
bool      xtk_togglesplit_setenabled(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool      xtk_togglesplit_setchecked(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
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
bool xtk_radiogroup_setaname(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_radiogroup_setaid(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_radiogroup_setahelp(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_radiogroup_setadesc(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_radiogroup_setastatus(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_radiogroup_setaitem(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_radiogroup_setactype(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_radiogroup_setaaccel(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_radiogroup_setakey(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_radiogroup_setalandmark(XtkScene *scene, XtkCtrl control, XtkLandmark value, XtkChangeStamp change);
bool xtk_radiogroup_setalandname(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
);
bool xtk_radiogroup_setalive(XtkScene *scene, XtkCtrl control, XtkLiveSetting value, XtkChangeStamp change);
bool xtk_radiogroup_setaheading(XtkScene *scene, XtkCtrl control, XtkHeadingLevel value, XtkChangeStamp change);
bool xtk_radiogroup_setaview(XtkScene *scene, XtkCtrl control, XtkAccessView value, XtkChangeStamp change);
bool xtk_radiogroup_setarequired(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_radiogroup_setavalid(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_radiogroup_setaperipheral(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_radiogroup_setadialog(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_radiogroup_setapos(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_radiogroup_setasize(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_radiogroup_setalevel(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_radiogroup_setaculture(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_radiogroup_setalabel(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_radiogroup_setadescribed(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
);
bool xtk_radiogroup_setaflowsto(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
);
bool xtk_radiogroup_setaflowsfrom(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
);
bool xtk_radiogroup_setacontrols(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
);
bool      xtk_radiogroup_setenabled(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool      xtk_radiogroup_setsel(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool      xtk_radiogroup_setnitem(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool      xtk_radiogroup_setncol(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
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
bool      xtk_rating_setaname(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_rating_setaid(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_rating_setahelp(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_rating_setadesc(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_rating_setastatus(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_rating_setaitem(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_rating_setactype(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_rating_setaaccel(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_rating_setakey(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_rating_setalandmark(XtkScene *scene, XtkCtrl control, XtkLandmark value, XtkChangeStamp change);
bool xtk_rating_setalandname(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_rating_setalive(XtkScene *scene, XtkCtrl control, XtkLiveSetting value, XtkChangeStamp change);
bool xtk_rating_setaheading(XtkScene *scene, XtkCtrl control, XtkHeadingLevel value, XtkChangeStamp change);
bool xtk_rating_setaview(XtkScene *scene, XtkCtrl control, XtkAccessView value, XtkChangeStamp change);
bool xtk_rating_setarequired(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_rating_setavalid(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_rating_setaperipheral(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_rating_setadialog(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_rating_setapos(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_rating_setasize(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_rating_setalevel(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_rating_setaculture(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_rating_setalabel(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_rating_setadescribed(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_rating_setaflowsto(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_rating_setaflowsfrom(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_rating_setacontrols(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_rating_setvalue(XtkScene *scene, XtkCtrl control, double value, XtkChangeStamp change);
bool xtk_rating_setmax(XtkScene *scene, XtkCtrl control, double value, XtkChangeStamp change);
bool xtk_rating_settext(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_rating_setplaceholder(XtkScene *scene, XtkCtrl control, double value, XtkChangeStamp change);
bool xtk_rating_setinitial(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_rating_setclear(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_rating_setreadonly(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
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
bool xtk_selector_setaname(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_selector_setaid(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_selector_setahelp(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_selector_setadesc(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_selector_setastatus(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_selector_setaitem(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_selector_setactype(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_selector_setaaccel(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_selector_setakey(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_selector_setalandmark(XtkScene *scene, XtkCtrl control, XtkLandmark value, XtkChangeStamp change);
bool xtk_selector_setalandname(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_selector_setalive(XtkScene *scene, XtkCtrl control, XtkLiveSetting value, XtkChangeStamp change);
bool xtk_selector_setaheading(XtkScene *scene, XtkCtrl control, XtkHeadingLevel value, XtkChangeStamp change);
bool xtk_selector_setaview(XtkScene *scene, XtkCtrl control, XtkAccessView value, XtkChangeStamp change);
bool xtk_selector_setarequired(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_selector_setavalid(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_selector_setaperipheral(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_selector_setadialog(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_selector_setapos(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_selector_setasize(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_selector_setalevel(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_selector_setaculture(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_selector_setalabel(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_selector_setadescribed(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
);
bool xtk_selector_setaflowsto(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_selector_setaflowsfrom(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
);
bool xtk_selector_setacontrols(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_selector_setenabled(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_selector_setsel(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_selector_setnitem(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
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
bool xtk_selectoritem_setaname(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_selectoritem_setaid(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_selectoritem_setahelp(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_selectoritem_setadesc(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_selectoritem_setastatus(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
);
bool xtk_selectoritem_setaitem(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_selectoritem_setactype(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
);
bool xtk_selectoritem_setaaccel(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
);
bool xtk_selectoritem_setakey(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_selectoritem_setalandmark(XtkScene *scene, XtkCtrl control, XtkLandmark value, XtkChangeStamp change);
bool xtk_selectoritem_setalandname(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
);
bool xtk_selectoritem_setalive(XtkScene *scene, XtkCtrl control, XtkLiveSetting value, XtkChangeStamp change);
bool xtk_selectoritem_setaheading(XtkScene *scene, XtkCtrl control, XtkHeadingLevel value, XtkChangeStamp change);
bool xtk_selectoritem_setaview(XtkScene *scene, XtkCtrl control, XtkAccessView value, XtkChangeStamp change);
bool xtk_selectoritem_setarequired(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_selectoritem_setavalid(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_selectoritem_setaperipheral(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_selectoritem_setadialog(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_selectoritem_setapos(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_selectoritem_setasize(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_selectoritem_setalevel(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_selectoritem_setaculture(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_selectoritem_setalabel(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
);
bool xtk_selectoritem_setadescribed(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
);
bool xtk_selectoritem_setaflowsto(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
);
bool xtk_selectoritem_setaflowsfrom(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
);
bool xtk_selectoritem_setacontrols(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
);
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
bool xtk_breadcrumb_setaname(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_breadcrumb_setaid(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_breadcrumb_setahelp(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_breadcrumb_setadesc(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_breadcrumb_setastatus(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_breadcrumb_setaitem(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_breadcrumb_setactype(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_breadcrumb_setaaccel(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_breadcrumb_setakey(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_breadcrumb_setalandmark(XtkScene *scene, XtkCtrl control, XtkLandmark value, XtkChangeStamp change);
bool xtk_breadcrumb_setalandname(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
);
bool xtk_breadcrumb_setalive(XtkScene *scene, XtkCtrl control, XtkLiveSetting value, XtkChangeStamp change);
bool xtk_breadcrumb_setaheading(XtkScene *scene, XtkCtrl control, XtkHeadingLevel value, XtkChangeStamp change);
bool xtk_breadcrumb_setaview(XtkScene *scene, XtkCtrl control, XtkAccessView value, XtkChangeStamp change);
bool xtk_breadcrumb_setarequired(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_breadcrumb_setavalid(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_breadcrumb_setaperipheral(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_breadcrumb_setadialog(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_breadcrumb_setapos(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_breadcrumb_setasize(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_breadcrumb_setalevel(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_breadcrumb_setaculture(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_breadcrumb_setalabel(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_breadcrumb_setadescribed(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
);
bool xtk_breadcrumb_setaflowsto(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
);
bool xtk_breadcrumb_setaflowsfrom(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
);
bool xtk_breadcrumb_setacontrols(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
);
bool      xtk_breadcrumb_setenabled(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool      xtk_breadcrumb_setsel(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool      xtk_breadcrumb_setnitem(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
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
bool      xtk_crumb_setaname(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_crumb_setaid(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_crumb_setahelp(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_crumb_setadesc(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_crumb_setastatus(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_crumb_setaitem(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_crumb_setactype(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_crumb_setaaccel(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_crumb_setakey(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_crumb_setalandmark(XtkScene *scene, XtkCtrl control, XtkLandmark value, XtkChangeStamp change);
bool xtk_crumb_setalandname(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_crumb_setalive(XtkScene *scene, XtkCtrl control, XtkLiveSetting value, XtkChangeStamp change);
bool xtk_crumb_setaheading(XtkScene *scene, XtkCtrl control, XtkHeadingLevel value, XtkChangeStamp change);
bool xtk_crumb_setaview(XtkScene *scene, XtkCtrl control, XtkAccessView value, XtkChangeStamp change);
bool xtk_crumb_setarequired(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_crumb_setavalid(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_crumb_setaperipheral(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_crumb_setadialog(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_crumb_setapos(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_crumb_setasize(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_crumb_setalevel(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_crumb_setaculture(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_crumb_setalabel(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_crumb_setadescribed(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_crumb_setaflowsto(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_crumb_setaflowsfrom(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_crumb_setacontrols(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_crumb_seticon(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_crumb_setenabled(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_crumb_setselected(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_crumb_setexpanded(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
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
bool xtk_teachtip_setaname(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_teachtip_setaid(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_teachtip_setahelp(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_teachtip_setadesc(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_teachtip_setastatus(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_teachtip_setaitem(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_teachtip_setactype(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_teachtip_setaaccel(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_teachtip_setakey(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_teachtip_setalandmark(XtkScene *scene, XtkCtrl control, XtkLandmark value, XtkChangeStamp change);
bool xtk_teachtip_setalandname(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_teachtip_setalive(XtkScene *scene, XtkCtrl control, XtkLiveSetting value, XtkChangeStamp change);
bool xtk_teachtip_setaheading(XtkScene *scene, XtkCtrl control, XtkHeadingLevel value, XtkChangeStamp change);
bool xtk_teachtip_setaview(XtkScene *scene, XtkCtrl control, XtkAccessView value, XtkChangeStamp change);
bool xtk_teachtip_setarequired(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_teachtip_setavalid(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_teachtip_setaperipheral(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_teachtip_setadialog(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_teachtip_setapos(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_teachtip_setasize(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_teachtip_setalevel(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_teachtip_setaculture(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_teachtip_setalabel(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_teachtip_setadescribed(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
);
bool xtk_teachtip_setaflowsto(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_teachtip_setaflowsfrom(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
);
bool xtk_teachtip_setacontrols(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_teachtip_settext(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
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
bool      xtk_tree_setaname(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_tree_setaid(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_tree_setahelp(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_tree_setadesc(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_tree_setastatus(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_tree_setaitem(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_tree_setactype(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_tree_setaaccel(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_tree_setakey(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_tree_setalandmark(XtkScene *scene, XtkCtrl control, XtkLandmark value, XtkChangeStamp change);
bool xtk_tree_setalandname(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_tree_setalive(XtkScene *scene, XtkCtrl control, XtkLiveSetting value, XtkChangeStamp change);
bool xtk_tree_setaheading(XtkScene *scene, XtkCtrl control, XtkHeadingLevel value, XtkChangeStamp change);
bool xtk_tree_setaview(XtkScene *scene, XtkCtrl control, XtkAccessView value, XtkChangeStamp change);
bool xtk_tree_setarequired(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_tree_setavalid(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_tree_setaperipheral(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_tree_setadialog(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_tree_setapos(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_tree_setasize(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_tree_setalevel(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_tree_setaculture(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_tree_setalabel(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_tree_setadescribed(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_tree_setaflowsto(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_tree_setaflowsfrom(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_tree_setacontrols(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_tree_setenabled(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_tree_setsel(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_tree_setnitem(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_tree_setitemh(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
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
bool xtk_treeitem_setaname(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_treeitem_setaid(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_treeitem_setahelp(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_treeitem_setadesc(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_treeitem_setastatus(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_treeitem_setaitem(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_treeitem_setactype(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_treeitem_setaaccel(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_treeitem_setakey(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_treeitem_setalandmark(XtkScene *scene, XtkCtrl control, XtkLandmark value, XtkChangeStamp change);
bool xtk_treeitem_setalandname(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_treeitem_setalive(XtkScene *scene, XtkCtrl control, XtkLiveSetting value, XtkChangeStamp change);
bool xtk_treeitem_setaheading(XtkScene *scene, XtkCtrl control, XtkHeadingLevel value, XtkChangeStamp change);
bool xtk_treeitem_setaview(XtkScene *scene, XtkCtrl control, XtkAccessView value, XtkChangeStamp change);
bool xtk_treeitem_setarequired(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_treeitem_setavalid(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_treeitem_setaperipheral(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_treeitem_setadialog(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_treeitem_setapos(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_treeitem_setasize(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_treeitem_setalevel(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_treeitem_setaculture(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_treeitem_setalabel(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_treeitem_setadescribed(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
);
bool xtk_treeitem_setaflowsto(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_treeitem_setaflowsfrom(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
);
bool xtk_treeitem_setacontrols(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_treeitem_seticon(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_treeitem_setenabled(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_treeitem_setselected(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_treeitem_setexpanded(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
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
bool      xtk_refresh_setaname(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_refresh_setaid(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_refresh_setahelp(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_refresh_setadesc(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_refresh_setastatus(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_refresh_setaitem(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_refresh_setactype(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_refresh_setaaccel(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_refresh_setakey(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_refresh_setalandmark(XtkScene *scene, XtkCtrl control, XtkLandmark value, XtkChangeStamp change);
bool xtk_refresh_setalandname(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_refresh_setalive(XtkScene *scene, XtkCtrl control, XtkLiveSetting value, XtkChangeStamp change);
bool xtk_refresh_setaheading(XtkScene *scene, XtkCtrl control, XtkHeadingLevel value, XtkChangeStamp change);
bool xtk_refresh_setaview(XtkScene *scene, XtkCtrl control, XtkAccessView value, XtkChangeStamp change);
bool xtk_refresh_setarequired(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_refresh_setavalid(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_refresh_setaperipheral(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_refresh_setadialog(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_refresh_setapos(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_refresh_setasize(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_refresh_setalevel(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_refresh_setaculture(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_refresh_setalabel(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_refresh_setadescribed(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_refresh_setaflowsto(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_refresh_setaflowsfrom(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_refresh_setacontrols(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_refresh_setdirection(XtkScene *scene, XtkCtrl control, XtkPullDirection value, XtkChangeStamp change);
bool xtk_refresh_setvisualizer(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_refresh_setthreshold(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_refresh_setrefreshing(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
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
bool      xtk_avatar_setaname(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_avatar_setaid(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_avatar_setahelp(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_avatar_setadesc(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_avatar_setastatus(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_avatar_setaitem(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_avatar_setactype(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_avatar_setaaccel(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_avatar_setakey(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_avatar_setalandmark(XtkScene *scene, XtkCtrl control, XtkLandmark value, XtkChangeStamp change);
bool xtk_avatar_setalandname(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_avatar_setalive(XtkScene *scene, XtkCtrl control, XtkLiveSetting value, XtkChangeStamp change);
bool xtk_avatar_setaheading(XtkScene *scene, XtkCtrl control, XtkHeadingLevel value, XtkChangeStamp change);
bool xtk_avatar_setaview(XtkScene *scene, XtkCtrl control, XtkAccessView value, XtkChangeStamp change);
bool xtk_avatar_setarequired(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_avatar_setavalid(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_avatar_setaperipheral(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_avatar_setadialog(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_avatar_setapos(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_avatar_setasize(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_avatar_setalevel(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_avatar_setaculture(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_avatar_setalabel(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_avatar_setadescribed(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_avatar_setaflowsto(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_avatar_setaflowsfrom(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_avatar_setacontrols(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_avatar_settext(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_avatar_setinitials(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_avatar_setsrc(XtkScene *scene, XtkCtrl control, XtkResource value, XtkChangeStamp change);
bool xtk_avatar_setbadgeglyph(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_avatar_setbadgevalue(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_avatar_setbadgeimage(XtkScene *scene, XtkCtrl control, XtkResource value, XtkChangeStamp change);
bool xtk_avatar_setbadgetext(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
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
bool xtk_pager_setaname(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_pager_setaid(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_pager_setahelp(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_pager_setadesc(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_pager_setastatus(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_pager_setaitem(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_pager_setactype(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_pager_setaaccel(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_pager_setakey(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_pager_setalandmark(XtkScene *scene, XtkCtrl control, XtkLandmark value, XtkChangeStamp change);
bool xtk_pager_setalandname(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_pager_setalive(XtkScene *scene, XtkCtrl control, XtkLiveSetting value, XtkChangeStamp change);
bool xtk_pager_setaheading(XtkScene *scene, XtkCtrl control, XtkHeadingLevel value, XtkChangeStamp change);
bool xtk_pager_setaview(XtkScene *scene, XtkCtrl control, XtkAccessView value, XtkChangeStamp change);
bool xtk_pager_setarequired(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_pager_setavalid(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_pager_setaperipheral(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_pager_setadialog(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_pager_setapos(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_pager_setasize(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_pager_setalevel(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_pager_setaculture(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_pager_setalabel(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_pager_setadescribed(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_pager_setaflowsto(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_pager_setaflowsfrom(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_pager_setacontrols(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_pager_setsel(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_pager_setnitem(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_pager_setdisplay(XtkScene *scene, XtkCtrl control, XtkPagerDisplayMode value, XtkChangeStamp change);
bool xtk_pager_setfirst(XtkScene *scene, XtkCtrl control, XtkPagerButtonVis value, XtkChangeStamp change);
bool xtk_pager_setprev(XtkScene *scene, XtkCtrl control, XtkPagerButtonVis value, XtkChangeStamp change);
bool xtk_pager_setnext(XtkScene *scene, XtkCtrl control, XtkPagerButtonVis value, XtkChangeStamp change);
bool xtk_pager_setlast(XtkScene *scene, XtkCtrl control, XtkPagerButtonVis value, XtkChangeStamp change);
bool xtk_pager_setprefix(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_pager_setsuffix(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_pager_sethideends(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
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
bool xtk_splitview_setaname(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_splitview_setaid(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_splitview_setahelp(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_splitview_setadesc(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_splitview_setastatus(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_splitview_setaitem(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_splitview_setactype(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_splitview_setaaccel(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_splitview_setakey(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_splitview_setalandmark(XtkScene *scene, XtkCtrl control, XtkLandmark value, XtkChangeStamp change);
bool xtk_splitview_setalandname(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
);
bool xtk_splitview_setalive(XtkScene *scene, XtkCtrl control, XtkLiveSetting value, XtkChangeStamp change);
bool xtk_splitview_setaheading(XtkScene *scene, XtkCtrl control, XtkHeadingLevel value, XtkChangeStamp change);
bool xtk_splitview_setaview(XtkScene *scene, XtkCtrl control, XtkAccessView value, XtkChangeStamp change);
bool xtk_splitview_setarequired(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_splitview_setavalid(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_splitview_setaperipheral(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_splitview_setadialog(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_splitview_setapos(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_splitview_setasize(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_splitview_setalevel(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_splitview_setaculture(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_splitview_setalabel(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_splitview_setadescribed(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
);
bool xtk_splitview_setaflowsto(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_splitview_setaflowsfrom(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
);
bool xtk_splitview_setacontrols(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
);
bool xtk_splitview_setdir(XtkScene *scene, XtkCtrl control, XtkStackDirection value, XtkChangeStamp change);
bool xtk_splitview_setgap(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_splitview_setpl(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_splitview_setpt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_splitview_setpr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_splitview_setpb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_splitview_setfill(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_splitview_setopen(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_splitview_setdisplay(XtkScene *scene, XtkCtrl control, XtkSplitViewDisplayMode value, XtkChangeStamp change);
bool xtk_splitview_setplacement(
  XtkScene *scene, XtkCtrl control, XtkSplitViewPanePlacement value, XtkChangeStamp change
);
bool      xtk_splitview_setopenlen(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_splitview_setcompactlen(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
XtkSubRef xtk_splitview_onopen(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg);
bool      xtk_splitpane_setw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_splitpane_seth(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_splitpane_setgrow(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_splitpane_setshrink(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_splitpane_setself(XtkScene *scene, XtkCtrl control, XentFlexAlign value, XtkChangeStamp change);
bool      xtk_splitpane_setml(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_splitpane_setmt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_splitpane_setmr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_splitpane_setmb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool      xtk_splitpane_settip(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_splitpane_setaname(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_splitpane_setaid(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_splitpane_setahelp(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_splitpane_setadesc(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_splitpane_setastatus(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_splitpane_setaitem(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_splitpane_setactype(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_splitpane_setaaccel(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_splitpane_setakey(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_splitpane_setalandmark(XtkScene *scene, XtkCtrl control, XtkLandmark value, XtkChangeStamp change);
bool xtk_splitpane_setalandname(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
);
bool xtk_splitpane_setalive(XtkScene *scene, XtkCtrl control, XtkLiveSetting value, XtkChangeStamp change);
bool xtk_splitpane_setaheading(XtkScene *scene, XtkCtrl control, XtkHeadingLevel value, XtkChangeStamp change);
bool xtk_splitpane_setaview(XtkScene *scene, XtkCtrl control, XtkAccessView value, XtkChangeStamp change);
bool xtk_splitpane_setarequired(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_splitpane_setavalid(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_splitpane_setaperipheral(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_splitpane_setadialog(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_splitpane_setapos(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_splitpane_setasize(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_splitpane_setalevel(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_splitpane_setaculture(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_splitpane_setalabel(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_splitpane_setadescribed(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
);
bool xtk_splitpane_setaflowsto(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_splitpane_setaflowsfrom(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
);
bool xtk_splitpane_setacontrols(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
);
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
bool      xtk_splitpane_setflow(XtkScene *scene, XtkCtrl control, XentDirection value, XtkChangeStamp change);
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
bool xtk_splitbody_setaname(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_splitbody_setaid(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_splitbody_setahelp(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_splitbody_setadesc(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_splitbody_setastatus(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_splitbody_setaitem(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_splitbody_setactype(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_splitbody_setaaccel(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_splitbody_setakey(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_splitbody_setalandmark(XtkScene *scene, XtkCtrl control, XtkLandmark value, XtkChangeStamp change);
bool xtk_splitbody_setalandname(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
);
bool xtk_splitbody_setalive(XtkScene *scene, XtkCtrl control, XtkLiveSetting value, XtkChangeStamp change);
bool xtk_splitbody_setaheading(XtkScene *scene, XtkCtrl control, XtkHeadingLevel value, XtkChangeStamp change);
bool xtk_splitbody_setaview(XtkScene *scene, XtkCtrl control, XtkAccessView value, XtkChangeStamp change);
bool xtk_splitbody_setarequired(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_splitbody_setavalid(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_splitbody_setaperipheral(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_splitbody_setadialog(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_splitbody_setapos(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_splitbody_setasize(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_splitbody_setalevel(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_splitbody_setaculture(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_splitbody_setalabel(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_splitbody_setadescribed(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
);
bool xtk_splitbody_setaflowsto(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_splitbody_setaflowsfrom(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
);
bool xtk_splitbody_setacontrols(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
);
bool xtk_splitbody_setdir(XtkScene *scene, XtkCtrl control, XtkStackDirection value, XtkChangeStamp change);
bool xtk_splitbody_setitems(XtkScene *scene, XtkCtrl control, XentFlexAlign value, XtkChangeStamp change);
bool xtk_splitbody_setjustify(XtkScene *scene, XtkCtrl control, XentFlexJustify value, XtkChangeStamp change);
bool xtk_splitbody_setgap(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_splitbody_setpl(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_splitbody_setpt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_splitbody_setpr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_splitbody_setpb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_splitbody_setfill(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_splitbody_setfitw(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_splitbody_setfith(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_splitbody_setwrap(XtkScene *scene, XtkCtrl control, XentFlexWrap value, XtkChangeStamp change);
bool xtk_splitbody_setdrop(XtkScene *scene, XtkCtrl control, XtkDropOperation value, XtkChangeStamp change);
bool xtk_splitbody_setdragtext(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_splitbody_setdragfiles(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
);
bool      xtk_splitbody_setflow(XtkScene *scene, XtkCtrl control, XentDirection value, XtkChangeStamp change);
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
bool xtk_titlebar_setaname(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_titlebar_setaid(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_titlebar_setahelp(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_titlebar_setadesc(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_titlebar_setastatus(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_titlebar_setaitem(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_titlebar_setactype(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_titlebar_setaaccel(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_titlebar_setakey(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_titlebar_setalandmark(XtkScene *scene, XtkCtrl control, XtkLandmark value, XtkChangeStamp change);
bool xtk_titlebar_setalandname(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_titlebar_setalive(XtkScene *scene, XtkCtrl control, XtkLiveSetting value, XtkChangeStamp change);
bool xtk_titlebar_setaheading(XtkScene *scene, XtkCtrl control, XtkHeadingLevel value, XtkChangeStamp change);
bool xtk_titlebar_setaview(XtkScene *scene, XtkCtrl control, XtkAccessView value, XtkChangeStamp change);
bool xtk_titlebar_setarequired(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_titlebar_setavalid(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_titlebar_setaperipheral(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_titlebar_setadialog(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_titlebar_setapos(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_titlebar_setasize(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_titlebar_setalevel(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_titlebar_setaculture(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_titlebar_setalabel(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_titlebar_setadescribed(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
);
bool xtk_titlebar_setaflowsto(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_titlebar_setaflowsfrom(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
);
bool xtk_titlebar_setacontrols(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_titlebar_settext(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
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
bool xtk_scrollbar_setaname(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_scrollbar_setaid(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_scrollbar_setahelp(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_scrollbar_setadesc(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_scrollbar_setastatus(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_scrollbar_setaitem(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_scrollbar_setactype(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_scrollbar_setaaccel(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_scrollbar_setakey(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_scrollbar_setalandmark(XtkScene *scene, XtkCtrl control, XtkLandmark value, XtkChangeStamp change);
bool xtk_scrollbar_setalandname(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
);
bool xtk_scrollbar_setalive(XtkScene *scene, XtkCtrl control, XtkLiveSetting value, XtkChangeStamp change);
bool xtk_scrollbar_setaheading(XtkScene *scene, XtkCtrl control, XtkHeadingLevel value, XtkChangeStamp change);
bool xtk_scrollbar_setaview(XtkScene *scene, XtkCtrl control, XtkAccessView value, XtkChangeStamp change);
bool xtk_scrollbar_setarequired(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_scrollbar_setavalid(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_scrollbar_setaperipheral(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_scrollbar_setadialog(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_scrollbar_setapos(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_scrollbar_setasize(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_scrollbar_setalevel(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_scrollbar_setaculture(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_scrollbar_setalabel(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_scrollbar_setadescribed(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
);
bool xtk_scrollbar_setaflowsto(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_scrollbar_setaflowsfrom(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
);
bool xtk_scrollbar_setacontrols(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
);
bool xtk_scrollbar_setenabled(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_scrollbar_setdir(XtkScene *scene, XtkCtrl control, XtkStackDirection value, XtkChangeStamp change);
bool xtk_scrollbar_setmin(XtkScene *scene, XtkCtrl control, double value, XtkChangeStamp change);
bool xtk_scrollbar_setmax(XtkScene *scene, XtkCtrl control, double value, XtkChangeStamp change);
bool xtk_scrollbar_setvalue(XtkScene *scene, XtkCtrl control, double value, XtkChangeStamp change);
bool xtk_scrollbar_setviewport(XtkScene *scene, XtkCtrl control, double value, XtkChangeStamp change);
bool xtk_scrollbar_setsmallchange(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_scrollbar_setlargechange(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
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
bool      xtk_looping_setaname(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_looping_setaid(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_looping_setahelp(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool      xtk_looping_setadesc(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_looping_setastatus(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_looping_setaitem(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_looping_setactype(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_looping_setaaccel(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_looping_setakey(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_looping_setalandmark(XtkScene *scene, XtkCtrl control, XtkLandmark value, XtkChangeStamp change);
bool xtk_looping_setalandname(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_looping_setalive(XtkScene *scene, XtkCtrl control, XtkLiveSetting value, XtkChangeStamp change);
bool xtk_looping_setaheading(XtkScene *scene, XtkCtrl control, XtkHeadingLevel value, XtkChangeStamp change);
bool xtk_looping_setaview(XtkScene *scene, XtkCtrl control, XtkAccessView value, XtkChangeStamp change);
bool xtk_looping_setarequired(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_looping_setavalid(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_looping_setaperipheral(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_looping_setadialog(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_looping_setapos(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_looping_setasize(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_looping_setalevel(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_looping_setaculture(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_looping_setalabel(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_looping_setadescribed(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_looping_setaflowsto(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_looping_setaflowsfrom(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_looping_setacontrols(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_looping_setenabled(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_looping_setnitem(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_looping_setsel(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_looping_setitemh(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_looping_setitemw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_looping_setloop(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
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
bool xtk_datepicker_setaname(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_datepicker_setaid(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_datepicker_setahelp(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_datepicker_setadesc(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_datepicker_setastatus(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_datepicker_setaitem(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_datepicker_setactype(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_datepicker_setaaccel(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_datepicker_setakey(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_datepicker_setalandmark(XtkScene *scene, XtkCtrl control, XtkLandmark value, XtkChangeStamp change);
bool xtk_datepicker_setalandname(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
);
bool xtk_datepicker_setalive(XtkScene *scene, XtkCtrl control, XtkLiveSetting value, XtkChangeStamp change);
bool xtk_datepicker_setaheading(XtkScene *scene, XtkCtrl control, XtkHeadingLevel value, XtkChangeStamp change);
bool xtk_datepicker_setaview(XtkScene *scene, XtkCtrl control, XtkAccessView value, XtkChangeStamp change);
bool xtk_datepicker_setarequired(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_datepicker_setavalid(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_datepicker_setaperipheral(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_datepicker_setadialog(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_datepicker_setapos(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_datepicker_setasize(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_datepicker_setalevel(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_datepicker_setaculture(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_datepicker_setalabel(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_datepicker_setadescribed(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
);
bool xtk_datepicker_setaflowsto(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
);
bool xtk_datepicker_setaflowsfrom(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
);
bool xtk_datepicker_setacontrols(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
);
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
bool xtk_timepicker_setaname(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_timepicker_setaid(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_timepicker_setahelp(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_timepicker_setadesc(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_timepicker_setastatus(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_timepicker_setaitem(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_timepicker_setactype(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_timepicker_setaaccel(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_timepicker_setakey(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_timepicker_setalandmark(XtkScene *scene, XtkCtrl control, XtkLandmark value, XtkChangeStamp change);
bool xtk_timepicker_setalandname(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
);
bool xtk_timepicker_setalive(XtkScene *scene, XtkCtrl control, XtkLiveSetting value, XtkChangeStamp change);
bool xtk_timepicker_setaheading(XtkScene *scene, XtkCtrl control, XtkHeadingLevel value, XtkChangeStamp change);
bool xtk_timepicker_setaview(XtkScene *scene, XtkCtrl control, XtkAccessView value, XtkChangeStamp change);
bool xtk_timepicker_setarequired(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_timepicker_setavalid(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_timepicker_setaperipheral(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_timepicker_setadialog(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_timepicker_setapos(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_timepicker_setasize(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_timepicker_setalevel(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_timepicker_setaculture(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_timepicker_setalabel(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_timepicker_setadescribed(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
);
bool xtk_timepicker_setaflowsto(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
);
bool xtk_timepicker_setaflowsfrom(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
);
bool xtk_timepicker_setacontrols(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
);
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
bool xtk_calendar_setaname(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_calendar_setaid(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_calendar_setahelp(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_calendar_setadesc(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_calendar_setastatus(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_calendar_setaitem(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_calendar_setactype(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_calendar_setaaccel(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_calendar_setakey(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_calendar_setalandmark(XtkScene *scene, XtkCtrl control, XtkLandmark value, XtkChangeStamp change);
bool xtk_calendar_setalandname(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_calendar_setalive(XtkScene *scene, XtkCtrl control, XtkLiveSetting value, XtkChangeStamp change);
bool xtk_calendar_setaheading(XtkScene *scene, XtkCtrl control, XtkHeadingLevel value, XtkChangeStamp change);
bool xtk_calendar_setaview(XtkScene *scene, XtkCtrl control, XtkAccessView value, XtkChangeStamp change);
bool xtk_calendar_setarequired(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_calendar_setavalid(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_calendar_setaperipheral(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_calendar_setadialog(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_calendar_setapos(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_calendar_setasize(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_calendar_setalevel(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_calendar_setaculture(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_calendar_setalabel(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_calendar_setadescribed(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
);
bool xtk_calendar_setaflowsto(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_calendar_setaflowsfrom(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
);
bool xtk_calendar_setacontrols(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_calendar_setenabled(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_calendar_setdate(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_calendar_setmode(XtkScene *scene, XtkCtrl control, XtkCalendarMode value, XtkChangeStamp change);
bool xtk_calendar_setmindate(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_calendar_setmaxdate(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_calendar_setfirstday(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
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
bool xtk_colorpicker_setaname(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_colorpicker_setaid(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_colorpicker_setahelp(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_colorpicker_setadesc(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_colorpicker_setastatus(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
);
bool xtk_colorpicker_setaitem(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_colorpicker_setactype(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_colorpicker_setaaccel(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_colorpicker_setakey(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_colorpicker_setalandmark(XtkScene *scene, XtkCtrl control, XtkLandmark value, XtkChangeStamp change);
bool xtk_colorpicker_setalandname(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
);
bool xtk_colorpicker_setalive(XtkScene *scene, XtkCtrl control, XtkLiveSetting value, XtkChangeStamp change);
bool xtk_colorpicker_setaheading(XtkScene *scene, XtkCtrl control, XtkHeadingLevel value, XtkChangeStamp change);
bool xtk_colorpicker_setaview(XtkScene *scene, XtkCtrl control, XtkAccessView value, XtkChangeStamp change);
bool xtk_colorpicker_setarequired(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_colorpicker_setavalid(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_colorpicker_setaperipheral(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_colorpicker_setadialog(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_colorpicker_setapos(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_colorpicker_setasize(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_colorpicker_setalevel(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_colorpicker_setaculture(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_colorpicker_setalabel(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_colorpicker_setadescribed(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
);
bool xtk_colorpicker_setaflowsto(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
);
bool xtk_colorpicker_setaflowsfrom(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
);
bool xtk_colorpicker_setacontrols(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
);
bool      xtk_colorpicker_setenabled(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool      xtk_colorpicker_setcolor(XtkScene *scene, XtkCtrl control, XtkColor value, XtkChangeStamp change);
bool      xtk_colorpicker_setalpha(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool      xtk_colorpicker_setmorebutton(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool      xtk_colorpicker_setspectrum(XtkScene *scene, XtkCtrl control, XtkSpectrum value, XtkChangeStamp change);
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
bool xtk_colheader_setaname(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_colheader_setaid(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_colheader_setahelp(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_colheader_setadesc(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_colheader_setastatus(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_colheader_setaitem(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_colheader_setactype(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_colheader_setaaccel(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_colheader_setakey(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_colheader_setalandmark(XtkScene *scene, XtkCtrl control, XtkLandmark value, XtkChangeStamp change);
bool xtk_colheader_setalandname(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
);
bool xtk_colheader_setalive(XtkScene *scene, XtkCtrl control, XtkLiveSetting value, XtkChangeStamp change);
bool xtk_colheader_setaheading(XtkScene *scene, XtkCtrl control, XtkHeadingLevel value, XtkChangeStamp change);
bool xtk_colheader_setaview(XtkScene *scene, XtkCtrl control, XtkAccessView value, XtkChangeStamp change);
bool xtk_colheader_setarequired(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_colheader_setavalid(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_colheader_setaperipheral(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_colheader_setadialog(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_colheader_setapos(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_colheader_setasize(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_colheader_setalevel(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_colheader_setaculture(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_colheader_setalabel(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_colheader_setadescribed(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
);
bool xtk_colheader_setaflowsto(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_colheader_setaflowsfrom(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
);
bool xtk_colheader_setacontrols(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
);
bool xtk_colitem_setw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_colitem_setminw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_colitem_setmaxw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_colitem_settext(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_colitem_settip(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_colitem_setaname(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_colitem_setaid(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_colitem_setahelp(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_colitem_setadesc(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_colitem_setastatus(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_colitem_setaitem(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_colitem_setactype(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_colitem_setaaccel(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_colitem_setakey(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_colitem_setalandmark(XtkScene *scene, XtkCtrl control, XtkLandmark value, XtkChangeStamp change);
bool xtk_colitem_setalandname(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_colitem_setalive(XtkScene *scene, XtkCtrl control, XtkLiveSetting value, XtkChangeStamp change);
bool xtk_colitem_setaheading(XtkScene *scene, XtkCtrl control, XtkHeadingLevel value, XtkChangeStamp change);
bool xtk_colitem_setaview(XtkScene *scene, XtkCtrl control, XtkAccessView value, XtkChangeStamp change);
bool xtk_colitem_setarequired(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_colitem_setavalid(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_colitem_setaperipheral(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_colitem_setadialog(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_colitem_setapos(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_colitem_setasize(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_colitem_setalevel(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_colitem_setaculture(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_colitem_setalabel(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_colitem_setadescribed(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_colitem_setaflowsto(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_colitem_setaflowsfrom(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_colitem_setacontrols(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_colitem_setalign(XtkScene *scene, XtkCtrl control, XtkTextAlign value, XtkChangeStamp change);
bool xtk_colitem_setenabled(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_colitem_setresizable(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_colitem_setsort(XtkScene *scene, XtkCtrl control, XtkSortDirection value, XtkChangeStamp change);
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
bool xtk_commandbar_setaname(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_commandbar_setaid(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_commandbar_setahelp(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_commandbar_setadesc(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_commandbar_setastatus(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_commandbar_setaitem(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_commandbar_setactype(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_commandbar_setaaccel(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_commandbar_setakey(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_commandbar_setalandmark(XtkScene *scene, XtkCtrl control, XtkLandmark value, XtkChangeStamp change);
bool xtk_commandbar_setalandname(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
);
bool xtk_commandbar_setalive(XtkScene *scene, XtkCtrl control, XtkLiveSetting value, XtkChangeStamp change);
bool xtk_commandbar_setaheading(XtkScene *scene, XtkCtrl control, XtkHeadingLevel value, XtkChangeStamp change);
bool xtk_commandbar_setaview(XtkScene *scene, XtkCtrl control, XtkAccessView value, XtkChangeStamp change);
bool xtk_commandbar_setarequired(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_commandbar_setavalid(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_commandbar_setaperipheral(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_commandbar_setadialog(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_commandbar_setapos(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_commandbar_setasize(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_commandbar_setalevel(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_commandbar_setaculture(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_commandbar_setalabel(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_commandbar_setadescribed(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
);
bool xtk_commandbar_setaflowsto(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
);
bool xtk_commandbar_setaflowsfrom(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
);
bool xtk_commandbar_setacontrols(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
);
bool      xtk_commandbar_setenabled(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool      xtk_commandbar_setopen(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool      xtk_commandbar_setsticky(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool      xtk_commandbar_setmode(XtkScene *scene, XtkCtrl control, XtkAppBarMode value, XtkChangeStamp change);
bool      xtk_commandbar_setlabels(XtkScene *scene, XtkCtrl control, XtkLabelPosition value, XtkChangeStamp change);
bool      xtk_commandbar_setmore(XtkScene *scene, XtkCtrl control, XtkOverflowButton value, XtkChangeStamp change);
bool      xtk_commandbar_setdynamic(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
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
bool xtk_appbarbutton_setaname(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_appbarbutton_setaid(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_appbarbutton_setahelp(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_appbarbutton_setadesc(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_appbarbutton_setastatus(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
);
bool xtk_appbarbutton_setaitem(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_appbarbutton_setactype(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
);
bool xtk_appbarbutton_setaaccel(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
);
bool xtk_appbarbutton_setakey(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_appbarbutton_setalandmark(XtkScene *scene, XtkCtrl control, XtkLandmark value, XtkChangeStamp change);
bool xtk_appbarbutton_setalandname(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
);
bool xtk_appbarbutton_setalive(XtkScene *scene, XtkCtrl control, XtkLiveSetting value, XtkChangeStamp change);
bool xtk_appbarbutton_setaheading(XtkScene *scene, XtkCtrl control, XtkHeadingLevel value, XtkChangeStamp change);
bool xtk_appbarbutton_setaview(XtkScene *scene, XtkCtrl control, XtkAccessView value, XtkChangeStamp change);
bool xtk_appbarbutton_setarequired(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_appbarbutton_setavalid(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_appbarbutton_setaperipheral(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_appbarbutton_setadialog(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_appbarbutton_setapos(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_appbarbutton_setasize(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_appbarbutton_setalevel(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_appbarbutton_setaculture(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_appbarbutton_setalabel(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
);
bool xtk_appbarbutton_setadescribed(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
);
bool xtk_appbarbutton_setaflowsto(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
);
bool xtk_appbarbutton_setaflowsfrom(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
);
bool xtk_appbarbutton_setacontrols(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
);
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
bool xtk_appbartoggle_setaname(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_appbartoggle_setaid(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_appbartoggle_setahelp(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_appbartoggle_setadesc(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_appbartoggle_setastatus(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
);
bool xtk_appbartoggle_setaitem(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_appbartoggle_setactype(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
);
bool xtk_appbartoggle_setaaccel(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
);
bool xtk_appbartoggle_setakey(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_appbartoggle_setalandmark(XtkScene *scene, XtkCtrl control, XtkLandmark value, XtkChangeStamp change);
bool xtk_appbartoggle_setalandname(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
);
bool xtk_appbartoggle_setalive(XtkScene *scene, XtkCtrl control, XtkLiveSetting value, XtkChangeStamp change);
bool xtk_appbartoggle_setaheading(XtkScene *scene, XtkCtrl control, XtkHeadingLevel value, XtkChangeStamp change);
bool xtk_appbartoggle_setaview(XtkScene *scene, XtkCtrl control, XtkAccessView value, XtkChangeStamp change);
bool xtk_appbartoggle_setarequired(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_appbartoggle_setavalid(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_appbartoggle_setaperipheral(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_appbartoggle_setadialog(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_appbartoggle_setapos(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_appbartoggle_setasize(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_appbartoggle_setalevel(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_appbartoggle_setaculture(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_appbartoggle_setalabel(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
);
bool xtk_appbartoggle_setadescribed(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
);
bool xtk_appbartoggle_setaflowsto(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
);
bool xtk_appbartoggle_setaflowsfrom(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
);
bool xtk_appbartoggle_setacontrols(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
);
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
bool xtk_appbarsep_setaname(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_appbarsep_setaid(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_appbarsep_setahelp(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_appbarsep_setadesc(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_appbarsep_setastatus(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_appbarsep_setaitem(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_appbarsep_setactype(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_appbarsep_setaaccel(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_appbarsep_setakey(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_appbarsep_setalandmark(XtkScene *scene, XtkCtrl control, XtkLandmark value, XtkChangeStamp change);
bool xtk_appbarsep_setalandname(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
);
bool xtk_appbarsep_setalive(XtkScene *scene, XtkCtrl control, XtkLiveSetting value, XtkChangeStamp change);
bool xtk_appbarsep_setaheading(XtkScene *scene, XtkCtrl control, XtkHeadingLevel value, XtkChangeStamp change);
bool xtk_appbarsep_setaview(XtkScene *scene, XtkCtrl control, XtkAccessView value, XtkChangeStamp change);
bool xtk_appbarsep_setarequired(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_appbarsep_setavalid(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_appbarsep_setaperipheral(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_appbarsep_setadialog(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_appbarsep_setapos(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_appbarsep_setasize(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_appbarsep_setalevel(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_appbarsep_setaculture(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_appbarsep_setalabel(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_appbarsep_setadescribed(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
);
bool xtk_appbarsep_setaflowsto(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_appbarsep_setaflowsfrom(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
);
bool xtk_appbarsep_setacontrols(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
);
bool xtk_appbarsep_setsecondary(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_appbarsep_setorder(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_groupheader_setw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_groupheader_seth(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_groupheader_setgrow(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_groupheader_setshrink(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_groupheader_setself(XtkScene *scene, XtkCtrl control, XentFlexAlign value, XtkChangeStamp change);
bool xtk_groupheader_setml(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_groupheader_setmt(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_groupheader_setmr(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_groupheader_setmb(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_groupheader_settip(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_groupheader_setaname(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_groupheader_setaid(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_groupheader_setahelp(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_groupheader_setadesc(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_groupheader_setastatus(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
);
bool xtk_groupheader_setaitem(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_groupheader_setactype(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_groupheader_setaaccel(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_groupheader_setakey(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_groupheader_setalandmark(XtkScene *scene, XtkCtrl control, XtkLandmark value, XtkChangeStamp change);
bool xtk_groupheader_setalandname(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
);
bool xtk_groupheader_setalive(XtkScene *scene, XtkCtrl control, XtkLiveSetting value, XtkChangeStamp change);
bool xtk_groupheader_setaheading(XtkScene *scene, XtkCtrl control, XtkHeadingLevel value, XtkChangeStamp change);
bool xtk_groupheader_setaview(XtkScene *scene, XtkCtrl control, XtkAccessView value, XtkChangeStamp change);
bool xtk_groupheader_setarequired(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_groupheader_setavalid(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_groupheader_setaperipheral(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_groupheader_setadialog(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_groupheader_setapos(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_groupheader_setasize(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_groupheader_setalevel(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_groupheader_setaculture(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);
bool xtk_groupheader_setalabel(XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change);
bool xtk_groupheader_setadescribed(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
);
bool xtk_groupheader_setaflowsto(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
);
bool xtk_groupheader_setaflowsfrom(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
);
bool xtk_groupheader_setacontrols(
  XtkScene *scene, XtkCtrl control, char const *data, uint32_t len, XtkChangeStamp change
);
bool xtk_navslot_setw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_navslot_seth(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_navslot_setgrow(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_navslot_setshrink(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_navslot_setself(XtkScene *scene, XtkCtrl control, XentFlexAlign value, XtkChangeStamp change);
bool xtk_navslot_setslot(XtkScene *scene, XtkCtrl control, XtkNavSlot value, XtkChangeStamp change);
bool xtk_frame_setw(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_frame_seth(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_frame_setgrow(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_frame_setshrink(XtkScene *scene, XtkCtrl control, float value, XtkChangeStamp change);
bool xtk_frame_setself(XtkScene *scene, XtkCtrl control, XentFlexAlign value, XtkChangeStamp change);
bool xtk_frame_settransition(XtkScene *scene, XtkCtrl control, XtkNavTransitionKind value, XtkChangeStamp change);
bool xtk_frame_setis_back(XtkScene *scene, XtkCtrl control, bool value, XtkChangeStamp change);
bool xtk_frame_setpage_key(XtkScene *scene, XtkCtrl control, int32_t value, XtkChangeStamp change);

#endif
