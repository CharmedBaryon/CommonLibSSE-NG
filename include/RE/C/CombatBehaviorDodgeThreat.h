#pragma once

#include "RE/A/AITimer.h"
#include "RE/C/CombatAimController.h"
#include "RE/C/CombatBehavior.h"
#include "RE/C/CombatPath.h"
#include "RE/C/CombatThreat.h"

namespace RE
{
	class BSPathingRequest;

	class CombatBehaviorDodgeThreat : public CombatBehaviorAction
	{
	public:
		void Enter();
		void Exit();
		void Update();

		// members
		NiPointer<CombatPath>          path;                   // 00
		NiPointer<BSPathingRequest>    CurrentPathingRequest;  // 08
		NiPointer<CombatAimController> aim_control;            // 10
		NiPointer<CombatThreat>        threat;                 // 18
		AITimer                        done_timer;             // 20
		AITimer                        checkdodged_timer;      // 28
	};
	static_assert(sizeof(CombatBehaviorDodgeThreat) == 0x30);
}
