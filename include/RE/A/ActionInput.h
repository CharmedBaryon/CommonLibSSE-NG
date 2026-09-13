#pragma once

#include "RE/N/NiSmartPointer.h"
#include "RE/T/TESObjectREFR.h"

namespace RE
{
	class ActorState;
	class BGSAction;
	class BGSAnimationSequencer;

	class ActionInput
	{
	public:
		inline static constexpr auto RTTI = RTTI_ActionInput;
		inline static constexpr auto VTABLE = VTABLE_ActionInput;

		enum class Priority
		{
			kImperative = 0,
			kQueue = 1,
			kTry = 2,
		};

		virtual ~ActionInput();  // 00

		// add
		virtual ActorState*            GetSourceActorState() const;  // 01 - { return nullptr; }
		virtual void                   Unk_02(void);                 // 02 - { return 0; }
		virtual BGSAnimationSequencer* GetSourceSequencer() const;   // 03 - { return nullptr; }

		// members
		NiPointer<TESObjectREFR>              source;    // 08
		NiPointer<TESObjectREFR>              target;    // 10
		BGSAction*                            action;    // 18
		REX::EnumSet<Priority, std::uint32_t> priority;  // 20
	};
	static_assert(sizeof(ActionInput) == 0x28);
}
