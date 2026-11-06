#include "RE/C/CombatTargetLocationSearch.h"

namespace RE
{
	CombatTargetLocationSearch* CombatTargetLocationSearch::Ctor(Actor* a_actor, Actor* a_target, float a_radius)
	{
		using func_t = CombatTargetLocationSearch*(CombatTargetLocationSearch*, Actor*, Actor*, float);
		static REL::Relocation<func_t> func{ RELOCATION_ID(45702, 47011) };
		return func(this, a_actor, a_target, a_radius);
	}
}
