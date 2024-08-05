#pragma once

#include "RE/B/BSPCGamepadDeviceDelegate.h"

#include "REX/PS4/SCEPAD.h"

namespace RE
{
	// PS4 controller used via HID polling
	class BSPCOrbisGamepadDevice : public BSPCGamepadDeviceDelegate
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSPCOrbisGamepadDevice;
		inline static constexpr auto VTABLE = VTABLE_BSPCOrbisGamepadDevice;

		struct Keys
		{
			enum Key : std::uint32_t
			{
				// Masks for buttonState
				// Key hardware value
				kUp = REX::PS4::SCE_PAD_BUTTON::SCE_PAD_BUTTON_UP,
				kDown = REX::PS4::SCE_PAD_BUTTON::SCE_PAD_BUTTON_DOWN,
				kLeft = REX::PS4::SCE_PAD_BUTTON::SCE_PAD_BUTTON_LEFT,
				kRight = REX::PS4::SCE_PAD_BUTTON::SCE_PAD_BUTTON_RIGHT,
				kPS3_Start = REX::PS4::SCE_PAD_BUTTON::SCE_PAD_BUTTON_OPTIONS,
				kPS3_Back = REX::PS4::SCE_PAD_BUTTON::SCE_PAD_BUTTON_TOUCH_PAD,  // This is mapped to the touchpad on the PS4 controller
				kPS3_L3 = REX::PS4::SCE_PAD_BUTTON::SCE_PAD_BUTTON_L3,
				kPS3_R3 = REX::PS4::SCE_PAD_BUTTON::SCE_PAD_BUTTON_R3,
				kPS3_LB = REX::PS4::SCE_PAD_BUTTON::SCE_PAD_BUTTON_L1,
				kPS3_RB = REX::PS4::SCE_PAD_BUTTON::SCE_PAD_BUTTON_R1,
				kPS3_A = REX::PS4::SCE_PAD_BUTTON::SCE_PAD_BUTTON_CROSS,
				kPS3_B = REX::PS4::SCE_PAD_BUTTON::SCE_PAD_BUTTON_CIRCLE,
				kPS3_X = REX::PS4::SCE_PAD_BUTTON::SCE_PAD_BUTTON_SQUARE,
				kPS3_Y = REX::PS4::SCE_PAD_BUTTON::SCE_PAD_BUTTON_TRIANGLE,

				// Unused by Skyrim
				kPS4_Share = REX::PS4::SCE_PAD_BUTTON::SCE_PAD_BUTTON_SHARE,        // Skyrim uses the touchpad for Back and leaves the Share button unused
				kPS4_L2 = REX::PS4::SCE_PAD_BUTTON::SCE_PAD_BUTTON_L2,              // Skyrim uses trigger axis read instead of button press
				kPS4_R2 = REX::PS4::SCE_PAD_BUTTON::SCE_PAD_BUTTON_R2,              // Skyrim uses trigger axis read instead of button press
				kPS4_PSBtn = REX::PS4::SCE_PAD_BUTTON::SCE_PAD_BUTTON_PLAYSTATION,  // Playstation button

				// arbitrary values
				// IDs meant to be used with ButtonEvent
				kPS3_LT = 0x0009,
				kPS3_RT = 0x000a,
				// IDs meant to be used with ThumbstickEvent
				kPS3_LS = 0x000b,
				kPS3_RS = 0x000c,
			};
		};
		using Key = Keys::Key;

		struct ButtonState
		{
			bool Share: 1;            // 0x0001 -- unused by Skyrim
			bool L3: 1;               // 0x0002
			bool R3: 1;               // 0x0004
			bool Start: 1;            // 0x0008
			bool Up: 1;               // 0x0010
			bool Right: 1;            // 0x0020
			bool Down: 1;             // 0x0040
			bool Left: 1;             // 0x0080
			bool L2btn: 1;            // 0x0100 -- unused by Skyrim, which uses axis data
			bool R2btn: 1;            // 0x0200 -- unused by Skyrim, which uses axis data
			bool LB: 1;               // 0x0400
			bool RB: 1;               // 0x0800
			bool Triangle_Y: 1;       // 0x1000
			bool Circle_B: 1;         // 0x2000
			bool Cross_A: 1;          // 0x4000
			bool Square_X: 1;         // 0x8000
			bool PSbtn: 1;            // 0x00010000 -- unused by Skyrim
			bool _unused20000: 1;     // 0x00020000
			bool _unused40000: 1;     // 0x00040000
			bool _unused80000: 1;     // 0x00080000
			bool Touchpad: 1;         // 0x00100000
			bool _unused200000: 1;    // 0x00200000
			bool _unused400000: 1;    // 0x00400000
			bool _unused800000: 1;    // 0x00800000
			bool _unused1000000: 1;   // 0x01000000
			bool _unused2000000: 1;   // 0x02000000
			bool _unused4000000: 1;   // 0x04000000
			bool _unused8000000: 1;   // 0x08000000
			bool _unused10000000: 1;  // 0x10000000
			bool _unused20000000: 1;  // 0x20000000
			bool _unused40000000: 1;  // 0x40000000
			bool _Intercepted: 1;     // 0x80000000
		};
		static_assert(sizeof(ButtonState) == 0x4);

