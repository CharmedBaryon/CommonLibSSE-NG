#pragma once

#include "RE/B/BSTArray.h"
#include "RE/B/BSTEvent.h"
#include "RE/G/GFxValue.h"
#include "RE/I/IMenu.h"

#if !defined(ENABLE_SKYRIM_AE) && !(ENABLE_SKYRIM_SE)
#	include "RE/W/WorldSpaceMenu.h"
#endif

namespace RE
{
	class ActorValueMeter;
	class HUDObject;
	class ShoutMeter;
	class UserEventEnabledEvent;
	struct BSRemoteGamepadEvent;

	// menuDepth = 2
	// flags = kAlwaysOpen | kRequiresUpdate | kAllowSaving | kCustomRendering | kAssignCursorToRenderer
	// context = kNone
	class HUDMenu :
#if !defined(ENABLE_SKYRIM_AE) && !(ENABLE_SKYRIM_SE)
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
		inline static auto                RTTI = RTTI_HUDMenu;
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

		// override (BSTEventSink<UserEventEnabledEvent>)
		BSEventNotifyControl ProcessEvent(const UserEventEnabledEvent* a_event, BSTEventSource<UserEventEnabledEvent>* a_eventSource);  // 01

		// override (BSTEventSink<BSRemoteGamepadEvent>)
		BSEventNotifyControl ProcessEvent(const BSRemoteGamepadEvent* a_event, BSTEventSource<BSRemoteGamepadEvent>* a_eventSource);  // 01

		[[nodiscard]] inline RUNTIME_DATA& GetRuntimeData() noexcept
		{
			return REL::RelocateMember<RUNTIME_DATA>(this, 0x40, 0x70);
		}

		[[nodiscard]] inline const RUNTIME_DATA& GetRuntimeData() const noexcept
		{
			return REL::RelocateMember<RUNTIME_DATA>(this, 0x40, 0x70);
		}

		// members
#if !defined(ENABLE_SKYRIM_VR) || (!defined(ENABLE_SKYRIM_AE) && !defined(ENABLE_SKYRIM_SE))
#	if !defined(ENABLE_SKYRIM_AE) && !defined(ENABLE_SKYRIM_SE)
		std::uint64_t pad68;  // 68
#	endif
		RUNTIME_DATA_CONTENT  // 40, 70
#endif
	};
#ifndef ENABLE_SKYRIM_VR
	static_assert(sizeof(HUDMenu) == 0x98);
#elif !defined(ENABLE_SKYRIM_AE) && !defined(ENABLE_SKYRIM_SE)
	static_assert(sizeof(HUDMenu) == 0xC8);
#endif
}
#undef RUNTIME_DATA_CONTENT
