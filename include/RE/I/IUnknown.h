#pragma once

namespace RE
{
	struct __declspec(novtable) IUnknown
	{
	public:
		inline static constexpr auto RTTI = RTTI_IUnknown;

		// add
		virtual std::int32_t  QueryInterface(REX::W32::REFIID a_riid, void** a_interface) = 0;  // 00
		virtual std::uint32_t AddRef() = 0;                                                     // 01
		virtual std::uint32_t Release() = 0;                                                    // 02
	};
}
