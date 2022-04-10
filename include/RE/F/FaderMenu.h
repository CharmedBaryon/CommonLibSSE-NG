#pragma once

#include "RE/I/IMenu.h"

namespace RE
{
	// menuDepth = 3
	// flags = kAlwaysOpen | kAllowSaving | kCustomRendering
	// context = kNone
	class FaderMenu : public IMenu
	{
	public:
		inline static auto                RTTI = RTTI_FaderMenu;
		constexpr static std::string_view MENU_NAME = "Fader Menu";

		virtual ~FaderMenu();  // 00

		// override (IMenu)
		virtual UI_MESSAGE_RESULTS ProcessMessage(UIMessage& a_message) override;  // 04

		// members
#if !defined(ENABLE_SKYRIM_VR) || (!defined(ENABLE_SKYRIM_AE) && !defined(ENABLE_SKYRIM_SE))
		void*         unk30;  // 30 - smart ptr
		std::uint8_t  unk38;  // 38
		std::uint8_t  unk39;  // 39
		std::uint16_t pad3A;  // 3A
		std::uint32_t pad3C;  // 3C
#endif
	};
#ifndef ENABLE_SKYRIM_VR
	static_assert(sizeof(FaderMenu) == 0x40);
#elif !defined(ENABLE_SKYRIM_AE) && !defined(ENABLE_SKYRIM_SE)
	static_assert(sizeof(FaderMenu) == 0x50);
#endif
}
