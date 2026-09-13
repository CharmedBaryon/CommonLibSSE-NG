#include "RE/B/BSKeyboardDevice.h"

namespace RE
{
	BSKeyboardDevice::BSKeyboardDevice() :
		BSInputDevice()
	{
		BSInputDevice::GetRuntimeData().device = INPUT_DEVICE::kKeyboard;
		const char* prefix = *reinterpret_cast<const char**>(RELOCATION_ID(511916, 388487).address());
		const char* locale = *reinterpret_cast<const char**>(RELOCATION_ID(500908, 358892).address());
		std::string path = prefix + std::string(locale) + ".txt";
		if (!LoadControlsDefinitionFile(path.c_str())) {
			path = prefix + std::string("ENGLISH.txt");
			if (!LoadControlsDefinitionFile(path.c_str())) {
				path = prefix;
				path = path.substr(0, path.find_last_of('_')) + ".txt";
				LoadControlsDefinitionFile(path.c_str());
			}
		}
	}
}
