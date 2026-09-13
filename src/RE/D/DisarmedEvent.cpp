#include "RE/D/DisarmedEvent.h"

namespace RE
{
	BSTEventSource<DisarmedEvent::Event>* DisarmedEvent::GetEventSource()
	{
		using func_t = decltype(&DisarmedEvent::GetEventSource);
		static REL::Relocation<func_t> func{ RELOCATION_ID(37392, 38340) };
		return func();
	}
}
