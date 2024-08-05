#pragma once

#include "RE/B/BSTArray.h"
#include "RE/B/BSTHashMap.h"
#include "RE/C/CraftingSubMenu.h"
#include "RE/I/IMessageBoxCallback.h"

namespace RE
{
	class InventoryEntryData;

	namespace CraftingSubMenus
	{
		class SmithingMenu : public CraftingSubMenu
		{
		public:
			inline static constexpr auto RTTI = RTTI_CraftingSubMenus__SmithingMenu;
			inline static constexpr auto VTABLE = VTABLE_CraftingSubMenus__SmithingMenu;

			class SmithingConfirmCallback : public IMessageBoxCallback
			{
			public:
				inline static constexpr auto RTTI = RTTI_CraftingSubMenus__SmithingMenu__SmithingConfirmCallback;
				inline static constexpr auto VTABLE = VTABLE_CraftingSubMenus__SmithingMenu__SmithingConfirmCallback;

				~SmithingConfirmCallback() override;  // 00

				// override (IMessageBoxCallback)
				void Run(Message a_msg) override;  // 01

				// members
				SmithingMenu* subMenu;  // 10
			};
			static_assert(sizeof(SmithingConfirmCallback) == 0x18);

			struct SmithingItemEntry
			{
				// members
				TESForm*                item;                 // 00
				std::int64_t            unk08;                // 08
				BGSConstructibleObject* constructibleObject;  // 10
				float                   unk18;                // 18 - Health of item?
				float                   unk1C;                // 1C - kSmithing actor value?
				int                     unk20;                // 20
				int                     unk24;                // 24
				std::byte               unk28;                // 28
				std::byte               unk29;                // 29
				std::byte               unk2A;                // 2A
				std::byte               pad2B;                // 2B
				std::uint32_t           pad2C;                // 2C
			};
			static_assert(sizeof(SmithingItemEntry) == 0x30);

			~SmithingMenu() override;  // 00

			// override (CraftingSubMenu)
			void Accept(CallbackProcessor* a_cbReg) override;          // 01
			void Unk_02(void) override;                                // 02
			bool ProcessUserEvent(BSFixedString* a_control) override;  // 05

			// members
			BSTArray<SmithingItemEntry>  unk100;        // 100
			BSTHashMap<UnkKey, UnkValue> unk118;        // 118 - constructibleObject map?
			NiPointer<TESObjectREFR>     furnitureRef;  // 148
			std::uint32_t                unk150;        // 150
			std::int32_t                 unk154;        // 154
			FormType                     smithingType;  // 158
			std::uint32_t                unk15C;        // 15C
			InventoryEntryData*          unk160;        // 160
		};
		static_assert(sizeof(SmithingMenu) == 0x168);
	}
}
