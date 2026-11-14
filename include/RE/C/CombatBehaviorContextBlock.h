#pragma once

#include "RE/C/CombatBehaviorContextMelee.h"

namespace RE
{
	class CombatBehaviorContextBlock : public CombatBehaviorContextMelee
	{
	public:
		bool CheckStopBlocking();

		// members
		uint64_t field40;
	};
	static_assert(sizeof(CombatBehaviorContextBlock) == 0x48);
}
