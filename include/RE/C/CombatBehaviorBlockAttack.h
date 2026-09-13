#pragma once

#include "RE/A/AITimer.h"
#include "RE/C/CombatBehavior.h"

namespace RE
{
	class CombatBehaviorBlockAttack : public CombatBehaviorBranch
	{
	public:
		void Enter();
		void Exit();
		void Update();

		// members
		AITimer timer_block;        // 00
		AITimer child_retry_timer;  // 08
	};
	static_assert(sizeof(CombatBehaviorBlockAttack) == 0x10);
}
