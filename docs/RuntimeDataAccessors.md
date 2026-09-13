# Runtime Data Accessors

This document describes the helper macros and tooling for managing runtime data structures in CommonLibSSE-NG.

## Overview

CommonLibSSE-NG supports multiple Skyrim runtimes (SE, AE, VR) with different memory layouts. Runtime data accessors provide a consistent API to access data at runtime-specific offsets without manual `RelocateMember` calls.

## Macro Reference

### Basic Accessors

#### `RUNTIME_DATA_ACCESSOR(StructType, SEOffset, VROffset)`
Standard accessor with default name `GetRuntimeData`.
```cpp
struct RUNTIME_DATA { /*...*/ };
RUNTIME_DATA_ACCESSOR(RUNTIME_DATA, 0x40, 0x48);
// Generates: GetRuntimeData() for both const and non-const
```

#### `RUNTIME_DATA_ACCESSOR_EX(StructType, FuncName, SEOffset, VROffset)`
Custom function name variant.
```cpp
RUNTIME_DATA_ACCESSOR_EX(GEOMETRY_DATA, GetGeometryRuntimeData, 0xDA0, 0x1570);
// Generates: GetGeometryRuntimeData()
```

### Version-Gated Accessors

#### `RUNTIME_DATA_ACCESSOR_VERSIONED(StructType, Version, OldOffset, NewOffset)`
For SE/AE version differences.
```cpp
RUNTIME_DATA_ACCESSOR_VERSIONED(PLAYER_RUNTIME_DATA, SKSE::RUNTIME_SSE_1_6_629, 0x3D8, 0x3E0);
// Uses OldOffset for SE < 1.6.629, NewOffset for SE >= 1.6.629 and AE
```

### Pointer Member Accessors

#### `RUNTIME_DATA_POINTER_ACCESSOR_EX(PointerType, FuncName, SEOffset, VROffset)`
For pointer members (returns pointer by value, not reference).
```cpp
RUNTIME_DATA_POINTER_ACCESSOR_EX(TESRegionDataManager*, GetRegionDataManager, 0xDB0, 0x1580);
// Generates: TESRegionDataManager* GetRegionDataManager()
```

**Note:** Use this for pointer members (`T* member`), not struct members (`T member`). Struct members should use `RUNTIME_DATA_ACCESSOR_EX`.

### Three-Runtime Accessors (SE/AE/VR)

#### `RUNTIME_MEMBER_ACCESSOR_VERSIONED(StructType, FuncName, Version, SEOffset, VROffset, AEOffset)`
For members with different offsets in SE, AE, and VR.
```cpp
RUNTIME_MEMBER_ACCESSOR_VERSIONED(DepthStencilRuntimeData, GetDepthStencilData, 
                                  SKSE::RUNTIME_SSE_1_6_1130, 0x1FB8, 0x21D0, 0x2018);
// SE < 1.6.1130: 0x1FB8, VR: 0x21D0, AE >= 1.6.1130: 0x2018
```

### Runtime-Exclusive Accessors

#### `VR_RUNTIME_DATA_ACCESSOR(StructType, FuncName, VROffset)`
**Only available when VR is enabled.** Use for VR-specific data structures.
```cpp
struct VR_RUNTIME_DATA { /*...*/ };
VR_RUNTIME_DATA_ACCESSOR(VR_RUNTIME_DATA, GetVRRuntimeData, 0x40);
// Accessor only exists in VR builds (ENABLE_SKYRIM_VR defined)
```

**Note:** For SE/AE-exclusive pointer accessors, use `SE_ONLY_POINTER_ACCESSOR` (documented below).

### Runtime Cast Accessors

#### `RUNTIME_CAST_ACCESSOR(StructType, FuncName, SEOffset, VROffset)`
Provides cast-like access to base classes at runtime-specific offsets. In single-runtime builds (VR-only or FLATRIM-only), these types are actual base classes. In multi-runtime builds, they can't be in the inheritance hierarchy due to offset differences, so this macro provides consistent cast API access to the memory location.

**IMPORTANT**: This macro should be used alongside conditional inheritance. The types and offsets must match:

