#pragma once

#if !defined(ENABLE_SKYRIM_VR) && !defined(ENABLE_SKYRIM_SE) && defined(ENABLE_SKYRIM_AE)
/**
 * Defined to indicate that this build only supports AE
 */
#	define EXCLUSIVE_SKYRIM_AE
/**
 * Defined to indicate that this build only supports AE and SE
 */
#	define EXCLUSIVE_SKYRIM_FLAT
#elif !defined(ENABLE_SKYRIM_VR) && defined(ENABLE_SKYRIM_SE) && !defined(ENABLE_SKYRIM_AE)
/**
 * Defined to indicate that this build only supports SE
 */
#	define EXCLUSIVE_SKYRIM_SE
/**
 * Defined to indicate that this build only supports AE and SE
 */
#	define EXCLUSIVE_SKYRIM_FLAT
#elif defined(ENABLE_SKYRIM_VR) && !defined(ENABLE_SKYRIM_SE) && !defined(ENABLE_SKYRIM_AE)
/**
 * Defined to indicate that this build only supports VR
 */
#	define EXCLUSIVE_SKYRIM_VR
#elif !defined(ENABLE_SKYRIM_VR) && (defined(ENABLE_SKYRIM_SE) || defined(ENABLE_SKYRIM_AE))
/**
 * Defined to indicate that this build only supports AE and SE
 */
#	define EXCLUSIVE_SKYRIM_FLAT
#endif

#if defined(ENABLE_SKYRIM_VR) && (defined(ENABLE_SKYRIM_AE) || defined(ENABLE_SKYRIM_SE))
/**
 * Defined to indicate that this build supports both VR and non-VR runtimes.
 */
#	define SKYRIM_CROSS_VR
#endif

/**
 * Macros used for utils in CLIB-NG using GetRuntimeData | GetVRRuntimeData
 */
#if defined(EXCLUSIVE_SKYRIM_VR)
#	define GET_CROSSVR_RUNTIME_MEMBER(a_value)
#	define GET_CROSSVR_INSTANCE_MEMBER(a_value, a_source)
#elif defined(EXCLUSIVE_SKYRIM_FLAT)
#	define GET_CROSSVR_RUNTIME_MEMBER(a_value)
#	define GET_CROSSVR_INSTANCE_MEMBER(a_value, a_source)
#else
/**
 @def GET_CROSSVR_RUNTIME_MEMBER
 @brief Set variable in current namespace based on instance member from GetRuntimeData or GetVRRuntimeData.
  
 @warning The class must have both a GetRuntimeData() and GetVRRuntimeData() function.
  
 @param a_value The instance member value to access (e.g., renderTargets).
 @result The a_value will be set as a variable in the current namespace. (e.g., auto& renderTargets = GetVRRuntimeData().renderTargets; for vr)
 */
#	define GET_CROSSVR_RUNTIME_MEMBER(a_value) \
		auto& a_value = !REL::Module::IsVR() ? GetRuntimeData().a_value : GetVRRuntimeData().a_value;
/**
 @def GET_CROSSVR_INSTANCE_MEMBER
 @brief Set variable in current namespace based on instance member from GetRuntimeData or GetVRRuntimeData.
  
 @warning The class must have both a GetRuntimeData() and GetVRRuntimeData() function.
  
 @param a_value The instance member value to access (e.g., renderTargets).
 @param a_source The instance of the class (e.g., state).
 @result The a_value will be set as a variable in the current namespace. (e.g., auto& renderTargets = state->GetVRRuntimeData().renderTargets; for vr)
 */
#	define GET_CROSSVR_INSTANCE_MEMBER(a_value, a_source) \
		auto& a_value = !REL::Module::IsVR() ? a_source->GetRuntimeData().a_value : a_source->GetVRRuntimeData().a_value;
#endif

#if !defined(ENABLE_SKYRIM_AE) || (!defined(ENABLE_SKYRIM_SE) && !defined(ENABLE_SKYRIM_VR))
/**
 * A macro which defines a modifier for expressions that vary by Skyrim Address Library IDs.
 *
 * <p>
 * Currently defined as <code>constexpr</code> since this build only targets one family of Address Library.
 * </p>
 */
#	define SKYRIM_ADDR constexpr
#else
/**
 * A macro which defines a modifier for expressions that vary by Skyrim address library IDs.
 *
 * <p>
 * Currently defined as <code>inline</code> to support multiple Address Library ID families dynamically.
 * </p>
 */
