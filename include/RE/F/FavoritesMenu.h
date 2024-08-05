#pragma once

#include "RE/B/BSTArray.h"
#include "RE/G/GFxValue.h"
#include "RE/I/IMenu.h"
#include "RE/M/MenuEventHandler.h"

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
		bool CanProcess(InputEvent* a_event) override;      // 01
		bool ProcessKinect(KinectEvent* a_event) override;  // 02
		bool ProcessButton(ButtonEvent* a_event) override;  // 05
#endif

		[[nodiscard]] MenuEventHandler* AsMenuEventHandler() noexcept
		{
			return &REL::RelocateMember<MenuEventHandler>(this, 0x30, 0x40);
		}

		[[nodiscard]] const MenuEventHandler* AsMenuEventHandler() const noexcept
		{
			return const_cast<FavoritesMenu*>(this)->AsMenuEventHandler();
		}

		[[nodiscard]] inline RUNTIME_DATA& GetRuntimeData() noexcept
		{
			return REL::RelocateMember<RUNTIME_DATA>(this, 0x40, 0x50);
		}

		[[nodiscard]] inline const RUNTIME_DATA& GetRuntimeData() const noexcept
		{
			return REL::RelocateMember<RUNTIME_DATA>(this, 0x40, 0x50);
		}

		// members
#ifndef SKYRIM_CROSS_VR
		RUNTIME_DATA_CONTENT;  // 40, 50
#endif
	private:
		KEEP_FOR_RE()
	};
#if defined(EXCLUSIVE_SKYRIM_FLAT)
	static_assert(sizeof(FavoritesMenu) == 0x78);
#elif defined(EXCLUSIVE_SKYRIM_VR)
	static_assert(sizeof(FavoritesMenu) == 0x88);
#else
	static_assert(sizeof(FavoritesMenu) == 0x30);
#endif
}
#undef RUNTIME_DATA_CONTENT
