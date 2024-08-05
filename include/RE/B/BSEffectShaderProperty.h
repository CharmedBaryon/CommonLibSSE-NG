#pragma once

#include "RE/B/BSShaderProperty.h"

namespace RE
{
	class NiColor;

	class BSEffectShaderProperty : public BSShaderProperty
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSEffectShaderProperty;
		inline static constexpr auto Ni_RTTI = NiRTTI_BSEffectShaderProperty;
		inline static constexpr auto VTABLE = VTABLE_BSEffectShaderProperty;

		~BSEffectShaderProperty() override;  // 00

		// override (BSShaderProperty)
		const NiRTTI*          GetRTTI() const override;                                                                                    // 02
		NiObject*              CreateClone(NiCloningProcess& a_cloning) override;                                                           // 17 - { return 0; }
		void                   LoadBinary(NiStream& a_stream) override;                                                                     // 18
		void                   LinkObject(NiStream& a_stream) override;                                                                     // 19 - { NiShadeProperty::LinkObject(a_stream); }
		void                   SaveBinary(NiStream& a_stream) override;                                                                     // 1B
		void                   PostLinkObject(NiStream& a_stream) override;                                                                 // 1E - { NiObjectNET::PostLinkObject(a_stream); }
		bool                   SetupGeometry(BSGeometry* a_geometry) override;                                                              // 27
		RenderPassArray*       GetRenderPasses(BSGeometry* a_geometry, std::uint32_t a_arg2, BSShaderAccumulator* a_accumulator) override;  // 2A
		void                   Unk_2B(void) override;                                                                                       // 2B - { return 0; }
		void                   SetMaterialAlpha(float a_alpha) override;                                                                    // 31 - { baseColor->alpha = a_alpha }
		float                  QMaterialAlpha() override;                                                                                   // 32 - { baseColor->alpha }
		std::int32_t           ForEachTexture(ForEachVisitor& a_visitor) override;                                                          // 33
		std::int32_t           QShader() override;                                                                                          // 35 - { return 1; }
		NiSourceTexture*       GetBaseTexture() override;                                                                                   // 37 - { return material->sourceTexture }
		void                   Unk_3B(void) override;                                                                                       // 3B - { return; }
		void                   Unk_3C(void) override;                                                                                       // 3C - { return 1; }
		BSShaderMaterial::Type GetMaterialType() override;                                                                                  // 3E - { return 1; }

		BSEffectShaderMaterial* GetMaterial() { return static_cast<BSEffectShaderMaterial*>(GetBaseMaterial()); }

		// members
		NiColor*      unk88;  // 88
		std::uint64_t unk90;  // 90
		std::uint64_t unk98;  // 98
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(BSEffectShaderProperty) == 0xA0);
}
