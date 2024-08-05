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
		inline static constexpr auto      RTTI = RTTI_LevelUpMenu;
		constexpr static std::string_view MENU_NAME = "LevelUp Menu";

		struct RUNTIME_DATA
		{
#define RUNTIME_DATA_CONTENT      \
	bool          unk30; /* 00 */ \
	std::uint8_t  pad31; /* 01 */ \
	std::uint16_t pad32; /* 02 */ \
	std::uint32_t pad34; /* 04 */

			RUNTIME_DATA_CONTENT
		};
		static_assert(sizeof(RUNTIME_DATA) == 0x8);

		~LevelUpMenu() override;  // 00

		// override (IMenu)
		void Accept(CallbackProcessor* a_cbReg) override;  // 01

		[[nodiscard]] inline RUNTIME_DATA& GetRuntimeData() noexcept
		{
			return REL::RelocateMember<RUNTIME_DATA>(this, 0x30, 0x40);
		}

		[[nodiscard]] inline const RUNTIME_DATA& GetRuntimeData() const noexcept
		{
			return REL::RelocateMember<RUNTIME_DATA>(this, 0x30, 0x40);
		}

		// members
#ifndef SKYRIM_CROSS_VR
		RUNTIME_DATA_CONTENT;  // 30, 40
#endif
	private:
		KEEP_FOR_RE()
	};
#if defined(EXCLUSIVE_SKYRIM_FLAT)
	static_assert(sizeof(LevelUpMenu) == 0x38);
#elif defined(EXCLUSIVE_SKYRIM_VR)
	static_assert(sizeof(LevelUpMenu) == 0x48);
#else
	static_assert(sizeof(LevelUpMenu) == 0x30);
#endif
}
#undef RUNTIME_DATA_CONTENT
