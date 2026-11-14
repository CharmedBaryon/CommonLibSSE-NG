#ifdef ENABLE_SKYRIM_VR
#	include "RE/W/WorldSpaceMenu.h"
#	include "RE/I/InterfaceStrings.h"
#	include "RE/U/UI.h"
#	include "RE/U/UIMessage.h"

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

		if (auto* vrData = GetVRRuntimeData()) {
			vrData->menuName.~BSFixedString();
		}
		fxDelegate.reset();
		uiMovie.reset();
	}

	WorldSpaceMenu::WorldSpaceMenu(bool a_registerHudModeChangeEvent, bool a_matchAsTopMenu, bool a_queueUpdateFixup)
	{
		this->registerForHudModeChangeEvent = a_registerHudModeChangeEvent;
		this->matchAsTopMenu = a_matchAsTopMenu;
		this->queueUpdateFixup = a_queueUpdateFixup;
		this->SetRenderTarget(RE::VRMenuRenderTarget::kNone);
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
		static REL::Relocation<func_t> func{ REL::Offset(0x53C140) };
		return func(this);
	}

	UI_MESSAGE_RESULTS WorldSpaceMenu::ProcessMessage(UIMessage& a_message)
	{
		using func_t = decltype(&WorldSpaceMenu::ProcessMessage);
		static REL::Relocation<func_t> func{ REL::Offset(0x53C2B0) };
		return func(this, a_message);
	}
	void WorldSpaceMenu::SetRenderTarget(VRMenuRenderTarget a_target)
	{
		if SKYRIM_REL_VR_CONSTEXPR (!REL::Module::IsVR()) {
			return;
		}
		using func_t = decltype(&WorldSpaceMenu::SetRenderTarget);
		static REL::Relocation<func_t> func{ REL::Offset(0x53C220) };
		return func(this, a_target);
	}

	void WorldSpaceMenu::SetupMenuNode()
	{
		using func_t = decltype(&WorldSpaceMenu::SetupMenuNode);
		static REL::Relocation<func_t> func{ REL::Offset(0x53C450) };
		return func(this);
	}

	void WorldSpaceMenu::SetupMenuNodeWithNif(const char* nif, REX::EnumSet<QueuedMenuNodeUpdate::Flag, std::uint32_t> a_flags)
	{
		using func_t = decltype(&WorldSpaceMenu::SetupMenuNodeWithNif);
		static REL::Relocation<func_t> func{ REL::Offset(0x53CB50) };
		return func(this, nif, a_flags);
	}

	bool WorldSpaceMenu::MessageMatchesMenu(RE::UIMessage* a_message)
	{
		// See: SkyrimVR.exe+53C4B0
		bool isTopMenu = false;
		if (matchAsTopMenu) {
			RE::IMenu* topMenu = 0;
			UI::GetSingleton()->GetTopMostMenu(&topMenu, 15);
			auto* topVrData = topMenu ? topMenu->GetVRRuntimeData() : nullptr;
			if (topVrData &&
				topVrData->menuName == InterfaceStrings::GetSingleton()->hudMenu &&
				a_message->menu == InterfaceStrings::GetSingleton()->topMenu) {
				isTopMenu = true;
			}
		}
		auto* vrData = GetVRRuntimeData();
		return isTopMenu || (vrData && a_message->menu == vrData->menuName);
	}
}
#endif
