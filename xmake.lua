-- set minimum xmake version
set_xmakever("3.0.0")

-- set project constants
set_project("commonlibsse-ng")
set_arch("x64")
set_languages("c++23")
set_warnings("allextra")
set_encodings("utf-8")

-- add common rules
add_rules("mode.debug", "mode.releasedbg")
add_rules("plugin.vsxmake.autoupdate")

-- add options
option("rex_ini", function()
    set_default(false)
    set_description("Enable ini config support for REX")
    add_defines("REX_OPTION_INI=1")
end)

option("rex_json", function()
    set_default(false)
    set_description("Enable json config support for REX")
    add_defines("REX_OPTION_JSON=1")
end)

option("rex_toml", function()
    set_default(false)
    set_description("Enable toml config support for REX")
    add_defines("REX_OPTION_TOML=1")
end)

option("skyrim_se", function()
    set_default(true)
    set_description("Enable runtime support for Skyrim SE")
    add_defines("ENABLE_SKYRIM_SE=1")
end)

option("skyrim_ae", function()
    set_default(true)
    set_description("Enable runtime support for Skyrim AE")
    add_defines("ENABLE_SKYRIM_AE=1")
end)

option("skyrim_vr", function()
    set_default(true)
    set_description("Enable runtime support for Skyrim VR")
    add_defines("ENABLE_SKYRIM_VR=1")
end)

option("skse_xbyak", function()
    set_default(false)
    set_description("Enable trampoline support for Xbyak")
    add_defines("SKSE_SUPPORT_XBYAK=1")
end)

option("skse_patch_safety", function()
    set_default(true)
    set_description("Enable trampoline patch-site diagnostics")
    add_defines("SKSE_SUPPORT_PATCH_SAFETY=1")
end)

option("tests", function()
    set_default(false)
    set_description("Enable building unit tests")
    add_defines("ENABLE_COMMONLIBSSE_TESTING=1")
end)

-- add packages
add_requires("directxmath 2024.02", "directxtk 24.2.0")
add_requires("spdlog v1.16.0", { configs = { header_only = false, wchar = true, std_format = true } })

if has_config("rex_ini") then
    add_requires("simpleini v4.25")
end

if has_config("rex_json") then
    add_requires("nlohmann_json v3.12.0")
end

if has_config("rex_toml") then
    add_requires("toml11 v4.4.0")
end

if has_config("skse_xbyak") then
    add_requires("xbyak v7.06")
end

if has_config("skyrim_vr") then
    add_requires("rapidcsv v8.92")
end

