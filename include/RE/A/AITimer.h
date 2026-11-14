#pragma once

namespace RE
{
	struct AITimer
	{
		static float QTimer();

		//members
		float aiTimer;  // 00
		float timer;    // 04
	};
	static_assert(sizeof(AITimer) == 0x08);
}
