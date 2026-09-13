#pragma once

#include "RE/B/BSAtomic.h"
#include "RE/B/BSTArray.h"
#include "RE/N/NiNode.h"
#include "REL/RuntimeDataAccessors.h"

namespace RE
{
	class BSCullingProcess;
	class BSCompoundFrustum;
	class BSLight;
	class BSFogProperty;
	class BSLensFlareRenderData;
	class BSPortal;
	class BSPortalGraph;
	class BSShadowLight;
	class BSShadowDirectionalLight;
	class NiLight;

	class ShadowSceneNode : public NiNode
	{
	public:
		inline static constexpr auto RTTI = RTTI_ShadowSceneNode;
		inline static constexpr auto Ni_RTTI = NiRTTI_ShadowSceneNode;
		inline static constexpr auto VTABLE = VTABLE_ShadowSceneNode;

		struct LIGHT_CREATE_PARAMS
		{
		public:
			// members
			bool                   dynamic;          // 00
			bool                   shadowLight;      // 01
			bool                   portalStrict;     // 02
			bool                   affectLand;       // 03
			bool                   affectWater;      // 04
			bool                   neverFades;       // 05
			float                  fov;              // 08
			float                  falloff;          // 0C
			float                  nearDistance;     // 10
			float                  depthBias;        // 14
			std::uint32_t          sceneGraphIndex;  // 18
			NiAVObject*            restrictedNode;   // 20
			BSLensFlareRenderData* lensFlareData;    // 28
		};

		struct RUNTIME_DATA
		{
#define RUNTIME_DATA_CONTENT                                            \
	std::uint64_t                      unk128;                /* 128 */ \
	BSTArray<NiPointer<BSLight>>       activeLights;          /* 130 */ \
	BSTArray<NiPointer<BSShadowLight>> activeShadowLights;    /* 148 */ \
	BSTArray<NiPointer<BSLight>>       lightQueueAdd;         /* 160 */ \
	BSTArray<NiPointer<BSLight>>       lightQueueRemove;      /* 178 */ \
	BSTArray<NiPointer<BSLight>>       unk190;                /* 190 */ \
	mutable BSSpinLock                 lightQueueLock;        /* 1A8 */ \
	BSTArray<NiPointer<NiAVObject>>    litGeometry;           /* 1B0 */ \
	BSTArray<NiPointer<NiAVObject>>    particleNodes;         /* 1C8 */ \
	BSTArray<NiPointer<NiAVObject>>    actorRootNodes;        /* 1E0 */ \
	mutable BSSpinLock                 objectListLock;        /* 1F8 */ \
	BSLight*                           sunLight;              /* 200 */ \
	BSLight*                           cloudLight;            /* 208 */ \
	BSShadowDirectionalLight*          sunShadowDirLight;     /* 210 */ \
	std::uint8_t                       sceneGraphIndex;       /* 218 */ \
	bool                               disableLightUpdate;    /* 219 */ \
	bool                               wireframe;             /* 21A */ \
	bool                               opaqueWireframe;       /* 21B */ \
	std::uint32_t                      pad21C;                /* 21C */ \
	NiPointer<BSFogProperty>           fogProperty;           /* 220 */ \
	BSPortalGraph*                     portalGraph;           /* 228 */ \
	BSTArray<BSShadowLight*>           shadowLightsAccum;     /* 230 */ \
	std::uint32_t                      firstPersonShadowMask; /* 248 */ \
	std::uint32_t                      unk24C;                /* 24C */ \
	std::uint64_t                      unk250;                /* 250 */ \
	std::uint64_t                      unk258;                /* 258 */ \
	std::uint64_t                      unk260;                /* 260 */ \
	std::uint64_t                      unk268;                /* 268 */ \
	std::uint64_t                      unk270;                /* 270 */ \
	std::uint64_t                      unk278;                /* 278 */ \
	std::uint64_t                      unk280;                /* 280 */ \
	std::uint64_t                      unk288;                /* 288 */ \
	std::uint64_t                      unk290;                /* 290 */ \
	std::uint64_t                      unk298;                /* 298 */ \
	std::uint64_t                      unk2A0;                /* 2A0 */ \
	std::uint64_t                      unk2A8;                /* 2A8 */ \
	std::uint64_t                      unk2B0;                /* 2B0 */ \
	std::uint64_t                      unk2B8;                /* 2B8 */ \
	std::uint64_t                      unk2C0;                /* 2C0 */ \
	std::uint64_t                      unk2C8;                /* 2C8 */ \
	std::uint64_t                      unk2D0;                /* 2D0 */ \
	std::uint64_t                      unk2D8;                /* 2D8 */ \
	std::uint64_t                      unk2E0;                /* 2E0 */ \
	NiPoint3                           lightingOffset;        /* 2E8 */ \
	NiPoint3                           cameraPos;             /* 2F4 / 31C */

