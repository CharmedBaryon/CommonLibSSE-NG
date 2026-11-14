#pragma once

#include "RE/C/ChildSelectorBase.h"

namespace RE
{
	class CombatBehaviorTreeNode;

	class NextChildSelector : public ChildSelectorBase
	{
	public:
		uint32_t SelectChild(CombatBehaviorTreeNode* node, uint32_t selected_ind);
	};
	static_assert(sizeof(NextChildSelector) == 0x1);
}
