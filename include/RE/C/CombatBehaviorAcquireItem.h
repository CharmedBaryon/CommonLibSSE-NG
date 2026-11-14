#pragma once

#include "RE/A/AITimer.h"
#include "RE/C/CombatAcquireItem.h"
#include "RE/C/CombatBehavior.h"
#include "RE/C/CombatPath.h"

namespace RE
{
	class CombatBehaviorAcquireItem : public CombatBehaviorAction
	{
	public:
		void Enter();
		void Update();

		// members
		NiPointer<CombatPath> path;             // 00
		CombatAcquireItem     item;             // 08
		AITimer               pickup_timer;     // 20
		AITimer               animation_timer;  // 28
	};
	static_assert(sizeof(CombatBehaviorAcquireItem) == 0x30);
}
