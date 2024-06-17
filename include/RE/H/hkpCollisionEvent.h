#pragma once

namespace RE
{
	class hkpRigidBody;
	class hkpSimpleConstraintContactMgr;

	struct hkpCollisionEvent
	{
	public:
		enum class CallbackSource
		{
			kSourceA = 0,
			kSourceB = 1,
			kSourceWorld
		};

		hkpCollisionEvent(CallbackSource a_source, hkpRigidBody* a_bodyA, hkpRigidBody* a_bodyB, hkpSimpleConstraintContactMgr* a_mgr) :
			source(a_source), contactMgr(a_mgr)
		{
			bodies[0] = a_bodyA;
			bodies[1] = a_bodyB;
		}

		// members
		CallbackSource                 source;      // 00
		hkpRigidBody*                  bodies[2];   // 04
		hkpSimpleConstraintContactMgr* contactMgr;  // 14
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(hkpCollisionEvent) == 0x20);
}
