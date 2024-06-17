#pragma once

namespace RE
{
	struct INPUT_DEVICES
	{
		enum INPUT_DEVICE
		{
			kNone = static_cast<std::underlying_type_t<INPUT_DEVICE>>(-1),
			kKeyboard = 0,
			kMouse = 1,
			kGamepad = 2,
			kFlatVirtualKeyboard = 3,
			kFlatTotal = 4,
#ifdef ENABLE_SKYRIM_VR
			kVivePrimary = 3,
			kViveSecondary = 4,
			kOculusPrimary = 5,
			kOculusSecondary = 6,
			kWMRPrimary = 7,
			kWMRSecondary = 8,
			kVRVirtualKeyboard = 9,
			kVRTotal = 10,
			kTotal = 10,
#else
			kTotal = 4,
#endif
		};
		static_assert(sizeof(INPUT_DEVICE) == 0x4);

	public:
		[[nodiscard]] static SKYRIM_REL_VR INPUT_DEVICE VirtualKeyboard()
		{
			if SKYRIM_REL_VR_CONSTEXPR (REL::Module::IsVR()) {
				return static_cast<INPUT_DEVICE>(INPUT_DEVICES::kTotal - 1);
			} else {
				return INPUT_DEVICES::kFlatVirtualKeyboard;
			}
		}
	};
	using INPUT_DEVICE = INPUT_DEVICES::INPUT_DEVICE;
}
