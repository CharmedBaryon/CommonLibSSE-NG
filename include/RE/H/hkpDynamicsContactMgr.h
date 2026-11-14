#pragma once

#include "RE/H/hkArray.h"
#include "RE/H/hkpContactMgr.h"

namespace RE
{
	class hkpConstraintInstance;
	class hkpEntity;
	class hkpWorld;
	struct hkpBodyVelocity;
	struct hkpSimpleConstraintInfoInitInput;
	struct hkpToiEvent;

	class hkpDynamicsContactMgr : public hkpContactMgr
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkpDynamicsContactMgr;
		inline static constexpr auto VTABLE = VTABLE_hkpDynamicsContactMgr;

		~hkpDynamicsContactMgr() override;  // 00

		// add
		virtual hkpContactPointProperties* GetContactPointProperties(std::uint16_t a_id);                                                                                                                                                                             // 0A - { return nullptr; }
		virtual hkContactPoint*            GetContactPoint(std::uint16_t a_id);                                                                                                                                                                                       // 0B - { return nullptr; }
		virtual void                       GetAllContactPointIds(hkArray<std::uint16_t>& a_contactPointIds) const;                                                                                                                                                    // 0C - { return; }
		virtual Type                       GetType() const = 0;                                                                                                                                                                                                       // 0D
		virtual void                       ToiCollisionResponseBeginCallback(const hkContactPoint& a_cp, hkpSimpleConstraintInfoInitInput& a_inA, hkpBodyVelocity& a_velA, hkpSimpleConstraintInfoInitInput& a_inB, hkpBodyVelocity& a_velB);                         // 0E - { return; }
		virtual void                       ToiCollisionResponseEndCallback(const hkContactPoint& a_cp, hkReal a_impulseApplied, hkpSimpleConstraintInfoInitInput& a_inA, hkpBodyVelocity& a_velA, hkpSimpleConstraintInfoInitInput& a_inB, hkpBodyVelocity& a_velB);  // 0F - { return; }
		virtual hkpConstraintInstance*     GetConstraintInstance();                                                                                                                                                                                                   // 10 - { return nullptr; }
		virtual bool                       FireCallbacksForEarliestToi(hkpToiEvent& a_event, hkReal& a_rotateNormal);                                                                                                                                                 // 11 - { return false; }
		virtual void                       ConfirmToi(hkpToiEvent& a_event, hkReal a_rotateNormal, hkArray<hkpEntity*>& a_outToBeActivated);                                                                                                                          // 12 - { return; }

		// members
		hkpWorld* world;  // 18
	};
	static_assert(sizeof(hkpDynamicsContactMgr) == 0x20);

}
