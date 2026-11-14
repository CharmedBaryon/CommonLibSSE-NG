#include "RE/C/CombatBehaviorBlock.h"

#include "RE/C/CombatBehaviorTreeNode.h"

namespace RE
{
	void CombatBehaviorBlock::Enter()
	{
		using func_t = decltype(&CombatBehaviorBlock::Enter);
		static REL::Relocation<func_t> func{ RELOCATION_ID(46633, 0) };
		return func(this);
	}

	void CombatBehaviorBlock::Exit()
	{
		using func_t = decltype(&CombatBehaviorBlock::Exit);
		static REL::Relocation<func_t> func{ RELOCATION_ID(46635, 0) };
		return func(this);
	}

	void CombatBehaviorBlock::Update()
	{
		using func_t = decltype(&CombatBehaviorBlock::Update);
		static REL::Relocation<func_t> func{ RELOCATION_ID(46634, 0) };
		return func(this);
	}
}
