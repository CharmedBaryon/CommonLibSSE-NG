#include "RE/B/bhkRigidBody.h"
#include "RE/H/hkpRigidBody.h"
#include "RE/RTTI.h"

namespace RE
{
	hkpRigidBody* bhkRigidBody::GetRigidBody() const
	{
		return skyrim_cast<hkpRigidBody*>(referencedObject.get());
	}

	void bhkRigidBody::SetAngularImpulse(const hkVector4& a_impulse)
	{
		using func_t = decltype(&bhkRigidBody::SetAngularImpulse);
		static REL::Relocation<func_t> func{ RELOCATION_ID(76262, 78092) };
		return func(this, a_impulse);
	}

	void bhkRigidBody::SetAngularVelocity(const hkVector4& a_newVel)
	{
		using func_t = decltype(&bhkRigidBody::SetAngularVelocity);
		static REL::Relocation<func_t> func{ RELOCATION_ID(76260, 78090) };
		return func(this, a_newVel);
	}

	void bhkRigidBody::SetLinearImpulse(const hkVector4& a_impulse)
	{
		using func_t = decltype(&bhkRigidBody::SetLinearImpulse);
		static REL::Relocation<func_t> func{ RELOCATION_ID(76261, 78091) };
		return func(this, a_impulse);
	}

	void bhkRigidBody::SetLinearVelocity(const hkVector4& a_newVel)
	{
		using func_t = decltype(&bhkRigidBody::SetLinearVelocity);
		static REL::Relocation<func_t> func{ RELOCATION_ID(76259, 78089) };
		return func(this, a_newVel);
	}
}
