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

local function validate_catalog()
  local known = {}
  for _, prop in ipairs(catalog.properties) do known[prop[1]] = true end
  for _, control in ipairs(catalog.controls) do
    for _, id in ipairs(control.props or control.extra or {}) do assert(known[id], control.token .. ": " .. id) end
    for _, event in ipairs(control.events or {}) do assert(catalog.events[event], control.token .. ": " .. event) end
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

local function append_line(bit, prop)
  local name, id, kind = prop[1], prop[2], prop[3]
  local has = string.format("(props->set >> %du) & 1u", bit)
  if kind == "string" then
    return string.format(
      "\txtk_controls_append_string(patches, &count, %s, %s, props->%s, props->%s_len, change);",
      has, id, name, name)
  end
  return string.format("\txtk_controls_append_%s(patches, &count, %s, %s, props->%s, change);",
    kind, has, id, name)
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
  local props = catalog.props[control.group]
  local lines = {
    "XtkLocalId " .. name .. "(XtkTxn *txn, XtkNodeRef parent, "
      .. catalog.structs[control.group] .. " const *props) {",
    "\tif (!props) return xtk_txn_create(txn, " .. enum .. ", parent, xtk_ref_none(), NULL, 0u);",
    "\tXtkPropPatch patches [" .. #props .. "];",
    "\tuint32_t     count = 0u;",
    "\tXtkChangeStamp change = props->stamp;",
  }
  for bit, prop in ipairs(props) do
    if supports_prop(control, prop) then add(lines, append_line(bit - 1, prop)) end
  end
  add(lines, "\treturn xtk_txn_create(txn, " .. enum .. ", parent, xtk_ref_none(), patches, count);", "}")
  return join(lines)
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

local function internal_header()
  local lines = {
    "#ifndef XTK_CONTROLS_INTERNAL_H",
    "#define XTK_CONTROLS_INTERNAL_H",
    "",
    "#include <xtk/xtk_controls.h>",
    "",
    "uint32_t xtk_controls_text_len(char const *text, uint32_t len);",
  }
  local kinds = {"bool", "i32", "f32", "f64", "enum", "color", "resource"}
  for _, kind in ipairs(kinds) do
    add(lines, "void xtk_controls_append_" .. kind
      .. "(XtkPropPatch *patches, uint32_t *count, bool has, XtkPropertyId id, "
      .. catalog.kinds[kind].ctype .. " value, XtkChangeStamp change);")
  end
  add(lines,
    "void xtk_controls_append_string(",
    "  XtkPropPatch *patches, uint32_t *count, bool has, XtkPropertyId id, char const *text, uint32_t len,",
    "  XtkChangeStamp change",
    ");",
    "",
    "#endif",
    "")
  return join(lines)
end

local function support_source()
  return [=[#include "xtk_controls_internal.h"

#include <string.h>

uint32_t xtk_controls_text_len(char const *text, uint32_t len) {
	if (!text) return 0u;
	return len ? len : ( uint32_t ) strlen(text);
}

#define DEFINE_APPEND(suffix, c_type, wire_kind, field)                                         \
	void xtk_controls_append_##suffix(                                                           \
	  XtkPropPatch *patches, uint32_t *count, bool has, XtkPropertyId id, c_type value,           \
	  XtkChangeStamp change                                                                      \
	) {                                                                                           \
		if (!has) return;                                                                          \
		patches [(*count)++] = (XtkPropPatch) {                                                    \
		  .id = id, .value = {.kind = wire_kind, .u.field = value}, .change = change,              \
		};                                                                                         \
	}

DEFINE_APPEND(bool, bool, XTK_VALUE_BOOL, b)
DEFINE_APPEND(i32, int32_t, XTK_VALUE_I32, i32)
DEFINE_APPEND(f32, float, XTK_VALUE_F32, f32)
DEFINE_APPEND(f64, double, XTK_VALUE_F64, f64)
DEFINE_APPEND(enum, uint32_t, XTK_VALUE_ENUM, u32)
DEFINE_APPEND(color, XtkColor, XTK_VALUE_COLOR, color)
DEFINE_APPEND(resource, XtkResource, XTK_VALUE_RESOURCE, resource)

void xtk_controls_append_string(
  XtkPropPatch *patches, uint32_t *count, bool has, XtkPropertyId id, char const *text, uint32_t len,
  XtkChangeStamp change
) {
	if (!has) return;
	patches [(*count)++] = (XtkPropPatch) {
	  .id = id,
	  .value = {
	    .kind = XTK_VALUE_STRING,
	    .u.string = {.data = ( char * ) text, .len = xtk_controls_text_len(text, len)},
	  },
	  .change = change,
	};
}
]=]
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

local function control_props(control)
  if control.internal then return control.props end
  local ids = {}
  if control.group then
    for _, prop in ipairs(catalog.props[control.group]) do
      if supports_prop(control, prop) then ids[#ids + 1] = prop[2] end
    end
  end
  for _, id in ipairs(control.extra or {}) do ids[#ids + 1] = id end
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
  local generated = {
    write(out_ids, ids_header()),
    write(out_catalog, catalog_source()),
    write(out_h, header()),
    write(path.join(out_dir, "xtk_controls_internal.h"), internal_header()),
    write(path.join(out_dir, "xtk_controls_support.c"), support_source()),
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
