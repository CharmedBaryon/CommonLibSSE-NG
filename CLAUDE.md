# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

CommonLibSSE NG is a modern C++ library for SKSE (Skyrim Script Extender) plugin development that supports multiple Skyrim runtimes: SE (Special Edition), AE (Anniversary Edition), and VR. It provides a comprehensive C++ API for interacting with Skyrim's game engine and is designed to enable single-DLL plugins that work across all supported runtimes.

## Multi-Runtime Architecture

The library uses a unique multi-targeting system that allows plugins to support SE, AE, and VR simultaneously:
- Runtime detection happens at loading time
- Code can probe for runtime-specific features before using them
- Address Library integration handles different game versions automatically
- Conditional compilation flags control runtime support: `ENABLE_SKYRIM_SE`, `ENABLE_SKYRIM_AE`, `ENABLE_SKYRIM_VR`

## Build System Commands

### Quick Build Script (Recommended for AI Agents)

**For fast iteration and error detection**, use the comprehensive build script:

```bash
# From Windows
.\scripts\build-all-presets.cmd

# From WSL/Linux
cmd.exe /c "scripts\build-all-presets.cmd"
```

This script:
- Builds all presets (SE, AE, VR, Flatrim, All) in sequence
- **Stops at first failure** for fast error detection
- **Shows only errors** (filters out verbose output)
- Perfect for LLM-assisted development iterations

### Building from WSL (Claude Code, Linux Environments)

**IMPORTANT**: The `msvc`-compiler presets need Windows-specific tooling (Visual Studio 2022, MSVC compiler). Claude Code running in WSL must use PowerShell to invoke the Windows build tools for those. If you're on a genuine Linux host (not WSL) and want to avoid Windows tooling entirely, see "Building via Linux-host cross-compile" below instead.

**CRITICAL**: CMake must run from a Visual Studio Developer Shell to properly detect the MSVC compiler. If run from a regular shell, CMake may incorrectly detect clang++ and fail with compiler errors. This does NOT apply to the `linux-clangcl` presets described below, which are specifically designed to run from a regular Linux shell with no VS environment at all.

```bash
# WSL/Linux: Use powershell.exe to launch VS Developer Shell and build
# IMPORTANT: Adjust the VS installation path to match your system
# The examples below use F:\Program Files but yours may be on C:\ or another drive
# Standard path: <DRIVE>:\Program Files\Microsoft Visual Studio\2022\Community\Common7\Tools\Launch-VsDevShell.ps1

# Configure and build VR preset (adjust path to your VS installation)
powershell.exe "& '<DRIVE>:\Program Files\Microsoft Visual Studio\2022\Community\Common7\Tools\Launch-VsDevShell.ps1' -Arch amd64; cmake --preset build-release-msvc-vcpkg-vr; cmake --build build/release-msvc-vcpkg-vr"

# Example with F: drive:
powershell.exe "& 'F:\Program Files\Microsoft Visual Studio\2022\Community\Common7\Tools\Launch-VsDevShell.ps1' -Arch amd64; cmake --preset build-release-msvc-vcpkg-vr; cmake --build build/release-msvc-vcpkg-vr"

# Configure and build ALL preset (SE + AE + VR)
powershell.exe "& '<DRIVE>:\Program Files\Microsoft Visual Studio\2022\Community\Common7\Tools\Launch-VsDevShell.ps1' -Arch amd64; cmake --preset build-release-msvc-vcpkg-all; cmake --build build/release-msvc-vcpkg-all"

# Configure and build FLATRIM preset (SE + AE, no VR)
powershell.exe "& '<DRIVE>:\Program Files\Microsoft Visual Studio\2022\Community\Common7\Tools\Launch-VsDevShell.ps1' -Arch amd64; cmake --preset build-release-msvc-vcpkg-flatrim; cmake --build build/release-msvc-vcpkg-flatrim"

# Run tests (from Windows side after build)
powershell.exe "ctest --preset all"
```

### Building from Native Windows

