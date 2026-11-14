#pragma once

#include "RE/A/AITimeStamp.h"
#include "RE/B/BSTHashMap.h"
#include "RE/C/CombatBehaviorStack.h"
#include "RE/C/CombatBlackboardKey.h"

namespace RE
{
	class CombatBlackboard
	{
	public:
		template <typename T>
		T GetValue(const CombatBlackboardKey<T>& key) const
		{
			if (auto it = stack_offsets.find(&key); it != stack_offsets.end()) {
				return stack.Access<T>(it->second);
			} else {
				return T();
			}
		}

		// TODO: add overrides for found instantations
		//AITimeStamp GetValue(const CombatBlackboardKey<AITimeStamp>& key) const;

		// members
		BSTHashMap<const CombatBlackboardKeyBase*, uint32_t> stack_offsets;  // 00
		CombatBehaviorStack                                  stack;          // 30
		uint32_t                                             flags;          // 40 -- see CombatBlackboardFlag
		uint32_t                                             pad44;          // 44
	};
	static_assert(sizeof(CombatBlackboard) == 0x48);
}
