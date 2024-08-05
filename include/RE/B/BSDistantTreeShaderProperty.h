#pragma once

#include "RE/B/BSShaderProperty.h"

namespace RE
{
	class BSDistantTreeShaderProperty : public BSShaderProperty
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSDistantTreeShaderProperty;
		inline static constexpr auto Ni_RTTI = NiRTTI_BSDistantTreeShaderProperty;
		inline static constexpr auto VTABLE = VTABLE_BSDistantTreeShaderProperty;

		~BSDistantTreeShaderProperty() override;  // 00

		// override (BSShaderProperty)
		const NiRTTI*                  GetRTTI() const override;                                                                                    // 02
		RenderPassArray*               GetRenderPasses(BSGeometry* a_geometry, std::uint32_t a_arg2, BSShaderAccumulator* a_accumulator) override;  // 2A
		void                           Unk_2B(void) override;                                                                                       // 2B
		void                           Unk_2F(void) override;                                                                                       // 2F
		std::int32_t                   ForEachTexture(ForEachVisitor& a_visitor) override;                                                          // 33
		[[nodiscard]] NiSourceTexture* GetBaseTexture() override;                                                                                   // 37

		// members
		std::uint64_t unk88;  // 88
		std::uint64_t unk90;  // 90
		std::uint64_t unk98;  // 98
		std::uint64_t unkA0;  // A0
		std::uint64_t unkA8;  // A8
	};
	static_assert(sizeof(BSDistantTreeShaderProperty) == 0xB0);
}
