#pragma once

#include "RE/C/CombatBehaviorParallel.h"

namespace RE
{
	class CombatBehaviorSpawnParallel : public CombatBehaviorParallel
	{
	public:
		CombatBehaviorSpawnParallel() = default;

		void Enter();

		// members
		uint32_t copies;  // 20
	};
	static_assert(sizeof(CombatBehaviorSpawnParallel) == 0x28);
}
