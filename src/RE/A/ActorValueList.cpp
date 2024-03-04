#include "RE/A/ActorValueList.h"

#include "RE/A/ActorValueInfo.h"

namespace RE
{
	ActorValueInfo* ActorValueList::GetActorValue(ActorValue a_actorValue) const
	{
		return a_actorValue < ActorValue::kTotal ?
		           actorValues[std::to_underlying(a_actorValue)] :
		           nullptr;
	}

	ActorValue ActorValueList::LookupActorValueByName(std::string_view a_enumName) const
	{
		for (std::size_t i = 0; i < std::to_underlying(ActorValue::kTotal); ++i) {
			if (a_enumName.size() == strlen(actorValues[i]->enumName) &&
				_strnicmp(actorValues[i]->enumName, a_enumName.data(), a_enumName.size()) == 0) {
				return static_cast<ActorValue>(i);
			}
		}
		return ActorValue::kNone;
	}
}
