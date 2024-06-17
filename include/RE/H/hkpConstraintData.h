#pragma once

#include "RE/H/hkReferencedObject.h"

namespace RE
{
	class hkpSolverResults;
	class hkpConstraintRuntime;

	class hkpConstraintData : public hkReferencedObject
	{
	public:
		enum ConstraintType
		{
			kBallAndSocket = 0,
			kHinge = 1,
			kLimitedHinge = 2,
			kPointToPath = 3,
			kPrismatic = 6,
			kRagdoll = 7,
			kStiffSpring = 8,
			kWheel = 9,
			kGeneric = 10,
			kContact = 11,
			kBreakable = 12,
			kMalleable = 13,
			kPointToPlane = 14,

			kPulley = 15,

			kRotational = 16,

			kHingeLimits = 18,
			kRagdollLimits = 19,

			kCustom = 20,

			kRackAndPinion = 21,
			kCogWheel = 22,

			kChainTypes = 100,
			kStiffSpringChain = 100,
			kBallSocketChain = 101,
			kPoweredChain = 102
		};

		enum SolvingMethod
		{
			kStabilized = 0,
			kOld = 1
		};

		struct RuntimeInfo
		{
			int32_t sizeOfExternalRuntime;
			int32_t numSolverResults;
		};

		inline static constexpr auto RTTI = RTTI_hkpConstraintData;
		inline static constexpr auto VTABLE = VTABLE_hkpConstraintData;

		~hkpConstraintData() override;  // 00

		// add
		virtual void             SetMaxLinearImpulse(float a_maxImpulse);                                                                              // 03
		virtual float            GetMaxLinearImpulse() const;                                                                                          // 04
		virtual void             SetSolvingMethod(SolvingMethod a_method);                                                                             // 05
		virtual hkResult         GetInertiaStabilizationFactor(float& a_inertiaStabilizationFactorOut) const;                                          // 06
		virtual hkResult         SetInertiaStabilizationFactor(const float a_inertiaStabilizationFactorIn);                                            // 07
		virtual void             SetBodyToNotify(int32_t a_bodyIdx);                                                                                   // 08
		virtual uint8_t          GetNotifiedBodyIndex() const;                                                                                         // 09
		virtual bool             IsValid() const = 0;                                                                                                  // 0A
		virtual int32_t          GetType() const = 0;                                                                                                  // 0B
		virtual void             GetRuntimeInfo(bool bWantRuntime, RuntimeInfo& a_infoOut) const = 0;                                                  // 0C
		virtual hkpSolverResults GetSolverResults(hkpConstraintRuntime* a_runtime);                                                                    // 0D
		virtual void             AddInstance(hkpConstraintInstance* a_constraint, hkpConstraintRuntime* a_runtime, int32_t a_sizeOfRuntime) const;     // 0E
		virtual void             RemoveInstance(hkpConstraintInstance* a_constraint, hkpConstraintRuntime* a_runtime, int32_t a_sizeOfRuntime) const;  // 0F

		// members
		uint64_t userData;  // 10
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(hkpConstraintData) == 0x18);
}
