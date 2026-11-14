#pragma once

#include "RE/A/AITimer.h"
#include "RE/N/NiPoint3.h"

namespace RE
{
	class BGSAttackData;

	class CombatAttackData
	{
	public:
		// members
		BGSAttackData* attackdata;
		NiPoint3       hitframe_pos;
		NiPoint3       final_pos;
		float          hitframe_pos_len;
		float          hitframe_time;
		AITimer        cooldown_timer;
	};
	static_assert(sizeof(CombatAttackData) == 0x30);
}
