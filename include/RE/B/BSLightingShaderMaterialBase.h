#pragma once

#include "RE/B/BSShaderMaterial.h"
#include "RE/N/NiColor.h"
#include "RE/N/NiSmartPointer.h"

namespace RE
{
	class BSTextureSet;
	class NiSourceTexture;
	class NiStream;

	class BSLightingShaderMaterialBase : public BSShaderMaterial
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSLightingShaderMaterialBase;
		inline static constexpr auto VTABLE = VTABLE_BSLightingShaderMaterialBase;

		~BSLightingShaderMaterialBase() override = default;  // 00

		// override (BSShaderMaterial)
		BSShaderMaterial* Create() override = 0;                            // 01
		void              CopyMembers(BSShaderMaterial* a_other) override;  // 02
		bool              DoIsCopy(BSShaderMaterial* a_other) override;     // 03
		std::uint32_t     ComputeCRC32(uint32_t srcHash) override;          // 04
		BSShaderMaterial* GetDefault() override;                            // 05
		Feature           GetFeature() const override;                      // 06 - { return Feature::kDefault; }
		Type              GetType() const override;                         // 07 - { return Type::kLighting; }

		// add
		virtual void     OnLoadTextureSet(std::uint64_t arg1, BSTextureSet* inTextureSet);                                               // 08
		virtual void     ClearTextures();                                                                                                // 09
		virtual void     ReceiveValuesFromRootMaterial(bool skinned, bool rimLighting, bool softLighting, bool backLighting, bool MSN);  // 0A
		virtual uint32_t GetTextures(NiSourceTexture** textures);                                                                        // 0B
		virtual void     SaveBinary(NiStream& stream);                                                                                   // 0C
		virtual void     LoadBinary(NiStream& stream);                                                                                   // 0D

		static BSLightingShaderMaterialBase* CreateMaterial(Feature a_feature);
		template <class T>
		static T* CreateMaterial();

		void                    CopyBaseMembers(BSLightingShaderMaterialBase* a_other);
		NiPointer<BSTextureSet> GetTextureSet() const;
		void                    SetTextureSet(NiPointer<BSTextureSet> a_textureSet);

		// members
		NiColor                    specularColor = NiColor(1.f, 1.f, 1.f);  // 38
		std::uint32_t              pad44;                                   // 44
		NiPointer<NiSourceTexture> diffuseTexture;                          // 48
		std::int32_t               diffuseRenderTargetSourceIndex = -1;     // 50
		std::uint32_t              pad54;                                   // 54
		NiPointer<NiSourceTexture> normalTexture;                           // 58
		NiPointer<NiSourceTexture> rimSoftLightingTexture;                  // 60
		NiPointer<NiSourceTexture> specularBackLightingTexture;             // 68
		std::int32_t               textureClampMode = 3;                    // 70
		std::int32_t               pad74;                                   // 70
		NiPointer<BSTextureSet>    textureSet;                              // 78
		float                      materialAlpha = 1.f;                     // 80
		float                      refractionPower = 0.f;                   // 84
		float                      specularPower = 1.f;                     // 88
		float                      specularColorScale = 1.f;                // 8C
		float                      subSurfaceLightRolloff = 0.f;            // 90
		float                      rimLightPower = 0.f;                     // 94
		std::uint32_t              unk98 = 0;                               // 98

	protected:
		static BSLightingShaderMaterialBase* Constructor(BSLightingShaderMaterialBase* material)
		{
			using func_t = decltype(&BSLightingShaderMaterialBase::Constructor);
			REL::Relocation<func_t> func{ RELOCATION_ID(100004, 106711) };
			return func(material);
		}

	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(BSLightingShaderMaterialBase) == 0xA0);

	template <class T>
	T* BSLightingShaderMaterialBase::CreateMaterial()
	{
		return static_cast<T*>(CreateMaterial(T::FEATURE));
	}
}
