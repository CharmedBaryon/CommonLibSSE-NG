#include "REX/W32/ADVAPI32.h"

REX_W32_IMPORT(std::int32_t, RegGetValueA, REX::W32::HKEY, const char*, const char*, std::uint32_t, std::uint32_t*, void*, std::uint32_t*);
REX_W32_IMPORT(std::int32_t, RegGetValueW, REX::W32::HKEY, const wchar_t*, const wchar_t*, std::uint32_t, std::uint32_t*, void*, std::uint32_t*);

namespace REX::W32
{
	std::int32_t RegGetValueA(HKEY a_key, const char* a_subKey, const char* a_value, std::uint32_t a_flags, std::uint32_t* a_type, void* a_data, std::uint32_t* a_dataLen)
	{
		return ::W32_IMPL_RegGetValueA(a_key, a_subKey, a_value, a_flags, a_type, a_data, a_dataLen);
	}

	std::int32_t RegGetValueW(HKEY a_key, const wchar_t* a_subKey, const wchar_t* a_value, std::uint32_t a_flags, std::uint32_t* a_type, void* a_data, std::uint32_t* a_dataLen)
	{
		return ::W32_IMPL_RegGetValueW(a_key, a_subKey, a_value, a_flags, a_type, a_data, a_dataLen);
	}
}
