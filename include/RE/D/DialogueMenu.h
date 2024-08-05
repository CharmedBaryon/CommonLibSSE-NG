#pragma once

#include "RE/B/BSTArray.h"
#include "RE/B/BSTEvent.h"
#include "RE/I/IMenu.h"
#include "RE/W/WorldSpaceMenu.h"

namespace RE
{
	class MenuOpenCloseEvent;

	// menuDepth = 3
	// flags = kUpdateUsesCursor | kDontHideCursorWhenTopmost
	// context = kMenuMode
	class DialogueMenu :
#if defined(EXCLUSIVE_SKYRIM_FLAT)
		public WorldSpaceMenu,                   // 00
		public BSTEventSink<MenuOpenCloseEvent>  // 88
#elif defined(EXCLUSIVE_SKYRIM_VR)
		public IMenu,                            // 00
		public BSTEventSink<MenuOpenCloseEvent>  // 30
#else
		public IMenu  // 00
#endif
	{
	public:
		inline static constexpr auto      RTTI = RTTI_DialogueMenu;
		inline static constexpr auto      VTABLE = VTABLE_DialogueMenu;
		constexpr static std::string_view MENU_NAME = "Dialogue Menu";

		struct Data
		{
			void*         unk00;  // 00
			std::uint64_t unk08;  // 08
		};
		static_assert(sizeof(Data) == 0x10);

		struct RUNTIME_DATA
		{
#define RUNTIME_DATA_CONTENT BSTArray<Data> unk38; /* 00 */
			RUNTIME_DATA_CONTENT
		};

		~DialogueMenu() override;  // 00

		// override (IMenu)
		void               Accept(CallbackProcessor* a_processor) override;  // 01
		UI_MESSAGE_RESULTS ProcessMessage(UIMessage& a_message) override;    // 04

#ifndef SKYRIM_CROSS_VR
		// override (BSTEventSink<MenuOpenCloseEvent>)
		BSEventNotifyControl ProcessEvent(const MenuOpenCloseEvent* a_event, BSTEventSource<MenuOpenCloseEvent>* a_eventSource) override;  // 01
#endif

		[[nodiscard]] BSTEventSink<MenuOpenCloseEvent>* AsMenuOpenCloseEventSink() noexcept
		{
			return &REL::RelocateMember<BSTEventSink<MenuOpenCloseEvent>>(this, 0x30, 0x58);
		}

		[[nodiscard]] const BSTEventSink<MenuOpenCloseEvent>* AsMenuOpenCloseEventSink() const noexcept
		{
			return const_cast<DialogueMenu*>(this)->AsMenuOpenCloseEventSink();
		}

		[[nodiscard]] BSTEventSink<HudModeChangeEvent>* AsHudModeChangeEventSink() noexcept
		{
			return &REL::RelocateMember<BSTEventSink<HudModeChangeEvent>>(this, 0, 0x40);
		}

		[[nodiscard]] const BSTEventSink<HudModeChangeEvent>* AsHudModeChangeEventSink() const noexcept
		{
			return const_cast<DialogueMenu*>(this)->AsHudModeChangeEventSink();
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
#	if defined(ENABLE_SKYRIM_AE) || defined(ENABLE_SKYRIM_SE)
	static_assert(sizeof(DialogueMenu) == 0x68);
#	else
	static_assert(sizeof(DialogueMenu) == 0x50);
#	endif
#elif defined(EXCLUSIVE_SKYRIM_VR)
	static_assert(sizeof(DialogueMenu) == 0x60);
#else
	static_assert(sizeof(DialogueMenu) == 0x30);
#endif
}
#undef RUNTIME_DATA_CONTENT
