#pragma once

#include "RE/B/BSScaleformExternalTexture.h"
#include "RE/B/BSTEvent.h"
#include "RE/G/GFxFunctionHandler.h"
#include "RE/I/IMenu.h"
#include "RE/M/MenuEventHandler.h"
#include "REL/RuntimeDataAccessors.h"

namespace RE
{
	class MenuOpenCloseEvent;

	// menuDepth = 0
	// flags = kUsesMenuContext | kDisablePauseMenu | kUpdateUsesCursor | kInventoryItemMenu | kDontHideCursorWhenTopmost
	// context = kItemMenu
	class CreationClubMenu :
#ifndef SKYRIM_CROSS_VR
		public IMenu,                            // 00
		public MenuEventHandler,                 // 30
		public GFxFunctionHandler,               // 40
		public BSTEventSink<MenuOpenCloseEvent>  // 50
#else
		public IMenu  // 00
#endif
	{
	public:
		inline static constexpr auto      RTTI = RTTI_CreationClubMenu;
		inline static constexpr auto      VTABLE = VTABLE_CreationClubMenu;
		constexpr static std::string_view MENU_NAME = "Creation Club Menu";

		struct RUNTIME_DATA
		{
#define RUNTIME_DATA_CONTENT                        \
	BSScaleformExternalTexture background; /* 00 */ \
	BSScaleformExternalTexture details;    /* 18 */

			RUNTIME_DATA_CONTENT
		};
		static_assert(sizeof(RUNTIME_DATA) == 0x30);

		~CreationClubMenu() override;  // 00

		// override (IMenu)
		void AdvanceMovie(float a_interval, std::uint32_t a_currentTime) override;  // 05

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

		// override (BSTEventSink<MenuOpenCloseEvent>)
		BSEventNotifyControl ProcessEvent(const MenuOpenCloseEvent* a_event, BSTEventSource<MenuOpenCloseEvent>* a_eventSource) override;  // 01
#endif

#ifndef SKYRIM_CROSS_VR
		RUNTIME_CAST_ACCESSOR(MenuEventHandler, AsMenuEventHandler, 0x30, 0x40);
		RUNTIME_CAST_ACCESSOR(GFxFunctionHandler, AsGFxFunctionHandler, 0x40, 0x50);
		RUNTIME_CAST_ACCESSOR(BSTEventSink<MenuOpenCloseEvent>, AsMenuOpenCloseEventSink, 0x50, 0x60);

		RUNTIME_DATA_ACCESSOR(RUNTIME_DATA, 0x58, 0x68);
#endif
		// members
#ifndef SKYRIM_CROSS_VR
		RUNTIME_DATA_CONTENT;  // 58, 68
#endif
	};
	STATIC_ASSERT_SIZE(CreationClubMenu, 0x88, 0x88, 0x98, 0x30);
}
#undef RUNTIME_DATA_CONTENT
