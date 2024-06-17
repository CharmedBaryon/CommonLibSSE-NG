#include "RE/W/WorldSpaceMenu.h"
#include "RE/I/InterfaceStrings.h"
#include "RE/U/UI.h"
#include "RE/U/UIMessage.h"

#ifdef ENABLE_SKYRIM_VR
namespace RE
{
	WorldSpaceMenu::~WorldSpaceMenu()
	{
		// TODO, unregister if registered on hudmodechangevent
		if (menuNode.get() && menuNode.get()->parent) {
			if (menuNode.get()->parent) {
				menuNode.get()->parent->DetachChild2(menuNode.get());
			}
			menuNode.reset();
		}

		menuName.~BSFixedString();
		fxDelegate.reset();
		uiMovie.reset();
	}

	WorldSpaceMenu::WorldSpaceMenu(bool a_registerHudModeChangeEvent, bool a_matchAsTopMenu, bool a_queueUpdateFixup)
	{
		this->registerForHudModeChangeEvent = a_registerHudModeChangeEvent;
		this->matchAsTopMenu = a_matchAsTopMenu;
		this->queueUpdateFixup = a_queueUpdateFixup;
		this->Unk_09(RE::UI_MENU_Unk09::kNone);
		this->menuFlags.set(RE::UI_MENU_FLAGS::kUsesCursor, RE::UI_MENU_FLAGS::kModal,
			RE::UI_MENU_FLAGS::kDisablePauseMenu, RE::UI_MENU_FLAGS::kTopmostRenderedMenu,
			RE::UI_MENU_FLAGS::kAllowSaving, RE::UI_MENU_FLAGS::kInventoryItemMenu);
		this->depthPriority = 2;
		if (this->registerForHudModeChangeEvent) {
			// TODO: Register the menu for the hud mode change event
			// See SkyrimVR.exe+53D050
		}
	}

	void WorldSpaceMenu::PostCreate()
	{
		using func_t = decltype(&WorldSpaceMenu::PostCreate);
		REL::Relocation<func_t> func{ REL::Offset(0x53C140) };
		return func(this);
	}

	UI_MESSAGE_RESULTS WorldSpaceMenu::ProcessMessage(UIMessage& a_message)
	{
		using func_t = decltype(&WorldSpaceMenu::ProcessMessage);
		REL::Relocation<func_t> func{ REL::Offset(0x53C2B0) };
		return func(this, a_message);
	}
	void WorldSpaceMenu::Unk_09(UI_MENU_Unk09 a_unk)
	{
		using func_t = decltype(&WorldSpaceMenu::Unk_09);
		REL::Relocation<func_t> func{ REL::Offset(0x53C220) };
		return func(this, a_unk);
	}

	void WorldSpaceMenu::SetupMenuNode()
	{
		using func_t = decltype(&WorldSpaceMenu::SetupMenuNode);
		REL::Relocation<func_t> func{ REL::Offset(0x53C450) };
		return func(this);
	}

	void WorldSpaceMenu::SetupMenuNodeWithNif(const char* nif, bool a_unk)
	{
		using func_t = decltype(&WorldSpaceMenu::SetupMenuNodeWithNif);
		REL::Relocation<func_t> func{ REL::Offset(0x53CB50) };
		return func(this, nif, a_unk);
	}

	bool WorldSpaceMenu::MessageMatchesMenu(RE::UIMessage* a_message)
	{
		// See: SkyrimVR.exe+53C4B0
		bool isTopMenu = false;
		if (matchAsTopMenu) {
			RE::IMenu* topMenu = 0;
			UI::GetSingleton()->GetTopMostMenu(&topMenu, 15);
			if (topMenu &&
				topMenu->menuName == InterfaceStrings::GetSingleton()->hudMenu &&
				a_message->menu == InterfaceStrings::GetSingleton()->topMenu) {
				isTopMenu = true;
			}
		}
		return isTopMenu || a_message->menu == menuName;
	}
}
#endif
