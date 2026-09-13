#pragma once

#include "RE/I/IMenu.h"

namespace RE
{
	// menuDepth = 11
	// flags = kNone
	// context = kNone
	class SafeZoneMenu : public IMenu
	{
	public:
		inline static constexpr auto      RTTI = RTTI_SafeZoneMenu;
		inline static constexpr auto      VTABLE = VTABLE_SafeZoneMenu;
		constexpr static std::string_view MENU_NAME = "SafeZoneMenu";

		~SafeZoneMenu() override;  // 00
	};
	STATIC_ASSERT_SIZE(SafeZoneMenu, 0x30, 0x40);
}
