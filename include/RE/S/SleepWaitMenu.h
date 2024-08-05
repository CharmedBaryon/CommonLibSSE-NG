#pragma once

#include "RE/G/GFxValue.h"
#include "RE/I/IMenu.h"

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
		constexpr static std::string_view MENU_NAME = "Sleep/Wait Menu";

		struct RUNTIME_DATA
		{
#define RUNTIME_DATA_CONTENT                           \
	std::uint32_t unk30; /* 00 */                      \
	std::uint32_t pad34; /* 04 */                      \
	GFxValue      root;  /* 08 - "SleepWaitMenu_mc" */ \
	std::uint8_t  unk50; /* 20 */                      \
	std::uint8_t  unk51; /* 21 */                      \
	std::uint16_t pad52; /* 22 */                      \
	std::uint32_t pad54; /* 24 */

			RUNTIME_DATA_CONTENT
		};
		static_assert(sizeof(RUNTIME_DATA) == 0x28);

		~SleepWaitMenu() override;  // 00

		// override (IMenu)
		void               Accept(CallbackProcessor* a_processor) override;  // 01
		UI_MESSAGE_RESULTS ProcessMessage(UIMessage& a_message) override;    // 04

		[[nodiscard]] inline RUNTIME_DATA& GetRuntimeData() noexcept
		{
			return REL::RelocateMember<RUNTIME_DATA>(this, 0x30, 0x40);
		}

		[[nodiscard]] inline const RUNTIME_DATA& GetRuntimeData() const noexcept
		{
			return REL::RelocateMember<RUNTIME_DATA>(this, 0x30, 0x40);
		}

		static void ToggleOpenSleepWaitMenu(bool a_sleeping)
		{
			using func_t = decltype(&SleepWaitMenu::ToggleOpenSleepWaitMenu);
			static REL::Relocation<func_t> func{ RELOCATION_ID(51618, 52490) };
			return func(a_sleeping);
		}
		
		// members
#ifndef SKYRIM_CROSS_VR
		RUNTIME_DATA_CONTENT;  // 30, 40
#endif
	private:
		KEEP_FOR_RE()
	};
#if defined(EXCLUSIVE_SKYRIM_FLAT)
	static_assert(sizeof(SleepWaitMenu) == 0x58);
#elif defined(EXCLUSIVE_SKYRIM_VR)
	static_assert(sizeof(SleepWaitMenu) == 0x68);
#else
	static_assert(sizeof(SleepWaitMenu) == 0x30);
#endif
}
#undef RUNTIME_DATA_CONTENT
