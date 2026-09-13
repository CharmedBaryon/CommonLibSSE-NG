#include "RE/C/CombatBehaviorTreeNode.h"

namespace RE
{
	CombatBehaviorTreeNode::CombatBehaviorTreeNode()
	{
		using func_t = CombatBehaviorTreeNode*(CombatBehaviorTreeNode*);
		static REL::Relocation<func_t> func{ RELOCATION_ID(46301, 0) };
		func(this);
	}

	void CombatBehaviorTreeNode::AddChild(CombatBehaviorTreeNode* a_child)
	{
		using func_t = decltype(&CombatBehaviorTreeNode::AddChild);
		static REL::Relocation<func_t> func{ RELOCATION_ID(46304, 47548) };
		func(this, a_child);
	}

	void CombatBehaviorTreeNode::AddChildren(const BSTArray<CombatBehaviorTreeNode*>& a_children)
	{
		using func_t = decltype(&CombatBehaviorTreeNode::AddChildren);
		static REL::Relocation<func_t> func{ RELOCATION_ID(46305, 47549) };
		func(this, a_children);
	}

	CombatBehaviorTreeNode* CombatBehaviorTreeNode::FindChild(const BSFixedString& ch_name) const
	{
		using func_t = decltype(&CombatBehaviorTreeNode::FindChild);
		static REL::Relocation<func_t> func{ RELOCATION_ID(46306, 0) };
		return func(this, ch_name);
	}

	int32_t CombatBehaviorTreeNode::FindChildIndex(const BSFixedString& ch_name) const
	{
		using func_t = decltype(&CombatBehaviorTreeNode::FindChildIndex);
		static REL::Relocation<func_t> func{ RELOCATION_ID(46307, 0) };
		return func(this, ch_name);
	}

	CombatBehaviorTreeNode* CombatBehaviorTreeNode::GetRoot()
	{
		CombatBehaviorTreeNode* cur = this;
		while (cur->parent)
			cur = cur->parent;
		return cur;
	}

	void CombatBehaviorTreeNode::SetVftable(REL::VariantID id)
	{
		*(uint64_t*)this = id.address();
	}
}
