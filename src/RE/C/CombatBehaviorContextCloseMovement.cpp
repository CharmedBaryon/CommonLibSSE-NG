#include "RE/C/CombatBehaviorContextCloseMovement.h"

namespace RE
{
	bool CombatBehaviorContextCloseMovement::CheckOutOfPosition() const
	{
		using func_t = decltype(&CombatBehaviorContextCloseMovement::CheckOutOfPosition);
		static REL::Relocation<func_t> func{ RELOCATION_ID(46697, 0) };
		return func(this);
	}

	bool CombatBehaviorContextCloseMovement::CheckOutOfRange() const
	{
		using func_t = decltype(&CombatBehaviorContextCloseMovement::CheckOutOfRange);
		static REL::Relocation<func_t> func{ RELOCATION_ID(46696, 0) };
		return func(this);
	}

	bool CombatBehaviorContextCloseMovement::CheckShouldFallbackToRanged() const
	{
		using func_t = decltype(&CombatBehaviorContextCloseMovement::CheckOutOfRange);
		static REL::Relocation<func_t> func{ RELOCATION_ID(46699, 0) };
		return func(this);
	}

	bool CombatBehaviorContextCloseMovement::CheckShouldStop(float R) const
	{
		using func_t = decltype(&CombatBehaviorContextCloseMovement::CheckShouldStop);
		static REL::Relocation<func_t> func{ RELOCATION_ID(46698, 0) };
		return func(this, R);
	}

	void CombatBehaviorContextCloseMovement::Enter()
	{
		using func_t = decltype(&CombatBehaviorContextCloseMovement::Enter);
		static REL::Relocation<func_t> func{ RELOCATION_ID(46695, 0) };
		return func(this);
	}

	void CombatBehaviorContextCloseMovement::SetTargetLocation(const NiPointer<CombatTargetLocation>& loc)
	{
		using func_t = decltype(&CombatBehaviorContextCloseMovement::SetTargetLocation);
		static REL::Relocation<func_t> func{ RELOCATION_ID(46700, 0) };
		return func(this, loc);
	}
}
