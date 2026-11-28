#include "xtk_controls_internal.h"

#include <assert.h>
#include <stddef.h>
#include <string.h>

static_assert(XTK_PROP_STANDARD_COUNT <= UINT16_MAX, "property id fits uint16_t");
static_assert(
  XTK_VALUE_BOOL < XTK_VALUE_I32
    && XTK_VALUE_I32 < XTK_VALUE_F32
    && XTK_VALUE_F32 < XTK_VALUE_F64
    && XTK_VALUE_F64 < XTK_VALUE_ENUM,
  "numeric value kinds contiguous"
);
static_assert(sizeof(XentDirection) == sizeof(uint32_t), "enum size fits uint32_t");
static_assert(sizeof(XentFlexAlign) == sizeof(uint32_t), "enum size fits uint32_t");
static_assert(sizeof(XentFlexJustify) == sizeof(uint32_t), "enum size fits uint32_t");
static_assert(sizeof(XentFlexWrap) == sizeof(uint32_t), "enum size fits uint32_t");
static_assert(sizeof(XtkAccessView) == sizeof(uint32_t), "enum size fits uint32_t");
static_assert(sizeof(XtkAppBarMode) == sizeof(uint32_t), "enum size fits uint32_t");
static_assert(sizeof(XtkBadgeMode) == sizeof(uint32_t), "enum size fits uint32_t");
static_assert(sizeof(XtkButtonStyle) == sizeof(uint32_t), "enum size fits uint32_t");
static_assert(sizeof(XtkCalendarMode) == sizeof(uint32_t), "enum size fits uint32_t");
static_assert(sizeof(XtkClock) == sizeof(uint32_t), "enum size fits uint32_t");
static_assert(sizeof(XtkConnectedKind) == sizeof(uint32_t), "enum size fits uint32_t");
static_assert(sizeof(XtkDialogButton) == sizeof(uint32_t), "enum size fits uint32_t");
static_assert(sizeof(XtkDropOperation) == sizeof(uint32_t), "enum size fits uint32_t");
static_assert(sizeof(XtkElementLabel) == sizeof(uint32_t), "enum size fits uint32_t");
static_assert(sizeof(XtkFontWeight) == sizeof(uint32_t), "enum size fits uint32_t");
static_assert(sizeof(XtkHeadingLevel) == sizeof(uint32_t), "enum size fits uint32_t");
static_assert(sizeof(XtkImageStretch) == sizeof(uint32_t), "enum size fits uint32_t");
static_assert(sizeof(XtkInfoBarSeverity) == sizeof(uint32_t), "enum size fits uint32_t");
static_assert(sizeof(XtkLabelPosition) == sizeof(uint32_t), "enum size fits uint32_t");
static_assert(sizeof(XtkLandmark) == sizeof(uint32_t), "enum size fits uint32_t");
static_assert(sizeof(XtkListSelMode) == sizeof(uint32_t), "enum size fits uint32_t");
static_assert(sizeof(XtkLiveSetting) == sizeof(uint32_t), "enum size fits uint32_t");
static_assert(sizeof(XtkNavBackButton) == sizeof(uint32_t), "enum size fits uint32_t");
static_assert(sizeof(XtkNavKind) == sizeof(uint32_t), "enum size fits uint32_t");
static_assert(sizeof(XtkNavPaneMode) == sizeof(uint32_t), "enum size fits uint32_t");
static_assert(sizeof(XtkNavSlot) == sizeof(uint32_t), "enum size fits uint32_t");
static_assert(sizeof(XtkNavTransitionKind) == sizeof(uint32_t), "enum size fits uint32_t");
static_assert(sizeof(XtkOverflowButton) == sizeof(uint32_t), "enum size fits uint32_t");
static_assert(sizeof(XtkPagerButtonVis) == sizeof(uint32_t), "enum size fits uint32_t");
static_assert(sizeof(XtkPagerDisplayMode) == sizeof(uint32_t), "enum size fits uint32_t");
static_assert(sizeof(XtkPipsNavVis) == sizeof(uint32_t), "enum size fits uint32_t");
static_assert(sizeof(XtkProgressState) == sizeof(uint32_t), "enum size fits uint32_t");
static_assert(sizeof(XtkPullDirection) == sizeof(uint32_t), "enum size fits uint32_t");
static_assert(sizeof(XtkScrollBarIndicator) == sizeof(uint32_t), "enum size fits uint32_t");
static_assert(sizeof(XtkSliderSnap) == sizeof(uint32_t), "enum size fits uint32_t");
static_assert(sizeof(XtkSortDirection) == sizeof(uint32_t), "enum size fits uint32_t");
static_assert(sizeof(XtkSpectrum) == sizeof(uint32_t), "enum size fits uint32_t");
static_assert(sizeof(XtkSplitViewDisplayMode) == sizeof(uint32_t), "enum size fits uint32_t");
static_assert(sizeof(XtkSplitViewPanePlacement) == sizeof(uint32_t), "enum size fits uint32_t");
static_assert(sizeof(XtkStackDirection) == sizeof(uint32_t), "enum size fits uint32_t");
static_assert(sizeof(XtkTeachingTipPlacement) == sizeof(uint32_t), "enum size fits uint32_t");
static_assert(sizeof(XtkTeachingTipTail) == sizeof(uint32_t), "enum size fits uint32_t");
static_assert(sizeof(XtkTextAlign) == sizeof(uint32_t), "enum size fits uint32_t");
static_assert(sizeof(XtkTextTrim) == sizeof(uint32_t), "enum size fits uint32_t");
static_assert(sizeof(XtkThemeTransitionKind) == sizeof(uint32_t), "enum size fits uint32_t");
static_assert(sizeof(XtkTickPlacement) == sizeof(uint32_t), "enum size fits uint32_t");

static XtkCtrlField const k_a11y_fields [28] = {
  {( uint16_t ) (offsetof(XtkLayoutProps, tip) - offsetof(XtkLayoutProps, tip)),
   ( uint16_t ) (offsetof(XtkLayoutProps, tip_len) - offsetof(XtkLayoutProps, tip)), XTK_PROP_TOOLTIP, 0u,
   XTK_VALUE_STRING},
  {( uint16_t ) (offsetof(XtkLayoutProps, aname) - offsetof(XtkLayoutProps, tip)),
   ( uint16_t ) (offsetof(XtkLayoutProps, aname_len) - offsetof(XtkLayoutProps, tip)), XTK_PROP_A11Y_NAME, 1u,
   XTK_VALUE_STRING},
  {( uint16_t ) (offsetof(XtkLayoutProps, aid) - offsetof(XtkLayoutProps, tip)),
   ( uint16_t ) (offsetof(XtkLayoutProps, aid_len) - offsetof(XtkLayoutProps, tip)), XTK_PROP_A11Y_ID, 2u,
   XTK_VALUE_STRING},
  {( uint16_t ) (offsetof(XtkLayoutProps, ahelp) - offsetof(XtkLayoutProps, tip)),
   ( uint16_t ) (offsetof(XtkLayoutProps, ahelp_len) - offsetof(XtkLayoutProps, tip)), XTK_PROP_A11Y_HELP, 3u,
   XTK_VALUE_STRING},
  {( uint16_t ) (offsetof(XtkLayoutProps, adesc) - offsetof(XtkLayoutProps, tip)),
   ( uint16_t ) (offsetof(XtkLayoutProps, adesc_len) - offsetof(XtkLayoutProps, tip)), XTK_PROP_A11Y_DESCRIPTION, 4u,
   XTK_VALUE_STRING},
  {( uint16_t ) (offsetof(XtkLayoutProps, astatus) - offsetof(XtkLayoutProps, tip)),
   ( uint16_t ) (offsetof(XtkLayoutProps, astatus_len) - offsetof(XtkLayoutProps, tip)), XTK_PROP_A11Y_ITEM_STATUS, 5u,
   XTK_VALUE_STRING},
  {( uint16_t ) (offsetof(XtkLayoutProps, aitem) - offsetof(XtkLayoutProps, tip)),
   ( uint16_t ) (offsetof(XtkLayoutProps, aitem_len) - offsetof(XtkLayoutProps, tip)), XTK_PROP_A11Y_ITEM_TYPE, 6u,
   XTK_VALUE_STRING},
  {( uint16_t ) (offsetof(XtkLayoutProps, actype) - offsetof(XtkLayoutProps, tip)),
   ( uint16_t ) (offsetof(XtkLayoutProps, actype_len) - offsetof(XtkLayoutProps, tip)), XTK_PROP_A11Y_CONTROL_TYPE, 7u,
   XTK_VALUE_STRING},
  {( uint16_t ) (offsetof(XtkLayoutProps, aaccel) - offsetof(XtkLayoutProps, tip)),
   ( uint16_t ) (offsetof(XtkLayoutProps, aaccel_len) - offsetof(XtkLayoutProps, tip)), XTK_PROP_A11Y_ACCELERATOR, 8u,
   XTK_VALUE_STRING},
  {( uint16_t ) (offsetof(XtkLayoutProps, akey) - offsetof(XtkLayoutProps, tip)),
   ( uint16_t ) (offsetof(XtkLayoutProps, akey_len) - offsetof(XtkLayoutProps, tip)), XTK_PROP_A11Y_ACCESS_KEY, 9u,
   XTK_VALUE_STRING},
  {( uint16_t ) (offsetof(XtkLayoutProps, alandmark) - offsetof(XtkLayoutProps, tip)), 0u, XTK_PROP_A11Y_LANDMARK, 10u,
   XTK_VALUE_ENUM},
  {( uint16_t ) (offsetof(XtkLayoutProps, alandname) - offsetof(XtkLayoutProps, tip)),
   ( uint16_t ) (offsetof(XtkLayoutProps, alandname_len) - offsetof(XtkLayoutProps, tip)), XTK_PROP_A11Y_LANDMARK_NAME,
   11u, XTK_VALUE_STRING},
  {( uint16_t ) (offsetof(XtkLayoutProps, alive) - offsetof(XtkLayoutProps, tip)), 0u, XTK_PROP_A11Y_LIVE, 12u,
   XTK_VALUE_ENUM},
  {( uint16_t ) (offsetof(XtkLayoutProps, aheading) - offsetof(XtkLayoutProps, tip)), 0u, XTK_PROP_A11Y_HEADING, 13u,
   XTK_VALUE_ENUM},
  {( uint16_t ) (offsetof(XtkLayoutProps, aview) - offsetof(XtkLayoutProps, tip)), 0u, XTK_PROP_A11Y_VIEW, 14u,
   XTK_VALUE_ENUM},
  {( uint16_t ) (offsetof(XtkLayoutProps, arequired) - offsetof(XtkLayoutProps, tip)), 0u, XTK_PROP_A11Y_REQUIRED, 15u,
   XTK_VALUE_BOOL},
  {( uint16_t ) (offsetof(XtkLayoutProps, avalid) - offsetof(XtkLayoutProps, tip)), 0u, XTK_PROP_A11Y_DATA_VALID, 16u,
   XTK_VALUE_BOOL},
  {( uint16_t ) (offsetof(XtkLayoutProps, aperipheral) - offsetof(XtkLayoutProps, tip)), 0u, XTK_PROP_A11Y_PERIPHERAL,
   17u, XTK_VALUE_BOOL},
  {( uint16_t ) (offsetof(XtkLayoutProps, adialog) - offsetof(XtkLayoutProps, tip)), 0u, XTK_PROP_A11Y_DIALOG, 18u,
   XTK_VALUE_BOOL},
  {( uint16_t ) (offsetof(XtkLayoutProps, apos) - offsetof(XtkLayoutProps, tip)), 0u, XTK_PROP_A11Y_POSITION, 19u,
   XTK_VALUE_I32},
  {( uint16_t ) (offsetof(XtkLayoutProps, asize) - offsetof(XtkLayoutProps, tip)), 0u, XTK_PROP_A11Y_SIZE, 20u,
   XTK_VALUE_I32},
  {( uint16_t ) (offsetof(XtkLayoutProps, alevel) - offsetof(XtkLayoutProps, tip)), 0u, XTK_PROP_A11Y_LEVEL, 21u,
   XTK_VALUE_I32},
  {( uint16_t ) (offsetof(XtkLayoutProps, aculture) - offsetof(XtkLayoutProps, tip)), 0u, XTK_PROP_A11Y_CULTURE, 22u,
   XTK_VALUE_I32},
  {( uint16_t ) (offsetof(XtkLayoutProps, alabel) - offsetof(XtkLayoutProps, tip)),
   ( uint16_t ) (offsetof(XtkLayoutProps, alabel_len) - offsetof(XtkLayoutProps, tip)), XTK_PROP_A11Y_LABELED_BY, 23u,
   XTK_VALUE_STRING},
  {( uint16_t ) (offsetof(XtkLayoutProps, adescribed) - offsetof(XtkLayoutProps, tip)),
   ( uint16_t ) (offsetof(XtkLayoutProps, adescribed_len) - offsetof(XtkLayoutProps, tip)), XTK_PROP_A11Y_DESCRIBED_BY,
   24u, XTK_VALUE_STRING},
  {( uint16_t ) (offsetof(XtkLayoutProps, aflowsto) - offsetof(XtkLayoutProps, tip)),
   ( uint16_t ) (offsetof(XtkLayoutProps, aflowsto_len) - offsetof(XtkLayoutProps, tip)), XTK_PROP_A11Y_FLOWS_TO, 25u,
   XTK_VALUE_STRING},
  {( uint16_t ) (offsetof(XtkLayoutProps, aflowsfrom) - offsetof(XtkLayoutProps, tip)),
   ( uint16_t ) (offsetof(XtkLayoutProps, aflowsfrom_len) - offsetof(XtkLayoutProps, tip)), XTK_PROP_A11Y_FLOWS_FROM,
   26u, XTK_VALUE_STRING},
  {( uint16_t ) (offsetof(XtkLayoutProps, acontrols) - offsetof(XtkLayoutProps, tip)),
   ( uint16_t ) (offsetof(XtkLayoutProps, acontrols_len) - offsetof(XtkLayoutProps, tip)), XTK_PROP_A11Y_CONTROLLED,
   27u, XTK_VALUE_STRING},
};

uint32_t xtk_controls_text_len(char const *text, uint32_t len) {
	if (!text) return 0u;
	return len ? len : ( uint32_t ) strlen(text);
}

static void pack_num_value(XtkValue *v, uint8_t const *p, uint8_t kind) {
	if (kind == XTK_VALUE_BOOL) {
		v->kind = XTK_VALUE_BOOL;
		memcpy(&v->u.b, p, sizeof(v->u.b));
		return;
	}
	if (kind == XTK_VALUE_I32) {
		v->kind = XTK_VALUE_I32;
		memcpy(&v->u.i32, p, sizeof(v->u.i32));
		return;
	}
	if (kind == XTK_VALUE_F32) {
		v->kind = XTK_VALUE_F32;
		memcpy(&v->u.f32, p, sizeof(v->u.f32));
		return;
	}
	v->kind = XTK_VALUE_F64;
	memcpy(&v->u.f64, p, sizeof(v->u.f64));
}

static void pack_other_value(XtkValue *v, uint8_t const *base, XtkCtrlField const *f, uint16_t delta) {
	uint8_t const *p = base + delta + f->offset;
	if (f->kind == XTK_VALUE_ENUM) {
		v->kind = XTK_VALUE_ENUM;
		memcpy(&v->u.u32, p, sizeof(v->u.u32));
		return;
	}
	if (f->kind == XTK_VALUE_COLOR) {
		v->kind = XTK_VALUE_COLOR;
		memcpy(&v->u.color, p, sizeof(v->u.color));
		return;
	}
	if (f->kind == XTK_VALUE_RESOURCE) {
		v->kind = XTK_VALUE_RESOURCE;
		memcpy(&v->u.resource, p, sizeof(v->u.resource));
		return;
	}
	char const *text = NULL;
	uint32_t    len  = 0u;
	memcpy(&text, p, sizeof(text));
	memcpy(&len, base + delta + f->len_offset, sizeof(len));
	v->kind          = XTK_VALUE_STRING;
	v->u.string.data = ( char * ) text;
	v->u.string.len  = xtk_controls_text_len(text, len);
}

static void pack_slice(
  XtkPropPatch *patches, uint32_t *count, uint8_t const *base, uint64_t set, XtkChangeStamp change,
  XtkCtrlField const *fields, uint32_t start, uint32_t end, uint16_t delta, uint8_t bit_base
) {
	for (uint32_t i = start; i < end; i++) {
		XtkCtrlField const *f = &fields [i];
		if (!((set >> (bit_base + f->bit)) & 1ull)) continue;
		XtkPropPatch *patch = &patches [(*count)++];
		patch->id           = f->id;
		patch->change       = change;
		if (f->kind <= XTK_VALUE_F64) pack_num_value(&patch->value, base + delta + f->offset, f->kind);
		else pack_other_value(&patch->value, base, f, delta);
	}
}

XtkLocalId
xtk_controls_create(XtkTxn *txn, XtkCtrlId type, XtkNodeRef parent, void const *props, XtkCtrlPack const *pack) {
	if (!props || !pack) return xtk_txn_create(txn, type, parent, xtk_ref_none(), NULL, 0u);
	uint8_t const *base = ( uint8_t const * ) props;
	uint64_t       set  = 0u;
	memcpy(&set, base, sizeof(set));
	if (set == 0u) return xtk_txn_create(txn, type, parent, xtk_ref_none(), NULL, 0u);

	XtkChangeStamp change = {0};
	memcpy(&change, base + offsetof(XtkLayoutProps, stamp), sizeof(change));

	XtkPropPatch patches [64];
	uint32_t     count = 0u;
	if (pack->pre_count) pack_slice(patches, &count, base, set, change, pack->fields, 0u, pack->pre_count, 0u, 0u);
	if (pack->has_a11y)
		pack_slice(patches, &count, base, set, change, k_a11y_fields, 0u, 28u, pack->a11y_offset, pack->a11y_bit);
	if (pack->field_count > pack->pre_count)
		pack_slice(patches, &count, base, set, change, pack->fields, pack->pre_count, pack->field_count, 0u, 0u);
	return xtk_txn_create(txn, type, parent, xtk_ref_none(), patches, count);
}

