#pragma once

#include "RE/B/BSTArray.h"
#include "RE/B/bhkEntity.h"

namespace RE
{
	class hkAabb;
	class hkTransform;
	class hkQuaternion;
	class hkVector4;
	class hkpRigidBody;

	class bhkRigidBody : public bhkEntity
	{
	public:
		inline static constexpr auto RTTI = RTTI_bhkRigidBody;
		inline static constexpr auto Ni_RTTI = NiRTTI_bhkRigidBody;
		inline static constexpr auto VTABLE = VTABLE_bhkRigidBody;

		~bhkRigidBody() override;  // 00

		// override (bhkEntity)
		const NiRTTI* GetRTTI() const override;                           // 02
		bhkRigidBody* AsBhkRigidBody() override;                          // 15 - { return this; }
		NiObject*     CreateClone(NiCloningProcess& a_cloning) override;  // 17
		void          LoadBinary(NiStream& a_stream) override;            // 18
		void          LinkObject(NiStream& a_stream) override;            // 19
		bool          RegisterStreamables(NiStream& a_stream) override;   // 1A
		void          SaveBinary(NiStream& a_stream) override;            // 1B
		bool          IsEqual(NiObject* a_object) override;               // 1C
		void          MoveToWorld(bhkWorld* a_world) override;            // 29
		void          RemoveFromCurrentWorld() override;                  // 2A
		void          Unk_2B(void) override;                              // 2B
		void          Unk_2C(void) override;                              // 2C - { return 0x110; }
		void          Unk_2D(void) override;                              // 2D
		void          Unk_2E(void) override;                              // 2E
		void          Unk_2F(void) override;                              // 2F
		void          Unk_30(void) override;                              // 30
		void          Unk_32(void) override;                              // 32

		// add
		virtual void GetPosition(hkVector4& a_outPosition);                                    // 33
		virtual void GetRotation(hkQuaternion& a_outRotation);                                 // 34
		virtual void SetPosition(hkVector4& a_position);                                       // 35
		virtual void SetRotation(hkQuaternion& a_rotation);                                    // 36
		virtual void SetPositionAndRotation(hkVector4& a_position, hkQuaternion& a_rotation);  // 37
		virtual void GetCenterOfMassLocal(hkVector4& a_outCenterOfMassLocal);                  // 38
		virtual void GetCenterOfMassWorld(hkVector4& a_outCenterOfMassWorld);                  // 39
		virtual void GetTransform(hkTransform& a_outTransform);                                // 3A
		virtual void GetAabbWorldspace(hkAabb& a_outAabb);                                     // 3B
		virtual void Unk_3C(void);                                                             // 3C

		hkpRigidBody* GetRigidBody() const;
		void          SetAngularImpulse(const hkVector4& a_impulse);
		void          SetAngularVelocity(const hkVector4& a_newVel);
		void          SetLinearImpulse(const hkVector4& a_impulse);
		void          SetLinearVelocity(const hkVector4& a_newVel);

		// members
		BSTArray<void*> unk28;  // 28 - array of smart ptrs to bhkConstraints
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(bhkRigidBody) == 0x40);
}
