#pragma once

namespace RE
{
	struct TESSleepStopEvent
	{
	public:
		// members
		bool interrupted;  // 0
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(TESSleepStopEvent) == 0x1);
}
