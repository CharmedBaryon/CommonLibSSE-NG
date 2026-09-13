#include "RE/B/BSGamepadDevice.h"

namespace RE
{
	BSGamepadDevice::BSGamepadDevice() :
		BSInputDevice()
	{
		auto& rt = GetRuntimeData();
		rt.userIndex = -1;
		rt.connected = false;
		rt.listeningForInput = false;
		rt.padCE = 0;
		BSInputDevice::GetRuntimeData().device = INPUT_DEVICE::kGamepad;
		const char* gamepadFile = *reinterpret_cast<const char**>(RELOCATION_ID(511903, 388468).address());
		LoadControlsDefinitionFile(gamepadFile);
	}
}
