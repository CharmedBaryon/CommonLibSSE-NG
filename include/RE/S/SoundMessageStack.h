#pragma once

namespace RE
{
	class BSSoundMessage;

	class SoundMessageStack
	{
	public:
		// members
		std::uint32_t   size;            // 00
		bool            bottomless;      // 04
		std::byte       pad05[3];        // 05
		BSSoundMessage* top;             // 08
		std::uint32_t   lastUpdateTime;  // 10
		std::byte       pad14[4];        // 14
	};
	static_assert(sizeof(SoundMessageStack) == 0x18);
}
