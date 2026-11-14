#pragma once

#include "RE/B/BSFixedString.h"
#include "RE/B/BSIInputDevice.h"
#include "RE/B/BSTHashMap.h"
#include "RE/I/InputDevices.h"
#include "REL/Common.h"
#include "REL/RuntimeDataAccessors.h"

#include <array>
#include <unordered_map>
#include <vector>

namespace RE
{
	class BSInputDevice : public BSIInputDevice
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSInputDevice;
		inline static constexpr auto VTABLE = VTABLE_BSInputDevice;

		struct InputButton
		{
			BSFixedString name;          // 00
			float         heldDownSecs;  // 08
			std::uint32_t keycode;       // 0C
		};
		static_assert(sizeof(InputButton) == 0x10);

		// VR note: an extra 8-byte field exists at 0x08 in VR, shifting all members by +8.
		// SE: device@0x08, deviceButtons@0x10, buttonNameIDMap@0x40
		// VR: device@0x10, deviceButtons@0x18, buttonNameIDMap@0x48
		struct RUNTIME_DATA
		{
#define RUNTIME_DATA_CONTENT                                           \
	INPUT_DEVICE                             device;          /* 08 */ \
	std::uint32_t                            pad0C;           /* 0C */ \
	BSTHashMap<std::uint32_t, InputButton*>  deviceButtons;   /* 10 */ \
	BSTHashMap<BSFixedString, std::uint32_t> buttonNameIDMap; /* 40 */
			RUNTIME_DATA_CONTENT
		};
		static_assert(sizeof(RUNTIME_DATA) == 0x68);

		~BSInputDevice() override;  // 00

		// override (BSIInputDevice)
		bool               GetButtonNameFromID(std::int32_t a_id, BSFixedString& a_buttonName) override;  // 04
		std::uint32_t      GetMappingKey(BSFixedString a_mapping) override;                               // 05
		bool               GetKeyCodeFromID(std::int32_t a_id, std::uint32_t& a_keyCode) override;        // 06
		[[nodiscard]] bool IsEnabled() const override;                                                    // 07 - { return true; }

		[[nodiscard]] bool IsKeyboard() const;
		[[nodiscard]] bool IsMouse() const;
		[[nodiscard]] bool IsGamepad() const;
		[[nodiscard]] bool IsPressed(std::uint32_t a_keyCode) const;

		bool LoadControlsDefinitionFile(const char* a_fileName);                                                                    // loads the controls definition file from <FILENAME>.txt (usually located in 'interface\controls' folder)
		void ResetButtonMaps();                                                                                                     // resets the button maps
		void SetButtonState(std::uint32_t a_buttonId, float a_timeSinceLastPoll, bool a_buttonWasPressed, bool a_buttonIsPressed);  // sets the button state for a given key code and emits a button event if necessary

