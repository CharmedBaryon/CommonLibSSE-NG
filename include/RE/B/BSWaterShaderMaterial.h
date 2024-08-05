#pragma once

#include "RE/B/BSShaderMaterial.h"
#include "RE/N/NiColor.h"
#include "RE/N/NiSmartPointer.h"
#include "RE/T/TESWaterForm.h"

namespace RE
{
	class NiSourceTexture;

	class BSWaterShaderMaterial : public BSShaderMaterial
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSWaterShaderMaterial;
		inline static constexpr auto VTABLE = VTABLE_BSWaterShaderMaterial;

		~BSWaterShaderMaterial() override;  // 00::

		// override (BSShaderMaterial)
		BSShaderMaterial* Create() override;                                // 01
		void              CopyMembers(BSShaderMaterial* a_other) override;  // 02
		bool              DoIsCopy(BSShaderMaterial* a_other) override;     // 03
		std::uint32_t     ComputeCRC32(uint32_t srcHash) override;          // 04
		BSShaderMaterial* GetDefault() override;                            // 05
		Type              GetType() const override;                         // 07 - { return Type::kWater; }

		// members
		NiPointer<NiSourceTexture>       staticReflectionTexture;  // 038
		NiPointer<NiSourceTexture>       normalTexture1;           // 040
		NiPointer<NiSourceTexture>       normalTexture2;           // 048
		NiPointer<NiSourceTexture>       normalTexture3;           // 050
		NiPointer<NiSourceTexture>       normalTexture4;           // 058
		NiColor                          shallowWaterColor;        // 060
		float                            sunSparklePower;          // 06C
		NiColorA                         deepWaterColor;           // 070
		NiColorA                         reflectionColor;          // 080
		float                            sunSpecularPower;         // 090
		float                            reflectionAmount;         // 094
		float                            alpha;                    // 098
		float                            refractionMagnitude;      // 09C
		std::uint64_t                    unk0A0;                   // 0A0
		float                            unk0A8;                   // 0A8
		std::uint64_t                    unk0B0;                   // 0B0
		std::uint64_t                    unk0B8;                   // 0B8
		std::uint64_t                    unk0C0;                   // 0C0
		float                            specularPower;            // 0C8
		std::uint64_t                    unk0D0;                   // 0D0
		std::uint64_t                    unk0D8;                   // 0D8
		float                            noiseFalloff;             // 0E0
		float                            reflectionMagnitude;      // 0E4
		float                            sunSparkleMagnitude;      // 0E8
		float                            unk0EC;                   // 0EC
		WaterShaderData::DepthProperties depthProperties;          // 0F0
		std::uint64_t                    unk100;                   // 100
		std::uint64_t                    unk108;                   // 108
		std::uint64_t                    unk110;                   // 100
		std::uint64_t                    unk118;                   // 118
		float                            uvScaleA[3];              // 120
		std::uint32_t                    unk12C;                   // 12C
		float                            amplitudeA[3];            // 130
		float                            displacementDampener;     // 13C
		NiPlane                          plane;                    // 140
		std::uint32_t                    unk150;                   // 150
		float                            flowmapScale;             // 154
		float                            aboveWaterFogDistFar;     // 158
		float                            unk15C;                   // 15C
		float                            unk160;                   // 160
		float                            underwaterFogDistFar;     // 164
		float                            unk168;                   // 168
		float                            underwaterFogAmount;      // 16C
		float                            fresnelAmount;            // 170
		std::uint32_t                    unk174;                   // 174
		std::uint32_t                    unk178;                   // 178
		std::uint8_t                     unk17C;                   // 17C
		std::uint8_t                     unk17D;                   // 17D
		std::uint8_t                     unk17E;                   // 17E
		std::uint8_t                     unk17F;                   // 17F
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(BSWaterShaderMaterial) == 0x180);
}
