# `CommonLibSSE NG`
[![C++20](https://img.shields.io/static/v1?label=standard&message=C%2B%2B20&color=blue&logo=c%2B%2B&&logoColor=white&style=flat)](https://en.cppreference.com/w/cpp/compiler_support)
[![Platform](https://img.shields.io/static/v1?label=platform&message=windows&color=dimgray&style=flat)](#)
[![Main CI](https://github.com/CharmedBaryon/CommonLibSSE-NG/actions/workflows/main_ci.yml/badge.svg)](https://github.com/CharmedBaryon/CommonLibSSE-NG/actions/workflows/main_ci.yml)

CommonLibSSE NG is a fork of CommonLibSSE which tracks upstream updates but adds a number of enhancements:
* Support for Address Libraries for SE, AE, and VR.
* Dynamic cross-runtime support (ability to produce a single DLL that works on AE, SE, or VR), with access to all
  cross-compatible features.
* Complete support (up to modern RE standards) for Skyrim VR, including the ability to use Skyrim VR and Skyrim SE
  functionality from a single DLL build even where Skyrim VR is normally ABI-incompatible.
* Ability to build locked to a single runtime, where access to non-portable features is needed.
* Updated GitHub Actions CI workflows to build for all likely target runtime combinations.
* Fully extensible native function binding traits (enables custom script object bindings in
  [Fully Dynamic Game Engine](https://gitlab.com/colorglass/fully-dynamic-game-engine)).
* Unit testing support (can be run without being hosted in a Skyrim executable).
* Better support for the CLion IDE, including a completed CMakePresets.json file that works in non-Visual Studio IDEs.
* Fixes to support the current versions of  dependencies on Vcpkg.
* Uses modern Vcpkg manifest version feature and assigns semantic versions to specific CommonLibSSE NG releases.
* Upgrades the build system to Ninja for faster builds.
* Provides distribution through Vcpkg rather than requiring import as a Git submodule.
* A related [new example plugin](https://gitlab.com/colorglass/commonlibsse-sample-plugin) that demonstrates not only a
  project structure but a full-featured dev environment and implementation of a number of features using the library,
  including support for AE, SE, and VR with a single DLL.

CommonLibSSE NG is available as a Vcpkg port. To add it to your project, create a `vcpkg-configuration.json` file in the
project root (next to `vcpkg.json`) with the following contents:

```json
{
    "registries": [
        {
            "kind": "git",
            "repository": "https://gitlab.com/colorglass/vcpkg-colorglass",
            // Update this baseline to the latest commit from the above repo.
            "baseline": "59ebdd824b295fad4effcdccfe6e6aaa47ff4764",
            "packages": [
                "commonlibsse-ng"
            ]
        }
    ]
}
```

Then add `commonlibsse-ng` as a dependency in `vcpkg.json`. There are also runtime-specific versions of the project:
* `commonlibsse-ng-ae`: Supports AE executables (1.6.x) only.
* `commonlibsse-ng-se`: Supports pre-AE executables (1.5.x) only.
* `commonlibsse-ng-vr`: Supports VR only.
* `commonlibsse-ng-prebuilt`: A prebuilt binary for CommonLibSSE NG, avoids the overhead of compiling it. Recommended to
  be used only with `x64-windows-static-md` triplet (or equivalent custom one), but can also be used with
  `x64-windows-static` (or custom equivalent) if your project links against a compatible version of the MSVC 2022 CRT.

The runtime-specific ports will not attempt to dynamically lookup the version of Skyrim at runtime, and will enable
access to reverse engineered content that is specific to that version of Skyrim and non-portable (i.e. it does not exist
in all versions of Skyrim, or has not been reverse engineered on all versions of Skyrim). Note that VR is only partially
supported in this fork. It is treated largely as SE, but with VR Address Library support. Some functionality may still
be exposed which is not available for VR (e.g. ESL-flagged plugins), and not all Address Library IDs are mapped by VR
Address Library at this time.

You should have the following in `CMakeLists.txt` to compile and link successfully:
```cmake
find_package(CommonLibSSE REQUIRED)
# ...
target_link_libraries(${PROJECT_NAME} PUBLIC CommonLibSSE::CommonLibSSE)
```

For more information on how to use CommonLibSSE NG, you can look at the
[example plugin](https://gitlab.com/colorglass/commonlibsse-sample-plugin).

## Build Dependencies
* [Boost](https://www.boost.org/)
	* Stl_interfaces
* [spdlog](https://github.com/gabime/spdlog)
* [Visual Studio Community 2019 16.10.0 Preview 3.0](https://visualstudio.microsoft.com/vs/preview/)
	* Desktop development with C++

## End User Dependencies
* [Address Library for SKSE Plugins](https://www.nexusmods.com/skyrimspecialedition/mods/32444)
* [SKSE64](https://skse.silverlock.org/)

## Development
* [Address Library for SKSE Plugins](https://www.nexusmods.com/skyrimspecialedition/mods/32444)
* [clang-format 12.0.0](https://github.com/llvm/llvm-project/releases)
* [CMake](https://cmake.org/)
* [vcpkg](https://github.com/microsoft/vcpkg)

## Notes
* CommonLib is incompatible with SKSE and is intended to replace it as a static dependency. However, you will still need the runtime component.
