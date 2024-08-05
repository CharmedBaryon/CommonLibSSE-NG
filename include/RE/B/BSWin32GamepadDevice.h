#pragma once

#include "RE/B/BSPCGamepadDeviceDelegate.h"

#include "REX/W32/XINPUT.h"

namespace RE
{
	class BSWin32GamepadDevice : public BSPCGamepadDeviceDelegate
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSWin32GamepadDevice;
		inline static constexpr auto VTABLE = VTABLE_BSWin32GamepadDevice;

		struct Keys
		{
			enum Key : std::uint32_t
			{
				// button masks for wButtons
				kUp = REX::W32::XINPUT_GAMEPAD_DPAD_UP,                    // 0x0001
				kDown = REX::W32::XINPUT_GAMEPAD_DPAD_DOWN,                // 0x0002
				kLeft = REX::W32::XINPUT_GAMEPAD_DPAD_LEFT,                // 0x0004
				kRight = REX::W32::XINPUT_GAMEPAD_DPAD_RIGHT,              // 0x0008
				kStart = REX::W32::XINPUT_GAMEPAD_START,                   // 0x0010
				kBack = REX::W32::XINPUT_GAMEPAD_BACK,                     // 0x0020
				kLeftThumb = REX::W32::XINPUT_GAMEPAD_LEFT_THUMB,          // 0x0040
				kRightThumb = REX::W32::XINPUT_GAMEPAD_RIGHT_THUMB,        // 0x0080
				kLeftShoulder = REX::W32::XINPUT_GAMEPAD_LEFT_SHOULDER,    // 0x0100
				kRightShoulder = REX::W32::XINPUT_GAMEPAD_RIGHT_SHOULDER,  // 0x0200
				kA = REX::W32::XINPUT_GAMEPAD_A,                           // 0x1000
				kB = REX::W32::XINPUT_GAMEPAD_B,                           // 0x2000
				kX = REX::W32::XINPUT_GAMEPAD_X,                           // 0x4000
				kY = REX::W32::XINPUT_GAMEPAD_Y,                           // 0x8000

				// arbitrary values
				// IDs meant to be used with ButtonEvent
				kLeftTrigger = 0x0009,
				kRightTrigger = 0x000A,
				// IDs meant to be used with ThumbstickEvent
				kLeftStick = 0x000B,
				kRightStick = 0x000C
			};
		};
		using Key = Keys::Key;

		struct ButtonState
		{
			bool up: 1;             // 0x0001
			bool down: 1;           // 0x0002
			bool left: 1;           // 0x0004
			bool right: 1;          // 0x0008
			bool start: 1;          // 0x0010
			bool back: 1;           // 0x0020
			bool leftThumb: 1;      // 0x0040
			bool rightThumb: 1;     // 0x0080
			bool leftShoulder: 1;   // 0x0100
			bool rightShoulder: 3;  // 0x0200, skip over 2 bits (XInput documentation says the state of these two bits are undefined)
			bool a: 1;              // 0x1000
			bool b: 1;              // 0x2000
			bool x: 1;              // 0x4000
			bool y: 1;              // 0x8000
		};

		~BSWin32GamepadDevice() override;  // 00

		// override (BSPCGamepadDeviceDelegate)
		void Initialize() override;                           // 01
		void Process(float a_arg1) override;                  // 02
		void Release() override;                              // 03 - { return; }
		void Reset() override;                                // 08 - { std::memset(&unk0D8, 0, 0x50); }
		void SetRumble(float lValue, float rValue) override;  // 09 - { return; }

		// Returns the previous ButtonState of the gamepad
		ButtonState GetPreviousButtonState() const
		{
			return stl::unrestricted_cast<ButtonState>(previousState.gamepad.buttons & REX::W32::XINPUT_GAMEPAD_BUTTON_MASK);
		}

		// Returns the current ButtonState of the gamepad
		ButtonState GetCurrentButtonState() const
		{
			return stl::unrestricted_cast<ButtonState>(currentState.gamepad.buttons & REX::W32::XINPUT_GAMEPAD_BUTTON_MASK);
		}

		// members
		REX::W32::XINPUT_STATE previousState;  // 0D8
		float                  previousLT;     // 0E8
		float                  previousRT;     // 0EC
		float                  previousLX;     // 0F0
		float                  previousLY;     // 0F4
		float                  previousRX;     // 0F8
		float                  previousRY;     // 0FC
		REX::W32::XINPUT_STATE currentState;   // 100
		float                  currentLT;      // 110
		float                  currentRT;      // 114
		float                  currentLX;      // 118
		float                  currentLY;      // 11C
		float                  currentRX;      // 120
		float                  currentRY;      // 124

	protected:
		friend class BSGamepadDeviceHandler;
		BSWin32GamepadDevice();

	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(BSWin32GamepadDevice) == 0x128);
}
