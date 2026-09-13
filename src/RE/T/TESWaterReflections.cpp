#include "RE/T/TESWaterReflections.h"

namespace RE
{
	bool TESWaterReflections::UpdateActor()
	{
		using func_t = decltype(&TESWaterReflections::UpdateActor);
		static REL::Relocation<func_t> func{ RELOCATION_ID(31373, 32160) };
		return func(this);
	}

	void TESWaterReflections::Dtor()
	{
		using func_t = decltype(&TESWaterReflections::Dtor);
		static REL::Relocation<func_t> func{ RELOCATION_ID(31451, 32256) };
		func(this);
	}
}
