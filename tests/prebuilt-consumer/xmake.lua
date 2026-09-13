-- Minimal SKSE plugin that consumes CommonLib from a PREBUILT bundle (staged by CI
-- into lib/commonlibsse-ng) rather than from source. Building this proves the bundle
-- is consumable: the commonlibsse-ng.plugin rule + transitive deps resolve and the
-- plugin links against the prebuilt static library with no CommonLib recompile.
set_xmakever("3.0.0")
set_project("prebuilt-consumer")
set_arch("x64")
set_languages("c++23")
add_rules("mode.debug", "mode.releasedbg")
set_defaultmode("releasedbg")

-- Match the options the prebuilt library was built with (see
-- lib/commonlibsse-ng/PREBUILT.md). These must be set before includes(). Set the
-- runtime flags explicitly rather than relying on defaults so the test always
-- matches the published "all" contract even if the upstream defaults drift.
set_config("skyrim_se", true)
set_config("skyrim_ae", true)
set_config("skyrim_vr", true)
set_config("rex_ini", true)
set_config("skse_xbyak", true)

includes("lib/commonlibsse-ng")

target("prebuilt-consumer", function()
    add_deps("commonlibsse-ng")
    add_rules("commonlibsse-ng.plugin", {
        name = "prebuilt-consumer",
        author = "ci",
        description = "CommonLib prebuilt-bundle consumption self-test",
    })
    add_files("src/main.cpp")
end)
