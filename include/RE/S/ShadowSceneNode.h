#pragma once

#include "RE/B/BSAtomic.h"
#include "RE/B/BSTArray.h"
#include "RE/N/NiNode.h"

namespace RE
{
	class BSLight;
	class BSFogProperty;
	class BSLensFlareRenderData;
	class BSPortalGraph;
	class BSShadowLight;
	class BSShadowDirectionalLight;

	class ShadowSceneNode : public NiNode
	{
	public:
		inline static constexpr auto RTTI = RTTI_ShadowSceneNode;
		inline static auto           Ni_RTTI = NiRTTI_ShadowSceneNode;

		struct LIGHT_CREATE_PARAMS
		{
		public:
			// members
			bool                   dynamic;         // 00
			bool                   shadowLight;     // 01
			bool                   portalStrict;    // 02
			bool                   affectLand;      // 03
			bool                   affectWater;     // 04
			bool                   neverFades;      // 05
			float                  fov;             // 08
			float                  falloff;         // 0C
			float                  nearDistance;    // 10
			float                  depthBias;       // 14
			std::uint32_t          unk18;           // 18
			NiAVObject*            restrictedNode;  // 20
			BSLensFlareRenderData* lensFlareData;   // 28
		};

		struct RUNTIME_DATA
		{
#define RUNTIME_DATA_CONTENT                                                                 \
	std::uint64_t                      unk128;             /* 128 */                         \
	BSTArray<NiPointer<BSLight>>       activePointLights;  /* 130 */                         \
	BSTArray<NiPointer<BSShadowLight>> activeShadowLights; /* 148 */                         \
	BSTArray<NiPointer<BSLight>>       unk160;             /* 160 */                         \
	BSTArray<void*>                    unk178;             /* 178 */                         \
	BSTArray<NiPointer<BSLight>>       unk190;             /* 190 */                         \
	mutable BSSpinLock                 unk1A8;             /* 1A8 */                         \
	BSTArray<NiPointer<NiAVObject>>    geometries;         /* 1B0 */                         \
	BSTArray<NiPointer<NiAVObject>>    particleNodes;      /* 1C8 */                         \
	BSTArray<NiPointer<NiAVObject>>    actorRootNodes;     /* 1E0 */                         \
	mutable BSSpinLock                 unk1F8;             /* 1F8 */                         \
	BSLight*                           sunLight;           /* 200 */                         \
	BSLight*                           cloudLight;         /* 208 */                         \
	BSShadowDirectionalLight*          shadowDirLight;     /* 210 */                         \
	std::uint8_t                       unk218;             /* 218 */                         \
	std::uint8_t                       unk219;             /* 219 */                         \
	std::uint8_t                       unk21A;             /* 21A */                         \
	std::uint8_t                       unk21B;             /* 21B */                         \
	std::uint32_t                      pad21C;             /* 21C */                         \
	NiPointer<BSFogProperty>           fogProperty;        /* 220 */                         \
	BSPortalGraph*                     portalGraph;        /* 228 */                         \
	BSTArray<BSShadowLight*>           shadowCasterLights; /* 230 */                         \
	std::uint64_t                      unk248;             /* 248 */                         \
	std::uint64_t                      unk250;             /* 250 */                         \
	std::uint64_t                      unk258;             /* 258 */                         \
	std::uint64_t                      unk260;             /* 260 */                         \
	std::uint64_t                      unk268;             /* 268 */                         \
	std::uint64_t                      unk270;             /* 270 */                         \
	std::uint64_t                      unk278;             /* 278 */                         \
	std::uint64_t                      unk280;             /* 280 */                         \
	std::uint64_t                      unk288;             /* 288 */                         \
	std::uint64_t                      unk290;             /* 290 */                         \
	std::uint64_t                      unk298;             /* 298 */                         \
	std::uint64_t                      unk2A0;             /* 2A0 */                         \
	std::uint64_t                      unk2A8;             /* 2A8 */                         \
	std::uint64_t                      unk2B0;             /* 2B0 */                         \
	std::uint64_t                      unk2B8;             /* 2B8 */                         \
	std::uint64_t                      unk2C0;             /* 2C0 */                         \
	std::uint64_t                      unk2C8;             /* 2C8 */                         \
	std::uint64_t                      unk2D0;             /* 2D0 */                         \
	std::uint64_t                      unk2D8;             /* 2D8 */                         \
	std::uint64_t                      unk2E0;             /* 2E0 */                         \
	NiPoint3                           unk2E8;             /* 2E8 */                         \
	NiPoint3                           cameraPos;          /* 2F4 */                         \
														   /*	NiPoint3 unk328;  // VR Only*/ \
	std::uint8_t  unk300;                                  /* 300 */                         \
	std::uint8_t  pad301;                                  /* 301 */                         \
	std::uint16_t pad302;                                  /* 302 */                         \
	float         unk304;                                  /* 304 */

			RUNTIME_DATA_CONTENT
		};
		static_assert(sizeof(RUNTIME_DATA) == 0x1E0);

		~ShadowSceneNode() override;  // 00

		// override (NiNode)
		const NiRTTI* GetRTTI() const override;  // 02
#if !defined(ENABLE_SKYRIM_VR) || (!defined(ENABLE_SKYRIM_AE) && !defined(ENABLE_SKYRIM_VR))
		// The following are virtual functions past the point where VR compatibility breaks.
		void OnVisible(NiCullingProcess& a_process) override;  // 34
#endif

		[[nodiscard]] inline RUNTIME_DATA& GetRuntimeData() noexcept
		{
			return REL::RelocateMember<RUNTIME_DATA>(this, 0x128, 0x150);
		}

		[[nodiscard]] inline const RUNTIME_DATA& GetRuntimeData() const noexcept
		{
			return REL::RelocateMember<RUNTIME_DATA>(this, 0x128, 0x150);
		}

		void AttachObject(RE::NiAVObject* object)
		{
			using func_t = decltype(&ShadowSceneNode::AttachObject);
			REL::Relocation<func_t> func{ RELOCATION_ID(99696, 106330) };
			return func(this, object);
		}

		BSLight* AddLight(NiLight* a_light, const LIGHT_CREATE_PARAMS& a_params)
		{
			using func_t = decltype(&ShadowSceneNode::AddLight);
			REL::Relocation<func_t> func{ RELOCATION_ID(99692, 106326) };
			return func(this, a_light, a_params);
		}

		// members
#ifndef SKYRIM_CROSS_VR
		RUNTIME_DATA_CONTENT;  // 128, 150
#endif
	private:
		KEEP_FOR_RE()
	};
#if !defined(ENABLE_SKYRIM_VR)
	static_assert(sizeof(ShadowSceneNode) == 0x308);
#elif !defined(ENABLE_SKYRIM_AE) && !defined(ENABLE_SKYRIM_SE)
	static_assert(sizeof(ShadowSceneNode) == 0x330);
#endif
}
#undef RUNTIME_DATA_CONTENT
