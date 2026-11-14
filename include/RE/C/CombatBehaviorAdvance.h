#pragma once

#include "RE/C/CombatAimController.h"
#include "RE/C/CombatBehavior.h"
#include "RE/C/CombatPath.h"
#include "RE/C/CombatTargetLocationSearch.h"
#include "RE/C/CombatTargetLocationSearchResult.h"
#include "RE/N/NiSmartPointer.h"

namespace RE
{
	class CombatBehaviorAdvance : public CombatBehaviorAction
	{
	public:
		void Enter();
		void Update();

		// members
		NiPointer<CombatPath>                       path;            // 00
		NiPointer<CombatAimController>              aim_control;     // 08
		NiPointer<CombatTargetLocationSearch>       locationSearch;  // 10
		NiPointer<CombatTargetLocationSearchResult> searchResult;    // 18
	};
	static_assert(sizeof(CombatBehaviorAdvance) == 0x20);
}