```cpp
class TESAmmo :
    public TESBoundObject,
    // ... other bases ...
#if defined(EXCLUSIVE_SKYRIM_FLAT)
    , public BGSDestructibleObjectForm,  // 0xC0
    public BGSPickupPutdownSounds       // 0xD0
#elif defined(EXCLUSIVE_SKYRIM_VR)
    , public BGSDestructibleObjectForm,  // 0xB0
    public BGSPickupPutdownSounds       // 0xC0
#endif
{
    // Cast accessors match the conditional bases above
    RUNTIME_CAST_ACCESSOR(BGSDestructibleObjectForm, AsDestructibleObjectForm, 0xC0, 0xB0);
    RUNTIME_CAST_ACCESSOR(BGSPickupPutdownSounds, AsPickupPutdownSoundsForm, 0xD0, 0xC0);
    // StructType matches inheritance, SEOffset matches FLAT offset, VROffset matches VR offset
};
```

**Why both?** Single-runtime builds can use actual inheritance (efficient static_cast). Multi-runtime builds use RelocateMember since they can't inherit from both layouts simultaneously. The accessor provides a consistent API for both cases.

#### `VR_ONLY_POINTER_ACCESSOR(StructType, FuncName, VROffset)`
Returns pointer in VR, `nullptr` in SE/AE. Available in all builds.
```cpp
VR_ONLY_POINTER_ACCESSOR(VR_INFO_RUNTIME_DATA, GetVRInfoRuntimeData, 0x8E4);
// Returns pointer in VR, nullptr in SE/AE (safe for runtime checks)
```

#### `SE_ONLY_POINTER_ACCESSOR(StructType, FuncName, SEOffset)`
Returns pointer in SE/AE, `nullptr` in VR. Available in all builds.
```cpp
SE_ONLY_POINTER_ACCESSOR(BSTEventSource<TESFastTravelEndEvent>, AsTESFastTravelEndEventSource, 0x1238);
// Returns pointer in SE/AE, nullptr in VR
```

## Usage Patterns

### Pattern 1: Cross-Runtime Data (Same Structure, Different Offsets)
```cpp
struct RUNTIME_DATA {
#define RUNTIME_DATA_CONTENT \
    float value;     /* SE 0x10, VR 0x18 */ \
    int   count;     /* SE 0x14, VR 0x1C */
    RUNTIME_DATA_CONTENT
};

RUNTIME_DATA_ACCESSOR(RUNTIME_DATA, 0x10, 0x18);

// Members stored differently per build:
#if defined(EXCLUSIVE_SKYRIM_VR)
    RUNTIME_DATA_CONTENT;  // VR: members at 0x18
#else
    RUNTIME_DATA_CONTENT;  // SE/AE: members at 0x10
#endif
```

### Pattern 2: VR-Exclusive Data
```cpp
struct RUNTIME_DATA {
#define RUNTIME_DATA_CONTENT \
    NiPoint3  coords; /* VR 0x20 */ \
    uint16_t  unk2c;  /* VR 0x2C */
    RUNTIME_DATA_CONTENT
};

#if defined(EXCLUSIVE_SKYRIM_VR)
    RUNTIME_DATA_CONTENT;  // Only in VR builds
#endif
VR_RUNTIME_DATA_ACCESSOR(RUNTIME_DATA, GetRuntimeData, 0x20);
// Accessor doesn't exist in FLATRIM builds
```

### Pattern 3: Different Structures Per Runtime
```cpp
struct RUNTIME_DATA {  // SE/AE structure
    float seValue;
};

struct VR_RUNTIME_DATA {  // VR structure  
    double vrValue;
};

// Two separate accessors:
RUNTIME_DATA_ACCESSOR_EX(RUNTIME_DATA, GetRuntimeData, 0x40, 0);
VR_RUNTIME_DATA_ACCESSOR(VR_RUNTIME_DATA, GetVRRuntimeData, 0x40);
```

## Conversion Tools

### VSCode Snippets

Snippets are available in `.vscode/commonlibvr.code-snippets`:

- `runtime_data_content` - Create macro with SE/VR offsets
- `convert_member` - Convert single member to macro format
- `runtime_data_struct` - Complete struct with accessor
- `vr_exclusive_data` - VR-exclusive struct template

### Quick Conversion: Find & Replace

When pulling from upstream, use VSCode's regex find & replace (Ctrl+H):

**For same offsets (most common case):**
- Find: `^(\s+)(.+?)\s+(\w+);\s*//\s*([0-9A-Fa-fx]+)`
- Replace: `$1$2 $3; /* SE $4, VR $4 */ \\`

**Example:**
```cpp
// Before (upstream):
    float value;  // 0x10
    int count;    // 0x14

// After (apply regex, then add #define):
    float value; /* SE 0x10, VR 0x10 */ \
    int count;   /* SE 0x14, VR 0x14 */
```

