#pragma once

#include "RE/B/BSFixedString.h"
#include "RE/B/BSInputDevice.h"
#include "RE/B/BSTArray.h"
#include "RE/B/BSTEvent.h"
#include "RE/B/BSTSingleton.h"
#include "RE/I/InputDevices.h"
#include "RE/P/PCGamepadType.h"
#include "RE/U/UserEvents.h"
#include <SKSE/Version.h>

namespace RE
{
	class UserEventEnabled;

	class ControlMap :
		public BSTSingletonSDM<ControlMap>,      // 00
		public BSTEventSource<UserEventEnabled>  // 08
	{
	public:
		using InputContextID = UserEvents::INPUT_CONTEXT_ID;
		using UEFlag = UserEvents::USER_EVENT_FLAG;

		enum : std::uint32_t
		{
			kInvalid = static_cast<std::uint8_t>(-1)
		};

		struct UserEventMapping
		{
		public:
			// members
			BSFixedString                           eventID;             // 00
			std::uint16_t                           inputKey;            // 08
			std::uint16_t                           modifier;            // 08
			std::int8_t                             indexInContext;      // 0C
			bool                                    remappable;          // 0D
			bool                                    linked;              // 0E
			stl::enumeration<UEFlag, std::uint32_t> userEventGroupFlag;  // 10
			std::uint32_t                           pad14;               // 14
		};
		static_assert(sizeof(UserEventMapping) == 0x18);

		struct InputContext
		{
		public:
			[[nodiscard]] static SKYRIM_REL_VR std::size_t GetNumDeviceMappings() noexcept
			{
#ifndef SKYRIM_CROSS_VR
				return INPUT_DEVICES::kTotal;
#else
				if SKYRIM_REL_VR_CONSTEXPR (REL::Module::IsVR()) {
					return INPUT_DEVICES::kTotal;
				} else {
					return INPUT_DEVICES::kFlatTotal;
				}
#endif
			}

			// members
			BSTArray<UserEventMapping> deviceMappings[INPUT_DEVICES::kTotal];  // 00
		};
#ifdef ENABLE_SKYRIM_VR
		static_assert(sizeof(InputContext) == 0xF0);
#else
		static_assert(sizeof(InputContext) == 0x60);
#endif

		struct LinkedMapping
		{
		public:
			// members
			BSFixedString  linkedMappingName;     // 00
			InputContextID linkedMappingContext;  // 08
			INPUT_DEVICE   device;                // 0C
			InputContextID linkFromContext;       // 10
			std::uint32_t  pad14;                 // 14
			BSFixedString  linkFromName;          // 18
		};
		static_assert(sizeof(LinkedMapping) == 0x20);

		static ControlMap* GetSingleton();

		std::int8_t               AllowTextInput(bool a_allow);
		constexpr bool            AreControlsEnabled(UEFlag a_flags) const noexcept { return GetRuntimeData().enabledControls.all(a_flags); }
		bool                      GetButtonNameFromUserEvent(const BSFixedString& a_eventID, INPUT_DEVICE a_device, BSFixedString& a_buttonName);
		std::uint32_t             GetMappedKey(std::string_view a_eventID, INPUT_DEVICE a_device, InputContextID a_context = InputContextID::kGameplay) const;
		bool                      GetMappingFromEventName(const BSFixedString& a_eventID, UserEvents::INPUT_CONTEXT_ID a_context, INPUT_DEVICE a_device, UserEventMapping& a_mapping);
		std::string_view          GetUserEventName(std::uint32_t a_buttonID, INPUT_DEVICE a_device, InputContextID a_context = InputContextID::kGameplay) const;
		constexpr PC_GAMEPAD_TYPE GetGamePadType() const noexcept { return GetRuntimeData().gamePadMapType.get(); }
		constexpr bool            IsActivateControlsEnabled() const noexcept { return GetRuntimeData().enabledControls.all(UEFlag::kActivate); }
		constexpr bool            IsConsoleControlsEnabled() const noexcept { return GetRuntimeData().enabledControls.all(UEFlag::kConsole); }
		constexpr bool            IsFightingControlsEnabled() const noexcept { return GetRuntimeData().enabledControls.all(UEFlag::kFighting); }
		constexpr bool            IsLookingControlsEnabled() const noexcept { return GetRuntimeData().enabledControls.all(UEFlag::kLooking); }
		constexpr bool            IsMenuControlsEnabled() const noexcept { return GetRuntimeData().enabledControls.all(UEFlag::kMenu); }
		constexpr bool            IsMainFourControlsEnabled() const noexcept { return GetRuntimeData().enabledControls.all(UEFlag::kMainFour); }
		constexpr bool            IsMovementControlsEnabled() const noexcept { return GetRuntimeData().enabledControls.all(UEFlag::kMovement); }
		constexpr bool            IsPOVSwitchControlsEnabled() const noexcept { return GetRuntimeData().enabledControls.all(UEFlag::kPOVSwitch); }
		constexpr bool            IsSneakingControlsEnabled() const noexcept { return GetRuntimeData().enabledControls.all(UEFlag::kSneaking); }
		constexpr bool            IsVATSControlsEnabled() const noexcept { return GetRuntimeData().enabledControls.all(UEFlag::kVATS); }
		constexpr bool            IsWheelZoomControlsEnabled() const noexcept { return GetRuntimeData().enabledControls.all(UEFlag::kWheelZoom); }
		void                      PopInputContext(InputContextID a_context);
		void                      PushInputContext(InputContextID a_context);
		void                      ToggleControls(UEFlag a_flags, bool a_enable);

		struct RUNTIME_DATA
		{
#define RUNTIME_DATA_CONTENT                                                                        \
	BSTArray<LinkedMapping>                          linkedMappings;               /* 0E8, VR 108*/ \
	BSTArray<InputContextID>                         contextPriorityStack;         /* 100, VR 120*/ \
	stl::enumeration<UEFlag, std::uint32_t>          enabledControls;              /* 118, VR 138*/ \
	stl::enumeration<UEFlag, std::uint32_t>          unk11C;                       /* 11C, VR 13C*/ \
	std::int8_t                                      textEntryCount;               /* 120, VR 140*/ \
	bool                                             ignoreKeyboardMouse;          /* 121, VR 141*/ \
	bool                                             ignoreActivateDisabledEvents; /* 122, VR 142*/ \
	std::uint8_t                                     pad123;                       /* 123, VR 143*/ \
	stl::enumeration<PC_GAMEPAD_TYPE, std::uint32_t> gamePadMapType;               /* 124, VR 144*/
			RUNTIME_DATA_CONTENT
		};
		static_assert(sizeof(RUNTIME_DATA) == 0x40);

		//members

		// members
		InputContext* controlMap[InputContextID::kTotal];  // 060
#if defined(EXCLUSIVE_SKYRIM_FLAT)                         // FLAT
#	if defined(EXCLUSIVE_SKYRIM_SE)                       // SSE
		RUNTIME_DATA_CONTENT;                              // 0E8
#	else                                                  // AE
		RUNTIME_DATA_CONTENT;  // 0F8
#	endif
#elif defined(EXCLUSIVE_SKYRIM_VR)  // VR
		RUNTIME_DATA_CONTENT;  // 108
#else                               // ALL
		// controlMap can be accessed up to kTotal, kAETotal, or kVRTotal based on runtime
#endif

		[[nodiscard]] inline RUNTIME_DATA& GetRuntimeData() noexcept
		{
			if SKYRIM_REL_CONSTEXPR (REL::Module::IsAE()) {
				if (REL::Module::get().version().compare(SKSE::RUNTIME_SSE_1_6_1130) != std::strong_ordering::less) {
					return REL::RelocateMember<RUNTIME_DATA>(this, 0xf0);
				}
			}
			return REL::RelocateMember<RUNTIME_DATA>(this, 0xE8, 0x108);
		}

		[[nodiscard]] inline const RUNTIME_DATA& GetRuntimeData() const noexcept
		{
			if SKYRIM_REL_CONSTEXPR (REL::Module::IsAE()) {
				if (REL::Module::get().version().compare(SKSE::RUNTIME_SSE_1_6_1130) != std::strong_ordering::less) {
					return REL::RelocateMember<RUNTIME_DATA>(this, 0xf0);
				}
			}
			return REL::RelocateMember<RUNTIME_DATA>(this, 0xE8, 0x108);
		}
	};
#if defined(EXCLUSIVE_SKYRIM_FLAT)
#	if defined(EXCLUSIVE_SKYRIM_SE)
	static_assert(sizeof(ControlMap) == 0x128);
#	else
	static_assert(sizeof(ControlMap) == 0x130);
#	endif
#elif defined(EXCLUSIVE_SKYRIM_VR)
	static_assert(sizeof(ControlMap) == 0x128);
#else
	static_assert(sizeof(ControlMap) == 0xE8);
#endif
}
#undef RUNTIME_DATA_CONTENT
