#pragma once

#include "RE/B/BSFixedString.h"
#include "RE/B/BSTHashMap.h"

namespace RE
{
	class CombatBlackboardFlag;
	class CombatBlackboardKeyBase;

	class CombatBlackboardManager
	{
	public:
		static CombatBlackboardManager* GetSingleton();

		void                           AddFlag(const CombatBlackboardFlag* val);
		void                           AddMember(const CombatBlackboardKeyBase* val);
		const CombatBlackboardFlag*    GetFlag(uint32_t flag);
		const CombatBlackboardKeyBase* GetMember(const BSFixedString& name);

		// members
		BSTHashMap<BSFixedString, CombatBlackboardKeyBase*> keys;   // 00
		BSTHashMap<uint32_t, CombatBlackboardFlag*>         flags;  // 30
	};
	static_assert(sizeof(CombatBlackboardManager) == 0x60);
}
