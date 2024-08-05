#include "RE/A/ArmorRatingVisitorBase.h"

namespace RE
{
	BSContainer::ForEachResult ArmorRatingVisitorBase::Visit(InventoryEntryData* a_entryData)
	{
		using func_t = decltype(&ArmorRatingVisitorBase::Visit);
		static REL::Relocation<func_t> func(RELOCATION_ID(39223, 40299));
		return func(this, a_entryData);
	}
}
