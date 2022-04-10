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
		inline static auto                RTTI = RTTI_SafeZoneMenu;
		constexpr static std::string_view MENU_NAME = "SafeZoneMenu";

		~SafeZoneMenu() override;  // 00
	};
#ifndef ENABLE_SKYRIM_VR
	static_assert(sizeof(SafeZoneMenu) == 0x30);
#elif !defined(ENABLE_SKYRIM_AE) && !defined(ENABLE_SKYRIM_SE)
	static_assert(sizeof(SafeZoneMenu) == 0x40);
#endif
}
