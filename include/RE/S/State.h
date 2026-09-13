#pragma once

#include "RE/B/BSTArray.h"
#include "RE/N/NiCamera.h"
#include "RE/N/NiSmartPointer.h"
#include "RE/N/NiSourceTexture.h"
#include "REL/RuntimeDataAccessors.h"
#include "SKSE/Version.h"
#include <SimpleMath.h>
using namespace DirectX::SimpleMath;

namespace RE
{
	class NiCamera;

	namespace BSGraphics
	{
		//WARNING: Structs containing ViewData appear to break when returned via RelocateMember due to incorrect offsets.
		struct alignas(16) ViewData
		{
			Vector4  viewUp;                            // 00
			Vector4  viewRight;                         // 10
			Vector4  viewForward;                       // 20
			Matrix   viewMat;                           // 30
			Matrix   projMat;                           // 70
			Matrix   viewProjMat;                       // B0
			Matrix   unknownMat1;                       // F0 - all 0?
			Matrix   viewProjMatrixUnjittered;          // 130
			Matrix   previousViewProjMatrixUnjittered;  // 170
			Matrix   projMatrixUnjittered;              // 1B0
			Matrix   unknownMat2;                       // 1F0 - all 0?
			float    viewPort[4];                       // 230 - NiRect<float> { left = 0, right = 1, top = 1, bottom = 0 }
			NiPoint2 viewDepthRange;                    // 240
			char     _pad0[0x8];                        // 248
		};
		static_assert(sizeof(ViewData) == 0x250);
		static_assert(offsetof(ViewData, viewUp) == 0);
		static_assert(offsetof(ViewData, viewRight) == 0x10);
		static_assert(offsetof(ViewData, viewForward) == 0x20);
		static_assert(offsetof(ViewData, viewMat) == 0x30);
		static_assert(offsetof(ViewData, projMat) == 0x70);
		static_assert(offsetof(ViewData, viewProjMat) == 0xb0);
		static_assert(offsetof(ViewData, unknownMat1) == 0xf0);
		static_assert(offsetof(ViewData, viewProjMatrixUnjittered) == 0x130);
		static_assert(offsetof(ViewData, previousViewProjMatrixUnjittered) == 0x170);
		static_assert(offsetof(ViewData, projMatrixUnjittered) == 0x1b0);
		static_assert(offsetof(ViewData, unknownMat2) == 0x1f0);
		static_assert(offsetof(ViewData, viewPort) == 0x230);
		static_assert(offsetof(ViewData, viewDepthRange) == 0x240);

		// NOTE: alignas(16) on ViewData causes padding when embedded in structs.
		// This affects FLATRIM builds where ViewData is embedded directly.
#pragma warning(push)
#pragma warning(disable: 4324)  // structure was padded due to alignment specifier
		struct CAMERASTATE_RUNTIME_DATA
		{
#if !defined(ENABLE_SKYRIM_VR)  // Non-VR
#	define CAMERASTATE_RUNTIME_DATA_CONTENT                                                               \
		ViewData camViewData;       /* 08 VR is BSTArray, Each array has 2 elements (one for each eye?) */ \
		NiPoint3 posAdjust;         /* 20 */                                                               \
		NiPoint3 currentPosAdjust;  /* 38 */                                                               \
		NiPoint3 previousPosAdjust; /* 50 */
#elif defined(EXCLUSIVE_SKYRIM_VR)  // VR
#	define CAMERASTATE_RUNTIME_DATA_CONTENT                                                                         \
		BSTArray<ViewData> camViewData;       /* 08 VR is BSTArray, Each array has 2 elements (one for each eye?) */ \
		BSTArray<NiPoint3> posAdjust;         /* 20 */                                                               \
		BSTArray<NiPoint3> currentPosAdjust;  /* 38 */                                                               \
		BSTArray<NiPoint3> previousPosAdjust; /* 50 */
#else
#	define CAMERASTATE_RUNTIME_DATA_CONTENT
#endif
			//members
			CAMERASTATE_RUNTIME_DATA_CONTENT;  // 08
			bool     useJitter;                /* 68 */
			uint32_t numData;                  /* 6c */
		};

