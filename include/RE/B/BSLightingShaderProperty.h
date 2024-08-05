#pragma once

#include "RE/B/BSShaderProperty.h"
#include "RE/B/BSTArray.h"
#include "RE/N/NiColor.h"

namespace RE
{
	class BSShader;
	class BSLight;

	class BSLightingShaderProperty : public BSShaderProperty
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSLightingShaderProperty;
		inline static constexpr auto Ni_RTTI = NiRTTI_BSLightingShaderProperty;
		inline static constexpr auto VTABLE = VTABLE_BSLightingShaderProperty;

		struct Data
		{
			void          Clear();
			BSRenderPass* EmplacePass(BSShader* a_shader, BSShaderProperty* a_property, BSGeometry* a_geometry,
				uint32_t a_technique, uint8_t a_numLights = 0, BSLight* a_light0 = nullptr, BSLight* a_light1 = nullptr,
				BSLight* a_light2 = nullptr, BSLight* a_light3 = nullptr);

			// members
			RE::BSRenderPass* head;   // 00
			std::uint64_t     unk08;  // 08
		};
		static_assert(sizeof(Data) == 0x10);

		~BSLightingShaderProperty() override;  // 00

		// override (BSShaderProperty)
		const NiRTTI*          GetRTTI() const override;                                                                                    // 02
		NiObject*              CreateClone(NiCloningProcess& a_cloning) override;                                                           // 17
		void                   LoadBinary(NiStream& a_stream) override;                                                                     // 18
		void                   LinkObject(NiStream& a_stream) override;                                                                     // 19
		bool                   RegisterStreamables(NiStream& a_stream) override;                                                            // 1A
		void                   SaveBinary(NiStream& a_stream) override;                                                                     // 1B
		bool                   IsEqual(NiObject* a_object) override;                                                                        // 1C - { return false; }
		void                   PostLinkObject(NiStream& a_stream) override;                                                                 // 1E
		bool                   SetupGeometry(BSGeometry* a_geometry) override;                                                              // 27
		bool                   FinishSetupGeometry(BSGeometry* a_geometry) override;                                                        // 28
		RenderPassArray*       GetRenderPasses(BSGeometry* a_geometry, std::uint32_t a_arg2, BSShaderAccumulator* a_accumulator) override;  // 2A
		void                   Unk_2B(void) override;                                                                                       // 2B
		void                   Unk_2C(void) override;                                                                                       // 2C
		void                   Unk_2D(void) override;                                                                                       // 2D
		void                   Unk_2F(void) override;                                                                                       // 2F
		bool                   CanMerge(const BSShaderProperty* a_other) override;                                                          // 30
		void                   SetMaterialAlpha(float a_alpha) override;                                                                    // 31
		float                  QMaterialAlpha() override;                                                                                   // 32
		std::int32_t           ForEachTexture(ForEachVisitor& a_visitor) override;                                                          // 33
		void                   DoClearRenderPasses() override;                                                                              // 34
		std::int32_t           QShader() override;                                                                                          // 35 - { return 11; }
		NiSourceTexture*       GetBaseTexture() override;                                                                                   // 37 - { return diffuseTexture }
		bool                   AcceptsEffectData() const override;                                                                          // 39 - { return !(flags & kRefraction) && !(flags & kTempRefraction); }
		void                   Unk_3B(void) override;                                                                                       // 3B
		std::uint32_t          DetermineUtilityShaderDecl() override;                                                                       // 3D
		BSShaderMaterial::Type GetMaterialType() override;                                                                                  // 3E - { return 2; }

		void CopyMembers(BSLightingShaderProperty* a_other);
		void InvalidateTextures(std::uint32_t a_unk1);

		BSLightingShaderProperty* Ctor()
		{
			using func_t = decltype(&BSLightingShaderProperty::Ctor);
			REL::Relocation<func_t> func{ RELOCATION_ID(99854, 106499) };
			return func(this);
		}

		// members
		Data            unk088[3];          // 088
		Data            unk0B8;             // 0B8
		Data            unk0C8;             // 0C8
		Data            unk0D8;             // 0D8
		BSRenderPass*   unk0E8;             // 0E8
		NiColor*        emissiveColor;      // 0F0
		float           emissiveMult;       // 0F8
		float           forcedDarkness;     // 0FC - unused
		float           specularLODFade;    // 100
		float           envmapLODFade;      // 104
		std::uint32_t   unk108;             // 108
		NiColorA        projectedUVParams;  // 10C
		NiColorA        projectedUVColor;   // 11C
		std::int32_t    unk12C;             // 12C
		std::uint32_t   unk130;             // 130
		std::uint32_t   unk134;             // 134
		BSTArray<void*> unk138;             // 138
		std::uint64_t   unk150;             // 150
		std::uint8_t    unk158;             // 158
		std::uint8_t    pad159;             // 159
		std::uint16_t   pad15A;             // 15A
		std::uint32_t   pad15C;             // 15C
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(BSLightingShaderProperty) == 0x160);
}
