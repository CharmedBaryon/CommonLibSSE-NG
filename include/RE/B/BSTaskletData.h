#pragma once

namespace RE
{
	class BSTaskletData
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSTaskletData;
		inline static constexpr auto VTABLE = VTABLE_BSTaskletData;

		virtual ~BSTaskletData() = default;  // 00

		// add
		[[nodiscard]] virtual bool Func1() { return true; }  // 01 - { return 1; }
		virtual void               Func2() { return; }       // 02 - { return; }
		virtual void               Func3() { return; }       // 03 - { return; }
	};
	static_assert(sizeof(BSTaskletData) == 0x8);
}
