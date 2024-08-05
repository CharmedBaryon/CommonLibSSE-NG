#pragma once

#include "RE/H/hkpArrayAction.h"

namespace RE
{
	class hkpEaseConstraintsAction : public hkpArrayAction
	{
	public:
		inline static constexpr auto RTTI = RTTI_hkpEaseConstraintsAction;
		inline static constexpr auto VTABLE = VTABLE_hkpEaseConstraintsAction;

		virtual ~hkpEaseConstraintsAction() override;  // 00

		// add
		void       ApplyAction(const hkStepInfo& a_stepInfo) override;                                                         // 03
		hkpAction* Clone(const hkArray<hkpEntity*>& a_newEntities, const hkArray<hkpPhantom*>& a_newPhantoms) const override;  // 07

		// members
		float                           duration;             // 40
		float                           timePassed;           // 44
		hkArray<hkpConstraintInstance*> originalConstraints;  // 48
		hkArray<float>                  originalLimits;       // 58
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(hkpEaseConstraintsAction) == 0x68);
}
