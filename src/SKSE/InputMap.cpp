#include "SKSE/InputMap.h"

#include "RE/C/ControlMap.h"

#include "REX/PS4/SCEPAD.h"
#include "REX/W32/DINPUT.h"
#include "REX/W32/USER32.h"
#include "REX/W32/XINPUT.h"

namespace SKSE
{
	std::uint32_t InputMap::XInputToScePadOffset(std::uint32_t keyMask)
	{
		switch (keyMask) {
		case REX::W32::XINPUT_GAMEPAD_DPAD_UP:
			return REX::PS4::SCE_PAD_BUTTON_UP;
		case REX::W32::XINPUT_GAMEPAD_DPAD_DOWN:
			return REX::PS4::SCE_PAD_BUTTON_DOWN;
		case REX::W32::XINPUT_GAMEPAD_DPAD_LEFT:
			return REX::PS4::SCE_PAD_BUTTON_LEFT;
		case REX::W32::XINPUT_GAMEPAD_DPAD_RIGHT:
			return REX::PS4::SCE_PAD_BUTTON_RIGHT;
		case REX::W32::XINPUT_GAMEPAD_START:
			return REX::PS4::SCE_PAD_BUTTON_OPTIONS;
		case REX::W32::XINPUT_GAMEPAD_BACK:
			return REX::PS4::SCE_PAD_BUTTON_TOUCH_PAD;
		case REX::W32::XINPUT_GAMEPAD_LEFT_THUMB:
			return REX::PS4::SCE_PAD_BUTTON_L3;
		case REX::W32::XINPUT_GAMEPAD_RIGHT_THUMB:
			return REX::PS4::SCE_PAD_BUTTON_R3;
		case REX::W32::XINPUT_GAMEPAD_LEFT_SHOULDER:
			return REX::PS4::SCE_PAD_BUTTON_L1;
		case REX::W32::XINPUT_GAMEPAD_RIGHT_SHOULDER:
			return REX::PS4::SCE_PAD_BUTTON_R1;
		case REX::W32::XINPUT_GAMEPAD_A:
			return REX::PS4::SCE_PAD_BUTTON_CROSS;
		case REX::W32::XINPUT_GAMEPAD_B:
			return REX::PS4::SCE_PAD_BUTTON_CIRCLE;
		case REX::W32::XINPUT_GAMEPAD_X:
			return REX::PS4::SCE_PAD_BUTTON_SQUARE;
		case REX::W32::XINPUT_GAMEPAD_Y:
			return REX::PS4::SCE_PAD_BUTTON_TRIANGLE;
		default:
			return keyMask;
		}
	}

	std::uint32_t InputMap::ScePadOffsetToXInput(std::uint32_t keyMask)
	{
		switch (keyMask) {
		case REX::PS4::SCE_PAD_BUTTON_UP:
			return REX::W32::XINPUT_GAMEPAD_DPAD_UP;
		case REX::PS4::SCE_PAD_BUTTON_DOWN:
			return REX::W32::XINPUT_GAMEPAD_DPAD_DOWN;
		case REX::PS4::SCE_PAD_BUTTON_LEFT:
			return REX::W32::XINPUT_GAMEPAD_DPAD_LEFT;
		case REX::PS4::SCE_PAD_BUTTON_RIGHT:
			return REX::W32::XINPUT_GAMEPAD_DPAD_RIGHT;
		case REX::PS4::SCE_PAD_BUTTON_OPTIONS:
			return REX::W32::XINPUT_GAMEPAD_START;
		case REX::PS4::SCE_PAD_BUTTON_TOUCH_PAD:
			return REX::W32::XINPUT_GAMEPAD_BACK;
		case REX::PS4::SCE_PAD_BUTTON_L3:
			return REX::W32::XINPUT_GAMEPAD_LEFT_THUMB;
		case REX::PS4::SCE_PAD_BUTTON_R3:
			return REX::W32::XINPUT_GAMEPAD_RIGHT_THUMB;
		case REX::PS4::SCE_PAD_BUTTON_L1:
			return REX::W32::XINPUT_GAMEPAD_LEFT_SHOULDER;
		case REX::PS4::SCE_PAD_BUTTON_R1:
			return REX::W32::XINPUT_GAMEPAD_RIGHT_SHOULDER;
		case REX::PS4::SCE_PAD_BUTTON_CROSS:
			return REX::W32::XINPUT_GAMEPAD_A;
		case REX::PS4::SCE_PAD_BUTTON_CIRCLE:
			return REX::W32::XINPUT_GAMEPAD_B;
		case REX::PS4::SCE_PAD_BUTTON_SQUARE:
			return REX::W32::XINPUT_GAMEPAD_X;
		case REX::PS4::SCE_PAD_BUTTON_TRIANGLE:
			return REX::W32::XINPUT_GAMEPAD_Y;
		default:
			return keyMask;
		}
	}

