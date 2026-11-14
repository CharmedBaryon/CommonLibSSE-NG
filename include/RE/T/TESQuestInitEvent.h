#pragma once

#include "RE/B/BSCoreTypes.h"

namespace RE
{
	struct TESQuestInitEvent
	{
	public:
		// members
		FormID formID;  // 0
	};
	static_assert(sizeof(TESQuestInitEvent) == 0x4);
}
