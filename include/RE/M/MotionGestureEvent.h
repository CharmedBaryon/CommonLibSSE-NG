#pragma once

#include "RE/I/IDEvent.h"

namespace RE
{
#ifdef ENABLE_SKYRIM_AE
	class MotionGestureEvent : public IDEvent
	{
	public:
		inline static constexpr auto RTTI = RTTI_MotionGestureEvent;
		inline static constexpr auto VTABLE = VTABLE_MotionGestureEvent;

		~MotionGestureEvent() override;  // 00

		// members
		std::int32_t  unk28;  // 28
		std::int32_t  unk2C;  // 2C
		bool          unk30;  // 30
		std::uint8_t  pad31;  // 31
		std::uint16_t pad32;  // 32
		std::int32_t  unk34;  // 34
	};
	static_assert(sizeof(MotionGestureEvent) == 0x38);
#endif
}