target("commonlibsse-ng", function()
    -- Prebuilt mode: when a prebuilt `lib/commonlibsse-ng.lib` is available — a bundle
    -- shipped alongside this xmake.lua, or one auto-fetched for a clean release tag — the
    -- target links that static library (phony) instead of compiling src/. Consumers keep
    -- using `includes(...)` + the `commonlibsse-ng.plugin` rule unchanged; the only
    -- difference is zero recompile. The decision is made in on_load (not at parse) so the
    -- network fetch can run and so any failure falls back cleanly to a normal source build.
    -- (A phony target ignores add_files, so the source configuration below is harmless in
    -- prebuilt mode and can stay unconditional.)
    set_kind("static")

    on_load(function(target)
        local scriptdir = target:scriptdir()

        -- Resolve a directory containing a prebuilt lib/commonlibsse-ng.lib:
        --   1. a bundle shipped next to this xmake.lua, or
        --   2. on a CLEAN release tag, in CI (or with COMMONLIB_PREBUILT set), the matching
        --      bundle downloaded from the GitHub release and SHA256-verified.
        -- Anything else (no tag, dirty tree, missing/unverified asset, offline) returns nil
        -- so the target stays a source build. The download runs at most once per tag
        -- (cached under build/.prebuilt/<tag>; a failure is remembered, not retried).
        local function resolve()
            if os.isfile(path.join(scriptdir, "lib", "commonlibsse-ng.lib")) then
                return scriptdir
            end
            if not (os.getenv("GITHUB_ACTIONS") or os.getenv("COMMONLIB_PREBUILT")) then
                return nil
            end
            -- actions/checkout fetches submodules shallow and without tags, so describe can't
            -- see the release tag in CI; pull tags best-effort first (depth 1, ~fast). Still
            -- uses --exact-match, so a non-tag commit safely falls back to a source build.
            try { function() os.iorunv("git", { "-C", scriptdir, "fetch", "--tags", "--depth=1", "origin" }) end }
            local tag = try { function()
                return os.iorunv("git", { "-C", scriptdir, "describe", "--tags", "--exact-match", "--dirty" })
            end }
            if not tag then return nil end
            tag = tag:trim()
            if tag:find("dirty", 1, true) or not tag:match("^v%d") then return nil end

            local cachedir = path.join(scriptdir, "build", ".prebuilt", tag)
            if os.isfile(path.join(cachedir, "lib", "commonlibsse-ng.lib")) then return cachedir end
            if os.isfile(path.join(cachedir, ".failed")) then return nil end

            local got = try { function()
                import("net.http")
                import("utils.archive")
                local base = "https://github.com/alandtse/CommonLibSSE-NG/releases/download/" .. tag
                local asset = "commonlibsse-ng-prebuilt-" .. tag .. "-all-msvc.7z"
                local arch = os.tmpfile() .. ".7z"
                http.download(base .. "/" .. asset, arch)
                local shafile = os.tmpfile()
                http.download(base .. "/" .. asset .. ".sha256", shafile)
                local want = (io.readfile(shafile) or ""):match("%x+")
                assert(want and hash.sha256(arch):lower() == want:lower(), "sha256 verification failed")
                os.mkdir(cachedir)
                archive.extract(arch, cachedir)
                -- the archive has a single top-level folder; surface its lib/ directory
                local found = os.files(path.join(cachedir, "**", "lib", "commonlibsse-ng.lib"))[1]
                return found and path.directory(path.directory(found))
            end }
            if got then return got end
            os.mkdir(cachedir)
            io.writefile(path.join(cachedir, ".failed"), "")
            return nil
        end

        local prebuiltdir = resolve()
        if prebuiltdir then
            target:set("kind", "phony")
            target:data_set("commonlib.prebuiltdir", prebuiltdir)
            target:add("linkdirs", path.join(prebuiltdir, "lib"), { public = true })
            target:add("links", "commonlibsse-ng", { public = true })
            target:add("syslinks", "advapi32", "bcrypt", "d3d11", "d3dcompiler", "dbghelp", "dxgi", "ole32", "shell32", "user32", "version", { public = true })
        else
            -- Source build only: a phony target ignores add_files but would still build a
            -- pcxxheader, so set the PCH here rather than unconditionally.
            target:set("pcxxheader", path.join(target:scriptdir(), "include", "SKSE", "Impl", "PCH.h"))

            if has_config("skse_patch_safety") then
                local cachedir = path.join(target:autogendir(), "minhook-v1.3.4")
                local hde = path.join(cachedir, "minhook-1.3.4", "src", "hde")
                if not os.isfile(path.join(cachedir, ".complete")) then
                    import("net.http")
                    import("utils.archive")
                    local arch = os.tmpfile() .. ".tar.gz"
                    try { function()
                        http.download("https://github.com/TsudaKageyu/minhook/archive/refs/tags/v1.3.4.tar.gz", arch)
                        assert(hash.sha256(arch) == "1aebeae4ca898330c507860acc2fca2eb335fe446a3a2b8444c3bf8b2660a14e",
                            "MinHook v1.3.4 sha256 verification failed")
                        archive.extract(arch, cachedir)
                    end, finally { function(ok, errors)
                        os.tryrm(arch)
                        if not ok then raise(errors) end
                    end } }
                    io.writefile(path.join(cachedir, ".complete"), "")
                end
                target:add("files", path.join(hde, "hde64.c"))
                target:add("includedirs", hde)
            end

            -- The embedded license notice (src/REL/Module.cpp) wants a version string.
            -- Derive it from the git tag rather than tracking a second, manually-synced
            -- version number -- CMake's PROJECT_VERSION is itself just a mirror of the
            -- same tag, kept in sync by semantic-release's replace-plugin; the tag is
            -- the actual source of truth. --always falls back to an abbreviated commit
            -- hash when no tag is reachable (e.g. a shallow clone).
            local version = try { function()
                return os.iorunv("git", { "-C", scriptdir, "describe", "--tags", "--always", "--dirty" })
            end }
            target:add("defines", "COMMONLIB_VERSION=\"" .. (version and version:trim() or "unknown") .. "\"")
        end
    end)

    -- Once options are resolved: if we're on a prebuilt, refuse an ABI-incompatible config,
    -- and supply openvr headers from the bundle when the nested openvr submodule isn't
    -- checked out. Only the skyrim runtime set is layout-critical (linking the fixed lib while
    -- compiling ENABLE_SKYRIM_* headers differently is a silent ABI break). rex_ini and
    -- skse_xbyak are additive — the baked lib is a superset, and this target only adds their
    -- defines/packages when the consumer enables them — so a consumer may leave them off.
    -- rex_json/toml are baked off, so the lib lacks those symbols and they must stay off.
    on_config(function(target)
        if target:kind() ~= "phony" then return end
        local required = {
            skyrim_se = true, skyrim_ae = true, skyrim_vr = true,
            rex_json = false, rex_toml = false, skse_patch_safety = true,
        }
        for opt, want in pairs(required) do
            local got = has_config(opt) and true or false
            if got ~= want then
                raise("prebuilt commonlibsse-ng.lib requires %s=%s, but the consumer has %s=%s. "
                    .. "Match the baked config (skyrim all; rex_json/toml off; patch safety on; see PREBUILT.md) "
                    .. "or build from source.", opt, want and "y" or "n", opt, got and "y" or "n")
            end
        end
        local prebuiltdir = target:data("commonlib.prebuiltdir")
        if has_config("skyrim_vr") and prebuiltdir
            and not os.isdir(path.join(target:scriptdir(), "extern", "openvr", "headers")) then
            target:add("includedirs", path.join(prebuiltdir, "extern", "openvr", "headers"), { public = true })
        end
    end)

    -- set build by default
    set_default(os.scriptdir() == os.projectdir())

    -- add packages
    add_packages("directxmath", "directxtk", "spdlog", { public = true })

    -- add config packages
    if has_config("skyrim_vr") then
        add_packages("rapidcsv", { public = true })
        -- Source-tree openvr headers (added only if present). A prebuilt consumer without
        -- the nested openvr submodule gets them from the bundle instead (see on_config).
        local ovr = path.join(os.scriptdir(), "extern", "openvr", "headers")
        if os.isdir(ovr) then
            add_includedirs(ovr, { public = true })
        end
    end

    if has_config("rex_ini") then
        add_packages("simpleini", { public = true })
    end

    if has_config("rex_json") then
        add_packages("nlohmann_json", { public = true })
    end

    if has_config("rex_toml") then
        add_packages("toml11", { public = true })
    end

    if has_config("skse_xbyak") then
        add_packages("xbyak", { public = true })
    end

    -- add options
    add_options("rex_ini", "rex_json", "rex_toml", "skyrim_se", "skyrim_ae", "skyrim_vr", "skse_xbyak", "skse_patch_safety", "tests", { public = true })

    if (has_config("skyrim_se") and has_config("skyrim_ae"))
        or (has_config("skyrim_se") and has_config("skyrim_vr"))
        or (has_config("skyrim_ae") and has_config("skyrim_vr")) then
        add_defines("HAS_SKYRIM_MULTI_TARGETING=1", { public = true })
    end

    -- System links + sources. A phony (prebuilt) target ignores add_files, and the
    -- prebuilt path adds its own public syslinks in on_load, so this stays unconditional.
    add_syslinks("advapi32", "bcrypt", "d3d11", "d3dcompiler", "dbghelp", "dxgi", "ole32", "shell32", "user32", "version")
    add_files("src/**.cpp")

    -- add header files
    add_includedirs("include", { public = true })
    add_headerfiles(
        "include/(RE/**.h)",
        "include/(REL/**.h)",
        "include/(REX/**.h)",
        "include/(SKSE/**.h)"
    )


    -- add flags
    add_cxxflags("/EHsc", "/permissive-", "/Zc:preprocessor", { public = true })

    -- add flags (cl)
    add_cxxflags(
        "cl::/bigobj",
        "cl::/cgthreads8",
        "cl::/diagnostics:caret",
        "cl::/external:W0",
        "cl::/fp:contract",
        "cl::/fp:except-",
        "cl::/guard:cf-",
        "cl::/Zc:enumTypes",
        "cl::/Zc:preprocessor",
        "cl::/Zc:templateScope"
    )

    -- add flags (cl: warnings -> errors)
    add_cxxflags("cl::/we4715") -- `function` : not all control paths return a value

    -- add flags (cl: disable warnings)
    add_cxxflags(
        "cl::/wd4005", -- macro redefinition
        "cl::/wd4061", -- enumerator `identifier` in switch of enum `enumeration` is not explicitly handled by a case label
        "cl::/wd4068", -- unknown pragma 'clang'
        "cl::/wd4200", -- nonstandard extension used : zero-sized array in struct/union
        "cl::/wd4201", -- nonstandard extension used : nameless struct/union
        "cl::/wd4264", -- 'virtual_function' : no override available for virtual member function from base 'class'; function is hidden
        "cl::/wd4265", -- 'type': class has virtual functions, but its non-trivial destructor is not virtual; instances of this class may not be destructed correctly
        "cl::/wd4266", -- 'function' : no override available for virtual member function from base 'type'; function is hidden
        "cl::/wd4324", -- 'struct_name' : structure was padded due to __declspec(align())
        "cl::/wd4371", -- 'classname': layout of class may have changed from a previous version of the compiler due to better packing of member 'member'
        "cl::/wd4514", -- 'function' : unreferenced inline function has been removed
        "cl::/wd4582", -- 'type': constructor is not implicitly called
        "cl::/wd4583", -- 'type': destructor is not implicitly called
        "cl::/wd4623", -- 'derived class' : default constructor was implicitly defined as deleted because a base class default constructor is inaccessible or deleted
        "cl::/wd4625", -- 'derived class' : copy constructor was implicitly defined as deleted because a base class copy constructor is inaccessible or deleted
        "cl::/wd4626", -- 'derived class' : assignment operator was implicitly defined as deleted because a base class assignment operator is inaccessible or deleted
        "cl::/wd4686", -- 'user-defined type' : possible change in behavior, change in UDT return calling convention
        "cl::/wd4710", -- 'function' : function not inlined
        "cl::/wd4711", -- function 'function' selected for inline expansion
        "cl::/wd4820", -- 'bytes' bytes padding added after construct 'member_name'
        "cl::/wd5082", -- second argument to 'va_start' is not the last named parameter
        "cl::/wd5026", -- 'type': move constructor was implicitly defined as deleted
        "cl::/wd5027", -- 'type': move assignment operator was implicitly defined as deleted
        "cl::/wd5045", -- compiler will insert Spectre mitigation for memory load if /Qspectre switch specified
        "cl::/wd5053", -- support for 'explicit(<expr>)' in C++17 and earlier is a vendor extension
        "cl::/wd5105", -- macro expansion producing 'defined' has undefined behavior (workaround for older msvc bug)
        "cl::/wd5204", -- 'type-name': class has virtual functions, but its trivial destructor is not virtual; instances of objects derived from this class may not be destructed correctly
        "cl::/wd5220"  -- 'member': a non-static data member with a volatile qualified type no longer implies that compiler generated copy / move constructors and copy / move assignment operators are not trivial
    )

    -- add flags (clang-cl)
    add_cxxflags(
        "clang_cl::-fms-compatibility",
        "clang_cl::-fms-extensions",
        { public = true }
    )

    -- add flags (clang-cl: disable warnings)
    add_cxxflags(
        "clang_cl::-Wno-delete-non-abstract-non-virtual-dtor",
        "clang_cl::-Wno-deprecated-volatile",
        "clang_cl::-Wno-ignored-qualifiers",
        "clang_cl::-Wno-inconsistent-missing-override",
        "clang_cl::-Wno-invalid-offsetof",
        "clang_cl::-Wno-microsoft-include",
        "clang_cl::-Wno-overloaded-virtual",
        "clang_cl::-Wno-pragma-system-header-outside-header",
        "clang_cl::-Wno-reinterpret-base-class",
        "clang_cl::-Wno-switch",
        "clang_cl::-Wno-unused-private-field",
        { public = true }
    )
end)

