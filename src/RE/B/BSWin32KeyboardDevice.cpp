#include "RE/B/BSWin32KeyboardDevice.h"

namespace RE
{
	bool BSWin32KeyboardDevice::IsPressed(std::uint32_t a_keyCode) const
	{
		return (a_keyCode < sizeof(curState)) && ((curState[a_keyCode] & 0x80) != 0);
	}

	BSKeyboardDevice::Key BSWin32KeyboardDevice::RemapNumpadKey(REX::W32::DIK a_key)
	{
		if (REX::W32::GetKeyState(REX::W32::VK::VK_NUMLOCK) != 1) {
			return Key::kNone;
		}
		switch (a_key) {
		case REX::W32::DIK::DIK_NUMPAD7:
			return Key::kKP_Multiply;
		case REX::W32::DIK::DIK_NUMPAD8:
			return Key::kLeftAlt;
		case REX::W32::DIK::DIK_NUMPAD9:
			return Key::kSpacebar;
		case REX::W32::DIK::DIK_NUMPAD4:
			return Key::kPeriod;
		case REX::W32::DIK::DIK_NUMPAD5:
			return Key::kSlash;
		case REX::W32::DIK::DIK_NUMPAD6:
			return Key::kRightShift;
		case REX::W32::DIK::DIK_NUMPAD1:
			return Key::kN;
		case REX::W32::DIK::DIK_NUMPAD2:
			return Key::kM;
		case REX::W32::DIK::DIK_NUMPAD3:
			return Key::kComma;
		case REX::W32::DIK::DIK_NUMPAD0:
			return Key::kB;
		case REX::W32::DIK::DIK_DECIMAL:
			return Key::kC;
		case REX::W32::DIK::DIK_DIVIDE:
			return Key::kV;
		default:
			break;
		}
		return Key::kNone;
	}

	BSWin32KeyboardDevice::BSWin32KeyboardDevice() :
		BSKeyboardDevice(),
		dInputDevice(nullptr),
		diObjData(),
		prevState(),
		curState(),
		capsLockOn(false)
	{}
}
