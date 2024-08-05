#pragma once

#include "RE/A/ActorValues.h"
#include "RE/B/BSFixedString.h"
#include "RE/B/BSTEvent.h"
#include "RE/F/FxDelegateHandler.h"
#include "RE/G/GFxValue.h"

namespace RE
{
	class GFxMovieView;
	class TESFurniture;
	struct ItemCard;
	struct TESFurnitureEvent;

	namespace CraftingSubMenus
	{
		class CraftingSubMenu :
			public FxDelegateHandler,               // 00
			public BSTEventSink<TESFurnitureEvent>  // 10
		{
		public:
			inline static constexpr auto RTTI = RTTI_CraftingSubMenus__CraftingSubMenu;
			inline static constexpr auto VTABLE = VTABLE_CraftingSubMenus__CraftingSubMenu;

			~CraftingSubMenu() override;  // 00

			// add
			virtual void Unk_02(void);                                // 02 - { return; }
			virtual void Unk_03(void);                                // 03 - { return; }
			virtual bool HasItemPreview();                            // 04 - { return 1; }
			virtual bool ProcessUserEvent(BSFixedString* a_control);  // 05 - { return 0; }
			virtual void Unk_06(void);                                // 06 - { return; }
			virtual void SetItemCardInfo(ItemCard* a_itemCard);       // 07 - { return; }

			void UpdateCraftingInfo(ActorValue a_actorValue)
			{
				using func_t = decltype(&CraftingSubMenu::UpdateCraftingInfo);
				static REL::Relocation<func_t> func{ RELOCATION_ID(50461, 51364) };
				return func(this, a_actorValue);
			}

			// members
			GFxMovieView* view;                   // 018
			TESFurniture* furniture;              // 020
			ItemCard*     itemCard;               // 028
			GFxValue*     unk030;                 // 030
			GFxValue      craftingMenu;           // 038
			GFxValue      itemList;               // 050
			GFxValue      entryList;              // 068
			GFxValue      itemInfo;               // 080
			GFxValue      bottomBarInfo;          // 098
			GFxValue      additionalDescription;  // 0B0
			GFxValue      menuName;               // 0C8
			GFxValue      buttonText;             // 0E0
			bool          unk0F8;                 // 0F8
			std::uint8_t  pad0F9;                 // 0F9
			std::uint16_t pad0FA;                 // 0FA
			std::uint32_t pad0FC;                 // 0FC
		};
		static_assert(sizeof(CraftingSubMenu) == 0x100);
	}
}
