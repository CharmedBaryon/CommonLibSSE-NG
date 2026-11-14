#pragma once

#include "RE/B/bhkRigidBody.h"
#include "RE/H/hkQuaternion.h"
#include "RE/H/hkVector4.h"

namespace RE
{
	class bhkRigidBodyT : bhkRigidBody
	{
	public:
		inline static constexpr auto RTTI = RTTI_bhkRigidBodyT;
		inline static constexpr auto Ni_RTTI = NiRTTI_bhkRigidBodyT;
		inline static constexpr auto VTABLE = VTABLE_bhkRigidBodyT;

		~bhkRigidBodyT() override;  // 00

		// override (bhkRigidBody)
		const NiRTTI* GetRTTI() const override;                                                          // 02
		NiObject*     CreateClone(NiCloningProcess& a_cloning) override;                                 // 17
		void          LoadBinary(NiStream& a_stream) override;                                           // 18
		void          SaveBinary(NiStream& a_stream) override;                                           // 1B
		void          Unk_31(void) override;                                                             // 31
		void          GetPosition(hkVector4& a_outPosition) override;                                    // 33
		void          GetRotation(hkQuaternion& a_outRotation) override;                                 // 34
		void          SetPosition(hkVector4& a_position) override;                                       // 35
		void          SetRotation(hkQuaternion& a_rotation) override;                                    // 36
		void          SetPositionAndRotation(hkVector4& a_position, hkQuaternion& a_rotation) override;  // 37
		void          GetCenterOfMassWorld(hkVector4& a_outCenterOfMassWorld) override;                  // 39
		void          GetTransform(hkTransform& a_outTransform) override;                                // 3A

		hkQuaternion rotation;     // 40
		hkVector4    translation;  // 50
	};
	static_assert(sizeof(bhkRigidBodyT) == 0x60);
}
