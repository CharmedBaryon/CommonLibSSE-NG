#pragma once

#include "RE\D\DepthStencilDepthModes.h"
#include "RE\S\State.h"
#include "RE\T\TextureAddressModes.h"
#include "RE\T\TextureFilterModes.h"

#include <d3d11.h>

// see https://github.com/Nukem9/SkyrimSETest/blob/master/skyrim64_test/src/patches/TES/BSGraphics/BSGraphicsRenderer.h
namespace RE
{
	namespace BSGraphics
	{
		//
		// Renderer shadow state settings
		//
		enum ShaderFlags : uint32_t
		{
			DIRTY_RENDERTARGET = 0x1,
			DIRTY_VIEWPORT = 0x2,
			DIRTY_DEPTH_MODE = 0x4,
			DIRTY_DEPTH_STENCILREF_MODE = 0x8,
			DIRTY_UNKNOWN1 = 0x10,
			DIRTY_RASTER_CULL_MODE = 0x20,
			DIRTY_RASTER_DEPTH_BIAS = 0x40,
			DIRTY_ALPHA_BLEND = 0x80,
			DIRTY_ALPHA_TEST_REF = 0x100,
			DIRTY_ALPHA_ENABLE_TEST = 0x200,
			DIRTY_VERTEX_DESC = 0x400,
			DIRTY_PRIMITIVE_TOPO = 0x800,
			DIRTY_UNKNOWN2 = 0x1000,
			DIRTY_VRPREVIEW = 0x2000,  // VR
		};

		enum ClearDepthStencilTarget
		{
			CLEAR_DEPTH_STENCIL_TARGET_DEPTH = 1,
			CLEAR_DEPTH_STENCIL_TARGET_STENCIL = 2,
			CLEAR_DEPTH_STENCIL_TARGET_ALL = 3,
		};

		enum SetRenderTargetMode : uint32_t
		{
			SRTM_CLEAR = 0,
			SRTM_CLEAR_DEPTH = 1,
			SRTM_CLEAR_STENCIL = 2,
			SRTM_RESTORE = 3,
			SRTM_NO_CLEAR = 4,
			SRTM_FORCE_COPY_RESTORE = 5,
			SRTM_INIT = 6,
		};

		enum DepthStencilStencilMode
		{
			DEPTH_STENCIL_STENCIL_MODE_DISABLED = 0,

			DEPTH_STENCIL_STENCIL_MODE_DEFAULT = DEPTH_STENCIL_STENCIL_MODE_DISABLED,  // Used for BSShader::RestoreX
		};

		enum RasterStateCullMode
		{
			RASTER_STATE_CULL_MODE_BACK = 1,

			RASTER_STATE_CULL_MODE_DEFAULT = RASTER_STATE_CULL_MODE_BACK,  // Used for BSShader::RestoreX
		};

		template <typename T, uint32_t size = 1>
		class EYE_POSITION
		{
		public:
			/**
         * Get the eye of type T
		 *
         * @param a_index The index of the eye. By default it is set to 0. Default in SSE or Left in VR. 1 is Right.
		 * @throws std::out_of_range if index is greater than or equal to size.
         */
			T getEye(uint32_t a_index = 0)
			{
				if (a_index >= size)
					throw std::out_of_range("Index for eye is out of range");
				return eye[a_index];
			}

		private:
			T eye[size];  // default or left eye is index 0, right eye is index 1, should use getEye
		};