	std::uint32_t InputMap::GamepadMaskToKeycode(std::uint32_t keyMask)
	{
		if (RE::ControlMap::GetSingleton()->GetGamePadType() == RE::PC_GAMEPAD_TYPE::kOrbis) {
			keyMask = ScePadOffsetToXInput(keyMask);
		}

		switch (keyMask) {
		case REX::W32::XINPUT_GAMEPAD_DPAD_UP:
			return kGamepadButtonOffset_DPAD_UP;
		case REX::W32::XINPUT_GAMEPAD_DPAD_DOWN:
			return kGamepadButtonOffset_DPAD_DOWN;
		case REX::W32::XINPUT_GAMEPAD_DPAD_LEFT:
			return kGamepadButtonOffset_DPAD_LEFT;
		case REX::W32::XINPUT_GAMEPAD_DPAD_RIGHT:
			return kGamepadButtonOffset_DPAD_RIGHT;
		case REX::W32::XINPUT_GAMEPAD_START:
			return kGamepadButtonOffset_START;
		case REX::W32::XINPUT_GAMEPAD_BACK:
			return kGamepadButtonOffset_BACK;
		case REX::W32::XINPUT_GAMEPAD_LEFT_THUMB:
			return kGamepadButtonOffset_LEFT_THUMB;
		case REX::W32::XINPUT_GAMEPAD_RIGHT_THUMB:
			return kGamepadButtonOffset_RIGHT_THUMB;
		case REX::W32::XINPUT_GAMEPAD_LEFT_SHOULDER:
			return kGamepadButtonOffset_LEFT_SHOULDER;
		case REX::W32::XINPUT_GAMEPAD_RIGHT_SHOULDER:
			return kGamepadButtonOffset_RIGHT_SHOULDER;
		case REX::W32::XINPUT_GAMEPAD_A:
			return kGamepadButtonOffset_A;
		case REX::W32::XINPUT_GAMEPAD_B:
			return kGamepadButtonOffset_B;
		case REX::W32::XINPUT_GAMEPAD_X:
			return kGamepadButtonOffset_X;
		case REX::W32::XINPUT_GAMEPAD_Y:
			return kGamepadButtonOffset_Y;
		case 0x9:  // Left Trigger game-defined ID
			return kGamepadButtonOffset_LT;
		case 0xA:  // Right Trigger game-defined ID
			return kGamepadButtonOffset_RT;
		default:
			return kMaxMacros;  // Invalid
		}
	}

	std::uint32_t InputMap::GamepadKeycodeToMask(std::uint32_t keyCode)
	{
		std::uint32_t keyMask;

		switch (keyCode) {
		case kGamepadButtonOffset_DPAD_UP:
			keyMask = REX::W32::XINPUT_GAMEPAD_DPAD_UP;
			break;
		case kGamepadButtonOffset_DPAD_DOWN:
			keyMask = REX::W32::XINPUT_GAMEPAD_DPAD_DOWN;
			break;
		case kGamepadButtonOffset_DPAD_LEFT:
			keyMask = REX::W32::XINPUT_GAMEPAD_DPAD_LEFT;
			break;
		case kGamepadButtonOffset_DPAD_RIGHT:
			keyMask = REX::W32::XINPUT_GAMEPAD_DPAD_RIGHT;
			break;
		case kGamepadButtonOffset_START:
			keyMask = REX::W32::XINPUT_GAMEPAD_START;
			break;
		case kGamepadButtonOffset_BACK:
			keyMask = REX::W32::XINPUT_GAMEPAD_BACK;
			break;
		case kGamepadButtonOffset_LEFT_THUMB:
			keyMask = REX::W32::XINPUT_GAMEPAD_LEFT_THUMB;
			break;
		case kGamepadButtonOffset_RIGHT_THUMB:
			keyMask = REX::W32::XINPUT_GAMEPAD_RIGHT_THUMB;
			break;
		case kGamepadButtonOffset_LEFT_SHOULDER:
			keyMask = REX::W32::XINPUT_GAMEPAD_LEFT_SHOULDER;
			break;
		case kGamepadButtonOffset_RIGHT_SHOULDER:
			keyMask = REX::W32::XINPUT_GAMEPAD_RIGHT_SHOULDER;
			break;
		case kGamepadButtonOffset_A:
			keyMask = REX::W32::XINPUT_GAMEPAD_A;
			break;
		case kGamepadButtonOffset_B:
			keyMask = REX::W32::XINPUT_GAMEPAD_B;
			break;
		case kGamepadButtonOffset_X:
			keyMask = REX::W32::XINPUT_GAMEPAD_X;
			break;
		case kGamepadButtonOffset_Y:
			keyMask = REX::W32::XINPUT_GAMEPAD_Y;
			break;
		case kGamepadButtonOffset_LT:
			keyMask = 0x9;  // Left Trigger game-defined ID
			break;
		case kGamepadButtonOffset_RT:
			keyMask = 0xA;  // Right Trigger game-defined ID
			break;
		default:
			keyMask = 0xFF;  // Invalid
			break;
		}

		if (RE::ControlMap::GetSingleton()->GetGamePadType() == RE::PC_GAMEPAD_TYPE::kOrbis) {
			keyMask = XInputToScePadOffset(keyMask);
		}

		return keyMask;
	}

