#include "RE/S/SoulsTrapped.h"

namespace RE
{
	BSTEventSource<SoulsTrapped::Event>* SoulsTrapped::GetEventSource()
	{
		using func_t = decltype(&SoulsTrapped::GetEventSource);
		static REL::Relocation<func_t> func{ RELOCATION_ID(37916, 38873) };
		return func();
	}

	void SoulsTrapped::SendEvent(Actor* a_trapper, Actor* a_target)
	{
		Event e{ a_trapper, a_target };
		auto  source = GetEventSource();
		if (source) {
			source->SendEvent(std::addressof(e));
		}
	}
}
