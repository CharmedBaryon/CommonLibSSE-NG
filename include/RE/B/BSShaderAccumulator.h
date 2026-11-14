#pragma once

#include "RE/B/BSTArray.h"
#include "RE/N/NiAlphaAccumulator.h"
#include "RE/N/NiColor.h"
#include "RE/N/NiSmartPointer.h"
#include "REL/RuntimeDataAccessors.h"
#include "REX/REX/EnumSet.h"

namespace RE
{
	class BSBatchRenderer;
	class ShadowSceneNode;

	class BSShaderAccumulator : public NiAlphaAccumulator
	{
	public:
		enum class RENDER_MODE : std::uint32_t
		{
			kNormal = 0x00,
			kShadowMask = 0x0C,
			kShadowMapPlain = 0x0D,
			kShadowMapClamped = 0x0E,
			kShadowMapPb = 0x0F,
			kShadowMapCube = 0x11,
			kLocalMap = 0x12,
			kLodLandscapePass = 0x14,
			kWaterReflectionPass = 0x15,
			kFirstPersonView = 0x16,
			kBloodDecalPass = kFirstPersonView,
			kAlphaTransparencyShadowPass = 0x17,  // no-op on SE/AE/VR (verified: bare `return`)
			// Slot 0x18 dispatches unrelated code per runtime, so it's aliased below rather than
			// given one shared name.
			kSEEndFirstPersonView = 0x18,
			kAEResetQueuedShadowPassList = 0x18,
			kVRWorldSpaceUIPass = 0x18,
			kVolumetricLightingPass = 0x19,    // SE/AE; shared with kOcclusion's handler
			kVREndFirstPersonView = 0x19,      // VR: kSEEndFirstPersonView's behavior sits here instead
			kOcclusion = 0x1A,                 // SE/AE; VR shares this slot with 0x1B under a different handler
			kPrecipitationOcclusionMap = 0x1C  // SE/AE only -- VR has no handler at this slot
		};

		// Render flags passed to NiCamera::RenderCameraView and through the finish handlers and
		// BSBatchRenderer to the shaders' SetupGeometry. Bits marked kUnk have no confirmed meaning.
		enum class RENDER_FLAG : std::uint32_t
		{
			kNone = 0,
			kUseJitter = 1 << 0,           // BSGraphics::State::SetCameraData: a_useJitter = flags & 1
			kUnk002 = 1 << 1,              // set for the pre/post resolve depth render; BSLightingShader zeroes a constant when set
			kApplyAlphaProperty = 1 << 2,  // BSRenderPass draw applies the pass's NiProperty state; RenderEffects always sets it
			kCubeMap = 1 << 3,             // BSCubeMapCamera::RenderFaces; also stops ApplyPassAlphaCullState overriding the cull mode
			kNoMotionVectors = 1 << 4,     // BSLightingShader uses the current world matrix as the previous one; Main::RenderFirstPersonView sets it while paused
			kDepthPrepass = 1 << 5,        // world depth prepass (0x21) and UI3D depth; RenderDecalPassesAlt skips when set
			kUnk040 = 1 << 6,              // only Main::RenderFirstPersonView passes it (0x43)
			kUnk080 = 1 << 7,              // tested in RenderPostAccumulationPasses (with 0x200)
			kUnk100 = 1 << 8,              // tested in FinishAccumulatingSharedModes; with kCubeMap suppresses the cull override
			kUnk200 = 1 << 9,              // UI3DSceneManager::Render post-resolve depth
			kUpdateViewport = 1 << 10      // NiCamera::RenderCameraView calls Renderer::UpdateViewPort
		};

		class SunOcclusionTest
		{
		public:
			void*         occlusionQuery;   // 00 BSGraphics::OcclusionQuery
			float         percentOccluded;  // 08
			std::uint32_t pixelCount;       // 0C
			std::uint32_t frameCount;       // 10
			bool          waiting;          // 14
		};
		static_assert(sizeof(SunOcclusionTest) == 0x18);

		// VR only: geometry that AccumulateObject queued for StepBatchList.
		struct DeferredAccumulation
		{
		public:
			NiPointer<BSGeometry>           geometry;  // 00
			BSBatchRenderer::GeometryGroup* group;     // 08
		};
		static_assert(sizeof(DeferredAccumulation) == 0x10);

		inline static constexpr auto RTTI = RTTI_BSShaderAccumulator;
		inline static constexpr auto Ni_RTTI = NiRTTI_BSShaderAccumulator;
		inline static constexpr auto VTABLE = VTABLE_BSShaderAccumulator;

