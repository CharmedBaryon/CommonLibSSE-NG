#include "RE/R/Rumble.h"

namespace RE
{
	void Rumble::DisableRumble()
	{
		//  XINPUT_VIBRATION pVibration;
		//  pVibration = 0;
		//  return XInputSetState(0, &pVibration);
		using func_t = decltype(&Rumble::DisableRumble);
		static REL::Relocation<func_t> func{ RELOCATION_ID(67224, 68533) };
		return func();
	}
}
