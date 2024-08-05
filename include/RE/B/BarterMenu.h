#pragma once

#include "RE/B/BSTArray.h"
#include "RE/G/GFxValue.h"
#include "RE/I/IMenu.h"

namespace RE
{
	struct BottomBar;
	struct ItemCard;
	struct ItemList;

	// menuDepth = 0
	// flags = kPausesGame | kUsesMenuContext | kDisablePauseMenu | kUpdateUsesCursor | kInventoryItemMenu | kCustomRendering
	// context = kItemMenu
	class BarterMenu : public IMenu
	{
	public:
		inline static constexpr auto      RTTI = RTTI_BarterMenu;
		constexpr static std::string_view MENU_NAME = "BarterMenu";

		struct RUNTIME_DATA
		{
#define RUNTIME_DATA_CONTENT                              \
	ItemList*       itemList;        /* 00 */             \
	ItemCard*       itemCard;        /* 08 */             \
	BottomBar*      bottomBar;       /* 10 */             \
	GFxValue        root;            /* 18 - "Menu_mc" */ \
	std::uint64_t   unk60;           /* 30 */             \
	std::uint64_t   unk68;           /* 38 */             \
	std::uint64_t   unk70;           /* 40 */             \
	std::uint8_t    unk78;           /* 48 */             \
	std::uint8_t    pad79;           /* 49 */             \
	std::uint16_t   pad7A;           /* 4A */             \
	std::uint32_t   pad7C;           /* 4C */             \
	BSTArray<void*> unk80;           /* 50 */             \
	std::uint64_t   unk98;           /* 68 */             \
	std::uint32_t   unkA0;           /* 70 */             \
	bool            pcControlsReady; /* 74 */             \
	std::uint8_t    padA5;           /* 75 */             \
	std::uint16_t   padA6;           /* 76 */

			RUNTIME_DATA_CONTENT
		};
		static_assert(sizeof(RUNTIME_DATA) == 0x78);

		~BarterMenu() override;  // 00

		// override (IMenu)
		void               Accept(CallbackProcessor* a_processor) override;  // 01
		UI_MESSAGE_RESULTS ProcessMessage(UIMessage& a_message) override;    // 04
		void               PostDisplay() override;                           // 06

		[[nodiscard]] static RefHandle GetTargetRefHandle();

		[[nodiscard]] inline RUNTIME_DATA& GetRuntimeData() noexcept
		{
			return REL::RelocateMember<RUNTIME_DATA>(this, 0x30, 0x40);
		}

		[[nodiscard]] inline const RUNTIME_DATA& GetRuntimeData() const noexcept
		{
			return REL::RelocateMember<RUNTIME_DATA>(this, 0x30, 0x40);
		}

		// members
#ifndef SKYRIM_CROSS_VR
		RUNTIME_DATA_CONTENT  // 30, 40
#endif
	};
#if defined(EXCLUSIVE_SKYRIM_FLAT)
	static_assert(sizeof(BarterMenu) == 0xA8);
#elif defined(EXCLUSIVE_SKYRIM_VR)
	static_assert(sizeof(BarterMenu) == 0xB8);
#else
	static_assert(sizeof(BarterMenu) == 0x30);
#endif
}
#undef RUNTIME_DATA_CONTENT