		[[nodiscard]] static BSShaderAccumulator* Create(std::uint32_t a_unk);
		[[nodiscard]] static BSShaderAccumulator* GetCurrentAccumulator();
		[[nodiscard]] static BSShaderAccumulator* GetMainAccumulator() noexcept
		{
			static REL::Relocation<BSShaderAccumulator**> accumulator{ RELOCATION_ID(528064, 415009) };
			return *accumulator;
		}
		static void SetCurrentAccumulator(BSShaderAccumulator* a_accumulator);
		void        RenderFirstPersonView_End(bool a_force);

		~BSShaderAccumulator() override = default;  // 00

		// override (NiObject)
		[[nodiscard]] const NiRTTI* GetRTTI() const override;  // 02

		// override (NiAccumulator)
		void                            StartAccumulating(NiCamera* a_camera) override;                        // 25
		void                            FinishAccumulating() override;                                         // 26
		BSBatchRenderer::GeometryGroup* StartGroupingAlphas(NiBound* a_bound) override;                        // 28
		void                            StopGroupingAlphas(BSBatchRenderer::GeometryGroup* a_group) override;  // 29

		// add
		virtual void FinishAccumulatingDispatch(std::uint32_t flags);          // 2A -- table dispatch on renderMode, not a fixed body
		virtual void FinishAccumulatingPostResolveDepth(std::uint32_t flags);  // 2B
		virtual void FinishAccumulatingSunGlint();                             // 2C -- no-op on SE/AE/VR (verified: bare `return`)

		static constexpr std::ptrdiff_t kFlagsOffset = 0x128;
		static constexpr std::ptrdiff_t kFlagsOffsetVR = 0x150;
		static constexpr std::ptrdiff_t kRuntimeDataSE = 0x130;
		static constexpr std::ptrdiff_t kRuntimeDataVR = 0x158;

		struct FLAT_RUNTIME_DATA
		{
#define FLAT_RUNTIME_DATA_CONTENT                                                                                                              \
	std::uint8_t     unk58[0x4];               /* 58 */                                                                                        \
	bool             useEqualDepthTest;        /* 5C */                                                                                        \
	std::uint32_t    sunPixelCount;            /* 60 */                                                                                        \
	bool             waitingForSunQuery;       /* 64 */                                                                                        \
	float            percentSunOccludedStored; /* 68 */                                                                                        \
	std::uint8_t     pad6C[0x4];               /* 6C */                                                                                        \
	SunOcclusionTest sunOcclusionTests[3];     /* 70 */                                                                                        \
	bool             unkB8;                    /* B8 */                                                                                        \
	bool             noFade;                   /* B9 */                                                                                        \
	bool             unkBA;                    /* BA */                                                                                        \
	std::uint8_t     padBB[0x5];               /* BB */                                                                                        \
	std::uint8_t     unkC0[0x10];              /* C0 */                                                                                        \
	std::uint8_t     fadeNodeMap[0x20];        /* D0 */                                                                                        \
	std::uint8_t     unkF0[0x10];              /* F0 */                                                                                        \
	void*            unk100;                   /* 100 */                                                                                       \
	void*            unk108;                   /* 108 */                                                                                       \
	std::uint32_t    unk110;                   /* 110 */                                                                                       \
	bool             unk114;                   /* 114 */                                                                                       \
	NiColorA         silhouetteColor;          /* 118 */                                                                                       \
	bool             firstPerson;              /* 128 */                                                                                       \
	bool             unk129;                   /* 129 */                                                                                       \
	bool             unk12A;                   /* 12A */                                                                                       \
	bool             unk12B;                   /* 12B */                                                                                       \
	bool             drawDecals;               /* 12C */                                                                                       \
	bool             isShadowMapAccumulator;   /* 12D */                                                                                       \
	bool             isDirectionalShadowMap;   /* 12E */                                                                                       \
	BSBatchRenderer* batchRenderer;            /* 130 */                                                                                       \
	std::uint32_t    currentPass;              /* 138 */                                                                                       \
	std::uint32_t    currentBucket;            /* 13C */                                                                                       \
	bool             currentActive;            /* 140 */                                                                                       \
	std::uint8_t     pad141[0x7];              /* 141 */                                                                                       \
	union                                                                                                                                      \
	{                                                                                                                                          \
		void*            shaderManagerState;    /* 148 -- BSShaderManager::State*, void* to avoid a circular include with BSShaderManager.h */ \
		ShadowSceneNode* activeShadowSceneNode; /* 148 */                                                                                      \
	};                                                                                                                                         \
	RENDER_MODE   renderMode;       /* 150 */                                                                                                  \
	std::uint8_t  pad154[0x4];      /* 154 */                                                                                                  \
	void*         unk158;           /* 158 */                                                                                                  \
	std::uint32_t flagOverrideMode; /* 160 */                                                                                                  \
	std::uint32_t flagOverrideMask; /* 164 */                                                                                                  \
	std::uint32_t shadowMapIndex;   /* 168 */                                                                                                  \
	NiPoint3      eyePosition;      /* 16C */                                                                                                  \
	std::uint8_t  unk178[0x8];      /* 178 */

