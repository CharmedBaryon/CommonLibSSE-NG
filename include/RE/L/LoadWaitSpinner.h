#pragma once

#include "RE/B/BSTEvent.h"
#include "RE/G/GFxValue.h"
#include "RE/I/IMenu.h"

namespace RE
{
	class BSSystemEvent;
	struct BGSSaveLoadManagerEvent;
	struct BSGamerProfileEvent;

	// menuDepth = 10
	// flags = kAlwaysOpen | kAllowSaving
	// context = kNone
	class LoadWaitSpinner :
#if !defined(ENABLE_SKYRIM_VR) || (!defined(ENABLE_SKYRIM_AE) && !defined(ENABLE_SKYRIM_SE))
		public IMenu,                                 // 00
		public BSTEventSink<BSSystemEvent>,           // 30
		public BSTEventSink<BSGamerProfileEvent>,     // 38
		public BSTEventSink<BGSSaveLoadManagerEvent>  // 40
#else
		public IMenu  // 00
#endif
	{
	public:
		inline static auto                RTTI = RTTI_LoadWaitSpinner;
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

#if !defined(ENABLE_SKYRIM_VR) || (!defined(ENABLE_SKYRIM_AE) && !defined(ENABLE_SKYRIM_SE))
		// override (BSTEventSink<BSSystemEvent>)
		BSEventNotifyControl ProcessEvent(const BSSystemEvent* a_event, BSTEventSource<BSSystemEvent>* a_eventSource) override;  // 01

		// override (BSTEventSink<BSGamerProfileEvent>)
		BSEventNotifyControl ProcessEvent(const BSGamerProfileEvent* a_event, BSTEventSource<BSGamerProfileEvent>* a_eventSource) override;  // 01

		// override (BSTEventSink<BGSSaveLoadManagerEvent>)
		BSEventNotifyControl ProcessEvent(const BGSSaveLoadManagerEvent* a_event, BSTEventSource<BGSSaveLoadManagerEvent>* a_eventSource) override;  // 01
#endif

		[[nodiscard]] inline RUNTIME_DATA& GetRuntimeData() noexcept
		{
			return REL::RelocateMember<RUNTIME_DATA>(this, 0x48, 0x58);
		}

		[[nodiscard]] inline const RUNTIME_DATA& GetRuntimeData() const noexcept
		{
			return REL::RelocateMember<RUNTIME_DATA>(this, 0x48, 0x58);
		}

		// members
#if !defined(ENABLE_SKYRIM_VR) || (!defined(ENABLE_SKYRIM_AE) && !defined(ENABLE_SKYRIM_SE))
		RUNTIME_DATA_CONTENT  // 48, 58
#endif
	};
#ifndef ENABLE_SKYRIM_VR
	static_assert(sizeof(LoadWaitSpinner) == 0x68);
#elif !defined(ENABLE_SKYRIM_AE) && !defined(ENABLE_SKYRIM_SE)
	static_assert(sizeof(LoadWaitSpinner) == 0x78);
#endif
}
#undef RUNTIME_DATA_CONTENT
