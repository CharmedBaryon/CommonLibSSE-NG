#pragma once

#include "RE/G/GFxFunctionHandler.h"
#include "RE/I/IMenu.h"
#include "RE/M/MenuEventHandler.h"

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
		constexpr static std::string_view MENU_NAME = "Mod Manager Menu";

		struct RUNTIME_DATA
		{
#define RUNTIME_DATA_CONTENT      \
	std::uint8_t  unk50; /* 50 */ \
	std::uint8_t  pad51; /* 51 */ \
	std::uint16_t pad52; /* 52 */ \
	std::uint32_t pad54; /* 54 */

			RUNTIME_DATA_CONTENT
		};
		static_assert(sizeof(RUNTIME_DATA) == 0x8);

		~ModManagerMenu() override;  // 00

		// override (IMenu)
		UI_MESSAGE_RESULTS ProcessMessage(UIMessage& a_message) override;                         // 04
		void               AdvanceMovie(float a_interval, std::uint32_t a_currentTime) override;  // 05

#ifndef SKYRIM_CROSS_VR
		// override (MenuEventHandler)
		bool CanProcess(InputEvent* a_event) override;              // 01
		bool ProcessThumbstick(ThumbstickEvent* a_event) override;  // 03

		// override (GFxFunctionHandler)
		void Call(Params& a_params) override;  // 01
#endif

		[[nodiscard]] MenuEventHandler* AsMenuEventHandler() noexcept
		{
			return &REL::RelocateMember<MenuEventHandler>(this, 0x30, 0x40);
		}

		[[nodiscard]] const MenuEventHandler* AsMenuEventHandler() const noexcept
		{
			return const_cast<ModManagerMenu*>(this)->AsMenuEventHandler();
		}

		[[nodiscard]] GFxFunctionHandler* AsGFxFunctionHandler() noexcept
		{
			return &REL::RelocateMember<GFxFunctionHandler>(this, 0x40, 0x50);
		}

		[[nodiscard]] const GFxFunctionHandler* AsGFxFunctionHandler() const noexcept
		{
			return const_cast<ModManagerMenu*>(this)->AsGFxFunctionHandler();
		}

		[[nodiscard]] inline RUNTIME_DATA& GetRuntimeData() noexcept
		{
			return REL::RelocateMember<RUNTIME_DATA>(this, 0x50, 0x60);
		}

		[[nodiscard]] inline const RUNTIME_DATA& GetRuntimeData() const noexcept
		{
			return REL::RelocateMember<RUNTIME_DATA>(this, 0x50, 0x60);
		}

		// members
#ifndef SKYRIM_CROSS_VR
		RUNTIME_DATA_CONTENT;  // 50, 60
#endif
	private:
		KEEP_FOR_RE()
	};
#if defined(EXCLUSIVE_SKYRIM_FLAT)
	static_assert(sizeof(ModManagerMenu) == 0x58);
#elif defined(EXCLUSIVE_SKYRIM_VR)
	static_assert(sizeof(ModManagerMenu) == 0x68);
#else
	static_assert(sizeof(ModManagerMenu) == 0x30);
#endif
}
#undef RUNTIME_DATA_CONTENT
