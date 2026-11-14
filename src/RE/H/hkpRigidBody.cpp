#include "RE/H/hkpRigidBody.h"

namespace RE
{
	void hkpRigidBody::ApplyLinearImpulse(const hkVector4& a_impulse)
	{
		Activate();
		motion.ApplyLinearImpulse(a_impulse);
	}

	void hkpRigidBody::SetLinearVelocity(const hkVector4& a_newVel)
	{
		Activate();
		motion.SetLinearVelocity(a_newVel);
	}

	void hkpRigidBody::SetAngularVelocity(const hkVector4& a_newVel)
	{
		Activate();
		motion.SetAngularVelocity(a_newVel);
	}
}
