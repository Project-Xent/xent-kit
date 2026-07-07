set_project("xent-kit")
set_version("0.1.0")
set_languages("c23")
add_rules("mode.debug", "mode.release")
set_warnings("all")

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
    add_files("src/*.c")
target_end()

target("test_xtk_el")
    set_default(false)
    set_kind("binary")
    add_deps("xtk")
    add_files("tests/test_xtk_el.c")
    add_includedirs("include")
target_end()

target("test_xtk_list")
    set_default(false)
    set_kind("binary")
    add_deps("xtk")
    add_files("tests/test_xtk_list.c")
    add_includedirs("include")
target_end()
