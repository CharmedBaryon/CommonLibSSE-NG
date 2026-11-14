#pragma once

#include "RE/G/GFxValue.h"
#include "RE/I/IMenu.h"
#include "REL/RuntimeDataAccessors.h"

namespace RE
{
	// menuDepth = 4
	// flags = kPausesGame | kRequiresUpdate | kAllowSaving | kApplicationMenu
	// kUsesCursor if gamepad disabled
	// context = kMenuMode
	class SleepWaitMenu : public IMenu
	{
	public:
		inline static constexpr auto      RTTI = RTTI_SleepWaitMenu;
		inline static constexpr auto      VTABLE = VTABLE_SleepWaitMenu;
		constexpr static std::string_view MENU_NAME = "Sleep/Wait Menu";

		struct RUNTIME_DATA
		{
#define RUNTIME_DATA_CONTENT                                \
	float         timer;      /* 00 */                      \
	std::uint32_t pad34;      /* 04 */                      \
	GFxValue      root;       /* 08 - "SleepWaitMenu_mc" */ \
	bool          isSleeping; /* 20 */                      \
	bool          isActive;   /* 21 */                      \
	std::uint16_t pad52;      /* 22 */                      \
	std::uint32_t pad54;      /* 24 */

			RUNTIME_DATA_CONTENT
		};
		static_assert(sizeof(RUNTIME_DATA) == 0x28);

		~SleepWaitMenu() override;  // 00

		// override (IMenu)
		void               Accept(CallbackProcessor* a_processor) override;  // 01
		UI_MESSAGE_RESULTS ProcessMessage(UIMessage& a_message) override;    // 04

		RUNTIME_DATA_ACCESSOR(RUNTIME_DATA, 0x30, 0x40);
		static void ToggleOpenMenu(bool a_sleeping)
		{
			using func_t = decltype(&SleepWaitMenu::ToggleOpenMenu);
			static REL::Relocation<func_t> func{ RELOCATION_ID(51618, 52490) };
			return func(a_sleeping);
		}

		// members
#ifndef SKYRIM_CROSS_VR
		RUNTIME_DATA_CONTENT;  // 30, 40
#endif
	};
	STATIC_ASSERT_SIZE(SleepWaitMenu, 0x58, 0x58, 0x68, 0x30);
}
#undef RUNTIME_DATA_CONTENT
