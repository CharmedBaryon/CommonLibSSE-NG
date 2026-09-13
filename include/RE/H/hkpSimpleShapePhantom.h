#pragma once

#include "RE/H/hkpShapePhantom.h"

namespace RE
{
	class hkpSimpleShapePhantom : public hkpShapePhantom
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkpSimpleShapePhantom;
		inline static constexpr auto VTABLE = VTABLE_hkpSimpleShapePhantom;

		~hkpSimpleShapePhantom() override;  // 00

		// override (hkpShapePhantom)
		void           CalcContentStatistics(hkStatisticsCollector* a_collector, const hkClass* a_class) const override;                                                                                    // 02
		hkpPhantomType GetType() const override;                                                                                                                                                            // 06 - { return hkpPhantomType::kSimpleShape; }
		void           AddOverlappingCollidable(hkpCollidable* a_collidable) override;                                                                                                                      // 08
		bool           IsOverlappingCollidableAdded(const hkpCollidable* a_collidable) override;                                                                                                            // 09
		void           RemoveOverlappingCollidable(hkpCollidable* a_collidable) override;                                                                                                                   // 0A
		void           EnsureDeterministicOrder() override;                                                                                                                                                 // 0B
		hkpPhantom*    Clone() const override;                                                                                                                                                              // 0C
		void           DeallocateInternalArrays() override;                                                                                                                                                 // 0E
		void           SetPositionAndLinearCast(const hkVector4& a_position, const hkpLinearCastInput& a_input, hkpCdPointCollector& a_castCollector, hkpCdPointCollector* a_startCollector) override;      // 0F
		void           SetTransformAndLinearCast(const hkTransform& a_transform, const hkpLinearCastInput& a_input, hkpCdPointCollector& a_castCollector, hkpCdPointCollector* a_startCollector) override;  // 10
		void           GetClosestPoints(hkpCdPointCollector& a_collector, const hkpCollisionInput* a_input = 0) override;                                                                                   // 11
		void           GetPenetrations(hkpCdBodyPairCollector& a_collector, const hkpCollisionInput* a_input = 0) override;                                                                                 // 12

		// members
		hkArray<hkpCollidable*> collisionDetails;  // 1A0
		bool                    orderDirty;        // 1B0
		std::uint8_t            pad1B1[15];        // 1B1
	};
	static_assert(sizeof(hkpSimpleShapePhantom) == 0x1C0);
}