			RUNTIME_DATA_CONTENT
		};
		static_assert(sizeof(RUNTIME_DATA) == 0x1D8);

		~ShadowSceneNode() override;  // 00

		// override (NiNode)
		const NiRTTI* GetRTTI() const override;  // 02
#if defined(EXCLUSIVE_SKYRIM_FLAT)
		// The following are virtual functions past the point where VR compatibility breaks.
		void OnVisible(NiCullingProcess& a_process, std::int32_t a_alphaGroupIndex) override;  // 34
#endif

		RUNTIME_DATA_ACCESSOR(RUNTIME_DATA, 0x128, 0x150);
		// VR-only: extra NiPoint3 between cameraPos and allowLightRemoveQueues (confirmed by disasm)
		VR_ONLY_POINTER_ACCESSOR(NiPoint3, GetUnk328, 0x328);
		// SE+0x300 / VR+0x334 — outside RUNTIME_DATA due to VR-only NiPoint3 breaking uniform offset
		RUNTIME_DATA_ACCESSOR_EX(bool, GetAllowLightRemoveQueues, 0x300, 0x334);
		RUNTIME_DATA_ACCESSOR_EX(float, GetWindMagnitude, 0x304, 0x338);

		void AttachObject(RE::NiAVObject* object)
		{
			using func_t = decltype(&ShadowSceneNode::AttachObject);
			static REL::Relocation<func_t> func{ RELOCATION_ID(99696, 106330) };
			return func(this, object);
		}

		BSLight* AddLight(NiLight* a_light, const LIGHT_CREATE_PARAMS& a_params);
		void     AddLight(BSLight* a_light);

		// Convenience overload for a non-shadow, non-portal-strict, never-fading light.
		void AddLight(NiLight* a_light)
		{
			using func_t = void (*)(ShadowSceneNode*, NiLight*);
			static REL::Relocation<func_t> func{ RELOCATION_ID(99691, 106325) };
			return func(this, a_light);
		}
		BSLight*           GetLight(NiLight* a_light);
		BSLight*           GetPointLight(NiLight* a_light);
		BSLight*           GetShadowLight(NiLight* a_light);
		void               RemoveAllLights();
		void               RemoveLight(NiLight* a_light);
		void               RemoveLight(const NiPointer<BSLight>& a_light);
		BSCompoundFrustum* BuildSharedCompoundFrustum(BSCullingProcess* a_cullingProcess, BSPortal* a_portal);
		void               SetPortalGraph(BSPortalGraph* a_graph);  // called from ResetCellGrid on cell transition

		// members
#ifndef SKYRIM_CROSS_VR
		RUNTIME_DATA_CONTENT;  // 128, 150
#	ifdef EXCLUSIVE_SKYRIM_VR
		NiPoint3 unk328;  // 328 - VR only
#	endif
		bool          allowLightRemoveQueues;  // 300 / 334
		std::uint8_t  pad301;                  // 301 / 335
		std::uint16_t pad302;                  // 302 / 336
		float         windMagnitude;           // 304 / 338
#endif
	};
	STATIC_ASSERT_SIZE(ShadowSceneNode, 0x308, 0x308, 0x340, 0x110);
}
#undef RUNTIME_DATA_CONTENT
