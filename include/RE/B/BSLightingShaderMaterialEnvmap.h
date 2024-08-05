#pragma once

#include "RE/B/BSLightingShaderMaterialBase.h"
#include "RE/N/NiSmartPointer.h"

namespace RE
{
	class NiSourceTexture;

	class BSLightingShaderMaterialEnvmap : public BSLightingShaderMaterialBase
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSLightingShaderMaterialEnvmap;
		inline static constexpr auto VTABLE = VTABLE_BSLightingShaderMaterialEnvmap;
		inline static auto           FEATURE = Feature::kEnvironmentMap;

		~BSLightingShaderMaterialEnvmap() override;  // 00

		// override (BSLightingShaderMaterialBase)
		BSShaderMaterial* Create() override;                                                                                                                 // 01
		void              CopyMembers(BSShaderMaterial* a_other) override;                                                                                   // 02
		std::uint32_t     ComputeCRC32(uint32_t srcHash) override;                                                                                           // 04
		Feature           GetFeature() const override;                                                                                                       // 06 - { return Feature::kEnvironmentMap; }
		void              OnLoadTextureSet(std::uint64_t a_arg1, BSTextureSet* a_textureSet) override;                                                       // 08
		void              ClearTextures() override;                                                                                                          // 09
		void              ReceiveValuesFromRootMaterial(bool a_skinned, bool a_rimLighting, bool a_softLighting, bool a_backLighting, bool a_MSN) override;  // 0A
		uint32_t          GetTextures(NiSourceTexture** textures) override;                                                                                  // 0B
		void              SaveBinary(NiStream& a_stream) override;                                                                                           // 0C
		void              LoadBinary(NiStream& a_stream) override;                                                                                           // 0D

		// members
		NiPointer<NiSourceTexture> envTexture;      // A0
		NiPointer<NiSourceTexture> envMaskTexture;  // A8
		float                      envMapScale;     // B0
		std::uint32_t              padB4;           // B4

	protected:
		BSLightingShaderMaterialEnvmap* Ctor()
		{
			using func_t = decltype(&BSLightingShaderMaterialEnvmap::Ctor);
			static REL::Relocation<func_t> func{ RELOCATION_ID(100021, 106728) };
			return func(this);
		}
		friend class BSLightingShaderMaterialBase;

	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(BSLightingShaderMaterialEnvmap) == 0xB8);
}
