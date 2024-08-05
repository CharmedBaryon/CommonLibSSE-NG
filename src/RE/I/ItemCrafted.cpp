#include "RE/I/ItemCrafted.h"

namespace RE
{
	BSTEventSource<ItemCrafted::Event>* ItemCrafted::GetEventSource()
	{
		using func_t = decltype(&ItemCrafted::GetEventSource);
		static REL::Relocation<func_t> func{ RELOCATION_ID(50515, 51403) };
		return func();
	}
}
