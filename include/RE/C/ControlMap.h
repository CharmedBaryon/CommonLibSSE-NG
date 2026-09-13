#pragma once

#include "RE/B/BSFixedString.h"
#include "RE/B/BSInputDevice.h"
#include "RE/B/BSTArray.h"
#include "RE/B/BSTEvent.h"
#include "RE/B/BSTSingleton.h"
#include "RE/I/InputDevices.h"
#include "RE/P/PCGamepadType.h"
#include "RE/U/UserEvents.h"
#include "REL/RuntimeDataAccessors.h"
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
			BSFixedString                       eventID;             // 00
			std::uint16_t                       inputKey;            // 08
			std::uint16_t                       modifier;            // 08
			std::int8_t                         indexInContext;      // 0C
			bool                                remappable;          // 0D
			bool                                linked;              // 0E
			REX::EnumSet<UEFlag, std::uint32_t> userEventGroupFlag;  // 10
			std::uint32_t                       pad14;               // 14
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

		void                      AllowTextInput(bool a_allow);
		constexpr bool            AreControlsEnabled(UEFlag a_flags) const noexcept { return GetRuntimeData().enabledControls.all(a_flags); }
		bool                      GetButtonNameFromUserEvent(const BSFixedString& a_eventID, INPUT_DEVICE a_device, BSFixedString& a_buttonName);
		std::uint32_t             GetMappedKey(std::string_view a_eventID, INPUT_DEVICE a_device, InputContextID a_context = InputContextID::kGameplay) const;
		bool                      GetMappingFromEventName(const BSFixedString& a_eventID, UserEvents::INPUT_CONTEXT_ID a_context, INPUT_DEVICE a_device, UserEventMapping& a_mapping);
		std::string_view          GetUserEventName(std::uint32_t a_buttonID, INPUT_DEVICE a_device, InputContextID a_context = InputContextID::kGameplay) const;
		constexpr PC_GAMEPAD_TYPE GetGamePadType() const noexcept { return GetRuntimeData().gamePadMapType.get(); }
		void                      SetGamePadType(PC_GAMEPAD_TYPE a_gamePadType);
		constexpr bool            IsActivateControlsEnabled() const noexcept { return GetRuntimeData().enabledControls.all(UEFlag::kActivate); }
		constexpr bool            IsConsoleControlsEnabled() const noexcept { return GetRuntimeData().enabledControls.all(UEFlag::kConsole); }
		constexpr bool            IsFightingControlsEnabled() const noexcept { return GetRuntimeData().enabledControls.all(UEFlag::kFighting); }
		constexpr bool            IsJumpingControlsEnabled() const noexcept { return GetRuntimeData().enabledControls.all(UEFlag::kJumping); }
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
		void                      StoreControls();
		void                      LoadStoredControls();
		void                      ToggleControls(UEFlag a_flags, bool a_enable, bool a_storeState);
		void                      GetControlsState(std::uint32_t& a_enabledControls, std::uint32_t& a_storedControls) const;
		void                      SetControlsState(std::uint32_t a_enabledControls, std::uint32_t a_storedControls);
		void                      ResetControls();

		struct RUNTIME_DATA
		{
#define RUNTIME_DATA_CONTENT                                                                    \
	BSTArray<LinkedMapping>                      linkedMappings;               /* 0E8, VR 108*/ \
	BSTArray<InputContextID>                     contextPriorityStack;         /* 100, VR 120*/ \
	REX::EnumSet<UEFlag, std::uint32_t>          enabledControls;              /* 118, VR 138*/ \
	REX::EnumSet<UEFlag, std::uint32_t>          storedControls;               /* 11C, VR 13C*/ \
	std::int8_t                                  textEntryCount;               /* 120, VR 140*/ \
	bool                                         ignoreKeyboardMouse;          /* 121, VR 141*/ \
	bool                                         ignoreActivateDisabledEvents; /* 122, VR 142*/ \
	std::uint8_t                                 pad123;                       /* 123, VR 143*/ \
	REX::EnumSet<PC_GAMEPAD_TYPE, std::uint32_t> gamePadMapType;               /* 124, VR 144*/
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
		RUNTIME_DATA_CONTENT;  // 0F0
#	endif
#elif defined(EXCLUSIVE_SKYRIM_VR)  // VR
		RUNTIME_DATA_CONTENT;  // 108
#else                               // ALL
		// controlMap can be accessed up to kTotal, kAETotal, or kVRTotal based on runtime
#endif

		RUNTIME_MEMBER_ACCESSOR_VERSIONED(RUNTIME_DATA, GetRuntimeData, SKSE::RUNTIME_SSE_1_6_1130, 0xE8, 0x108, 0xF0);
	};
	STATIC_ASSERT_SIZE(ControlMap, 0x128, 0x130, 0x128, 0xE8);
}
#undef RUNTIME_DATA_CONTENT
