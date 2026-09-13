#pragma once

#include "RE/H/hkbBlendingTransitionEffect.h"
#include "RE/H/hkbGenerator.h"

namespace RE
{
	// Ported from https://github.com/adamhynek/activeragdoll (GPL-3.0). Its own
	// inline comment for crossBlendEventId (0x64) doesn't reproduce its own
	// confirmed offsetof(state)==0xA8 anchor; 0x68 (computed here) does.
	class BSCyclicBlendTransitionGenerator : public hkbGenerator
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSCyclicBlendTransitionGenerator;
		inline static constexpr auto VTABLE = VTABLE_BSCyclicBlendTransitionGenerator;

		enum class State : std::int8_t
		{
			kInvalid = -1,
			kNone = 0,
			kFreeze = 1,
			kCrossBlend = 2,
			kCrossBlendStart = 3,
		};

		// members
		std::uint32_t                unk48;                     // 48
		std::uint32_t                pad4C;                     // 4C
		hkbGenerator*                generator;                 // 50
		std::uint32_t                freezeEventId;             // 58
		std::uint32_t                pad5C;                     // 5C
		std::uint64_t                unk60;                     // 60
		std::uint32_t                crossBlendEventId;         // 68
		std::uint32_t                pad6C;                     // 6C
		std::uint64_t                unk70;                     // 70
		float                        blendParameter;            // 78
		float                        transitionDuration;        // 7C
		std::uint8_t                 unk80;                     // 80
		std::uint8_t                 pad81[3];                  // 81
		std::uint32_t                pad84;                     // 84
		std::uint64_t                unk88;                     // 88
		hkbGenerator*                clonedGenerator;           // 90
		std::uint64_t                unk98;                     // 98
		hkbBlendingTransitionEffect* blendingTransitionEffect;  // A0
		State                        state;                     // A8
	};
	static_assert(offsetof(BSCyclicBlendTransitionGenerator, state) == 0xA8);
}
