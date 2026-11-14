#pragma once

namespace RE
{
	class CombatBehaviorAccessors
	{
	public:
		static void Fail();
		static void Finish();
		static void Finish(bool failed);
	};
}
