#include "RE/C/CombatBehaviorSurround.h"

namespace RE
{
	void CombatBehaviorSurround::Enter()
	{
		using func_t = decltype(&CombatBehaviorSurround::Enter);
		static REL::Relocation<func_t> func{ RELOCATION_ID(46709, 0) };
		return func(this);
	}

	void CombatBehaviorSurround::Update()
	{
		using func_t = decltype(&CombatBehaviorSurround::Enter);
		static REL::Relocation<func_t> func{ RELOCATION_ID(46710, 0) };
		return func(this);
	}
}
