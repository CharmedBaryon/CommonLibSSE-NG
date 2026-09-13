#include "RE/C/CombatBehaviorTreeManager.h"

namespace RE
{
	const CombatBehaviorTree* CombatBehaviorTreeManager::FindTree(const BSFixedString& a_name) const
	{
		using func_t = decltype(&CombatBehaviorTreeManager::FindTree);
		static REL::Relocation<func_t> func{ RELOCATION_ID(46272, 47527) };
		return func(this, a_name);
	}

	const CombatBehaviorTreeNode* CombatBehaviorTreeManager::FindRootNode(const BSFixedString& a_name) const
	{
		using func_t = decltype(&CombatBehaviorTreeManager::FindRootNode);
		static REL::Relocation<func_t> func{ RELOCATION_ID(46273, 47528) };
		return func(this, a_name);
	}

	void CombatBehaviorTreeManager::RegisterBehaviorTree(CombatBehaviorTree* a_tree)
	{
		using func_t = decltype(&CombatBehaviorTreeManager::RegisterBehaviorTree);
		static REL::Relocation<func_t> func{ RELOCATION_ID(46271, 47526) };
		return func(this, a_tree);
	}

	void CombatBehaviorTreeManager::Init()
	{
		using func_t = decltype(&CombatBehaviorTreeManager::Init);
		static REL::Relocation<func_t> func{ RELOCATION_ID(46274, 47529) };
		return func(this);
	}

	void CombatBehaviorTreeManager::InitializeTrees()
	{
		using func_t = decltype(&CombatBehaviorTreeManager::InitializeTrees);
		static REL::Relocation<func_t> func{ RELOCATION_ID(46275, 47530) };
		return func(this);
	}
}
