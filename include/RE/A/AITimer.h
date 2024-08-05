#pragma once

namespace RE
{
	struct AITimer
	{
		//members
		float aiTimer;  // 00
		float timer;    // 04
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(AITimer) == 0x08);
}
