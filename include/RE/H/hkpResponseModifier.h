#pragma once

namespace RE
{
	class hkVector4;
	class hkpConstraintOwner;
	class hkpDynamicsContactMgr;
	class hkpRigidBody;

	class hkpResponseModifier
	{
	public:
		enum Flags
		{
			kMassScaling = 1,
			kCenterOfMassDisplacement = 2,
			kSurfaceVelocity = 4,
			kImpulseScaling = 8,
			kViscousSurface = 16,

			kAdditionalSizeModifiers = kMassScaling | kCenterOfMassDisplacement | kSurfaceVelocity,
		};

		static void SetInvMassScalingForContact(hkpDynamicsContactMgr* a_mgr, hkpRigidBody* a_body, hkpConstraintOwner& a_constraintOwner, const hkVector4& a_factor);
	};
	static_assert(std::is_empty_v<hkpResponseModifier>);
}
