#pragma once

#include "RE/H/hkBaseTypes.h"

namespace RE
{
	class hkContactPointMaterial
	{
	public:
		enum class Flag
		{
			kIsNew = 1 << 0,
			kUsesSolverPath2 = 1 << 1,
			kBreakoffObjectID = 1 << 2,
			kIsDisabled = 1 << 3
		};

		// members
		std::uint64_t                        userData;     // 00
		hkUFloat8                            friction;     // 08
		std::uint8_t                         restitution;  // 09
		hkUFloat8                            maxImpulse;   // 0A
		stl::enumeration<Flag, std::uint8_t> flags;        // 0B
	};
	static_assert(sizeof(hkContactPointMaterial) == 0x10);
}
