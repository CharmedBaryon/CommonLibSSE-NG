#include "RE/C/CombatTargetLocationSearch.h"

namespace RE
{
	CombatTargetLocationSearch::CombatTargetLocationSearch(Actor* actor, Actor* target, float R)
	{
		using func_t = CombatTargetLocationSearch*(CombatTargetLocationSearch*, Actor*, Actor*, float);
		static REL::Relocation<func_t> func{ RELOCATION_ID(45702, 47011) };
		func(this, actor, target, R);
	}
}
