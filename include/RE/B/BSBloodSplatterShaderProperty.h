#pragma once

#include "RE/B/BSShaderProperty.h"
#include "RE/B/BSTArray.h"
#include "RE/N/NiColor.h"
#include "RE/N/NiPoint3.h"

namespace RE
{
	class NiSourceTexture;

	class BSBloodSplatterShaderProperty : public BSShaderProperty
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSBloodSplatterShaderProperty;
		inline static constexpr auto Ni_RTTI = NiRTTI_BSBloodSplatterShaderProperty;
		inline static constexpr auto VTABLE = VTABLE_BSBloodSplatterShaderProperty;

		enum : std::uint32_t
		{
			kBloodColor = 0,
			kBloodAlpha,
			kFlareColor,

			kTotal
		};

		~BSBloodSplatterShaderProperty() override;  // 00

		// override (BSShaderProperty)
		const NiRTTI*    GetRTTI() const override;                                                                                    // 02
		NiObject*        CreateClone(NiCloningProcess& a_cloning) override;                                                           // 17
		RenderPassArray* GetRenderPasses(BSGeometry* a_geometry, std::uint32_t a_arg2, BSShaderAccumulator* a_accumulator) override;  // 2A
		std::int32_t     ForEachTexture(ForEachVisitor& a_visitor) override;                                                          // 33
		std::int32_t     QShader() override;                                                                                          // 35 - { return 12 }
		NiSourceTexture* GetBaseTexture() override;                                                                                   // 37 - { return bloodColorTexture; }

		// members
		NiPointer<NiSourceTexture> bloodTextures[kTotal];  // 088
		std::int32_t               textureClampMode;       // 0A0
		float*                     alphaSource;            // 0A8
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(BSBloodSplatterShaderProperty) == 0xB0);
}