		class CameraStateData
		{
		public:
			[[nodiscard]] CAMERASTATE_RUNTIME_DATA& GetCameraStateRuntimeData() noexcept
			{
				return REL::RelocateMember<CAMERASTATE_RUNTIME_DATA>(this, 0x8, 0x8);
			}

			[[nodiscard]] inline const CAMERASTATE_RUNTIME_DATA& GetCameraStateRuntimeData() const noexcept
			{
				return REL::RelocateMember<CAMERASTATE_RUNTIME_DATA>(this, 0x8, 0x8);
			}

			// members
			NiCamera* referenceCamera;         /* 00 */
			CAMERASTATE_RUNTIME_DATA_CONTENT;  // 08
		};
#pragma warning(pop)
#if defined(EXCLUSIVE_SKYRIM_SE) || defined(EXCLUSIVE_SKYRIM_AE)  // SE/AE only
		static_assert(sizeof(CameraStateData) == 0x290);
#elif defined(EXCLUSIVE_SKYRIM_VR)  // VR only
		static_assert(sizeof(CameraStateData) == 0x68);
#elif defined(SKYRIM_CROSS_VR)      // Multi-runtime (ALL)
		static_assert(sizeof(CameraStateData) == 0x8);
#endif
		// FLATRIM: Size check skipped - alignas(16) padding causes indeterminate size
		class State
		{
		public:
			struct RUNTIME_DATA
			{
#if defined(EXCLUSIVE_SKYRIM_VR)  // VR
#	define RUNTIME_DATA_CONTENT                                                                                               \
		uint32_t                   eyeIndex;                             /* 058 -- current render eye (0 = left, 1 = right) */ \
		NiPointer<NiSourceTexture> defaultTextureBlack;                  /* SE 058, AE,VR 060 - "BSShader_DefHeightMap"*/      \
		NiPointer<NiSourceTexture> defaultTextureWhite;                  /* SE 060, AE,VR 068 */                               \
		NiPointer<NiSourceTexture> defaultTextureGrey;                   /* SE 068, AE,VR 070 */                               \
		NiPointer<NiSourceTexture> defaultHeightMap;                     /* SE 070, AE,VR 078 */                               \
		NiPointer<NiSourceTexture> defaultReflectionCubeMap;             /* SE 078, AE,VR 080 */                               \
		NiPointer<NiSourceTexture> defaultFaceDetailMap;                 /* SE 080, AE,VR 088 */                               \
		NiPointer<NiSourceTexture> defaultTexEffectMap;                  /* SE 088, AE,VR 090 */                               \
		NiPointer<NiSourceTexture> defaultTextureNormalMap;              /* SE 090, AE,VR 098 */                               \
		NiPointer<NiSourceTexture> defaultTextureDitherNoiseMap;         /* SE 098, AE,VR 0a0 */                               \
		BSTArray<CameraStateData>  cameraDataCacheA;                     /* SE 0a0, AE,VR 0a8 */                               \
		std::uint32_t              unk0C0;                               /* SE 0a8, AE,VR 0c0 */                               \
		float                      haltonSequence[2][8];                 /* SE 0c0, AE,VR 0c4 (2, 3) Halton Sequence points */ \
		float                      dynamicResolutionWidthRatio;          /* SE 0c4, AE,VR 104 */                               \
		float                      dynamicResolutionHeightRatio;         /* SE 104, AE,VR 108 */                               \
		float                      dynamicResolutionPreviousWidthRatio;  /* SE 108, AE,VR 10c */                               \
		float                      dynamicResolutionPreviousHeightRatio; /* SE 10c, AE,VR 110 */                               \
		std::uint32_t              dynamicResolutionIncreaseFrameWaited; /* SE 110, AE,VR 114 */                               \
		volatile std::int32_t      dynamicResolutionLock;                /* SE 114, AE,VR 118 */                               \
		bool                       canIncreaseDynamicResolution;         /* SE 118, AE,VR 11c */                               \
		bool                       canDecreaseDynamicResolution;         /* SE 119, AE,VR 11d */                               \
		bool                       canChangeDynamicResolution;           /* SE 120, AE,VR 11e */

#else
#	define RUNTIME_DATA_CONTENT                                                                                               \
		NiPointer<NiSourceTexture> defaultTextureBlack;                  /* SE 058, AE,VR 060 - "BSShader_DefHeightMap"*/      \
		NiPointer<NiSourceTexture> defaultTextureWhite;                  /* SE 060, AE,VR 068 */                               \
		NiPointer<NiSourceTexture> defaultTextureGrey;                   /* SE 068, AE,VR 070 */                               \
		NiPointer<NiSourceTexture> defaultHeightMap;                     /* SE 070, AE,VR 078 */                               \
		NiPointer<NiSourceTexture> defaultReflectionCubeMap;             /* SE 078, AE,VR 080 */                               \
		NiPointer<NiSourceTexture> defaultFaceDetailMap;                 /* SE 080, AE,VR 088 */                               \
		NiPointer<NiSourceTexture> defaultTexEffectMap;                  /* SE 088, AE,VR 090 */                               \
		NiPointer<NiSourceTexture> defaultTextureNormalMap;              /* SE 090, AE,VR 098 */                               \
		NiPointer<NiSourceTexture> defaultTextureDitherNoiseMap;         /* SE 098, AE,VR 0a0 */                               \
		BSTArray<CameraStateData>  cameraDataCacheA;                     /* SE 0a0, AE,VR 0a8 */                               \
		std::uint32_t              unk0C0;                               /* SE 0a8, AE,VR 0c0 */                               \
		float                      haltonSequence[2][8];                 /* SE 0c0, AE,VR 0c4 (2, 3) Halton Sequence points */ \
		float                      dynamicResolutionWidthRatio;          /* SE 0c4, AE,VR 104 */                               \
		float                      dynamicResolutionHeightRatio;         /* SE 104, AE,VR 108 */                               \
		float                      dynamicResolutionPreviousWidthRatio;  /* SE 108, AE,VR 10c */                               \
		float                      dynamicResolutionPreviousHeightRatio; /* SE 10c, AE,VR 110 */                               \
		std::uint32_t              dynamicResolutionIncreaseFrameWaited; /* SE 110, AE,VR 114 */                               \
		volatile std::int32_t      dynamicResolutionLock;                /* SE 114, AE,VR 118 */                               \
		bool                       canIncreaseDynamicResolution;         /* SE 118, AE,VR 11c */                               \
		bool                       canDecreaseDynamicResolution;         /* SE 119, AE,VR 11d */                               \
		bool                       canChangeDynamicResolution;           /* SE 120, AE,VR 11e */
#endif
				RUNTIME_DATA_CONTENT;
			};
#if !defined(ENABLE_SKYRIM_VR)  // Non-VR
			static_assert(offsetof(RUNTIME_DATA, dynamicResolutionWidthRatio) == 0xA4);
#elif defined(EXCLUSIVE_SKYRIM_VR)  // VR
			static_assert(offsetof(RUNTIME_DATA, dynamicResolutionWidthRatio) == 0xAC);
#else
			static_assert(offsetof(RUNTIME_DATA, dynamicResolutionWidthRatio) == 0xA4);
#endif
#ifdef ENABLE_SKYRIM_AE
			// projectionPosScaleXUI/YUI: the UI/menu TAA pass's own projection scale (main scene
			// and UI share projectionPosScaleX/Y on legacy AE). gUpdateCounter increments in
			// Main::Update(), unlike frameCount which only increments on rendered frames.
			struct FRAME_STATE_1799
			{
				float         projectionPosScaleXUI;    // 00 (0x4C)
				float         projectionPosScaleYUI;    // 04 (0x50)
				std::uint32_t frameCount;               // 08 (0x54)
				std::uint32_t gUpdateCounter;           // 0C (0x58)
				std::uint8_t  unk05C[4];                // 10 (0x5C) unresolved
				bool          insideFrame;              // 14 (0x60)
				bool          letterbox;                // 15 (0x61)
				std::uint8_t  unk062[2];                // 16 (0x62) unresolved
				bool          compiledShaderThisFrame;  // 18 (0x64)
				bool          useEarlyZ;                // 19 (0x65)
				std::uint8_t  unk066[10];               // 1A (0x66) unresolved
			};
			static_assert(sizeof(FRAME_STATE_1799) == 0x24);  // pins to RUNTIME_DATA start: 0x4C + 0x24 == 0x70
			static_assert(offsetof(FRAME_STATE_1799, frameCount) == 0x08);
			static_assert(offsetof(FRAME_STATE_1799, insideFrame) == 0x14);
			static_assert(offsetof(FRAME_STATE_1799, letterbox) == 0x15);
			static_assert(offsetof(FRAME_STATE_1799, compiledShaderThisFrame) == 0x18);
			static_assert(offsetof(FRAME_STATE_1799, useEarlyZ) == 0x19);

