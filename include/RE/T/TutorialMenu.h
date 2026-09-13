#pragma once

#include "RE/B/BGSDefaultObjectManager.h"
#include "RE/G/GFxValue.h"
#include "RE/I/IMenu.h"
#include "REL/RuntimeDataAccessors.h"

namespace RE
{
	// menuDepth = 10
	// flags = kPausesGame | kModal | kUpdateUsesCursor
	// context = kMenuMode
	class TutorialMenu : public IMenu
	{
	public:
		inline static constexpr auto      RTTI = RTTI_TutorialMenu;
		inline static constexpr auto      VTABLE = VTABLE_TutorialMenu;
		constexpr static std::string_view MENU_NAME = "Tutorial Menu";

		~TutorialMenu() override;  // 00

		// override (IMenu)
		void               Accept(CallbackProcessor* a_processor) override;  // 01
		UI_MESSAGE_RESULTS ProcessMessage(UIMessage& a_message) override;    // 04

		[[nodiscard]] inline GFxValue GetRoot() const noexcept
		{
			return REL::RelocateMember<GFxValue>(this, 0x30, 0x40);
		}

		inline void SetRoot(GFxValue a_root) noexcept
		{
			REL::RelocateMember<GFxValue>(this, 0x30, 0x40) = a_root;
		}

		static BSTArray<DEFAULT_OBJECT>& QTutorialsShown();

		static void OpenMenu(DEFAULT_OBJECT a_id);
		static void OpenMenu(BGSMessage* a_message);
		static void OpenMenu(DEFAULT_OBJECT a_id, BGSMessage* a_message);

		// members
#ifndef SKYRIM_CROSS_VR
		GFxValue root;  // 30, 40 - "Menu_mc"
#endif
	};
	STATIC_ASSERT_SIZE(TutorialMenu, 0x48, 0x48, 0x58, 0x30);
}
