#pragma once

#include "REX/W32/COM.h"

namespace REX::W32
{
	struct IDXGIAdapter;
	struct IDXGIAdapter1;
	struct IDXGIDevice;
	struct IDXGIDevice1;
	struct IDXGIDeviceSubObject;
	struct IDXGIFactory1;
	struct IDXGIKeyedMutex;
	struct IDXGIObject;
	struct IDXGIOutput;
	struct IDXGIResource;
	struct IDXGISurface;
	struct IDXGISurface1;
	struct IDXGISwapChain;
}

namespace REX::W32
{
	enum DXGI_ADAPTER_FLAG
	{
		DXGI_ADAPTER_FLAG_NONE = 0,
		DXGI_ADAPTER_FLAG_REMOTE = 1,
		DXGI_ADAPTER_FLAG_SOFTWARE = 2,
		DXGI_ADAPTER_FLAG_FORCE_DWORD = 0xFFFFFFFF,
	};

	enum DXGI_COLOR_SPACE_TYPE
	{
		DXGI_COLOR_SPACE_RGB_FULL_G22_NONE_P709 = 0,
		DXGI_COLOR_SPACE_RGB_FULL_G10_NONE_P709 = 1,
		DXGI_COLOR_SPACE_RGB_STUDIO_G22_NONE_P709 = 2,
		DXGI_COLOR_SPACE_RGB_STUDIO_G22_NONE_P2020 = 3,
		DXGI_COLOR_SPACE_RESERVED = 4,
		DXGI_COLOR_SPACE_YCBCR_FULL_G22_NONE_P709_X601 = 5,
		DXGI_COLOR_SPACE_YCBCR_STUDIO_G22_LEFT_P601 = 6,
		DXGI_COLOR_SPACE_YCBCR_FULL_G22_LEFT_P601 = 7,
		DXGI_COLOR_SPACE_YCBCR_STUDIO_G22_LEFT_P709 = 8,
		DXGI_COLOR_SPACE_YCBCR_FULL_G22_LEFT_P709 = 9,
		DXGI_COLOR_SPACE_YCBCR_STUDIO_G22_LEFT_P2020 = 10,
		DXGI_COLOR_SPACE_YCBCR_FULL_G22_LEFT_P2020 = 11,
		DXGI_COLOR_SPACE_RGB_FULL_G2084_NONE_P2020 = 12,
		DXGI_COLOR_SPACE_YCBCR_STUDIO_G2084_LEFT_P2020 = 13,
		DXGI_COLOR_SPACE_RGB_STUDIO_G2084_NONE_P2020 = 14,
		DXGI_COLOR_SPACE_YCBCR_STUDIO_G22_TOPLEFT_P2020 = 15,
		DXGI_COLOR_SPACE_YCBCR_STUDIO_G2084_TOPLEFT_P2020 = 16,
		DXGI_COLOR_SPACE_RGB_FULL_G22_NONE_P2020 = 17,
		DXGI_COLOR_SPACE_YCBCR_STUDIO_GHLG_TOPLEFT_P2020 = 18,
		DXGI_COLOR_SPACE_YCBCR_FULL_GHLG_TOPLEFT_P2020 = 19,
		DXGI_COLOR_SPACE_RGB_STUDIO_G24_NONE_P709 = 20,
		DXGI_COLOR_SPACE_RGB_STUDIO_G24_NONE_P2020 = 21,
		DXGI_COLOR_SPACE_YCBCR_STUDIO_G24_LEFT_P709 = 22,
		DXGI_COLOR_SPACE_YCBCR_STUDIO_G24_LEFT_P2020 = 23,
		DXGI_COLOR_SPACE_YCBCR_STUDIO_G24_TOPLEFT_P2020 = 24,
		DXGI_COLOR_SPACE_CUSTOM = 0xFFFFFFFF,
	};

