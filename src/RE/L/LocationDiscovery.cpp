#include "RE/L/LocationDiscovery.h"

namespace RE
{
	BSTEventSource<LocationDiscovery::Event>* LocationDiscovery::GetEventSource()
	{
		using func_t = decltype(&LocationDiscovery::GetEventSource);
		static REL::Relocation<func_t> func{ RELOCATION_ID(40056, 41067) };
		return func();
	}
}
