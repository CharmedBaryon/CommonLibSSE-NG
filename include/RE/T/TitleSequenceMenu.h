#pragma once

#include "RE/I/IMenu.h"

namespace RE
{
	// menuDepth = 4
	// flags = kNone
	// context = kNone
	class TitleSequenceMenu : public IMenu
	{
	public:
		inline static auto                RTTI = RTTI_TitleSequenceMenu;
		constexpr static std::string_view MENU_NAME = "TitleSequence Menu";

		~TitleSequenceMenu() override;  // 00

		// override (IMenu)
		UI_MESSAGE_RESULTS ProcessMessage(UIMessage& a_message) override;  // 04
	};
#ifndef ENABLE_SKYRIM_VR
	static_assert(sizeof(TitleSequenceMenu) == 0x30);
#elif !defined(ENABLE_SKYRIM_AE) && !defined(ENABLE_SKYRIM_SE)
	static_assert(sizeof(TitleSequenceMenu) == 0x40);
#endif
}
