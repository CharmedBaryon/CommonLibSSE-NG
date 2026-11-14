#include "RE/C/CombatBehaviorContextMelee.h"

namespace RE
{
	void CombatBehaviorContextMelee::CalculateAnimationData()
	{
		using func_t = decltype(&CombatBehaviorContextMelee::CalculateAnimationData);
		static REL::Relocation<func_t> func{ RELOCATION_ID(48146, 0) };
		return func(this);
	}

	bool CombatBehaviorContextMelee::CheckAttack(CombatAttackData* attack)
	{
		using func_t = decltype(&CombatBehaviorContextMelee::CheckAttack);
		static REL::Relocation<func_t> func{ RELOCATION_ID(48140, 0) };
		return func(this, attack);
	}

	bool CombatBehaviorContextMelee::CheckAttackRange()
	{
		using func_t = decltype(&CombatBehaviorContextMelee::CheckAttackRange);
		static REL::Relocation<func_t> func{ RELOCATION_ID(48141, 0) };
		return func(this);
	}

	void CombatBehaviorContextMelee::Enter()
	{
		return GatherAttackData();
	}

	void CombatBehaviorContextMelee::FinishedAttack()
	{
		using func_t = decltype(&CombatBehaviorContextMelee::FinishedAttack);
		static REL::Relocation<func_t> func{ RELOCATION_ID(48142, 0) };
		return func(this);
	}

	void CombatBehaviorContextMelee::GatherAttackData()
	{
		using func_t = decltype(&CombatBehaviorContextMelee::GatherAttackData);
		static REL::Relocation<func_t> func{ RELOCATION_ID(48145, 0) };
		return func(this);
	}

	bool CombatBehaviorContextMelee::StartAttack()
	{
		using func_t = decltype(&CombatBehaviorContextMelee::StartAttack);
		static REL::Relocation<func_t> func{ RELOCATION_ID(48139, 0) };
		return func(this);
	}
}