Then manually wrap with `#define RUNTIME_DATA_CONTENT \` and remove trailing `\` from last line.

**For offset shifts** (rare - when VR differs):
Only do manual conversion if you know VR offsets differ from SE. Most upstream structures have identical offsets.

## When to Use Each Macro

| Scenario | Macro to Use |
|----------|--------------|
| Same structure, different offsets | `RUNTIME_DATA_ACCESSOR` |
| Custom accessor name needed | `RUNTIME_DATA_ACCESSOR_EX` |
| SE/AE version difference | `RUNTIME_DATA_ACCESSOR_VERSIONED` |
| VR-only data (doesn't exist in SE/AE) | `VR_RUNTIME_DATA_ACCESSOR` |
| VR-only pointer (safe runtime check) | `VR_ONLY_POINTER_ACCESSOR` |
| SE-only pointer (safe runtime check) | `SE_ONLY_POINTER_ACCESSOR` |
| Three-way offsets (SE/AE/VR all differ) | `RUNTIME_MEMBER_ACCESSOR_VERSIONED` |
| Pointer member accessor | `RUNTIME_DATA_POINTER_ACCESSOR_EX` |

## Merging from Upstream CommonLibSSE

When syncing with upstream CommonLibSSE, you may encounter conflicts with accessor macros:

### Common Scenarios

1. **Upstream adds new virtual functions**: Usually merges cleanly (different lines)
2. **Upstream adds new base classes with "As" accessors**: Need manual conversion
3. **Upstream changes offsets**: Update macro parameters

### Converting New Upstream Accessors

When upstream adds new cast accessors, convert using this pattern:

**Upstream adds:**
```cpp
[[nodiscard]] inline NewBaseClass* AsNewBaseClass() noexcept
{
    return &REL::RelocateMember<NewBaseClass>(this, 0xXX, 0xYY);
}

[[nodiscard]] inline const NewBaseClass* AsNewBaseClass() const noexcept
{
    return const_cast<ClassName*>(this)->AsNewBaseClass();
}
```

**Convert to:**
```cpp
RUNTIME_CAST_ACCESSOR(NewBaseClass, AsNewBaseClass, 0xXX, 0xYY);
```

### Regex for Quick Conversion

Use this VSCode regex to convert upstream accessors:

**Find:**
```regex
\[\[nodiscard\]\] inline (\w+)\* (As\w+)\(\) noexcept\s*\{[^\}]*RelocateMember<\1>\(this, (0x[0-9A-F]+), (0x[0-9A-F]+)\);[^\}]*\}[^\}]*\[\[nodiscard\]\] inline const \1\* \2\(\) const noexcept[^\}]*\}
```

**Replace:**
```
RUNTIME_CAST_ACCESSOR($1, $2, $3, $4);
```

## Related: Static Size Assertions

When using runtime data accessors, you'll often need to validate class sizes across runtimes. Use `STATIC_ASSERT_SIZE` from `REL/Common.h`:

```cpp
// Single size for all runtimes
STATIC_ASSERT_SIZE(MyClass, 0x100);

// Different sizes for Flat vs VR
STATIC_ASSERT_SIZE(CursorMenu, 0x40, 0x50);  // Flat=0x40, VR=0x50

// SE, AE, VR specified
STATIC_ASSERT_SIZE(PlayerCharacter, 0xBE0, 0x9A8, 0x12F0);

// All five presets specified
STATIC_ASSERT_SIZE(ButtonEvent, 0x30, 0x30, 0x38, 0x18, 0x20);
//                               SE    AE    VR    ALL   FLAT
```

**Benefits:**
- Single line replaces conditional `#ifdef` blocks
- Provides detailed error messages showing all sizes
- Use `0x0` for unknown sizes (assertion skipped for that preset)

See `REL/Common.h` for full documentation and examples.

## Implementation Notes

- All reference-returning macros generate both const and non-const overloads
- Pointer-returning macros use `SKYRIM_REL_CONSTEXPR` for compile-time optimization
- Accessor macros reduce merge conflicts by consolidating multi-line patterns into single lines
- Macro-generated accessors automatically handle runtime detection via `REL::Module::IsVR()`

## Examples in Codebase

- **FastTravelConfirmCallback** - VR-exclusive data using `VR_RUNTIME_DATA_ACCESSOR`
- **PlayerCamera** - Different structures per runtime with separate accessors
- **TESDataHandler** - Version-gated accessor with `RUNTIME_DATA_ACCESSOR_VERSIONED_EX`
- **Actor** - Cross-runtime data with `RUNTIME_DATA_ACCESSOR_VERSIONED`
