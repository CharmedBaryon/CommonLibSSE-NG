#pragma once

#include "RE/B/BSShaderMaterial.h"
#include "RE/I/IMenu.h"
#include "RE/N/NiColor.h"
#include "RE/N/NiSmartPointer.h"
#include "RE/T/TextureAddressModes.h"
#include "REL/RuntimeDataAccessors.h"

namespace RE
{
	class NiSourceTexture;

	class BSEffectShaderMaterial : public BSShaderMaterial
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSEffectShaderMaterial;
		inline static constexpr auto VTABLE = VTABLE_BSEffectShaderMaterial;

		struct VR_RUNTIME_DATA
		{
#define VR_RUNTIME_DATA_CONTENT \
	REX::EnumSet<VRMenuRenderTarget, std::int32_t> renderTarget{ VRMenuRenderTarget::kNone }; /* 00 (0x84) */
			VR_RUNTIME_DATA_CONTENT
		};
		static_assert(sizeof(VR_RUNTIME_DATA) == 0x4);

		VR_ONLY_POINTER_ACCESSOR(VR_RUNTIME_DATA, GetVRRuntimeData, 0x84);

		BSEffectShaderMaterial()
		{
			if SKYRIM_REL_VR_CONSTEXPR (REL::Module::IsVR()) {
				if (auto* vrData = GetVRRuntimeData()) {
					vrData->renderTarget = VRMenuRenderTarget::kNone;
				}
			}
		}

		~BSEffectShaderMaterial() override;  // 00

		// override (BSShaderMaterial)
		BSShaderMaterial* Create() override;                                // 01
		void              CopyMembers(BSShaderMaterial* a_other) override;  // 02
		bool              DoIsCopy(BSShaderMaterial* a_other) override;     // 03
		std::uint32_t     ComputeCRC32(uint32_t srcHash) override;          // 04
		BSShaderMaterial* GetDefault() override;                            // 05
		Type              GetType() const override;                         // 07 - { return Type::kEffect; }

		// members
		float                                                      falloffStartAngle;     // 38
		float                                                      falloffStopAngle;      // 3C
		float                                                      falloffStartOpacity;   // 40
		float                                                      falloffStopOpacity;    // 44
		NiColorA                                                   baseColor;             // 48
		NiPointer<NiSourceTexture>                                 sourceTexture;         // 58
		NiPointer<NiSourceTexture>                                 greyscaleTexture;      // 60
		float                                                      softFalloffDepth;      // 68
		float                                                      baseColorScale;        // 6C
		BSFixedString                                              sourceTexturePath;     // 70
		BSFixedString                                              greyscaleTexturePath;  // 78
		REX::EnumSet<BSGraphics::TextureAddressMode, std::uint8_t> effectClampMode;       // 80
		std::uint8_t                                               unk81;                 // 81
#if defined(EXCLUSIVE_SKYRIM_VR)
		std::uint16_t pad82{ 0 };  // 82
		VR_RUNTIME_DATA_CONTENT    // 84
#endif
	};
	STATIC_ASSERT_SIZE(BSEffectShaderMaterial, 0x88);
}
#undef VR_RUNTIME_DATA_CONTENT
