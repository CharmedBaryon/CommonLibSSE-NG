#include "RE/B/BSWin32GamepadDevice.h"

namespace RE
{
	BSWin32GamepadDevice::BSWin32GamepadDevice() :
		BSPCGamepadDeviceDelegate()
	{
		auto& rt = GetRuntimeData();
		rt.previousState = {};
		rt.previousLT = 0.0f;
		rt.previousRT = 0.0f;
		rt.previousLX = 0.0f;
		rt.previousLY = 0.0f;
		rt.previousRX = 0.0f;
		rt.previousRY = 0.0f;
		rt.currentState = {};
		rt.currentLT = 0.0f;
		rt.currentRT = 0.0f;
		rt.currentLX = 0.0f;
		rt.currentLY = 0.0f;
		rt.currentRX = 0.0f;
		rt.currentRY = 0.0f;
	}
}
