#include "RE/B/BSMultiBoundNode.h"

using namespace REL;

namespace RE
{
#if !defined(ENABLE_SKYRIM_VR) || (!defined(ENABLE_SKYRIM_AE) && !defined(ENABLE_SKYRIM_VR))
	BSMultiBoundRoom* BSMultiBoundNode::GetMultiBoundRoom()
	{
		return RelocateVirtual<decltype(&BSMultiBoundNode::GetMultiBoundRoom)>(0x3E, 0x3F, this);
	}

	bool BSMultiBoundNode::QPointWithin(const NiPoint3& a_point)
	{
		return RelocateVirtual<decltype(&BSMultiBoundNode::QPointWithin)>(0x3F, 0x40, this, a_point);
	}

	bool BSMultiBoundNode::CheckBound1(const BSMultiBound& a_targetBound)
	{
		return RelocateVirtual<decltype(&BSMultiBoundNode::CheckBound1)>(0x40, 0x41, this, a_targetBound);
	}

	bool BSMultiBoundNode::CheckBound2(const NiBound& a_targetBound)
	{
		return RelocateVirtual<decltype(&BSMultiBoundNode::CheckBound2)>(0x41, 0x42, this, a_targetBound);
	}
#endif
}
