#include "RE/C/CombatBehaviorContextFlee.h"

namespace RE
{
	bool CombatBehaviorContextFlee::CheckShouldFlee() const
	{
		using func_t = decltype(&CombatBehaviorContextFlee::CheckShouldFlee);
		static REL::Relocation<func_t> func{ RELOCATION_ID(47404, 0) };
		return func(this);
	}

	bool CombatBehaviorContextFlee::StartFlee() const
	{
		using func_t = decltype(&CombatBehaviorContextFlee::StartFlee);
		static REL::Relocation<func_t> func{ RELOCATION_ID(47405, 0) };
		return func(this);
	}
}
