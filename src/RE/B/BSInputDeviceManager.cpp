#include "RE/B/BSInputDeviceManager.h"

#include "RE/B/BSInputDeviceFactory.h"
#include "RE/B/BSPCGamepadDeviceDelegate.h"
#include "RE/B/BSPCGamepadDeviceHandler.h"
#include "RE/B/BSTrackedControllerDevice.h"
#include "RE/B/BSWin32KeyboardDevice.h"
#include "RE/B/BSWin32MouseDevice.h"
#include "RE/B/BSWin32VirtualKeyboardDevice.h"

namespace RE
{
	BSInputDeviceManager* BSInputDeviceManager::GetSingleton()
	{
		static REL::Relocation<BSInputDeviceManager**> singleton{ RELOCATION_ID(516574, 402776) };
		return *singleton;
	}

	bool BSInputDeviceManager::GetButtonNameFromID(INPUT_DEVICE a_device, std::int32_t a_id, BSFixedString& a_buttonName) const
	{
		using func_t = decltype(&BSInputDeviceManager::GetButtonNameFromID);
		static REL::Relocation<func_t> func{ RELOCATION_ID(67316, 68618) };
		return func(this, a_device, a_id, a_buttonName);
	}

	BSPCGamepadDeviceDelegate* BSInputDeviceManager::GetGamepad()
	{
		auto handler = GetGamepadHandler();
		return handler ? handler->GetRuntimeData().currentPCGamePadDelegate : nullptr;
	}

	BSPCGamepadDeviceHandler* BSInputDeviceManager::GetGamepadHandler()
	{
		return static_cast<BSPCGamepadDeviceHandler*>(devices[std::to_underlying(INPUT_DEVICE::kGamepad)]);
	}

	BSWin32KeyboardDevice* BSInputDeviceManager::GetKeyboard()
	{
		return static_cast<BSWin32KeyboardDevice*>(devices[std::to_underlying(INPUT_DEVICE::kKeyboard)]);
	}

	BSWin32MouseDevice* BSInputDeviceManager::GetMouse()
	{
		return static_cast<BSWin32MouseDevice*>(devices[std::to_underlying(INPUT_DEVICE::kMouse)]);
	}

	BSTrackedControllerDevice* BSInputDeviceManager::GetVRControllerRight()
	{
#if !defined(ENABLE_SKYRIM_VR)
		return nullptr;
#else
		if SKYRIM_REL_VR_CONSTEXPR (!REL::Module::IsVR()) {
			return nullptr;
		}
		const auto deviceType = BSOpenVR::GetSingleton()->GetHMDDeviceType();
		return static_cast<BSTrackedControllerDevice*>(devices[2 * std::to_underlying(deviceType) + 3]);  //3,5,7 for vive, oculus, windows
#endif
	}

	BSTrackedControllerDevice* BSInputDeviceManager::GetVRControllerLeft()
	{
#if !defined(ENABLE_SKYRIM_VR)
		return nullptr;
#else
		if SKYRIM_REL_VR_CONSTEXPR (!REL::Module::IsVR()) {
			return nullptr;
		}
		const auto deviceType = BSOpenVR::GetSingleton()->GetHMDDeviceType();
		return static_cast<BSTrackedControllerDevice*>(devices[2 * std::to_underlying(deviceType) + 4]);  //4,6,8 for vive, oculus, windows
#endif
	}

	BSWin32VirtualKeyboardDevice* BSInputDeviceManager::GetVirtualKeyboard()
	{
		return static_cast<BSWin32VirtualKeyboardDevice*>(devices[std::to_underlying(INPUT_DEVICES::VirtualKeyboard())]);
	}

	bool BSInputDeviceManager::IsGamepadConnected()
	{
		auto handler = GetGamepadHandler();
		return handler && handler->GetRuntimeData().currentPCGamePadDelegate;
	}

	bool BSInputDeviceManager::IsGamepadEnabled()
	{
		auto handler = GetGamepadHandler();
		return handler && handler->GetRuntimeData().currentPCGamePadDelegate && handler->GetRuntimeData().currentPCGamePadDelegate->IsEnabled();
	}

	bool BSInputDeviceManager::IsMouseBackground()
	{
		auto mouse = GetMouse();
		return mouse && static_cast<BSMouseDevice*>(mouse)->GetRuntimeData().backgroundMouse;
	}

	bool BSInputDeviceManager::GetDeviceButtonNameFromID(INPUT_DEVICE a_device, std::uint32_t a_key, BSFixedString& a_mapping)
	{
		auto device = devices[std::to_underlying(a_device)];
		return device && device->GetButtonNameFromID(a_key, a_mapping);
	}

	bool BSInputDeviceManager::GetDeviceKeyCodeFromID(INPUT_DEVICE a_device, std::uint32_t a_key, uint32_t& a_outKeyCode)
	{
		auto device = devices[std::to_underlying(a_device)];
		return device && device->GetKeyCodeFromID(a_key, a_outKeyCode);
	}

	void BSInputDeviceManager::ProcessGamepadEnabledChange()
	{
		if (GetRuntimeData().valueQueued) {
			bool* pGamepadEnable = reinterpret_cast<bool*>(RELOCATION_ID(511901, 388465).address());
			*pGamepadEnable = true;
			GetRuntimeData().valueQueued = false;
		}
	}

	void BSInputDeviceManager::ReinitializeMouse()
	{
		auto mouse = GetMouse();
		if (mouse) {
			mouse->Reinitialize();
		}
	}

	void BSInputDeviceManager::CreateInputDevices()
	{
		for (std::uint32_t i = 0; i < INPUT_DEVICE::kTotal; i++) {
			devices[i] = BSInputDeviceFactory::CreateInputDevice(static_cast<INPUT_DEVICE>(i));
			devices[i]->Initialize();
		}
	}

	void BSInputDeviceManager::ResetInputDevices()
	{
		for (std::uint32_t i = 0; i < INPUT_DEVICE::kTotal; i++) {
			if (devices[i]) {
				devices[i]->ClearInputState();
			}
		}
	}

	void BSInputDeviceManager::DestroyInputDevices()
	{
		for (std::uint32_t i = 0; i < INPUT_DEVICE::kTotal; i++) {
			if (devices[i]) {
				devices[i]->Shutdown();
				BSInputDeviceFactory::DestroyInputDevice(devices[i]);
			}
		}
	}

	// Called by Main::Update()
	void BSInputDeviceManager::PollInputDevices(float a_secsSinceLastFrame)
	{
		// Calls Process() on each device
		// Calls ControlMap::ProcessButtonEvent(ButtonEvent*)
		// Calls Rumble::Update(float secsSinceLastFrame)
		// Emits the last InputEvent
		// resets the global BSInputEventQueue
		using func_t = decltype(&BSInputDeviceManager::PollInputDevices);
		static REL::Relocation<func_t> func{ RELOCATION_ID(67315, 68617) };
		return func(this, a_secsSinceLastFrame);
	}
}
