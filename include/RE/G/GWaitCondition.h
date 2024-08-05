#pragma once

namespace RE
{
	class GWaitConditionImpl;

	class GWaitCondition
	{
	public:
		GWaitConditionImpl* impl;  // 00
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(GWaitCondition) == 0x8);
}
