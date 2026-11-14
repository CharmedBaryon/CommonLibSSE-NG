#pragma once

#include "RE/B/BSTArray.h"
#include "RE/G/GFxValue.h"
#include "RE/I/IMenu.h"
#include "RE/M/MenuEventHandler.h"
#include "REL/RuntimeDataAccessors.h"

namespace RE
{
	class InventoryEntryData;
	class TESForm;

	// menuDepth = 3
	// flags = kPausesGame | kUpdateUsesCursor | kInventoryItemMenu | kCustomRendering
	// context = kFavorites
	class FavoritesMenu :
#ifndef SKYRIM_CROSS_VR
		public IMenu,            // 00
		public MenuEventHandler  // 30
#else
		public IMenu  // 00
#endif
	{
	public:
		inline static constexpr auto      RTTI = RTTI_FavoritesMenu;
		inline static constexpr auto      VTABLE = VTABLE_FavoritesMenu;
		constexpr static std::string_view MENU_NAME = "FavoritesMenu";

		struct Entry
		{
			TESForm*            item;       // 00
			InventoryEntryData* entryData;  // 08
		};
		static_assert(sizeof(Entry) == 0x10);

		struct RUNTIME_DATA
		{
#define RUNTIME_DATA_CONTENT                              \
	GFxValue        root;            /* 00 - "Menu_mc" */ \
	BSTArray<Entry> favorites;       /* 18 */             \
	std::uint16_t   unk70;           /* 30 */             \
	bool            pcControlsReady; /* 32 */             \
	bool            isVampire;       /* 33 */             \
	std::uint32_t   pad74;           /* 34 */

			RUNTIME_DATA_CONTENT
		};
		static_assert(sizeof(RUNTIME_DATA) == 0x38);

		~FavoritesMenu() override;  // 00

		// override (IMenu)
		void               Accept(CallbackProcessor* a_processor) override;  // 01
		UI_MESSAGE_RESULTS ProcessMessage(UIMessage& a_message) override;    // 04

		// override (MenuEventHandler)
#ifndef SKYRIM_CROSS_VR
		bool CanProcess(InputEvent* a_event) override;  // 01
#endif
#ifdef EXCLUSIVE_SKYRIM_VR
		bool ProcessKinect(KinectEvent* a_event) override;  // 02
		bool ProcessButton(ButtonEvent* a_event) override;  // 05
#endif

#ifndef SKYRIM_CROSS_VR
		RUNTIME_CAST_ACCESSOR(MenuEventHandler, AsMenuEventHandler, 0x30, 0x40);
#endif

		RUNTIME_DATA_ACCESSOR(RUNTIME_DATA, 0x40, 0x50);
		// members
#ifndef SKYRIM_CROSS_VR
		RUNTIME_DATA_CONTENT;  // 40, 50
#endif
	};
	STATIC_ASSERT_SIZE(FavoritesMenu, 0x78, 0x78, 0x88, 0x30);
}
#undef RUNTIME_DATA_CONTENT
