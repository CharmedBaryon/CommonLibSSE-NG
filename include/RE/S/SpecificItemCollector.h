#pragma once

#include "RE/H/hkpClosestRayHitCollector.h"

#include "RE/C/CFilter.h"

namespace RE
{
	class SpecificItemCollector : public hkpClosestRayHitCollector
	{
	public:
		inline static constexpr auto RTTI = RTTI_SpecificItemCollector;
		inline static constexpr auto VTABLE = VTABLE_SpecificItemCollector;

		// override (hkpClosestRayHitCollector)
		void AddRayHit(const hkpCdBody& a_body, const hkpShapeRayCastCollectorOutput& a_hitInfo) override;  // 01

		~SpecificItemCollector() override;  // 00

		// members
		CFilter filter;  // 70
	};
	static_assert(sizeof(SpecificItemCollector) == 0x80);
}
