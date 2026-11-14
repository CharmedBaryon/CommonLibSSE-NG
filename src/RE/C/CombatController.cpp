#include "RE/C/CombatController.h"

namespace RE
{
	bool RE::CombatController::CheckCombatArea(Actor* atatcker) const
	{
		using func_t = decltype(&CombatController::CheckCombatArea);
		static REL::Relocation<func_t> func{ RELOCATION_ID(32508, 0) };
		return func(this, atatcker);
	}

	bool CombatController::CheckStraightPath(NiPoint3& dst, float dist, float min_dist) const
	{
		using func_t = decltype(&CombatController::CheckStraightPath);
		static REL::Relocation<func_t> func{ RELOCATION_ID(32513, 0) };
		return func(this, dst, dist, min_dist);
	}
}
