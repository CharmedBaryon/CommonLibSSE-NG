#pragma once

#include "REX/W32/BASE.h"

namespace REX::W32
{
	inline auto HKEY_CLASSES_ROOT{ reinterpret_cast<HKEY>(0x80000000ull) };
	inline auto HKEY_CURRENT_USER{ reinterpret_cast<HKEY>(0x80000001ull) };
	inline auto HKEY_LOCAL_MACHINE{ reinterpret_cast<HKEY>(0x80000002ull) };
}

namespace REX::W32
{
	std::int32_t RegGetValueA(HKEY a_key, const char* a_subKey, const char* a_value, std::uint32_t a_flags, std::uint32_t* a_type, void* a_data, std::uint32_t* a_dataLen);
	std::int32_t RegGetValueW(HKEY a_key, const wchar_t* a_subKey, const wchar_t* a_value, std::uint32_t a_flags, std::uint32_t* a_type, void* a_data, std::uint32_t* a_dataLen);
}
