set_project("xent-kit")
-- Version from the git tag: release CI injects $XENT_VERSION (tag minus "v").
set_version(os.getenv("XENT_VERSION") or "0.3.0-dev")
set_languages("c23")
add_rules("mode.debug", "mode.release")
set_warnings("all")

local unit_tests = {
    "test_xtk_el",
    "test_xtk_list",
    "test_xtk_batch",
    "test_xtk_alloc_fail",
    "test_xtk_catalog",
    "test_xtk_nav_model",
    "test_xtk_tree_model",
    "test_xtk_event",
    "test_xtk_headers",
    "test_xtk_retained",
    "test_xtk_scene",
    "test_xtk_controls",
    "test_xtk_probe_component",
    "test_xtk_reconcile_txn",
    "test_xtk_regions",
    "test_xtk_cells",
}

-- Tests/benches that link the headless retained host (tests/retained).
local testhost_consumers = {
    test_xtk_alloc_fail = true,
    test_xtk_controls = true,
    test_xtk_list = true,
    test_xtk_probe_component = true,
    test_xtk_reconcile_txn = true,
    test_xtk_regions = true,
    test_xtk_cells = true,
    test_xtk_retained = true,
    test_xtk_scene = true,
}

if is_mode("release") then
    set_optimize("faster")
end

-- Pinned package by default; sibling source when present (local dev).
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
    add_headerfiles("include/xtk/*.h")
    add_files("src/*.c", "src/*/*.c")
target_end()

-- Headless retained host: test/bench fixture only, not part of libxtk.
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

for _, test_name in ipairs(unit_tests) do
    target(test_name)
        set_default(false)
        set_kind("binary")
        add_deps("xtk")
        if testhost_consumers[test_name] then
            add_deps("xtk_testhost")
        end
        add_files("tests/" .. test_name .. ".c")
        add_includedirs("include", "src")
end

task("test")
    set_menu {
        usage = "xmake test",
        description = "Build and run all unit tests.",
    }
    on_run(function ()
        for _, test_name in ipairs(unit_tests) do
            os.exec("xmake build " .. test_name)
            os.exec("xmake run " .. test_name)
        end
    end)

task("gen-controls")
    set_menu {
        usage = "xmake gen-controls",
        description = "Regenerate the typed control API from tools/catalog.lua.",
    }
    on_run(function ()
        os.execv("xmake", {"lua", path.join(os.scriptdir(), "tools", "gen_controls.lua")})
    end)
