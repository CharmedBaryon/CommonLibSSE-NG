#pragma once

#include "RE/B/BSFixedString.h"
#include "RE/B/BSTArray.h"

namespace RE
{
	class BGSLoadFormBuffer;
	class BGSSaveFormBuffer;
	class CombatBehaviorThread;

	class CombatBehaviorTreeNode
	{
	public:
		inline static constexpr auto RTTI = RTTI_CombatBehaviorTreeNode;
		inline static constexpr auto VTABLE = VTABLE_CombatBehaviorTreeNode;

		CombatBehaviorTreeNode();
		virtual ~CombatBehaviorTreeNode();  // 00

		virtual const BSFixedString& GetName();                                                                      // 01
		virtual void                 Enter(CombatBehaviorThread* a_thread);                                          // 02
		virtual void                 Exit(CombatBehaviorThread* a_thread);                                           // 03
		virtual void                 Update(CombatBehaviorThread* a_thread);                                         // 04
		virtual void                 Abort(CombatBehaviorThread* a_thread);                                          // 05
		virtual void                 SaveGame(CombatBehaviorThread* a_thread, BGSSaveFormBuffer* a_saveGameBuffer);  // 06
		virtual void                 LoadGame(CombatBehaviorThread* a_thread, BGSLoadFormBuffer* a_loadGameBuffer);  // 07
		virtual bool                 Validate(CombatBehaviorTreeNode* a_node) const;                                 // 08
		virtual const BSFixedString& GetType() const;                                                                // 09

		void                    AddChild(CombatBehaviorTreeNode* a_child);
		void                    AddChildren(const BSTArray<CombatBehaviorTreeNode*>& a_children);
		CombatBehaviorTreeNode* FindChild(const BSFixedString& a_name) const;
		std::int32_t            FindChildIndex(const BSFixedString& a_name) const;
		CombatBehaviorTreeNode* GetRoot();
		void                    SetVftable(REL::VariantID a_id);

		TES_HEAP_REDEFINE_NEW();

		// members
		BSFixedString                          name;      // 08
		CombatBehaviorTreeNode*                parent;    // 10
		BSStaticArray<CombatBehaviorTreeNode*> children;  // 18
	};
	static_assert(sizeof(CombatBehaviorTreeNode) == 0x28);
}
