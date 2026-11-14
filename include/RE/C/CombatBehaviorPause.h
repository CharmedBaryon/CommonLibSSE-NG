#pragma once

#include "RE/A/AITimer.h"
#include "RE/C/CombatBehavior.h"

namespace RE
{
	class CombatBehaviorPause : public CombatBehaviorAction
	{
	public:
		CombatBehaviorPause() = default;

		void Enter();
	};
	static_assert(sizeof(CombatBehaviorPause) == 0x4);
}
