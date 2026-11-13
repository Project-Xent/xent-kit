# Changelog

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
