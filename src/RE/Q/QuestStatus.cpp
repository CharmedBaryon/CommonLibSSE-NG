#include "RE/Q/QuestStatus.h"

namespace RE
{
	BSTEventSource<QuestStatus::Event>* QuestStatus::GetEventSource()
	{
		using func_t = decltype(&QuestStatus::GetEventSource);
		static REL::Relocation<func_t> func{ RELOCATION_ID(24719, 25196) };
		return func();
	}
}
