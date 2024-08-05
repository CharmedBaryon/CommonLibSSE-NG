#pragma once

#include "RE/B/BSShaderProperty.h"

namespace RE
{
	class BSSkyShaderProperty : public BSShaderProperty
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSSkyShaderProperty;
		inline static auto           Ni_RTTI = NiRTTI_BSSkyShaderProperty;
		inline static auto           VTABLE = VTABLE_BSSkyShaderProperty;

		~BSSkyShaderProperty() override;  // 00

		// override (BSShaderProperty)
		const NiRTTI*                          GetRTTI() const override;                                                                                    // 02
		NiObject*                              CreateClone(NiCloningProcess& a_cloning) override;                                                           // 17
		void                                   LoadBinary(NiStream& a_stream) override;                                                                     // 18
		void                                   LinkObject(NiStream& a_stream) override;                                                                     // 19
		bool                                   RegisterStreamables(NiStream& a_stream) override;                                                            // 1A
		void                                   SaveBinary(NiStream& a_stream) override;                                                                     // 1B
		bool                                   IsEqual(NiObject* a_object) override;                                                                        // 1C
		void                                   PostLinkObject(NiStream& a_stream) override;                                                                 // 1E
		RenderPassArray*                       GetRenderPasses(BSGeometry* a_geometry, std::uint32_t a_arg2, BSShaderAccumulator* a_accumulator) override;  // 2A
		std::int32_t                           ForEachTexture(ForEachVisitor& a_visitor) override;                                                          // 33
		virtual std::int32_t                   QShader() override;                                                                                          // 35
		[[nodiscard]] virtual NiSourceTexture* GetBaseTexture() override;                                                                                   // 37

		enum SkyObject
		{
			SO_SUN = 0x0,
			SO_SUN_GLARE = 0x1,
			SO_ATMOSPHERE = 0x2,
			SO_CLOUDS = 0x3,
			SO_SKYQUAD = 0x4,
			SO_STARS = 0x5,
			SO_MOON = 0x6,
			SO_MOON_SHADOW = 0x7,
		};

		// members
		RE::NiColorA                               kBlendColor;         // 088
		RE::NiSourceTexture*                       pBaseTexture;        // 098
		RE::NiSourceTexture*                       pBlendTexture;       // 0A0
		std::uint8_t                               unk0A8[0x10];        // 0A8
		float                                      fBlendValue;         // 0B8
		std::uint16_t                              usCloudLayer;        // 0BC
		bool                                       bFadeSecondTexture;  // 0BE
		stl::enumeration<SkyObject, std::uint32_t> uiSkyObjectType;     // 0BF
	};
	static_assert(sizeof(BSSkyShaderProperty) == 0xC8);
}
