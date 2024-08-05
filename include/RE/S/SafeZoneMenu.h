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
#if defined(EXCLUSIVE_SKYRIM_FLAT)
	static_assert(sizeof(SafeZoneMenu) == 0x30);
#elif defined(EXCLUSIVE_SKYRIM_VR)
	static_assert(sizeof(SafeZoneMenu) == 0x40);
#else
	static_assert(sizeof(RaceSexMenu) == 0x30);
#endif
}
