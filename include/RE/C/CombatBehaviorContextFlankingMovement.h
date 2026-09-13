#pragma once

#include "RE/C/CombatBehaviorContext.h"

namespace RE
{
	class CombatBehaviorContextFlankingMovement : public CombatBehaviorContext
	{
	public:
		bool CheckShouldStalk();

		// members
		uint64_t field0;
	};
	static_assert(sizeof(CombatBehaviorContextFlankingMovement) == 0x8);
}
