#pragma once

#include "RE/B/BSShaderProperty.h"
#include "RE/B/BSShaderPropertyLightData.h"
#include "RE/B/BSTArray.h"
#include "RE/M/MemoryManager.h"
#include "RE/N/NiColor.h"

namespace RE
{
	class BSLight;

	class BSLightingShaderProperty : public BSShaderProperty
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSLightingShaderProperty;
		inline static constexpr auto Ni_RTTI = NiRTTI_BSLightingShaderProperty;
		inline static constexpr auto VTABLE = VTABLE_BSLightingShaderProperty;

		~BSLightingShaderProperty() override;  // 00

		// override (BSShaderProperty)
		const NiRTTI*          GetRTTI() const override;                                                                                                          // 02
		NiObject*              CreateClone(NiCloningProcess& a_cloning) override;                                                                                 // 17
		void                   LoadBinary(NiStream& a_stream) override;                                                                                           // 18
		void                   LinkObject(NiStream& a_stream) override;                                                                                           // 19
		bool                   RegisterStreamables(NiStream& a_stream) override;                                                                                  // 1A
		void                   SaveBinary(NiStream& a_stream) override;                                                                                           // 1B
		bool                   IsEqual(NiObject* a_object) override;                                                                                              // 1C - { return false; }
		void                   PostLinkObject(NiStream& a_stream) override;                                                                                       // 1E
		bool                   SetupGeometry(BSGeometry* a_geometry) override;                                                                                    // 27
		bool                   FinishSetupGeometry(BSGeometry* a_geometry) override;                                                                              // 28
		RenderPassArray*       GetRenderPasses(BSGeometry* a_geometry, std::uint32_t a_renderMode, BSShaderAccumulator* a_accumulator) override;                  // 2A
		RenderPassArray*       GetRenderPasses_ShadowMapOrMask(BSGeometry* a_geometry, std::uint32_t a_renderMode, BSShaderAccumulator* a_accumulator) override;  // 2B
		RenderPassArray*       GetRenderPasses_LocalMap(BSGeometry* a_geometry, std::uint32_t a_renderMode, BSShaderAccumulator* a_accumulator) override;         // 2C
		RenderPassArray*       GetRenderPasses_Occlusion(BSGeometry* a_geometry, std::uint32_t a_renderMode, BSShaderAccumulator* a_accumulator) override;        // 2D
		RE::BSRenderPass*      GetRenderDepthPass(BSGeometry* a_geometry) override;                                                                               // 2F
		bool                   CanMerge(const BSShaderProperty* a_other) override;                                                                                // 30
		void                   SetMaterialAlpha(float a_alpha) override;                                                                                          // 31
		float                  QMaterialAlpha() override;                                                                                                         // 32
		std::int32_t           ForEachTexture(ForEachVisitor& a_visitor) override;                                                                                // 33
		void                   DoClearRenderPasses() override;                                                                                                    // 34
		std::int32_t           QShader() override;                                                                                                                // 35 - { return 11; }
		NiSourceTexture*       GetBaseTexture() override;                                                                                                         // 37 - { return diffuseTexture }
		bool                   AcceptsEffectData() const override;                                                                                                // 39 - { return !(flags & kRefraction) && !(flags & kTempRefraction); }
		void                   Unk_3B(void) override;                                                                                                             // 3B
		std::uint32_t          DetermineUtilityShaderDecl() override;                                                                                             // 3D
		BSShaderMaterial::Type GetMaterialType() override;                                                                                                        // 3E - { return 2; }

		void CopyMembers(BSLightingShaderProperty* a_other);
		void InvalidateTextures(std::uint32_t a_unk1);

		// Engine's own CreateClone allocates kSizeVR on VR, not sizeof(this).
		inline static constexpr std::size_t kSizeFlat = 0x160;
		inline static constexpr std::size_t kSizeVR = 0x178;

		static BSLightingShaderProperty* Create()
		{
			auto prop = malloc_runtime<BSLightingShaderProperty>(kSizeFlat, kSizeVR);
			if (prop) {
				prop->Ctor();
			}
			return prop;
		}

		BSLightingShaderProperty* Ctor()
		{
			using func_t = decltype(&BSLightingShaderProperty::Ctor);
			static REL::Relocation<func_t> func{ RELOCATION_ID(99854, 106499) };
			return func(this);
		}

		// members
		RenderPassArray           arrayQueue[3];                  // 088
		RenderPassArray           shadowMapOrMaskPasses;          // 0B8
		RenderPassArray           occlusionPasses;                // 0C8
		RenderPassArray           volumetricShadowUtilityPasses;  // 0D8
		BSRenderPass*             depthPass;                      // 0E8
		NiColor*                  emissiveColor;                  // 0F0
		float                     emissiveMult;                   // 0F8
		float                     forcedDarkness;                 // 0FC - unused
		float                     specularLODFade;                // 100
		float                     envmapLODFade;                  // 104
		float                     unk108;                         // 108
		NiColorA                  projectedUVParams;              // 10C
		NiColorA                  projectedUVColor;               // 11C
		std::int32_t              unk12C;                         // 12C - initialized to -1
		std::uint8_t              pad130[2];                      // 130
		std::uint8_t              arrayQueueWriteIndex;           // 132
		std::uint8_t              arrayQueueReadIndex;            // 133
		std::uint32_t             unk134;                         // 134
		BSShaderPropertyLightData lightingLightData;              // 138
#if defined(EXCLUSIVE_SKYRIM_VR)
		bool  unk160;  // 160 - VR-only; not copied by CreateClone
		float unk164;  // 164 - VR-only; not copied by CreateClone
		float unk168;  // 168 - VR-only; not copied by CreateClone
		float unk16C;  // 16C - VR-only; not copied by CreateClone
		bool  unk170;  // 170 - VR-only; copied by CreateClone
#endif
	};
	STATIC_ASSERT_SIZE(BSLightingShaderProperty, BSLightingShaderProperty::kSizeFlat, BSLightingShaderProperty::kSizeFlat, BSLightingShaderProperty::kSizeVR, BSLightingShaderProperty::kSizeFlat);
}
