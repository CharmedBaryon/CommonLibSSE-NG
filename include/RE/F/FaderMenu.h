#pragma once

#include "RE/I/IMenu.h"
#include "REL/RuntimeDataAccessors.h"

namespace RE
{
	// menuDepth = 3
	// flags = kAlwaysOpen | kAllowSaving | kCustomRendering
	// context = kNone
	class FaderMenu : public IMenu
	{
	public:
		inline static constexpr auto      RTTI = RTTI_FaderMenu;
		inline static constexpr auto      VTABLE = VTABLE_FaderMenu;
		constexpr static std::string_view MENU_NAME = "Fader Menu";

		struct RUNTIME_DATA
		{
#define RUNTIME_DATA_CONTENT                     \
	void*         unk30;    /* 00 - smart ptr */ \
	bool          isActive; /* 08 */             \
	std::uint8_t  unk39;    /* 09 */             \
	std::uint16_t pad3A;    /* 0A */             \
	std::uint32_t pad3C;    /* 0C */

			RUNTIME_DATA_CONTENT
		};
		static_assert(sizeof(RUNTIME_DATA) == 0x10);

		~FaderMenu() override;  // 00

		// override (IMenu)
		UI_MESSAGE_RESULTS ProcessMessage(UIMessage& a_message) override;                         // 04
		void               AdvanceMovie(float a_interval, std::uint32_t a_currentTime) override;  // 05

		RUNTIME_DATA_ACCESSOR(RUNTIME_DATA, 0x30, 0x40);
		// members
#ifndef SKYRIM_CROSS_VR
		RUNTIME_DATA_CONTENT;  // 30 - smart ptr
#endif
	};
	STATIC_ASSERT_SIZE(FaderMenu, 0x40, 0x40, 0x50, 0x30);
}
#undef RUNTIME_DATA_CONTENT
