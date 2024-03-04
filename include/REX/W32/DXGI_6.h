#pragma once

#include "REX/W32/DXGI_5.h"

namespace REX::W32
{
	struct IDXGIAdapter4;
	struct IDXGIFactory6;
	struct IDXGIFactory7;
	struct IDXGIOutput6;
}

namespace REX::W32
{
	enum DXGI_ADAPTER_FLAG3
	{
		DXGI_ADAPTER_FLAG3_NONE = 0,
		DXGI_ADAPTER_FLAG3_REMOTE = 1,
		DXGI_ADAPTER_FLAG3_SOFTWARE = 2,
		DXGI_ADAPTER_FLAG3_ACG_COMPATIBLE = 4,
		DXGI_ADAPTER_FLAG3_SUPPORT_MONITORED_FENCES = 8,
		DXGI_ADAPTER_FLAG3_SUPPORT_NON_MONITORED_FENCES = 0x10,
		DXGI_ADAPTER_FLAG3_KEYED_MUTEX_CONFORMANCE = 0x20,
		DXGI_ADAPTER_FLAG3_FORCE_DWORD = 0xFFFFFFFF,
	};

	enum DXGI_GPU_PREFERENCE
	{
		DXGI_GPU_PREFERENCE_UNSPECIFIED = 0,
		DXGI_GPU_PREFERENCE_MINIMUM_POWER = (DXGI_GPU_PREFERENCE_UNSPECIFIED + 1),
		DXGI_GPU_PREFERENCE_HIGH_PERFORMANCE = (DXGI_GPU_PREFERENCE_MINIMUM_POWER + 1),
	};

	enum DXGI_HARDWARE_COMPOSITION_SUPPORT_FLAGS
	{
		DXGI_HARDWARE_COMPOSITION_SUPPORT_FLAG_FULLSCREEN = 1,
		DXGI_HARDWARE_COMPOSITION_SUPPORT_FLAG_WINDOWED = 2,
		DXGI_HARDWARE_COMPOSITION_SUPPORT_FLAG_CURSOR_STRETCHED = 4,
	};
}

namespace REX::W32
{
	struct DXGI_ADAPTER_DESC3
	{
		wchar_t                              description[128];
		std::uint32_t                        vendorID;
		std::uint32_t                        deviceID;
		std::uint32_t                        subSysID;
		std::uint32_t                        revision;
		std::size_t                          dedicatedVideoMemory;
		std::size_t                          dedicatedSystemMemory;
		std::size_t                          sharedSystemMemory;
		LUID                                 adapterLUID;
		DXGI_ADAPTER_FLAG3                   flags;
		DXGI_GRAPHICS_PREEMPTION_GRANULARITY graphicsPreemptionGranularity;
		DXGI_COMPUTE_PREEMPTION_GRANULARITY  computePreemptionGranularity;
	};

	struct DXGI_OUTPUT_DESC1
	{
		wchar_t               deviceName[32];
		RECT                  desktopCoordinates;
		BOOL                  attachedToDesktop;
		DXGI_MODE_ROTATION    rotation;
		HMONITOR              monitor;
		std::uint32_t         bitsPerColor;
		DXGI_COLOR_SPACE_TYPE colorSpace;
		float                 redPrimary[2];
		float                 greenPrimary[2];
		float                 bluePrimary[2];
		float                 whitePoint[2];
		float                 minLuminance;
		float                 maxLuminance;
		float                 maxFullFrameLuminance;
	};
}

namespace REX::W32
{
	struct __declspec(novtable, uuid("3C8D99D1-4FBF-4181-A82C-AF66BF7BD24E"))
		IDXGIAdapter4 : public IDXGIAdapter3
	{
		virtual HRESULT GetDesc3(DXGI_ADAPTER_DESC3* a_desc) = 0;
	};

	struct __declspec(novtable, uuid("C1B6694F-FF09-44A9-B03C-77900A0A1D17"))
		IDXGIFactory6 : public IDXGIFactory5
	{
		virtual HRESULT EnumAdapterByGpuPreference(std::uint32_t a_adapterFlags, DXGI_GPU_PREFERENCE a_gpuPreference, const IID& a_iid, void** a_adapter) = 0;
	};

	struct __declspec(novtable, uuid("A4966EED-76DB-44DA-84C1-EE9A7AFB20A8"))
		IDXGIFactory7 : public IDXGIFactory6
	{
		virtual HRESULT RegisterAdaptersChangedEvent(HANDLE a_event, std::uint32_t* a_cookie) = 0;
		virtual HRESULT UnregisterAdaptersChangedEvent(std::uint32_t a_cookie) = 0;
	};

	struct __declspec(novtable, uuid("068346E8-AAEC-4B84-ADD7-137F513F77A1"))
		IDXGIOutput6 : public IDXGIOutput5
	{
		virtual HRESULT GetDesc1(DXGI_OUTPUT_DESC1* a_desc) = 0;
		virtual HRESULT CheckHardwareCompositionSupport(std::uint32_t* a_flags) = 0;
	};
}

namespace REX::W32
{
	inline constexpr IID IID_IDXGIAdapter4{ 0x3C8D99D1, 0x4FBF, 0x4181, { 0xA8, 0x2C, 0xAF, 0x66, 0xBF, 0x7B, 0xD2, 0x4E } };
	inline constexpr IID IID_IDXGIFactory6{ 0xC1B6694F, 0xFF09, 0x44A9, { 0xB0, 0x3C, 0x77, 0x90, 0x0A, 0x0A, 0x1D, 0x17 } };
	inline constexpr IID IID_IDXGIFactory7{ 0xA4966EED, 0x76DB, 0x44DA, { 0x84, 0xC1, 0xEE, 0x9A, 0x7A, 0xFB, 0x20, 0xA8 } };
	inline constexpr IID IID_IDXGIOutput6{ 0x068346E8, 0xAAEC, 0x4B84, { 0xAD, 0xD7, 0x13, 0x7F, 0x51, 0x3F, 0x77, 0xA1 } };
}
