#pragma once

#include "RE/C/CombatBehaviorTreeNode.h"

namespace RE
{
	class CombatBehaviorTreeRootNode : public CombatBehaviorTreeNode
	{
	public:
		~CombatBehaviorTreeRootNode() = default;
		void                 Enter(CombatBehaviorThread* thread) override;
		void                 Update(CombatBehaviorThread* thread) override;
		void                 Abort(CombatBehaviorThread* thread) override;
		void                 SaveGame(CombatBehaviorThread* thread, BGSSaveFormBuffer* buf) override;
		void                 LoadGame(CombatBehaviorThread* thread, BGSLoadFormBuffer* buf) override;
		bool                 Validate(CombatBehaviorTreeNode* node) const override;
		const BSFixedString& GetType() const override;
	};
	static_assert(sizeof(CombatBehaviorTreeRootNode) == 0x28);
}
