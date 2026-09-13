#include "RE/B/BSPCGamepadDeviceDelegate.h"

namespace RE
{
	BSPCGamepadDeviceDelegate::BSPCGamepadDeviceDelegate() :
		BSGamepadDevice()
	{
		GetRuntimeData().gamepadDeviceHandler = nullptr;
	}
}
