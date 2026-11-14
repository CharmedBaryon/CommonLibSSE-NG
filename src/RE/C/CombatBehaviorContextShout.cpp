#include "RE/C/CombatBehaviorContextShout.h"

namespace RE
{
	float CombatBehaviorContextShout::CalcCastMagicChance() const
	{
		using func_t = decltype(&CombatBehaviorContextShout::CalcCastMagicChance);
		static REL::Relocation<func_t> func{ RELOCATION_ID(48806, 0) };
		return func(this);
	}
}
