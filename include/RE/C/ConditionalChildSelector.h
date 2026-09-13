#pragma once

#include "RE/C/ChildSelectorBase.h"

namespace RE
{
	class CombatBehaviorTreeNode;

	class ConditionalChildSelector : public ChildSelectorBase
	{
	public:
		static bool Validate(CombatBehaviorTreeNode* node);

		uint32_t SelectChild(CombatBehaviorTreeNode* node, uint32_t selected);
	};
	static_assert(sizeof(ConditionalChildSelector) == 0x1);
}
