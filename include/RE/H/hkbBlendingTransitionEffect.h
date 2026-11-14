#pragma once

#include "RE/H/hkArray.h"
#include "RE/H/hkQsTransform.h"
#include "RE/H/hkbTransitionEffect.h"

namespace RE
{
	// Ported from https://github.com/adamhynek/activeragdoll (GPL-3.0). Total size
	// isn't asserted there either; left to natural compiler alignment.
	class hkbBlendingTransitionEffect : public hkbTransitionEffect
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkbBlendingTransitionEffect;
		inline static constexpr auto VTABLE = VTABLE_hkbBlendingTransitionEffect;

		// members
		float                  duration;                      // 50
		float                  toGeneratorStartTimeFraction;  // 54
		std::uint16_t          flags;                         // 58
		std::uint8_t           endMode;                       // 5A
		std::uint8_t           blendCurve;                    // 5B
		std::uint16_t          alignmentBone;                 // 5C
		std::uint16_t          pad5E;                         // 5E
		hkbGenerator*          fromGenerator;                 // 60
		hkbGenerator*          toGenerator;                   // 68
		hkArray<hkQsTransform> worldFromModelTransforms;      // 70 - from, to, last(?)
		float                  timeRemaining;                 // 80
		float                  timeInTransition;              // 84
		bool                   applySelfTransition;           // 88
		bool                   initializeCharacterPose;       // 89
	};
	static_assert(offsetof(hkbBlendingTransitionEffect, fromGenerator) == 0x60);
}
