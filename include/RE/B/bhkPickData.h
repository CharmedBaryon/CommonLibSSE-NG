#pragma once

#include "RE/H/hkpWorldRayCastInput.h"
#include "RE/H/hkpWorldRayCastOutput.h"

namespace RE
{
	class hkpClosestRayHitCollector;

	struct bhkPickData
	{
	public:
		// members
		hkpWorldRayCastInput       rayInput;                      // 00
		hkpWorldRayCastOutput      rayOutput;                     // 30
		hkVector4                  ray;                           // 90
		hkpClosestRayHitCollector* rayHitCollectorA0{ nullptr };  // A0
		hkpClosestRayHitCollector* rayHitCollectorA8{ nullptr };  // A8
		hkpClosestRayHitCollector* rayHitCollectorB0{ nullptr };  // B0
		hkpClosestRayHitCollector* rayHitCollectorB8{ nullptr };  // B8
		bool                       unkC0{ false };                // C0
		std::uint8_t               padC1;                         // C1
		std::uint16_t              padC2;                         // C2
		std::uint32_t              padC4;                         // C4
		std::uint32_t              padC8;                         // C8
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(bhkPickData) == 0xD0);
}
