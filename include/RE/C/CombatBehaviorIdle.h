#pragma once

#include "RE/A/AITimer.h"
#include "RE/C/CombatBehavior.h"

namespace RE
{
	class CombatBehaviorIdle : public CombatBehaviorAction
	{
	public:
		CombatBehaviorIdle(float interval);

		void Update(CombatBehaviorThread* a_thread);

		// members
		AITimer timer;  // 00
	};
	static_assert(sizeof(CombatBehaviorIdle) == 0x8);
}
