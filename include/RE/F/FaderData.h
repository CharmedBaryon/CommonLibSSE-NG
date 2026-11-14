#pragma once

#include "RE/I/IUIMessageData.h"
#include "REL/Common.h"

namespace RE
{
	class FaderData : public IUIMessageData
	{
	public:
		inline static constexpr auto             RTTI = RTTI_FaderData;
		inline static constexpr auto             VTABLE = VTABLE_FaderData;
		inline static constexpr std::string_view CLASS_NAME = "FaderData";

		~FaderData() override;  // 00

		// members
		std::uint64_t unk10;         // 10
		std::uint8_t  unk18;         // 18
		std::uint8_t  pad19;         // 19
		std::uint16_t pad1A;         // 1A
		float         minDuration;   // 1C
		float         fadeDuration;  // 20
		bool          isFadingOut;   // 24
		bool          isBlack;       // 25 - otherwise white
		bool          unk26;         // 26
		bool          pausesGame;    // 27
#if defined(EXCLUSIVE_SKYRIM_VR)
		bool         unkVr28;     // 28 - the VR constructor writes 0
		std::uint8_t padVr29[7];  // 29
#endif
	};
	STATIC_ASSERT_SIZE(FaderData, 0x28, 0x30);
}
