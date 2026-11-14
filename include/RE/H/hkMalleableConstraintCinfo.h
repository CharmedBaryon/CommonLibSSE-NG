#pragma once

#include "RE/H/hkConstraintCinfo.h"

namespace RE
{
	// Ported from https://github.com/adamhynek/activeragdoll (GPL-3.0)
	class hkMalleableConstraintCinfo : public hkConstraintCinfo
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkMalleableConstraintCinfo;
		inline static constexpr auto VTABLE = VTABLE_hkMalleableConstraintCinfo;

		hkMalleableConstraintCinfo();
	};
	static_assert(sizeof(hkMalleableConstraintCinfo) == 0x28);
}