		class RendererShadowState
		{
		public:
#pragma warning(push)
#pragma warning(disable: 4324)  // ignore warning about padded due to alignment from DirectX datatypes (e.g., XMVECTOR, XMMATRIX).
			struct FLAT_RUNTIME_DATA
			{
#define FLAT_RUNTIME_DATA_CONTENT                                                                                                                                     \
	stl::enumeration<ShaderFlags, uint32_t>        stateUpdateFlags;                                            /* 00 Flags +0x0  0xFFFFFFFF; global state updates */ \
	uint32_t                                       PSResourceModifiedBits;                                      /* 04 Flags +0x4  0xFFFF */                           \
	uint32_t                                       PSSamplerModifiedBits;                                       /* 08 Flags +0x8  0xFFFF */                           \
	uint32_t                                       CSResourceModifiedBits;                                      /* 0c Flags +0xC  0xFFFF */                           \
	uint32_t                                       CSSamplerModifiedBits;                                       /* 10 Flags +0x10 0xFFFF */                           \
	uint32_t                                       CSUAVModifiedBits;                                           /* 14 Flags +0x14 0xFF */                             \
	RENDER_TARGET                                  renderTargets[D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT];       /* 18, VR 20 */                                       \
	uint32_t                                       depthStencil;                                                /* 38, VR 40 - Index */                               \
	uint32_t                                       depthStencilSlice;                                           /* 3c, VR 44 Index */                                 \
	uint32_t                                       cubeMapRenderTarget;                                         /* 40, VR 48 = Index */                               \
	uint32_t                                       cubeMapRenderTargetView;                                     /* 44, VR 4c Index */                                 \
	SetRenderTargetMode                            setRenderTargetMode[D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT]; /* 48, VR 50 */                                       \
	SetRenderTargetMode                            setDepthStencilMode;                                         /* 68, VR 70 */                                       \
	SetRenderTargetMode                            setCubeMapRenderTargetMode;                                  /* 6c, VR 74 */                                       \
	D3D11_VIEWPORT                                 viewPort;                                                    /* 70, VR 78 */                                       \
	DepthStencilDepthMode                          depthStencilDepthMode;                                       /* 88, VR 90 */                                       \
	DepthStencilDepthMode                          depthStencilDepthModePrevious;                               /* 8c, VR 94 - also some kind of mode */              \
	uint32_t                                       depthStencilStencilMode;                                     /* 90, VR 98 */                                       \
	uint32_t                                       stencilRef;                                                  /* 94, VR 9c */                                       \
	uint32_t                                       rasterStateFillMode;                                         /* 98, VR a0 */                                       \
	uint32_t                                       rasterStateCullMode;                                         /* 9c, VR a4 */                                       \
	uint32_t                                       rasterStateDepthBiasMode;                                    /* a0, VR a8 */                                       \
	uint32_t                                       rasterStateScissorMode;                                      /* a4, VR ac */                                       \
	uint32_t                                       alphaBlendMode;                                              /* a8, VR b0 */                                       \
	uint32_t                                       alphaBlendAlphaToCoverage;                                   /* ac, VR b4 */                                       \
	uint32_t                                       alphaBlendWriteMode;                                         /* b0, VR b8 */                                       \
	bool                                           alphaTestEnabled;                                            /* b4, VR BC */                                       \
	float                                          alphaTestRef;                                                /* b8, VR C0 */                                       \
	stl::enumeration<TextureAddressMode, uint32_t> PSTextureAddressMode[16];                                    /* bc, VR c4 */                                       \
	stl::enumeration<TextureFilterMode, uint32_t>  PSTextureFilterMode[16];                                     /* fc, VR 104 */                                      \
	ID3D11ShaderResourceView*                      PSTexture[16];                                               /* 140, VR 148 */                                     \
	stl::enumeration<TextureAddressMode, uint32_t> CSTextureAddressMode[16];                                    /* 1c0, VR 1c8 */                                     \
	stl::enumeration<TextureFilterMode, uint32_t>  CSTextureFilterMode[16];                                     /* 200, VR 208 */                                     \
	ID3D11ShaderResourceView*                      CSTexture[16];                                               /* 240, VR 248 */                                     \
	uint32_t                                       CSTextureMinLodMode[16];                                     /* 2c0, VR 2C8 */                                     \
	ID3D11UnorderedAccessView*                     CSUAV[8];                                                    /* 300, VR 308 */                                     \
	uint64_t                                       vertexDesc;                                                  /* 340, VR 388 only? */                               \
	VertexShader*                                  currentVertexShader;                                         /* 348, VR 390 */                                     \
	PixelShader*                                   currentPixelShader;                                          /* 350, VR 398 */                                     \
	D3D11_PRIMITIVE_TOPOLOGY                       topology;                                                    /* 358, VR 3A0 */                                     \
	EYE_POSITION<NiPoint3>                         posAdjust;                                                   /* 35c, VR 3A4 */                                     \
	EYE_POSITION<NiPoint3>                         previousPosAdjust;                                           /* 368, VR 3BC */                                     \
	EYE_POSITION<ViewData>                         cameraData;                                                  /* 380, VR 3E0 - size of each is 250 */               \
	uint32_t                                       alphaBlendModeExtra;                                         /* 5d0, VR 88c */                                     \
	float                                          unk5c8;                                                      /* 5d4, VR 884 */                                     \
	float                                          unk5cc;                                                      /* 5d8 VR 888 */                                      \
	uint32_t                                       unk5d0;                                                      /* 5d0 VR 88c */
                FLAT_RUNTIME_DATA_CONTENT;
			};
			static_assert(sizeof(FLAT_RUNTIME_DATA) == 0x5e0);
			static_assert(offsetof(FLAT_RUNTIME_DATA, renderTargets) == 0x18);
			static_assert(offsetof(FLAT_RUNTIME_DATA, depthStencil) == 0x38);
			static_assert(offsetof(FLAT_RUNTIME_DATA, depthStencilSlice) == 0x3c);
			static_assert(offsetof(FLAT_RUNTIME_DATA, cubeMapRenderTarget) == 0x40);
			static_assert(offsetof(FLAT_RUNTIME_DATA, setRenderTargetMode) == 0x48);
			static_assert(offsetof(FLAT_RUNTIME_DATA, setDepthStencilMode) == 0x68);
			static_assert(offsetof(FLAT_RUNTIME_DATA, setCubeMapRenderTargetMode) == 0x6c);
			static_assert(offsetof(FLAT_RUNTIME_DATA, viewPort) == 0x70);
			static_assert(offsetof(FLAT_RUNTIME_DATA, depthStencilDepthMode) == 0x88);
			static_assert(offsetof(FLAT_RUNTIME_DATA, depthStencilDepthModePrevious) == 0x8c);
			static_assert(offsetof(FLAT_RUNTIME_DATA, depthStencilStencilMode) == 0x90);
			static_assert(offsetof(FLAT_RUNTIME_DATA, alphaTestEnabled) == 0xb4);
			static_assert(offsetof(FLAT_RUNTIME_DATA, alphaTestRef) == 0xb8);
			static_assert(offsetof(FLAT_RUNTIME_DATA, PSTextureAddressMode) == 0xbc);
			static_assert(offsetof(FLAT_RUNTIME_DATA, PSTextureFilterMode) == 0xfc);
			static_assert(offsetof(FLAT_RUNTIME_DATA, PSTexture) == 0x140);
			static_assert(offsetof(FLAT_RUNTIME_DATA, CSTextureAddressMode) == 0x1c0);
			static_assert(offsetof(FLAT_RUNTIME_DATA, CSTextureFilterMode) == 0x200);
			static_assert(offsetof(FLAT_RUNTIME_DATA, CSTexture) == 0x240);
			static_assert(offsetof(FLAT_RUNTIME_DATA, CSTextureMinLodMode) == 0x2c0);
			static_assert(offsetof(FLAT_RUNTIME_DATA, CSUAV) == 0x300);
			static_assert(offsetof(FLAT_RUNTIME_DATA, vertexDesc) == 0x340);
			static_assert(offsetof(FLAT_RUNTIME_DATA, currentVertexShader) == 0x348);
			static_assert(offsetof(FLAT_RUNTIME_DATA, currentPixelShader) == 0x350);
			static_assert(offsetof(FLAT_RUNTIME_DATA, topology) == 0x358);
			static_assert(offsetof(FLAT_RUNTIME_DATA, posAdjust) == 0x35c);
			static_assert(offsetof(FLAT_RUNTIME_DATA, previousPosAdjust) == 0x368);
			static_assert(offsetof(FLAT_RUNTIME_DATA, cameraData) == 0x380);
#pragma warning(pop)

