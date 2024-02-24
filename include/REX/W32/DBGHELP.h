#pragma once

namespace REX::W32
{
	// symbol name undecoration flags
	inline constexpr auto UNDNAME_NO_MS_KEYWORDS{ 0x00000002u };
	inline constexpr auto UNDNAME_NO_FUNCTION_RETURNS{ 0x00000004u };
	inline constexpr auto UNDNAME_NO_ALLOCATION_MODEL{ 0x00000008u };
	inline constexpr auto UNDNAME_NO_ALLOCATION_LANGUAGE{ 0x00000010u };
	inline constexpr auto UNDNAME_NO_THISTYPE{ 0x00000060u };
	inline constexpr auto UNDNAME_NO_ACCESS_SPECIFIERS{ 0x00000080u };
	inline constexpr auto UNDNAME_NO_THROW_SIGNATURES{ 0x00000100u };
	inline constexpr auto UNDNAME_NO_RETURN_UDT_MODEL{ 0x00000400u };
	inline constexpr auto UNDNAME_NAME_ONLY{ 0x00001000u };
	inline constexpr auto UNDNAME_NO_ARGUMENTS{ 0x00002000u };
}

namespace REX::W32
{
	std::uint32_t UnDecorateSymbolName(const char* a_name, char* a_buf, std::uint32_t a_bufLen, std::uint32_t a_flags) noexcept;
	std::uint32_t UnDecorateSymbolNameW(const wchar_t* a_name, wchar_t* a_buf, std::uint32_t a_bufLen, std::uint32_t a_flags) noexcept;
}
