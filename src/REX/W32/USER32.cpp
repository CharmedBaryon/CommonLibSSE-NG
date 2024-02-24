#include "REX/W32/KERNEL32.h"

REX_W32_IMPORT(REX::W32::BOOL, GetClientRect, REX::W32::HWND, REX::W32::RECT*);
REX_W32_IMPORT(std::int32_t, GetKeyNameTextA, std::int32_t, char*, std::int32_t);
REX_W32_IMPORT(std::int32_t, GetKeyNameTextW, std::int32_t, wchar_t*, std::int32_t);
REX_W32_IMPORT(std::int16_t, GetKeyState, std::int32_t);
REX_W32_IMPORT(REX::W32::BOOL, GetWindowRect, REX::W32::HWND, REX::W32::RECT*);
REX_W32_IMPORT(std::int32_t, MessageBoxA, REX::W32::HWND, const char*, const char*, std::uint32_t);
REX_W32_IMPORT(std::int32_t, MessageBoxW, REX::W32::HWND, const wchar_t*, const wchar_t*, std::uint32_t);
REX_W32_IMPORT(std::intptr_t, SetWindowLongPtrA, REX::W32::HWND, std::int32_t, std::intptr_t);
REX_W32_IMPORT(std::int32_t, ShowCursor, REX::W32::BOOL);

namespace REX::W32
{
	bool GetClientRect(HWND a_wnd, RECT* a_rect) noexcept
	{
		return ::W32_IMPL_GetClientRect(a_wnd, a_rect);
	}

	std::int32_t GetKeyNameTextA(std::int32_t a_param, char* a_buf, std::int32_t a_bufLen) noexcept
	{
		return ::W32_IMPL_GetKeyNameTextA(a_param, a_buf, a_bufLen);
	}

	std::int32_t GetKeyNameTextW(std::int32_t a_param, wchar_t* a_buf, std::int32_t a_bufLen) noexcept
	{
		return ::W32_IMPL_GetKeyNameTextW(a_param, a_buf, a_bufLen);
	}

	std::int16_t GetKeyState(std::int32_t a_key) noexcept
	{
		return ::W32_IMPL_GetKeyState(a_key);
	}

	bool GetWindowRect(HWND a_wnd, RECT* a_rect) noexcept
	{
		return ::W32_IMPL_GetWindowRect(a_wnd, a_rect);
	}

	std::int32_t MessageBoxA(HWND a_wnd, const char* a_text, const char* a_caption, std::uint32_t a_type) noexcept
	{
		return ::W32_IMPL_MessageBoxA(a_wnd, a_text, a_caption, a_type);
	}

	std::int32_t MessageBoxW(HWND a_wnd, const wchar_t* a_text, const wchar_t* a_caption, std::uint32_t a_type) noexcept
	{
		return ::W32_IMPL_MessageBoxW(a_wnd, a_text, a_caption, a_type);
	}

	std::intptr_t SetWindowLongPtrA(HWND a_wnd, std::int32_t a_index, std::intptr_t a_newPtr) noexcept
	{
		return ::W32_IMPL_SetWindowLongPtrA(a_wnd, a_index, a_newPtr);
	}

	std::int32_t ShowCursor(bool a_show) noexcept
	{
		return ::W32_IMPL_ShowCursor(a_show);
	}
}
