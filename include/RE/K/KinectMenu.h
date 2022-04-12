#pragma once

#include "RE/B/BSTEvent.h"
#include "RE/G/GFxValue.h"
#include "RE/I/IMenu.h"

namespace RE
{
	class MenuOpenCloseEvent;

	// menuDepth = 6
	// flags = kAllowSaving | kCustomRendering | kAssignCursorToRenderer
	// context = kNone
	class KinectMenu :
#if !defined(ENABLE_SKYRIM_VR) || (!defined(ENABLE_SKYRIM_AE) && !defined(ENABLE_SKYRIM_SE))
		public IMenu,                            // 00
		public BSTEventSink<MenuOpenCloseEvent>  // 30
#else
		public IMenu  // 00
#endif
	{
	public:
		inline static auto                RTTI = RTTI_KinectMenu;
		constexpr static std::string_view MENU_NAME = "Kinect Menu";

		~KinectMenu() override;  // 00

		// override (IMenu)
		UI_MESSAGE_RESULTS ProcessMessage(UIMessage& a_message) override;  // 04

#if !defined(ENABLE_SKYRIM_VR) || (!defined(ENABLE_SKYRIM_AE) && !defined(ENABLE_SKYRIM_SE))
		// override (BSTEventSink<MenuOpenCloseEvent>)
		BSEventNotifyControl ProcessEvent(const MenuOpenCloseEvent* a_event, BSTEventSource<MenuOpenCloseEvent>* a_eventSource) override;  // 01
#endif

		[[nodiscard]] inline GFxValue GetRoot() const noexcept
		{
			return REL::RelocateMember<GFxValue>(this, 0x38, 0x48);
		}

		inline void SetRoot(GFxValue a_root) noexcept
		{
			REL::RelocateMember<GFxValue>(this, 0x38, 0x48) = a_root;
		}

		// members
#if !defined(ENABLE_SKYRIM_VR) || (!defined(ENABLE_SKYRIM_AE) && !defined(ENABLE_SKYRIM_SE))
		GFxValue root;  // 38, 48 - "Menu_mc"
#endif
	};
#ifndef ENABLE_SKYRIM_VR
	static_assert(sizeof(KinectMenu) == 0x50);
#elif !defined(ENABLE_SKYRIM_AE) && !defined(ENABLE_SKYRIM_SE)
	static_assert(sizeof(KinectMenu) == 0x60);
#endif
}