```powershell
# Option 1: Launch VS Developer PowerShell manually, then run:
cmake --preset build-release-msvc-vcpkg-all
cmake --build build/release-msvc-vcpkg-all

# Option 2: Use VS Dev Shell launcher in one command (adjust path to your VS installation):
& "<DRIVE>:\Program Files\Microsoft Visual Studio\2022\Community\Common7\Tools\Launch-VsDevShell.ps1" -Arch amd64
cmake --preset build-release-msvc-vcpkg-vr
cmake --build build/release-msvc-vcpkg-vr
```

### Building via Linux-host cross-compile

Targets the same Windows PE/MSVC ABI output as the presets above, using
`clang-cl`+`lld-link` against an `xwin`-generated Windows SDK/CRT
sysroot instead of a real MSVC install. Runs from an ordinary Linux
shell, no VS Developer Shell or Windows tooling involved at all.

```bash
cmake --preset build-release-linux-clangcl-vcpkg-all
cmake --build --preset release-linux-clangcl-vcpkg-all
```

One-time host setup (xwin, Wine, llvm-mingw, vcpkg) and the reasoning
behind each piece are documented in `examples/linux-cross-compile/README.md`.
A clean build proves the toolchain, not runtime correctness: struct
layout or vtable mismatches between clang-cl output and the real MSVC
game binary compile fine and only surface as an in-game crash.

### Package Manager
The project uses Vcpkg for dependency management:
- **Vcpkg**: All presets use `-vcpkg-` in the name
- Dependencies are defined in `vcpkg.json`

### Runtime-Specific Builds
Available runtime configurations:
- `all`: Supports SE, AE, and VR
- `flatrim`: SE and AE only (no VR)
- `vr`: VR only
- `se`: SE only
- `ae`: AE only

### Test Categories
- **Unit tests**: `[unit]` - No Skyrim module required
- **Integration tests**: `[integration]` - Skyrim module at rest
- **End-to-end tests**: `[e2e]` - Full Skyrim engine required

## Code Architecture

### Directory Structure
- `include/RE/`: Reverse-engineered Skyrim classes organized alphabetically
- `include/REL/`: Address Library integration and relocation utilities
- `include/REX/`: Cross-platform abstraction layer
- `include/SKSE/`: SKSE plugin framework interfaces
- `src/`: Implementation files mirroring the include structure
- `tests/`: Unit and integration tests using Catch2

### Key Components
- **RE namespace**: Skyrim engine classes (Actor, TESForm, etc.)
- **REL namespace**: Address resolution and version management
- **SKSE namespace**: Plugin lifecycle, event systems, and serialization
- **BST containers**: Bethesda's STL-like container classes
- **Havok integration**: Physics system bindings

### Plugin Declaration
Use the simplified CMake function instead of manual plugin setup:
```cmake
find_package(CommonLibSSE REQUIRED)
add_commonlibsse_plugin(${PROJECT_NAME} SOURCES ${sources})
target_link_libraries(${PROJECT_NAME} PUBLIC CommonLibSSE::CommonLibSSE)
```

## Dependencies and Requirements

### Build Dependencies
- Visual Studio 2022 with C++ Desktop Development
- CMake 3.19+
- Vcpkg or Conan
- Address Library for target runtimes

### C++ Standard
The project uses **C++23** (`cxx_std_23` is set in CMakeLists.txt)

### Address Library Integration
Essential for cross-version compatibility:
- SE: Address Library for SKSE Plugins
- VR: VR Address Library for SKSEVR
- Version detection and offset resolution handled automatically

## Development Workflow

### Making Changes
1. Understand the multi-runtime implications of your changes
2. Use runtime feature detection when accessing version-specific functionality
3. Follow existing patterns for BST containers and Skyrim conventions
4. Run unit tests before integration tests
5. Test across different runtime configurations when possible

### Testing Strategy
- Write unit tests for logic that doesn't require Skyrim
- Use integration tests for Skyrim API interactions
- Reserve e2e tests for full engine functionality
- Tests can load different Skyrim executables for cross-runtime validation

