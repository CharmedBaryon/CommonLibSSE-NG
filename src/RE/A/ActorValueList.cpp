#include "RE/A/ActorValueList.h"

namespace RE
{
	ActorValueInfo* ActorValueList::GetActorValueInfo(ActorValue a_actorValue)
	{
		using func_t = decltype(&ActorValueList::GetActorValueInfo);
		static REL::Relocation<func_t> func{ RELOCATION_ID(26569, 27202) };
		return func(a_actorValue);
	}

	ActorValue ActorValueList::LookupActorValueByName(const char* a_enumName)
	{
		using func_t = decltype(&ActorValueList::LookupActorValueByName);
		static REL::Relocation<func_t> func{ RELOCATION_ID(26570, 27203) };
		return func(a_enumName);
	}

	const char* ActorValueList::GetActorValueName(ActorValue a_actorValue)
	{
		using func_t = decltype(&ActorValueList::GetActorValueName);
		static REL::Relocation<func_t> func{ RELOCATION_ID(26561, 27192) };
		return func(a_actorValue);
	}

	std::string_view ActorValueToString(ActorValue a_actorValue) noexcept
	{
		auto name = ActorValueList::GetActorValueName(a_actorValue);
		return name ? name : "None"sv;
	}
}
