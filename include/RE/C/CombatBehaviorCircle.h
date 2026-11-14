#pragma once

#include "RE/A/AITimer.h"
#include "RE/C/CombatBehavior.h"
#include "RE/C/CombatPath.h"
#include "RE/N/NiSmartPointer.h"

namespace RE
{
	class CombatBehaviorCircle : public CombatBehaviorAction
	{
	public:
		void Enter();
		void Update();

		// members
		NiPointer<CombatPath> path;   // 00
		AITimer               timer;  // 08
	};
	static_assert(sizeof(CombatBehaviorCircle) == 0x10);
}
