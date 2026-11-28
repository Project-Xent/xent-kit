local catalog = import("catalog", {rootdir = os.scriptdir()}).get()

local function join(lines) return table.concat(lines, "\n") end

local function add(lines, ...)
  for _, line in ipairs({...}) do lines[#lines + 1] = line end
end

local function supports_prop(control, prop) return not prop[4] or prop[4] == control.token end

local function camel(token)
  return (token:gsub("^%l", string.upper):gsub("_(%l)", string.upper))
end

local rust_keywords = {
  ["self"] = true, ["type"] = true, ["loop"] = true, ["move"] = true, ["ref"] = true, ["match"] = true,
  ["mod"] = true, ["use"] = true, ["fn"] = true, ["impl"] = true, ["box"] = true, ["final"] = true,
}

local function rust_ident(name)
  return rust_keywords[name] and (name .. "_") or name
end

local rust_value = {
  bool = {"bool", "Value::Bool(v)"},
  i32 = {"i32", "Value::I32(v)"},
  f32 = {"f32", "Value::F32(v)"},
  f64 = {"f64", "Value::F64(v)"},
  enum = {"u32", "Value::Enum(v)"},
  color = {"u32", "Value::Color(v)"},
  string = {"&str", "Value::Str(v.into())"},
  resource = {"u64", "Value::Resource(v)"},
}

local rust_payload = {
  none = nil,
  bool = {"bool", "Bool"},
  i32 = {"i32", "I32"},
  f32 = {"f32", "F32"},
  f64 = {"f64", "F64"},
  string = {"String", "Str"},
  query = {"String, i32", "Query"},
  rating = {"f64, i32", "Rating"},
  index_bool = {"i32, bool", "IndexBool"},
  range = {"f32, f32", "Range"},
  scroll = {"ScrollPos", "Scroll"},
}

local function event_method(def)
  return rust_ident((def.token:gsub("^on", "on_")))
end

local function enum_name(c_name) return (c_name:gsub("^Xtk", ""):gsub("^Xent", "")) end

local function variant(member)
  local digits, rest = member:match("^(%d+)(.*)$")
  if digits then member = rest .. digits end
  return (member:lower():gsub("^%l", string.upper):gsub("_(%w)", string.upper))
end

local function sorted_enums()
  local names = {}
  for name in pairs(catalog.enums) do names[#names + 1] = name end
  table.sort(names)
  return names
end

local function rust_enum(c_name)
  local def = catalog.enums[c_name]
  local lines = {
    "#[repr(u32)]",
    "#[derive(Clone, Copy, Debug, PartialEq, Eq, Hash)]",
    "pub enum " .. enum_name(c_name) .. " {",
  }
  for _, member in ipairs(def.members) do
    add(lines, "    " .. variant(member) .. " = sys::" .. def.prefix .. member .. " as u32,")
  end
  add(lines, "}")
  return join(lines)
end

local function rust_prop(lines, prop)
  if prop.values then
    add(lines,
      "    pub fn " .. rust_ident(prop[1]) .. "(self, v: " .. enum_name(prop.values) .. ") -> Self {",
      "        self.0.prop(sys::" .. prop[2] .. ", Value::Enum(v as u32));",
      "        self",
      "    }")
    return
  end
  local spec = assert(rust_value[prop[3]], prop[3])
  add(lines,
    "    pub fn " .. rust_ident(prop[1]) .. "(self, v: " .. spec[1] .. ") -> Self {",
    "        self.0.prop(sys::" .. prop[2] .. ", " .. spec[2] .. ");",
    "        self",
    "    }")
end

local function rust_event(lines, def)
  if def.payload == "window" then return end
  local payload = rust_payload[def.payload]
  if not payload then
    add(lines,
      "    pub fn " .. event_method(def) .. "(self, msg: A::Msg) -> Self {",
      "        self.0.on(sys::" .. def.id .. ", Handler::Value(msg));",
      "        self",
      "    }")
    return
  end
  add(lines,
    "    pub fn " .. event_method(def) .. "(self, f: fn(" .. payload[1] .. ") -> A::Msg) -> Self {",
    "        self.0.on(sys::" .. def.id .. ", Handler::" .. payload[2] .. "(f));",
    "        self",
    "    }")
end

local function rust_control(control)
  local name = camel(control.token)
  local lines = {
    "pub struct " .. name .. "<'ui, A: App>(pub(crate) El<'ui, A>);",
    "",
    "impl<'ui, A: App> Ui<'ui, A> {",
    "    pub fn " .. rust_ident(control.token) .. "(&'ui self) -> " .. name .. "<'ui, A> {",
    "        " .. name .. "(self.el(sys::XTK_CTRL_" .. control.token:upper() .. ", &raw const sys::flux_ctrl_" .. control.token .. "))",
    "    }",
    "}",
    "",
    "impl<'ui, A: App> " .. name .. "<'ui, A> {",
    "    pub fn key(self, key: u64) -> Self {",
    "        self.0.key(key);",
    "        self",
    "    }",
    "    pub fn child(self, child: impl Into<El<'ui, A>>) -> Self {",
    "        self.0.child(child.into());",
    "        self",
    "    }",
    "    pub fn children<I: IntoIterator<Item = El<'ui, A>>>(self, kids: I) -> Self {",
    "        for kid in kids {",
    "            self.0.child(kid);",
    "        }",
    "        self",
    "    }",
  }
  if control.group then
    for _, prop in ipairs(catalog.props[control.group]) do
      if supports_prop(control, prop) then rust_prop(lines, prop) end
    end
  end
  for _, key in ipairs(control.events) do rust_event(lines, catalog.events[key]) end
  add(lines,
    "}",
    "",
    "impl<'ui, A: App> From<" .. name .. "<'ui, A>> for El<'ui, A> {",
    "    fn from(b: " .. name .. "<'ui, A>) -> Self {",
    "        b.0",
    "    }",
    "}")
  return join(lines)
end

local function rust()
  local chunks = {
    "#![allow(clippy::unnecessary_cast)]",
    "",
    "use crate::{App, El, Handler, ScrollPos, Ui, Value};",
    "use oxent_sys as sys;",
  }
  for _, name in ipairs(sorted_enums()) do add(chunks, "", rust_enum(name)) end
  for _, control in ipairs(catalog.public) do add(chunks, "", rust_control(control)) end
  add(chunks, "")
  return join(chunks)
end

local zig_keywords = {}
for _, word in ipairs({
  "addrspace", "align", "allowzero", "and", "anyframe", "anytype", "asm", "break", "callconv", "catch", "comptime",
  "const", "continue", "defer", "else", "enum", "errdefer", "error", "export", "extern", "fn", "for", "if", "inline",
  "noalias", "nosuspend", "noinline", "opaque", "or", "orelse", "packed", "pub", "resume", "return", "linksection",
  "struct", "suspend", "switch", "test", "threadlocal", "try", "union", "unreachable", "var", "volatile", "while",
}) do zig_keywords[word] = true end

local function zig_ident(name)
  if zig_keywords[name] or not name:match("^[%a_][%w_]*$") then return '@"' .. name .. '"' end
  return name
end

local function zig_field(member)
  local digits, rest = member:match("^(%d+)(.*)$")
  if digits then member = rest .. digits end
  return zig_ident(member:lower())
end

local function zig_method(token)
  return zig_ident((token:gsub("^on(%l)", function(ch) return "on" .. ch:upper() end)))
end

local zig_value = {
  bool = {"bool", ".{ .bool = v }"},
  i32 = {"i32", ".{ .i32 = v }"},
  f32 = {"f32", ".{ .f32 = v }"},
  f64 = {"f64", ".{ .f64 = v }"},
  color = {"u32", ".{ .color = v }"},
  string = {"[]const u8", ".{ .str = v }"},
  resource = {"u64", ".{ .resource = v }"},
}

local zig_payload = {
  bool = {"bool", "bool"},
  i32 = {"i32", "i32"},
  f32 = {"f32", "f32"},
  f64 = {"f64", "f64"},
  string = {"[]const u8", "str"},
  query = {"[]const u8, i32", "query"},
  rating = {"f64, i32", "rating"},
  index_bool = {"i32, bool", "index_bool"},
  range = {"f32, f32", "range"},
  scroll = {"rt.ScrollPos", "scroll"},
}

local function zig_enum(c_name)
  local def = catalog.enums[c_name]
  local lines = {"pub const " .. enum_name(c_name) .. " = enum(c_int) {"}
  for _, member in ipairs(def.members) do
    add(lines, "    " .. zig_field(member) .. " = c." .. def.prefix .. member .. ",")
  end
  add(lines, "};")
  return join(lines)
end

local function zig_prop(lines, prop)
  local name = zig_ident(prop[1])
  if prop.values then
    add(lines,
      "        pub fn " .. name .. "(b: Self, v: " .. enum_name(prop.values) .. ") Self {",
      "            b.el.prop(c." .. prop[2] .. ", .{ .enumeration = @intCast(@backingInt(v)) });",
      "            return b;",
      "        }")
    return
  end
  local spec = assert(zig_value[prop[3]], prop[3])
  add(lines,
    "        pub fn " .. name .. "(b: Self, v: " .. spec[1] .. ") Self {",
    "            b.el.prop(c." .. prop[2] .. ", " .. spec[2] .. ");",
    "            return b;",
    "        }")
end

local function zig_event(lines, def)
  if def.payload == "window" then return end
  local method = zig_method(def.token)
  local payload = zig_payload[def.payload]
  if not payload then
    add(lines,
      "        pub fn " .. method .. "(b: Self, msg: A.Msg) Self {",
      "            b.el.on(c." .. def.id .. ", .{ .value = msg });",
      "            return b;",
      "        }")
    return
  end
  add(lines,
    "        pub fn " .. method .. "(b: Self, f: *const fn (" .. payload[1] .. ") A.Msg) Self {",
    "            b.el.on(c." .. def.id .. ", .{ ." .. payload[2] .. " = f });",
    "            return b;",
    "        }")
end

local function zig_control(control)
  local name = camel(control.token)
  local lines = {
    "pub fn " .. name .. "(comptime A: type) type {",
    "    return struct {",
    "        el: rt.El(A),",
    "        const Self = @This();",
    "        pub fn key(b: Self, k: u64) Self {",
    "            b.el.key(k);",
    "            return b;",
    "        }",
    "        pub fn child(b: Self, kid: anytype) Self {",
    "            b.el.child(rt.toEl(A, kid));",
    "            return b;",
    "        }",
  }
  if control.group then
    for _, prop in ipairs(catalog.props[control.group]) do
      if supports_prop(control, prop) then zig_prop(lines, prop) end
    end
  end
  for _, key in ipairs(control.events) do
    zig_event(lines, catalog.events[key])
    if key == "realize" then
      add(lines,
        "        pub fn items(b: Self, count: usize, f: rt.ItemFn(A)) Self {",
        "            b.el.items(count, f);",
        "            return b;",
        "        }")
    end
  end
  add(lines,
    "    };",
    "}",
    "",
    "pub fn " .. zig_ident(control.token) .. "(ui: anytype) " .. name .. "(@TypeOf(ui.*).App) {",
    "    return .{ .el = ui.el(c.XTK_CTRL_" .. control.token:upper() .. ", &c.flux_ctrl_" .. control.token .. ") };",
    "}")
  return join(lines)
end

local function zig()
  local chunks = {
    'pub const c = @import("c");',
    'const rt = @import("runtime.zig");',
    "",
    "pub const Ui = rt.Ui;",
    "pub const El = rt.El;",
    "pub const ItemFn = rt.ItemFn;",
    "pub const ScrollPos = rt.ScrollPos;",
    "pub const Value = rt.Value;",
    "pub const Theme = rt.Theme;",
    "pub const Window = rt.Window;",
    "pub const Channel = rt.Channel;",
    "pub const run = rt.run;",
    "pub const app = rt.app;",
    "pub const hot = @import(\"hot.zig\");",
  }
  for _, name in ipairs(sorted_enums()) do add(chunks, "", zig_enum(name)) end
  for _, control in ipairs(catalog.public) do add(chunks, "", zig_control(control)) end
  add(chunks, "")
  return join(chunks)
end

local py_keywords = {}
for _, word in ipairs({
  "False", "None", "True", "and", "as", "assert", "async", "await", "break", "class", "continue", "def", "del",
  "elif", "else", "except", "finally", "for", "from", "global", "if", "import", "in", "is", "lambda", "nonlocal",
  "not", "or", "pass", "raise", "return", "try", "while", "with", "yield",
}) do py_keywords[word] = true end

local function py_ident(name) return py_keywords[name] and (name .. "_") or name end

local function py_member(member)
  local digits, rest = member:match("^(%d+)(.*)$")
  return digits and (rest .. digits) or member
end

local py_kind = {
  bool = {"K_BOOL", "bool"},
  i32 = {"K_I32", "int"},
  f32 = {"K_F32", "float"},
  f64 = {"K_F64", "float"},
  enum = {"K_ENUM", nil},
  color = {"K_COLOR", "int"},
  string = {"K_STRING", "str"},
  resource = {"K_RESOURCE", "int"},
}

local py_payload = {
  none = {"P_NONE", "Msg"},
  bool = {"P_BOOL", "Msg | Callable[[bool], Msg]"},
  i32 = {"P_I32", "Msg | Callable[[int], Msg]"},
  f32 = {"P_F32", "Msg | Callable[[float], Msg]"},
  f64 = {"P_F64", "Msg | Callable[[float], Msg]"},
  string = {"P_STRING", "Msg | Callable[[str], Msg]"},
  query = {"P_QUERY", "Msg | Callable[[str, int], Msg]"},
  rating = {"P_RATING", "Msg | Callable[[float, int], Msg]"},
  index_bool = {"P_INDEX_BOOL", "Msg | Callable[[int, bool], Msg]"},
  range = {"P_RANGE", "Msg | Callable[[float, float], Msg]"},
  scroll = {"P_SCROLL", "Msg | Callable[[ScrollPos], Msg]"},
}

local function py_event_name(def) return py_ident((def.token:gsub("^on", "on_"))) end

local function control_props(control)
  local out = {}
  if control.group then
    for _, prop in ipairs(catalog.props[control.group]) do
      if supports_prop(control, prop) then out[#out + 1] = prop end
    end
  end
  return out
end

local function control_events(control)
  local out = {}
  for _, key in ipairs(control.events) do
    local def = catalog.events[key]
    if def.payload ~= "window" then out[#out + 1] = def end
  end
  return out
end

local function virtualized(control)
  for _, key in ipairs(control.events) do
    if key == "realize" then return true end
  end
  return false
end

local function cython_ids()
  local lines = {'cdef extern from "xtk/xtk.h":', "    enum:"}
  local seen = {}
  local function declare(name)
    if not seen[name] then
      seen[name] = true
      add(lines, "        " .. name)
    end
  end
  for _, control in ipairs(catalog.public) do
    declare("XTK_CTRL_" .. control.token:upper())
    for _, prop in ipairs(control_props(control)) do declare(prop[2]) end
    for _, def in ipairs(control_events(control)) do declare(def.id) end
  end
  for _, name in ipairs(sorted_enums()) do
    local def = catalog.enums[name]
    for _, member in ipairs(def.members) do declare(def.prefix .. member) end
  end
  declare("XTK_CTRL_LISTITEM")
  declare("XTK_PROP_REALIZED_FIRST")
  declare("XTK_PROP_ITEM_COUNT")
  declare("XTK_PROP_ITEM_HEIGHT")
  declare("XTK_PROP_ENABLED")
  declare("XTK_EVENT_REALIZE")
  add(lines, "")
  return join(lines)
end

local function cython_pxi()
  local lines = {}
  for _, name in ipairs(sorted_enums()) do
    local def = catalog.enums[name]
    add(lines, "", "", "class " .. enum_name(name) .. "(IntEnum):")
    for _, member in ipairs(def.members) do
      add(lines, "    " .. py_member(member) .. " = " .. def.prefix .. member)
    end
  end
  add(lines, "", "")
  for _, control in ipairs(catalog.public) do
    local props, events = {}, {}
    for _, prop in ipairs(control_props(control)) do
      props[#props + 1] = string.format('"%s": (%s, %s)', py_ident(prop[1]), prop[2], py_kind[prop[3]][1])
    end
    for _, def in ipairs(control_events(control)) do
      events[#events + 1] = string.format('"%s": (%s, %s)', py_event_name(def), def.id, py_payload[def.payload][1])
    end
    add(lines, string.format("SPEC_%s = Spec(XTK_CTRL_%s, {%s}, {%s}, %s, %s)", control.token:upper(),
      control.token:upper(), table.concat(props, ", "), table.concat(events, ", "),
      virtualized(control) and "True" or "False", control.model and ('"' .. control.model .. '"') or "None"))
  end
  add(lines, "")
  return join(lines)
end

local function cython_py()
  local lines = {"from ._reconcile import el as _el"}
  local specs = {}
  for _, control in ipairs(catalog.public) do specs[#specs + 1] = "SPEC_" .. control.token:upper() end
  add(lines, "from ._reconcile import " .. table.concat(specs, ", "))
  for _, control in ipairs(catalog.public) do
    add(lines, "", "", "def " .. py_ident(control.token) .. "(*children, **kw):",
      "    return _el(SPEC_" .. control.token:upper() .. ", children, kw)")
  end
  add(lines, "")
  return join(lines)
end

local py_models = {
  strings = {"items: Sequence[str] | None = None"},
  names = {"names: Sequence[str] | None = None"},
  tabs = {"items: Sequence[str | tuple[str | None, str]] | None = None"},
  selector = {"items: Sequence[str | tuple[str | None, str] | tuple[str | None, str, bool]] | None = None"},
  nav = {
    "items: Sequence[NavKind | tuple[NavKind, str | None, str | None]] | None = None",
    "titlebar: bool | None = None",
    "title: str | None = None",
  },
}

local function cython_pyi()
  local lines = {
    "from collections.abc import Callable, Sequence",
    "from enum import IntEnum",
    "from typing import Any",
    "",
    "from ._reconcile import El, ScrollPos",
    "",
    "Msg = Any",
  }
  for _, name in ipairs(sorted_enums()) do
    add(lines, "", "", "class " .. enum_name(name) .. "(IntEnum):")
    for _, member in ipairs(catalog.enums[name].members) do add(lines, "    " .. py_member(member) .. ": int") end
  end
  for _, control in ipairs(catalog.public) do
    local params = {"*children: El", "key: int | str | None = None", "focus: bool | int | str | None = None"}
    for _, prop in ipairs(control_props(control)) do
      local ptype = prop.values and enum_name(prop.values) or py_kind[prop[3]][2]
      params[#params + 1] = py_ident(prop[1]) .. ": " .. ptype .. " | None = None"
    end
    for _, def in ipairs(control_events(control)) do
      params[#params + 1] = py_event_name(def) .. ": " .. py_payload[def.payload][2] .. " | None = None"
    end
    if virtualized(control) then
      params[#params + 1] = "items: tuple[int, Callable[[int], El]] | None = None"
    end
    for _, param in ipairs(py_models[control.model] or {}) do params[#params + 1] = param end
    add(lines, "", "", "def " .. py_ident(control.token) .. "(", "    " .. table.concat(params, ",\n    ") .. ",",
      ") -> El: ...")
  end
  add(lines, "")
  return join(lines)
end

local function cython(out)
  io.writefile(path.join(out, "_ids.pxi"), cython_ids())
  io.writefile(path.join(out, "_controls.pxi"), cython_pxi())
  io.writefile(path.join(out, "_controls.py"), cython_py())
  io.writefile(path.join(out, "_controls.pyi"), cython_pyi())
end

local hs_keywords = {}
for _, word in ipairs({
  "case", "class", "data", "default", "deriving", "do", "else", "foreign", "if", "import", "in", "infix", "infixl",
  "infixr", "instance", "let", "module", "newtype", "of", "then", "type", "where", "forall", "mdo", "rec", "proc",
}) do hs_keywords[word] = true end

local function hs_ident(name) return hs_keywords[name] and (name .. "_") or name end

local function hs_tag(control) return camel(control.token) end

local function hs_ctor(c_name, member)
  local digits, rest = member:match("^(%d+)(.*)$")
  if digits then member = rest .. digits end
  return enum_name(c_name) .. variant(member)
end

local hs_kind = {
  bool = {"P.Bool", "VBool"},
  i32 = {"Int32", "VI32"},
  f32 = {"P.Float", "VF32"},
  f64 = {"P.Double", "VF64"},
  color = {"Word32", "VColor"},
  string = {"T.Text", "VStr"},
  resource = {"Word64", "VRes"},
}

local hs_payload = {
  bool = {"P.Bool", "HBool"},
  i32 = {"Int32", "HI32"},
  f32 = {"P.Float", "HF32"},
  f64 = {"P.Double", "HF64"},
  string = {"T.Text", "HStr"},
  query = {"QueryEvent", "HQuery"},
  rating = {"RatingEvent", "HRating"},
  index_bool = {"IndexBoolEvent", "HIndexBool"},
  range = {"RangeEvent", "HRange"},
  scroll = {"ScrollPos", "HScroll"},
}

local function haskell_controls()
  local lines = {
    "{-# LANGUAGE NoImplicitPrelude #-}",
    "",
    "module Xent.Controls where",
    "",
    "#include \"xtk/xtk.h\"",
    "#include \"xtk/xtk_catalog.h\"",
    "",
    "import qualified Prelude as P",
    "import Xent.Runtime (Attr, El, XEnum (..), element)",
  }
  for _, name in ipairs(sorted_enums()) do
    local def = catalog.enums[name]
    local ctors = {}
    for _, member in ipairs(def.members) do ctors[#ctors + 1] = hs_ctor(name, member) end
    add(lines, "", "data " .. enum_name(name), "  = " .. table.concat(ctors, "\n  | "),
      "  deriving (P.Eq, P.Ord, P.Show, P.Enum, P.Bounded)", "",
      "instance XEnum " .. enum_name(name) .. " where")
    for _, member in ipairs(def.members) do
      add(lines, "  toC " .. hs_ctor(name, member) .. " = #{const " .. def.prefix .. member .. "}")
    end
  end
  for _, control in ipairs(catalog.public) do
    local tag = hs_tag(control)
    add(lines, "", "data " .. tag, "",
      hs_ident(control.token) .. " :: [Attr " .. tag .. " msg] -> [El msg] -> El msg",
      hs_ident(control.token) .. " = element #{const XTK_CTRL_" .. control.token:upper() .. "}")
  end
  add(lines, "")
  return join(lines)
end

local function attr_value_type(prop)
  if prop.values then return enum_name(prop.values), "VEnum (toC v)" end
  local spec = hs_kind[prop[3]]
  return spec[1], spec[2] .. " v"
end

local function attr_groups()
  local order, groups = {}, {}
  local function slot(name)
    if not groups[name] then
      groups[name] = {}
      order[#order + 1] = name
    end
    return groups[name]
  end
  for _, control in ipairs(catalog.public) do
    if control.group then
      for _, prop in ipairs(catalog.props[control.group]) do
        if supports_prop(control, prop) then
          local vtype, value = attr_value_type(prop)
          local g = slot(hs_ident(prop[1]))
          g[#g + 1] = {tag = hs_tag(control), vtype = vtype, body = "prop #{const " .. prop[2] .. "} (" .. value .. ")"}
        end
      end
    end
    for _, key in ipairs(control.events) do
      local def = catalog.events[key]
      if def.payload ~= "window" then
        local name = hs_ident((def.token:gsub("^on(%l)", function(ch) return "on" .. ch:upper() end)))
        local payload = hs_payload[def.payload]
        local g = slot(name)
        local event = "#{const " .. def.id .. "}"
        if payload then
          g[#g + 1] = {tag = hs_tag(control), vtype = payload[1], handler = true,
            body = "on " .. event .. " (" .. payload[2] .. " f)"}
        else
          g[#g + 1] = {tag = hs_tag(control), vtype = nil, msg = true, body = "on " .. event .. " (HValue m)"}
        end
      end
    end
  end
  return order, groups
end

local function uniform(group)
  for _, inst in ipairs(group) do
    if inst.vtype ~= group[1].vtype or inst.body ~= group[1].body then return false end
  end
  return true
end

local function method_sig(name, inst, vtype)
  if inst.msg then return name .. " :: msg -> Attr c msg", name .. " m" end
  if inst.handler then return name .. " :: (" .. vtype .. " -> msg) -> Attr c msg", name .. " f" end
  return name .. " :: " .. vtype .. " -> Attr c msg", name .. " v"
end

local function class_name(name) return "Has" .. (name:gsub("_$", ""):gsub("^%l", string.upper)) end

local function haskell_attr()
  local lines = {
    "{-# LANGUAGE NoImplicitPrelude #-}",
    "{-# LANGUAGE TypeFamilies #-}",
    "",
    "module Xent.Attr where",
    "",
    "#include \"xtk/xtk.h\"",
    "",
    "import qualified Prelude as P",
    "import Data.Int (Int32)",
    "import qualified Data.Text as T",
    "import Data.Word (Word32, Word64)",
    "import Xent.Controls",
    "import Xent.Runtime",
  }
  local order, groups = attr_groups()
  for _, name in ipairs(order) do
    local group = groups[name]
    local cls = class_name(name)
    if uniform(group) then
      local sig, head = method_sig(name, group[1], group[1].vtype)
      add(lines, "", "class " .. cls .. " c where", "  " .. sig, "  " .. head .. " = " .. group[1].body)
      for _, inst in ipairs(group) do add(lines, "", "instance " .. cls .. " " .. inst.tag) end
    else
      local family = cls:gsub("^Has", "") .. "V"
      local sig = method_sig(name, group[1], family .. " c")
      add(lines, "", "class " .. cls .. " c where", "  type " .. family .. " c", "  " .. sig)
      for _, inst in ipairs(group) do
        local _, head = method_sig(name, inst, "")
        add(lines, "", "instance " .. cls .. " " .. inst.tag .. " where",
          "  type " .. family .. " " .. inst.tag .. " = " .. (inst.vtype or "()"),
          "  " .. head .. " = " .. inst.body)
      end
    end
  end
  local virtual = {}
  for _, control in ipairs(catalog.public) do
    for _, key in ipairs(control.events) do
      if key == "realize" then virtual[#virtual + 1] = hs_tag(control) end
    end
  end
  add(lines, "", "class HasVirtualItems c where",
    "  virtualItems :: P.Int -> (P.Int -> El msg) -> Attr c msg",
    "  virtualItems = items_")
  for _, tag in ipairs(virtual) do add(lines, "", "instance HasVirtualItems " .. tag) end
  add(lines, "")
  return join(lines)
end

local function haskell(out)
  io.writefile(path.join(out, "Controls.hsc"), haskell_controls())
  io.writefile(path.join(out, "Attr.hsc"), haskell_attr())
end

local function enum_types() return table.concat(sorted_enums(), "|") end

local backends = {rust = rust, zig = zig, ["enum-types"] = enum_types}
local directory_backends = {cython = cython, haskell = haskell}

function main(lang, out)
  if directory_backends[lang] then
    directory_backends[lang](assert(out, "usage: xmake gen-bindings cython|haskell <directory>"))
    print("generated " .. lang .. " bindings for " .. #catalog.public .. " controls: " .. path.absolute(out))
    return
  end
  local backend = assert(backends[lang], "unknown binding language: " .. tostring(lang))
  if not out then
    io.write(backend())
    return
  end
  io.writefile(out, backend())
  print("generated " .. lang .. " bindings for " .. #catalog.public .. " controls: " .. path.absolute(out))
end
