#include "RE/B/BSValueNode.h"

#include "REL/Relocation.h"

namespace RE
{
#ifdef SKYRIM_CROSS_VR
	bool BSValueNode::ParseNameForValue()
	{
		return REL::RelocateVirtual<decltype(&BSValueNode::ParseNameForValue)>(0x35, 0x36, this);
	}
#endif
}
