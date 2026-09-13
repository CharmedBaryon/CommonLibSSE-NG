#pragma once

#include <cassert>
#include <cstddef>
#include <type_traits>

#include "REL/Relocation.h"
#include "SKSE/Version.h"

namespace REL
{
	/**
	 * Applies the byte/slot shift required when a Skyrim runtime update inserts an
	 * additional base class/vtable slot, pushing every member or virtual function
	 * declared after it forward by a fixed amount on builds at or above a_threshold.
	 *
	 * <p>
	 * Neither a_delta nor a_threshold has a default -- both are per-class RE facts
	 * (a member shift is a byte count, a vtable slot index shifts by however many
	 * slots were inserted) and must be confirmed per call site rather than assumed.
	 * </p>
	 */
	[[nodiscard]] SKYRIM_REL std::size_t VersionShift(std::size_t a_offset, std::size_t a_delta, REL::Version a_threshold) noexcept
	{
		return REL::Module::IsAtLeast(a_threshold) ? a_offset + a_delta : a_offset;
	}
}

// Helper macros for generating runtime data accessor functions.
// These reduce boilerplate for common patterns across ~160+ accessor function pairs.
// See docs/RuntimeDataAccessors.md for usage documentation.
//
// MACRO CATEGORIES:
// 1. Struct/Value Accessors - Return references to struct/value members
// 2. Pointer Accessors - Return pointers by value for pointer members
// 3. Cast Accessors - Provide runtime-aware base class access
// 4. Runtime-Exclusive Accessors - VR-only or SE-only members
//
// NAMING CONVENTION:
// - RUNTIME_DATA_* = Struct/value member accessors (returns T&)
// - RUNTIME_DATA_POINTER_* = Pointer member accessors (returns T*)
// - RUNTIME_CAST_* = Base class cast accessors (returns T*)
// - *_ONLY_* = Runtime-exclusive accessors (VR_ONLY, SE_ONLY)
// - *_VERSIONED* = Handles SE vs AE version differences
// - *_EX = Extended version with custom function name

// ========================================
// Struct/Value Member Accessors
// ========================================

