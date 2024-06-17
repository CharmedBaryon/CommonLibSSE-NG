#pragma once

#include "RE/A/ActiveEffect.h"
#include "RE/B/BSTArray.h"
#include "RE/B/BSTSmartPointer.h"

namespace RE
{
	class TESQuest;
	class TESQuestTarget;

	class GuideEffect :
		public ActiveEffect  // 00
	{
	public:
		inline static constexpr auto RTTI = RTTI_GuideEffect;
		inline static constexpr auto VTABLE = VTABLE_GuideEffect;

		// override (ActiveEffect)
		virtual ~GuideEffect();          // 13
		virtual void Start() override;   // 14
		virtual void Finish() override;  // 15

		// members
		TESQuest*                 quest;        // 90
		TESQuestTarget*           questTarget;  // 98
		BSTArray<ObjectRefHandle> hazards;      // A0
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(GuideEffect) == 0xB8);
}