	enum DXGI_FORMAT
	{
		DXGI_FORMAT_UNKNOWN = 0,
		DXGI_FORMAT_R32G32B32A32_TYPELESS = 1,
		DXGI_FORMAT_R32G32B32A32_FLOAT = 2,
		DXGI_FORMAT_R32G32B32A32_UINT = 3,
		DXGI_FORMAT_R32G32B32A32_SINT = 4,
		DXGI_FORMAT_R32G32B32_TYPELESS = 5,
		DXGI_FORMAT_R32G32B32_FLOAT = 6,
		DXGI_FORMAT_R32G32B32_UINT = 7,
		DXGI_FORMAT_R32G32B32_SINT = 8,
		DXGI_FORMAT_R16G16B16A16_TYPELESS = 9,
		DXGI_FORMAT_R16G16B16A16_FLOAT = 10,
		DXGI_FORMAT_R16G16B16A16_UNORM = 11,
		DXGI_FORMAT_R16G16B16A16_UINT = 12,
		DXGI_FORMAT_R16G16B16A16_SNORM = 13,
		DXGI_FORMAT_R16G16B16A16_SINT = 14,
		DXGI_FORMAT_R32G32_TYPELESS = 15,
		DXGI_FORMAT_R32G32_FLOAT = 16,
		DXGI_FORMAT_R32G32_UINT = 17,
		DXGI_FORMAT_R32G32_SINT = 18,
		DXGI_FORMAT_R32G8X24_TYPELESS = 19,
		DXGI_FORMAT_D32_FLOAT_S8X24_UINT = 20,
		DXGI_FORMAT_R32_FLOAT_X8X24_TYPELESS = 21,
		DXGI_FORMAT_X32_TYPELESS_G8X24_UINT = 22,
		DXGI_FORMAT_R10G10B10A2_TYPELESS = 23,
		DXGI_FORMAT_R10G10B10A2_UNORM = 24,
		DXGI_FORMAT_R10G10B10A2_UINT = 25,
		DXGI_FORMAT_R11G11B10_FLOAT = 26,
		DXGI_FORMAT_R8G8B8A8_TYPELESS = 27,
		DXGI_FORMAT_R8G8B8A8_UNORM = 28,
		DXGI_FORMAT_R8G8B8A8_UNORM_SRGB = 29,
		DXGI_FORMAT_R8G8B8A8_UINT = 30,
		DXGI_FORMAT_R8G8B8A8_SNORM = 31,
		DXGI_FORMAT_R8G8B8A8_SINT = 32,
		DXGI_FORMAT_R16G16_TYPELESS = 33,
		DXGI_FORMAT_R16G16_FLOAT = 34,
		DXGI_FORMAT_R16G16_UNORM = 35,
		DXGI_FORMAT_R16G16_UINT = 36,
		DXGI_FORMAT_R16G16_SNORM = 37,
		DXGI_FORMAT_R16G16_SINT = 38,
		DXGI_FORMAT_R32_TYPELESS = 39,
		DXGI_FORMAT_D32_FLOAT = 40,
		DXGI_FORMAT_R32_FLOAT = 41,
		DXGI_FORMAT_R32_UINT = 42,
		DXGI_FORMAT_R32_SINT = 43,
		DXGI_FORMAT_R24G8_TYPELESS = 44,
		DXGI_FORMAT_D24_UNORM_S8_UINT = 45,
		DXGI_FORMAT_R24_UNORM_X8_TYPELESS = 46,
		DXGI_FORMAT_X24_TYPELESS_G8_UINT = 47,
		DXGI_FORMAT_R8G8_TYPELESS = 48,
		DXGI_FORMAT_R8G8_UNORM = 49,
		DXGI_FORMAT_R8G8_UINT = 50,
		DXGI_FORMAT_R8G8_SNORM = 51,
		DXGI_FORMAT_R8G8_SINT = 52,
		DXGI_FORMAT_R16_TYPELESS = 53,
		DXGI_FORMAT_R16_FLOAT = 54,
		DXGI_FORMAT_D16_UNORM = 55,
		DXGI_FORMAT_R16_UNORM = 56,
		DXGI_FORMAT_R16_UINT = 57,
		DXGI_FORMAT_R16_SNORM = 58,
		DXGI_FORMAT_R16_SINT = 59,
		DXGI_FORMAT_R8_TYPELESS = 60,
		DXGI_FORMAT_R8_UNORM = 61,
		DXGI_FORMAT_R8_UINT = 62,
		DXGI_FORMAT_R8_SNORM = 63,
		DXGI_FORMAT_R8_SINT = 64,
		DXGI_FORMAT_A8_UNORM = 65,
		DXGI_FORMAT_R1_UNORM = 66,
		DXGI_FORMAT_R9G9B9E5_SHAREDEXP = 67,
		DXGI_FORMAT_R8G8_B8G8_UNORM = 68,
		DXGI_FORMAT_G8R8_G8B8_UNORM = 69,
		DXGI_FORMAT_BC1_TYPELESS = 70,
		DXGI_FORMAT_BC1_UNORM = 71,
		DXGI_FORMAT_BC1_UNORM_SRGB = 72,
		DXGI_FORMAT_BC2_TYPELESS = 73,
		DXGI_FORMAT_BC2_UNORM = 74,
		DXGI_FORMAT_BC2_UNORM_SRGB = 75,
		DXGI_FORMAT_BC3_TYPELESS = 76,
		DXGI_FORMAT_BC3_UNORM = 77,
		DXGI_FORMAT_BC3_UNORM_SRGB = 78,
		DXGI_FORMAT_BC4_TYPELESS = 79,
		DXGI_FORMAT_BC4_UNORM = 80,
		DXGI_FORMAT_BC4_SNORM = 81,
		DXGI_FORMAT_BC5_TYPELESS = 82,
		DXGI_FORMAT_BC5_UNORM = 83,
		DXGI_FORMAT_BC5_SNORM = 84,
		DXGI_FORMAT_B5G6R5_UNORM = 85,
		DXGI_FORMAT_B5G5R5A1_UNORM = 86,
		DXGI_FORMAT_B8G8R8A8_UNORM = 87,
		DXGI_FORMAT_B8G8R8X8_UNORM = 88,
		DXGI_FORMAT_R10G10B10_XR_BIAS_A2_UNORM = 89,
		DXGI_FORMAT_B8G8R8A8_TYPELESS = 90,
		DXGI_FORMAT_B8G8R8A8_UNORM_SRGB = 91,
		DXGI_FORMAT_B8G8R8X8_TYPELESS = 92,
		DXGI_FORMAT_B8G8R8X8_UNORM_SRGB = 93,
		DXGI_FORMAT_BC6H_TYPELESS = 94,
		DXGI_FORMAT_BC6H_UF16 = 95,
		DXGI_FORMAT_BC6H_SF16 = 96,
		DXGI_FORMAT_BC7_TYPELESS = 97,
		DXGI_FORMAT_BC7_UNORM = 98,
		DXGI_FORMAT_BC7_UNORM_SRGB = 99,
		DXGI_FORMAT_AYUV = 100,
		DXGI_FORMAT_Y410 = 101,
		DXGI_FORMAT_Y416 = 102,
		DXGI_FORMAT_NV12 = 103,
		DXGI_FORMAT_P010 = 104,
		DXGI_FORMAT_P016 = 105,
		DXGI_FORMAT_420_OPAQUE = 106,
		DXGI_FORMAT_YUY2 = 107,
		DXGI_FORMAT_Y210 = 108,
		DXGI_FORMAT_Y216 = 109,
		DXGI_FORMAT_NV11 = 110,
		DXGI_FORMAT_AI44 = 111,
		DXGI_FORMAT_IA44 = 112,
		DXGI_FORMAT_P8 = 113,
		DXGI_FORMAT_A8P8 = 114,
		DXGI_FORMAT_B4G4R4A4_UNORM = 115,

