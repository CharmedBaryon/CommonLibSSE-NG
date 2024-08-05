#pragma once

#include "RE/I/IMenu.h"

namespace RE
{
	// menuDepth = 3
	// flags = kAlwaysOpen | kAllowSaving | kCustomRendering
	// context = kNone
	class FaderMenu : public IMenu
	{
	public:
		inline static constexpr auto      RTTI = RTTI_FaderMenu;
		constexpr static std::string_view MENU_NAME = "Fader Menu";

		struct RUNTIME_DATA
		{
#define RUNTIME_DATA_CONTENT                  \
	void*         unk30; /* 00 - smart ptr */ \
	std::uint8_t  unk38; /* 08 */             \
	std::uint8_t  unk39; /* 09 */             \
	std::uint16_t pad3A; /* 0A */             \
	std::uint32_t pad3C; /* 0C */

			RUNTIME_DATA_CONTENT
		};
		static_assert(sizeof(RUNTIME_DATA) == 0x10);

		~FaderMenu() override;  // 00

		// override (IMenu)
		UI_MESSAGE_RESULTS ProcessMessage(UIMessage& a_message) override;  // 04

		// members
#ifndef SKYRIM_CROSS_VR
		RUNTIME_DATA_CONTENT;  // 30 - smart ptr
#endif
	private:
		KEEP_FOR_RE()
	};
#if defined(EXCLUSIVE_SKYRIM_FLAT)
	static_assert(sizeof(FaderMenu) == 0x40);
#elif defined(EXCLUSIVE_SKYRIM_VR)
	static_assert(sizeof(FaderMenu) == 0x50);
#else
	static_assert(sizeof(FaderMenu) == 0x30);
#endif
}
#undef RUNTIME_DATA_CONTENT
