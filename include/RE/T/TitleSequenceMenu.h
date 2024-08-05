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
		inline static constexpr auto      RTTI = RTTI_TitleSequenceMenu;
		constexpr static std::string_view MENU_NAME = "TitleSequence Menu";

		~TitleSequenceMenu() override;  // 00

		// override (IMenu)
		UI_MESSAGE_RESULTS ProcessMessage(UIMessage& a_message) override;  // 04
	private:
		KEEP_FOR_RE()
	};
#if defined(EXCLUSIVE_SKYRIM_VR)
	static_assert(sizeof(TitleSequenceMenu) == 0x40);
#else
	static_assert(sizeof(TitleSequenceMenu) == 0x30);
#endif
}
