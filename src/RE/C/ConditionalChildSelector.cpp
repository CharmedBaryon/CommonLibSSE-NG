#include "RE/C/ConditionalChildSelector.h"

namespace RE
{
	bool ConditionalChildSelector::Validate(CombatBehaviorTreeNode* node)
	{
		using func_t = decltype(&ConditionalChildSelector::Validate);
		static REL::Relocation<func_t> func{ RELOCATION_ID(46166, 0) };
		return func(node);
	}

	uint32_t ConditionalChildSelector::SelectChild(CombatBehaviorTreeNode* node, uint32_t selected)
	{
		using func_t = decltype(&ConditionalChildSelector::SelectChild);
		static REL::Relocation<func_t> func{ RELOCATION_ID(46165, 0) };
		return func(this, node, selected);
	}
}
