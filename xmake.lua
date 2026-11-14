set_project("xent-kit")
set_version(os.getenv("XENT_VERSION") or "0.3.2")
set_languages("c23")
add_rules("mode.debug", "mode.release")
if is_plat("mingw") and is_mode("release") then
    set_symbols("none")
end
set_warnings("all")

if is_mode("release") then
    set_optimize("faster")
end

add_repositories("xent-repo https://github.com/Project-Xent/xent-repo.git")
local dev = os.isdir(path.absolute(path.join(os.scriptdir(), "..", "xent-core")))
if dev then
    includes(path.join(os.scriptdir(), "..", "xent-core"))
else
    add_requires("xent-core")
end

target("xtk")
    set_kind("static")
    if dev then
        add_deps("xent_core")
    else
        add_packages("xent-core")
    end
    add_includedirs("include", { public = true })
    add_includedirs("src", { private = true })
    add_headerfiles("include/(xtk/*.h)")
    add_files("src/*.c", "src/*/*.c")
target_end()

target("xtk_testhost")
    set_default(false)
    set_kind("static")
    add_deps("xtk")
    add_files("tests/retained/*.c")
    add_includedirs("tests/retained", { public = true })
    add_includedirs("src", { private = true })
target_end()

target("bench_xtk_reconcile")
    set_default(false)
    set_kind("binary")
    add_deps("xtk", "xtk_testhost")
    add_files("bench/bench_xtk_reconcile.c")
    add_includedirs("include", "src")

target("bench_xtk_composition")
    set_default(false)
    set_kind("binary")
    add_files("bench/bench_xtk_composition.c", "bench/composition/*.c")
    add_includedirs("bench")

target("bench_xtk_binding")
    set_default(false)
    set_kind("binary")
    add_deps("xtk", "xtk_testhost")
    add_files("bench/bench_xtk_binding.c")
    add_includedirs("include", "src")

target("bench_xtk_workloads")
    set_default(false)
    set_kind("binary")
    add_deps("xtk", "xtk_testhost")
    add_files("bench/bench_xtk_workloads.c")
    add_includedirs("include", "src")

target("test_xtk_alloc_fail")
    set_default(false)
    set_kind("binary")
    add_deps("xtk", "xtk_testhost")
    add_files("tests/test_xtk_alloc_fail.c")
    add_includedirs("src")

task("gen-bindings")
    set_menu {
        usage = "xmake gen-bindings <lang> <output>",
        description = "Generate a typed language binding layer from tools/catalog.lua.",
        options = {
            {nil, "lang", "v", nil, "Binding language: rust, zig, cython, haskell."},
            {nil, "output", "v", nil, "Output file (directory for cython and haskell)."},
        },
    }
    on_run(function ()
        import("core.base.option")
        os.execv("xmake", {"lua", path.join(os.scriptdir(), "tools", "gen_bindings.lua"), option.get("lang"), path.absolute(option.get("output"))})
    end)
task_end()

task("gen-controls")
    set_menu {
        usage = "xmake gen-controls",
        description = "Regenerate the typed control API from tools/catalog.lua.",
    }
    on_run(function ()
        os.execv("xmake", {"lua", path.join(os.scriptdir(), "tools", "gen_controls.lua")})
    end)
