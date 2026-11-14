#pragma once

#include "RE/I/IMenu.h"
#include "REL/RuntimeDataAccessors.h"

namespace RE
{
	// menuDepth = 3
	// flags = kPausesGame
	// context = kNone
	class ConsoleNativeUIMenu : public IMenu
	{
	public:
		inline static constexpr auto      RTTI = RTTI_ConsoleNativeUIMenu;
		inline static constexpr auto      VTABLE = VTABLE_ConsoleNativeUIMenu;
		constexpr static std::string_view MENU_NAME = "Console Native UI Menu";

		struct RUNTIME_DATA
		{
#define RUNTIME_DATA_CONTENT      \
	std::uint8_t  unk30; /* 00 */ \
	std::uint8_t  pad31; /* 01 */ \
	std::uint16_t pad32; /* 02 */ \
	std::uint32_t pad34; /* 04 */

			RUNTIME_DATA_CONTENT
		};
		static_assert(sizeof(RUNTIME_DATA) == 0x8);

		~ConsoleNativeUIMenu() override;  // 00

		// override (IMenu)
		UI_MESSAGE_RESULTS ProcessMessage(UIMessage& a_message) override;  // 04

		RUNTIME_DATA_ACCESSOR(RUNTIME_DATA, 0x30, 0x40);
		// members
#ifndef SKYRIM_CROSS_VR
		RUNTIME_DATA_CONTENT;  // 30, 40
#endif
	};

	STATIC_ASSERT_SIZE(ConsoleNativeUIMenu, 0x38, 0x38, 0x48, 0x30);
}
#undef RUNTIME_DATA_CONTENT
