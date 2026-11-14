#include "RE/C/CombatBehaviorParallel.h"

namespace RE
{
	void CombatBehaviorParallel::Abort()
	{
		using func_t = decltype(&CombatBehaviorParallel::Abort);
		static REL::Relocation<func_t> func{ RELOCATION_ID(46170, 0) };
		return func(this);
	}

	void CombatBehaviorParallel::Enter()
	{
		using func_t = decltype(&CombatBehaviorParallel::Enter);
		static REL::Relocation<func_t> func{ RELOCATION_ID(46168, 0) };
		return func(this);
	}

	void CombatBehaviorParallel::Update()
	{
		using func_t = decltype(&CombatBehaviorParallel::Enter);
		static REL::Relocation<func_t> func{ RELOCATION_ID(46169, 0) };
		return func(this);
	}
}
