#pragma once

#include "REX/W32/BASE.h"

namespace REX::W32
{
	struct __declspec(novtable, uuid("00000000-0000-0000-c000-000000000046"))
		IUnknown
	{
		virtual HRESULT       QueryInterface(const IID& a_iid, void** a_object) = 0;
		virtual std::uint32_t AddRef() = 0;
		virtual std::uint32_t Release() = 0;

		template <class T>
		HRESULT QueryInterface(T** a_object)
		{
			return QueryInterface(*reinterpret_cast<const IID*>(&__uuidof(T)), static_cast<void**>(a_object));
		}
	};
}

namespace REX::W32
{
	inline constexpr IID IID_IUnknown{ 0x00000000, 0x0000, 0x0000, { 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46 } };
}
