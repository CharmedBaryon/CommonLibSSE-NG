#include "RE/T/TESAmmo.h"

namespace RE
{
	bool TESAmmo::IgnoresNormalWeaponResistance()
	{
		return GetRuntimeData().data.flags.all(AMMO_DATA::Flag::kIgnoresNormalWeaponResistance);
	}

	bool TESAmmo::IsBolt()
	{
		return GetRuntimeData().data.flags.none(AMMO_DATA::Flag::kNonBolt);
	}
}
