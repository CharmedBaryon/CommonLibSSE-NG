#pragma once

#include "RE/B/BSTArray.h"
#include "RE/G/GFxValue.h"
#include "RE/I/IMenu.h"

namespace RE
{
	struct ItemCard;
	struct ItemList;

	// menuDepth = 3
	// flags = kPausesGame | kUsesMenuContext | kDisablePauseMenu | kUpdateUsesCursor | kInventoryItemMenu | kCustomRendering
	// context = kItemMenu
	class GiftMenu : public IMenu
	{
	public:
		inline static constexpr auto      RTTI = RTTI_GiftMenu;
		constexpr static std::string_view MENU_NAME = "GiftMenu";

		struct RUNTIME_DATA
		{
#define RUNTIME_DATA_CONTENT                              \
	GFxValue        root;            /* 00 - "Menu_mc" */ \
	ItemList*       itemList;        /* 18 */             \
	ItemCard*       itemCard;        /* 20 */             \
	BSTArray<void*> unk58;           /* 28 */             \
	std::uint64_t   unk70;           /* 40 */             \
	bool            pcControlsReady; /* 48 */             \
	std::uint8_t    pad79;           /* 49 */             \
	std::uint16_t   pad7A;           /* 4A */             \
	std::uint32_t   pad7C;           /* 4C */

			RUNTIME_DATA_CONTENT
		};
		static_assert(sizeof(RUNTIME_DATA) == 0x50);

		~GiftMenu() override;  // 00

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
		RUNTIME_DATA_CONTENT;  // 30, 40
#endif
	private:
		KEEP_FOR_RE()
	};
#if defined(EXCLUSIVE_SKYRIM_FLAT)
	static_assert(sizeof(GiftMenu) == 0x80);
#elif defined(EXCLUSIVE_SKYRIM_VR)
	static_assert(sizeof(GiftMenu) == 0x90);
#else
	static_assert(sizeof(GiftMenu) == 0x30);
#endif

};
#undef RUNTIME_DATA_CONTENT
