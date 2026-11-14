#pragma once

#include "RE/B/BSFixedString.h"
#include "RE/I/IUIMessageData.h"

namespace RE
{
	class KinectStateChangeData : public IUIMessageData
	{
	public:
		inline static constexpr auto             RTTI = RTTI_KinectStateChangeData;
		inline static constexpr auto             VTABLE = VTABLE_KinectStateChangeData;
		inline static constexpr std::string_view CLASS_NAME = "KinectStateChangeData";

		// override (IUIMessageData)
		~KinectStateChangeData() override;  // 00

		// members
		std::uint64_t unk10;  // 10
		BSFixedString unk18;  // 18
	};
	static_assert(sizeof(KinectStateChangeData) == 0x20);
}
