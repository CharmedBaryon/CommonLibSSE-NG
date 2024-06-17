#pragma once

// see https://github.com/Nukem9/SkyrimSETest/blob/master/skyrim64_test/src/patches/TES/BSShader/BSShaderAccumulator.h
namespace RE
{
	class NiBackToFrontAccumulator : public NiAccumulator
	{
	public:
		inline static constexpr auto RTTI = RTTI_NiBackToFrontAccumulator;
		inline static auto           Ni_RTTI = NiRTTI_NiBackToFrontAccumulator;

		virtual ~NiBackToFrontAccumulator() = default;  //00

		char         _pad[0x18];                        // NiTPointerList<BSGeometry *> m_kItems;
		int32_t      numItems;                          // 30
		int32_t      maxItems;                          // 34
		BSGeometry** kItems;                            // 38
		float*       depths;                            // 40
		int32_t      currItem;                          // 48
	};
	static_assert(sizeof(NiBackToFrontAccumulator) == 0x50);
	static_assert(offsetof(NiBackToFrontAccumulator, numItems) == 0x30);
	static_assert(offsetof(NiBackToFrontAccumulator, maxItems) == 0x34);
	static_assert(offsetof(NiBackToFrontAccumulator, kItems) == 0x38);
	static_assert(offsetof(NiBackToFrontAccumulator, depths) == 0x40);
	static_assert(offsetof(NiBackToFrontAccumulator, currItem) == 0x48);
}
