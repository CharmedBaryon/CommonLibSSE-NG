#pragma once
#include "RE/N/NiObject.h"

// see https://github.com/Nukem9/SkyrimSETest/blob/master/skyrim64_test/src/patches/TES/BSShader/BSShaderAccumulator.h
namespace RE
{
	class NiAccumulator : public NiObject
	{
	public:
		inline static constexpr auto RTTI = RTTI_NiAccumulator;
		inline static auto           Ni_RTTI = NiRTTI_NiAccumulator;

		virtual ~NiAccumulator() = default;  // 00
		// add
		virtual void StartAccumulating(NiCamera const*);
		virtual void FinishAccumulating();
		virtual void RegisterObjectArray(/*NiVisibleArray &*/);
		virtual void Unk_0(void);
		virtual void Unk_1(void);

		const NiCamera* kCamera;  // 10
	};
	static_assert(sizeof(NiAccumulator) == 0x18);
	static_assert(offsetof(NiAccumulator, kCamera) == 0x10);
}
