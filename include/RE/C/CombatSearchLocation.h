#pragma once

#include "RE/A/AITimeStamp.h"
#include "RE/B/BGSWorldLocation.h"

namespace RE
{
	class CombatSearchLocation
	{
	public:
		// members
		BGSWorldLocation loc;        // 00
		AITimeStamp      timestamp;  // 18
		float            unk20;      // 20
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(CombatSearchLocation) == 0x20);
}
