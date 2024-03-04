#pragma once

#include "REX/W32/D3D11.h"

namespace REX::W32
{
	struct ID3DDeviceContextState;
	struct ID3DUserDefinedAnnotation;
	struct ID3D11BlendState1;
	struct ID3D11Device1;
	struct ID3D11DeviceContext1;
	struct ID3D11RasterizerState1;
	struct ID3D11VideoContext1;
	struct ID3D11VideoDevice1;
	struct ID3D11VideoProcessorEnumerator1;
}

namespace REX::W32
{
	enum D3D11_1_CREATE_DEVICE_CONTEXT_STATE_FLAG
	{
		D3D11_1_CREATE_DEVICE_CONTEXT_STATE_SINGLETHREADED = 0x1,
	};

	enum D3D11_COPY_FLAGS
	{
		D3D11_COPY_NO_OVERWRITE = 0x1,
		D3D11_COPY_DISCARD = 0x2,
	};

	enum D3D11_CRYPTO_SESSION_STATUS
	{
		D3D11_CRYPTO_SESSION_STATUS_OK = 0,
		D3D11_CRYPTO_SESSION_STATUS_KEY_LOST = 1,
		D3D11_CRYPTO_SESSION_STATUS_KEY_AND_CONTENT_LOST = 2,
	};

	enum D3D11_LOGIC_OP
	{
		D3D11_LOGIC_OP_CLEAR = 0,
		D3D11_LOGIC_OP_SET = (D3D11_LOGIC_OP_CLEAR + 1),
		D3D11_LOGIC_OP_COPY = (D3D11_LOGIC_OP_SET + 1),
		D3D11_LOGIC_OP_COPY_INVERTED = (D3D11_LOGIC_OP_COPY + 1),
		D3D11_LOGIC_OP_NOOP = (D3D11_LOGIC_OP_COPY_INVERTED + 1),
		D3D11_LOGIC_OP_INVERT = (D3D11_LOGIC_OP_NOOP + 1),
		D3D11_LOGIC_OP_AND = (D3D11_LOGIC_OP_INVERT + 1),
		D3D11_LOGIC_OP_NAND = (D3D11_LOGIC_OP_AND + 1),
		D3D11_LOGIC_OP_OR = (D3D11_LOGIC_OP_NAND + 1),
		D3D11_LOGIC_OP_NOR = (D3D11_LOGIC_OP_OR + 1),
		D3D11_LOGIC_OP_XOR = (D3D11_LOGIC_OP_NOR + 1),
		D3D11_LOGIC_OP_EQUIV = (D3D11_LOGIC_OP_XOR + 1),
		D3D11_LOGIC_OP_AND_REVERSE = (D3D11_LOGIC_OP_EQUIV + 1),
		D3D11_LOGIC_OP_AND_INVERTED = (D3D11_LOGIC_OP_AND_REVERSE + 1),
		D3D11_LOGIC_OP_OR_REVERSE = (D3D11_LOGIC_OP_AND_INVERTED + 1),
		D3D11_LOGIC_OP_OR_INVERTED = (D3D11_LOGIC_OP_OR_REVERSE + 1),
	};

	enum D3D11_VIDEO_DECODER_CAPS
	{
		D3D11_VIDEO_DECODER_CAPS_DOWNSAMPLE = 0x1,
		D3D11_VIDEO_DECODER_CAPS_NON_REAL_TIME = 0x2,
		D3D11_VIDEO_DECODER_CAPS_DOWNSAMPLE_DYNAMIC = 0x4,
		D3D11_VIDEO_DECODER_CAPS_DOWNSAMPLE_REQUIRED = 0x8,
		D3D11_VIDEO_DECODER_CAPS_UNSUPPORTED = 0x10,
	};

