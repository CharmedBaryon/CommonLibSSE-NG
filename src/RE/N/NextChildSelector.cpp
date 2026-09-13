#include "RE/N/NextChildSelector.h"

namespace RE
{
	uint32_t NextChildSelector::SelectChild(CombatBehaviorTreeNode* node, uint32_t a_selected_ind)
	{
		using func_t = decltype(&NextChildSelector::SelectChild);
		static REL::Relocation<func_t> func{ RELOCATION_ID(46152, 0) };
		return func(this, node, a_selected_ind);
	}
}
