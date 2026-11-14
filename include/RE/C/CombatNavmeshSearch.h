#pragma once

#include "RE/B/BSFastNavmeshTriLocation.h"
#include "RE/B/BSNavmeshSearch.h"

namespace RE
{
	class CombatNavmeshSearch : public BSNavmeshSearch
	{
	public:
		inline static constexpr auto RTTI = RTTI_CombatNavmeshSearch;
		inline static constexpr auto VTABLE = VTABLE_CombatNavmeshSearch;

		~CombatNavmeshSearch() override;

		// members
		void*                     pad08[(0x1D0 - 0x08) / 8];  // 008
		BSFastNavmeshTriLocation* bestGoal;                   // 1D0 - null until A* result==2; confirmed SE+VR binary RE
	};
	static_assert(sizeof(CombatNavmeshSearch) == 0x1D8, "size");
}
