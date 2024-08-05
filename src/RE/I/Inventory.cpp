#include "RE/I/Inventory.h"

namespace RE
{
	BSTEventSource<Inventory::Event>* Inventory::GetEventSource()
	{
		using func_t = decltype(&Inventory::GetEventSource);
		static REL::Relocation<func_t> func{ RELOCATION_ID(15980, 16225) };
		return func();
	}
}
