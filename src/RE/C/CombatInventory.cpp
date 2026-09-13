#include "RE/C/CombatInventory.h"

namespace RE
{
	float CombatInventory::QRawMaxRange() const
	{
		using func_t = decltype(&CombatInventory::QRawMaxRange);
		static REL::Relocation<func_t> func{ RELOCATION_ID(48463, 0) };
		return func(this);
	}
}
