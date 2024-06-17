#pragma once

#include "RE/H/hkpRayHitCollector.h"
#include "RE/H/hkpWorldRayCastOutput.h"

namespace RE
{
	class hkpClosestRayHitCollector : public hkpRayHitCollector
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkpClosestRayHitCollector;
		inline static constexpr auto VTABLE = VTABLE_hkpClosestRayHitCollector;

		// override (hkpRayHitCollector)
		void AddRayHit(const hkpCdBody& a_body, const hkpShapeRayCastCollectorOutput& a_hitInfo) override;  // 01

		~hkpClosestRayHitCollector() override;  // 00

		constexpr bool HasHit() noexcept { return rayHit.HasHit(); }

		constexpr void Reset() noexcept
		{
			hkpRayHitCollector::Reset();
			rayHit.Reset();
		}

		// members
		hkpWorldRayCastOutput rayHit;  // 10
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(hkpClosestRayHitCollector) == 0x70);
}
