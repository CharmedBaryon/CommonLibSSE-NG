#pragma once

#include "RE/B/BSScaleformExternalTexture.h"
#include "RE/B/BSTEvent.h"
#include "RE/G/GFxFunctionHandler.h"
#include "RE/I/IMenu.h"
#include "RE/M/MenuEventHandler.h"

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

#ifndef SKYRIM_CROSS_VR
		// override (MenuEventHandler)
		bool CanProcess(InputEvent* a_event) override;              // 01
		bool ProcessThumbstick(ThumbstickEvent* a_event) override;  // 03

		// override (GFxFunctionHandler)
		void Call(Params& a_params) override;  // 01

		// override (BSTEventSink<MenuOpenCloseEvent>)
		BSEventNotifyControl ProcessEvent(const MenuOpenCloseEvent* a_event, BSTEventSource<MenuOpenCloseEvent>* a_eventSource) override;  // 01
#endif

		[[nodiscard]] MenuEventHandler* AsMenuEventHandler() noexcept
		{
			return &REL::RelocateMember<MenuEventHandler>(this, 0x30, 0x40);
		}

		[[nodiscard]] const MenuEventHandler* AsMenuEventHandler() const noexcept
		{
			return const_cast<CreationClubMenu*>(this)->AsMenuEventHandler();
		}

		[[nodiscard]] GFxFunctionHandler* AsGFxFunctionHandler() noexcept
		{
			return &REL::RelocateMember<GFxFunctionHandler>(this, 0x40, 0x50);
		}

		[[nodiscard]] const GFxFunctionHandler* AsGFxFunctionHandler() const noexcept
		{
			return const_cast<CreationClubMenu*>(this)->AsGFxFunctionHandler();
		}

		[[nodiscard]] BSTEventSink<MenuOpenCloseEvent>* AsMenuOpenCloseEventSink() noexcept
		{
			return &REL::RelocateMember<BSTEventSink<MenuOpenCloseEvent>>(this, 0x50, 0x60);
		}

		[[nodiscard]] const BSTEventSink<MenuOpenCloseEvent>* AsMenuOpenCloseEventSink() const noexcept
		{
			return const_cast<CreationClubMenu*>(this)->AsMenuOpenCloseEventSink();
		}

		[[nodiscard]] inline RUNTIME_DATA& GetRuntimeData() noexcept
		{
			return REL::RelocateMember<RUNTIME_DATA>(this, 0x58, 0x68);
		}

		[[nodiscard]] inline const RUNTIME_DATA& GetRuntimeData() const noexcept
		{
			return REL::RelocateMember<RUNTIME_DATA>(this, 0x58, 0x68);
		}

		// members
#ifndef SKYRIM_CROSS_VR
		RUNTIME_DATA_CONTENT;  // 58, 68
#endif
	private:
		KEEP_FOR_RE();
	};
#if defined(EXCLUSIVE_SKYRIM_FLAT)
	static_assert(sizeof(CreationClubMenu) == 0x88);
#elif defined(EXCLUSIVE_SKYRIM_VR)
	static_assert(sizeof(CreationClubMenu) == 0x98);
#else
	static_assert(sizeof(CreationClubMenu) == 0x30);
#endif
}
#undef RUNTIME_DATA_CONTENT
