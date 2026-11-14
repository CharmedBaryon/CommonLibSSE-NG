#pragma once

#include "RE/B/BSFixedString.h"

namespace RE
{
	class CombatBlackboardFlag
	{
	public:
		CombatBlackboardFlag(const char* a_name, std::uint8_t a_bit);

		static CombatBlackboardFlag* GetHiding();
		static CombatBlackboardFlag* GetUsingCover();

		// members
		BSFixedString name;   // 00
		uint32_t      flag;   // 08
		uint32_t      pad0C;  // 0C
	};
	static_assert(sizeof(CombatBlackboardFlag) == 0x10);
}
