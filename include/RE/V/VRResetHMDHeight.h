#pragma once

namespace RE
{
#ifdef ENABLE_SKYRIM_VR
	struct VRResetHMDHeight
	{
	public:
		// members
	};
	//static_assert(sizeof(VRResetHMDHeight) == 0x0); // TODO: Find how this is constructed, may be unused?
#endif
}
