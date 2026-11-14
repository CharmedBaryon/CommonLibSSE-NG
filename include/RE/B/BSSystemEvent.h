#pragma once

namespace RE
{
	class BSSystemEvent
	{
	public:
		std::uint64_t unk00;
		std::uint64_t unk08;
		std::uint32_t unk10;
	};
	static_assert(sizeof(BSSystemEvent) == 0x18);
}
