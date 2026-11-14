#include "RE/H/hkpCharacterRigidBody.h"

namespace RE
{
	void hkpCharacterRigidBody::SetLinearVelocity(const hkVector4& a_newVel, float a_timestep)
	{
		using func_t = decltype(&hkpCharacterRigidBody::SetLinearVelocity);
		static REL::Relocation<func_t> func{ RELOCATION_ID(61559, 0) };
		return func(this, a_newVel, a_timestep);
	}
}
