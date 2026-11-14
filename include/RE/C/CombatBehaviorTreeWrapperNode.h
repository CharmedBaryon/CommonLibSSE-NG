#pragma once

#include "RE/C/CombatBehaviorTreeNode.h"

namespace RE
{
	class CombatBehaviorTreeWrapperNode : public CombatBehaviorTreeNode
	{
	public:
		~CombatBehaviorTreeWrapperNode() = default;
		virtual const BSFixedString& GetName() override { return wrapped->GetName(); }
		virtual void                 Enter(CombatBehaviorThread* thread) override { return wrapped->Enter(thread); }
		virtual void                 Exit(CombatBehaviorThread* thread) override { return wrapped->Exit(thread); }
		virtual void                 Update(CombatBehaviorThread* thread) override { return wrapped->Update(thread); }
		virtual void                 Abort(CombatBehaviorThread* thread) override { return wrapped->Abort(thread); }
		virtual void                 SaveGame(CombatBehaviorThread* thread, BGSSaveFormBuffer* buf) override { return wrapped->SaveGame(thread, buf); }
		virtual void                 LoadGame(CombatBehaviorThread* thread, BGSLoadFormBuffer* buf) override { return wrapped->LoadGame(thread, buf); }
		virtual bool                 Validate(CombatBehaviorTreeNode* node) const override { return wrapped->Validate(node); }
		virtual const BSFixedString& GetType() const override { return wrapped->GetType(); }

		// members
		CombatBehaviorTreeNode* wrapped;  // 28
	};
	static_assert(sizeof(CombatBehaviorTreeWrapperNode) == 0x30);
}
