local root = path.absolute(path.join(os.scriptdir(), ".."))
local out_h = path.join(root, "include", "xtk", "xtk_controls.h")
local out_ids = path.join(root, "include", "xtk", "xtk_ids.h")
local out_catalog = path.join(root, "src", "xtk_catalog.c")
local out_dir = path.join(root, "src", "controls")
local catalog = import("catalog", {rootdir = os.scriptdir()}).get()

local function join(lines)
  return table.concat(lines, "\n")
end

local function add(lines, ...)
  for _, line in ipairs({...}) do
    lines[#lines + 1] = line
  end
end

local function validate_unique(values, label)
  local seen = {}
  for _, value in ipairs(values) do
    assert(not seen[value], label .. ": duplicate " .. value)
    seen[value] = true
  end
end

local item_models = {strings = "XTK_PROP_ITEMS", names = "XTK_PROP_ITEMS", tabs = "XTK_PROP_ITEMS", selector = "XTK_PROP_ITEMS",
  tree = "XTK_PROP_ITEMS", nav = "XTK_PROP_NAV_MODEL"}

local function validate_model(control)
  local carrier
  for _, id in ipairs(control.extra or {}) do
    if id == "XTK_PROP_ITEMS" or id == "XTK_PROP_NAV_MODEL" then carrier = id end
  end
  assert(not control.model or item_models[control.model], control.token .. ": unknown model " .. tostring(control.model))
  assert(item_models[control.model] == carrier, control.token .. ": model must match its item property")
end

local function validate_catalog()
  local known = {}
  for _, prop in ipairs(catalog.properties) do known[prop[1]] = true end
  for _, control in ipairs(catalog.controls) do
    for _, id in ipairs(control.props or control.extra or {}) do assert(known[id], control.token .. ": " .. id) end
    for _, event in ipairs(control.events or {}) do assert(catalog.events[event], control.token .. ": " .. event) end
    validate_model(control)
  end
  for _, def in ipairs(catalog.event_defs) do
    for _, id in ipairs(def.mirrors) do assert(known[id], def.key .. ": mirror " .. id) end
  end
end

local function validate()
  validate_catalog()
  local tokens = {}
  for _, control in ipairs(catalog.public) do
    tokens[#tokens + 1] = control.token
    local event_tokens = {}
    for _, event in ipairs(control.events) do
      assert(catalog.events[event], control.api .. ": unknown event " .. event)
      event_tokens[#event_tokens + 1] = catalog.events[event].token
    end
    validate_unique(event_tokens, control.api)
  end
  validate_unique(tokens, "controls")
  for _, group in ipairs(catalog.prop_order) do
    local props = assert(catalog.props[group], "missing property group " .. group)
    assert(#props <= 64, group .. ": presence mask exceeds uint64_t")
    local names = {}
    for _, prop in ipairs(props) do
      names[#names + 1] = prop[1]
      assert(catalog.kinds[prop[3]], group .. ": unknown kind " .. prop[3])
      assert((prop[3] == "enum") == (prop.values ~= nil), group .. "." .. prop[1] .. ": enum props need a value domain")
      assert(not prop.values or catalog.enums[prop.values], group .. "." .. prop[1] .. ": unknown enum " .. tostring(prop.values))
    end
    validate_unique(names, group)
  end
end

local function struct_fields(group)
  local lines = {
    "\tuint64_t       set;",
    "\tXtkChangeStamp stamp;",
  }
  for _, prop in ipairs(catalog.props[group]) do
    local name, kind = prop[1], prop[3]
    if kind == "string" then
      add(lines,
        "\tchar const    *" .. name .. ";",
        "\tuint32_t       " .. name .. "_len;")
    else
      add(lines, string.format("\t%-14s %s;", prop.values or catalog.kinds[kind].ctype, name))
    end
  end
  return join(lines)
end

local function props_structs()
  local chunks = {}
  for _, group in ipairs(catalog.prop_order) do
    local lines = {
      "typedef struct " .. catalog.structs[group] .. " {",
      struct_fields(group),
      "} " .. catalog.structs[group] .. ";",
    }
    for bit, prop in ipairs(catalog.props[group]) do
      add(lines, string.format("#define XTK_%s_%s_MASK (1ull << %du)",
        group:upper(), prop[1]:upper(), bit - 1))
    end
    chunks[#chunks + 1] = join(lines)
  end
  return table.concat(chunks, "\n\n")
end

local function create_decl(control)
  local head = "XtkLocalId xtk_" .. control.token .. "_create(XtkTxn *txn, XtkNodeRef parent"
  if control.group then head = head .. ", " .. catalog.structs[control.group] .. " const *props" end
  return head .. ");"
end

local function setter_decl(control, prop)
  local name, kind = prop[1], prop[3]
  local ctype = prop.values or catalog.kinds[kind].ctype
  local head = "bool xtk_" .. control.token .. "_set" .. name .. "(XtkScene *scene, XtkCtrl control, "
  if kind == "string" then
    return head .. "char const *data, uint32_t len, XtkChangeStamp change);"
  end
  return head .. ctype .. " value, XtkChangeStamp change);"
end

local function event_decl(control, event)
  return "XtkSubRef xtk_" .. control.token .. "_" .. catalog.events[event].token
    .. "(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg);"
end

local function supports_prop(control, prop)

  return not prop[4] or prop[4] == control.token
end

local function header()
  local lines = {
    "#ifndef XTK_CONTROLS_H",
    "#define XTK_CONTROLS_H",
    "",
    "#include \"xtk_catalog.h\"",
    "#include \"xtk_scene.h\"",
    "",
    "#include <stdint.h>",
    "",
    props_structs(),
    "",
  }
  for _, control in ipairs(catalog.public) do
    add(lines, create_decl(control))
  end
  for _, control in ipairs(catalog.public) do
    if control.group then
      for _, prop in ipairs(catalog.props[control.group]) do
        if supports_prop(control, prop) then add(lines, setter_decl(control, prop)) end
      end
    end
    for _, event in ipairs(control.events) do add(lines, event_decl(control, event)) end
  end
  add(lines, "", "#endif", "")
  return join(lines)
end

local value_kinds = {
  bool = "XTK_VALUE_BOOL",
  i32 = "XTK_VALUE_I32",
  f32 = "XTK_VALUE_F32",
  f64 = "XTK_VALUE_F64",
  enum = "XTK_VALUE_ENUM",
  color = "XTK_VALUE_COLOR",
  string = "XTK_VALUE_STRING",
  resource = "XTK_VALUE_RESOURCE",
}

local function a11y_template()
  local lay = catalog.props.layout
  local block = {}
  for i = 10, #lay do block[#block + 1] = lay[i] end
  return block
end

local a11y_fields = a11y_template()

local function has_prop_restriction(group)
  for _, prop in ipairs(catalog.props[group]) do
    if prop[4] then return true end
  end
  return false
end

local function pack_key_for(control)
  if not control.group then return nil end
  return has_prop_restriction(control.group) and control.token or control.group
end

local function supported_props(control)
  local list = {}
  for bit, prop in ipairs(catalog.props[control.group]) do
    if supports_prop(control, prop) then
      list[#list + 1] = {bit = bit - 1, prop = prop}
    end
  end
  return list
end

local function find_a11y_run(items)
  local need = #a11y_fields
  for i = 1, #items - need + 1 do
    local ok = true
    for j = 1, need do
      local p, q = items[i + j - 1].prop, a11y_fields[j]
      if p[1] ~= q[1] or p[2] ~= q[2] or p[3] ~= q[3] then
        ok = false
        break
      end
    end
    if ok then
      for j = 2, need do
        if items[i + j - 1].bit ~= items[i].bit + j - 1 then
          ok = false
          break
        end
      end
      if ok then return i, items[i].bit end
    end
  end
  return nil, nil
end

local function collect_packs()
  local list = {}
  local seen = {}
  for _, control in ipairs(catalog.public) do
    local key = pack_key_for(control)
    if key and not seen[key] then
      seen[key] = true
      local items = supported_props(control)
      local a11y_pos, a11y_bit = find_a11y_run(items)
      local fields = {}
      local pre_count = 0
      for i, item in ipairs(items) do
        local in_a11y = a11y_pos and i >= a11y_pos and i < a11y_pos + #a11y_fields
        if not in_a11y then
          fields[#fields + 1] = item
          if a11y_pos and i < a11y_pos then pre_count = pre_count + 1 end
        end
      end
      list[#list + 1] = {
        key = key,
        struct = catalog.structs[control.group],
        fields = fields,
        pre_count = pre_count,
        a11y_bit = a11y_bit or 0,
        has_a11y = a11y_pos ~= nil,
      }
    end
  end
  return list
end

local function create_fn(control)
  local name = "xtk_" .. control.token .. "_create"
  local enum = "XTK_CTRL_" .. control.token:upper()
  if not control.group then
    return join({
      "XtkLocalId " .. name .. "(XtkTxn *txn, XtkNodeRef parent) {",
      "\treturn xtk_txn_create(txn, " .. enum .. ", parent, xtk_ref_none(), NULL, 0u);",
      "}",
    })
  end
  local key = pack_key_for(control)
  return join({
    "XtkLocalId " .. name .. "(XtkTxn *txn, XtkNodeRef parent, "
      .. catalog.structs[control.group] .. " const *props) {",
    "\treturn xtk_controls_create(txn, " .. enum .. ", parent, props, &xtk_pack_" .. key .. ");",
    "}",
  })
end

local function setter_fn(control, prop)
  local name, id, kind = prop[1], prop[2], prop[3]
  local head = "bool xtk_" .. control.token .. "_set" .. name .. "(XtkScene *scene, XtkCtrl control, "
  if kind == "string" then
    return join({
      head .. "char const *data, uint32_t len, XtkChangeStamp change) {",
      "\treturn " .. catalog.kinds[kind].setter .. "(scene, control, " .. id
        .. ", data, xtk_controls_text_len(data, len), change);",
      "}",
    })
  end
  return join({
    head .. (prop.values or catalog.kinds[kind].ctype) .. " value, XtkChangeStamp change) {",
    "\treturn " .. catalog.kinds[kind].setter .. "(scene, control, " .. id .. ", value, change);",
    "}",
  })
end

local function event_fn(control, event)
  local spec = catalog.events[event]
  return join({
    "XtkSubRef xtk_" .. control.token .. "_" .. spec.token
      .. "(XtkTxn *txn, XtkNodeRef target, XtkEventFn fn, void *arg) {",
    "\treturn xtk_txn_on(txn, target, " .. spec.id .. ", XTK_EVENT_PHASE_MASK_TARGET, fn, arg);",
    "}",
  })
end

local function source(control)
  local chunks = {'#include "xtk_controls_internal.h"', "", create_fn(control)}
  if control.group then
    for _, prop in ipairs(catalog.props[control.group]) do
      if supports_prop(control, prop) then add(chunks, "", setter_fn(control, prop)) end
    end
  end
  for _, event in ipairs(control.events) do add(chunks, "", event_fn(control, event)) end
  add(chunks, "")
  return join(chunks)
end

local function internal_header(packs)
  local lines = {
    "#ifndef XTK_CONTROLS_INTERNAL_H",
    "#define XTK_CONTROLS_INTERNAL_H",
    "",
    "#include <xtk/xtk_controls.h>",
    "",
    "typedef struct XtkCtrlField {",
    "\tuint16_t offset;",
    "\tuint16_t len_offset;",
    "\tuint16_t id;",
    "\tuint8_t  bit;",
    "\tuint8_t  kind;",
    "} XtkCtrlField;",
    "",
    "typedef struct XtkCtrlPack {",
    "\tXtkCtrlField const *fields;",
    "\tuint16_t            a11y_offset;",
    "\tuint8_t             pre_count;",
    "\tuint8_t             field_count;",
    "\tuint8_t             a11y_bit;",
    "\tuint8_t             has_a11y;",
    "} XtkCtrlPack;",
    "",
    "uint32_t xtk_controls_text_len(char const *text, uint32_t len);",
    "XtkLocalId xtk_controls_create(",
    "  XtkTxn *txn, XtkCtrlId type, XtkNodeRef parent, void const *props, XtkCtrlPack const *pack",
    ");",
    "",
  }
  for _, pack in ipairs(packs) do
    add(lines, "extern XtkCtrlPack const xtk_pack_" .. pack.key .. ";")
  end
  add(lines, "", "#endif", "")
  return join(lines)
end

local function rel_field_row(struct_name, base_field, bit, prop)
  local name, id, kind = prop[1], prop[2], prop[3]
  local off = "( uint16_t ) (offsetof(" .. struct_name .. ", " .. name .. ") - offsetof(" .. struct_name .. ", " .. base_field .. "))"
  local loff = kind == "string"
    and "( uint16_t ) (offsetof(" .. struct_name .. ", " .. name .. "_len) - offsetof(" .. struct_name .. ", " .. base_field .. "))"
    or "0u"
  return string.format("\t{%s, %s, %s, %du, %s},", off, loff, id, bit, assert(value_kinds[kind]))
end

local function abs_field_row(struct_name, bit, prop)
  local name, id, kind = prop[1], prop[2], prop[3]
  local off = "( uint16_t ) offsetof(" .. struct_name .. ", " .. name .. ")"
  local loff = kind == "string" and "( uint16_t ) offsetof(" .. struct_name .. ", " .. name .. "_len)" or "0u"
  return string.format("\t{%s, %s, %s, %du, %s},", off, loff, id, bit, assert(value_kinds[kind]))
end

local function support_prelude()
  local lines = {
    '#include "xtk_controls_internal.h"',
    "",
    "#include <assert.h>",
    "#include <stddef.h>",
    "#include <string.h>",
    "",
    'static_assert(XTK_PROP_STANDARD_COUNT <= UINT16_MAX, "property id fits uint16_t");',
    'static_assert(XTK_VALUE_BOOL < XTK_VALUE_I32 && XTK_VALUE_I32 < XTK_VALUE_F32 && XTK_VALUE_F32 < XTK_VALUE_F64 && XTK_VALUE_F64 < XTK_VALUE_ENUM, "numeric value kinds contiguous");',
  }
  local enum_names = {}
  for name in pairs(catalog.enums) do enum_names[#enum_names + 1] = name end
  table.sort(enum_names)
  for _, name in ipairs(enum_names) do
    add(lines, string.format('static_assert(sizeof(%s) == sizeof(uint32_t), "enum size fits uint32_t");', name))
  end
  add(lines, "", "static XtkCtrlField const k_a11y_fields [28] = {")
  for j, prop in ipairs(a11y_fields) do
    add(lines, rel_field_row("XtkLayoutProps", "tip", j - 1, prop))
  end
  add(lines, "};")
  return join(lines)
end

local support_helpers = [=[
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

XtkLocalId xtk_controls_create(
  XtkTxn *txn, XtkCtrlId type, XtkNodeRef parent, void const *props, XtkCtrlPack const *pack
) {
	if (!props || !pack) return xtk_txn_create(txn, type, parent, xtk_ref_none(), NULL, 0u);
	uint8_t const *base = ( uint8_t const * ) props;
	uint64_t       set  = 0u;
	memcpy(&set, base, sizeof(set));
	if (set == 0u) return xtk_txn_create(txn, type, parent, xtk_ref_none(), NULL, 0u);

	XtkChangeStamp change = {0};
	memcpy(&change, base + offsetof(XtkLayoutProps, stamp), sizeof(change));

	XtkPropPatch patches [64];
	uint32_t     count = 0u;
	if (pack->pre_count)
		pack_slice(patches, &count, base, set, change, pack->fields, 0u, pack->pre_count, 0u, 0u);
	if (pack->has_a11y)
		pack_slice(
		  patches, &count, base, set, change, k_a11y_fields, 0u, 28u, pack->a11y_offset, pack->a11y_bit
		);
	if (pack->field_count > pack->pre_count)
		pack_slice(patches, &count, base, set, change, pack->fields, pack->pre_count, pack->field_count, 0u, 0u);
	return xtk_txn_create(txn, type, parent, xtk_ref_none(), patches, count);
}
]=]

local function pack_source(pack)
  local lines = {
    string.format('static_assert(offsetof(%s, set) == 0u && offsetof(%s, stamp) == offsetof(XtkLayoutProps, stamp), "header prefix");', pack.struct, pack.struct),
  }
  if pack.has_a11y then
    add(lines, string.format(
      'static_assert(offsetof(%s, acontrols_len) - offsetof(%s, tip) == offsetof(XtkLayoutProps, acontrols_len) - offsetof(XtkLayoutProps, tip), "a11y span");',
      pack.struct, pack.struct))
  end
  local fields_ref = "NULL"
  if #pack.fields > 0 then
    fields_ref = "k_fields_" .. pack.key
    add(lines, "static XtkCtrlField const " .. fields_ref .. " [" .. #pack.fields .. "] = {")
    for _, item in ipairs(pack.fields) do
      add(lines, abs_field_row(pack.struct, item.bit, item.prop))
    end
    add(lines, "};")
  end
  local a11y_off = pack.has_a11y and ("( uint16_t ) offsetof(" .. pack.struct .. ", tip)") or "0u"
  add(lines,
    "XtkCtrlPack const xtk_pack_" .. pack.key .. " = {",
    "\t.fields      = " .. fields_ref .. ",",
    "\t.a11y_offset = " .. a11y_off .. ",",
    "\t.pre_count   = " .. tostring(pack.pre_count) .. "u,",
    "\t.field_count = " .. tostring(#pack.fields) .. "u,",
    "\t.a11y_bit    = " .. tostring(pack.a11y_bit) .. "u,",
    "\t.has_a11y    = " .. (pack.has_a11y and "1u" or "0u") .. ",",
    "};")
  return join(lines)
end

local function support_source(packs)
  local chunks = {support_prelude(), "", support_helpers}
  for _, pack in ipairs(packs) do add(chunks, pack_source(pack)) end
  add(chunks, "")
  return join(chunks)
end

local function enum_block(name, invalid, entries, count)
  local lines = {"typedef enum " .. name, "{", "\t" .. invalid .. " = 0,"}
  for _, entry in ipairs(entries) do add(lines, "\t" .. entry .. ",") end
  add(lines, "\t" .. count .. ",", "} " .. name .. ";")
  return join(lines)
end

local function ctrl_const(control) return "XTK_CTRL_" .. control.token:upper() end

local function ids_header()
  local ctrls, props, events = {}, {}, {}
  for _, control in ipairs(catalog.controls) do ctrls[#ctrls + 1] = ctrl_const(control) end
  for _, prop in ipairs(catalog.properties) do props[#props + 1] = prop[1] end
  for _, def in ipairs(catalog.event_defs) do events[#events + 1] = def.id end
  return join({
    "#ifndef XTK_IDS_H",
    "#define XTK_IDS_H",
    "",
    "#include <assert.h>",
    "",
    enum_block("XtkCtrlType", "XTK_CTRL_INVALID", ctrls, "XTK_CTRL_TYPE_COUNT"),
    "",
    enum_block("XtkStandardPropertyId", "XTK_PROP_INVALID", props, "XTK_PROP_STANDARD_COUNT"),
    "",
    enum_block("XtkStandardEventId", "XTK_EVENT_INVALID", events, "XTK_EVENT_STANDARD_COUNT"),
    "",
    'static_assert(sizeof(XtkCtrlType) == 4, "XtkCtrlType crosses the ABI as int32");',
    'static_assert(sizeof(XtkStandardPropertyId) == 4, "XtkStandardPropertyId crosses the ABI as int32");',
    'static_assert(sizeof(XtkStandardEventId) == 4, "XtkStandardEventId crosses the ABI as int32");',
    "",
    "#endif",
    "",
  })
end

local invalidation = {
  geometry = "GEOMETRY",
  content = "CONTENT",
  state = "STATE",
  tree = "TREE",
  layout = "XTK_INVALIDATE_LAYOUT",
  paint = "XTK_INVALIDATE_PAINT",
  hit_test = "XTK_INVALIDATE_HIT_TEST",
  semantics = "XTK_INVALIDATE_SEMANTICS",
  access = "XTK_INVALIDATE_ACCESS",
  none = "XTK_INVALIDATE_NONE",
}

local common_extra = {
  "XTK_PROP_STYLE_BG",
  "XTK_PROP_STYLE_BORDER",
  "XTK_PROP_STYLE_RADIUS",
  "XTK_PROP_STYLE_BORDER_W",
  "XTK_PROP_STYLE_OPACITY",
  "XTK_PROP_STYLE_TX",
  "XTK_PROP_STYLE_TY",
  "XTK_PROP_STYLE_SX",
  "XTK_PROP_STYLE_SY",
  "XTK_PROP_STYLE_ROTATION",
  "XTK_PROP_MOTION_IMPLICIT",
  "XTK_PROP_MOTION_ENTER_EXIT",
  "XTK_PROP_CONNECTED_KEY",
  "XTK_PROP_CONNECTED_CONFIG",
  "XTK_PROP_CONNECTED_COORD",
}

local function control_props(control)
  if control.internal then return control.props end
  local ids = {}
  if control.group then
    for _, prop in ipairs(catalog.props[control.group]) do
      if supports_prop(control, prop) then ids[#ids + 1] = prop[2] end
    end
  end
  for _, id in ipairs(control.extra or {}) do ids[#ids + 1] = id end
  for _, id in ipairs(common_extra) do ids[#ids + 1] = id end
  return ids
end

local function id_array(ctype, name, ids)
  if #ids == 0 then return nil end
  local lines = {"static " .. ctype .. " const " .. name .. " [] = {"}
  for _, id in ipairs(ids) do add(lines, "  " .. id .. ",") end
  add(lines, "};")
  return join(lines)
end

local function property_rows()
  local lines = {"static XtkPropDesc const properties [XTK_PROP_STANDARD_COUNT] = {"}
  for _, prop in ipairs(catalog.properties) do
    local flags = {}
    for _, key in ipairs(prop[4]) do flags[#flags + 1] = assert(invalidation[key], key) end
    local resource = prop.resource and ("XTK_RESOURCE_TYPE_" .. prop.resource:upper()) or "XTK_RESOURCE_TYPE_INVALID"
    add(lines, string.format('  [%s] = {%s, "%s", XTK_PROP_KIND_%s, 0u, %s, %s},',
      prop[1], prop[1], prop[2], prop[3]:upper(), table.concat(flags, " | "), resource))
  end
  add(lines, "};")
  return join(lines)
end

local function event_rows()
  local lines = {"static XtkEventDesc const events [XTK_EVENT_STANDARD_COUNT] = {"}
  for _, def in ipairs(catalog.event_defs) do
    add(lines, string.format('  [%s] = {%s, "%s", XTK_EVENT_ROUTE_%s, XTK_EVENT_PAYLOAD_%s},',
      def.id, def.id, def.name, def.routing:upper(), def.payload:upper()))
  end
  add(lines, "};")
  return join(lines)
end

local function mirror_rows()
  local lines = {"static XtkPropertyId const mirrors [XTK_EVENT_STANDARD_COUNT][XTK_MIRROR_CANDIDATES] = {"}
  for _, def in ipairs(catalog.event_defs) do
    if #def.mirrors > 0 then add(lines, "  [" .. def.id .. "] = {" .. table.concat(def.mirrors, ", ") .. "},") end
  end
  add(lines, "};")
  return join(lines)
end

local function control_arrays()
  local chunks = {}
  for _, control in ipairs(catalog.controls) do
    local events = {}
    for _, key in ipairs(control.events or {}) do events[#events + 1] = catalog.events[key].id end
    chunks[#chunks + 1] = id_array("XtkPropertyId", control.token .. "_props", control_props(control))
    chunks[#chunks + 1] = id_array("XtkEventId", control.token .. "_events", events)
  end
  return table.concat(chunks, "\n")
end

local function list_ref(name, count)
  if count == 0 then return "NULL, 0u" end
  return name .. ", COUNT_OF(" .. name .. ")"
end

local function control_rows()
  local lines = {"static XtkCtrlDesc const controls [XTK_CTRL_TYPE_COUNT] = {"}
  for _, control in ipairs(catalog.controls) do
    local access = control.access
    add(lines, string.format(
      '  [%s] = {%s, "%s", %s, %s, {XTK_ACCESS_ROLE_%s, %s, %s}, NULL, 0u, TREE, TREE},',
      ctrl_const(control), ctrl_const(control), control.name,
      list_ref(control.token .. "_props", #control_props(control)),
      list_ref(control.token .. "_events", #(control.events or {})),
      access[1]:upper(), tostring(access[2]), tostring(access[3])))
  end
  add(lines, "};")
  return join(lines)
end

local catalog_functions = [=[
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
]=]

local catalog_prelude = [=[
#include <xtk/xtk_catalog.h>

#define COUNT_OF(a)           (( uint32_t ) (sizeof(a) / sizeof((a) [0])))
#define XTK_MIRROR_CANDIDATES 3u
#define GEOMETRY              (XTK_INVALIDATE_LAYOUT | XTK_INVALIDATE_PAINT | XTK_INVALIDATE_HIT_TEST)
#define CONTENT               (XTK_INVALIDATE_LAYOUT | XTK_INVALIDATE_PAINT | XTK_INVALIDATE_SEMANTICS | XTK_INVALIDATE_ACCESS)
#define STATE                 (XTK_INVALIDATE_PAINT | XTK_INVALIDATE_HIT_TEST | XTK_INVALIDATE_SEMANTICS | XTK_INVALIDATE_ACCESS)
#define TREE                  (GEOMETRY | XTK_INVALIDATE_SEMANTICS | XTK_INVALIDATE_ACCESS)
]=]

local function catalog_source()
  return join({
    catalog_prelude,
    property_rows(),
    "",
    event_rows(),
    "",
    mirror_rows(),
    "",
    control_arrays(),
    "",
    control_rows(),
    "",
    catalog_functions,
  })
end

local function write(pathname, content)
  io.writefile(pathname, content)
  return path.absolute(pathname)
end

local function generate()
  os.mkdir(out_dir)
  local packs = collect_packs()
  local generated = {
    write(out_ids, ids_header()),
    write(out_catalog, catalog_source()),
    write(out_h, header()),
    write(path.join(out_dir, "xtk_controls_internal.h"), internal_header(packs)),
    write(path.join(out_dir, "xtk_controls_support.c"), support_source(packs)),
  }
  local expected = {}
  for _, pathname in ipairs(generated) do expected[pathname] = true end
  for _, control in ipairs(catalog.public) do
    local pathname = path.join(out_dir, "xtk_controls_" .. control.token .. ".c")
    local absolute = write(pathname, source(control))
    generated[#generated + 1] = absolute
    expected[absolute] = true
  end
  for _, pathname in ipairs(os.files(path.join(out_dir, "xtk_controls_*.c"))) do
    if not expected[path.absolute(pathname)] then os.rm(pathname) end
  end
  return generated
end

local function format(paths)
  local formatter = os.getenv("CLANG_FORMAT") or "clang-format"
  local version = os.iorunv(formatter, {"--version"})
  local major = tonumber(version:match("version (%d+)%."))
  assert(major and major >= 22, "clang-format 22+ required: " .. version)
  local args = {"--style=file", "-i"}
  for _, pathname in ipairs(paths) do args[#args + 1] = pathname end
  os.execv(formatter, args)
end

validate()
local generated = generate()
format(generated)
print(string.format("generated %d controls from tools/catalog.lua", #catalog.controls))
