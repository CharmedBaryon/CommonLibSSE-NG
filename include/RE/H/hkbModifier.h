#pragma once

#include "RE/H/hkbNode.h"

namespace RE
{
	// Ported from https://github.com/adamhynek/activeragdoll (GPL-3.0)
	class hkbModifier : public hkbNode
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkbModifier;
		inline static constexpr auto VTABLE = VTABLE_hkbModifier;

		// members
		bool          enable;  // 48
		std::uint8_t  pad49;   // 49
		std::uint16_t pad4A;   // 4A
		std::uint32_t pad4C;   // 4C
	};
	static_assert(sizeof(hkbModifier) == 0x50);
}
