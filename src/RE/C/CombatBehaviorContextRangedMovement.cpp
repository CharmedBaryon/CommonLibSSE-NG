#include "RE/C/CombatBehaviorContextRangedMovement.h"

namespace RE
{
	bool RE::CombatBehaviorContextRangedMovement::CheckOutOfRange() const
	{
		using func_t = decltype(&CombatBehaviorContextRangedMovement::CheckOutOfRange);
		static REL::Relocation<func_t> func{ RELOCATION_ID(48467, 0) };
		return func(this);
	}
}
