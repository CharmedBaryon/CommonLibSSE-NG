#include "REX/W32/DBGHELP.h"

REX_W32_IMPORT(std::uint32_t, UnDecorateSymbolName, const char*, char*, std::uint32_t, std::uint32_t);
REX_W32_IMPORT(std::uint32_t, UnDecorateSymbolNameW, const wchar_t*, wchar_t*, std::uint32_t, std::uint32_t);

namespace REX::W32
{
	std::uint32_t UnDecorateSymbolName(const char* a_name, char* a_buf, std::uint32_t a_bufLen, std::uint32_t a_flags) noexcept
	{
		return ::W32_IMPL_UnDecorateSymbolName(a_name, a_buf, a_bufLen, a_flags);
	}

	std::uint32_t UnDecorateSymbolNameW(const wchar_t* a_name, wchar_t* a_buf, std::uint32_t a_bufLen, std::uint32_t a_flags) noexcept
	{
		return ::W32_IMPL_UnDecorateSymbolNameW(a_name, a_buf, a_bufLen, a_flags);
	}
}
