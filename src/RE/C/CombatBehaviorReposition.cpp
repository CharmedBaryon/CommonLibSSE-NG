#include "RE/C/CombatBehaviorReposition.h"

namespace RE
{
	void CombatBehaviorReposition::Enter()
	{
		using func_t = decltype(&CombatBehaviorReposition::Enter);
		static REL::Relocation<func_t> func{ RELOCATION_ID(46708, 0) };
		return func(this);
	}
}
