#pragma once

#include "REX/W32/DXGI_3.h"

namespace REX::W32
{
	struct IDXGIAdapter3;
	struct IDXGIFactory4;
	struct IDXGIOutput4;
	struct IDXGISwapChain3;
}

namespace REX::W32
{
	enum DXGI_MEMORY_SEGMENT_GROUP
	{
		DXGI_MEMORY_SEGMENT_GROUP_LOCAL = 0,
		DXGI_MEMORY_SEGMENT_GROUP_NON_LOCAL = 1,
	};

	enum DXGI_OVERLAY_COLOR_SPACE_SUPPORT_FLAG
	{
		DXGI_OVERLAY_COLOR_SPACE_SUPPORT_FLAG_PRESENT = 0x1,
	};

	enum DXGI_SWAP_CHAIN_COLOR_SPACE_SUPPORT_FLAG
	{
		DXGI_SWAP_CHAIN_COLOR_SPACE_SUPPORT_FLAG_PRESENT = 0x1,
		DXGI_SWAP_CHAIN_COLOR_SPACE_SUPPORT_FLAG_OVERLAY_PRESENT = 0x2,
	};
}

namespace REX::W32
{
	struct DXGI_QUERY_VIDEO_MEMORY_INFO
	{
		std::uint64_t budget;
		std::uint64_t currentUsage;
		std::uint64_t availableForReservation;
		std::uint64_t currentReservation;
	};
}

namespace REX::W32
{
	struct __declspec(novtable, uuid("645967A4-1392-4310-A798-8053CE3E93FD"))
		IDXGIAdapter3 : public IDXGIAdapter2
	{
		virtual HRESULT RegisterHardwareContentProtectionTeardownStatusEvent(HANDLE a_event, std::uint32_t* a_cookie) = 0;
		virtual void    UnregisterHardwareContentProtectionTeardownStatus(std::uint32_t a_cookie) = 0;
		virtual HRESULT QueryVideoMemoryInfo(std::uint32_t a_nodeIndex, DXGI_MEMORY_SEGMENT_GROUP a_memorySegmentGroup, DXGI_QUERY_VIDEO_MEMORY_INFO* a_videoMemoryInfo) = 0;
		virtual HRESULT SetVideoMemoryReservation(std::uint32_t a_nodeIndex, DXGI_MEMORY_SEGMENT_GROUP a_memorySegmentGroup, std::uint64_t a_reservation) = 0;
		virtual HRESULT RegisterVideoMemoryBudgetChangeNotificationEvent(HANDLE a_event, std::uint32_t* a_cookie) = 0;
		virtual void    UnregisterVideoMemoryBudgetChangeNotification(std::uint32_t a_cookie) = 0;
	};

	struct __declspec(novtable, uuid("1BC6EA02-EF36-464F-BF0C-21CA39E5168A"))
		IDXGIFactory4 : public IDXGIFactory3
	{
		virtual HRESULT EnumAdapterByLuid(LUID a_luid, const IID& a_iid, void** a_adapter) = 0;
		virtual HRESULT EnumWarpAdapter(const IID& a_iid, void** a_adapter) = 0;
	};

	struct __declspec(novtable, uuid("DC7DCA35-2196-414D-9F53-617884032A60"))
		IDXGIOutput4 : public IDXGIOutput3
	{
		virtual HRESULT CheckOverlayColorSpaceSupport(DXGI_FORMAT a_format, DXGI_COLOR_SPACE_TYPE a_colorSpace, IUnknown* a_concernedDevice, std::uint32_t* a_flags) = 0;
	};

	struct __declspec(novtable, uuid("94D99BDB-F1F8-4AB0-B236-7DA0170EDAB1"))
		IDXGISwapChain3 : public IDXGISwapChain2
	{
		virtual std::uint32_t GetCurrentBackBufferIndex(void) = 0;
		virtual HRESULT       CheckColorSpaceSupport(DXGI_COLOR_SPACE_TYPE a_colorSpace, std::uint32_t* a_colorSpaceSupport) = 0;
		virtual HRESULT       SetColorSpace1(DXGI_COLOR_SPACE_TYPE a_colorSpace) = 0;
		virtual HRESULT       ResizeBuffers1(std::uint32_t a_bufferCount, std::uint32_t a_width, std::uint32_t a_height, DXGI_FORMAT a_format, std::uint32_t a_swapChainFlags, const std::uint32_t* a_creationNodeMask, IUnknown* const* a_presentQueue) = 0;
	};
}

namespace REX::W32
{
	inline constexpr IID IID_IDXGIAdapter3{ 0x645967A4, 0x1392, 0x4310, { 0xA7, 0x98, 0x80, 0x53, 0xCE, 0x3E, 0x93, 0xFD } };
	inline constexpr IID IID_IDXGIFactory4{ 0x1BC6EA02, 0xEF36, 0x464F, { 0xBF, 0x0C, 0x21, 0xCA, 0x39, 0xE5, 0x16, 0x8A } };
	inline constexpr IID IID_IDXGIOutput4{ 0xDC7DCA35, 0x2196, 0x414D, { 0x9F, 0x53, 0x61, 0x78, 0x84, 0x03, 0x2A, 0x60 } };
	inline constexpr IID IID_IDXGISwapChain3{ 0x94D99BDB, 0xF1F8, 0x4AB0, { 0xB2, 0x36, 0x7D, 0xA0, 0x17, 0x0E, 0xDA, 0xB1 } };
}
