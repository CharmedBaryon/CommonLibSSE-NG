#pragma once

namespace RE
{
	class IPathBuilderTracker
	{
	public:
		inline static constexpr auto RTTI = RTTI_IPathBuilderTracker;
		inline static constexpr auto VTABLE = VTABLE_IPathBuilderTracker;

		virtual ~IPathBuilderTracker();  // 00

		virtual void Unk_01(void) = 0;  // 01
		virtual void Unk_02(void) = 0;  // 02
	};
	STATIC_ASSERT_SIZE(IPathBuilderTracker, 0x8);
}
