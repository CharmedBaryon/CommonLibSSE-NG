#pragma once

#include "RE/C/ChildSelectorBase.h"

namespace RE
{
	class PriorityChildSelector : public ChildSelectorBase
	{
	public:
		static bool Validate(CombatBehaviorTreeNode* node);

		uint32_t SelectChild(CombatBehaviorTreeNode* node, uint32_t selected);
	};
	static_assert(sizeof(PriorityChildSelector) == 0x1);
}
