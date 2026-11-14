#pragma once

#include "RE/B/bhkConstraint.h"

namespace RE
{
	// Ported from https://github.com/adamhynek/activeragdoll (GPL-3.0)
	class bhkMalleableConstraint : public bhkConstraint
	{
	public:
		inline static constexpr auto RTTI = RTTI_bhkMalleableConstraint;
		inline static constexpr auto VTABLE = VTABLE_bhkMalleableConstraint;
	};
	static_assert(sizeof(bhkMalleableConstraint) == 0x20);
}
