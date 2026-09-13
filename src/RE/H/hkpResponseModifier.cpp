#include "RE/H/hkpResponseModifier.h"

namespace RE
{
	void hkpResponseModifier::SetInvMassScalingForContact(hkpDynamicsContactMgr* a_mgr, hkpRigidBody* a_body, hkpConstraintOwner& a_constraintOwner, const hkVector4& a_factor)
	{
		using func_t = decltype(&hkpResponseModifier::SetInvMassScalingForContact);
		static REL::Relocation<func_t> func{ RELOCATION_ID(61388, 62282) };
		func(a_mgr, a_body, a_constraintOwner, a_factor);
	}
}
