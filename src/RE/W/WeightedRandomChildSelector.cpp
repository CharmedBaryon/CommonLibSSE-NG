#include "RE/W/WeightedRandomChildSelector.h"

namespace RE
{
	bool WeightedRandomChildSelector::Validate(CombatBehaviorTreeNode* node)
	{
		using func_t = decltype(&WeightedRandomChildSelector::Validate);
		static REL::Relocation<func_t> func{ RELOCATION_ID(46162, 0) };
		return func(node);
	}

	uint32_t WeightedRandomChildSelector::SelectChild(CombatBehaviorTreeNode* node, uint32_t a_selected_ind)
	{
		using func_t = decltype(&WeightedRandomChildSelector::SelectChild);
		static REL::Relocation<func_t> func{ RELOCATION_ID(46159, 0) };
		return func(this, node, a_selected_ind);
	}
}
