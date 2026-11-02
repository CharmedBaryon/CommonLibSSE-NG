#pragma once

#include "RE/B/BSFixedString.h"
#include "RE/B/BSTArray.h"
#include "RE/C/CombatBehaviorThread.h"

namespace RE
{
	class BGSLoadFormBuffer;
	class BGSSaveFormBuffer;

	class CombatBehaviorTreeNode
	{
	public:
		inline static constexpr auto RTTI = RTTI_CombatBehaviorTreeNode;
		inline static constexpr auto VTABLE = VTABLE_CombatBehaviorTreeNode;

		CombatBehaviorTreeNode();
		virtual ~CombatBehaviorTreeNode() = default;  // 00

		virtual const BSFixedString& GetName() { return name; };                                                                                          // 01
		virtual void                 Enter([[maybe_unused]] CombatBehaviorThread* a_thread) {};                                                           // 02
		virtual void                 Exit([[maybe_unused]] CombatBehaviorThread* a_thread) {};                                                            // 03
		virtual void                 Update(CombatBehaviorThread* a_thread) { a_thread->Ascend(); };                                                      // 04
		virtual void                 Abort(CombatBehaviorThread* a_thread) { a_thread->Ascend(); };                                                       // 05
		virtual void                 SaveGame([[maybe_unused]] CombatBehaviorThread* a_thread, [[maybe_unused]] BGSSaveFormBuffer* a_saveGameBuffer) {};  // 06
		virtual void                 LoadGame([[maybe_unused]] CombatBehaviorThread* a_thread, [[maybe_unused]] BGSLoadFormBuffer* a_loadGameBuffer) {};  // 07
		virtual bool                 Validate([[maybe_unused]] const CombatBehaviorTreeNode* a_node) { return true; };                                    // 08
		virtual const BSFixedString& GetType() = 0;                                                                                                       // 09

		void AddChild(CombatBehaviorTreeNode* a_child);
		void AddChildren(const BSTArray<CombatBehaviorTreeNode*>& a_children);

		// members
		BSFixedString            name;        // 08
		CombatBehaviorTreeNode*  parent;      // 10
		CombatBehaviorTreeNode** children;    // 18
		std::uint32_t            childCount;  // 20
		std::uint32_t            pad24;       // 24

	protected:
		CombatBehaviorTreeNode* Ctor();
	};
	static_assert(sizeof(CombatBehaviorTreeNode) == 0x28);
}
