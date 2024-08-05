#pragma once

#include "RE/B/BSTArray.h"
#include "RE/C/CraftingSubMenu.h"
#include "RE/I/IMessageBoxCallback.h"

namespace RE
{
	namespace CraftingSubMenus
	{
		class ConstructibleObjectMenu : public CraftingSubMenu
		{
		public:
			inline static constexpr auto RTTI = RTTI_CraftingSubMenus__ConstructibleObjectMenu;
			inline static constexpr auto VTABLE = VTABLE_CraftingSubMenus__ConstructibleObjectMenu;

			class CreationConfirmCallback : public IMessageBoxCallback
			{
			public:
				inline static constexpr auto RTTI = RTTI_CraftingSubMenus__ConstructibleObjectMenu__CreationConfirmCallback;
				inline static constexpr auto VTABLE = VTABLE_CraftingSubMenus__ConstructibleObjectMenu__CreationConfirmCallback;

				~CreationConfirmCallback() override;  // 00

				// override (IMessageBoxCallback)
				void Run(Message a_msg) override;  // 01

				// members
				ConstructibleObjectMenu* menu;  // 10
			};
			static_assert(sizeof(CreationConfirmCallback) == 0x18);

			struct ItemEntry
			{
				BGSConstructibleObject* constructibleObject;  // 00
				std::uint32_t           filterFlag;           // 08
				std::uint32_t           pad0C;                // 0C
			};
			static_assert(sizeof(ItemEntry) == 0x10);

			enum class FilterFlags : std::uint32_t
			{
				Wood = 0x0,
				Hide = 0x1,
				Draugr = 0x2,
				Iron = 0x3,
				Studded = 0x4,
				Imperial = 0x5,
				Steel = 0x6,
				Leather = 0x7,
				Dwarven = 0x8,
				Elven = 0x9,
				Falmer = 0xA,
				Orcish = 0xB,
				Ebony = 0xC,
				Glass = 0xD,
				Dragon = 0xE,
				Daedric = 0xF,
				Jewelry = 0x10,
				Unk11 = 0x11,
				GenericCraftableKeyword01 = 0x12,
				GenericCraftableKeyword02 = 0x13,
				GenericCraftableKeyword03 = 0x14,
				GenericCraftableKeyword04 = 0x15,
				GenericCraftableKeyword05 = 0x16,
				GenericCraftableKeyword06 = 0x17,
				GenericCraftableKeyword07 = 0x18,
				GenericCraftableKeyword08 = 0x19,
				Bonemold = 0x1A,
				Chitin = 0x1B,
				Nordic = 0x1C,
				Stalhrim = 0x1D
			};

			~ConstructibleObjectMenu() override;  // 00

			// override (CraftingSubMenu)
			void Accept(CallbackProcessor* a_cbReg) override;     // 01
			void Unk_06(void) override;                           // 06
			void SetItemCardInfo(ItemCard* a_itemCard) override;  // 07

			// members
			BSTArray<ItemEntry>             crafts;               // 100
			BSTHashMap<FormID, FilterFlags> materialFilterFlags;  // 118 - kwd's formid -> FilterFlags
			std::uint32_t                   currentCobjIdx;       // 148
			std::uint32_t                   pad14C;               // 14C
			std::uint64_t                   unk150;               // 150
			std::uint64_t                   unk158;               // 158
		};
		static_assert(sizeof(ConstructibleObjectMenu) == 0x160);
	}
}
