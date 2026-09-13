#pragma once

#include "RE/H/hkAabb.h"
#include "RE/H/hkpPhantom.h"
#include "RE/H/hkpWorldRayCastInput.h"
#include "RE/H/hkpWorldRayCastOutput.h"

namespace RE
{
	class hkpCdPointCollector;
	struct hkpLinearCastInput;

	class hkpAabbPhantom : public hkpPhantom
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkpAabbPhantom;
		inline static constexpr auto VTABLE = VTABLE_hkpAabbPhantom;

		~hkpAabbPhantom() override;  // 00

		// override (hkpWorldObject)
		void           CalcContentStatistics(hkStatisticsCollector* a_collector, const hkClass* a_class) const override;  // 02
		hkMotionState* GetMotionState() override;                                                                         // 05 - { return 0; }
		hkpPhantomType GetType() const override;                                                                          // 06
		void           CalcAabb(hkAabb& a_aabb) override;                                                                 // 07
		void           AddOverlappingCollidable(hkpCollidable* a_collidable) override;                                    // 08
		bool           IsOverlappingCollidableAdded(const hkpCollidable* a_collidable) override;                          // 09
		void           RemoveOverlappingCollidable(hkpCollidable* a_collidable) override;                                 // 0A
		void           EnsureDeterministicOrder() override;                                                               // 0B
		hkpPhantom*    Clone() const override;                                                                            // 0C
		void           DeallocateInternalArrays() override;                                                               // 0E

		void castRay(const hkpWorldRayCastInput& input, hkpRayHitCollector& collector) const;
		void castRay(const hkpWorldRayCastInput& input, hkpWorldRayCastOutput& output) const;
		void linearCast(const hkpCollidable* castCollidable, const hkpLinearCastInput& input, hkpCdPointCollector& castCollector, hkpCdPointCollector* startCollector) const;
		void setAabb(const hkAabb& a_aabb);

		// members
		hkAabb                  aabb;                    // F0
		hkArray<hkpCollidable*> overlappingCollidables;  // 110
		bool                    orderDirty;              // 120
		std::uint8_t            pad121[15];              // 121
	};
	static_assert(sizeof(hkpAabbPhantom) == 0x130);
}