	enum D3D11_VIDEO_PROCESSOR_BEHAVIOR_HINTS
	{
		D3D11_VIDEO_PROCESSOR_BEHAVIOR_HINT_MULTIPLANE_OVERLAY_ROTATION = 0x1,
		D3D11_VIDEO_PROCESSOR_BEHAVIOR_HINT_MULTIPLANE_OVERLAY_RESIZE = 0x2,
		D3D11_VIDEO_PROCESSOR_BEHAVIOR_HINT_MULTIPLANE_OVERLAY_COLOR_SPACE_CONVERSION = 0x4,
		D3D11_VIDEO_PROCESSOR_BEHAVIOR_HINT_TRIPLE_BUFFER_OUTPUT = 0x8,
	};
}

namespace REX::W32
{
	struct D3D11_KEY_EXCHANGE_HW_PROTECTION_INPUT_DATA;
	struct D3D11_KEY_EXCHANGE_HW_PROTECTION_OUTPUT_DATA;
	struct D3D11_VIDEO_DECODER_SUB_SAMPLE_MAPPING_BLOCK;

	struct D3D11_KEY_EXCHANGE_HW_PROTECTION_DATA
	{
		std::uint32_t                                 hwProtectionFunctionID;
		D3D11_KEY_EXCHANGE_HW_PROTECTION_INPUT_DATA*  inputData;
		D3D11_KEY_EXCHANGE_HW_PROTECTION_OUTPUT_DATA* outputData;
		HRESULT                                       status;
	};

	struct D3D11_KEY_EXCHANGE_HW_PROTECTION_INPUT_DATA
	{
		std::uint32_t privateDataSize;
		std::uint32_t hwProtectionDataSize;
		std::uint8_t  input[4];
	};

	struct D3D11_KEY_EXCHANGE_HW_PROTECTION_OUTPUT_DATA
	{
		std::uint32_t privateDataSize;
		std::uint32_t maxHWProtectionDataSize;
		std::uint32_t hwProtectionDataSize;
		std::uint64_t transportTime;
		std::uint64_t executionTime;
		std::uint8_t  output[4];
	};

	struct D3D11_RASTERIZER_DESC1
	{
		D3D11_FILL_MODE fillMode;
		D3D11_CULL_MODE cullMode;
		BOOL            frontCounterClockwise;
		std::int32_t    depthBias;
		float           depthBiasClamp;
		float           slopeScaledDepthBias;
		BOOL            depthClipEnable;
		BOOL            scissorEnable;
		BOOL            multisampleEnable;
		BOOL            antialiasedLineEnable;
		std::uint32_t   forcedSampleCount;
	};

	struct D3D11_RENDER_TARGET_BLEND_DESC1
	{
		BOOL           blendEnable;
		BOOL           logicOpEnable;
		D3D11_BLEND    srcBlend;
		D3D11_BLEND    destBlend;
		D3D11_BLEND_OP blendOp;
		D3D11_BLEND    srcBlendAlpha;
		D3D11_BLEND    destBlendAlpha;
		D3D11_BLEND_OP blendOpAlpha;
		D3D11_LOGIC_OP logicOp;
		std::uint8_t   renderTargetWriteMask;
	};

	struct D3D11_VIDEO_DECODER_BEGIN_FRAME_CRYPTO_SESSION
	{
		ID3D11CryptoSession* cryptoSession;
		std::uint32_t        blobSize;
		void*                blob;
		GUID*                keyInfoId;
		std::uint32_t        privateDataSize;
		void*                privateData;
	};

	struct D3D11_VIDEO_DECODER_BUFFER_DESC1
	{
		D3D11_VIDEO_DECODER_BUFFER_TYPE               bufferType;
		std::uint32_t                                 dataOffset;
		std::uint32_t                                 dataSize;
		void*                                         iv;
		std::uint32_t                                 ivSize;
		D3D11_VIDEO_DECODER_SUB_SAMPLE_MAPPING_BLOCK* subSampleMappingBlock;
		std::uint32_t                                 subSampleMappingCount;
	};

	struct D3D11_VIDEO_DECODER_SUB_SAMPLE_MAPPING_BLOCK
	{
		std::uint32_t clearSize;
		std::uint32_t encryptedSize;
	};

	struct D3D11_VIDEO_PROCESSOR_STREAM_BEHAVIOR_HINT
	{
		BOOL          enable;
		std::uint32_t width;
		std::uint32_t height;
		DXGI_FORMAT   format;
	};

