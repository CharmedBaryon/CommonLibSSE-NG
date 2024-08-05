#pragma once

#include "RE/B/BSLightingShaderMaterialBase.h"
#include "RE/N/NiColor.h"

namespace RE
{
	class BSLightingShaderMaterialSnow : public BSLightingShaderMaterialBase
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSLightingShaderMaterialSnow;
		inline static constexpr auto VTABLE = VTABLE_BSLightingShaderMaterialSnow;
		inline static auto           FEATURE = Feature::kMultiIndexTriShapeSnow;

		~BSLightingShaderMaterialSnow() override;  // 00

		// override (BSLightingShaderMaterialBase)
		BSShaderMaterial* Create() override;                              // 01
		void              CopyMembers(BSShaderMaterial* a_src) override;  // 02
		std::uint32_t     ComputeCRC32(uint32_t srcHash) override;        // 04
		Feature           GetFeature() const override;                    // 06 - { return Feature::kMultiIndexTriShapeSnow; }
		void              SaveBinary(NiStream& a_stream) override;        // 0C
		void              LoadBinary(NiStream& a_stream) override;        // 0D

		// members
		NiColorA sparkleParams;  // A0

	protected:
		BSLightingShaderMaterialSnow* Ctor()
		{
			using func_t = decltype(&BSLightingShaderMaterialSnow::Ctor);
			static REL::Relocation<func_t> func{ RELOCATION_ID(100118, 106825) };
			return func(this);
		}
		friend class BSLightingShaderMaterialBase;

	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(BSLightingShaderMaterialSnow) == 0xB0);
}
