#pragma once

#include "RE/C/CombatBehaviorContext.h"

namespace RE
{
	class CombatBehaviorContextFlee : public CombatBehaviorContext
	{
	public:
		bool CheckShouldFlee() const;
		bool StartFlee() const;

		// members
		uint64_t field0;
	};
	static_assert(sizeof(CombatBehaviorContextFlee) == 0x8);
}
