#pragma once

#include "RE/M/MenuEventHandler.h"

namespace RE
{
	class VrWandTouchpadPositionEvent;

	struct DirectionHandler : public MenuEventHandler
	{
	public:
		inline static constexpr auto RTTI = RTTI_DirectionHandler;
		inline static constexpr auto VTABLE = VTABLE_DirectionHandler;

		~DirectionHandler() override;  // 00

		// override (MenuEventHandler)
		bool CanProcess(InputEvent* a_event) override;  // 01
#ifdef EXCLUSIVE_SKYRIM_VR
		bool ProcessThumbstick(ThumbstickEvent* a_event) override;  // 03 (VR 06)
		bool ProcessButton(ButtonEvent* a_event) override;          // 05 (VR 08)
#endif
#if defined(EXCLUSIVE_SKYRIM_VR)
		bool ProcessVrWandTouchpadPosition([[maybe_unused]] VrWandTouchpadPositionEvent* a_event) override
		{
			return false;
		}  // VR 03
#endif

		// members
		float         nextRepeat;                // 10
		float         menuKeyRepeatLong;         // 14
		float         menuKeyRepeatShort;        // 18
		std::uint32_t repeatTimer;               // 1C
		std::uint32_t currentRepeatCount;        // 20
		std::uint32_t longRepeatThresholdCount;  // 24
		bool          repeatEnabled;             // 28
		bool          unk29;                     // 29
		std::uint8_t  pad2A;                     // 2A
		std::uint16_t pad2B;                     // 2B
	};
	static_assert(sizeof(DirectionHandler) == 0x30);
}
