#pragma once

#include "RE/H/hkpCollisionEvent.h"
#include "RE/H/hkpRigidBody.h"

namespace RE
{
	class hkContactPoint;
	class hkpContactPointProperties;
	class hkpVelocityAccumulator;

	using hkpShapeKey = std::uint32_t;

	struct hkpContactPointEvent : public hkpCollisionEvent
	{
	public:
		enum class Type
		{
			kTOI,
			kExpandManifold,
			kManifold,

			kManifoldAtEndOfStep,
			kManifoldFromSavedContactPoint
		};

		inline hkpShapeKey* GetShapeKeys(std::uint32_t a_bodyIdx) const
		{
			if (a_bodyIdx == 0 || a_bodyIdx == 1) {
				if (bodies[a_bodyIdx]->numShapeKeysInContactPointProperties > 0) {
					return shapeKeyStorage + (a_bodyIdx * bodies[0]->numShapeKeysInContactPointProperties);
				}
			}
			return nullptr;
		}

		// members
		Type                       type;                            // 20
		std::uint32_t              pad24;                           // 24
		hkContactPoint*            contactPoint;                    // 28
		hkpContactPointProperties* contactPointProperties;          // 30
		bool                       firingCallbacksForFullManifold;  // 38
		bool                       firstCallbackForFullManifold;    // 39
		bool                       lastCallbackForFullManifold;     // 3A
		float*                     separatingVelocity;              // 40
		float*                     rotateNormal;                    // 48
		hkpShapeKey*               shapeKeyStorage;                 // 50
		hkpVelocityAccumulator*    accumulators[2];                 // 58
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(hkpContactPointEvent) == 0x68);
}
