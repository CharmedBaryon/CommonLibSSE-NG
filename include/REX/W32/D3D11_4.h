#pragma once

#include "REX/W32/D3D11_3.h"
#include "REX/W32/DXGI_5.h"

namespace REX::W32
{
	struct ID3D11Device4;
	struct ID3D11Device5;
	struct ID3D11Multithread;
	struct ID3D11VideoContext2;
	struct ID3D11VideoContext3;
	struct ID3D11VideoDevice2;
}

namespace REX::W32
{
	enum D3D11_CRYPTO_SESSION_KEY_EXCHANGE_FLAGS
	{
		D3D11_CRYPTO_SESSION_KEY_EXCHANGE_FLAG_NONE = 0,
	};

	enum D3D11_FEATURE_VIDEO
	{
		D3D11_FEATURE_VIDEO_DECODER_HISTOGRAM = 0,
	};

	enum D3D11_VIDEO_DECODER_HISTOGRAM_COMPONENT
	{
		D3D11_VIDEO_DECODER_HISTOGRAM_COMPONENT_Y = 0,
		D3D11_VIDEO_DECODER_HISTOGRAM_COMPONENT_U = 1,
		D3D11_VIDEO_DECODER_HISTOGRAM_COMPONENT_V = 2,
		D3D11_VIDEO_DECODER_HISTOGRAM_COMPONENT_R = 0,
		D3D11_VIDEO_DECODER_HISTOGRAM_COMPONENT_G = 1,
		D3D11_VIDEO_DECODER_HISTOGRAM_COMPONENT_B = 2,
		D3D11_VIDEO_DECODER_HISTOGRAM_COMPONENT_A = 3,
	};

	enum D3D11_VIDEO_DECODER_HISTOGRAM_COMPONENT_FLAGS
	{
		D3D11_VIDEO_DECODER_HISTOGRAM_COMPONENT_FLAG_NONE = 0,
		D3D11_VIDEO_DECODER_HISTOGRAM_COMPONENT_FLAG_Y = (1 << D3D11_VIDEO_DECODER_HISTOGRAM_COMPONENT_Y),
		D3D11_VIDEO_DECODER_HISTOGRAM_COMPONENT_FLAG_U = (1 << D3D11_VIDEO_DECODER_HISTOGRAM_COMPONENT_U),
		D3D11_VIDEO_DECODER_HISTOGRAM_COMPONENT_FLAG_V = (1 << D3D11_VIDEO_DECODER_HISTOGRAM_COMPONENT_V),
		D3D11_VIDEO_DECODER_HISTOGRAM_COMPONENT_FLAG_R = (1 << D3D11_VIDEO_DECODER_HISTOGRAM_COMPONENT_R),
		D3D11_VIDEO_DECODER_HISTOGRAM_COMPONENT_FLAG_G = (1 << D3D11_VIDEO_DECODER_HISTOGRAM_COMPONENT_G),
		D3D11_VIDEO_DECODER_HISTOGRAM_COMPONENT_FLAG_B = (1 << D3D11_VIDEO_DECODER_HISTOGRAM_COMPONENT_B),
		D3D11_VIDEO_DECODER_HISTOGRAM_COMPONENT_FLAG_A = (1 << D3D11_VIDEO_DECODER_HISTOGRAM_COMPONENT_A),
	};
}

namespace REX::W32
{
	struct D3D11_FEATURE_DATA_D3D11_OPTIONS4
	{
		BOOL extendedNV12SharedTextureSupported;
	};

	struct D3D11_FEATURE_DATA_VIDEO_DECODER_HISTOGRAM
	{
		D3D11_VIDEO_DECODER_DESC                      decoderDesc;
		D3D11_VIDEO_DECODER_HISTOGRAM_COMPONENT_FLAGS components;
		std::uint32_t                                 binCount;
		std::uint32_t                                 counterBitDepth;
	};

	struct D3D11_VIDEO_DECODER_BUFFER_DESC2
	{
		D3D11_VIDEO_DECODER_BUFFER_TYPE               bufferType;
		std::uint32_t                                 dataOffset;
		std::uint32_t                                 dataSize;
		void*                                         iv;
		std::uint32_t                                 ivSize;
		D3D11_VIDEO_DECODER_SUB_SAMPLE_MAPPING_BLOCK* subSampleMappingBlock;
		std::uint32_t                                 subSampleMappingCount;
		std::uint32_t                                 cBlocksStripeEncrypted;
		std::uint32_t                                 cBlocksStripeClear;
	};
}

namespace REX::W32
{
	struct __declspec(novtable, uuid("8992ab71-02e6-4b8d-ba48-b056dcda42c4"))
		ID3D11Device4 : public ID3D11Device3
	{
		virtual HRESULT RegisterDeviceRemovedEvent(HANDLE a_event, std::uint32_t* a_cookie) = 0;
		virtual void    UnregisterDeviceRemoved(std::uint32_t a_cookie) = 0;
	};

