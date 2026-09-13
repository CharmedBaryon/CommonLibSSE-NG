#pragma once

#include "RE/C/ChildSelectorBase.h"

namespace RE
{
	class CombatBehaviorTreeNode;

	class ValueChildSelector : public ChildSelectorBase
	{
	public:
		static bool Validate(CombatBehaviorTreeNode* node);

		uint32_t SelectChild(CombatBehaviorTreeNode* node, uint32_t selected_ind);
	};
	static_assert(sizeof(ValueChildSelector) == 0x1);
}