if has_config("tests") then
    add_requires("catch2")

    target("commonlibsse-ng-tests", function()
        -- set target kind
        set_kind("binary")

        -- set build by default
        set_default(os.scriptdir() == os.projectdir())

        -- add dependencies
        add_deps("commonlibsse-ng")

        -- add packages
        add_packages("catch2")

        -- add source files
        add_files("tests/**.cpp")

        -- set precompiled header
        set_pcxxheader("include/SKSE/Impl/PCH.h")

        -- add flags (cl: disable warnings)
        add_cxxflags("cl::/wd4200") -- nonstandard extension used : zero-sized array in struct/union

        -- copy runtime files to run directory
        before_run(function(target)
            local plugins = path.join(path.absolute(target:targetdir()), "Data/SKSE/Plugins")
            os.mkdir(plugins)
            os.cp("$(scriptdir)/tests/REL/*.csv", plugins)
            os.cp("$(scriptdir)/tests/REL/*.bin", plugins)
        end)
    end)
end

-- copied from libxse/commonlib-shared
rule("commonlib.plugin", function()
    add_deps("win.sdk.resource")

    on_config(function(target)
        import("core.project.project")
        import("core.base.semver")

        target:set("arch", "x64")
        target:set("kind", "shared")

        target:set("configdir", target:autogendir())
        target:add("configfiles", path.join(os.scriptdir(), "res/commonlib-plugin.rc.in"))
        target:add("files", path.join(target:configdir(), "commonlib-plugin.rc"))

        local data = target:data("commonlib.plugin.config") or {}
        target:set("configvar", "COMMONLIB_PLUGIN_AUTHOR", data.author or "")
        target:set("configvar", "COMMONLIB_PLUGIN_CONTACT", data.contact or "")
        target:set("configvar", "COMMONLIB_PLUGIN_DESCRIPTION", data.description or "")
        target:set("configvar", "COMMONLIB_PLUGIN_LICENSE", (target:license() or "Unknown") .. " License")
        target:set("configvar", "COMMONLIB_PLUGIN_NAME", data.name or target:name())
        target:set("configvar", "COMMONLIB_PLUGIN_VERSION", target:version() or "0.0.0")
        target:set("configvar", "COMMONLIB_PLUGIN_VERSION_MAJOR", semver.new(target:version() or "0.0.0"):major())
        target:set("configvar", "COMMONLIB_PLUGIN_VERSION_MINOR", semver.new(target:version() or "0.0.0"):minor())
        target:set("configvar", "COMMONLIB_PLUGIN_VERSION_PATCH", semver.new(target:version() or "0.0.0"):patch())
        target:set("configvar", "COMMONLIB_PROJECT_NAME", project.name() or "")
        target:set("configvar", "COMMONLIB_PROJECT_VERSION", project.version() or "0.0.0")
        target:set("configvar", "COMMONLIB_PROJECT_VERSION_MAJOR", semver.new(project.version() or "0.0.0"):major())
        target:set("configvar", "COMMONLIB_PROJECT_VERSION_MINOR", semver.new(project.version() or "0.0.0"):minor())
        target:set("configvar", "COMMONLIB_PROJECT_VERSION_PATCH", semver.new(project.version() or "0.0.0"):patch())
    end)

    on_install(function(target)
        import("target.action.install")(target, { binaries = false, headers = false, libraries = false, packages = false })
    end)

    on_package(function(target)
        import("core.project.config")
        import("core.project.project")

        local archivename = target:name() .. "-" .. (target:version() or "0.0.0") .. ".zip"
        cprint("${dim}packaging %s .. ", archivename)

        local rootdir = path.join(os.tmpdir(), "packages", project.name() or "", target:name())
        os.tryrm(rootdir)

        local data = target:data("commonlib.plugin.package") or {}
        local installdir = path.join(rootdir, data.prefixdir or "")
        os.mkdir(installdir)

        local srcfiles, dstfiles = target:installfiles(installdir)
        if srcfiles and #srcfiles > 0 and dstfiles and #dstfiles > 0 then
            for idx, srcfile in ipairs(srcfiles) do
                os.trycp(srcfile, dstfiles[idx])
            end
        else
            return
        end

        local archivedir = path.absolute(path.join(config.builddir(), "packages"))
        local archivefile = path.join(archivedir, archivename)
        os.tryrm(archivefile)

        local olddir = os.cd(rootdir)
        local archivefiles = os.files("**")
        os.cd(olddir)

        import("utils.archive").archive(archivefile, archivefiles, { curdir = rootdir })

        cprint("${dim}packaging %s to %s ... ${color.success}${text.success}", archivename, archivedir)
    end)

    after_build(function(target)
        import("core.project.depend")
        import("core.project.task")

        depend.on_changed(function()
            local srcfiles, dstfiles = target:installfiles()
            if srcfiles and #srcfiles > 0 and dstfiles and #dstfiles > 0 then
                task.run("install")
            end
        end, { changed = target:is_rebuilt(), files = { target:targetfile() } })
    end)
end)

