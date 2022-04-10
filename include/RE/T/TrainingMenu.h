#pragma once

#include "RE/A/ActorValues.h"
#include "RE/B/BSTEvent.h"
#include "RE/G/GFxValue.h"
#include "RE/I/IMenu.h"

namespace RE
{
	class MenuOpenCloseEvent;

	// menuDepth = 3
	// flags = kPausesGame | kUsesMenuContext | kUpdateUsesCursor
	// kUsesCursor if gamepad disabled
	// context = kNone
	class TrainingMenu :
		public IMenu,                            // 00
		public BSTEventSink<MenuOpenCloseEvent>  // 30
	{
	public:
		inline static auto                RTTI = RTTI_TrainingMenu;
		constexpr static std::string_view MENU_NAME = "Training Menu";

		struct RUNTIME_DATA
		{
			void*         unk38;            // 00 - smart ptr
			ActorValue    skill;            // 08
			std::uint32_t unk44;            // 0C
			GFxValue      trainingMenuObj;  // 10 - MovieClip
			GFxValue      skillName;        // 28 - TextField
			GFxValue      skillMeter;       // 40 - Components.Meter
			GFxValue      trainerSkill;     // 58 - TextField
			GFxValue      timesTrained;     // 70 - TextField
			GFxValue      trainCost;        // 88 - TextField
			GFxValue      currentGold;      // A0 - TextField
		};
		static_assert(sizeof(RUNTIME_DATA) == 0xB8);

		~TrainingMenu() override;  // 00

		// override (IMenu)
		void               Accept(CallbackProcessor* a_cbReg) override;    // 01
		UI_MESSAGE_RESULTS ProcessMessage(UIMessage& a_message) override;  // 04

		// override (BSTEventSink<MenuOpenCloseEvent>)
		BSEventNotifyControl ProcessEvent(const MenuOpenCloseEvent* a_event, BSTEventSource<MenuOpenCloseEvent>* a_eventSource) override;  // 01

		[[nodiscard]] inline RUNTIME_DATA& GetRuntimeData() noexcept
		{
			return REL::RelocateMember<RUNTIME_DATA>(this, 0x38, 0x48);
		}

		[[nodiscard]] inline const RUNTIME_DATA& GetRuntimeData() const noexcept
		{
			return REL::RelocateMember<RUNTIME_DATA>(this, 0x38, 0x48);
		}

		// members
#if !defined(ENABLE_SKYRIM_VR) || (!defined(ENABLE_SKYRIM_AE) && !defined(ENABLE_SKYRIM_SE))
		RUNTIME_DATA runtimeData; // 38, 48
#endif
	};
#ifndef ENABLE_SKYRIM_VR
	static_assert(sizeof(TrainingMenu) == 0x0F0);
#elif !defined(ENABLE_SKYRIM_AE) && !defined(ENABLE_SKYRIM_SE)
	static_assert(sizeof(TrainingMenu) == 0x100);
#endif
}
