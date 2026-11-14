#pragma once

namespace RE
{
	class hkVector4;
	class hkpRigidBody;
	struct hkpContactPointEvent;

	class hkpAddModifierUtil
	{
	public:
		static void SetInvMassScalingForContact(const hkpContactPointEvent& a_event, hkpRigidBody* a_body, const hkVector4& a_factor);
	};
	static_assert(std::is_empty_v<hkpAddModifierUtil>);
}
