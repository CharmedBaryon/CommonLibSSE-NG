#pragma once

#include "RE/C/CombatObject.h"

namespace RE
{
	class CombatTargetLocation;
	class CombatTargetLocationSearch;

	class CombatTargetLocationSearchResult : public RE::CombatObject
	{
	public:
		// members
		CombatTargetLocationSearch* search;
		CombatTargetLocation*       ans;
	};
	static_assert(sizeof(CombatTargetLocationSearchResult) == 0x20);
}
