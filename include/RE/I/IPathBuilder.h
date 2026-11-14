#pragma once

namespace RE
{
	class IPathBuilder
	{
	public:
		inline static constexpr auto RTTI = RTTI_IPathBuilder;
		inline static constexpr auto VTABLE = VTABLE_IPathBuilder;

		virtual ~IPathBuilder();  // 00

		virtual void Build() = 0;  // 01
	};
	STATIC_ASSERT_SIZE(IPathBuilder, 0x8);
}
