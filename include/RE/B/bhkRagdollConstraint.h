#pragma once

#include "RE/B/bhkConstraint.h"

namespace RE
{
	// Ported from https://github.com/adamhynek/activeragdoll (GPL-3.0)
	class bhkRagdollConstraint : public bhkConstraint
	{
	public:
		inline static constexpr auto RTTI = RTTI_bhkRagdollConstraint;
		inline static constexpr auto VTABLE = VTABLE_bhkRagdollConstraint;
	};
	static_assert(sizeof(bhkRagdollConstraint) == 0x20);
}
