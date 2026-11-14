#pragma once

#include "RE/B/BSTArray.h"
#include "RE/G/GFxValue.h"
#include "RE/I/IMenu.h"
#include "REL/RuntimeDataAccessors.h"

namespace RE
{
	class GFxMovieView;
	class TESBoundObject;
	class TESObjectREFR;
	struct BottomBar;
	struct ItemCard;
	struct ItemList;

	// menuDepth = 0
	// flags = kPausesGame | kDisablePauseMenu | kUpdateUsesCursor | kInventoryItemMenu | kCustomRendering
	// context = kNone
	class InventoryMenu : public IMenu
	{
	public:
		inline static constexpr auto      RTTI = RTTI_InventoryMenu;
		inline static constexpr auto      VTABLE = VTABLE_InventoryMenu;
		constexpr static std::string_view MENU_NAME = "InventoryMenu";

		struct RUNTIME_DATA
		{
#define RUNTIME_DATA_CONTENT                                                                      \
	GFxValue                  root;                 /* 00 - kDisplayObject - "_level0.Menu_mc" */ \
	ItemList*                 itemList;             /* 18 */                                      \
	ItemCard*                 itemCard;             /* 20 */                                      \
	BottomBar*                bottomBar;            /* 28 */                                      \
	BSTArray<TESBoundObject*> pendingUpdateObjects; /* 30 */                                      \
	std::uint8_t              unk78;                /* 48 */                                      \
	std::uint8_t              pad79;                /* 49 */                                      \
	std::uint16_t             pad7A;                /* 4A */                                      \
	std::uint32_t             unk7C;                /* 4C */                                      \
	bool                      pcControlsReady;      /* 50 */                                      \
	std::uint8_t              unk81;                /* 51 */                                      \
	std::uint16_t             pad82;                /* 52 */                                      \
	std::uint32_t             pad84;                /* 54 */

			RUNTIME_DATA_CONTENT
		};
		static_assert(sizeof(RUNTIME_DATA) == 0x58);

		~InventoryMenu() override;  // 00

		// override (IMenu)
		void               Accept(CallbackProcessor* a_processor) override;  // 01
		UI_MESSAGE_RESULTS ProcessMessage(UIMessage& a_message) override;    // 04
		void               PostDisplay() override;                           // 06

		void RefreshItemList()
		{
			using func_t = decltype(&InventoryMenu::RefreshItemList);
			static REL::Relocation<func_t> func{ RELOCATION_ID(50987, 51866) };
			return func(this);
		}

		void RefreshBottomBar()
		{
			using func_t = decltype(&InventoryMenu::RefreshBottomBar);
			static REL::Relocation<func_t> func{ RELOCATION_ID(50986, 51865) };
			return func(this);
		}

		RUNTIME_DATA_ACCESSOR(RUNTIME_DATA, 0x30, 0x40);
		// members
#ifndef SKYRIM_CROSS_VR
		RUNTIME_DATA_CONTENT;  // 30, 40
#endif
	};
	STATIC_ASSERT_SIZE(InventoryMenu, 0x88, 0x88, 0x98, 0x30);
}
#undef RUNTIME_DATA_CONTENT
