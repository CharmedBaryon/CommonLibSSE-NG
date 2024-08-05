#pragma once

#include "RE/A/ActiveEffect.h"
#include "RE/A/ActorInventoryEvent.h"
#include "RE/B/BSTEvent.h"

namespace RE
{
	class TESForm;

	class BoundItemEffect :
		public ActiveEffect,                      // 00
		public BSTEventSink<ActorInventoryEvent>  // 90
	{
	public:
		inline static constexpr auto RTTI = RTTI_BoundItemEffect;
		inline static constexpr auto VTABLE = VTABLE_BoundItemEffect;

		// override (ActiveEffect)
		virtual void Update(float a_delta) override;                     // 04
		virtual void SaveGame(BGSSaveFormBuffer* a_buf) override;        // 08
		virtual void LoadGame(BGSLoadFormBuffer* a_buf) override;        // 09
		virtual void FinishLoadGame(BGSLoadFormBuffer* a_buf) override;  // 0A
		virtual void Revert(BGSLoadFormBuffer* a_buf) override;          // 0B
		virtual void ClearTargetImpl() override;                         // 12
		virtual ~BoundItemEffect();                                      // 13
		virtual void Start() override;                                   // 14
		virtual void Finish() override;                                  // 15
		virtual bool CanFinish() override;                               // 16

		// override (BSTEventSink)
		virtual BSEventNotifyControl ProcessEvent(const ActorInventoryEvent* a_event, BSTEventSource<ActorInventoryEvent>* a_eventSource) override;  // 01

		// members
		BSTArray<SpellItem*> spells;  // 98
		bool                 unkB0;   // B0
		bool                 unkB1;   // B1
		bool                 unkB2;   // B2
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(BoundItemEffect) == 0xB8);
}