	struct D3D11_VIDEO_SAMPLE_DESC
	{
		std::uint32_t         width;
		std::uint32_t         height;
		DXGI_FORMAT           format;
		DXGI_COLOR_SPACE_TYPE colorSpace;
	};

	struct D3D11_BLEND_DESC1
	{
		BOOL                            alphaToCoverageEnable;
		BOOL                            independentBlendEnable;
		D3D11_RENDER_TARGET_BLEND_DESC1 renderTarget[8];
	};
}

namespace REX::W32
{
	struct __declspec(novtable, uuid("5c1e0d8a-7c23-48f9-8c59-a92958ceff11"))
		ID3DDeviceContextState : public ID3D11DeviceChild
	{};

	struct __declspec(novtable, uuid("b2daad8b-03d4-4dbf-95eb-32ab4b63d0ab"))
		ID3DUserDefinedAnnotation : public IUnknown
	{
		virtual std::int32_t BeginEvent(const wchar_t* a_name) = 0;
		virtual std::int32_t EndEvent(void) = 0;
		virtual void         SetMarker(const wchar_t* a_name) = 0;
		virtual BOOL         GetStatus(void) = 0;
	};

	struct __declspec(novtable, uuid("cc86fabe-da55-401d-85e7-e3c9de2877e9"))
		ID3D11BlendState1 : public ID3D11BlendState
	{
		virtual void GetDesc1(D3D11_BLEND_DESC1* a_desc) = 0;
	};

	struct __declspec(novtable, uuid("a04bfb29-08ef-43d6-a49c-a9bdbdcbe686"))
		ID3D11Device1 : public ID3D11Device
	{
		virtual void    GetImmediateContext1(ID3D11DeviceContext1** a_immediateContext) = 0;
		virtual HRESULT CreateDeferredContext1(std::uint32_t a_contextFlags, ID3D11DeviceContext1** a_deferredContext) = 0;
		virtual HRESULT CreateBlendState1(const D3D11_BLEND_DESC1* a_blendStateDesc, ID3D11BlendState1** a_blendState) = 0;
		virtual HRESULT CreateRasterizerState1(const D3D11_RASTERIZER_DESC1* a_rasterizerDesc, ID3D11RasterizerState1** a_rasterizerState) = 0;
		virtual HRESULT CreateDeviceContextState(std::uint32_t a_flags, const D3D_FEATURE_LEVEL* a_pFeatureLevels, std::uint32_t a_featureLevels, std::uint32_t a_sdkVersion, const IID& a_emulatedInterface, D3D_FEATURE_LEVEL* a_pFeatureLevel, ID3DDeviceContextState** a_contextState) = 0;
		virtual HRESULT OpenSharedResource1(HANDLE a_resourceHandle, const IID& a_returnedInterface, void** a_resource) = 0;
		virtual HRESULT OpenSharedResourceByName(const wchar_t* a_name, std::uint32_t a_desiredAccess, const IID& a_returnedInterface, void** a_resource) = 0;
	};