		DXGI_FORMAT_P208 = 130,
		DXGI_FORMAT_V208 = 131,
		DXGI_FORMAT_V408 = 132,

		DXGI_FORMAT_SAMPLER_FEEDBACK_MIN_MIP_OPAQUE = 189,
		DXGI_FORMAT_SAMPLER_FEEDBACK_MIP_REGION_USED_OPAQUE = 190,

		DXGI_FORMAT_FORCE_UINT = 0xFFFFFFFF,
	};

	enum DXGI_MODE_ROTATION
	{
		DXGI_MODE_ROTATION_UNSPECIFIED = 0,
		DXGI_MODE_ROTATION_IDENTITY = 1,
		DXGI_MODE_ROTATION_ROTATE90 = 2,
		DXGI_MODE_ROTATION_ROTATE180 = 3,
		DXGI_MODE_ROTATION_ROTATE270 = 4,
	};

	enum DXGI_MODE_SCALING
	{
		DXGI_MODE_SCALING_UNSPECIFIED = 0,
		DXGI_MODE_SCALING_CENTERED = 1,
		DXGI_MODE_SCALING_STRETCHED = 2,
	};

	enum DXGI_MODE_SCANLINE_ORDER
	{
		DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED = 0,
		DXGI_MODE_SCANLINE_ORDER_PROGRESSIVE = 1,
		DXGI_MODE_SCANLINE_ORDER_UPPER_FIELD_FIRST = 2,
		DXGI_MODE_SCANLINE_ORDER_LOWER_FIELD_FIRST = 3,
	};

