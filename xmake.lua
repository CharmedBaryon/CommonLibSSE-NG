-- set minimum xmake version
set_xmakever("2.8.2")

-- make extras available
includes("xmake-extra.lua")

-- set project
set_project("commonlibsse-ng")
set_arch("x64")
set_languages("c++23")
set_warnings("allextra")
set_encodings("utf-8")

-- add rules
add_rules("mode.debug", "mode.release")

-- define options
option("skyrim_se")
    set_default(true)
    set_description("Enable runtime support for Skyrim SE")
    add_defines("ENABLE_SKYRIM_SE=1")
option_end()

option("skyrim_ae")
    set_default(true)
    set_description("Enable runtime support for Skyrim AE")
    add_defines("ENABLE_SKYRIM_AE=1")
option_end()

option("skyrim_vr")
    set_default(true)
    set_description("Enable runtime support for Skyrim VR")
    add_defines("ENABLE_SKYRIM_VR=1")
option_end()

option("skse_xbyak")
    set_default(false)
    set_description("Enable trampoline support for Xbyak")
    add_defines("SKSE_SUPPORT_XBYAK=1")
option_end()

option("tests")
    set_default(false)
    set_description("Enable building unit tests")
    add_defines("ENABLE_COMMONLIBSSE_TESTING=1")
option_end()

-- require packages
add_requires("directxmath", "directxtk", "spdlog", { configs = { header_only = false, wchar = true, std_format = true } })

if has_config("skyrim_vr") then
    add_requires("rapidcsv")
end

if has_config("skse_xbyak") then
    add_requires("xbyak")
end

-- define targets
target("commonlibsse-ng")
    -- set target kind
    set_kind("static")

    -- add packages
    add_packages("directxmath", "directxtk", "spdlog", { public = true })

    if has_config("skyrim_vr") then
        add_packages("rapidcsv", { public = true })
    end

    if has_config("skse_xbyak") then
        add_packages("xbyak", { public = true })
    end

    -- add options
    add_options("skyrim_se", "skyrim_ae", "skyrim_vr", "skse_xbyak", "tests", { public = true })

    -- add system links
    add_syslinks("advapi32", "d3d11", "d3dcompiler", "dbghelp", "dxgi", "ole32", "shell32", "user32", "version")

    -- add source files
    add_files("src/**.cpp")

    -- add header files
    add_includedirs("include", { public = true })
    add_headerfiles(
        "include/(RE/**.h)",
        "include/(REL/**.h)",
        "include/(REX/**.h)",
        "include/(SKSE/**.h)"
    )

    -- set precompiled header
    set_pcxxheader("include/SKSE/Impl/PCH.h")

    -- add flags
    add_cxxflags("/EHsc", "/permissive-", { public = true })

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

    -- add flags (clang-cl: disable warnings)
    add_cxxflags(
        "clang_cl::-Wno-delete-non-abstract-non-virtual-dtor",
        "clang_cl::-Wno-inconsistent-missing-override",
        "clang_cl::-Wno-overloaded-virtual",
        "clang_cl::-Wno-reinterpret-base-class"
    )
target_end()

if has_config("tests") then
    add_requires("catch2")

    target("commonlibsse-ng-tests")
        -- set target kind
        set_kind("binary")

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
    target_end()
end
