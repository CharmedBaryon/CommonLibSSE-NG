#pragma once

#include "RE/C/CombatBehaviorContext.h"

namespace RE
{
	class CombatTrackTargetAimController;

	class CombatBehaviorContextRangedMovement : public CombatBehaviorContext
	{
	public:
		bool CheckOutOfRange() const;

		// members
		CombatTrackTargetAimController* aimController;  // 00
	};
	static_assert(sizeof(CombatBehaviorContextRangedMovement) == 0x8);
}
