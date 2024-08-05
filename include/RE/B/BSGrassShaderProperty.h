#pragma once

#include "RE/B/BSLightingShaderProperty.h"

namespace RE
{
	class BSGrassShaderProperty : public BSLightingShaderProperty
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSGrassShaderProperty;
		inline static constexpr auto Ni_RTTI = NiRTTI_BSGrassShaderProperty;
		inline static constexpr auto VTABLE = VTABLE_BSGrassShaderProperty;

		virtual ~BSGrassShaderProperty();  // 00

		// override (BSLightingShaderProperty)
		const NiRTTI*    GetRTTI() const override;                                                                                    // 02
		NiObject*        CreateClone(NiCloningProcess& a_cloning) override;                                                           // 17
		void             LoadBinary(NiStream& a_stream) override;                                                                     // 18
		void             LinkObject(NiStream& a_stream) override;                                                                     // 19
		bool             RegisterStreamables(NiStream& a_stream) override;                                                            // 1A
		void             SaveBinary(NiStream& a_stream) override;                                                                     // 1B
		bool             IsEqual(NiObject* a_object) override;                                                                        // 1C
		bool             SetupGeometry(BSGeometry* a_geometry) override;                                                              // 27
		RenderPassArray* GetRenderPasses(BSGeometry* a_geometry, std::uint32_t a_arg2, BSShaderAccumulator* a_accumulator) override;  // 2A
		void             Unk_2B(void) override;                                                                                       // 2B
		void             Unk_2F(void) override;                                                                                       // 2F
		std::int32_t     QShader() override;                                                                                          // 35

		// add
		void Unk_3F(void);  // 3F
		void Unk_40(void);  // 40

		// members
		std::uint64_t unk160;  // 160
		std::uint64_t unk168;  // 168
		std::uint64_t unk170;  // 170
		std::uint64_t unk178;  // 178
		std::uint64_t unk180;  // 180
		std::uint64_t unk188;  // 188
		std::uint64_t unk190;  // 190
		std::uint64_t unk198;  // 198
		std::uint64_t unk1A0;  // 1A0
		std::uint64_t unk1A8;  // 1A8
		std::uint64_t unk1B0;  // 1B0
		std::uint64_t unk1B8;  // 1B8
		std::uint64_t unk1C0;  // 1C0
		std::uint64_t unk1C8;  // 1C8
	};
	static_assert(sizeof(BSGrassShaderProperty) == 0x1D0);
}