### Code Organization
- Reverse-engineered classes follow Skyrim's naming conventions
- Use RTTI information for class hierarchies and virtual functions
- Address Library IDs are managed through REL::ID system
- Cross-runtime code uses feature detection patterns

### Multi-Runtime Conditional Patterns

CommonLibSSE NG handles runtime differences using two main conditional patterns:

#### Pattern 1: Runtime-Exclusive Virtual Functions

Use this pattern when a class has the **same base class** across runtimes, but **different virtual functions** exist in different runtimes.

**Example:** Camera state classes all inherit from `TESCameraState`, but VR has an extra `Unk_03()` virtual function that SE/AE don't have.

**For runtime-exclusive virtual functions (e.g., VR-only camera state `Unk_03()`):**

**Base Class Pattern:**
```cpp
// Header (.h file) - Three-way conditional pattern
#if defined(EXCLUSIVE_SKYRIM_FLAT)
    // Function doesn't exist in SE/AE-only builds
#elif defined(EXCLUSIVE_SKYRIM_VR)
    virtual void Unk_03();  // 03 - VR only
#else
    void Unk_03();          // 03 - Multi-runtime (non-virtual)
#endif

// Implementation (.cpp file)
#ifdef SKYRIM_CROSS_VR
    void ClassName::Unk_03()
    {
        if (REL::Module::IsVR()) {
            REL::RelocateVirtual<decltype(&ClassName::Unk_03)>(0x03, 0x03, this);
        }
        // SE/AE: no-op, this function should never be called
    }
#endif
```

**Derived Class Pattern:**
```cpp
// Header (.h file) - Must match base class pattern
#if defined(EXCLUSIVE_SKYRIM_FLAT)
    // Function doesn't exist in SE/AE-only builds
#elif defined(EXCLUSIVE_SKYRIM_VR)
    void Unk_03() override;  // 03 - VR only
#else
    void Unk_03();           // 03 - Multi-runtime
#endif

// Implementation (.cpp file) - Same as base class
#ifdef SKYRIM_CROSS_VR
    void DerivedClass::Unk_03()
    {
        if (REL::Module::IsVR()) {
            REL::RelocateVirtual<decltype(&DerivedClass::Unk_03)>(0x03, 0x03, this);
        }
        // SE/AE: no-op, this function should never be called
    }
#endif
```

**CRITICAL: Vtable Slot Alignment**

When a runtime-exclusive function exists, ALL virtual functions that come after it in the inheritance hierarchy get shifted in the vtable:

```cpp
// SE/AE vtable: Begin(01) -> End(02) -> Update(03) -> GetRotation(04)
// VR vtable:    Begin(01) -> End(02) -> Unk_03(03) -> Update(04) -> GetRotation(05)
```

**Every derived class that overrides functions after a runtime-exclusive function MUST implement RelocateVirtual for those functions:**

```cpp
#ifdef SKYRIM_CROSS_VR
    void DerivedClass::Update(BSTSmartPointer<TESCameraState>& a_nextState)
    {
        REL::RelocateVirtual<decltype(&DerivedClass::Update)>(0x03, 0x04, this, a_nextState);
        //                                                    SE^   VR^ (shifted by Unk_03)
    }

    void DerivedClass::GetRotation(NiQuaternion& a_rotation)
    {
        REL::RelocateVirtual<decltype(&DerivedClass::GetRotation)>(0x04, 0x05, this, a_rotation);
        //                                                         SE^   VR^ (shifted by Unk_03)
    }
#endif
```

**Build behavior:**
- **EXCLUSIVE_SKYRIM_FLAT** (SE/AE-only): Function doesn't exist, no vtable shift
- **EXCLUSIVE_SKYRIM_VR** (VR-only): Function declared as virtual, engine provides implementation
- **Multi-runtime** (ALL/FLATRIM): Function uses RelocateVirtual with runtime detection

**Note:** This pattern works for any runtime-exclusive function (VR-only, SE-only, AE-only, etc.), though VR-only functions are the most common case.

