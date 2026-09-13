#pragma once

#include "RE/H/hkpBroadPhaseCastCollector.h"
#include "RE/H/hkpShapeRayCastInput.h"

namespace RE
{
	class hkpRayCollidableFilter;
	struct hkpWorldRayCastInput;

	class hkpWorldRayCaster : public hkpBroadPhaseCastCollector
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkpWorldRayCaster;
		inline static constexpr auto VTABLE = VTABLE_hkpWorldRayCaster;

		~hkpWorldRayCaster() override = default;  // 00

		// override (hkpBroadPhaseCastCollector)
		float AddBroadPhaseHandle(const hkpBroadPhaseHandle* a_broadphaseHandle, std::int32_t a_castIndex) override;  // 01

		// members
		hkpWorldRayCastInput*   input;          // 08
		hkpRayCollidableFilter* filter;         // 10
		hkpRayHitCollector*     collectors;     // 18
		std::int32_t            collectorSize;  // 20
		std::uint8_t            pad24[12];      // 24
		hkpShapeRayCastInput    shapeInput;     // 30
	};
	static_assert(sizeof(hkpWorldRayCaster) == 0x60);
}
