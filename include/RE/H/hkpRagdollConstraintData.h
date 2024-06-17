#pragma once

#include "RE/H/hkpConstraintAtom.h"
#include "RE/H/hkpConstraintData.h"
#include "RE/H/hkpSolverResults.h"

namespace RE
{
	class hkpRagdollConstraintData : public hkpConstraintData
	{
	public:
		enum SolverResultType
		{
			kMotor0 = 0,
			kMotor1,
			kMotor2,

			kFriction0,
			kFriction1,
			kFriction2,

			kTwist,
			kCone,
			kPlane,

			kLinear0,
			kLinear1,
			kLinear2,

			kNUM
		};

		inline static constexpr auto RTTI = RTTI_hkpRagdollConstraintData;
		inline static constexpr auto VTABLE = VTABLE_hkpRagdollConstraintData;

		struct Atoms
		{
			struct hkpSetLocalTransformsConstraintAtom transforms;
			struct hkpSetupStabilizationAtom           setupStabilization;
			struct hkpRagdollMotorConstraintAtom       ragdollMotors;
			struct hkpAngFrictionConstraintAtom        angFriction;
			struct hkpTwistLimitConstraintAtom         twistLimit;
			struct hkpConeLimitConstraintAtom          coneLimit;
			struct hkpConeLimitConstraintAtom          planesLimit;
			struct hkpBallSocketConstraintAtom         ballSocket;
		};
		static_assert(sizeof(Atoms) == 0x160);

		struct Runtime
		{
			hkpSolverResults solverResults[SolverResultType::kNUM];  // 00
			bool             previousTargetInitialized[3];           // 60
			float            previousTargetAngle[3];                 // 64
			float            coneAngle;                              // 70
		};
		static_assert(sizeof(Runtime) == 0x74);

		// members
		Atoms atoms;  // 18
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(hkpRagdollConstraintData) == 0x180);
}
