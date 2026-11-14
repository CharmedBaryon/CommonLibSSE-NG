#include "RE/R/RandomValueChildSelector.h"

namespace RE
{
	bool RandomValueChildSelector::Validate(CombatBehaviorTreeNode* node)
	{
		using func_t = decltype(&RandomValueChildSelector::Validate);
		static REL::Relocation<func_t> func{ RELOCATION_ID(46158, 0) };
		return func(node);
	}

	uint32_t RandomValueChildSelector::SelectChild(CombatBehaviorTreeNode* node, uint32_t a_selected_ind)
	{
		using func_t = decltype(&RandomValueChildSelector::SelectChild);
		static REL::Relocation<func_t> func{ RELOCATION_ID(46155, 0) };
		return func(this, node, a_selected_ind);
	}
}
