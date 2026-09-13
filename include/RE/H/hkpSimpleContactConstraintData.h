#pragma once

#include "RE/H/hkpConstraintData.h"
#include "RE/H/hkpDynamicsCpIdMgr.h"

namespace RE
{
	class hkContactPoint;
	class hkpSimpleContactConstraintAtom;
	struct hkpBodyVelocity;
	struct hkpSimpleConstraintInfoInitInput;

	class hkpSimpleContactConstraintData : public hkpConstraintData
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkpSimpleContactConstraintData;
		inline static constexpr auto VTABLE = VTABLE_hkpSimpleContactConstraintData;

		~hkpSimpleContactConstraintData() override;  // 00

		// override (hkpConstraintData)
		bool              IsValid() const override;                                                   // 0A
		std::int32_t      GetType() const override;                                                   // 0B
		void              GetRuntimeInfo(bool a_wantRuntime, RuntimeInfo& a_infoOut) const override;  // 0C
		hkpSolverResults* GetSolverResults(hkpConstraintRuntime* a_runtime) override;                 // 0D
		void              GetConstraintInfo(ConstraintInfo& a_infoOut) const override;                // 12

		// add
		virtual void CollisionResponseBeginCallback(const hkContactPoint& a_cp, hkpSimpleConstraintInfoInitInput& a_inA, hkpBodyVelocity& a_velA, hkpSimpleConstraintInfoInitInput& a_inB, hkpBodyVelocity& a_velB);                         // 13
		virtual void CollisionResponseEndCallback(const hkContactPoint& a_cp, hkReal a_impulseApplied, hkpSimpleConstraintInfoInitInput& a_inA, hkpBodyVelocity& a_velA, hkpSimpleConstraintInfoInitInput& a_inB, hkpBodyVelocity& a_velB);  // 14

		// members
		hkpDynamicsCpIdMgr              idMgrA;      // 18
		void*                           clientData;  // 30
		hkpConstraintInstance*          constraint;  // 38
		hkpSimpleContactConstraintAtom* atom;        // 40
		std::int32_t                    atomSize;    // 48
		std::uint32_t                   pad4C;       // 4C
	};
	static_assert(sizeof(hkpSimpleContactConstraintData) == 0x50);
}