rule("commonlibsse-ng.plugin", function()
    add_deps("commonlib.plugin")

    on_load(function(target)
        target:data_set("commonlib.plugin.config", target:extraconf("rules", "commonlibsse-ng.plugin"))
        target:data_set("commonlib.plugin.package", { prefixdir = "Data" })
    end)

    on_config(function(target)
        target:add("deps", "commonlibsse-ng")

        target:add("configfiles", path.join(os.scriptdir(), "res/commonlibsse-ng-plugin.cpp.in"))
        target:add("files", path.join(target:configdir(), "commonlibsse-ng-plugin.cpp"))

        local conf = target:extraconf("rules", "commonlibsse-ng.plugin")
        local conf_opt_struct_compatibility = "SKSE::StructCompatibility::Independent"
        local conf_opt_runtime_compatibility = "SKSE::VersionIndependence::AddressLibrary"
        if conf.options then
            if conf.options.struct_dependent then
                conf_opt_struct_compatibility = "SKSE::StructCompatibility::Dependent"
            end

            if conf.options.address_library or conf.options.signature_scanning then
                if not conf.options.address_library then
                    conf_opt_runtime_compatibility = "SKSE::VersionIndependence::SignatureScanning"
                end
            end
        end

        target:set("configvar", "COMMONLIBSSE_NG_OPTION_STRUCT_COMPATIBILITY", conf_opt_struct_compatibility)
        target:set("configvar", "COMMONLIBSSE_NG_OPTION_RUNTIME_COMPATIBILITY", conf_opt_runtime_compatibility)

        if os.getenv("XSE_TES5_MODS_PATH") then
            target:set("installdir", path.join(os.getenv("XSE_TES5_MODS_PATH"), target:name()))
        elseif os.getenv("XSE_TES5_GAME_PATH") then
            target:set("installdir", path.join(os.getenv("XSE_TES5_GAME_PATH"), "Data"))
        end

        target:add("installfiles", target:targetfile(), { prefixdir = "SKSE/Plugins" })
        target:add("installfiles", target:symbolfile(), { prefixdir = "SKSE/Plugins" })
    end)
end)