	enum DXGI_RESIDENCY
	{
		DXGI_RESIDENCY_FULLY_RESIDENT = 1,
		DXGI_RESIDENCY_RESIDENT_IN_SHARED_MEMORY = 2,
		DXGI_RESIDENCY_EVICTED_TO_DISK = 3,
	};

	enum DXGI_SWAP_EFFECT
	{
		DXGI_SWAP_EFFECT_DISCARD = 0,
		DXGI_SWAP_EFFECT_SEQUENTIAL = 1,
		DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL = 3,
		DXGI_SWAP_EFFECT_FLIP_DISCARD = 4,
	};

	enum DXGI_SWAP_CHAIN_FLAG
	{
		DXGI_SWAP_CHAIN_FLAG_NONPREROTATED = 1,
		DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH = 2,
		DXGI_SWAP_CHAIN_FLAG_GDI_COMPATIBLE = 4,
		DXGI_SWAP_CHAIN_FLAG_RESTRICTED_CONTENT = 8,
		DXGI_SWAP_CHAIN_FLAG_RESTRICT_SHARED_RESOURCE_DRIVER = 16,
		DXGI_SWAP_CHAIN_FLAG_DISPLAY_ONLY = 32,
		DXGI_SWAP_CHAIN_FLAG_FRAME_LATENCY_WAITABLE_OBJECT = 64,
		DXGI_SWAP_CHAIN_FLAG_FOREGROUND_LAYER = 128,
		DXGI_SWAP_CHAIN_FLAG_FULLSCREEN_VIDEO = 256,
		DXGI_SWAP_CHAIN_FLAG_YUV_VIDEO = 512,
		DXGI_SWAP_CHAIN_FLAG_HW_PROTECTED = 1024,
		DXGI_SWAP_CHAIN_FLAG_ALLOW_TEARING = 2048,
		DXGI_SWAP_CHAIN_FLAG_RESTRICTED_TO_ALL_HOLOGRAPHIC_DISPLAYS = 4096,
	};
}

namespace REX::W32
{
	struct D3DCOLORVALUE
	{
		float r;
		float g;
		float b;
		float a;
	};

	using DXGI_RGBA = D3DCOLORVALUE;
	using DXGI_USAGE = std::uint32_t;

	struct LUID
	{
		std::uint32_t lo;
		std::int32_t  hi;
	};
}

namespace REX::W32
{
	struct DXGI_ADAPTER_DESC
	{
		wchar_t       description[128];
		std::uint32_t vendorId;
		std::uint32_t deviceId;
		std::uint32_t subSysId;
		std::uint32_t revision;
		std::size_t   dedicatedVideoMemory;
		std::size_t   dedicatedSystemMemory;
		std::size_t   sharedSystemMemory;
		LUID          adapterLuid;
	};