**Do NOT use `SKYRIM_REL_VR_VIRTUAL` for runtime-exclusive functions** - it breaks vtable alignment in multi-runtime builds. Use `SKYRIM_REL_VR_VIRTUAL` only for functions that exist across all runtimes but may need different calling conventions.

#### Pattern 2: Runtime-Exclusive Inheritance

Use this pattern when a class has **completely different base classes** in different runtimes.

**Example:** `ButtonEvent` inherits from `VRWandEvent` in VR but from `IDEvent` in SE/AE. `HUDMenu` inherits from `WorldSpaceMenu` in VR but from `IMenu` in SE/AE.

**Inheritance Pattern:**
```cpp
// Header (.h file) - Three-way conditional inheritance
class ClassName :
#if defined(EXCLUSIVE_SKYRIM_VR)
    public VROnlyBaseClass,
    public SharedBaseClass1,
    public SharedBaseClass2
#elif !defined(ENABLE_SKYRIM_VR)  // SE/AE-only
    public SEAEOnlyBaseClass,
    public SharedBaseClass1,
    public SharedBaseClass2
#else
    // Multi-runtime: can't inherit from incompatible base classes
    public CommonBaseClass  // Choose most compatible base
#endif
{
public:
    // Upcast functions for multi-runtime builds
    [[nodiscard]] VROnlyBaseClass* AsVROnlyBaseClass() noexcept
    {
        if SKYRIM_REL_CONSTEXPR (!REL::Module::IsVR()) {
            return nullptr;
        }
        return &REL::RelocateMember<VROnlyBaseClass>(this, 0, 0);
    }

    [[nodiscard]] SEAEOnlyBaseClass* AsSEAEOnlyBaseClass() noexcept
    {
        if SKYRIM_REL_CONSTEXPR (REL::Module::IsVR()) {
            return nullptr;
        }
        return &REL::RelocateMember<SEAEOnlyBaseClass>(this, 0, 0);
    }
};
```

**Critical:** Use `!defined(ENABLE_SKYRIM_VR)` for SE/AE-only case, not just `#else`, to ensure proper compilation across all preset types.

**Build behavior:**
- **EXCLUSIVE_SKYRIM_VR** (VR-only): Inherits from VR-specific base classes
- **SE/AE-only builds**: Inherits from SE/AE-specific base classes
- **Multi-runtime** (ALL): Inherits from most compatible base, provides upcast functions that return nullptr when invalid

#### Pattern 3: Chained Inheritance Access

Use this pattern when you need to access base class functionality through a **chain of inheritance** that differs between runtimes.

**Example:** `ButtonEvent` needs access to `IDEvent` members, but:
- **VR**: `ButtonEvent` → `VRWandEvent` → `IDEvent` → `InputEvent`
- **SE/AE**: `ButtonEvent` → `IDEvent` → `InputEvent`
- **Multi-runtime**: `ButtonEvent` → `InputEvent` (no direct inheritance relationship to `IDEvent`)

**Access Function Pattern:**
```cpp
[[nodiscard]] IDEvent* AsIDEvent() noexcept
{
#if defined(EXCLUSIVE_SKYRIM_VR)
    // VR builds: Navigate through VRWandEvent to reach IDEvent
    return static_cast<IDEvent*>(static_cast<VRWandEvent*>(this));
#elif !defined(ENABLE_SKYRIM_VR)
    // SE/AE builds: Direct inheritance from IDEvent
    return static_cast<IDEvent*>(this);
#else
    // Multi-runtime builds: No inheritance relationship, use RelocateMember
    return &REL::RelocateMember<IDEvent>(this, 0, 0);
#endif
}

// Accessor functions that work across all runtimes
[[nodiscard]] std::uint32_t GetIDCode() const noexcept
{
    if (auto idEvent = AsIDEvent()) {
        return idEvent->idCode;
    }
    return 0;  // Fallback for invalid cases
}

void SetIDCode(std::uint32_t a_idCode)
{
    if (auto idEvent = AsIDEvent()) {
        idEvent->idCode = a_idCode;
    }
}
```

