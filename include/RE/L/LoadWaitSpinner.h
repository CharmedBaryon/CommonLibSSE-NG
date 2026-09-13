#pragma once

#include "RE/B/BSTEvent.h"
#include "RE/G/GFxValue.h"
#include "RE/I/IMenu.h"
#include "REL/RuntimeDataAccessors.h"

namespace RE
{
	class BSSystemEvent;
	struct BGSSaveLoadManagerEvent;
	struct BSGamerProfileEvent;

	// menuDepth = 10
	// flags = kAlwaysOpen | kAllowSaving
	// context = kNone
	class LoadWaitSpinner :
#ifndef SKYRIM_CROSS_VR
		public IMenu,                                 // 00
		public BSTEventSink<BSSystemEvent>,           // 30
		public BSTEventSink<BSGamerProfileEvent>,     // 38
		public BSTEventSink<BGSSaveLoadManagerEvent>  // 40
#else
		public IMenu  // 00
#endif
	{
	public:
		inline static constexpr auto      RTTI = RTTI_LoadWaitSpinner;
		inline static constexpr auto      VTABLE = VTABLE_LoadWaitSpinner;
		constexpr static std::string_view MENU_NAME = "LoadWaitSpinner";

		struct RUNTIME_DATA
		{
#define RUNTIME_DATA_CONTENT                           \
	GFxValue              root;   /* 00 - "Menu_mc" */ \
	volatile std::int32_t unk60;  /* 18 */             \
	bool                  fadeIn; /* 1C */             \
	std::uint8_t          pad65;  /* 1D */             \
	std::uint16_t         pad66;  /* 1E */

			RUNTIME_DATA_CONTENT
		};
		static_assert(sizeof(RUNTIME_DATA) == 0x20);

		~LoadWaitSpinner() override;  // 00

		// override (IMenu)
		void               Accept(CallbackProcessor* a_processor) override;  // 01 - { return; }
		UI_MESSAGE_RESULTS ProcessMessage(UIMessage& a_message) override;    // 04

#ifndef SKYRIM_CROSS_VR
		// override (BSTEventSink<BSSystemEvent>)
		BSEventNotifyControl ProcessEvent(const BSSystemEvent* a_event, BSTEventSource<BSSystemEvent>* a_eventSource) override;  // 01

		// override (BSTEventSink<BSGamerProfileEvent>)
		BSEventNotifyControl ProcessEvent(const BSGamerProfileEvent* a_event, BSTEventSource<BSGamerProfileEvent>* a_eventSource) override;  // 01

		// override (BSTEventSink<BGSSaveLoadManagerEvent>)
		BSEventNotifyControl ProcessEvent(const BGSSaveLoadManagerEvent* a_event, BSTEventSource<BGSSaveLoadManagerEvent>* a_eventSource) override;  // 01
#endif

		RUNTIME_CAST_ACCESSOR(BSTEventSink<BSSystemEvent>, AsBSSystemEventSink, 0x30, 0x40);
		RUNTIME_CAST_ACCESSOR(BSTEventSink<BSGamerProfileEvent>, AsBSGamerProfileEventSink, 0x38, 0x48);
		RUNTIME_CAST_ACCESSOR(BSTEventSink<BGSSaveLoadManagerEvent>, AsBGSSaveLoadManagerEvent, 0x40, 0x50);

		RUNTIME_DATA_ACCESSOR(RUNTIME_DATA, 0x48, 0x58);
		// members
#ifndef SKYRIM_CROSS_VR
		RUNTIME_DATA_CONTENT;  // 48, 58
#endif
	};
	STATIC_ASSERT_SIZE(LoadWaitSpinner, 0x68, 0x68, 0x78, 0x30);
}
#undef RUNTIME_DATA_CONTENT
