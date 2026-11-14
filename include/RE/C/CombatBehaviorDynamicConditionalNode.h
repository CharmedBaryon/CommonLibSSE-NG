#pragma once

#include "RE/A/AITimer.h"
#include "RE/C/CombatBehavior.h"

namespace RE
{
	class CombatBehaviorThread;

	class CombatBehaviorDynamicConditionalNode : public CombatBehaviorBranch
	{
	public:
		static bool Validate(CombatBehaviorTreeNode* node);

		CombatBehaviorDynamicConditionalNode(float interval);

		void Abort();
		void Enter();
		void Update();

		// members
		CombatBehaviorThread* child_thread;  // 00 TODO: unique_ptr?
		AITimer               timer;         // 08
	};
	static_assert(sizeof(CombatBehaviorDynamicConditionalNode) == 0x10);
}
