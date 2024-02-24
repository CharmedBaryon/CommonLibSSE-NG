#pragma once

namespace REX::W32
{
	bool          GetFileVersionInfoA(const char* a_name, std::uint32_t a_handle, std::uint32_t a_dataLen, void* a_data) noexcept;
	std::uint32_t GetFileVersionInfoSizeA(const char* a_name, std::uint32_t* a_handle) noexcept;
	//std::uint32_t GetFileVersionInfoSizeExA(std::uint32_t a_flags, const char* a_name, std::uint32_t* a_handle) noexcept;
	std::uint32_t GetFileVersionInfoSizeExW(std::uint32_t a_flags, const wchar_t* a_name, std::uint32_t* a_handle) noexcept;
	std::uint32_t GetFileVersionInfoSizeW(const wchar_t* a_name, std::uint32_t* a_handle) noexcept;
	bool          GetFileVersionInfoW(const wchar_t* a_name, std::uint32_t a_handle, std::uint32_t a_dataLen, void* a_data) noexcept;
	bool          VerQueryValueA(const void* a_block, const char* a_subBlock, void** a_buf, std::uint32_t* a_bufLen) noexcept;
	bool          VerQueryValueW(const void* a_block, const wchar_t* a_subBlock, void** a_buf, std::uint32_t* a_bufLen) noexcept;
}
