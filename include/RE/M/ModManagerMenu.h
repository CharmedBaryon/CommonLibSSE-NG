#pragma once

#include "RE/G/GFxFunctionHandler.h"
#include "RE/I/IMenu.h"
#include "RE/M/MenuEventHandler.h"
#include "REL/RuntimeDataAccessors.h"

namespace RE
{
	// menuDepth = 9
	// flags = kPausesGame | kUsesMenuContext | kModal | kDisablePauseMenu | kRequiresUpdate | kTopmostRenderedMenu | kUpdateUsesCursor
	// context = kMenuMode
	class ModManagerMenu :
#ifndef SKYRIM_CROSS_VR
		public IMenu,              // 00
		public MenuEventHandler,   // 30
		public GFxFunctionHandler  // 40
#else
		public IMenu  // 00
#endif
	{
	public:
		inline static constexpr auto      RTTI = RTTI_ModManagerMenu;
		inline static constexpr auto      VTABLE = VTABLE_ModManagerMenu;
		constexpr static std::string_view MENU_NAME = "Mod Manager Menu";

		struct RUNTIME_DATA
		{
#define RUNTIME_DATA_CONTENT                         \
	bool          useTransparentBackground; /* 50 */ \
	std::uint8_t  pad51;                    /* 51 */ \
	std::uint16_t pad52;                    /* 52 */ \
	std::uint32_t pad54;                    /* 54 */

			RUNTIME_DATA_CONTENT
		};
		static_assert(sizeof(RUNTIME_DATA) == 0x8);

		~ModManagerMenu() override;  // 00

		// override (IMenu)
		UI_MESSAGE_RESULTS ProcessMessage(UIMessage& a_message) override;                         // 04
		void               AdvanceMovie(float a_interval, std::uint32_t a_currentTime) override;  // 05

		// override (MenuEventHandler)
#ifndef SKYRIM_CROSS_VR
		bool CanProcess(InputEvent* a_event) override;  // 01
#endif
#ifdef EXCLUSIVE_SKYRIM_VR
		bool ProcessThumbstick(ThumbstickEvent* a_event) override;  // 03
#endif

#ifndef SKYRIM_CROSS_VR
		// override (GFxFunctionHandler)
		void Call(Params& a_params) override;  // 01
#endif

		RUNTIME_CAST_ACCESSOR(MenuEventHandler, AsMenuEventHandler, 0x30, 0x40);
		RUNTIME_CAST_ACCESSOR(GFxFunctionHandler, AsGFxFunctionHandler, 0x40, 0x50);

		RUNTIME_DATA_ACCESSOR(RUNTIME_DATA, 0x50, 0x60);
		// members
#ifndef SKYRIM_CROSS_VR
		RUNTIME_DATA_CONTENT;  // 50, 60
#endif
	};
	STATIC_ASSERT_SIZE(ModManagerMenu, 0x58, 0x58, 0x68, 0x30);
}
#undef RUNTIME_DATA_CONTENT
