#pragma once

#include "RE/H/hkpBroadPhaseCastCollector.h"
#include "RE/H/hkpShapeRayCastInput.h"

namespace RE
{
	class hkpRayCollidableFilter;
	struct hkpWorldRayCastInput;
	struct hkpWorldRayCastOutput;

	class hkpSimpleWorldRayCaster : public hkpBroadPhaseCastCollector
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkpSimpleWorldRayCaster;
		inline static constexpr auto VTABLE = VTABLE_hkpSimpleWorldRayCaster;

		~hkpSimpleWorldRayCaster() override = default;  // 00

		// override (hkpBroadPhaseCastCollector)
		float AddBroadPhaseHandle(const hkpBroadPhaseHandle* a_broadphaseHandle, std::int32_t a_castIndex) override;  // 01

		// members
		hkpWorldRayCastInput*   input;       // 08
		hkpRayCollidableFilter* filter;      // 10
		hkpWorldRayCastOutput*  result;      // 18
		hkpShapeRayCastInput    shapeInput;  // 20
	};
	static_assert(sizeof(hkpSimpleWorldRayCaster) == 0x50);
}
