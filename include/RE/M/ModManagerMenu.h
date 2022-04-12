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
		public IMenu,  // 00
#if !defined(ENABLE_SKYRIM_VR) || (!defined(ENABLE_SKYRIM_AE) && !defined(ENABLE_SKYRIM_SE))
		public MenuEventHandler,   // 30
		public GFxFunctionHandler  // 40
#else
		public MenuEventHandler  // 30
#endif
	{
	public:
		inline static auto                RTTI = RTTI_ModManagerMenu;
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

#if !defined(ENABLE_SKYRIM_VR) || (!defined(ENABLE_SKYRIM_AE) && !defined(ENABLE_SKYRIM_SE))
		// override (MenuEventHandler)
		bool CanProcess(InputEvent* a_event) override;              // 01
		bool ProcessThumbstick(ThumbstickEvent* a_event) override;  // 03

		// override (GFxFunctionHandler)
		void Call(Params& a_params) override;  // 01
#endif

		[[nodiscard]] inline RUNTIME_DATA& GetRuntimeData() noexcept
		{
			return REL::RelocateMember<RUNTIME_DATA>(this, 0x50, 0x60);
		}

		[[nodiscard]] inline const RUNTIME_DATA& GetRuntimeData() const noexcept
		{
			return REL::RelocateMember<RUNTIME_DATA>(this, 0x50, 0x60);
		}

		// members
#if !defined(ENABLE_SKYRIM_VR) || (!defined(ENABLE_SKYRIM_AE) && !defined(ENABLE_SKYRIM_SE))
		RUNTIME_DATA_CONTENT  // 50, 60
#endif
	};
#ifndef ENABLE_SKYRIM_VR
	static_assert(sizeof(ModManagerMenu) == 0x58);
#elif !defined(ENABLE_SKYRIM_AE) && !defined(ENABLE_SKYRIM_SE)
	static_assert(sizeof(ModManagerMenu) == 0x68);
#endif
}
#undef RUNTIME_DATA_CONTENT
