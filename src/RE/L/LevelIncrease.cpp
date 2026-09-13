#include "RE/L/LevelIncrease.h"

namespace RE
{
	BSTEventSource<LevelIncrease::Event>* LevelIncrease::GetEventSource()
	{
		using func_t = decltype(&LevelIncrease::GetEventSource);
		static REL::Relocation<func_t> func{ RELOCATION_ID(39247, 40319) };
		return func();
	}
}
