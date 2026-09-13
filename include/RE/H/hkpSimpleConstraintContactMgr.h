#pragma once

#include "RE/H/hkpConstraintInstance.h"
#include "RE/H/hkpDynamicsContactMgr.h"
#include "RE/H/hkpSimpleContactConstraintData.h"

namespace RE
{
	class hkpSimpleConstraintContactMgr : public hkpDynamicsContactMgr
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkpSimpleConstraintContactMgr;
		inline static constexpr auto VTABLE = VTABLE_hkpSimpleConstraintContactMgr;

		~hkpSimpleConstraintContactMgr() override;  // 00

		// override (hkReferencedObject)
		const hkClass* GetClassType() const override;                                                                     // 01
		void           CalcContentStatistics(hkStatisticsCollector* a_collector, const hkClass* a_class) const override;  // 02

		// override (hkpContactMgr)
		std::uint16_t AddContactPointImpl(const hkpCdBody& a_bodyA, const hkpCdBody& a_bodyB, const hkpProcessCollisionInput& a_input, hkpProcessCollisionOutput& a_output, const hkpGskCache* a_contactCache, hkContactPoint& a_cp) override;                                                                            // 03
		hkResult      ReserveContactPointsImpl(std::int32_t a_numPoints) override;                                                                                                                                                                                                                                        // 04
		void          RemoveContactPointImpl(std::uint16_t a_cpId, hkpConstraintOwner& a_constraintOwner) override;                                                                                                                                                                                                       // 05
		void          ProcessContactImpl(const hkpCollidable& a_bodyA, const hkpCollidable& a_bodyB, const hkpProcessCollisionInput& a_input, hkpProcessCollisionData& a_collisionData) override;                                                                                                                         // 06
		ToiAccept     AddToiImpl(const hkpCdBody& a_bodyA, const hkpCdBody& a_bodyB, const hkpProcessCollisionInput& a_input, hkpProcessCollisionOutput& a_output, hkTime a_toi, hkContactPoint& a_cp, const hkpGskCache* a_gskCache, hkReal& a_projectedVelocity, hkpContactPointProperties& a_propertiesOut) override;  // 07
		void          RemoveToiImpl(hkpConstraintOwner& a_constraintOwner, hkpContactPointProperties& a_properties) override;                                                                                                                                                                                             // 08
		void          Cleanup() override;                                                                                                                                                                                                                                                                                 // 09 - { delete this; }

		// override (hkpDynamicsContactMgr)
		hkpContactPointProperties* GetContactPointProperties(std::uint16_t a_id) override;                                                                                                                                                                             // 0A
		hkContactPoint*            GetContactPoint(std::uint16_t a_id) override;                                                                                                                                                                                       // 0B
		void                       GetAllContactPointIds(hkArray<std::uint16_t>& a_contactPointIds) const override;                                                                                                                                                    // 0C
		Type                       GetType() const override;                                                                                                                                                                                                           // 0D
		void                       ToiCollisionResponseBeginCallback(const hkContactPoint& a_cp, hkpSimpleConstraintInfoInitInput& a_inA, hkpBodyVelocity& a_velA, hkpSimpleConstraintInfoInitInput& a_inB, hkpBodyVelocity& a_velB) override;                         // 0E
		void                       ToiCollisionResponseEndCallback(const hkContactPoint& a_cp, hkReal a_impulseApplied, hkpSimpleConstraintInfoInitInput& a_inA, hkpBodyVelocity& a_velA, hkpSimpleConstraintInfoInitInput& a_inB, hkpBodyVelocity& a_velB) override;  // 0F
		hkpConstraintInstance*     GetConstraintInstance() override;                                                                                                                                                                                                   // 10
		bool                       FireCallbacksForEarliestToi(hkpToiEvent& a_event, hkReal& a_rotateNormal) override;                                                                                                                                                 // 11
		void                       ConfirmToi(hkpToiEvent& a_event, hkReal a_rotateNormal, hkArray<hkpEntity*>& a_outToBeActivated) override;                                                                                                                          // 12

		// add
		virtual const hkpConstraintInstance* GetConstraintInstance() const;  // 13

		// members
		std::uint16_t                  reservedContactPoints;      // 20
		std::uint16_t                  contactPointCallbackDelay;  // 22
		std::uint32_t                  pad24;                      // 24
		hkpSimpleContactConstraintData contactConstraintData;      // 28
		hkpConstraintInstance          constraint;                 // 78
		std::uint64_t                  padE8;                      // E8
	};
	static_assert(sizeof(hkpSimpleConstraintContactMgr) == 0xF0);
}
