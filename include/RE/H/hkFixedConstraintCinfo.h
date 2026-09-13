#pragma once

#include "RE/H/hkConstraintCinfo.h"

namespace RE
{
	// Ported from https://github.com/adamhynek/activeragdoll (GPL-3.0)
	class hkFixedConstraintCinfo : public hkConstraintCinfo
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkFixedConstraintCinfo;
		inline static constexpr auto VTABLE = VTABLE_hkFixedConstraintCinfo;

		// members
		std::uint64_t unk28 = 0;  // 28
		std::uint8_t  unk30 = 0;  // 30 - type or something
	};
}
