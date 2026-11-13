local root = path.absolute(path.join(os.scriptdir(), ".."))
local out_h = path.join(root, "include", "xtk", "xtk_controls.h")
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

local function validate()
  local tokens = {}
  for _, control in ipairs(catalog.controls) do
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
      add(lines, string.format("\t%-14s %s;", catalog.kinds[kind].ctype, name))
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
  local head = "bool xtk_" .. control.token .. "_set" .. name .. "(XtkScene *scene, XtkCtrl control, "
  if kind == "string" then
    return head .. "char const *data, uint32_t len, XtkChangeStamp change);"
  end
  return head .. catalog.kinds[kind].ctype .. " value, XtkChangeStamp change);"
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
  for _, control in ipairs(catalog.controls) do
    add(lines, create_decl(control))
  end
  for _, control in ipairs(catalog.controls) do
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
    head .. catalog.kinds[kind].ctype .. " value, XtkChangeStamp change) {",
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

local function write(pathname, content)
  io.writefile(pathname, content)
  return path.absolute(pathname)
end

local function generate()
  os.mkdir(out_dir)
  local generated = {
    write(out_h, header()),
    write(path.join(out_dir, "xtk_controls_internal.h"), internal_header()),
    write(path.join(out_dir, "xtk_controls_support.c"), support_source()),
  }
  local expected = {}
  for _, pathname in ipairs(generated) do expected[pathname] = true end
  for _, control in ipairs(catalog.controls) do
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
