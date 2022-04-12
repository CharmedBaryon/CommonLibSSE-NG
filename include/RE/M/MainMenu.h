#pragma once

#include "RE/B/BSTEvent.h"
#include "RE/G/GFxFunctionHandler.h"
#include "RE/I/IMenu.h"
#include "RE/I/ImageData.h"

namespace RE
{
	class BSSaveDataEvent;
	class BSSystemEvent;

	// menuDepth = 0
	// flags = kPausesGame | kDisablePauseMenu | kRequiresUpdate | kUpdateUsesCursor | kApplicationMenu
	// context = kMenuMode
	class MainMenu :
#if !defined(ENABLE_SKYRIM_VR) || (!defined(ENABLE_SKYRIM_AE) && !defined(ENABLE_SKYRIM_SE))
		public IMenu,                          // 00
		public BSTEventSink<BSSystemEvent>,    // 30
		public BSTEventSink<BSSaveDataEvent>,  // 38
		public GFxFunctionHandler              // 40
#else
		public IMenu  // 00
#endif
	{
	public:
		inline static auto                RTTI = RTTI_MainMenu;
		constexpr static std::string_view MENU_NAME = "Main Menu";

		struct RUNTIME_DATA
		{
#define RUNTIME_DATA_CONTENT      \
	ImageData     unk50; /* 00 */ \
	std::uint32_t unk68; /* 18 */ \
	std::uint8_t  unk6C; /* 1C */ \
	std::uint8_t  unk6D; /* 1D */ \
	std::uint8_t  unk6E; /* 1E */ \
	std::uint8_t  pad6F; /* 1F */

			RUNTIME_DATA_CONTENT
		};
		static_assert(sizeof(RUNTIME_DATA) == 0x20);

		~MainMenu() override;  // 00

		// override (IMenu)
		void               Accept(CallbackProcessor* a_processor) override;                       // 01
		UI_MESSAGE_RESULTS ProcessMessage(UIMessage& a_message) override;                         // 04
		void               AdvanceMovie(float a_interval, std::uint32_t a_currentTime) override;  // 05

#if !defined(ENABLE_SKYRIM_VR) || (!defined(ENABLE_SKYRIM_AE) && !defined(ENABLE_SKYRIM_SE))
		// override (BSTEventSink<BSSystemEvent>)
		BSEventNotifyControl ProcessEvent(const BSSystemEvent* a_event, BSTEventSource<BSSystemEvent>* a_eventSource) override;  // 01

		// override (BSTEventSink<BSSaveDataEvent>)
		BSEventNotifyControl ProcessEvent(const BSSaveDataEvent* a_event, BSTEventSource<BSSaveDataEvent>* a_eventSource) override;  // 01

		// override (GFxFunctionHandler)
		void Call(Params& a_params) override;  // 01
#endif

		[[nodiscard]] inline RUNTIME_DATA& GetRuntimeData() noexcept
		{
			return REL::RelocateMember<RUNTIME_DATA>(this, 0x50, 0x60);
		}

		[[nodiscard]] inline const RUNTIME_DATA& GetRuntimeData() const noexcept
		{
			return REL::RelocateMember<RUNTIME_DATA>(this, 0x50, 0x60);
		}

		// members
#if !defined(ENABLE_SKYRIM_VR) || (!defined(ENABLE_SKYRIM_AE) && !defined(ENABLE_SKYRIM_SE))
		RUNTIME_DATA_CONTENT  // 50, 60
#endif
	};
#ifndef ENABLE_SKYRIM_VR
	static_assert(sizeof(MainMenu) == 0x70);
#elif !defined(ENABLE_SKYRIM_AE) && !defined(ENABLE_SKYRIM_SE)
	static_assert(sizeof(MainMenu) == 0x80);
#endif
}
#undef RUNTIME_DATA_CONTENT
