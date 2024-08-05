#include "RE/B/BSPCGamepadDeviceHandler.h"

namespace RE
{
	void BSPCGamepadDeviceHandler::InitializeDelegate()
	{
		using func_t = decltype(&BSPCGamepadDeviceHandler::InitializeDelegate);
		static REL::Relocation<func_t> func{ RELOCATION_ID(67457, 68762) };
		return func(this);
	}

	BSPCGamepadDeviceHandler::BSPCGamepadDeviceHandler() :
		BSIInputDevice()	
	{
		this->GetRuntimeData().currentPCGamePadDelegate = nullptr;
	}
}