#	define SKYRIM_ADDR inline
#endif

#if (!defined(ENABLE_SKYRIM_AE) && !defined(ENABLE_SKYRIM_VR)) || (!defined(ENABLE_SKYRIM_SE) && !defined(ENABLE_SKYRIM_VR)) || (!defined(ENABLE_SKYRIM_AE) && !defined(ENABLE_SKYRIM_SE))
/**
 * A macro which defines a modifier for expressions that vary by the specific Skyrim runtime.
 *
 * <p>
 * Currently defined as <code>constexpr</code> since this build is for only a single runtime.
 * </p>
 */
#	define SKYRIM_REL constexpr

/**
 * A macro which defines a modifier for expressions which may be <code>constexpr</code> when using selective targeting.
 *
 * <p>
 * Currently defined as <code>constexpr</code> since this build is for only a single runtime.
 * </p>
 */
#	define SKYRIM_REL_CONSTEXPR constexpr
#else
/**
 * A macro which defines a modifier for expressions that vary by the specific Skyrim runtime.
 *
 * <p>
 * Currently defined as <code>inline</code> to support multiple runtimes dynamically.
 * </p>
 */
#	define SKYRIM_REL inline

/**
 * A macro which defines a modifier for expressions which may be <code>constexpr</code> when using selective targeting.
 *
 * <p>
 * Currently defined as empty to support multiple runtimes.
 * </p>
 */
#	define SKYRIM_REL_CONSTEXPR
#endif

#ifndef SKYRIM_CROSS_VR
/**
 * A macro which defines a modifier for expressions that vary between Skyrim SE/AE and Skyrim VR.
 *
 * <p>
 * Currently defined as <code>constexpr</code> since this build is only for VR or non-VR.
 * </p>
 */
#	define SKYRIM_REL_VR constexpr

/**
 * A macro which defines a modifier for expressions which may be <code>constexpr</code> when using selectively VR or non-VR.
 *
 * <p>
 * Currently defined as <code>constexpr</code> since this build is only for VR or non-VR.
 * </p>
 */
#	define SKYRIM_REL_VR_CONSTEXPR constexpr

/**
 * A macro which defines a modifier for functions which may be <code>virtual</code> when using selectively VR or non-VR.
 *
 * <p>
 * Currently defined as <code>virtual</code> since this build is only for VR or non-VR.
 * </p>
 */
#	define SKYRIM_REL_VR_VIRTUAL virtual
#else
/**
 * A macro which defines a modifier for expressions that vary between Skyrim SE/AE and Skyrim VR.
 *
 * <p>
 * Currently defined as <code>inline</code> since this build is for both VR and non-VR.
 * </p>
 */
#	define SKYRIM_REL_VR inline

/**
 * A macro which defines a modifier for expressions which may be <code>constexpr</code> when using selectively VR or non-VR.
 *
 * <p>
 * Currently defined as empty since this build is for both VR and non-VR.
 * </p>
 */
#	define SKYRIM_REL_VR_CONSTEXPR

/**
 * A macro which defines a modifier for functions which may be <code>virtual</code> when using selectively VR or non-VR.
 *
 * <p>
 * Currently defined as empty since this build is for both VR and non-VR.
 * </p>
 */
#	define SKYRIM_REL_VR_VIRTUAL
#endif

