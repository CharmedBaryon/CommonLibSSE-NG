#pragma once

namespace RE
{
	class BSPathingActorAttributes
	{
	public:
		float                              radius;    // 00
		float                              height;    // 04
		BSTSmartPointer<BSPathingLockData> lockData;  // 08
		std::uint32_t                      data;      // 10
	};
	static_assert(sizeof(BSPathingActorAttributes) == 0x18);
}
