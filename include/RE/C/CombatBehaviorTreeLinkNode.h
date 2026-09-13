#pragma once

#include "RE/C/CombatBehaviorTreeNode.h"

namespace RE
{
	class CombatBehaviorTreeLinkNode : public CombatBehaviorTreeNode
	{
	public:
		inline static constexpr auto RTTI = RTTI_CombatBehaviorTreeLinkNode;
		inline static constexpr auto VTABLE = VTABLE_CombatBehaviorTreeLinkNode;

		// override (CombatBehaviorTreeNode)
		void                 Enter(CombatBehaviorThread* a_thread) override;           // 02
		bool                 Validate(CombatBehaviorTreeNode* a_node) const override;  // 08
		const BSFixedString& GetType() const override;                                 // 09

		// members
		BSFixedString linkName;  // 28
	};
	static_assert(sizeof(CombatBehaviorTreeLinkNode) == 0x30);
}
