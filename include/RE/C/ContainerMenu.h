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
	class ContainerMenu : public IMenu
	{
	public:
		inline static constexpr auto      RTTI = RTTI_ContainerMenu;
		constexpr static std::string_view MENU_NAME = "ContainerMenu";

		enum class ContainerMode : std::uint32_t
		{
			kLoot = 0,
			kSteal = 1,
			kPickpocket = 2,
			kNPCMode = 3
		};

		struct RUNTIME_DATA
		{
#define RUNTIME_DATA_CONTENT                              \
	GFxValue        root;            /* 00 - "Menu_mc" */ \
	ItemList*       itemList;        /* 18 */             \
	ItemCard*       itemCard;        /* 20 */             \
	BottomBar*      bottomBar;       /* 28 */             \
	BSTArray<void*> unk60;           /* 30 */             \
	BSTArray<void*> unk78;           /* 48 */             \
	std::uint64_t   unk90;           /* 60 */             \
	std::uint64_t   unk98;           /* 68 */             \
	std::uint64_t   unkA0;           /* 70 */             \
	std::uint8_t    unkA8;           /* 78 */             \
	std::uint8_t    padA9;           /* 79 */             \
	std::uint16_t   padAA;           /* 7A */             \
	std::uint32_t   padAC;           /* 7C */             \
	std::int32_t    value;           /* 80 */             \
	std::uint32_t   unkB4;           /* 84 */             \
	std::uint8_t    unkB8;           /* 88 */             \
	bool            pcControlsReady; /* 89 */             \
	std::uint16_t   padBA;           /* 8A */             \
	std::uint32_t   padBC;           /* 8C */

			RUNTIME_DATA_CONTENT
		};
		static_assert(sizeof(RUNTIME_DATA) == 0x90);

		~ContainerMenu() override;  // 00

		// override (IMenu)
		void               Accept(CallbackProcessor* a_processor) override;  // 01
		UI_MESSAGE_RESULTS ProcessMessage(UIMessage& a_message) override;    // 04
		void               PostDisplay() override;                           // 06

		[[nodiscard]] ContainerMode    GetContainerMode();
		[[nodiscard]] static RefHandle GetTargetRefHandle();

		[[nodiscard]] GFxValue  GetRoot() const noexcept;
		[[nodiscard]] ItemList* GetItemList() const noexcept;

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
	static_assert(sizeof(ContainerMenu) == 0xC0);
#elif defined(EXCLUSIVE_SKYRIM_VR)
	static_assert(sizeof(ContainerMenu) == 0xD0);
#else
	static_assert(sizeof(ContainerMenu) == 0x30);
#endif
}
#undef RUNTIME_DATA_CONTENT
