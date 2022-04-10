#pragma once

#include "RE/I/IMenu.h"

namespace RE
{
	// menuDepth = 10
	// flags = kPausesGame | kAlwaysOpen | kUsesCursor | kModal
	// context = kMenuMode
	class MessageBoxMenu : public IMenu
	{
	public:
		inline static auto                RTTI = RTTI_MessageBoxMenu;
		constexpr static std::string_view MENU_NAME = "MessageBoxMenu";

		~MessageBoxMenu() override;  // 00

		// override (IMenu)
		void               Accept(CallbackProcessor* a_processor) override;  // 01
		UI_MESSAGE_RESULTS ProcessMessage(UIMessage& a_message) override;    // 04

		// members
#if !defined(ENABLE_SKYRIM_VR) || (!defined(ENABLE_SKYRIM_AE) && !defined(ENABLE_SKYRIM_SE))
		std::uint8_t  unk30;  // 30
		std::uint8_t  pad31;  // 31
		std::uint16_t pad32;  // 32
		std::uint32_t pad34;  // 34
#endif
	};
#ifndef ENABLE_SKYRIM_VR
	static_assert(sizeof(MessageBoxMenu) == 0x38);
#elif !defined(ENABLE_SKYRIM_AE) && !defined(ENABLE_SKYRIM_SE)
	static_assert(sizeof(MessageBoxMenu) == 0x48);
#endif
}