	struct DXGI_ADAPTER_DESC1
	{
		wchar_t       description[128];
		std::uint32_t vendorId;
		std::uint32_t deviceId;
		std::uint32_t subSysId;
		std::uint32_t revision;
		std::size_t   dedicatedVideoMemory;
		std::size_t   dedicatedSystemMemory;
		std::size_t   sharedSystemMemory;
		LUID          adapterLuid;
		std::uint32_t flags;
	};

	struct DXGI_DISPLAY_COLOR_SPACE
	{
		float primaryCoordinates[8][2];
		float whitePoints[16][2];
	};

	struct DXGI_FRAME_STATISTICS
	{
		std::uint32_t presentCount;
		std::uint32_t presentRefreshCount;
		std::uint32_t syncRefreshCount;
		std::int64_t  syncQPCTime;
		std::int64_t  syncGPUTime;
	};

	struct DXGI_RGB
	{
		float red;
		float green;
		float blue;
	};

	struct DXGI_GAMMA_CONTROL
	{
		DXGI_RGB scale;
		DXGI_RGB offset;
		DXGI_RGB gammaCurve[1025];
	};

	struct DXGI_GAMMA_CONTROL_CAPABILITIES
	{
		BOOL          scaleAndOffsetSupported;
		float         maxConvertedValue;
		float         minConvertedValue;
		std::uint32_t numGammaControlPoints;
		float         controlPointPositions[1025];
	};

	struct DXGI_MAPPED_RECT
	{
		std::int32_t  pitch;
		std::uint8_t* bits;
	};

	struct DXGI_RATIONAL
	{
		std::uint32_t numerator;
		std::uint32_t denominator;
	};

	struct DXGI_MODE_DESC
	{
		std::uint32_t            width;
		std::uint32_t            height;
		DXGI_RATIONAL            refreshRate;
		DXGI_FORMAT              format;
		DXGI_MODE_SCANLINE_ORDER scanlineOrdering;
		DXGI_MODE_SCALING        scaling;
	};

	struct DXGI_OUTPUT_DESC
	{
		wchar_t            deviceName[32];
		RECT               desktopCoordinates;
		BOOL               attachedToDesktop;
		DXGI_MODE_ROTATION rotation;
		HMONITOR           monitor;
	};

	struct DXGI_SAMPLE_DESC
	{
		std::uint32_t count;
		std::uint32_t quality;
	};

	struct DXGI_SHARED_RESOURCE
	{
		HANDLE handle;
	};

	struct DXGI_SURFACE_DESC
	{
		std::uint32_t    width;
		std::uint32_t    height;
		DXGI_FORMAT      format;
		DXGI_SAMPLE_DESC sampleDesc;
	};

	struct DXGI_SWAP_CHAIN_DESC
	{
		DXGI_MODE_DESC   bufferDesc;
		DXGI_SAMPLE_DESC sampleDesc;
		DXGI_USAGE       bufferUsage;
		std::uint32_t    bufferCount;
		HWND             outputWindow;
		BOOL             windowed;
		DXGI_SWAP_EFFECT swapEffect;
		std::uint32_t    flags;
	};
}

namespace REX::W32
{
	struct __declspec(novtable, uuid("aec22fb8-76f3-4639-9be0-28eb43a67a2e"))
		IDXGIObject : public IUnknown
	{
		virtual HRESULT SetPrivateData(const GUID& a_iid, std::uint32_t a_dataSize, const void* a_data) = 0;
		virtual HRESULT SetPrivateDataInterface(const GUID& a_iid, const IUnknown* a_unknown) = 0;
		virtual HRESULT GetPrivateData(const GUID& a_iid, std::uint32_t* a_dataSize, void* a_data) = 0;
		virtual HRESULT GetParent(const GUID& a_iid, void** a_parent) = 0;
	};

