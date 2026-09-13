#pragma once

#include "RE/H/hkArray.h"
#include "RE/H/hkpRayHitCollector.h"
#include "RE/H/hkpWorldRayCastOutput.h"

namespace RE
{
	class hkpAllRayHitCollector : public hkpRayHitCollector
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkpAllRayHitCollector;
		inline static constexpr auto VTABLE = VTABLE_hkpAllRayHitCollector;

		hkpAllRayHitCollector()
		{
			stl::emplace_vtable(this);
		}

		// override (hkpRayHitCollector)
		void AddRayHit(const hkpCdBody& a_body, const hkpShapeRayCastCollectorOutput& a_hitInfo) override  // 00
		{
			using func_t = decltype(&hkpAllRayHitCollector::AddRayHit);
			static REL::Relocation<func_t> func{ RELOCATION_ID(77446, 79318) };
			return func(this, a_body, a_hitInfo);
		}

		~hkpAllRayHitCollector() override{};  // 01

		// members
		hkInplaceArray<hkpWorldRayCastOutput, 8> hits{};  // 010
	};
	static_assert(sizeof(hkpAllRayHitCollector) == 0x320);
}
