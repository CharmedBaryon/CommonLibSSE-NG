#pragma once

#include "RE/H/hkContactPointMaterial.h"
#include "RE/H/hkpSolverResults.h"

namespace RE
{
	class hkpContactPointProperties :
		public hkpSolverResults,       // 00
		public hkContactPointMaterial  // 08
	{
	public:
		// members
		float internalData;  // 18
	};
	static_assert(sizeof(hkpContactPointProperties) == 0x20);
}
