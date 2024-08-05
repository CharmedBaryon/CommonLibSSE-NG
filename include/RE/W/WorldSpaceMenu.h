#pragma once

#include "RE/B/BSTEvent.h"
#include "RE/I/IMenu.h"
#include "RE/N/NiNode.h"

namespace RE
{
	class HudModeChangeEvent;

	// Used in a global array, which is processed every MAIN_DRAW
	// Cleared after each MAIN_DRAW
	struct QueuedMenuNodeUpdate
	{
	public:
		// members
		NiNode*  menuNode;  // 00 - set to WorldSpaceMenu->unk48
		bool     hideMenu;  // 08 - false also unhides the menu if its already hidden
		uint32_t unk0C;     // 0C
		uint32_t unk10;     // 10 - set to WorldSpaceMenu->unk30, applied somehow to every child in the menunode
		uint32_t unk14;     // 14
	};
	static_assert(sizeof(QueuedMenuNodeUpdate) == 0x18);

	// menuDepth = 4
	// context = 22
	class WorldSpaceMenu :
#ifndef SKYRIM_CROSS_VR
		public IMenu,                            // 00
		public BSTEventSink<HudModeChangeEvent>  // 40
#else
		public IMenu  // 00
#endif
	{
	public:
#if defined(EXCLUSIVE_SKYRIM_VR)
		inline static constexpr auto RTTI = RTTI_WorldSpaceMenu;
#endif
		WorldSpaceMenu(bool a_registerHudModeChangeEvent, bool a_matchAsTopMenu, bool a_queueUpdateFixup);

		~WorldSpaceMenu() override;  // 00

		[[nodiscard]] BSTEventSink<HudModeChangeEvent>* AsHudModeChangeEventSink() noexcept
		{
			if (!REL::Module::IsVR()) {
				return nullptr;
			}
			return &REL::RelocateMember<BSTEventSink<HudModeChangeEvent>>(this, 0, 0x40);
		}

		[[nodiscard]] const BSTEventSink<HudModeChangeEvent>* AsHudModeChangeEventSink() const noexcept
		{
			return const_cast<WorldSpaceMenu*>(this)->AsHudModeChangeEventSink();
		}

		// override
		virtual void               PostCreate() override;                          // 02
		virtual UI_MESSAGE_RESULTS ProcessMessage(UIMessage& a_message) override;  // 04
#ifdef ENABLE_SKYRIM_VR
		virtual void               Unk_09(UI_MENU_Unk09 a_unk) override;           // 09
#endif

		// add
		virtual void        SetupMenuNode();          // 0B - Sets up menuNode
		virtual RE::NiNode* GetMenuParentNode() = 0;  // 0C - purecall, menuNode is attached to this in PostCreate()
		virtual void        SetTransform() = 0;       // 0D - purecall, set rotation,translation, etc. called in PostCreate()

		bool MessageMatchesMenu(RE::UIMessage* a_message);

		void SetupMenuNodeWithNif(const char* nif, bool unk);

		RE::NiPointer<RE::NiNode> menuNode;                       // 48 - Created automatically in SetupMenuNode()
		bool                      registerForHudModeChangeEvent;  // 50 - Set/Used in WorldSpaceMenu constructor
		bool                      matchAsTopMenu{ false };        // 51 - Only used when calling MessageMatchesMenu so far
		bool                      queueUpdateFixup{ false };      // 52 - Update menuNode immediately, or on next MAIN_DRAW when calling Unk_09
		std::uint8_t              pad53{ 0 };
		std::uint32_t             pad54{ 0 };

	private:
		KEEP_FOR_RE()
	};
#if defined(EXCLUSIVE_SKYRIM_FLAT)
	static_assert(sizeof(WorldSpaceMenu) == 0x48);
#elif defined(EXCLUSIVE_SKYRIM_VR)
	static_assert(sizeof(WorldSpaceMenu) == 0x58);
#else
	static_assert(sizeof(WorldSpaceMenu) == 0x40);
#endif
}
