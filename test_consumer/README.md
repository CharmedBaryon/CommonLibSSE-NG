# Consumer Integration Test

This directory contains an integration test that validates CommonLib works correctly when consumed as a CMake subdirectory dependency.

## Purpose

This test specifically validates that **CommonLib's internal STATIC_ASSERT_SIZE macros** compile correctly when the library is used as a dependency via `add_subdirectory()`.

## The Problem This Test Catches

Without the `/Zc:preprocessor` compiler flag, CommonLib's variadic macro dispatcher for `STATIC_ASSERT_SIZE` fails to expand correctly. This causes compilation errors like:

```text
error C2338: static_assert failed: 'STATIC_ASSERT_SIZE requires at least 2 arguments: ClassName and Size'
```

**The key issue**: CommonLib builds fine in isolation, but when consumed as a dependency, its own headers fail to compile due to the preprocessor issue.

## How It Works

1. The test includes CommonLib headers that contain `STATIC_ASSERT_SIZE` calls (PlayerCharacter, Actor, RaceSexMenu, etc.)
2. Uses CommonLib's precompiled header to get necessary definitions (RTTI macros, `stl::` namespace, etc.)
3. If `/Zc:preprocessor` is missing, these CommonLib headers fail to compile
4. If the build succeeds, it proves the preprocessor fix is working

## Running the Test

**Note:** This test requires vcpkg dependencies since it builds CommonLib from source. Make sure vcpkg is set up correctly.

```bash
# With vcpkg toolchain file
cmake -B build -S . \
  -DCMAKE_TOOLCHAIN_FILE=/path/to/vcpkg/scripts/buildsystems/vcpkg.cmake \
  -DENABLE_SKYRIM_SE=ON \
  -DENABLE_SKYRIM_AE=ON \
  -DENABLE_SKYRIM_VR=ON

cmake --build build --config Release
./build/Release/ConsumerTest.exe
```

## Relationship to Other Tests

- `tests/` - Unit tests that test CommonLib functionality
- `test_package/` - Tests CommonLib as a Conan package (via `find_package`)
- `test_consumer/` - Tests CommonLib as a subdirectory dependency (via `add_subdirectory`)
