#pragma once

#include "RE/A/AITimer.h"
#include "RE/C/CombatBehavior.h"

namespace RE
{
	class CombatBehaviorBlock : public CombatBehaviorBranch
	{
	public:
		void Enter();
		void Exit();
		void Update();

		// members
		AITimer timer_block;           // 00
		AITimer child_retry_timer;     // 08
		AITimer check_distance_timer;  // 10
	};
	static_assert(sizeof(CombatBehaviorBlock) == 0x18);
}
