#include "RE/T/TESTopicInfo.h"

#include "RE/T/TESTopic.h"

namespace RE
{
	TESTopicInfo::ResponseData::~ResponseData()
	{
		delete next;
	}

	void TESTopicInfo::ResponseData::PopulateResponseText(TESFile* a_file)
	{
		using func_t = decltype(&TESTopicInfo::ResponseData::PopulateResponseText);
		static REL::Relocation<func_t> func{ RELOCATION_ID(24985, 25491) };
		return func(this, a_file);
	}

	float TOPIC_INFO_DATA::GetResetHours() const
	{
		return static_cast<float>(timeUntilReset);
	}

	DialogueItem TESTopicInfo::GetDialogueData(TESObjectREFR* a_speaker)
	{
		return { parentTopic->ownerQuest, parentTopic, this, a_speaker };
	}
}
