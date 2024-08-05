#pragma once

#include "RE/H/hkReferencedObject.h"

namespace RE
{
	class hkaSkeleton;
	class hkpConstraintInstance;

	class hkaRagdollInstance : public hkReferencedObject
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkaRagdollInstance;
		inline static constexpr auto VTABLE = VTABLE_hkaRagdollInstance;

		~hkaRagdollInstance() override;  // 00

		// members
		hkArray<hkpRigidBody*>          rigidBodies;         // 10
		hkArray<hkpConstraintInstance*> constraints;         // 20
		hkArray<int>                    boneToRigidBodyMap;  // 30
		hkRefPtr<const hkaSkeleton>     skeleton;            // 40
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(hkaRagdollInstance) == 0x48);
}
