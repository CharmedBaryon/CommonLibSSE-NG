#pragma once

#include "RE/B/BSExtraData.h"
#include "RE/B/BSSoundHandle.h"
#include "RE/E/ExtraDataTypes.h"

namespace RE
{
	class BGSDialogueBranch;
	class DialogueItem;
	class TESTopic;

	class ExtraSayToTopicInfo : public BSExtraData
	{
	public:
		inline static constexpr auto RTTI = RTTI_ExtraSayToTopicInfo;
		inline static constexpr auto VTABLE = VTABLE_ExtraSayToTopicInfo;
		inline static constexpr auto EXTRADATATYPE = ExtraDataType::kSayTopicInfo;

		~ExtraSayToTopicInfo() override;  // 00

		// override (BSExtraData)
		ExtraDataType GetType() const override;  // 01 - { return kSayTopicInfo; }

		// members
		TESTopic*          topic;                // 10
		bool               voicePaused;          // 18
		std::uint8_t       pad19;                // 19
		std::uint16_t      pad1A;                // 1A
		float              subtitleSpeechDelay;  // 1C
		BGSDialogueBranch* exclusiveBranch;      // 20
		BSSoundHandle      sound;                // 28
		std::uint32_t      pad34;                // 34
		DialogueItem*      item;                 // 38
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(ExtraSayToTopicInfo) == 0x40);
}