			struct VR_RUNTIME_DATA
			{
#define VR_RUNTIME_DATA_CONTENT                                                                                                                                       \
	stl::enumeration<ShaderFlags, uint32_t>        stateUpdateFlags;                                            /* 00 Flags +0x0  0xFFFFFFFF; global state updates */ \
	uint32_t                                       PSResourceModifiedBits;                                      /* 04 Flags +0x4  0xFFFF */                           \
	uint32_t                                       PSSamplerModifiedBits;                                       /* 08 Flags +0x8  0xFFFF */                           \
	uint32_t                                       CSResourceModifiedBits;                                      /* 0c Flags +0xC  0xFFFF */                           \
	uint32_t                                       CSSamplerModifiedBits;                                       /* 10 Flags +0x10 0xFFFF */                           \
	uint32_t                                       CSUAVModifiedBits;                                           /* 14 Flags +0x14 0xFF */                             \
	uint32_t                                       OMUAVModifiedBits;                                           /* 18 Flags +0x18 0xFF VR Only  */                    \
	uint32_t                                       SRVModifiedBits;                                             /* 1c Flags +0x1C 0xFF VR Only  */                    \
	RENDER_TARGET                                  renderTargets[D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT];       /* 18, VR 20 */                                       \
	uint32_t                                       depthStencil;                                                /* 38, VR 40 - Index */                               \
	uint32_t                                       depthStencilSlice;                                           /* 3c, VR 44 Index */                                 \
	uint32_t                                       cubeMapRenderTarget;                                         /* 40, VR 48 = Index */                               \
	uint32_t                                       cubeMapRenderTargetView;                                     /* 44, VR 4c Index */                                 \
	SetRenderTargetMode                            setRenderTargetMode[D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT]; /* 48, VR 50 */                                       \
	SetRenderTargetMode                            setDepthStencilMode;                                         /* 68, VR 70 */                                       \
	SetRenderTargetMode                            setCubeMapRenderTargetMode;                                  /* 6c, VR 74 */                                       \
	D3D11_VIEWPORT                                 viewPort;                                                    /* 70, VR 78 */                                       \
	DepthStencilDepthMode                          depthStencilDepthMode;                                       /* 88, VR 90 */                                       \
	DepthStencilDepthMode                          depthStencilDepthModePrevious;                               /* 8c, VR 94 - also some kind of mode */              \
	uint32_t                                       depthStencilStencilMode;                                     /* 90, VR 98 */                                       \
	uint32_t                                       stencilRef;                                                  /* 94, VR 9c */                                       \
	uint32_t                                       rasterStateFillMode;                                         /* 98, VR a0 */                                       \
	uint32_t                                       rasterStateCullMode;                                         /* 9c, VR a4 */                                       \
	uint32_t                                       rasterStateDepthBiasMode;                                    /* a0, VR a8 */                                       \
	uint32_t                                       rasterStateScissorMode;                                      /* a4, VR ac */                                       \
	uint32_t                                       alphaBlendMode;                                              /* a8, VR b0 */                                       \
	uint32_t                                       alphaBlendAlphaToCoverage;                                   /* ac, VR b4 */                                       \
	uint32_t                                       alphaBlendWriteMode;                                         /* b0, VR b8 */                                       \
	bool                                           alphaTestEnabled;                                            /* b4, VR BC */                                       \
	float                                          alphaTestRef;                                                /* b8, VR C0 */                                       \
	stl::enumeration<TextureAddressMode, uint32_t> PSTextureAddressMode[16];                                    /* bc, VR c4 */                                       \
	stl::enumeration<TextureFilterMode, uint32_t>  PSTextureFilterMode[16];                                     /* fc, VR 104 */                                      \
	ID3D11ShaderResourceView*                      PSTexture[16];                                               /* 140, VR 148 */                                     \
	stl::enumeration<TextureAddressMode, uint32_t> CSTextureAddressMode[16];                                    /* 1c0, VR 1c8 */                                     \
	stl::enumeration<TextureFilterMode, uint32_t>  CSTextureFilterMode[16];                                     /* 200, VR 208 */                                     \
	ID3D11ShaderResourceView*                      CSTexture[16];                                               /* 240, VR 248 */                                     \
	uint32_t                                       CSTextureMinLodMode[16];                                     /* 2c0, VR 2C8 */                                     \
	ID3D11UnorderedAccessView*                     CSUAV[8];                                                    /* 300, VR 308 */                                     \
	uint8_t                                        unk348[0x388 - 0x348];                                       /* VR 348 */                                          \
	uint64_t                                       vertexDesc;                                                  /* 340, VR 388 only? */                               \
	VertexShader*                                  currentVertexShader;                                         /* 348, VR 390 */                                     \
	PixelShader*                                   currentPixelShader;                                          /* 350, VR 398 */                                     \
	D3D11_PRIMITIVE_TOPOLOGY                       topology;                                                    /* 358, VR 3A0 */                                     \
	EYE_POSITION<NiPoint3, 2>                      posAdjust;                                                   /* 35c, VR 3A4 */                                     \
	EYE_POSITION<NiPoint3, 2>                      previousPosAdjust;                                           /* 368, VR 3BC */                                     \
	uint8_t                                        unk3d4[0x3e0 - 0x3d4];                                       /* 3d4, VR only pad */                                \
	EYE_POSITION<ViewData, 2>                      cameraData;                                                  /* 380, VR 3E0 - size of each is 250 */               \
	uint32_t                                       unk880;                                                      /* 5d0, VR 880 */                                     \
	float                                          unk884;                                                      /* 5d4, VR 884 */                                     \
	float                                          unk888;                                                      /* 5d8 VR 888 */                                      \
	uint32_t                                       alphaBlendModeExtra;                                         /* 5dc VR 88c */                                      \
	ID3D11Buffer*                                  VSConstantBuffers[12];                                       /* VR 890 only */                                     \
	ID3D11Buffer*                                  PSConstantBuffers[12];                                       /* VR 8F0 only */
                VR_RUNTIME_DATA_CONTENT;
			};

