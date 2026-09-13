#include "RE/C/CombatBehaviorPause.h"

namespace RE
{
	void CombatBehaviorPause::Enter()
	{
		using func_t = decltype(&CombatBehaviorPause::Enter);
		static REL::Relocation<func_t> func{ RELOCATION_ID(46190, 0) };
		return func(this);
	}
}
