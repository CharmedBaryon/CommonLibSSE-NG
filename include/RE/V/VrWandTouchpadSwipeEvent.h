#pragma once

#include "RE/V/VRWandEvent.h"

namespace RE
{
	class VrWandTouchpadSwipeEvent : public VRWandEvent
	{
	public:
		std::uint64_t unk30;  // 30
		std::uint64_t unk38;  // 38
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(VrWandTouchpadSwipeEvent) == 0x40);
}
