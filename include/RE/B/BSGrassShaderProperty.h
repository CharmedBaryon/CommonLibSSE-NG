#pragma once

#include "RE/B/BSLightingShaderProperty.h"

namespace RE
{
	class BSGrassShaderProperty : public BSLightingShaderProperty
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSGrassShaderProperty;
		inline static constexpr auto Ni_RTTI = NiRTTI_BSGrassShaderProperty;
		inline static constexpr auto VTABLE = VTABLE_BSGrassShaderProperty;

		virtual ~BSGrassShaderProperty();  // 00

		// override (BSLightingShaderProperty)
		const NiRTTI*    GetRTTI() const override;                                                                                                          // 02
		NiObject*        CreateClone(NiCloningProcess& a_cloning) override;                                                                                 // 17
		void             LoadBinary(NiStream& a_stream) override;                                                                                           // 18
		void             LinkObject(NiStream& a_stream) override;                                                                                           // 19
		bool             RegisterStreamables(NiStream& a_stream) override;                                                                                  // 1A
		void             SaveBinary(NiStream& a_stream) override;                                                                                           // 1B
		bool             IsEqual(NiObject* a_object) override;                                                                                              // 1C
		bool             SetupGeometry(BSGeometry* a_geometry) override;                                                                                    // 27
		RenderPassArray* GetRenderPasses(BSGeometry* a_geometry, std::uint32_t a_arg2, BSShaderAccumulator* a_accumulator) override;                        // 2A
		RenderPassArray* GetRenderPasses_ShadowMapOrMask(BSGeometry* a_geometry, std::uint32_t a_renderMode, BSShaderAccumulator* a_accumulator) override;  // 2B
		BSRenderPass*    GetRenderDepthPass(BSGeometry* a_geometry) override;                                                                               // 2F
		std::int32_t     QShader() override;                                                                                                                // 35

		// add
		BSGraphics::TextureAddressMode QClampMode();                                         // 3F
		void                           SetClampMode(BSGraphics::TextureAddressMode a_mode);  // 40

		// members
		BSTArray<float>                fadeAlphas;         // 160
		std::uint64_t                  unk178;             // 178
		BSGraphics::TextureAddressMode clampMode;          // 180
		float                          wavePeriod;         // 184
		std::uint32_t                  windTimer;          // 188
		std::uint32_t                  unk18C;             // 18C
		BSRenderPass*                  grassDepthPass;     // 190
		BSShaderPropertyLightData      grassLightData;     // 198
		RenderPassArray                grassShadowPasses;  // 1C0
	};
	STATIC_ASSERT_SIZE(BSGrassShaderProperty, 0x1D0, 0x1D0, 0x1E8, 0x1D0);
}
