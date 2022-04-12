#include "RE/B/BSInputDeviceManager.h"

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
		REL::Relocation<BSInputDeviceManager**> singleton{ Offset::BSInputDeviceManager::Singleton };
		return *singleton;
	}

	BSPCGamepadDeviceDelegate* BSInputDeviceManager::GetGamepad()
	{
		auto handler = GetGamepadHandler();
		return handler ? handler->currentPCGamePadDelegate : nullptr;
	}

	BSPCGamepadDeviceHandler* BSInputDeviceManager::GetGamepadHandler()
	{
		return static_cast<BSPCGamepadDeviceHandler*>(devices[stl::to_underlying(INPUT_DEVICE::kGamepad)]);
	}

	BSWin32KeyboardDevice* BSInputDeviceManager::GetKeyboard()
	{
		return static_cast<BSWin32KeyboardDevice*>(devices[stl::to_underlying(INPUT_DEVICE::kKeyboard)]);
	}

	BSWin32MouseDevice* BSInputDeviceManager::GetMouse()
	{
		return static_cast<BSWin32MouseDevice*>(devices[stl::to_underlying(INPUT_DEVICE::kMouse)]);
	}

	BSTrackedControllerDevice* BSInputDeviceManager::GetVRControllerRight()
	{
#ifndef ENABLE_SKYRIM_VR
		return nullptr;
#else
		if (!REL::Module::get().IsVR()) {
			return nullptr;
		}
		return static_cast<BSTrackedControllerDevice*>(devices[stl::to_underlying(INPUT_DEVICE::kVRRight)]);
#endif
	}

	BSTrackedControllerDevice* BSInputDeviceManager::GetVRControllerLeft()
	{
#ifndef ENABLE_SKYRIM_VR
		return nullptr;
#else
		if (!REL::Module::get().IsVR()) {
			return nullptr;
		}
		return static_cast<BSTrackedControllerDevice*>(devices[stl::to_underlying(INPUT_DEVICE::kVRLeft)]);
#endif
	}

	BSWin32VirtualKeyboardDevice* BSInputDeviceManager::GetVirtualKeyboard()
	{
		return static_cast<BSWin32VirtualKeyboardDevice*>(devices[stl::to_underlying(INPUT_DEVICE::kVirtualKeyboard)]);
	}

	bool BSInputDeviceManager::IsGamepadConnected()
	{
		auto handler = GetGamepadHandler();
		return handler && handler->currentPCGamePadDelegate;
	}

	bool BSInputDeviceManager::IsGamepadEnabled()
	{
		auto handler = GetGamepadHandler();
		return handler && handler->currentPCGamePadDelegate && handler->currentPCGamePadDelegate->IsEnabled();
	}
}
