#pragma once

namespace RE
{
	struct TESFastTravelEndEvent
	{
	public:
		// members
		float         fastTravelEndHours;  // 00
		std::uint32_t pad04;               // 04
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(TESFastTravelEndEvent) == 0x08);
}
