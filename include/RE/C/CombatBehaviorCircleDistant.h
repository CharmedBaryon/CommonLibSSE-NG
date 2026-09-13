#pragma once

#include "RE/C/CombatBehavior.h"
#include "RE/C/CombatPath.h"
#include "RE/N/NiSmartPointer.h"

namespace RE
{
	class CombatBehaviorCircleDistant : public CombatBehaviorAction
	{
	public:
		void Enter();
		void Update();

		// members
		NiPointer<CombatPath> path;  // 00
	};
	static_assert(sizeof(CombatBehaviorCircleDistant) == 0x8);
}