	struct __declspec(novtable, uuid("3d3e0379-f9de-4d58-bb6c-18d62992f1a6"))
		IDXGIDeviceSubObject : public IDXGIObject
	{
		virtual HRESULT GetDevice(const GUID& a_iid, void** a_device) = 0;
	};

	struct __declspec(novtable, uuid("035f3ab4-482e-4e50-b41f-8a7f8bd8960b"))
		IDXGIResource : public IDXGIDeviceSubObject
	{
		virtual HRESULT GetSharedHandle(HANDLE* a_sharedHandle) = 0;
		virtual HRESULT GetUsage(DXGI_USAGE* a_usage) = 0;
		virtual HRESULT SetEvictionPriority(std::uint32_t a_evictionPriority) = 0;
		virtual HRESULT GetEvictionPriority(std::uint32_t* a_evictionPriority) = 0;
	};

	struct __declspec(novtable, uuid("9d8e1289-d7b3-465f-8126-250e349af85d"))
		IDXGIKeyedMutex : public IDXGIDeviceSubObject
	{
		virtual HRESULT AcquireSync(std::uint64_t a_key, std::uint32_t a_milliseconds) = 0;
		virtual HRESULT ReleaseSync(std::uint64_t a_key) = 0;
	};

	struct __declspec(novtable, uuid("cafcb56c-6ac3-4889-bf47-9e23bbd260ec"))
		IDXGISurface : public IDXGIDeviceSubObject
	{
		virtual HRESULT GetDesc(DXGI_SURFACE_DESC* a_desc) = 0;
		virtual HRESULT Map(DXGI_MAPPED_RECT* a_lockedRect, std::uint32_t a_mapFlags) = 0;
		virtual HRESULT Unmap(void) = 0;
	};

	struct __declspec(novtable, uuid("4AE63092-6327-4c1b-80AE-BFE12EA32B86"))
		IDXGISurface1 : public IDXGISurface
	{
		virtual HRESULT GetDC(BOOL a_discard, HDC* a_hdc) = 0;
		virtual HRESULT ReleaseDC(RECT* a_dirtyRect) = 0;
	};

	struct __declspec(novtable, uuid("2411e7e1-12ac-4ccf-bd14-9798e8534dc0"))
		IDXGIAdapter : public IDXGIObject
	{
		virtual HRESULT EnumOutputs(std::uint32_t a_outputSize, IDXGIOutput** a_output) = 0;
		virtual HRESULT GetDesc(DXGI_ADAPTER_DESC* a_desc) = 0;
		virtual HRESULT CheckInterfaceSupport(const GUID& a_iid, std::int64_t* a_umdVersion) = 0;
	};

	struct __declspec(novtable, uuid("29038f61-3839-4626-91fd-086879011a05"))
		IDXGIAdapter1 : public IDXGIAdapter
	{
		virtual HRESULT GetDesc1(DXGI_ADAPTER_DESC1* a_desc) = 0;
	};

	struct __declspec(novtable, uuid("ae02eedb-c735-4690-8d52-5a8dc20213aa"))
		IDXGIOutput : public IDXGIObject
	{
		virtual HRESULT GetDesc(DXGI_OUTPUT_DESC* a_desc) = 0;
		virtual HRESULT GetDisplayModeList(DXGI_FORMAT a_enumFormat, std::uint32_t a_flags, std::uint32_t* a_numModes, DXGI_MODE_DESC* a_desc) = 0;
		virtual HRESULT FindClosestMatchingMode(const DXGI_MODE_DESC* a_modeToMatch, DXGI_MODE_DESC* a_closestMatch, IUnknown* a_concernedDevice) = 0;
		virtual HRESULT WaitForVBlank(void) = 0;
		virtual HRESULT TakeOwnership(IUnknown* a_device, BOOL a_exclusive) = 0;
		virtual void    ReleaseOwnership(void) = 0;
		virtual HRESULT GetGammaControlCapabilities(DXGI_GAMMA_CONTROL_CAPABILITIES* a_gammaCaps) = 0;
		virtual HRESULT SetGammaControl(const DXGI_GAMMA_CONTROL* a_array) = 0;
		virtual HRESULT GetGammaControl(DXGI_GAMMA_CONTROL* a_array) = 0;
		virtual HRESULT SetDisplaySurface(IDXGISurface* a_scanoutSurface) = 0;
		virtual HRESULT GetDisplaySurfaceData(IDXGISurface* a_destination) = 0;
		virtual HRESULT GetFrameStatistics(DXGI_FRAME_STATISTICS* a_stats) = 0;
	};

