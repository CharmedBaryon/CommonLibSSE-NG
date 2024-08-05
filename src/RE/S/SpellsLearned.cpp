#include "RE/S/SpellsLearned.h"

namespace RE
{
	BSTEventSource<SpellsLearned::Event>* SpellsLearned::GetEventSource()
	{
		using func_t = decltype(&SpellsLearned::GetEventSource);
		static REL::Relocation<func_t> func{ RELOCATION_ID(37917, 38874) };
		return func();
	}

	void SpellsLearned::SendEvent(SpellItem* a_spell)
	{
		Event e{ a_spell };
		auto  source = GetEventSource();
		if (source) {
			source->SendEvent(std::addressof(e));
		}
	}
}
