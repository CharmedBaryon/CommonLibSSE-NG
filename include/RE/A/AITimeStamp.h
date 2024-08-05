#pragma once

namespace RE
{
	struct AITimeStamp
	{
	public:
		// members
		float timeStamp;  // 0
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(AITimeStamp) == 0x4);
}
