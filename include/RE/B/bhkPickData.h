#pragma once

#include "RE/H/hkpBroadPhase.h"
#include "RE/H/hkpWorldRayCastInput.h"
#include "RE/H/hkpWorldRayCastOutput.h"

namespace RE
{
	class hkpAllRayHitCollector;
	class hkpAllRayHitTempCollector;
	class hkpClosestRayHitCollector;
	class hkpRayHitCollector;

	struct bhkPickData
	{
	public:
		// members
		hkpWorldRayCastInput       rayInput;                           // 00
		hkpWorldRayCastOutput      rayOutput;                          // 30
		hkVector4                  ray;                                // 90
		hkpBroadPhaseAabbCache*    aabbCache{ nullptr };               // A0
		hkpClosestRayHitCollector* closestRayHitCollector{ nullptr };  // A8
		hkpAllRayHitCollector*     allRayHitCollector{ nullptr };      // B0
		hkpAllRayHitTempCollector* allRayHitTempCollector{ nullptr };  // B8
		bool                       pickFailed{ false };                // C0
		std::uint8_t               padC1;                              // C1
		std::uint16_t              padC2;                              // C2
		std::uint32_t              padC4;                              // C4
		std::uint32_t              padC8;                              // C8
	};
	static_assert(sizeof(bhkPickData) == 0xD0);
}
