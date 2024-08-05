#pragma once

#include "RE/B/BSTSmartPointer.h"
#include "RE/N/NiSmartPointer.h"

namespace RE
{
	class TESObjectREFR;

	namespace REFREventCallbacks
	{
		class IEventCallback;
	}

	struct TESTopicInfoEvent
	{
	public:
		enum class TopicInfoEventType
		{
			kTopicBegin = 0,
			kTopicEnd
		};

		// members
		BSTSmartPointer<REFREventCallbacks::IEventCallback> callback;         // 00
		NiPointer<TESObjectREFR>                            speakerRef;       // 08
		FormID                                              topicInfoFormID;  // 10
		stl::enumeration<TopicInfoEventType, std::uint32_t> type;             // 14
		std::uint16_t                                       stage;            // 18
	};
	static_assert(sizeof(TESTopicInfoEvent) == 0x20);
}
