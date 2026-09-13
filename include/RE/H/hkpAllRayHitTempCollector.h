#pragma once

#include "RE/H/hkArray.h"
#include "RE/H/hkpRayHitCollector.h"
#include "RE/H/hkpWorldRayCastOutput.h"

namespace RE
{
	class hkpAllRayHitTempCollector : public hkpRayHitCollector
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkpAllRayHitTempCollector;
		inline static constexpr auto VTABLE = VTABLE_hkpAllRayHitTempCollector;

		hkpAllRayHitTempCollector()
		{
			stl::emplace_vtable(this);
		}

		// override (hkpRayHitCollector)
		void AddRayHit(const hkpCdBody& a_body, const hkpShapeRayCastCollectorOutput& a_hitInfo) override  // 00
		{
			using func_t = decltype(&hkpAllRayHitTempCollector::AddRayHit);
			static REL::Relocation<func_t> func{ RELOCATION_ID(76693, 78566) };
			return func(this, a_body, a_hitInfo);
		}

		~hkpAllRayHitTempCollector() override{};  // 01

		void Reset()
		{
			using func_t = decltype(&hkpAllRayHitTempCollector::Reset);
			static REL::Relocation<func_t> func{ RELOCATION_ID(15073, 15250) };
			return func(this);
		}

		// members
		hkInplaceArray<hkpWorldRayCastOutput, 8> hits{};  // 010
	};
	static_assert(sizeof(hkpAllRayHitTempCollector) == 0x320);
}
