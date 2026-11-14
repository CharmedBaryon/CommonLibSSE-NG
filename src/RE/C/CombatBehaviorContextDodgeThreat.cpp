#include "RE/C/CombatBehaviorContextDodgeThreat.h"

namespace RE
{
	bool CombatBehaviorContextDodgeThreat::CheckShouldDodge() const
	{
		using func_t = decltype(&CombatBehaviorContextDodgeThreat::CheckShouldDodge);
		static REL::Relocation<func_t> func{ RELOCATION_ID(46589, 0) };
		return func(this);
	}
}
