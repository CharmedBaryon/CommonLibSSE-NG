#pragma once

namespace RE
{
	struct hkpAgent1nSector
	{
	public:
		// members
		std::uint32_t bytesAllocated;  // 000
		std::uint32_t pad04;           // 004
		std::uint32_t pad08;           // 008
		std::uint32_t pad0C;           // 00C
		std::uint8_t  data[0x1F0];     // 010
	};
	static_assert(sizeof(hkpAgent1nSector) == 0x200);
}
