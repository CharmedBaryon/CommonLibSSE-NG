#pragma once

#include "RE/B/BSLightingShaderMaterialBase.h"
#include "RE/N/NiColor.h"

namespace RE
{
	class BSLightingShaderMaterialHairTint : public BSLightingShaderMaterialBase
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSLightingShaderMaterialHairTint;
		inline static constexpr auto VTABLE = VTABLE_BSLightingShaderMaterialHairTint;
		inline static auto           FEATURE = Feature::kHairTint;

		~BSLightingShaderMaterialHairTint() override;  // 00

		// override (BSLightingShaderMaterialBase)
		BSShaderMaterial* Create() override;                                // 01
		void              CopyMembers(BSShaderMaterial* a_other) override;  // 02
		std::uint32_t     ComputeCRC32(uint32_t srcHash) override;          // 04
		Feature           GetFeature() const override;                      // 06 - { return Feature::kHairTint; }
		void              SaveBinary(NiStream& a_stream) override;          // 0C
		void              LoadBinary(NiStream& a_stream) override;          // 0D

		// members
		NiColor       tintColor;  // A0
		std::uint32_t padAC;      // AC

	protected:
		BSLightingShaderMaterialHairTint* Ctor()
		{
			using func_t = decltype(&BSLightingShaderMaterialHairTint::Ctor);
			static REL::Relocation<func_t> func{ RELOCATION_ID(100095, 106802) };
			return func(this);
		}
		friend class BSLightingShaderMaterialBase;

	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(BSLightingShaderMaterialHairTint) == 0xB0);
}
