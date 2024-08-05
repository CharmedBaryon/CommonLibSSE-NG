#include "RE/U/UI3DSceneManager.h"

namespace RE
{
	UI3DSceneManager* UI3DSceneManager::GetSingleton()
	{
		REL::Relocation<UI3DSceneManager**> singleton{ RELOCATION_ID(517052, 403560) };
		return *singleton;
	}

	void UI3DSceneManager::AttachChild(NiAVObject* a_obj)
	{
		AttachChild(a_obj, currentlightScheme);
	}

	void UI3DSceneManager::AttachChild(NiAVObject* a_obj, INTERFACE_LIGHT_SCHEME a_scheme)
	{
		using func_t = void (*)(UI3DSceneManager*, NiAVObject*, INTERFACE_LIGHT_SCHEME);
		static REL::Relocation<func_t> func{ RELOCATION_ID(51859, 52731) };
		return func(this, a_obj, a_scheme);
	}

	void UI3DSceneManager::DetachChild(NiAVObject* a_obj)
	{
		using func_t = decltype(&UI3DSceneManager::DetachChild);
		static REL::Relocation<func_t> func{ RELOCATION_ID(51861, 52733) };
		return func(this, a_obj);
	}

	void UI3DSceneManager::SetCameraFOV(float a_fov)
	{
		using func_t = decltype(&UI3DSceneManager::SetCameraFOV);
		static REL::Relocation<func_t> func{ RELOCATION_ID(51870, 52742) };
		return func(this, a_fov);
	}

	void UI3DSceneManager::SetCameraRotate(const NiMatrix3& a_rotate)
	{
		using func_t = decltype(&UI3DSceneManager::SetCameraRotate);
		static REL::Relocation<func_t> func{ RELOCATION_ID(51869, 52741) };
		return func(this, a_rotate);
	}

	void UI3DSceneManager::SetCameraPosition(const NiPoint3& a_pos)
	{
		using func_t = decltype(&UI3DSceneManager::SetCameraRotate);
		static REL::Relocation<func_t> func{ RELOCATION_ID(51867, 52739) };
		return func(this, a_pos);
	}
}
