#pragma once

#include "RE/C/CombatBehavior.h"

namespace RE
{
	class CombatBehaviorSequence : public CombatBehaviorNode
	{
	public:
		void Enter();
		void Update();

		// members
		uint32_t ind;  // 00
	};
	static_assert(sizeof(CombatBehaviorSequence) == 0x4);
}