	struct __declspec(novtable, uuid("bb2c6faa-b5fb-4082-8e6b-388b8cfa90e1"))
		ID3D11DeviceContext1 : public ID3D11DeviceContext
	{
		virtual void CopySubresourceRegion1(ID3D11Resource* a_dstResource, std::uint32_t a_dstSubresource, std::uint32_t a_dstX, std::uint32_t a_dstY, std::uint32_t a_dstZ, ID3D11Resource* a_srcResource, std::uint32_t a_srcSubresource, const D3D11_BOX* a_srcBox, std::uint32_t a_copyFlags) = 0;
		virtual void UpdateSubresource1(ID3D11Resource* a_dstResource, std::uint32_t a_dstSubresource, const D3D11_BOX* a_dstBox, const void* a_srcData, std::uint32_t a_srcRowPitch, std::uint32_t a_srcDepthPitch, std::uint32_t a_copyFlags) = 0;
		virtual void DiscardResource(ID3D11Resource* a_resource) = 0;
		virtual void DiscardView(ID3D11View* a_resourceView) = 0;
		virtual void VSSetConstantBuffers1(std::uint32_t a_startSlot, std::uint32_t a_numBuffers, ID3D11Buffer* const* a_constantBuffers, const std::uint32_t* a_firstConstant, const std::uint32_t* a_numConstants) = 0;
		virtual void HSSetConstantBuffers1(std::uint32_t a_startSlot, std::uint32_t a_numBuffers, ID3D11Buffer* const* a_constantBuffers, const std::uint32_t* a_firstConstant, const std::uint32_t* a_numConstants) = 0;
		virtual void DSSetConstantBuffers1(std::uint32_t a_startSlot, std::uint32_t a_numBuffers, ID3D11Buffer* const* a_constantBuffers, const std::uint32_t* a_firstConstant, const std::uint32_t* a_numConstants) = 0;
		virtual void GSSetConstantBuffers1(std::uint32_t a_startSlot, std::uint32_t a_numBuffers, ID3D11Buffer* const* a_constantBuffers, const std::uint32_t* a_firstConstant, const std::uint32_t* a_numConstants) = 0;
		virtual void PSSetConstantBuffers1(std::uint32_t a_startSlot, std::uint32_t a_numBuffers, ID3D11Buffer* const* a_constantBuffers, const std::uint32_t* a_firstConstant, const std::uint32_t* a_numConstants) = 0;
		virtual void CSSetConstantBuffers1(std::uint32_t a_startSlot, std::uint32_t a_numBuffers, ID3D11Buffer* const* a_constantBuffers, const std::uint32_t* a_firstConstant, const std::uint32_t* a_numConstants) = 0;
		virtual void VSGetConstantBuffers1(std::uint32_t a_startSlot, std::uint32_t a_numBuffers, ID3D11Buffer** a_constantBuffers, std::uint32_t* a_firstConstant, std::uint32_t* a_numConstants) = 0;
		virtual void HSGetConstantBuffers1(std::uint32_t a_startSlot, std::uint32_t a_numBuffers, ID3D11Buffer** a_constantBuffers, std::uint32_t* a_firstConstant, std::uint32_t* a_numConstants) = 0;
		virtual void DSGetConstantBuffers1(std::uint32_t a_startSlot, std::uint32_t a_numBuffers, ID3D11Buffer** a_constantBuffers, std::uint32_t* a_firstConstant, std::uint32_t* a_numConstants) = 0;
		virtual void GSGetConstantBuffers1(std::uint32_t a_startSlot, std::uint32_t a_numBuffers, ID3D11Buffer** a_constantBuffers, std::uint32_t* a_firstConstant, std::uint32_t* a_numConstants) = 0;
		virtual void PSGetConstantBuffers1(std::uint32_t a_startSlot, std::uint32_t a_numBuffers, ID3D11Buffer** a_constantBuffers, std::uint32_t* a_firstConstant, std::uint32_t* a_numConstants) = 0;
		virtual void CSGetConstantBuffers1(std::uint32_t a_startSlot, std::uint32_t a_numBuffers, ID3D11Buffer** a_constantBuffers, std::uint32_t* a_firstConstant, std::uint32_t* a_numConstants) = 0;
		virtual void SwapDeviceContextState(ID3DDeviceContextState* a_state, ID3DDeviceContextState** a_previousState) = 0;
		virtual void ClearView(ID3D11View* a_view, const float a_color[4], const D3D11_RECT* a_rect, std::uint32_t a_numRects) = 0;
		virtual void DiscardView1(ID3D11View* a_resourceView, const D3D11_RECT* a_rects, std::uint32_t a_numRects) = 0;
	};

	struct __declspec(novtable, uuid("1217d7a6-5039-418c-b042-9cbe256afd6e"))
		ID3D11RasterizerState1 : public ID3D11RasterizerState
	{
		virtual void GetDesc1(D3D11_RASTERIZER_DESC1* a_desc) = 0;
	};

