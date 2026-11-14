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
		virtual bool OnStartup() { return true; };  // 01
		virtual void Process(){};                   // 02
		virtual void OnComplete(){};                // 03

		// members
		bool         yielding;  // 08
		std::uint8_t pad09[7];  // 09
	};
	static_assert(sizeof(BSTaskletData) == 0x10);
}
