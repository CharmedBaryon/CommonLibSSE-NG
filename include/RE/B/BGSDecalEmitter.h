#pragma once

#include "RE/N/NiSmartPointer.h"

namespace RE
{
	class BGSImpactData;
	class BSTempEffectParticle;

	class BGSDecalEmitter
	{
	public:
		// members
		std::int32_t                    unk00;            // 00
		bool                            unk04;            // 04
		bool                            pad05;            // 05
		std::uint16_t                   pad06;            // 06
		BGSImpactData*                  impactData;       // 08
		NiPointer<BSTempEffectParticle> particleEmitter;  // 10
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(BGSDecalEmitter) == 0x18);
}