			FLAT_RUNTIME_DATA_CONTENT
		};
		static_assert(sizeof(FLAT_RUNTIME_DATA) == 0x128);
		static_assert(offsetof(FLAT_RUNTIME_DATA, firstPerson) == kFlagsOffset - 0x58);
		static_assert(offsetof(FLAT_RUNTIME_DATA, drawDecals) == kFlagsOffset - 0x58 + 0x4);
		static_assert(offsetof(FLAT_RUNTIME_DATA, batchRenderer) == kRuntimeDataSE - 0x58);
		static_assert(offsetof(FLAT_RUNTIME_DATA, renderMode) == 0x150 - 0x58);
		static_assert(offsetof(FLAT_RUNTIME_DATA, eyePosition) == 0x16C - 0x58);

		struct VR_RUNTIME_DATA
		{
#define VR_RUNTIME_DATA_CONTENT                                        \
	std::uint8_t                   unk58[0x4];               /* 58 */  \
	bool                           useEqualDepthTest;        /* 5C */  \
	std::uint32_t                  sunPixelCount;            /* 60 */  \
	bool                           waitingForSunQuery;       /* 64 */  \
	float                          percentSunOccludedStored; /* 68 */  \
	std::uint8_t                   pad6C[0x4];               /* 6C */  \
	SunOcclusionTest               sunOcclusionTests[3];     /* 70 */  \
	bool                           unkB8;                    /* B8 */  \
	bool                           noFade;                   /* B9 */  \
	bool                           unkBA;                    /* BA */  \
	std::uint8_t                   padBB[0x5];               /* BB */  \
	BSTArray<DeferredAccumulation> deferredAccumulations;    /* C0 */  \
	std::uint32_t                  deferredCursor;           /* D8 */  \
	bool                           unkDC;                    /* DC */  \
	std::uint8_t                   padDD[0xB];               /* DD */  \
	std::uint8_t                   unkE8[0x10];              /* E8 */  \
	std::uint8_t                   fadeNodeMap[0x20];        /* F8 */  \
	std::uint8_t                   unk118[0x10];             /* 118 */ \
	void*                          unk128;                   /* 128 */ \
	void*                          unk130;                   /* 130 */ \
	std::uint32_t                  unk138;                   /* 138 */ \
	bool                           unk13C;                   /* 13C */ \
	NiColorA                       silhouetteColor;          /* 140 */ \
	bool                           firstPerson;              /* 150 */ \
	bool                           unk151;                   /* 151 */ \
	bool                           unk152;                   /* 152 */ \
	bool                           unk153;                   /* 153 */ \
	bool                           drawDecals;               /* 154 */ \
	bool                           isShadowMapAccumulator;   /* 155 */ \
	bool                           isDirectionalShadowMap;   /* 156 */ \
	std::uint8_t                   unk157;                   /* 157 */ \
	BSBatchRenderer*               batchRenderer;            /* 158 */ \
	std::uint32_t                  currentPass;              /* 160 */ \
	std::uint32_t                  currentBucket;            /* 164 */ \
	bool                           currentActive;            /* 168 */ \
	std::uint8_t                   pad169[0x7];              /* 169 */ \
	ShadowSceneNode*               activeShadowSceneNode;    /* 170 */ \
	RENDER_MODE                    renderMode;               /* 178 */ \
	std::uint8_t                   pad17c[0x4];              /* 17C */ \
	void*                          unk180;                   /* 180 */ \
	std::uint32_t                  flagOverrideMode;         /* 188 */ \
	std::uint32_t                  flagOverrideMask;         /* 18C */ \
	std::uint32_t                  shadowMapIndex;           /* 190 */ \
	NiPoint3                       eyePosition;              /* 194 */ \
	std::uint8_t                   unk1A0[0x10];             /* 1A0 */

