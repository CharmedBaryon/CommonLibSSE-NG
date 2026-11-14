#pragma once

#include "RE/C/CombatBehaviorAdvance.h"

namespace RE
{
	class CombatBehaviorReposition : public CombatBehaviorAdvance
	{
	public:
		void Enter();
	};
	static_assert(sizeof(CombatBehaviorReposition) == 0x20);
}
