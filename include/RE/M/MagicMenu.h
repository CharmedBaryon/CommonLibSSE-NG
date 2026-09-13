#pragma once

#include "RE/G/GFxValue.h"
#include "RE/I/IMenu.h"
#include "REL/RuntimeDataAccessors.h"

namespace RE
{
	struct BottomBar;
	struct ItemCard;
	struct MagicItemList;

	// menuDepth = 0
	// flags = kPausesGame | kUsesMenuContext | kDisablePauseMenu | kUpdateUsesCursor | kInventoryItemMenu | kCustomRendering
	// context = kItemMenu
	class MagicMenu : public IMenu
	{
	public:
		inline static constexpr auto      RTTI = RTTI_MagicMenu;
		inline static constexpr auto      VTABLE = VTABLE_MagicMenu;
		constexpr static std::string_view MENU_NAME = "MagicMenu";

		struct RUNTIME_DATA
		{
#define RUNTIME_DATA_CONTENT                             \
	MagicItemList* itemList;        /* 00 */             \
	ItemCard*      itemCard;        /* 08 */             \
	BottomBar*     bottomBar;       /* 10 */             \
	GFxValue       root;            /* 18 - "Menu_mc" */ \
	bool           pcControlsReady; /* 30 */             \
	std::uint8_t   pad61;           /* 31 */             \
	std::uint16_t  pad62;           /* 32 */             \
	std::uint32_t  pad64;           /* 34 */

			RUNTIME_DATA_CONTENT
		};
		static_assert(sizeof(RUNTIME_DATA) == 0x38);

		~MagicMenu() override;  // 00

		// override (IMenu)
		void               Accept(CallbackProcessor* a_processor) override;  // 01
		UI_MESSAGE_RESULTS ProcessMessage(UIMessage& a_message) override;    // 04
		void               PostDisplay() override;                           // 06

		RUNTIME_DATA_ACCESSOR(RUNTIME_DATA, 0x30, 0x40);
		// members
#ifndef SKYRIM_CROSS_VR
		RUNTIME_DATA_CONTENT;  // 30, 40
#endif
	};
	STATIC_ASSERT_SIZE(MagicMenu, 0x68, 0x68, 0x78, 0x30);
}
#undef RUNTIME_DATA_CONTENT
