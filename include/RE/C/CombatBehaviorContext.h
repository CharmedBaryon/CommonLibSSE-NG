#pragma once

namespace RE
{
#pragma warning(push)
#pragma warning(disable: 4324)  // structure was padded due to alignment specifier

	class CombatBehaviorTreeNode;

	class alignas(4) CombatBehaviorContext
	{
	public:
		static bool Validate(CombatBehaviorTreeNode* node);

		void Enter() {}
		void Exit() {}
	};

#pragma warning(pop)
}
