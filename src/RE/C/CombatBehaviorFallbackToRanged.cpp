#include "RE/C/CombatBehaviorFallbackToRanged.h"

namespace RE
{
	void CombatBehaviorFallbackToRanged::Enter()
	{
		using func_t = decltype(&CombatBehaviorFallbackToRanged::Enter);
		static REL::Relocation<func_t> func{ RELOCATION_ID(46716, 0) };
		return func(this);
	}

	void CombatBehaviorFallbackToRanged::Update()
	{
		using func_t = decltype(&CombatBehaviorFallbackToRanged::Update);
		static REL::Relocation<func_t> func{ RELOCATION_ID(46717, 0) };
		return func(this);
	}
}
