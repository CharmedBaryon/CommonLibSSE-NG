#pragma once

#ifdef ENABLE_SKYRIM_VR

#	include "RE/B/BSTrackedControllerDevice.h"
#	include "RE/N/NiPoint2.h"

namespace RE
{
	class BSOpenVRControllerDevice : public BSTrackedControllerDevice
	{
	public:
#	if defined(EXCLUSIVE_SKYRIM_VR)
		inline static constexpr auto RTTI = RTTI_BSOpenVRControllerDevice;
#	endif

		~BSOpenVRControllerDevice() override;

		struct Keys
		{
			enum Key : std::uint32_t  // Only tested with Oculus, keys are same for both controllers (L/R) are devices (6/5) respectively
			{
				kBY = 1,                // Y (left) / B (right) button
				kGrip = 2,              // Grip button (official OpenVR, but see kGripAlt)
				kXA = 7,                // X (left) / A (right) button
										// kJoystick = 11, // Joystick moving event
				kJoystickTrigger = 32,  // Joystick press (stick click)
				kTrigger = 33,          // Trigger button
				kGripAlt = 34,          // Grip button (Axis2, used by Oculus/Quest via OpenVR)
				kTouchpadClick = 35,    // Touchpad click (Vive/Index)
				kTouchpadAlt = 36,      // Touchpad alt (rare)
			};
		};
		using Key = Keys::Key;

		// override BSIInputDevice
		void               Initialize() override;                                                         // 01
		void               Poll(float a_timeDelta) override;                                              // 02
		void               Shutdown() override;                                                           // 03 - { return; }
		bool               GetButtonNameFromID(std::int32_t a_id, BSFixedString& a_buttonName) override;  // 04
		std::uint32_t      GetMappingKey(BSFixedString a_mapping) override;                               // 05
		bool               GetKeyCodeFromID(std::int32_t a_id, std::uint32_t& a_keyCode) override;        // 06
		[[nodiscard]] bool IsEnabled() const override;                                                    // 07 - { return true; }
		void               ClearInputState() override;                                                    // 08

		// Helper functions for VR button detection
		static inline bool IsGripButton(std::uint32_t keyCode)
		{
			// kGrip = 2 (official), kGripAlt = 34 (Axis2, Oculus/Quest)
			return keyCode == Keys::kGrip || keyCode == Keys::kGripAlt;
		}
		static inline bool IsTriggerButton(std::uint32_t keyCode)
		{
			return keyCode == Keys::kTrigger;
		}
		static inline bool IsStickClick(std::uint32_t keyCode)
		{
			return keyCode == Keys::kJoystickTrigger;
		}
		static inline bool IsAButton(std::uint32_t keyCode)
		{
			// Right A, left X (same code)
			return keyCode == Keys::kXA;
		}
		static inline bool IsBButton(std::uint32_t keyCode)
		{
			// Right B, left Y (same code)
			return keyCode == Keys::kBY;
		}
		static inline bool IsXButton(std::uint32_t keyCode)
		{
			// Left X, right A (same code)
			return keyCode == Keys::kXA;
		}
		static inline bool IsYButton(std::uint32_t keyCode)
		{
			// Left Y, right B (same code)
			return keyCode == Keys::kBY;
		}
		static inline bool IsTouchpadClick(std::uint32_t keyCode)
		{
			return keyCode == Keys::kTouchpadClick || keyCode == Keys::kTouchpadAlt;
		}

		// Returns true if Skyrim VR is in left-handed mode (swaps primary/secondary controllers)
		static inline bool IsLeftHandedMode()
		{
			static REL::Relocation<bool*> leftHandedMode{ REL::Offset(0x1e71778) };
			// Add null check for safety - defaults to false (right-handed) if pointer is invalid
			return leftHandedMode.get() != nullptr ? *leftHandedMode : false;
		}