/**
 * @brief Static assert macro for cross-runtime size validation with diagnostic error messages.
 * 
 * STATIC_ASSERT_SIZE(ClassName, SESize[, AESize[, VRSize[, AllSize[, FlatSize]]]])
 * 
 * This macro simplifies size assertions across different Skyrim runtimes (SE, AE, VR) by automatically
 * selecting the correct expected size based on the build configuration. It provides detailed error
 * messages showing the runtime, expected size, and all known sizes for debugging.
 * 
 * @par Usage Examples
 * @code
 * STATIC_ASSERT_SIZE(MyClass, 0x100);                              // Same size for all runtimes
 * STATIC_ASSERT_SIZE(MyClass, 0x100, 0x120);                       // Flat=0x100, VR=0x120; SE and AE unspecified (SIZE_UNDEFINED)
 * STATIC_ASSERT_SIZE(PlayerCharacter, 0xBE0, 0x9A8, 0x12F0);      // SE, AE, VR specified; Flat unspecified (SIZE_UNDEFINED)
 * STATIC_ASSERT_SIZE(ButtonEvent, 0x30, 0x30, 0x38, 0x18);        // SE, AE, VR, All specified; Flat unspecified (SIZE_UNDEFINED)
 * STATIC_ASSERT_SIZE(ComplexClass, 0x30, 0x30, 0x38, 0x18, 0x20); // SE, AE, VR, All, Flat different
 * @endcode
 * 
 * @par Error Messages
 * @code
 * error C2338: Projectile size mismatch in EXCLUSIVE_SKYRIM_VR: expected 0x28 (SE=0x10, AE=0x10, VR=0x28)
 * @endcode
 * 
 * @par Supported Overloads
 * - STATIC_ASSERT_SIZE(ClassName, Size)
 *     All presets use same size
 * 
 * - STATIC_ASSERT_SIZE(ClassName, FlatSize, VRSize)
 *     Flat and VR specified; SESize and AESize are undefined (SIZE_UNDEFINED). Use 6-arg to specify per-runtime sizes.
 * 
 * - STATIC_ASSERT_SIZE(ClassName, SESize, AESize, VRSize)
 *     SE, AE, and VR specified; Flat is left undefined (SIZE_UNDEFINED) unless provided in 6-arg.
 * 
 * - STATIC_ASSERT_SIZE(ClassName, SESize, AESize, VRSize, AllSize)
 *     SE, AE, VR, and All specified; Flat left undefined (SIZE_UNDEFINED) unless provided in 6-arg.
 * 
 * - STATIC_ASSERT_SIZE(ClassName, SESize, AESize, VRSize, AllSize, FlatSize)
 *     Full control - all sizes specified explicitly
 *     Use SIZE_UNDEFINED for any undefined size to skip assertion for that preset
 * 
 * @par Benefits
 * - Single line replaces conditional static_assert blocks
 * - Clear error messages with all runtime sizes
 * - Incremental: add args as you discover differences
 * - IDE-friendly with hover documentation
 * 
 * @par How It Works
 * Uses preprocessor conditionals to select the appropriate size based on build defines:
 * - EXCLUSIVE_SKYRIM_SE: Uses SESize
 * - EXCLUSIVE_SKYRIM_AE: Uses AESize
 * - EXCLUSIVE_SKYRIM_VR: Uses VRSize
 * - SKYRIM_CROSS_VR (multi-runtime): Uses AllSize
 * - EXCLUSIVE_SKYRIM_FLAT (SE+AE, no VR): Uses FlatSize
 * 
 * If the expected size is SIZE_UNDEFINED, the assertion is skipped (size undefined for that preset).
 * Undefined sizes allow incremental migration - specify only known sizes, discover others later.
 */

/**
 * @brief Special value to indicate an undefined size/offset in STATIC_ASSERT_SIZE and STATIC_ASSERT_OFFSET.
 *
 * Use this to skip assertions for presets where the size/offset is not yet known.
 * Uses a large impossible value so it cannot collide with valid offsets (including 0x0).
 */
#define SIZE_UNDEFINED 0xDEAD

#define STATIC_ASSERT_SIZE(...)                                                                                                                                                         \
	_STATIC_ASSERT_SIZE_DISPATCH(__VA_ARGS__, _STATIC_ASSERT_SIZE_6, _STATIC_ASSERT_SIZE_5, _STATIC_ASSERT_SIZE_4, _STATIC_ASSERT_SIZE_3, _STATIC_ASSERT_SIZE_2, _STATIC_ASSERT_SIZE_1) \
	(__VA_ARGS__)
#define _STATIC_ASSERT_SIZE_DISPATCH(_1, _2, _3, _4, _5, _6, NAME, ...) NAME

// 1 arg: Error - need at least class name and one size
#define _STATIC_ASSERT_SIZE_1(ClassName) \
	static_assert(false, "STATIC_ASSERT_SIZE requires at least 2 arguments: ClassName and Size")

