#pragma once

#include "RE/B/BSString.h"
#include "RE/B/BSTArray.h"
#include "RE/B/BSTSmartPointer.h"
#include "RE/C/CraftingSubMenu.h"
#include "RE/E/Effect.h"
#include "RE/F/FormTypes.h"
#include "RE/G/GFxValue.h"
#include "RE/I/IMessageBoxCallback.h"
#include "RE/M/MagicItemTraversalFunctor.h"

namespace RE
{
	class EnchantmentItem;
	class ExtraDataList;
	class InventoryEntryData;

	namespace CraftingSubMenus
	{
		class EnchantConstructMenu : public CraftingSubMenu
		{
		public:
			inline static constexpr auto RTTI = RTTI_CraftingSubMenus__EnchantConstructMenu;
			inline static constexpr auto VTABLE = VTABLE_CraftingSubMenus__EnchantConstructMenu;

			struct FilterTypes
			{
				enum FilterType
				{
					kDisenchant = 0,
					kDivider = 1,
					kItem = 2,
					kEnchantment = 3,
					kSoulGem = 4,

					kTotal = 5
				};
			};
			using FilterType = FilterTypes::FilterType;

			enum class FilterFlag
			{
				EnchantWeapon = 0x1,
				DisenchantWeapon = 0x2,
				EnchantArmor = 0x4,
				DisenchantArmor = 0x8,
				EffectWeapon = 0x10,
				EffectArmor = 0x20,
				SoulGem = 0x40,
			};

			enum class Category
			{
				Disenchant = 0,
				SoulGem = 1,
				Item = 2,
				Enchantment = 3,
			};

			class CategoryListEntry : public BSIntrusiveRefCounted
			{
			public:
				inline static constexpr auto RTTI = RTTI_CraftingSubMenus__EnchantConstructMenu__CategoryListEntry;
				inline static constexpr auto VTABLE = VTABLE_CraftingSubMenus__EnchantConstructMenu__CategoryListEntry;

				virtual ~CategoryListEntry();  // 00

				// add
				virtual void        ShowInItemCard(EnchantConstructMenu* a_menu);  // 01
				virtual void        ShowItem3D(bool a_show);                       // 02
				virtual const char* GetName();                                     // 03
				virtual void        SetData(GFxValue* dataContainer);              // 04

				// members
				REX::EnumSet<FilterFlag, std::uint32_t> filterFlag;  // 0C
				bool                                    selected;    // 10
				bool                                    enabled;     // 11
				std::uint16_t                           pad12;       // 12
				std::uint32_t                           pad14;       // 14
			};
			static_assert(sizeof(CategoryListEntry) == 0x18);

			class EnchantmentEntry : public CategoryListEntry
			{
			public:
				inline static constexpr auto RTTI = RTTI_CraftingSubMenus__EnchantConstructMenu__EnchantmentEntry;
				inline static constexpr auto VTABLE = VTABLE_CraftingSubMenus__EnchantConstructMenu__EnchantmentEntry;

				// members
				EnchantmentItem* data;          // 18
				float            magnitude;     // 20
				float            maxMagnitude;  // 24
			};
			static_assert(sizeof(EnchantmentEntry) == 0x28);

			class ItemChangeEntry : public CategoryListEntry
			{
			public:
				inline static constexpr auto RTTI = RTTI_CraftingSubMenus__EnchantConstructMenu__ItemChangeEntry;
				inline static constexpr auto VTABLE = VTABLE_CraftingSubMenus__EnchantConstructMenu__ItemChangeEntry;

				// members
				InventoryEntryData* data;  // 18
			};
			static_assert(sizeof(ItemChangeEntry) == 0x20);

			class CreateEffectFunctor : public MagicItemTraversalFunctor
			{
			public:
				inline static constexpr auto RTTI = RTTI_CraftingSubMenus__EnchantConstructMenu__CreateEffectFunctor;
				inline static constexpr auto VTABLE = VTABLE_CraftingSubMenus__EnchantConstructMenu__CreateEffectFunctor;

				~CreateEffectFunctor() override;  // 00

				// override (MagicItemTraversalFunctor)
				BSContainer::ForEachResult operator()(Effect* a_effect) override;  // 01

				// members
				BSTArray<Effect>  createdEffects;      // 10
				Effect*           costliestEffect;     // 28
				EnchantmentEntry* enchantmentParams;   // 30
				EnchantmentItem*  createdEnchantment;  // 38
				FormType          formType;            // 40
				TESForm*          baseObject;          // 48
				float             soulGemRatio;        // 50
				std::uint32_t     pad5C;               // 5C
			};
			static_assert(sizeof(CreateEffectFunctor) == 0x58);

