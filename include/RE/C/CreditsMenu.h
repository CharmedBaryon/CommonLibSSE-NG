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
		constexpr static std::string_view MENU_NAME = "Credits Menu";

		~CreditsMenu() override;  // 00

		// override (IMenu)
		UI_MESSAGE_RESULTS ProcessMessage(UIMessage& a_message) override;  // 04

#ifndef SKYRIM_CROSS_VR
		// override (GFxFunctionHandler)
		void Call(Params& a_params) override;  // 01
#endif

		[[nodiscard]] GFxFunctionHandler* AsGFxFunctionHandler() noexcept
		{
			return &REL::RelocateMember<GFxFunctionHandler>(this, 0x30, 0x40);
		}

		[[nodiscard]] const GFxFunctionHandler* AsGFxFunctionHandler() const noexcept
		{
			return const_cast<CreditsMenu*>(this)->AsGFxFunctionHandler();
		}

	private:
		KEEP_FOR_RE()
	};
#if defined(EXCLUSIVE_SKYRIM_FLAT)
	static_assert(sizeof(CreditsMenu) == 0x40);
#elif defined(EXCLUSIVE_SKYRIM_VR)
	static_assert(sizeof(CreditsMenu) == 0x50);
#else
	static_assert(sizeof(CreditsMenu) == 0x30);
#endif
}