			// members
#ifndef ENABLE_SKYRIM_VR
			FLAT_RUNTIME_DATA_CONTENT;  // 0
#elif defined(EXCLUSIVE_SKYRIM_VR)
			VR_RUNTIME_DATA_CONTENT;  // 0
#endif

			[[nodiscard]] inline FLAT_RUNTIME_DATA& GetRuntimeData() noexcept
			{
				return REL::RelocateMember<FLAT_RUNTIME_DATA>(this, 0, 0);
			}

			[[nodiscard]] inline const FLAT_RUNTIME_DATA& GetRuntimeData() const noexcept
			{
				return REL::RelocateMember<FLAT_RUNTIME_DATA>(this, 0, 0);
			}

			[[nodiscard]] inline VR_RUNTIME_DATA& GetVRRuntimeData() noexcept
			{
				return REL::RelocateMember<VR_RUNTIME_DATA>(this, 0, 0);
			}

			[[nodiscard]] inline const VR_RUNTIME_DATA& GetVRRuntimeData() const noexcept
			{
				return REL::RelocateMember<VR_RUNTIME_DATA>(this, 0, 0);
			}

			static RendererShadowState* GetSingleton()
			{
				static RendererShadowState* g_RendererShadowState = (RendererShadowState*)RELOCATION_ID(524773, 388819).address();
				return g_RendererShadowState;
			}

