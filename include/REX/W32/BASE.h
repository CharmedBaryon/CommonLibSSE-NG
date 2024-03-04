#pragma once

#ifdef _INC_WINAPIFAMILY
#	error Windows API detected. Please move any Windows API includes after CommonLib, or remove them.
#endif

#define REX_W32_IMPORT(a_ret, a_name, ...)                                            \
	extern "C" __declspec(dllimport) a_ret __stdcall W32_IMPL_##a_name(...) noexcept; \
	__pragma(comment(linker, "/alternatename:__imp_W32_IMPL_" #a_name "=__imp_" #a_name))

namespace REX::W32
{
	using BOOL = std::int32_t;
	using HANDLE = void*;
	using HBITMAP = struct HBITMAP__*;
	using HBRUSH = struct HBRUSH__*;
	using HCURSOR = struct HCURSOR__*;
	using HDC = struct HDC__*;
	using HFONT = struct HFONT__*;
	using HICON = struct HICON__*;
	using HINSTANCE = struct HINSTANCE__*;
	using HKEY = struct HKEY__*;
	using HMENU = struct HMENU__*;
	using HMODULE = HINSTANCE;
	using HMONITOR = struct HMONITOR__*;
	using HPALETTE = struct HPALETTE__*;
	using HPEN = struct HPEN__*;
	using HRESULT = std::int32_t;
	using HSTRING = struct HSTRING__*;
	using HWND = struct HWND__*;

	// general constants
	inline const auto     INVALID_HANDLE_VALUE{ reinterpret_cast<HANDLE>(static_cast<std::intptr_t>(-1)) };
	inline constexpr auto MAX_PATH{ 260u };
}

namespace REX::W32
{
	struct FILETIME
	{
		constexpr FILETIME() noexcept = default;

		constexpr FILETIME(std::uint64_t a_value) noexcept
		{
			*this = std::bit_cast<FILETIME>(a_value);
		}

		constexpr operator std::uint64_t() const noexcept
		{
			return std::bit_cast<std::uint64_t>(*this);
		}

		std::uint32_t lo;  // 00
		std::uint32_t hi;  // 04
	};
	static_assert(sizeof(FILETIME) == 0x8);
}

namespace REX::W32
{
	struct GUID
	{
		constexpr GUID() noexcept = default;

		constexpr GUID(const std::uint32_t a_data1, std::uint16_t const a_data2, const std::uint16_t a_data3, const std::array<std::uint8_t, 8>& a_data4) noexcept :
			data1(a_data1), data2(a_data2), data3(a_data3), data4{ a_data4[0], a_data4[1], a_data4[2], a_data4[3], a_data4[4], a_data4[5], a_data4[6], a_data4[7] }
		{}

		friend bool operator==(const GUID& a_lhs, const GUID& a_rhs) noexcept
		{
			return std::memcmp(&a_lhs, &a_rhs, sizeof(a_lhs)) == 0;
		}

		friend bool operator!=(const GUID& a_lhs, const GUID& a_rhs) noexcept
		{
			return !(a_lhs == a_rhs);
		}

		std::uint32_t data1;     // 00
		std::uint16_t data2;     // 04
		std::uint16_t data3;     // 08
		std::uint8_t  data4[8];  // 10
	};
	static_assert(sizeof(GUID) == 0x10);

	using UUID = GUID;
	using IID = GUID;
}

namespace REX::W32
{
	struct POINT
	{
		constexpr POINT() noexcept = default;

		constexpr POINT(std::int32_t a_x, std::int32_t a_y) noexcept :
			x(a_x), y(a_y)
		{}

		std::int32_t x;  // 00
		std::int32_t y;  // 04
	};
	static_assert(sizeof(POINT) == 0x8);
}

namespace REX::W32
{
	struct RECT
	{
		constexpr RECT() noexcept = default;

		constexpr RECT(const std::int32_t a_x1, const std::int32_t a_y1, const std::int32_t a_x2, const std::int32_t a_y2) noexcept :
			x1(a_x1), y1(a_y1), x2(a_x2), y2(a_y2)
		{}

		std::int32_t x1;  // 00
		std::int32_t y1;  // 04
		std::int32_t x2;  // 08
		std::int32_t y2;  // 10
	};
	static_assert(sizeof(RECT) == 0x10);
}

namespace REX::W32
{
	struct SIZE
	{
		std::int32_t x;  // 00
		std::int32_t y;  // 04
	};
	static_assert(sizeof(SIZE) == 0x8);
}

namespace REX::W32
{
	struct CRITICAL_SECTION
	{
		void*          debugInfo;       // 00
		std::int32_t   lockCount;       // 08
		std::int32_t   recursionCount;  // 0C
		HANDLE         owningThread;    // 10
		HANDLE         lockSemaphore;   // 18
		std::uintptr_t spinCount;       // 20
	};
	static_assert(sizeof(CRITICAL_SECTION) == 0x28);

	struct SECURITY_ATTRIBUTES
	{
		std::uint32_t length;              // 00
		void*         securityDescriptor;  // 04
		BOOL          inheritHandle;       // 0C
	};
	static_assert(sizeof(SECURITY_ATTRIBUTES) == 0x18);

	union ULARGE_INTEGER
	{
		struct
		{
			std::uint32_t lo;
			std::uint32_t hi;
		};
		std::uint64_t value;
	};
}
