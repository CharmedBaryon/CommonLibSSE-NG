#include "RE/S/ShoutAttack.h"

namespace RE
{
	BSTEventSource<ShoutAttack::Event>* ShoutAttack::GetEventSource()
	{
		using func_t = decltype(&ShoutAttack::GetEventSource);
		static REL::Relocation<func_t> func{ RELOCATION_ID(40060, 41071) };
		return func();
	}
}
