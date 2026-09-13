#pragma once

#include "RE/H/hkbGenerator.h"

namespace RE
{
	// Ported from https://github.com/adamhynek/activeragdoll (GPL-3.0). Total size
	// (0x50) isn't directly asserted there, but is forced by
	// hkbBlendingTransitionEffect's confirmed offsetof(fromGenerator)==0x60 combined
	// with its preceding field list.
	class hkbTransitionEffect : public hkbGenerator
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkbTransitionEffect;
		inline static constexpr auto VTABLE = VTABLE_hkbTransitionEffect;

		// members
		std::uint8_t selfTransitionMode;  // 48
		std::uint8_t eventMode;           // 49
		std::uint8_t defaultEventMode;    // 4A
		std::uint8_t unk4B[5];            // 4B - gap between defaultEventMode and hkbBlendingTransitionEffect's own fields
	};
	static_assert(offsetof(hkbTransitionEffect, eventMode) == 0x49);
	static_assert(sizeof(hkbTransitionEffect) == 0x50);
}
