#include "RE/C/CombatBehaviorAdvance.h"

namespace RE
{
	void CombatBehaviorAdvance::Enter()
	{
		using func_t = decltype(&CombatBehaviorAdvance::Enter);
		static REL::Relocation<func_t> func{ RELOCATION_ID(46703, 0) };
		return func(this);
	}

	void CombatBehaviorAdvance::Update()
	{
		using func_t = decltype(&CombatBehaviorAdvance::Update);
		static REL::Relocation<func_t> func{ RELOCATION_ID(46704, 0) };
		return func(this);
	}
}
