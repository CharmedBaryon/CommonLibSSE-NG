#pragma once

#include "RE/I/IMenu.h"
#include "RE/I/IMessageBoxCallback.h"
#include "REL/RuntimeDataAccessors.h"

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
#define RUNTIME_DATA_CONTENT              \
	bool          playerLeveled; /* 00 */ \
	std::uint8_t  pad31;         /* 01 */ \
	std::uint16_t pad32;         /* 02 */ \
	std::uint32_t pad34;         /* 04 */

			RUNTIME_DATA_CONTENT
		};
		static_assert(sizeof(RUNTIME_DATA) == 0x8);
		class ConfirmLevelUpAttributeCallback : public IMessageBoxCallback
		{
		public:
			inline static constexpr auto RTTI = RTTI___ConfirmLevelUpAttributeCallback;
			inline static constexpr auto VTABLE = VTABLE___ConfirmLevelUpAttributeCallback;

			~ConfirmLevelUpAttributeCallback() override;  // 00

			// override (IMessageBoxCallback)
			void Run(std::uint8_t a_button) override;  // 01

			// members
			LevelUpMenu* menu;        // 10
			ActorValue   actorValue;  // 18
		};
		static_assert(sizeof(ConfirmLevelUpAttributeCallback) == 0x20);

		~LevelUpMenu() override;  // 00

		// override (IMenu)
		void Accept(CallbackProcessor* a_cbReg) override;  // 01

		RUNTIME_DATA_ACCESSOR(RUNTIME_DATA, 0x30, 0x40);
		// members
#ifndef SKYRIM_CROSS_VR
		RUNTIME_DATA_CONTENT;  // 30, 40
#endif
	};
	STATIC_ASSERT_SIZE(LevelUpMenu, 0x38, 0x38, 0x48, 0x30);
}
#undef RUNTIME_DATA_CONTENT