			void SetPSTexture(size_t textureIndex, BSGraphics::Texture* newTexture)
			{
				GET_CROSSVR_RUNTIME_MEMBER(PSTexture)
				GET_CROSSVR_RUNTIME_MEMBER(PSResourceModifiedBits)
				ID3D11ShaderResourceView* resourceView = newTexture ? newTexture->resourceView : nullptr;
				if (PSTexture[textureIndex] != resourceView) {
					PSTexture[textureIndex] = resourceView;
					PSResourceModifiedBits |= (1 << textureIndex);
				}
			}

			void SetPSTexture(size_t textureIndex, const BSGraphics::RenderTargetData& newTexture)
			{
				GET_CROSSVR_RUNTIME_MEMBER(PSTexture)
				GET_CROSSVR_RUNTIME_MEMBER(PSResourceModifiedBits)
				ID3D11ShaderResourceView* resourceView = newTexture.SRV;
				if (PSTexture[textureIndex] != resourceView) {
					PSTexture[textureIndex] = resourceView;
					PSResourceModifiedBits |= (1 << textureIndex);
				}
			}

			void SetPSTextureAddressMode(size_t textureIndex, TextureAddressMode newAddressMode)
			{
				GET_CROSSVR_RUNTIME_MEMBER(PSTextureAddressMode)
				GET_CROSSVR_RUNTIME_MEMBER(PSSamplerModifiedBits)
				if (PSTextureAddressMode[textureIndex] != newAddressMode) {
					PSTextureAddressMode[textureIndex] = newAddressMode;
					PSSamplerModifiedBits |= (1 << textureIndex);
				}
			}

