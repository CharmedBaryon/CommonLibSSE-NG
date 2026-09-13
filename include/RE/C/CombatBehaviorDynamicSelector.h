#pragma once

namespace RE
{
	template <typename Selector>
	class CombatBehaviorDynamicSelector : public CombatBehaviorNode
	{
	public:
		static bool Validate(CombatBehaviorTreeNode* node)
		{
			return CombatBehaviorNode::Validate(node) && Selector::Validate(node);
		}

		// TODO
	};
}
