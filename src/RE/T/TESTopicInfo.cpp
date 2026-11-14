#include "RE/T/TESTopicInfo.h"

#include "RE/T/TESTopic.h"

namespace RE
{
	TESTopicInfo::TESResponse::~TESResponse()
	{
		delete next;
	}

	void TESTopicInfo::TESResponse::LoadResponseText(TESFile* a_file)
	{
		using func_t = decltype(&TESTopicInfo::TESResponse::LoadResponseText);
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

	TESTopicInfo::TESResponseList* TESTopicInfo::GetResponseList(TESResponseList* a_list)
	{
		using func_t = decltype(&TESTopicInfo::GetResponseList);
		static REL::Relocation<func_t> func{ RELOCATION_ID(25083, 25626) };
		return func(this, a_list);
	}
}
