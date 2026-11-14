#pragma once

#include "RE/H/hkConstraintCinfo.h"

namespace RE
{
	// Ported from https://github.com/adamhynek/activeragdoll (GPL-3.0)
	class hkBallAndSocketConstraintCinfo : public hkConstraintCinfo
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkBallAndSocketConstraintCinfo;
		inline static constexpr auto VTABLE = VTABLE_hkBallAndSocketConstraintCinfo;

		// members - not necessarily 16-byte aligned
		float pivotB[4];  // 28
		float pivotA[4];  // 38
	};
}
