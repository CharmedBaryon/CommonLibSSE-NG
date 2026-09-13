#include "RE/B/BSInputDeviceFactory.h"
#include "RE/B/BSPCGamepadDeviceHandler.h"
#include "RE/B/BSWin32MouseDevice.h"

namespace RE
{
	BSIInputDevice* BSInputDeviceFactory::CreateInputDevice(INPUT_DEVICE a_deviceType)
	{
		using func_t = decltype(&BSInputDeviceFactory::CreateInputDevice);
		static REL::Relocation<func_t> func{ RELOCATION_ID(67431, 68738) };
		return func(a_deviceType);
	}

	void BSInputDeviceFactory::DestroyInputDevice(BSIInputDevice* a_device)
	{
		delete a_device;
	}
}