**Key Points:**
- **Single-runtime builds**: Use efficient `static_cast` following known inheritance chains
- **Multi-runtime builds**: Use `RelocateMember` since inheritance relationship doesn't exist at compile time
- **Always validate**: Check return values from upcast functions for safety
- **Consistent API**: Accessor functions provide the same interface regardless of runtime

**Build behavior:**
- **EXCLUSIVE_SKYRIM_VR**: Uses double static_cast through inheritance chain
- **SE/AE-only builds**: Uses direct static_cast
- **Multi-runtime**: Uses RelocateMember for runtime-specific memory layout access

#### Multi-Runtime Architecture Patterns

CommonLibSSE NG uses different abstraction patterns based on the type and complexity of runtime differences:

**Virtual Functions (Explicit Pattern - Recommended):**
- Use three-way conditionals for clarity and maintainability
- Virtual functions are relatively rare, so explicit patterns don't create significant maintenance burden
- Clear separation between runtime-exclusive and cross-runtime functions

**Data Structures (Macro Pattern - Established):**
- Use `RUNTIME_DATA_CONTENT` macros for complex structural differences
- Beneficial when multiple large structs have significant layout differences
- Examples: `HUDMenu`, `State`, `BGSShaderParticleGeometryData`

**Inheritance (Three-way Conditional):**
- Use explicit conditionals for different base class hierarchies
- Example: VR's `WorldSpaceMenu` vs SE/AE's `IMenu` inheritance

**Individual Members (Mixed Approach):**
- Simple exclusions: `#ifndef SKYRIM_CROSS_VR`
- Type differences: Three-way conditionals
- Runtime detection: Use `REL::Module::IsVR()` when both layouts exist

**Maintainability Guidelines:**
- Prefer explicit patterns for infrequent changes (virtual functions)
- Use macro abstraction for repetitive complex patterns (data structures)
- Document offset calculations and Address Library relationships
- Standardize member accessor patterns using `RelocateMember`
## CommonLibSSE-NG Code Conventions & Best Practices

### Virtual Function Implementation Guidelines

**CRITICAL**: Always verify virtual function signatures match the base class exactly, including all parameters.

**Common Mistakes to Avoid:**

1. **Incorrect Override Declarations**
   - **WRONG:** Adding `override` when function doesn't actually override
   - **CORRECT:** Only use `override` when signature exactly matches base class

   ```cpp
   // Base class: void OnVisible(NiCullingProcess&, std::int32_t)

   // WRONG - missing parameter, doesn't actually override
   void OnVisible(NiCullingProcess& a_process) override;

   // CORRECT - matches base class signature
   void OnVisible(NiCullingProcess& a_process, std::int32_t a_alphaGroupIndex) override;
   ```

2. **Three-Way Conditional Pattern**
   - Always use the standard pattern for runtime-exclusive virtual functions:

   ```cpp
   #if defined(EXCLUSIVE_SKYRIM_FLAT)
       void MyFunction() override;  // SE/AE only - virtual
   #elif defined(EXCLUSIVE_SKYRIM_VR)
       // VR has different vtable - function doesn't exist
   #else
       void MyFunction();  // Multi-runtime - non-virtual wrapper
   #endif
   ```

3. **Static Assert Patterns**
   - Use conditional `static_assert` for classes with three-way conditionals:

   ```cpp
   #if defined(EXCLUSIVE_SKYRIM_FLAT)
       static_assert(sizeof(MyClass) == 0x170);
   #endif
   ```

   - Use `STATIC_ASSERT_SIZE` macro only for simple multi-runtime structs without conditional members

### Resource Management

1. **REL::Relocation Must Be Static**
   - **WRONG:** `REL::Relocation<Type*> singleton{ REL::ID(12345) };`
   - **CORRECT:** `static REL::Relocation<Type*> singleton{ REL::ID(12345) };`

   Static ensures singleton is initialized once and persists across calls.