			class EnchantMenuCallback : public IMessageBoxCallback
			{
			public:
				inline static constexpr auto RTTI = RTTI_CraftingSubMenus__EnchantConstructMenu__EnchantMenuCallback;
				inline static constexpr auto VTABLE = VTABLE_CraftingSubMenus__EnchantConstructMenu__EnchantMenuCallback;

				~EnchantMenuCallback() override;  // 00

				// members
				EnchantConstructMenu* subMenu;  // 10
			};
			static_assert(sizeof(EnchantMenuCallback) == 0x18);

			class EnchantMenuDisenchantCallback : public EnchantMenuCallback
			{
			public:
				inline static constexpr auto RTTI = RTTI_CraftingSubMenus__EnchantConstructMenu__EnchantMenuDisenchantCallback;
				inline static constexpr auto VTABLE = VTABLE_CraftingSubMenus__EnchantConstructMenu__EnchantMenuDisenchantCallback;

				~EnchantMenuDisenchantCallback() override;  // 00

				// override (EnchantMenuCallback)
				void Run(std::uint8_t a_button) override;  // 01
			};
			static_assert(sizeof(EnchantMenuDisenchantCallback) == 0x18);

			class EnchantMenuCraftCallback : public EnchantMenuCallback
			{
			public:
				inline static constexpr auto RTTI = RTTI_CraftingSubMenus__EnchantConstructMenu__EnchantMenuCraftCallback;
				inline static constexpr auto VTABLE = VTABLE_CraftingSubMenus__EnchantConstructMenu__EnchantMenuCraftCallback;

				~EnchantMenuCraftCallback() override;  // 00

				// override (EnchantMenuCallback)
				void Run(std::uint8_t a_button) override;  // 01
			};
			static_assert(sizeof(EnchantMenuCraftCallback) == 0x18);

			class EnchantMenuExitCallback : public EnchantMenuCallback
			{
			public:
				inline static constexpr auto RTTI = RTTI_CraftingSubMenus__EnchantConstructMenu__EnchantMenuExitCallback;
				inline static constexpr auto VTABLE = VTABLE_CraftingSubMenus__EnchantConstructMenu__EnchantMenuExitCallback;

				~EnchantMenuExitCallback() override;  // 00

				// override (EnchantMenuCallback)
				void Run(std::uint8_t a_button) override;  // 01
			};
			static_assert(sizeof(EnchantMenuExitCallback) == 0x18);

			struct Selections
			{
			public:
				// members
				BSTSmartPointer<ItemChangeEntry>            item;                    // 00
				BSTSmartPointer<ItemChangeEntry>            soulGem;                 // 08
				BSTArray<BSTSmartPointer<EnchantmentEntry>> effects;                 // 10
				std::uint32_t                               numEnchantmentsAllowed;  // 28
				std::uint32_t                               pad2C;                   // 2C
			};
			static_assert(sizeof(Selections) == 0x30);

			~EnchantConstructMenu() override;  // 00

			// override (CraftingSubMenu)
			void               Accept(CallbackProcessor* a_cbReg) override;          // 01
			[[nodiscard]] bool HasItemPreview() override;                            // 04 - { return currentCategory != Enchantment || craftItemPreview; }
			bool               ProcessUserEvent(BSFixedString* a_control) override;  // 05
			void               SetItemCardInfo(ItemCard* a_itemCard) override;       // 07

			void RenameItem(const char* a_name);
			void RenameItem_Impl(InventoryEntryData* a_entryData, ExtraDataList* a_extraList, const char* a_name);
			void UpdateInterface();

			// members
			REX::EnumSet<FilterFlag, std::uint32_t>      filters[FilterType::kTotal];  // 100
			std::uint32_t                                pad114;                       // 114
			BSTArray<BSTSmartPointer<CategoryListEntry>> listEntries;                  // 118
			BSString                                     customName;                   // 130
			GFxValue                                     categories;                   // 140
			GFxValue                                     inventoryLists;               // 158
			Selections                                   selected;                     // 170
			InventoryEntryData*                          craftItemPreview;             // 1A0
			CreateEffectFunctor                          createEffectFunctor;          // 1A8
			std::int32_t                                 sliderEnchantmentIndex;       // 200
			float                                        sliderMaxMagnitude;           // 204
			std::uint32_t                                highlightIndex;               // 208
			REX::EnumSet<Category, std::uint32_t>        currentCategory;              // 20C
			REX::EnumSet<FilterFlag, std::uint32_t>      enabledFilters;               // 210
			float                                        enchantmentCost;              // 214
			float                                        chargeAmount;                 // 218
			bool                                         exiting;                      // 21C
			bool                                         sliderShown;                  // 21D
			bool                                         hasHighlightedEntry;          // 21E
			std::uint8_t                                 pad21F;                       // 21F
		};
		static_assert(sizeof(EnchantConstructMenu) == 0x220);
	}
}