// 2 args: ClassName, Size (use this size for all runtimes - add more args as you discover differences)
#define _STATIC_ASSERT_SIZE_2(ClassName, Size) \
	static_assert(sizeof(ClassName) == (Size), \
		#ClassName " size mismatch: expected " #Size " (using for all runtimes)")

// 3 args: ClassName, FlatSize, VRSize
// Sets Flat for EXCLUSIVE_SKYRIM_FLAT and VR for EXCLUSIVE_SKYRIM_VR.
// Does assume SE and AE equal Flat.
#define _STATIC_ASSERT_SIZE_3(ClassName, FlatSize, VRSize) \
	_STATIC_ASSERT_SIZE_6(ClassName, FlatSize, FlatSize, VRSize, SIZE_UNDEFINED, FlatSize)

// 4 args: ClassName, SESize, AESize, VRSize
// SE, AE and VR specified. Flat is left undefined (SIZE_UNDEFINED) unless explicitly provided via 6-arg.
// All: undefined
#define _STATIC_ASSERT_SIZE_4(ClassName, SESize, AESize, VRSize) \
	_STATIC_ASSERT_SIZE_6(ClassName, SESize, AESize, VRSize, SIZE_UNDEFINED, SIZE_UNDEFINED)

// 5 args: ClassName, SESize, AESize, VRSize, AllSize
// SE, AE, VR, All specified. Flat left undefined (SIZE_UNDEFINED) unless explicitly provided in 6-arg.
#define _STATIC_ASSERT_SIZE_5(ClassName, SESize, AESize, VRSize, AllSize) \
	_STATIC_ASSERT_SIZE_6(ClassName, SESize, AESize, VRSize, AllSize, SIZE_UNDEFINED)

// 6 args: ClassName, SESize, AESize, VRSize, AllSize, FlatSize
#define _STATIC_ASSERT_SIZE_6(ClassName, SESize, AESize, VRSize, AllSize, FlatSize) \
	_STATIC_ASSERT_SIZE_IMPL(ClassName, SESize, AESize, VRSize, AllSize, FlatSize)

// Implementation - generates the actual static_assert with detailed error message
// If the expected size is SIZE_UNDEFINED, skip the assertion (size is undefined for this preset)
#define _STATIC_ASSERT_SIZE_IMPL(ClassName, SESize, AESize, VRSize, AllSize, FlatSize)                              \
	static_assert(_STATIC_ASSERT_SIZE_EXPECTED(SESize, AESize, VRSize, AllSize, FlatSize) == SIZE_UNDEFINED ||      \
					  sizeof(ClassName) == _STATIC_ASSERT_SIZE_EXPECTED(SESize, AESize, VRSize, AllSize, FlatSize), \
		#ClassName " size mismatch in " _STATIC_ASSERT_SIZE_RUNTIME_NAME()                                          \
			": "                                                                                                    \
			"expected " _STATIC_ASSERT_SIZE_EXPECTED_STR(SESize, AESize, VRSize, AllSize, FlatSize) " (SE=" #SESize ", AE=" #AESize ", VR=" #VRSize ", All=" #AllSize ", Flat=" #FlatSize ")");

// Preprocessor-based runtime selection for expected size
#if defined(EXCLUSIVE_SKYRIM_SE)
// SE: use SESize.
#	define _STATIC_ASSERT_SIZE_EXPECTED(SESize, AESize, VRSize, AllSize, FlatSize) \
		(SESize)
#	define _STATIC_ASSERT_SIZE_EXPECTED_STR(SESize, AESize, VRSize, AllSize, FlatSize) \
		#SESize
#	define _STATIC_ASSERT_SIZE_RUNTIME_NAME() "EXCLUSIVE_SKYRIM_SE"
#elif defined(EXCLUSIVE_SKYRIM_AE)
// AE: use AESize.
#	define _STATIC_ASSERT_SIZE_EXPECTED(SESize, AESize, VRSize, AllSize, FlatSize) \
		(AESize)
#	define _STATIC_ASSERT_SIZE_EXPECTED_STR(SESize, AESize, VRSize, AllSize, FlatSize) \
		#AESize
#	define _STATIC_ASSERT_SIZE_RUNTIME_NAME() "EXCLUSIVE_SKYRIM_AE"
#elif defined(EXCLUSIVE_SKYRIM_VR)
#	define _STATIC_ASSERT_SIZE_EXPECTED(SESize, AESize, VRSize, AllSize, FlatSize) (VRSize)
#	define _STATIC_ASSERT_SIZE_EXPECTED_STR(SESize, AESize, VRSize, AllSize, FlatSize) #VRSize
#	define _STATIC_ASSERT_SIZE_RUNTIME_NAME() "EXCLUSIVE_SKYRIM_VR"
#elif defined(SKYRIM_CROSS_VR)
// All: use AllSize
#	define _STATIC_ASSERT_SIZE_EXPECTED(SESize, AESize, VRSize, AllSize, FlatSize) (AllSize)
#	define _STATIC_ASSERT_SIZE_EXPECTED_STR(SESize, AESize, VRSize, AllSize, FlatSize) #AllSize
#	define _STATIC_ASSERT_SIZE_RUNTIME_NAME() "SKYRIM_CROSS_VR"
#elif defined(EXCLUSIVE_SKYRIM_FLAT)
// Flat: use FlatSize.
#	define _STATIC_ASSERT_SIZE_EXPECTED(SESize, AESize, VRSize, AllSize, FlatSize) \
		(FlatSize)
#	define _STATIC_ASSERT_SIZE_EXPECTED_STR(SESize, AESize, VRSize, AllSize, FlatSize) #FlatSize
#	define _STATIC_ASSERT_SIZE_RUNTIME_NAME() "EXCLUSIVE_SKYRIM_FLAT"
#else
// Fallback (shouldn't happen in practice)
#	define _STATIC_ASSERT_SIZE_EXPECTED(SESize, AESize, VRSize, AllSize, FlatSize) (SESize)
#	define _STATIC_ASSERT_SIZE_EXPECTED_STR(SESize, AESize, VRSize, AllSize, FlatSize) #SESize
#	define _STATIC_ASSERT_SIZE_RUNTIME_NAME() "UNKNOWN_RUNTIME"
#endif

// -----------------------------------------------------------------------------
// STATIC_ASSERT_OFFSET - offsetof-based static asserts with runtime variants
// Usage examples:
//   STATIC_ASSERT_OFFSET(MyClass, member, 0x10);
//   STATIC_ASSERT_OFFSET(MyClass, member, 0x10, 0x10); // Flat, VR
//   STATIC_ASSERT_OFFSET(MyClass, member, 0x10, 0x10, 0x10); // SE, AE, VR
//   STATIC_ASSERT_OFFSET(MyClass, member, 0x10, 0x10, 0x10, 0x10); // SE, AE, VR, All
//   STATIC_ASSERT_OFFSET(MyClass, member, 0x10, 0x10, 0x10, 0x10, 0x10); // SE, AE, VR, All, Flat
// -----------------------------------------------------------------------------
#define STATIC_ASSERT_OFFSET(...)                                                                                                                                            \
	_STATIC_ASSERT_OFFSET_DISPATCH(__VA_ARGS__, _STATIC_ASSERT_OFFSET_7, _STATIC_ASSERT_OFFSET_6, _STATIC_ASSERT_OFFSET_5, _STATIC_ASSERT_OFFSET_4, _STATIC_ASSERT_OFFSET_3) \
	(__VA_ARGS__)
#define _STATIC_ASSERT_OFFSET_DISPATCH(_1, _2, _3, _4, _5, _6, _7, NAME, ...) NAME

// 1-2 args: Error - need at least class name, member and one offset
#define _STATIC_ASSERT_OFFSET_1(ClassName) \
	static_assert(false, "STATIC_ASSERT_OFFSET requires at least 3 arguments: ClassName, MemberName and Offset")
#define _STATIC_ASSERT_OFFSET_2(ClassName, Member) \
	static_assert(false, "STATIC_ASSERT_OFFSET requires at least 3 arguments: ClassName, MemberName and Offset")

// 3 args: ClassName, Member, Offset (use this offset for all runtimes)
#define _STATIC_ASSERT_OFFSET_3(ClassName, Member, Offset) \
	static_assert(offsetof(ClassName, Member) == (Offset), \
		#ClassName "::" #Member " offset mismatch: expected " #Offset " (using for all runtimes)")

// 4 args: ClassName, Member, FlatOffset, VROffset
// Assumes SE and AE equal FlatOffset
#define _STATIC_ASSERT_OFFSET_4(ClassName, Member, FlatOffset, VROffset) \
	_STATIC_ASSERT_OFFSET_7(ClassName, Member, FlatOffset, FlatOffset, VROffset, SIZE_UNDEFINED, FlatOffset)

// 5 args: ClassName, Member, SESize, AESize, VROffset
#define _STATIC_ASSERT_OFFSET_5(ClassName, Member, SESize, AESize, VROffset) \
	_STATIC_ASSERT_OFFSET_7(ClassName, Member, SESize, AESize, VROffset, SIZE_UNDEFINED, SIZE_UNDEFINED)

// 6 args: ClassName, Member, SESize, AESize, VROffset, AllOffset
#define _STATIC_ASSERT_OFFSET_6(ClassName, Member, SESize, AESize, VROffset, AllOffset) \
	_STATIC_ASSERT_OFFSET_7(ClassName, Member, SESize, AESize, VROffset, AllOffset, SIZE_UNDEFINED)

// 7 args: ClassName, Member, SESize, AESize, VROffset, AllOffset, FlatOffset
#define _STATIC_ASSERT_OFFSET_7(ClassName, Member, SESize, AESize, VROffset, AllOffset, FlatOffset) \
	_STATIC_ASSERT_OFFSET_IMPL(ClassName, Member, SESize, AESize, VROffset, AllOffset, FlatOffset)

#define _STATIC_ASSERT_OFFSET_IMPL(ClassName, Member, SESize, AESize, VROffset, AllOffset, FlatOffset)                                \
	static_assert(_STATIC_ASSERT_OFFSET_EXPECTED(SESize, AESize, VROffset, AllOffset, FlatOffset) == SIZE_UNDEFINED ||                \
					  offsetof(ClassName, Member) == _STATIC_ASSERT_OFFSET_EXPECTED(SESize, AESize, VROffset, AllOffset, FlatOffset), \
		#ClassName "::" #Member " offset mismatch in " _STATIC_ASSERT_OFFSET_RUNTIME_NAME() ": expected " _STATIC_ASSERT_OFFSET_EXPECTED_STR(SESize, AESize, VROffset, AllOffset, FlatOffset) " (SE=" #SESize ", AE=" #AESize ", VR=" #VROffset ", All=" #AllOffset ", Flat=" #FlatOffset ")")

// Runtime selection
#if defined(EXCLUSIVE_SKYRIM_SE)
#	define _STATIC_ASSERT_OFFSET_EXPECTED(SESize, AESize, VRSize, AllSize, FlatSize) (SESize)
#	define _STATIC_ASSERT_OFFSET_EXPECTED_STR(SESize, AESize, VRSize, AllSize, FlatSize) #SESize
#	define _STATIC_ASSERT_OFFSET_RUNTIME_NAME() "EXCLUSIVE_SKYRIM_SE"
#elif defined(EXCLUSIVE_SKYRIM_AE)
#	define _STATIC_ASSERT_OFFSET_EXPECTED(SESize, AESize, VRSize, AllSize, FlatSize) (AESize)
#	define _STATIC_ASSERT_OFFSET_EXPECTED_STR(SESize, AESize, VRSize, AllSize, FlatSize) #AESize
#	define _STATIC_ASSERT_OFFSET_RUNTIME_NAME() "EXCLUSIVE_SKYRIM_AE"
#elif defined(EXCLUSIVE_SKYRIM_VR)
#	define _STATIC_ASSERT_OFFSET_EXPECTED(SESize, AESize, VRSize, AllSize, FlatSize) (VRSize)
#	define _STATIC_ASSERT_OFFSET_EXPECTED_STR(SESize, AESize, VRSize, AllSize, FlatSize) #VRSize
#	define _STATIC_ASSERT_OFFSET_RUNTIME_NAME() "EXCLUSIVE_SKYRIM_VR"
#elif defined(SKYRIM_CROSS_VR)
#	define _STATIC_ASSERT_OFFSET_EXPECTED(SESize, AESize, VRSize, AllSize, FlatSize) (AllSize)
#	define _STATIC_ASSERT_OFFSET_EXPECTED_STR(SESize, AESize, VRSize, AllSize, FlatSize) #AllSize
#	define _STATIC_ASSERT_OFFSET_RUNTIME_NAME() "SKYRIM_CROSS_VR"
#elif defined(EXCLUSIVE_SKYRIM_FLAT)
#	define _STATIC_ASSERT_OFFSET_EXPECTED(SESize, AESize, VRSize, AllSize, FlatSize) (FlatSize)
#	define _STATIC_ASSERT_OFFSET_EXPECTED_STR(SESize, AESize, VRSize, AllSize, FlatSize) #FlatSize
#	define _STATIC_ASSERT_OFFSET_RUNTIME_NAME() "EXCLUSIVE_SKYRIM_FLAT"
#else
#	define _STATIC_ASSERT_OFFSET_EXPECTED(SESize, AESize, VRSize, AllSize, FlatSize) (SESize)
#	define _STATIC_ASSERT_OFFSET_EXPECTED_STR(SESize, AESize, VRSize, AllSize, FlatSize) #SESize
#	define _STATIC_ASSERT_OFFSET_RUNTIME_NAME() "UNKNOWN_RUNTIME"
#endif