			void SetPSTextureFilterMode(size_t textureIndex, TextureFilterMode newFilterMode)
			{
				GET_CROSSVR_RUNTIME_MEMBER(PSTextureFilterMode)
				GET_CROSSVR_RUNTIME_MEMBER(PSSamplerModifiedBits)
				if (PSTextureFilterMode[textureIndex] != newFilterMode) {
					PSTextureFilterMode[textureIndex] = newFilterMode;
					PSSamplerModifiedBits |= (1 << textureIndex);
				}
			}

			void SetVertexShader(VertexShader* shader)
			{
				GET_CROSSVR_RUNTIME_MEMBER(stateUpdateFlags)
				GET_CROSSVR_RUNTIME_MEMBER(currentVertexShader)
				stateUpdateFlags |= ShaderFlags::DIRTY_VERTEX_DESC;
				currentVertexShader = shader;
				if (shader != nullptr) {
					Renderer::GetSingleton()->GetRuntimeData().context->VSSetShader(shader->shader, nullptr, 0);
				}
			}

			void SetPixelShader(PixelShader* shader)
			{
				GET_CROSSVR_RUNTIME_MEMBER(currentPixelShader)
				currentPixelShader = shader;
				if (shader != nullptr) {
					Renderer::GetSingleton()->GetRuntimeData().context->PSSetShader(shader->shader, nullptr, 0);
				}
			}

			ConstantGroup& GetVSConstantGroup(ConstantGroupLevel level)
			{
				GET_CROSSVR_RUNTIME_MEMBER(currentVertexShader)
				return currentVertexShader->constantBuffers[static_cast<size_t>(level)];
			}

			ConstantGroup& GetPSConstantGroup(ConstantGroupLevel level)
			{
				GET_CROSSVR_RUNTIME_MEMBER(currentPixelShader)
				return currentPixelShader->constantBuffers[static_cast<size_t>(level)];
			}

			template <typename ValueType>
			void SetVSConstant(const ValueType& value, ConstantGroupLevel level, size_t index)
			{
				GET_CROSSVR_RUNTIME_MEMBER(currentVertexShader)
				const int8_t offset = currentVertexShader->constantTable[index];
				*reinterpret_cast<ValueType*>((reinterpret_cast<float*>(currentVertexShader->constantBuffers[static_cast<size_t>(level)].data) + offset)) = value;
			}

