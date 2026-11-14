#pragma once

#include "RE/B/BSFixedString.h"
#include "RE/I/IUIMessageData.h"

namespace RE
{
	class KinectUserEventData : public IUIMessageData
	{
	public:
		inline static constexpr auto             RTTI = RTTI_KinectUserEventData;
		inline static constexpr auto             VTABLE = VTABLE_KinectUserEventData;
		inline static constexpr std::string_view CLASS_NAME = "KinectUserEventData";

		// override (IUIMessageData)
		~KinectUserEventData() override;  // 00

		// members
		BSFixedString unk10;  // 10
		BSFixedString unk18;  // 18
	};
	static_assert(sizeof(KinectUserEventData) == 0x20);
}
