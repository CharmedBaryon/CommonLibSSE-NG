#pragma once

namespace RE
{
#ifdef ENABLE_SKYRIM_VR
	struct VRResetHMDHeight
	{
	public:
		// members
	private:
		KEEP_FOR_RE()
	};
	//static_assert(sizeof(VRResetHMDHeight) == 0x0); // TODO: Find how this is constructed, may be unused?
#endif
}
