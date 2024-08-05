#pragma once

namespace RE
{
	struct TESWaitStopEvent
	{
	public:
		// members
		bool interrupted;  // 0
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(TESWaitStopEvent) == 0x1);
}
