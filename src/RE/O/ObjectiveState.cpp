#include "RE/O/ObjectiveState.h"

namespace RE
{
	BSTEventSource<ObjectiveState::Event>* ObjectiveState::GetEventSource()
	{
		using func_t = decltype(&ObjectiveState::GetEventSource);
		static REL::Relocation<func_t> func{ RELOCATION_ID(23486, 23951) };
		return func();
	}
}
