#pragma once

#include "RE/C/CFilter.h"
#include "RE/H/hkVector4.h"

namespace RE
{
	struct hkpWorldRayCastInput
	{
	public:
		// members
		hkVector4 from;                                  // 00
		hkVector4 to;                                    // 10
		bool      enableShapeCollectionFilter{ false };  // 20
		CFilter   filterInfo{};                          // 24
	};
	static_assert(sizeof(hkpWorldRayCastInput) == 0x30);
}
