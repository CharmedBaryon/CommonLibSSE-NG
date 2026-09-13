#include "RE/B/BSOpenVR.h"

namespace RE
{
#ifdef ENABLE_SKYRIM_VR
	BSOpenVR* BSOpenVR::GetSingleton()
	{
		static REL::Relocation<BSOpenVR**> singleton{ REL::Offset(0x2FEB9B0) };
		// Add null check for safety - returns nullptr if pointer is invalid
		return singleton.get() != nullptr ? *singleton : nullptr;
	}

	vr::IVRCompositor* BSOpenVR::GetIVRCompositor()
	{
		using func_t = decltype(&BSOpenVR::GetIVRCompositor);
		static REL::Relocation<func_t> func{ REL::Offset(0xC57880) };
		return func();
	}

	vr::IVROverlay* BSOpenVR::GetIVROverlayFromContext(COpenVRContext* a_vrContext)
	{
		using func_t = decltype(&BSOpenVR::GetIVROverlayFromContext);
		static REL::Relocation<func_t> func{ REL::Offset(0x8A0110) };
		return func(a_vrContext);
	}

	vr::IVRRenderModels* BSOpenVR::GetIVRRenderModels()
	{
		using func_t = decltype(&BSOpenVR::GetIVRRenderModels);
		static REL::Relocation<func_t> func{ REL::Offset(0xC57920) };
		return func();
	}

	vr::IVRSettings* BSOpenVR::GetIVRSettings()
	{
		using func_t = decltype(&BSOpenVR::GetIVRSettings);
		static REL::Relocation<func_t> func{ REL::Offset(0xC579C0) };
		return func();
	}

	vr::IVRSystem* BSOpenVR::GetIVRSystem()
	{
		using func_t = decltype(&BSOpenVR::GetIVRSystem);
		static REL::Relocation<func_t> func{ REL::Offset(0xC57A60) };
		return func();
	}

	float BSOpenVR::GetHapticPulseScale()
	{
		// Haptic pulse duration is multiplied by the value at this address (default 3999.0 in SkyrimVR.exe)
		static REL::Relocation<float*> hapticPulseScale{ REL::Offset(0x17E6E50) };
		// Add null check for safety - defaults to 3999.0 if pointer is invalid
		return hapticPulseScale.get() != nullptr ? *hapticPulseScale : 3999.0f;
	}

	void BSOpenVR::SetHapticPulseScale(float value)
	{
		static REL::Relocation<float*> hapticPulseScale{ REL::Offset(0x17E6E50) };

		// Add validation for reasonable bounds
		// Clamp between 0.0 (disabled) and 20000.0 (5x default, prevents excessive haptic duration)
		constexpr float MIN_HAPTIC_SCALE = 0.0f;
		constexpr float MAX_HAPTIC_SCALE = 20000.0f;

		if (value < MIN_HAPTIC_SCALE) {
			value = MIN_HAPTIC_SCALE;
		} else if (value > MAX_HAPTIC_SCALE) {
			value = MAX_HAPTIC_SCALE;
		}

		// Add null check for safety - only set value if pointer is valid
		if (hapticPulseScale.get() != nullptr) {
			*hapticPulseScale = value;
		}
	}
#endif
}