2. **Runtime Data Accessor Pattern**
   - Classes with `RUNTIME_DATA_CONTENT` macros must use accessor functions:

   ```cpp
   // WRONG - direct member access fails in multi-runtime builds
   this->root.Invoke("method", &result);

   // CORRECT - use GetRuntimeData() accessor
   auto runtimeData = GetRuntimeData();
   runtimeData.root.Invoke("method", &result);
   ```

### File Organization

1. **Empty Implementation Files**
   - Delete `.cpp` files that only contain comments or boilerplate
   - Update `cmake/sourcelist.cmake` when removing files
   - If methods are inline in header, no `.cpp` needed

2. **Implementation Files for Multi-Runtime**
   - Virtual function wrappers for multi-runtime builds need `.cpp` files
   - Always guard with `#ifdef SKYRIM_CROSS_VR`
   - Use `REL::RelocateVirtual` to dispatch to correct runtime vtable

### Comments and Documentation

1. **No Version Difference Comments**
   - **WRONG:** `// Moved to OtherFile.h`
   - **WRONG:** `float member; // 0x158 in SE/AE, 0x110 in VR`
   - **CORRECT:** `float member; // 158 / 110` (standard offset format)

2. **Keep Comments Minimal**
   - Only add comments explaining *why*, not *what*
   - Virtual function slot numbers are sufficient: `void Update() override; // 05`
   - Remove TODO comments after issues are resolved

### Common Build Errors and Solutions

**Error: "method with override specifier 'override' did not override any base class methods"**
- **Cause**: Function signature doesn't match base class
- **Solution**: Check base class signature, ensure all parameters match exactly

**Error: "is not a member of [class]"**
- **Cause**: Trying to access RUNTIME_DATA members directly in multi-runtime builds
- **Solution**: Use `GetRuntimeData()` accessor function

**Error: "overloaded member function not found"**
- **Cause**: Header declaration and implementation parameter count mismatch
- **Solution**: Ensure `.cpp` implementation matches header declaration exactly

**Error: "static assertion failed" (size mismatch)**
- **Cause**: Class size doesn't match expected size for current build configuration
- **Solution**:
  1. Verify member offsets and padding
  2. Check if using correct size for SE/AE vs VR vs multi-runtime
  3. Use `#if defined(EXCLUSIVE_SKYRIM_FLAT)` pattern for conditional assertions

### Testing Workflow for AI Agents

1. **Use the Build Script**
   ```bash
   .\scripts\build-all-presets.cmd
   ```
   - Stops at first error for fast iteration
   - Shows only error messages
   - Tests all runtime configurations

2. **Incremental Testing**
   - Fix errors one at a time
   - Run build script after each fix
   - Don't proceed to next error until current one is resolved

3. **Multi-Runtime Verification**
   - Changes affecting virtual functions MUST be tested in all presets
   - VR, Flatrim (SE+AE), and All presets can have different compilation results
   - Runtime data access patterns are especially critical in All preset

### Quick Reference: Preprocessor Defines

- `ENABLE_SKYRIM_SE` - SE runtime support enabled
- `ENABLE_SKYRIM_AE` - AE runtime support enabled
- `ENABLE_SKYRIM_VR` - VR runtime support enabled
- `EXCLUSIVE_SKYRIM_FLAT` - Only SE/AE enabled (no VR)
- `EXCLUSIVE_SKYRIM_VR` - Only VR enabled (no SE/AE)
- `SKYRIM_CROSS_VR` - Both VR and (SE or AE) enabled (multi-runtime)

**Build Preset Combinations:**
- `se`: Only `ENABLE_SKYRIM_SE`, defines `EXCLUSIVE_SKYRIM_FLAT`
- `ae`: Only `ENABLE_SKYRIM_AE`, defines `EXCLUSIVE_SKYRIM_FLAT`
- `vr`: Only `ENABLE_SKYRIM_VR`, defines `EXCLUSIVE_SKYRIM_VR`
- `flatrim`: `ENABLE_SKYRIM_SE` + `ENABLE_SKYRIM_AE`, defines `EXCLUSIVE_SKYRIM_FLAT`
- `all`: All three enabled, defines `SKYRIM_CROSS_VR`


