#pragma once

#include "RE/G/GFxFunctionHandler.h"
#include "RE/I/IMenu.h"

namespace RE
{
	// menuDepth = 10
	// flags = kPausesGame
	// context = kMenuMode
	class CreditsMenu :
#ifndef SKYRIM_CROSS_VR
		public IMenu,              // 00
		public GFxFunctionHandler  // 30
#else
		public IMenu  // 00
#endif
	{
	public:
		inline static constexpr auto      RTTI = RTTI_CreditsMenu;
		inline static constexpr auto      VTABLE = VTABLE_CreditsMenu;
		constexpr static std::string_view MENU_NAME = "Credits Menu";

		~CreditsMenu() override;  // 00

		// override (IMenu)
		UI_MESSAGE_RESULTS ProcessMessage(UIMessage& a_message) override;  // 04

#ifndef SKYRIM_CROSS_VR
		// override (GFxFunctionHandler)
		void Call(Params& a_params) override;  // 01
#endif

		RUNTIME_CAST_ACCESSOR(GFxFunctionHandler, AsGFxFunctionHandler, 0x30, 0x40);
	};
	STATIC_ASSERT_SIZE(CreditsMenu, 0x40, 0x40, 0x50, 0x30);
}
