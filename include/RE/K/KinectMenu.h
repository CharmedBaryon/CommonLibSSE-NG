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
#ifndef SKYRIM_CROSS_VR
		public IMenu,                            // 00
		public BSTEventSink<MenuOpenCloseEvent>  // 30
#else
		public IMenu  // 00
#endif
	{
	public:
		inline static constexpr auto      RTTI = RTTI_KinectMenu;
		constexpr static std::string_view MENU_NAME = "Kinect Menu";

		~KinectMenu() override;  // 00

		// override (IMenu)
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
			return const_cast<KinectMenu*>(this)->AsMenuOpenCloseEventSink();
		}

		[[nodiscard]] inline GFxValue GetRoot() const noexcept
		{
			return REL::RelocateMember<GFxValue>(this, 0x38, 0x48);
		}

		inline void SetRoot(GFxValue a_root) noexcept
		{
			REL::RelocateMember<GFxValue>(this, 0x38, 0x48) = a_root;
		}

		// members
#ifndef SKYRIM_CROSS_VR
		GFxValue root;  // 38, 48 - "Menu_mc"
#endif
	private:
		KEEP_FOR_RE()
	};
#if defined(EXCLUSIVE_SKYRIM_FLAT)
	static_assert(sizeof(KinectMenu) == 0x50);
#elif defined(EXCLUSIVE_SKYRIM_VR)
	static_assert(sizeof(KinectMenu) == 0x60);
#else
	static_assert(sizeof(KinectMenu) == 0x30);
#endif
}
