#pragma once

#include "RE/B/BSFixedString.h"
#include "RE/B/BSTArray.h"
#include "RE/C/CraftingSubMenu.h"
#include "RE/I/IMessageBoxCallback.h"

namespace RE::CraftingSubMenus
{
	namespace CraftingSubMenus
	{
		class AlchemyMenu : public CraftingSubMenu
		{
		public:
			inline static constexpr auto RTTI = RTTI_CraftingSubMenus__AlchemyMenu;
			inline static constexpr auto VTABLE = VTABLE_CraftingSubMenus__AlchemyMenu;

			class QuitMenuCallback : public IMessageBoxCallback
			{
			public:
				inline static constexpr auto RTTI = RTTI_CraftingSubMenus__AlchemyMenu__QuitMenuCallback;
				inline static constexpr auto VTABLE = VTABLE_CraftingSubMenus__AlchemyMenu__QuitMenuCallback;

				~QuitMenuCallback() override;  // 00

				// override (IMessageBoxCallback)
				void Run(Message a_msg) override;  // 01

				// members
				AlchemyMenu* subMenu;  // 10
			};
			static_assert(sizeof(QuitMenuCallback) == 0x18);

			class UsableEffectMap
			{
			public:
				std::uint32_t ingredientIndex;               // 00
				std::uint32_t effectIndex;                   // 04
				std::uint32_t nextCompatibleEffectMapIndex;  // 08
			};
			static_assert(sizeof(UsableEffectMap) == 0xC);

			class MenuIngredientEntry
			{
			public:
				InventoryEntryData* ingredient;       // 00
				std::uint8_t        effect1FilterID;  // 09
				std::uint8_t        effect2FilterID;  // 0A
				std::uint8_t        effect3FilterID;  // 0B
				std::uint8_t        effect4FilterID;  // 0C
				std::uint8_t        isSelected;       // 0D
				std::uint8_t        isNotGreyed;      // 0E
				std::uint16_t       padE;             // 0F
			};
			static_assert(sizeof(MenuIngredientEntry) == 0x10);

			class PotionCreationData
			{
			public:
				BSTArray<UsableEffectMap>      usableEffectsMaps;  // 0
				BSTArray<MenuIngredientEntry>* ingredientEntries;  // 18
			};
			static_assert(sizeof(PotionCreationData) == 0x20);

			~AlchemyMenu() override;  // 00

			// override (CraftingSubMenu)
			void Accept(CallbackProcessor* a_cbReg) override;          // 01
			bool ProcessUserEvent(BSFixedString* a_control) override;  // 05

			// members
			BSTArray<MenuIngredientEntry>   ingredientEntries;      // 100
			BSTSmallArray<std::uint32_t, 4> selectedIndexes;        // 118
			PotionCreationData              potionCreationData;     // 138
			GFxValue                        categories;             // 158
			InventoryEntryData*             resultPotionEntry;      // 170
			AlchemyItem*                    unknownPotion;          // 178 - displayed when player does not know effects
			AlchemyItem*                    resultPotion;           // 180
			std::uint32_t                   currentIngredientIdx;   // 188
			std::uint32_t                   pad18C;                 // 18C
			BSFixedString                   newRecipeFormatString;  // 190
			bool                            playerHasPurityPerk;    // 198
			std::uint8_t                    pad199;                 // 199
			std::uint16_t                   pad19A;                 // 19A
			std::uint32_t                   pad19C;                 // 19C
		};
		static_assert(sizeof(AlchemyMenu) == 0x1A0);
	}
}
