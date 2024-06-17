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
		constexpr static std::string_view MENU_NAME = "SafeZoneMenu";

		~SafeZoneMenu() override;  // 00
	private:
		KEEP_FOR_RE()
	};
#if !defined(ENABLE_SKYRIM_VR)
#	ifdef ENABLE_SKYRIM_AE
	static_assert(sizeof(SafeZoneMenu) == 0x40);
#	else
	static_assert(sizeof(SafeZoneMenu) == 0x30);
#	endif
#elif !defined(ENABLE_SKYRIM_AE) && !defined(ENABLE_SKYRIM_SE)
	static_assert(sizeof(SafeZoneMenu) == 0x40);
#endif
}
