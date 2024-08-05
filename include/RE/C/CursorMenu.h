#pragma once

#include "RE/I/IMenu.h"
#include "RE/M/MenuEventHandler.h"

namespace RE
{
	// menuDepth = 13
	// flags = kAllowSaving | kCustomRendering
	// context = kNone
	class CursorMenu :
#ifndef SKYRIM_CROSS_VR
		public IMenu,            // 00
		public MenuEventHandler  // 30
#else
		public IMenu  // 00
#endif
	{
	public:
		inline static constexpr auto      RTTI = RTTI_CursorMenu;
		constexpr static std::string_view MENU_NAME = "Cursor Menu";

		~CursorMenu() override;  // 00

		// override (IMenu)
		UI_MESSAGE_RESULTS ProcessMessage(UIMessage& a_message) override;  // 04

		// override (MenuEventHandler)
#ifndef SKYRIM_CROSS_VR
		bool CanProcess(InputEvent* a_event) override;              // 01
		bool ProcessThumbstick(ThumbstickEvent* a_event) override;  // 03
		bool ProcessMouseMove(MouseMoveEvent* a_event) override;    // 04
#endif

		[[nodiscard]] MenuEventHandler* AsMenuEventHandler() noexcept
		{
			return &REL::RelocateMember<MenuEventHandler>(this, 0x30, 0x40);
		}

		[[nodiscard]] const MenuEventHandler* AsMenuEventHandler() const noexcept
		{
			return const_cast<CursorMenu*>(this)->AsMenuEventHandler();
		}

	private:
		KEEP_FOR_RE()
	};
#if defined(EXCLUSIVE_SKYRIM_FLAT)
	static_assert(sizeof(CursorMenu) == 0x40);
#elif defined(EXCLUSIVE_SKYRIM_VR)
	static_assert(sizeof(CursorMenu) == 0x50);
#else
	static_assert(sizeof(CursorMenu) == 0x30);
#endif
}