	struct __declspec(novtable, uuid("310d36a0-d2e7-4c0a-aa04-6a9d23b8886a"))
		IDXGISwapChain : public IDXGIDeviceSubObject
	{
		virtual HRESULT Present(std::uint32_t a_syncInterval, std::uint32_t a_flags) = 0;
		virtual HRESULT GetBuffer(std::uint32_t a_buffer, const GUID& a_iid, void** a_surface) = 0;
		virtual HRESULT SetFullscreenState(BOOL a_fullscreen, IDXGIOutput* a_target) = 0;
		virtual HRESULT GetFullscreenState(BOOL* a_fullscreen, IDXGIOutput** a_target) = 0;
		virtual HRESULT GetDesc(DXGI_SWAP_CHAIN_DESC* a_desc) = 0;
		virtual HRESULT ResizeBuffers(std::uint32_t a_bufferCount, std::uint32_t a_width, std::uint32_t a_height, DXGI_FORMAT a_newFormat, std::uint32_t a_swapChainFlags) = 0;
		virtual HRESULT ResizeTarget(const DXGI_MODE_DESC* a_newTargetParameters) = 0;
		virtual HRESULT GetContainingOutput(IDXGIOutput** a_output) = 0;
		virtual HRESULT GetFrameStatistics(DXGI_FRAME_STATISTICS* a_stats) = 0;
		virtual HRESULT GetLastPresentCount(std::uint32_t* a_lastPresentCount) = 0;
	};

	struct __declspec(novtable, uuid("7b7166ec-21c7-44ae-b21a-c9ae321ae369"))
		IDXGIFactory : public IDXGIObject
	{
		virtual HRESULT EnumAdapters(std::uint32_t a_adapterSize, IDXGIAdapter** a_adapter) = 0;
		virtual HRESULT MakeWindowAssociation(HWND a_windowHandle, std::uint32_t a_flags) = 0;
		virtual HRESULT GetWindowAssociation(HWND* a_windowHandle) = 0;
		virtual HRESULT CreateSwapChain(IUnknown* a_device, DXGI_SWAP_CHAIN_DESC* a_desc, IDXGISwapChain** a_swapChain) = 0;
		virtual HRESULT CreateSoftwareAdapter(HMODULE a_module, IDXGIAdapter** a_adapter) = 0;
	};

	struct __declspec(novtable, uuid("770aae78-f26f-4dba-a829-253c83d1b387"))
		IDXGIFactory1 : public IDXGIFactory
	{
		virtual HRESULT EnumAdapters1(std::uint32_t a_adapterSize, IDXGIAdapter1** a_adapter) = 0;
		virtual BOOL    IsCurrent(void) = 0;
	};

	struct __declspec(novtable, uuid("54ec77fa-1377-44e6-8c32-88fd5f44c84c"))
		IDXGIDevice : public IDXGIObject
	{
		virtual HRESULT GetAdapter(IDXGIAdapter** a_adapter) = 0;
		virtual HRESULT CreateSurface(const DXGI_SURFACE_DESC* a_desc, std::uint32_t a_numSurfaces, DXGI_USAGE a_usage, const DXGI_SHARED_RESOURCE* a_sharedResource, IDXGISurface** a_surface) = 0;
		virtual HRESULT QueryResourceResidency(IUnknown* const* a_resources, DXGI_RESIDENCY* a_residencyStatus, std::uint32_t a_numResources) = 0;
		virtual HRESULT SetGPUThreadPriority(std::int32_t a_priority) = 0;
		virtual HRESULT GetGPUThreadPriority(std::int32_t* a_priority) = 0;
	};

