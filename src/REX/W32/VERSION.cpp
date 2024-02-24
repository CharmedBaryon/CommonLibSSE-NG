#include "REX/W32/VERSION.h"

REX_W32_IMPORT(REX::W32::BOOL, GetFileVersionInfoA, const char*, std::uint32_t, std::uint32_t, void*);
REX_W32_IMPORT(REX::W32::BOOL, GetFileVersionInfoW, const wchar_t*, std::uint32_t, std::uint32_t, void*);
REX_W32_IMPORT(std::uint32_t, GetFileVersionInfoSizeA, const char*, std::uint32_t*);
//REX_W32_IMPORT(std::uint32_t, GetFileVersionInfoSizeExA, std::uint32_t, const char*, std::uint32_t*);
REX_W32_IMPORT(std::uint32_t, GetFileVersionInfoSizeExW, std::uint32_t, const wchar_t*, std::uint32_t*);
REX_W32_IMPORT(std::uint32_t, GetFileVersionInfoSizeW, const wchar_t*, std::uint32_t*);
REX_W32_IMPORT(REX::W32::BOOL, VerQueryValueA, const void*, const char*, void**, std::uint32_t*);
REX_W32_IMPORT(REX::W32::BOOL, VerQueryValueW, const void*, const wchar_t*, void**, std::uint32_t*);

namespace REX::W32
{
	bool GetFileVersionInfoA(const char* a_name, std::uint32_t a_handle, std::uint32_t a_dataLen, void* a_data) noexcept
	{
		return ::W32_IMPL_GetFileVersionInfoA(a_name, a_handle, a_dataLen, a_data);
	}

	std::uint32_t GetFileVersionInfoSizeA(const char* a_name, std::uint32_t* a_handle) noexcept
	{
		return ::W32_IMPL_GetFileVersionInfoSizeA(a_name, a_handle);
	}

	//std::uint32_t GetFileVersionInfoSizeExA(std::uint32_t a_flags, const char* a_name, std::uint32_t* a_handle) noexcept
	//{
	//    return ::W32_IMPL_GetFileVersionInfoSizeExA(a_flags, a_name, a_handle);
	//}

	std::uint32_t GetFileVersionInfoSizeExW(std::uint32_t a_flags, const wchar_t* a_name, std::uint32_t* a_handle) noexcept
	{
		return ::W32_IMPL_GetFileVersionInfoSizeExW(a_flags, a_name, a_handle);
	}

	std::uint32_t GetFileVersionInfoSizeW(const wchar_t* a_name, std::uint32_t* a_handle) noexcept
	{
		return ::W32_IMPL_GetFileVersionInfoSizeW(a_name, a_handle);
	}

	bool GetFileVersionInfoW(const wchar_t* a_name, std::uint32_t a_handle, std::uint32_t a_dataLen, void* a_data) noexcept
	{
		return ::W32_IMPL_GetFileVersionInfoW(a_name, a_handle, a_dataLen, a_data);
	}

	bool VerQueryValueA(const void* a_block, const char* a_subBlock, void** a_buf, std::uint32_t* a_bufLen) noexcept
	{
		return ::W32_IMPL_VerQueryValueA(a_block, a_subBlock, a_buf, a_bufLen);
	}

	bool VerQueryValueW(const void* a_block, const wchar_t* a_subBlock, void** a_buf, std::uint32_t* a_bufLen) noexcept
	{
		return ::W32_IMPL_VerQueryValueW(a_block, a_subBlock, a_buf, a_bufLen);
	}
}
