#include "RE/T/TESCamera.h"

namespace RE
{
	void TESCamera::SetState(TESCameraState* a_state)
	{
		using func_t = decltype(&TESCamera::SetState);
		static REL::Relocation<func_t> func{ RELOCATION_ID(32290, 33026) };
		return func(this, a_state);
	}
}
