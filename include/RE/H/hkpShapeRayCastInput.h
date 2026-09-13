#pragma once

#include "RE/H/hkVector4.h"
#include "RE/H/hkpRayShapeCollectionFilter.h"

namespace RE
{
	struct hkpShapeRayCastInput
	{
	public:
		// members
		hkVector4                          from;                                 // 00
		hkVector4                          to;                                   // 10
		CFilter                            collisionFilterInfo{};                // 20
		std::uint8_t                       pad24[4];                             // 24
		const hkpRayShapeCollectionFilter* rayShapeCollectionFilter{ nullptr };  // 28
	};
	static_assert(sizeof(hkpShapeRayCastInput) == 0x30);
}