static_assert(
  offsetof(XtkContainerProps, set) == 0u && offsetof(XtkContainerProps, stamp) == offsetof(XtkLayoutProps, stamp),
  "header prefix"
);
static_assert(
  offsetof(XtkContainerProps, acontrols_len) - offsetof(XtkContainerProps, tip)
    == offsetof(XtkLayoutProps, acontrols_len) - offsetof(XtkLayoutProps, tip),
  "a11y span"
);
static XtkCtrlField const k_fields_container [25] = {
  {( uint16_t ) offsetof(XtkContainerProps, w), 0u, XTK_PROP_WIDTH, 0u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkContainerProps, h), 0u, XTK_PROP_HEIGHT, 1u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkContainerProps, grow), 0u, XTK_PROP_GROW, 2u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkContainerProps, shrink), 0u, XTK_PROP_SHRINK, 3u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkContainerProps, self), 0u, XTK_PROP_ALIGN_SELF, 4u, XTK_VALUE_ENUM},
  {( uint16_t ) offsetof(XtkContainerProps, ml), 0u, XTK_PROP_MARGIN_LEFT, 5u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkContainerProps, mt), 0u, XTK_PROP_MARGIN_TOP, 6u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkContainerProps, mr), 0u, XTK_PROP_MARGIN_RIGHT, 7u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkContainerProps, mb), 0u, XTK_PROP_MARGIN_BOTTOM, 8u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkContainerProps, dir), 0u, XTK_PROP_ORIENTATION, 37u, XTK_VALUE_ENUM},
  {( uint16_t ) offsetof(XtkContainerProps, items), 0u, XTK_PROP_ALIGN_ITEMS, 38u, XTK_VALUE_ENUM},
  {( uint16_t ) offsetof(XtkContainerProps, justify), 0u, XTK_PROP_JUSTIFY_CONTENT, 39u, XTK_VALUE_ENUM},
  {( uint16_t ) offsetof(XtkContainerProps, gap), 0u, XTK_PROP_GAP, 40u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkContainerProps, pl), 0u, XTK_PROP_PADDING_LEFT, 41u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkContainerProps, pt), 0u, XTK_PROP_PADDING_TOP, 42u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkContainerProps, pr), 0u, XTK_PROP_PADDING_RIGHT, 43u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkContainerProps, pb), 0u, XTK_PROP_PADDING_BOTTOM, 44u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkContainerProps, fill), 0u, XTK_PROP_FILL, 45u, XTK_VALUE_BOOL},
  {( uint16_t ) offsetof(XtkContainerProps, fitw), 0u, XTK_PROP_FIT_WIDTH, 46u, XTK_VALUE_BOOL},
  {( uint16_t ) offsetof(XtkContainerProps, fith), 0u, XTK_PROP_FIT_HEIGHT, 47u, XTK_VALUE_BOOL},
  {( uint16_t ) offsetof(XtkContainerProps, wrap), 0u, XTK_PROP_WRAP, 48u, XTK_VALUE_ENUM},
  {( uint16_t ) offsetof(XtkContainerProps, drop), 0u, XTK_PROP_DROP_OPERATION, 49u, XTK_VALUE_ENUM},
  {( uint16_t ) offsetof(XtkContainerProps, dragtext), ( uint16_t ) offsetof(XtkContainerProps, dragtext_len),
   XTK_PROP_DRAG_TEXT, 50u, XTK_VALUE_STRING},
  {( uint16_t ) offsetof(XtkContainerProps, dragfiles), ( uint16_t ) offsetof(XtkContainerProps, dragfiles_len),
   XTK_PROP_DRAG_FILES, 51u, XTK_VALUE_STRING},
  {( uint16_t ) offsetof(XtkContainerProps, flow), 0u, XTK_PROP_FLOW_DIRECTION, 52u, XTK_VALUE_ENUM},
};
XtkCtrlPack const xtk_pack_container = {
  .fields      = k_fields_container,
  .a11y_offset = ( uint16_t ) offsetof(XtkContainerProps, tip),
  .pre_count   = 9u,
  .field_count = 25u,
  .a11y_bit    = 9u,
  .has_a11y    = 1u,
};
static_assert(
  offsetof(XtkTextProps, set) == 0u && offsetof(XtkTextProps, stamp) == offsetof(XtkLayoutProps, stamp), "header prefix"
);
static_assert(
  offsetof(XtkTextProps, acontrols_len) - offsetof(XtkTextProps, tip)
    == offsetof(XtkLayoutProps, acontrols_len) - offsetof(XtkLayoutProps, tip),
  "a11y span"
);
static XtkCtrlField const k_fields_text [17] = {
  {( uint16_t ) offsetof(XtkTextProps, w), 0u, XTK_PROP_WIDTH, 0u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkTextProps, h), 0u, XTK_PROP_HEIGHT, 1u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkTextProps, grow), 0u, XTK_PROP_GROW, 2u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkTextProps, self), 0u, XTK_PROP_ALIGN_SELF, 3u, XTK_VALUE_ENUM},
  {( uint16_t ) offsetof(XtkTextProps, ml), 0u, XTK_PROP_MARGIN_LEFT, 4u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkTextProps, mt), 0u, XTK_PROP_MARGIN_TOP, 5u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkTextProps, mr), 0u, XTK_PROP_MARGIN_RIGHT, 6u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkTextProps, mb), 0u, XTK_PROP_MARGIN_BOTTOM, 7u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkTextProps, text), ( uint16_t ) offsetof(XtkTextProps, text_len), XTK_PROP_TEXT, 8u,
   XTK_VALUE_STRING},
  {( uint16_t ) offsetof(XtkTextProps, fontsize), 0u, XTK_PROP_FONT_SIZE, 37u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkTextProps, fontweight), 0u, XTK_PROP_FONT_WEIGHT, 38u, XTK_VALUE_ENUM},
  {( uint16_t ) offsetof(XtkTextProps, textalign), 0u, XTK_PROP_TEXT_ALIGN, 39u, XTK_VALUE_ENUM},
  {( uint16_t ) offsetof(XtkTextProps, fg), 0u, XTK_PROP_FOREGROUND, 40u, XTK_VALUE_COLOR},
  {( uint16_t ) offsetof(XtkTextProps, maxlines), 0u, XTK_PROP_MAX_LINES, 41u, XTK_VALUE_I32},
  {( uint16_t ) offsetof(XtkTextProps, trim), 0u, XTK_PROP_TEXT_TRIM, 42u, XTK_VALUE_ENUM},
  {( uint16_t ) offsetof(XtkTextProps, textwrap), 0u, XTK_PROP_TEXT_WRAP, 43u, XTK_VALUE_BOOL},
  {( uint16_t ) offsetof(XtkTextProps, selectable), 0u, XTK_PROP_SELECTABLE, 44u, XTK_VALUE_BOOL},
};
XtkCtrlPack const xtk_pack_text = {
  .fields      = k_fields_text,
  .a11y_offset = ( uint16_t ) offsetof(XtkTextProps, tip),
  .pre_count   = 9u,
  .field_count = 17u,
  .a11y_bit    = 9u,
  .has_a11y    = 1u,
};
static_assert(
  offsetof(XtkButtonProps, set) == 0u && offsetof(XtkButtonProps, stamp) == offsetof(XtkLayoutProps, stamp),
  "header prefix"
);
static_assert(
  offsetof(XtkButtonProps, acontrols_len) - offsetof(XtkButtonProps, tip)
    == offsetof(XtkLayoutProps, acontrols_len) - offsetof(XtkLayoutProps, tip),
  "a11y span"
);
static XtkCtrlField const k_fields_button [12] = {
  {( uint16_t ) offsetof(XtkButtonProps, w), 0u, XTK_PROP_WIDTH, 0u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkButtonProps, h), 0u, XTK_PROP_HEIGHT, 1u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkButtonProps, grow), 0u, XTK_PROP_GROW, 2u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkButtonProps, self), 0u, XTK_PROP_ALIGN_SELF, 3u, XTK_VALUE_ENUM},
  {( uint16_t ) offsetof(XtkButtonProps, ml), 0u, XTK_PROP_MARGIN_LEFT, 4u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkButtonProps, mt), 0u, XTK_PROP_MARGIN_TOP, 5u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkButtonProps, mr), 0u, XTK_PROP_MARGIN_RIGHT, 6u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkButtonProps, mb), 0u, XTK_PROP_MARGIN_BOTTOM, 7u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkButtonProps, text), ( uint16_t ) offsetof(XtkButtonProps, text_len), XTK_PROP_TEXT, 8u,
   XTK_VALUE_STRING},
  {( uint16_t ) offsetof(XtkButtonProps, enabled), 0u, XTK_PROP_ENABLED, 37u, XTK_VALUE_BOOL},
  {( uint16_t ) offsetof(XtkButtonProps, icon), ( uint16_t ) offsetof(XtkButtonProps, icon_len), XTK_PROP_ICON, 38u,
   XTK_VALUE_STRING},
  {( uint16_t ) offsetof(XtkButtonProps, style), 0u, XTK_PROP_BUTTON_STYLE, 39u, XTK_VALUE_ENUM},
};
XtkCtrlPack const xtk_pack_button = {
  .fields      = k_fields_button,
  .a11y_offset = ( uint16_t ) offsetof(XtkButtonProps, tip),
  .pre_count   = 9u,
  .field_count = 12u,
  .a11y_bit    = 9u,
  .has_a11y    = 1u,
};
static_assert(
  offsetof(XtkToggleProps, set) == 0u && offsetof(XtkToggleProps, stamp) == offsetof(XtkLayoutProps, stamp),
  "header prefix"
);
static_assert(
  offsetof(XtkToggleProps, acontrols_len) - offsetof(XtkToggleProps, tip)
    == offsetof(XtkLayoutProps, acontrols_len) - offsetof(XtkLayoutProps, tip),
  "a11y span"
);
static XtkCtrlField const k_fields_toggle [11] = {
  {( uint16_t ) offsetof(XtkToggleProps, w), 0u, XTK_PROP_WIDTH, 0u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkToggleProps, h), 0u, XTK_PROP_HEIGHT, 1u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkToggleProps, grow), 0u, XTK_PROP_GROW, 2u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkToggleProps, self), 0u, XTK_PROP_ALIGN_SELF, 3u, XTK_VALUE_ENUM},
  {( uint16_t ) offsetof(XtkToggleProps, ml), 0u, XTK_PROP_MARGIN_LEFT, 4u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkToggleProps, mt), 0u, XTK_PROP_MARGIN_TOP, 5u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkToggleProps, mr), 0u, XTK_PROP_MARGIN_RIGHT, 6u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkToggleProps, mb), 0u, XTK_PROP_MARGIN_BOTTOM, 7u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkToggleProps, text), ( uint16_t ) offsetof(XtkToggleProps, text_len), XTK_PROP_TEXT, 8u,
   XTK_VALUE_STRING},
  {( uint16_t ) offsetof(XtkToggleProps, enabled), 0u, XTK_PROP_ENABLED, 37u, XTK_VALUE_BOOL},
  {( uint16_t ) offsetof(XtkToggleProps, checked), 0u, XTK_PROP_CHECKED, 38u, XTK_VALUE_BOOL},
};
XtkCtrlPack const xtk_pack_toggle = {
  .fields      = k_fields_toggle,
  .a11y_offset = ( uint16_t ) offsetof(XtkToggleProps, tip),
  .pre_count   = 9u,
  .field_count = 11u,
  .a11y_bit    = 9u,
  .has_a11y    = 1u,
};
static_assert(
  offsetof(XtkCheckBoxProps, set) == 0u && offsetof(XtkCheckBoxProps, stamp) == offsetof(XtkLayoutProps, stamp),
  "header prefix"
);
static_assert(
  offsetof(XtkCheckBoxProps, acontrols_len) - offsetof(XtkCheckBoxProps, tip)
    == offsetof(XtkLayoutProps, acontrols_len) - offsetof(XtkLayoutProps, tip),
  "a11y span"
);
static XtkCtrlField const k_fields_checkbox [13] = {
  {( uint16_t ) offsetof(XtkCheckBoxProps, w), 0u, XTK_PROP_WIDTH, 0u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkCheckBoxProps, h), 0u, XTK_PROP_HEIGHT, 1u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkCheckBoxProps, grow), 0u, XTK_PROP_GROW, 2u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkCheckBoxProps, self), 0u, XTK_PROP_ALIGN_SELF, 3u, XTK_VALUE_ENUM},
  {( uint16_t ) offsetof(XtkCheckBoxProps, ml), 0u, XTK_PROP_MARGIN_LEFT, 4u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkCheckBoxProps, mt), 0u, XTK_PROP_MARGIN_TOP, 5u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkCheckBoxProps, mr), 0u, XTK_PROP_MARGIN_RIGHT, 6u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkCheckBoxProps, mb), 0u, XTK_PROP_MARGIN_BOTTOM, 7u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkCheckBoxProps, text), ( uint16_t ) offsetof(XtkCheckBoxProps, text_len), XTK_PROP_TEXT, 8u,
   XTK_VALUE_STRING},
  {( uint16_t ) offsetof(XtkCheckBoxProps, enabled), 0u, XTK_PROP_ENABLED, 37u, XTK_VALUE_BOOL},
  {( uint16_t ) offsetof(XtkCheckBoxProps, checked), 0u, XTK_PROP_CHECKED, 38u, XTK_VALUE_BOOL},
  {( uint16_t ) offsetof(XtkCheckBoxProps, indeterminate), 0u, XTK_PROP_INDETERMINATE, 39u, XTK_VALUE_BOOL},
  {( uint16_t ) offsetof(XtkCheckBoxProps, threestate), 0u, XTK_PROP_IS_THREE_STATE, 40u, XTK_VALUE_BOOL},
};
XtkCtrlPack const xtk_pack_checkbox = {
  .fields      = k_fields_checkbox,
  .a11y_offset = ( uint16_t ) offsetof(XtkCheckBoxProps, tip),
  .pre_count   = 9u,
  .field_count = 13u,
  .a11y_bit    = 9u,
  .has_a11y    = 1u,
};
static_assert(
  offsetof(XtkSliderProps, set) == 0u && offsetof(XtkSliderProps, stamp) == offsetof(XtkLayoutProps, stamp),
  "header prefix"
);
static_assert(
  offsetof(XtkSliderProps, acontrols_len) - offsetof(XtkSliderProps, tip)
    == offsetof(XtkLayoutProps, acontrols_len) - offsetof(XtkLayoutProps, tip),
  "a11y span"
);
static XtkCtrlField const k_fields_slider [22] = {
  {( uint16_t ) offsetof(XtkSliderProps, w),           0u, XTK_PROP_WIDTH,           0u,  XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkSliderProps, h),           0u, XTK_PROP_HEIGHT,          1u,  XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkSliderProps, grow),        0u, XTK_PROP_GROW,            2u,  XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkSliderProps, self),        0u, XTK_PROP_ALIGN_SELF,      3u,  XTK_VALUE_ENUM},
  {( uint16_t ) offsetof(XtkSliderProps, ml),          0u, XTK_PROP_MARGIN_LEFT,     4u,  XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkSliderProps, mt),          0u, XTK_PROP_MARGIN_TOP,      5u,  XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkSliderProps, mr),          0u, XTK_PROP_MARGIN_RIGHT,    6u,  XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkSliderProps, mb),          0u, XTK_PROP_MARGIN_BOTTOM,   7u,  XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkSliderProps, enabled),     0u, XTK_PROP_ENABLED,         36u, XTK_VALUE_BOOL},
  {( uint16_t ) offsetof(XtkSliderProps, min),         0u, XTK_PROP_MIN_F32,         37u, XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkSliderProps, max),         0u, XTK_PROP_MAX_F32,         38u, XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkSliderProps, value),       0u, XTK_PROP_VALUE_F32,       39u, XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkSliderProps, step),        0u, XTK_PROP_STEP_F32,        40u, XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkSliderProps, tick),        0u, XTK_PROP_TICK_FREQUENCY,  41u, XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkSliderProps, tickplace),   0u, XTK_PROP_TICK_PLACEMENT,  42u, XTK_VALUE_ENUM},
  {( uint16_t ) offsetof(XtkSliderProps, snapsto),     0u, XTK_PROP_SLIDER_SNAPS_TO, 43u, XTK_VALUE_ENUM},
  {( uint16_t ) offsetof(XtkSliderProps, smallchange), 0u, XTK_PROP_SMALL_CHANGE,    44u, XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkSliderProps, largechange), 0u, XTK_PROP_LARGE_CHANGE,    45u, XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkSliderProps, dir),         0u, XTK_PROP_ORIENTATION,     46u, XTK_VALUE_ENUM},
  {( uint16_t ) offsetof(XtkSliderProps, range),       0u, XTK_PROP_IS_RANGE,        47u, XTK_VALUE_BOOL},
  {( uint16_t ) offsetof(XtkSliderProps, rangestart),  0u, XTK_PROP_RANGE_START,     48u, XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkSliderProps, rangeend),    0u, XTK_PROP_RANGE_END,       49u, XTK_VALUE_F32 },
};
XtkCtrlPack const xtk_pack_slider = {
  .fields      = k_fields_slider,
  .a11y_offset = ( uint16_t ) offsetof(XtkSliderProps, tip),
  .pre_count   = 8u,
  .field_count = 22u,
  .a11y_bit    = 8u,
  .has_a11y    = 1u,
};
static_assert(
  offsetof(XtkTextBoxProps, set) == 0u && offsetof(XtkTextBoxProps, stamp) == offsetof(XtkLayoutProps, stamp),
  "header prefix"
);
static_assert(
  offsetof(XtkTextBoxProps, acontrols_len) - offsetof(XtkTextBoxProps, tip)
    == offsetof(XtkLayoutProps, acontrols_len) - offsetof(XtkLayoutProps, tip),
  "a11y span"
);
static XtkCtrlField const k_fields_textbox [13] = {
  {( uint16_t ) offsetof(XtkTextBoxProps, w), 0u, XTK_PROP_WIDTH, 0u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkTextBoxProps, h), 0u, XTK_PROP_HEIGHT, 1u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkTextBoxProps, grow), 0u, XTK_PROP_GROW, 2u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkTextBoxProps, self), 0u, XTK_PROP_ALIGN_SELF, 3u, XTK_VALUE_ENUM},
  {( uint16_t ) offsetof(XtkTextBoxProps, ml), 0u, XTK_PROP_MARGIN_LEFT, 4u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkTextBoxProps, mt), 0u, XTK_PROP_MARGIN_TOP, 5u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkTextBoxProps, mr), 0u, XTK_PROP_MARGIN_RIGHT, 6u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkTextBoxProps, mb), 0u, XTK_PROP_MARGIN_BOTTOM, 7u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkTextBoxProps, text), ( uint16_t ) offsetof(XtkTextBoxProps, text_len), XTK_PROP_TEXT, 8u,
   XTK_VALUE_STRING},
  {( uint16_t ) offsetof(XtkTextBoxProps, enabled), 0u, XTK_PROP_ENABLED, 37u, XTK_VALUE_BOOL},
  {( uint16_t ) offsetof(XtkTextBoxProps, placeholder), ( uint16_t ) offsetof(XtkTextBoxProps, placeholder_len),
   XTK_PROP_PLACEHOLDER, 38u, XTK_VALUE_STRING},
  {( uint16_t ) offsetof(XtkTextBoxProps, multiline), 0u, XTK_PROP_MULTILINE, 39u, XTK_VALUE_BOOL},
  {( uint16_t ) offsetof(XtkTextBoxProps, readonly), 0u, XTK_PROP_READ_ONLY, 40u, XTK_VALUE_BOOL},
};
XtkCtrlPack const xtk_pack_textbox = {
  .fields      = k_fields_textbox,
  .a11y_offset = ( uint16_t ) offsetof(XtkTextBoxProps, tip),
  .pre_count   = 9u,
  .field_count = 13u,
  .a11y_bit    = 9u,
  .has_a11y    = 1u,
};
static_assert(
  offsetof(XtkScrollProps, set) == 0u && offsetof(XtkScrollProps, stamp) == offsetof(XtkLayoutProps, stamp),
  "header prefix"
);
static_assert(
  offsetof(XtkScrollProps, acontrols_len) - offsetof(XtkScrollProps, tip)
    == offsetof(XtkLayoutProps, acontrols_len) - offsetof(XtkLayoutProps, tip),
  "a11y span"
);
static XtkCtrlField const k_fields_scroll [23] = {
  {( uint16_t ) offsetof(XtkScrollProps, w),       0u, XTK_PROP_WIDTH,           0u,  XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkScrollProps, h),       0u, XTK_PROP_HEIGHT,          1u,  XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkScrollProps, grow),    0u, XTK_PROP_GROW,            2u,  XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkScrollProps, shrink),  0u, XTK_PROP_SHRINK,          3u,  XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkScrollProps, self),    0u, XTK_PROP_ALIGN_SELF,      4u,  XTK_VALUE_ENUM},
  {( uint16_t ) offsetof(XtkScrollProps, ml),      0u, XTK_PROP_MARGIN_LEFT,     5u,  XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkScrollProps, mt),      0u, XTK_PROP_MARGIN_TOP,      6u,  XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkScrollProps, mr),      0u, XTK_PROP_MARGIN_RIGHT,    7u,  XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkScrollProps, mb),      0u, XTK_PROP_MARGIN_BOTTOM,   8u,  XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkScrollProps, dir),     0u, XTK_PROP_ORIENTATION,     37u, XTK_VALUE_ENUM},
  {( uint16_t ) offsetof(XtkScrollProps, items),   0u, XTK_PROP_ALIGN_ITEMS,     38u, XTK_VALUE_ENUM},
  {( uint16_t ) offsetof(XtkScrollProps, justify), 0u, XTK_PROP_JUSTIFY_CONTENT, 39u, XTK_VALUE_ENUM},
  {( uint16_t ) offsetof(XtkScrollProps, gap),     0u, XTK_PROP_GAP,             40u, XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkScrollProps, pl),      0u, XTK_PROP_PADDING_LEFT,    41u, XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkScrollProps, pt),      0u, XTK_PROP_PADDING_TOP,     42u, XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkScrollProps, pr),      0u, XTK_PROP_PADDING_RIGHT,   43u, XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkScrollProps, pb),      0u, XTK_PROP_PADDING_BOTTOM,  44u, XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkScrollProps, fill),    0u, XTK_PROP_FILL,            45u, XTK_VALUE_BOOL},
  {( uint16_t ) offsetof(XtkScrollProps, fitw),    0u, XTK_PROP_FIT_WIDTH,       46u, XTK_VALUE_BOOL},
  {( uint16_t ) offsetof(XtkScrollProps, fith),    0u, XTK_PROP_FIT_HEIGHT,      47u, XTK_VALUE_BOOL},
  {( uint16_t ) offsetof(XtkScrollProps, wrap),    0u, XTK_PROP_WRAP,            48u, XTK_VALUE_ENUM},
  {( uint16_t ) offsetof(XtkScrollProps, x),       0u, XTK_PROP_SCROLL_X,        49u, XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkScrollProps, y),       0u, XTK_PROP_SCROLL_Y,        50u, XTK_VALUE_F32 },
};
XtkCtrlPack const xtk_pack_scroll = {
  .fields      = k_fields_scroll,
  .a11y_offset = ( uint16_t ) offsetof(XtkScrollProps, tip),
  .pre_count   = 9u,
  .field_count = 23u,
  .a11y_bit    = 9u,
  .has_a11y    = 1u,
};
static_assert(
  offsetof(XtkImageProps, set) == 0u && offsetof(XtkImageProps, stamp) == offsetof(XtkLayoutProps, stamp),
  "header prefix"
);
static_assert(
  offsetof(XtkImageProps, acontrols_len) - offsetof(XtkImageProps, tip)
    == offsetof(XtkLayoutProps, acontrols_len) - offsetof(XtkLayoutProps, tip),
  "a11y span"
);
static XtkCtrlField const k_fields_image [14] = {
  {( uint16_t ) offsetof(XtkImageProps, w),    0u, XTK_PROP_WIDTH,            0u,  XTK_VALUE_F32     },
  {( uint16_t ) offsetof(XtkImageProps, h),    0u, XTK_PROP_HEIGHT,           1u,  XTK_VALUE_F32     },
  {( uint16_t ) offsetof(XtkImageProps, grow), 0u, XTK_PROP_GROW,             2u,  XTK_VALUE_F32     },
  {( uint16_t ) offsetof(XtkImageProps, self), 0u, XTK_PROP_ALIGN_SELF,       3u,  XTK_VALUE_ENUM    },
  {( uint16_t ) offsetof(XtkImageProps, ml),   0u, XTK_PROP_MARGIN_LEFT,      4u,  XTK_VALUE_F32     },
  {( uint16_t ) offsetof(XtkImageProps, mt),   0u, XTK_PROP_MARGIN_TOP,       5u,  XTK_VALUE_F32     },
  {( uint16_t ) offsetof(XtkImageProps, mr),   0u, XTK_PROP_MARGIN_RIGHT,     6u,  XTK_VALUE_F32     },
  {( uint16_t ) offsetof(XtkImageProps, mb),   0u, XTK_PROP_MARGIN_BOTTOM,    7u,  XTK_VALUE_F32     },
  {( uint16_t ) offsetof(XtkImageProps, src),  0u, XTK_PROP_IMAGE_SOURCE,     36u, XTK_VALUE_RESOURCE},
  {( uint16_t ) offsetof(XtkImageProps, fit),  0u, XTK_PROP_IMAGE_STRETCH,    37u, XTK_VALUE_ENUM    },
  {( uint16_t ) offsetof(XtkImageProps, nl),   0u, XTK_PROP_NINE_GRID_LEFT,   38u, XTK_VALUE_F32     },
  {( uint16_t ) offsetof(XtkImageProps, nt),   0u, XTK_PROP_NINE_GRID_TOP,    39u, XTK_VALUE_F32     },
  {( uint16_t ) offsetof(XtkImageProps, nr),   0u, XTK_PROP_NINE_GRID_RIGHT,  40u, XTK_VALUE_F32     },
  {( uint16_t ) offsetof(XtkImageProps, nb),   0u, XTK_PROP_NINE_GRID_BOTTOM, 41u, XTK_VALUE_F32     },
};
XtkCtrlPack const xtk_pack_image = {
  .fields      = k_fields_image,
  .a11y_offset = ( uint16_t ) offsetof(XtkImageProps, tip),
  .pre_count   = 8u,
  .field_count = 14u,
  .a11y_bit    = 8u,
  .has_a11y    = 1u,
};
static_assert(
  offsetof(XtkProgressProps, set) == 0u && offsetof(XtkProgressProps, stamp) == offsetof(XtkLayoutProps, stamp),
  "header prefix"
);
static_assert(
  offsetof(XtkProgressProps, acontrols_len) - offsetof(XtkProgressProps, tip)
    == offsetof(XtkLayoutProps, acontrols_len) - offsetof(XtkLayoutProps, tip),
  "a11y span"
);
static XtkCtrlField const k_fields_progress [18] = {
  {( uint16_t ) offsetof(XtkProgressProps, w),             0u, XTK_PROP_WIDTH,                 0u,  XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkProgressProps, h),             0u, XTK_PROP_HEIGHT,                1u,  XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkProgressProps, grow),          0u, XTK_PROP_GROW,                  2u,  XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkProgressProps, self),          0u, XTK_PROP_ALIGN_SELF,            3u,  XTK_VALUE_ENUM},
  {( uint16_t ) offsetof(XtkProgressProps, ml),            0u, XTK_PROP_MARGIN_LEFT,           4u,  XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkProgressProps, mt),            0u, XTK_PROP_MARGIN_TOP,            5u,  XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkProgressProps, mr),            0u, XTK_PROP_MARGIN_RIGHT,          6u,  XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkProgressProps, mb),            0u, XTK_PROP_MARGIN_BOTTOM,         7u,  XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkProgressProps, min),           0u, XTK_PROP_MIN_F32,               36u, XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkProgressProps, max),           0u, XTK_PROP_MAX_F32,               37u, XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkProgressProps, value),         0u, XTK_PROP_VALUE_F32,             38u, XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkProgressProps, indeterminate), 0u, XTK_PROP_INDETERMINATE,         39u, XTK_VALUE_BOOL},
  {( uint16_t ) offsetof(XtkProgressProps, state),         0u, XTK_PROP_PROGRESS_STATE,        40u, XTK_VALUE_ENUM},
  {( uint16_t ) offsetof(XtkProgressProps, pl),            0u, XTK_PROP_PADDING_LEFT,          42u, XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkProgressProps, pt),            0u, XTK_PROP_PADDING_TOP,           43u, XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkProgressProps, pr),            0u, XTK_PROP_PADDING_RIGHT,         44u, XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkProgressProps, pb),            0u, XTK_PROP_PADDING_BOTTOM,        45u, XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkProgressProps, border_width),  0u, XTK_PROP_PROGRESS_BORDER_WIDTH, 46u, XTK_VALUE_F32 },
};
XtkCtrlPack const xtk_pack_progress = {
  .fields      = k_fields_progress,
  .a11y_offset = ( uint16_t ) offsetof(XtkProgressProps, tip),
  .pre_count   = 8u,
  .field_count = 18u,
  .a11y_bit    = 8u,
  .has_a11y    = 1u,
};
static_assert(
  offsetof(XtkListProps, set) == 0u && offsetof(XtkListProps, stamp) == offsetof(XtkLayoutProps, stamp), "header prefix"
);
static_assert(
  offsetof(XtkListProps, acontrols_len) - offsetof(XtkListProps, tip)
    == offsetof(XtkLayoutProps, acontrols_len) - offsetof(XtkLayoutProps, tip),
  "a11y span"
);
static XtkCtrlField const k_fields_list [17] = {
  {( uint16_t ) offsetof(XtkListProps, w),       0u, XTK_PROP_WIDTH,               0u,  XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkListProps, h),       0u, XTK_PROP_HEIGHT,              1u,  XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkListProps, grow),    0u, XTK_PROP_GROW,                2u,  XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkListProps, self),    0u, XTK_PROP_ALIGN_SELF,          3u,  XTK_VALUE_ENUM},
  {( uint16_t ) offsetof(XtkListProps, ml),      0u, XTK_PROP_MARGIN_LEFT,         4u,  XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkListProps, mt),      0u, XTK_PROP_MARGIN_TOP,          5u,  XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkListProps, mr),      0u, XTK_PROP_MARGIN_RIGHT,        6u,  XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkListProps, mb),      0u, XTK_PROP_MARGIN_BOTTOM,       7u,  XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkListProps, enabled), 0u, XTK_PROP_ENABLED,             36u, XTK_VALUE_BOOL},
  {( uint16_t ) offsetof(XtkListProps, sel),     0u, XTK_PROP_SELECTED_INDEX,      37u, XTK_VALUE_I32 },
  {( uint16_t ) offsetof(XtkListProps, nitem),   0u, XTK_PROP_ITEM_COUNT,          38u, XTK_VALUE_I32 },
  {( uint16_t ) offsetof(XtkListProps, itemh),   0u, XTK_PROP_ITEM_HEIGHT,         39u, XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkListProps, itemw),   0u, XTK_PROP_ITEM_WIDTH,          40u, XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkListProps, ncol),    0u, XTK_PROP_COLUMN_COUNT,        41u, XTK_VALUE_I32 },
  {( uint16_t ) offsetof(XtkListProps, mode),    0u, XTK_PROP_SELECTION_MODE,      42u, XTK_VALUE_ENUM},
  {( uint16_t ) offsetof(XtkListProps, first),   0u, XTK_PROP_REALIZED_FIRST,      43u, XTK_VALUE_I32 },
  {( uint16_t ) offsetof(XtkListProps, rectsel), 0u, XTK_PROP_RECTANGLE_SELECTION, 44u, XTK_VALUE_BOOL},
};
XtkCtrlPack const xtk_pack_list = {
  .fields      = k_fields_list,
  .a11y_offset = ( uint16_t ) offsetof(XtkListProps, tip),
  .pre_count   = 8u,
  .field_count = 17u,
  .a11y_bit    = 8u,
  .has_a11y    = 1u,
};
static_assert(
  offsetof(XtkLayoutProps, set) == 0u && offsetof(XtkLayoutProps, stamp) == offsetof(XtkLayoutProps, stamp),
  "header prefix"
);
static_assert(
  offsetof(XtkLayoutProps, acontrols_len) - offsetof(XtkLayoutProps, tip)
    == offsetof(XtkLayoutProps, acontrols_len) - offsetof(XtkLayoutProps, tip),
  "a11y span"
);
static XtkCtrlField const k_fields_layout [9] = {
  {( uint16_t ) offsetof(XtkLayoutProps, w),      0u, XTK_PROP_WIDTH,         0u, XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkLayoutProps, h),      0u, XTK_PROP_HEIGHT,        1u, XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkLayoutProps, grow),   0u, XTK_PROP_GROW,          2u, XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkLayoutProps, shrink), 0u, XTK_PROP_SHRINK,        3u, XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkLayoutProps, self),   0u, XTK_PROP_ALIGN_SELF,    4u, XTK_VALUE_ENUM},
  {( uint16_t ) offsetof(XtkLayoutProps, ml),     0u, XTK_PROP_MARGIN_LEFT,   5u, XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkLayoutProps, mt),     0u, XTK_PROP_MARGIN_TOP,    6u, XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkLayoutProps, mr),     0u, XTK_PROP_MARGIN_RIGHT,  7u, XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkLayoutProps, mb),     0u, XTK_PROP_MARGIN_BOTTOM, 8u, XTK_VALUE_F32 },
};
XtkCtrlPack const xtk_pack_layout = {
  .fields      = k_fields_layout,
  .a11y_offset = ( uint16_t ) offsetof(XtkLayoutProps, tip),
  .pre_count   = 9u,
  .field_count = 9u,
  .a11y_bit    = 9u,
  .has_a11y    = 1u,
};
static_assert(
  offsetof(XtkInputProps, set) == 0u && offsetof(XtkInputProps, stamp) == offsetof(XtkLayoutProps, stamp),
  "header prefix"
);
static_assert(
  offsetof(XtkInputProps, acontrols_len) - offsetof(XtkInputProps, tip)
    == offsetof(XtkLayoutProps, acontrols_len) - offsetof(XtkLayoutProps, tip),
  "a11y span"
);
static XtkCtrlField const k_fields_input [11] = {
  {( uint16_t ) offsetof(XtkInputProps, w), 0u, XTK_PROP_WIDTH, 0u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkInputProps, h), 0u, XTK_PROP_HEIGHT, 1u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkInputProps, grow), 0u, XTK_PROP_GROW, 2u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkInputProps, self), 0u, XTK_PROP_ALIGN_SELF, 3u, XTK_VALUE_ENUM},
  {( uint16_t ) offsetof(XtkInputProps, ml), 0u, XTK_PROP_MARGIN_LEFT, 4u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkInputProps, mt), 0u, XTK_PROP_MARGIN_TOP, 5u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkInputProps, mr), 0u, XTK_PROP_MARGIN_RIGHT, 6u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkInputProps, mb), 0u, XTK_PROP_MARGIN_BOTTOM, 7u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkInputProps, text), ( uint16_t ) offsetof(XtkInputProps, text_len), XTK_PROP_TEXT, 8u,
   XTK_VALUE_STRING},
  {( uint16_t ) offsetof(XtkInputProps, enabled), 0u, XTK_PROP_ENABLED, 37u, XTK_VALUE_BOOL},
  {( uint16_t ) offsetof(XtkInputProps, placeholder), ( uint16_t ) offsetof(XtkInputProps, placeholder_len),
   XTK_PROP_PLACEHOLDER, 38u, XTK_VALUE_STRING},
};
XtkCtrlPack const xtk_pack_input = {
  .fields      = k_fields_input,
  .a11y_offset = ( uint16_t ) offsetof(XtkInputProps, tip),
  .pre_count   = 9u,
  .field_count = 11u,
  .a11y_bit    = 9u,
  .has_a11y    = 1u,
};
static_assert(
  offsetof(XtkNumberProps, set) == 0u && offsetof(XtkNumberProps, stamp) == offsetof(XtkLayoutProps, stamp),
  "header prefix"
);
static_assert(
  offsetof(XtkNumberProps, acontrols_len) - offsetof(XtkNumberProps, tip)
    == offsetof(XtkLayoutProps, acontrols_len) - offsetof(XtkLayoutProps, tip),
  "a11y span"
);
static XtkCtrlField const k_fields_number [14] = {
  {( uint16_t ) offsetof(XtkNumberProps, w),        0u, XTK_PROP_WIDTH,         0u,  XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkNumberProps, h),        0u, XTK_PROP_HEIGHT,        1u,  XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkNumberProps, grow),     0u, XTK_PROP_GROW,          2u,  XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkNumberProps, self),     0u, XTK_PROP_ALIGN_SELF,    3u,  XTK_VALUE_ENUM},
  {( uint16_t ) offsetof(XtkNumberProps, ml),       0u, XTK_PROP_MARGIN_LEFT,   4u,  XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkNumberProps, mt),       0u, XTK_PROP_MARGIN_TOP,    5u,  XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkNumberProps, mr),       0u, XTK_PROP_MARGIN_RIGHT,  6u,  XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkNumberProps, mb),       0u, XTK_PROP_MARGIN_BOTTOM, 7u,  XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkNumberProps, enabled),  0u, XTK_PROP_ENABLED,       36u, XTK_VALUE_BOOL},
  {( uint16_t ) offsetof(XtkNumberProps, value),    0u, XTK_PROP_VALUE_F64,     37u, XTK_VALUE_F64 },
  {( uint16_t ) offsetof(XtkNumberProps, min),      0u, XTK_PROP_MIN_F64,       38u, XTK_VALUE_F64 },
  {( uint16_t ) offsetof(XtkNumberProps, max),      0u, XTK_PROP_MAX_F64,       39u, XTK_VALUE_F64 },
  {( uint16_t ) offsetof(XtkNumberProps, step),     0u, XTK_PROP_STEP_F64,      40u, XTK_VALUE_F64 },
  {( uint16_t ) offsetof(XtkNumberProps, hidespin), 0u, XTK_PROP_HIDE_SPIN,     41u, XTK_VALUE_BOOL},
};
XtkCtrlPack const xtk_pack_number = {
  .fields      = k_fields_number,
  .a11y_offset = ( uint16_t ) offsetof(XtkNumberProps, tip),
  .pre_count   = 8u,
  .field_count = 14u,
  .a11y_bit    = 8u,
  .has_a11y    = 1u,
};
static_assert(
  offsetof(XtkLinkProps, set) == 0u && offsetof(XtkLinkProps, stamp) == offsetof(XtkLayoutProps, stamp), "header prefix"
);
static_assert(
  offsetof(XtkLinkProps, acontrols_len) - offsetof(XtkLinkProps, tip)
    == offsetof(XtkLayoutProps, acontrols_len) - offsetof(XtkLayoutProps, tip),
  "a11y span"
);
static XtkCtrlField const k_fields_link [11] = {
  {( uint16_t ) offsetof(XtkLinkProps, w), 0u, XTK_PROP_WIDTH, 0u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkLinkProps, h), 0u, XTK_PROP_HEIGHT, 1u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkLinkProps, grow), 0u, XTK_PROP_GROW, 2u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkLinkProps, self), 0u, XTK_PROP_ALIGN_SELF, 3u, XTK_VALUE_ENUM},
  {( uint16_t ) offsetof(XtkLinkProps, ml), 0u, XTK_PROP_MARGIN_LEFT, 4u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkLinkProps, mt), 0u, XTK_PROP_MARGIN_TOP, 5u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkLinkProps, mr), 0u, XTK_PROP_MARGIN_RIGHT, 6u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkLinkProps, mb), 0u, XTK_PROP_MARGIN_BOTTOM, 7u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkLinkProps, text), ( uint16_t ) offsetof(XtkLinkProps, text_len), XTK_PROP_TEXT, 8u,
   XTK_VALUE_STRING},
  {( uint16_t ) offsetof(XtkLinkProps, enabled), 0u, XTK_PROP_ENABLED, 37u, XTK_VALUE_BOOL},
  {( uint16_t ) offsetof(XtkLinkProps, url), ( uint16_t ) offsetof(XtkLinkProps, url_len), XTK_PROP_URL, 38u,
   XTK_VALUE_STRING},
};
XtkCtrlPack const xtk_pack_link = {
  .fields      = k_fields_link,
  .a11y_offset = ( uint16_t ) offsetof(XtkLinkProps, tip),
  .pre_count   = 9u,
  .field_count = 11u,
  .a11y_bit    = 9u,
  .has_a11y    = 1u,
};
static_assert(
  offsetof(XtkProgressProps, set) == 0u && offsetof(XtkProgressProps, stamp) == offsetof(XtkLayoutProps, stamp),
  "header prefix"
);
static_assert(
  offsetof(XtkProgressProps, acontrols_len) - offsetof(XtkProgressProps, tip)
    == offsetof(XtkLayoutProps, acontrols_len) - offsetof(XtkLayoutProps, tip),
  "a11y span"
);
static XtkCtrlField const k_fields_progressring [14] = {
  {( uint16_t ) offsetof(XtkProgressProps, w),             0u, XTK_PROP_WIDTH,           0u,  XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkProgressProps, h),             0u, XTK_PROP_HEIGHT,          1u,  XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkProgressProps, grow),          0u, XTK_PROP_GROW,            2u,  XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkProgressProps, self),          0u, XTK_PROP_ALIGN_SELF,      3u,  XTK_VALUE_ENUM},
  {( uint16_t ) offsetof(XtkProgressProps, ml),            0u, XTK_PROP_MARGIN_LEFT,     4u,  XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkProgressProps, mt),            0u, XTK_PROP_MARGIN_TOP,      5u,  XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkProgressProps, mr),            0u, XTK_PROP_MARGIN_RIGHT,    6u,  XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkProgressProps, mb),            0u, XTK_PROP_MARGIN_BOTTOM,   7u,  XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkProgressProps, min),           0u, XTK_PROP_MIN_F32,         36u, XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkProgressProps, max),           0u, XTK_PROP_MAX_F32,         37u, XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkProgressProps, value),         0u, XTK_PROP_VALUE_F32,       38u, XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkProgressProps, indeterminate), 0u, XTK_PROP_INDETERMINATE,   39u, XTK_VALUE_BOOL},
  {( uint16_t ) offsetof(XtkProgressProps, state),         0u, XTK_PROP_PROGRESS_STATE,  40u, XTK_VALUE_ENUM},
  {( uint16_t ) offsetof(XtkProgressProps, active),        0u, XTK_PROP_PROGRESS_ACTIVE, 41u, XTK_VALUE_BOOL},
};
XtkCtrlPack const xtk_pack_progressring = {
  .fields      = k_fields_progressring,
  .a11y_offset = ( uint16_t ) offsetof(XtkProgressProps, tip),
  .pre_count   = 8u,
  .field_count = 14u,
  .a11y_bit    = 8u,
  .has_a11y    = 1u,
};
static_assert(
  offsetof(XtkBadgeProps, set) == 0u && offsetof(XtkBadgeProps, stamp) == offsetof(XtkLayoutProps, stamp),
  "header prefix"
);
static_assert(
  offsetof(XtkBadgeProps, acontrols_len) - offsetof(XtkBadgeProps, tip)
    == offsetof(XtkLayoutProps, acontrols_len) - offsetof(XtkLayoutProps, tip),
  "a11y span"
);
static XtkCtrlField const k_fields_badge [12] = {
  {( uint16_t ) offsetof(XtkBadgeProps, w), 0u, XTK_PROP_WIDTH, 0u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkBadgeProps, h), 0u, XTK_PROP_HEIGHT, 1u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkBadgeProps, grow), 0u, XTK_PROP_GROW, 2u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkBadgeProps, shrink), 0u, XTK_PROP_SHRINK, 3u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkBadgeProps, self), 0u, XTK_PROP_ALIGN_SELF, 4u, XTK_VALUE_ENUM},
  {( uint16_t ) offsetof(XtkBadgeProps, ml), 0u, XTK_PROP_MARGIN_LEFT, 5u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkBadgeProps, mt), 0u, XTK_PROP_MARGIN_TOP, 6u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkBadgeProps, mr), 0u, XTK_PROP_MARGIN_RIGHT, 7u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkBadgeProps, mb), 0u, XTK_PROP_MARGIN_BOTTOM, 8u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkBadgeProps, badgemode), 0u, XTK_PROP_BADGE_MODE, 37u, XTK_VALUE_ENUM},
  {( uint16_t ) offsetof(XtkBadgeProps, value), 0u, XTK_PROP_BADGE_VALUE, 38u, XTK_VALUE_I32},
  {( uint16_t ) offsetof(XtkBadgeProps, icon), ( uint16_t ) offsetof(XtkBadgeProps, icon_len), XTK_PROP_ICON, 39u,
   XTK_VALUE_STRING},
};
XtkCtrlPack const xtk_pack_badge = {
  .fields      = k_fields_badge,
  .a11y_offset = ( uint16_t ) offsetof(XtkBadgeProps, tip),
  .pre_count   = 9u,
  .field_count = 12u,
  .a11y_bit    = 9u,
  .has_a11y    = 1u,
};
static_assert(
  offsetof(XtkOverlayProps, set) == 0u && offsetof(XtkOverlayProps, stamp) == offsetof(XtkLayoutProps, stamp),
  "header prefix"
);
static_assert(
  offsetof(XtkOverlayProps, acontrols_len) - offsetof(XtkOverlayProps, tip)
    == offsetof(XtkLayoutProps, acontrols_len) - offsetof(XtkLayoutProps, tip),
  "a11y span"
);
static XtkCtrlField const k_fields_overlay [11] = {
  {( uint16_t ) offsetof(XtkOverlayProps, w), 0u, XTK_PROP_WIDTH, 0u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkOverlayProps, h), 0u, XTK_PROP_HEIGHT, 1u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkOverlayProps, grow), 0u, XTK_PROP_GROW, 2u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkOverlayProps, self), 0u, XTK_PROP_ALIGN_SELF, 3u, XTK_VALUE_ENUM},
  {( uint16_t ) offsetof(XtkOverlayProps, ml), 0u, XTK_PROP_MARGIN_LEFT, 4u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkOverlayProps, mt), 0u, XTK_PROP_MARGIN_TOP, 5u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkOverlayProps, mr), 0u, XTK_PROP_MARGIN_RIGHT, 6u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkOverlayProps, mb), 0u, XTK_PROP_MARGIN_BOTTOM, 7u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkOverlayProps, text), ( uint16_t ) offsetof(XtkOverlayProps, text_len), XTK_PROP_TEXT, 8u,
   XTK_VALUE_STRING},
  {( uint16_t ) offsetof(XtkOverlayProps, open), 0u, XTK_PROP_OPEN, 37u, XTK_VALUE_BOOL},
  {( uint16_t ) offsetof(XtkOverlayProps, enabled), 0u, XTK_PROP_ENABLED, 38u, XTK_VALUE_BOOL},
};
XtkCtrlPack const xtk_pack_overlay = {
  .fields      = k_fields_overlay,
  .a11y_offset = ( uint16_t ) offsetof(XtkOverlayProps, tip),
  .pre_count   = 9u,
  .field_count = 11u,
  .a11y_bit    = 9u,
  .has_a11y    = 1u,
};
static_assert(
  offsetof(XtkComboProps, set) == 0u && offsetof(XtkComboProps, stamp) == offsetof(XtkLayoutProps, stamp),
  "header prefix"
);
static_assert(
  offsetof(XtkComboProps, acontrols_len) - offsetof(XtkComboProps, tip)
    == offsetof(XtkLayoutProps, acontrols_len) - offsetof(XtkLayoutProps, tip),
  "a11y span"
);
static XtkCtrlField const k_fields_combo [13] = {
  {( uint16_t ) offsetof(XtkComboProps, w), 0u, XTK_PROP_WIDTH, 0u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkComboProps, h), 0u, XTK_PROP_HEIGHT, 1u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkComboProps, grow), 0u, XTK_PROP_GROW, 2u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkComboProps, self), 0u, XTK_PROP_ALIGN_SELF, 3u, XTK_VALUE_ENUM},
  {( uint16_t ) offsetof(XtkComboProps, ml), 0u, XTK_PROP_MARGIN_LEFT, 4u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkComboProps, mt), 0u, XTK_PROP_MARGIN_TOP, 5u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkComboProps, mr), 0u, XTK_PROP_MARGIN_RIGHT, 6u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkComboProps, mb), 0u, XTK_PROP_MARGIN_BOTTOM, 7u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkComboProps, enabled), 0u, XTK_PROP_ENABLED, 36u, XTK_VALUE_BOOL},
  {( uint16_t ) offsetof(XtkComboProps, placeholder), ( uint16_t ) offsetof(XtkComboProps, placeholder_len),
   XTK_PROP_PLACEHOLDER, 37u, XTK_VALUE_STRING},
  {( uint16_t ) offsetof(XtkComboProps, sel), 0u, XTK_PROP_SELECTED_INDEX, 38u, XTK_VALUE_I32},
  {( uint16_t ) offsetof(XtkComboProps, text), ( uint16_t ) offsetof(XtkComboProps, text_len), XTK_PROP_TEXT, 39u,
   XTK_VALUE_STRING},
  {( uint16_t ) offsetof(XtkComboProps, editable), 0u, XTK_PROP_IS_EDITABLE, 40u, XTK_VALUE_BOOL},
};
XtkCtrlPack const xtk_pack_combo = {
  .fields      = k_fields_combo,
  .a11y_offset = ( uint16_t ) offsetof(XtkComboProps, tip),
  .pre_count   = 8u,
  .field_count = 13u,
  .a11y_bit    = 8u,
  .has_a11y    = 1u,
};
static_assert(
  offsetof(XtkExpanderProps, set) == 0u && offsetof(XtkExpanderProps, stamp) == offsetof(XtkLayoutProps, stamp),
  "header prefix"
);
static_assert(
  offsetof(XtkExpanderProps, acontrols_len) - offsetof(XtkExpanderProps, tip)
    == offsetof(XtkLayoutProps, acontrols_len) - offsetof(XtkLayoutProps, tip),
  "a11y span"
);
static XtkCtrlField const k_fields_expander [11] = {
  {( uint16_t ) offsetof(XtkExpanderProps, w), 0u, XTK_PROP_WIDTH, 0u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkExpanderProps, h), 0u, XTK_PROP_HEIGHT, 1u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkExpanderProps, grow), 0u, XTK_PROP_GROW, 2u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkExpanderProps, self), 0u, XTK_PROP_ALIGN_SELF, 3u, XTK_VALUE_ENUM},
  {( uint16_t ) offsetof(XtkExpanderProps, ml), 0u, XTK_PROP_MARGIN_LEFT, 4u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkExpanderProps, mt), 0u, XTK_PROP_MARGIN_TOP, 5u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkExpanderProps, mr), 0u, XTK_PROP_MARGIN_RIGHT, 6u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkExpanderProps, mb), 0u, XTK_PROP_MARGIN_BOTTOM, 7u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkExpanderProps, text), ( uint16_t ) offsetof(XtkExpanderProps, text_len), XTK_PROP_TEXT, 8u,
   XTK_VALUE_STRING},
  {( uint16_t ) offsetof(XtkExpanderProps, expanded), 0u, XTK_PROP_EXPANDED, 37u, XTK_VALUE_BOOL},
  {( uint16_t ) offsetof(XtkExpanderProps, contenth), 0u, XTK_PROP_CONTENT_HEIGHT, 38u, XTK_VALUE_F32},
};
XtkCtrlPack const xtk_pack_expander = {
  .fields      = k_fields_expander,
  .a11y_offset = ( uint16_t ) offsetof(XtkExpanderProps, tip),
  .pre_count   = 9u,
  .field_count = 11u,
  .a11y_bit    = 9u,
  .has_a11y    = 1u,
};
static_assert(
  offsetof(XtkItemProps, set) == 0u && offsetof(XtkItemProps, stamp) == offsetof(XtkLayoutProps, stamp), "header prefix"
);
static_assert(
  offsetof(XtkItemProps, acontrols_len) - offsetof(XtkItemProps, tip)
    == offsetof(XtkLayoutProps, acontrols_len) - offsetof(XtkLayoutProps, tip),
  "a11y span"
);
static XtkCtrlField const k_fields_item [13] = {
  {( uint16_t ) offsetof(XtkItemProps, w), 0u, XTK_PROP_WIDTH, 0u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkItemProps, h), 0u, XTK_PROP_HEIGHT, 1u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkItemProps, grow), 0u, XTK_PROP_GROW, 2u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkItemProps, self), 0u, XTK_PROP_ALIGN_SELF, 3u, XTK_VALUE_ENUM},
  {( uint16_t ) offsetof(XtkItemProps, ml), 0u, XTK_PROP_MARGIN_LEFT, 4u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkItemProps, mt), 0u, XTK_PROP_MARGIN_TOP, 5u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkItemProps, mr), 0u, XTK_PROP_MARGIN_RIGHT, 6u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkItemProps, mb), 0u, XTK_PROP_MARGIN_BOTTOM, 7u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkItemProps, text), ( uint16_t ) offsetof(XtkItemProps, text_len), XTK_PROP_TEXT, 8u,
   XTK_VALUE_STRING},
  {( uint16_t ) offsetof(XtkItemProps, icon), ( uint16_t ) offsetof(XtkItemProps, icon_len), XTK_PROP_ICON, 37u,
   XTK_VALUE_STRING},
  {( uint16_t ) offsetof(XtkItemProps, enabled), 0u, XTK_PROP_ENABLED, 38u, XTK_VALUE_BOOL},
  {( uint16_t ) offsetof(XtkItemProps, selected), 0u, XTK_PROP_SELECTED, 39u, XTK_VALUE_BOOL},
  {( uint16_t ) offsetof(XtkItemProps, expanded), 0u, XTK_PROP_EXPANDED, 40u, XTK_VALUE_BOOL},
};
XtkCtrlPack const xtk_pack_item = {
  .fields      = k_fields_item,
  .a11y_offset = ( uint16_t ) offsetof(XtkItemProps, tip),
  .pre_count   = 9u,
  .field_count = 13u,
  .a11y_bit    = 9u,
  .has_a11y    = 1u,
};
static_assert(
  offsetof(XtkInfoBarProps, set) == 0u && offsetof(XtkInfoBarProps, stamp) == offsetof(XtkLayoutProps, stamp),
  "header prefix"
);
static_assert(
  offsetof(XtkInfoBarProps, acontrols_len) - offsetof(XtkInfoBarProps, tip)
    == offsetof(XtkLayoutProps, acontrols_len) - offsetof(XtkLayoutProps, tip),
  "a11y span"
);
static XtkCtrlField const k_fields_infobar [12] = {
  {( uint16_t ) offsetof(XtkInfoBarProps, w), 0u, XTK_PROP_WIDTH, 0u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkInfoBarProps, h), 0u, XTK_PROP_HEIGHT, 1u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkInfoBarProps, grow), 0u, XTK_PROP_GROW, 2u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkInfoBarProps, self), 0u, XTK_PROP_ALIGN_SELF, 3u, XTK_VALUE_ENUM},
  {( uint16_t ) offsetof(XtkInfoBarProps, ml), 0u, XTK_PROP_MARGIN_LEFT, 4u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkInfoBarProps, mt), 0u, XTK_PROP_MARGIN_TOP, 5u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkInfoBarProps, mr), 0u, XTK_PROP_MARGIN_RIGHT, 6u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkInfoBarProps, mb), 0u, XTK_PROP_MARGIN_BOTTOM, 7u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkInfoBarProps, text), ( uint16_t ) offsetof(XtkInfoBarProps, text_len), XTK_PROP_TEXT, 8u,
   XTK_VALUE_STRING},
  {( uint16_t ) offsetof(XtkInfoBarProps, message), ( uint16_t ) offsetof(XtkInfoBarProps, message_len),
   XTK_PROP_MESSAGE, 9u, XTK_VALUE_STRING},
  {( uint16_t ) offsetof(XtkInfoBarProps, severity), 0u, XTK_PROP_SEVERITY, 38u, XTK_VALUE_ENUM},
  {( uint16_t ) offsetof(XtkInfoBarProps, closable), 0u, XTK_PROP_CLOSABLE, 39u, XTK_VALUE_BOOL},
};
XtkCtrlPack const xtk_pack_infobar = {
  .fields      = k_fields_infobar,
  .a11y_offset = ( uint16_t ) offsetof(XtkInfoBarProps, tip),
  .pre_count   = 10u,
  .field_count = 12u,
  .a11y_bit    = 10u,
  .has_a11y    = 1u,
};
static_assert(
  offsetof(XtkDialogProps, set) == 0u && offsetof(XtkDialogProps, stamp) == offsetof(XtkLayoutProps, stamp),
  "header prefix"
);
static_assert(
  offsetof(XtkDialogProps, acontrols_len) - offsetof(XtkDialogProps, tip)
    == offsetof(XtkLayoutProps, acontrols_len) - offsetof(XtkLayoutProps, tip),
  "a11y span"
);
static XtkCtrlField const k_fields_dialog [16] = {
  {( uint16_t ) offsetof(XtkDialogProps, w), 0u, XTK_PROP_WIDTH, 0u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkDialogProps, h), 0u, XTK_PROP_HEIGHT, 1u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkDialogProps, grow), 0u, XTK_PROP_GROW, 2u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkDialogProps, shrink), 0u, XTK_PROP_SHRINK, 3u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkDialogProps, self), 0u, XTK_PROP_ALIGN_SELF, 4u, XTK_VALUE_ENUM},
  {( uint16_t ) offsetof(XtkDialogProps, ml), 0u, XTK_PROP_MARGIN_LEFT, 5u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkDialogProps, mt), 0u, XTK_PROP_MARGIN_TOP, 6u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkDialogProps, mr), 0u, XTK_PROP_MARGIN_RIGHT, 7u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkDialogProps, mb), 0u, XTK_PROP_MARGIN_BOTTOM, 8u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkDialogProps, text), ( uint16_t ) offsetof(XtkDialogProps, text_len), XTK_PROP_TEXT, 37u,
   XTK_VALUE_STRING},
  {( uint16_t ) offsetof(XtkDialogProps, primary), ( uint16_t ) offsetof(XtkDialogProps, primary_len),
   XTK_PROP_PRIMARY_TEXT, 38u, XTK_VALUE_STRING},
  {( uint16_t ) offsetof(XtkDialogProps, secondary), ( uint16_t ) offsetof(XtkDialogProps, secondary_len),
   XTK_PROP_SECONDARY_TEXT, 39u, XTK_VALUE_STRING},
  {( uint16_t ) offsetof(XtkDialogProps, close), ( uint16_t ) offsetof(XtkDialogProps, close_len), XTK_PROP_CLOSE_TEXT,
   40u, XTK_VALUE_STRING},
  {( uint16_t ) offsetof(XtkDialogProps, contenth), 0u, XTK_PROP_CONTENT_HEIGHT, 41u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkDialogProps, default_button), 0u, XTK_PROP_DIALOG_DEFAULT_BUTTON, 42u, XTK_VALUE_ENUM},
  {( uint16_t ) offsetof(XtkDialogProps, open), 0u, XTK_PROP_OPEN, 43u, XTK_VALUE_BOOL},
};
XtkCtrlPack const xtk_pack_dialog = {
  .fields      = k_fields_dialog,
  .a11y_offset = ( uint16_t ) offsetof(XtkDialogProps, tip),
  .pre_count   = 9u,
  .field_count = 16u,
  .a11y_bit    = 9u,
  .has_a11y    = 1u,
};
static_assert(
  offsetof(XtkNavProps, set) == 0u && offsetof(XtkNavProps, stamp) == offsetof(XtkLayoutProps, stamp), "header prefix"
);
static_assert(
  offsetof(XtkNavProps, acontrols_len) - offsetof(XtkNavProps, tip)
    == offsetof(XtkLayoutProps, acontrols_len) - offsetof(XtkLayoutProps, tip),
  "a11y span"
);
static XtkCtrlField const k_fields_nav [16] = {
  {( uint16_t ) offsetof(XtkNavProps, w), 0u, XTK_PROP_WIDTH, 0u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkNavProps, h), 0u, XTK_PROP_HEIGHT, 1u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkNavProps, grow), 0u, XTK_PROP_GROW, 2u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkNavProps, self), 0u, XTK_PROP_ALIGN_SELF, 3u, XTK_VALUE_ENUM},
  {( uint16_t ) offsetof(XtkNavProps, ml), 0u, XTK_PROP_MARGIN_LEFT, 4u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkNavProps, mt), 0u, XTK_PROP_MARGIN_TOP, 5u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkNavProps, mr), 0u, XTK_PROP_MARGIN_RIGHT, 6u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkNavProps, mb), 0u, XTK_PROP_MARGIN_BOTTOM, 7u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkNavProps, enabled), 0u, XTK_PROP_ENABLED, 36u, XTK_VALUE_BOOL},
  {( uint16_t ) offsetof(XtkNavProps, sel), 0u, XTK_PROP_SELECTED_INDEX, 37u, XTK_VALUE_I32},
  {( uint16_t ) offsetof(XtkNavProps, display), 0u, XTK_PROP_DISPLAY_MODE, 38u, XTK_VALUE_ENUM},
  {( uint16_t ) offsetof(XtkNavProps, settings_visible), 0u, XTK_PROP_SETTINGS_VISIBLE, 39u, XTK_VALUE_BOOL},
  {( uint16_t ) offsetof(XtkNavProps, pane_title), ( uint16_t ) offsetof(XtkNavProps, pane_title_len),
   XTK_PROP_PANE_TITLE, 40u, XTK_VALUE_STRING},
  {( uint16_t ) offsetof(XtkNavProps, always_show_header), 0u, XTK_PROP_ALWAYS_SHOW_HEADER, 41u, XTK_VALUE_BOOL},
  {( uint16_t ) offsetof(XtkNavProps, back_button), 0u, XTK_PROP_NAV_BACK_BUTTON, 42u, XTK_VALUE_ENUM},
  {( uint16_t ) offsetof(XtkNavProps, back_enabled), 0u, XTK_PROP_NAV_BACK_ENABLED, 43u, XTK_VALUE_BOOL},
};
XtkCtrlPack const xtk_pack_nav = {
  .fields      = k_fields_nav,
  .a11y_offset = ( uint16_t ) offsetof(XtkNavProps, tip),
  .pre_count   = 8u,
  .field_count = 16u,
  .a11y_bit    = 8u,
  .has_a11y    = 1u,
};
static_assert(
  offsetof(XtkSelectionProps, set) == 0u && offsetof(XtkSelectionProps, stamp) == offsetof(XtkLayoutProps, stamp),
  "header prefix"
);
static_assert(
  offsetof(XtkSelectionProps, acontrols_len) - offsetof(XtkSelectionProps, tip)
    == offsetof(XtkLayoutProps, acontrols_len) - offsetof(XtkLayoutProps, tip),
  "a11y span"
);
static XtkCtrlField const k_fields_selection [11] = {
  {( uint16_t ) offsetof(XtkSelectionProps, w),       0u, XTK_PROP_WIDTH,          0u,  XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkSelectionProps, h),       0u, XTK_PROP_HEIGHT,         1u,  XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkSelectionProps, grow),    0u, XTK_PROP_GROW,           2u,  XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkSelectionProps, self),    0u, XTK_PROP_ALIGN_SELF,     3u,  XTK_VALUE_ENUM},
  {( uint16_t ) offsetof(XtkSelectionProps, ml),      0u, XTK_PROP_MARGIN_LEFT,    4u,  XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkSelectionProps, mt),      0u, XTK_PROP_MARGIN_TOP,     5u,  XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkSelectionProps, mr),      0u, XTK_PROP_MARGIN_RIGHT,   6u,  XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkSelectionProps, mb),      0u, XTK_PROP_MARGIN_BOTTOM,  7u,  XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkSelectionProps, enabled), 0u, XTK_PROP_ENABLED,        36u, XTK_VALUE_BOOL},
  {( uint16_t ) offsetof(XtkSelectionProps, sel),     0u, XTK_PROP_SELECTED_INDEX, 37u, XTK_VALUE_I32 },
  {( uint16_t ) offsetof(XtkSelectionProps, nitem),   0u, XTK_PROP_ITEM_COUNT,     38u, XTK_VALUE_I32 },
};
XtkCtrlPack const xtk_pack_selection = {
  .fields      = k_fields_selection,
  .a11y_offset = ( uint16_t ) offsetof(XtkSelectionProps, tip),
  .pre_count   = 8u,
  .field_count = 11u,
  .a11y_bit    = 8u,
  .has_a11y    = 1u,
};
static_assert(
  offsetof(XtkItemsViewProps, set) == 0u && offsetof(XtkItemsViewProps, stamp) == offsetof(XtkLayoutProps, stamp),
  "header prefix"
);
static_assert(
  offsetof(XtkItemsViewProps, acontrols_len) - offsetof(XtkItemsViewProps, tip)
    == offsetof(XtkLayoutProps, acontrols_len) - offsetof(XtkLayoutProps, tip),
  "a11y span"
);
static XtkCtrlField const k_fields_itemsview [17] = {
  {( uint16_t ) offsetof(XtkItemsViewProps, w),       0u, XTK_PROP_WIDTH,                0u,  XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkItemsViewProps, h),       0u, XTK_PROP_HEIGHT,               1u,  XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkItemsViewProps, grow),    0u, XTK_PROP_GROW,                 2u,  XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkItemsViewProps, self),    0u, XTK_PROP_ALIGN_SELF,           3u,  XTK_VALUE_ENUM},
  {( uint16_t ) offsetof(XtkItemsViewProps, ml),      0u, XTK_PROP_MARGIN_LEFT,          4u,  XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkItemsViewProps, mt),      0u, XTK_PROP_MARGIN_TOP,           5u,  XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkItemsViewProps, mr),      0u, XTK_PROP_MARGIN_RIGHT,         6u,  XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkItemsViewProps, mb),      0u, XTK_PROP_MARGIN_BOTTOM,        7u,  XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkItemsViewProps, enabled), 0u, XTK_PROP_ENABLED,              36u, XTK_VALUE_BOOL},
  {( uint16_t ) offsetof(XtkItemsViewProps, sel),     0u, XTK_PROP_SELECTED_INDEX,       37u, XTK_VALUE_I32 },
  {( uint16_t ) offsetof(XtkItemsViewProps, nitem),   0u, XTK_PROP_ITEM_COUNT,           38u, XTK_VALUE_I32 },
  {( uint16_t ) offsetof(XtkItemsViewProps, itemh),   0u, XTK_PROP_ITEM_HEIGHT,          39u, XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkItemsViewProps, itemw),   0u, XTK_PROP_ITEM_WIDTH,           40u, XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkItemsViewProps, ncol),    0u, XTK_PROP_COLUMN_COUNT,         41u, XTK_VALUE_I32 },
  {( uint16_t ) offsetof(XtkItemsViewProps, mode),    0u, XTK_PROP_SELECTION_MODE,       42u, XTK_VALUE_ENUM},
  {( uint16_t ) offsetof(XtkItemsViewProps, invoked), 0u, XTK_PROP_ITEM_INVOKED_ENABLED, 43u, XTK_VALUE_BOOL},
  {( uint16_t ) offsetof(XtkItemsViewProps, first),   0u, XTK_PROP_REALIZED_FIRST,       44u, XTK_VALUE_I32 },
};
XtkCtrlPack const xtk_pack_itemsview = {
  .fields      = k_fields_itemsview,
  .a11y_offset = ( uint16_t ) offsetof(XtkItemsViewProps, tip),
  .pre_count   = 8u,
  .field_count = 17u,
  .a11y_bit    = 8u,
  .has_a11y    = 1u,
};
static_assert(
  offsetof(XtkFlipProps, set) == 0u && offsetof(XtkFlipProps, stamp) == offsetof(XtkLayoutProps, stamp), "header prefix"
);
static_assert(
  offsetof(XtkFlipProps, acontrols_len) - offsetof(XtkFlipProps, tip)
    == offsetof(XtkLayoutProps, acontrols_len) - offsetof(XtkLayoutProps, tip),
  "a11y span"
);
static XtkCtrlField const k_fields_flip [10] = {
  {( uint16_t ) offsetof(XtkFlipProps, w),    0u, XTK_PROP_WIDTH,          0u,  XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkFlipProps, h),    0u, XTK_PROP_HEIGHT,         1u,  XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkFlipProps, grow), 0u, XTK_PROP_GROW,           2u,  XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkFlipProps, self), 0u, XTK_PROP_ALIGN_SELF,     3u,  XTK_VALUE_ENUM},
  {( uint16_t ) offsetof(XtkFlipProps, ml),   0u, XTK_PROP_MARGIN_LEFT,    4u,  XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkFlipProps, mt),   0u, XTK_PROP_MARGIN_TOP,     5u,  XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkFlipProps, mr),   0u, XTK_PROP_MARGIN_RIGHT,   6u,  XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkFlipProps, mb),   0u, XTK_PROP_MARGIN_BOTTOM,  7u,  XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkFlipProps, sel),  0u, XTK_PROP_SELECTED_INDEX, 36u, XTK_VALUE_I32 },
  {( uint16_t ) offsetof(XtkFlipProps, dir),  0u, XTK_PROP_ORIENTATION,    37u, XTK_VALUE_ENUM},
};
XtkCtrlPack const xtk_pack_flip = {
  .fields      = k_fields_flip,
  .a11y_offset = ( uint16_t ) offsetof(XtkFlipProps, tip),
  .pre_count   = 8u,
  .field_count = 10u,
  .a11y_bit    = 8u,
  .has_a11y    = 1u,
};
static_assert(
  offsetof(XtkPipsProps, set) == 0u && offsetof(XtkPipsProps, stamp) == offsetof(XtkLayoutProps, stamp), "header prefix"
);
static_assert(
  offsetof(XtkPipsProps, acontrols_len) - offsetof(XtkPipsProps, tip)
    == offsetof(XtkLayoutProps, acontrols_len) - offsetof(XtkLayoutProps, tip),
  "a11y span"
);
static XtkCtrlField const k_fields_pips [13] = {
  {( uint16_t ) offsetof(XtkPipsProps, w),          0u, XTK_PROP_WIDTH,          0u,  XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkPipsProps, h),          0u, XTK_PROP_HEIGHT,         1u,  XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkPipsProps, grow),       0u, XTK_PROP_GROW,           2u,  XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkPipsProps, self),       0u, XTK_PROP_ALIGN_SELF,     3u,  XTK_VALUE_ENUM},
  {( uint16_t ) offsetof(XtkPipsProps, ml),         0u, XTK_PROP_MARGIN_LEFT,    4u,  XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkPipsProps, mt),         0u, XTK_PROP_MARGIN_TOP,     5u,  XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkPipsProps, mr),         0u, XTK_PROP_MARGIN_RIGHT,   6u,  XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkPipsProps, mb),         0u, XTK_PROP_MARGIN_BOTTOM,  7u,  XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkPipsProps, sel),        0u, XTK_PROP_SELECTED_INDEX, 36u, XTK_VALUE_I32 },
  {( uint16_t ) offsetof(XtkPipsProps, nitem),      0u, XTK_PROP_ITEM_COUNT,     37u, XTK_VALUE_I32 },
  {( uint16_t ) offsetof(XtkPipsProps, dir),        0u, XTK_PROP_ORIENTATION,    38u, XTK_VALUE_ENUM},
  {( uint16_t ) offsetof(XtkPipsProps, maxvisible), 0u, XTK_PROP_MAX_VISIBLE,    39u, XTK_VALUE_I32 },
  {( uint16_t ) offsetof(XtkPipsProps, nav),        0u, XTK_PROP_NAV_VISIBILITY, 40u, XTK_VALUE_ENUM},
};
XtkCtrlPack const xtk_pack_pips = {
  .fields      = k_fields_pips,
  .a11y_offset = ( uint16_t ) offsetof(XtkPipsProps, tip),
  .pre_count   = 8u,
  .field_count = 13u,
  .a11y_bit    = 8u,
  .has_a11y    = 1u,
};
static_assert(
  offsetof(XtkSuggestProps, set) == 0u && offsetof(XtkSuggestProps, stamp) == offsetof(XtkLayoutProps, stamp),
  "header prefix"
);
static_assert(
  offsetof(XtkSuggestProps, acontrols_len) - offsetof(XtkSuggestProps, tip)
    == offsetof(XtkLayoutProps, acontrols_len) - offsetof(XtkLayoutProps, tip),
  "a11y span"
);
static XtkCtrlField const k_fields_suggest [12] = {
  {( uint16_t ) offsetof(XtkSuggestProps, w), 0u, XTK_PROP_WIDTH, 0u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkSuggestProps, h), 0u, XTK_PROP_HEIGHT, 1u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkSuggestProps, grow), 0u, XTK_PROP_GROW, 2u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkSuggestProps, self), 0u, XTK_PROP_ALIGN_SELF, 3u, XTK_VALUE_ENUM},
  {( uint16_t ) offsetof(XtkSuggestProps, ml), 0u, XTK_PROP_MARGIN_LEFT, 4u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkSuggestProps, mt), 0u, XTK_PROP_MARGIN_TOP, 5u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkSuggestProps, mr), 0u, XTK_PROP_MARGIN_RIGHT, 6u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkSuggestProps, mb), 0u, XTK_PROP_MARGIN_BOTTOM, 7u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkSuggestProps, text), ( uint16_t ) offsetof(XtkSuggestProps, text_len), XTK_PROP_TEXT, 8u,
   XTK_VALUE_STRING},
  {( uint16_t ) offsetof(XtkSuggestProps, enabled), 0u, XTK_PROP_ENABLED, 37u, XTK_VALUE_BOOL},
  {( uint16_t ) offsetof(XtkSuggestProps, placeholder), ( uint16_t ) offsetof(XtkSuggestProps, placeholder_len),
   XTK_PROP_PLACEHOLDER, 38u, XTK_VALUE_STRING},
  {( uint16_t ) offsetof(XtkSuggestProps, icon), ( uint16_t ) offsetof(XtkSuggestProps, icon_len), XTK_PROP_ICON, 39u,
   XTK_VALUE_STRING},
};
XtkCtrlPack const xtk_pack_suggest = {
  .fields      = k_fields_suggest,
  .a11y_offset = ( uint16_t ) offsetof(XtkSuggestProps, tip),
  .pre_count   = 9u,
  .field_count = 12u,
  .a11y_bit    = 9u,
  .has_a11y    = 1u,
};
static_assert(
  offsetof(XtkRadioGroupProps, set) == 0u && offsetof(XtkRadioGroupProps, stamp) == offsetof(XtkLayoutProps, stamp),
  "header prefix"
);
static_assert(
  offsetof(XtkRadioGroupProps, acontrols_len) - offsetof(XtkRadioGroupProps, tip)
    == offsetof(XtkLayoutProps, acontrols_len) - offsetof(XtkLayoutProps, tip),
  "a11y span"
);
static XtkCtrlField const k_fields_radiogroup [12] = {
  {( uint16_t ) offsetof(XtkRadioGroupProps, w),       0u, XTK_PROP_WIDTH,          0u,  XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkRadioGroupProps, h),       0u, XTK_PROP_HEIGHT,         1u,  XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkRadioGroupProps, grow),    0u, XTK_PROP_GROW,           2u,  XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkRadioGroupProps, self),    0u, XTK_PROP_ALIGN_SELF,     3u,  XTK_VALUE_ENUM},
  {( uint16_t ) offsetof(XtkRadioGroupProps, ml),      0u, XTK_PROP_MARGIN_LEFT,    4u,  XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkRadioGroupProps, mt),      0u, XTK_PROP_MARGIN_TOP,     5u,  XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkRadioGroupProps, mr),      0u, XTK_PROP_MARGIN_RIGHT,   6u,  XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkRadioGroupProps, mb),      0u, XTK_PROP_MARGIN_BOTTOM,  7u,  XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkRadioGroupProps, enabled), 0u, XTK_PROP_ENABLED,        36u, XTK_VALUE_BOOL},
  {( uint16_t ) offsetof(XtkRadioGroupProps, sel),     0u, XTK_PROP_SELECTED_INDEX, 37u, XTK_VALUE_I32 },
  {( uint16_t ) offsetof(XtkRadioGroupProps, nitem),   0u, XTK_PROP_ITEM_COUNT,     38u, XTK_VALUE_I32 },
  {( uint16_t ) offsetof(XtkRadioGroupProps, ncol),    0u, XTK_PROP_COLUMN_COUNT,   39u, XTK_VALUE_I32 },
};
XtkCtrlPack const xtk_pack_radiogroup = {
  .fields      = k_fields_radiogroup,
  .a11y_offset = ( uint16_t ) offsetof(XtkRadioGroupProps, tip),
  .pre_count   = 8u,
  .field_count = 12u,
  .a11y_bit    = 8u,
  .has_a11y    = 1u,
};
static_assert(
  offsetof(XtkRatingProps, set) == 0u && offsetof(XtkRatingProps, stamp) == offsetof(XtkLayoutProps, stamp),
  "header prefix"
);
static_assert(
  offsetof(XtkRatingProps, acontrols_len) - offsetof(XtkRatingProps, tip)
    == offsetof(XtkLayoutProps, acontrols_len) - offsetof(XtkLayoutProps, tip),
  "a11y span"
);
static XtkCtrlField const k_fields_rating [16] = {
  {( uint16_t ) offsetof(XtkRatingProps, w), 0u, XTK_PROP_WIDTH, 0u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkRatingProps, h), 0u, XTK_PROP_HEIGHT, 1u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkRatingProps, grow), 0u, XTK_PROP_GROW, 2u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkRatingProps, shrink), 0u, XTK_PROP_SHRINK, 3u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkRatingProps, self), 0u, XTK_PROP_ALIGN_SELF, 4u, XTK_VALUE_ENUM},
  {( uint16_t ) offsetof(XtkRatingProps, ml), 0u, XTK_PROP_MARGIN_LEFT, 5u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkRatingProps, mt), 0u, XTK_PROP_MARGIN_TOP, 6u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkRatingProps, mr), 0u, XTK_PROP_MARGIN_RIGHT, 7u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkRatingProps, mb), 0u, XTK_PROP_MARGIN_BOTTOM, 8u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkRatingProps, value), 0u, XTK_PROP_VALUE_F64, 37u, XTK_VALUE_F64},
  {( uint16_t ) offsetof(XtkRatingProps, max), 0u, XTK_PROP_MAX_F64, 38u, XTK_VALUE_F64},
  {( uint16_t ) offsetof(XtkRatingProps, text), ( uint16_t ) offsetof(XtkRatingProps, text_len), XTK_PROP_TEXT, 39u,
   XTK_VALUE_STRING},
  {( uint16_t ) offsetof(XtkRatingProps, placeholder), 0u, XTK_PROP_PLACEHOLDER_F64, 40u, XTK_VALUE_F64},
  {( uint16_t ) offsetof(XtkRatingProps, initial), 0u, XTK_PROP_INITIAL_VALUE, 41u, XTK_VALUE_I32},
  {( uint16_t ) offsetof(XtkRatingProps, clear), 0u, XTK_PROP_CLEAR_ENABLED, 42u, XTK_VALUE_BOOL},
  {( uint16_t ) offsetof(XtkRatingProps, readonly), 0u, XTK_PROP_READ_ONLY, 43u, XTK_VALUE_BOOL},
};
XtkCtrlPack const xtk_pack_rating = {
  .fields      = k_fields_rating,
  .a11y_offset = ( uint16_t ) offsetof(XtkRatingProps, tip),
  .pre_count   = 9u,
  .field_count = 16u,
  .a11y_bit    = 9u,
  .has_a11y    = 1u,
};
static_assert(
  offsetof(XtkTeachingTipProps, set) == 0u && offsetof(XtkTeachingTipProps, stamp) == offsetof(XtkLayoutProps, stamp),
  "header prefix"
);
static_assert(
  offsetof(XtkTeachingTipProps, acontrols_len) - offsetof(XtkTeachingTipProps, tip)
    == offsetof(XtkLayoutProps, acontrols_len) - offsetof(XtkLayoutProps, tip),
  "a11y span"
);
static XtkCtrlField const k_fields_teachtip [21] = {
  {( uint16_t ) offsetof(XtkTeachingTipProps, w), 0u, XTK_PROP_WIDTH, 0u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkTeachingTipProps, h), 0u, XTK_PROP_HEIGHT, 1u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkTeachingTipProps, grow), 0u, XTK_PROP_GROW, 2u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkTeachingTipProps, shrink), 0u, XTK_PROP_SHRINK, 3u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkTeachingTipProps, self), 0u, XTK_PROP_ALIGN_SELF, 4u, XTK_VALUE_ENUM},
  {( uint16_t ) offsetof(XtkTeachingTipProps, ml), 0u, XTK_PROP_MARGIN_LEFT, 5u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkTeachingTipProps, mt), 0u, XTK_PROP_MARGIN_TOP, 6u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkTeachingTipProps, mr), 0u, XTK_PROP_MARGIN_RIGHT, 7u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkTeachingTipProps, mb), 0u, XTK_PROP_MARGIN_BOTTOM, 8u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkTeachingTipProps, text), ( uint16_t ) offsetof(XtkTeachingTipProps, text_len),
   XTK_PROP_TEXT, 37u, XTK_VALUE_STRING},
  {( uint16_t ) offsetof(XtkTeachingTipProps, subtitle), ( uint16_t ) offsetof(XtkTeachingTipProps, subtitle_len),
   XTK_PROP_SUBTITLE, 38u, XTK_VALUE_STRING},
  {( uint16_t ) offsetof(XtkTeachingTipProps, icon), ( uint16_t ) offsetof(XtkTeachingTipProps, icon_len),
   XTK_PROP_ICON, 39u, XTK_VALUE_STRING},
  {( uint16_t ) offsetof(XtkTeachingTipProps, action), ( uint16_t ) offsetof(XtkTeachingTipProps, action_len),
   XTK_PROP_ACTION_TEXT, 40u, XTK_VALUE_STRING},
  {( uint16_t ) offsetof(XtkTeachingTipProps, actionaccent), 0u, XTK_PROP_ACTION_ACCENT, 41u, XTK_VALUE_BOOL},
  {( uint16_t ) offsetof(XtkTeachingTipProps, close), ( uint16_t ) offsetof(XtkTeachingTipProps, close_len),
   XTK_PROP_CLOSE_TEXT, 42u, XTK_VALUE_STRING},
  {( uint16_t ) offsetof(XtkTeachingTipProps, placement), 0u, XTK_PROP_PLACEMENT, 43u, XTK_VALUE_ENUM},
  {( uint16_t ) offsetof(XtkTeachingTipProps, untargeted), 0u, XTK_PROP_UNTARGETED, 44u, XTK_VALUE_BOOL},
  {( uint16_t ) offsetof(XtkTeachingTipProps, lightdismiss), 0u, XTK_PROP_LIGHT_DISMISS, 45u, XTK_VALUE_BOOL},
  {( uint16_t ) offsetof(XtkTeachingTipProps, tail), 0u, XTK_PROP_TAIL_VISIBILITY, 46u, XTK_VALUE_ENUM},
  {( uint16_t ) offsetof(XtkTeachingTipProps, placementmargin), 0u, XTK_PROP_PLACEMENT_MARGIN, 47u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkTeachingTipProps, open), 0u, XTK_PROP_OPEN, 48u, XTK_VALUE_BOOL},
};
XtkCtrlPack const xtk_pack_teachtip = {
  .fields      = k_fields_teachtip,
  .a11y_offset = ( uint16_t ) offsetof(XtkTeachingTipProps, tip),
  .pre_count   = 9u,
  .field_count = 21u,
  .a11y_bit    = 9u,
  .has_a11y    = 1u,
};
static_assert(
  offsetof(XtkTreeProps, set) == 0u && offsetof(XtkTreeProps, stamp) == offsetof(XtkLayoutProps, stamp), "header prefix"
);
static_assert(
  offsetof(XtkTreeProps, acontrols_len) - offsetof(XtkTreeProps, tip)
    == offsetof(XtkLayoutProps, acontrols_len) - offsetof(XtkLayoutProps, tip),
  "a11y span"
);
static XtkCtrlField const k_fields_tree [12] = {
  {( uint16_t ) offsetof(XtkTreeProps, w),       0u, XTK_PROP_WIDTH,          0u,  XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkTreeProps, h),       0u, XTK_PROP_HEIGHT,         1u,  XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkTreeProps, grow),    0u, XTK_PROP_GROW,           2u,  XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkTreeProps, self),    0u, XTK_PROP_ALIGN_SELF,     3u,  XTK_VALUE_ENUM},
  {( uint16_t ) offsetof(XtkTreeProps, ml),      0u, XTK_PROP_MARGIN_LEFT,    4u,  XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkTreeProps, mt),      0u, XTK_PROP_MARGIN_TOP,     5u,  XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkTreeProps, mr),      0u, XTK_PROP_MARGIN_RIGHT,   6u,  XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkTreeProps, mb),      0u, XTK_PROP_MARGIN_BOTTOM,  7u,  XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkTreeProps, enabled), 0u, XTK_PROP_ENABLED,        36u, XTK_VALUE_BOOL},
  {( uint16_t ) offsetof(XtkTreeProps, sel),     0u, XTK_PROP_SELECTED_INDEX, 37u, XTK_VALUE_I32 },
  {( uint16_t ) offsetof(XtkTreeProps, nitem),   0u, XTK_PROP_ITEM_COUNT,     38u, XTK_VALUE_I32 },
  {( uint16_t ) offsetof(XtkTreeProps, itemh),   0u, XTK_PROP_ITEM_HEIGHT,    39u, XTK_VALUE_F32 },
};
XtkCtrlPack const xtk_pack_tree = {
  .fields      = k_fields_tree,
  .a11y_offset = ( uint16_t ) offsetof(XtkTreeProps, tip),
  .pre_count   = 8u,
  .field_count = 12u,
  .a11y_bit    = 8u,
  .has_a11y    = 1u,
};
static_assert(
  offsetof(XtkRefreshProps, set) == 0u && offsetof(XtkRefreshProps, stamp) == offsetof(XtkLayoutProps, stamp),
  "header prefix"
);
static_assert(
  offsetof(XtkRefreshProps, acontrols_len) - offsetof(XtkRefreshProps, tip)
    == offsetof(XtkLayoutProps, acontrols_len) - offsetof(XtkLayoutProps, tip),
  "a11y span"
);
static XtkCtrlField const k_fields_refresh [12] = {
  {( uint16_t ) offsetof(XtkRefreshProps, w),          0u, XTK_PROP_WIDTH,           0u,  XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkRefreshProps, h),          0u, XTK_PROP_HEIGHT,          1u,  XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkRefreshProps, grow),       0u, XTK_PROP_GROW,            2u,  XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkRefreshProps, self),       0u, XTK_PROP_ALIGN_SELF,      3u,  XTK_VALUE_ENUM},
  {( uint16_t ) offsetof(XtkRefreshProps, ml),         0u, XTK_PROP_MARGIN_LEFT,     4u,  XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkRefreshProps, mt),         0u, XTK_PROP_MARGIN_TOP,      5u,  XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkRefreshProps, mr),         0u, XTK_PROP_MARGIN_RIGHT,    6u,  XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkRefreshProps, mb),         0u, XTK_PROP_MARGIN_BOTTOM,   7u,  XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkRefreshProps, direction),  0u, XTK_PROP_PULL_DIRECTION,  36u, XTK_VALUE_ENUM},
  {( uint16_t ) offsetof(XtkRefreshProps, visualizer), 0u, XTK_PROP_VISUALIZER_SIZE, 37u, XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkRefreshProps, threshold),  0u, XTK_PROP_THRESHOLD_RATIO, 38u, XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkRefreshProps, refreshing), 0u, XTK_PROP_REFRESHING,      39u, XTK_VALUE_BOOL},
};
XtkCtrlPack const xtk_pack_refresh = {
  .fields      = k_fields_refresh,
  .a11y_offset = ( uint16_t ) offsetof(XtkRefreshProps, tip),
  .pre_count   = 8u,
  .field_count = 12u,
  .a11y_bit    = 8u,
  .has_a11y    = 1u,
};
static_assert(
  offsetof(XtkAvatarProps, set) == 0u && offsetof(XtkAvatarProps, stamp) == offsetof(XtkLayoutProps, stamp),
  "header prefix"
);
static_assert(
  offsetof(XtkAvatarProps, acontrols_len) - offsetof(XtkAvatarProps, tip)
    == offsetof(XtkLayoutProps, acontrols_len) - offsetof(XtkLayoutProps, tip),
  "a11y span"
);
static XtkCtrlField const k_fields_avatar [17] = {
  {( uint16_t ) offsetof(XtkAvatarProps, w), 0u, XTK_PROP_WIDTH, 0u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkAvatarProps, h), 0u, XTK_PROP_HEIGHT, 1u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkAvatarProps, grow), 0u, XTK_PROP_GROW, 2u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkAvatarProps, shrink), 0u, XTK_PROP_SHRINK, 3u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkAvatarProps, self), 0u, XTK_PROP_ALIGN_SELF, 4u, XTK_VALUE_ENUM},
  {( uint16_t ) offsetof(XtkAvatarProps, ml), 0u, XTK_PROP_MARGIN_LEFT, 5u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkAvatarProps, mt), 0u, XTK_PROP_MARGIN_TOP, 6u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkAvatarProps, mr), 0u, XTK_PROP_MARGIN_RIGHT, 7u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkAvatarProps, mb), 0u, XTK_PROP_MARGIN_BOTTOM, 8u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkAvatarProps, text), ( uint16_t ) offsetof(XtkAvatarProps, text_len), XTK_PROP_TEXT, 37u,
   XTK_VALUE_STRING},
  {( uint16_t ) offsetof(XtkAvatarProps, initials), ( uint16_t ) offsetof(XtkAvatarProps, initials_len),
   XTK_PROP_INITIALS, 38u, XTK_VALUE_STRING},
  {( uint16_t ) offsetof(XtkAvatarProps, src), 0u, XTK_PROP_IMAGE_SOURCE, 39u, XTK_VALUE_RESOURCE},
  {( uint16_t ) offsetof(XtkAvatarProps, badgeglyph), ( uint16_t ) offsetof(XtkAvatarProps, badgeglyph_len),
   XTK_PROP_BADGE_GLYPH, 40u, XTK_VALUE_STRING},
  {( uint16_t ) offsetof(XtkAvatarProps, badgevalue), 0u, XTK_PROP_BADGE_VALUE, 41u, XTK_VALUE_I32},
  {( uint16_t ) offsetof(XtkAvatarProps, badgeimage), 0u, XTK_PROP_BADGE_IMAGE_SOURCE, 42u, XTK_VALUE_RESOURCE},
  {( uint16_t ) offsetof(XtkAvatarProps, badgetext), ( uint16_t ) offsetof(XtkAvatarProps, badgetext_len),
   XTK_PROP_BADGE_TEXT, 43u, XTK_VALUE_STRING},
  {( uint16_t ) offsetof(XtkAvatarProps, group), 0u, XTK_PROP_IS_GROUP, 44u, XTK_VALUE_BOOL},
};
XtkCtrlPack const xtk_pack_avatar = {
  .fields      = k_fields_avatar,
  .a11y_offset = ( uint16_t ) offsetof(XtkAvatarProps, tip),
  .pre_count   = 9u,
  .field_count = 17u,
  .a11y_bit    = 9u,
  .has_a11y    = 1u,
};
static_assert(
  offsetof(XtkPagerProps, set) == 0u && offsetof(XtkPagerProps, stamp) == offsetof(XtkLayoutProps, stamp),
  "header prefix"
);
static_assert(
  offsetof(XtkPagerProps, acontrols_len) - offsetof(XtkPagerProps, tip)
    == offsetof(XtkLayoutProps, acontrols_len) - offsetof(XtkLayoutProps, tip),
  "a11y span"
);
static XtkCtrlField const k_fields_pager [19] = {
  {( uint16_t ) offsetof(XtkPagerProps, w), 0u, XTK_PROP_WIDTH, 0u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkPagerProps, h), 0u, XTK_PROP_HEIGHT, 1u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkPagerProps, grow), 0u, XTK_PROP_GROW, 2u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkPagerProps, shrink), 0u, XTK_PROP_SHRINK, 3u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkPagerProps, self), 0u, XTK_PROP_ALIGN_SELF, 4u, XTK_VALUE_ENUM},
  {( uint16_t ) offsetof(XtkPagerProps, ml), 0u, XTK_PROP_MARGIN_LEFT, 5u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkPagerProps, mt), 0u, XTK_PROP_MARGIN_TOP, 6u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkPagerProps, mr), 0u, XTK_PROP_MARGIN_RIGHT, 7u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkPagerProps, mb), 0u, XTK_PROP_MARGIN_BOTTOM, 8u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkPagerProps, sel), 0u, XTK_PROP_SELECTED_INDEX, 37u, XTK_VALUE_I32},
  {( uint16_t ) offsetof(XtkPagerProps, nitem), 0u, XTK_PROP_ITEM_COUNT, 38u, XTK_VALUE_I32},
  {( uint16_t ) offsetof(XtkPagerProps, display), 0u, XTK_PROP_DISPLAY_MODE, 39u, XTK_VALUE_ENUM},
  {( uint16_t ) offsetof(XtkPagerProps, first), 0u, XTK_PROP_FIRST_BUTTON, 40u, XTK_VALUE_ENUM},
  {( uint16_t ) offsetof(XtkPagerProps, prev), 0u, XTK_PROP_PREVIOUS_BUTTON, 41u, XTK_VALUE_ENUM},
  {( uint16_t ) offsetof(XtkPagerProps, next), 0u, XTK_PROP_NEXT_BUTTON, 42u, XTK_VALUE_ENUM},
  {( uint16_t ) offsetof(XtkPagerProps, last), 0u, XTK_PROP_LAST_BUTTON, 43u, XTK_VALUE_ENUM},
  {( uint16_t ) offsetof(XtkPagerProps, prefix), ( uint16_t ) offsetof(XtkPagerProps, prefix_len), XTK_PROP_PREFIX, 44u,
   XTK_VALUE_STRING},
  {( uint16_t ) offsetof(XtkPagerProps, suffix), ( uint16_t ) offsetof(XtkPagerProps, suffix_len), XTK_PROP_SUFFIX, 45u,
   XTK_VALUE_STRING},
  {( uint16_t ) offsetof(XtkPagerProps, hideends), 0u, XTK_PROP_HIDE_ENDS, 46u, XTK_VALUE_BOOL},
};
XtkCtrlPack const xtk_pack_pager = {
  .fields      = k_fields_pager,
  .a11y_offset = ( uint16_t ) offsetof(XtkPagerProps, tip),
  .pre_count   = 9u,
  .field_count = 19u,
  .a11y_bit    = 9u,
  .has_a11y    = 1u,
};
static_assert(
  offsetof(XtkSplitViewProps, set) == 0u && offsetof(XtkSplitViewProps, stamp) == offsetof(XtkLayoutProps, stamp),
  "header prefix"
);
static_assert(
  offsetof(XtkSplitViewProps, acontrols_len) - offsetof(XtkSplitViewProps, tip)
    == offsetof(XtkLayoutProps, acontrols_len) - offsetof(XtkLayoutProps, tip),
  "a11y span"
);
static XtkCtrlField const k_fields_splitview [21] = {
  {( uint16_t ) offsetof(XtkSplitViewProps, w),          0u, XTK_PROP_WIDTH,               0u,  XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkSplitViewProps, h),          0u, XTK_PROP_HEIGHT,              1u,  XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkSplitViewProps, grow),       0u, XTK_PROP_GROW,                2u,  XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkSplitViewProps, shrink),     0u, XTK_PROP_SHRINK,              3u,  XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkSplitViewProps, self),       0u, XTK_PROP_ALIGN_SELF,          4u,  XTK_VALUE_ENUM},
  {( uint16_t ) offsetof(XtkSplitViewProps, ml),         0u, XTK_PROP_MARGIN_LEFT,         5u,  XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkSplitViewProps, mt),         0u, XTK_PROP_MARGIN_TOP,          6u,  XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkSplitViewProps, mr),         0u, XTK_PROP_MARGIN_RIGHT,        7u,  XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkSplitViewProps, mb),         0u, XTK_PROP_MARGIN_BOTTOM,       8u,  XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkSplitViewProps, dir),        0u, XTK_PROP_ORIENTATION,         37u, XTK_VALUE_ENUM},
  {( uint16_t ) offsetof(XtkSplitViewProps, gap),        0u, XTK_PROP_GAP,                 38u, XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkSplitViewProps, pl),         0u, XTK_PROP_PADDING_LEFT,        39u, XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkSplitViewProps, pt),         0u, XTK_PROP_PADDING_TOP,         40u, XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkSplitViewProps, pr),         0u, XTK_PROP_PADDING_RIGHT,       41u, XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkSplitViewProps, pb),         0u, XTK_PROP_PADDING_BOTTOM,      42u, XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkSplitViewProps, fill),       0u, XTK_PROP_FILL,                43u, XTK_VALUE_BOOL},
  {( uint16_t ) offsetof(XtkSplitViewProps, open),       0u, XTK_PROP_OPEN,                44u, XTK_VALUE_BOOL},
  {( uint16_t ) offsetof(XtkSplitViewProps, display),    0u, XTK_PROP_DISPLAY_MODE,        45u, XTK_VALUE_ENUM},
  {( uint16_t ) offsetof(XtkSplitViewProps, placement),  0u, XTK_PROP_PANE_PLACEMENT,      46u, XTK_VALUE_ENUM},
  {( uint16_t ) offsetof(XtkSplitViewProps, openlen),    0u, XTK_PROP_OPEN_PANE_LENGTH,    47u, XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkSplitViewProps, compactlen), 0u, XTK_PROP_COMPACT_PANE_LENGTH, 48u, XTK_VALUE_F32 },
};
XtkCtrlPack const xtk_pack_splitview = {
  .fields      = k_fields_splitview,
  .a11y_offset = ( uint16_t ) offsetof(XtkSplitViewProps, tip),
  .pre_count   = 9u,
  .field_count = 21u,
  .a11y_bit    = 9u,
  .has_a11y    = 1u,
};
static_assert(
  offsetof(XtkTitleBarProps, set) == 0u && offsetof(XtkTitleBarProps, stamp) == offsetof(XtkLayoutProps, stamp),
  "header prefix"
);
static_assert(
  offsetof(XtkTitleBarProps, acontrols_len) - offsetof(XtkTitleBarProps, tip)
    == offsetof(XtkLayoutProps, acontrols_len) - offsetof(XtkLayoutProps, tip),
  "a11y span"
);
static XtkCtrlField const k_fields_titlebar [16] = {
  {( uint16_t ) offsetof(XtkTitleBarProps, w), 0u, XTK_PROP_WIDTH, 0u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkTitleBarProps, h), 0u, XTK_PROP_HEIGHT, 1u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkTitleBarProps, grow), 0u, XTK_PROP_GROW, 2u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkTitleBarProps, shrink), 0u, XTK_PROP_SHRINK, 3u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkTitleBarProps, self), 0u, XTK_PROP_ALIGN_SELF, 4u, XTK_VALUE_ENUM},
  {( uint16_t ) offsetof(XtkTitleBarProps, ml), 0u, XTK_PROP_MARGIN_LEFT, 5u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkTitleBarProps, mt), 0u, XTK_PROP_MARGIN_TOP, 6u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkTitleBarProps, mr), 0u, XTK_PROP_MARGIN_RIGHT, 7u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkTitleBarProps, mb), 0u, XTK_PROP_MARGIN_BOTTOM, 8u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkTitleBarProps, text), ( uint16_t ) offsetof(XtkTitleBarProps, text_len), XTK_PROP_TEXT, 37u,
   XTK_VALUE_STRING},
  {( uint16_t ) offsetof(XtkTitleBarProps, subtitle), ( uint16_t ) offsetof(XtkTitleBarProps, subtitle_len),
   XTK_PROP_SUBTITLE, 38u, XTK_VALUE_STRING},
  {( uint16_t ) offsetof(XtkTitleBarProps, icon), ( uint16_t ) offsetof(XtkTitleBarProps, icon_len), XTK_PROP_ICON, 39u,
   XTK_VALUE_STRING},
  {( uint16_t ) offsetof(XtkTitleBarProps, showback), 0u, XTK_PROP_SHOW_BACK, 40u, XTK_VALUE_BOOL},
  {( uint16_t ) offsetof(XtkTitleBarProps, backdisabled), 0u, XTK_PROP_BACK_DISABLED, 41u, XTK_VALUE_BOOL},
  {( uint16_t ) offsetof(XtkTitleBarProps, showtoggle), 0u, XTK_PROP_SHOW_PANE_TOGGLE, 42u, XTK_VALUE_BOOL},
  {( uint16_t ) offsetof(XtkTitleBarProps, integrate), 0u, XTK_PROP_INTEGRATE_WINDOW, 43u, XTK_VALUE_BOOL},
};
XtkCtrlPack const xtk_pack_titlebar = {
  .fields      = k_fields_titlebar,
  .a11y_offset = ( uint16_t ) offsetof(XtkTitleBarProps, tip),
  .pre_count   = 9u,
  .field_count = 16u,
  .a11y_bit    = 9u,
  .has_a11y    = 1u,
};
static_assert(
  offsetof(XtkScrollBarProps, set) == 0u && offsetof(XtkScrollBarProps, stamp) == offsetof(XtkLayoutProps, stamp),
  "header prefix"
);
static_assert(
  offsetof(XtkScrollBarProps, acontrols_len) - offsetof(XtkScrollBarProps, tip)
    == offsetof(XtkLayoutProps, acontrols_len) - offsetof(XtkLayoutProps, tip),
  "a11y span"
);
static XtkCtrlField const k_fields_scrollbar [17] = {
  {( uint16_t ) offsetof(XtkScrollBarProps, w),           0u, XTK_PROP_WIDTH,          0u,  XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkScrollBarProps, h),           0u, XTK_PROP_HEIGHT,         1u,  XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkScrollBarProps, grow),        0u, XTK_PROP_GROW,           2u,  XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkScrollBarProps, self),        0u, XTK_PROP_ALIGN_SELF,     3u,  XTK_VALUE_ENUM},
  {( uint16_t ) offsetof(XtkScrollBarProps, ml),          0u, XTK_PROP_MARGIN_LEFT,    4u,  XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkScrollBarProps, mt),          0u, XTK_PROP_MARGIN_TOP,     5u,  XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkScrollBarProps, mr),          0u, XTK_PROP_MARGIN_RIGHT,   6u,  XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkScrollBarProps, mb),          0u, XTK_PROP_MARGIN_BOTTOM,  7u,  XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkScrollBarProps, enabled),     0u, XTK_PROP_ENABLED,        36u, XTK_VALUE_BOOL},
  {( uint16_t ) offsetof(XtkScrollBarProps, dir),         0u, XTK_PROP_ORIENTATION,    37u, XTK_VALUE_ENUM},
  {( uint16_t ) offsetof(XtkScrollBarProps, min),         0u, XTK_PROP_MIN_F64,        38u, XTK_VALUE_F64 },
  {( uint16_t ) offsetof(XtkScrollBarProps, max),         0u, XTK_PROP_MAX_F64,        39u, XTK_VALUE_F64 },
  {( uint16_t ) offsetof(XtkScrollBarProps, value),       0u, XTK_PROP_VALUE_F64,      40u, XTK_VALUE_F64 },
  {( uint16_t ) offsetof(XtkScrollBarProps, viewport),    0u, XTK_PROP_VIEWPORT_SIZE,  41u, XTK_VALUE_F64 },
  {( uint16_t ) offsetof(XtkScrollBarProps, smallchange), 0u, XTK_PROP_SMALL_CHANGE,   42u, XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkScrollBarProps, largechange), 0u, XTK_PROP_LARGE_CHANGE,   43u, XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkScrollBarProps, indicator),   0u, XTK_PROP_INDICATOR_MODE, 44u, XTK_VALUE_ENUM},
};
XtkCtrlPack const xtk_pack_scrollbar = {
  .fields      = k_fields_scrollbar,
  .a11y_offset = ( uint16_t ) offsetof(XtkScrollBarProps, tip),
  .pre_count   = 8u,
  .field_count = 17u,
  .a11y_bit    = 8u,
  .has_a11y    = 1u,
};
static_assert(
  offsetof(XtkLoopingProps, set) == 0u && offsetof(XtkLoopingProps, stamp) == offsetof(XtkLayoutProps, stamp),
  "header prefix"
);
static_assert(
  offsetof(XtkLoopingProps, acontrols_len) - offsetof(XtkLoopingProps, tip)
    == offsetof(XtkLayoutProps, acontrols_len) - offsetof(XtkLayoutProps, tip),
  "a11y span"
);
static XtkCtrlField const k_fields_looping [14] = {
  {( uint16_t ) offsetof(XtkLoopingProps, w),       0u, XTK_PROP_WIDTH,          0u,  XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkLoopingProps, h),       0u, XTK_PROP_HEIGHT,         1u,  XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkLoopingProps, grow),    0u, XTK_PROP_GROW,           2u,  XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkLoopingProps, self),    0u, XTK_PROP_ALIGN_SELF,     3u,  XTK_VALUE_ENUM},
  {( uint16_t ) offsetof(XtkLoopingProps, ml),      0u, XTK_PROP_MARGIN_LEFT,    4u,  XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkLoopingProps, mt),      0u, XTK_PROP_MARGIN_TOP,     5u,  XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkLoopingProps, mr),      0u, XTK_PROP_MARGIN_RIGHT,   6u,  XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkLoopingProps, mb),      0u, XTK_PROP_MARGIN_BOTTOM,  7u,  XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkLoopingProps, enabled), 0u, XTK_PROP_ENABLED,        36u, XTK_VALUE_BOOL},
  {( uint16_t ) offsetof(XtkLoopingProps, nitem),   0u, XTK_PROP_ITEM_COUNT,     37u, XTK_VALUE_I32 },
  {( uint16_t ) offsetof(XtkLoopingProps, sel),     0u, XTK_PROP_SELECTED_INDEX, 38u, XTK_VALUE_I32 },
  {( uint16_t ) offsetof(XtkLoopingProps, itemh),   0u, XTK_PROP_ITEM_HEIGHT,    39u, XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkLoopingProps, itemw),   0u, XTK_PROP_ITEM_WIDTH,     40u, XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkLoopingProps, loop),    0u, XTK_PROP_SHOULD_LOOP,    41u, XTK_VALUE_BOOL},
};
XtkCtrlPack const xtk_pack_looping = {
  .fields      = k_fields_looping,
  .a11y_offset = ( uint16_t ) offsetof(XtkLoopingProps, tip),
  .pre_count   = 8u,
  .field_count = 14u,
  .a11y_bit    = 8u,
  .has_a11y    = 1u,
};
static_assert(
  offsetof(XtkDatePickerProps, set) == 0u && offsetof(XtkDatePickerProps, stamp) == offsetof(XtkLayoutProps, stamp),
  "header prefix"
);
static_assert(
  offsetof(XtkDatePickerProps, acontrols_len) - offsetof(XtkDatePickerProps, tip)
    == offsetof(XtkLayoutProps, acontrols_len) - offsetof(XtkLayoutProps, tip),
  "a11y span"
);
static XtkCtrlField const k_fields_datepicker [13] = {
  {( uint16_t ) offsetof(XtkDatePickerProps, w), 0u, XTK_PROP_WIDTH, 0u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkDatePickerProps, h), 0u, XTK_PROP_HEIGHT, 1u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkDatePickerProps, grow), 0u, XTK_PROP_GROW, 2u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkDatePickerProps, self), 0u, XTK_PROP_ALIGN_SELF, 3u, XTK_VALUE_ENUM},
  {( uint16_t ) offsetof(XtkDatePickerProps, ml), 0u, XTK_PROP_MARGIN_LEFT, 4u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkDatePickerProps, mt), 0u, XTK_PROP_MARGIN_TOP, 5u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkDatePickerProps, mr), 0u, XTK_PROP_MARGIN_RIGHT, 6u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkDatePickerProps, mb), 0u, XTK_PROP_MARGIN_BOTTOM, 7u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkDatePickerProps, enabled), 0u, XTK_PROP_ENABLED, 36u, XTK_VALUE_BOOL},
  {( uint16_t ) offsetof(XtkDatePickerProps, header), ( uint16_t ) offsetof(XtkDatePickerProps, header_len),
   XTK_PROP_HEADER, 37u, XTK_VALUE_STRING},
  {( uint16_t ) offsetof(XtkDatePickerProps, date), 0u, XTK_PROP_DATE, 38u, XTK_VALUE_I32},
  {( uint16_t ) offsetof(XtkDatePickerProps, minyear), 0u, XTK_PROP_MIN_YEAR, 39u, XTK_VALUE_I32},
  {( uint16_t ) offsetof(XtkDatePickerProps, maxyear), 0u, XTK_PROP_MAX_YEAR, 40u, XTK_VALUE_I32},
};
XtkCtrlPack const xtk_pack_datepicker = {
  .fields      = k_fields_datepicker,
  .a11y_offset = ( uint16_t ) offsetof(XtkDatePickerProps, tip),
  .pre_count   = 8u,
  .field_count = 13u,
  .a11y_bit    = 8u,
  .has_a11y    = 1u,
};
static_assert(
  offsetof(XtkTimePickerProps, set) == 0u && offsetof(XtkTimePickerProps, stamp) == offsetof(XtkLayoutProps, stamp),
  "header prefix"
);
static_assert(
  offsetof(XtkTimePickerProps, acontrols_len) - offsetof(XtkTimePickerProps, tip)
    == offsetof(XtkLayoutProps, acontrols_len) - offsetof(XtkLayoutProps, tip),
  "a11y span"
);
static XtkCtrlField const k_fields_timepicker [13] = {
  {( uint16_t ) offsetof(XtkTimePickerProps, w), 0u, XTK_PROP_WIDTH, 0u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkTimePickerProps, h), 0u, XTK_PROP_HEIGHT, 1u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkTimePickerProps, grow), 0u, XTK_PROP_GROW, 2u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkTimePickerProps, self), 0u, XTK_PROP_ALIGN_SELF, 3u, XTK_VALUE_ENUM},
  {( uint16_t ) offsetof(XtkTimePickerProps, ml), 0u, XTK_PROP_MARGIN_LEFT, 4u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkTimePickerProps, mt), 0u, XTK_PROP_MARGIN_TOP, 5u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkTimePickerProps, mr), 0u, XTK_PROP_MARGIN_RIGHT, 6u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkTimePickerProps, mb), 0u, XTK_PROP_MARGIN_BOTTOM, 7u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkTimePickerProps, enabled), 0u, XTK_PROP_ENABLED, 36u, XTK_VALUE_BOOL},
  {( uint16_t ) offsetof(XtkTimePickerProps, header), ( uint16_t ) offsetof(XtkTimePickerProps, header_len),
   XTK_PROP_HEADER, 37u, XTK_VALUE_STRING},
  {( uint16_t ) offsetof(XtkTimePickerProps, time), 0u, XTK_PROP_TIME, 38u, XTK_VALUE_I32},
  {( uint16_t ) offsetof(XtkTimePickerProps, clock), 0u, XTK_PROP_CLOCK, 39u, XTK_VALUE_ENUM},
  {( uint16_t ) offsetof(XtkTimePickerProps, step), 0u, XTK_PROP_MINUTE_INCREMENT, 40u, XTK_VALUE_I32},
};
XtkCtrlPack const xtk_pack_timepicker = {
  .fields      = k_fields_timepicker,
  .a11y_offset = ( uint16_t ) offsetof(XtkTimePickerProps, tip),
  .pre_count   = 8u,
  .field_count = 13u,
  .a11y_bit    = 8u,
  .has_a11y    = 1u,
};
static_assert(
  offsetof(XtkCalendarProps, set) == 0u && offsetof(XtkCalendarProps, stamp) == offsetof(XtkLayoutProps, stamp),
  "header prefix"
);
static_assert(
  offsetof(XtkCalendarProps, acontrols_len) - offsetof(XtkCalendarProps, tip)
    == offsetof(XtkLayoutProps, acontrols_len) - offsetof(XtkLayoutProps, tip),
  "a11y span"
);
static XtkCtrlField const k_fields_calendar [14] = {
  {( uint16_t ) offsetof(XtkCalendarProps, w),        0u, XTK_PROP_WIDTH,          0u,  XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkCalendarProps, h),        0u, XTK_PROP_HEIGHT,         1u,  XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkCalendarProps, grow),     0u, XTK_PROP_GROW,           2u,  XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkCalendarProps, self),     0u, XTK_PROP_ALIGN_SELF,     3u,  XTK_VALUE_ENUM},
  {( uint16_t ) offsetof(XtkCalendarProps, ml),       0u, XTK_PROP_MARGIN_LEFT,    4u,  XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkCalendarProps, mt),       0u, XTK_PROP_MARGIN_TOP,     5u,  XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkCalendarProps, mr),       0u, XTK_PROP_MARGIN_RIGHT,   6u,  XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkCalendarProps, mb),       0u, XTK_PROP_MARGIN_BOTTOM,  7u,  XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkCalendarProps, enabled),  0u, XTK_PROP_ENABLED,        36u, XTK_VALUE_BOOL},
  {( uint16_t ) offsetof(XtkCalendarProps, date),     0u, XTK_PROP_DATE,           37u, XTK_VALUE_I32 },
  {( uint16_t ) offsetof(XtkCalendarProps, mode),     0u, XTK_PROP_SELECTION_MODE, 38u, XTK_VALUE_ENUM},
  {( uint16_t ) offsetof(XtkCalendarProps, mindate),  0u, XTK_PROP_MIN_DATE,       39u, XTK_VALUE_I32 },
  {( uint16_t ) offsetof(XtkCalendarProps, maxdate),  0u, XTK_PROP_MAX_DATE,       40u, XTK_VALUE_I32 },
  {( uint16_t ) offsetof(XtkCalendarProps, firstday), 0u, XTK_PROP_FIRST_DAY,      41u, XTK_VALUE_I32 },
};
XtkCtrlPack const xtk_pack_calendar = {
  .fields      = k_fields_calendar,
  .a11y_offset = ( uint16_t ) offsetof(XtkCalendarProps, tip),
  .pre_count   = 8u,
  .field_count = 14u,
  .a11y_bit    = 8u,
  .has_a11y    = 1u,
};
static_assert(
  offsetof(XtkColorPickerProps, set) == 0u && offsetof(XtkColorPickerProps, stamp) == offsetof(XtkLayoutProps, stamp),
  "header prefix"
);
static_assert(
  offsetof(XtkColorPickerProps, acontrols_len) - offsetof(XtkColorPickerProps, tip)
    == offsetof(XtkLayoutProps, acontrols_len) - offsetof(XtkLayoutProps, tip),
  "a11y span"
);
static XtkCtrlField const k_fields_colorpicker [13] = {
  {( uint16_t ) offsetof(XtkColorPickerProps, w),          0u, XTK_PROP_WIDTH,               0u,  XTK_VALUE_F32  },
  {( uint16_t ) offsetof(XtkColorPickerProps, h),          0u, XTK_PROP_HEIGHT,              1u,  XTK_VALUE_F32  },
  {( uint16_t ) offsetof(XtkColorPickerProps, grow),       0u, XTK_PROP_GROW,                2u,  XTK_VALUE_F32  },
  {( uint16_t ) offsetof(XtkColorPickerProps, self),       0u, XTK_PROP_ALIGN_SELF,          3u,  XTK_VALUE_ENUM },
  {( uint16_t ) offsetof(XtkColorPickerProps, ml),         0u, XTK_PROP_MARGIN_LEFT,         4u,  XTK_VALUE_F32  },
  {( uint16_t ) offsetof(XtkColorPickerProps, mt),         0u, XTK_PROP_MARGIN_TOP,          5u,  XTK_VALUE_F32  },
  {( uint16_t ) offsetof(XtkColorPickerProps, mr),         0u, XTK_PROP_MARGIN_RIGHT,        6u,  XTK_VALUE_F32  },
  {( uint16_t ) offsetof(XtkColorPickerProps, mb),         0u, XTK_PROP_MARGIN_BOTTOM,       7u,  XTK_VALUE_F32  },
  {( uint16_t ) offsetof(XtkColorPickerProps, enabled),    0u, XTK_PROP_ENABLED,             36u, XTK_VALUE_BOOL },
  {( uint16_t ) offsetof(XtkColorPickerProps, color),      0u, XTK_PROP_COLOR,               37u, XTK_VALUE_COLOR},
  {( uint16_t ) offsetof(XtkColorPickerProps, alpha),      0u, XTK_PROP_ALPHA_ENABLED,       38u, XTK_VALUE_BOOL },
  {( uint16_t ) offsetof(XtkColorPickerProps, morebutton), 0u, XTK_PROP_MORE_BUTTON_VISIBLE, 39u, XTK_VALUE_BOOL },
  {( uint16_t ) offsetof(XtkColorPickerProps, spectrum),   0u, XTK_PROP_SPECTRUM,            40u, XTK_VALUE_ENUM },
};
XtkCtrlPack const xtk_pack_colorpicker = {
  .fields      = k_fields_colorpicker,
  .a11y_offset = ( uint16_t ) offsetof(XtkColorPickerProps, tip),
  .pre_count   = 8u,
  .field_count = 13u,
  .a11y_bit    = 8u,
  .has_a11y    = 1u,
};
static_assert(
  offsetof(XtkColumnProps, set) == 0u && offsetof(XtkColumnProps, stamp) == offsetof(XtkLayoutProps, stamp),
  "header prefix"
);
static_assert(
  offsetof(XtkColumnProps, acontrols_len) - offsetof(XtkColumnProps, tip)
    == offsetof(XtkLayoutProps, acontrols_len) - offsetof(XtkLayoutProps, tip),
  "a11y span"
);
static XtkCtrlField const k_fields_column [8] = {
  {( uint16_t ) offsetof(XtkColumnProps, w), 0u, XTK_PROP_WIDTH, 0u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkColumnProps, minw), 0u, XTK_PROP_MIN_WIDTH, 1u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkColumnProps, maxw), 0u, XTK_PROP_MAX_WIDTH, 2u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkColumnProps, text), ( uint16_t ) offsetof(XtkColumnProps, text_len), XTK_PROP_TEXT, 3u,
   XTK_VALUE_STRING},
  {( uint16_t ) offsetof(XtkColumnProps, align), 0u, XTK_PROP_TEXT_ALIGN, 32u, XTK_VALUE_ENUM},
  {( uint16_t ) offsetof(XtkColumnProps, enabled), 0u, XTK_PROP_ENABLED, 33u, XTK_VALUE_BOOL},
  {( uint16_t ) offsetof(XtkColumnProps, resizable), 0u, XTK_PROP_RESIZABLE, 34u, XTK_VALUE_BOOL},
  {( uint16_t ) offsetof(XtkColumnProps, sort), 0u, XTK_PROP_SORT_DIRECTION, 35u, XTK_VALUE_ENUM},
};
XtkCtrlPack const xtk_pack_column = {
  .fields      = k_fields_column,
  .a11y_offset = ( uint16_t ) offsetof(XtkColumnProps, tip),
  .pre_count   = 4u,
  .field_count = 8u,
  .a11y_bit    = 4u,
  .has_a11y    = 1u,
};
static_assert(
  offsetof(XtkCommandBarProps, set) == 0u && offsetof(XtkCommandBarProps, stamp) == offsetof(XtkLayoutProps, stamp),
  "header prefix"
);
static_assert(
  offsetof(XtkCommandBarProps, acontrols_len) - offsetof(XtkCommandBarProps, tip)
    == offsetof(XtkLayoutProps, acontrols_len) - offsetof(XtkLayoutProps, tip),
  "a11y span"
);
static XtkCtrlField const k_fields_commandbar [15] = {
  {( uint16_t ) offsetof(XtkCommandBarProps, w),       0u, XTK_PROP_WIDTH,                      0u,  XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkCommandBarProps, h),       0u, XTK_PROP_HEIGHT,                     1u,  XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkCommandBarProps, grow),    0u, XTK_PROP_GROW,                       2u,  XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkCommandBarProps, self),    0u, XTK_PROP_ALIGN_SELF,                 3u,  XTK_VALUE_ENUM},
  {( uint16_t ) offsetof(XtkCommandBarProps, ml),      0u, XTK_PROP_MARGIN_LEFT,                4u,  XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkCommandBarProps, mt),      0u, XTK_PROP_MARGIN_TOP,                 5u,  XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkCommandBarProps, mr),      0u, XTK_PROP_MARGIN_RIGHT,               6u,  XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkCommandBarProps, mb),      0u, XTK_PROP_MARGIN_BOTTOM,              7u,  XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkCommandBarProps, enabled), 0u, XTK_PROP_ENABLED,                    36u, XTK_VALUE_BOOL},
  {( uint16_t ) offsetof(XtkCommandBarProps, open),    0u, XTK_PROP_OPEN,                       37u, XTK_VALUE_BOOL},
  {( uint16_t ) offsetof(XtkCommandBarProps, sticky),  0u, XTK_PROP_IS_STICKY,                  38u, XTK_VALUE_BOOL},
  {( uint16_t ) offsetof(XtkCommandBarProps, mode),    0u, XTK_PROP_CLOSED_DISPLAY_MODE,        39u, XTK_VALUE_ENUM},
  {( uint16_t ) offsetof(XtkCommandBarProps, labels),  0u, XTK_PROP_DEFAULT_LABEL_POSITION,     40u, XTK_VALUE_ENUM},
  {( uint16_t ) offsetof(XtkCommandBarProps, more),    0u, XTK_PROP_OVERFLOW_BUTTON_VISIBILITY, 41u, XTK_VALUE_ENUM},
  {( uint16_t ) offsetof(XtkCommandBarProps, dynamic), 0u, XTK_PROP_DYNAMIC_OVERFLOW,           42u, XTK_VALUE_BOOL},
};
XtkCtrlPack const xtk_pack_commandbar = {
  .fields      = k_fields_commandbar,
  .a11y_offset = ( uint16_t ) offsetof(XtkCommandBarProps, tip),
  .pre_count   = 8u,
  .field_count = 15u,
  .a11y_bit    = 8u,
  .has_a11y    = 1u,
};
static_assert(
  offsetof(XtkAppBarButtonProps, set) == 0u && offsetof(XtkAppBarButtonProps, stamp) == offsetof(XtkLayoutProps, stamp),
  "header prefix"
);
static_assert(
  offsetof(XtkAppBarButtonProps, acontrols_len) - offsetof(XtkAppBarButtonProps, tip)
    == offsetof(XtkLayoutProps, acontrols_len) - offsetof(XtkLayoutProps, tip),
  "a11y span"
);
static XtkCtrlField const k_fields_appbarbutton [15] = {
  {( uint16_t ) offsetof(XtkAppBarButtonProps, w), 0u, XTK_PROP_WIDTH, 0u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkAppBarButtonProps, h), 0u, XTK_PROP_HEIGHT, 1u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkAppBarButtonProps, grow), 0u, XTK_PROP_GROW, 2u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkAppBarButtonProps, self), 0u, XTK_PROP_ALIGN_SELF, 3u, XTK_VALUE_ENUM},
  {( uint16_t ) offsetof(XtkAppBarButtonProps, ml), 0u, XTK_PROP_MARGIN_LEFT, 4u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkAppBarButtonProps, mt), 0u, XTK_PROP_MARGIN_TOP, 5u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkAppBarButtonProps, mr), 0u, XTK_PROP_MARGIN_RIGHT, 6u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkAppBarButtonProps, mb), 0u, XTK_PROP_MARGIN_BOTTOM, 7u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkAppBarButtonProps, text), ( uint16_t ) offsetof(XtkAppBarButtonProps, text_len),
   XTK_PROP_TEXT, 36u, XTK_VALUE_STRING},
  {( uint16_t ) offsetof(XtkAppBarButtonProps, icon), ( uint16_t ) offsetof(XtkAppBarButtonProps, icon_len),
   XTK_PROP_ICON, 37u, XTK_VALUE_STRING},
  {( uint16_t ) offsetof(XtkAppBarButtonProps, enabled), 0u, XTK_PROP_ENABLED, 38u, XTK_VALUE_BOOL},
  {( uint16_t ) offsetof(XtkAppBarButtonProps, labelpos), 0u, XTK_PROP_LABEL_POSITION, 39u, XTK_VALUE_ENUM},
  {( uint16_t ) offsetof(XtkAppBarButtonProps, accel), ( uint16_t ) offsetof(XtkAppBarButtonProps, accel_len),
   XTK_PROP_ACCELERATOR_TEXT, 40u, XTK_VALUE_STRING},
  {( uint16_t ) offsetof(XtkAppBarButtonProps, secondary), 0u, XTK_PROP_SECONDARY, 41u, XTK_VALUE_BOOL},
  {( uint16_t ) offsetof(XtkAppBarButtonProps, order), 0u, XTK_PROP_DYNAMIC_OVERFLOW_ORDER, 42u, XTK_VALUE_I32},
};
XtkCtrlPack const xtk_pack_appbarbutton = {
  .fields      = k_fields_appbarbutton,
  .a11y_offset = ( uint16_t ) offsetof(XtkAppBarButtonProps, tip),
  .pre_count   = 8u,
  .field_count = 15u,
  .a11y_bit    = 8u,
  .has_a11y    = 1u,
};
static_assert(
  offsetof(XtkAppBarToggleProps, set) == 0u && offsetof(XtkAppBarToggleProps, stamp) == offsetof(XtkLayoutProps, stamp),
  "header prefix"
);
static_assert(
  offsetof(XtkAppBarToggleProps, acontrols_len) - offsetof(XtkAppBarToggleProps, tip)
    == offsetof(XtkLayoutProps, acontrols_len) - offsetof(XtkLayoutProps, tip),
  "a11y span"
);
static XtkCtrlField const k_fields_appbartoggle [16] = {
  {( uint16_t ) offsetof(XtkAppBarToggleProps, w), 0u, XTK_PROP_WIDTH, 0u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkAppBarToggleProps, h), 0u, XTK_PROP_HEIGHT, 1u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkAppBarToggleProps, grow), 0u, XTK_PROP_GROW, 2u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkAppBarToggleProps, self), 0u, XTK_PROP_ALIGN_SELF, 3u, XTK_VALUE_ENUM},
  {( uint16_t ) offsetof(XtkAppBarToggleProps, ml), 0u, XTK_PROP_MARGIN_LEFT, 4u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkAppBarToggleProps, mt), 0u, XTK_PROP_MARGIN_TOP, 5u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkAppBarToggleProps, mr), 0u, XTK_PROP_MARGIN_RIGHT, 6u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkAppBarToggleProps, mb), 0u, XTK_PROP_MARGIN_BOTTOM, 7u, XTK_VALUE_F32},
  {( uint16_t ) offsetof(XtkAppBarToggleProps, text), ( uint16_t ) offsetof(XtkAppBarToggleProps, text_len),
   XTK_PROP_TEXT, 36u, XTK_VALUE_STRING},
  {( uint16_t ) offsetof(XtkAppBarToggleProps, icon), ( uint16_t ) offsetof(XtkAppBarToggleProps, icon_len),
   XTK_PROP_ICON, 37u, XTK_VALUE_STRING},
  {( uint16_t ) offsetof(XtkAppBarToggleProps, enabled), 0u, XTK_PROP_ENABLED, 38u, XTK_VALUE_BOOL},
  {( uint16_t ) offsetof(XtkAppBarToggleProps, labelpos), 0u, XTK_PROP_LABEL_POSITION, 39u, XTK_VALUE_ENUM},
  {( uint16_t ) offsetof(XtkAppBarToggleProps, accel), ( uint16_t ) offsetof(XtkAppBarToggleProps, accel_len),
   XTK_PROP_ACCELERATOR_TEXT, 40u, XTK_VALUE_STRING},
  {( uint16_t ) offsetof(XtkAppBarToggleProps, checked), 0u, XTK_PROP_CHECKED, 41u, XTK_VALUE_BOOL},
  {( uint16_t ) offsetof(XtkAppBarToggleProps, secondary), 0u, XTK_PROP_SECONDARY, 42u, XTK_VALUE_BOOL},
  {( uint16_t ) offsetof(XtkAppBarToggleProps, order), 0u, XTK_PROP_DYNAMIC_OVERFLOW_ORDER, 43u, XTK_VALUE_I32},
};
XtkCtrlPack const xtk_pack_appbartoggle = {
  .fields      = k_fields_appbartoggle,
  .a11y_offset = ( uint16_t ) offsetof(XtkAppBarToggleProps, tip),
  .pre_count   = 8u,
  .field_count = 16u,
  .a11y_bit    = 8u,
  .has_a11y    = 1u,
};
static_assert(
  offsetof(XtkAppBarSeparatorProps, set) == 0u
    && offsetof(XtkAppBarSeparatorProps, stamp) == offsetof(XtkLayoutProps, stamp),
  "header prefix"
);
static_assert(
  offsetof(XtkAppBarSeparatorProps, acontrols_len) - offsetof(XtkAppBarSeparatorProps, tip)
    == offsetof(XtkLayoutProps, acontrols_len) - offsetof(XtkLayoutProps, tip),
  "a11y span"
);
static XtkCtrlField const k_fields_appbarsep [10] = {
  {( uint16_t ) offsetof(XtkAppBarSeparatorProps, w),         0u, XTK_PROP_WIDTH,                  0u,  XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkAppBarSeparatorProps, h),         0u, XTK_PROP_HEIGHT,                 1u,  XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkAppBarSeparatorProps, grow),      0u, XTK_PROP_GROW,                   2u,  XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkAppBarSeparatorProps, self),      0u, XTK_PROP_ALIGN_SELF,             3u,  XTK_VALUE_ENUM},
  {( uint16_t ) offsetof(XtkAppBarSeparatorProps, ml),        0u, XTK_PROP_MARGIN_LEFT,            4u,  XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkAppBarSeparatorProps, mt),        0u, XTK_PROP_MARGIN_TOP,             5u,  XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkAppBarSeparatorProps, mr),        0u, XTK_PROP_MARGIN_RIGHT,           6u,  XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkAppBarSeparatorProps, mb),        0u, XTK_PROP_MARGIN_BOTTOM,          7u,  XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkAppBarSeparatorProps, secondary), 0u, XTK_PROP_SECONDARY,              36u, XTK_VALUE_BOOL},
  {( uint16_t ) offsetof(XtkAppBarSeparatorProps, order),     0u, XTK_PROP_DYNAMIC_OVERFLOW_ORDER, 37u, XTK_VALUE_I32 },
};
XtkCtrlPack const xtk_pack_appbarsep = {
  .fields      = k_fields_appbarsep,
  .a11y_offset = ( uint16_t ) offsetof(XtkAppBarSeparatorProps, tip),
  .pre_count   = 8u,
  .field_count = 10u,
  .a11y_bit    = 8u,
  .has_a11y    = 1u,
};
static_assert(
  offsetof(XtkNavSlotProps, set) == 0u && offsetof(XtkNavSlotProps, stamp) == offsetof(XtkLayoutProps, stamp),
  "header prefix"
);
static XtkCtrlField const k_fields_navslot [6] = {
  {( uint16_t ) offsetof(XtkNavSlotProps, w),      0u, XTK_PROP_WIDTH,      0u, XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkNavSlotProps, h),      0u, XTK_PROP_HEIGHT,     1u, XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkNavSlotProps, grow),   0u, XTK_PROP_GROW,       2u, XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkNavSlotProps, shrink), 0u, XTK_PROP_SHRINK,     3u, XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkNavSlotProps, self),   0u, XTK_PROP_ALIGN_SELF, 4u, XTK_VALUE_ENUM},
  {( uint16_t ) offsetof(XtkNavSlotProps, slot),   0u, XTK_PROP_NAV_SLOT,   5u, XTK_VALUE_ENUM},
};
XtkCtrlPack const xtk_pack_navslot = {
  .fields      = k_fields_navslot,
  .a11y_offset = 0u,
  .pre_count   = 0u,
  .field_count = 6u,
  .a11y_bit    = 0u,
  .has_a11y    = 0u,
};
static_assert(
  offsetof(XtkFrameProps, set) == 0u && offsetof(XtkFrameProps, stamp) == offsetof(XtkLayoutProps, stamp),
  "header prefix"
);
static XtkCtrlField const k_fields_frame [8] = {
  {( uint16_t ) offsetof(XtkFrameProps, w),          0u, XTK_PROP_WIDTH,            0u, XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkFrameProps, h),          0u, XTK_PROP_HEIGHT,           1u, XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkFrameProps, grow),       0u, XTK_PROP_GROW,             2u, XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkFrameProps, shrink),     0u, XTK_PROP_SHRINK,           3u, XTK_VALUE_F32 },
  {( uint16_t ) offsetof(XtkFrameProps, self),       0u, XTK_PROP_ALIGN_SELF,       4u, XTK_VALUE_ENUM},
  {( uint16_t ) offsetof(XtkFrameProps, transition), 0u, XTK_PROP_FRAME_TRANSITION, 5u, XTK_VALUE_ENUM},
  {( uint16_t ) offsetof(XtkFrameProps, is_back),    0u, XTK_PROP_FRAME_BACK,       6u, XTK_VALUE_BOOL},
  {( uint16_t ) offsetof(XtkFrameProps, page_key),   0u, XTK_PROP_FRAME_PAGE_KEY,   7u, XTK_VALUE_I32 },
};
XtkCtrlPack const xtk_pack_frame = {
  .fields      = k_fields_frame,
  .a11y_offset = 0u,
  .pre_count   = 0u,
  .field_count = 8u,
  .a11y_bit    = 0u,
  .has_a11y    = 0u,
};
