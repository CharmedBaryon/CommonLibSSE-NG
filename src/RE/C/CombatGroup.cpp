#include "RE/C/CombatGroup.h"

namespace RE
{
	bool CombatGroup::IsSearching() const
	{
		using func_t = decltype(&CombatGroup::IsSearching);
		static REL::Relocation<func_t> func{ RELOCATION_ID(48023, 0) };
		return func(this);
	}
}