			RUNTIME_DATA_ACCESSOR_VERSIONED_OPTIONAL_EX(FRAME_STATE_1799, GetFrameState1799, SKSE::RUNTIME_SSE_1_7_99, 0x4C);

			[[nodiscard]] inline std::uint32_t& GetFrameCount() noexcept
			{
				if (auto* fs = GetFrameState1799()) {
					return fs->frameCount;
				}
				return REL::RelocateMember<std::uint32_t>(this, 0x4C);
			}

			[[nodiscard]] inline bool& GetInsideFrame() noexcept
			{
				if (auto* fs = GetFrameState1799()) {
					return fs->insideFrame;
				}
				return REL::RelocateMember<bool>(this, 0x54);
			}

			// Legacy AE's letterbox/useEarlyZ sit 4 bytes later (0x55/0x59) than SE/VR's (0x51/0x55).
			[[nodiscard]] inline bool& GetUseEarlyZ() noexcept
			{
				if (auto* fs = GetFrameState1799()) {
					return fs->useEarlyZ;
				}
				if SKYRIM_REL_CONSTEXPR (REL::Module::IsAE()) {
					return REL::RelocateMember<bool>(this, 0x59);
				}
				return REL::RelocateMember<bool>(this, 0x55);
			}

			[[nodiscard]] inline bool& GetLetterbox() noexcept
			{
				if (auto* fs = GetFrameState1799()) {
					return fs->letterbox;
				}
				if SKYRIM_REL_CONSTEXPR (REL::Module::IsAE()) {
					return REL::RelocateMember<bool>(this, 0x55);
				}
				return REL::RelocateMember<bool>(this, 0x51);
			}

