#include "RE/C/CombatBlackboardFlag.h"

namespace RE
{
	CombatBlackboardFlag::CombatBlackboardFlag()
	{
		using func_t = CombatBlackboardFlag*(CombatBlackboardFlag*);
		static REL::Relocation<func_t> func{ RELOCATION_ID(43311, 0) };
		func(this);
	}

	CombatBlackboardFlag* CombatBlackboardFlag::GetHiding()
	{
		static REL::Relocation<CombatBlackboardFlag*> value{ RELOCATION_ID(518923, 0) };
		return value.get();
	}

	CombatBlackboardFlag* CombatBlackboardFlag::GetUsingCover()
	{
		static REL::Relocation<CombatBlackboardFlag*> value{ RELOCATION_ID(519134, 0) };
		return value.get();
	}
}