	struct __declspec(novtable, uuid("A7F026DA-A5F8-4487-A564-15E34357651E"))
		ID3D11VideoContext1 : public ID3D11VideoContext
	{
		virtual HRESULT SubmitDecoderBuffers1(ID3D11VideoDecoder* a_decoder, std::uint32_t a_numBuffers, const D3D11_VIDEO_DECODER_BUFFER_DESC1* a_bufferDesc) = 0;
		virtual HRESULT GetDataForNewHardwareKey(ID3D11CryptoSession* a_cryptoSession, std::uint32_t a_privateInputSize, const void* a_privateInputData, std::uint64_t* a_privateOutputData) = 0;
		virtual HRESULT CheckCryptoSessionStatus(ID3D11CryptoSession* a_cryptoSession, D3D11_CRYPTO_SESSION_STATUS* a_status) = 0;
		virtual HRESULT DecoderEnableDownsampling(ID3D11VideoDecoder* a_decoder, DXGI_COLOR_SPACE_TYPE a_inputColorSpace, const D3D11_VIDEO_SAMPLE_DESC* a_outputDesc, std::uint32_t a_referenceFrameCount) = 0;
		virtual HRESULT DecoderUpdateDownsampling(ID3D11VideoDecoder* a_decoder, const D3D11_VIDEO_SAMPLE_DESC* a_outputDesc) = 0;
		virtual void    VideoProcessorSetOutputColorSpace1(ID3D11VideoProcessor* a_videoProcessor, DXGI_COLOR_SPACE_TYPE a_colorSpace) = 0;
		virtual void    VideoProcessorSetOutputShaderUsage(ID3D11VideoProcessor* a_videoProcessor, BOOL a_shaderUsage) = 0;
		virtual void    VideoProcessorGetOutputColorSpace1(ID3D11VideoProcessor* a_videoProcessor, DXGI_COLOR_SPACE_TYPE* a_colorSpace) = 0;
		virtual void    VideoProcessorGetOutputShaderUsage(ID3D11VideoProcessor* a_videoProcessor, BOOL* a_shaderUsage) = 0;
		virtual void    VideoProcessorSetStreamColorSpace1(ID3D11VideoProcessor* a_videoProcessor, std::uint32_t a_streamIndex, DXGI_COLOR_SPACE_TYPE a_colorSpace) = 0;
		virtual void    VideoProcessorSetStreamMirror(ID3D11VideoProcessor* a_videoProcessor, std::uint32_t a_streamIndex, BOOL a_enable, BOOL a_flipHorizontal, BOOL a_flipVertical) = 0;
		virtual void    VideoProcessorGetStreamColorSpace1(ID3D11VideoProcessor* a_videoProcessor, std::uint32_t a_streamIndex, DXGI_COLOR_SPACE_TYPE* a_colorSpace) = 0;
		virtual void    VideoProcessorGetStreamMirror(ID3D11VideoProcessor* a_videoProcessor, std::uint32_t a_streamIndex, BOOL* a_enable, BOOL* a_flipHorizontal, BOOL* a_flipVertical) = 0;
		virtual HRESULT VideoProcessorGetBehaviorHints(ID3D11VideoProcessor* a_videoProcessor, std::uint32_t a_outputWidth, std::uint32_t a_outputHeight, DXGI_FORMAT a_outputFormat, std::uint32_t a_streamCount, const D3D11_VIDEO_PROCESSOR_STREAM_BEHAVIOR_HINT* a_streams, std::uint32_t* a_behaviorHints) = 0;
	};

