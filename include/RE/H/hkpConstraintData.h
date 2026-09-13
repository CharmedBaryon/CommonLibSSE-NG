#pragma once

#include "RE/H/hkBaseTypes.h"
#include "RE/H/hkReferencedObject.h"
#include "RE/H/hkpConstraintInfo.h"

namespace RE
{
	class hkpConstraintInstance;
	class hkpConstraintQueryIn;
	class hkpConstraintQueryOut;
	class hkpSolverResults;
	struct hkpConstraintAtom;

	class hkpConstraintData : public hkReferencedObject
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkpConstraintData;
		inline static constexpr auto VTABLE = VTABLE_hkpConstraintData;

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

		struct ConstraintInfo : public hkpConstraintInfo
		{
			// members
			hkpConstraintAtom* atoms;           // 10
			std::uint32_t      sizeOfAllAtoms;  // 18
			std::uint32_t      pad1C;           // 1C
		};
		static_assert(sizeof(ConstraintInfo) == 0x20);

		struct RuntimeInfo
		{
			// members
			std::int32_t sizeOfExternalRuntime;  // 00
			std::int32_t numSolverResults;       // 04
		};
		static_assert(sizeof(RuntimeInfo) == 0x8);

		~hkpConstraintData() override;  // 00

		// add
		virtual void              SetMaxLinearImpulse(float a_maxImpulse);                                                                                // 03
		virtual hkReal            GetMaxLinearImpulse() const;                                                                                            // 04
		virtual void              SetSolvingMethod(SolvingMethod a_method);                                                                               // 05
		virtual hkResult          GetInertiaStabilizationFactor(hkReal& a_inertiaStabilizationFactorOut) const;                                           // 06
		virtual hkResult          SetInertiaStabilizationFactor(const hkReal a_inertiaStabilizationFactorIn);                                             // 07
		virtual void              SetBodyToNotify(std::int32_t a_bodyIdx);                                                                                // 08
		virtual std::uint8_t      GetNotifiedBodyIndex() const;                                                                                           // 09 - { return 0xff; }
		virtual bool              IsValid() const = 0;                                                                                                    // 0A
		virtual std::int32_t      GetType() const = 0;                                                                                                    // 0B
		virtual void              GetRuntimeInfo(bool a_wantRuntime, RuntimeInfo& a_infoOut) const = 0;                                                   // 0C
		virtual hkpSolverResults* GetSolverResults(hkpConstraintRuntime* a_runtime);                                                                      // 0D
		virtual void              AddInstance(hkpConstraintInstance* a_constraint, hkpConstraintRuntime* a_runtime, std::int32_t a_sizeOfRuntime) const;  // 0E
		virtual void              BuildJacobian(const hkpConstraintQueryIn& a_in, hkpConstraintQueryOut& a_out);                                          // 0F - deprecated
		virtual bool              IsBuildJacobianCallbackRequired() const;                                                                                // 10 - { return false; }
		virtual void              BuildJacobianCallback(const hkpConstraintQueryIn& a_in);                                                                // 11
		virtual void              GetConstraintInfo(ConstraintInfo& a_infoOut) const = 0;                                                                 // 12

		// members
		std::uint64_t userData;  // 10
	};
	static_assert(sizeof(hkpConstraintData) == 0x18);
}
