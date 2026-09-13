#pragma once

#include "RE/B/BSShader.h"
#include "RE/B/BSTHashMap.h"
#include "RE/N/NiColor.h"
#include "RE/N/NiPoint3.h"

#include "REX/W32/D3D.h"

namespace RE
{
	class BSLightingShader : public BSShader
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSLightingShader;
		inline static constexpr auto VTABLE = VTABLE_BSLightingShader;

		// Bit flags packed into the lower 24 bits of the raw technique ID.
		// Source: Nukem9/skyrimse-test BSLightingShader.h; confirmed against aers/Skyrim-SE-Shader-Tools HLSL defines.
		enum class TechniqueFlag : std::uint32_t
		{
			kVC = 1 << 0,
			kSkinned = 1 << 1,
			kModelSpaceNormals = 1 << 2,
			kLightCount1 = 1 << 3,
			kLightCount2 = 1 << 4,
			kLightCount3 = 1 << 5,
			kLightCount4 = 1 << 6,
			kLightCount5 = 1 << 7,
			kLightCount6 = 1 << 8,
			kSpecular = 1 << 9,
			kSoftLighting = 1 << 10,
			kRimLighting = 1 << 11,
			kBackLighting = 1 << 12,
			kShadowDir = 1 << 13,
			kDefShadow = 1 << 14,
			kProjectedUV = 1 << 15,
			kAnisoLighting = 1 << 16,
			kAmbientSpecular = 1 << 17,
			kWorldMap = 1 << 18,
			kBaseObjectIsSnow = 1 << 19,
			kDoAlphaTest = 1 << 20,
			kSnow = 1 << 21,
			kCharacterLight = 1 << 22,
			kAdditionalAlphaMask = 1 << 23
		};

		[[nodiscard]] static std::uint32_t GetVertexTechnique(std::uint32_t a_technique)
		{
			using func_t = decltype(&BSLightingShader::GetVertexTechnique);
			static REL::Relocation<func_t> func{ RELOCATION_ID(101632, 108699) };
			return func(a_technique);
		}

		[[nodiscard]] static std::uint32_t GetPixelTechnique(std::uint32_t a_technique)
		{
			using func_t = decltype(&BSLightingShader::GetPixelTechnique);
			static REL::Relocation<func_t> func{ RELOCATION_ID(101633, 108700) };
			return func(a_technique);
		}

		// Base technique ID for BSLightingShader: (0x48 << 24) | always-on flags (VC, MSN, LightCount1, LightCount3).
		// Subtracting this from a raw technique ID isolates the material feature in bits [29:24].
		// Not named in reference implementations (Nukem9/skyrimse-test); decomposed here for clarity.
		static constexpr std::uint32_t kTechniqueIDBase =
			(0x48u << 24) |
			static_cast<std::uint32_t>(TechniqueFlag::kVC) |
			static_cast<std::uint32_t>(TechniqueFlag::kModelSpaceNormals) |
			static_cast<std::uint32_t>(TechniqueFlag::kLightCount1) |
			static_cast<std::uint32_t>(TechniqueFlag::kLightCount3);

		std::uint32_t                                 unk90;                 // 90
		std::uint32_t                                 currentRawTechnique;   // 94
		std::uint64_t                                 unk98;                 // 98
		BSTFixedHashMap<std::uint32_t, std::uint32_t> techniqueRefCounts;    // A0 - Technique ID -> reference count
		std::uint64_t                                 unkC8;                 // C8
		NiColorA                                      skyColor0;             // D0 - Sky::skyColor[0]
		NiPoint3                                      cloudLightRadius;      // E0 - Sun::cloudLight->radius
		float                                         cloudLightRadiusFade;  // EC
		std::uint8_t                                  iblUp;                 // F0 - Console 'IBL up' flag
		std::uint8_t                                  padF1[7];              // F1
	};
	static_assert(sizeof(BSLightingShader) == 0xF8);

	inline REX::W32::D3D_SHADER_MACRO* GetLightingShaderDefines(std::uint32_t a_descriptor, REX::W32::D3D_SHADER_MACRO* a_defines)
	{
		using func_t = decltype(&GetLightingShaderDefines);
		static REL::Relocation<func_t> func{ RELOCATION_ID(101631, 108698) };
		return func(a_descriptor, a_defines);
	}
}
