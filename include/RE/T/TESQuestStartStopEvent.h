#pragma once

namespace RE
{
	struct TESQuestStartStopEvent
	{
	public:
		// members
		FormID        formID;   // 00
		bool          started;  // 04
		bool          failed;   // 05
		std::uint16_t pad06;    // 06
	};
	static_assert(sizeof(TESQuestStartStopEvent) == 0x8);
}
