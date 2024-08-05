#pragma once

#include "RE/B/BSLightingShaderMaterialBase.h"
#include "RE/N/NiColor.h"

namespace RE
{
	class BSLightingShaderMaterialFacegenTint : public BSLightingShaderMaterialBase
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSLightingShaderMaterialFacegenTint;
		inline static constexpr auto VTABLE = VTABLE_BSLightingShaderMaterialFacegenTint;
		inline static auto           FEATURE = Feature::kFaceGenRGBTint;

		~BSLightingShaderMaterialFacegenTint() override;  // 00

		// override (BSLightingShaderMaterialBase)
		BSShaderMaterial* Create() override;                                // 01
		void              CopyMembers(BSShaderMaterial* a_other) override;  // 02
		std::uint32_t     ComputeCRC32(uint32_t srcHash) override;          // 04
		Feature           GetFeature() const override;                      // 06 - { return Feature::kFaceGenRGBTint; }
		void              SaveBinary(NiStream& a_stream) override;          // 0C
		void              LoadBinary(NiStream& a_stream) override;          // 0D

		// members
		NiColor       tintColor;  // A0
		std::uint32_t padAC;      // AC

	protected:
		BSLightingShaderMaterialFacegenTint* Ctor()
		{
			using func_t = decltype(&BSLightingShaderMaterialFacegenTint::Ctor);
			static REL::Relocation<func_t> func{ RELOCATION_ID(100087, 106794) };
			return func(this);
		}
		friend class BSLightingShaderMaterialBase;

	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(BSLightingShaderMaterialFacegenTint) == 0xB0);
}
