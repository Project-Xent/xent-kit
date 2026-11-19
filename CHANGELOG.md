# Changelog

## 0.3.4 (unreleased)

- the generated Cython stubs (`_controls.pyi`) list the `focus` argument that
  xenthon accepts on every element.

## 0.3.3

- added the column header (`XTK_CTRL_COLHEADER`, `XTK_CTRL_COLITEM`) and
  CommandBar (`XTK_CTRL_COMMANDBAR`, `APPBARBUTTON`, `APPBARTOGGLE`,
  `APPBARSEP`) controls, their properties and events, and the declarative
  `xtk_colheader`, `xtk_colitem`, `xtk_commandbar`, `xtk_appbarbutton`,
  `xtk_appbartoggle`, `xtk_appbarsep`;
- added `XTK_TRIM_PATH_ELLIPSIS`;
- added drag and drop: `DROP_OPERATION`, `DRAG_TEXT`, `DRAG_FILES`, events
  `DRAG_HOVER`, `DROP_FILES`, `DROP_TEXT`, `DRAG_COMPLETED`, and `xtk_dragdrop`;
- added list grouping: `XTK_PROP_GROUPS` (int32 group sizes) on List and
  GridView, the `XTK_CTRL_GROUPHEADER` control, `xtk_list_row` to map a row to
  its group and item, and `XtkListDesc.groups / ngroup / group_header`;
- added `XTK_PROP_RECTANGLE_SELECTION` and `XtkListDesc.rect_select`;
- added `XTK_PROP_NINE_GRID_LEFT/TOP/RIGHT/BOTTOM`, `XtkImageDesc.nine`, and
  the image events `XTK_EVENT_IMAGE_OPENED` / `XTK_EVENT_IMAGE_FAILED`
  (`XtkImageDesc.opened / failed`);
- added `XTK_FONT_INHERIT`; `xtk_text` with `size` 0 or `XTK_FONT_INHERIT`
  inherits from its ancestors;
- widened the declarative binding's user-event mask to 64 bits;

### Breaking changes

| Change | Migration |
| --- | --- |
| `xtk_list`, `xtk_listbox` and `xtk_repeater` default to measured rows (`itemh` 0) instead of 40 px | Set `itemh` to keep fixed-height rows |
| `xtk_text` no longer sends 14 px / regular by default; it inherits | Set `size` or `weight` explicitly |

## 0.3.2

- made `tools/catalog.lua` the single source of the control catalog:
  `xtk_ids.h`, `xtk_catalog.c` and the typed control API are generated from it,
  and enumerated properties carry their value domain, so the typed API takes
  real enum types instead of `uint32_t`;
- added `xmake gen-bindings <rust|zig|cython|haskell|enum-types> <out>`, the
  generator the official language bindings (oxent, zxent, xenthon, hsxent)
  build their control builders from;
- added `XTK_EVENT_REALIZE` (payload `window {first, last, lanes}`) and
  `XTK_PROP_REALIZED_FIRST`: list hosts announce the realized window, and the
  consumer resizes the children and sets the first index in one transaction,
  reusing slots in place. Virtualization is now available to the imperative
  API, not only to the declarative runtime;
- added the change-stamp echo contract: the host stamps each user event with
  `{source, revision}` and records the properties it mirrors
  (`xtk_catalog_mirrors`, at most `XTK_MIRROR_MAX`); a stamped set older than
  the latest user edit of that property is dropped. The declarative runtime
  resends mirrored properties after a user event, so a model that rejects an
  edit pulls the control back;
- added controlled scrolling: `XTK_PROP_SCROLL_X/Y` (NaN leaves an axis
  uncontrolled, +inf pins it to the end as content grows) and
  `XTK_EVENT_SCROLL` (payload `scroll {x, y, max_x, max_y}`);
  `xtk_scroll` takes an `XtkScrollDesc {x, y, scroll}`;
- made `xtk_txn_commit` the only commit path (validate, host preflight,
  prepare, commit) and reported the failing stage in `XtkBatchDiag.stage`;
- added `xtk_txn_beginwith`, which reuses a caller-owned batch so a steady-state
  frame commits without allocating;
- added `xtk_scene_ctrldesc` for querying a host's control descriptors;
- made `XTK_END` a constant address instead of an exported variable;
- routed `xtk_rt` and `gallery_decl` through the public txn/scene/catalog API
  only;
- **Fixed:** result verification read the batch after commit had freed it.

### Breaking changes

| Change | Migration |
|---|---|
| `xtk_scroll(ui, kids)` | `xtk_scroll(ui, (XtkScrollDesc) {.x = NAN, .y = NAN}, kids)` for an uncontrolled viewer |
| `XtkRtCfg.viewport`, `XtkRtCfg.virtual_range`, `XtkViewport`, `XtkVirtualRange` removed | handle `XTK_EVENT_REALIZE`; the host owns the viewport |
| `XtkRtCfg.node_cleanup` removed | — |
| `XtkListDesc.overscan`, `XtkItemsViewDesc.overscan` removed | overscan belongs to the host |
| `XtkListItemDesc.x/y/w/h` removed | items are laid out by the host |
| `XtkStandardPropertyId`, `XtkStandardEventId`, `XtkCtrlType` moved to the generated `xtk_ids.h` | include `xtk/xtk.h` as before; values are unchanged in name |
| typed descriptors use enum types (e.g. `self` is `XentFlexAlign`) | pass the enum constant |
| `extern XtkEl *const XTK_END` became a macro | rebuild; bindings use the value `1` |

