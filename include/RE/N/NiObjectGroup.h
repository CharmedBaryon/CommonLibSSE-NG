#pragma once

namespace RE
{
	class NiObjectGroup
	{
	public:
		// members
		std::uint32_t size;   // 00
		std::uint32_t pad04;  // 04
		std::uint64_t unk08;  // 08
		std::uint64_t unk10;  // 10
		std::uint32_t unk18;  // 18
		std::uint32_t pad1C;  // 1C
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(NiObjectGroup) == 0x20);
}
