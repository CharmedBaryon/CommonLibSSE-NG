#pragma once

#include "RE/B/BSTArray.h"
#include "RE/G/GFxValue.h"
#include "RE/I/IMenu.h"

namespace RE
{
	class GFxMovieView;
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
		constexpr static std::string_view MENU_NAME = "InventoryMenu";

		struct RUNTIME_DATA
		{
#define RUNTIME_DATA_CONTENT                                                       \
	GFxValue        root;            /* 00 - kDisplayObject - "_level0.Menu_mc" */ \
	ItemList*       itemList;        /* 18 */                                      \
	ItemCard*       itemCard;        /* 20 */                                      \
	BottomBar*      bottomBar;       /* 28 */                                      \
	BSTArray<void*> unk60;           /* 30 */                                      \
	std::uint8_t    unk78;           /* 48 */                                      \
	std::uint8_t    pad79;           /* 49 */                                      \
	std::uint16_t   pad7A;           /* 4A */                                      \
	std::uint32_t   unk7C;           /* 4C */                                      \
	bool            pcControlsReady; /* 50 */                                      \
	std::uint8_t    unk81;           /* 51 */                                      \
	std::uint16_t   pad82;           /* 52 */                                      \
	std::uint32_t   pad84;           /* 54 */

			RUNTIME_DATA_CONTENT
		};
		static_assert(sizeof(RUNTIME_DATA) == 0x58);

		~InventoryMenu() override;  // 00

		// override (IMenu)
		void               Accept(CallbackProcessor* a_processor) override;  // 01
		UI_MESSAGE_RESULTS ProcessMessage(UIMessage& a_message) override;    // 04
		void               PostDisplay() override;                           // 06

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
		RUNTIME_DATA_CONTENT;  // 30, 40
#endif
	private:
		KEEP_FOR_RE()
	};
#if defined(EXCLUSIVE_SKYRIM_FLAT)
	static_assert(sizeof(InventoryMenu) == 0x88);
#elif defined(EXCLUSIVE_SKYRIM_VR)
	static_assert(sizeof(InventoryMenu) == 0x98);
#else
	static_assert(sizeof(InventoryMenu) == 0x30);
#endif
}
#undef RUNTIME_DATA_CONTENT
