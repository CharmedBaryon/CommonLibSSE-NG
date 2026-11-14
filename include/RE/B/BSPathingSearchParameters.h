#pragma once

namespace RE
{
	class BSPathingSearchParameters
	{
	public:
		float         preferredCostFactor;     // 00
		float         tangentSmoothingFactor;  // 04
		std::uint16_t retryCount;              // 08
		std::uint16_t flags;                   // 0A
	};
	static_assert(sizeof(BSPathingSearchParameters) == 0xC);
}
