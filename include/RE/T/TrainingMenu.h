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
#ifndef SKYRIM_CROSS_VR
		public IMenu,                            // 00
		public BSTEventSink<MenuOpenCloseEvent>  // 30
#else
		public IMenu  // 00
#endif
	{
	public:
		inline static constexpr auto      RTTI = RTTI_TrainingMenu;
		constexpr static std::string_view MENU_NAME = "Training Menu";

		struct RUNTIME_DATA
		{
#define RUNTIME_DATA_CONTENT                                   \
	Actor*        trainer;         /* 38 - smart ptr */        \
	ActorValue    skill;           /* 40 */                    \
	std::uint32_t unk44;           /* 44 */                    \
	GFxValue      trainingMenuObj; /* 48 - MovieClip */        \
	GFxValue      skillName;       /* 60 - TextField */        \
	GFxValue      skillMeter;      /* 78 - Components.Meter */ \
	GFxValue      trainerSkill;    /* 90 - TextField */        \
	GFxValue      timesTrained;    /* A8 - TextField */        \
	GFxValue      trainCost;       /* C0 - TextField */        \
	GFxValue      currentGold;     /* D8 - TextField */

			RUNTIME_DATA_CONTENT
		};
		static_assert(sizeof(RUNTIME_DATA) == 0xB8);

		~TrainingMenu() override;  // 00

		// override (IMenu)
		void               Accept(CallbackProcessor* a_cbReg) override;    // 01
		UI_MESSAGE_RESULTS ProcessMessage(UIMessage& a_message) override;  // 04

#ifndef SKYRIM_CROSS_VR
		// override (BSTEventSink<MenuOpenCloseEvent>)
		BSEventNotifyControl ProcessEvent(const MenuOpenCloseEvent* a_event, BSTEventSource<MenuOpenCloseEvent>* a_eventSource) override;  // 01
#endif

		[[nodiscard]] BSTEventSink<MenuOpenCloseEvent>* AsMenuOpenCloseEventSink() noexcept
		{
			return &REL::RelocateMember<BSTEventSink<MenuOpenCloseEvent>>(this, 0x30, 0x40);
		}

		[[nodiscard]] const BSTEventSink<MenuOpenCloseEvent>* AsMenuOpenCloseEventSink() const noexcept
		{
			return const_cast<TrainingMenu*>(this)->AsMenuOpenCloseEventSink();
		}

		[[nodiscard]] inline RUNTIME_DATA& GetRuntimeData() noexcept
		{
			return REL::RelocateMember<RUNTIME_DATA>(this, 0x38, 0x48);
		}

		[[nodiscard]] inline const RUNTIME_DATA& GetRuntimeData() const noexcept
		{
			return REL::RelocateMember<RUNTIME_DATA>(this, 0x38, 0x48);
		}

		// members
#ifndef SKYRIM_CROSS_VR
		RUNTIME_DATA_CONTENT;  // 38, 48
#endif
	private:
		KEEP_FOR_RE()
	};
#if defined(EXCLUSIVE_SKYRIM_FLAT)
	static_assert(sizeof(TrainingMenu) == 0x0F0);
#elif defined(EXCLUSIVE_SKYRIM_VR)
	static_assert(sizeof(TrainingMenu) == 0x100);
#else
	static_assert(sizeof(TrainingMenu) == 0x30);
#endif
}

#undef RUNTIME_DATA_CONTENT
