#include "RE/V/ValueChildSelector.h"

namespace RE
{
	bool ValueChildSelector::Validate(CombatBehaviorTreeNode* node)
	{
		using func_t = decltype(&ValueChildSelector::Validate);
		static REL::Relocation<func_t> func{ RELOCATION_ID(46164, 0) };
		return func(node);
	}

	uint32_t ValueChildSelector::SelectChild(CombatBehaviorTreeNode* node, uint32_t a_selected_ind)
	{
		using func_t = decltype(&ValueChildSelector::SelectChild);
		static REL::Relocation<func_t> func{ RELOCATION_ID(46163, 0) };
		return func(this, node, a_selected_ind);
	}
}