			[[nodiscard]] inline bool& GetCompiledShaderThisFrame() noexcept
			{
				if (auto* fs = GetFrameState1799()) {
					return fs->compiledShaderThisFrame;
				}
				if SKYRIM_REL_CONSTEXPR (REL::Module::IsAE()) {
					return REL::RelocateMember<bool>(this, 0x58);
				}
				return REL::RelocateMember<bool>(this, 0x54);
			}
#endif

			[[nodiscard]] static State* GetSingleton()
			{
				static REL::Relocation<State*> singleton{ RELOCATION_ID(524998, 411479) };
				return singleton.get();
			}

			CameraStateData* FindCameraDataCache(const NiCamera* a_camera, bool a_useJitter)
			{
				for (uint32_t i = 0; i < GetRuntimeData().cameraDataCacheA.size(); i++) {
					if (GetRuntimeData().cameraDataCacheA[i].referenceCamera == a_camera &&
						GetRuntimeData().cameraDataCacheA[i].GetCameraStateRuntimeData().useJitter == a_useJitter)
						return &GetRuntimeData().cameraDataCacheA[i];
				}
				return nullptr;
			}

#if defined(EXCLUSIVE_SKYRIM_VR)
			// The exclusive-VR RUNTIME_DATA includes firstCameraStateIndex at State + 0x58.
			// Cross-runtime RUNTIME_DATA omits that field and therefore begins at State + 0x60.
			static constexpr std::size_t RUNTIME_DATA_VR_OFFSET = 0x58;
#else
			static constexpr std::size_t RUNTIME_DATA_VR_OFFSET = 0x60;
#endif
			[[nodiscard]] static std::size_t RUNTIME_DATA_AE_OFFSET() noexcept
			{
				static const std::size_t offset = REL::Module::IsAtLeast(SKSE::RUNTIME_SSE_1_7_99) ? 0x70 : 0x60;
				return offset;
			}
			RUNTIME_MEMBER_ACCESSOR_VERSIONED(RUNTIME_DATA, GetRuntimeData, SKSE::RUNTIME_SSE_1_6_629, 0x58, RUNTIME_DATA_VR_OFFSET, RUNTIME_DATA_AE_OFFSET());

#if defined(ENABLE_SKYRIM_VR)
			static_assert(RUNTIME_DATA_VR_OFFSET + offsetof(RUNTIME_DATA, dynamicResolutionWidthRatio) == 0x104);
			static_assert(RUNTIME_DATA_VR_OFFSET + offsetof(RUNTIME_DATA, dynamicResolutionLock) == 0x118);
#endif

