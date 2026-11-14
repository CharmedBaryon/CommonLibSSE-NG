#pragma once

#include "RE/C/CombatObject.h"

namespace RE
{
	class CombatTargetLocation : public CombatObject
	{
	public:
		TES_HEAP_REDEFINE_NEW();

		// members
		uint32_t     field_10;  // 10
		uint32_t     field_14;  // 14
		float        angle[4];  // 18
		RE::NiPoint3 V;         // 28
		uint32_t     pad34;     // 34
	};
	static_assert(sizeof(CombatTargetLocation) == 0x38);
}
