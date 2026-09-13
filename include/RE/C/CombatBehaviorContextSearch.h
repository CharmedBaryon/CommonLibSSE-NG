#pragma once

#include "RE/C/CombatBehaviorContext.h"

namespace RE
{
	class CombatBehaviorContextSearch : public CombatBehaviorContext
	{
	public:
		uint32_t QCurrentSearchPriority() const { return priority; }

		// members
		AITimer  timer;     // 00
		uint32_t priority;  // 08
	};
	static_assert(sizeof(CombatBehaviorContextSearch) == 0xC);
}