			[[nodiscard]] inline bool GetDoubleDynamicResolutionAdjustmentFrequency() noexcept
			{
				if SKYRIM_REL_CONSTEXPR (REL::Module::IsAE()) {
					return REL::RelocateMember<bool>(this, 0x57);
				}
				return false;
			}

			void SetCameraData(const NiCamera* a_camera, std::uint32_t a_flags)
			{
				using func_t = decltype(&State::SetCameraData);
				static REL::Relocation<func_t> func{ RELOCATION_ID(75694, 77503) };
				return func(this, a_camera, a_flags);
			}

			// members
			NiPointer<NiSourceTexture> defaultTextureProjNoiseMap;         // 000
			NiPointer<NiSourceTexture> defaultTextureProjDiffuseMap;       // 008
			NiPointer<NiSourceTexture> defaultTextureProjNormalMap;        // 010
			NiPointer<NiSourceTexture> defaultTextureProjNormalDetailMap;  // 018
			std::uint32_t              unk20;                              // 020
			std::uint32_t              screenWidth;                        // 024
			std::uint32_t              screenHeight;                       // 028
			std::uint32_t              frameBufferViewport[2];             // 02C
			std::uint32_t              unk34;                              // 034
			std::uint32_t              unk38;                              // 038
			std::uint32_t              unk03C;                             // 03C
			std::uint32_t              unk040;                             // 040
			float                      projectionPosScaleX;                // 044
			float                      projectionPosScaleY;                // 048
#ifndef ENABLE_SKYRIM_AE
			// AE >= 1.7.99 relocates these into FRAME_STATE_1799 above -- use the GetXxx()
			// accessors on ENABLE_SKYRIM_AE builds instead.
			std::uint32_t frameCount;               // 04C
			bool          insideFrame;              // 050 -- Renderer::Begin sets true / End sets false
			bool          letterbox;                // 051
			bool          unk052;                   // 052
			bool          unk053;                   // 053
			bool          compiledShaderThisFrame;  // 054 -- "Hitched from shader compile" diagnostic
			bool          useEarlyZ;                // 055
			RUNTIME_DATA_CONTENT;                   // 058, AE,VR 060
#endif
		};
#if defined(EXCLUSIVE_SKYRIM_SE)  // SE
		static_assert(sizeof(State) == 0x118);
		static_assert(offsetof(State, screenWidth) == 0x24);
		static_assert(offsetof(State, frameBufferViewport) == 0x2C);
		static_assert(offsetof(State, insideFrame) == 0x50);
		static_assert(offsetof(State, letterbox) == 0x51);
		static_assert(offsetof(State, compiledShaderThisFrame) == 0x54);
		static_assert(offsetof(State, defaultTextureBlack) == 0x58);
		static_assert(offsetof(State, defaultTextureWhite) == 0x60);
		static_assert(offsetof(State, cameraDataCacheA) == 0xa0);
		static_assert(offsetof(State, dynamicResolutionWidthRatio) == 0x0fc);
#elif defined(EXCLUSIVE_SKYRIM_VR)  // VR
		static_assert(sizeof(State) == 0x120);
		static_assert(offsetof(State, screenWidth) == 0x24);
		static_assert(offsetof(State, frameBufferViewport) == 0x2C);
		static_assert(offsetof(State, insideFrame) == 0x50);
		static_assert(offsetof(State, letterbox) == 0x51);
		static_assert(offsetof(State, compiledShaderThisFrame) == 0x54);
		static_assert(offsetof(State, defaultTextureBlack) == 0x60);
		static_assert(offsetof(State, defaultTextureWhite) == 0x68);
		static_assert(offsetof(State, cameraDataCacheA) == 0xa8);
		static_assert(offsetof(State, dynamicResolutionWidthRatio) == 0x104);
#else
		// frameCount/insideFrame/letterbox/compiledShaderThisFrame/useEarlyZ: not flat members
		// here -- see FRAME_STATE_1799 and GetFrameCount()/GetInsideFrame()/GetLetterbox()/
		// GetCompiledShaderThisFrame()/GetUseEarlyZ().
		static_assert(sizeof(State) == 0x50);
		static_assert(offsetof(State, screenWidth) == 0x24);
		static_assert(offsetof(State, frameBufferViewport) == 0x2C);
#endif
	}
}

