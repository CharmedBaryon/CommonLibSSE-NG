#include "RE/B/BGSAutoWater.h"

namespace RE
{
	BGSAutoWater* BGSAutoWater::GetSingleton()
	{
		static REL::Relocation<BGSAutoWater**> singleton{ RELOCATION_ID(514289, 400449) };
		return *singleton;
	}

	void BGSAutoWater::GenerateMultibounds(TESObjectCELL* a_cell)
	{
		using func_t = decltype(&BGSAutoWater::GenerateMultibounds);
		static REL::Relocation<func_t> func{ RELOCATION_ID(31235, 32035) };
		func(this, a_cell);
	}

	void BGSAutoWater::GeneratePlaceableWater(TESObjectCELL* a_cell, NiAVObject* a_water)
	{
		using func_t = decltype(&BGSAutoWater::GeneratePlaceableWater);
		static REL::Relocation<func_t> func{ RELOCATION_ID(31236, 32036) };
		func(this, a_cell, a_water);
	}

	void BGSAutoWater::GeneratePlaceableWaterForCell(TESObjectCELL* a_cell, bool a_unk)
	{
		using func_t = decltype(&BGSAutoWater::GeneratePlaceableWaterForCell);
		static REL::Relocation<func_t> func{ RELOCATION_ID(31230, 32030) };
		func(this, a_cell, a_unk);
	}
}