## 0.3.1

- added the `SCROLLBAR` control: a scroll bar that owns no content, with the
  range, viewport size and indicator mode a WinUI ScrollBar carries;
- added the `VIEWPORT_SIZE` and `INDICATOR_MODE` properties, and an access role
  for scroll bars;
- added the declarative `xtk_scroll_bar` element, its encoder and its change
  binding;
- added the `LOOPING` and `LOOPITEM` controls: the snapped wheel the date and
  time pickers spin, and the cells it recycles;
- added the `SHOULD_LOOP` property;
- added the declarative `xtk_looping_selector` element, its encoder and its
  selection binding;
- added `MULTILINE` and gave `READ_ONLY` to the TextBox, so a declarative
  field can be a scrolling, read-only, wrapping document;
- added `MAX_LINES`, `TEXT_TRIM`, `TEXT_WRAP` and `SELECTABLE` to static text,
  with the `XtkTextTrim` policies; `XtkTextDesc` gained `max_lines`, `trim`,
  `nowrap` and `selectable`, and `XtkTextBoxDesc` gained `multiline` and
  `readonly`;
- added `checked` to `XtkTreeNodeDesc`, carried by the tree model as
  `XTK_TREE_MODEL_CHECKED`, so a multiple-selection TreeView's checks belong to
  the model and survive an items update; a node with children takes the state
  its children imply;
- changed the TreeView's default row height from 28 to 32, the height WinUI's
  item template produces;
- regenerated the typed control API from the catalog.

### Renamed

Public names now follow `<pkg>_<module>_<verbobject>` with `comp`/`ctrl` abbreviations.

| Old | New |
|---|---|
| `xtk_batch_result_create` | `xtk_batchresult_create` |
| `xtk_batch_result_destroy` | `xtk_batchresult_destroy` |
| `xtk_catalog_control_event` | `xtk_catalog_ctrlevent` |
| `xtk_catalog_control_property` | `xtk_catalog_ctrlprop` |
| `xtk_change_stamp_valid` | `xtk_changestamp_valid` |
| `xtk_ctrl_is_component` | `xtk_ctrl_iscomp` |
| `xtk_is_list_type` | `xtk_ctrl_islist` |
| `xtk_event_phases_valid` | `xtk_event_phasesvalid` |
| `xtk_list_auto_columns` | `xtk_list_autocolumns` |
| `xtk_scene_from_host` | `xtk_scene_fromhost` |
| `xtk_component_*` | xtk_comp_* (e.g. `xtk_component_query_provider` -> `xtk_comp_queryprovider`) |
| `xtk_control_set_{bool,f32,f64,i32,enum,color,string,resource}` | `xtk_ctrl_set{bool,f32,f64,i32,enum,color,string,resource}` |
| `xtk_control_set / xtk_control_get` | xtk_ctrl_set / xtk_ctrl_get |
| `xtk_nav_model_*` | `xtk_navmodel_*` |
| `xtk_tree_model_*` | `xtk_treemodel_*` |
| `xtk_nav_model.h` | `xtk_navmodel.h` |
| `xtk_tree_model.h` | `xtk_treemodel.h` |
| `XTK_PROP_MORE_EXPANDED` (`more-expanded`) | `XTK_PROP_MORE_BUTTON_VISIBLE` (`more-button-visible`): now WinUI's `IsMoreButtonVisible`; whether the text entries are open is internal, as in WinUI |
| `XtkColorPickerProps.more`, `XTK_COLORPICKER_MORE_MASK`, `xtk_colorpicker_setmore`, `XtkColorPickerDesc.more` | `morebutton`, `XTK_COLORPICKER_MOREBUTTON_MASK`, `xtk_colorpicker_setmorebutton`, `XtkColorPickerDesc.morebutton` |

### Changed

- the TextBox has its own property group: `xtk_textbox_create` takes
  `XtkTextBoxProps` (masks `XTK_TEXTBOX_*`) instead of `XtkInputProps`, which
  the PasswordBox keeps.

### Removed

- removed `xtk_cells` (`xtk_cells.h`): restricted Component-owned leaf-property cells.
- removed `trace_id` from `XtkMsg` and `XtkEvent`; it only carried fluxent's navigation trace, which is gone.
- removed `placeholder` from the DatePicker and TimePicker (`XtkDatePickerProps` / `XtkTimePickerProps`, `XtkDatePickerDesc` / `XtkTimePickerDesc`, `xtk_datepicker_setplaceholder`, `xtk_timepicker_setplaceholder`, `XTK_DATEPICKER_PLACEHOLDER_MASK`, `XTK_TIMEPICKER_PLACEHOLDER_MASK`). WinUI has no PlaceholderText on these controls: with no value each column shows its own name. The presence-mask bits after it moved down by one.

## 0.3.0

- introduced the standard retained Host and validated atomic `XtkBatch`
  protocol;
- generated typed imperative controls from the same catalog used by the
  declarative encoder and Host;
- made reconciliation transactional and O(n) for positional and keyed
  children, with retained-capacity reuse and ordered moves;
- added allocation-free scalar keys, static and revisioned regions, and a
  control-neutral virtualization seam;
- added normalized event routing, bounded message queues, and source/revision
  stamps;
- added transactional Components and typed Scene-scoped Providers;
- removed the old backend mutation vtable and custom-control escape hatch.
