#include "RE/C/CombatBehaviorTreeLinkNode.h"

namespace RE
{
	void CombatBehaviorTreeLinkNode::Enter(CombatBehaviorThread* a_thread)
	{
		using func_t = decltype(&CombatBehaviorTreeLinkNode::Enter);
		static REL::Relocation<func_t> func{ RELOCATION_ID(46330, 47574) };
		return func(this, a_thread);
	}

	bool CombatBehaviorTreeLinkNode::Validate(CombatBehaviorTreeNode* a_node) const
	{
		using func_t = decltype(&CombatBehaviorTreeLinkNode::Validate);
		static REL::Relocation<func_t> func{ RELOCATION_ID(46331, 47575) };
		return func(this, a_node);
	}

	const BSFixedString& CombatBehaviorTreeLinkNode::GetType() const
	{
		using func_t = decltype(&CombatBehaviorTreeLinkNode::GetType);
		static REL::Relocation<func_t> func{ RELOCATION_ID(46332, 47576) };
		return func(this);
	}
}
