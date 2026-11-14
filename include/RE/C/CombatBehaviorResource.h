#pragma once

#include "RE/B/BSFixedString.h"
#include "RE/B/BSTArray.h"
#include "RE/B/BSTTuple.h"
#include "RE/N/NiRefObject.h"

namespace RE
{
	class CombatBehaviorController;
	class CombatBehaviorThread;

	class CombatBehaviorResource : public NiRefObject
	{
	public:
		CombatBehaviorResource(CombatBehaviorController* controller, const BSFixedString& name);
		~CombatBehaviorResource() = default;

		bool AcquireResource(CombatBehaviorThread* thread, uint32_t priority, bool can_suspend);
		void ClearOwner(CombatBehaviorThread* thread);
		void ForceAcquireResource(CombatBehaviorThread* new_owner);
		void ReleaseResource(CombatBehaviorThread* thread);

		// members
		CombatBehaviorController*                      controller;     // 10
		BSFixedString                                  name;           // 18
		CombatBehaviorThread*                          owner;          // 20
		BSTArray<CombatBehaviorThread*>                suspended;      // 28
		BSTArray<BSTTuple<int, CombatBehaviorThread*>> subscribersPQ;  // 40
	};
	static_assert(sizeof(CombatBehaviorResource) == 0x58);
}