	struct __declspec(novtable, uuid("77db970f-6276-48ba-ba28-070143b4392c"))
		IDXGIDevice1 : public IDXGIDevice
	{
		virtual HRESULT SetMaximumFrameLatency(std::uint32_t a_maxLatency) = 0;
		virtual HRESULT GetMaximumFrameLatency(std::uint32_t* a_maxLatency) = 0;
	};
}

namespace REX::W32
{
	HRESULT CreateDXGIFactory(const IID& a_iid, void** a_factory) noexcept;
	HRESULT CreateDXGIFactory1(const IID& a_iid, void** a_factory) noexcept;
}

namespace REX::W32
{
	inline constexpr IID IID_IDXGIAdapter{ 0x2411E7E1, 0x12AC, 0x4CCF, { 0xBD, 0x14, 0x97, 0x98, 0xE8, 0x53, 0x4D, 0xC0 } };
	inline constexpr IID IID_IDXGIAdapter1{ 0x29038F61, 0x3839, 0x4626, { 0x91, 0xFD, 0x08, 0x68, 0x79, 0x01, 0x1A, 0x05 } };
	inline constexpr IID IID_IDXGIObject{ 0xAEC22Fb8, 0x76F3, 0x4639, { 0x9B, 0xE0, 0x28, 0xEB, 0x43, 0xA6, 0x7A, 0x2E } };
	inline constexpr IID IID_IDXGIDevice{ 0x54EC77FA, 0x1377, 0x44E6, { 0x8C, 0x32, 0x88, 0xFD, 0x5F, 0x44, 0xC8, 0x4C } };
	inline constexpr IID IID_IDXGIDevice1{ 0x77DB970F, 0x6276, 0x48BA, { 0xBA, 0x28, 0x07, 0x01, 0x43, 0xB4, 0x39, 0x2C } };
	inline constexpr IID IID_IDXGIDeviceSubObject{ 0x3D3E0379, 0xF9DE, 0x4D58, { 0xBB, 0x6C, 0x18, 0xD6, 0x29, 0x92, 0xF1, 0xA6 } };
	inline constexpr IID IID_IDXGIFactory{ 0x7B7166EC, 0x21C7, 0x44AE, { 0xB2, 0x1A, 0xC9, 0xAE, 0x32, 0x1A, 0xE3, 0x69 } };
	inline constexpr IID IID_IDXGIFactory1{ 0x770AAE78, 0xF26F, 0x4DBA, { 0xA8, 0x29, 0x25, 0x3C, 0x83, 0xD1, 0xB3, 0x87 } };
	inline constexpr IID IID_IDXGIKeyedMutex{ 0x9D8E1289, 0xD7B3, 0x465F, { 0x81, 0x26, 0x25, 0x0E, 0x34, 0x9A, 0xF8, 0x5D } };
	inline constexpr IID IID_IDXGIOutput{ 0xAE02EEDB, 0xC735, 0x4690, { 0x8D, 0x52, 0x5A, 0x8D, 0xC2, 0x02, 0x13, 0xAA } };
	inline constexpr IID IID_IDXGIResource{ 0x035F3AB4, 0x482E, 0x4E50, { 0xB4, 0x1F, 0x8A, 0x7F, 0x8B, 0xD8, 0x96, 0x0B } };
	inline constexpr IID IID_IDXGISurface{ 0xCAFCB56C, 0x6AC3, 0x4889, { 0xBF, 0x47, 0x9E, 0x23, 0xBB, 0xD2, 0x60, 0xEC } };
	inline constexpr IID IID_IDXGISurface1{ 0x4AE63092, 0x6327, 0x4C1B, { 0x80, 0xAE, 0xBF, 0xE1, 0x2E, 0xA3, 0x2B, 0x86 } };
	inline constexpr IID IID_IDXGISwapChain{ 0x310D36A0, 0xD2E7, 0x4C0A, { 0xAA, 0x04, 0x6A, 0x9D, 0x23, 0xB8, 0x88, 0x6A } };
}
