#pragma once

#include "RE/B/BSTArray.h"
#include "RE/B/BSTSmartPointer.h"
#include "RE/G/GFxValue.h"
#include "RE/I/IGiftMenuScriptCallback.h"
#include "RE/I/IMenu.h"
#include "REL/RuntimeDataAccessors.h"

namespace RE
{
	class BGSListForm;
	class Actor;

	struct ItemCard;
	struct ItemList;

	// menuDepth = 3
	// flags = kPausesGame | kUsesMenuContext | kDisablePauseMenu | kUpdateUsesCursor | kInventoryItemMenu | kCustomRendering
	// context = kItemMenu
	class GiftMenu : public IMenu
	{
	public:
		inline static constexpr auto      RTTI = RTTI_GiftMenu;
		inline static constexpr auto      VTABLE = VTABLE_GiftMenu;
		constexpr static std::string_view MENU_NAME = "GiftMenu";

		struct RUNTIME_DATA
		{
#define RUNTIME_DATA_CONTENT                                                                                    \
	GFxValue        root;                  /* 00 - "Menu_mc" */                                                 \
	ItemList*       itemList;              /* 18 */                                                             \
	ItemCard*       itemCard;              /* 20 */                                                             \
	BSTArray<void*> unk58;                 /* 28 */                                                             \
	std::int32_t    totalValueTransferred; /* 40 - gold value, argument of the callback after menu is closed */ \
	std::uint32_t   unk74;                 /* 44 */                                                             \
	bool            pcControlsReady;       /* 48 */                                                             \
	std::uint8_t    pad79;                 /* 49 */                                                             \
	std::uint16_t   pad7A;                 /* 4A */                                                             \
	std::uint32_t   pad7C;                 /* 4C */

			RUNTIME_DATA_CONTENT
		};
		static_assert(sizeof(RUNTIME_DATA) == 0x50);

		~GiftMenu() override;  // 00

		// override (IMenu)
		void               Accept(CallbackProcessor* a_processor) override;  // 01
		UI_MESSAGE_RESULTS ProcessMessage(UIMessage& a_message) override;    // 04
		void               PostDisplay() override;                           // 06

		[[nodiscard]] static RefHandle                GetGifterRefHandle();
		[[nodiscard]] static RefHandle                GetReceiverRefHandle();
		[[nodiscard]] static bool                     GetShowStolenItems();
		[[nodiscard]] static BGSListForm*             GetFilterList();
		[[nodiscard]] static IGiftMenuScriptCallback* GetCallbackFn();

		static void OpenMenuAsGifter(Actor* a_receiver);
		static void OpenMenuAsGifter(Actor* a_receiver, GiftMenuCallback_t a_callbackFn, BGSListForm* a_filterList, bool a_showStolenItems);
		static void OpenMenuAsGifter(Actor* a_receiver, BSTSmartPointer<IGiftMenuScriptCallback>* a_callbackFn, BGSListForm* a_filterList, bool a_showStolenItems);
		static void OpenMenuAsReceiver(Actor* a_gifter);
		static void OpenMenuAsReceiver(Actor* a_gifter, GiftMenuCallback_t a_callbackFn, BGSListForm* a_filterList, bool a_showStolenItems);
		static void OpenMenuAsReceiver(Actor* a_gifter, BSTSmartPointer<IGiftMenuScriptCallback>* a_callbackFn, BGSListForm* a_filterList, bool a_showStolenItems);

		bool IsPlayerGifting();
		bool IsPlayerReceiving();

		RUNTIME_DATA_ACCESSOR(RUNTIME_DATA, 0x30, 0x40);
		// members
#ifndef SKYRIM_CROSS_VR
		RUNTIME_DATA_CONTENT;  // 30, 40
#endif
	private:
		static void OpenMenu_Impl(Actor* a_gifter, Actor* a_receiver, BSTSmartPointer<IGiftMenuScriptCallback>* a_callbackFn, BGSListForm* a_filterList, bool a_showStolenItems, bool a_useFavorPoints = false);  // value of a_useFavorPoints is always ignored
	};
	STATIC_ASSERT_SIZE(GiftMenu, 0x80, 0x80, 0x90, 0x30);
}
#undef RUNTIME_DATA_CONTENT
