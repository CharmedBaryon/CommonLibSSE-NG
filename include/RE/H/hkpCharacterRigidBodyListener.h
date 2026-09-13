#pragma once

#include "RE/H/hkReferencedObject.h"

#include "RE/H/hkpLinkedCollidable.h"

namespace RE
{
	class hkpCharacterRigidBody;
	class hkpCapsuleShape;
	class hkpWorld;
	class hkpWorldPostSimulationListener;
	class hkpSimpleConstraintContactMgr;

	class hkpCharacterRigidBodyListener : public hkReferencedObject
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkpCharacterRigidBodyListener;
		inline static constexpr auto VTABLE = VTABLE_hkpCharacterRigidBodyListener;

		virtual ~hkpCharacterRigidBodyListener() override;  //00

		virtual void CharacterCallback(hkpWorld* a_world, hkpCharacterRigidBody* a_characterRB);                                                                                                                                                                 // 03
		virtual void ProcessActualPoints(const hkpWorld* a_world, hkpCharacterRigidBody* a_characterRB, const hkpLinkedCollidable::CollisionEntry& a_entry, hkpSimpleConstraintContactMgr* a_mgr, hkArray<std::uint16_t>& a_contactPointIds);                    // 04
		virtual void UnweldContactPoints(hkpCharacterRigidBody* characterRB, const hkpLinkedCollidable::CollisionEntry& entry, hkpSimpleConstraintContactMgr* mgr, const hkArray<std::uint16_t>& contactPointIds);                                               // 05
		virtual void ConsiderCollisionEntryForSlope(const hkpWorld* world, hkpCharacterRigidBody* characterRB, const hkpLinkedCollidable::CollisionEntry& entry, hkpSimpleConstraintContactMgr* mgr, hkArray<std::uint16_t>& contactPointIds);                   // 06
		virtual void ConsiderCollisionEntryForMassModification(const hkpWorld* world, hkpCharacterRigidBody* characterRB, const hkpLinkedCollidable::CollisionEntry& entry, hkpSimpleConstraintContactMgr* mgr, const hkArray<std::uint16_t>& contactPointIds);  // 07
	};
}
