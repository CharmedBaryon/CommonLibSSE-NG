#pragma once

#include "REX/W32/DXGI_4.h"

namespace REX::W32
{
	struct IDXGIDevice4;
	struct IDXGIFactory5;
	struct IDXGIOutput5;
	struct IDXGISwapChain4;
}

namespace REX::W32
{
	enum DXGI_FEATURE
	{
		DXGI_FEATURE_PRESENT_ALLOW_TEARING = 0,
	};

	enum DXGI_HDR_METADATA_TYPE
	{
		DXGI_HDR_METADATA_TYPE_NONE = 0,
		DXGI_HDR_METADATA_TYPE_HDR10 = 1,
		DXGI_HDR_METADATA_TYPE_HDR10PLUS = 2,
	};

	enum DXGI_OFFER_RESOURCE_FLAGS
	{
		DXGI_OFFER_RESOURCE_FLAG_ALLOW_DECOMMIT = 0x1,
	};

	enum DXGI_RECLAIM_RESOURCE_RESULTS
	{
		DXGI_RECLAIM_RESOURCE_RESULT_OK = 0,
		DXGI_RECLAIM_RESOURCE_RESULT_DISCARDED = 1,
		DXGI_RECLAIM_RESOURCE_RESULT_NOT_COMMITTED = 2,
	};
}

namespace REX::W32
{
	struct DXGI_HDR_METADATA_HDR10
	{
		std::uint16_t redPrimary[2];
		std::uint16_t GreenPrimary[2];
		std::uint16_t bluePrimary[2];
		std::uint16_t whitePoint[2];
		std::uint32_t maxMasteringLuminance;
		std::uint32_t minMasteringLuminance;
		std::uint16_t maxContentLightLevel;
		std::uint16_t maxFrameAverageLightLevel;
	};

	struct DXGI_HDR_METADATA_HDR10PLUS
	{
		std::uint8_t data[72];
	};
}

namespace REX::W32
{
	struct __declspec(novtable, uuid("95B4F95F-D8DA-4CA4-9EE6-3B76D5968A10"))
		IDXGIDevice4 : public IDXGIDevice3
	{
		virtual HRESULT OfferResources1(std::uint32_t a_numResources, IDXGIResource* const* a_resources, DXGI_OFFER_RESOURCE_PRIORITY a_priority, std::uint32_t a_flags) = 0;
		virtual HRESULT ReclaimResources1(std::uint32_t a_numResources, IDXGIResource* const* a_resources, DXGI_RECLAIM_RESOURCE_RESULTS* a_results) = 0;
	};

	struct __declspec(novtable, uuid("7632E1F5-EE65-4DCA-87FD-84CD75F8838D"))
		IDXGIFactory5 : public IDXGIFactory4
	{
		virtual HRESULT CheckFeatureSupport(DXGI_FEATURE a_feature, void* a_featureSupportData, std::uint32_t a_featureSupportDataSize) = 0;
	};

	struct __declspec(novtable, uuid("80A07424-AB52-42EB-833C-0C42FD282D98"))
		IDXGIOutput5 : public IDXGIOutput4
	{
		virtual HRESULT DuplicateOutput1(IUnknown* a_device, std::uint32_t a_flags, std::uint32_t a_supportedFormatsCount, const DXGI_FORMAT* a_supportedFormats, IDXGIOutputDuplication** a_outputDuplication) = 0;
	};

	struct __declspec(novtable, uuid("3D585D5A-BD4A-489E-B1F4-3DBCB6452FFB"))
		IDXGISwapChain4 : public IDXGISwapChain3
	{
		virtual HRESULT SetHDRMetaData(DXGI_HDR_METADATA_TYPE a_type, std::uint32_t a_size, void* a_metaData) = 0;
	};
}

namespace REX::W32
{
	inline constexpr IID IID_IDXGIDevice4{ 0x95B4F95F, 0xD8DA, 0x4CA4, { 0x9E, 0xE6, 0x3B, 0x76, 0xD5, 0x96, 0x8A, 0x10 } };
	inline constexpr IID IID_IDXGIFactory5{ 0x7632E1F5, 0xEE65, 0x4DCA, { 0x87, 0xFD, 0x84, 0xCD, 0x75, 0xF8, 0x83, 0x8D } };
	inline constexpr IID IID_IDXGIOutput5{ 0x80A07424, 0xAB52, 0x42EB, { 0x83, 0x3C, 0x0C, 0x42, 0xFD, 0x28, 0x2D, 0x98 } };
	inline constexpr IID IID_IDXGISwapChain4{ 0x3D585D5A, 0xBD4A, 0x489E, { 0xB1, 0xF4, 0x3D, 0xBC, 0xB6, 0x45, 0x2F, 0xFB } };
}