		struct Vector3
		{
			float x;  // 00
			float y;  // 04
			float z;  // 08
		};
		static_assert(sizeof(Vector3) == 0x0C);

		struct Vector4
		{
			float x;  // 00
			float y;  // 04
			float z;  // 08
			float w;  // 0C
		};
		static_assert(sizeof(Vector4) == 0x10);

		struct PadTouch
		{
			std::uint16_t x;         // 00
			std::uint16_t y;         // 02
			std::uint8_t  touch_id;  // 04
			std::uint8_t  pad05[3];  // 05
		};
		static_assert(sizeof(PadTouch) == 0x08);

		struct TouchPadData
		{
			std::uint8_t  touchNum;  // 00 - Number of touch reports
			std::uint8_t  pad01[3];  // 01
			std::uint32_t pad04;     // 04
			PadTouch      touch[2];  // 08 - Touch Data for max number of touch points = 2
		};
		static_assert(sizeof(TouchPadData) == 0x18);

		struct UnusedExtensionData
		{
			std::uint32_t extUnitId;   // 00
			std::uint8_t  pad04;       // 04
			std::uint8_t  dataLength;  // 05
			std::uint8_t  data[10];    // 06
		};
		static_assert(sizeof(UnusedExtensionData) == 0x10);

		struct GamepadData
		{
			std::uint32_t       buttonState;      // 00
			std::byte           rawLeftStickX;    // 04
			std::byte           rawLeftStickY;    // 05
			std::byte           rawRightStickX;   // 06
			std::byte           rawRightStickY;   // 07
			std::byte           rawLeftTrigger;   // 08
			std::byte           rawRightTrigger;  // 09
			std::byte           pad0A[2];         // 0A
			Vector4             orientation;      // 0C
			Vector3             acceleration;     // 1C
			Vector3             angularVelocity;  // 28
			TouchPadData        touchPadData;     // 34
			bool                padConnected;     // 4C
			std::byte           pad4D[3];         // 4D
			std::uint64_t       timestamp;        // 50
			UnusedExtensionData unusedExtData;    // 58 -- unused
			std::uint8_t        connectedCount;   // 68 -- Controller handle connected count
			std::uint8_t        pad69[2];         // 69
			std::uint8_t        specialDataLen;   // 6B
			std::uint8_t        specialData[12];  // 6C -- Device data for special controllers
		};
		static_assert(sizeof(GamepadData) == 0x78);

		~BSPCOrbisGamepadDevice() override;  // 00

		// override (BSPCGamepadDeviceDelegate)
		void Initialize() override;                                                                            // 01
		void Process(float a_arg1) override;                                                                   // 02
		void Release() override;                                                                               // 03
		void Reset() override;                                                                                 // 08 - { memset(this+0xD8, 0, 0x120); }
		void SetRumble(float lValue, float rValue) override;                                                   // 09
		void SetLEDColor(ColorParam* colorParam) override;                                                     // 0A
		void ResetLEDColor() override;                                                                         // 0B
		void NormalizeThumbstickValue(int32_t a_rawX, int32_t a_rawY, float& a_outX, float& a_outY) override;  // 0D
		void DoEnableListeningMode(void) override;                                                             // 0E - { return; }

		ButtonState GetPreviousButtonState() const
		{
			return stl::unrestricted_cast<ButtonState>(previousPadState.buttonState);
		}
		ButtonState GetCurrentButtonState() const
		{
			return stl::unrestricted_cast<ButtonState>(currentPadState.buttonState);
		}

		// members
		GamepadData previousPadState;  // 0D8
		float       previousLT;        // 150
		float       previousRT;        // 154
		float       previousLX;        // 158
		float       previousLY;        // 15C
		float       previousRX;        // 160
		float       previousRY;        // 164
		GamepadData currentPadState;   // 168
		float       currentLT;         // 1E0
		float       currentRT;         // 1E4
		float       currentLX;         // 1E8
		float       currentLY;         // 1EC
		float       currentRX;         // 1F0
		float       currentRY;         // 1F4

	protected:
		friend class BSGamepadDeviceHandler;
		BSPCOrbisGamepadDevice();

	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(BSPCOrbisGamepadDevice) == 0x1F8);
}
