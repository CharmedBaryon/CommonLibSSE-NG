#pragma once

#include "RE/C/CombatBehaviorContextMagic.h"

namespace RE
{
	class TESShout;

	class CombatBehaviorContextShout : public CombatBehaviorContextMagic
	{
	public:
		float CalcCastMagicChance() const;

		// members
		TESShout* shout;  // 20
	};
	static_assert(sizeof(CombatBehaviorContextShout) == 0x28);
}
