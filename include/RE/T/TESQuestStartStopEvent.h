#pragma once

namespace RE
{
	struct TESQuestStartStopEvent
	{
	public:
		// members
		FormID        formID;   // 00
		bool          started;  // 04
		std::uint8_t  unk05;    // 05
		std::uint16_t pad06;    // 06
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(TESQuestStartStopEvent) == 0x8);
}
