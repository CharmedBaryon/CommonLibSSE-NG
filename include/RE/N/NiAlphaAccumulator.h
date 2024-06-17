#pragma once
#include "RE/N/NiBackToFrontAccumulator.h"

// see https://github.com/Nukem9/SkyrimSETest/blob/master/skyrim64_test/src/patches/TES/BSShader/BSShaderAccumulator.h
namespace RE
{
	class NiAlphaAccumulator : public NiBackToFrontAccumulator
	{
	public:
		inline static constexpr auto RTTI = RTTI_NiAlphaAccumulator;
		inline static auto           Ni_RTTI = NiRTTI_NiAlphaAccumulator;

		virtual ~NiAlphaAccumulator() = default;  //00

		bool observeNoSortHint;                   //50
		bool sortByClosestPoint;                  //51
		bool interfaceSort;                       //52
	};
	static_assert(sizeof(NiAlphaAccumulator) == 0x58);
	static_assert(offsetof(NiAlphaAccumulator, observeNoSortHint) == 0x50);
	static_assert(offsetof(NiAlphaAccumulator, sortByClosestPoint) == 0x51);
	static_assert(offsetof(NiAlphaAccumulator, interfaceSort) == 0x52);
}
