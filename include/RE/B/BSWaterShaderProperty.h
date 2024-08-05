#pragma once

#include "RE/B/BSShaderProperty.h"
#include "RE/B/BSTArray.h"
#include "RE/N/NiPlane.h"

namespace RE
{
	class BSWaterShaderProperty : public BSShaderProperty
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSWaterShaderProperty;
		inline static constexpr auto Ni_RTTI = NiRTTI_BSWaterShaderProperty;
		inline static constexpr auto VTABLE = VTABLE_BSWaterShaderProperty;

		enum class WaterFlag
		{
			kNone = 0,
			kUnderwater = 1 << 5,
			kUseReflections = 1 << 6,
			kUseCubemapReflections = 1 << 14,
			kEnableFlowmap = 1 << 15,
			kBlendNormals = 1 << 16
		};

		~BSWaterShaderProperty() override;  // 00

		// override (BSShaderProperty)
		const NiRTTI*          GetRTTI() const override;                                                                                    // 02
		NiObject*              CreateClone(NiCloningProcess& a_cloning) override;                                                           // 17
		void                   LoadBinary(NiStream& a_stream) override;                                                                     // 18
		void                   LinkObject(NiStream& a_stream) override;                                                                     // 19
		bool                   RegisterStreamables(NiStream& a_stream) override;                                                            // 1A
		void                   SaveBinary(NiStream& a_stream) override;                                                                     // 1B
		bool                   IsEqual(NiObject* a_object) override;                                                                        // 1C - { return false; }
		void                   PostLinkObject(NiStream& a_stream) override;                                                                 // 1E
		RenderPassArray*       GetRenderPasses(BSGeometry* a_geometry, std::uint32_t a_arg2, BSShaderAccumulator* a_accumulator) override;  // 2A
		void                   Unk_2C(void) override;                                                                                       // 2C                                                                                        // 2C
		void                   Unk_2D(void) override;                                                                                       // 2D
		void                   Unk_2F(void) override;                                                                                       // 2F
		std::int32_t           ForEachTexture(ForEachVisitor& a_visitor) override;                                                          // 33
		void                   DoClearRenderPasses() override;                                                                              // 34
		std::int32_t           QShader() override;                                                                                          // 35 - { return 17; }
		BSShaderMaterial::Type GetMaterialType() override;                                                                                  // 3E - { return 3; }

		// members
		stl::enumeration<WaterFlag, std::uint32_t> waterFlags;            // 88
		std::uint32_t                              unk8C;                 // 8C
		std::uint64_t                              unk90;                 // 90
		std::uint64_t                              unk98;                 // 98
		NiPlane                                    plane;                 // A0
		std::uint64_t                              unkB0;                 // B0
		std::uint8_t                               unkB8;                 // B8
		std::uint8_t                               padB9;                 // B9
		std::uint16_t                              padBA;                 // BA
		std::uint16_t                              padBC;                 // BC
		BSRenderPass*                              unkC0;                 // C0
		RenderPassArray                            simpleRenderPassList;  // C8
		std::uint64_t                              unkD0;                 // D0
		BSTArray<void*>                            unkD8;                 // D8
		std::int32_t                               unkF0;                 // F0
		std::uint32_t                              unkF4;                 // F4
		std::uint8_t                               unkF8;                 // F8
		std::uint8_t                               padF9;                 // F9
		std::uint16_t                              padFA;                 // FA
		std::uint16_t                              padFC;                 // FC
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(BSWaterShaderProperty) == 0x100);
}
