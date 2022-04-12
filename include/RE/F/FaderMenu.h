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
		inline static auto                RTTI = RTTI_FaderMenu;
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

		virtual ~FaderMenu();  // 00

		// override (IMenu)
		virtual UI_MESSAGE_RESULTS ProcessMessage(UIMessage& a_message) override;  // 04

		// members
#if !defined(ENABLE_SKYRIM_VR) || (!defined(ENABLE_SKYRIM_AE) && !defined(ENABLE_SKYRIM_SE))
		RUNTIME_DATA_CONTENT  // 30 - smart ptr
#endif
	};
#ifndef ENABLE_SKYRIM_VR
	static_assert(sizeof(FaderMenu) == 0x40);
#elif !defined(ENABLE_SKYRIM_AE) && !defined(ENABLE_SKYRIM_SE)
	static_assert(sizeof(FaderMenu) == 0x50);
#endif
}
#undef RUNTIME_DATA_CONTENT