	struct __declspec(novtable, uuid("29DA1D51-1321-4454-804B-F5FC9F861F0F"))
		ID3D11VideoDevice1 : public ID3D11VideoDevice
	{
		virtual HRESULT GetCryptoSessionPrivateDataSize(const GUID* a_cryptoType, const GUID* a_decoderProfile, const GUID* a_keyExchangeType, std::uint32_t* a_privateInputSize, std::uint32_t* a_privateOutputSize) = 0;
		virtual HRESULT GetVideoDecoderCaps(const GUID* a_decoderProfile, std::uint32_t a_sampleWidth, std::uint32_t a_sampleHeight, const DXGI_RATIONAL* a_frameRate, std::uint32_t a_bitRate, const GUID* a_cryptoType, std::uint32_t* a_decoderCaps) = 0;
		virtual HRESULT CheckVideoDecoderDownsampling(const D3D11_VIDEO_DECODER_DESC* a_inputDesc, DXGI_COLOR_SPACE_TYPE a_inputColorSpace, const D3D11_VIDEO_DECODER_CONFIG* a_inputConfig, const DXGI_RATIONAL* a_frameRate, const D3D11_VIDEO_SAMPLE_DESC* a_outputDesc, BOOL* a_supported, BOOL* a_realTimeHint) = 0;
		virtual HRESULT RecommendVideoDecoderDownsampleParameters(const D3D11_VIDEO_DECODER_DESC* a_inputDesc, DXGI_COLOR_SPACE_TYPE a_inputColorSpace, const D3D11_VIDEO_DECODER_CONFIG* a_inputConfig, const DXGI_RATIONAL* a_frameRate, D3D11_VIDEO_SAMPLE_DESC* a_recommendedOutputDesc) = 0;
	};

	struct __declspec(novtable, uuid("465217F2-5568-43CF-B5B9-F61D54531CA1"))
		ID3D11VideoProcessorEnumerator1 : public ID3D11VideoProcessorEnumerator
	{
		virtual HRESULT CheckVideoProcessorFormatConversion(DXGI_FORMAT a_inputFormat, DXGI_COLOR_SPACE_TYPE a_inputColorSpace, DXGI_FORMAT a_outputFormat, DXGI_COLOR_SPACE_TYPE a_outputColorSpace, BOOL* a_supported) = 0;
	};
}

namespace REX::W32
{
	inline constexpr IID IID_ID3DDeviceContextState{ 0x5C1E0D8A, 0x7C23, 0x48F9, { 0x8C, 0x59, 0xA9, 0x29, 0x58, 0xCE, 0xFF, 0x11 } };
	inline constexpr IID IID_ID3DUserDefinedAnnotation{ 0xB2DAAD8B, 0x03D4, 0x4DBF, { 0x95, 0xEB, 0x32, 0xAB, 0x4B, 0x63, 0xD0, 0xAB } };
	inline constexpr IID IID_ID3D11BlendState1{ 0xCC86FABE, 0xDA55, 0x401D, { 0x85, 0xE7, 0xE3, 0xC9, 0xDE, 0x28, 0x77, 0xE9 } };
	inline constexpr IID IID_ID3D11Device1{ 0xA04BFB29, 0x08EF, 0x43D6, { 0xA4, 0x9C, 0xA9, 0xBD, 0xBD, 0xCB, 0xE6, 0x86 } };
	inline constexpr IID IID_ID3D11DeviceContext1{ 0xBB2C6FAA, 0xB5FB, 0x4082, { 0x8E, 0x6B, 0x38, 0x8B, 0x8C, 0xFA, 0x90, 0xE1 } };
	inline constexpr IID IID_ID3D11RasterizerState1{ 0x1217D7A6, 0x5039, 0x418C, { 0xB0, 0x42, 0x9C, 0xBE, 0x25, 0x6A, 0xFD, 0x6E } };
	inline constexpr IID IID_ID3D11VideoContext1{ 0xA7F026DA, 0xA5F8, 0x4487, { 0xA5, 0x64, 0x15, 0xE3, 0x43, 0x57, 0x65, 0x1E } };
	inline constexpr IID IID_ID3D11VideoDevice1{ 0x29DA1D51, 0x1321, 0x4454, { 0x80, 0x4B, 0xF5, 0xFC, 0x9F, 0x86, 0x1F, 0x0F } };
	inline constexpr IID IID_ID3D11VideoProcessorEnumerator1{ 0x465217F2, 0x5568, 0x43CF, { 0xB5, 0xB9, 0xF6, 0x1D, 0x54, 0x53, 0x1C, 0xA1 } };
}