	struct __declspec(novtable, uuid("8ffde202-a0e7-45df-9e01-e837801b5ea0"))
		ID3D11Device5 : public ID3D11Device4
	{
		virtual HRESULT OpenSharedFence(HANDLE a_fenceHandle, const IID& a_returnedInterface, void** a_fence) = 0;
		virtual HRESULT CreateFence(std::uint64_t a_initialValue, D3D11_FENCE_FLAG a_flags, const IID& a_returnedInterface, void** a_fence) = 0;
	};

	struct __declspec(novtable, uuid("9B7E4E00-342C-4106-A19F-4F2704F689F0"))
		ID3D11Multithread : public IUnknown
	{
		virtual void Enter(void) = 0;
		virtual void Leave(void) = 0;
		virtual BOOL SetMultithreadProtected(BOOL a_mtProtect) = 0;
		virtual BOOL GetMultithreadProtected(void) = 0;
	};

	struct __declspec(novtable, uuid("C4E7374C-6243-4D1B-AE87-52B4F740E261"))
		ID3D11VideoContext2 : public ID3D11VideoContext1
	{
		virtual void VideoProcessorSetOutputHDRMetaData(ID3D11VideoProcessor* a_videoProcessor, DXGI_HDR_METADATA_TYPE a_type, std::uint32_t a_size, const void* a_hdrMetaData) = 0;
		virtual void VideoProcessorGetOutputHDRMetaData(ID3D11VideoProcessor* a_videoProcessor, DXGI_HDR_METADATA_TYPE* a_type, std::uint32_t a_size, void* a_hdrMetaData) = 0;
		virtual void VideoProcessorSetStreamHDRMetaData(ID3D11VideoProcessor* a_videoProcessor, std::uint32_t a_streamIndex, DXGI_HDR_METADATA_TYPE a_type, std::uint32_t a_size, const void* a_hdrMetaData) = 0;
		virtual void VideoProcessorGetStreamHDRMetaData(ID3D11VideoProcessor* a_videoProcessor, std::uint32_t a_streamIndex, DXGI_HDR_METADATA_TYPE* a_type, std::uint32_t a_size, void* a_hdrMetaData) = 0;
	};

	struct __declspec(novtable, uuid("A9E2FAA0-CB39-418F-A0B7-D8AAD4DE672E"))
		ID3D11VideoContext3 : public ID3D11VideoContext2
	{
		virtual HRESULT DecoderBeginFrame1(ID3D11VideoDecoder* a_decoder, ID3D11VideoDecoderOutputView* a_view, std::uint32_t a_contentKeySize, const void* a_contentKey, std::uint32_t a_numComponentHistograms, const std::uint32_t* a_histogramOffsets, ID3D11Buffer* const* a_histogramBuffers) = 0;
		virtual HRESULT SubmitDecoderBuffers2(ID3D11VideoDecoder* a_decoder, std::uint32_t a_numBuffers, const D3D11_VIDEO_DECODER_BUFFER_DESC2* a_bufferDesc) = 0;
	};

	struct __declspec(novtable, uuid("59C0CB01-35F0-4A70-8F67-87905C906A53"))
		ID3D11VideoDevice2 : public ID3D11VideoDevice1
	{
		virtual HRESULT CheckFeatureSupport(D3D11_FEATURE_VIDEO a_feature, void* a_featureSupportData, std::uint32_t a_featureSupportDataSize) = 0;
		virtual HRESULT NegotiateCryptoSessionKeyExchangeMT(ID3D11CryptoSession* a_cryptoSession, D3D11_CRYPTO_SESSION_KEY_EXCHANGE_FLAGS a_flags, std::uint32_t a_dataSize, void* a_data) = 0;
	};
}

namespace REX::W32
{
	inline constexpr IID IID_ID3D11Device4{ 0x8992AB71, 0x02E6, 0x4B8D, { 0xBA, 0x48, 0xB0, 0x56, 0xDC, 0xDA, 0x42, 0xC4 } };
	inline constexpr IID IID_ID3D11Device5{ 0x8FFDE202, 0xA0E7, 0x45DF, { 0x9E, 0x01, 0xE8, 0x37, 0x80, 0x1B, 0x5E, 0xA0 } };
	inline constexpr IID IID_ID3D11Multithread{ 0x9B7E4E00, 0x342C, 0x4106, { 0xA1, 0x9F, 0x4F, 0x27, 0x04, 0xF6, 0x89, 0xF0 } };
	inline constexpr IID IID_ID3D11VideoContext2{ 0xC4E7374C, 0x6243, 0x4D1B, { 0xAE, 0x87, 0x52, 0xB4, 0xF7, 0x40, 0xE2, 0x61 } };
	inline constexpr IID IID_ID3D11VideoContext3{ 0xA9E2FAA0, 0xCB39, 0x418F, { 0xA0, 0xB7, 0xD8, 0xAA, 0xD4, 0xDE, 0x67, 0x2E } };
	inline constexpr IID IID_ID3D11VideoDevice2{ 0x59C0CB01, 0x35F0, 0x4A70, { 0x8F, 0x67, 0x87, 0x90, 0x5C, 0x90, 0x6A, 0x53 } };
}
