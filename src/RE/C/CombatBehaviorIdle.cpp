#include "RE/C/CombatBehaviorIdle.h"

namespace RE
{
	CombatBehaviorIdle::CombatBehaviorIdle(float interval)
	{
		using func_t = CombatBehaviorIdle*(CombatBehaviorIdle*, float);
		static REL::Relocation<func_t> func{ RELOCATION_ID(46187, 0) };
		func(this, interval);
	}

	void CombatBehaviorIdle::Update()
	{
		using func_t = decltype(&CombatBehaviorIdle::Update);
		static REL::Relocation<func_t> func{ RELOCATION_ID(32436, 0) };
		return func(this);
	}
}
