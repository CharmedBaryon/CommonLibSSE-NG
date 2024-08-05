#pragma once

#include "RE/A/ActorState.h"
#include "RE/B/BGSAction.h"
#include "RE/B/BGSAnimationSequencer.h"

namespace RE
{
	class ActionInput
	{
	public:
		inline static constexpr auto RTTI = RTTI_ActionInput;
		inline static constexpr auto VTABLE = VTABLE_ActionInput;

		virtual ~ActionInput();  // 00

		// add
		virtual ActorState*            GetSourceActorState() const;  // 01 - { return nullptr; }
		virtual void                   Unk_02(void);                 // 02 - { return 0; }
		virtual BGSAnimationSequencer* GetSourceSequencer() const;   // 03 - { return nullptr; }

		// members
		NiPointer<TESObjectREFR> source;  // 08
		NiPointer<TESObjectREFR> target;  // 10
		BGSAction*               action;  // 18
		uint32_t                 unk20;   // 20
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(ActionInput) == 0x28);
}
