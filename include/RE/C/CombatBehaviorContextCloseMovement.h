#pragma once

#include "RE/C/CombatAimController.h"
#include "RE/C/CombatBehaviorContext.h"
#include "RE/C/CombatTargetLocation.h"
#include "RE/N/NiSmartPointer.h"

namespace RE
{
	class CombatBehaviorContextCloseMovement : public CombatBehaviorContext
	{
	public:
		bool CheckOutOfPosition() const;
		bool CheckOutOfRange() const;
		bool CheckShouldFallbackToRanged() const;
		bool CheckShouldStop(float R) const;
		void Enter();
		void SetTargetLocation(const NiPointer<CombatTargetLocation>& loc);

		// members
		NiPointer<CombatAimController>  aim_controller;
		NiPointer<CombatTargetLocation> target_loc;
	};
	static_assert(sizeof(CombatBehaviorContextCloseMovement) == 0x10);
}
