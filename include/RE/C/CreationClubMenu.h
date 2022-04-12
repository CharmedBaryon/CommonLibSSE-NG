#pragma once

#include "RE/B/BSTEvent.h"
#include "RE/G/GFxFunctionHandler.h"
#include "RE/I/IMenu.h"
#include "RE/I/ImageData.h"
#include "RE/M/MenuEventHandler.h"

namespace RE
{
	class MenuOpenCloseEvent;

	// menuDepth = 0
	// flags = kUsesMenuContext | kDisablePauseMenu | kUpdateUsesCursor | kInventoryItemMenu | kDontHideCursorWhenTopmost
	// context = kItemMenu
	class CreationClubMenu :
#if !defined(ENABLE_SKYRIM_VR) || (!defined(ENABLE_SKYRIM_AE) && !defined(ENABLE_SKYRIM_SE))
		public IMenu,                            // 00
		public MenuEventHandler,                 // 30
		public GFxFunctionHandler,               // 40
		public BSTEventSink<MenuOpenCloseEvent>  // 50
#else
		public IMenu  // 00
#endif
	{
	public:
		inline static auto                RTTI = RTTI_CreationClubMenu;
		constexpr static std::string_view MENU_NAME = "Creation Club Menu";

		struct RUNTIME_DATA
		{
#define RUNTIME_DATA_CONTENT       \
	ImageData background; /* 00 */ \
	ImageData details;    /* 18 */

			RUNTIME_DATA_CONTENT
		};
		static_assert(sizeof(RUNTIME_DATA) == 0x30);

		~CreationClubMenu() override;  // 00

		// override (IMenu)
		void AdvanceMovie(float a_interval, std::uint32_t a_currentTime) override;  // 05

#if !defined(ENABLE_SKYRIM_VR) || (!defined(ENABLE_SKYRIM_AE) && !defined(ENABLE_SKYRIM_SE))
		// override (MenuEventHandler)
		bool CanProcess(InputEvent* a_event) override;              // 01
		bool ProcessThumbstick(ThumbstickEvent* a_event) override;  // 03

		// override (GFxFunctionHandler)
		void Call(Params& a_params) override;  // 01

		// override (BSTEventSink<MenuOpenCloseEvent>)
		BSEventNotifyControl ProcessEvent(const MenuOpenCloseEvent* a_event, BSTEventSource<MenuOpenCloseEvent>* a_eventSource) override;  // 01
#endif

		[[nodiscard]] inline RUNTIME_DATA& GetRuntimeData() noexcept
		{
			return REL::RelocateMember<RUNTIME_DATA>(this, 0x58, 0x68);
		}

		[[nodiscard]] inline const RUNTIME_DATA& GetRuntimeData() const noexcept
		{
			return REL::RelocateMember<RUNTIME_DATA>(this, 0x58, 0x68);
		}

		// members
#if !defined(ENABLE_SKYRIM_VR) || (!defined(ENABLE_SKYRIM_AE) && !defined(ENABLE_SKYRIM_SE))
		RUNTIME_DATA_CONTENT  // 58, 68
#endif
	};
#ifndef ENABLE_SKYRIM_VR
	static_assert(sizeof(CreationClubMenu) == 0x88);
#elif !defined(ENABLE_SKYRIM_AE) && !defined(ENABLE_SKYRIM_SE)
	static_assert(sizeof(CreationClubMenu) == 0x98);
#endif
}
#undef RUNTIME_DATA_CONTENT
