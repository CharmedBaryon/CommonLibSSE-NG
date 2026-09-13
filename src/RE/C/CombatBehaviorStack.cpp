#include "RE/C/CombatBehaviorStack.h"

namespace RE
{
	void CombatBehaviorStack::CheckBuffer(std::uint32_t a_size)
	{
		using func_t = decltype(&CombatBehaviorStack::CheckBuffer);
		static REL::Relocation<func_t> func{ RELOCATION_ID(32426, 33159) };
		return func(this, a_size);
	}
}
