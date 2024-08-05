#include "RE/T/TESWorldSpace.h"

namespace RE
{
	bool TESWorldSpace::HasMaxHeightData() const
	{
		return maxHeightData != nullptr;
	}

	TESObjectCELL* TESWorldSpace::GetSkyCell()
	{
		using func_t = decltype(&TESWorldSpace::GetSkyCell);
		static REL::Relocation<func_t> func{ RELOCATION_ID(20095, 20543) };
		return func(this);
	}

	float TESWorldSpace::GetDefaultWaterHeight() const
	{
		auto world = this;
		while (world->parentWorld && world->parentUseFlags.any(ParentUseFlag::kUseLandData)) {
			world = world->parentWorld;
		}
		return world->defaultWaterHeight;
	}
}
