#include "RE/C/CombatBehaviorCircle.h"

namespace RE
{
	void CombatBehaviorCircle::Enter()
	{
		using func_t = decltype(&CombatBehaviorCircle::Enter);
		static REL::Relocation<func_t> func{ RELOCATION_ID(46720, 0) };
		return func(this);
	}

	void CombatBehaviorCircle::Update()
	{
		using func_t = decltype(&CombatBehaviorCircle::Update);
		static REL::Relocation<func_t> func{ RELOCATION_ID(46721, 0) };
		return func(this);
	}
}
