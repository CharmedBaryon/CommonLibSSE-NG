#include "RE/C/CombatBehaviorFallback.h"

namespace RE
{
	void CombatBehaviorFallback::Enter()
	{
		using func_t = decltype(&CombatBehaviorFallback::Enter);
		static REL::Relocation<func_t> func{ RELOCATION_ID(46712, 0) };
		return func(this);
	}

	void CombatBehaviorFallback::Update()
	{
		using func_t = decltype(&CombatBehaviorFallback::Update);
		static REL::Relocation<func_t> func{ RELOCATION_ID(46713, 0) };
		return func(this);
	}
}
