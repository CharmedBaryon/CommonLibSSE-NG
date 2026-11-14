#include "RE/C/CombatBlackboardFlag.h"

namespace RE
{
	CombatBlackboardFlag::CombatBlackboardFlag(const char* a_name, std::uint8_t a_bit)
	{
		using func_t = CombatBlackboardFlag*(CombatBlackboardFlag*, const char*, std::uint8_t);
		static REL::Relocation<func_t> func{ RELOCATION_ID(43311, 0) };
		func(this, a_name, a_bit);
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
