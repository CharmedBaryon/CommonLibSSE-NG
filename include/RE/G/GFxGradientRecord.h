#pragma once

#include "RE/G/GColor.h"

namespace RE
{
	class GFxGradientRecord
	{
	public:
		bool operator==(const GFxGradientRecord& a_rhs) const { return ratio == a_rhs.ratio && color == a_rhs.color; }

		// members
		std::uint8_t ratio{ 0 };  // 0
		GColor       color;       // 4
	};
	static_assert(sizeof(GFxGradientRecord) == 0x8);
}
