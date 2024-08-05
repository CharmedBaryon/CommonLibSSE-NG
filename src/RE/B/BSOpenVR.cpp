#pragma once

#include "RE/B/BSOpenVR.h"

namespace RE
{
#ifdef ENABLE_SKYRIM_VR
	BSOpenVR* BSOpenVR::GetSingleton()
	{
		REL::Relocation<BSOpenVR**> singleton{ REL::Offset(0x2FEB9B0) };
		return *singleton;
	}

	vr::IVRCompositor* BSOpenVR::GetIVRCompositor()
	{
		using func_t = decltype(&BSOpenVR::GetIVRCompositor);
		REL::Relocation<func_t> func{ REL::Offset(0xC57880) };
		return func();
	}

	vr::IVROverlay* BSOpenVR::GetIVROverlay(Unk190* a_unk190)
	{
		using func_t = decltype(&BSOpenVR::GetIVROverlay);
		REL::Relocation<func_t> func{ REL::Offset(0x8A0110) };
		return func(a_unk190);
	}

	vr::IVRRenderModels* BSOpenVR::GetIVRRenderModels()
	{
		using func_t = decltype(&BSOpenVR::GetIVRRenderModels);
		REL::Relocation<func_t> func{ REL::Offset(0xC57920) };
		return func();
	}

	vr::IVRSettings* BSOpenVR::GetIVRSettings()
	{
		using func_t = decltype(&BSOpenVR::GetIVRSettings);
		REL::Relocation<func_t> func{ REL::Offset(0xC579C0) };
		return func();
	}

	vr::IVRSystem* BSOpenVR::GetIVRSystem()
	{
		using func_t = decltype(&BSOpenVR::GetIVRSystem);
		REL::Relocation<func_t> func{ REL::Offset(0xC57A60) };
		return func();
	}
#endif
}
