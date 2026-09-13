#include "RE/G/GetWornMaskVisitor.h"
#include "RE/I/InventoryEntryData.h"
#include "RE/T/TESBoundObject.h"

namespace RE
{
	BSContainer::ForEachResult GetWornMaskVisitor::Visit(InventoryEntryData* a_entryData)
	{
		using func_t = decltype(&GetWornMaskVisitor::Visit);
		static REL::Relocation<func_t> func{ RELOCATION_ID(15991, 16233) };
		return func(this, a_entryData);
	}
}
