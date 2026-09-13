#include "RE/I/ItemsPickpocketed.h"

namespace RE
{
	BSTEventSource<ItemsPickpocketed::Event>* ItemsPickpocketed::GetEventSource()
	{
		using func_t = decltype(&ItemsPickpocketed::GetEventSource);
		static REL::Relocation<func_t> func{ RELOCATION_ID(50258, 51183) };
		return func();
	}

	void ItemsPickpocketed::SendEvent(std::int32_t a_numItems)
	{
		Event e = { a_numItems, 0 };
		auto  source = GetEventSource();
		if (source) {
			source->SendEvent(std::addressof(e));
		}
	}
}
