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
		public IMenu,            // 00
		public MenuEventHandler  // 30
	{
	public:
		inline static auto                RTTI = RTTI_FavoritesMenu;
		constexpr static std::string_view MENU_NAME = "FavoritesMenu";

		struct Entry
		{
			TESForm*            item;       // 00
			InventoryEntryData* entryData;  // 08
		};
		static_assert(sizeof(Entry) == 0x10);

		struct RUNTIME_DATA
		{
			GFxValue        root;             // 00 - "Menu_mc"
			BSTArray<Entry> favorites;        // 18
			std::uint16_t   unk70;            // 30
			bool            pcControlsReady;  // 32
			bool            isVampire;        // 33
			std::uint32_t   pad74;            // 34
		};
		static_assert(sizeof(RUNTIME_DATA) == 0x38);

		~FavoritesMenu() override;  // 00

		// override (IMenu)
		void               Accept(CallbackProcessor* a_processor) override;  // 01
		UI_MESSAGE_RESULTS ProcessMessage(UIMessage& a_message) override;    // 04

		// override (MenuEventHandler)
		bool CanProcess(InputEvent* a_event) override;      // 01
		bool ProcessKinect(KinectEvent* a_event) override;  // 02
		bool ProcessButton(ButtonEvent* a_event) override;  // 05

		[[nodiscard]] inline RUNTIME_DATA& GetRuntimeData() noexcept
		{
			return REL::RelocateMember<RUNTIME_DATA>(this, 0x40, 0x50);
		}

		[[nodiscard]] inline const RUNTIME_DATA& GetRuntimeData() const noexcept
		{
			return REL::RelocateMember<RUNTIME_DATA>(this, 0x40, 0x50);
		}

		// members
#if !defined(ENABLE_SKYRIM_VR) || (!defined(ENABLE_SKYRIM_AE) && !defined(ENABLE_SKYRIM_SE))
		RUNTIME_DATA runtimeData; // 40, 50
#endif
	};
#ifndef ENABLE_SKYRIM_VR
	static_assert(sizeof(FavoritesMenu) == 0x78);
#elif !defined(ENABLE_SKYRIM_AE) && !defined(ENABLE_SKYRIM_SE)
	static_assert(sizeof(FavoritesMenu) == 0x88);
#endif
}