	std::string InputMap::GetKeyName(std::uint32_t a_keyCode)
	{
		if (a_keyCode >= kMacro_MouseButtonOffset && a_keyCode < kMacro_GamepadOffset) {
			return GetMouseButtonName(a_keyCode);
		} else if (a_keyCode >= kMacro_GamepadOffset && a_keyCode < kMaxMacros) {
			return GetGamepadButtonName(a_keyCode);
		} else {
			return GetKeyboardKeyName(a_keyCode);
		}
	}

	std::string InputMap::GetKeyboardKeyName(std::uint32_t a_keyCode)
	{
		std::int32_t scancode = static_cast<std::int32_t>(a_keyCode & 0xFF);

		switch (scancode) {
		case REX::W32::DIK_NUMPADENTER:  // Numpad Enter
			scancode = 0x11C;
			break;
		case REX::W32::DIK_RCONTROL:  // Right Control
			scancode = 0x11D;
			break;
		case REX::W32::DIK_DIVIDE:  // Numpad /
			scancode = 0x135;
			break;
		case REX::W32::DIK_RALT:  // Right Alt
			scancode = 0x138;
			break;
		case REX::W32::DIK_HOME:  // Home
			scancode = 0x147;
			break;
		case REX::W32::DIK_UPARROW:  // Up Arrow
			scancode = 0x148;
			break;
		case REX::W32::DIK_PGUP:  // Page Up
			scancode = 0x149;
			break;
		case REX::W32::DIK_LEFTARROW:  // Left Arrow
			scancode = 0x14B;
			break;
		case REX::W32::DIK_RIGHTARROW:  // Right Arrow
			scancode = 0x14D;
			break;
		case REX::W32::DIK_END:  // End
			scancode = 0x14F;
			break;
		case REX::W32::DIK_DOWNARROW:  // Down Arrow
			scancode = 0x150;
			break;
		case REX::W32::DIK_PGDN:  // Page Down
			scancode = 0x151;
			break;
		case REX::W32::DIK_INSERT:  // Insert
			scancode = 0x152;
			break;
		case REX::W32::DIK_DELETE:  // Delete
			scancode = 0x153;
			break;
		}

		std::int32_t lParam = scancode << 16;

		if (scancode == 0x45) {
			lParam |= (0x1 << 24);
		}

		wchar_t      buffer[REX::W32::MAX_PATH];
		auto         length = REX::W32::GetKeyNameTextW(lParam, buffer, REX::W32::MAX_PATH);
		std::wstring keyNameW{ buffer, static_cast<std::size_t>(length) };

		return stl::utf16_to_utf8(keyNameW).value_or(""s);
	}

	std::string InputMap::GetMouseButtonName(std::uint32_t a_keyCode)
	{
		switch (a_keyCode) {
		case 256:
			return "Left Mouse Button"s;
		case 257:
			return "Right Mouse Button"s;
		case 258:
			return "Middle Mouse Button"s;
		case 259:
			return "Mouse Button 3"s;
		case 260:
			return "Mouse Button 4"s;
		case 261:
			return "Mouse Button 5"s;
		case 262:
			return "Mouse Button 6"s;
		case 263:
			return "Mouse Button 7"s;
		case 264:
			return "Mouse Wheel Up"s;
		case 265:
			return "Mouse Wheel Down"s;
		default:
			return ""s;
		}
	}

	std::string InputMap::GetGamepadButtonName(std::uint32_t a_keyCode)
	{
		switch (a_keyCode) {
		case kGamepadButtonOffset_DPAD_UP:
			return "Gamepad DPad Up"s;
		case kGamepadButtonOffset_DPAD_DOWN:
			return "Gamepad DPad Down"s;
		case kGamepadButtonOffset_DPAD_LEFT:
			return "Gamepad DPad Left"s;
		case kGamepadButtonOffset_DPAD_RIGHT:
			return "Gamepad DPad Right"s;
		case kGamepadButtonOffset_START:
			return "Gamepad Start"s;
		case kGamepadButtonOffset_BACK:
			return "Gamepad Back"s;
		case kGamepadButtonOffset_LEFT_THUMB:
			return "Gamepad Left Thumb"s;
		case kGamepadButtonOffset_RIGHT_THUMB:
			return "Gamepad Right Thumb"s;
		case kGamepadButtonOffset_LEFT_SHOULDER:
			return "Gamepad Left Shoulder"s;
		case kGamepadButtonOffset_RIGHT_SHOULDER:
			return "Gamepad Right Shoulder"s;
		case kGamepadButtonOffset_A:
			return "Gamepad A"s;
		case kGamepadButtonOffset_B:
			return "Gamepad B"s;
		case kGamepadButtonOffset_X:
			return "Gamepad X"s;
		case kGamepadButtonOffset_Y:
			return "Gamepad Y"s;
		case kGamepadButtonOffset_LT:
			return "Gamepad LT"s;
		case kGamepadButtonOffset_RT:
			return "Gamepad RT"s;
		default:
			return ""s;
		}
	}
}
