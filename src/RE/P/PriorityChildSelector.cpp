#include "RE/P/PriorityChildSelector.h"

namespace RE
{
	bool PriorityChildSelector::Validate(CombatBehaviorTreeNode* node)
	{
		using func_t = decltype(&PriorityChildSelector::Validate);
		static REL::Relocation<func_t> func{ RELOCATION_ID(46154, 0) };
		return func(node);
	}

	uint32_t PriorityChildSelector::SelectChild(CombatBehaviorTreeNode* node, uint32_t selected)
	{
		using func_t = decltype(&PriorityChildSelector::SelectChild);
		static REL::Relocation<func_t> func{ RELOCATION_ID(46153, 0) };
		return func(this, node, selected);
	}
}
