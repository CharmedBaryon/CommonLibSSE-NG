#pragma once

#include "RE/B/BSTArray.h"
#include "RE/B/BSTEvent.h"
#include "RE/I/IMenu.h"

namespace RE
{
	class MenuOpenCloseEvent;

	// menuDepth = 3
	// flags = kUpdateUsesCursor | kDontHideCursorWhenTopmost
	// context = kMenuMode
	class DialogueMenu :
		public IMenu,                            // 00
		public BSTEventSink<MenuOpenCloseEvent>  // 30
	{
	public:
		inline static auto                RTTI = RTTI_DialogueMenu;
		constexpr static std::string_view MENU_NAME = "Dialogue Menu";

		struct Data
		{
			void*         unk00;  // 00
			std::uint64_t unk08;  // 08
		};
		static_assert(sizeof(Data) == 0x10);

		~DialogueMenu() override;  // 00

		// override (IMenu)
		void               Accept(CallbackProcessor* a_processor) override;  // 01
		UI_MESSAGE_RESULTS ProcessMessage(UIMessage& a_message) override;    // 04

		// override (BSTEventSink<MenuOpenCloseEvent>)
		BSEventNotifyControl ProcessEvent(const MenuOpenCloseEvent* a_event, BSTEventSource<MenuOpenCloseEvent>* a_eventSource) override;  // 01

		// members
#if !defined(ENABLE_SKYRIM_VR) || (!defined(ENABLE_SKYRIM_AE) && !defined(ENABLE_SKYRIM_SE))
		BSTArray<Data> unk38;  // 38, 48
#endif
	};
#ifndef ENABLE_SKYRIM_VR
	static_assert(sizeof(DialogueMenu) == 0x50);
#elif !defined(ENABLE_SKYRIM_AE) && !defined(ENABLE_SKYRIM_SE)
	static_assert(sizeof(DialogueMenu) == 0x60);
#endif
}