#ifdef FMT_VERSION
template <>
struct fmt::formatter<Vector3>
{
	// Presentation format: 'f' - fixed, 'e' - exponential.
	char presentation = 'f';

	// Parses format specifications of the form ['f' | 'e'].
	constexpr auto parse(format_parse_context& ctx) -> format_parse_context::iterator
	{
		auto it = ctx.begin(), end = ctx.end();
		if (it != end && (*it == 'f' || *it == 'e'))
			presentation = *it++;

		// Check if reached the end of the range:
		if (it != end && *it != '}')
			format_error("invalid format");

		// Return an iterator past the end of the parsed range:
		return it;
	}

	// Formats the point p using the parsed format specification (presentation)
	// stored in this formatter.
	auto format(const Vector3& v, format_context& ctx) const -> format_context::iterator
	{
		// ctx.out() is an output iterator to write to.
		return presentation == 'f' ? fmt::format_to(ctx.out(), "[{:.1f}, {:.1f}, {:.1f}]", v.x, v.y, v.z) : fmt::format_to(ctx.out(), "[{:.1e}, {:.1e}, {:.1e}]", v.x, v.y, v.z);
	}
};

template <>
struct fmt::formatter<Vector4>
{
	// Presentation format: 'f' - fixed, 'e' - exponential.
	char presentation = 'f';

	// Parses format specifications of the form ['f' | 'e'].
	constexpr auto parse(format_parse_context& ctx) -> format_parse_context::iterator
	{
		auto it = ctx.begin(), end = ctx.end();
		if (it != end && (*it == 'f' || *it == 'e'))
			presentation = *it++;

		// Check if reached the end of the range:
		if (it != end && *it != '}')
			format_error("invalid format");

		// Return an iterator past the end of the parsed range:
		return it;
	}

	// Formats the point p using the parsed format specification (presentation)
	// stored in this formatter.
	auto format(const Vector4& v, format_context& ctx) const -> format_context::iterator
	{
		// ctx.out() is an output iterator to write to.
		return presentation == 'f' ? fmt::format_to(ctx.out(), "[{:.1f}, {:.1f}, {:.1f}, {:.1f}]", v.x, v.y, v.z, v.w) : fmt::format_to(ctx.out(), "[{:.1e}, {:.1e}, {:.1e}, {:.1e}]", v.x, v.y, v.z, v.w);
	}
};

template <>
struct fmt::formatter<Matrix>
{
	char presentation = 'f';

	// Parses format specifications of the form ['f' | 'e'].
	constexpr auto parse(format_parse_context& ctx) -> format_parse_context::iterator
	{
		auto it = ctx.begin(), end = ctx.end();
		if (it != end && (*it == 'f' || *it == 'e'))
			presentation = *it++;

		// Check if reached the end of the range:
		if (it != end && *it != '}')
			format_error("invalid format");

		// Return an iterator past the end of the parsed range:
		return it;
	}

	// Formats the point p using the parsed format specification (presentation)
	// stored in this formatter.
	auto format(const Matrix& m, format_context& ctx) const -> format_context::iterator
	{
		// ctx.out() is an output iterator to write to.
		return fmt::format_to(ctx.out(), "[{}, {}, {}, {}]", (Vector4)m.m[0], (Vector4)m.m[1], (Vector4)m.m[2], (Vector4)m.m[3]);
	}
};
#endif
#undef RUNTIME_DATA_CONTENT
