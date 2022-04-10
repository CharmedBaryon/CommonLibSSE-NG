#pragma once

#include "RE/G/GFxFunctionHandler.h"
#include "RE/I/IMenu.h"

namespace RE
{
	// menuDepth = 10
	// flags = kPausesGame
	// context = kMenuMode
	class CreditsMenu :
		public IMenu,              // 00
		public GFxFunctionHandler  // 30
	{
	public:
		inline static auto                RTTI = RTTI_CreditsMenu;
		constexpr static std::string_view MENU_NAME = "Credits Menu";

		~CreditsMenu() override;  // 00

		// override (IMenu)
		UI_MESSAGE_RESULTS ProcessMessage(UIMessage& a_message) override;  // 04

		// override (GFxFunctionHandler)
		void Call(Params& a_params) override;  // 01
	};
#ifndef ENABLE_SKYRIM_VR
	static_assert(sizeof(CreditsMenu) == 0x40);
#elif !defined(ENABLE_SKYRIM_AE) && !defined(ENABLE_SKYRIM_SE)
	static_assert(sizeof(CreditsMenu) == 0x50);
#endif
}
