# CommonLibSSE NG

[![C++23](https://img.shields.io/static/v1?label=standard&message=c%2B%2B23&color=blue&logo=c%2B%2B&&logoColor=white&style=flat)](https://en.cppreference.com/w/cpp/compiler_support)
![Platform](https://img.shields.io/static/v1?label=platform&message=windows&color=dimgray&style=flat&logo=windows)
[![License: GPL-3.0-or-later](https://img.shields.io/static/v1?label=license&message=GPL-3.0-or-later&color=blue&style=flat)](#license)
[![Latest Release](https://img.shields.io/github/v/release/alandtse/CommonLibSSE-NG?logo=pkgsrc&logoColor=white)](#use)
[![Main CI](https://github.com/alandtse/CommonLibSSE-NG/actions/workflows/main_ci.yml/badge.svg?branch=ng)](https://github.com/alandtse/CommonLibSSE-NG/actions/workflows/main_ci.yml)
[![Ask DeepWiki](https://deepwiki.com/badge.svg)](https://deepwiki.com/alandtse/CommonLibSSE-NG)

CommonLibSSE NG is a fork of CharmedBaryon's CommonLibSSE-NG, itself a fork of CommonLibSSE, which tracks upstream updates but adds a number of enhancements.
It supports Skyrim Special Edition (SE), Skyrim Anniversary Edition (AE), and Skyrim Virtual Reality (VR).

## Usage

To develop a C++ project that uses CommonLibSSE, you'll want to have this code available for discovery, and included as a build dependency by your build manager. Below are examples using the `xmake` or `cmake` managers.

> [!TIP]
> For examples & templates see the wiki: https://github.com/alandtse/CommonLibSSE-NG/wiki/Projects-using-CommonLib

### Getting the code: Git SubModule

Assuming you have a folder with your mod material, this can be converted to a git repository, for which this repo can be added as a submodule,
allowing git to manage updates, paths, names, versions... To do this:

Use the folder to [initialize a git repository](https://git-scm.com/book/en/v2/Git-Basics-Getting-a-Git-Repository):

```powershell
PS E:\Git\foo-bar> git init
Initialized empty Git repository in E:/Git/foo-bar/.git/
```

Add this CommonLibSSE repo as a [git submodule](https://git-scm.com/book/en/v2/Git-Tools-Submodules), specifying the `ng` branch,
and storing it in `lib/commonlibsse-ng` folder:

```powershell
PS E:\Git\foo-bar> git submodule add -b ng https://github.com/alandtse/CommonLibSSE-NG.git lib/commonlibsse-ng
Cloning into 'E:/Git/foo-bar/lib/commonlibsse-ng'...
remote: Enumerating objects: 66210, done.
remote: Counting objects: 100% (2526/2526), done.
remote: Compressing objects: 100% (197/197), done.
remote: Total 66210 (delta 2397), reused 2335 (delta 2329), pack-reused 63684 (from 1)
Receiving objects: 100% (66210/66210), 18.99 MiB | 19.58 MiB/s, done.
Resolving deltas: 100% (51252/51252), done.
PS E:\Git\foo-bar
```

> [!TIP]
> If your submodule ended up in a location where the rest of the code can't find it, you can remove & re-add submodules, see https://stackoverflow.com/a/1260982

At this point, git is tracking changes to your code in your machine. You can add a cloud-based remote for backup, distribution, or collaboration; instructions are here for [GitHub](https://docs.github.com/en/migrations/importing-source-code/using-the-command-line-to-import-source-code/adding-locally-hosted-code-to-github) or [CodeBerg](https://docs.codeberg.org/getting-started/first-repository/).

To update your project's submodules you can use:
```powershell
PS E:\Git\foo-bar> git submodule update --init --recursive
```

### Build Dependency: Xmake

If using the [Xmake build system](https://xmake.io/guide/introduction.html), you can add a build dependency and
a custom rule suitable for SKSE plugins by adding this to your DLL target recipe:

```xmake
target("my_plugin")
   set_kind("shared")                         --specifies this is a DLL
   add_deps("commonlibsse-ng")                --adds the dependency

   add_rules("commonlibsse-ng.plugin", {      --adds a custom build rule, whose details are in CommonLibSSE
      name = "my_plugin",
      author = "Dovahkiin",
      description = "SKSE64 plugin using CommonLibSSE-NG"
   })
```

### Build Dependency: CMake

If using the [CMake build system](https://cmake.org/cmake/help/v4.2/index.html#), you can add the following in `CMakeLists.txt` to compile and link successfully:

```cmake
find_package(CommonLibSSE REQUIRED)
target_link_libraries(${PROJECT_NAME} PUBLIC CommonLibSSE::CommonLibSSE)
```

## New Features

### Multiple Runtime Targets

![stability](https://img.shields.io/static/v1?label=stability&message=stable&color=dimgreen&style=flat)

CommonLibSSE NG has support for Skyrim SE, AE, and VR, and is able to create builds for any combination of these
runtimes, including all three. This makes it possible to create SKSE plugins with a single DLL that works in any
Skyrim runtime, improving developer productivity (only one build and CMake preset necessary) and improving the end-user
experience (no need to make a choice of multiple download options or select the right DLL from a FOMOD). For Skyrim AE,
both versions before 1.6.629 and those after are supported in a single DLL (both struct layouts are supported).

Builds that target multiple ABI-incompatible runtimes provide the necessary (but minimal) abstractions needed to work
transparently regardless of the Skyrim edition in use. All functionality and classes from all runtimes is always
available for potential use, with the necessary support for probing the features available. This allows single plugins
that dynamic alter their behavior to take advantage of the specific features of a single Skyrim edition (e.g. VR
features) when that runtime is present.

[Read about multi-targeting, and how you can take advantage in your project.](https://github.com/CharmedBaryon/CommonLibSSE-NG/wiki/Runtime-Targeting)

### Simplified Plugin Declaration

![stability](https://img.shields.io/static/v1?label=stability&message=stable&color=dimgreen&style=flat)

Historically, plugins needed to define `SKSEPlugin_Version` or `SKSEPlugin_Query` to be detected as SKSE plugins. To
simplify code and ensure both functions are generated for correct cross-runtime compatibility, this is made code-free in
CommonLibSSE NG. Just replace `add_library` with `add_commonlibsse_plugin` in `CMakeLists.txt` and CMake will create
your shared library target, configure CommonLibSSE linkage, and auto-generate this content and inject it into the
plugin.

```cmake
find_package(CommonLibSSE REQUIRED)

add_commonlibsse_plugin(${PROJECT_NAME}
    SOURCES ${headers} ${sources})
```

[Read more on
the project wiki.](https://github.com/CharmedBaryon/CommonLibSSE-NG/wiki/Runtime-Targeting#cmake-integration)

### Clang Support

![stability-beta](https://img.shields.io/static/v1?label=stability&message=beta&color=yellow&style=flat)

Clang 13.x and newer are supported when built for MSVC ABI compatibility (versions built natively for Windows). It is
even hypothetically possible, with the proper setup, to cross-compile with Clang from a Linux host (testing and
instructions for this are pending). Note that currently linking must still be done with the Microsoft linker, pending
fixes to SKSE itself.

[Read more on
the project wiki.](https://github.com/CharmedBaryon/CommonLibSSE-NG/wiki/Compiling-with-Clang)

### Unit Testing Enhancements

![stability-stable](https://img.shields.io/static/v1?label=stability&message=stable&color=dimgreen&style=flat)

Improvements have been made to the way in which the Skyrim executable module is accessed for the sake of memory
relocation and handling of Address Library IDs. This makes it easier to run CommonLibSSE-based plugin code outside of
the context of a Skyrim process so that unit testing is possible. It is even possible to handle a minimal level of
functionality from the engine by loading in a Skyrim executable module programmatically during testing, allowing, for
example, tests to be run within a single test suite that vary between SE, AE, and VR executables.

[Read more on
the project wiki.](https://github.com/CharmedBaryon/CommonLibSSE-NG/wiki/Unit-Testing)

### Older Releases via Vcpkg and Conan

> [!WARNING]
> These are not part of this repository and are not currently maintained.

Older versions of CommonLibSSE, specifically CharmedByron's, are (were) available as a
[vcpkg port](https://gitlab.com/colorglass/vcpkg-colorglass) and as a 
[Conan package](https://charmedbaryon.jfrog.io/artifactory/api/conan/default-conan). These are not maintained as part of this project.

[See how to use CommonLibSSE NG in your project.](#use)

### Ninja Builds

![stability-stable](https://img.shields.io/static/v1?label=stability&message=stable&color=dimgreen&style=flat)

CommonLibSSE NG migrates the build system to Ninja, resulting in faster parallel builds than NMake.

### Other Changes

- Ability to define offsets and address IDs for objects which can exist in only a subset of runtimes, while being able
  dynamically test for feature support before using those offsets.
- Completely regenerated RTTI and vtable offsets, now with consistent naming and access across all runtimes.
- Updated GitHub Actions CI workflows to build for all likely target runtime combinations.
- Fully extensible native function binding traits (enables custom script object bindings in
  [Fully Dynamic Game Engine](https://gitlab.com/colorglass/fully-dynamic-game-engine)).
- Better support for the CLion IDE.


## Build Dependencies

Dependencies are managed via vcpkg. See `vcpkg.json` for the complete list.

**Core Dependencies:**
- [fmt](https://github.com/fmtlib/fmt) 12.1+
- [rapidcsv](https://github.com/d99kris/rapidcsv) 8.9+
- [spdlog](https://github.com/gabime/spdlog) 1.16+
- [xbyak](https://github.com/herumi/xbyak) 7.28+
- [catch2](https://github.com/catchorg/Catch2) 3.1.0+ (for testing)
- [directxmath](https://github.com/microsoft/DirectXMath) 2025-04-03 - DirectX Math library
- [directxtk](https://github.com/microsoft/DirectXTK) 2025-10-27 - DirectX Toolkit

**Build Tools:**
- [Visual Studio 2022](https://visualstudio.microsoft.com/vs/) - Desktop development with C++
- [CMake](https://cmake.org/) 3.19+
- [Vcpkg](https://github.com/microsoft/vcpkg)

### Cross-compiling from Linux

The `build-*-linux-clangcl-vcpkg-*` presets target the same Windows
PE/MSVC ABI output as the presets above, using `clang-cl`+`lld-link`
against an `xwin`-generated sysroot instead of a real MSVC install, and
run from an ordinary Linux shell. See
[`examples/linux-cross-compile/README.md`](examples/linux-cross-compile/README.md)
for setup and usage.

## End User Dependencies

- [Address Library for SKSE Plugins](https://www.nexusmods.com/skyrimspecialedition/mods/32444) or
  [VR Address Library for SKSEVR](https://www.nexusmods.com/skyrimspecialedition/mods/58101)
- [SKSE64](https://skse.silverlock.org/)

## Development

- [Address Library for SKSE Plugins](https://www.nexusmods.com/skyrimspecialedition/mods/32444) and
  [VR Address Library for SKSEVR](https://www.nexusmods.com/skyrimspecialedition/mods/58101)
- [clang-format 12.0.0](https://github.com/llvm/llvm-project/releases)
- [CMake](https://cmake.org/)

## Notes

- CommonLib is incompatible with SKSE and is intended to replace it as a static dependency. However, you will still need the runtime component.

## License

[GPL-3.0-or-later](COPYING.txt) WITH [Modding Exception AND GPL-3.0 Linking Exception (with Corresponding Source)](EXCEPTIONS.md).
Specifically, the Modded Code includes:

- Skyrim (and its variants)
- Hardware drivers to enable additional functionality provided via proprietary SDKs, such as [Nvidia DLSS/Streamline](https://developer.nvidia.com/rtx/dlss/get-started) and [AMD FidelityFX FSR3](https://gpuopen.com/fidelityfx-super-resolution-3/)

The Modding Libraries include:

- [SKSE](https://skse.silverlock.org/)
- Windows

> [!IMPORTANT]
> This is a breaking change from the previous MIT license. The Modding Exception only covers interoperation with
> Skyrim itself and proprietary hardware SDKs (like DLSS/Streamline or FSR3) that neither we nor plugin authors have
> the right to relicense -- it does **not** cover plugin/mod code. A plugin that statically links CommonLibSSE NG
> forms a combined work with it and must itself be licensed under the GPL-3.0-or-later (or a GPL-compatible
> license); see [EXCEPTIONS.md](EXCEPTIONS.md) for the exact terms.

Originally based on code under [MIT](licenses/LICENSE-MIT.txt).