			template <typename ValueType>
			void SetPSConstant(const ValueType& value, ConstantGroupLevel level, size_t index)
			{
				GET_CROSSVR_RUNTIME_MEMBER(currentPixelShader)
				const int8_t offset = currentPixelShader->constantTable[index];
				*reinterpret_cast<ValueType*>((reinterpret_cast<float*>(currentPixelShader->constantBuffers[static_cast<size_t>(level)].data) + offset)) = value;
			}
		};
#if defined(EXCLUSIVE_SKYRIM_FLAT)
		static_assert(sizeof(RendererShadowState) == 0x5e0);
		static_assert(offsetof(RendererShadowState, renderTargets) == 0x18);
		static_assert(offsetof(RendererShadowState, depthStencil) == 0x38);
		static_assert(offsetof(RendererShadowState, depthStencilSlice) == 0x3c);
		static_assert(offsetof(RendererShadowState, cubeMapRenderTarget) == 0x40);
		static_assert(offsetof(RendererShadowState, setRenderTargetMode) == 0x48);
		static_assert(offsetof(RendererShadowState, setDepthStencilMode) == 0x68);
		static_assert(offsetof(RendererShadowState, setCubeMapRenderTargetMode) == 0x6c);
		static_assert(offsetof(RendererShadowState, viewPort) == 0x70);
		static_assert(offsetof(RendererShadowState, depthStencilDepthMode) == 0x88);
		static_assert(offsetof(RendererShadowState, depthStencilDepthModePrevious) == 0x8c);
		static_assert(offsetof(RendererShadowState, depthStencilStencilMode) == 0x90);
		static_assert(offsetof(RendererShadowState, alphaTestEnabled) == 0xb4);
		static_assert(offsetof(RendererShadowState, alphaTestRef) == 0xb8);
		static_assert(offsetof(RendererShadowState, PSTextureAddressMode) == 0xbc);
		static_assert(offsetof(RendererShadowState, PSTextureFilterMode) == 0xfc);
		static_assert(offsetof(RendererShadowState, PSTexture) == 0x140);
		static_assert(offsetof(RendererShadowState, CSTextureAddressMode) == 0x1c0);
		static_assert(offsetof(RendererShadowState, CSTextureFilterMode) == 0x200);
		static_assert(offsetof(RendererShadowState, CSTexture) == 0x240);
		static_assert(offsetof(RendererShadowState, CSTextureMinLodMode) == 0x2c0);
		static_assert(offsetof(RendererShadowState, CSUAV) == 0x300);
		static_assert(offsetof(RendererShadowState, vertexDesc) == 0x340);
		static_assert(offsetof(RendererShadowState, currentVertexShader) == 0x348);
		static_assert(offsetof(RendererShadowState, currentPixelShader) == 0x350);
		static_assert(offsetof(RendererShadowState, topology) == 0x358);
		static_assert(offsetof(RendererShadowState, posAdjust) == 0x35c);
		static_assert(offsetof(RendererShadowState, previousPosAdjust) == 0x368);
		static_assert(offsetof(RendererShadowState, cameraData) == 0x380);
#elif defined(EXCLUSIVE_SKYRIM_VR)
		static_assert(sizeof(RendererShadowState) == 0x950);
		static_assert(offsetof(RendererShadowState, OMUAVModifiedBits) == 0x18);
		static_assert(offsetof(RendererShadowState, renderTargets) == 0x20);
		static_assert(offsetof(RendererShadowState, depthStencil) == 0x40);
		static_assert(offsetof(RendererShadowState, depthStencilSlice) == 0x44);
		static_assert(offsetof(RendererShadowState, cubeMapRenderTarget) == 0x48);
		static_assert(offsetof(RendererShadowState, setRenderTargetMode) == 0x50);
		static_assert(offsetof(RendererShadowState, setDepthStencilMode) == 0x70);
		static_assert(offsetof(RendererShadowState, setCubeMapRenderTargetMode) == 0x74);
		static_assert(offsetof(RendererShadowState, viewPort) == 0x78);
		static_assert(offsetof(RendererShadowState, depthStencilDepthMode) == 0x90);
		static_assert(offsetof(RendererShadowState, depthStencilDepthModePrevious) == 0x94);
		static_assert(offsetof(RendererShadowState, depthStencilStencilMode) == 0x98);
		static_assert(offsetof(RendererShadowState, alphaTestEnabled) == 0xbc);
		static_assert(offsetof(RendererShadowState, alphaTestRef) == 0xc0);
		static_assert(offsetof(RendererShadowState, PSTextureAddressMode) == 0xc4);
		static_assert(offsetof(RendererShadowState, PSTextureFilterMode) == 0x104);
		static_assert(offsetof(RendererShadowState, PSTexture) == 0x148);
		static_assert(offsetof(RendererShadowState, CSTextureAddressMode) == 0x1c8);
		static_assert(offsetof(RendererShadowState, CSTextureFilterMode) == 0x208);
		static_assert(offsetof(RendererShadowState, CSTexture) == 0x248);
		static_assert(offsetof(RendererShadowState, CSTextureMinLodMode) == 0x2c8);
		static_assert(offsetof(RendererShadowState, CSUAV) == 0x308);
		static_assert(offsetof(RendererShadowState, vertexDesc) == 0x388);
		static_assert(offsetof(RendererShadowState, currentVertexShader) == 0x390);
		static_assert(offsetof(RendererShadowState, currentPixelShader) == 0x398);
		static_assert(offsetof(RendererShadowState, topology) == 0x3a0);
		static_assert(offsetof(RendererShadowState, posAdjust) == 0x3a4);
		static_assert(offsetof(RendererShadowState, previousPosAdjust) == 0x3bc);
		static_assert(offsetof(RendererShadowState, cameraData) == 0x3e0);
		static_assert(offsetof(RendererShadowState, VSConstantBuffers) == 0x890);
		static_assert(offsetof(RendererShadowState, PSConstantBuffers) == 0x8f0);
#else
		static_assert(sizeof(RendererShadowState) == 1);
#endif
	}
}
#undef FLAT_RUNTIME_DATA_CONTENT
#undef VR_RUNTIME_DATA_CONTENT