			VR_RUNTIME_DATA_CONTENT
		};
		static_assert(sizeof(VR_RUNTIME_DATA) == 0x158);
		static_assert(offsetof(VR_RUNTIME_DATA, isDirectionalShadowMap) == offsetof(FLAT_RUNTIME_DATA, isDirectionalShadowMap) + 0x28);
		static_assert(offsetof(VR_RUNTIME_DATA, sunOcclusionTests) == 0x70 - 0x58);
		static_assert(offsetof(VR_RUNTIME_DATA, fadeNodeMap) == 0xF8 - 0x58);
		static_assert(offsetof(VR_RUNTIME_DATA, silhouetteColor) == 0x140 - 0x58);
		static_assert(offsetof(VR_RUNTIME_DATA, deferredAccumulations) == 0xC0 - 0x58);
		static_assert(offsetof(VR_RUNTIME_DATA, deferredCursor) == 0xD8 - 0x58);
		static_assert(offsetof(VR_RUNTIME_DATA, firstPerson) == kFlagsOffsetVR - 0x58);
		static_assert(offsetof(VR_RUNTIME_DATA, drawDecals) == kFlagsOffsetVR - 0x58 + 0x4);
		static_assert(offsetof(VR_RUNTIME_DATA, batchRenderer) == kRuntimeDataVR - 0x58);
		static_assert(offsetof(VR_RUNTIME_DATA, renderMode) == 0x178 - 0x58);
		static_assert(offsetof(VR_RUNTIME_DATA, eyePosition) == 0x194 - 0x58);

		struct RUNTIME_FLAGS
		{
			bool         firstPerson;             // 128 (VR 150)
			bool         unk129;                  // 129
			bool         unk12A;                  // 12A
			bool         unk12B;                  // 12B
			bool         drawDecals;              // 12C
			bool         isShadowMapAccumulator;  // 12D
			bool         isDirectionalShadowMap;  // 12E
			std::uint8_t unk12F;                  // 12F
		};
		static_assert(offsetof(RUNTIME_FLAGS, firstPerson) == 0);
		static_assert(offsetof(RUNTIME_FLAGS, drawDecals) == 0x4);
		static_assert(sizeof(RUNTIME_FLAGS) == 0x8);

		struct RUNTIME_DATA
		{
#define RUNTIME_DATA_CONTENT                                    \
	BSBatchRenderer*                     batchRenderer;         \
	std::uint32_t                        currentPass;           \
	std::uint32_t                        currentBucket;         \
	bool                                 currentActive;         \
	std::uint8_t                         pad0[0x7];             \
	ShadowSceneNode*                     activeShadowSceneNode; \
	RE::BSShaderAccumulator::RENDER_MODE renderMode;            \
	std::uint8_t                         pad1[0x18];            \
	NiPoint3                             eyePosition;           \
	std::uint8_t                         pad2[0x8];

			RUNTIME_DATA_CONTENT
		};
		static_assert(sizeof(RUNTIME_DATA) == 0x50);
		static_assert(offsetof(RUNTIME_DATA, batchRenderer) == 0);
		static_assert(offsetof(RUNTIME_DATA, currentPass) == 0x8);
		static_assert(offsetof(RUNTIME_DATA, currentBucket) == 0xC);
		static_assert(offsetof(RUNTIME_DATA, currentActive) == 0x10);
		static_assert(offsetof(RUNTIME_DATA, activeShadowSceneNode) == 0x18);
		static_assert(offsetof(RUNTIME_DATA, renderMode) == 0x20);
		static_assert(offsetof(RUNTIME_DATA, eyePosition) == 0x3C);

		RUNTIME_DATA_ACCESSOR(RUNTIME_DATA, kRuntimeDataSE, kRuntimeDataVR);
		RUNTIME_DATA_ACCESSOR_EX(RUNTIME_FLAGS, GetRuntimeFlags, kFlagsOffset, kFlagsOffsetVR);
		SE_ONLY_POINTER_ACCESSOR(FLAT_RUNTIME_DATA, GetFlatRuntimeData, 0x58);
		VR_ONLY_POINTER_ACCESSOR(VR_RUNTIME_DATA, GetVRRuntimeData, 0x58);

		// members
#if defined(EXCLUSIVE_SKYRIM_FLAT)
		FLAT_RUNTIME_DATA_CONTENT;  // 58
#elif defined(EXCLUSIVE_SKYRIM_VR)
		VR_RUNTIME_DATA_CONTENT;  // 58
#endif

	protected:
		BSShaderAccumulator* Ctor(std::uint32_t a_unk);
	};
	STATIC_ASSERT_SIZE(BSShaderAccumulator, 0x180, 0x180, 0x1B0, 0x58, 0x180);

	namespace BSGraphics
	{
		// Same native class; kept as an alias for the name's existing callers.
		// see https://github.com/Nukem9/SkyrimSETest/blob/master/skyrim64_test/src/patches/TES/BSShader/BSShaderAccumulator.h
		using BSShaderAccumulator = RE::BSShaderAccumulator;
	}
}

#undef FLAT_RUNTIME_DATA_CONTENT
#undef RUNTIME_DATA_CONTENT
#undef VR_RUNTIME_DATA_CONTENT
