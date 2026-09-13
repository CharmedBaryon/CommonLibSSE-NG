#pragma once

namespace RE
{
	class BSTasklet
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSTasklet;
		inline static constexpr auto VTABLE = VTABLE_BSTasklet;

		virtual ~BSTasklet() = default;  // 00
	};
	static_assert(sizeof(BSTasklet) == 0x8);
}
