#pragma once

#include "RE/I/IMenu.h"

namespace RE
{
	// menuDepth = 3
	// flags = kPausesGame
	// context = kNone
	class ConsoleNativeUIMenu : public IMenu
	{
	public:
		inline static auto                RTTI = RTTI_ConsoleNativeUIMenu;
		constexpr static std::string_view MENU_NAME = "Console Native UI Menu";

		~ConsoleNativeUIMenu() override;  // 00

		// override (IMenu)
		UI_MESSAGE_RESULTS ProcessMessage(UIMessage& a_message) override;  // 04

		// members
#if !defined(ENABLE_SKYRIM_VR) || (!defined(ENABLE_SKYRIM_AE) && !defined(ENABLE_SKYRIM_SE))
		std::uint8_t  unk30;  // 30
		std::uint8_t  pad31;  // 31
		std::uint16_t pad32;  // 32
		std::uint32_t pad34;  // 34
#endif
	};
#ifndef ENABLE_SKYRIM_VR
	static_assert(sizeof(ConsoleNativeUIMenu) == 0x38);
#elif !defined(ENABLE_SKYRIM_AE) && !defined(ENABLE_SKYRIM_SE)
	static_assert(sizeof(ConsoleNativeUIMenu) == 0x48);
#endif
}