		// New helpers for primary/secondary abstraction
		static inline bool IsPrimaryController(INPUT_DEVICE device)
		{
			// By convention, primary is VivePrimary, OculusPrimary, WMRPrimary
			bool isPhysPrimary = device == INPUT_DEVICE::kVivePrimary ||
			                     device == INPUT_DEVICE::kOculusPrimary ||
			                     device == INPUT_DEVICE::kWMRPrimary;
			return IsLeftHandedMode() ? !isPhysPrimary : isPhysPrimary;
		}
		static inline bool IsSecondaryController(INPUT_DEVICE device)
		{
			// By convention, secondary is ViveSecondary, OculusSecondary, WMRSecondary
			bool isPhysSecondary = device == INPUT_DEVICE::kViveSecondary ||
			                       device == INPUT_DEVICE::kOculusSecondary ||
			                       device == INPUT_DEVICE::kWMRSecondary;
			return IsLeftHandedMode() ? !isPhysSecondary : isPhysSecondary;
		}

		// Thumbstick / trackpad (rAxis[0]) from the last IVRSystem poll, x/y in [-1, 1]. Reads the
		// typed currentState via GetRuntimeData() so it resolves correctly in every build: the
		// accessor relocates to the verified VR offset (0xC0) regardless of the C++ base-class size,
		// which shrinks in SKYRIM_CROSS_VR builds.
		[[nodiscard]] NiPoint2 GetThumbstick() const noexcept
		{
			const auto& axis = GetRuntimeData().currentState.rAxis[0];
			return { axis.x, axis.y };
		}

		// Device state block, maintained by Poll() via IVRSystem (see BSOpenVRControllerDevice::Poll
		// RE). Begins at 0x88 (right after BSTrackedControllerDevice in VR); reached via the runtime
		// accessor so cross-runtime builds, where the base classes drop their VR-only members from the
		// C++ layout, still land on the engine's real offsets.
		struct RUNTIME_DATA
		{
#	define RUNTIME_DATA_CONTENT                             \
		std::uint64_t           prevButtonPressed; /* 088 */ \
		std::uint64_t           prevButtonTouched; /* 090 */ \
		vr::VRControllerAxis_t  prevAxis[5];       /* 098 */ \
		vr::VRControllerState_t currentState;      /* 0C0 */ \
		std::uint64_t           unk100[7];         /* 100 */ \
		std::uint32_t           swipe[8];          /* 138 */
            RUNTIME_DATA_CONTENT
		};
		static_assert(sizeof(RUNTIME_DATA) == 0xD0);

		RUNTIME_DATA_ACCESSOR(RUNTIME_DATA, 0x88, 0x88);
#	ifndef SKYRIM_CROSS_VR
		// members
		RUNTIME_DATA_CONTENT
#	endif
	};
	STATIC_ASSERT_SIZE(BSOpenVRControllerDevice, SIZE_UNDEFINED, SIZE_UNDEFINED, 0x158, SIZE_UNDEFINED, SIZE_UNDEFINED);
#	undef RUNTIME_DATA_CONTENT

	// Returns a canonical string name for a given OpenVR controller key code
	inline const char* GetOpenVRButtonName(std::uint32_t keyCode)
	{
		using Keys = BSOpenVRControllerDevice::Keys;
		switch (keyCode) {
		case Keys::kTrigger:
			return "Trigger";
		case Keys::kGrip:
			return "Grip";
		case Keys::kGripAlt:
			return "Grip Alt";
		case Keys::kJoystickTrigger:
			return "Joystick Click";
		case Keys::kTouchpadClick:
			return "Touchpad Click";
		case Keys::kTouchpadAlt:
			return "Touchpad Alt";
		case Keys::kXA:
			return "A/X";
		case Keys::kBY:
			return "B/Y";
		// Add any other explicit codes here if needed
		default:
			break;
		}
		// Fallback to helper functions for extensibility
		if (BSOpenVRControllerDevice::IsTriggerButton(keyCode))
			return "Trigger";
		if (BSOpenVRControllerDevice::IsGripButton(keyCode))
			return "Grip";
		if (BSOpenVRControllerDevice::IsStickClick(keyCode))
			return "Joystick Click";
		if (BSOpenVRControllerDevice::IsTouchpadClick(keyCode))
			return "Touchpad Click";
		if (BSOpenVRControllerDevice::IsAButton(keyCode))
			return "A";
		if (BSOpenVRControllerDevice::IsBButton(keyCode))
			return "B";
		if (BSOpenVRControllerDevice::IsXButton(keyCode))
			return "X";
		if (BSOpenVRControllerDevice::IsYButton(keyCode))
			return "Y";
		return "?";
	}
}
#endif
