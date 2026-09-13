#include "RE/C/CombatBehaviorTree.h"

namespace RE
{
	CombatBehaviorTree::TreeBuilder::TreeBuilder(CombatBehaviorTreeNode* a_node)
	{
		using func_t = CombatBehaviorTree::TreeBuilder*(CombatBehaviorTree::TreeBuilder*, CombatBehaviorTreeNode*);
		static REL::Relocation<func_t> func{ RELOCATION_ID(46266, 47521) };
		func(this, a_node);
	}

	CombatBehaviorTreeNode* CombatBehaviorTree::TreeBuilder::GetNode()
	{
		using func_t = decltype(&CombatBehaviorTree::TreeBuilder::GetNode);
		static REL::Relocation<func_t> func{ RELOCATION_ID(46257, 47512) };
		return func(this);
	}

	CombatBehaviorTree::TreeBuilder& CombatBehaviorTree::TreeBuilder::operator[](const TreeBuilder& a_other)
	{
		using func_t = decltype(&CombatBehaviorTree::TreeBuilder::operator[]);
		static REL::Relocation<func_t> func{ RELOCATION_ID(46256, 47511) };
		return func(this, a_other);
	}

	CombatBehaviorTree::TreeBuilder &CombatBehaviorTree::TreeBuilder::operator,(const TreeBuilder& a_other)
	{
		using func_t = decltype(&CombatBehaviorTree::TreeBuilder::operator, );
		static REL::Relocation<func_t> func{ RELOCATION_ID(46255, 47510) };
		return func(this, a_other);
	}

	CombatBehaviorTree::CombatBehaviorTree(const char* a_name)
	{
		using func_t = CombatBehaviorTree*(CombatBehaviorTree*, const char*);
		static REL::Relocation<func_t> func{ RELOCATION_ID(46262, 47517) };
		func(this, a_name);
	}

	void CombatBehaviorTree::CreateTree(CombatBehaviorTreeNode* a_node)
	{
		using func_t = decltype(&CombatBehaviorTree::CreateTree);
		static REL::Relocation<func_t> func{ RELOCATION_ID(46263, 47518) };
		func(this, a_node);
	}

	CombatBehaviorTree::TreeBuilder CombatBehaviorTree::AddNode(const char* a_name, CombatBehaviorTreeNode* a_node)
	{
		using func_t = decltype(&CombatBehaviorTree::AddNode);
		static REL::Relocation<func_t> func{ RELOCATION_ID(46261, 47516) };
		return func(a_name, a_node);
	}

	CombatBehaviorTreeNode* CombatBehaviorTree::CreateLink(const char* a_name)
	{
		using func_t = decltype(&CombatBehaviorTree::CreateLink);
		static REL::Relocation<func_t> func{ RELOCATION_ID(46262, 47517) };
		return func(a_name);
	}

	Actor* CombatBehaviorTree::GetAttacker()
	{
		using func_t = decltype(&CombatBehaviorTree::GetAttacker);
		static REL::Relocation<func_t> func{ RELOCATION_ID(46264, 47519) };
		return func();
	}

	Actor* CombatBehaviorTree::GetTarget()
	{
		using func_t = decltype(&CombatBehaviorTree::GetTarget);
		static REL::Relocation<func_t> func{ RELOCATION_ID(46265, 47520) };
		return func();
	}
}
