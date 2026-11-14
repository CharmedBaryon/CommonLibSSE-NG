#include "RE/C/ChestsLooted.h"

namespace RE
{
	BSTEventSource<ChestsLooted::Event>* ChestsLooted::GetEventSource()
	{
		using func_t = decltype(&ChestsLooted::GetEventSource);
		static REL::Relocation<func_t> func{ RELOCATION_ID(50257, 51182) };
		return func();
	}

	void ChestsLooted::SendEvent()
	{
		const Event e{};
		auto        source = GetEventSource();
		if (source) {
			source->SendEvent(&e);
		}
	}
}
