#pragma once

#include "RE/B/BSFixedString.h"
#include "RE/B/BSTHashMap.h"
#include "RE/B/BSTSingleton.h"

namespace RE
{
	class CombatBehaviorTree;
	class CombatBehaviorTreeNode;

	class CombatBehaviorTreeManager : public BSTSingletonImplicit<CombatBehaviorTreeManager>
	{
	public:
		[[nodiscard]] static CombatBehaviorTreeManager* GetSingleton()
		{
			using func_t = decltype(&CombatBehaviorTreeManager::GetSingleton);
			static REL::Relocation<func_t> func{ RELOCATION_ID(32551, 33306) };
			return func();
		}

		const CombatBehaviorTreeNode* FindRootNode(const BSFixedString& a_name) const;
		const CombatBehaviorTree*     FindTree(const BSFixedString& a_name) const;
		void                          Init();
		void                          InitializeTrees();
		void                          RegisterBehaviorTree(CombatBehaviorTree* a_tree);

		// members
		BSTHashMap<BSFixedString, CombatBehaviorTree*> trees;  // 00
	};
	static_assert(sizeof(CombatBehaviorTreeManager) == 0x30);
}
