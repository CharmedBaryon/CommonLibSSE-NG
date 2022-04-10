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
			kVRRight = 5,
			kVRLeft = 6,

			kTotal
		};
		static_assert(sizeof(INPUT_DEVICE) == 0x4);
	};
	using INPUT_DEVICE = INPUT_DEVICES::INPUT_DEVICE;
}
