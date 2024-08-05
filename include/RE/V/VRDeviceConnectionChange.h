#pragma once

namespace RE
{
#ifdef ENABLE_SKYRIM_VR
	struct VRDeviceConnectionChange
	{
	public:
		// members
		bool          unk00;
		std::uint32_t unk04;

	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(VRDeviceConnectionChange) == 0x8);
#endif
}
