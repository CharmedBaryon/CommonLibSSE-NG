#include "RE/B/BSWin32MouseDevice.h"

namespace RE
{
	BSWin32MouseDevice::BSWin32MouseDevice() :
		BSMouseDevice()
	{
		auto& rt = GetRuntimeData();
		rt.dInputDevice = nullptr;
		rt.dInputPrevState = {};
		rt.dInputNextState = {};
		rt.notInitialized = false;
		std::memset(&rt.reinitializeLock, 0, sizeof(rt.reinitializeLock));
	}
}
