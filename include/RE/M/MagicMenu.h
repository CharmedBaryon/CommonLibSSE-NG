#pragma once

#include "RE/G/GFxValue.h"
#include "RE/I/IMenu.h"

namespace RE
{
	struct BottomBar;
	struct ItemCard;

	// menuDepth = 0
	// flags = kPausesGame | kUsesMenuContext | kDisablePauseMenu | kUpdateUsesCursor | kInventoryItemMenu | kCustomRendering
	// context = kItemMenu
	class MagicMenu : public IMenu
	{
	public:
		inline static constexpr auto      RTTI = RTTI_MagicMenu;
		inline static constexpr auto      VTABLE = VTABLE_MagicMenu;
		constexpr static std::string_view MENU_NAME = "MagicMenu";

		struct RUNTIME_DATA
		{
#define RUNTIME_DATA_CONTENT                                                  \
	void*         unk30;           /* 00 - some variation of the item list */ \
	ItemCard*     itemCard;        /* 08 */                                   \
	BottomBar*    bottomBar;       /* 10 */                                   \
	GFxValue      root;            /* 18 - "Menu_mc" */                       \
	bool          pcControlsReady; /* 30 */                                   \
	std::uint8_t  pad61;           /* 31 */                                   \
	std::uint16_t pad62;           /* 32 */                                   \
	std::uint32_t pad64;           /* 34 */

			RUNTIME_DATA_CONTENT
		};
		static_assert(sizeof(RUNTIME_DATA) == 0x38);

		~MagicMenu() override;  // 00

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
	static_assert(sizeof(MagicMenu) == 0x68);
#elif defined(EXCLUSIVE_SKYRIM_VR)
	static_assert(sizeof(MagicMenu) == 0x78);
#else
	static_assert(sizeof(MagicMenu) == 0x30);
#endif
}
#undef RUNTIME_DATA_CONTENT
