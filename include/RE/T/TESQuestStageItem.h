#pragma once

#include "RE/B/BGSLocalizedStringDL.h"
#include "RE/T/TESCondition.h"

namespace RE
{
	class TESQuest;
	class TESQuestStage;

	struct TESQuestStageItem
	{
	public:
		const char* GetLogEntry(const TESQuest* a_ownerQuest)
		{
			using func_t = decltype(&TESQuestStageItem::GetLogEntry);
			static REL::Relocation<func_t> func{ RELOCATION_ID(24778, 25259) };
			return func(this, a_ownerQuest);
		}

		// members
		TESCondition         objConditions;  // 00
		TESQuest*            nextQuest;      // 08
		BGSLocalizedStringDL logEntry;       // 10
		std::uint8_t         data;           // 14
		std::uint8_t         index;          // 15
		bool                 hasLogEntry;    // 16
		std::uint8_t         pad17;          // 17
		TESQuest*            owner;          // 18
		TESQuestStage*       owningStage;    // 20
	};
	static_assert(sizeof(TESQuestStageItem) == 0x28);
}
