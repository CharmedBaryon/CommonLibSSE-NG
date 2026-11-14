#include "RE/C/CombatAcquireItem.h"

namespace RE
{
	bool CombatAcquireItem::IsValid() const
	{
		using func_t = decltype(&CombatAcquireItem::IsValid);
		static REL::Relocation<func_t> func{ RELOCATION_ID(46338, 0) };
		return func(this);
	}
}