		RUNTIME_DATA_ACCESSOR(RUNTIME_DATA, 0x8, 0x10);
#ifndef SKYRIM_CROSS_VR
		// members
		RUNTIME_DATA_CONTENT
#endif
	};
	STATIC_ASSERT_SIZE(BSInputDevice, 0x70, 0x70, 0x78, 0x8);

	// Add enum for controller role
	enum class ControllerRole : uint8_t
	{
		Primary = 0,
		Secondary = 1,
		Count
	};

	struct ButtonState
	{
		bool   isPressed = false;
		double lastPressTime = 0.0;
		double lastReleaseTime = 0.0;
		double holdDuration = 0.0;

		// Call this on every press/release event
		void OnEvent(bool pressed, double eventTime)
		{
			if (pressed && !isPressed) {
				isPressed = true;
				lastPressTime = eventTime;
			} else if (!pressed && isPressed) {
				isPressed = false;
				lastReleaseTime = eventTime;
				holdDuration = lastReleaseTime - lastPressTime;
			}
		}

		// Returns true if the last release was a click (short press)
		bool IsClick(double threshold = 0.5) const { return !isPressed && holdDuration < threshold; }
		// Returns true if the last release was a hold (long press)
		bool IsHold(double threshold = 0.5) const { return !isPressed && holdDuration >= threshold; }
		// Returns the current held time (live if pressed, last duration if released)
		double GetCurrentHeldTime(double now) const { return isPressed ? (now - lastPressTime) : holdDuration; }
	};

	// Tracks the state of a thumbstick (axes)
	struct ThumbstickState
	{
		float x = 0.0f;
		float y = 0.0f;
		void  OnEvent(float newX, float newY)
		{
			x = newX;
			y = newY;
		}
	};

	// Tracks the state of a trigger (analog value)
	struct TriggerState
	{
		float value = 0.0f;
		void  OnEvent(float newValue) { value = newValue; }
	};

	// Unified input device state - optimized for all common input devices
	struct InputDeviceState
	{
		// Large array covers all common input devices optimally:
		// - VR controllers (button IDs 1-36)
		// - Gamepads (button IDs 0-15)
		// - Keyboards (DIK scan codes 1-237)
		// - Mice (button IDs 0-7)
		static constexpr size_t BUTTON_ARRAY_SIZE = 256;

		INPUT_DEVICE deviceType = INPUT_DEVICE::kNone;

		// Fast O(1) array access for all common input devices
		std::array<ButtonState, BUTTON_ARRAY_SIZE> buttons{};

		// Simple, fast button access with bounds safety
		ButtonState& operator[](uint32_t buttonId)
		{
			return buttons[buttonId < BUTTON_ARRAY_SIZE ? buttonId : 0];
		}

		const ButtonState& operator[](uint32_t buttonId) const
		{
			return buttons[buttonId < BUTTON_ARRAY_SIZE ? buttonId : 0];
		}

		// Device-specific analog inputs (VR/gamepad)
		std::array<ThumbstickState, static_cast<size_t>(ControllerRole::Count)> thumbsticks;
		std::array<TriggerState, static_cast<size_t>(ControllerRole::Count)>    triggers;

		// Returns all active (pressed or previously pressed) buttons
		std::vector<std::pair<uint32_t, const ButtonState*>> GetActiveButtons() const
		{
			std::vector<std::pair<uint32_t, const ButtonState*>> result;
			for (size_t i = 0; i < BUTTON_ARRAY_SIZE; ++i) {
				const auto& state = buttons[i];
				if (state.isPressed || state.lastPressTime > 0.0) {
					result.emplace_back(static_cast<uint32_t>(i), &state);
				}
			}
			return result;
		}

		// Utility methods
		void Clear()
		{
			buttons.fill(ButtonState{});
			thumbsticks.fill(ThumbstickState{});
			triggers.fill(TriggerState{});
		}

		// Statistics for debugging/optimization
		size_t GetActiveButtonCount() const
		{
			size_t count = 0;
			for (const auto& button : buttons) {
				if (button.isPressed || button.lastPressTime > 0.0)
					count++;
			}
			return count;
		}

		// Supplementary info (for mod authors or device-specific extensions)
		std::unordered_map<std::string, double> customData;
	};

	// Type aliases for clarity and future flexibility
	using VRControllerState = InputDeviceState;  // VR controllers use unified state
	using GamepadState = InputDeviceState;       // Gamepads use unified state
	using KeyboardState = InputDeviceState;      // Keyboards use unified state
	using MouseState = InputDeviceState;         // Mice use unified state

	// Returns a string label for the thumbstick direction/quadrant
	inline const char* GetQuadrantName(float x, float y)
	{
		if (x > 0 && y > 0)
			return "Top-Right";
		if (x < 0 && y > 0)
			return "Top-Left";
		if (x < 0 && y < 0)
			return "Bottom-Left";
		if (x > 0 && y < 0)
			return "Bottom-Right";
		if (x == 0 && y == 0)
			return "Center";
		if (y == 0)
			return x > 0 ? "Right" : "Left";
		if (x == 0)
			return y > 0 ? "Top" : "Bottom";
		return "";
	}

	// Generic button mapping struct for mapping device key codes to logical actions
	struct ButtonMapping
	{
		uint32_t keyCode;        // Device-specific key code
		int      logicalButton;  // Logical action (e.g., ImGui button/key, or your own enum)
		bool     isKeyEvent;     // True if this is a key event, false if mouse/button
		int      key;            // Logical key (if applicable)
		bool     isShift;        // True if shift modifier is required
	};
}
#undef RUNTIME_DATA_CONTENT
