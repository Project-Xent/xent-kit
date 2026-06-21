set_project("xent-kit")
set_version("0.1.0")
set_languages("c17")
add_rules("mode.debug", "mode.release")
set_warnings("all")

if is_mode("release") then
    set_optimize("faster")
end

local function xtk_dep(name, url)
    local sibling = path.absolute(path.join(os.scriptdir(), "..", name))
    if os.isdir(sibling) then return sibling end
    local vendor = path.join(os.scriptdir(), ".deps", name)
    if not os.isdir(vendor) then
        print("xent-kit: cloning %s from %s", name, url)
        os.vrunv("git", {"clone", "--depth=1", url, vendor})
    end
    return vendor
end

includes(xtk_dep("xent-core", "https://github.com/Project-Xent/xent-core.git"))

target("xtk")
    set_kind("static")
    add_deps("xent_core")
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
