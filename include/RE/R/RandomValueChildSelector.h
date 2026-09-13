#pragma once

#include "RE/C/ChildSelectorBase.h"

namespace RE
{
	class CombatBehaviorTreeNode;

	class RandomValueChildSelector : public ChildSelectorBase
	{
	public:
		static bool Validate(CombatBehaviorTreeNode* node);

		uint32_t SelectChild(CombatBehaviorTreeNode* node, uint32_t selected_ind);

		// members
		uint32_t tried_mask;  // 00
	};
	static_assert(sizeof(RandomValueChildSelector) == 0x4);
}
