# CommonLibSSE NG

[![C++23](https://img.shields.io/static/v1?label=standard&message=c%2B%2B20&color=blue&logo=c%2B%2B&&logoColor=white&style=flat)](https://en.cppreference.com/w/cpp/compiler_support)
![Platform](https://img.shields.io/static/v1?label=platform&message=windows&color=dimgray&style=flat&logo=windows)
[![Latest Release](https://img.shields.io/github/v/release/CharmedBaryon/CommonLibSSE-NG?logo=pkgsrc&logoColor=white)](#use)
[![Main CI](https://img.shields.io/github/workflow/status/CharmedBaryon/CommonLibSSE-NG/Main%20CI/main?logo=github&label=tests)](https://github.com/CharmedBaryon/CommonLibSSE-NG/actions/workflows/main_ci.yml)

CommonLibSSE NG is a fork of CommonLibSSE which tracks upstream updates but adds a number of enhancements.

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

### Versioned Releases via Vcpkg and Conan

![stability-stable](https://img.shields.io/static/v1?label=vcpkg&message=stable&color=dimgreen&style=flat)

![stability-experimental](https://img.shields.io/static/v1?label=conan&message=experimental&color=orange&style=flat)

Traditionally CommonLibSSE is consumed via a Git submodule; this practice generally requires the project using it to add
CommonLibSSE's own Vcpkg dependencies and parts of it CMake configuration, as CommonLibSSE is built as a part of the
plugin project. CommonLibSSE NG instead uses specific releases with semantic versioning, and distributes them as their
own Vcpkg ports, through the [Color-Glass Studios Vcpkg repository](https://gitlab.com/colorglass/vcpkg-colorglass).
As a result, it is simpler to use, does not require absorbing transitive requirements into your own project, and needs
only be built once (cleaning will not require rebuilding CommonLibSSE, only your own code).

In addition, starting with version 3.5.0, CommonLibSSE NG can now be both built and consumed via the Conan package
manager, both as a source build or prebuilt packages targeting Windows on x86_64 with Visual Studio compiler versions 16
and 17 (2019 and 2022).

[See how to use CommonLibSSE NG in your project.](#use)

### Ninja Builds

![stability-stable](https://img.shields.io/static/v1?label=stability&message=stable&color=dimgreen&style=flat)

CommonLibSSE NG migrates the build system to Ninja, resulting in faster parallel builds than NMake.

## Other Changes

- Ability to define offsets and address IDs for objects which can exist in only a subset of runtimes, while being able
  dynamically test for feature support before using those offsets.
- Completely regenerated RTTI and vtable offsets, now with consistent naming and access across all runtimes.
- Updated GitHub Actions CI workflows to build for all likely target runtime combinations.
- Fully extensible native function binding traits (enables custom script object bindings in
  [Fully Dynamic Game Engine](https://gitlab.com/colorglass/fully-dynamic-game-engine)).
- Better support for the CLion IDE.

## Use

### Via Vcpkg

CommonLibSSE NG is available as a Vcpkg port. To add it to your project, create a `vcpkg-configuration.json` file in the
project root (next to `vcpkg.json`) with the following contents:

```json
{
  "registries": [
    {
      "kind": "git",
      "repository": "https://gitlab.com/colorglass/vcpkg-colorglass",
      // Update this baseline to the latest commit from the above repo.
      "baseline": "9eae9f03f03e0ca96fce5031f44f4e64cd6debdc",
      "packages": [
        "commonlibsse-ng",
        "commonlibsse-ng-ae",
        "commonlibsse-ng-se",
        "commonlibsse-ng-vr",
        "commonlibsse-ng-flatrim"
      ]
    }
  ]
}
```

Then add `commonlibsse-ng` as a dependency in `vcpkg.json`. There are also runtime-specific versions of the project:

- `commonlibsse-ng-ae`: Supports AE executables (1.6.x) only.
- `commonlibsse-ng-se`: Supports pre-AE executables (1.5.x) only.
- `commonlibsse-ng-vr`: Supports VR only.
- `commonlibsse-ng-flatrim`: Support for SE/AE, but not VR.

The runtime-specific ports will not attempt to dynamically lookup the version of Skyrim at runtime, and will enable
access to reverse engineered content that is specific to that version of Skyrim and non-portable (i.e. it does not exist
in all versions of Skyrim, or has not been reverse engineered on all versions of Skyrim).

### Via Conan

CommonLibSSE NG is now available via Conan. Add it as a requirement to your project's `conanfile.txt` or `conanfile.py`:

```ini
[requires]
commonlibsse-ng/3.5.2
```

```python
class MyProject:
    # ...
    requires = 'commonlibsse-ng/3.5.2'
```

Update the version number to the version constraints you want. Conan support was added in version 3.5.0, making that the
earliest version available. Currently Conan binaries are available for the following
`build_type`/`arch`/`os`/`compiler`/`compiler.version` combinations:

- Debug/x86_64/Windows/Visual Studio/16
- Debug/x86_64/Windows/Visual Studio/17
- Release/x86_64/Windows/Visual Studio/16
- Release/x86_64/Windows/Visual Studio/17

Selective runtime support is handled via package options:

```ini
[requires]
commonlibsse-ng/3.5.2

[options]
commonlibsse-ng:ae=True
commonlibsse-ng:se=True
commonlibsse-ng:vr=True
```

```python
class MyProject:
    # ...
    requires = 'commonlibsse-ng/3.5.2'
    default_options = {
      # ...
      'commonlibsse-ng:with_ae': True,
      'commonlibsse-ng:with_se': True,
      'commonlibsse-ng:with_vr': True
    }
```

The above shows the default values (which includes support for all runtimes). Disable any runtimes you do not want.

### Linking in CMake

You should have the following in `CMakeLists.txt` to compile and link successfully:

```cmake
find_package(CommonLibSSE REQUIRED)
target_link_libraries(${PROJECT_NAME} PUBLIC CommonLibSSE::CommonLibSSE)
```

For more information on how to use CommonLibSSE NG, you can look at the
[example plugin](https://gitlab.com/colorglass/commonlibsse-sample-plugin).

## Build Dependencies

- [rapidcsv](https://github.com/d99kris/rapidcsv)
- [spdlog](https://github.com/gabime/spdlog)
- [Visual Studio 2022](https://visualstudio.microsoft.com/vs/)
  - Desktop development with C++

## End User Dependencies

- [Address Library for SKSE Plugins](https://www.nexusmods.com/skyrimspecialedition/mods/32444) or
  [VR Address Library for SKSEVR](https://www.nexusmods.com/skyrimspecialedition/mods/58101)
- [SKSE64](https://skse.silverlock.org/)

## Development

- [Address Library for SKSE Plugins](https://www.nexusmods.com/skyrimspecialedition/mods/32444) and
  [VR Address Library for SKSEVR](https://www.nexusmods.com/skyrimspecialedition/mods/58101)
- [clang-format 12.0.0](https://github.com/llvm/llvm-project/releases)
- [CMake](https://cmake.org/)
- [Conan](https://conan.io) or [Vcpkg](https://github.com/microsoft/vcpkg)

## Notes

- CommonLib is incompatible with SKSE and is intended to replace it as a static dependency. However, you will still need
- the runtime component.
