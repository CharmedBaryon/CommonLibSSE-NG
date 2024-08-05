#pragma once

#if !defined(ENABLE_SKYRIM_VR) && !defined(ENABLE_SKYRIM_SE) && defined(ENABLE_SKYRIM_AE)
/**
 * Defined to indicate that this build only supports AE
 */
#define EXCLUSIVE_SKYRIM_AE
/**
 * Defined to indicate that this build only supports AE and SE
 */
#define EXCLUSIVE_SKYRIM_FLAT
#elif !defined(ENABLE_SKYRIM_VR) && defined(ENABLE_SKYRIM_SE) && !defined(ENABLE_SKYRIM_AE)
/**
 * Defined to indicate that this build only supports SE
 */
#define EXCLUSIVE_SKYRIM_SE
/**
 * Defined to indicate that this build only supports AE and SE
 */
#define EXCLUSIVE_SKYRIM_FLAT
#elif defined(ENABLE_SKYRIM_VR) && !defined(ENABLE_SKYRIM_SE) && !defined(ENABLE_SKYRIM_AE)
/**
 * Defined to indicate that this build only supports VR
 */
#define EXCLUSIVE_SKYRIM_VR
#elif !defined(ENABLE_SKYRIM_VR) && (defined(ENABLE_SKYRIM_SE) || defined(ENABLE_SKYRIM_AE))
/**
 * Defined to indicate that this build only supports AE and SE
 */
#define EXCLUSIVE_SKYRIM_FLAT
#endif

#if defined(ENABLE_SKYRIM_VR) && (defined(ENABLE_SKYRIM_AE) || defined(ENABLE_SKYRIM_SE))
/**
 * Defined to indicate that this build supports both VR and non-VR runtimes.
 */
#define SKYRIM_CROSS_VR
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
#define SKYRIM_ADDR constexpr
#else
/**
 * A macro which defines a modifier for expressions that vary by Skyrim address library IDs.
 *
 * <p>
 * Currently defined as <code>inline</code> to support multiple Address Library ID families dynamically.
 * </p>
 */
#define SKYRIM_ADDR inline
#endif

#if (!defined(ENABLE_SKYRIM_AE) && !defined(ENABLE_SKYRIM_VR)) || (!defined(ENABLE_SKYRIM_SE) && !defined(ENABLE_SKYRIM_VR)) || (!defined(ENABLE_SKYRIM_AE) && !defined(ENABLE_SKYRIM_SE))
/**
 * A macro which defines a modifier for expressions that vary by the specific Skyrim runtime.
 *
 * <p>
 * Currently defined as <code>constexpr</code> since this build is for only a single runtime.
 * </p>
 */
#define SKYRIM_REL constexpr

/**
 * A macro which defines a modifier for expressions which may be <code>constexpr</code> when using selective targeting.
 *
 * <p>
 * Currently defined as <code>constexpr</code> since this build is for only a single runtime.
 * </p>
 */
#define SKYRIM_REL_CONSTEXPR constexpr
#else
/**
 * A macro which defines a modifier for expressions that vary by the specific Skyrim runtime.
 *
 * <p>
 * Currently defined as <code>inline</code> to support multiple runtimes dynamically.
 * </p>
 */
#define SKYRIM_REL inline

/**
 * A macro which defines a modifier for expressions which may be <code>constexpr</code> when using selective targeting.
 *
 * <p>
 * Currently defined as empty to support multiple runtimes.
 * </p>
 */
#define SKYRIM_REL_CONSTEXPR
#endif

#ifndef SKYRIM_CROSS_VR
/**
 * A macro which defines a modifier for expressions that vary between Skyrim SE/AE and Skyrim VR.
 *
 * <p>
 * Currently defined as <code>constexpr</code> since this build is only for VR or non-VR.
 * </p>
 */
#define SKYRIM_REL_VR constexpr

/**
 * A macro which defines a modifier for expressions which may be <code>constexpr</code> when using selectively VR or non-VR.
 *
 * <p>
 * Currently defined as <code>constexpr</code> since this build is only for VR or non-VR.
 * </p>
 */
#define SKYRIM_REL_VR_CONSTEXPR constexpr

/**
 * A macro which defines a modifier for functions which may be <code>virtual</code> when using selectively VR or non-VR.
 *
 * <p>
 * Currently defined as <code>virtual</code> since this build is only for VR or non-VR.
 * </p>
 */
#define SKYRIM_REL_VR_VIRTUAL virtual
#else
/**
 * A macro which defines a modifier for expressions that vary between Skyrim SE/AE and Skyrim VR.
 *
 * <p>
 * Currently defined as <code>inline</code> since this build is for both VR and non-VR.
 * </p>
 */
#define SKYRIM_REL_VR inline

/**
 * A macro which defines a modifier for expressions which may be <code>constexpr</code> when using selectively VR or non-VR.
 *
 * <p>
 * Currently defined as empty since this build is for both VR and non-VR.
 * </p>
 */
#define SKYRIM_REL_VR_CONSTEXPR

/**
 * A macro which defines a modifier for functions which may be <code>virtual</code> when using selectively VR or non-VR.
 *
 * <p>
 * Currently defined as empty since this build is for both VR and non-VR.
 * </p>
 */
#define SKYRIM_REL_VR_VIRTUAL
#endif
