#pragma once

#include "RE/I/IMenu.h"

namespace RE
{
	// menuDepth = 3
	// flags = kPausesGame | kModal | kDisablePauseMenu
	// kUsesCursor is gamepad is disabled
	// context = kMenuMode
	class LevelUpMenu : public IMenu
	{
	public:
		inline static auto                RTTI = RTTI_LevelUpMenu;
		constexpr static std::string_view MENU_NAME = "LevelUp Menu";

		~LevelUpMenu() override;  // 00

		// override (IMenu)
		void Accept(CallbackProcessor* a_cbReg) override;  // 01

		// members
#if !defined(ENABLE_SKYRIM_VR) || (!defined(ENABLE_SKYRIM_AE) && !defined(ENABLE_SKYRIM_SE))
		bool          unk30;  // 30
		std::uint8_t  pad31;  // 31
		std::uint16_t pad32;  // 32
		std::uint32_t pad34;  // 34
#endif
	};
#ifndef ENABLE_SKYRIM_VR
	static_assert(sizeof(LevelUpMenu) == 0x38);
#elif !defined(ENABLE_SKYRIM_AE) && !defined(ENABLE_SKYRIM_SE)
	static_assert(sizeof(LevelUpMenu) == 0x48);
#endif
}
