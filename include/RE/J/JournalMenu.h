#pragma once

#include "RE/B/BSTEvent.h"
#include "RE/I/IMenu.h"
#include "RE/J/Journal_QuestsTab.h"
#include "RE/J/Journal_StatsTab.h"
#include "RE/J/Journal_SystemTab.h"
#include "RE/M/MenuEventHandler.h"
#include "REL/RuntimeDataAccessors.h"

namespace RE
{
	class BSSystemEvent;

	// menuDepth = 5
	// flags = kPausesGame | kUsesMenuContext | kFreezeFrameBackground | kRequiresUpdate | kTopmostRenderedMenu | kUpdateUsesCursor | kAllowSaving
	// kDisablePauseMenu if game load prevented
	// context = kJournal
	class JournalMenu :
		public IMenu,  // 00
#ifndef SKYRIM_CROSS_VR
		public MenuEventHandler,            // 30
		public BSTEventSink<BSSystemEvent>  // 40
#else
		public MenuEventHandler  // 30
#endif
	{
	public:
		inline static constexpr auto      RTTI = RTTI_JournalMenu;
		inline static constexpr auto      VTABLE = VTABLE_JournalMenu;
		constexpr static std::string_view MENU_NAME = "Journal Menu";

		struct RUNTIME_DATA
		{
#define RUNTIME_DATA_CONTENT              \
	Journal_QuestsTab questsTab; /* 00 */ \
	Journal_StatsTab  statsTab;  /* 38 */ \
	Journal_SystemTab systemTab; /* 50 */ \
	std::uint64_t     unkD0;     /* 88 */ \
	std::uint64_t     unkD8;     /* 90 */ \
	std::uint64_t     unkE0;     /* 98 */

			RUNTIME_DATA_CONTENT
		};
		static_assert(sizeof(RUNTIME_DATA) == 0xA0);

		~JournalMenu() override;  // 00

		// override (IMenu)
		void               Accept(CallbackProcessor* a_processor) override;                       // 01
		UI_MESSAGE_RESULTS ProcessMessage(UIMessage& a_message) override;                         // 04
		void               AdvanceMovie(float a_interval, std::uint32_t a_currentTime) override;  // 05
		void               PostDisplay() override;                                                // 06

		// override (MenuEventHandler)
		bool CanProcess(InputEvent* a_event) override;  // 01
#ifdef EXCLUSIVE_SKYRIM_VR
		bool ProcessThumbstick(ThumbstickEvent* a_event) override;  // 03
#endif

#ifndef SKYRIM_CROSS_VR
		// override (BSTEventSink<BSSystemEvent>)
		BSEventNotifyControl ProcessEvent(const BSSystemEvent* a_event, BSTEventSource<BSSystemEvent>* a_eventSource) override;  // 01
#endif

		RUNTIME_CAST_ACCESSOR(MenuEventHandler, AsMenuEventHandler, 0x30, 0x40);
		RUNTIME_CAST_ACCESSOR(BSTEventSink<BSSystemEvent>, AsBSSystemEventSink, 0x40, 0x50);

		RUNTIME_DATA_ACCESSOR(RUNTIME_DATA, 0x48, 0x58);
		// members
#ifndef SKYRIM_CROSS_VR
		RUNTIME_DATA_CONTENT;  // 48, 58
#endif
	};
	STATIC_ASSERT_SIZE(JournalMenu, 0xE8, 0xE8, 0xF8, 0x40);
}
#undef RUNTIME_DATA_CONTENT
