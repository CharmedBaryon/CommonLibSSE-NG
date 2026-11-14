#include "RE/I/ItemHarvested.h"

namespace RE
{
	BSTEventSource<TESHarvestedEvent::ItemHarvested>* TESHarvestedEvent::GetEventSource()
	{
		using func_t = decltype(&TESHarvestedEvent::GetEventSource);
		static REL::Relocation<func_t> func{ RELOCATION_ID(14704, 14875) };
		return func();
	}
}
