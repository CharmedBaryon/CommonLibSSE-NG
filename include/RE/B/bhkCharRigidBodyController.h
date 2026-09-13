#pragma once

#include "RE/B/bhkCharacterController.h"
#include "RE/B/bhkCharacterRigidBody.h"
#include "RE/H/hkpCharacterRigidBodyListener.h"

namespace RE
{
	class bhkCharRigidBodyController :
		public bhkCharacterController,        // 00
		public hkpCharacterRigidBodyListener  // 330
	{
	public:
		inline static constexpr auto RTTI = RTTI_bhkCharRigidBodyController;
		inline static constexpr auto VTABLE = VTABLE_bhkCharRigidBodyController;

		~bhkCharRigidBodyController() override;  // 00

		// override (hkpCharacterRigidBodyListener)
		virtual void CharacterCallback(hkpWorld* a_world, hkpCharacterRigidBody* a_characterRB) override;                                                                                                                                                                 // 03
		virtual void ProcessActualPoints(const hkpWorld* a_world, hkpCharacterRigidBody* a_characterRB, const hkpLinkedCollidable::CollisionEntry& a_entry, hkpSimpleConstraintContactMgr* a_mgr, hkArray<std::uint16_t>& a_contactPointIds) override;                    // 04
		virtual void UnweldContactPoints(hkpCharacterRigidBody* characterRB, const hkpLinkedCollidable::CollisionEntry& entry, hkpSimpleConstraintContactMgr* mgr, const hkArray<std::uint16_t>& contactPointIds) override;                                               // 05
		virtual void ConsiderCollisionEntryForSlope(const hkpWorld* world, hkpCharacterRigidBody* characterRB, const hkpLinkedCollidable::CollisionEntry& entry, hkpSimpleConstraintContactMgr* mgr, hkArray<std::uint16_t>& contactPointIds) override;                   // 06
		virtual void ConsiderCollisionEntryForMassModification(const hkpWorld* world, hkpCharacterRigidBody* characterRB, const hkpLinkedCollidable::CollisionEntry& entry, hkpSimpleConstraintContactMgr* mgr, const hkArray<std::uint16_t>& contactPointIds) override;  // 07

		// The mass of whatever the character is currently standing on.
		float GetSupportMass()
		{
			using func_t = decltype(&bhkCharRigidBodyController::GetSupportMass);
			static REL::Relocation<func_t> func{ RELOCATION_ID(76426, 78265) };
			return func(this);
		}

		bhkCharacterRigidBody charRigidBody;  // 340
	};
	static_assert(offsetof(bhkCharRigidBodyController, charRigidBody) == 0x340);
}
