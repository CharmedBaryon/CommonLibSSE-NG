#pragma once

#include "RE/C/CombatBehaviorTreeWrapperNode.h"

namespace RE
{
	template <typename T>
	class CombatBehaviorTreeValueNode : public CombatBehaviorTreeWrapperNode
	{
		static BSFixedString GetClassType()
		{
			char a[256] = "CombatBehaviorTreeValueNode - ";
			strcat_s(a, 0x104, typeid(T).name());
			return BSFixedString(a);
		}

	public:
		const BSFixedString& GetType() const override
		{
			static BSFixedString ans = GetClassType();
			return ans;
		}

		virtual T GetValue() = 0;
	};
	static_assert(sizeof(CombatBehaviorTreeValueNode<void*>) == 0x30);
}