// Generates GetXXX() accessor with SE/VR offsets
// Params: StructType, FuncName, SEOffset, VROffset
// VROffset=0 means "no VR layout" -- misuse would silently read `this + 0`
// as StructType instead of failing loudly, so this asserts on it in VR.
#define RUNTIME_DATA_ACCESSOR_EX(StructType, FuncName, SEOffset, VROffset)                             \
	[[nodiscard]] inline StructType& FuncName() noexcept                                               \
	{                                                                                                  \
		assert(!((VROffset) == 0 && REL::Module::IsVR()) &&                                            \
			   #FuncName "() has no VR layout (VROffset=0) -- call GetVRRuntimeData() instead in VR"); \
		return REL::RelocateMember<StructType>(this, SEOffset, VROffset);                              \
	}                                                                                                  \
	[[nodiscard]] inline const StructType& FuncName() const noexcept                                   \
	{                                                                                                  \
		assert(!((VROffset) == 0 && REL::Module::IsVR()) &&                                            \
			   #FuncName "() has no VR layout (VROffset=0) -- call GetVRRuntimeData() instead in VR"); \
		return REL::RelocateMember<StructType>(this, SEOffset, VROffset);                              \
	}

// Generates GetXXX() accessor with SE old/AE new version gate
// Params: StructType, FuncName, Version, OldOffset, NewOffset (both SE/AE, same VR offset)
#define RUNTIME_DATA_ACCESSOR_VERSIONED_EX(StructType, FuncName, Version, OldOffset, NewOffset) \
	[[nodiscard]] inline StructType& FuncName() noexcept                                        \
	{                                                                                           \
		return REL::RelocateMemberIfNewer<StructType>(Version, this, OldOffset, NewOffset);     \
	}                                                                                           \
	[[nodiscard]] inline const StructType& FuncName() const noexcept                            \
	{                                                                                           \
		return REL::RelocateMemberIfNewer<StructType>(Version, this, OldOffset, NewOffset);     \
	}

// Standard name variants (use "GetRuntimeData" by default)

// Simple accessor with standard "GetRuntimeData" name
// Usage: RUNTIME_DATA_ACCESSOR(RUNTIME_DATA, 0x30, 0x40)
#define RUNTIME_DATA_ACCESSOR(StructType, SEOffset, VROffset) \
	RUNTIME_DATA_ACCESSOR_EX(StructType, GetRuntimeData, SEOffset, VROffset)

// Convenience: Same as _VERSIONED_EX but uses "GetRuntimeData" name
// Params: StructType, Version, OldOffset, NewOffset
#define RUNTIME_DATA_ACCESSOR_VERSIONED(StructType, Version, OldOffset, NewOffset) \
	RUNTIME_DATA_ACCESSOR_VERSIONED_EX(StructType, GetRuntimeData, Version, OldOffset, NewOffset)

// Generates a GetXXX() accessor for a field/struct with no pre-Version offset -- nullptr on older runtimes.
// Params: StructType, FuncName, Version, Offset (absolute, from `this`)
// No plain (non-_EX) variant: a name shared across multiple appendices on one class would collide.
#define RUNTIME_DATA_ACCESSOR_VERSIONED_OPTIONAL_EX(StructType, FuncName, Version, Offset) \
	[[nodiscard]] inline StructType* FuncName() noexcept                                   \
	{                                                                                      \
		if (!REL::Module::IsAtLeast(Version)) {                                            \
			return nullptr;                                                                \
		}                                                                                  \
		return &REL::RelocateMember<StructType>(this, Offset);                             \
	}                                                                                      \
	[[nodiscard]] inline const StructType* FuncName() const noexcept                       \
	{                                                                                      \
		return const_cast<std::remove_cvref_t<decltype(*this)>*>(this)->FuncName();        \
	}

// ========================================
// Runtime-Exclusive Accessors
// ========================================

// VR-only struct/value accessor (returns reference in VR, use with runtime check)
// Usage: VR_RUNTIME_DATA_ACCESSOR(VR_PLAYER_RUNTIME_DATA, GetVRPlayerRuntimeData, 0x3D8)
// Note: Callers should check REL::Module::IsVR() before calling in multi-runtime builds
#define VR_RUNTIME_DATA_ACCESSOR(StructType, FuncName, VROffset)     \
	[[nodiscard]] inline StructType& FuncName() noexcept             \
	{                                                                \
		return REL::RelocateMember<StructType>(this, 0, VROffset);   \
	}                                                                \
	[[nodiscard]] inline const StructType& FuncName() const noexcept \
	{                                                                \
		return REL::RelocateMember<StructType>(this, 0, VROffset);   \
	}

// Generates a GetXXX() accessor for a field shared by name (not offset)
// between a class's SE/AE and VR runtime-data structs -- no "wrong" struct
// left to pick, unlike RUNTIME_DATA_ACCESSOR_EX + a manual IsVR() branch.
// Params: FieldType, FuncName, RuntimeDataFunc, VRRuntimeDataFunc, FieldName
// VRRuntimeDataFunc must be a self-guarding pointer accessor (e.g.
// VR_ONLY_POINTER_ACCESSOR); guaranteed non-null here since IsVR() is true.
// Usage: RUNTIME_DATA_FIELD_ACCESSOR(ImageSpaceBaseData*, GetCurrentBaseData, GetRuntimeData, GetVRRuntimeData, currentBaseData)
#define RUNTIME_DATA_FIELD_ACCESSOR(FieldType, FuncName, RuntimeDataFunc, VRRuntimeDataFunc, FieldName) \
	[[nodiscard]] inline FieldType& FuncName() noexcept                                                 \
	{                                                                                                   \
		if (REL::Module::IsVR()) {                                                                      \
			return VRRuntimeDataFunc()->FieldName;                                                      \
		}                                                                                               \
		return RuntimeDataFunc().FieldName;                                                             \
	}                                                                                                   \
	[[nodiscard]] inline FieldType const& FuncName() const noexcept                                     \
	{                                                                                                   \
		if (REL::Module::IsVR()) {                                                                      \
			return VRRuntimeDataFunc()->FieldName;                                                      \
		}                                                                                               \
		return RuntimeDataFunc().FieldName;                                                             \
	}

// ========================================
// Pointer Accessors - Return pointer or nullptr
// ========================================

// Generates GetXXX() pointer accessor for SE/AE-only data (returns nullptr in VR)
// Params: StructType, FuncName, SEOffset
#define SE_ONLY_POINTER_ACCESSOR(StructType, FuncName, SEOffset)        \
	[[nodiscard]] inline StructType* FuncName() noexcept                \
	{                                                                   \
		if SKYRIM_REL_CONSTEXPR (REL::Module::IsVR()) {                 \
			return nullptr;                                             \
		} else {                                                        \
			return &REL::RelocateMember<StructType>(this, SEOffset, 0); \
		}                                                               \
	}                                                                   \
	[[nodiscard]] inline const StructType* FuncName() const noexcept    \
	{                                                                   \
		if SKYRIM_REL_CONSTEXPR (REL::Module::IsVR()) {                 \
			return nullptr;                                             \
		} else {                                                        \
			return &REL::RelocateMember<StructType>(this, SEOffset, 0); \
		}                                                               \
	}

// Generates GetXXX() pointer accessor for VR-only data (returns nullptr in SE/AE)
// Params: StructType, FuncName, VROffset
#define VR_ONLY_POINTER_ACCESSOR(StructType, FuncName, VROffset)        \
	[[nodiscard]] inline StructType* FuncName() noexcept                \
	{                                                                   \
		if SKYRIM_REL_VR_CONSTEXPR (!REL::Module::IsVR()) {             \
			return nullptr;                                             \
		} else {                                                        \
			return &REL::RelocateMember<StructType>(this, 0, VROffset); \
		}                                                               \
	}                                                                   \
	[[nodiscard]] inline const StructType* FuncName() const noexcept    \
	{                                                                   \
		if SKYRIM_REL_VR_CONSTEXPR (!REL::Module::IsVR()) {             \
			return nullptr;                                             \
		} else {                                                        \
			return &REL::RelocateMember<StructType>(this, 0, VROffset); \
		}                                                               \
	}

// Generates GetXXX() pointer accessor for AE-only inline data present since AE's
// initial release (returns nullptr on SE/VR). For AE data reached via a stored
// pointer member and added partway through AE's own version lifecycle, use
// AE_ONLY_POINTER_ACCESSOR_VERSIONED instead.
// Params: StructType, FuncName, AEOffset
#define AE_ONLY_POINTER_ACCESSOR(StructType, FuncName, AEOffset)     \
	[[nodiscard]] inline StructType* FuncName() noexcept             \
	{                                                                \
		if SKYRIM_REL_CONSTEXPR (REL::Module::IsAE()) {              \
			return &REL::RelocateMember<StructType>(this, AEOffset); \
		} else {                                                     \
			return nullptr;                                          \
		}                                                            \
	}                                                                \
	[[nodiscard]] inline const StructType* FuncName() const noexcept \
	{                                                                \
		if SKYRIM_REL_CONSTEXPR (REL::Module::IsAE()) {              \
			return &REL::RelocateMember<StructType>(this, AEOffset); \
		} else {                                                     \
			return nullptr;                                          \
		}                                                            \
	}

// Generates GetXXX() pointer accessor for AE-only data reached via a stored
// pointer member, present only from a given SKSE runtime version onward within
// AE itself (returns nullptr on SE/VR, and on AE before Version). For AE data
// inline-embedded at a fixed offset with no version gate, use
// AE_ONLY_POINTER_ACCESSOR instead.
// Params: StructType, FuncName, Version, AEOffset
#define AE_ONLY_POINTER_ACCESSOR_VERSIONED(StructType, FuncName, Version, AEOffset)                       \
	[[nodiscard]] inline StructType* FuncName() noexcept                                                  \
	{                                                                                                     \
		if SKYRIM_REL_CONSTEXPR (REL::Module::IsAE()) {                                                   \
			if (REL::Module::get().version().compare(Version) != std::strong_ordering::less) {            \
				return REL::RelocateMember<StructType*>(this, AEOffset);                                  \
			}                                                                                             \
		}                                                                                                 \
		return nullptr;                                                                                   \
	}                                                                                                     \
	[[nodiscard]] inline const StructType* FuncName() const noexcept                                      \
	{                                                                                                     \
		return const_cast<std::remove_const_t<std::remove_pointer_t<decltype(this)>>*>(this)->FuncName(); \
	}

// ========================================
// Pointer Member Accessors
// ========================================

// Generate accessor for pointer members (returns pointer by value, not reference)
// Usage: RUNTIME_DATA_POINTER_ACCESSOR_EX(TESRegionDataManager*, GetRegionDataManager, 0xDB0, 0x1580)
// NOTE: Use this for pointer members (T* member), not struct members (T member)
#define RUNTIME_DATA_POINTER_ACCESSOR_EX(PointerType, FuncName, SEOffset, VROffset) \
	[[nodiscard]] inline PointerType FuncName() noexcept                            \
	{                                                                               \
		return REL::RelocateMember<PointerType>(this, SEOffset, VROffset);          \
	}                                                                               \
	[[nodiscard]] inline const PointerType FuncName() const noexcept                \
	{                                                                               \
		return REL::RelocateMember<PointerType>(this, SEOffset, VROffset);          \
	}

// ========================================
// Cast Accessors (Base Class Access)
// ========================================

// Generates AsXXX() pointer accessor for runtime-conditional base classes
// Params: StructType, FuncName, SEOffset, VROffset
// Note: In multi-runtime builds, base classes can't be in hierarchy due to offset conflicts
#define RUNTIME_CAST_ACCESSOR(StructType, FuncName, SEOffset, VROffset)                                   \
	[[nodiscard]] inline StructType* FuncName() noexcept                                                  \
	{                                                                                                     \
		return &REL::RelocateMember<StructType>(this, SEOffset, VROffset);                                \
	}                                                                                                     \
	[[nodiscard]] inline const StructType* FuncName() const noexcept                                      \
	{                                                                                                     \
		return const_cast<std::remove_const_t<std::remove_pointer_t<decltype(this)>>*>(this)->FuncName(); \
	}

// Versioned runtime-aware base class cast accessor
// Usage: RUNTIME_CAST_ACCESSOR_VERSIONED(MagicTarget, AsMagicTarget, SKSE::RUNTIME_SSE_1_6_629, 0x98, 0xA0)
#define RUNTIME_CAST_ACCESSOR_VERSIONED(StructType, FuncName, Version, OldOffset, NewOffset)              \
	[[nodiscard]] inline StructType* FuncName() noexcept                                                  \
	{                                                                                                     \
		return &REL::RelocateMemberIfNewer<StructType>(Version, this, OldOffset, NewOffset);              \
	}                                                                                                     \
	[[nodiscard]] inline const StructType* FuncName() const noexcept                                      \
	{                                                                                                     \
		return const_cast<std::remove_const_t<std::remove_pointer_t<decltype(this)>>*>(this)->FuncName(); \
	}

// ========================================
// Three-Runtime Accessors (SE/AE/VR)
// ========================================

// Accessor for members with different offsets in SE, AE, and VR
// Usage: RUNTIME_MEMBER_ACCESSOR_VERSIONED(DepthStencilRuntimeData, GetDepthStencilData, SKSE::RUNTIME_SSE_1_6_1130, 0x1FB8, 0x21D0, 0x2018)
// Parameters: (StructType, FuncName, Version, SEOffset, VROffset, AEOffset)
// NOTE: If the first parameter (StructType) is a template type containing commas (e.g. `REX::EnumSet<Flag, std::uint32_t>`),
//       the preprocessor will split the commas into separate macro arguments. Two easy workarounds:
//         1) Define a short `using` alias before the macro call and pass the alias (recommended):
//              using FooFlags = REX::EnumSet<Flag, std::uint32_t>;
//              RUNTIME_MEMBER_ACCESSOR_VERSIONED(FooFlags, GetFooFlags, ...)
//         2) Wrap the type in parentheses and use a small unwrapping helper (more intrusive change to macros):
//              RUNTIME_MEMBER_ACCESSOR_VERSIONED((REX::EnumSet<Flag, std::uint32_t>), GetFooFlags, ...)
//       We recommend option 1 for clarity and minimal churn.
#define RUNTIME_MEMBER_ACCESSOR_VERSIONED(StructType, FuncName, Version, SEOffset, VROffset, AEOffset) \
	[[nodiscard]] inline StructType& FuncName() noexcept                                               \
	{                                                                                                  \
		if SKYRIM_REL_CONSTEXPR (REL::Module::IsAE()) {                                                \
			return REL::RelocateMemberIfNewer<StructType>(Version, this, SEOffset, AEOffset);          \
		}                                                                                              \
		return REL::RelocateMember<StructType>(this, SEOffset, VROffset);                              \
	}                                                                                                  \
	[[nodiscard]] inline const StructType& FuncName() const noexcept                                   \
	{                                                                                                  \
		if SKYRIM_REL_CONSTEXPR (REL::Module::IsAE()) {                                                \
			return REL::RelocateMemberIfNewer<StructType>(Version, this, SEOffset, AEOffset);          \
		}                                                                                              \
		return REL::RelocateMember<StructType>(this, SEOffset, VROffset);                              \
	}

// Versioned runtime-aware base class cast accessor for members with different offsets in SE, AE, and VR
// Usage: RUNTIME_CAST_ACCESSOR_VERSIONED_VR(MagicTarget, AsMagicTarget, SKSE::RUNTIME_SSE_1_6_629, 0x98, 0xA0, 0xA8)
// Parameters: (StructType, FuncName, Version, SEOffset, VROffset, AEOffset) -- same shape as
// RUNTIME_MEMBER_ACCESSOR_VERSIONED above, just returning a pointer (for base-class cast accessors)
// instead of a reference.
#define RUNTIME_CAST_ACCESSOR_VERSIONED_VR(StructType, FuncName, Version, SEOffset, VROffset, AEOffset)   \
	[[nodiscard]] inline StructType* FuncName() noexcept                                                  \
	{                                                                                                     \
		if SKYRIM_REL_CONSTEXPR (REL::Module::IsAE()) {                                                   \
			return &REL::RelocateMemberIfNewer<StructType>(Version, this, SEOffset, AEOffset);            \
		}                                                                                                 \
		return &REL::RelocateMember<StructType>(this, SEOffset, VROffset);                                \
	}                                                                                                     \
	[[nodiscard]] inline const StructType* FuncName() const noexcept                                      \
	{                                                                                                     \
		return const_cast<std::remove_const_t<std::remove_pointer_t<decltype(this)>>*>(this)->FuncName(); \
	}
