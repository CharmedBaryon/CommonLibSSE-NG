#pragma once

namespace RE
{
	struct INPUT_DEVICES
	{
		enum INPUT_DEVICE
		{
			kNone = static_cast<std::underlying_type_t<INPUT_DEVICE>>(-1),
			kKeyboard = 0,
			kMouse,
			kGamepad,
			kVirtualKeyboard,
#ifdef ENABLE_SKYRIM_VR
			kVRRight = 5,
			kVRLeft = 6,
#endif

			kTotal
		};
		static_assert(sizeof(INPUT_DEVICE) == 0x4);
	};
	using INPUT_DEVICE = INPUT_DEVICES::INPUT_DEVICE;
}
