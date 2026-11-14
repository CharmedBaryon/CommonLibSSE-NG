#pragma once

#include "RE/H/hkReferencedObject.h"

namespace RE
{
	class hkContactPoint;
	class hkpCdBody;
	class hkpCollidable;
	class hkpConstraintOwner;
	class hkpContactPointProperties;
	class hkpGskCache;
	struct hkpProcessCollisionData;
	struct hkpProcessCollisionInput;
	struct hkpProcessCollisionOutput;

	class hkpContactMgr : public hkReferencedObject
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkpContactMgr;
		inline static constexpr auto VTABLE = VTABLE_hkpContactMgr;

		enum class Type : std::uint32_t
		{
			kSimpleConstraintContact = 0,
			kReportContact = 1,
			kConvexListContact = 2,
			kNullContact = 3,
			kUserContact = 4,
			kMax
		};

		enum class ToiAccept
		{
			kAccept = 0,
			kReject = 1
		};

		~hkpContactMgr() override;  // 00

		// add
		virtual std::uint16_t AddContactPointImpl(const hkpCdBody& a_bodyA, const hkpCdBody& a_bodyB, const hkpProcessCollisionInput& a_input, hkpProcessCollisionOutput& a_output, const hkpGskCache* a_contactCache, hkContactPoint& a_cp) = 0;                                                                            // 03
		virtual hkResult      ReserveContactPointsImpl(std::int32_t a_numPoints) = 0;                                                                                                                                                                                                                                        // 04
		virtual void          RemoveContactPointImpl(std::uint16_t a_cpId, hkpConstraintOwner& a_constraintOwner) = 0;                                                                                                                                                                                                       // 05
		virtual void          ProcessContactImpl(const hkpCollidable& a_bodyA, const hkpCollidable& a_bodyB, const hkpProcessCollisionInput& a_input, hkpProcessCollisionData& a_collisionData) = 0;                                                                                                                         // 06
		virtual ToiAccept     AddToiImpl(const hkpCdBody& a_bodyA, const hkpCdBody& a_bodyB, const hkpProcessCollisionInput& a_input, hkpProcessCollisionOutput& a_output, hkTime a_toi, hkContactPoint& a_cp, const hkpGskCache* a_gskCache, hkReal& a_projectedVelocity, hkpContactPointProperties& a_propertiesOut) = 0;  // 07
		virtual void          RemoveToiImpl(class hkpConstraintOwner& a_constraintOwner, hkpContactPointProperties& a_properties) = 0;                                                                                                                                                                                       // 08
		virtual void          Cleanup();                                                                                                                                                                                                                                                                                     // 09 - { return; }

		// members
		Type          type;   // 10
		std::uint32_t pad14;  // 14
	};
	static_assert(sizeof(hkpContactMgr) == 0x18);
}
