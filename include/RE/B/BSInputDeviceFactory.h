#pragma once

#include "RE/B/BSIInputDevice.h"
#include "RE/I/InputDevices.h"

namespace RE
{
	class BSInputDeviceFactory
	{
	public:
		static BSIInputDevice* CreateInputDevice(INPUT_DEVICE a_deviceType);
		static void            DestroyInputDevice(BSIInputDevice* a_device);

	private:
		KEEP_FOR_RE()
	};
}