#pragma once

#include "RE/C/CombatBehaviorContext.h"

namespace RE
{
	class CombatBehaviorContextDodgeThreat : public CombatBehaviorContext
	{
	public:
		bool CheckShouldDodge() const;
	};
	static_assert(sizeof(CombatBehaviorContextDodgeThreat) == 0x4);
}
