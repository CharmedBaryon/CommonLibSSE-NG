#pragma once

#include "RE/A/ActorInventoryEvent.h"
#include "RE/A/ActorValues.h"
#include "RE/B/BSTEvent.h"
#include "RE/D/DualValueModifierEffect.h"

namespace RE
{
	class EnhanceWeaponEffect :
		public DualValueModifierEffect,           // 00
		public BSTEventSink<ActorInventoryEvent>  // A0
	{
	public:
		inline static constexpr auto RTTI = RTTI_EnhanceWeaponEffect;
		inline static constexpr auto VTABLE = VTABLE_EnhanceWeaponEffect;

		// override (ActiveEffect)
		virtual void FinishLoadGame(BGSLoadFormBuffer* a_buf) override;  // 0A
		virtual void Revert(BGSLoadFormBuffer* a_buf) override;          // 0B
		virtual void ClearTargetImpl() override;                         // 12
		virtual ~EnhanceWeaponEffect();                                  // 13
		virtual void Start() override;                                   // 14
		virtual void Finish() override;                                  // 15

		// override (DualValueModifierEffect)
		virtual ActorValue GetAdditionalActorValue() const override;  // 21
		virtual float      GetSecondaryAVWeight() const override;     // 22

		// override (BSTEventSink)
		virtual BSEventNotifyControl ProcessEvent(const ActorInventoryEvent* a_event, BSTEventSource<ActorInventoryEvent>* a_eventSource) override;  // 01

		// members
		ActorValue secondaryActorValue;  // A8
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(EnhanceWeaponEffect) == 0xB0);
}
