#include "RE/C/CombatBehaviorSpawnParallel.h"

namespace RE
{
	void CombatBehaviorSpawnParallel::Enter()
	{
		using func_t = decltype(&CombatBehaviorSpawnParallel::Enter);
		static REL::Relocation<func_t> func{ RELOCATION_ID(46173, 0) };
		return func(this);
	}
}
