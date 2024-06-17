#pragma once

#include "RE/V/VRWandEvent.h"

namespace RE
{
	class VrWandTouchpadPositionEvent : public VRWandEvent
	{
	public:
		std::uint64_t unk30;  // 30
		std::uint64_t unk38;  // 38
		std::uint64_t unk40;  // 40
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(VrWandTouchpadPositionEvent) == 0x48);
}
