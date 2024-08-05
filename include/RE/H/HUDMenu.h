#pragma once

#include "RE/B/BSTArray.h"
#include "RE/B/BSTEvent.h"
#include "RE/G/GFxValue.h"
#include "RE/I/IMenu.h"
#include "RE/W/WorldSpaceMenu.h"

namespace RE
{
	class ActorValueMeter;
	class HudModeChangeEvent;
	class HUDObject;
	class ShoutMeter;
	class UserEventEnabledEvent;
	struct BSRemoteGamepadEvent;

	// menuDepth = 2
	// flags = kAlwaysOpen | kRequiresUpdate | kAllowSaving | kCustomRendering | kAssignCursorToRenderer
	// context = kNone
	class HUDMenu :
#if defined(EXCLUSIVE_SKYRIM_VR)
		public WorldSpaceMenu,                       // 00
		public BSTEventSink<UserEventEnabledEvent>,  // 58
		public BSTEventSink<BSRemoteGamepadEvent>    // 60
#elif !defined(ENABLE_SKYRIM_VR)
		public IMenu,                                // 00
		public BSTEventSink<UserEventEnabledEvent>,  // 30
		public BSTEventSink<BSRemoteGamepadEvent>    // 38
#else
		public IMenu  // 00
#endif
	{
	public:
		inline static constexpr auto      RTTI = RTTI_HUDMenu;
		inline static constexpr auto      VTABLE = VTABLE_HUDMenu;
		constexpr static std::string_view MENU_NAME = "HUD Menu";

		struct RUNTIME_DATA
		{
#define RUNTIME_DATA_CONTENT                                                                 \
	BSTArray<HUDObject*> objects; /* 00 */                                                   \
	ActorValueMeter*     health;  /* 18 */                                                   \
	ActorValueMeter*     stamina; /* 20 */                                                   \
	ActorValueMeter*     magicka; /* 28 */                                                   \
	ShoutMeter*          shout;   /* 30 */                                                   \
	GFxValue             root;    /* 38 - kDisplayObject - "_level0.HUDMovieBaseInstance" */ \
	std::uint64_t        unk90;   /* 50 */

			RUNTIME_DATA_CONTENT
		};

		~HUDMenu() override;  // 00

		// override (IMenu)
		void               Accept(CallbackProcessor* a_processor) override;                       // 01
		UI_MESSAGE_RESULTS ProcessMessage(UIMessage& a_message) override;                         // 04
		void               AdvanceMovie(float a_interval, std::uint32_t a_currentTime) override;  // 05
		void               RefreshPlatform() override;                                            // 08

#ifndef SKYRIM_CROSS_VR
		// override (BSTEventSink<UserEventEnabledEvent>)
		BSEventNotifyControl ProcessEvent(const UserEventEnabledEvent* a_event, BSTEventSource<UserEventEnabledEvent>* a_eventSource) override;  // 01

		// override (BSTEventSink<BSRemoteGamepadEvent>)
		BSEventNotifyControl ProcessEvent(const BSRemoteGamepadEvent* a_event, BSTEventSource<BSRemoteGamepadEvent>* a_eventSource) override;  // 01
#endif

		[[nodiscard]] WorldSpaceMenu* AsWorldSpaceMenu() noexcept
		{
			if SKYRIM_REL_CONSTEXPR (!REL::Module::IsVR()) {
				return nullptr;
			}
			return &REL::RelocateMember<WorldSpaceMenu>(this, 0, 0);
		}

		[[nodiscard]] const WorldSpaceMenu* AsWorldSpaceMenu() const noexcept
		{
			return const_cast<HUDMenu*>(this)->AsWorldSpaceMenu();
		}

		[[nodiscard]] BSTEventSink<UserEventEnabledEvent>* AsUserEventEnabledEventSink() noexcept
		{
			return &REL::RelocateMember<BSTEventSink<UserEventEnabledEvent>>(this, 0x30, 0x58);
		}

		[[nodiscard]] const BSTEventSink<UserEventEnabledEvent>* AsUserEventEnabledEventSink() const noexcept
		{
			return const_cast<HUDMenu*>(this)->AsUserEventEnabledEventSink();
		}

		[[nodiscard]] BSTEventSink<BSRemoteGamepadEvent>* AsBSRemoteGamepadEventSink() noexcept
		{
			return &REL::RelocateMember<BSTEventSink<BSRemoteGamepadEvent>>(this, 0x38, 0x60);
		}

		[[nodiscard]] const BSTEventSink<BSRemoteGamepadEvent>* AsBSRemoteGamepadEventSink() const noexcept
		{
			return const_cast<HUDMenu*>(this)->AsBSRemoteGamepadEventSink();
		}

		[[nodiscard]] inline RUNTIME_DATA& GetRuntimeData() noexcept
		{
			return REL::RelocateMember<RUNTIME_DATA>(this, 0x40, 0x70);
		}

		[[nodiscard]] inline const RUNTIME_DATA& GetRuntimeData() const noexcept
		{
			return REL::RelocateMember<RUNTIME_DATA>(this, 0x40, 0x70);
		}

		static void FlashMeter(ActorValue a_actorValue)
		{
			using func_t = decltype(&HUDMenu::FlashMeter);
			static REL::Relocation<func_t> func{ RELOCATION_ID(51907, 52845) };
			return func(a_actorValue);
		}

		static void UpdateCrosshairMagicTarget(bool a_valid)
		{
			using func_t = decltype(&HUDMenu::UpdateCrosshairMagicTarget);
			static REL::Relocation<func_t> func{ RELOCATION_ID(50738, 51633) };
			return func(a_valid);
		}

		// members
#ifndef SKYRIM_CROSS_VR
#	if defined(EXCLUSIVE_SKYRIM_VR)
		std::uint64_t pad68;  // 68
#	endif
		RUNTIME_DATA_CONTENT;  // 40, 70
#endif
	private:
		KEEP_FOR_RE()
	};
#ifndef ENABLE_SKYRIM_VR
	static_assert(sizeof(HUDMenu) == 0x98);
#elif defined(EXCLUSIVE_SKYRIM_VR)
	static_assert(sizeof(HUDMenu) == 0xC8);
#else
	static_assert(sizeof(HUDMenu) == 0x30);
#endif
}
#undef RUNTIME_DATA_CONTENT
