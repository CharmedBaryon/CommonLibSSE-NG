#include "RE/S/SkillIncrease.h"

namespace RE
{
	BSTEventSource<SkillIncrease::Event>* SkillIncrease::GetEventSource()
	{
		using func_t = decltype(&SkillIncrease::GetEventSource);
		static REL::Relocation<func_t> func{ RELOCATION_ID(39248, 40320) };
		return func();
	}
}
