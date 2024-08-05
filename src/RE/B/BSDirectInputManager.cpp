#include "RE/B/BSDirectInputManager.h"

namespace RE
{
	BSDirectInputManager* BSDirectInputManager::GetSingleton()
	{
		REL::Relocation<BSDirectInputManager**> singleton{ RELOCATION_ID(517046, 403554) };
		return *singleton;
	}

	REX::W32::IDirectInputDevice8A* BSDirectInputManager::CreateDeviceWithGUID(REX::W32::GUID* a_guid)
	{
		using func_t = decltype(&BSDirectInputManager::CreateDeviceWithGUID);
		static REL::Relocation<func_t> func{ RELOCATION_ID(67373, 68675) };
		return func(this, a_guid);
	}

	void BSDirectInputManager::GetDeviceState(REX::W32::IDirectInputDevice8A* a_device, std::uint32_t a_size, void* a_outData)
	{
		using func_t = decltype(&BSDirectInputManager::GetDeviceState);
		static REL::Relocation<func_t> func{ RELOCATION_ID(67375, 68677) };
		return func(this, a_device, a_size, a_outData);
	}

	void BSDirectInputManager::GetDeviceData(REX::W32::IDirectInputDevice8A* a_device, std::uint32_t* a_dataSize, REX::W32::DIDEVICEOBJECTDATA** a_outData)
	{
		using func_t = decltype(&BSDirectInputManager::GetDeviceData);
		static REL::Relocation<func_t> func{ RELOCATION_ID(67376, 68678) };
		return func(this, a_device, a_dataSize, a_outData);
	}

	void BSDirectInputManager::ReleaseDevice(REX::W32::IDirectInputDevice8A* a_device)
	{
		using func_t = decltype(&BSDirectInputManager::ReleaseDevice);
		static REL::Relocation<func_t> func{ RELOCATION_ID(67374, 68676) };
		return func(this, a_device);
	}
}
