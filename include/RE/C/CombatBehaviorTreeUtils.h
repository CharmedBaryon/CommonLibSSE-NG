#pragma once

namespace RE
{
	class Actor;

	namespace CombatBehaviorTreeUtils
	{
		class CombatBehaviorAttacker
		{
		public:
			operator Actor*();
		};

		class CombatBehaviorTarget
		{
		public:
			operator Actor*();
		};
	}
}
