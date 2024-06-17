#pragma once

#include "RE/H/hkpConstraintAtom.h"
#include "RE/H/hkpConstraintData.h"
#include "RE/H/hkpSolverResults.h"

namespace RE
{
	class hkpLimitedHingeConstraintData : public hkpConstraintData
	{
	public:
		enum SolverResultType
		{
			kMotor = 0,
			kFriction,
			kLimit,

			kAngle0,
			kAngle1,

			kLinear0,
			kLinear1,
			kLinear2,

			kNUM
		};

		inline static constexpr auto RTTI = RTTI_hkpLimitedHingeConstraintData;
		inline static constexpr auto VTABLE = VTABLE_hkpLimitedHingeConstraintData;

		struct Atoms
		{
			struct hkpSetLocalTransformsConstraintAtom transforms;
			struct hkpSetupStabilizationAtom           setupStabilization;
			struct hkpAngMotorConstraintAtom           angMotor;
			struct hkpAngFrictionConstraintAtom        angFriction;
			struct hkpAngLimitConstraintAtom           angLimit;
			struct hkp2dAngConstraintAtom              twoDAng;
			struct hkpBallSocketConstraintAtom         ballSocket;
		};
		static_assert(sizeof(Atoms) == 0xF0);

		struct Runtime
		{
			inline float getCurrentAngle()
			{
				return solverResults[SolverResultType::kLimit].data * -1.f;
			}

			hkpSolverResults solverResults[SolverResultType::kNUM];  // 00
			bool             previousTargetInitialized;              // 40
			float            previousTargetAngle;                    // 44
		};
		static_assert(sizeof(Runtime) == 0x48);

		// members
		Atoms atoms;  // 18
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(hkpLimitedHingeConstraintData) == 0x110);
}
