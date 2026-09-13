#pragma once

#include "RE/B/BSFixedString.h"

namespace RE
{
	class CombatBehaviorTreeNode;

	class ChildSelectorBase
	{
	public:
		static bool Validate(CombatBehaviorTreeNode*);
		static bool ValidateChildren(CombatBehaviorTreeNode* node, const BSFixedString& type);

		uint32_t SelectChild(CombatBehaviorTreeNode*, [[maybe_unused]] uint32_t selected_ind) const;
	};
}
